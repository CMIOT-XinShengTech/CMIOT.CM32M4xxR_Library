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
#include "log.h"

/** @addtogroup CM32M4xxR_StdPeriph_Examples
 * @{
 */

/** @addtogroup TIM_PWM_Output
 * @{
 */

TIM_TimeBaseInitType TIM_TimeBaseStructure;
TIM_OCInitType TIM_OCInitStructure;
uint16_t CCR1_Val       = 333;
uint16_t CCR2_Val       = 249;
uint16_t CCR3_Val       = 166;
uint16_t CCR4_Val       = 83;
uint16_t PrescalerValue = 0;

void RCC_Configuration(void);
void GPIO_Configuration(void);

/**
 * @brief  Main function
 */
int main(void)
{
	RCC_ClocksType RCCClock;

    /* System Clocks Configuration */
    RCC_Configuration();

    /* GPIO Configuration */
    GPIO_Configuration();

    /* -----------------------------------------------------------------------
    TIM3 Configuration: generate 4 PWM signals with 4 different duty cycles:
    The TIM3CLK frequency is set to APB1*2 (72 MHz), to get TIM3 counter
    clock at 4 MHz the Prescaler is computed as following:
     - Prescaler = (TIM3CLK / TIM3 counter clock) - 1

    The TIM3 output is running at 6 KHz, User can change it as you want:
    (AR + 1) = TIM3 counter clock /TIM3 Frequency  = 4 MHz / 6000 = 666
    TIM3 Channel1 duty cycle = (TIM3_CCR1 / (TIM3_ARR + 1)) * 100 = 50%
    TIM3 Channel2 duty cycle = (TIM3_CCR2 / (TIM3_ARR + 1)) * 100 = 37.5%
    TIM3 Channel3 duty cycle = (TIM3_CCR3 / (TIM3_ARR + 1)) * 100 = 25%
    TIM3 Channel4 duty cycle = (TIM3_CCR4 / (TIM3_ARR + 1)) * 100 = 12.5%
    ----------------------------------------------------------------------- */
    /* Compute the prescaler value */
    RCC_GetClocksFreqValue(&RCCClock);
    PrescalerValue = (uint16_t)(RCCClock.Pclk1Freq*2 / 4000000) - 1;

    /* Time base configuration */
    TIM_TimeBaseStructure.Period    = 665;
    TIM_TimeBaseStructure.Prescaler = PrescalerValue;
    TIM_TimeBaseStructure.ClkDiv    = 0;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;

    TIM_InitTimeBase(TIM3, &TIM_TimeBaseStructure);

    /* PWM1 Mode configuration: Channel1 */
    TIM_OCInitStructure.OcMode      = TIM_OCMODE_PWM1;
    TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.Pulse       = CCR1_Val;
    TIM_OCInitStructure.OcPolarity  = TIM_OC_POLARITY_HIGH;

    TIM_InitOc1(TIM3, &TIM_OCInitStructure);

    TIM_ConfigOc1Preload(TIM3, TIM_OC_PRE_LOAD_ENABLE);

    /* PWM1 Mode configuration: Channel2 */
    TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.Pulse       = CCR2_Val;

    TIM_InitOc2(TIM3, &TIM_OCInitStructure);

    TIM_ConfigOc2Preload(TIM3, TIM_OC_PRE_LOAD_ENABLE);

    /* PWM1 Mode configuration: Channel3 */
    TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.Pulse       = CCR3_Val;

    TIM_InitOc3(TIM3, &TIM_OCInitStructure);

    TIM_ConfigOc3Preload(TIM3, TIM_OC_PRE_LOAD_ENABLE);

    /* PWM1 Mode configuration: Channel4 */
    TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.Pulse       = CCR4_Val;

    TIM_InitOc4(TIM3, &TIM_OCInitStructure);

    TIM_ConfigOc4Preload(TIM3, TIM_OC_PRE_LOAD_ENABLE);

    TIM_ConfigArPreload(TIM3, ENABLE);

    /* TIM3 enable counter */
    TIM_Enable(TIM3, ENABLE);

    while (1)
    {
    }
}

/**
 * @brief  Configures the different system clocks.
 */
void RCC_Configuration(void)
{
	/* PCLK1 = 36M PCLK2 = 72M */

    /* TIM3 clock enable */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM3, ENABLE);

    /* GPIOA and GPIOB clock enable */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_GPIOC | RCC_APB2_PERIPH_AFIO, ENABLE);
}

/**
 * @brief  Configure the TIM3 Ouput Channels.
 */
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    /* GPIOA Configuration:TIM3 Channel1, 2, 3 and 4 as alternate function push-pull */
    GPIO_InitStructure.Pin        = GPIO_PIN_6 | GPIO_PIN_7;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}


/**
 * @}
 */

/**
 * @}
 */
