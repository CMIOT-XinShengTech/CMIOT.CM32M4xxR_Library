/*
  ******************************************************************************
  *
  * COPYRIGHT(c) 2020, China Mobile IOT
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of China Mobile IOT nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
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
  ******************************************************************************
  */ 

/**
 * @file main.c
 * @author CMIOT
 * @version v1.0.1
 *
 * @COPYRIGHT(c) 2020, China Mobile IOT. All rights reserved.
 */
#include "main.h"

/** @addtogroup DAC_TwoChannels_TriangleWave
 * @{
 */

void GPIO_Configuration(void);
void TIM5_Init(void);
void DAC_ChannelsConfig(void);

/**
 * @brief   Main program.
 */
int main(void)
{
    /* Once the DAC channel is enabled, the corresponding GPIO pin is automatically
       connected to the DAC converter. In order to avoid parasitic consumption,
       the GPIO pin should be configured in analog */
    GPIO_Configuration();
    TIM5_Init();
    DAC_ChannelsConfig();
    /* TIM2 enable counter */
    TIM_Enable(TIM5, ENABLE);

    while (1)
    {
    }
}

/**
 * @brief  Configures the different system clocks.
 */

/**
 * @brief  TIM5 Init.
 */
void TIM5_Init(void)
{
    TIM_TimeBaseInitType TIM_TimeBaseStructure;
    /* TIM5 Periph clock enable */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM5, ENABLE);
    /* TIM5 Configuration */
    TIM_InitTimBaseStruct(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.Period    = 0xF;
    TIM_TimeBaseStructure.Prescaler = 0xF;
    TIM_TimeBaseStructure.ClkDiv    = 0x0;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
    TIM_InitTimeBase(TIM5, &TIM_TimeBaseStructure);

    /* TIM5 TRGO selection */
    TIM_SelectOutputTrig(TIM5, TIM_TRGO_SRC_UPDATE);
}
/**
 * @brief  DAC channel1 Configuration.
 */
void DAC_ChannelsConfig(void)
{
    DAC_InitType DAC_InitStructure;

    /* DAC Periph clock enable */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_DAC, ENABLE);
    /* DAC channel1 Configuration */
    DAC_InitStructure.Trigger          = DAC_TRG_T5_TRGO;
    DAC_InitStructure.WaveGen          = DAC_WAVEGEN_TRIANGLE;
    DAC_InitStructure.LfsrUnMaskTriAmp = DAC_TRIAMP_2047;
    DAC_InitStructure.BufferOutput     = DAC_BUFFOUTPUT_DISABLE;
    DAC_Init(DAC_CHANNEL_1, &DAC_InitStructure);

    /* DAC channel2 Configuration */
    DAC_InitStructure.LfsrUnMaskTriAmp = DAC_TRIAMP_1023;
    DAC_Init(DAC_CHANNEL_2, &DAC_InitStructure);

    /* Enable DAC Channel1: Once the DAC channel1 is enabled, PA.04 is
             automatically connected to the DAC converter. */
    DAC_Enable(DAC_CHANNEL_1, ENABLE);

    /* Enable DAC Channel2: Once the DAC channel2 is enabled, PA.05 is
             automatically connected to the DAC converter. */
    DAC_Enable(DAC_CHANNEL_2, ENABLE);

    /* Set DAC dual channel DR12DCH register */
    DAC_SetDualChData(DAC_ALIGN_R_12BIT, 0x100, 0x100);
}
/**
 * @brief  Configures the different GPIO ports.
 */
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;
    /* GPIOA Periph clock enable */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
    /* Once the DAC channel is enabled, the corresponding GPIO pin is automatically
       connected to the DAC converter. In order to avoid parasitic consumption,
       the GPIO pin should be configured in analog */
    GPIO_InitStructure.Pin       = GPIO_PIN_4 | GPIO_PIN_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}
