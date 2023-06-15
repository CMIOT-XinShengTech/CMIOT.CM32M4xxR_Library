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

#include "main.h"

/** @addtogroup CM32M4xxR_StdPeriph_Examples
 * @{
 */

/**
 * @brief  Main function
 */
int main(void)
{
	/* EXTBoard R/G/B LED*/
	LedInit(LED_RED_PORT, LED_RED_PIN);
	LedInit(LED_GREEN_PORT, LED_GREEN_PIN);
	LedInit(LED_BLUE_PORT, LED_BLUE_PIN);

	/* BaseBorad LED */
	LedInit(LED1_PORT, LED1_PIN);
	LedInit(LED2_PORT, LED2_PIN);
	LedInit(LED3_PORT, LED3_PIN);

	/* EXTBoard RGBLED*/
	LedInit(RGBLED_R_PORT, RGBLED_R_PIN);
	LedInit(RGBLED_G_PORT, RGBLED_G_PIN);
	LedInit(RGBLED_B_PORT, RGBLED_B_PIN);
	/* use pwm to adjust the light of RGBLED */
	RGBLEDPwmInit(TIM4, 100);

    while (1)
    {
    	/*LED ON*/
    	LedOn(LED_RED_PORT, LED_RED_PIN);
    	LedOn(LED_GREEN_PORT, LED_GREEN_PIN);
    	LedOn(LED_BLUE_PORT, LED_BLUE_PIN);

    	LedOn(LED1_PORT, LED1_PIN);
    	LedOn(LED2_PORT, LED2_PIN);
    	LedOn(LED3_PORT, LED3_PIN);

    	/* configure RGBLED light */
    	RGBLEDValueCfg(20, 127, 255);
    	/* RGBLED ON */
    	RGBLEDPwmStart(TIM4);

    	delay_ms(1000);

    	/* RGBLED OFF */
    	RGBLEDPwmStop(TIM4);

    	/* LED OFF */
    	LedOff(LED_RED_PORT, LED_RED_PIN);
    	LedOff(LED_GREEN_PORT, LED_GREEN_PIN);
    	LedOff(LED_BLUE_PORT, LED_BLUE_PIN);

    	LedOff(LED1_PORT, LED1_PIN);
    	LedOff(LED2_PORT, LED2_PIN);
    	LedOff(LED3_PORT, LED3_PIN);

    	delay_ms(1000);
    }
}



/**
 * @}
 */

/**
 * @}
 */
