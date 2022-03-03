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
#include <string.h>
#include "main.h"
#include "bsp_Tim_38K.h"

/** @addtogroup CM32M4xxR_StdPeriph_Examples
 * @{
 */

/** @addtogroup USART_IrDA_Tx&Rx
 * @{
 */

typedef enum
{
    FAILED = 0,
    PASSED = !FAILED
} TestStatus;

#define TxBufferSize1 (countof(TxBuffer1))
#define countof(a) (sizeof(a) / sizeof(*(a)))

USART_InitType USART_InitStructure;
uint8_t TxBuffer1[]                = "USART IrDA Example: Board1_USARTy -> Board2_USARTy using Irda low power mode.";
__IO uint8_t TxCounter             = 0;
__IO uint8_t RxCounter             = 0;
volatile uint8_t RxBuffer1[TxBufferSize1];
uint8_t TxBufferSize2 = (uint8_t)TxBufferSize1;
volatile TestStatus TransferStatus = FAILED;

void RCC_Configuration(void);
void GPIO_Configuration(void);
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);

/**
 * @brief  Configures the enhanced core local interrupt controller.
 */
void ECLIC_Configuration(void)
{
    /* Configure the ECLIC level and priority Bits */
    ECLIC_SetCfgNlbits(0); /* 0 bits for level, 4 bits for priority */

    /* Enable the USARTy Interrupt */
    ECLIC_SetPriorityIRQ(USARTy_IRQn, 0);
    ECLIC_SetTrigIRQ(USARTy_IRQn, ECLIC_LEVEL_TRIGGER);
    ECLIC_EnableIRQ(USARTy_IRQn);
}

/**
 * @brief  Main program
 */
int main(void)
{
    /* Disable global interrupt */
    __disable_irq();

    /* System Clocks Configuration */
    RCC_Configuration();
    ECLIC_Configuration();
    /* Configure the GPIO ports */
    GPIO_Configuration();

    /* GPIO PE9 Output 38KHz Clock */
    //ADVANCE_TIM_Init();

    /* USARTy and USARTz configuration ------------------------------------------------------*/
    USART_InitStructure.BaudRate            = 9600;
    USART_InitStructure.WordLength          = USART_WL_8B;
    USART_InitStructure.StopBits            = USART_STPB_1;
    USART_InitStructure.Parity              = USART_PE_NO;
    USART_InitStructure.HardwareFlowControl = USART_HFCTRL_NONE;
    USART_InitStructure.Mode                = USART_MODE_RX | USART_MODE_TX;


    /* Configure USARTy */
    USART_Init(USARTy, &USART_InitStructure);
    USART_ConfigInt(USARTy, USART_INT_RXDNE, ENABLE);

    /* Set the USARTy prescaler */
    USART_SetPrescaler(USARTy, 2);
    /* Configure the USARTy IrDA mode */
    USART_ConfigIrDAMode(USARTy, USART_IRDAMODE_LOWPPWER);
    /* Enable the USARTy IrDA mode */
    USART_EnableIrDA(USARTy, ENABLE);

    /* Enable the USARTy */
	USART_Enable(USARTy, ENABLE);

    /* Enable global interrupt */
    __enable_irq();

    memset((void *)RxBuffer1, 0, TxBufferSize1);

#ifdef IrDA_Transmitter
    while (TxCounter < TxBufferSize1)
    {


        /* Loop until USARTx transfer data register is empty */
        while (USART_GetFlagStatus(USARTy, USART_FLAG_TXDE) == RESET)
        {
        }

        /* Send one byte from USARTx to USARTx */
        USART_SendData(USARTy, TxBuffer1[TxCounter++]);

        delay_ms(5);
    }
#endif

#ifdef IrDA_Receiver
    while (RxCounter < TxBufferSize1)
    {
    }
#endif

    /* Check the received data with the send ones */
    /* TransferStatus = PASSED, if the data transmitted from USARTx and
    received by USARTx are the same */
    /* TransferStatus = FAILED, if the data transmitted from USARTx and
    received by USARTx are different */
    TransferStatus = Buffercmp(TxBuffer1, (uint8_t*)RxBuffer1, TxBufferSize1);

    while (1)
    {
    }
}

/**
 * @brief  Configures the different system clocks.
 */
void RCC_Configuration(void)
{
    /* Enable GPIO clock */
    RCC_EnableAPB2PeriphClk(USARTy_GPIO_CLK | SD_GPIO_CLK | RCC_APB2_PERIPH_AFIO, ENABLE);

    /* Enable USARTy and USARTz Clock */
    USARTy_APBxClkCmd(USARTy_CLK, ENABLE);
}

/**
 * @brief  Configures the different GPIO ports.
 */
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    /* Configure USARTy Rx as input floating */
    GPIO_InitStructure.Pin       = USARTy_RxPin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(USARTy_GPIO, &GPIO_InitStructure);

    /* Configure USARTy Tx as alternate function push-pull */
    GPIO_InitStructure.Pin        = USARTy_TxPin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_Init(USARTy_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.Pin        = SD_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_Init(SD_GPIO, &GPIO_InitStructure);
    GPIO_WriteBit(SD_GPIO, SD_Pin, Bit_RESET);

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
