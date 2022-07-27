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
 * @file cm32m4xxr_it.c
 * @author CMIOT Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */
#include "cm32m4xxr_it.h"
#include "main.h"

/** @addtogroup CM32M4xxR_StdPeriph_Template
 * @{
 */

extern __IO uint8_t USART1_Tx_Done;
extern __IO uint8_t USART2_Rx_Done;
extern __IO uint8_t USART4_Tx_Done;
extern __IO uint8_t USART4_Rx_Done;

extern uint8_t TxBuffer6[], RxBuffer7[];
extern uint8_t TxCounter6, RxCounter7;
extern uint8_t NbrOfDataToTransfer6;

/******************************************************************************/
/*                 N308 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
 * @brief  This function handles NMI exception.
 */
void InsUnalign_EXCHandler(void)
{
	while(1)
	{
	
	}
}

/******************************************************************************/
/*                 N308 Processor Interrupt Handlers                          */
/******************************************************************************/

/**
 * @brief  This function handles software interrupt request.
 */
void eclic_msip_handler(void)
{

}

/**
 * @brief  This function handles TIMER interrupt request.
 */
void eclic_mtip_handler(void)
{

}


/******************************************************************************/
/* CM32M4xxR Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_cm32m4xxr.S).                    */
/******************************************************************************/

/**
 * @brief  This function handles USART1_Tx DMA global interrupt request.
 */
void USART1_Tx_DMA_IRQHandler(void)
{
    if(DMA_GetIntStatus(USART1_Tx_DMA_INT, USART1_DMAx) != RESET)
    {
        USART1_Tx_Done = 1;
            
        DMA_ConfigInt(USART1_Tx_DMA_Channel, DMA_INT_TXC, DISABLE);
        DMA_ClrIntPendingBit(USART1_Tx_DMA_INT, USART1_DMAx);
    }     
}

/**
 * @brief  This function handles USART2_Rx DMA global interrupt request.
 */
void USART2_Rx_DMA_IRQHandler(void)
{
    if(DMA_GetIntStatus(USART2_Rx_DMA_INT, USART2_DMAx) != RESET)
    {
        USART2_Rx_Done = 1;
            
        DMA_ConfigInt(USART2_Rx_DMA_Channel, DMA_INT_TXC, DISABLE);
        DMA_ClrIntPendingBit(USART2_Rx_DMA_INT, USART2_DMAx);
    }     
}

/**
 * @brief  This function handles USART4_Tx DMA global interrupt request.
 */
void USART4_Tx_DMA_IRQHandler(void)
{
    if(DMA_GetIntStatus(USART4_Tx_DMA_INT, USART4_DMAx) != RESET)
	{
		USART4_Tx_Done = 1;

		DMA_ConfigInt(USART4_Tx_DMA_Channel, DMA_INT_TXC, DISABLE);
		DMA_ClrIntPendingBit(USART4_Tx_DMA_INT, USART4_DMAx);
	}
}

/**
 * @brief  This function handles USART4_Rx DMA global interrupt request.
 */
void USART4_Rx_DMA_IRQHandler(void)
{
    if(DMA_GetIntStatus(USART4_Rx_DMA_INT, USART4_DMAx) != RESET)
    {
        USART4_Rx_Done = 1;

        DMA_ConfigInt(USART4_Rx_DMA_Channel, DMA_INT_TXC, DISABLE);
        DMA_ClrIntPendingBit(USART4_Rx_DMA_INT, USART4_DMAx);
    }
}

/**
 * @brief  This function handles USART6 global interrupt request.
 */
void UART6_IRQHandler(void)
{
	if (USART_GetIntStatus(UART6, USART_INT_TXDE) != RESET)
	{
		/* Write one byte to the transmit data register */
		USART_SendData(UART6, TxBuffer6[TxCounter6++]);

		if (TxCounter6 == NbrOfDataToTransfer6)
		{
			/* Disable the USARTy Transmit interrupt */
			USART_ConfigInt(UART6, USART_INT_TXDE, DISABLE);
		}
	}
}

/**
 * @brief  This function handles USART7 global interrupt request.
 */
void UART7_IRQHandler(void)
{
	if (USART_GetIntStatus(UART7, USART_INT_RXDNE) != RESET)
	{
		/* Read one byte from the receive data register */
		RxBuffer7[RxCounter7++] = USART_ReceiveData(UART7);

		if (RxCounter7 == NbrOfDataToTransfer6)
		{
			/* Disable the USARTy Receive interrupt */
			USART_ConfigInt(UART7, USART_INT_RXDNE, DISABLE);
		}
	}
}

/**
 * @}
 */
