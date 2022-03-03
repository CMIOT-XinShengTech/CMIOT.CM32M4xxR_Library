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
 * @file cm32m4xxr_rngc.h
 * @author CMIOT Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */
#ifndef __CM32M4xxR_RNGC_H__
#define __CM32M4xxR_RNGC_H__

#ifdef __cplusplus
extern "C" {
#endif


/** @addtogroup CM32M4xxR_StdPeriph_Driver
 * @{
 */

/** @addtogroup RNGC
 * @{
 */

/** @defgroup RNGC_Exported_Types RNGC Exported Types
 * @{
 */

typedef struct
{
    uint32_t Prescaler;	/*!< Specifies the random number generator clock prescaler. 
                             This parameter can be a value of RCC_RNGCCLK_SYSCLK_DIV1 ~ RCC_RNGCCLK_SYSCLK_DIV32
                             defined in cm32m4xxr_rcc.h file */
    bool Ring0En;		/*!< Enable inverter ring 0 if 1, disable inverter ring 0 if 0. */
    bool Ring1En;		/*!< Enable inverter ring 1 if 1, disable inverter ring 1 if 0. */
} RNGC_InitType;

/**
 * @}
 */

/** @defgroup RNGC_Exported_Constants RNGC Exported Constants
 * @{
 */

#define INVALID_RANDOM_VALUE    ((uint32_t) 0x5555AAAA)


/** @addtogroup RNG_mode
 * @{
 */

#define RNG_MODE_DISABLE		((uint32_t) 0x00000000)	/* Disable random number generator */
#define RNG_MODE_RANDOM_SOURCE	((uint32_t) 0x00000001)	/* Random source */
#define RNG_MODE_PRNG			((uint32_t) 0x00000002)	/* Pseudo-random */
#define RNG_MODE_TRNG			((uint32_t) 0x00000003)	/* True random */
#define IS_RNG_MODE(MODE)		(((MODE) == RNG_MODE_DISABLE) || ((MODE) == RNG_MODE_RANDOM_SOURCE) || \
								 ((MODE) == RNG_MODE_PRNG)    || ((MODE) == RNG_MODE_TRNG))

/**
 * @}
 */


 /**
 * @}
 */
 
/** @defgroup RNGC_Exported_Functions RNGC Exported Functions
 * @{
 */

void		RNGC_DeInit (void);
ErrorStatus	RNGC_Init (RNGC_InitType* RNGC_InitStruct);
ErrorStatus	RNGC_SetRngMode (uint32_t RNG_Mode);
uint32_t	RNGC_GetRand (void);
FlagStatus  RNGC_GetCtrlWrReadyFlag (void);
FlagStatus  RNGC_GetDataReadyFlag (void);



#ifdef __cplusplus
}
#endif

#endif /* __CM32M4xxR_RNGC_H__ */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
