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
#include "log.h"

#include <string.h>

/** @addtogroup CM32M4xxR_StdPeriph_Examples
 * @{
 */

/**
 *  Flash_RAM
 */

#define BUFFER_SIZE	(sizeof(SRC_Const_Buffer)/sizeof(SRC_Const_Buffer[0]))

DMA_InitType DMA_InitStructure;
__IO uint32_t CurrDataCounterBegin = 0;
__IO uint32_t CurrDataCounterEnd   = 0x01; /* This variable should not be initialized to 0 */

const uint32_t SRC_Const_Buffer[] = {
    0x72aa0305, 0x839916bf, 0x913782c5, 0x7e3bd953, 0x4174430c, 0x40d59981, 0xbccff537, 0xd22bca1a,
    0xda039c07, 0xff38219a, 0x17f16c33, 0x0056b9cf, 0x4e75ab0a, 0x0751b137, 0xbb051ec9, 0xcac01e06,
    0x5de647ba, 0xf2bd2108, 0x60a32be0, 0xbf80a68f, 0x299b4a55, 0xd37b1965, 0x84a3ca5b, 0x0f08f335,
    0x21c4084b, 0x738688ca, 0xe7971a03, 0xadcd6bfc, 0xd4bb55ae, 0x0ea4ed88, 0x131711a3, 0x4e92f42f,
};

uint32_t DST_Buffer[BUFFER_SIZE];

void RCC_Configuration(void);
void ECLIC_Configuration(void);


/**
 * @brief  Main function
 */
int main(void)
{
	/* Disable global interrupt */
	__disable_irq();

    log_init();
    log_info("DMA Flash to RAM Demo\n");

    /* System Clocks Configuration */
    RCC_Configuration();

    /* ECLIC configuration */
    ECLIC_Configuration();

    /* DMA1 Channel1 configuration */
    DMA_DeInit(DMA_CHANNEL_USED);
    DMA_InitStructure.PeriphAddr     = (uint32_t)SRC_Const_Buffer;
    DMA_InitStructure.MemAddr        = (uint32_t)DST_Buffer;
    DMA_InitStructure.Direction      = DMA_DIR_PERIPH_SRC;
    DMA_InitStructure.BufSize        = BUFFER_SIZE;
    DMA_InitStructure.PeriphInc      = DMA_PERIPH_INC_ENABLE;
    DMA_InitStructure.DMA_MemoryInc  = DMA_MEM_INC_ENABLE;
    DMA_InitStructure.PeriphDataSize = DMA_PERIPH_DATA_SIZE_WORD;
    DMA_InitStructure.MemDataSize    = DMA_MEMORY_DATA_SIZE_WORD;
    DMA_InitStructure.CircularMode   = DMA_MODE_NORMAL;
    DMA_InitStructure.Priority       = DMA_PRIORITY_HIGH;
    DMA_InitStructure.Mem2Mem        = DMA_M2M_ENABLE;
    DMA_Init(DMA_CHANNEL_USED, &DMA_InitStructure);

    /* Enable DMA1 Channel1 Transfer Complete interrupt */
    DMA_ConfigInt(DMA_CHANNEL_USED, DMA_INT_TXC, ENABLE);

    /* Get Current Data Counter value before transfer begins */
    CurrDataCounterBegin = DMA_GetCurrDataCounter(DMA_CHANNEL_USED);

    /* Enable global interrupt */
    __enable_irq();

    /* Enable DMA1 Channel1 transfer */
    DMA_EnableChannel(DMA_CHANNEL_USED, ENABLE);

    /* Wait the end of transmission */
    while (CurrDataCounterEnd != 0)
    {
    }

    /* Check if the transmitted and received data are equal */
    if (memcmp(SRC_Const_Buffer, DST_Buffer, BUFFER_SIZE) == 0)
    {
        log_info("DMA Flash to RAM passed\n");
    }
    else
    {
        log_error("DMA Flash to RAM failed\n");
    }

    while (1)
    {
    }
}

/**
 * @brief  Configures the different system clocks.
 */
void RCC_Configuration(void)
{
    /* Enable peripheral clocks ------------------------------------------------*/
    /* Enable DMA1 clock */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_DMA1, ENABLE);
}

/**
 * @brief  Configure the enhanced core local interrupt controller.
 */
void ECLIC_Configuration(void)
{
    /* Enable the DMA1 Channel1 Interrupt */
	ECLIC_SetLevelIRQ(DMA_IRQN, 0);
	ECLIC_SetPriorityIRQ(DMA_IRQN, 0);
	ECLIC_SetTrigIRQ(DMA_IRQN, ECLIC_LEVEL_TRIGGER);
	ECLIC_EnableIRQ(DMA_IRQN);
}

/**
 * @brief  Compares two buffers.
 * @param  pBuffer, pBuffer1: buffers to be compared.
 * @param BufferLength buffer's length
 * @return PASSED: pBuffer identical to pBuffer1
 *         FAILED: pBuffer differs from pBuffer1
 */
Status Buffercmp(const uint32_t* pBuffer, uint32_t* pBuffer1, uint16_t BufferLength)
{
    while (BufferLength--)
    {
        if (*pBuffer != *pBuffer1)
        {
            return FAILED;
        }

        pBuffer++;
        pBuffer1++;
    }

    return PASSED;
}

/**
 * @}
 */
