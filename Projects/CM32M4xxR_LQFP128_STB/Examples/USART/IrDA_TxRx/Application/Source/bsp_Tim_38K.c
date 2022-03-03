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

#include "bsp_Tim_38K.h"

void ADVANCE_TIM_GPIO_Config(void)
{
    GPIO_InitType GPIO_InitStructure;

    /* Enable GPIO clock */
    RCC_EnableAPB2PeriphClk(ADVANCE_TIM_CH1_GPIO_CLK, ENABLE);

    /* Configure PE9 as Out_PP */
    GPIO_InitStructure.Pin        = ADVANCE_TIM_CH1_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(ADVANCE_TIM_CH1_PORT, &GPIO_InitStructure);

    GPIO_ConfigPinRemap(ADVANCE_TIM_CH1_GPIO_RMP, ENABLE);
}

static void ADVANCE_TIM_Mode_Config(void)
{
    TIM_TimeBaseInitType TIM_TimeBaseStructure;
    TIM_OCInitType TIM_OCInitStructure;

    ADVANCE_TIM_APBxClock_FUN(ADVANCE_TIM_CLK, ENABLE);

    /* Time base configuration */
    TIM_TimeBaseStructure.Period    = ADVANCE_TIM_Period;
    TIM_TimeBaseStructure.Prescaler = ADVANCE_TIM_Prescaler;
    TIM_TimeBaseStructure.ClkDiv    = TIM_CLK_DIV1;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
    TIM_TimeBaseStructure.RepetCnt  = 0;
    TIM_InitTimeBase(ADVANCE_TIM, &TIM_TimeBaseStructure);

    /* PWM1 Mode configuration: Channel1 */
    TIM_OCInitStructure.OcMode       = TIM_OCMODE_PWM1;
    TIM_OCInitStructure.OutputState  = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.OutputNState = TIM_OUTPUT_NSTATE_DISABLE;
    TIM_OCInitStructure.Pulse        = ADVANCE_TIM_Pulse;
    TIM_OCInitStructure.OcPolarity   = TIM_OC_POLARITY_HIGH;
    TIM_OCInitStructure.OcIdleState  = TIM_OC_IDLE_STATE_SET;
    TIM_OCInitStructure.OcNIdleState = TIM_OCN_IDLE_STATE_SET;
    TIM_OCInitStructure.OcNPolarity   = TIM_OCN_POLARITY_HIGH;
    TIM_InitOc1(ADVANCE_TIM, &TIM_OCInitStructure);

    TIM_ConfigOc1Preload(ADVANCE_TIM, TIM_OC_PRE_LOAD_ENABLE);

    /* TIM counter enable */
    TIM_Enable(ADVANCE_TIM, ENABLE);

    /* TIM Main Output Enable */
    TIM_EnableCtrlPwmOutputs(ADVANCE_TIM, ENABLE);
}

void ADVANCE_TIM_Init(void)
{
    ADVANCE_TIM_GPIO_Config();
    ADVANCE_TIM_Mode_Config();
}

