/*******************************************************************************
 *
 * COPYRIGHT(c) 2020, China Mobile IOT
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *	1. Redistributions of source code must retain the above copyright notice,
 *	   this list of conditions and the following disclaimer.
 *	2. Redistributions in binary form must reproduce the above copyright notice,
 *	   this list of conditions and the following disclaimer in the documentation
 *	   and/or other materials provided with the distribution.
 *	3. Neither the name of China Mobile IOT nor the names of its contributors
 *	   may be used to endorse or promote products derived from this software
 *	   without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *******************************************************************************/

/**
 * @file xmodem.c
 * @author CMIOT Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 * Copyright (c) 2018 Ferenc Nemeth - https://github.com/ferenc-nemeth
 */
/** @addtogroup CM32M4xxR_IAP_Bootloader
  * @{
  */

#include "xmodem.h"
#include "serial.h"
#include "flash.h"

/* Global variables. */
static uint8_t xmodem_packet_number = 1u;         /**< Packet number counter. */
static uint32_t xmodem_actual_flash_address = 0u; /**< Address where we have to write. */
static uint8_t x_first_packet_received = false;   /**< First packet or not. */

/* 2 bytes for packet number, 1024 for data, 2 for CRC*/
static uint8_t received_packet_number[X_PACKET_NUMBER_SIZE];
static uint8_t received_packet_data[X_PACKET_1024_SIZE];
static uint8_t received_packet_crc[X_PACKET_CRC_SIZE];

/* Local functions. */
static uint16_t xmodem_calc_crc(uint8_t *data, uint16_t length);
static xmodem_status xmodem_handle_packet(uint8_t size);
static xmodem_status xmodem_error_handler(uint8_t *error_number, uint8_t max_error_number);

/**
 * @brief   This function is the base of the Xmodem protocol.
 *          When we receive a header from UART, it decides what action it shall take.
 * @param   void
 * @return  void
 */
xmodem_status xmodem_receive(void)
{
  volatile xmodem_status status = X_OK;
  uint8_t error_number = 0u;

  x_first_packet_received = false;
  xmodem_packet_number = 1u;
  xmodem_actual_flash_address = USER_FLASH_BASE;

  /* Loop until there isn't any error (or until we jump to the user application). */
  while (X_OK == status)
  {
    uint8_t header = 0x00u;

    /* Get the header from UART. */
    ErrorStatus comm_status = serial_receive(&header, 1u, 1000);

    /* Spam the host (until we receive something) with ACSII "C", to notify it, we want to use CRC-16. */
    if ((SUCCESS != comm_status) && (false == x_first_packet_received))
    {
      serial_transmitbyte(X_C);
    }
    /* Uart timeout or any other errors. */
    else if ((SUCCESS != comm_status) && (true == x_first_packet_received))
    {
      status = xmodem_error_handler(&error_number, X_MAX_ERRORS);
    }
    else
    {
      /* Do nothing. */
    }
    xmodem_status packet_status = X_ERROR;
    /* The header can be: SOH, STX, EOT and CAN. */
    switch(header)
    {
      /* 128 or 1024 bytes of data. */
      case X_SOH:
      case X_STX:
        /* If the handling was successful, then send an ACK. */
        packet_status = xmodem_handle_packet(header);
        if (X_OK == packet_status)
        {
          (void)serial_transmitbyte(X_ACK);
        }
        /* If the error was flash related, then immediately set the error counter to max (graceful abort). */
        else if (X_ERROR_FLASH == packet_status)
        {
          error_number = X_MAX_ERRORS;
          status = xmodem_error_handler(&error_number, X_MAX_ERRORS);
        }
        /* Error while processing the packet, either send a NAK or do graceful abort. */
        else
        {
          status = xmodem_error_handler(&error_number, X_MAX_ERRORS);
        }
        break;
      /* End of Transmission. */
      case X_EOT:
        /* ACK, feedback to user (as a text), then jump to user application. */
        (void)serial_transmitbyte(X_ACK);
        (void)serial_putstring((uint8_t*)"\n\rFirmware updated!\n\r");
        return X_OK;
      /* Abort from host. */
      case X_CAN:
        status = X_ERROR;
        break;
      default:
        /* Wrong header. */
        if (SUCCESS == comm_status)
        {
          status = xmodem_error_handler(&error_number, X_MAX_ERRORS);
        }
        break;
    }
  }
  return status;
}

/**
 * @brief   Calculates the CRC-16 for the input package.
 * @param   *data:  Array of the data which we want to calculate.
 * @param   length: Size of the data, either 128 or 1024 bytes.
 * @return  status: The calculated CRC.
 */
static uint16_t xmodem_calc_crc(uint8_t *data, uint16_t length)
{
    uint16_t crc = 0u;
    while (length)
    {
        length--;
        crc = crc ^ ((uint16_t)*data++ << 8u);
        for (uint8_t i = 0u; i < 8u; i++)
        {
            if (crc & 0x8000u)
            {
                crc = (crc << 1u) ^ 0x1021u;
            }
            else
            {
                crc = crc << 1u;
            }
        }
    }
    return crc;
}

/**
 * @brief   This function handles the data packet we get from the xmodem protocol.
 * @param   header: SOH or STX.
 * @return  status: Report about the packet.
 */
static xmodem_status xmodem_handle_packet(uint8_t header)
{
  xmodem_status status = X_OK;
  uint16_t size = 0u;

  /* Get the size of the data. */
  if (X_SOH == header)
  {
    size = X_PACKET_128_SIZE;
  }
  else if (X_STX == header)
  {
    size = X_PACKET_1024_SIZE;
  }
  else
  {
    /* Wrong header type. This shoudn't be possible... */
    status |= X_ERROR;
  }

  ErrorStatus comm_status = SUCCESS;
  /* Get the packet number, data and CRC from UART. */
  comm_status |= serial_receive(&received_packet_number[0u], X_PACKET_NUMBER_SIZE, 1000);
  comm_status |= serial_receive(&received_packet_data[0u], size, 1000);
  comm_status |= serial_receive(&received_packet_crc[0u], X_PACKET_CRC_SIZE, 1000);
  /* Merge the two bytes of CRC. */
  uint16_t crc_received = ((uint16_t)received_packet_crc[X_PACKET_CRC_HIGH_INDEX] << 8u) | ((uint16_t)received_packet_crc[X_PACKET_CRC_LOW_INDEX]);
  /* We calculate it too. */
  uint16_t crc_calculated = xmodem_calc_crc(&received_packet_data[0u], size);

  /* Communication error. */
  if (SUCCESS != comm_status)
  {
    status |= X_ERROR_UART;
  }

  /* If it is the first packet, then erase the memory. */
  if ((X_OK == status) && (false == x_first_packet_received))
  {
    if (FLASH_OK == FLASH_EraseUser())
    {
      x_first_packet_received = true;
    }
    else
    {
      status |= X_ERROR_FLASH;
    }
  }

  /* Error handling and flashing. */
  if (X_OK == status)
  {
    if (xmodem_packet_number != received_packet_number[0u])
    {
      /* Packet number counter mismatch. */
      status |= X_ERROR_NUMBER;
    }
    if (255u != (received_packet_number[X_PACKET_NUMBER_INDEX] + received_packet_number[X_PACKET_NUMBER_COMPLEMENT_INDEX]))
    {
      /* The sum of the packet number and packet number complement aren't 255. */
      /* The sum always has to be 255. */
      status |= X_ERROR_NUMBER;
    }
    if (crc_calculated != crc_received)
    {
      /* The calculated and received CRC are different. */
      status |= X_ERROR_CRC;
    }
  }

    /* Do the actual flashing (if there weren't any errors). */
    if ((X_OK == status) && (FLASH_OK != FLASH_WriteUser(xmodem_actual_flash_address, (uint32_t*)&received_packet_data[0u], (uint32_t)size/4u)))
    {
      /* Flashing error. */
      status |= X_ERROR_FLASH;
    }

  /* Raise the packet number and the address counters (if there weren't any errors). */
  if (X_OK == status)
  {
    xmodem_packet_number++;
    xmodem_actual_flash_address += size;
  }

  return status;
}

/**
 * @brief   Handles the xmodem error.
 *          Raises the error counter, then if the number of the errors reached critical, do a graceful abort, otherwise send a NAK.
 * @param   *error_number:    Number of current errors (passed as a pointer).
 * @param   max_error_number: Maximal allowed number of errors.
 * @return  status: X_ERROR in case of too many errors, X_OK otherwise.
 */
static xmodem_status xmodem_error_handler(uint8_t *error_number, uint8_t max_error_number)
{
  xmodem_status status = X_OK;
  /* Raise the error counter. */
  (*error_number)++;
  /* If the counter reached the max value, then abort. */
  if ((*error_number) >= max_error_number)
  {
    /* Graceful abort. */
    serial_transmitbyte(X_CAN);
    serial_transmitbyte(X_CAN);
    status = X_ERROR;
  }
  /* Otherwise send a NAK for a repeat. */
  else
  {
	  serial_transmitbyte(X_NAK);
    status = X_OK;
  }
  return status;
}
