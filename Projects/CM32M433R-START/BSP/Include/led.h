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
 * @file led.h
 * @author CMIOT Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */
#ifndef __LED_H__
#define __LED_H__

/* Start BaseBoard LED */
#define LED1_PORT		GPIOB
#define LED2_PORT      	GPIOB
#define LED3_PORT		GPIOB
#define LED1_PIN       	GPIO_PIN_5
#define LED2_PIN       	GPIO_PIN_6
#define LED3_PIN		GPIO_PIN_7

/* Start ExtBoard LED */
#define LED_RED_PORT	GPIOE
#define LED_GREEN_PORT  GPIOE
#define LED_BLUE_PORT   GPIOE
#define LED_RED_PIN		GPIO_PIN_6
#define LED_GREEN_PIN	GPIO_PIN_4
#define LED_BLUE_PIN	GPIO_PIN_2

/* Start ExtBoard RGBLED */
#define RGBLED_B_PORT	GPIOA
#define RGBLED_G_PORT	GPIOF
#define RGBLED_R_PORT	GPIOF
#define RGBLED_B_PIN	GPIO_PIN_2
#define RGBLED_G_PIN	GPIO_PIN_3
#define RGBLED_R_PIN	GPIO_PIN_1

typedef enum {
	LED_ERROR_OK            = 0x00U,  /*!< No error   */
	LED_ERROR_PARA          = 0x01U,  /*!< Parameter error */
}LED_ErrorTypeDef;


/* For all LEDs on BaseBoard and ExtBoard*/
void LedInit(GPIO_Module* GPIOx, uint16_t Pin);
void LedOn(GPIO_Module* GPIOx, uint16_t Pin);
void LedOff(GPIO_Module* GPIOx, uint16_t Pin);
void LedOnOff(GPIO_Module* GPIOx, uint32_t Pin);
void LedBlink(GPIO_Module* GPIOx, uint16_t Pin);

/* For RGB LED on ExtBoard*/
LED_ErrorTypeDef RGBLEDPwmInit(TIM_Module* TIMx, uint32_t Freq);
void RGBLEDValueCfg(uint8_t Red, uint8_t Green, uint8_t Blue);
void RGBLEDPwmStart(TIM_Module* TIMx);
void RGBLEDPwmStop(TIM_Module* TIMx);
void RGBLEDIntHandle(void);

#endif /* __LED_H__ */
