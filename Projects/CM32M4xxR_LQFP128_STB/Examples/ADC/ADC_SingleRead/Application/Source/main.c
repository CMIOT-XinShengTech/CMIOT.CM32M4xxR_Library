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
 * @version v1.0.0
 *
 * @COPYRIGHT(c) 2020, China Mobile IOT. All rights reserved.
 */
#include "main.h"

/** @addtogroup ADC_ADC1_DMA
 * @{
 */

ADC_InitType ADC_InitStructure;
DMA_InitType DMA_InitStructure;
__IO uint16_t ADC1ConvertedValue[5],ADC2ConvertedValue[5],ADC3ConvertedValue[5],ADC4ConvertedValue[5];

void RCC_Configuration(void);
void GPIO_Configuration(void);
void ADC_Initial(ADC_Module* ADCx);
uint16_t ADC_GetData(ADC_Module* ADCx, uint8_t ADC_Channel);

void ADC_Initial(ADC_Module* ADCx)
{
	/* ADC configuration ------------------------------------------------------*/
	ADC_InitStructure.WorkMode       = ADC_WORKMODE_INDEPENDENT;
	ADC_InitStructure.MultiChEn      = DISABLE;
	ADC_InitStructure.ContinueConvEn = DISABLE;
	ADC_InitStructure.ExtTrigSelect  = ADC_EXT_TRIGCONV_NONE;
	ADC_InitStructure.DatAlign       = ADC_DAT_ALIGN_R;
	ADC_InitStructure.ChsNumber      = 1;
	ADC_Init(ADCx, &ADC_InitStructure);


	/* Enable ADC */
	ADC_Enable(ADCx, ENABLE);
	/*Check ADC Ready*/
	while(ADC_GetFlagStatusReady(ADCx,ADC_FLAG_RDY) == RESET)
	;
	/* Start ADC calibration */
	ADC_StartCalibration(ADCx);
	/* Check the end of ADC calibration */
	while (ADC_GetCalibrationStatus(ADCx))
	;
}
/**
* @brief   Main program
*/
int main(void)
{
	/* System clocks configuration ---------------------------------------------*/
	RCC_Configuration();

	/* GPIO configuration ------------------------------------------------------*/
	GPIO_Configuration();

	ADC_Initial(ADC1);
	ADC_Initial(ADC2);
	ADC_Initial(ADC3);
	ADC_Initial(ADC4);

	while (1)
	{
		ADC1ConvertedValue[0]=ADC_GetData(ADC1,ADC1_Channel_06_PC0);
		ADC1ConvertedValue[1]=ADC_GetData(ADC1,ADC1_Channel_07_PC1);

		ADC2ConvertedValue[0]=ADC_GetData(ADC2,ADC2_Channel_08_PC2);
		ADC2ConvertedValue[1]=ADC_GetData(ADC2,ADC2_Channel_09_PC3);

		ADC3ConvertedValue[0]=ADC_GetData(ADC3,ADC3_Channel_07_PD10);
		ADC3ConvertedValue[1]=ADC_GetData(ADC3,ADC3_Channel_08_PD11);

		ADC4ConvertedValue[0]=ADC_GetData(ADC4,ADC4_Channel_09_PD12);
		ADC4ConvertedValue[1]=ADC_GetData(ADC4,ADC4_Channel_10_PD13);
	}
}

/**
* @brief  Configures the different system clocks.
*/
void RCC_Configuration(void)
{
	/* Enable peripheral clocks ------------------------------------------------*/

	/* Enable GPIOC and GPIOD clocks */
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC | RCC_APB2_PERIPH_GPIOD, ENABLE);

	/* Enable ADC1, ADC2, ADC3 and ADC4 clocks */
	RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_ADC1 | RCC_AHB_PERIPH_ADC2 | RCC_AHB_PERIPH_ADC3 | RCC_AHB_PERIPH_ADC4, ENABLE);

	/* RCC_ADCHCLK_DIV16*/
	ADC_ConfigClk(ADC1,ADC_CTRL3_CKMOD_AHB,RCC_ADCHCLK_DIV16);
	ADC_ConfigClk(ADC2,ADC_CTRL3_CKMOD_AHB,RCC_ADCHCLK_DIV16);
	ADC_ConfigClk(ADC3,ADC_CTRL3_CKMOD_AHB,RCC_ADCHCLK_DIV16);
	ADC_ConfigClk(ADC4,ADC_CTRL3_CKMOD_AHB,RCC_ADCHCLK_DIV16);

    RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSI, RCC_ADC1MCLK_DIV8);
}

/**
* @brief  Configures the different GPIO ports.
*/
void GPIO_Configuration(void)
{
	GPIO_InitType GPIO_InitStructure;

	/* Configure PC0 PC1 as analog input -------------------------*/
	GPIO_InitStructure.Pin       = GPIO_PIN_0 | GPIO_PIN_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	/* Configure PC2 PC3 as analog input -------------------------*/
	GPIO_InitStructure.Pin       = GPIO_PIN_2 | GPIO_PIN_3;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	/* Configure PD10 PD11 as analog input -------------------------*/
	GPIO_InitStructure.Pin       = GPIO_PIN_10 | GPIO_PIN_11;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	/* Configure PD12 PD13 as analog input -------------------------*/
	GPIO_InitStructure.Pin       = GPIO_PIN_12 | GPIO_PIN_13;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}

uint16_t ADC_GetData(ADC_Module* ADCx, uint8_t ADC_Channel)
{
	uint16_t dat;

	ADC_ConfigRegularChannel(ADCx, ADC_Channel, 1, ADC_SAMP_TIME_239CYCLES5);
	/* Start ADC Software Conversion */
	ADC_EnableSoftwareStartConv(ADCx, ENABLE);
	while(ADC_GetFlagStatus(ADCx, ADC_FLAG_ENDC)==0){
	}
	ADC_ClearFlag(ADCx, ADC_FLAG_ENDC);
	ADC_ClearFlag(ADCx, ADC_FLAG_STR);
	dat=ADC_GetDat(ADCx);
	return dat;
}


/**
 * @}
 */

/**
 * @}
 */
