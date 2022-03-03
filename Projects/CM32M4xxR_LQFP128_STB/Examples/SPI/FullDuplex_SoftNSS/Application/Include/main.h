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
 * @file main.h
 * @author CMIOT Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */

#ifndef __MAIN_H__
#define __MAIN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "nuclei_sdk_soc.h"

/* SPI configuration */
#define SPIy         	SPI1
#define SPIy_CLK     	RCC_APB2_PERIPH_SPI1
#define SPIy_GPIO     	GPIOA
#define SPIy_GPIO_CLK	RCC_APB2_PERIPH_GPIOA
#define SPIy_PIN_SCK  	GPIO_PIN_5
#define SPIy_PIN_MISO	GPIO_PIN_6
#define SPIy_PIN_MOSI	GPIO_PIN_7

#define SPIz         	SPI2
#define SPIz_CLK     	RCC_APB1_PERIPH_SPI2
#define SPIz_GPIO    	GPIOB
#define SPIz_GPIO_CLK	RCC_APB2_PERIPH_GPIOB
#define SPIz_PIN_SCK 	GPIO_PIN_13
#define SPIz_PIN_MISO	GPIO_PIN_14
#define SPIz_PIN_MOSI	GPIO_PIN_15

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */
