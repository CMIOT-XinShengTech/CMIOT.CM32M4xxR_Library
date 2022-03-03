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
 * @file cm32m4xxr_wwdg.h
 * @author CMIOT Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */
#ifndef __CM32M4xxR_WWDG_H__
#define __CM32M4xxR_WWDG_H__

#ifdef __cplusplus
extern "C" {
#endif


/** @addtogroup CM32M4xxR_StdPeriph_Driver
 * @{
 */

/** @addtogroup WWDG
 * @{
 */


/** @defgroup WWDG_Exported_Constants WWDG Exported Constants
 * @{
 */

/** @addtogroup WWDG_Prescaler
 * @{
 */

#define WWDG_PRESCALER_DIV1					((uint32_t) 0x00000000)
#define WWDG_PRESCALER_DIV2					((uint32_t) 0x00000080)
#define WWDG_PRESCALER_DIV4					((uint32_t) 0x00000100)
#define WWDG_PRESCALER_DIV8					((uint32_t) 0x00000180)
#define IS_WWDG_PRESCALER_DIV(PRESCALER)	(((PRESCALER) == WWDG_PRESCALER_DIV1) || ((PRESCALER) == WWDG_PRESCALER_DIV2) || \
											 ((PRESCALER) == WWDG_PRESCALER_DIV4) || ((PRESCALER) == WWDG_PRESCALER_DIV8))
#define IS_WWDG_VALUE(VALUE)				((VALUE) <= (uint8_t)0x7F)
#define IS_WWDG_CNT(COUNTER)				(((COUNTER) >= (uint8_t)0x40) && ((COUNTER) <= (uint8_t)0x7F))

/**
 * @}
 */

/**
 * @}
 */


/** @defgroup WWDG_Exported_Functions WWDG Exported Functions
 * @{
 */

void		WWDG_DeInit (void);
void		WWDG_SetPrescalerDiv (uint32_t WWDG_Prescaler);
void		WWDG_SetWValue (uint8_t WindowValue);
void		WWDG_EnableInt (void);
void		WWDG_SetCnt (uint8_t Counter);
void		WWDG_Enable (uint8_t Counter);
FlagStatus	WWDG_GetEWINTF (void);
void		WWDG_ClrEWINTF (void);

#ifdef __cplusplus
}
#endif

#endif /* __CM32M4xxR__WWDG_H */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
