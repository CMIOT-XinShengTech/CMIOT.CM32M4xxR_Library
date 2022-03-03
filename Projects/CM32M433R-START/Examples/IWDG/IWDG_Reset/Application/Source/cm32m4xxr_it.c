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

extern __IO uint32_t TimingDelay;
__IO uint16_t IC1ReadValue1 = 0, IC1ReadValue2 = 0;
__IO uint16_t CaptureNumber = 0;
__IO uint32_t Capture       = 0;
extern uint32_t LsiFreq;

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
    TimingDelay--;

	SysTick_Reload(SystemCoreClock / 1000);
}


/******************************************************************************/
/* CM32M4xxR Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_cm32m4xxr.S).                    */
/******************************************************************************/

/**
 * @brief  This function handles TIM5 global interrupt request.
 */
void TIM5_IRQHandler(void)
{
    if (TIM_GetIntStatus(TIM5, TIM_INT_CC4) != RESET)
    {
        if (CaptureNumber == 0)
        {
            /* Get the Input Capture value */
            IC1ReadValue1 = TIM_GetCap4(TIM5);
        }
        else if (CaptureNumber == 2)
        {
            RCC_ClocksType clks;

            /* Get the Input Capture value */
            IC1ReadValue2 = TIM_GetCap4(TIM5);

            /* Capture computation */
            if (IC1ReadValue2 > IC1ReadValue1)
            {
                Capture = (IC1ReadValue2 - IC1ReadValue1);
            }
            else
            {
                Capture = ((0xFFFF - IC1ReadValue1) + IC1ReadValue2);
            }

            RCC_GetClocksFreqValue(&clks);

            /* Frequency computation */
            uint32_t tim5_clk = (uint32_t)clks.Pclk1Freq * 2;
            LsiFreq = tim5_clk / Capture;
            LsiFreq *= 16; /* 2 * 8 = 16 LSI clocks */
        }

        CaptureNumber++;

        /* Clear TIM5 Capture compare interrupt pending bit */
        TIM_ClrIntPendingBit(TIM5, TIM_INT_CC4);
    }
}

/**
 * @}
 */
