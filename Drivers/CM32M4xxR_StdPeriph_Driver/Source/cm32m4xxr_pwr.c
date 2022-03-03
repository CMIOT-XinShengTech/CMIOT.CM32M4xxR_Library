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
 * @file cm32m4xxr_pwr.c
 * @author CMIOT Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */
#include "nuclei_sdk_soc.h"


/** @addtogroup CM32M4xxR_StdPeriph_Driver
 * @{
 */

/** @defgroup PWR PWR
 * @brief PWR driver modules
 * @{
 */

#ifdef	DRIVER_MODULE_ENABLED_PWR

/** @defgroup PWR_Exported_Functions PWR Exported Functions
 * @{
 */

/**
 * @brief  Deinitializes the PWR peripheral registers to their default reset values.
 */
void PWR_DeInit(void)
{
	/* Reset PWR */
    RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_PWR, ENABLE);
    RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_PWR, DISABLE);
}

/**
 * @brief Enables or disables access to the RTC and backup registers.
 * @param Cmd new state of the access to the RTC and backup registers.
 *   This parameter can be: ENABLE or DISABLE.
 */
void PWR_BackupAccessEnable(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

	if(ENABLE == Cmd){
		__AMOOR_W((__IO int32_t *)(&(PWR->CTRL)), PWR_CTRL_DBKP); /* Atomic OR operation */
	}else{
		__AMOAND_W((__IO int32_t *)(&(PWR->CTRL)), ~PWR_CTRL_DBKP); /* Atomic AND operation */
	}
}

/**
 * @brief Enables or disables the Power Voltage Detector(PVD).
 * @param Cmd new state of the PVD.
 *   This parameter can be: ENABLE or DISABLE.
 */
void PWR_PvdEnable(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
	
	if(ENABLE == Cmd){
		__AMOOR_W((__IO int32_t *)(&(PWR->CTRL)), PWR_CTRL_PVDEN);
	}else{
		__AMOAND_W((__IO int32_t *)(&(PWR->CTRL)), ~PWR_CTRL_PVDEN);
	}
}

/**
 * @brief  Configures the voltage threshold detected by the Power Voltage Detector(PVD).
 * @param PWR_PVDLevel specifies the PVD detection level
 *   This parameter can be one of the following values:
 *	   MSB = 0:
 *     @arg PWR_PVDRANGRE_2V2 PVD detection level set to 2.2V
 *     @arg PWR_PVDRANGRE_2V3 PVD detection level set to 2.3V
 *     @arg PWR_PVDRANGRE_2V4 PVD detection level set to 2.4V
 *     @arg PWR_PVDRANGRE_2V5 PVD detection level set to 2.5V
 *     @arg PWR_PVDRANGRE_2V6 PVD detection level set to 2.6V
 *     @arg PWR_PVDRANGRE_2V7 PVD detection level set to 2.7V
 *     @arg PWR_PVDRANGRE_2V8 PVD detection level set to 2.8V
 *     @arg PWR_PVDRANGRE_2V9 PVD detection level set to 2.9V
 *	   MSB = 1:
 *     @arg PWR_PVDRANGE_1V78 PVD detection level set to 1.78V
 *     @arg PWR_PVDRANGE_1V88 PVD detection level set to 1.88V
 *     @arg PWR_PVDRANGE_1V98 PVD detection level set to 1.98V
 *     @arg PWR_PVDRANGE_2V08 PVD detection level set to 2.08V
 *     @arg PWR_PVDRANGE_3V06 PVD detection level set to 3.06V
 *     @arg PWR_PVDRANGE_3V24 PVD detection level set to 3.24V
 *     @arg PWR_PVDRANGE_3V42 PVD detection level set to 3.42V
 *     @arg PWR_PVDRANGE_3V60 PVD detection level set to 3.60V
 */
void PWR_PvdRangeConfig(uint32_t PWR_PVDLevel)
{
    uint32_t tmpregister = 0;
	
    /* Check the parameters */
    assert_param(IS_PWR_PVD_LEVEL(PWR_PVDLevel));
	
    tmpregister = PWR->CTRL;
	
    /* Clear PRS[7:5] bits */
    tmpregister &= ~(PWR_CTRL_PRS | PWR_CTRL_MSB); //EXMODE bit set in SystemInit function
	
    /* Set PRS[7:5] bits according to PWR_PVDLevel value */
    tmpregister |= PWR_PVDLevel;
	
    /* Store the new value */
    PWR->CTRL = tmpregister;
}

/**
 * @brief  Enables or disables the WakeUp Pin functionality.
 * @param Cmd new state of the WakeUp Pin functionality.
 *   This parameter can be: ENABLE or DISABLE.
 */
void PWR_WakeUpPinEnable(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
	
	if(ENABLE == Cmd){
		__AMOOR_W((__IO int32_t *)(&(PWR->CTRLSTS)), PWR_CTRLSTS_WKUPEN);
	}else{
		__AMOAND_W((__IO int32_t *)(&(PWR->CTRLSTS)), ~PWR_CTRLSTS_WKUPEN);
	}
}

/**
 * @brief  Enters SLEEP mode.
 * @param PWR_STOPEntry specifies if SLEEP mode in entered with WFI or WFE instruction.
 *   This parameter can be one of the following values:
 *     @arg PWR_STOPENTRY_WFI enter SLEEP mode with WFI instruction
 *     @arg PWR_STOPENTRY_WFE enter SLEEP mode with WFE instruction
 */
void PWR_EnterSLEEPMode(uint8_t PWR_STOPEntry)
{	
    /* Check the parameters */
    assert_param(IS_PWR_STOP_ENTRY(PWR_STOPEntry));

    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_PWR, ENABLE);
    PWR->CTRL2 &= ~PWR_CTRL2_STOP2S;

	/* Shallow sleep mode */
	__set_wfi_sleepmode(WFI_SHALLOW_SLEEP);

    /* Select SLEEP mode entry */
    if (PWR_STOPEntry == PWR_STOPENTRY_WFI)
    {
        /* Request Wait For Interrupt */
        __WFI();
    }
    else
    {
        /* Request Wait For Event */
        __WFE();
    }
}

/**
 * @brief  Enters STOP mode.
 * @param PWR_Regulator specifies the regulator state in STOP mode.
 *   This parameter can be one of the following values:
 *     @arg PWR_REGULATOR_ON STOP mode with regulator ON
 *     @arg PWR_REGULATOR_LOWPOWER STOP mode with regulator in low power mode
 * @param PWR_STOPEntry specifies if STOP mode in entered with WFI or WFE instruction.
 *   This parameter can be one of the following values:
 *     @arg PWR_STOPENTRY_WFI enter STOP mode with WFI instruction
 *     @arg PWR_STOPENTRY_WFE enter STOP mode with WFE instruction
 */
void PWR_EnterStopState(uint32_t PWR_Regulator, uint8_t PWR_STOPEntry)
{
    uint32_t tmpregister = 0;
	
    /* Check the parameters */
    assert_param(IS_PWR_REGULATOR(PWR_Regulator));
    assert_param(IS_PWR_STOP_ENTRY(PWR_STOPEntry));

    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_PWR, ENABLE);
    PWR->CTRL2 &= ~PWR_CTRL2_STOP2S;

    /* Select the regulator state in STOP mode ---------------------------------*/
    tmpregister = PWR->CTRL;
	
    /* Clear PDS and LPS bits */
    tmpregister &= ~(PWR_CTRL_LPS | PWR_CTRL_PDS);
	
    /* Set LPS bit according to PWR_Regulator value */
    tmpregister |= PWR_Regulator;
	
    /* Store the new value */
    PWR->CTRL = tmpregister;
	
	/* Deep sleep mode */
	__set_wfi_sleepmode(WFI_DEEP_SLEEP);

    /* Select STOP mode entry --------------------------------------------------*/
    if (PWR_STOPEntry == PWR_STOPENTRY_WFI)
    {
        /* Request Wait For Interrupt */
        __WFI();
    }
    else
    {
        /* Request Wait For Event */
        __WFE();
    }

    /* Reset SLEEPVALUE bit of sleepvalue csr after wakeup */
	__set_wfi_sleepmode(WFI_SHALLOW_SLEEP);
}

/**
 * @brief  Enters STOP2 mode.
 * @param PWR_STOPEntry specifies if STOP2 mode in entered with WFI or WFE instruction.
 *   This parameter can be one of the following values:
 *     @arg PWR_STOPENTRY_WFI enter STOP2 mode with WFI instruction
 *     @arg PWR_STOPENTRY_WFE enter STOP2 mode with WFE instruction
 */
void PWR_EnterSTOP2Mode(uint8_t PWR_STOPEntry)
{
    uint32_t tmpregister = 0;
	
    /* Check the parameters */
    assert_param(IS_PWR_STOP_ENTRY(PWR_STOPEntry));

    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_PWR, ENABLE);
    PWR->CTRL2 &= ~PWR_CTRL2_STOP2S;

    /* Select the regulator state in STOP2 mode ---------------------------------*/
    tmpregister = PWR->CTRL;
	
    /* Clear PDS and LPS bits */
    tmpregister &= ~(PWR_CTRL_LPS | PWR_CTRL_PDS);
	
    /* Store the new value */
    PWR->CTRL = tmpregister;
	
    /* STOP2 sleep mode control-stop2s */
    PWR->CTRL2 |= PWR_CTRL2_STOP2S;
	
	/* Deep sleep mode */
	__set_wfi_sleepmode(WFI_DEEP_SLEEP);
	
    /* Select STOP mode entry --------------------------------------------------*/
    if (PWR_STOPEntry == PWR_STOPENTRY_WFI)
    {
        /* Request Wait For Interrupt */
        __WFI();
    }
    else
    {
        /* Request Wait For Event */
        __WFE();
    }

    /* Reset SLEEPVALUE bit of sleepvalue csr after wakeup */
	__set_wfi_sleepmode(WFI_SHALLOW_SLEEP);
}

/**
 * @brief  Enters STANDBY mode.
 */
void PWR_EnterStandbyState(void)
{

    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_PWR, ENABLE);
    PWR->CTRL2 &= ~PWR_CTRL2_STOP2S;

    /* Clear Wake-up flag */
    PWR->CTRL |= PWR_CTRL_CWKUP;
	
    /* Clear PDS and LPS bits */
    PWR->CTRL &= ~(PWR_CTRL_LPS | PWR_CTRL_PDS);
	
    /* Select STANDBY mode */
    PWR->CTRL |= PWR_CTRL_PDS;
	
	/* Deep sleep mode */
	__set_wfi_sleepmode(WFI_DEEP_SLEEP);

    /* Request Wait For Interrupt */
    __WFI();
}

/**
 * @brief  Checks whether the specified PWR flag is set or not.
 * @param PWR_FLAG specifies the flag to check.
 *   This parameter can be one of the following values:
 *     @arg PWR_WU_FLAG Wake Up flag
 *     @arg PWR_SB_FLAG StandBy flag
 *     @arg PWR_PVDO_FLAG PVD Output
 *     @arg PWR_VBATF_FLAG VBAT flag
 * @retval The new state of PWR_FLAG (SET or RESET).
 */
FlagStatus PWR_GetFlagStatus(uint32_t PWR_FLAG)
{
    FlagStatus bitstatus = RESET;
	
    /* Check the parameters */
    assert_param(IS_PWR_GET_FLAG(PWR_FLAG));

    if ((PWR->CTRLSTS & PWR_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
	
    /* Return the flag status */
    return bitstatus;
}

/**
 * @brief  Clears the PWR's pending flags.
 * @param PWR_FLAG specifies the flag to clear.
 *   This parameter can be one of the following values:
 *     @arg PWR_WU_FLAG Wake Up flag
 *     @arg PWR_SB_FLAG StandBy and VBAT flag
 */
void PWR_ClearFlag(uint32_t PWR_FLAG)
{
    /* Check the parameters */
    assert_param(IS_PWR_CLEAR_FLAG(PWR_FLAG));

    PWR->CTRL |= (PWR_FLAG << 2);
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
