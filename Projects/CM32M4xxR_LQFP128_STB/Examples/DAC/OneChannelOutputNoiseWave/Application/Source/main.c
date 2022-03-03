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

/** @addtogroup DAC_OneChanneloutputNoiseWave
 * @{
 */

void GPIO_Configuration(void);
void DAC_Channel1Config(void);

/**
 * @brief   Main program.
 */
int main(void)
{
    /* Once the DAC channel is enabled, the corresponding GPIO pin is automatically
       connected to the DAC converter. In order to avoid parasitic consumption,
       the GPIO pin should be configured in analog */
    GPIO_Configuration();
    DAC_Channel1Config();

    while (1)
    {
        /* Start DAC Channel1 conversion by software */
        DAC_SoftTrgEnable(DAC_CHANNEL_1, ENABLE);
    }
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
    GPIO_InitStructure.Pin       = GPIO_PIN_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/**
 * @brief  Configures the different GPIO ports.
 */
void DAC_Channel1Config(void)
{
    DAC_InitType DAC_InitStructure;

    /* DAC Periph clock enable */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_DAC, ENABLE);
    /* DAC channel1 Configuration */
    DAC_InitStructure.Trigger          = DAC_TRG_SOFTWARE;
    DAC_InitStructure.WaveGen          = DAC_WAVEGEN_NOISE;
    DAC_InitStructure.LfsrUnMaskTriAmp = DAC_UNMASK_LFSRBITS11_0;
    DAC_InitStructure.BufferOutput     = DAC_BUFFOUTPUT_ENABLE;
    DAC_Init(DAC_CHANNEL_1, &DAC_InitStructure);

    /* Enable DAC Channel1: Once the DAC channel1 is enabled, PA.04 is
       automatically connected to the DAC converter. */
    DAC_Enable(DAC_CHANNEL_1, ENABLE);

    /* Set DAC Channel1 DHR12L register */
    DAC_SetCh1Data(DAC_ALIGN_R_12BIT, 4094);
}
