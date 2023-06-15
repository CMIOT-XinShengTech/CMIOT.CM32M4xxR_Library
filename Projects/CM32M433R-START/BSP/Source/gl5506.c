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
 * @file gl5506.c
 * @author CMIOT Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */

#include "gl5506.h"

/**
 * @brief Configures gl5506 ADC sampling.
 */
GL5506_ErrorType gl5506_init(void)
{
    GPIO_InitType GPIO_InitStructure;
    ADC_InitType ADC_InitStructure;

    /* Enable the GPIO Clock */
    if (GL5506_ADC_PORT == GPIOA)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
    }
    else if (GL5506_ADC_PORT == GPIOB)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
    }
    else if (GL5506_ADC_PORT == GPIOC)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);
    }
    else if (GL5506_ADC_PORT == GPIOD)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOD, ENABLE);
    }
    else if (GL5506_ADC_PORT == GPIOE)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOE, ENABLE);
    }
    else if (GL5506_ADC_PORT == GPIOF)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOF, ENABLE);
    }
    else if (GL5506_ADC_PORT == GPIOG)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOG, ENABLE);
    }
    else
    {
    	return GL5506_ERROR_PARA;
    }

    /* Configure the GPIO pin */
    if (GL5506_ADC_PIN <= GPIO_PIN_ALL)
    {
        GPIO_InitStructure.Pin        = GL5506_ADC_PIN;
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN;
        GPIO_InitStructure.GPIO_Speed = GPIO_INPUT;
        GPIO_Init(GL5506_ADC_PORT, &GPIO_InitStructure);
    }

    /* Enable the ADC Clock */
    if (GL5506_ADC_INDEX == ADC1)
	{
    	RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_ADC1, ENABLE);
	}
	else if (GL5506_ADC_INDEX == ADC2)
	{
		RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_ADC2, ENABLE);
	}
	else if (GL5506_ADC_INDEX == ADC3)
	{
		RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_ADC3, ENABLE);
	}
	else if (GL5506_ADC_INDEX == ADC4)
	{
		RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_ADC4, ENABLE);
	}
	else
	{
		return GL5506_ERROR_PARA;
	}

    ADC_ConfigClk(GL5506_ADC_INDEX,ADC_CTRL3_CKMOD_AHB,RCC_ADCHCLK_DIV16);
    RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSI, RCC_ADC1MCLK_DIV8);

	/* Config ADC perip*/
	ADC_InitStructure.WorkMode       = ADC_WORKMODE_INDEPENDENT;
	ADC_InitStructure.MultiChEn      = DISABLE;
	ADC_InitStructure.ContinueConvEn = DISABLE;
	ADC_InitStructure.ExtTrigSelect  = ADC_EXT_TRIGCONV_NONE;
	ADC_InitStructure.DatAlign       = ADC_DAT_ALIGN_R;
	ADC_InitStructure.ChsNumber      = 1;
	ADC_Init(GL5506_ADC_INDEX, &ADC_InitStructure);


	/* Enable ADC */
	ADC_Enable(GL5506_ADC_INDEX, ENABLE);
	/*Check ADC Ready*/
	while(ADC_GetFlagStatusReady(GL5506_ADC_INDEX,ADC_FLAG_RDY) == RESET)
	;
	/* Start ADC calibration */
	ADC_StartCalibration(GL5506_ADC_INDEX);
	/* Check the end of ADC calibration */
	while (ADC_GetCalibrationStatus(GL5506_ADC_INDEX))
	;

    return GL5506_ERROR_OK;
}

/**
 * @brief Get gl5506 status.
 */
GL5506_ErrorType gl5506_getresult(GL5506_ResultType* pResult)
{
	uint16_t data;
	uint32_t resistance;

	ADC_ConfigRegularChannel(GL5506_ADC_INDEX, ADC1_Channel_07_PC1, 1, ADC_SAMP_TIME_239CYCLES5);
	/* Start ADC Software Conversion */
	ADC_EnableSoftwareStartConv(GL5506_ADC_INDEX, ENABLE);
	while(ADC_GetFlagStatus(GL5506_ADC_INDEX, ADC_FLAG_ENDC)==0){
	}
	ADC_ClearFlag(GL5506_ADC_INDEX, ADC_FLAG_ENDC);
	ADC_ClearFlag(GL5506_ADC_INDEX, ADC_FLAG_STR);

	pResult->adcsample=ADC_GetDat(GL5506_ADC_INDEX);

	pResult->voltage = (uint32_t)3300*pResult->adcsample/0xFFF;

	/* Calculate the resistance of GL5506 */
	pResult->resistance = (uint32_t)pResult->adcsample*10000 / (0xFFF - pResult->adcsample);

	if(pResult->resistance > GL5506_RES_DARK_THRESHOLD)	//500K
	{
		pResult->status = GL5506_STATUS_DARK;
	}
	else if(pResult->resistance < GL5506_RES_BRIGHT_THRESHOLD)	//7K
	{
		pResult->status = GL5506_STATUS_BRIGHT;
	}
	else
	{
		pResult->status = GL5506_STATUS_MEDIUM;
	}

	return GL5506_ERROR_OK;
}

