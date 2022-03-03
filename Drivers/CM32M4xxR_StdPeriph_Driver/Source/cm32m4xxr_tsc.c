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
 * @file cm32m4xxr_tsc.c
 * @author CMIOT Firmware Team
 * @brief Source file containing functions prototypes of TSC stdperiph library.
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */
#include "nuclei_sdk_soc.h"

/** @addtogroup CM32M4xxR_StdPeriph_Driver
 * @{
 */

/** @defgroup TSC TSC
 * @brief TSC driver modules
 * @{
 */

#ifdef	DRIVER_MODULE_ENABLED_TSC

/* Exported functions --------------------------------------------------------*/
/** @defgroup TSC_Exported_Functions TSC Exported Functions
  * @{
  */

/**
 * @brief  Deinitializes the TSC peripheral registers to their default reset values.
 */
void TSC_DeInit(void)
{
    RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_TSC, ENABLE);
    RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_TSC, DISABLE);
}

/**
* @brief  Init TSC config
* @param  TSC_Init: TSC initialize structure
* @return TSC error code
*/
TSC_ErrorTypeDef TSC_Init(TSC_InitType* TSC_Init)
{
    uint32_t tempreg;
    uint32_t timeout;

    assert_param(IS_TSC_PTR_NONNULL(TSC_Init));
    assert_param(IS_TSC_DET_PERIOD(TSC_Init->Period));
    assert_param(IS_TSC_FILTER(TSC_Init->Filter));
    assert_param(IS_TSC_DET_TYPE(TSC_Init->Type));
    assert_param(IS_TSC_INT(TSC_Init->Int));
    assert_param(IS_TSC_OUT(TSC_Init->Out));
    assert_param(IS_TSC_PAD_OPTION(TSC_Init->PadOpt));
    assert_param(IS_TSC_PAD_SPEED(TSC_Init->Speed));

    /* waiting tsc hw for idle status */
    timeout = 0;
    do
    {
        __TSC_HW_DISABLE();
        
        if(++timeout > TSC_TIMEOUT)
            return TSC_ERROR_HW_MODE;
			
    }while (__TSC_GET_HW_MODE());

    /* TSC_CTRL config */
    tempreg = 0;
	tempreg |= TSC_Init->Period;
	tempreg |= TSC_Init->Filter;
	tempreg |= TSC_Init->Type;
	tempreg |= TSC_Init->Int;
	tempreg |= TSC_Init->Out;

    TSC->CTRL = tempreg;

    /* TSC_ANA_SEL config */
    TSC->ANA_SEL = TSC_Init->PadOpt | TSC_Init->Speed;

    return TSC_ERROR_OK;
}

/**
 * @brief Fills each TSC_InitStruct member with its default value.
 * @param TSC_InitStruct pointer to a TSC_InitStruct structure which will
 *         be initialized.
 */
void TSC_InitStruct(TSC_InitType* TSC_InitStruct)
{

	assert_param(IS_TSC_PTR_NONNULL(TSC_InitStruct));

    /* Reset GPIO init structure parameters values */
	TSC_InitStruct->Filter = TSC_DET_FILTER_1;
	TSC_InitStruct->Int    = TSC_IT_DET_DISABLE;
	TSC_InitStruct->Out    = TSC_OUT_PIN;
	TSC_InitStruct->PadOpt = TSC_PAD_INTERNAL_RES;
	TSC_InitStruct->Period = TSC_DET_PERIOD_8;
	TSC_InitStruct->Speed  = TSC_PAD_SPEED_0;
	TSC_InitStruct->Type   = TSC_DET_TYPE_LESS;
}

/**
 * @brief  Configure the clock source of TSC。
 *         Note:if LSE is specified, LSI will be closed.
 * @param  TSC_ClkSource specifies the clock source of TSC.
 *   This parameter can be one of the following values:
 *     @arg TSC_CLK_SRC_LSI:              TSC clock source is LSI(default)
 *     @arg TSC_CLK_SRC_LSE:              TSC clock source is LSE
 * @return TSC error code
 */
TSC_ErrorTypeDef TSC_ConfigClock(uint32_t TSC_ClkSource)
{
    uint32_t timeout;

    assert_param(IS_TSC_CLK_SOURCE(TSC_ClkSource));
    
    /* Enable PWR peripheral Clock */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_PWR, ENABLE);

    if(TSC_CLK_SRC_LSI == TSC_ClkSource)
    {
        /* Enable LSI clock */
        RCC_EnableLsi(ENABLE);

        /* Wait LSI stable */
        timeout = 0;
        while(RCC_GetFlagStatus(RCC_FLAG_LSIRD) == RESET)
        {
            if(++timeout >TSC_TIMEOUT)
                return TSC_ERROR_CLOCK;
        }
    }
    else if(TSC_CLK_SRC_LSE == TSC_ClkSource)
    {
        if(RCC_GetFlagStatus(RCC_FLAG_LSERD) == RESET)
        {
            /* Set bit 8 of PWR_CTRL1.Open PWR DBP */
            PWR_BackupAccessEnable(ENABLE);
            RCC_ConfigLse(TSC_ClkSource);
            
            timeout = 0;
            while(RCC_GetFlagStatus(RCC_FLAG_LSERD) == RESET)
            {
                if(++timeout > TSC_TIMEOUT)
                    return TSC_ERROR_CLOCK;
            }

            RCC_EnableLsi(DISABLE);

        }
    }
    else
        return TSC_ERROR_PARAMETER;
    
    /* Enable TSC clk */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TSC, ENABLE);

    return TSC_ERROR_OK;
}

/**
 * @brief  Configure analog signal parameters.
 * @param  AnaCfg Pointer of analog parameter structure.
 * @return TSC error code
 */
TSC_ErrorTypeDef TSC_ConfigAna(TSC_AnaCfg* AnaCfg)
{
	uint32_t timeout;

	assert_param(IS_TSC_PAD_OPTION(AnaCfg->TSC_AnaResisOption));
	assert_param(IS_TSC_PAD_SPEED(AnaCfg->TSC_AnaSpeedOption));

    /* waiting tsc hw for idle status */
    timeout = 0;
    do
    {
        __TSC_HW_DISABLE();

        if(++timeout > TSC_TIMEOUT)
            return TSC_ERROR_HW_MODE;

    }while (__TSC_GET_HW_MODE());

    /* set resistor and speed */
    __TSC_PAD_OPT_CONFIG(AnaCfg->TSC_AnaResisOption);
    __TSC_PAD_SPEED_CONFIG(AnaCfg->TSC_AnaSpeedOption);

    return TSC_ERROR_OK;
}

/**
 * @brief  Configure internal charge resistor for some channels
 * @param  Channels: channels to be configed, as TSC_CHNEN defined
 *   This parameter:bit[0:23] used,bit[24:31] must be 0
 *   bitx: TSC channel x
 * @param  res:  internal resistor select
 *   This parameter can be one of the following values:
 *      @arg TSC_RESR0_CHN_RESIST0_1M:      1M OHM
 *      @arg TSC_RESR0_CHN_RESIST0_875K:    875K OHM
 *      @arg TSC_RESR0_CHN_RESIST0_750K:    750K OHM
 *      @arg TSC_RESR0_CHN_RESIST0_625K:    625K OHM
 *      @arg TSC_RESR0_CHN_RESIST0_500K:    500K OHM
 *      @arg TSC_RESR0_CHN_RESIST0_375K:    375K OHM
 *      @arg TSC_RESR0_CHN_RESIST0_250K:    250K OHM
 *      @arg TSC_RESR0_CHN_RESIST0_125K:    125K OHM
 * @return TSC error code
 *
*/
TSC_ErrorTypeDef TSC_ConfigInternalResistor(uint32_t Channels, uint32_t res )
{
    uint32_t i;
    uint32_t chn;
    uint32_t timeout;
    uint32_t nReg;
    uint32_t nPos;

    assert_param(IS_TSC_CHN(Channels));
    assert_param(IS_TSC_RESISTOR_VALUE(res));

    /* waiting tsc hw for idle status */
    timeout = 0;
    do
    {
        __TSC_HW_DISABLE();
        
        if(++timeout > TSC_TIMEOUT)
            return TSC_ERROR_HW_MODE;
			
    }while (__TSC_GET_HW_MODE());

    /* Mask invalid bits */
    chn  = Channels & TSC_CHNEN_CHN_SEL_ALL_Msk;
    
    /* Set resistance for each channel one by one */
    for (i = 0; i < MAX_TSC_HW_CHN; i++)
    {
        if (chn & 0x00000001)
        {
            nReg = i >> 3;
            nPos = (i & 0x7UL) * 4;
            MODIFY_REG(TSC->RESR[nReg], TSC_RESR0_CHN_RESIST0_Msk << nPos, res << nPos);
        }

        chn >>= 1;
    }

    return TSC_ERROR_OK;
}

/**
 * @brief  Configure threshold value for some channels
 * @param  Channels: channels to be configed, as TSC_CHNEN defined
 *   This parameter:bit[0:23] used,bit[24:31] must be 0
 *                  bitx: TSC channel x
 * @param  base:   base value of threshold, 0-MAX_TSC_THRESHOLD_BASE
 * @param  delta:  delta value of threshold,0-MAX_TSC_THRESHOLD_DELRA
 * @return TSC error code
 */
TSC_ErrorTypeDef TSC_ConfigThreshold(uint32_t Channels, uint32_t base, uint32_t delta)
{
    uint32_t i;
    uint32_t chn;
    uint32_t timeout;
    
    assert_param(IS_TSC_CHN(Channels));
    assert_param(IS_TSC_THRESHOLD_BASE(base));
    assert_param(IS_TSC_THRESHOLD_DELTA(delta));
    
    /* waiting tsc hw for idle status */
    timeout = 0;
    do
    {
        __TSC_HW_DISABLE();
        
        if(++timeout > TSC_TIMEOUT)
            return TSC_ERROR_HW_MODE;
			
    }while (__TSC_GET_HW_MODE());

    /* Mask invalid bits */
    chn = Channels & TSC_CHNEN_CHN_SEL_ALL_Msk;
    
    /* Set the base and delta for each channel one by one */
    for (i = 0; i < MAX_TSC_HW_CHN; i++)
    {
        if (chn & 0x00000001)
        {
            TSC->THRHD[i] = (base << TSC_THRHD0_BASE0_Pos) | (delta << TSC_THRHD0_DELTA0_Pos);
        }

        chn >>= 1;
    }

    return TSC_ERROR_OK;
}

/**
 * @brief  Configure channel parameters by channel or operation.Support configure several channels at the same time.
 * @param  ChnCfg Channel parameters.
 * @param  Channels Set the channels.
 * @return TSC error code
 */
TSC_ErrorTypeDef TSC_ConfigChannel(uint32_t Channels, TSC_ChnCfg* ChnCfg)
{
	TSC_ErrorTypeDef rtn;

    assert_param(IS_TSC_CHN(Channels));
	assert_param(IS_TSC_PTR_NONNULL(ChnCfg));

    /* Set resistance */
    rtn = TSC_ConfigInternalResistor(Channels, (uint32_t)ChnCfg->TSC_Resistor);
    if(rtn != TSC_ERROR_OK)
    {
    	return rtn;
    }
    /* Set the threshold of base and delta */
    rtn = TSC_ConfigThreshold(Channels, (uint32_t)ChnCfg->TSC_Base, (uint32_t)ChnCfg->TSC_Delta);

    return rtn;
}

/**
 * @brief  Get parameters of one channel.
 * @param  ChnCfg: Pointer of TSC_ChnCfg structure.
 * @param  ChannelNum: The channel number of which we want to get parameters,must be less then MAX_TSC_HW_CHN
 * @return: TSC error code
 */
TSC_ErrorTypeDef TSC_GetChannelCfg(uint32_t ChannelNum,TSC_ChnCfg* ChnCfg)
{
    uint32_t nReg;
    uint32_t nPos;

    assert_param(IS_TSC_CHN_NUMBER(ChannelNum));
    assert_param(IS_TSC_PTR_NONNULL(ChnCfg));

    /* Get the base and delta value for a channel */
    ChnCfg->TSC_Base     = (TSC->THRHD[ChannelNum] & TSC_THRHD0_BASE0_Msk)  >> TSC_THRHD0_BASE0_Pos;
    ChnCfg->TSC_Delta    = (TSC->THRHD[ChannelNum] & TSC_THRHD0_DELTA0_Msk) >> TSC_THRHD0_DELTA0_Pos;

    /* Get the charge resistor type for a channel */
    nReg = ChannelNum >> 3;
    nPos = (ChannelNum & 0x7UL) * 4;
    ChnCfg->TSC_Resistor = (TSC->RESR[nReg] >> nPos) & TSC_RESR0_CHN_RESIST0_Msk;

    return TSC_ERROR_OK;
}

/**
 * @brief  Enable/Disable hardware detection.
 * @param  Channels Set the channel.
 * @param  Cmd ENABLE:Enable hardware detection,DISALBE:Disable hardware detection.
 * @note You can only output one channel at a time.
 * @return TSC error code
 */
TSC_ErrorTypeDef TSC_ConfigHWMode(uint32_t Channels, FunctionalState Cmd)
{
	uint32_t timeout;
	assert_param(IS_TSC_CHN(Channels));

    if (Cmd != DISABLE)
    {
        /* Enable tsc channel */
        __TSC_CHN_CONFIG(Channels);

        /* Enable the TSC */
        __TSC_HW_ENABLE();
    }
    else
    {
    	timeout = 0;

        /* Disable the TSC */
        do
        {
            __TSC_HW_DISABLE();

            if(++timeout > TSC_TIMEOUT)
            	return TSC_ERROR_HW_MODE;
        }while (__TSC_GET_HW_MODE());

        __TSC_CHN_CONFIG(0);
    }

    return TSC_ERROR_OK;
}

/**
 * @brief  Toggle channels to output to TIMER2/TIMER4 by software mode.
 * @param  ChannelNum Set the channel.
 * @param  OutDir Set the TSC_OUT to the TIM2 or TIM4 or TSC_OUT Pin��IT can be any value of @ref TSC_Out
 * @param  Cmd ENABLE:Enable software detection,DISALBE:Disable software detection.
 * @note   It can only output to TIMER2/TIMER4 by software mode.Other channels are not valid.
 * @return TSC error code
 */
TSC_ErrorTypeDef TSC_ConfigSWMode(uint32_t ChannelNum, uint32_t OutDir, FunctionalState Cmd)
{
    uint32_t i;
    uint32_t timeout;

    assert_param(IS_TSC_CHN_NUMBER(ChannelNum));
    assert_param(IS_TSC_OUT(OutDir));

    /* waiting tsc hw for idle status */
    timeout = 0;
    do
    {
        __TSC_HW_DISABLE();

        if(++timeout > TSC_TIMEOUT)
            return TSC_ERROR_HW_MODE;

    }while (__TSC_GET_HW_MODE());

    /* set TSC_OUT map and channel mux */
    __TSC_OUT_CONFIG(OutDir);
    __TSC_SW_CHN_NUM_CONFIG(ChannelNum);

    /* set SW enable bit */
    if(Cmd == ENABLE)
    {
        __TSC_SW_ENABLE();
    }
    else
    {
    	__TSC_SW_DISABLE();
    }

    /* Delay 35us for tsc channel stabilize output */
    delay_us(35);

    return TSC_ERROR_OK;
}

/**
 * @brief  Switch channel for scan channel input in SW mode
 * @param  ChannelNum Set the channel.
 * @note   It can only output to TIMER2/TIMER4 by software mode.Other channels are not valid.
 * @return TSC error code
 */
TSC_ErrorTypeDef TSC_SwitchChannel(uint32_t ChannelNum)
{
    uint32_t i;

    assert_param(IS_TSC_CHN_NUMBER(ChannelNum));

    /* waiting tsc hw for idle status */
    __TSC_SW_CHN_NUM_CONFIG(ChannelNum);

    /* Delay time for tsc channel stabilize output */
    delay_us(30);

    return TSC_ERROR_OK;
}

/**
 * @brief  Get TSC status value.
 * @param  type TSC status type.
 * @return TSC status data
 */
uint32_t TSC_GetStatus(TSC_Status type)
{
    uint32_t value;

    assert_param(IS_TSC_STS_TPYE(type));

	switch (type)
	{
	case TSC_STS_TYP_CNTVALUE:
		value = __TSC_GET_CHN_CNT();
		break;

	case TSC_STS_TYP_LESS_DET:
		value = __TSC_GET_HW_DET_TYPE(TSC_FLAG_LESS_DET);
		break;

	case TSC_STS_TYP_GREAT_DET:
		value = __TSC_GET_HW_DET_TYPE(TSC_FLAG_GREAT_DET);
		break;

	case TSC_STS_TYP_CHN_NUM:
		value = __TSC_GET_CHN_NUMBER();
		break;

	case TSC_STS_TYP_DET_ST:
		value = __TSC_GET_HW_MODE();
		break;

	default:
		value = 0;
		break;
	}

    return value;
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
