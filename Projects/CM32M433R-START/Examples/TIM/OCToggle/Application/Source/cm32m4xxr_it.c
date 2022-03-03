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

uint16_t capture = 0;
extern __IO uint16_t CCR1_Val;
extern __IO uint16_t CCR2_Val;
extern __IO uint16_t CCR3_Val;
extern __IO uint16_t CCR4_Val;

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
 * @brief  This function handles TIM3 global interrupt request.
 */
void TIM3_IRQHandler(void)
{
    /* TIM3_CH1 toggling with frequency = 183.1 Hz */
    if (TIM_GetIntStatus(TIM3, TIM_INT_CC1) != RESET)
    {
        TIM_ClrIntPendingBit(TIM3, TIM_INT_CC1);
        capture = TIM_GetCap1(TIM3);
        TIM_SetCmp1(TIM3, capture + CCR1_Val);
    }

    /* TIM3_CH2 toggling with frequency = 366.2 Hz */
    if (TIM_GetIntStatus(TIM3, TIM_INT_CC2) != RESET)
    {
        TIM_ClrIntPendingBit(TIM3, TIM_INT_CC2);
        capture = TIM_GetCap2(TIM3);
        TIM_SetCmp2(TIM3, capture + CCR2_Val);
    }

    /* TIM3_CH3 toggling with frequency = 732.4 Hz */
    if (TIM_GetIntStatus(TIM3, TIM_INT_CC3) != RESET)
    {
        TIM_ClrIntPendingBit(TIM3, TIM_INT_CC3);
        capture = TIM_GetCap3(TIM3);
        TIM_SetCmp3(TIM3, capture + CCR3_Val);
    }

    /* TIM3_CH4 toggling with frequency = 1464.8 Hz */
    if (TIM_GetIntStatus(TIM3, TIM_INT_CC4) != RESET)
    {
        TIM_ClrIntPendingBit(TIM3, TIM_INT_CC4);
        capture = TIM_GetCap4(TIM3);
        TIM_SetCmp4(TIM3, capture + CCR4_Val);
    }
}

/**
 * @}
 */
