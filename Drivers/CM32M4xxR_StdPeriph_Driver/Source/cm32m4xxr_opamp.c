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
 * @file cm32m4xxr_opamp.c
 * @author CMIOT Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */
#include "nuclei_sdk_soc.h"

/** @addtogroup CM32M4xxR_StdPeriph_Driver
 * @{
 */

/** @addtogroup OPAMP
 * @brief OPAMP driver modules
 * @{
 */

#ifdef	DRIVER_MODULE_ENABLED_OPAMP


/** @addtogroup OPAMP_Exported_Functions
 * @{
 */

/**
 * @brief  Deinitializes the OPAMP peripheral registers to their default reset values.
 */
void OPAMP_DeInit(void)
{
	OPAMP->CS1 = 0;
	OPAMP->CS2 = 0;
	OPAMP->CS3 = 0;
	OPAMP->CS4 = 0;
	OPAMP->LOCK = 0;
}

/**
 * @brief Fills OPAMP_InitStruct member with its default value.
 * @param OPAMP_InitStruct pointer to a OPAMP_InitType structure which will be
 *         initialized.
 */
void OPAMP_StructInit(OPAMP_InitType* OPAMP_InitStruct)
{
	assert_param(OPAMP_InitStruct);

    OPAMP_InitStruct->Gain           = OPAMP_CS_PGA_GAIN_2;
    OPAMP_InitStruct->HighVolRangeEn = ENABLE;
    OPAMP_InitStruct->TimeAutoMuxEn  = DISABLE;
    OPAMP_InitStruct->Mod            = OPAMP_CS_PGA_EN;
}

/**
 * @brief  Initializes the OPAMP (specified by OPAMPx) registers according to the specified parameters
 *         in OPAMP_InitStruct.
 * @param  OPAMPx where x can be 1 to 4 to select the OPAMP
 * @param  OPAMP_InitStruct pointer to a OPAMP_InitType structure that contains
 *         the configuration information for the OPAMP peripheral.
 */
void OPAMP_Init(OPAMP_PeriphType OPAMPx, OPAMP_InitType* OPAMP_InitStruct)
{
    __IO uint32_t* pCs = &OPAMP->CS1 + OPAMPx;
    __IO uint32_t tmpregister  = *pCs;

    assert_param(OPAMP_InitStruct);

    MODIFY_REG(tmpregister, OPAMP_CS_PGAGAN, OPAMP_InitStruct->Gain);
	
	if(OPAMP_InitStruct->HighVolRangeEn == ENABLE)
        MODIFY_REG(tmpregister, OPAMP_CS_RANGE, OPAMP_CS_RANGE);
    else
        CLEAR_BIT(tmpregister, OPAMP_CS_RANGE);

    if(OPAMP_InitStruct->TimeAutoMuxEn == ENABLE)
        MODIFY_REG(tmpregister, OPAMP_CS_TCMEN, OPAMP_CS_TCMEN);
    else
        CLEAR_BIT(tmpregister, OPAMP_CS_TCMEN);

    MODIFY_REG(tmpregister, OPAMP_CS_MOD, OPAMP_InitStruct->Mod);
    
	*pCs = tmpregister;
}

/**
 * @brief Enables or disables the specified OPAMP.
 * @param OPAMPx where x can 1 to 4 to select the OPAMP to be configured.
 * @param Cmd new state of the specified OPAMP.
 *   This parameter can be: ENABLE or DISABLE.
 */
void OPAMP_Enable(OPAMP_PeriphType OPAMPx, FunctionalState Cmd)
{
    __IO uint32_t* pCs = &OPAMP->CS1 + OPAMPx;
	
    if (Cmd)
        SET_BIT(*pCs, OPAMP_CS_EN);
    else
        CLEAR_BIT(*pCs, OPAMP_CS_EN);
}

/**
 * @brief Configure PGA gain of the specified OPAMP.
 * @param OPAMPx where x can 1 to 4 to select the OPAMP to be configured.
 * @param Gain PGA gain, see @ref OPAMP_CS_PGA_GAIN_Type.
 */
void OPAMP_SetPgaGain(OPAMP_PeriphType OPAMPx, OPAMP_CS_PGA_GAIN_Type Gain)
{
    __IO uint32_t* pCs = &OPAMP->CS1 + OPAMPx;
    __IO uint32_t tmpregister  = *pCs;
	
    MODIFY_REG(tmpregister, OPAMP_CS_PGAGAN, Gain);
    *pCs = tmpregister;
}

/**
 * @brief Configure non inverted input secondary selection of the specified OPAMP.
 * @param OPAMPx where x can 1 to 4 to select the OPAMP to be configured.
 * @param VpSSel Non inverted input secondary selection, see @ref OPAMP_CS_VPSSEL_Type.
 */
void OPAMP_SetVpSecondSel(OPAMP_PeriphType OPAMPx, OPAMP_CS_VPSSEL_Type VpSSel)
{
    __IO uint32_t* pCs = &OPAMP->CS1 + OPAMPx;
    __IO uint32_t tmpregister  = *pCs;
	
    MODIFY_REG(tmpregister, OPAMP_CS_VPSSEL, VpSSel);
    *pCs = tmpregister;
}

/**
 * @brief Configure inverted input secondary selection of the specified OPAMP.
 * @param OPAMPx where x can 1 to 4 to select the OPAMP to be configured.
 * @param VmSSel inverted input secondary selection, see @ref OPAMP_CS_VMSSEL_Type.
 */
void OPAMP_SetVmSecondSel(OPAMP_PeriphType OPAMPx, OPAMP_CS_VMSSEL_Type VmSSel)
{
    __IO uint32_t* pCs = &OPAMP->CS1 + OPAMPx;
    __IO uint32_t tmpregister  = *pCs;
	
    MODIFY_REG(tmpregister, OPAMP_CS_VMSSEL, VmSSel);
    *pCs = tmpregister;
}

/**
 * @brief Configure non inverted input selection of the specified OPAMP.
 * @param OPAMPx where x can 1 to 4 to select the OPAMP to be configured.
 * @param VpSel non inverted input selection, see @ref OPAMP_CS_VPSEL_Type.
 */
void OPAMP_SetVpSel(OPAMP_PeriphType OPAMPx, OPAMP_CS_VPSEL_Type VpSel)
{
    __IO uint32_t* pCs = &OPAMP->CS1 + OPAMPx;
    __IO uint32_t tmpregister  = *pCs;
	
    MODIFY_REG(tmpregister, OPAMP_CS_VPSEL, VpSel);
    *pCs = tmpregister;
}

/**
 * @brief Configure inverted input selection of the specified OPAMP.
 * @param OPAMPx where x can 1 to 4 to select the OPAMP to be configured.
 * @param VmSel inverted input selection, see @ref OPAMP_CS_VMSEL_Type.
 */
void OPAMP_SetVmSel(OPAMP_PeriphType OPAMPx, OPAMP_CS_VMSEL_Type VmSel)
{
    __IO uint32_t* pCs = &OPAMP->CS1 + OPAMPx;
    __IO uint32_t tmpregister  = *pCs;
	
    MODIFY_REG(tmpregister, OPAMP_CS_VMSEL, VmSel);
    *pCs = tmpregister;
}

/**
 * @brief Get operation amplifier calibration output status of the specified OPAMP.
 * @param OPAMPx where x can 1 to 4 to select the OPAMP to be configured.
 * @retval The operation amplifier calibration output status.
 * true output high
 * false output low
 */
bool OPAMP_IsCalOutHigh(OPAMP_PeriphType OPAMPx)
{
    __IO uint32_t* pCs = &OPAMP->CS1 + OPAMPx;
	
    return (READ_BIT(*pCs, OPAMP_CS_CALOUT)) ? true : false;
}

/**
 * @brief Enables or disables calibration mode of the specified OPAMP.
 * @param OPAMPx where x can 1 to 4 to select the OPAMP to be configured.
 * @param Cmd new state of the specified OPAMP.
 *   This parameter can be: ENABLE or DISABLE.
 */
void OPAMP_CalibrationEnable(OPAMP_PeriphType OPAMPx, FunctionalState Cmd)
{
    __IO uint32_t* pCs = &OPAMP->CS1 + OPAMPx;
	
    if (Cmd)
        SET_BIT(*pCs, OPAMP_CS_CALON);
    else
        CLEAR_BIT(*pCs, OPAMP_CS_CALON);
}

/**
 * @brief Lock OPAMP registers for read only.
 * @param Lock the lock bit of corresponding OPAMP.
 *   This parameter can be any combination of the following values:
 *     @arg OPAMP_LOCK_OPAMP1LK to lock OPAMP1.
 *     @arg OPAMP_LOCK_OPAMP2LK to lock OPAMP2.
 *     @arg OPAMP_LOCK_OPAMP3LK to lock OPAMP3.
 *     @arg OPAMP_LOCK_OPAMP4LK to lock OPAMP4.
 */
void OPAMP_SetLock(uint32_t Lock)
{
    OPAMP->LOCK = Lock;
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
