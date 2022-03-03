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
 * @file cm32m4xxr_iwdg.c
 * @author CMIOT Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */
#include "nuclei_sdk_soc.h"

/** @addtogroup CM32M4xxR_StdPeriph_Driver
 * @{
 */

/** @addtogroup IWDG
 * @brief IWDG driver modules
 * @{
 */

#ifdef	DRIVER_MODULE_ENABLED_IWDG


/** @defgroup IWDG_Private_Constants IWDG Private Constants
 * @{
 */

/* KEY register bit mask */
#define KEY_ReloadKey	((uint16_t) 0xAAAA)	/* Write the value to KEY register to reload iwdg counter */
#define KEY_EnableKey	((uint16_t) 0xCCCC)	/* Write the value to KEY register to enable iwdg */

/**
 * @}
 */


/** @addtogroup IWDG_Exported_Functions
 * @{
 */

/**
 * @brief  Enables or disables write access to IWDG_PREDIV and IWDG_RELV registers.
 * @param IWDG_WriteAccess new state of write access to IWDG_PREDIV and IWDG_RELV registers.
 *   This parameter can be one of the following values:
 *     @arg IWDG_WRITE_ENABLE Enable write access to IWDG_PREDIV and IWDG_RELV registers
 *     @arg IWDG_WRITE_DISABLE Disable write access to IWDG_PREDIV and IWDG_RELV registers
 */
void IWDG_WriteConfig(uint16_t IWDG_WriteAccess)
{
    /* Check the parameters */
    assert_param(IS_IWDG_WRITE(IWDG_WriteAccess));
	
    IWDG->KEY = IWDG_WriteAccess;
}

/**
 * @brief  Sets IWDG Prescaler value.
 * @param IWDG_Prescaler specifies the IWDG Prescaler value.
 *   This parameter can be one of the following values:
 *     @arg IWDG_PRESCALER_DIV4 IWDG prescaler set to 4
 *     @arg IWDG_PRESCALER_DIV8 IWDG prescaler set to 8
 *     @arg IWDG_PRESCALER_DIV16 IWDG prescaler set to 16
 *     @arg IWDG_PRESCALER_DIV32 IWDG prescaler set to 32
 *     @arg IWDG_PRESCALER_DIV64 IWDG prescaler set to 64
 *     @arg IWDG_PRESCALER_DIV128 IWDG prescaler set to 128
 *     @arg IWDG_PRESCALER_DIV256 IWDG prescaler set to 256
 */
void IWDG_SetPrescalerDiv(uint8_t IWDG_Prescaler)
{
    /* Check the parameters */
    assert_param(IS_IWDG_PRESCALER_DIV(IWDG_Prescaler));
	
    IWDG->PREDIV = IWDG_Prescaler;
}

/**
 * @brief  Sets IWDG Reload value.
 * @param Reload specifies the IWDG Reload value.
 *   This parameter must be a number between 0 and 0x0FFF.
 */
void IWDG_CntReload(uint16_t Reload)
{
    /* Check the parameters */
    assert_param(IS_IWDG_RELOAD(Reload));
	
    IWDG->RELV = Reload;
}

/**
 * @brief  Reloads IWDG counter with value defined in the reload register
 *   (write access to IWDG_PREDIV and IWDG_RELV registers disabled).
 */
void IWDG_ReloadKey(void)
{
    IWDG->KEY = KEY_ReloadKey;
}

/**
 * @brief  Enables IWDG (write access to IWDG_PREDIV and IWDG_RELV registers disabled).
 */
void IWDG_Enable(void)
{
    IWDG->KEY = KEY_EnableKey;
}

/**
 * @brief  Checks whether the specified IWDG flag is set or not.
 * @param IWDG_FLAG specifies the flag to check.
 *   This parameter can be one of the following values:
 *     @arg IWDG_PVU_FLAG Prescaler Value Update on going
 *     @arg IWDG_CRVU_FLAG Reload Value Update on going
 * @retval The new state of IWDG_FLAG (SET or RESET).
 */
FlagStatus IWDG_GetStatus(uint16_t IWDG_FLAG)
{
    FlagStatus bitstatus = RESET;
	
    /* Check the parameters */
    assert_param(IS_IWDG_FLAG(IWDG_FLAG));
	
    if ((IWDG->STS & IWDG_FLAG) != (uint32_t)RESET)
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
 * @}
 */

#endif

/**
 * @}
 */

/**
 * @}
 */
