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
 * @file key.h
 * @author CMIOT Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */
#ifndef __KEY_H__
#define __KEY_H__

#define KEY_INPUT_PORT1		    GPIOA   /* WKUP key or normal key */
#define KEY_INPUT_PORT2         GPIOC	/* RTC key or normal key*/
#define KEY_INPUT_PORT3			GPIOA	/* TSC input 1 or normal key */
#define KEY_INPUT_PORT4			GPIOA   /* TSC input 2 or normal key */

#define KEY_INPUT_PIN1       	GPIO_PIN_0
#define KEY_INPUT_PIN2       	GPIO_PIN_13
#define KEY_INPUT_PIN3			GPIO_PIN_4
#define KEY_INPUT_PIN4			GPIO_PIN_5

#define KEY_INPUT_EXTI_LINE   	EXTI_LINE0
#define KEY_INPUT_PORT_SOURCE 	GPIOA_PORT_SOURCE
#define KEY_INPUT_PIN_SOURCE  	GPIO_PIN_SOURCE0
#define KEY_INPUT_IRQn        	EXTI0_IRQn
#define KEY_INPUT_IRQHandler	EXTI0_IRQHandler

void KeyInputInit(GPIO_Module* GPIOx, uint16_t Pin);
FlagStatus KeyReadValue(GPIO_Module* GPIOx, uint16_t Pin);
void KeyInputExtiInit(GPIO_Module* GPIOx, uint16_t Pin);

#endif /* __KEY_H__ */
