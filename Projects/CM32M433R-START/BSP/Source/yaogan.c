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
 * @file yaogan.c
 * @author CMIOT
 * @version v1.0.1
 *
 * @COPYRIGHT(c) 2020, China Mobile IOT. All rights reserved.
 */

#include "nuclei_sdk_soc.h"
#include "log.h"

__IO uint16_t ADC_yaogan_ValueTab[2];
void yaogan_init(void)
{
	ADC_InitType ADC_InitStructure;
	DMA_InitType DMA_InitStructure;
	TIM_TimeBaseInitType TIM_TimeBaseStructure;
	TIM_OCInitType TIM_OCInitStructure;
    /* System clocks configuration ---------------------------------------------*/
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_TIM8, ENABLE);
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_ADC4, ENABLE);
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_DMA2, ENABLE);
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOD, ENABLE);

    ADC_ConfigClk(ADC4,ADC_CTRL3_CKMOD_AHB,RCC_ADCHCLK_DIV16);
    RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSE, RCC_ADC1MCLK_DIV8);

    /* ECLIC configuration ------------------------------------------------------*/
	ECLIC_SetCfgNlbits(0); /* 0 bits for level, 4 bits for priority */

    /* Enable the USARTy Interrupt */
	ECLIC_SetPriorityIRQ(ADC3_4_IRQn, 1);
	ECLIC_SetTrigIRQ(ADC3_4_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
	ECLIC_EnableIRQ(ADC3_4_IRQn);

    /* GPIO configuration ------------------------------------------------------*/

    /* Configure PC.02 and PC.03 as analog input */
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStructure.Pin       = GPIO_PIN_10 | GPIO_PIN_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    /* TIM1 configuration ------------------------------------------------------*/
    /* Time Base configuration */
    TIM_InitTimBaseStruct(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.Period    = 0xFFFF; // 0xFF;
    TIM_TimeBaseStructure.Prescaler = 0xFF;
    TIM_TimeBaseStructure.ClkDiv    = 0x0;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
    TIM_InitTimeBase(TIM8, &TIM_TimeBaseStructure);
    /* TIM1 channel1 configuration in PWM mode */
    TIM_InitOcStruct(&TIM_OCInitStructure);
    TIM_OCInitStructure.OcMode      = TIM_OCMODE_PWM1;
    TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.Pulse       = 0x7F;
    TIM_OCInitStructure.OcPolarity  = TIM_OC_POLARITY_LOW;
    TIM_InitOc1(TIM8, &TIM_OCInitStructure);
    TIM_InitOc2(TIM8, &TIM_OCInitStructure);
    TIM_InitOc4(TIM8, &TIM_OCInitStructure);

    /* DMA1 Channel1 Configuration ----------------------------------------------*/
    DMA_DeInit(DMA2_CH8);
    DMA_InitStructure.PeriphAddr     = (uint32_t)&ADC4->DAT;
    DMA_InitStructure.MemAddr        = (uint32_t)ADC_yaogan_ValueTab;
    DMA_InitStructure.Direction      = DMA_DIR_PERIPH_SRC;
    DMA_InitStructure.BufSize        = 2;
    DMA_InitStructure.PeriphInc      = DMA_PERIPH_INC_DISABLE;
    DMA_InitStructure.DMA_MemoryInc  = DMA_MEM_INC_ENABLE;
    DMA_InitStructure.PeriphDataSize = DMA_PERIPH_DATA_SIZE_HALFWORD;
    DMA_InitStructure.MemDataSize    = DMA_MEMORY_DATA_SIZE_HALFWORD;
    DMA_InitStructure.CircularMode   = DMA_MODE_CIRCULAR;
    DMA_InitStructure.Priority       = DMA_PRIORITY_HIGH;
    DMA_InitStructure.Mem2Mem        = DMA_M2M_DISABLE;
    DMA_Init(DMA2_CH8, &DMA_InitStructure);
    /* Enable DMA1 channel1 */
    DMA_EnableChannel(DMA2_CH8, ENABLE);

    /* ADC1 configuration ------------------------------------------------------*/
    ADC_InitStructure.WorkMode       = ADC_WORKMODE_INDEPENDENT;
    ADC_InitStructure.MultiChEn      = ENABLE;
    ADC_InitStructure.ContinueConvEn = DISABLE;
    ADC_InitStructure.ExtTrigSelect  = ADC_EXT_TRIGCONV_T8_CC1;
    ADC_InitStructure.DatAlign       = ADC_DAT_ALIGN_R;
    ADC_InitStructure.ChsNumber      = 2;
    ADC_Init(ADC4, &ADC_InitStructure);

    /* Enable JEOC interrupt */
    ADC_ConfigInt(ADC4, ADC_INT_ENDC, ENABLE);

    /* ADC1 regular channel14 configuration */
    ADC_ConfigRegularChannel(ADC4, ADC4_Channel_07_PD10, 1, ADC_SAMP_TIME_13CYCLES5);
    ADC_ConfigRegularChannel(ADC4, ADC4_Channel_08_PD11, 2, ADC_SAMP_TIME_13CYCLES5);
    ADC_EnableDMA(ADC4, ENABLE);
    /* Enable ADC1 external trigger */
    ADC_EnableExternalTrigConv(ADC4, ENABLE);
    __enable_irq();
    /* Enable ADC1 */
    ADC_Enable(ADC4, ENABLE);
    /*Check ADC Ready*/
    while(ADC_GetFlagStatusReady(ADC4,ADC_FLAG_RDY) == RESET)
        ;
    /* Start ADC1 calibration */
    ADC_StartCalibration(ADC4);
    /* Check the end of ADC1 calibration */
    while (ADC_GetCalibrationStatus(ADC4))
        ;

    /* TIM1 counter enable */
    TIM_Enable(TIM8, ENABLE);
    /* TIM1 main Output Enable */
    TIM_EnableCtrlPwmOutputs(TIM8, ENABLE);

}

