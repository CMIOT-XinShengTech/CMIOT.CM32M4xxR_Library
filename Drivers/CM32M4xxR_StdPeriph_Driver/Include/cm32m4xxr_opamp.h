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
 * @file cm32m4xxr_opamp.h
 * @author CMIOT Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */
#ifndef __CM32M4xxR_OPAMP_H__
#define __CM32M4xxR_OPAMP_H__

#ifdef __cplusplus
extern "C" {
#endif


/** @addtogroup CM32M4xxR_StdPeriph_Driver
 * @{
 */

/** @addtogroup OPAMP
 * @{
 */

/** @defgroup OPAMP_Exported_Constants OPAMP Exported Constants
 * @{
 */
typedef enum
{
	OPAMP1 = 0U,
	OPAMP2 = 4U,
	OPAMP3 = 8U,
	OPAMP4 = 12U,
} OPAMP_PeriphType;

/**@def OPAMP_CS_VPSSEL_Type OPAMP CS VPSSEL Type
 */
typedef enum
{
    OPAMP1_CS_VPSSEL_PA1     	= (0x00UL << 19U),
    OPAMP1_CS_VPSSEL_PA3     	= (0x01UL << 19U),
    OPAMP1_CS_VPSSEL_DAC2_PA5	= (0x02UL << 19U),
    OPAMP1_CS_VPSSEL_PC3     	= (0x03UL << 19U),
    OPAMP1_CS_VPSSEL_PA7     	= (0x04UL << 19U),
	
    OPAMP2_CS_VPSSEL_PA7     	= (0x00UL << 19U),
    OPAMP2_CS_VPSSEL_PB0     	= (0x01UL << 19U),
    OPAMP2_CS_VPSSEL_PE8     	= (0x02UL << 19U),
	
    OPAMP3_CS_VPSSEL_PC9     	= (0x00UL << 19U),
    OPAMP3_CS_VPSSEL_PA1     	= (0x01UL << 19U),
    OPAMP3_CS_VPSSEL_DAC2_PA5	= (0x02UL << 19U),
    OPAMP3_CS_VPSSEL_PC3     	= (0x03UL << 19U),
	
    OPAMP4_CS_VPSSEL_PC3     	= (0x00UL << 19U),
    OPAMP4_CS_VPSSEL_DAC1_PA4	= (0x01UL << 19U),
    OPAMP4_CS_VPSSEL_PC5     	= (0x02UL << 19U),
} OPAMP_CS_VPSSEL_Type;

/**@def OPAMP_CS_VMSSEL_Type OPAMP CS VMSSEL Type
 */
typedef enum
{
    OPAMP1_CS_VMSSEL_PA3  		= (0x00UL << 17U),
    OPAMP1_CS_VMSSEL_PA2  		= (0x01UL << 17U),
	
    OPAMPx_CS_VMSSEL_FLOAT		= (0x03UL << 17U),
	
    OPAMP2_CS_VMSSEL_PA2  		= (0x00UL << 17U),
    OPAMP2_CS_VMSSEL_PA5  		= (0x01UL << 17U),
	
    OPAMP3_CS_VMSSEL_PC4  		= (0x00UL << 17U),
    OPAMP3_CS_VMSSEL_PB10 		= (0x01UL << 17U),
	
    OPAMP4_CS_VMSSEL_PB10 		= (0x00UL << 17U),
    OPAMP4_CS_VMSSEL_PC9  		= (0x01UL << 17U),
    OPAMP4_CS_VMSSEL_PD8		= (0x02UL << 17U),
} OPAMP_CS_VMSSEL_Type;

/**@def OPAMP_CS_VPSEL_Type OPAMP CS VPSEL Type
 */
typedef enum
{
    OPAMP1_CS_VPSEL_PA1     	= (0x00UL << 8U),
    OPAMP1_CS_VPSEL_PA3     	= (0x01UL << 8U),
    OPAMP1_CS_VPSEL_DAC2_PA5	= (0x02UL << 8U),
    OPAMP1_CS_VPSEL_PC3     	= (0x03UL << 8U),
    OPAMP1_CS_VPSEL_PA7     	= (0x04UL << 8U),
	
    OPAMP2_CS_VPSEL_PA7     	= (0x00UL << 8U),
    OPAMP2_CS_VPSEL_PB0     	= (0x01UL << 8U),
    OPAMP2_CS_VPSEL_PE8     	= (0x02UL << 8U),
	
    OPAMP3_CS_VPSEL_PC9     	= (0x00UL << 8U),
    OPAMP3_CS_VPSEL_PA1     	= (0x01UL << 8U),
    OPAMP3_CS_VPSEL_DAC2_PA5	= (0x02UL << 8U),
    OPAMP3_CS_VPSEL_PC3     	= (0x03UL << 8U),
	
    OPAMP4_CS_VPSEL_PC3     	= (0x00UL << 8U),
    OPAMP4_CS_VPSEL_DAC1_PA4	= (0x01UL << 8U),
    OPAMP4_CS_VPSEL_PC5     	= (0x02UL << 8U),
} OPAMP_CS_VPSEL_Type;

/**@def OPAMP_CS_VMSEL_Type OPAMP CS VMSEL Type
 */
typedef enum
{
    OPAMP1_CS_VMSEL_PA3  		= (0x00UL << 6U),
    OPAMP1_CS_VMSEL_PA2  		= (0x01UL << 6U),
	
    OPAMPx_CS_VMSEL_FLOAT		= (0x03UL << 6U),
	
    OPAMP2_CS_VMSEL_PA2  		= (0x00UL << 6U),
    OPAMP2_CS_VMSEL_PA5  		= (0x01UL << 6U),
	
    OPAMP3_CS_VMSEL_PC4  		= (0x00UL << 6U),
    OPAMP3_CS_VMSEL_PB10 		= (0x01UL << 6U),
	
    OPAMP4_CS_VMSEL_PB10 		= (0x00UL << 6U),
    OPAMP4_CS_VMSEL_PC9  		= (0x01UL << 6U),
    OPAMP4_CS_VMSEL_PD8   		= (0x02UL << 6U),
} OPAMP_CS_VMSEL_Type;

/**@def OPAMP_CS_PGA_GAIN_Type OPAMP CS PGA GAIN Type
 */
typedef enum
{
    OPAMP_CS_PGA_GAIN_2 		= (0x00UL << 3U),
    OPAMP_CS_PGA_GAIN_4 		= (0x01UL << 3U),
    OPAMP_CS_PGA_GAIN_8 		= (0x02UL << 3U),
    OPAMP_CS_PGA_GAIN_16		= (0x03UL << 3U),
    OPAMP_CS_PGA_GAIN_32		= (0x04UL << 3U),
} OPAMP_CS_PGA_GAIN_Type;

typedef enum
{
    OPAMP_CS_EXT_OPAMP			= (0x00UL << 1U),
    OPAMP_CS_PGA_EN   			= (0x02UL << 1U),
    OPAMP_CS_FOLLOW   			= (0x03UL << 1U),
} OPAMP_CS_MOD_Type;

/**
 * @}
 */


/**@defgroup OPAMP_Exported_Types OPAMP Exported Types
 * @{
 * @brief  OPAMP Init structure definition
 */

typedef struct
{
    FunctionalState TimeAutoMuxEn;	/* call ENABLE or DISABLE */

    FunctionalState HighVolRangeEn; /* call ENABLE or DISABLE, low range VDDA < 2.4V, high range VDDA >= 2.4V */

    OPAMP_CS_PGA_GAIN_Type Gain;	/* see @OPAMP_CS_PGA_GAIN_Type */

    OPAMP_CS_MOD_Type Mod;			/* see @OPAMP_CS_MOD_Type */
} OPAMP_InitType;


/**
 * @}
 */

/** @defgroup OPAMP_Exported_Functions OPAMP Exported Functions
 * @{
 */

void	OPAMP_DeInit (void);
void	OPAMP_StructInit (OPAMP_InitType* OPAMP_InitStruct);
void	OPAMP_Init (OPAMP_PeriphType OPAMPx, OPAMP_InitType* OPAMP_InitStruct);
void	OPAMP_Enable (OPAMP_PeriphType OPAMPx, FunctionalState Cmd);
void	OPAMP_SetPgaGain (OPAMP_PeriphType OPAMPx, OPAMP_CS_PGA_GAIN_Type Gain);
void	OPAMP_SetVpSecondSel (OPAMP_PeriphType OPAMPx, OPAMP_CS_VPSSEL_Type VpSSel);
void	OPAMP_SetVmSecondSel (OPAMP_PeriphType OPAMPx, OPAMP_CS_VMSSEL_Type VmSSel);
void	OPAMP_SetVpSel (OPAMP_PeriphType OPAMPx, OPAMP_CS_VPSEL_Type VpSel);
void	OPAMP_SetVmSel (OPAMP_PeriphType OPAMPx, OPAMP_CS_VMSEL_Type VmSel);
bool	OPAMP_IsCalOutHigh (OPAMP_PeriphType OPAMPx);
void	OPAMP_CalibrationEnable (OPAMP_PeriphType OPAMPx, FunctionalState Cmd);
void	OPAMP_SetLock (uint32_t Lock);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /*__CM32M4xxR_OPAMP_H */
/**
 * @}
 */
/**
 * @}
 */

