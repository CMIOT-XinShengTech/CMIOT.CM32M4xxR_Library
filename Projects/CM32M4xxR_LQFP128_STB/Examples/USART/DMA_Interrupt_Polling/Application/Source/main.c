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

#include <stdio.h>
#include "main.h"

/** @addtogroup CM32M4xxR_StdPeriph_Examples
 * @{
 */

/** @addtogroup USART_DMA_Interrupt_Polling
 * @{
 */

typedef enum
{
    FAILED = 0,
    PASSED = !FAILED
} TestStatus;

#define TxBufferSize1 (countof(TxBuffer1) - 1)
#define TxBufferSize2 (countof(TxBuffer2) - 1)

#define countof(a) (sizeof(a) / sizeof(*(a)))

USART_InitType USART_InitStructure;
uint8_t TxBuffer1[] = {"USART DMA: USARTy -> USARTz using Interrupt mode"};
uint8_t TxBuffer2[] = {"USART DMA: USARTz -> USARTy using Polling mode"};
uint8_t RxBuffer1[TxBufferSize2];
uint8_t RxBuffer2[TxBufferSize1];
uint8_t TxCounter1 = 0, RxCounter1 = 0;
uint8_t TxCounter2 = 0, RxCounter2 = 0;
volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED;

__IO uint8_t USARTy_Tx_Done = 0;
__IO uint8_t USARTz_Rx_Done = 0;

void RCC_Configuration(void);
void GPIO_Configuration(void);
void ECLIC_Configuration(void);
void DMA_Configuration(void);
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);

/**
 * @brief  Main function
 */
int main(void)
{
	/* Disable global interrupt */
	__disable_irq();

    /* System Clocks Configuration */
    RCC_Configuration();

    /* ECLIC configuration */
    ECLIC_Configuration();

    /* Configure the GPIO ports */
    GPIO_Configuration();

    /* Configure the DMA */
    DMA_Configuration();

    /* USARTy and USARTz configuration ------------------------------------------------------*/
    USART_InitStructure.BaudRate            = 115200;
    USART_InitStructure.WordLength          = USART_WL_8B;
    USART_InitStructure.StopBits            = USART_STPB_1;
    USART_InitStructure.Parity              = USART_PE_NO;
    USART_InitStructure.HardwareFlowControl = USART_HFCTRL_NONE;
    USART_InitStructure.Mode                = USART_MODE_TX | USART_MODE_RX;

    /* Configure USARTy and USARTz */
    USART_Init(USARTy, &USART_InitStructure);
    USART_Init(USARTz, &USART_InitStructure);

    /* Enable USARTy DMA Rx and TX request */
    USART_EnableDMA(USARTy, USART_DMAREQ_RX | USART_DMAREQ_TX, ENABLE);
    /* Enable USARTz DMA Rx and TX request */
    USART_EnableDMA(USARTz, USART_DMAREQ_RX | USART_DMAREQ_TX, ENABLE);

    /* Enable the USARTy and USARTz */
	USART_Enable(USARTy, ENABLE);
	USART_Enable(USARTz, ENABLE);

	/* Enable USARTy RX DMA1 Channel */
	DMA_EnableChannel(USARTy_Rx_DMA_Channel, ENABLE);
	/* Enable USARTz RX DMA1 Channel */
	DMA_EnableChannel(USARTz_Rx_DMA_Channel, ENABLE);

	/* Enable USARTy TX DMA1 Channel */
	DMA_EnableChannel(USARTy_Tx_DMA_Channel, ENABLE);
	/* Enable USARTz TX DMA1 Channel */
	DMA_EnableChannel(USARTz_Tx_DMA_Channel, ENABLE);

    /* Enable global interrupt */
    __enable_irq();

    /* Wait until USARTy TX DMA Channel Transfer Complete */
    while(!USARTy_Tx_Done)
    {        
    }    
    /* Wait until USARTz RX DMA Channel Transfer Complete */
    while(!USARTz_Rx_Done)
    {        
    }

    /* Wait until USARTz TX DMA Channel Transfer Complete */
    while (DMA_GetFlagStatus(USARTz_Tx_DMA_FLAG, USARTz_DMAx) == RESET)
    {
    }
    /* Wait until USARTy RX DMA Channel Transfer Complete */
    while (DMA_GetFlagStatus(USARTy_Rx_DMA_FLAG, USARTy_DMAx) == RESET)
    {
    }    

    /* Check the received data with the send ones */
    TransferStatus1 = Buffercmp(TxBuffer1, RxBuffer2, TxBufferSize1);

    TransferStatus2 = Buffercmp(TxBuffer2, RxBuffer1, TxBufferSize2);

    while (1)
    {
    }
}

/**
 * @brief  Configures the different system clocks.
 */
void RCC_Configuration(void)
{
    /* DMA clock enable */
    RCC_EnableAHBPeriphClk(USARTy_DMAx_CLK, ENABLE);
    RCC_EnableAHBPeriphClk(USARTz_DMAx_CLK, ENABLE);

    /* Enable GPIO clock */
    RCC_EnableAPB2PeriphClk(USARTy_GPIO_CLK | USARTz_GPIO_CLK | RCC_APB2_PERIPH_AFIO, ENABLE);

    /* Enable USARTy and USARTz Clock */
    USARTy_APBxClkCmd(USARTy_CLK, ENABLE);
    USARTz_APBxClkCmd(USARTz_CLK, ENABLE);
}

/**
 * @brief  Configures the different GPIO ports.
 */
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;
    GPIO_ConfigPinRemap(GPIO_RMP_USART1,ENABLE);

    /* Configure USARTy Rx as input floating */
	GPIO_InitStructure.Pin       = USARTy_RxPin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(USARTy_GPIO, &GPIO_InitStructure);

	/* Configure USARTz Rx as input floating */
	GPIO_InitStructure.Pin = USARTz_RxPin;
	GPIO_Init(USARTz_GPIO, &GPIO_InitStructure);

    /* Configure USARTy Tx as alternate function push-pull */
    GPIO_InitStructure.Pin        = USARTy_TxPin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_Init(USARTy_GPIO, &GPIO_InitStructure);

    /* Configure USARTz Tx as alternate function push-pull */
    GPIO_InitStructure.Pin = USARTz_TxPin;
    GPIO_Init(USARTz_GPIO, &GPIO_InitStructure);

    GPIO_ConfigPinRemap(GPIO_RMP2_UART6, ENABLE);
	GPIO_ConfigPinRemap(GPIO_RMP3_UART7, ENABLE);
}

/**
 * @brief  Configures the enhanced core local interrupt controller.
 */
void ECLIC_Configuration(void)
{
    /* Enable the USARTy_Tx DMA Interrupt */
	ECLIC_SetLevelIRQ(USARTy_Tx_DMA_IRQn, 0);
	ECLIC_SetPriorityIRQ(USARTy_Tx_DMA_IRQn, 0);
	ECLIC_SetTrigIRQ(USARTy_Tx_DMA_IRQn, ECLIC_LEVEL_TRIGGER);
	ECLIC_EnableIRQ(USARTy_Tx_DMA_IRQn);
	
	/* Enable the USARTz_Rx DMA Interrupt */
	ECLIC_SetLevelIRQ(USARTz_Rx_DMA_IRQn, 0);
	ECLIC_SetPriorityIRQ(USARTz_Rx_DMA_IRQn, 0);
	ECLIC_SetTrigIRQ(USARTz_Rx_DMA_IRQn, ECLIC_LEVEL_TRIGGER);
	ECLIC_EnableIRQ(USARTz_Rx_DMA_IRQn);
}

/**
 * @brief  Configures the DMA.
 */
void DMA_Configuration(void)
{
    DMA_InitType DMA_InitStructure;

    /* USARTy TX DMA1 Channel (triggered by USARTy Tx event) Config */
    DMA_DeInit(USARTy_Tx_DMA_Channel);
    DMA_InitStructure.PeriphAddr     = USARTy_DR_Base;
    DMA_InitStructure.MemAddr        = (uint32_t)TxBuffer1;
    DMA_InitStructure.Direction      = DMA_DIR_PERIPH_DST;
    DMA_InitStructure.BufSize        = TxBufferSize1;
    DMA_InitStructure.PeriphInc      = DMA_PERIPH_INC_DISABLE;
    DMA_InitStructure.DMA_MemoryInc  = DMA_MEM_INC_ENABLE;
    DMA_InitStructure.PeriphDataSize = DMA_PERIPH_DATA_SIZE_BYTE;
    DMA_InitStructure.MemDataSize    = DMA_MEMORY_DATA_SIZE_BYTE;
    DMA_InitStructure.CircularMode   = DMA_MODE_NORMAL;
    DMA_InitStructure.Priority       = DMA_PRIORITY_VERY_HIGH;
    DMA_InitStructure.Mem2Mem        = DMA_M2M_DISABLE;
    DMA_Init(USARTy_Tx_DMA_Channel, &DMA_InitStructure);

    /* Enable USARTy Tx DMA Channel Transfer Complete Interrupt */
    DMA_ConfigInt(USARTy_Tx_DMA_Channel, DMA_INT_TXC, ENABLE);

    /* USARTy RX DMA1 Channel (triggered by USARTy Rx event) Config */
    DMA_DeInit(USARTy_Rx_DMA_Channel);
    DMA_InitStructure.PeriphAddr = USARTy_DR_Base;
    DMA_InitStructure.MemAddr    = (uint32_t)RxBuffer1;
    DMA_InitStructure.Direction  = DMA_DIR_PERIPH_SRC;
    DMA_InitStructure.BufSize    = TxBufferSize2;
    DMA_Init(USARTy_Rx_DMA_Channel, &DMA_InitStructure);    

    /* USARTz TX DMA1 Channel (triggered by USARTz Tx event) Config */
    DMA_DeInit(USARTz_Tx_DMA_Channel);
    DMA_InitStructure.PeriphAddr = USARTz_DR_Base;
    DMA_InitStructure.MemAddr    = (uint32_t)TxBuffer2;
    DMA_InitStructure.Direction  = DMA_DIR_PERIPH_DST;
    DMA_InitStructure.BufSize    = TxBufferSize2;
    DMA_Init(USARTz_Tx_DMA_Channel, &DMA_InitStructure);

    /* USARTz RX DMA1 Channel (triggered by USARTz Rx event) Config */
    DMA_DeInit(USARTz_Rx_DMA_Channel);
    DMA_InitStructure.PeriphAddr = USARTz_DR_Base;
    DMA_InitStructure.MemAddr    = (uint32_t)RxBuffer2;
    DMA_InitStructure.Direction  = DMA_DIR_PERIPH_SRC;
    DMA_InitStructure.BufSize    = TxBufferSize1;
    DMA_Init(USARTz_Rx_DMA_Channel, &DMA_InitStructure);

    /* Enable USARTz Rx DMA Channel Transfer Complete Interrupt */
    DMA_ConfigInt(USARTz_Rx_DMA_Channel, DMA_INT_TXC, ENABLE);
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
