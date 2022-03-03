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
 * @file cm32m4xxr_adc.c
 * @author CMIOT Firmware Team
 * @version v1.0.1
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */
#include "nuclei_sdk_soc.h"

/** @addtogroup CM32M4xxR_StdPeriph_Driver
 * @{
 */

/** @defgroup ADC ADC
 * @brief ADC driver modules
 * @{
 */

#ifdef	DRIVER_MODULE_ENABLED_ADC

/** @defgroup ADC_Private_Constants ADC Private Constants
 * @{
 */
/* ADC Software start mask */
#define CTRL2_EXT_TRIG_SWSTART_SET   		((uint32_t)(ADC_CTRL2_SWSTRRCH | ADC_CTRL2_EXTRTRIG))
#define CTRL2_EXT_TRIG_SWSTART_RESET 		((uint32_t)(~CTRL2_EXT_TRIG_SWSTART_SET))

/* ADC injected software start mask */
#define CTRL2_INJ_EXT_TRIG_JSWSTART_SET   	((uint32_t)(ADC_CTRL2_SWSTRJCH | ADC_CTRL2_EXTJTRIG))
#define CTRL2_INJ_EXT_TRIG_JSWSTART_RESET 	((uint32_t)(~CTRL2_INJ_EXT_TRIG_JSWSTART_SET))

/* ADC JDATx registers offset */
#define JDAT_OFFSET							((uint8_t) 0x28)

/* ADC STS register mask */
#define ADC_STS_RESERVE_MASK    ((uint32_t)0x0000007F)    

/**
 * @}
 */

/** @defgroup ADC_Exported_Functions ADC Exported Functions
 * @{
 */

/**
 * @brief Deinitializes the ADCx peripheral registers to their default reset values.
 * @param ADCx where x can be 1, 2 ,3 or 4 to select the ADC peripheral.
 */
void ADC_DeInit(ADC_Module* ADCx)
{
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));

    if (ADCx == ADC1)
    {
        /* Enable ADC1 reset state */
        RCC_EnableAHBPeriphReset(RCC_AHB_PERIPH_ADC1, ENABLE);
		
        /* Release ADC1 from reset state */
        RCC_EnableAHBPeriphReset(RCC_AHB_PERIPH_ADC1, DISABLE);
    }
    else if (ADCx == ADC2)
    {
        /* Enable ADC2 reset state */
        RCC_EnableAHBPeriphReset(RCC_AHB_PERIPH_ADC2, ENABLE);
		
        /* Release ADC2 from reset state */
        RCC_EnableAHBPeriphReset(RCC_AHB_PERIPH_ADC2, DISABLE);
    }
    else if (ADCx == ADC3)
    {
        /* Enable ADC3 reset state */
        RCC_EnableAHBPeriphReset(RCC_AHB_PERIPH_ADC3, ENABLE);
		
        /* Release ADC3 from reset state */
        RCC_EnableAHBPeriphReset(RCC_AHB_PERIPH_ADC3, DISABLE);
    }
    else if (ADCx == ADC4)
    {
		/* Enable ADC4 reset state */
		RCC_EnableAHBPeriphReset(RCC_AHB_PERIPH_ADC4, ENABLE);
		
		/* Release ADC4 from reset state */
		RCC_EnableAHBPeriphReset(RCC_AHB_PERIPH_ADC4, DISABLE);
    }
	else
    {
    
    }
}

/**
 * @brief  Initializes the ADCx peripheral according to the specified parameters
 *         in the ADC_InitStruct.
 * @param ADCx where x can be 1, 2 ,3 or 4 to select the ADC peripheral.
 * @param ADC_InitStruct pointer to an ADC_InitType structure that contains
 *         the configuration information for the specified ADC peripheral.
 */
void ADC_Init(ADC_Module* ADCx, ADC_InitType* ADC_InitStruct)
{
    uint32_t tmpreg1 = 0;
    uint8_t  tmpreg2 = 0;
	
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(ADC_InitStruct != 0);
    assert_param(IsAdcWorkMode(ADC_InitStruct->WorkMode));
    assert_param(IS_FUNCTIONAL_STATE(ADC_InitStruct->MultiChEn));
    assert_param(IS_FUNCTIONAL_STATE(ADC_InitStruct->ContinueConvEn));
    assert_param(IsAdcExtTrig(ADC_InitStruct->ExtTrigSelect));
    assert_param(IsAdcDatAlign(ADC_InitStruct->DatAlign));
    assert_param(IsAdcSeqLenValid(ADC_InitStruct->ChsNumber));

    /*---------------------------- ADCx CTRL1 Configuration -----------------*/
    /* Get the ADCx CTRL1 value */
    tmpreg1 = ADCx->CTRL1;

    /* Clear DUSEL bits and Write to ADCx CTRL1 */
    tmpreg1 &= (uint32_t)~(ADC_CTRL1_DUSEL);
    ADCx->CTRL1 = tmpreg1;

    /* Clear SCANMD bits */
    tmpreg1 &= (uint32_t)~(ADC_CTRL1_SCANMD);

    /* Configure ADCx: Dual mode and scan conversion mode */
    /* Set DUSEL bits according to WorkMode value */
    /* Set SCANMD bit according to MultiChEn value */
    tmpreg1 |= (uint32_t)(ADC_InitStruct->WorkMode | ((uint32_t)ADC_InitStruct->MultiChEn << ADC_CTRL1_SCANMD_Pos));

    /* Write to ADCx CTRL1 */
    ADCx->CTRL1 = tmpreg1;

    /*---------------------------- ADCx CTRL2 Configuration -----------------*/
    /* Get the ADCx CTRL2 value */
    tmpreg1 = ADCx->CTRL2;

    /* Clear CONT, ALIGN and EXTSEL bits */
    tmpreg1 &= (uint32_t)~(ADC_CTRL2_CTU | ADC_CTRL2_ALIG | ADC_CTRL2_EXTRSEL);

    /* Configure ADCx: external trigger event and continuous conversion mode */
    /* Set ALIGN bit according to DatAlign value */
    /* Set EXTSEL bits according to ExtTrigSelect value */
    /* Set CONT bit according to ContinueConvEn value */
    tmpreg1 |= (uint32_t)(ADC_InitStruct->DatAlign | ADC_InitStruct->ExtTrigSelect | ((uint32_t)ADC_InitStruct->ContinueConvEn << 1));
						  
    /* Write to ADCx CTRL2 */
    ADCx->CTRL2 = tmpreg1;

    /*---------------------------- ADCx RSEQ1 Configuration -----------------*/
    /* Get the ADCx RSEQ1 value */
    tmpreg1 = ADCx->RSEQ1;
	
    /* Clear L bits */
    tmpreg1 &= (uint32_t)~ADC_RSEQ1_LEN;
	
    /* Configure ADCx: regular channel sequence length */
    /* Set L bits according to ChsNumber value */
    tmpreg2 |= (uint8_t)(ADC_InitStruct->ChsNumber - (uint8_t)1);
    tmpreg1 |= (uint32_t)tmpreg2 << 20;
	
    /* Write to ADCx RSEQ1 */
    ADCx->RSEQ1 = tmpreg1;
}

/**
 * @brief Fills each ADC_InitStruct member with its default value.
 * @param ADC_InitStruct pointer to an ADC_InitType structure which will be initialized.
 */
void ADC_InitStruct(ADC_InitType* ADC_InitStruct)
{
    /* Check the parameters */
    assert_param(ADC_InitStruct != 0);

    /* Reset ADC init structure parameters values */
    /* Initialize the WorkMode member */
    ADC_InitStruct->WorkMode = ADC_WORKMODE_INDEPENDENT;
	
    /* initialize the MultiChEn member */
    ADC_InitStruct->MultiChEn = DISABLE;
	
    /* Initialize the ContinueConvEn member */
    ADC_InitStruct->ContinueConvEn = DISABLE;
	
    /* Initialize the ExtTrigSelect member */
    ADC_InitStruct->ExtTrigSelect = ADC_EXT_TRIGCONV_T1_CC1;
	
    /* Initialize the DatAlign member */
    ADC_InitStruct->DatAlign = ADC_DAT_ALIGN_R;
	
    /* Initialize the ChsNumber member */
    ADC_InitStruct->ChsNumber = 1;
}

/**
 * @brief Enables or disables the specified ADC peripheral.
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param Cmd new state of the ADCx peripheral.
 *   This parameter can be: ENABLE or DISABLE.
 */
void ADC_Enable(ADC_Module* ADCx, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
	
    if (Cmd != DISABLE)
    {
        /* Set the AD_ON bit to wake up the ADC from power down mode */
        ADCx->CTRL2 |= ADC_CTRL2_ON;
    }
    else
    {
        /* Disable the selected ADC peripheral */
        ADCx->CTRL2 &= ~ADC_CTRL2_ON;
    }
}

/**
 * @brief Enables or disables the specified ADC DMA request.
 * @param ADCx where x can be 1 or 3 to select the ADC peripheral.
 * @param Cmd new state of the selected ADC DMA transfer.
 *   This parameter can be: ENABLE or DISABLE.
 */
void ADC_EnableDMA(ADC_Module* ADCx, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IsAdcDmaModule(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
	
    if (Cmd != DISABLE)
    {
        /* Enable the selected ADC DMA request */
        ADCx->CTRL2 |= ADC_CTRL2_ENDMA;
    }
    else
    {
        /* Disable the selected ADC DMA request */
        ADCx->CTRL2 &= ~ADC_CTRL2_ENDMA;
    }
}

/**
 * @brief Enables or disables the specified ADC interrupts.
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param ADC_IT specifies the ADC interrupt sources to be enabled or disabled.
 *   This parameter can be any combination of the following values:
 *     @arg ADC_INT_ENDC End of conversion interrupt mask
 *     @arg ADC_INT_AWD Analog watchdog interrupt mask
 *     @arg ADC_INT_JENDC End of injected conversion interrupt mask
 * @param Cmd new state of the specified ADC interrupts.
 *   This parameter can be: ENABLE or DISABLE.
 */
void ADC_ConfigInt(ADC_Module* ADCx, uint16_t ADC_IT, FunctionalState Cmd)
{
    uint8_t itmask = 0;
	
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    assert_param(IsAdcInt(ADC_IT));
	
    /* Get the ADC IT index */
    itmask = (uint8_t)ADC_IT;
	
    if (Cmd != DISABLE)
    {
        /* Enable the selected ADC interrupts */
        ADCx->CTRL1 |= itmask;
    }
    else
    {
        /* Disable the selected ADC interrupts */
        ADCx->CTRL1 &= (~(uint32_t)itmask);
    }
}

/**
 * @brief Starts the selected ADC calibration process.
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 */
void ADC_StartCalibration(ADC_Module* ADCx)
{
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
	
    /* Enable the selected ADC calibration process */
    if(ADCx->CALFACT==0)
	{
        ADCx->CTRL2 |= ADC_CTRL2_ENCAL;
    }
}

/**
 * @brief Gets the selected ADC calibration status.
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @retval The new state of ADC calibration (SET or RESET).
 */
FlagStatus ADC_GetCalibrationStatus(ADC_Module* ADCx)
{
    FlagStatus bitstatus = RESET;
	
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
	
    /* Check the status of CAL bit */
    if ((ADCx->CTRL2 & ADC_CTRL2_ENCAL_Msk) != (uint32_t)RESET)
    {
        /* CAL bit is set: calibration on going */
        bitstatus = SET;
    }
    else
    {
        /* CAL bit is reset(by hardware): end of calibration */
        bitstatus = RESET;
    }
    if(ADCx->CALFACT!=0)
    {
        bitstatus = RESET;
    }
    /* Return the CAL bit status */
    return bitstatus;
}

/**
 * @brief Enables or disables the selected ADC software start conversion.
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param Cmd new state of the selected ADC software start conversion.
 *   This parameter can be: ENABLE or DISABLE.
 */
void ADC_EnableSoftwareStartConv(ADC_Module* ADCx, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
	
    if (Cmd != DISABLE)
    {
        /* Enable the selected ADC conversion on external event and start the selected
           ADC conversion */
        ADCx->CTRL2 |= CTRL2_EXT_TRIG_SWSTART_SET;
    }
    else
    {
        /* Disable the selected ADC conversion on external event and stop the selected
           ADC conversion */
        ADCx->CTRL2 &= CTRL2_EXT_TRIG_SWSTART_RESET;
    }
}

/**
 * @brief  Configures the discontinuous mode for the selected ADC regular
 *         group channel.
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param Number specifies the discontinuous mode regular channel
 *         count value. This number must be between 1 and 8.
 */
void ADC_ConfigDiscModeChannelCount(ADC_Module* ADCx, uint8_t Number)
{
    uint32_t tmpreg1 = 0;
    uint32_t tmpreg2 = 0;
	
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IsAdcSeqDiscNumberValid(Number));
	
    /* Get the old register value */
    tmpreg1 = ADCx->CTRL1;
	
    /* Clear the old discontinuous mode channel count */
    tmpreg1 &= (uint32_t)~ADC_CTRL1_DCTU;
	
    /* Set the discontinuous mode channel count */
    tmpreg2 = Number - 1;
    tmpreg1 |= tmpreg2 << ADC_CTRL1_DCTU_Pos;
	
    /* Store the new register value */
    ADCx->CTRL1 = tmpreg1;
}

/**
 * @brief  Enables or disables the discontinuous mode on regular group
 *         channel for the specified ADC
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param Cmd new state of the selected ADC discontinuous mode
 *         on regular group channel.
 *         This parameter can be: ENABLE or DISABLE.
 */
void ADC_EnableRegularDiscMode(ADC_Module* ADCx, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
	
    if (Cmd != DISABLE)
    {
        /* Enable the selected ADC regular discontinuous mode */
        ADCx->CTRL1 |= ADC_CTRL1_DREGCH;
    }
    else
    {
        /* Disable the selected ADC regular discontinuous mode */
        ADCx->CTRL1 &= ~ADC_CTRL1_DREGCH;
    }
}

/**
 * @brief  Configures for the selected ADC regular channel its corresponding
 *         rank in the sequencer and its sample time.
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param ADC_Channel the ADC channel to configure.
 *   This parameter can be one of the following values:
 *     @arg ADC_CH_0 ADC Channel0 selected
 *     @arg ADC_CH_1 ADC Channel1 selected
 *     @arg ADC_CH_2 ADC Channel2 selected
 *     @arg ADC_CH_3 ADC Channel3 selected
 *     @arg ADC_CH_4 ADC Channel4 selected
 *     @arg ADC_CH_5 ADC Channel5 selected
 *     @arg ADC_CH_6 ADC Channel6 selected
 *     @arg ADC_CH_7 ADC Channel7 selected
 *     @arg ADC_CH_8 ADC Channel8 selected
 *     @arg ADC_CH_9 ADC Channel9 selected
 *     @arg ADC_CH_10 ADC Channel10 selected
 *     @arg ADC_CH_11 ADC Channel11 selected
 *     @arg ADC_CH_12 ADC Channel12 selected
 *     @arg ADC_CH_13 ADC Channel13 selected
 *     @arg ADC_CH_14 ADC Channel14 selected
 *     @arg ADC_CH_15 ADC Channel15 selected
 *     @arg ADC_CH_16 ADC Channel16 selected
 *     @arg ADC_CH_17 ADC Channel17 selected
 *     @arg ADC_CH_18 ADC Channel18 selected
 * @param Rank The rank in the regular group sequencer. This parameter must be between 1 to 16.
 * @param ADC_SampleTime The sample time value to be set for the selected channel.
 *   This parameter can be one of the following values:
 *     @arg ADC_SAMP_TIME_1CYCLES5 Sample time equal to 1.5 cycles
 *     @arg ADC_SAMP_TIME_7CYCLES5 Sample time equal to 7.5 cycles
 *     @arg ADC_SAMP_TIME_13CYCLES5 Sample time equal to 13.5 cycles
 *     @arg ADC_SAMP_TIME_28CYCLES5 Sample time equal to 28.5 cycles
 *     @arg ADC_SAMP_TIME_41CYCLES5 Sample time equal to 41.5 cycles
 *     @arg ADC_SAMP_TIME_55CYCLES5 Sample time equal to 55.5 cycles
 *     @arg ADC_SAMP_TIME_71CYCLES5 Sample time equal to 71.5 cycles
 *     @arg ADC_SAMP_TIME_239CYCLES5 Sample time equal to 239.5 cycles
 */
void ADC_ConfigRegularChannel(ADC_Module* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime)
{
    uint32_t tmpreg1 = 0;
	uint32_t tmpreg2 = 0;
	
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IsAdcChannel(ADC_Channel));
    assert_param(IsAdcReqRankValid(Rank));
    assert_param(IsAdcSampleTime(ADC_SampleTime));

    if (ADC_Channel == ADC_CH_18)
    {
        tmpreg1 = ADCx->SAMPT3;
        tmpreg1 &= ~ADC_SAMPT3_SAMP18;
        tmpreg1 |= ADC_SampleTime;
        ADCx->SAMPT3 = tmpreg1;
    }
    else if (ADC_Channel > ADC_CH_9) /* if ADC_CH_10 ... ADC_CH_17 is selected */
    {
        /* Get the old register value */
        tmpreg1 = ADCx->SAMPT1;
		
        /* Calculate the mask to clear */
        tmpreg2 = ADC_SAMPT1_SAMP10 << (3 * (ADC_Channel - 10));
		
        /* Clear the old channel sample time */
        tmpreg1 &= ~tmpreg2;
		
        /* Calculate the mask to set */
        tmpreg2 = (uint32_t)ADC_SampleTime << (3 * (ADC_Channel - 10));
		
        /* Set the new channel sample time */
        tmpreg1 |= tmpreg2;
		
        /* Store the new register value */
        ADCx->SAMPT1 = tmpreg1;
    }
    else /* ADC_Channel include in ADC_Channel_[0..9] */
    {
        /* Get the old register value */
        tmpreg1 = ADCx->SAMPT2;
		
        /* Calculate the mask to clear */
        tmpreg2 = ADC_SAMPT2_SAMP0 << (3 * ADC_Channel);
		
        /* Clear the old channel sample time */
        tmpreg1 &= ~tmpreg2;
		
        /* Calculate the mask to set */
        tmpreg2 = (uint32_t)ADC_SampleTime << (3 * ADC_Channel);
		
        /* Set the new channel sample time */
        tmpreg1 |= tmpreg2;
		
        /* Store the new register value */
        ADCx->SAMPT2 = tmpreg1;
    }
	
    /* For Rank 1 to 6 */
    if (Rank < 7)
    {
        /* Get the old register value */
        tmpreg1 = ADCx->RSEQ3;
		
        /* Calculate the mask to clear */
        tmpreg2 = ADC_RSEQ3_SEQ1 << (5 * (Rank - 1));
		
        /* Clear the old SQx bits for the selected rank */
        tmpreg1 &= ~tmpreg2;
		
        /* Calculate the mask to set */
        tmpreg2 = (uint32_t)ADC_Channel << (5 * (Rank - 1));
		
        /* Set the SQx bits for the selected rank */
        tmpreg1 |= tmpreg2;
		
        /* Store the new register value */
        ADCx->RSEQ3 = tmpreg1;
    }
    else if (Rank < 13) /* For Rank 7 to 12 */
    {
        /* Get the old register value */
        tmpreg1 = ADCx->RSEQ2;
		
        /* Calculate the mask to clear */
        tmpreg2 = ADC_RSEQ2_SEQ7 << (5 * (Rank - 7));
		
        /* Clear the old SQx bits for the selected rank */
        tmpreg1 &= ~tmpreg2;
		
        /* Calculate the mask to set */
        tmpreg2 = (uint32_t)ADC_Channel << (5 * (Rank - 7));
		
        /* Set the SQx bits for the selected rank */
        tmpreg1 |= tmpreg2;
		
        /* Store the new register value */
        ADCx->RSEQ2 = tmpreg1;
    }
    else /* For Rank 13 to 16 */
    {
        /* Get the old register value */
        tmpreg1 = ADCx->RSEQ1;
		
        /* Calculate the mask to clear */
        tmpreg2 = ADC_RSEQ1_SEQ13 << (5 * (Rank - 13));
		
        /* Clear the old SQx bits for the selected rank */
        tmpreg1 &= ~tmpreg2;
		
        /* Calculate the mask to set */
        tmpreg2 = (uint32_t)ADC_Channel << (5 * (Rank - 13));
		
        /* Set the SQx bits for the selected rank */
        tmpreg1 |= tmpreg2;
		
        /* Store the new register value */
        ADCx->RSEQ1 = tmpreg1;
    }
}

/**
 * @brief Enables or disables the ADCx conversion through external trigger.
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param Cmd new state of the selected ADC external trigger start of conversion.
 *   This parameter can be: ENABLE or DISABLE.
 */
void ADC_EnableExternalTrigConv(ADC_Module* ADCx, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
	
    if (Cmd != DISABLE)
    {
        /* Enable the selected ADC conversion on external event */
        ADCx->CTRL2 |= ADC_CTRL2_EXTRTRIG;
    }
    else
    {
        /* Disable the selected ADC conversion on external event */
        ADCx->CTRL2 &= ~ADC_CTRL2_EXTRTRIG;
    }
}

/**
 * @brief Returns the last ADCx conversion result data for regular channel.
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @retval The Data conversion value.
 */
uint16_t ADC_GetDat(ADC_Module* ADCx)
{
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
	
    /* Return the selected ADC conversion value */
    return (uint16_t)ADCx->DAT;
}

/**
 * @brief  Returns the last ADC1 and ADC2 OR last ADC3 and ADC4 conversion result data in dual mode.
  * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @retval The Data conversion value.
 */
uint32_t ADC_GetDualModeConversionDat(ADC_Module* ADCx)
{
	/* Check the parameters */
    assert_param(IsAdcModule(ADCx));
	
    /* Return the dual mode conversion value */
	if(ADCx == ADC1 || ADCx == ADC2)
    	return (uint32_t)ADC1->DAT;
	else
		return (uint32_t)ADC3->DAT;
}

/**
 * @brief  Enables or disables the selected ADC automatic injected group
 *         conversion after regular one.
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param Cmd new state of the selected ADC auto injected conversion
 *   This parameter can be: ENABLE or DISABLE.
 */
void ADC_EnableAutoInjectedConv(ADC_Module* ADCx, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
	
    if (Cmd != DISABLE)
    {
        /* Enable the selected ADC automatic injected group conversion */
        ADCx->CTRL1 |= ADC_CTRL1_AUTOJC;
    }
    else
    {
        /* Disable the selected ADC automatic injected group conversion */
        ADCx->CTRL1 &= ~ADC_CTRL1_AUTOJC;
    }
}

/**
 * @brief  Enables or disables the discontinuous mode for injected group
 *         channel for the specified ADC
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param Cmd new state of the selected ADC discontinuous mode
 *         on injected group channel.
 *   This parameter can be: ENABLE or DISABLE.
 */
void ADC_EnableInjectedDiscMode(ADC_Module* ADCx, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
	
    if (Cmd != DISABLE)
    {
        /* Enable the selected ADC injected discontinuous mode */
        ADCx->CTRL1 |= ADC_CTRL1_DJCH;
    }
    else
    {
        /* Disable the selected ADC injected discontinuous mode */
        ADCx->CTRL1 &= ~ADC_CTRL1_DJCH;
    }
}

/**
 * @brief Configures the ADCx external trigger for injected channels conversion.
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param ADC_ExternalTrigInjecConv specifies the ADC trigger to start injected conversion.
 *   This parameter can be one of the following values:
 *     @arg ADC_EXT_TRIG_INJ_CONV_T1_TRGO Timer1 TRGO event selected (for ADC1, ADC2 and ADC3)
 *     @arg ADC_EXT_TRIG_INJ_CONV_T1_CC4 Timer1 capture compare4 selected (for ADC1, ADC2 and ADC3)
 *     @arg ADC_EXT_TRIG_INJ_CONV_T2_TRGO Timer2 TRGO event selected (for ADC1 and ADC2)
 *     @arg ADC_EXT_TRIG_INJ_CONV_T2_CC1 Timer2 capture compare1 selected (for ADC1 and ADC2)
 *     @arg ADC_EXT_TRIG_INJ_CONV_T3_CC4 Timer3 capture compare4 selected (for ADC1 and ADC2)
 *     @arg ADC_EXT_TRIG_INJ_CONV_T4_TRGO Timer4 TRGO event selected (for ADC1 and ADC2)
 *     @arg ADC_EXT_TRIG_INJ_CONV_EXT_INT15_TIM8_CC4 External interrupt line 15 or Timer8
 *                                                       capture compare4 event selected (for ADC1 and ADC2)
 *     @arg ADC_EXT_TRIG_INJ_CONV_T4_CC3 Timer4 capture compare3 selected (for ADC3 only)
 *     @arg ADC_EXT_TRIG_INJ_CONV_T8_CC2 Timer8 capture compare2 selected (for ADC3 only)
 *     @arg ADC_EXT_TRIG_INJ_CONV_T8_CC4 Timer8 capture compare4 selected (for ADC3 only)
 *     @arg ADC_EXT_TRIG_INJ_CONV_T5_TRGO Timer5 TRGO event selected (for ADC3 only)
 *     @arg ADC_EXT_TRIG_INJ_CONV_T5_CC4 Timer5 capture compare4 selected (for ADC3 only)
 *     @arg ADC_EXT_TRIG_INJ_CONV_NONE Injected conversion started by software and not
 *                                          by external trigger (for ADC1, ADC2 and ADC3)
 */
void ADC_ConfigExternalTrigInjectedConv(ADC_Module* ADCx, uint32_t ADC_ExternalTrigInjecConv)
{
    uint32_t tmpregister = 0;
	
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IsAdcExtInjTrig(ADC_ExternalTrigInjecConv));
	
    /* Get the old register value */
    tmpregister = ADCx->CTRL2;
	
    /* Clear the old external event selection for injected group */
    tmpregister &= ~ADC_CTRL2_EXTJSEL;
	
    /* Set the external event selection for injected group */
    tmpregister |= ADC_ExternalTrigInjecConv;
	
    /* Store the new register value */
    ADCx->CTRL2 = tmpregister;
}

/**
 * @brief  Enables or disables the ADCx injected channels conversion through
 *         external trigger
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param Cmd new state of the selected ADC external trigger start of
 *         injected conversion.
 *   This parameter can be: ENABLE or DISABLE.
 */
void ADC_EnableExternalTrigInjectedConv(ADC_Module* ADCx, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
	
    if (Cmd != DISABLE)
    {
        /* Enable the selected ADC external event selection for injected group */
        ADCx->CTRL2 |= ADC_CTRL2_EXTJTRIG;
    }
    else
    {
        /* Disable the selected ADC external event selection for injected group */
        ADCx->CTRL2 &= ~ADC_CTRL2_EXTJTRIG;
    }
}

/**
 * @brief  Enables or disables the selected ADC start of the injected
 *         channels conversion.
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param Cmd new state of the selected ADC software start injected conversion.
 *   This parameter can be: ENABLE or DISABLE.
 */
void ADC_EnableSoftwareStartInjectedConv(ADC_Module* ADCx, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
	
    if (Cmd != DISABLE)
    {
        /* Enable the selected ADC conversion for injected group on external event and start the selected
           ADC injected conversion */
        ADCx->CTRL2 |= CTRL2_INJ_EXT_TRIG_JSWSTART_SET;
    }
    else
    {
        /* Disable the selected ADC conversion on external event for injected group and stop the selected
           ADC injected conversion */
        ADCx->CTRL2 &= CTRL2_INJ_EXT_TRIG_JSWSTART_RESET;
    }
}

/**
 * @brief Gets the selected ADC Software start injected conversion Status.
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @retval The new state of ADC software start injected conversion (SET or RESET).
 */
FlagStatus ADC_GetSoftwareStartInjectedConvCmdStatus(ADC_Module* ADCx)
{
    FlagStatus bitstatus = RESET;
	
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
	
    /* Check the status of INJ_SWSTART bit */
    if ((ADCx->CTRL2 & ADC_CTRL2_SWSTRJCH_Msk) != (uint32_t)RESET)
    {
        /* INJ_SWSTART bit is set */
        bitstatus = SET;
    }
    else
    {
        /* INJ_SWSTART bit is reset */
        bitstatus = RESET;
    }
	
    /* Return the INJ_SWSTART bit status */
    return bitstatus;
}

/**
 * @brief  Configures for the selected ADC injected channel its corresponding
 *         rank in the sequencer and its sample time.
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param ADC_Channel the ADC channel to configure.
 *   This parameter can be one of the following values:
 *     @arg ADC_CH_0 ADC Channel0 selected
 *     @arg ADC_CH_1 ADC Channel1 selected
 *     @arg ADC_CH_2 ADC Channel2 selected
 *     @arg ADC_CH_3 ADC Channel3 selected
 *     @arg ADC_CH_4 ADC Channel4 selected
 *     @arg ADC_CH_5 ADC Channel5 selected
 *     @arg ADC_CH_6 ADC Channel6 selected
 *     @arg ADC_CH_7 ADC Channel7 selected
 *     @arg ADC_CH_8 ADC Channel8 selected
 *     @arg ADC_CH_9 ADC Channel9 selected
 *     @arg ADC_CH_10 ADC Channel10 selected
 *     @arg ADC_CH_11 ADC Channel11 selected
 *     @arg ADC_CH_12 ADC Channel12 selected
 *     @arg ADC_CH_13 ADC Channel13 selected
 *     @arg ADC_CH_14 ADC Channel14 selected
 *     @arg ADC_CH_15 ADC Channel15 selected
 *     @arg ADC_CH_16 ADC Channel16 selected
 *     @arg ADC_CH_17 ADC Channel17 selected
 *     @arg ADC_CH_18 ADC Channel18 selected
 * @param Rank The rank in the injected group sequencer. This parameter must be between 1 and 4.
 * @param ADC_SampleTime The sample time value to be set for the selected channel.
 *                       (not for the Rank, the sample time going into effect is the last set value)
 *   This parameter can be one of the following values:
 *     @arg ADC_SAMP_TIME_1CYCLES5 Sample time equal to 1.5 cycles
 *     @arg ADC_SAMP_TIME_7CYCLES5 Sample time equal to 7.5 cycles
 *     @arg ADC_SAMP_TIME_13CYCLES5 Sample time equal to 13.5 cycles
 *     @arg ADC_SAMP_TIME_28CYCLES5 Sample time equal to 28.5 cycles
 *     @arg ADC_SAMP_TIME_41CYCLES5 Sample time equal to 41.5 cycles
 *     @arg ADC_SAMP_TIME_55CYCLES5 Sample time equal to 55.5 cycles
 *     @arg ADC_SAMP_TIME_71CYCLES5 Sample time equal to 71.5 cycles
 *     @arg ADC_SAMP_TIME_239CYCLES5 Sample time equal to 239.5 cycles
 */
void ADC_ConfigInjectedChannel(ADC_Module* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime)
{
    uint32_t tmpreg1 = 0;
	uint32_t tmpreg2 = 0;
	uint32_t tmpreg3 = 0;
	
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IsAdcChannel(ADC_Channel));
    assert_param(IsAdcInjRankValid(Rank));
    assert_param(IsAdcSampleTime(ADC_SampleTime));

    if (ADC_Channel == ADC_CH_18)
    {
        tmpreg1 = ADCx->SAMPT3;
        tmpreg1 &= ~ADC_SAMPT3_SAMP18;
        tmpreg1 |= ADC_SampleTime;
        ADCx->SAMPT3 = tmpreg1;
    }
    else if (ADC_Channel > ADC_CH_9) /* if ADC_CH_10 ... ADC_CH_17 is selected */
    {
        /* Get the old register value */
        tmpreg1 = ADCx->SAMPT1;
		
        /* Calculate the mask to clear */
        tmpreg2 = ADC_SAMPT1_SAMP10 << (3 * (ADC_Channel - 10));
		
        /* Clear the old channel sample time */
        tmpreg1 &= ~tmpreg2;
		
        /* Calculate the mask to set */
        tmpreg2 = (uint32_t)ADC_SampleTime << (3 * (ADC_Channel - 10));
		
        /* Set the new channel sample time */
        tmpreg1 |= tmpreg2;
		
        /* Store the new register value */
        ADCx->SAMPT1 = tmpreg1;
    }
    else /* ADC_Channel include in ADC_Channel_[0..9] */
    {
        /* Get the old register value */
        tmpreg1 = ADCx->SAMPT2;
		
        /* Calculate the mask to clear */
        tmpreg2 = ADC_SAMPT2_SAMP0 << (3 * ADC_Channel);
		
        /* Clear the old channel sample time */
        tmpreg1 &= ~tmpreg2;
		
        /* Calculate the mask to set */
        tmpreg2 = (uint32_t)ADC_SampleTime << (3 * ADC_Channel);
		
        /* Set the new channel sample time */
        tmpreg1 |= tmpreg2;
		
        /* Store the new register value */
        ADCx->SAMPT2 = tmpreg1;
    }
	
    /* Rank configuration */
    /* Get the old register value */
    tmpreg1 = ADCx->JSEQ;
	
    /* Get INJ_LEN value: Number = INJ_LEN+1 */
    tmpreg3 = (tmpreg1 & ADC_JSEQ_JLEN_Msk) >> ADC_JSEQ_JLEN_Pos;
	
    /* Calculate the mask to clear: ((Rank-1)+(4-INJ_LEN-1)). Here is different from the regular sequence. */
    tmpreg2 = ADC_JSEQ_JSEQ1 << (5 * (uint8_t)((Rank + 3) - (tmpreg3 + 1)));
	
    /* Clear the old JSQx bits for the selected rank */
    tmpreg1 &= ~tmpreg2;
	
    /* Calculate the mask to set: ((Rank - 1) + (4 - INJ_LEN - 1)). Here is different from the regular sequence. */
    tmpreg2 = (uint32_t)ADC_Channel << (5 * (uint8_t)((Rank + 3) - (tmpreg3 + 1)));
	
    /* Set the JSQx bits for the selected rank */
    tmpreg1 |= tmpreg2;
	
    /* Store the new register value */
    ADCx->JSEQ = tmpreg1;
}

/**
 * @brief Configures the sequencer length for injected channels
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param Length The sequencer length.
 *   This parameter must be a number between 1 to 4.
 */
void ADC_ConfigInjectedSequencerLength(ADC_Module* ADCx, uint8_t Length)
{
    uint32_t tmpreg1 = 0;
    uint32_t tmpreg2 = 0;
	
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IsAdcInjLenValid(Length));

    /* Get the old register value */
    tmpreg1 = ADCx->JSEQ;
	
    /* Clear the old injected sequnence lenght INJ_LEN bits */
    tmpreg1 &= (uint32_t)~ADC_JSEQ_JLEN;
	
    /* Set the injected sequnence lenght INJ_LEN bits */
    tmpreg2 = Length - 1;
    tmpreg1 |= tmpreg2 << ADC_JSEQ_JLEN_Pos;
	
    /* Store the new register value */
    ADCx->JSEQ = tmpreg1;
}

/**
 * @brief Set the injected channels conversion value offset
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param ADC_InjectedChannel the ADC injected channel to set its offset.
 *   This parameter can be one of the following values:
 *     @arg ADC_INJ_CH_1 Injected Channel1 selected
 *     @arg ADC_INJ_CH_2 Injected Channel2 selected
 *     @arg ADC_INJ_CH_3 Injected Channel3 selected
 *     @arg ADC_INJ_CH_4 Injected Channel4 selected
 * @param Offset the offset value for the selected ADC injected channel
 *   This parameter must be a 12bit value.
 */
void ADC_SetInjectedOffsetDat(ADC_Module* ADCx, uint8_t ADC_InjectedChannel, uint16_t Offset)
{
    __IO uint32_t tmp = 0;

    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IsAdcInjCh(ADC_InjectedChannel));
    assert_param(IsAdcOffsetValid(Offset));

    tmp = (uint32_t)ADCx;
    tmp += ADC_InjectedChannel;

    /* Set the selected injected channel data offset */
    *(__IO uint32_t*)tmp = (uint32_t)Offset;
}

/**
 * @brief Returns the ADC injected channel conversion result
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param ADC_InjectedChannel the converted ADC injected channel.
 *   This parameter can be one of the following values:
 *     @arg ADC_INJ_CH_1 Injected Channel1 selected
 *     @arg ADC_INJ_CH_2 Injected Channel2 selected
 *     @arg ADC_INJ_CH_3 Injected Channel3 selected
 *     @arg ADC_INJ_CH_4 Injected Channel4 selected
 * @retval The Data conversion value.
 */
uint16_t ADC_GetInjectedConversionDat(ADC_Module* ADCx, uint8_t ADC_InjectedChannel)
{
    __IO uint32_t tmp = 0;

    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IsAdcInjCh(ADC_InjectedChannel));

    tmp = (uint32_t)ADCx;
    tmp += ADC_InjectedChannel + JDAT_OFFSET;

    /* Returns the selected injected channel conversion data value */
    return (uint16_t)(*(__IO uint32_t*)tmp);
}

/**
 * @brief  Enables or disables the analog watchdog on single/all regular
 *         or injected channels
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param ADC_AnalogWatchdog the ADC analog watchdog configuration.
 *   This parameter can be one of the following values:
 *     @arg ADC_ANALOG_WTDG_SINGLEREG_ENABLE Analog watchdog on a single regular channel
 *     @arg ADC_ANALOG_WTDG_SINGLEINJEC_ENABLE Analog watchdog on a single injected channel
 *     @arg ADC_ANALOG_WTDG_SINGLEREG_OR_INJEC_ENABLE Analog watchdog on a single regular or injected channel
 *     @arg ADC_ANALOG_WTDG_ALLREG_ENABLE Analog watchdog on  all regular channel
 *     @arg ADC_ANALOG_WTDG_ALLINJEC_ENABLE Analog watchdog on  all injected channel
 *     @arg ADC_ANALOG_WTDG_ALLREG_ALLINJEC_ENABLE Analog watchdog on all regular and injected channels
 *     @arg ADC_ANALOG_WTDG_NONE No channel guarded by the analog watchdog
 */
void ADC_ConfigAnalogWatchdogWorkChannelType(ADC_Module* ADCx, uint32_t ADC_AnalogWatchdog)
{
    uint32_t tmpregister = 0;
	
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IsAdcAnalogWatchdog(ADC_AnalogWatchdog));
	
    /* Get the old register value */
    tmpregister = ADCx->CTRL1;
	
    /* Clear AWDEN, AWDENJ and AWDSGL bits */
    tmpregister &= (uint32_t)~(ADC_CTRL1_AWDGSGLEN | ADC_CTRL1_AWDGEJCH | ADC_CTRL1_AWDGERCH);
	
    /* Set the analog watchdog enable mode */
    tmpregister |= ADC_AnalogWatchdog;
	
    /* Store the new register value */
    ADCx->CTRL1 = tmpregister;
}

/**
 * @brief Configures the high and low thresholds of the analog watchdog.
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param HighThreshold the ADC analog watchdog High threshold value.
 *   This parameter must be a 12bit value.
 * @param LowThreshold the ADC analog watchdog Low threshold value.
 *   This parameter must be a 12bit value.
 */
void ADC_ConfigAnalogWatchdogThresholds(ADC_Module* ADCx, uint16_t HighThreshold, uint16_t LowThreshold)
{
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IsAdcThresholdValid(HighThreshold));
    assert_param(IsAdcThresholdValid(LowThreshold));
	
    /* Set the ADCx high threshold */
    ADCx->WDHIGH = (uint32_t)HighThreshold;
	
    /* Set the ADCx low threshold */
    ADCx->WDLOW = (uint32_t)LowThreshold;
}

/**
 * @brief Configures the analog watchdog guarded single channel
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param ADC_Channel the ADC channel to configure for the analog watchdog.
 *   This parameter can be one of the following values:
 *     @arg ADC_CH_0 ADC Channel0 selected
 *     @arg ADC_CH_1 ADC Channel1 selected
 *     @arg ADC_CH_2 ADC Channel2 selected
 *     @arg ADC_CH_3 ADC Channel3 selected
 *     @arg ADC_CH_4 ADC Channel4 selected
 *     @arg ADC_CH_5 ADC Channel5 selected
 *     @arg ADC_CH_6 ADC Channel6 selected
 *     @arg ADC_CH_7 ADC Channel7 selected
 *     @arg ADC_CH_8 ADC Channel8 selected
 *     @arg ADC_CH_9 ADC Channel9 selected
 *     @arg ADC_CH_10 ADC Channel10 selected
 *     @arg ADC_CH_11 ADC Channel11 selected
 *     @arg ADC_CH_12 ADC Channel12 selected
 *     @arg ADC_CH_13 ADC Channel13 selected
 *     @arg ADC_CH_14 ADC Channel14 selected
 *     @arg ADC_CH_15 ADC Channel15 selected
 *     @arg ADC_CH_16 ADC Channel16 selected
 *     @arg ADC_CH_17 ADC Channel17 selected
 *     @arg ADC_CH_18 ADC Channel18 selected
 */
void ADC_ConfigAnalogWatchdogSingleChannel(ADC_Module* ADCx, uint8_t ADC_Channel)
{
    uint32_t tmpregister = 0;
	
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IsAdcChannel(ADC_Channel));
	
    /* Get the old register value */
    tmpregister = ADCx->CTRL1;
	
    /* Clear the Analog watchdog channel select bits */
    tmpregister &= (uint32_t)~ADC_CTRL1_AWDGCH;
	
    /* Set the Analog watchdog channel */
    tmpregister |= ADC_Channel;
	
    /* Store the new register value */
    ADCx->CTRL1 = tmpregister;
}

/**
 * @brief Enables or disables the temperature sensor and Vrefint channel.
 * @param Cmd new state of the temperature sensor.
 *   This parameter can be: ENABLE or DISABLE.
 */
void ADC_EnableTempSensorVrefint(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
	
    if (Cmd != DISABLE)
    {
        /* Enable the temperature sensor and Vrefint channel*/
        ADC1->CTRL2 |= ADC_CTRL2_TEMPEN;
        _EnVref1p2();
    }
    else
    {
        /* Disable the temperature sensor and Vrefint channel*/
        ADC1->CTRL2 &= ~ADC_CTRL2_TEMPEN;
        _DisVref1p2();
    }
}

/**
 * @brief Checks whether the specified ADC flag is set or not.
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param ADC_FLAG specifies the flag to check.
 *   This parameter can be one of the following values:
 *     @arg ADC_FLAG_AWDG Analog watchdog flag
 *     @arg ADC_FLAG_ENDC End of conversion flag
 *     @arg ADC_FLAG_JENDC End of injected group conversion flag
 *     @arg ADC_FLAG_JSTR Start of injected group conversion flag
 *     @arg ADC_FLAG_STR Start of regular group conversion flag
 *     @arg ADC_FLAG_EOC_ANY End of any conversion flag
 *     @arg ADC_FLAG_JEOC_ANY End of any injected group conversion flag
 * @retval The new state of ADC_FLAG (SET or RESET).
 */
FlagStatus ADC_GetFlagStatus(ADC_Module* ADCx, uint8_t ADC_FLAG)
{
    FlagStatus bitstatus = RESET;
	
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IsAdcGetFlag(ADC_FLAG));
	
    /* Check the status of the specified ADC flag */
    if ((ADCx->STS & ADC_FLAG) != (uint8_t)RESET)
    {
        /* ADC_FLAG is set */
        bitstatus = SET;
    }
    else
    {
        /* ADC_FLAG is reset */
        bitstatus = RESET;
    }
	
    /* Return the ADC_FLAG status */
    return bitstatus;
}

/**
 * @brief Clears the ADCx's pending flags.
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param ADC_FLAG specifies the flag to clear.
 *   This parameter can be any combination of the following values:
 *     @arg ADC_FLAG_AWDG Analog watchdog flag
 *     @arg ADC_FLAG_ENDC End of conversion flag
 *     @arg ADC_FLAG_JENDC End of injected group conversion flag
 *     @arg ADC_FLAG_JSTR Start of injected group conversion flag
 *     @arg ADC_FLAG_STR Start of regular group conversion flag
 *     @arg ADC_FLAG_EOC_ANY End of any conversion flag
 *     @arg ADC_FLAG_JEOC_ANY End of any injected group conversion flag
 */
void ADC_ClearFlag(ADC_Module* ADCx, uint8_t ADC_FLAG)
{
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IsAdcClrFlag(ADC_FLAG));
	
    /* Clear the selected ADC flags */
    ADCx->STS = (~(uint32_t)ADC_FLAG & ADC_STS_RESERVE_MASK);
}

/**
 * @brief Checks whether the specified ADC interrupt has occurred or not.
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param ADC_IT specifies the ADC interrupt source to check.
 *   This parameter can be one of the following values:
 *     @arg ADC_INT_ENDC End of conversion interrupt mask
 *     @arg ADC_INT_AWD Analog watchdog interrupt mask
 *     @arg ADC_INT_JENDC End of injected conversion interrupt mask
 * @retval The new state of ADC_IT (SET or RESET).
 */
INTStatus ADC_GetIntStatus(ADC_Module* ADCx, uint16_t ADC_IT)
{
    INTStatus bitstatus    = RESET;
    uint32_t  itmask       = 0;
	uint32_t  enablestatus = 0;
	
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IsAdcGetInt(ADC_IT));
	
    /* Get the ADC IT index */
    itmask = (uint32_t)(ADC_IT >> 8);
	
    /* Get the ADC_IT enable bit status */
    enablestatus = (ADCx->CTRL1 & (uint8_t)ADC_IT);
	
    /* Check the status of the specified ADC interrupt */
    if (((ADCx->STS & itmask) != (uint32_t)RESET) && enablestatus)
    {
        /* ADC_IT is set */
        bitstatus = SET;
    }
    else
    {
        /* ADC_IT is reset */
        bitstatus = RESET;
    }
	
    /* Return the ADC_IT status */
    return bitstatus;
}

/**
 * @brief Clears the ADCx's interrupt pending bits.
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param ADC_IT specifies the ADC interrupt pending bit to clear.
 *   This parameter can be any combination of the following values:
 *     @arg ADC_INT_ENDC End of conversion interrupt mask
 *     @arg ADC_INT_AWD Analog watchdog interrupt mask
 *     @arg ADC_INT_JENDC End of injected conversion interrupt mask
 */
void ADC_ClearIntPendingBit(ADC_Module* ADCx, uint16_t ADC_IT)
{
    uint8_t itmask = 0;
	
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IsAdcInt(ADC_IT));
	
    /* Get the ADC IT index */
    itmask = (uint8_t)(ADC_IT >> 8);
	
    /* Clear the selected ADC interrupt pending bits */
    ADCx->STS = (~(uint32_t)itmask & ADC_STS_RESERVE_MASK);
}

/**
 * @brief  Initializes the ADCx peripheral according to the specified parameters
 *         in the ADC_InitStructEx.
 * @param ADCx where x can be 1, 2 ,3 or 4 to select the ADC peripheral.
 * @param ADC_InitStructEx pointer to an ADC_InitTypeEx structure that contains
 *         the configuration information for the specified ADC peripheral.
 */
void ADC_InitEx(ADC_Module* ADCx, ADC_InitTypeEx* ADC_InitStructEx)
{
    uint32_t tmpregister = 0;
	
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(ADC_InitStructEx != 0);
    assert_param(IS_FUNCTIONAL_STATE(ADC_InitStructEx->VbatMinitEn));
    assert_param(IS_FUNCTIONAL_STATE(ADC_InitStructEx->DeepPowerModEn));
    assert_param(IS_FUNCTIONAL_STATE(ADC_InitStructEx->JendcIntEn));
    assert_param(IS_FUNCTIONAL_STATE(ADC_InitStructEx->EndcIntEn));
    assert_param(IS_ADC_CTRL3_CKMOD(ADC_InitStructEx->ClkMode));
    assert_param(IS_FUNCTIONAL_STATE(ADC_InitStructEx->CalAtuoLoadEn));
    assert_param(IS_BOOL_STATE(ADC_InitStructEx->DifModCal));
    assert_param(IS_ADC_CTRL3_RES(ADC_InitStructEx->ResBit));
    assert_param(IS_BOOL_STATE(ADC_InitStructEx->SampSecondStyle));

    /* ADC_SAMPT3 sample time selection */
    if (ADC_InitStructEx->SampSecondStyle)
        ADCx->SAMPT3 |= ADC_SAMPT3_SAMPSEL;
    else
        ADCx->SAMPT3 &= (~ADC_SAMPT3_SAMPSEL);

    /*intial ADC_CTRL3 once initiall config*/
    tmpregister = ADCx->CTRL3;
    if (ADC_InitStructEx->VbatMinitEn)
    {
        tmpregister |= ADC_CTRL3_VBATMEN;
        _EnVref1p2();
    }
    else
    {
        tmpregister &= (~ADC_CTRL3_VBATMEN);
		_DisVref1p2();
    }

    if (ADC_InitStructEx->DeepPowerModEn)
        tmpregister |= ADC_CTRL3_DPWMOD;
    else
        tmpregister &= (~ADC_CTRL3_DPWMOD);

    if (ADC_InitStructEx->JendcIntEn)
        tmpregister |= ADC_CTRL3_JENDCAIEN;
    else
        tmpregister &= (~ADC_CTRL3_JENDCAIEN);

    if (ADC_InitStructEx->EndcIntEn)
        tmpregister |= ADC_CTRL3_ENDCAIEN;
    else
        tmpregister &= (~ADC_CTRL3_ENDCAIEN);

    if (ADC_InitStructEx->CalAtuoLoadEn)
        tmpregister |= ADC_CTRL3_CALALD;
    else
        tmpregister &= (~ADC_CTRL3_CALALD);

    if (ADC_InitStructEx->DifModCal)
        tmpregister |= ADC_CTRL3_CALDIF;
    else
        tmpregister &= (~ADC_CTRL3_CALDIF);

    tmpregister &= (~ADC_CTRL3_RES);
    tmpregister |= ADC_InitStructEx->ResBit;

    if(ADC_InitStructEx->ClkMode == ADC_CTRL3_CKMOD_PLL)
    	tmpregister |= ADC_CTRL3_CKMOD;
	else
    	tmpregister &= (~ADC_CTRL3_CKMOD);

    ADCx->CTRL3 = tmpregister;
}

/**
 * @brief Configure differential channels enable.
 * @param ADCx where x can be 1, 2 ,3 or 4 to select the ADC peripheral.
 * @param DifChs differential channels,see @ADC_dif_sel_ch_definition. eg: ADC_DIFSEL_CHS_3|ADC_DIFSEL_CHS_4
 * @param Cmd enable differential channels
 */
void ADC_SetDifChsEnable(ADC_Module* ADCx, uint32_t DifChs, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IS_ADC_DIFSEL_CHS(DifChs));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if (Cmd)
    	ADCx->DIFSEL |= DifChs;
	else
		ADCx->DIFSEL &= ~(DifChs);
}

/**
 * @brief Checks whether the specified ADC flag is set or not.
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param ReadyFlag specifies the flag to check.
 *   This parameter can be one of the following values:
 *     @arg ADC_FLAG_RDY ADC ready flag
 *     @arg ADC_FLAG_PD_RDY ADC powerdown ready flag
 * @retval The new state of ADC_FLAG_NEW (SET or RESET).
 */
FlagStatus ADC_GetFlagStatusReady(ADC_Module* ADCx, uint8_t ReadyFlag)
{
    FlagStatus bitstatus = RESET;
	
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IS_ADC_GET_READY(ReadyFlag));
	
    /* Check the status of the specified ADC flag */
    if ((ADCx->CTRL3 & ReadyFlag) != (uint8_t)RESET)
    {
        /* ReadyFlag is set */
        bitstatus = SET;
    }
    else
    {
        /* ReadyFlag is reset */
        bitstatus = RESET;
    }
	
    /* Return the ReadyFlag status */
    return bitstatus;
}

/**
 * @brief Set Adc calibration bypass or enable.
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param Cmd enable bypass calibration.
 *   This parameter can be one of the following values:
 *     @arg true bypass calibration
 *     @arg false not bypass calibration
 */
void ADC_SetBypassCalibration(ADC_Module* ADCx, FunctionalState Cmd)
{
    uint32_t tmpregister = 0;

    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    tmpregister = ADCx->CTRL3;
	
    if (Cmd)
        tmpregister |= ADC_CTRL3_BPCAL;
    else
        tmpregister &= (~ADC_CTRL3_BPCAL);
		
    ADCx->CTRL3 = tmpregister;
}

/**
 * @brief Set Adc transform data bits width.
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param ResultBitNum specifies num with adc transform width.
 *   This parameter can be one of the following values:
 *     @arg ADC_RST_BIT_12 12 bit trans
 *     @arg ADC_RST_BIT_10 10 bit trans
 *     @arg ADC_RST_BIT_8 8 bit trans
 *     @arg ADC_RST_BIT_6 6 bit trans
 */
void ADC_SetConvResultBitNum(ADC_Module* ADCx, uint32_t ResultBitNum)
{
    uint32_t tmpregister = 0;

    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IS_ADC_CTRL3_RES(ResultBitNum));

    tmpregister = ADCx->CTRL3;
	
    tmpregister &= (uint32_t)~ADC_CTRL3_RES;
    tmpregister |= ResultBitNum;
	
    ADCx->CTRL3 = tmpregister;
	
    return;
}

/**
 * @brief  Configures the ADCHCLK prescaler.
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param ADC_ClkMode where select the clock mode
 *     @arg ADC_CTRL3_CKMOD_AHB select AHB as clock
 *     @arg ADC_CTRL3_CKMOD_PLL select PLL as clock
 * @param RCC_ADCHCLKPrescaler specifies the ADCHCLK prescaler.
 *   This parameter can be on of the following values:
 *     @arg RCC_ADCHCLK_DIV1 ADCHCLKPRE[3:0] = 0000, HCLK Clock Divided By 1
 *     @arg RCC_ADCHCLK_DIV2 ADCHCLKPRE[3:0] = 0001, HCLK Clock Divided By 2
 *     @arg RCC_ADCHCLK_DIV4 ADCHCLKPRE[3:0] = 0010, HCLK Clock Divided By 4
 *     @arg RCC_ADCHCLK_DIV6 ADCHCLKPRE[3:0] = 0011, HCLK Clock Divided By 6
 *     @arg RCC_ADCHCLK_DIV8 ADCHCLKPRE[3:0] = 0100, HCLK Clock Divided By 8
 *     @arg RCC_ADCHCLK_DIV10 ADCHCLKPRE[3:0] = 0101, HCLK Clock Divided By 10
 *     @arg RCC_ADCHCLK_DIV12 ADCHCLKPRE[3:0] = 0110, HCLK Clock Divided By 12
 *     @arg RCC_ADCHCLK_DIV16 ADCHCLKPRE[3:0] = 0111, HCLK Clock Divided By 16
 *     @arg RCC_ADCHCLK_DIV32 ADCHCLKPRE[3:0] = 1000, HCLK Clock Divided By 32
 *     @arg RCC_ADCHCLK_DIV32 ADCHCLKPRE[3:0] = others, HCLK Clock Divided By 32

 *     @arg RCC_ADCPLLCLK_DISABLE ADCPLLCLKPRES[4:0] = 0xxxx, ADC Pll Clock Disable
 *     @arg RCC_ADCPLLCLK_DIV1 ADCPLLCLKPRES[4:0] = 10000, Pll Clock Divided By 1
 *     @arg RCC_ADCPLLCLK_DIV2 ADCPLLCLKPRES[4:0] = 10001, Pll Clock Divided By 2
 *     @arg RCC_ADCPLLCLK_DIV4 ADCPLLCLKPRES[4:0] = 10010, Pll Clock Divided By 4
 *     @arg RCC_ADCPLLCLK_DIV6 ADCPLLCLKPRES[4:0] = 10011, Pll Clock Divided By 6
 *     @arg RCC_ADCPLLCLK_DIV8 ADCPLLCLKPRES[4:0] = 10100, Pll Clock Divided By 8
 *     @arg RCC_ADCPLLCLK_DIV10 ADCPLLCLKPRES[4:0] = 10101, Pll Clock Divided By 10
 *     @arg RCC_ADCPLLCLK_DIV12 ADCPLLCLKPRES[4:0] = 10110, Pll Clock Divided By 12
 *     @arg RCC_ADCPLLCLK_DIV16 ADCPLLCLKPRES[4:0] = 10111, Pll Clock Divided By 16
 *     @arg RCC_ADCPLLCLK_DIV32 ADCPLLCLKPRES[4:0] = 11000, Pll Clock Divided By 32
 *     @arg RCC_ADCPLLCLK_DIV64 ADCPLLCLKPRES[4:0] = 11001, Pll Clock Divided By 64
 *     @arg RCC_ADCPLLCLK_DIV128 ADCPLLCLKPRES[4:0] = 11010, Pll Clock Divided By 128
 *     @arg RCC_ADCPLLCLK_DIV256 ADCPLLCLKPRES[4:0] = 11011, Pll Clock Divided By 256
 *     @arg RCC_ADCPLLCLK_DIV256 ADCPLLCLKPRES[4:0] = others, Pll Clock Divided By 256
 */
void ADC_ConfigClk(ADC_Module* ADCx, ADC_CTRL3_CKMOD_T ADC_ClkMode, uint32_t RCC_ADCHCLKPrescaler)
{
    /* Check the parameters */
	assert_param(IS_ADC_CTRL3_CKMOD(ADC_ClkMode));
    assert_param(IS_RCC_ADCHCLKPRE(RCC_ADCHCLKPrescaler));

    uint32_t tmpregister = 0;

    tmpregister = ADCx->CTRL3;

    if(ADC_ClkMode == ADC_CTRL3_CKMOD_AHB)
    {
        RCC_ConfigAdcPllClk(RCC_ADCPLLCLK_DIV1, DISABLE);
        RCC_ConfigAdcHclk(RCC_ADCHCLKPrescaler);
        tmpregister &= (~ADC_CTRL3_CKMOD);
    }
    else
    {
        RCC_ConfigAdcPllClk(RCC_ADCHCLKPrescaler, ENABLE);
        RCC_ConfigAdcHclk(RCC_ADCHCLK_DIV1);
        tmpregister |= ADC_CTRL3_CKMOD;
    }
    ADCx->CTRL3 = tmpregister;
}
/**
 * @}
 */

#endif

/**
 * @}
 */

/**
 * @}
 */
