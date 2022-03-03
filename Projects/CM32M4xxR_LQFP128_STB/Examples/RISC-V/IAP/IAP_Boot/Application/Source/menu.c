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
 * @file menu.c
 * @author CMIOT Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */
/** @addtogroup CM32M4xxR_IAP_Bootloader
  * @{
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "menu.h"
#include "flash.h"
#include "xmodem.h"
#include "serial.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
typedef void (*pFunction)(void);

/* Private function prototypes -----------------------------------------------*/
void FirmwareDownload(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Download a file via serial port
  * @param  None
  * @retval None
  */
void FirmwareDownload(void)
{
  uint8_t number[11] = {0};
  uint32_t size = 0;
  xmodem_status result;

  serial_putstring((uint8_t *)"Waiting for the file to be sent ... (press 'a' to abort)\n\r");
  result = xmodem_receive();
  if (result == X_OK)
  {
	serial_putstring((uint8_t *)"\n\n\r Programming Completed Successfully!\n\r");
  }
  else
  {
	  serial_putstring((uint8_t *)"\n\rFailed to receive the file!\n\r");
  }
}


void JumpApp(void)
{
    pFunction JumpToApplication = (pFunction) USER_FLASH_BASE;
    JumpToApplication();
}

/**
  * @brief  Display the Main Menu on HyperTerminal
  * @param  None
  * @retval None
  */
void Main_Menu(void)
{
  uint8_t key = 0;

  serial_putstring((uint8_t *)"\r\n======================================================================");
  serial_putstring((uint8_t *)"\r\n=                    (C) COPYRIGHT 2020 CMIOT                        =");
  serial_putstring((uint8_t *)"\r\n=                                                                    =");
  serial_putstring((uint8_t *)"\r\n=  CM32M4xxR_LQFP128_STB In-Application Programming Application      =");
  serial_putstring((uint8_t *)"\r\n=                                                Via XModem          =");
  serial_putstring((uint8_t *)"\r\n=                                   By XinSheng Tech Co.Ltd          =");
  serial_putstring((uint8_t *)"\r\n======================================================================");
  serial_putstring((uint8_t *)"\r\n\r\n");

  while (1)
  {

	serial_putstring((uint8_t *)"\r\n=================== Main Menu ============================\r\n\n");
	serial_putstring((uint8_t *)"  Download image to the internal Flash ----------------- 1\r\n\n");
	serial_putstring((uint8_t *)"  Execute the loaded application ----------------------- 2\r\n\n");
	serial_putstring((uint8_t *)"==========================================================\r\n\n");

    /* Clean the input path */
    serial_flushdr();

    /* Receive key */
    serial_receive(&key, 1, 0xFFFFFFFF);

    switch (key)
    {
    case '1' :
      /* Download user application in the Flash */
    	FirmwareDownload();
      break;
    case '2' :
    	serial_putstring((uint8_t *)"Start User Application......\r\n\n");
      /* execute the new program */
      JumpApp();
      break;
	default:
		serial_putstring((uint8_t *)"Invalid Number ! ==> The number should be either 1 or 2\r");
	break;
    }
  }
}

/**
  * @}
  */
