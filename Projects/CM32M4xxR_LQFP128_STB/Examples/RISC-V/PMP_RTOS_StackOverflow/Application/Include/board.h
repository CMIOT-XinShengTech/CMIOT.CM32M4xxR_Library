/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author          Notes
 * 2020-04-02     Huaqi Fang      first version
 *
 */

#ifndef __BOARD__
#define __BOARD__

//#include "nuclei_sdk_hal.h"
#include "nuclei_sdk_soc.h"

/* USARTx configuration */
#define _USART1_COM_
//#define _USART2_COM_

#ifdef _USART1_COM_
#define USARTx          	USART1
#define USARTx_GPIO     	GPIOA
#define USARTx_CLK      	RCC_APB2_PERIPH_USART1
#define USARTx_GPIO_CLK		RCC_APB2_PERIPH_GPIOA
#define USARTx_RxPin    	GPIO_PIN_10
#define USARTx_TxPin    	GPIO_PIN_9

#define GPIO_APBxClkCmd		RCC_EnableAPB2PeriphClk
#define USART_APBxClkCmd	RCC_EnableAPB2PeriphClk
#endif

#ifdef _USART2_COM_
#define USARTx          	USART2
#define USARTx_GPIO     	GPIOA
#define USARTx_CLK      	RCC_APB1_PERIPH_USART2
#define USARTx_GPIO_CLK 	RCC_APB2_PERIPH_GPIOA
#define USARTx_RxPin    	GPIO_PIN_3
#define USARTx_TxPin    	GPIO_PIN_2

#define GPIO_APBxClkCmd  	RCC_EnableAPB2PeriphClk
#define USART_APBxClkCmd 	RCC_EnableAPB1PeriphClk
#endif

void rt_hw_board_init(void);

#endif /* __BOARD__ */

/******************** end of file *******************/
