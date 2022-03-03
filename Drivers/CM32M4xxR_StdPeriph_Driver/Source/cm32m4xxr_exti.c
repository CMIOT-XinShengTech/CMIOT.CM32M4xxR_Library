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
 * @file cm32m4xxr_exti.c
 * @author CMIOT Firmware Team
 * @brief Source file containing functions prototypes of EXTI stdperiph library.
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */
#include "nuclei_sdk_soc.h"


/** @addtogroup CM32M4xxR_StdPeriph_Driver
 * @{
 */

/** @defgroup EXTI EXTI
 * @brief EXTI driver modules
 * @{
 */

#ifdef	DRIVER_MODULE_ENABLED_EXTI


/** @defgroup EXTI_Exported_Functions EXTI Exported Functions
 * @{
 */

/**
 * @brief  Deinitializes the EXTI peripheral registers to their default reset values.
 */
void EXTI_DeInit(void)
{
    EXTI->IMASK  = 0x00000000;	/* Disable interrupt on EXTI lines */
    EXTI->EMASK  = 0x00000000;	/* Disable event on EXTI lines */
    EXTI->RT_CFG = 0x00000000;	/* Disable rising trigger on EXTI lines */
    EXTI->FT_CFG = 0x00000000;	/* Disable falling trigger on EXTI lines */
    EXTI->PEND   = 0x003FFFFF;	/* Clear pending bit on EXTI lines */
}

/**
 * @brief  Initializes the EXTI peripheral according to the specified
 *         parameters in the EXTI_InitStruct.
 * @param EXTI_InitStruct pointer to a EXTI_InitType structure
 *         that contains the configuration information for the EXTI peripheral.
 */
void EXTI_Init(EXTI_InitType* EXTI_InitStruct)
{
    uint32_t tmpaddress = 0;
	uint32_t linepos	= 0;
	uint32_t linemsk	= 0;

    /* Check the parameters */
    assert_param(IS_EXTI_MODE(EXTI_InitStruct->EXTI_Mode));
    assert_param(IS_EXTI_TRIGGER(EXTI_InitStruct->EXTI_Trigger));
    assert_param(IS_EXTI_LINE(EXTI_InitStruct->EXTI_Line));
    assert_param(IS_FUNCTIONAL_STATE(EXTI_InitStruct->EXTI_LineCmd));

    tmpaddress	= (uint32_t)EXTI_BASE;
	linepos		= (EXTI_InitStruct->EXTI_Line & EXTI_PIN_MASK);
	linemsk		= (0x1UL << linepos);

    if (EXTI_InitStruct->EXTI_LineCmd != DISABLE)
    {
        /* Clear EXTI line configuration */
        EXTI->IMASK &= ~linemsk;
        EXTI->EMASK &= ~linemsk;

        tmpaddress += EXTI_InitStruct->EXTI_Mode;

        *(__IO uint32_t*)tmpaddress |= linemsk;

        /* Clear Rising Falling edge configuration */
        EXTI->RT_CFG &= ~linemsk;
        EXTI->FT_CFG &= ~linemsk;

        /* Select the trigger for the selected external interrupts */
        if (EXTI_InitStruct->EXTI_Trigger == EXTI_Trigger_Rising_Falling)
        {
            /* Rising Falling edge */
            EXTI->RT_CFG |= linemsk;
            EXTI->FT_CFG |= linemsk;
        }
        else
        {
            tmpaddress = (uint32_t)EXTI_BASE;
            tmpaddress += EXTI_InitStruct->EXTI_Trigger;

            *(__IO uint32_t*)tmpaddress |= linemsk;
        }
    }
    else
    {
        tmpaddress += EXTI_InitStruct->EXTI_Mode;

        /* Disable the selected external lines */
        *(__IO uint32_t*)tmpaddress &= ~linemsk;
    }
}

/**
 * @brief  Fills each EXTI_InitStruct member with its reset value.
 * @param  EXTI_InitStruct pointer to a EXTI_InitType structure which will
 *         be initialized.
 */
void EXTI_InitStruct(EXTI_InitType* EXTI_InitStruct)
{
    EXTI_InitStruct->EXTI_Line    = EXTI_LINENONE;
    EXTI_InitStruct->EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStruct->EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStruct->EXTI_LineCmd = DISABLE;
}

/**
 * @brief  Generates a Software interrupt.
 * @param EXTI_Line specifies the EXTI lines to be enabled or disabled.
 *   This parameter can be any combination of EXTI_Linex where x can be (0..21,except 18 and 19).
 */
void EXTI_TriggerSWInt(uint32_t EXTI_Line)
{
	uint32_t linepos = 0;
	uint32_t linemsk = 0;
	
    /* Check the parameters */
    assert_param(IS_EXTI_LINE(EXTI_Line));

	linepos = (EXTI_Line & EXTI_PIN_MASK);
	linemsk = (0x1UL << linepos);

    EXTI->SWIE |= linemsk;
}

/**
 * @brief  Checks whether the specified EXTI line flag is set or not.
 * @param EXTI_Line specifies the EXTI line flag to check.
 *   This parameter can be:
 *     @arg EXTI_Linex External interrupt line x where x(0..21,except 18 and 19)
 * @return The new state of EXTI_Line (SET or RESET).
 */
FlagStatus EXTI_GetStatusFlag(uint32_t EXTI_Line)
{
    FlagStatus bitstatus = RESET;
	uint32_t linepos = 0;
	uint32_t linemsk = 0;
	
    /* Check the parameters */
    assert_param(IS_GET_EXTI_LINE(EXTI_Line));

	linepos = (EXTI_Line & EXTI_PIN_MASK);
	linemsk = (0x1UL << linepos);

    if ((EXTI->PEND & linemsk) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
	
    return bitstatus;
}

/**
 * @brief  Clears the EXTI's line pending flags.
 * @param EXTI_Line specifies the EXTI lines flags to clear.
 *   This parameter can be any combination of EXTI_Linex where x can be (0..21,except 18 and 19)
 */
void EXTI_ClrStatusFlag(uint32_t EXTI_Line)
{
	uint32_t linepos = 0;
	uint32_t linemsk = 0;
	
    /* Check the parameters */
    assert_param(IS_EXTI_LINE(EXTI_Line));

	linepos = (EXTI_Line & EXTI_PIN_MASK);
	linemsk = (0x1UL << linepos);

    EXTI->PEND = linemsk;
}

/**
 * @brief  Checks whether the specified EXTI line is asserted or not.
 * @param EXTI_Line specifies the EXTI line to check.
 *   This parameter can be:
 *     @arg EXTI_Linex External interrupt line x where x(0..21,except 18 and 19)
 * @return The new state of EXTI_Line (SET or RESET).
 */
INTStatus EXTI_GetITStatus(uint32_t EXTI_Line)
{
    INTStatus bitstatus	= RESET;
	uint32_t linepos	= 0;
	uint32_t linemsk	= 0;	
	
    /* Check the parameters */
    assert_param(IS_GET_EXTI_LINE(EXTI_Line));

	linepos = (EXTI_Line & EXTI_PIN_MASK);
	linemsk = (0x1UL << linepos);

    if (((EXTI->PEND & linemsk) != (uint32_t)RESET) && ((EXTI->IMASK & linemsk) != (uint32_t)RESET))
    {
        bitstatus = SET;	/* PEND bit set and interrupt enabled */
    }
    else
    {
        bitstatus = RESET;
    }
	
    return bitstatus;
}

/**
 * @brief  Clears the EXTI's line pending bits.
 * @param EXTI_Line specifies the EXTI lines to clear.
 *   This parameter can be any combination of EXTI_Linex where x can be (0..21,except 18 and 19).
 */
void EXTI_ClrITPendBit(uint32_t EXTI_Line)
{
	uint32_t linepos	= 0;
	uint32_t linemsk	= 0;
	
    /* Check the parameters */
    assert_param(IS_EXTI_LINE(EXTI_Line));
	
	linepos = (EXTI_Line & EXTI_PIN_MASK);
	linemsk = (0x1UL << linepos);

    EXTI->PEND = linemsk;
}

/**
 * @brief  Select one of EXTI inputs to the RTC TimeStamp event.
 * @param EXTI_TSSEL_Line specifies the EXTI lines to select.
 *   This parameter can be any combination of EXTI_TSSEL_Line where x can be (0..15).
 */
void EXTI_RTCTimeStampSel(uint32_t EXTI_TSSEL_Line)
{
    /* Check the parameters */
    assert_param(IS_EXTI_TSSEL_LINE(EXTI_TSSEL_Line));

    EXTI->TSSEL &= ~EXTI_TS_SEL_TSSEL;
    EXTI->TSSEL |= EXTI_TSSEL_Line;
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
