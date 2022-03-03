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

/* USARTx configuration */
#define _USART5_USART6_

#ifdef _USART5_USART6_
#define USARTy                      UART5
#define USARTy_GPIO                 GPIOB
#define USARTy_CLK                  RCC_APB1_PERIPH_UART5
#define USARTy_GPIO_CLK             RCC_APB2_PERIPH_GPIOB
#define USARTy_TxPin                GPIO_PIN_13
#define USARTy_RxPin                GPIO_PIN_14
#define USARTy_APBxClkCmd           RCC_EnableAPB1PeriphClk
#define USARTy_DMAx                 DMA1
#define USARTy_DMAx_CLK             RCC_AHB_PERIPH_DMA1
#define USARTy_DR_Base              (UART5_BASE + 0x04)
#define USARTy_Tx_DMA_Channel       DMA1_CH1
#define USARTy_Tx_DMA_FLAG          DMA1_FLAG_TC1
#define USARTy_Rx_DMA_Channel       DMA1_CH8
#define USARTy_Rx_DMA_FLAG          DMA1_FLAG_TC8
#define USARTy_Tx_DMA_IRQn          DMA1_Channel1_IRQn
#define USARTy_Tx_DMA_IRQHandler    DMA1_Channel1_IRQHandler
#define USARTy_Tx_DMA_INT           DMA1_INT_TXC1
#define USARTy_IRQn       	        UART5_IRQn
#define USARTy_IRQHandler 	        UART5_IRQHandler

#define USARTz                      UART6
#define USARTz_GPIO                 GPIOB
#define USARTz_CLK                  RCC_APB2_PERIPH_UART6
#define USARTz_GPIO_CLK             RCC_APB2_PERIPH_GPIOB
#define USARTz_TxPin                GPIO_PIN_0
#define USARTz_RxPin                GPIO_PIN_1
#define USARTz_APBxClkCmd           RCC_EnableAPB2PeriphClk
#define USARTz_DMAx                 DMA2
#define USARTz_DMAx_CLK             RCC_AHB_PERIPH_DMA2
#define USARTz_DR_Base              (UART6_BASE + 0x04)
#define USARTz_Tx_DMA_Channel       DMA2_CH2
#define USARTz_Tx_DMA_FLAG          DMA2_FLAG_TC2
#define USARTz_Rx_DMA_Channel       DMA2_CH1
#define USARTz_Rx_DMA_FLAG          DMA2_FLAG_TC1
#define USARTz_Rx_DMA_IRQn          DMA2_Channel1_IRQn
#define USARTz_Rx_DMA_IRQHandler    DMA2_Channel1_IRQHandler
#define USARTz_Rx_DMA_INT           DMA2_INT_TXC1
#define USARTz_IRQn           	    UART6_IRQn
#define USARTz_IRQHandler 	        UART6_IRQHandler
#endif

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */
