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
 * @file main.c
 * @author CMIOT Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */

#include "main.h"
#include "log.h"

/** @addtogroup CM32M4xxR_StdPeriph_Examples
 * @{
 */

/** @addtogroup TIM_Input_Capture
 * @{
 */

ADC_InitType ADC_InitStructure;
DMA_InitType DMA_InitStructure;

void RCC_Configuration(void);
void GPIO_Configuration(void);
void OPA_Configuration(void);
uint16_t ADC_GetData(uint8_t ADC_Channel);
void ADC_Initial(void);

__IO uint16_t ADCConvertedValue;
/**
 * @brief  Main function
 */
int main(void)
{
    /* System Clocks Configuration */
    RCC_Configuration();

    /* Configure the GPIO ports */
    GPIO_Configuration();

    /* OPA configuration ------------------------------------------------------*/
    OPA_Configuration();

    /* ADC Initial ------------------------------------------------------*/
    ADC_Initial();
    while (1)
    {
    	ADCConvertedValue = ADC_GetData(ADC1_Channel_03_PA6);
    }
}



/**
 * @brief  Configures the Opa.
 */
void OPA_Configuration(void)
{
    OPAMP_InitType OPAMP_Initial;
    OPAMP_StructInit(&OPAMP_Initial);
    OPAMP_Initial.Mod            = OPAMP_CS_PGA_EN;//OPAMP_CS_FOLLOW; // OPA_CS_FOLLOW;//OPA_CS_PGA_EN;
    OPAMP_Initial.Gain           = OPAMP_CS_PGA_GAIN_2;
    OPAMP_Initial.HighVolRangeEn = ENABLE;
    OPAMP_Initial.TimeAutoMuxEn  = DISABLE;
    /*configure opa1*/
    OPAMP_Init(OPAMP1, &OPAMP_Initial);

    OPAMP_SetVpSel(OPAMP1, OPAMP1_CS_VPSEL_PA1);

    OPAMP_Enable(OPAMP1, ENABLE);

}

/**
 * @brief  Configures the different system clocks.
 */
void RCC_Configuration(void)
{
	RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_ADC1, ENABLE);
    /* TIM3 clock enable */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_OPAMP, ENABLE);

    /* GPIOA and GPIOB clock enable */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);

	/* RCC_ADCHCLK_DIV16*/
    ADC_ConfigClk(ADC1,ADC_CTRL3_CKMOD_AHB, RCC_ADCHCLK_DIV16);
    RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSI, RCC_ADC1MCLK_DIV8);  //selsect HSE as RCC ADC1M CLK Source

}

/**
 * @brief  Configure the GPIOD Pins.
 */
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    /* TIM3 channel 2 pin (PA.07) configuration */
    GPIO_InitStructure.Pin        = GPIO_PIN_1|GPIO_PIN_6;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

}


void ADC_Initial(void)
{
    /* ADC configuration ------------------------------------------------------*/
	ADC_InitStructure.WorkMode       = ADC_WORKMODE_INDEPENDENT;
	ADC_InitStructure.MultiChEn      = DISABLE;
    ADC_InitStructure.ContinueConvEn = DISABLE;
    ADC_InitStructure.ExtTrigSelect  = ADC_EXT_TRIGCONV_NONE;
    ADC_InitStructure.DatAlign       = ADC_DAT_ALIGN_R;
    ADC_InitStructure.ChsNumber      = 1;
    ADC_Init(ADC1, &ADC_InitStructure);

    /* Enable ADC */
    ADC_Enable(ADC1, ENABLE);
    /* Check ADC Ready */
    while(ADC_GetFlagStatusReady(ADC1,ADC_FLAG_RDY) == RESET)
        ;
    /* Start ADC1 calibration */
    ADC_StartCalibration(ADC1);
    /* Check the end of ADC1 calibration */
    while (ADC_GetCalibrationStatus(ADC1))
        ;
}

uint16_t ADC_GetData(uint8_t ADC_Channel)
{
    uint16_t dat;
    ADC_ConfigRegularChannel(ADC1, ADC_Channel, 1, ADC_SAMP_TIME_55CYCLES5);
    /* Start ADC Software Conversion */
    ADC_EnableSoftwareStartConv(ADC1,ENABLE);
    while(ADC_GetFlagStatus(ADC1,ADC_FLAG_ENDC)==0){
    }
    ADC_ClearFlag(ADC1,ADC_FLAG_ENDC);
    ADC_ClearFlag(ADC1,ADC_FLAG_STR);
    dat=ADC_GetDat(ADC1);
    return dat;
}

/**
 * @}
 */

/**
 * @}
 */
