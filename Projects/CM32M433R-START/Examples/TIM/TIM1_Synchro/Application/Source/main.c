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

/** @addtogroup TIM_TIM1_Synchro
 * @{
 */

TIM_TimeBaseInitType TIM_TimeBaseStructure;
TIM_OCInitType TIM_OCInitStructure;
TIM_BDTRInitType TIM_BDTRInitStructure;

void RCC_Configuration(void);
void GPIO_Configuration(void);

/**
 * @brief   Main function
 */
int main(void)
{
	RCC_ClocksType RCC_Clock;

    /* System Clocks Configuration */
    RCC_Configuration();

    /* GPIO Configuration */
    GPIO_Configuration();

    RCC_GetClocksFreqValue(&RCC_Clock);

    /* TIM1 and Timers(TIM3 and TIM4) synchronisation in parallel mode -----------
     1/TIM1 is configured as Master Timer:
     - PWM Mode is used
     - The TIM1 Update event is used as Trigger Output

     2/TIM3 and TIM4 are slaves for TIM1,
     - PWM Mode is used
     - The ITR0(TIM1) is used as input trigger for both slaves
     - Gated mode is used, so starts and stops of slaves counters
       are controlled by the Master trigger output signal(update event).

    The PCLK2 is 72 MHz and APB2 Prescaler is not 1, TIM1 CLK is 144M,
    TIM1 Prescaler = 18 so the TIM1 counter clock is 8 MHz.

    The Master Timer TIM1 is running at:
    TIM1 frequency = TIM1 counter clock / (TIM1_Period + 1) = 31.25 KHz
    and the duty cycle is equal to: TIM1_CCR1 / (TIM1_ARR + 1) = 50%

    The TIM3 is running at:
    (TIM1 frequency) / ((TIM3 period + 1) * (Repetition_Counter + 1)) = 2.08 KHz and
    a duty cycle equal to TIM3_CCR1 / (TIM3_ARR + 1) = 33.3%

    The TIM4 is running at:
    (TIM1 frequency) / ((TIM4 period + 1) * (Repetition_Counter + 1)) = 3.13 KHz and
    a duty cycle equal to TIM4_CCR1 / (TIM4_ARR + 1) = 50%
    --------------------------------------------------------------------------- */

    /* TIM3 Peripheral Configuration ---------------------------------------- */
    /* TIM3 Slave Configuration: PWM1 Mode */
    TIM_TimeBaseStructure.Period    = 2;
    TIM_TimeBaseStructure.Prescaler = 0;
    TIM_TimeBaseStructure.ClkDiv    = 0;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;

    TIM_InitTimeBase(TIM3, &TIM_TimeBaseStructure);

    TIM_OCInitStructure.OcMode      = TIM_OCMODE_PWM1;
    TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.Pulse       = 1;

    TIM_InitOc1(TIM3, &TIM_OCInitStructure);

    /* Slave Mode selection: TIM3 */
    TIM_SelectSlaveMode(TIM3, TIM_SLAVE_MODE_GATED);

    /* TIM4 Peripheral Configuration ---------------------------------------- */
    /* TIM4 Slave Configuration: PWM1 Mode */
    TIM_TimeBaseStructure.Period    = 1;
    TIM_TimeBaseStructure.Prescaler = 0;
    TIM_TimeBaseStructure.ClkDiv    = 0;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;

    TIM_InitTimeBase(TIM4, &TIM_TimeBaseStructure);

    TIM_OCInitStructure.OcMode      = TIM_OCMODE_PWM1;
    TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.Pulse       = 1;

    TIM_InitOc1(TIM4, &TIM_OCInitStructure);

    /* Slave Mode selection: TIM4 */
    TIM_SelectSlaveMode(TIM4, TIM_SLAVE_MODE_GATED);
    TIM_SelectInputTrig(TIM4, TIM_TRIG_SEL_IN_TR0);

    /* TIM1 Peripheral Configuration ---------------------------------------- */
    /* Time Base configuration */
    TIM_TimeBaseStructure.Prescaler = 17;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
    TIM_TimeBaseStructure.Period    = 255;
    TIM_TimeBaseStructure.ClkDiv    = 0;
    TIM_TimeBaseStructure.RepetCnt  = 4;

    TIM_InitTimeBase(TIM1, &TIM_TimeBaseStructure);

    /* Channel 1 Configuration in PWM mode */
    TIM_OCInitStructure.OcMode       = TIM_OCMODE_PWM2;
    TIM_OCInitStructure.OutputState  = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.OutputNState = TIM_OUTPUT_NSTATE_ENABLE;
    TIM_OCInitStructure.Pulse        = 127;
    TIM_OCInitStructure.OcPolarity   = TIM_OC_POLARITY_LOW;
    TIM_OCInitStructure.OcNPolarity  = TIM_OCN_POLARITY_LOW;
    TIM_OCInitStructure.OcIdleState  = TIM_OC_IDLE_STATE_SET;
    TIM_OCInitStructure.OcNIdleState = TIM_OCN_IDLE_STATE_RESET;

    TIM_InitOc1(TIM1, &TIM_OCInitStructure);

    /* Master Mode selection */
    TIM_SelectOutputTrig(TIM1, TIM_TRGO_SRC_UPDATE);

    /* Select the Master Slave Mode */
    TIM_SelectMasterSlaveMode(TIM1, TIM_MASTER_SLAVE_MODE_ENABLE);

    /* TIM1 counter enable */
    TIM_Enable(TIM1, ENABLE);

    /* TIM enable counter */
    TIM_Enable(TIM3, ENABLE);
    TIM_Enable(TIM4, ENABLE);

    /* Main Output Enable */
    TIM_EnableCtrlPwmOutputs(TIM1, ENABLE);

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

    /* TIM1, GPIOA and GPIOB clock enable */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_TIM1  | RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_GPIOD |
    						RCC_APB2_PERIPH_GPIOC | RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_AFIO,
                            ENABLE);

    /* TIM3 and TIM4 clock enable */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM3 | RCC_APB1_PERIPH_TIM4, ENABLE);
}

/**
 * @brief  Configures TIM1, TIM3 and TIM4 Pins.
 */
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    /* GPIOA Configuration: TIM1 Channel1 as alternate function push-pull */
    GPIO_InitStructure.Pin        = GPIO_PIN_8;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.Pin = GPIO_PIN_13;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* GPIOB Configuration: TIM3 Channel1 as alternate function push-pull */
    GPIO_InitStructure.Pin = GPIO_PIN_6;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_ConfigPinRemap(GPIO_ALL_RMP_TIM3,ENABLE);

    /* GPIOB Configuration: TIM4 Channel1 as alternate function push-pull */
    GPIO_InitStructure.Pin = GPIO_PIN_12;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_ConfigPinRemap(GPIO_RMP_TIM4, ENABLE);
}

/**
 * @}
 */

/**
 * @}
 */
