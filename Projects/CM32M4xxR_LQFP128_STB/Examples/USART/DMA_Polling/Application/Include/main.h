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
#define _USART1_USART2_
//#define _USART3_UART4_
//#define _UART6_UART7_

#ifdef _USART1_USART2_
#define USARTy                	USART1
#define USARTy_GPIO           	GPIOB
#define USARTy_CLK            	RCC_APB2_PERIPH_USART1
#define USARTy_GPIO_CLK       	RCC_APB2_PERIPH_GPIOB
#define USARTy_RxPin          	GPIO_PIN_7
#define USARTy_TxPin          	GPIO_PIN_6
#define USARTy_APBxClkCmd     	RCC_EnableAPB2PeriphClk
#define USARTy_DMAx           	DMA1
#define USARTy_DMAx_CLK       	RCC_AHB_PERIPH_DMA1
#define USARTy_DR_Base        	(USART1_BASE + 0x04)
#define USARTy_Tx_DMA_Channel 	DMA1_CH4
#define USARTy_Tx_DMA_FLAG    	DMA1_FLAG_TC4
#define USARTy_Rx_DMA_Channel 	DMA1_CH5
#define USARTy_Rx_DMA_FLAG    	DMA1_FLAG_TC5

#define USARTz                	USART2
#define USARTz_GPIO           	GPIOA
#define USARTz_CLK            	RCC_APB1_PERIPH_USART2
#define USARTz_GPIO_CLK       	RCC_APB2_PERIPH_GPIOA
#define USARTz_RxPin          	GPIO_PIN_3
#define USARTz_TxPin          	GPIO_PIN_2
#define USARTz_APBxClkCmd     	RCC_EnableAPB1PeriphClk
#define USARTz_DMAx           	DMA1
#define USARTz_DMAx_CLK       	RCC_AHB_PERIPH_DMA1
#define USARTz_DR_Base        	(USART2_BASE + 0x04)
#define USARTz_Tx_DMA_Channel 	DMA1_CH7
#define USARTz_Tx_DMA_FLAG    	DMA1_FLAG_TC7
#define USARTz_Rx_DMA_Channel 	DMA1_CH6
#define USARTz_Rx_DMA_FLAG    	DMA1_FLAG_TC6
#endif

#ifdef _USART3_UART4_
#define USARTy                	USART3
#define USARTy_GPIO           	GPIOB
#define USARTy_CLK            	RCC_APB1_PERIPH_USART3
#define USARTy_GPIO_CLK       	RCC_APB2_PERIPH_GPIOB
#define USARTy_RxPin          	GPIO_PIN_11
#define USARTy_TxPin          	GPIO_PIN_10
#define USARTy_APBxClkCmd     	RCC_EnableAPB1PeriphClk
#define USARTy_DMAx           	DMA1
#define USARTy_DMAx_CLK       	RCC_AHB_PERIPH_DMA1
#define USARTy_DR_Base        	(USART3_BASE + 0x04)
#define USARTy_Tx_DMA_Channel 	DMA1_CH2
#define USARTy_Tx_DMA_FLAG    	DMA1_FLAG_TC2
#define USARTy_Rx_DMA_Channel 	DMA1_CH3
#define USARTy_Rx_DMA_FLAG    	DMA1_FLAG_TC3

#define USARTz                	UART4
#define USARTz_GPIO           	GPIOC
#define USARTz_CLK            	RCC_APB1_PERIPH_UART4
#define USARTz_GPIO_CLK       	RCC_APB2_PERIPH_GPIOC
#define USARTz_RxPin          	GPIO_PIN_11
#define USARTz_TxPin          	GPIO_PIN_10
#define USARTz_APBxClkCmd     	RCC_EnableAPB1PeriphClk
#define USARTz_DMAx           	DMA2
#define USARTz_DMAx_CLK       	RCC_AHB_PERIPH_DMA2
#define USARTz_DR_Base        	(UART4_BASE + 0x04)
#define USARTz_Tx_DMA_Channel 	DMA2_CH5
#define USARTz_Tx_DMA_FLAG    	DMA2_FLAG_TC5
#define USARTz_Rx_DMA_Channel 	DMA2_CH3
#define USARTz_Rx_DMA_FLAG    	DMA2_FLAG_TC3
#endif

#ifdef _UART6_UART7_
#define USARTy                	UART6
#define USARTy_GPIO           	GPIOE
#define USARTy_CLK            	RCC_APB2_PERIPH_UART6
#define USARTy_GPIO_CLK       	RCC_APB2_PERIPH_GPIOE
#define USARTy_RxPin          	GPIO_PIN_3
#define USARTy_TxPin          	GPIO_PIN_2
#define USARTy_APBxClkCmd     	RCC_EnableAPB2PeriphClk
#define USARTy_DMAx           	DMA2
#define USARTy_DMAx_CLK       	RCC_AHB_PERIPH_DMA2
#define USARTy_DR_Base        	(UART6_BASE + 0x04)
#define USARTy_Tx_DMA_Channel 	DMA2_CH2
#define USARTy_Tx_DMA_FLAG    	DMA2_FLAG_TC2
#define USARTy_Rx_DMA_Channel 	DMA2_CH1
#define USARTy_Rx_DMA_FLAG    	DMA2_FLAG_TC1

#define USARTz                	UART7
#define USARTz_GPIO           	GPIOC
#define USARTz_CLK            	RCC_APB2_PERIPH_UART7
#define USARTz_GPIO_CLK       	RCC_APB2_PERIPH_GPIOC
#define USARTz_RxPin          	GPIO_PIN_5
#define USARTz_TxPin          	GPIO_PIN_4
#define USARTz_APBxClkCmd     	RCC_EnableAPB2PeriphClk
#define USARTz_DMAx           	DMA2
#define USARTz_DMAx_CLK       	RCC_AHB_PERIPH_DMA2
#define USARTz_DR_Base        	(UART7_BASE + 0x04)
#define USARTz_Tx_DMA_Channel 	DMA2_CH7
#define USARTz_Tx_DMA_FLAG    	DMA2_FLAG_TC7
#define USARTz_Rx_DMA_Channel 	DMA2_CH6
#define USARTz_Rx_DMA_FLAG    	DMA2_FLAG_TC6
#endif


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */
