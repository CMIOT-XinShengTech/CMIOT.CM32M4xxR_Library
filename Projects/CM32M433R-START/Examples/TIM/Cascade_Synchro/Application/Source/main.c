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

/** @addtogroup TIM_Cascade_Synchro
 * @{
 */

TIM_TimeBaseInitType TIM_TimeBaseStructure;
TIM_OCInitType TIM_OCInitStructure;

void RCC_Configuration(void);
void GPIO_Configuration(void);

/**
 * @brief  Main function
 */
int main(void)
{
    /* System Clocks Configuration */
    RCC_Configuration();

    /* GPIO Configuration */
    GPIO_Configuration();

    /* Timers synchronisation in cascade mode ----------------------------
     1/TIM2 is configured as Master Timer:
     - PWM Mode is used
     - The TIM2 Update event is used as Trigger Output

     2/TIM3 is slave for TIM2 and Master for TIM4,
     - PWM Mode is used
     - The ITR1(TIM2) is used as input trigger
     - Gated mode is used, so start and stop of slave counter
      are controlled by the Master trigger output signal(TIM2 update event).
      - The TIM3 Update event is used as Trigger Output.

      3/TIM4 is slave for TIM3,
     - PWM Mode is used
     - The ITR2(TIM3) is used as input trigger
     - Gated mode is used, so start and stop of slave counter
      are controlled by the Master trigger output signal(TIM3 update event).

	   The PCLK1 is 8 MHz, TIM2 Prescaler = 0 so the TIM2 counter clock is 8 MHz.

       The Master Timer TIM2 is running at TIM2 frequency :
       TIM2 frequency = (TIM2 counter clock) / (TIM2 period + 1) = 31.25 KHz
       and the duty cycle = TIM2_CCR1 / (TIM2_ARR + 1) = 25%.

       The TIM3 is running:
       - At (TIM2 frequency) / (TIM3 period + 1) = 7.81 KHz and a duty cycle
         equal to TIM3_CCR1 / (TIM3_ARR + 1) = 25%

        The TIM4 is running:
      - At (TIM3 frequency) / (TIM4 period + 1) = 1.95 KHz and a duty cycle
        equal to TIM4_CCR1 / (TIM4_ARR + 1) = 25%
    -------------------------------------------------------------------- */

    /* Time base configuration */
    TIM_TimeBaseStructure.Period    = 255;
    TIM_TimeBaseStructure.Prescaler = 0;
    TIM_TimeBaseStructure.ClkDiv    = 0;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;

    TIM_InitTimeBase(TIM2, &TIM_TimeBaseStructure);

    TIM_TimeBaseStructure.Period = 3;
    TIM_InitTimeBase(TIM3, &TIM_TimeBaseStructure);

    TIM_TimeBaseStructure.Period = 3;
    TIM_InitTimeBase(TIM4, &TIM_TimeBaseStructure);

    /* Master Configuration in PWM1 Mode */
    TIM_OCInitStructure.OcMode      = TIM_OCMODE_PWM1;
    TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.Pulse       = 64;
    TIM_OCInitStructure.OcPolarity  = TIM_OC_POLARITY_HIGH;

    TIM_InitOc1(TIM2, &TIM_OCInitStructure);

    /* Select the Master Slave Mode */
    TIM_SelectMasterSlaveMode(TIM2, TIM_MASTER_SLAVE_MODE_ENABLE);

    /* Master Mode selection */
    TIM_SelectOutputTrig(TIM2, TIM_TRGO_SRC_UPDATE);

    /* Slaves Configuration: PWM1 Mode */
    TIM_OCInitStructure.OcMode      = TIM_OCMODE_PWM1;
    TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.Pulse       = 1;

    TIM_InitOc1(TIM3, &TIM_OCInitStructure);

    TIM_InitOc1(TIM4, &TIM_OCInitStructure);

    /* Slave Mode selection: TIM3 */
    TIM_SelectSlaveMode(TIM3, TIM_SLAVE_MODE_GATED);
    TIM_SelectInputTrig(TIM3, TIM_TRIG_SEL_IN_TR1);

    /* Select the Master Slave Mode */
    TIM_SelectMasterSlaveMode(TIM3, TIM_MASTER_SLAVE_MODE_ENABLE);

    /* Master Mode selection: TIM3 */
    TIM_SelectOutputTrig(TIM3, TIM_TRGO_SRC_UPDATE);

    /* Slave Mode selection: TIM4 */
    TIM_SelectSlaveMode(TIM4, TIM_SLAVE_MODE_GATED);
    TIM_SelectInputTrig(TIM4, TIM_TRIG_SEL_IN_TR2);

    /* TIM enable counter */
    TIM_Enable(TIM3, ENABLE);
    TIM_Enable(TIM2, ENABLE);
    TIM_Enable(TIM4, ENABLE);

    while (1)
    {
    }
}

/**
 * @brief  Configures the different system clocks.
 */
void RCC_Configuration(void)
{
	/* PCLK1 = PCLK2 = HCLK = 8M */

    /* TIM2, TIM3 and TIM4 clock enable */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM2 | RCC_APB1_PERIPH_TIM3 | RCC_APB1_PERIPH_TIM4, ENABLE);

    /* GPIOA, GPIOB, GPIOC and AFIO clocks enable */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_GPIOC | RCC_APB2_PERIPH_GPIOD | RCC_APB2_PERIPH_AFIO, ENABLE);
}

/**
 * @brief  Configure the GPIOD Pins.
 */
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    /* GPIOA Configuration: PA0(TIM2 CH1) as alternate function push-pull */
    GPIO_InitStructure.Pin        = GPIO_PIN_0;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* GPIOC Configuration: PC6(TIM3 CH1) as alternate function push-pull */
    GPIO_InitStructure.Pin = GPIO_PIN_6;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_ConfigPinRemap(GPIO_ALL_RMP_TIM3,ENABLE);

    /* GPIOD Configuration: PD12(TIM4 CH1) as alternate function push-pull */
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
