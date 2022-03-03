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
 * @file cm32m4xxr_wwdg.c
 * @author CMIOT Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */
 #include "nuclei_sdk_soc.h"

/** @addtogroup CM32M4xxR_StdPeriph_Driver
 * @{
 */

/** @addtogroup WWDG
 * @brief WWDG driver modules
 * @{
 */

#ifdef	DRIVER_MODULE_ENABLED_WWDG

/** @defgroup WWDG_Private_Constants WWDG Private Constants
 * @{
 */

#define WWDG_CFG_ADDR		(WWDG_BASE + 0x04UL) /* WWDG_CFG Register address */


/* Enable WWDG */
#define CTRL_ACTB_SET		WWDG_CTRL_ACTB_Msk

/**
 * @}
 */


/** @addtogroup WWDG_Exported_Functions
 * @{
 */

/**
 * @brief  Deinitializes the WWDG peripheral registers to their default reset values.
 */
void WWDG_DeInit(void)
{
    RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_WWDG, ENABLE);
    RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_WWDG, DISABLE);
}

/**
 * @brief  Sets the WWDG Prescaler.
 * @param WWDG_Prescaler specifies the WWDG Prescaler.
 *   This parameter can be one of the following values:
 *     @arg WWDG_PRESCALER_DIV1 WWDG counter clock = (PCLK1/4096)/1
 *     @arg WWDG_PRESCALER_DIV2 WWDG counter clock = (PCLK1/4096)/2
 *     @arg WWDG_PRESCALER_DIV4 WWDG counter clock = (PCLK1/4096)/4
 *     @arg WWDG_PRESCALER_DIV8 WWDG counter clock = (PCLK1/4096)/8
 */
void WWDG_SetPrescalerDiv(uint32_t WWDG_Prescaler)
{
    uint32_t tmpregister = 0;
	
    /* Check the parameters */
    assert_param(IS_WWDG_PRESCALER_DIV(WWDG_Prescaler));
	
	tmpregister = WWDG->CFG;
	
    /* Clear WDGTB[1:0] bits */
    tmpregister &= (~WWDG_CFG_TIMERB);
	
    /* Set WDGTB[1:0] bits according to WWDG_Prescaler value */
    tmpregister |= WWDG_Prescaler;
	
    /* Store the new value */
    WWDG->CFG = tmpregister;
}

/**
 * @brief  Sets the WWDG window value.
 * @param WindowValue specifies the window value to be compared to the downcounter.
 *   This parameter value must be lower than 0x80.
 */
void WWDG_SetWValue(uint8_t WindowValue)
{
    uint32_t tmpregister = 0;

    /* Check the parameters */
    assert_param(IS_WWDG_VALUE(WindowValue));
	
	tmpregister = WWDG->CFG;
	
    /* Clear W[6:0] bits */
    tmpregister &= (~WWDG_CFG_W);

    /* Set W[6:0] bits according to WindowValue value */
    tmpregister |= (uint32_t)WindowValue;

    /* Store the new value */
    WWDG->CFG = tmpregister;
}

/**
 * @brief  Enables the WWDG Early Wakeup interrupt(EWI).
 */
void WWDG_EnableInt(void)
{
	__AMOOR_W((__IO int32_t *)WWDG_CFG_ADDR, WWDG_CFG_EWINT_Msk); /* Atomic OR operation */
}

/**
 * @brief  Sets the WWDG counter value.
 * @param Counter specifies the watchdog counter value.
 *   This parameter must be a number between 0x40 and 0x7F.
 */
void WWDG_SetCnt(uint8_t Counter)
{
    /* Check the parameters */
    assert_param(IS_WWDG_CNT(Counter));
	
    /* Write to T[6:0] bits to configure the counter value. Actually no need to do
       a read-modify-write, because writing a 0 to ACTB bit does nothing */
    WWDG->CTRL = Counter;
}

/**
 * @brief  Enables WWDG and load the counter value.
 * @param Counter specifies the watchdog counter value.
 *   This parameter must be a number between 0x40 and 0x7F.
 */
void WWDG_Enable(uint8_t Counter)
{
    /* Check the parameters */
    assert_param(IS_WWDG_CNT(Counter));
	
    WWDG->CTRL = CTRL_ACTB_SET | Counter;
}

/**
 * @brief  Checks whether the Early Wakeup interrupt flag is set or not.
 * @retval The new state of the Early Wakeup interrupt flag (SET or RESET)
 */
FlagStatus WWDG_GetEWINTF(void)
{
    return (FlagStatus)(WWDG->STS & WWDG_STS_EWINTF_Msk);
}

/**
 * @brief  Clears Early Wakeup interrupt flag.
 */
void WWDG_ClrEWINTF(void)
{
    WWDG->STS &= (~WWDG_STS_EWINTF);	/* Write '0' to clear early wakeup interrupt flag */
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
