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

#include <main.h>
#include "bsp.h"

/** @addtogroup CM32M4xxR_StdPeriph_Examples
 * @{
 */

/** @addtogroup LedBlink
 * @{
 */

/**
 * @brief Systick Time Counter, increment in Interrupt Handler
 */
volatile uint32_t g_SystickTimeTick = 0;

/**
 * @brief  Main function.
 */
int main(void)
{
    /* SystemInit() function has been called by startup file startup_cm32m4xxr.s */

    /* Initialize Led1  as output pushpull mode */
    LedInit(LED1_PORT, LED1_PIN);


    /* Turn off Led1 */
    LedOff(LED1_PORT, LED1_PIN);


    __enable_irq();

    /* Stop Systick timer*/
    SysTimer_Stop();
    SysTick_Config(SystemCoreClock);
    SysTimer_Start();


    while (1)
    {
    	uint32_t s_CurTimeTick = g_SystickTimeTick;
        /* LED1 Blink when System timer match  */
    	LedBlink(LED1_PORT, LED1_PIN);
    	while(s_CurTimeTick == g_SystickTimeTick);

    }
}

/**
 * @}
 */

/**
 * @}
 */
