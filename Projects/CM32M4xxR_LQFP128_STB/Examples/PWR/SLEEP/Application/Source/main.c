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
#include <stdio.h>
#include "log.h"
#include "led.h"

/** @addtogroup CM32M4xxR_StdPeriph_Examples
 * @{
 */


/** @addtogroup PWR_SLEEP
 * @{
 */

void delay(vu32 nCount);
void KeyInputExtiInit(GPIO_Module* GPIOx, uint16_t Pin);

/**
 * @brief  Main program.
 */
int main(void)
{
    /*!< At this stage the microcontroller clock setting is already configured,
         this is done through SystemInit() function which is called from startup
         file (startup_cm32m4xxr.s) before to branch to application main.
         To reconfigure the default setting of SystemInit() function, refer to
         system_cm32m4xxr.c file
       */

    /* Enable PWR Clock */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_PWR, ENABLE);

    /* Initialize LEDs on CM32M4xxR-EVAL board */
    LedInit(LED_PORT, (LED2 | LED3));

    LedOff(LED_PORT, LED3);
    LedOn(LED_PORT, LED2);

    /* Initialize Key button Interrupt to wake up the low power */
    KeyInputExtiInit(KEY_INPUT_PORT, KEY_INPUT_PIN);

    /* Clear the Interrupt flag */
    EXTI_ClrITPendBit(EXTI_LINE0);
	/* Enable global interrupt */
	__enable_irq();

    DBG_ConfigPeriph(DBG_SLEEP, ENABLE);

    while (1)
    {
        /* Blink LED3 and turn off LED2 */
    	LedBlink(LED_PORT, LED3);

        /* Insert a long delay */
        delay(600);
        LedOff(LED_PORT, LED2);

        /* Request to enter SLEEP mode*/
        PWR_EnterSLEEPMode(PWR_STOPENTRY_WFI);
    }
}

/**
 * @brief  Delay.
 * @param  nCount set the delay time.
 */
void delay(vu32 nCount)
{
    volatile vu32 index = 0;
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
