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
 * @file cm32m4xxr_iwdg.h
 * @author CMIOT Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */
#ifndef __CM32M4xxR_IWDG_H__
#define __CM32M4xxR_IWDG_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup CM32M4xxR_StdPeriph_Driver
 * @{
 */

/** @addtogroup IWDG
 * @{
 */


/** @defgroup IWDG_Exported_Constants IWDG Exported Constants
 * @{
 */

/** @addtogroup IWDG_WriteAccess
 * @{
 */

#define IWDG_WRITE_ENABLE		((uint16_t) 0x5555)	/* Write the value to KEY register to enable write access to IWDG_PREDIV and IWDG_RELV registers */
#define IWDG_WRITE_DISABLE		((uint16_t) 0x0000)	/* Write the value to KEY register to disable write access to IWDG_PREDIV and IWDG_RELV registers */
#define IS_IWDG_WRITE(ACCESS)	(((ACCESS) == IWDG_WRITE_ENABLE) || ((ACCESS) == IWDG_WRITE_DISABLE))
/**
 * @}
 */

/** @addtogroup IWDG_prescaler
 * @{
 */

#define IWDG_PRESCALER_DIV4 				((uint8_t) 0x00)
#define IWDG_PRESCALER_DIV8 				((uint8_t) 0x01)
#define IWDG_PRESCALER_DIV16				((uint8_t) 0x02)
#define IWDG_PRESCALER_DIV32				((uint8_t) 0x03)
#define IWDG_PRESCALER_DIV64				((uint8_t) 0x04)
#define IWDG_PRESCALER_DIV128				((uint8_t) 0x05)
#define IWDG_PRESCALER_DIV256				((uint8_t) 0x06)
#define IS_IWDG_PRESCALER_DIV(PRESCALER)	(((PRESCALER) == IWDG_PRESCALER_DIV4)  || ((PRESCALER) == IWDG_PRESCALER_DIV8)   || \
											 ((PRESCALER) == IWDG_PRESCALER_DIV16) || ((PRESCALER) == IWDG_PRESCALER_DIV32)  || \
											 ((PRESCALER) == IWDG_PRESCALER_DIV64) || ((PRESCALER) == IWDG_PRESCALER_DIV128) || \
											 ((PRESCALER) == IWDG_PRESCALER_DIV256))
/**
 * @}
 */

/** @addtogroup IWDG_Flag
 * @{
 */

#define IWDG_PVU_FLAG			((uint16_t) 0x0001)
#define IWDG_CRVU_FLAG			((uint16_t) 0x0002)
#define IS_IWDG_FLAG(FLAG)		(((FLAG) == IWDG_PVU_FLAG) || ((FLAG) == IWDG_CRVU_FLAG))
#define IS_IWDG_RELOAD(RELOAD)	((RELOAD) <= 0xFFF)
/**
 * @}
 */

/**
 * @}
 */


/** @defgroup IWDG_Exported_Functions IWDG Exported Functions
 * @{
 */

void		IWDG_WriteConfig (uint16_t IWDG_WriteAccess);
void		IWDG_SetPrescalerDiv (uint8_t IWDG_Prescaler);
void		IWDG_CntReload (uint16_t Reload);
void		IWDG_ReloadKey (void);
void		IWDG_Enable (void);
FlagStatus	IWDG_GetStatus (uint16_t IWDG_FLAG);

#ifdef __cplusplus
}
#endif

#endif /* __CM32M4xxR_IWDG_H__ */
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
