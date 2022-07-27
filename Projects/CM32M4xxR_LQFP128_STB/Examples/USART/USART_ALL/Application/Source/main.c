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

/** @addtogroup USART_ALL
 * @{
 */

typedef enum
{
    FAILED = 0,
    PASSED = !FAILED
} TestStatus;

#define countof(a) (sizeof(a) / sizeof(*(a)))

#define TxBufferSize1 (countof(TxBuffer1) - 1)
#define TxBufferSize2 (countof(TxBuffer2) - 1)
#define TxBufferSize4 (countof(TxBuffer4) - 1)
#define TxBufferSize5 (countof(TxBuffer5) - 1)
#define TxBufferSize6 (countof(TxBuffer6) - 1)
#define TxBufferSize7 (countof(TxBuffer7) - 1)

USART_InitType USART_InitStructure;

uint8_t TxBuffer1[] = {"USART DMA Half Duplex: USART1 -> USART2 using HalfDuplex mode"};
uint8_t TxBuffer2[] = {"USART DMA Half Duplex: USART2 -> USART1 using HalfDuplex mode"};
uint8_t RxBuffer1[TxBufferSize2];
uint8_t RxBuffer2[TxBufferSize1];
uint8_t TxCounter1 = 0, RxCounter1 = 0;
uint8_t TxCounter2 = 0, RxCounter2 = 0;
volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED;

uint8_t TxBuffer4[] = {"USART DMA: USART4 -> USART5 using Interrupt mode"};
uint8_t TxBuffer5[] = {"USART DMA: USART5 -> USART4 using Polling mode"};
uint8_t RxBuffer4[TxBufferSize5];
uint8_t RxBuffer5[TxBufferSize4];
uint8_t TxCounter4 = 0, RxCounter5 = 0;
uint8_t TxCounter5 = 0, RxCounter4 = 0;
volatile TestStatus TransferStatus4 = FAILED, TransferStatus5 = FAILED;

uint8_t TxBuffer6[] = {"Buffer Send from USART6 to USART7 using Flags"};
uint8_t TxBuffer7[] = {"Buffer Send from USART7 to USART6 using Flags"};
uint8_t RxBuffer6[TxBufferSize7];
uint8_t RxBuffer7[TxBufferSize6];
uint8_t TxCounter6 = 0, RxCounter7 = 0;
uint8_t TxCounter7 = 0, RxCounter6 = 0;
uint8_t NbrOfDataToTransfer6    = TxBufferSize6;
//uint8_t NbrOfDataToTransfer7    = TxBufferSize7;
volatile TestStatus TransferStatus6 = FAILED, TransferStatus7 = FAILED;

__IO uint8_t USART1_Tx_Done = 0;
__IO uint8_t USART2_Rx_Done = 0;
__IO uint8_t USART4_Tx_Done = 0;
__IO uint8_t USART4_Rx_Done = 0;

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

    /* USART1 and USART2 configuration ------------------------------------------------------*/
    USART_InitStructure.BaudRate            = 115200;
    USART_InitStructure.WordLength          = USART_WL_8B;
    USART_InitStructure.StopBits            = USART_STPB_1;
    USART_InitStructure.Parity              = USART_PE_NO;
    USART_InitStructure.HardwareFlowControl = USART_HFCTRL_NONE;
    /* Configure USART1 and USART2 and USART3 */
    USART_InitStructure.Mode                = USART_MODE_TX;
    USART_Init(USART1, &USART_InitStructure);
    USART_InitStructure.Mode                = USART_MODE_RX;
    USART_Init(USART2, &USART_InitStructure);
    USART_InitStructure.Mode                = USART_MODE_TX;
	USART_Init(USARTx_LOG, &USART_InitStructure);

    /* Enable USART1 DMA Rx and TX request */
    USART_EnableDMA(USART1, USART_DMAREQ_TX, ENABLE);
    /* Enable USART2 DMA Rx and TX request */
    USART_EnableDMA(USART2, USART_DMAREQ_RX, ENABLE);

	/* Enable USART1 Half Duplex Mode*/
	USART_EnableHalfDuplex(USART1, ENABLE);
	/* Enable USART2 Half Duplex Mode*/
	USART_EnableHalfDuplex(USART2, ENABLE);

    /* Enable the USART1 and USART2 and USART3 */
	USART_Enable(USART1, ENABLE);
	USART_Enable(USART2, ENABLE);
	USART_Enable(USARTx_LOG, ENABLE);

	/* Enable USART2 RX DMA1 Channel */
	DMA_EnableChannel(USART2_Rx_DMA_Channel, ENABLE);
	/* Enable USART1 TX DMA1 Channel */
	DMA_EnableChannel(USART1_Tx_DMA_Channel, ENABLE);

    /* Enable global interrupt */
    __enable_irq();

    /* Wait until USART1 TX DMA Channel Transfer Complete */
    while(!USART1_Tx_Done);

    /* Wait until USART2 RX DMA Channel Transfer Complete */
    while(!USART2_Rx_Done);

    /* Change the direction of transmission */
	USART1->CTRL1 &= ~USART_CTRL1_TXEN;
	USART1->CTRL1 |= USART_CTRL1_RXEN;
	USART2->CTRL1 &= ~USART_CTRL1_RXEN;
	USART2->CTRL1 |= USART_CTRL1_TXEN;

    while(TxCounter2 < TxBufferSize2)
    {
    	/* Send one byte from USART2 to USART1 */
		USART_SendData(USART2, TxBuffer2[TxCounter2++]);

		/* Loop until USART2 Send Data Register is empty */
		while (USART_GetFlagStatus(USART2, USART_FLAG_TXDE) == RESET);

		/* Loop until the USART1 Receive Data Register is not empty */
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXDNE) == RESET);

		/* Store the received byte in RxBuffer */
		RxBuffer1[RxCounter1++] = USART_ReceiveData(USART1);
    }

    /* Check the received data with the send ones */
    TransferStatus1 = Buffercmp(TxBuffer1, RxBuffer2, TxBufferSize1);

    TransferStatus2 = Buffercmp(TxBuffer2, RxBuffer1, TxBufferSize2);

    printf("\r\n115200,8,1,0:\r\nUSART1 -> USART2 result:%s, USART2 -> USART1 result:%s\r\n", (TransferStatus1?"PASSED":"FAILED"), (TransferStatus2?"PASSED":"FAILED"));

    /* Disable global interrupt */
	__disable_irq();

    /* USART4 and USART5 configuration ------------------------------------------------------*/
	USART_InitStructure.BaudRate            = 921600;
	USART_InitStructure.WordLength          = USART_WL_8B;
	USART_InitStructure.StopBits            = USART_STPB_1;
	USART_InitStructure.Parity              = USART_PE_EVEN;
	USART_InitStructure.HardwareFlowControl = USART_HFCTRL_NONE;
	USART_InitStructure.Mode                = USART_MODE_TX | USART_MODE_RX;

	/* Configure USART4 and USART5 */
	USART_Init(UART4, &USART_InitStructure);
	USART_Init(UART5, &USART_InitStructure);

	/* Enable USART4 DMA Rx and TX request */
	USART_EnableDMA(UART4, USART_DMAREQ_RX | USART_DMAREQ_TX, ENABLE);
	/* Enable USART5 DMA Rx and TX request */
	USART_EnableDMA(UART5, USART_DMAREQ_RX | USART_DMAREQ_TX, ENABLE);

	/* Enable the USART4 and USART5 */
	USART_Enable(UART4, ENABLE);
	USART_Enable(UART5, ENABLE);

	/* Enable USART4 RX DMA2 Channel */
	DMA_EnableChannel(USART4_Rx_DMA_Channel, ENABLE);
	/* Enable USART5 RX DMA1 Channel */
	DMA_EnableChannel(USART5_Rx_DMA_Channel, ENABLE);

	/* Enable USART4 TX DMA2 Channel */
	DMA_EnableChannel(USART4_Tx_DMA_Channel, ENABLE);
	/* Enable USART5 TX DMA1 Channel */
	DMA_EnableChannel(USART5_Tx_DMA_Channel, ENABLE);

	/* Enable global interrupt */
	__enable_irq();

    /* Wait until USART4 TX DMA Channel Transfer Complete */
	while(!USART4_Tx_Done);

	/* Wait until USART5 RX DMA1 Channel Transfer Complete */
	while (DMA_GetFlagStatus(USART5_Rx_DMA_FLAG, USART5_DMAx) == RESET);

	/* Check USART5 receive data PEF flag */
	if (USART_GetFlagStatus(UART5, USART_FLAG_PEF) == SET)
	{
		printf("\r\nUART5 receive data parity error!\r\n");
	}

	/* DMA received data with one bit check bit,so it must be abandoned */
	for(int BufferDeal = 0;BufferDeal < TxBufferSize4;BufferDeal ++)
	{
		RxBuffer5[BufferDeal] &= 0x7f;//deal with check bit
	}

	/* Wait until USART5 TX DMA1 Channel Transfer Complete */
	while (DMA_GetFlagStatus(USART5_Tx_DMA_FLAG, USART5_DMAx) == RESET);

	/* Wait until USART4 RX DMA Channel Transfer Complete */
	while(!USART4_Rx_Done);

	/* Check USART4 receive data PEF flag */
	if (USART_GetFlagStatus(UART4, USART_FLAG_PEF) == SET)
	{
		printf("\r\nUART4 receive data parity error!\r\n");
	}

	/* DMA received data with one bit check bit,so it must be abandoned */
	for(int BufferDeal = 0;BufferDeal < TxBufferSize5;BufferDeal ++)
	{
		RxBuffer4[BufferDeal] &= 0x7f;//deal with check bit
	}

	/* Check the received data with the send ones */
	TransferStatus4 = Buffercmp(TxBuffer4, RxBuffer5, TxBufferSize4);

	TransferStatus5 = Buffercmp(TxBuffer5, RxBuffer4, TxBufferSize5);

	printf("\r\n921600,8,1,2:\r\nUSART4 -> USART5 result:%s, USART5 -> USART4 result:%s\r\n", (TransferStatus4?"PASSED":"FAILED"), (TransferStatus5?"PASSED":"FAILED"));

	/* Disable global interrupt */
	__disable_irq();

	/* USART6 and USART7 configuration ------------------------------------------------------*/
	USART_InitStructure.BaudRate            = 38400;
	USART_InitStructure.WordLength          = USART_WL_9B;
	USART_InitStructure.StopBits            = USART_STPB_1;
	USART_InitStructure.Parity              = USART_PE_ODD;
	USART_InitStructure.HardwareFlowControl = USART_HFCTRL_NONE;
	USART_InitStructure.Mode                = USART_MODE_TX | USART_MODE_RX;

	/* Configure USART6 and USART7 */
	USART_Init(UART6, &USART_InitStructure);
	USART_Init(UART7, &USART_InitStructure);

	/* Enable USART7 Receive interrupt and USART6 Transmit interrupt */
	USART_ConfigInt(UART6, USART_INT_TXDE, ENABLE);
	USART_ConfigInt(UART7, USART_INT_RXDNE, ENABLE);

	/* Enable the USART6 and USART7 */
	USART_Enable(UART6, ENABLE);
	USART_Enable(UART7, ENABLE);

	/* Enable global interrupt */
	__enable_irq();

	/* Check USART7 receive data PEF flag */
	if (USART_GetFlagStatus(UART7, USART_FLAG_PEF) == SET)
	{
		printf("\r\nUART7 receive data parity error!\r\n");
	}

	while (TxCounter7 < TxBufferSize7)
	{
		/* Send one byte from USART7 to USART6 */
		USART_SendData(UART7, TxBuffer7[TxCounter7++]);

		/* Loop until USART7 Send Data Register is empty */
		while (USART_GetFlagStatus(UART7, USART_FLAG_TXDE) == RESET);

		/* Loop until the USART6 Receive Data Register is not empty */
		while (USART_GetFlagStatus(UART6, USART_FLAG_RXDNE) == RESET);

		/* Store the received byte in RxBuffer */
		RxBuffer6[RxCounter6++] = USART_ReceiveData(UART6);
	}

	/* Check USART6 receive data PEF flag */
	if (USART_GetFlagStatus(UART6, USART_FLAG_PEF) == SET)
	{
		printf("\r\nUART6 receive data parity error!\r\n");
	}

	/* Check the received data with the send ones */
	TransferStatus6 = Buffercmp(TxBuffer6, RxBuffer7, TxBufferSize6);

	TransferStatus7 = Buffercmp(TxBuffer7, RxBuffer6, TxBufferSize7);

	printf("\r\n38400,9,1,1:\r\nUSART6 -> USART7 result:%s, USART7 -> USART6 result:%s\r\n", (TransferStatus6?"PASSED":"FAILED"), (TransferStatus7?"PASSED":"FAILED"));

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
    RCC_EnableAHBPeriphClk(USART1_DMAx_CLK, ENABLE);
    RCC_EnableAHBPeriphClk(USART2_DMAx_CLK, ENABLE);
    RCC_EnableAHBPeriphClk(USART4_DMAx_CLK, ENABLE);
	RCC_EnableAHBPeriphClk(USART5_DMAx_CLK, ENABLE);

    /* Enable GPIO clock */
    RCC_EnableAPB2PeriphClk(USART1_GPIO_CLK | USART2_GPIO_CLK | USARTx_LOG_CLK | USART4_GPIO_CLK | USART5_GPIO_CLK \
    		| USART6_GPIO_CLK | USART7_GPIO_CLK | RCC_APB2_PERIPH_AFIO, ENABLE);

    /* Enable USARTy and USARTz Clock */
    USART1_APBxClkCmd(USART1_CLK, ENABLE);
    USART2_APBxClkCmd(USART2_CLK, ENABLE);
    USARTx_LOG_APBxClkCmd(USARTx_LOG_CLK, ENABLE);
    USART4_APBxClkCmd(USART4_CLK, ENABLE);
    USART5_APBxClkCmd(USART5_CLK, ENABLE);
    USART6_APBxClkCmd(USART6_CLK, ENABLE);
    USART7_APBxClkCmd(USART7_CLK, ENABLE);
}

/**
 * @brief  Configures the different GPIO ports.
 */
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;
    GPIO_ConfigPinRemap(GPIO_RMP_USART1,ENABLE);

    /* Configure USART1 and USART2 */
    /* Configure USART1 Tx as alternate function push-pull */
    GPIO_InitStructure.Pin        = USART1_TxPin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_Init(USART1_GPIO, &GPIO_InitStructure);

    /* Configure USART2 Tx as alternate function push-pull*/
    GPIO_InitStructure.Pin = USART2_TxPin;
    GPIO_Init(USART2_GPIO, &GPIO_InitStructure);

    GPIO_ConfigPinRemap(GPIO_RMP1_USART2, ENABLE);

    /* Configure USART3 */
    /* Configure USART3 Tx as alternate function push-pull */
	GPIO_InitStructure.Pin = USARTx_LOG_TxPin;
	GPIO_Init(USARTx_LOG_GPIO, &GPIO_InitStructure);

	//GPIO_ConfigPinRemap(GPIO_ALL_RMP_USART3, ENABLE);

    /* Configure USART4 and USART5 */
    /* Configure USART4 Rx as input floating */
	GPIO_InitStructure.Pin       = USART4_RxPin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(USART4_GPIO, &GPIO_InitStructure);

	/* Configure USART5 Rx as input floating */
	GPIO_InitStructure.Pin = USART5_RxPin;
	GPIO_Init(USART5_GPIO, &GPIO_InitStructure);

	/* Configure USART4 Tx as alternate function push-pull */
	GPIO_InitStructure.Pin        = USART4_TxPin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_Init(USART4_GPIO, &GPIO_InitStructure);

	/* Configure USART5 Tx as alternate function push-pull */
	GPIO_InitStructure.Pin = USART5_TxPin;
	GPIO_Init(USART5_GPIO, &GPIO_InitStructure);

	//GPIO_ConfigPinRemap(GPIO_RMP3_UART4, ENABLE);
	GPIO_ConfigPinRemap(GPIO_RMP1_UART5, ENABLE);

	/* Configure USART6 and USART7 */
    /* Configure USART6 Rx as input floating */
	GPIO_InitStructure.Pin       = USART6_RxPin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(USART6_GPIO, &GPIO_InitStructure);

	/* Configure USART7 Rx as input floating */
	GPIO_InitStructure.Pin = USART7_RxPin;
	GPIO_Init(USART7_GPIO, &GPIO_InitStructure);

	/* Configure USART6 Tx as alternate function push-pull */
	GPIO_InitStructure.Pin        = USART6_TxPin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_Init(USART6_GPIO, &GPIO_InitStructure);

	/* Configure USART7 Tx as alternate function push-pull */
	GPIO_InitStructure.Pin = USART7_TxPin;
	GPIO_Init(USART7_GPIO, &GPIO_InitStructure);

    GPIO_ConfigPinRemap(GPIO_RMP3_UART6, ENABLE);
	GPIO_ConfigPinRemap(GPIO_RMP3_UART7, ENABLE);
}

/**
 * @brief  Configures the enhanced core local interrupt controller.
 */
void ECLIC_Configuration(void)
{
	/* Configure the ECLIC level and priority Bits */
	ECLIC_SetCfgNlbits(1); /* 1 bits for level, 3 bits for priority */

    /* Enable the USART1_Tx DMA Interrupt */
	ECLIC_SetLevelIRQ(USART1_Tx_DMA_IRQn, 0);
	ECLIC_SetPriorityIRQ(USART1_Tx_DMA_IRQn, 0);
	ECLIC_SetTrigIRQ(USART1_Tx_DMA_IRQn, ECLIC_LEVEL_TRIGGER);
	ECLIC_EnableIRQ(USART1_Tx_DMA_IRQn);
	
	/* Enable the USART2_Rx DMA Interrupt */
	ECLIC_SetLevelIRQ(USART2_Rx_DMA_IRQn, 0);
	ECLIC_SetPriorityIRQ(USART2_Rx_DMA_IRQn, 0);
	ECLIC_SetTrigIRQ(USART2_Rx_DMA_IRQn, ECLIC_LEVEL_TRIGGER);
	ECLIC_EnableIRQ(USART2_Rx_DMA_IRQn);

	/* Enable the USART4_Tx DMA Interrupt */
	ECLIC_SetLevelIRQ(USART4_Tx_DMA_IRQn, 0);
	ECLIC_SetPriorityIRQ(USART4_Tx_DMA_IRQn, 0);
	ECLIC_SetTrigIRQ(USART4_Tx_DMA_IRQn, ECLIC_LEVEL_TRIGGER);
	ECLIC_EnableIRQ(USART4_Tx_DMA_IRQn);

	/* Enable the USART4_Tx DMA Interrupt */
	ECLIC_SetLevelIRQ(USART4_Rx_DMA_IRQn, 0);
	ECLIC_SetPriorityIRQ(USART4_Rx_DMA_IRQn, 0);
	ECLIC_SetTrigIRQ(USART4_Rx_DMA_IRQn, ECLIC_LEVEL_TRIGGER);
	ECLIC_EnableIRQ(USART4_Rx_DMA_IRQn);

	/* Enable the USART6 Interrupt */
	ECLIC_SetLevelIRQ(UART6_IRQn, 0);
	ECLIC_SetPriorityIRQ(UART6_IRQn, 0);
	ECLIC_SetTrigIRQ(UART6_IRQn, ECLIC_LEVEL_TRIGGER);
	ECLIC_EnableIRQ(UART6_IRQn);

	/* Enable the USART7 Interrupt */
	ECLIC_SetLevelIRQ(UART7_IRQn, 1);
	ECLIC_SetPriorityIRQ(UART7_IRQn, 1);
	ECLIC_SetTrigIRQ(UART7_IRQn, ECLIC_LEVEL_TRIGGER);
	ECLIC_EnableIRQ(UART7_IRQn);
}

/**
 * @brief  Configures the DMA.
 */
void DMA_Configuration(void)
{
    DMA_InitType DMA_InitStructure;

    /* USART1 TX DMA1 Channel (triggered by USART1 Tx event) Config */
    DMA_DeInit(USART1_Tx_DMA_Channel);
    DMA_InitStructure.PeriphAddr     = USART1_DR_Base;
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
    DMA_Init(USART1_Tx_DMA_Channel, &DMA_InitStructure);

    /* Enable USART1 Tx DMA Channel Transfer Complete Interrupt */
    DMA_ConfigInt(USART1_Tx_DMA_Channel, DMA_INT_TXC, ENABLE);

    /* USART2 RX DMA1 Channel (triggered by USART2 Rx event) Config */
    DMA_DeInit(USART2_Rx_DMA_Channel);
    DMA_InitStructure.PeriphAddr = USART2_DR_Base;
    DMA_InitStructure.MemAddr    = (uint32_t)RxBuffer2;
    DMA_InitStructure.Direction  = DMA_DIR_PERIPH_SRC;
    DMA_InitStructure.BufSize    = TxBufferSize1;
    DMA_Init(USART2_Rx_DMA_Channel, &DMA_InitStructure);

    /* Enable USART2 Rx DMA Channel Transfer Complete Interrupt */
    DMA_ConfigInt(USART2_Rx_DMA_Channel, DMA_INT_TXC, ENABLE);

    /* USART4 TX DMA2 Channel (triggered by USART4 Tx event) Config */
	DMA_DeInit(USART4_Tx_DMA_Channel);
	DMA_InitStructure.PeriphAddr = USART4_DR_Base;
	DMA_InitStructure.MemAddr    = (uint32_t)TxBuffer4;
	DMA_InitStructure.Direction  = DMA_DIR_PERIPH_DST;
	DMA_InitStructure.BufSize    = TxBufferSize4;
	DMA_Init(USART4_Tx_DMA_Channel, &DMA_InitStructure);

	/* Enable USART4 Rx DMA Channel Transfer Complete Interrupt */
	DMA_ConfigInt(USART4_Tx_DMA_Channel, DMA_INT_TXC, ENABLE);

	/* USART4 RX DMA2 Channel (triggered by USART4 Rx event) Config */
	DMA_DeInit(USART4_Rx_DMA_Channel);
	DMA_InitStructure.PeriphAddr = USART4_DR_Base;
	DMA_InitStructure.MemAddr    = (uint32_t)RxBuffer4;
	DMA_InitStructure.Direction  = DMA_DIR_PERIPH_SRC;
	DMA_InitStructure.BufSize    = TxBufferSize5;
	DMA_Init(USART4_Rx_DMA_Channel, &DMA_InitStructure);

	/* Enable USART4 Rx DMA Channel Transfer Complete Interrupt */
	DMA_ConfigInt(USART4_Rx_DMA_Channel, DMA_INT_TXC, ENABLE);

	/* USART5 TX DMA1 Channel (triggered by USART5 Tx event) Config */
	DMA_DeInit(USART5_Tx_DMA_Channel);
	DMA_InitStructure.PeriphAddr = USART5_DR_Base;
	DMA_InitStructure.MemAddr    = (uint32_t)TxBuffer5;
	DMA_InitStructure.Direction  = DMA_DIR_PERIPH_DST;
	DMA_InitStructure.BufSize    = TxBufferSize5;
	DMA_Init(USART5_Tx_DMA_Channel, &DMA_InitStructure);

	/* USART5 RX DMA1 Channel (triggered by USART5 Rx event) Config */
	DMA_DeInit(USART5_Rx_DMA_Channel);
	DMA_InitStructure.PeriphAddr = USART5_DR_Base;
	DMA_InitStructure.MemAddr    = (uint32_t)RxBuffer5;
	DMA_InitStructure.Direction  = DMA_DIR_PERIPH_SRC;
	DMA_InitStructure.BufSize    = TxBufferSize4;
	DMA_Init(USART5_Rx_DMA_Channel, &DMA_InitStructure);
}

/**
 * @brief  Compares two buffers.
 * @param  pBuffer1, pBuffer2: buffers to be compared.
 * @param  BufferLength buffer's length
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
 * @brief  Redefine printf function.
 */
int _put_char(char ch)
{
	USART_SendData(USARTx_LOG, (uint8_t)ch);

	/* Loop until the end of transmission */
    while (USART_GetFlagStatus(USARTx_LOG, USART_FLAG_TXDE) == RESET);

    return ch;
}

/**
 * @}
 */

/**
 * @}
 */
