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
#include "bsp.h"

/** @addtogroup CM32M4xxR_StdPeriph_Examples
 * @{
 */

/** @addtogroup TIM_TimeBase
 * @{
 */
/* User can change TIM2 counter clock as you need。range:PCLK1*2 ~ PCLK1/65536
 * Note: the CCRx_val is calculated from TIMER2_CNT_CLK, it should be less than 65535 */
#define TIMER2_CNT_CLK (2000000U)

TIM_TimeBaseInitType TIM_TimeBaseStructure;
TIM_OCInitType TIM_OCInitStructure;
RCC_ClocksType RCC_ClockStructure;
uint16_t CCR1_Val  = (uint16_t)(TIMER2_CNT_CLK / 50);
uint16_t CCR2_Val  = (uint16_t)(TIMER2_CNT_CLK / 100);
uint16_t CCR3_Val  = (uint16_t)(TIMER2_CNT_CLK / 150);
uint16_t CCR4_Val  = (uint16_t)(TIMER2_CNT_CLK / 200);
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
    TIM2 Configuration: Output Compare Timing Mode:
    TIM2 counter clock = TIMER2_CNT_CLK settings,
    if APB1Prescaler  = 1,   TIM2 counter clock = (PCLK1/ (PrescalerValue + 1))
    if APB1Prescaler != 1,   TIM2 counter clock = (2* PCLK1/ (PrescalerValue + 1))
    TIM2 counter clock = TIM2 counter clock = (2* PCLK1/ (PrescalerValue + 1))
    CC1 update rate = CC1 interrupt rate = TIM2 counter clock / CCR1_Val = 50 Hz
    PC6 IO toggle rate  = CC1 interrupt rate
    PC6 IO waveform rate =IO toggle rate/2
    CC2 update rate = CC2 interrupt rate= TIM2 counter clock / CCR2_Val = 100 Hz
    PC7 IO toggle rate  = CC2 interrupt rate
    PC7 IO waveform rate =IO toggle rate/2
    CC3 update rate = CC3 interrupt rate=TIM2 counter clock / CCR3_Val = 150 Hz
    PC8 IO toggle rate  = CC3 interrupt rate
    PC8 IO waveform rate =IO toggle rate/2
    CC4 update rate =CC4 interrupt rate= TIM2 counter clock / CCR4_Val = 200 Hz
    PC9 IO toggle rate  = CC4 interrupt rate
    PC9 IO waveform rate =IO toggle rate/2
    --------------------------------------------------------------- */
    /* Get the Clock of RCC*/
    RCC_GetClocksFreqValue(&RCC_ClockStructure);
    /* Compute the Timer prescaler value according to TIMER2_CNT_CLK = (PCLK1*2 / (PrescalerValue + 1))*/
    PrescalerValue = (uint16_t)(RCC_ClockStructure.Pclk1Freq*2 / TIMER2_CNT_CLK) - 1;

    TIM_InitTimBaseStruct(&TIM_TimeBaseStructure);
    /* Time base configuration */
    TIM_TimeBaseStructure.Period    = 65535; /* Max value to guarantee continuous counting */
    TIM_TimeBaseStructure.Prescaler = 0;
    TIM_TimeBaseStructure.ClkDiv    = 0;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;

    TIM_InitTimeBase(TIM2, &TIM_TimeBaseStructure);

    /* Prescaler configuration */
    TIM_ConfigPrescaler(TIM2, PrescalerValue, TIM_PSC_RELOAD_MODE_IMMEDIATE);

    TIM_InitOcStruct(&TIM_OCInitStructure);
    /* Output Compare Timing Mode configuration: Channel1 */
    TIM_OCInitStructure.OcMode      = TIM_OCMODE_TIMING;
    TIM_OCInitStructure.Pulse       = CCR1_Val;
    //TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
    //TIM_OCInitStructure.OcPolarity  = TIM_OC_POLARITY_HIGH;

    TIM_InitOc1(TIM2, &TIM_OCInitStructure);

    TIM_ConfigOc1Preload(TIM2, TIM_OC_PRE_LOAD_DISABLE);

    /* Output Compare Timing Mode configuration: Channel2 */
    TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.Pulse       = CCR2_Val;

    TIM_InitOc2(TIM2, &TIM_OCInitStructure);

    TIM_ConfigOc2Preload(TIM2, TIM_OC_PRE_LOAD_DISABLE);

    /* Output Compare Timing Mode configuration: Channel3 */
    TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.Pulse       = CCR3_Val;

    TIM_InitOc3(TIM2, &TIM_OCInitStructure);

    TIM_ConfigOc3Preload(TIM2, TIM_OC_PRE_LOAD_DISABLE);

    /* Output Compare Timing Mode configuration: Channel4 */
    TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.Pulse       = CCR4_Val;

    TIM_InitOc4(TIM2, &TIM_OCInitStructure);

    TIM_ConfigOc4Preload(TIM2, TIM_OC_PRE_LOAD_DISABLE);

    /* TIM IT enable */
    TIM_ConfigInt(TIM2, TIM_INT_CC1 | TIM_INT_CC2 | TIM_INT_CC3 | TIM_INT_CC4, ENABLE);

    /* Enable Interrupt */
    __enable_irq();

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
	/* PCLK1 = 36M */


    /* TIM2 clock enable */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM2, ENABLE);

    /* GPIOD clock enable */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOD, ENABLE);
}

/**
 * @brief  Configure the GPIO Pins.
 */
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    /* GPIOD Configuration:Pin3, 4, 5 and 6 as alternate function push-pull */
    GPIO_InitStructure.Pin        = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

    GPIO_Init(GPIOD, &GPIO_InitStructure);
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
