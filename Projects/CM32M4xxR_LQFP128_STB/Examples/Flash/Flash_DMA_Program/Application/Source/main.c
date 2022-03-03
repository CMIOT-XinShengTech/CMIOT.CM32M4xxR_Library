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

#include "main.h"
#include "log.h"

#include <string.h>

/** @addtogroup CM32M4xxR_StdPeriph_Examples
 * @{
 */

/**
 *  Flash_DMA_Program
 */

#define FLASH_PAGE_SIZE       	((uint16_t) 0x800) /* 2K bytes per page */
#define FLASH_WRITE_START_ADDR 	((uint32_t) 0x08010000)
#define FLASH_WRITE_END_ADDR   	((uint32_t) 0x08018000)

#define FLASH_PROGRAM_TIMEOUT 	((uint32_t) 0x00002000)

#define BUFFER_SIZE				((uint32_t) 32)

uint32_t* Flash_Data_Buffer = (uint32_t *)FLASH_WRITE_START_ADDR;

const uint32_t SRAM_Data_Buffer[BUFFER_SIZE] = {
    0x01020304, 0x05060708, 0x090A0B0C, 0x0D0E0F10, 0x11121314, 0x15161718, 0x191A1B1C, 0x1D1E1F20,
    0x21222324, 0x25262728, 0x292A2B2C, 0x2D2E2F30, 0x31323334, 0x35363738, 0x393A3B3C, 0x3D3E3F40,
    0x41424344, 0x45464748, 0x494A4B4C, 0x4D4E4F50, 0x51525354, 0x55565758, 0x595A5B5C, 0x5D5E5F60,
    0x61626364, 0x65666768, 0x696A6B6C, 0x6D6E6F70, 0x71727374, 0x75767778, 0x797A7B7C, 0x7D7E7F80};

void DMA_Flash_SRAM_Config(void);
uint8_t Buffercmp(const uint32_t* pBuffer1, uint32_t* pBuffer2, uint32_t BufferLength);

/**
 * @brief  Main function.
 */
int main(void)
{
    uint8_t Test_Result = 0;

    /* USART Init */
    log_init();

    log_info("Flash DMA Program Test Start\r\n");

    /* Program FLASH - Transmit Data From SRAM To FLASH */
    /* Unlocks the FLASH Program Erase Controller */
    FLASH_Unlock();

    /* Erase */
    if (FLASH_COMPL == FLASH_EraseOnePage(FLASH_WRITE_START_ADDR))
    {
        /* Clear All pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);

		/* if the previous operation is completed, proceed to program the new data */
		FLASH->CTRL |= FLASH_CTRL_PG;

		/* Start DMA Program FLASH */
		DMA_Flash_SRAM_Config();

		/* Wait for last operation to be completed */
		while (FLASH_COMPL == FLASH_WaitForLastOpt(FLASH_PROGRAM_TIMEOUT))
		{
			/* Check */
			if (PASSED == Buffercmp(SRAM_Data_Buffer, Flash_Data_Buffer, BUFFER_SIZE))
			{
				/* Test PASSED */
				Test_Result = PASSED;
				break;
			}
		}
    }
    else
    {
        /* Test Fail */
        Test_Result = FAILED;
    }

    /* Locks the FLASH Program Erase Controller */
    FLASH_Lock();

    if (Test_Result == FAILED)
    {
    	log_info("Test_Result = FAILED\r\n");
    }
    else
    {
    	log_info("Test_Result = PASSED\r\n");
    }

    while (1)
    {
    }
}

/**
 * @brief  DMA_Flash_SRAM_Config.
 */
void DMA_Flash_SRAM_Config(void)
{
    DMA_InitType DMA_InitStructure;

    /* DMA1 channel6 configuration */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_DMA1, ENABLE);

    DMA_InitStructure.PeriphAddr     = (uint32_t)SRAM_Data_Buffer;
    DMA_InitStructure.MemAddr        = (uint32_t)Flash_Data_Buffer;
    DMA_InitStructure.Direction      = DMA_DIR_PERIPH_SRC;
    DMA_InitStructure.BufSize        = BUFFER_SIZE;
    DMA_InitStructure.PeriphInc      = DMA_PERIPH_INC_ENABLE;
    DMA_InitStructure.DMA_MemoryInc  = DMA_MEM_INC_ENABLE;
    DMA_InitStructure.PeriphDataSize = DMA_PERIPH_DATA_SIZE_WORD;
    DMA_InitStructure.MemDataSize    = DMA_MEMORY_DATA_SIZE_WORD;
    DMA_InitStructure.CircularMode   = DMA_MODE_NORMAL;
    DMA_InitStructure.Priority       = DMA_PRIORITY_HIGH;
    DMA_InitStructure.Mem2Mem        = DMA_M2M_ENABLE;
    DMA_Init(DMA1_CH6, &DMA_InitStructure);

    DMA_ClearFlag(DMA1_FLAG_TC6, DMA1);
    DMA_EnableChannel(DMA1_CH6, ENABLE);
}

/**
 * @brief  Buffercmp.
 * @param  pBuffer1
 * @param  pBuffer2
 * @param  BufferLength
 */
uint8_t Buffercmp(const uint32_t* pBuffer1, uint32_t* pBuffer2, uint32_t BufferLength)
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

