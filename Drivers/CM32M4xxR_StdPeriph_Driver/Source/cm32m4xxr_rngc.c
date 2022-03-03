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
 * @file cm32m4xxr_rngc.c
 * @author CMIOT Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */
#include "nuclei_sdk_soc.h"


/** @addtogroup CM32M4xxR_StdPeriph_Driver
 * @{
 */

/** @addtogroup RNGC
 * @brief RGNC driver modules
 * @{
 */

#ifdef	DRIVER_MODULE_ENABLED_RNGC


/** @defgroup RGNC_Private_Defines RGNC Private Defines
 * @{
 */

#define CTRL_WR_READY_TIMEOUT   ((uint32_t) 0x00001000)
#define DATA_READY_TIMEOUT      ((uint32_t) 0x00001000)

/**
 * @}
 */


/** @addtogroup RNGC_Exported_Functions
 * @{
 */

/**
 * @brief Deinitializes the RNGC peripheral registers to their default reset values.
 */
void RNGC_DeInit(void)
{
	/* Enable RNGC reset state */
	RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_RNGC, ENABLE);
		
	/* Release RNGC from reset state */
	RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_RNGC, DISABLE);
}

/**
 * @brief Initializes the RNGC peripheral according to the specified
 *		  parameters in the RNGC_InitStruct.
 * @param RNGC_InitStruct pointer to a RNGC_InitType structure that
 *   	  contains the configuration information for the RNGC peripheral.
 * @retval  An ErrorStatus enumeration value:
 *          - SUCCESS: RNGC registers are initialized
 *          - ERROR: RNGC registers are not deinitialized
 */
ErrorStatus RNGC_Init(RNGC_InitType* RNGC_InitStruct)
{
    __IO uint32_t tempreg = 0;
    ErrorStatus status    = ERROR;
    uint32_t timeout      = CTRL_WR_READY_TIMEOUT;

    /* Check the parameters */
    assert_param(RNGC_InitStruct);
    assert_param(IS_RCC_RNGCCLKPRE(RNGC_InitStruct->Prescaler));

    /* Set RNGC clock prescaler---------------------------------------------- */
	/* Get RCC_CFG2 register value */
    tempreg = RCC->CFG2;

    /* Clear RNGCPRE[3:0] bits */
    tempreg &= (~RCC_CFG2_RNGCPRES);

    /* Set RNGCPRE[3:0] bits according to RCC_RNGCCLKPrescaler value */
    tempreg |= RNGC_InitStruct->Prescaler;

    /* Store the new value */
    RCC->CFG2 = tempreg;

    /* Set RNGC ring0/1 status----------------------------------------------- */
	/* Get RNGC_CTRL register value */
	tempreg = RNGC->CTRL;

    /* Clear RING0_EN, RING1_EN and RNG_MODE bits */
    tempreg &= (uint32_t)~(RNGC_CTRL_RING0_EN | RNGC_CTRL_RING1_EN);

	/* Set RING0_EN, RING1_EN and RNG_MODE according to the specified parameters */
	tempreg |= ((RNGC_InitStruct->Ring0En << RNGC_CTRL_RING0_EN_Pos) | (RNGC_InitStruct->Ring1En << RNGC_CTRL_RING1_EN_Pos));

    /* Wait till the RNGC_CTRL register ready to write or timeout */
    while((RNGC_GetCtrlWrReadyFlag() == RESET) && timeout--);

    if(RNGC_GetCtrlWrReadyFlag() == RESET)
    {
        status = ERROR; 
    }
    else
    {
        /* Set RNGC_CTRL register */
        RNGC->CTRL = tempreg;

        status = SUCCESS;
    }
    
    return status;
}

/**
 * @brief Set RNGC work mode according to the specified value of RNG_Mode.
 * @param RNG_Mode RNGC work mode whitch can be one of the following values:
 *				RNG_MODE_DISABLE
 *		  		RNG_MODE_RANDOM_SOURCE
 * 		  		RNG_MODE_PRNG
 *		  		RNG_MODE_TRNG
 * @retval  An ErrorStatus enumeration value:
 *          - SUCCESS: RNGC registers are initialized
 *          - ERROR: RNGC registers are not deinitialized
 * @note To get correct random number, should set RNG_MODE_RANDOM_SOURCE mode first after reset!
 */
ErrorStatus RNGC_SetRngMode (uint32_t RNG_Mode)
{
    __IO uint32_t tempreg = 0;
    ErrorStatus status    = ERROR;
    uint32_t timeout      = CTRL_WR_READY_TIMEOUT;

    /* Check the parameters */
	assert_param(IS_RNG_MODE(RNG_Mode));    

	/* Get RNGC_CTRL register value */
	tempreg = RNGC->CTRL;

    /* Clear RNG_MODE bits */
    tempreg &= (uint32_t)~RNGC_CTRL_RNG_MODE;

    /* Wait till the RNGC_CTRL register ready to write or timeout */
    while((RNGC_GetCtrlWrReadyFlag() == RESET) && timeout--);

    if(RNGC_GetCtrlWrReadyFlag() == RESET)
    {
        status = ERROR;
    }
    else
    {
        /* Disable RNGC first */
        RNGC->CTRL = tempreg;

    	/* Set RNG_MODE according to RNG_Mode */
    	tempreg |= (RNG_Mode << RNGC_CTRL_RNG_MODE_Pos);

    	timeout = CTRL_WR_READY_TIMEOUT;
    	while((RNGC_GetCtrlWrReadyFlag() == RESET) && timeout--);

    	if(RNGC_GetCtrlWrReadyFlag() == RESET)
    	{
    		status = ERROR;
    	}
    	else
    	{
    		RNGC->CTRL = tempreg;
    
    		/* Wait till seed filled if in RANDOM_SOURCE mode */
    		if(RNG_Mode == RNG_MODE_RANDOM_SOURCE)
    		{
    			timeout = DATA_READY_TIMEOUT;
    			while((RNGC_GetDataReadyFlag() == RESET) && timeout--);

    			if(RNGC_GetDataReadyFlag() == RESET)
    			{
    				status = ERROR;
    			}
    			else
    			{
    			    status = SUCCESS;
    			}
    		}
    		else
    		{
    		    status = SUCCESS;
    		}
    	}
    }

    return status;
}

/**
 * @brief Get a random number.
 * @retval Random number which can be a pseudo-random number or a true random
 * 		   number according to the RNG mode.
 */
uint32_t RNGC_GetRand(void)
{
    uint32_t timeout    = DATA_READY_TIMEOUT;
    uint32_t rand_value = INVALID_RANDOM_VALUE;

    /* Wait till the random data ready to read or timeout */
    while((RNGC_GetDataReadyFlag() == RESET) && timeout--);

    if(RNGC_GetDataReadyFlag() != RESET)
    {
        rand_value = (uint32_t)(RNGC->DAT);
    }

	return rand_value;
}

/**
 * @brief Get RNGC control register ready to write flag.
 * @retval The new state of control register ready to write flag.
 */
FlagStatus RNGC_GetCtrlWrReadyFlag(void)
{
    FlagStatus bitstatus = RESET;

    if((RNGC->CTRL_WR_READY & RNGC_CTRL_WR_READY_READY_Msk) != RESET)
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
 * @brief Get RNGC data ready flag.
 * @retval The new state of data ready flag.
 */
FlagStatus RNGC_GetDataReadyFlag(void)
{
    FlagStatus bitstatus = RESET;

    if((RNGC->DAT_READY & RNGC_DAT_READY_READY_Msk) != RESET)
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
 * @}
 */

#endif

/**
 * @}
 */

/**
 * @}
 */
