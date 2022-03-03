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
#include "nuclei_sdk_soc.h"

/** @addtogroup CM32M4xxR_StdPeriph_Template
 * @{
 */

uint8_t RxCounter = 0;
extern uint8_t RxBuffer2[];
extern uint8_t NbrOfDataToRead;

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
 * @brief  This function handles UART5 global interrupt request.
 */
void UART5_IRQHandler(void)
{
    if (USART_GetIntStatus(UART5, USART_INT_RXDNE) != RESET)
    {
        /* Read one byte from the receive data register */
        RxBuffer2[RxCounter++] = USART_ReceiveData(UART5);

        if (RxCounter == NbrOfDataToRead)
        {
            /* Disable the UART5 Receive interrupt */
            USART_ConfigInt(UART5, USART_INT_RXDNE, DISABLE);
        }
    }
}

/**
 * @brief  This function handles UART6 global interrupt request.
 */
void UART6_IRQHandler(void)
{
    if (USART_GetIntStatus(UART6, USART_INT_RXDNE) != RESET)
    {
        /* Read one byte from the receive data register */
        RxBuffer2[RxCounter++] = USART_ReceiveData(UART6);

        if (RxCounter == NbrOfDataToRead)
        {
            /* Disable the UART6 Receive interrupt */
            USART_ConfigInt(UART6, USART_INT_RXDNE, DISABLE);
        }
    }
}

/**
 * @brief  This function handles UART7 global interrupt request.
 */
void UART7_IRQHandler(void)
{
    if (USART_GetIntStatus(UART7, USART_INT_RXDNE) != RESET)
    {
        /* Read one byte from the receive data register */
        RxBuffer2[RxCounter++] = USART_ReceiveData(UART7);

        if (RxCounter == NbrOfDataToRead)
        {
            /* Disable the UART7 Receive interrupt */
            USART_ConfigInt(UART7, USART_INT_RXDNE, DISABLE);
        }
    }
}

/**
 * @}
 */
