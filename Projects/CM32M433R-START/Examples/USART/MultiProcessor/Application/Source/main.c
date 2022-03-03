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
#include "bsp.h"

/** @addtogroup CM32M4xxR_StdPeriph_Examples
 * @{
 */

/** @addtogroup USART_MultiProcessor
 * @{
 */

USART_InitType USART_InitStructure;

void RCC_Configuration(void);
void GPIO_Configuration(void);
void Delay(__IO uint32_t nCount);

/**
 * @brief  Main program
 */
int main(void)
{
	/* Disable global interrupt */
	__disable_irq();

    /* System Clocks Configuration */
    RCC_Configuration();

    /* Configure the GPIO ports */
    GPIO_Configuration();

    /* Initialize Leds, Wakeup and Key Buttons mounted on board */
    LedInit(LED1_PORT,LED1_PIN);
    LedInit(LED2_PORT,LED2_PIN);
    LedInit(LED3_PORT,LED3_PIN);
    KeyInputExtiInit(KEY_INPUT_PORT1,KEY_INPUT_PIN1);

    /* USARTy and USARTz configuration ------------------------------------------------------*/
    USART_InitStructure.BaudRate            = 115200;
    USART_InitStructure.WordLength          = USART_WL_9B;
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

    /* Set the USARTy and USARTz Address */
    USART_SetAddr(USARTy, 0x1);
    USART_SetAddr(USARTz, 0x2);

    /* Select the USARTz WakeUp Method */
    USART_ConfigWakeUpMode(USARTz, USART_WUM_ADDRMASK);

	/* Disable global interrupt */
	__enable_irq();

    while (1)
    {
        /* Send one byte from USARTy to USARTz */
        USART_SendData(USARTy, 0x33);

        /* Wait while USARTy TXE = 0 */
        while (USART_GetFlagStatus(USARTy, USART_FLAG_TXDE) == RESET)
        {
        }

        if (USART_GetFlagStatus(USARTz, USART_FLAG_RXDNE) != RESET)
        {
            if (USART_ReceiveData(USARTz) == 0x33)
            {
            	LedOn(LED1_PORT, LED1_PIN);
                delay_ms(100);
                LedOff(LED1_PORT, LED1_PIN);

                LedOn(LED2_PORT, LED2_PIN);
				delay_ms(100);
				LedOff(LED2_PORT, LED2_PIN);

				LedOn(LED3_PORT, LED3_PIN);
				delay_ms(100);
				LedOff(LED3_PORT, LED3_PIN);
            }
        }
    }
}

/**
 * @brief  Configures the different system clocks.
 */
void RCC_Configuration(void)
{
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
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_Init(USARTy_GPIO, &GPIO_InitStructure);

    /* Configure USARTz Tx as alternate function push-pull */
    GPIO_InitStructure.Pin = USARTz_TxPin;
    GPIO_Init(USARTz_GPIO, &GPIO_InitStructure);

    GPIO_ConfigPinRemap(GPIO_RMP1_UART5, ENABLE);
    GPIO_ConfigPinRemap(GPIO_RMP3_UART6, ENABLE);
}


/**
 * @}
 */

/**
 * @}
 */
