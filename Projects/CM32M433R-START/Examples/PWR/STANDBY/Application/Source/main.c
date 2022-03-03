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

#include "log.h"
#include "led.h"

/** @addtogroup CM32M4xxR_StdPeriph_Examples
 * @{
 */

/** @addtogroup PWR_STANDBY
 * @{
 */
void Delay(u32 nCount);
/**
 * @brief  Main function.
 */
int main(void)
{
    /* Initialize LEDs */
	LedInit(LED1_PORT, (LED1_PIN | LED2_PIN));

    /* Turn on LED1 and LED2 */
	LedOn(LED1_PORT, LED1_PIN);
	LedOn(LED1_PORT, LED2_PIN);

    /* Enable PWR and BKP clock */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_PWR, ENABLE);

    /* Enable WKUP pin */
    PWR_WakeUpPinEnable(ENABLE);

    /* Keep debugger connecting when in standby mode */
    DBG_ConfigPeriph(DBG_STDBY, ENABLE);

    while (1)
    {
        /* Check if the Wake-Up flag is set */
        if (PWR_GetFlagStatus(PWR_WU_FLAG) != RESET)
        {
            /* Clear Wake Up flag */
            PWR_ClearFlag(PWR_WU_FLAG);
        }
        /* Delay a long time */
        Delay(600);
        /* SRAM3 retention, SR2STBRET = 1 */
        PWR->CTRL2 |= PWR_CTRL2_SR2STBRET;

        /* Turn off LED1 and LED2 */
        LedOff(LED1_PORT, LED1_PIN);
        LedOff(LED1_PORT, LED2_PIN);

        /* Request to enter STANDBY mode */
        PWR_EnterStandbyState();
    }
}

/**
 * @brief  Delay.
 * @param  nCount set the delay time.
 */
void Delay(u32 nCount)
{
    volatile u32 index = 0;
    for (index = (34000 * nCount); index != 0; index--)
    {
    }
}

/**
 * @}
 */

/**
 * @}
 */
