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
 * @file cm32m4xxr_bkp.c
 * @author CMIOT Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */
#include "nuclei_sdk_soc.h"


/** @addtogroup CM32M4xxR_StdPeriph_Driver
 * @{
 */

/** @defgroup BKP BKP
 * @brief BKP driver modules
 * @{
 */

#ifdef	DRIVER_MODULE_ENABLED_BKP


/** @defgroup BKP_Private_Constants BKP Private Constants
 * @{
 */
#define BKP_CTRL_ADDR			(BKP_BASE + 0x30UL)	/* BKP_CTRL register address */
#define BKP_CSTS_ADDR			(BKP_BASE + 0x34UL)	/* BKP_CSTS register address */


/**
 * @}
 */




/** @addtogroup BKP_Exported_Functions
 * @{
 */

/**
 * @brief  Deinitializes the BKP peripheral registers to their default reset values.
 */
void BKP_DeInit(void)
{
	/* Reset backup domain */
    RCC_EnableBackupReset(ENABLE);
    RCC_EnableBackupReset(DISABLE);
}

/**
 * @brief  Configures the Tamper Pin active level.
 * @param BKP_TamperPinLevel specifies the Tamper Pin active level.
 *   This parameter can be one of the following values:
 *     @arg BKP_TP_HIGH Tamper pin active on high level
 *     @arg BKP_TP_LOW Tamper pin active on low level
 */
void BKP_ConfigTPLevel(uint16_t BKP_TamperPinLevel)
{
    /* Check the parameters */
    assert_param(IS_BKP_TP_LEVEL(BKP_TamperPinLevel));
	
	if(BKP_TP_HIGH == BKP_TamperPinLevel){
		__AMOAND_W((__IO int32_t *)BKP_CTRL_ADDR, ~BKP_CTRL_TP_ALEV_Msk); /* Atomic AND operation */
	}else{
		__AMOOR_W((__IO int32_t *)BKP_CTRL_ADDR, BKP_CTRL_TP_ALEV_Msk);	/* Atomic OR operation */
	}
}

/**
 * @brief  Enables or disables the Tamper Pin activation.
 * @param Cmd new state of the Tamper Pin activation.
 *   This parameter can be: ENABLE or DISABLE.
 */
void BKP_TPEnable(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
	
	if(ENABLE == Cmd){
		__AMOOR_W((__IO int32_t *)BKP_CTRL_ADDR, BKP_CTRL_TP_EN_Msk);
	}else{
		__AMOAND_W((__IO int32_t *)BKP_CTRL_ADDR, ~BKP_CTRL_TP_EN_Msk);
	}
}

/**
 * @brief  Enables or disables the Tamper Pin Interrupt.
 * @param Cmd new state of the Tamper Pin Interrupt.
 *   This parameter can be: ENABLE or DISABLE.
 */
void BKP_TPIntEnable(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
	
	if(ENABLE == Cmd){
		__AMOOR_W((__IO int32_t *)BKP_CSTS_ADDR, BKP_CSTS_TPINT_EN_Msk);
	}else{
		__AMOAND_W((__IO int32_t *)BKP_CSTS_ADDR, ~BKP_CSTS_TPINT_EN_Msk);
	}
}


/**
 * @brief  Writes user data to the specified Data Backup Register.
 * @param BKP_DAT specifies the Data Backup Register.
 *   This parameter can be BKP_DATx where x:[1, 42]
 * @param Data data to write
 */
void BKP_WriteBkpData(uint16_t BKP_DAT, uint16_t Data)
{
    __IO uint32_t tmp = 0;

    /* Check the parameters */
    assert_param(IS_BKP_DAT(BKP_DAT));

    tmp = (uint32_t)BKP_BASE;
    tmp += (uint32_t)BKP_DAT;

    *(__IO uint32_t*)tmp = (uint32_t)Data;
}

/**
 * @brief  Reads data from the specified Data Backup Register.
 * @param BKP_DAT specifies the Data Backup Register.
 *   This parameter can be BKP_DATx where x:[1, 42]
 * @retval The content of the specified Data Backup Register
 */
uint16_t BKP_ReadBkpData(uint16_t BKP_DAT)
{
    __IO uint32_t tmp = 0;

    /* Check the parameters */
    assert_param(IS_BKP_DAT(BKP_DAT));

    tmp = (uint32_t)BKP_BASE;
    tmp += (uint32_t)BKP_DAT;

    return (*(__IO uint16_t*) tmp);
}

/**
 * @brief  Checks whether the Tamper Pin Event flag is set or not.
 * @retval The new state of the Tamper Pin Event flag (SET or RESET).
 */
FlagStatus BKP_GetTEFlag(void)
{
	FlagStatus ef = (FlagStatus)(((uint32_t)BKP->CSTS & BKP_CSTS_TEF_Msk) >> BKP_CSTS_TEF_Pos);
	
    return ef;
}

/**
 * @brief  Clears Tamper Pin Event pending flag.
 */
void BKP_ClrTEFlag(void)
{
    /* Set CTE bit to clear Tamper Pin Event flag */
    BKP->CSTS |= ((uint16_t) BKP_CSTS_CLRTE);
}

/**
 * @brief  Checks whether the Tamper Pin Interrupt has occurred or not.
 * @retval The new state of the Tamper Pin Interrupt (SET or RESET).
 */
INTStatus BKP_GetTINTFlag(void)
{
	INTStatus intf = (INTStatus)(((uint32_t)BKP->CSTS & BKP_CSTS_TINTF_Msk) >> BKP_CSTS_TINTF_Pos);
	
    return intf;
}

/**
 * @brief  Clears Tamper Pin Interrupt pending bit.
 */
void BKP_ClrTINTFlag(void)
{
    /* Set CTI bit to clear Tamper Pin Interrupt pending bit */
    BKP->CSTS |= ((uint16_t) BKP_CSTS_CLRTINT);
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
