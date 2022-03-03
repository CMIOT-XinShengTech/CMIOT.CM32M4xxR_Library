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

/** @addtogroup ADC_ExtLinesTrigger
 * @{
 */

ADC_InitType ADC_InitStructure;
DMA_InitType DMA_InitStructure;
__IO uint16_t ADC_RegularConvertedValueTab[64] = {0};
__IO uint16_t ADC_InjectedConvertedValueTab[32] = {0};
uint32_t gCnt = 0;

void RCC_Configuration(void);
void GPIO_Configuration(void);
void ECLIC_Configuration(void);
void EXTI_Configuration(void);

/**
 * @brief   Main program
 */
int main(void)
{
    /* System clocks configuration ---------------------------------------------*/
    RCC_Configuration();

    /* ECLIC configuration ------------------------------------------------------*/
    ECLIC_Configuration();

    /* GPIO configuration ------------------------------------------------------*/
    GPIO_Configuration();

    /* EXTI configuration ------------------------------------------------------*/
    EXTI_Configuration();

    /* DMA1 channel1 configuration ----------------------------------------------*/
    DMA_DeInit(DMA1_CH1);
    DMA_InitStructure.PeriphAddr     = (uint32_t)&ADC1->DAT;
    DMA_InitStructure.MemAddr        = (uint32_t)ADC_RegularConvertedValueTab;
    DMA_InitStructure.Direction      = DMA_DIR_PERIPH_SRC;
    DMA_InitStructure.BufSize        = 64;
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
    ADC_InitStructure.MultiChEn      = ENABLE;
    ADC_InitStructure.ContinueConvEn = DISABLE;
    ADC_InitStructure.ExtTrigSelect  = ADC_EXT_TRIGCONV_EXT_INT11_TIM8_TRGO;
    ADC_InitStructure.DatAlign       = ADC_DAT_ALIGN_R;
    ADC_InitStructure.ChsNumber      = 2;
    ADC_Init(ADC1, &ADC_InitStructure);

    /* ADC1 regular channels configuration */
    ADC_ConfigRegularChannel(ADC1, ADC1_Channel_08_PC2, 1, ADC_SAMP_TIME_28CYCLES5);
    ADC_ConfigRegularChannel(ADC1, ADC1_Channel_09_PC3, 2, ADC_SAMP_TIME_28CYCLES5);

    /* Regular discontinuous mode channel number configuration */
    ADC_ConfigDiscModeChannelCount(ADC1, 1);
    /* Enable regular discontinuous mode */
    ADC_EnableRegularDiscMode(ADC1, ENABLE);

    /* Enable ADC1 external trigger conversion */
    ADC_EnableExternalTrigConv(ADC1, ENABLE);

    /* Set injected sequencer length */
    ADC_ConfigInjectedSequencerLength(ADC1, 2);
    /* ADC1 injected channel configuration */
    ADC_ConfigInjectedChannel(ADC1, ADC1_Channel_03_PA6, 1, ADC_SAMP_TIME_28CYCLES5);
    ADC_ConfigInjectedChannel(ADC1, ADC1_Channel_04_PA3, 2, ADC_SAMP_TIME_28CYCLES5);
    /* ADC1 injected external trigger configuration */
    ADC_ConfigExternalTrigInjectedConv(ADC1, ADC_EXT_TRIG_INJ_CONV_EXT_INT15_TIM8_CC4);
    /* Enable ADC1 injected external trigger conversion */
    ADC_EnableExternalTrigInjectedConv(ADC1, ENABLE);

    /* Enable JEOC interrupt */
    ADC_ConfigInt(ADC1, ADC_INT_JENDC, ENABLE);

    /* Enable ADC1 DMA */
    ADC_EnableDMA(ADC1, ENABLE);

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

    while (1)
    {
        gCnt++;
    }
}

/**
 * @brief  Configures the different system clocks.
 */
void RCC_Configuration(void)
{
    /* Enable peripheral clocks ------------------------------------------------*/
    /* Enable DMA1 and DMA2 clocks */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_DMA1 | RCC_AHB_PERIPH_DMA2, ENABLE);

    /* Enable GPIOC clocks */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_GPIOC
                                | RCC_APB2_PERIPH_GPIOE | RCC_APB2_PERIPH_AFIO,
                            ENABLE);
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
 * @brief  Configures the different EXTI lines.
 */
void EXTI_Configuration(void)
{
    EXTI_InitType EXTI_InitStructure;

    GPIO_ConfigEXTILine(GPIOE_PORT_SOURCE, GPIO_PIN_SOURCE11);
    /* EXTI line11 configuration -----------------------------------------------*/
    EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Event;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_Line    = EXTI_LINE11;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    /* Select the EXTI Line15 the GPIO pin source */
    GPIO_ConfigEXTILine(GPIOB_PORT_SOURCE, GPIO_PIN_SOURCE15);
    /* EXTI line15 configuration -----------------------------------------------*/
    EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Event;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_Line    = EXTI_LINE15;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
}

/**
 * @brief  Configures the different GPIO ports.
 */
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    /* Configure PC.02 and PC.03  as analog input ------------------------------*/
    GPIO_InitStructure.Pin       = GPIO_PIN_2 | GPIO_PIN_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    /* Configure PA.00 and PA.01 as analog input --------------------------*/
    GPIO_InitStructure.Pin       = GPIO_PIN_6 | GPIO_PIN_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Configure EXTI line11 ---------------------------------------------------*/
    GPIO_InitStructure.Pin       = GPIO_PIN_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    /* Configure EXTI line15 ---------------------------------------------------*/
    GPIO_InitStructure.Pin       = GPIO_PIN_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
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
