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

/** @addtogroup DAC_DualModeDMA_SineWave
 * @{
 */

#define DAC_DHR12RD_Address 0x40007420

/* Init Structure definition */
DAC_InitType DAC_InitStructure;
uint32_t Idx = 0;

const uint16_t Sine12bit[32] = {2047, 2447, 2831, 3185, 3498, 3750, 3939, 4056, 4095, 4056, 3939,
                                3750, 3495, 3185, 2831, 2447, 2047, 1647, 1263, 909,  599,  344,
                                155,  38,   0,    38,   155,  344,  599,  909,  1263, 1647};

uint32_t DualSine12bit[32];

void RCC_Configuration(void);
void GPIO_Configuration(void);
void TIM4_TrgoInit(void);
void DAC_SineWaveInit(void);
void DMA_Config(void);

/**
 * @brief   Main program.
 */
int main(void)
{
    /* Once the DAC channel is enabled, the corresponding GPIO pin is automatically
       connected to the DAC converter. In order to avoid parasitic consumption,
       the GPIO pin should be configured in analog */
    GPIO_Configuration();
    /* TIM4Init */
    TIM4_TrgoInit();
    /* DAC SineWave Config */
    DAC_SineWaveInit();

    /* Fill Sine32bit table */
    for (Idx = 0; Idx < 32; Idx++)
    {
        DualSine12bit[Idx] = (Sine12bit[Idx] << 16) + (Sine12bit[Idx]);
    }
    /* DMA Config */
    DMA_Config();

    /* Enable DAC Channel1: Once the DAC channel1 is enabled, PA.04 is
       automatically connected to the DAC converter. */
    DAC_Enable(DAC_CHANNEL_1, ENABLE);
    /* Enable DAC Channel2: Once the DAC channel2 is enabled, PA.05 is
       automatically connected to the DAC converter. */
    DAC_Enable(DAC_CHANNEL_2, ENABLE);

    /* Enable DMA for DAC Channel2 */
    DAC_DmaEnable(DAC_CHANNEL_2, ENABLE);

    /* TIM2 enable counter */
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
    /* DAC Periph clock enable */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_DAC, ENABLE);
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
/**
 * @brief  TIM4 Init.
 */
void TIM4_TrgoInit(void)
{
    TIM_TimeBaseInitType TIM_TimeBaseStructure;

    /* TIM4 Periph clock enable */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM4, ENABLE); // RCC_APB2_PERIPH_TIM8
    /* TIM4 Configuration */
    /* Time base configuration */
    TIM_InitTimBaseStruct(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.Period    = 13; 
    TIM_TimeBaseStructure.Prescaler = 0x0;
    TIM_TimeBaseStructure.ClkDiv    = 0x0;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
    TIM_InitTimeBase(TIM4, &TIM_TimeBaseStructure);

    /* TIM4 TRGO selection */
    TIM_SelectOutputTrig(TIM4, TIM_TRGO_SRC_UPDATE);
}
/**
 * @brief  DAC SineWave Config.
 */
void DAC_SineWaveInit(void)
{
    /* DAC Periph clock enable */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_DAC, ENABLE);

    /* DAC channel1 Configuration */
    DAC_InitStructure.Trigger      = DAC_TRG_T4_TRGO;
    DAC_InitStructure.WaveGen      = DAC_WAVEGEN_NONE;
    DAC_InitStructure.BufferOutput = DAC_BUFFOUTPUT_DISABLE;
    DAC_InitStructure.LfsrUnMaskTriAmp = DAC_UNMASK_LFSRBIT0;
    DAC_Init(DAC_CHANNEL_1, &DAC_InitStructure);

    /* DAC channel2 Configuration */
    DAC_Init(DAC_CHANNEL_2, &DAC_InitStructure);
}
/**
 * @brief  DMA Config.
 */
void DMA_Config(void)
{
    DMA_InitType DMA_InitStructure;

    /* DMA2 clock enable */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_DMA2, ENABLE);
    DMA_DeInit(DMA2_CH4);
    DMA_InitStructure.PeriphAddr     = DAC_DHR12RD_Address;
    DMA_InitStructure.MemAddr        = (uint32_t)&DualSine12bit;
    DMA_InitStructure.Direction      = DMA_DIR_PERIPH_DST;
    DMA_InitStructure.BufSize        = 32;
    DMA_InitStructure.PeriphInc      = DMA_PERIPH_INC_DISABLE;
    DMA_InitStructure.DMA_MemoryInc  = DMA_MEM_INC_ENABLE;
    DMA_InitStructure.PeriphDataSize = DMA_PERIPH_DATA_SIZE_WORD;
    DMA_InitStructure.MemDataSize    = DMA_MEMORY_DATA_SIZE_WORD;
    DMA_InitStructure.CircularMode   = DMA_MODE_CIRCULAR;
    DMA_InitStructure.Priority       = DMA_PRIORITY_HIGH;
    DMA_InitStructure.Mem2Mem        = DMA_M2M_DISABLE;
    DMA_Init(DMA2_CH4, &DMA_InitStructure);
    /* Enable DMA2 Channel4 */
    DMA_EnableChannel(DMA2_CH4, ENABLE);
}
