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
 * @file main.h
 * @author CMIOT Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */

#ifndef __MAIN_H__
#define __MAIN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "nuclei_sdk_soc.h"


#define DRIVER_MODULE_ENABLED_DMA

#define _USART1_USART2_

#ifdef _USART1_USART2_

#define USART1_GPIO                 GPIOB
#define USART1_CLK                  RCC_APB2_PERIPH_USART1
#define USART1_GPIO_CLK             RCC_APB2_PERIPH_GPIOB
#define USART1_TxPin                GPIO_PIN_6
#define USART1_APBxClkCmd           RCC_EnableAPB2PeriphClk
#define USART1_DMAx                 DMA1
#define USART1_DMAx_CLK             RCC_AHB_PERIPH_DMA1
#define USART1_DR_Base              (USART1_BASE + 0x04)
#define USART1_Tx_DMA_Channel       DMA1_CH4
#define USART1_Tx_DMA_FLAG          DMA1_FLAG_TC4
#define USART1_Tx_DMA_IRQn          DMA1_Channel4_IRQn
#define USART1_Tx_DMA_IRQHandler    DMA1_Channel4_IRQHandler
#define USART1_Tx_DMA_INT           DMA1_INT_TXC4



#define USART2_GPIO                 GPIOD
#define USART2_CLK                  RCC_APB1_PERIPH_USART2
#define USART2_GPIO_CLK             RCC_APB2_PERIPH_GPIOD
#define USART2_TxPin                GPIO_PIN_5
#define USART2_APBxClkCmd           RCC_EnableAPB1PeriphClk
#define USART2_DMAx                 DMA1
#define USART2_DMAx_CLK             RCC_AHB_PERIPH_DMA1
#define USART2_DR_Base              (USART2_BASE + 0x04)
#define USART2_Rx_DMA_Channel       DMA1_CH6
#define USART2_Rx_DMA_FLAG          DMA1_FLAG_TC6
#define USART2_Rx_DMA_IRQn          DMA1_Channel6_IRQn
#define USART2_Rx_DMA_IRQHandler    DMA1_Channel6_IRQHandler
#define USART2_Rx_DMA_INT           DMA1_INT_TXC6

#endif


#define _USART3_LOG_

#ifdef _USART3_LOG_

#define USARTx_LOG                  USART3
#define USARTx_LOG_GPIO             GPIOB
#define USARTx_LOG_CLK              RCC_APB1_PERIPH_USART3
#define USARTx_LOG_GPIO_CLK         RCC_APB2_PERIPH_GPIOB
#define USARTx_LOG_TxPin            GPIO_PIN_10
#define USARTx_LOG_APBxClkCmd       RCC_EnableAPB1PeriphClk

#endif


#define _USART4_USART5_

#ifdef _USART4_USART5_

#define USART4_GPIO                 GPIOC
#define USART4_CLK                  RCC_APB1_PERIPH_UART4
#define USART4_GPIO_CLK             RCC_APB2_PERIPH_GPIOC
#define USART4_TxPin                GPIO_PIN_10
#define USART4_RxPin                GPIO_PIN_11
#define USART4_APBxClkCmd           RCC_EnableAPB1PeriphClk
#define USART4_DMAx                 DMA2
#define USART4_DMAx_CLK             RCC_AHB_PERIPH_DMA2
#define USART4_DR_Base              (UART4_BASE + 0x04)
#define USART4_Tx_DMA_Channel       DMA2_CH5
#define USART4_Tx_DMA_FLAG          DMA2_FLAG_TC5
#define USART4_Rx_DMA_Channel       DMA2_CH3
#define USART4_Rx_DMA_FLAG          DMA2_FLAG_TC3
#define USART4_Tx_DMA_IRQn          DMA2_Channel5_IRQn
#define USART4_Tx_DMA_IRQHandler    DMA2_Channel5_IRQHandler
#define USART4_Rx_DMA_IRQn          DMA2_Channel3_IRQn
#define USART4_Rx_DMA_IRQHandler    DMA2_Channel3_IRQHandler
#define USART4_Tx_DMA_INT           DMA2_INT_TXC5
#define USART4_Rx_DMA_INT           DMA2_INT_TXC3


#define USART5_GPIO                 GPIOB
#define USART5_CLK                  RCC_APB1_PERIPH_UART5
#define USART5_GPIO_CLK             RCC_APB2_PERIPH_GPIOB
#define USART5_TxPin                GPIO_PIN_13
#define USART5_RxPin                GPIO_PIN_14
#define USART5_APBxClkCmd           RCC_EnableAPB1PeriphClk
#define USART5_DMAx                 DMA1
#define USART5_DMAx_CLK             RCC_AHB_PERIPH_DMA1
#define USART5_DR_Base              (UART5_BASE + 0x04)
#define USART5_Tx_DMA_Channel       DMA1_CH1
#define USART5_Tx_DMA_FLAG          DMA1_FLAG_TC1
#define USART5_Rx_DMA_Channel       DMA1_CH8
#define USART5_Rx_DMA_FLAG          DMA1_FLAG_TC8
#define USART5_Rx_DMA_IRQn          DMA1_Channel8_IRQn
#define USART5_Rx_DMA_IRQHandler    DMA1_Channel8_IRQHandler
#define USART5_Rx_DMA_INT           DMA1_INT_TXC8

#endif


#define _USART6_USART7_

#ifdef _USART6_USART7_

#define USART6_GPIO                 GPIOB
#define USART6_CLK                  RCC_APB2_PERIPH_UART6
#define USART6_GPIO_CLK             RCC_APB2_PERIPH_GPIOB
#define USART6_TxPin                GPIO_PIN_0
#define USART6_RxPin                GPIO_PIN_1
#define USART6_APBxClkCmd           RCC_EnableAPB2PeriphClk
#define USART6_DMAx                 DMA2
#define USART6_DMAx_CLK             RCC_AHB_PERIPH_DMA2
#define USART6_DR_Base              (UART6_BASE + 0x04)
#define USART6_Tx_DMA_Channel       DMA2_CH2
#define USART6_Tx_DMA_FLAG          DMA2_FLAG_TC2
#define USART6_Rx_DMA_Channel       DMA2_CH1
#define USART6_Rx_DMA_FLAG          DMA2_FLAG_TC1
#define USART6_Tx_DMA_IRQn          DMA2_Channel2_IRQn
#define USART6_Tx_DMA_IRQHandler    DMA2_Channel2_IRQHandler
#define USART6_Tx_DMA_INT           DMA2_INT_TXC2



#define USART7_GPIO                 GPIOG
#define USART7_CLK                  RCC_APB2_PERIPH_UART7
#define USART7_GPIO_CLK             RCC_APB2_PERIPH_GPIOG
#define USART7_TxPin                GPIO_PIN_0
#define USART7_RxPin                GPIO_PIN_1
#define USART7_APBxClkCmd           RCC_EnableAPB2PeriphClk
#define USART7_DMAx                 DMA2
#define USART7_DMAx_CLK             RCC_AHB_PERIPH_DMA2
#define USART7_DR_Base              (UART7_BASE + 0x04)
#define USART7_Tx_DMA_Channel       DMA2_CH7
#define USART7_Tx_DMA_FLAG          DMA2_FLAG_TC7
#define USART7_Rx_DMA_Channel       DMA2_CH6
#define USART7_Rx_DMA_FLAG          DMA2_FLAG_TC6
#define USART7_Rx_DMA_IRQn          DMA2_Channel6_IRQn
#define USART7_Rx_DMA_IRQHandler    DMA2_Channel6_IRQHandler
#define USART7_Rx_DMA_INT           DMA2_INT_TXC6

#endif

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */
