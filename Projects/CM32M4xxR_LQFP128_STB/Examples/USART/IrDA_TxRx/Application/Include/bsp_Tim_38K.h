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
 * @file bsp_Tim_38K.c
 * @author CMIOT Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */

#ifndef __BSP_TIM_38K_H__
#define __BSP_TIM_38K_H__

#include "nuclei_sdk_soc.h"

#define ADVANCE_TIM              	TIM1
#define ADVANCE_TIM_APBxClock_FUN	RCC_EnableAPB2PeriphClk
#define ADVANCE_TIM_CLK           	RCC_APB2_PERIPH_TIM1
#define ADVANCE_TIM_Period        	(105 - 1) //(947 - 1)
#define ADVANCE_TIM_Prescaler     	(2 - 1)
#define ADVANCE_TIM_Pulse         	(52) //473

#define ADVANCE_TIM_CH1_GPIO_CLK    RCC_APB2_PERIPH_GPIOE
#define ADVANCE_TIM_CH1_PORT        GPIOE      
#define ADVANCE_TIM_CH1_PIN         GPIO_PIN_9
#define ADVANCE_TIM_CH1_GPIO_RMP    GPIO_ALL_RMP_TIM1

void ADVANCE_TIM_Init(void);

#endif /* __BSP_TIM_38K_H__ */
