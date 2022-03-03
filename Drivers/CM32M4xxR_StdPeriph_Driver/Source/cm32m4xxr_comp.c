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
 * @file cm32m4xxr_comp.c
 * @author CMIOT Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */
#include "nuclei_sdk_soc.h"


/** @addtogroup CM32M4xxR_StdPeriph_Driver
 * @{
 */

/** @addtogroup COMP
 * @brief COMP driver modules
 * @{
 */

#ifdef	DRIVER_MODULE_ENABLED_COMP

/** @addtogroup COMP_Exported_Functions
 * @{
 */

/**
 * @brief  Deinitializes the COMP peripheral registers to their default reset values.
 */
void COMP_DeInit(void)
{
	COMP->LOCK = 0;
	for(int i=COMP1;i<COMP7;i++)
	{
		COMP->Cmp[i].CTRL = 0;
		COMP->Cmp[i].FILC = 0;
		COMP->Cmp[i].FILP = 0;
	}
	COMP->WINMODE = 0;
	COMP->INTEN = 0;
	COMP->INTSTS = 0;
	COMP->VREFSCL = 0;
}

/**
 * @brief Fills COMP_InitStruct member with its default value.
 * @param COMP_InitStruct pointer to a COMP_InitType structure which will be
 *         initialized.
 */
void COMP_StructInit(COMP_InitType* COMP_InitStruct)
{
	assert_param(COMP_InitStruct);

    COMP_InitStruct->InpDacConnect = false; 		/* only COMP1 have this bit */

    COMP_InitStruct->Blking = COMP_CTRL_BLKING_NO;	/*see @ref COMP_CTRL_BLKING_Type */

    COMP_InitStruct->Hyst = COMP_CTRL_HYST_NO;		/* see @COMP_CTRL_HYST_Type */

    COMP_InitStruct->PolRev = false;				/* out polarity reverse */

    COMP_InitStruct->OutSel = COMPX_CTRL_OUTSEL_NC;
    COMP_InitStruct->InpSel = COMPX_CTRL_INPSEL_RES;
    COMP_InitStruct->InmSel = COMPX_CTRL_INMSEL_RES;

    COMP_InitStruct->FilterEn=false;
    COMP_InitStruct->ClkPsc=0;
    COMP_InitStruct->SampWindow=0;
    COMP_InitStruct->Thresh=0;

    COMP_InitStruct->En = false;
}

/**
 * @brief  Initializes the COMP (specified by COMPx) registers according to the specified parameters
 *         in COMP_InitStruct.
 * @param  COMPx where x can be 1 to 7 to select the COMP
 * @param  COMP_InitStruct pointer to a COMP_InitType structure that contains
 *         the configuration information for the COMP peripheral.
 */
void COMP_Init(COMP_PeriphType COMPx, COMP_InitType* COMP_InitStruct)
{
    COMP_SingleType* pCS = &COMP->Cmp[COMPx];
    __IO uint32_t tmpregister;

    assert_param(COMP_InitStruct);

    /* Set filter register */
    tmpregister = pCS->FILC;
    MODIFY_REG(tmpregister, COMP_FILC_SAMPW,  COMP_InitStruct->SampWindow << 6U);
    MODIFY_REG(tmpregister, COMP_FILC_THRESH, COMP_InitStruct->Thresh     << 1U);
    MODIFY_REG(tmpregister, COMP_FILC_FILEN,  COMP_InitStruct->FilterEn   << 0U);
    pCS->FILC = tmpregister;
	
    /* Set filter psc register */
    pCS->FILP = COMP_InitStruct->ClkPsc;

    /* Set ctrl register */
    tmpregister = pCS->CTRL;
    if (COMPx == COMP1)
    {
        if (COMP_InitStruct->InpDacConnect)
            SET_BIT(tmpregister, COMP_CTRL_INPDAC);
        else
            CLEAR_BIT(tmpregister, COMP_CTRL_INPDAC);
    }
	
    MODIFY_REG(tmpregister, COMP_CTRL_BLKING, COMP_InitStruct->Blking);
    MODIFY_REG(tmpregister, COMP_CTRL_HYST, COMP_InitStruct->Hyst);
	
    if (COMP_InitStruct->PolRev)
        SET_BIT(tmpregister, COMP_CTRL_POL);
    else
        CLEAR_BIT(tmpregister, COMP_CTRL_POL);
	
    MODIFY_REG(tmpregister, COMP_CTRL_OUTTRG, COMP_InitStruct->OutSel);
    MODIFY_REG(tmpregister, COMP_CTRL_INPSEL, COMP_InitStruct->InpSel);
    MODIFY_REG(tmpregister, COMP_CTRL_INMSEL, COMP_InitStruct->InmSel);
	
    if (COMP_InitStruct->En)
        SET_BIT(tmpregister, COMP_CTRL_EN);
    else
        CLEAR_BIT(tmpregister, COMP_CTRL_EN);
	
    pCS->CTRL = tmpregister;
}

/**
 * @brief Enables or disables the specified COMP.
 * @param COMPx where x can 1 to 7 to select the COMP to be configured.
 * @param Cmd new state of the specified COMP.
 *   This parameter can be: ENABLE or DISABLE.
 */
void COMP_Enable(COMP_PeriphType COMPx, FunctionalState Cmd)
{
    if (Cmd)
        SET_BIT(COMP->Cmp[COMPx].CTRL, COMP_CTRL_EN);
    else
        CLEAR_BIT(COMP->Cmp[COMPx].CTRL, COMP_CTRL_EN);
}

/**
 * @brief Set reverse input source of the specified COMP.
 * @param COMPx where x can 1 to 7 to select the COMP to be configured.
 * @param VpSel reverse input source, see @ref COMP_CTRL_INPSEL_Type
 */
void COMP_SetInpSel(COMP_PeriphType COMPx, COMP_CTRL_INPSEL_Type VpSel)
{
    __IO uint32_t tmpregister = COMP->Cmp[COMPx].CTRL;
	
    MODIFY_REG(tmpregister, COMP_CTRL_INPSEL, VpSel);
    COMP->Cmp[COMPx].CTRL = tmpregister;
}

/**
 * @brief Set non-reverse input source of the specified COMP.
 * @param COMPx where x can 1 to 7 to select the COMP to be configured.
 * @param VmSel non-reverse input source, see @COMP_CTRL_INMSEL_Type
 */
void COMP_SetInmSel(COMP_PeriphType COMPx, COMP_CTRL_INMSEL_Type VmSel)
{
    __IO uint32_t tmpregister = COMP->Cmp[COMPx].CTRL;
	
    MODIFY_REG(tmpregister, COMP_CTRL_INMSEL, VmSel);
    COMP->Cmp[COMPx].CTRL = tmpregister;
}

/**
 * @brief Set trigger out signal destination of the specified COMP.
 * @param COMPx where x can 1 to 7 to select the COMP to be configured.
 * @param OutTrig trigger out signal destination, see @ref COMP_CTRL_OUTTRIG_Type
 */
void COMP_SetOutTrig(COMP_PeriphType COMPx, COMP_CTRL_OUTTRIG_Type OutTrig)
{
    __IO uint32_t tmpregister = COMP->Cmp[COMPx].CTRL;
	
    MODIFY_REG(tmpregister, COMP_CTRL_OUTTRG, OutTrig);
    COMP->Cmp[COMPx].CTRL = tmpregister;
}

/**
 * @brief Lock COMP registers for read only.
 * @param Lock the lock bit of corresponding COMP.
 *   This parameter can be any combination of the following values:
 *     @arg COMP_LOCK_CMP1LK to lock COMP1.
 *     @arg COMP_LOCK_CMP2LK to lock COMP2.
 *     @arg COMP_LOCK_CMP3LK to lock COMP3.
 *     @arg COMP_LOCK_CMP4LK to lock COMP4.
 *     @arg COMP_LOCK_CMP5LK to lock COMP5.
 *     @arg COMP_LOCK_CMP6LK to lock COMP6.
 *     @arg COMP_LOCK_CMP7LK to lock COMP7.
 */
void COMP_SetLock(uint32_t Lock)
{
    COMP->LOCK = Lock;
}

/**
 * @brief Enables or disables the interrupt of the specified COMP.
 * @param IntEn interrupt state(enable or disable) of the specific COMP.
 *   To enable interrupt IntEn can be any combination of the following values:
 *     @arg COMP_INTEN_CMP1IEN to enable COMP1 interrupt.
 *     @arg COMP_INTEN_CMP2IEN to enable COMP2 interrupt.
 *     @arg COMP_INTEN_CMP3IEN to enable COMP3 interrupt.
 *     @arg COMP_INTEN_CMP4IEN to enable COMP4 interrupt.
 *     @arg COMP_INTEN_CMP5IEN to enable COMP5 interrupt.
 *     @arg COMP_INTEN_CMP6IEN to enable COMP6 interrupt.
 *     @arg COMP_INTEN_CMP7IEN to enable COMP7 interrupt.
 */
void COMP_SetIntEn(uint32_t IntEn)
{
    COMP->INTEN = IntEn;
}

/**
 * @brief Get interrupt flags of all COMPs.
 * @retval The interrupt flags.
 */
uint32_t COMP_GetIntSts(void)
{
    return COMP->INTSTS;
}

/**
 * @brief Configure reference voltage of COMP.
 * @param Vv2Trim VREF2 voltage trim value.
 * @param Vv2En VREF2 state(enable or disable).
 * @param Vv1Trim VREF1 voltage trim value.
 * @param Vv1En VREF1 state(enable or disable).
 */
void COMP_SetRefScl(uint8_t Vv2Trim, bool Vv2En, uint8_t Vv1Trim, bool Vv1En)
{
    __IO uint32_t tmpregister = 0;

    assert_param(IS_COMP_VREFxSET(Vv2Trim));
    assert_param(IS_COMP_VREFxSET(Vv1Trim));

    MODIFY_REG(tmpregister, COMP_VREFSCL_VREF2SET, Vv2Trim << 8U);
    MODIFY_REG(tmpregister, COMP_VREFSCL_VREF2EN,  Vv2En   << 7U);
    MODIFY_REG(tmpregister, COMP_VREFSCL_VREF1SET, Vv1Trim << 1U);
    MODIFY_REG(tmpregister, COMP_VREFSCL_VREF1EN,  Vv1En   << 0U);

    COMP->VREFSCL = tmpregister;
}

/**
 * @brief Get output status of the specified COMP.
 * @param COMPx where x can 1 to 7 to select the COMP to be read.
 * @retval The output status.
 * SET when comp out '1'
 * RESET when comp out '0'
 */
FlagStatus COMP_GetOutStatus(COMP_PeriphType COMPx)
{
    return (COMP->Cmp[COMPx].CTRL & COMP_CTRL_OUT_Msk) ? SET : RESET;
}

/**
 * @brief Get interrupt flags of the specified COMP.
 * @param COMPx where x can 1 to 7 to select the COMP to be read.
 * @retval The interrupt flags.
 * SET when interrupt happend
 * RESET when interrupt didn't happen
 */
FlagStatus COMP_GetIntStsOneComp(COMP_PeriphType COMPx)
{
    return (COMP_GetIntSts() & (0x01UL << COMPx)) ? SET : RESET;
}

/**
 * @brief Set the COMP filter clock Prescaler value.
 * @param COMPx where x can be 1 to 7 to select the COMP peripheral.
 * @param FilPreVal Prescaler Value, Div clock = FilPreVal + 1.
 */
void COMP_SetFilterPrescaler(COMP_PeriphType COMPx , uint16_t FilPreVal)
{
    COMP->Cmp[COMPx].FILP = FilPreVal;
}

/**
 * @brief Set the COMP filter control value.
 * @param COMPx where x can be 1 to 7 to select the COMP peripheral.
 * @param FilEn 1 for enable, 0 for disable
 * @param TheresNum num under this value is noise
 * @param SampPW total sample number in a window
 */
void COMP_SetFilterControl(COMP_PeriphType COMPx, uint8_t FilEn, uint8_t TheresNum, uint8_t SampPW)
{
    COMP->Cmp[COMPx].FILC = (FilEn & COMP_FILC_FILEN_Msk) + ((TheresNum << 1) & COMP_FILC_THRESH_Msk) + ((SampPW << 6) & COMP_FILC_SAMPW_Msk);
}

/**
 * @brief Set the COMP Hyst value.
 * @param COMPx where x can be 1 to 7 to select the COMP peripheral.
 * @param HYST specifies the HYST level.
 *   This parameter can be one of the following values:
*     @arg COMP_CTRL_HYST_NO   Hyst disable
*     @arg COMP_CTRL_HYST_LOW  Hyst level 5.1mV
*     @arg COMP_CTRL_HYST_MID  Hyst level 15mV
*     @arg COMP_CTRL_HYST_HIGH Hyst level 25mV
 */
void COMP_SetHyst(COMP_PeriphType COMPx, COMP_CTRL_HYST_Type HYST)
{
    uint32_t tmpregister = COMP->Cmp[COMPx].CTRL;
    tmpregister &= (uint32_t)~COMP_CTRL_HYST;
    tmpregister |= (uint32_t)HYST;
    COMP->Cmp[COMPx].CTRL = tmpregister;
}

/**
 * @brief Set the COMP Blanking source .
 * @param COMPx where x can be 1 to 7 to select the COMP peripheral.
 * @param BLK specifies the blanking source .
 *   This parameter can be one of the following values:
*     @arg COMP_CTRL_BLKING_NO       Blanking disable
*     @arg COMP_CTRL_BLKING_TIM1_OC5 Blanking source TIM1_OC5
*     @arg COMP_CTRL_BLKING_TIM8_OC5 Blanking source TIM8_OC5
 */
void COMP_SetBlanking(COMP_PeriphType COMPx, COMP_CTRL_BLKING_Type BLK)
{
    uint32_t tmpregister = COMP->Cmp[COMPx].CTRL;
    tmpregister &= (uint32_t)~COMP_CTRL_BLKING;
    tmpregister |= (uint32_t)BLK;
    COMP->Cmp[COMPx].CTRL = tmpregister;
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
