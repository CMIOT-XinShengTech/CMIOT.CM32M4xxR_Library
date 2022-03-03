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

/** @addtogroup ADC_AnalogWatchdog
 * @{
 */

ADC_InitType ADC_InitStructure;
uint32_t gCnt = 0;

void RCC_Configuration(void);
void GPIO_Configuration(void);
void ECLIC_Configuration(void);
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

    /* ADC1 Configuration ------------------------------------------------------*/
    ADC_InitStructure.WorkMode       = ADC_WORKMODE_INDEPENDENT;
    ADC_InitStructure.MultiChEn      = DISABLE;
    ADC_InitStructure.ContinueConvEn = ENABLE;
    ADC_InitStructure.ExtTrigSelect  = ADC_EXT_TRIGCONV_NONE;
    ADC_InitStructure.DatAlign       = ADC_DAT_ALIGN_R;
    ADC_InitStructure.ChsNumber      = 1;
    ADC_Init(ADC1, &ADC_InitStructure);

    /* ADC1 regular channel14 configuration */
    ADC_ConfigRegularChannel(ADC1, ADC1_Channel_08_PC2, 1, ADC_SAMP_TIME_13CYCLES5);

    /* Configure high and low analog watchdog thresholds */
    ADC_ConfigAnalogWatchdogThresholds(ADC1, 0x0B00, 0x0300);
    /* Configure channel8 as the single analog watchdog guarded channel */
    ADC_ConfigAnalogWatchdogSingleChannel(ADC1, ADC1_Channel_08_PC2);
    /* Enable analog watchdog on one regular channel */
    ADC_ConfigAnalogWatchdogWorkChannelType(ADC1, ADC_ANALOG_WTDG_SINGLEREG_ENABLE);

    /* Enable AWD interrupt */
    ADC_ConfigInt(ADC1, ADC_INT_AWD, ENABLE);

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

    /* Start ADC1 Software Conversion */
    ADC_EnableSoftwareStartConv(ADC1, ENABLE);

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

    /* Enable ADC1, ADC2, ADC3 and GPIOC clocks */
    // RCC_EnableAPB2PeriphClk(RCC_APB2Periph_ADC1 | RCC_APB2Periph_ADC2 | RCC_APB2_PERIPH_GPIOC, ENABLE);

    /* Enable GPIOC clocks */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);
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

    /* Configure PC.02 (ADC Channel8) as analog input -------------------------*/
    GPIO_InitStructure.Pin       = GPIO_PIN_2;
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
