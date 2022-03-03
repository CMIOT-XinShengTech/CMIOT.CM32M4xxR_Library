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
 * @file main.c
 * @author CMIOT Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */

#include <main.h>
#include <spi_flash.h>
#include <stdio.h>
#include "log.h"
#include "led.h"
#include "key.h"

/** @addtogroup CM32M4xxR_StdPeriph_Examples
 * @{
 */


/** @addtogroup SPI_FLASH
 * @{
 */

typedef enum
{
    FAILED = 0,
    PASSED = !FAILED
} TestStatus;

#define FLASH_WriteAddress		(0x001000)
#define FLASH_ReadAddress   	FLASH_WriteAddress
#define FLASH_SectorToErase 	FLASH_WriteAddress
#define FLASH_BlockToErase		FLASH_WriteAddress

#define LED1		GPIO_PIN_1	/* PB.05 */
#define LED2		GPIO_PIN_0	/* PB.01 */

#define sFLASH_ID	sFLASH_GD25Q40_ID

#define BufferSize	(countof(Tx_Buffer) - 1)

#define countof(a)	(sizeof(a) / sizeof(*(a)))

uint8_t Tx_Buffer[] = "CM32M4xxR SPI Firmware Library Example: communication with an GD25Q40 SPI FLASH";
uint8_t Rx_Buffer[BufferSize];
__IO uint8_t Index                  = 0x0;
volatile TestStatus TransferStatus1 = FAILED;
volatile TestStatus TransferStatus2 = FAILED;
__IO uint32_t FlashID				= 0;

TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);

/**
 * @brief  Main function.
 */
int main(void)
{
    /*!< At this stage the microcontroller clock setting is already configured,
         this is done through SystemInit() function which is called from startup
         file (startup_cm32m4xxr.s) before to branch to application main.
         To reconfigure the default setting of SystemInit() function, refer to
         system_cm32m4xxr.c file
       */

	log_init();
	log_info("This is a SPI_FLASH demo-----------------------------------\r\n");

    LedInit(GPIOB, LED1);
    LedOff(GPIOB, LED1);
    LedInit(GPIOB, LED2);
    LedOff(GPIOB, LED2);
    KeyInputInit(GPIOA, GPIO_PIN_0);

    while (KeyReadValue(GPIOA, GPIO_PIN_0) == RESET)
    {
    }
	GPIO_ConfigPinRemap(GPIO_RMP_SW_JTAG_DISABLE,ENABLE);

    /* Initialize the SPI FLASH driver */
    sFLASH_Init();

    /* Get SPI Flash ID */
    FlashID = sFLASH_ReadID();

    /* Check the SPI Flash ID */
    if (FlashID == sFLASH_ID)
    {
        /* OK: Turn on LED1 */
        LedOn(GPIOB, LED1);

        /* Perform a write in the Flash followed by a read of the written data */
        /* Erase SPI FLASH Sector to write on */
        sFLASH_EraseSector(FLASH_SectorToErase);

        /* Write Tx_Buffer data to SPI FLASH memory */
        sFLASH_WriteBuffer(Tx_Buffer, FLASH_WriteAddress, BufferSize);

        /* Read data from SPI FLASH memory */
        sFLASH_ReadBuffer(Rx_Buffer, FLASH_ReadAddress, BufferSize);

        /* Check the correctness of written data */
        /* TransferStatus1 = PASSED, if the transmitted and received data by SPI1
           are the same */
        /* TransferStatus1 = FAILED, if the transmitted and received data by SPI1
           are different */
        TransferStatus1 = Buffercmp(Tx_Buffer, Rx_Buffer, BufferSize);

        log_info("%s\r\n", Rx_Buffer);

        /* Perform an erase in the Flash followed by a read of the written data */
        /*  Erase entire SPI FLASH */
//        sFLASH_EraseChip();

        /* Erase SPI FLASH Block to write on */
//        sFLASH_EraseBlock(FLASH_BlockToErase);

        /* Erase SPI FLASH Sector to write on */
        sFLASH_EraseSector(FLASH_SectorToErase);

        /* Read data from SPI FLASH memory */
        sFLASH_ReadBuffer(Rx_Buffer, FLASH_ReadAddress, BufferSize);

        /* Check the correctness of erasing operation data */
        /* TransferStatus2 = PASSED, if the specified sector part is erased */
        /* TransferStatus2 = FAILED, if the specified sector part is not well erased */
        TransferStatus2 = PASSED;
        for (Index = 0; Index < BufferSize; Index++)
        {
            if (Rx_Buffer[Index] != 0xFF)
            {
                TransferStatus2 = FAILED;
                break;
            }
        }
    }
    else
    {
        /* Error: Turn on LED2 */
        LedOn(GPIOB, LED2);
    }

    if ((TransferStatus1 == FAILED) || (TransferStatus2 == FAILED))
    {
        /* OK: Turn on LED1 */
        LedOff(GPIOB, LED1);
        /* Error: Turn on LED2 */
        LedOn(GPIOB, LED2);
    	log_info("CM32M4xxR SPI Firmware Library Example: FAILED,Status1:%d, Status2:%d\r\n", TransferStatus1, TransferStatus2);
    }
    else
    {
    	log_info("CM32M4xxR SPI Firmware Library Example: PASSED\r\n");
    }

	GPIO_ConfigPinRemap(GPIO_RMP_SW_JTAG_DISABLE,DISABLE);
    while (1)
    {
    }
}

/**
 * @brief  Compares two buffers.
 * @param  pBuffer1, pBuffer2: buffers to be compared.
 * @param BufferLength buffer's length
 * @return PASSED: pBuffer1 identical to pBuffer2
 *         FAILED: pBuffer1 differs from pBuffer2
 */
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
    while (BufferLength--)
    {
        if (*pBuffer1 != *pBuffer2)
        {
            return FAILED;
        }

        pBuffer1++;
        pBuffer2++;
    }

    return PASSED;
}

/**
 * @}
 */

/**
 * @}
 */
