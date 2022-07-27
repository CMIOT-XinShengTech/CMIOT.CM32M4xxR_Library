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

/** @addtogroup USART_DMA_Interrupt
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
uint8_t TxBuffer1[] = "USART DMA Interrupt: USARTy -> USARTz using DMA Tx and Rx Flag";
uint8_t TxBuffer2[] = "USART DMA Interrupt: USARTz -> USARTy using DMA Tx and Rx Interrupt";
uint8_t RxBuffer1[TxBufferSize2];
uint8_t RxBuffer2[TxBufferSize1];
uint8_t NbrOfDataToRead             = TxBufferSize1;
uint32_t indexFlag                  = 0;
volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED;

void RCC_Configuration(void);
void GPIO_Configuration(void);
void ECLIC_Configuration(void);
void DMA_Configuration(void);
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);

/**
 * @brief  Main program
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
    USART_InitStructure.BaudRate            = 57600; /* Band rate is too high may cause data lost in this example.
    													When system clock is 8M, the maximum band rate allowed is 57600 */
    USART_InitStructure.WordLength          = USART_WL_8B;
    USART_InitStructure.StopBits            = USART_STPB_1;
    USART_InitStructure.Parity              = USART_PE_NO;
    USART_InitStructure.HardwareFlowControl = USART_HFCTRL_NONE;
    USART_InitStructure.Mode                = USART_MODE_RX | USART_MODE_TX;

    /* Configure USARTy and USARTz */
    USART_Init(USARTy, &USART_InitStructure);
    USART_Init(USARTz, &USART_InitStructure);

    /* Enable the USARTy and USARTz */
	USART_Enable(USARTy, ENABLE);
	USART_Enable(USARTz, ENABLE);

    /* Enable USARTy DMA TX request */
    USART_EnableDMA(USARTy, USART_DMAREQ_TX, ENABLE);

    /* Enable USARTz DMA TX request */
    USART_EnableDMA(USARTz, USART_DMAREQ_TX, ENABLE);

    /* Enable the USARTz Receive Interrupt */
    USART_ConfigInt(USARTz, USART_INT_RXDNE, ENABLE);

    /* Enable global interrupt */
	__enable_irq();

    /* Enable USARTy TX DMA1 Channel */
    DMA_EnableChannel(USARTy_Tx_DMA_Channel, ENABLE);

    /* Enable USARTz TX DMA1 Channel */
    DMA_EnableChannel(USARTz_Tx_DMA_Channel, ENABLE);

    /* Receive the TxBuffer2 */
    while (indexFlag < TxBufferSize2)
    {
        while (USART_GetFlagStatus(USARTy, USART_FLAG_RXDNE) == RESET)
        {
        }

        RxBuffer1[indexFlag++] = USART_ReceiveData(USARTy);
    }

    /* Wait until USARTy TX DMA1 Channel Transfer Complete */
    while (DMA_GetFlagStatus(USARTy_Tx_DMA_FLAG, USARTy_DMAx) == RESET)
    {
    }

    /* Wait until USARTz TX DMA1 Channel Transfer Complete */
    while (DMA_GetFlagStatus(USARTz_Tx_DMA_FLAG, USARTz_DMAx) == RESET)
    {
    }

    /* Check the received data with the send ones */
    /* TransferStatus1 = PASSED, if the data transmitted from USARTz and
       received by USARTy are the same */
    /* TransferStatus1 = FAILED, if the data transmitted from USARTz and
       received by USARTy are different */
    TransferStatus1 = Buffercmp(TxBuffer2, RxBuffer1, TxBufferSize2);

    /* TransferStatus2 = PASSED, if the data transmitted from USARTy and
       received by USARTz are the same */
    /* TransferStatus2 = FAILED, if the data transmitted from USARTy and
       received by USARTz are different */
    TransferStatus2 = Buffercmp(TxBuffer1, RxBuffer2, TxBufferSize1);

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
}

/**
 * @brief  Configures the enhanced core local interrupt controller.
 */
void ECLIC_Configuration(void)
{
    /* Enable the USARTz Interrupt */
	ECLIC_SetLevelIRQ(USARTz_IRQn, 0);
	ECLIC_SetPriorityIRQ(USARTz_IRQn, 0);
	ECLIC_SetTrigIRQ(USARTz_IRQn, ECLIC_LEVEL_TRIGGER);
	ECLIC_EnableIRQ(USARTz_IRQn);
}

/**
 * @brief  Configures the DMA.
 */
void DMA_Configuration(void)
{
    DMA_InitType DMA_InitStructure;

    /* USARTy_Tx_DMA_Channel (triggered by USARTy Tx event) Config */
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

    /* USARTz_Tx_DMA_Channel (triggered by USARTz Tx event) Config */
    DMA_DeInit(USARTz_Tx_DMA_Channel);
    DMA_InitStructure.PeriphAddr = USARTz_DR_Base;
    DMA_InitStructure.MemAddr    = (uint32_t)TxBuffer2;
    DMA_InitStructure.Direction  = DMA_DIR_PERIPH_DST;
    DMA_InitStructure.BufSize    = TxBufferSize2;
    DMA_Init(USARTz_Tx_DMA_Channel, &DMA_InitStructure);
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
