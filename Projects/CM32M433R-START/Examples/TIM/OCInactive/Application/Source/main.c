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

/** @addtogroup TIM_OCInactive
 * @{
 */

TIM_TimeBaseInitType TIM_TimeBaseStructure;
TIM_OCInitType TIM_OCInitStructure;
uint16_t CCR1_Val       = 1000;
uint16_t CCR2_Val       = 500;
uint16_t CCR3_Val       = 250;
uint16_t CCR4_Val       = 125;
uint16_t PrescalerValue = 0;

void RCC_Configuration(void);
void GPIO_Configuration(void);
void ECLIC_Configuration(void);

/**
 * @brief  Main function
 */
int main(void)
{
    /* System Clocks Configuration */
    RCC_Configuration();

    /* ECLIC Configuration */
    ECLIC_Configuration();

    /* GPIO Configuration */
    GPIO_Configuration();

    /* ---------------------------------------------------------------
    TIM2 Configuration:
    TIM2CLK = SystemCoreClock,
    The objective is to get TIM2 counter clock at 1 KHz:
     - Prescaler = (TIM2CLK / TIM2 counter clock) - 1
    And generate 4 signals with 4 different delays:
    TIM2_CH1 delay = CCR1_Val / TIM2 counter clock = 1000 ms
    TIM2_CH2 delay = CCR2_Val / TIM2 counter clock = 500 ms
    TIM2_CH3 delay = CCR3_Val / TIM2 counter clock = 250 ms
    TIM2_CH4 delay = CCR4_Val / TIM2 counter clock = 125 ms

    --------------------------------------------------------------- */
    /* Compute the prescaler value */
    PrescalerValue = (uint16_t)(SystemCoreClock / 1000) - 1;

    /* Time base configuration */
    TIM_TimeBaseStructure.Period    = 65535;
    TIM_TimeBaseStructure.Prescaler = PrescalerValue;
    TIM_TimeBaseStructure.ClkDiv    = 0;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;

    TIM_InitTimeBase(TIM2, &TIM_TimeBaseStructure);

    /* Output Compare Active Mode configuration: Channel1 */
    TIM_OCInitStructure.OcMode      = TIM_OCMODE_INACTIVE;
    TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.Pulse       = CCR1_Val;
    TIM_OCInitStructure.OcPolarity  = TIM_OC_POLARITY_HIGH;

    TIM_InitOc1(TIM2, &TIM_OCInitStructure);

    TIM_ConfigOc1Preload(TIM2, TIM_OC_PRE_LOAD_DISABLE);

    /* Output Compare Active Mode configuration: Channel2 */
    TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.Pulse       = CCR2_Val;

    TIM_InitOc2(TIM2, &TIM_OCInitStructure);

    TIM_ConfigOc2Preload(TIM2, TIM_OC_PRE_LOAD_DISABLE);

    /* Output Compare Active Mode configuration: Channel3 */
    TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.Pulse       = CCR3_Val;

    TIM_InitOc3(TIM2, &TIM_OCInitStructure);

    TIM_ConfigOc3Preload(TIM2, TIM_OC_PRE_LOAD_DISABLE);

    /* Output Compare Active Mode configuration: Channel4 */
    TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.Pulse       = CCR4_Val;

    TIM_InitOc4(TIM2, &TIM_OCInitStructure);

    TIM_ConfigOc4Preload(TIM2, TIM_OC_PRE_LOAD_DISABLE);

    TIM_ConfigArPreload(TIM2, ENABLE);

    /* TIM IT enable */
    TIM_ConfigInt(TIM2, TIM_INT_CC1 | TIM_INT_CC2 | TIM_INT_CC3 | TIM_INT_CC4, ENABLE);

    /* Enable global interrupt */
    __enable_irq();

    /* Set PC.06, PC.07, PC.08 and PC.09 pins */
    GPIO_SetBits(GPIOC, GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9);

    /* TIM2 enable counter */
    TIM_Enable(TIM2, ENABLE);

    while (1)
    {
    }
}

/**
 * @brief  Configures the different system clocks.
 */
void RCC_Configuration(void)
{
    /* PCLK1 = PCLK2 = HCLK */

    /* TIM2 clock enable */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM2, ENABLE);

    /* GPIOC clock enable */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);
}

/**
 * @brief  Configure the GPIOD Pins.
 */
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    /* GPIOC Configuration: Pin6, 7, 8 and 9 as output push-pull */
    GPIO_InitStructure.Pin        = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/**
 * @brief  Configure ECLIC.
 */
void ECLIC_Configuration(void)
{
    /* Enable the TIM2 Interrupt */
	ECLIC_SetLevelIRQ(TIM2_IRQn, 0);
	ECLIC_SetPriorityIRQ(TIM2_IRQn, 1);
	ECLIC_SetTrigIRQ(TIM2_IRQn, ECLIC_LEVEL_TRIGGER);
	ECLIC_EnableIRQ(TIM2_IRQn);
}

/**
 * @}
 */

/**
 * @}
 */
