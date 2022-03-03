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

/** @addtogroup ADC_TIMTrigger_AutoInjection
 * @{
 */

ADC_InitType ADC_InitStructure;
DMA_InitType DMA_InitStructure;
TIM_TimeBaseInitType TIM_TimeBaseStructure;
TIM_OCInitType TIM_OCInitStructure;
__IO uint16_t ADC_RegularConvertedValueTab[32], ADC_InjectedConvertedValueTab[32];

void RCC_Configuration(void);
void GPIO_Configuration(void);
//void NVIC_Configuration(void);
void ECLIC_Configuration(void);

/**
 * @brief   Main program
 */
int main(void)
{
    /* System clocks configuration ---------------------------------------------*/
    RCC_Configuration();

    /* NVIC configuration ------------------------------------------------------*/
    //NVIC_Configuration();

    /* ECLIC configuration ------------------------------------------------------*/
    ECLIC_Configuration();

    /* GPIO configuration ------------------------------------------------------*/
    GPIO_Configuration();

    /* TIM1 configuration ------------------------------------------------------*/
    /* Time Base configuration */
    TIM_InitTimBaseStruct(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.Period    = 0x8FF; // 0xFF;
    TIM_TimeBaseStructure.Prescaler = 0x4;
    TIM_TimeBaseStructure.ClkDiv    = 0x0;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
    TIM_InitTimeBase(TIM1, &TIM_TimeBaseStructure);
    /* TIM1 channel1 configuration in PWM mode */
    TIM_OCInitStructure.OcMode      = TIM_OCMODE_PWM1;
    TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.Pulse       = 0x7F;
    TIM_OCInitStructure.OcPolarity  = TIM_OC_POLARITY_LOW;
    TIM_InitOc1(TIM1, &TIM_OCInitStructure);
    TIM_InitOc2(TIM1, &TIM_OCInitStructure);
    TIM_InitOc4(TIM1, &TIM_OCInitStructure);

    /* DMA1 Channel1 Configuration ----------------------------------------------*/
    DMA_DeInit(DMA1_CH1);
    DMA_InitStructure.PeriphAddr     = (uint32_t)&ADC1->DAT;
    DMA_InitStructure.MemAddr        = (uint32_t)ADC_RegularConvertedValueTab;
    DMA_InitStructure.Direction      = DMA_DIR_PERIPH_SRC;
    DMA_InitStructure.BufSize        = 32;
    DMA_InitStructure.PeriphInc      = DMA_PERIPH_INC_DISABLE;
    DMA_InitStructure.DMA_MemoryInc  = DMA_MEM_INC_ENABLE;
    DMA_InitStructure.PeriphDataSize = DMA_PERIPH_DATA_SIZE_HALFWORD;
    DMA_InitStructure.MemDataSize    = DMA_MEMORY_DATA_SIZE_HALFWORD;
    DMA_InitStructure.CircularMode   = DMA_MODE_CIRCULAR;
    DMA_InitStructure.Priority       = DMA_PRIORITY_HIGH;
    DMA_InitStructure.Mem2Mem        = DMA_M2M_DISABLE;
    DMA_Init(DMA1_CH1, &DMA_InitStructure);
    /* Enable DMA1 channel1 */
    DMA_EnableChannel(DMA1_CH1, ENABLE);

    /* ADC1 configuration ------------------------------------------------------*/
    ADC_InitStructure.WorkMode       = ADC_WORKMODE_INDEPENDENT;
    ADC_InitStructure.MultiChEn      = DISABLE;
    ADC_InitStructure.ContinueConvEn = DISABLE;
    ADC_InitStructure.ExtTrigSelect  = ADC_EXT_TRIGCONV_T1_CC2;
    ADC_InitStructure.DatAlign       = ADC_DAT_ALIGN_R;
    ADC_InitStructure.ChsNumber      = 1;
    ADC_Init(ADC1, &ADC_InitStructure);

    /* Set injected sequencer length */
    ADC_ConfigInjectedSequencerLength(ADC1, 1);
    /* ADC1 injected channel Configuration */
    ADC_ConfigInjectedChannel(ADC1, ADC1_Channel_09_PC3, 1, ADC_SAMP_TIME_71CYCLES5);
    /* ADC1 injected external trigger configuration */
    ADC_ConfigExternalTrigInjectedConv(ADC1, ADC_EXT_TRIG_INJ_CONV_NONE);
    /* Enable automatic injected conversion start after regular one */
    ADC_EnableAutoInjectedConv(ADC1, ENABLE);
    /* Enable JEOC interrupt */
    ADC_ConfigInt(ADC1, ADC_INT_JENDC, ENABLE);

    /* ADC1 regular channel14 configuration */
    ADC_ConfigRegularChannel(ADC1, ADC1_Channel_08_PC2, 1, ADC_SAMP_TIME_13CYCLES5);
    /* Enable ADC1 DMA */
    ADC_EnableDMA(ADC1, ENABLE);
    /* Enable ADC1 external trigger */
    ADC_EnableExternalTrigConv(ADC1, ENABLE);
    __enable_irq();
    /* Enable ADC1 */
    ADC_Enable(ADC1, ENABLE);
    /*Check ADC Ready*/
    while(ADC_GetFlagStatusReady(ADC1,ADC_FLAG_RDY) == RESET)
        ;
    /* Start ADC1 calibration */
    ADC_StartCalibration(ADC1);
    /* Check the end of ADC1 calibration */
    while (ADC_GetCalibrationStatus(ADC1))
        ;

    /* TIM1 counter enable */
    TIM_Enable(TIM1, ENABLE);
    /* TIM1 main Output Enable */
    TIM_EnableCtrlPwmOutputs(TIM1, ENABLE);

#if 0
    /* Test on channel1 transfer complete flag */
    while(!DMA_GetFlagStatus(DMA1_FLAG_TC1,DMA1));
    /* Clear channel1 transfer complete flag */
    DMA_ClearFlag(DMA1_FLAG_TC1,DMA1);
    /* TIM1 counter disable */
    TIM_Enable(TIM1, DISABLE);
#endif

    while (1)
    {
    }
}

/**
 * @brief  Configures the different system clocks.
 */
void RCC_Configuration(void)
{
    /* Enable peripheral clocks ------------------------------------------------*/
    /* Enable TIM1 clocks */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_TIM1, ENABLE);
    /* Enable DMA1 and DMA2 clocks */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_DMA1 | RCC_AHB_PERIPH_DMA2, ENABLE);

    /* Enable GPIOC clocks */
    RCC_EnableAPB2PeriphClk(
        RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_GPIOC | RCC_APB2_PERIPH_GPIOE, ENABLE);
    /* Enable ADC1, ADC2, ADC3 and ADC4 clocks */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_ADC1 | RCC_AHB_PERIPH_ADC2 | RCC_AHB_PERIPH_ADC3 | RCC_AHB_PERIPH_ADC4,
                           ENABLE);

    /* RCC_ADCHCLK_DIV16*/
    ADC_ConfigClk(ADC1,ADC_CTRL3_CKMOD_AHB,RCC_ADCHCLK_DIV16);
    ADC_ConfigClk(ADC2,ADC_CTRL3_CKMOD_AHB,RCC_ADCHCLK_DIV16);
    ADC_ConfigClk(ADC3,ADC_CTRL3_CKMOD_AHB,RCC_ADCHCLK_DIV16);
    ADC_ConfigClk(ADC4,ADC_CTRL3_CKMOD_AHB,RCC_ADCHCLK_DIV16);
}

/**
 * @brief  Configures the different GPIO ports.
 */
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    /* Configure TIM1_CH1 (PA8),CH4(PA11) as alternate function push-pull */
    GPIO_InitStructure.Pin        = GPIO_PIN_8 | GPIO_PIN_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Configure PC.06 as output push-pull */
    GPIO_InitStructure.Pin       = GPIO_PIN_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    /* Configure PC.02 and PC.03 as analog input */
    GPIO_InitStructure.Pin       = GPIO_PIN_2 | GPIO_PIN_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/**
 * @brief  Configures the enhanced core local interrupt controller.
 */
void ECLIC_Configuration(void)
{
    /* Configure the ECLIC level and priority Bits */
	ECLIC_SetCfgNlbits(0); /* 0 bits for level, 4 bits for priority */

    /* Enable the USARTy Interrupt */
	ECLIC_SetPriorityIRQ(ADC1_2_IRQn, 1);
	ECLIC_SetTrigIRQ(ADC1_2_IRQn, ECLIC_POSTIVE_EDGE_TRIGGER);
	ECLIC_EnableIRQ(ADC1_2_IRQn);

}

/**
 * @}
 */

/**
 * @}
 */
