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
 * @file cm32m4xxr_comp.h
 * @author CMIOT Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */
#ifndef __CM32M4xxR_COMP_H__
#define __CM32M4xxR_COMP_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup CM32M4xxR_StdPeriph_Driver
 * @{
 */

/** @addtogroup COMP
 * @{
 */

/** @defgroup COMP_Exported_Constants COMP Exported Constants
 * @{
 */
typedef enum
{
	COMP1 = 0U,
    COMP2 = 1U,
    COMP3 = 2U,
    COMP4 = 3U,
    COMP5 = 4U,
    COMP6 = 5U,
    COMP7 = 6U
} COMP_PeriphType;

typedef enum
{
    COMP_CTRL_BLKING_NO       = (0x0UL << 14U),
    COMP_CTRL_BLKING_TIM1_OC5 = (0x1UL << 14U),
    COMP_CTRL_BLKING_TIM8_OC5 = (0x2UL << 14U),
} COMP_CTRL_BLKING_Type;

typedef enum
{
    COMP_CTRL_HYST_NO		  = (0x0UL << 12U),
    COMP_CTRL_HYST_LOW		  = (0x1UL << 12U),
    COMP_CTRL_HYST_MID		  = (0x2UL << 12U),
    COMP_CTRL_HYST_HIGH		  = (0x3UL << 12U),
} COMP_CTRL_HYST_Type;

/** @def COMP_CTRL_OUTTRIG_Type COMP CTRL OUTTRIG Type
 */
typedef enum
{
	COMPX_CTRL_OUTSEL_NC 					= (0x0UL << 7U),
	
    /* comp1 out trig */
    COMP1_CTRL_OUTSEL_NC                  	= (0x0UL << 7U),
    COMP1_CTRL_OUTSEL_TIM1_BKIN           	= (0x1UL << 7U),
    COMP1_CTRL_OUTSEL_TIM1_IC1            	= (0x2UL << 7U),
    COMP1_CTRL_OUTSEL_TIM1_OCrefclear     	= (0x3UL << 7U),
    COMP1_CTRL_OUTSEL_TIM2_IC1            	= (0x4UL << 7U),
    COMP1_CTRL_OUTSEL_TIM2_OCrefclear     	= (0x5UL << 7U),
    COMP1_CTRL_OUTSEL_TIM3_IC1            	= (0x6UL << 7U),
    COMP1_CTRL_OUTSEL_TIM3_OCrefclear     	= (0x7UL << 7U),
    COMP1_CTRL_OUTSEL_TIM4_IC1            	= (0x8UL << 7U),
    COMP1_CTRL_OUTSEL_TIM4_OCrefclear     	= (0x9UL << 7U),
    COMP1_CTRL_OUTSEL_TIM8_BKIN           	= (0xAUL << 7U),
    COMP1_CTRL_OUTSEL_TIM1_BKIN_TIM8_BKIN 	= (0xBUL << 7U),
	
    /* comp2 out trig */
    COMP2_CTRL_OUTSEL_NC                  	= (0x0UL << 7U),
    COMP2_CTRL_OUTSEL_TIM1_BKIN           	= (0x1UL << 7U),
    COMP2_CTRL_OUTSEL_TIM1_IC1            	= (0x2UL << 7U),
    COMP2_CTRL_OUTSEL_TIM1_OCrefclear     	= (0x3UL << 7U),
    COMP2_CTRL_OUTSEL_TIM2_IC2            	= (0x4UL << 7U),
    COMP2_CTRL_OUTSEL_TIM2_OCrefclear     	= (0x5UL << 7U),
    COMP2_CTRL_OUTSEL_TIM3_IC2            	= (0x6UL << 7U),
    COMP2_CTRL_OUTSEL_TIM3_OCrefclear     	= (0x7UL << 7U),
    COMP2_CTRL_OUTSEL_TIM5_IC1            	= (0x8UL << 7U),
    COMP2_CTRL_OUTSEL_TIM8_BKIN           	= (0xAUL << 7U),
    COMP2_CTRL_OUTSEL_TIM1_BKIN_TIM8_BKIN 	= (0xBUL << 7U),
	
    /* comp3 out trig */
    COMP3_CTRL_OUTSEL_NC                  	= (0x0UL << 7U),
    COMP3_CTRL_OUTSEL_TIM1_BKIN           	= (0x1UL << 7U),
    COMP3_CTRL_OUTSEL_TIM1_IC1            	= (0x2UL << 7U),
    COMP3_CTRL_OUTSEL_TIM1_OCrefclear     	= (0x3UL << 7U),
    COMP3_CTRL_OUTSEL_TIM2_IC3            	= (0x4UL << 7U),
    COMP3_CTRL_OUTSEL_TIM2_OCrefclear     	= (0x5UL << 7U),
    COMP3_CTRL_OUTSEL_TIM4_IC2            	= (0x6UL << 7U),
    COMP3_CTRL_OUTSEL_TIM4_OCrefclear     	= (0x7UL << 7U),
    COMP3_CTRL_OUTSEL_TIM5_IC2            	= (0x8UL << 7U),
    COMP3_CTRL_OUTSEL_TIM8_BKIN           	= (0xAUL << 7U),
    COMP3_CTRL_OUTSEL_TIM1_BKIN_TIM8_BKIN 	= (0xBUL << 7U),
	
    /* comp4 out trig */
    COMP4_CTRL_OUTSEL_NC                  	= (0x0UL << 7U),
    COMP4_CTRL_OUTSEL_TIM1_BKIN           	= (0x1UL << 7U),
    COMP4_CTRL_OUTSEL_TIM3_IC3            	= (0x2UL << 7U),
    COMP4_CTRL_OUTSEL_TIM3_OCrefclear     	= (0x3UL << 7U),
    COMP4_CTRL_OUTSEL_TIM4_IC3            	= (0x4UL << 7U),
    COMP4_CTRL_OUTSEL_TIM4_OCrefclear     	= (0x5UL << 7U),
    COMP4_CTRL_OUTSEL_TIM5_IC3            	= (0x6UL << 7U),
    COMP4_CTRL_OUTSEL_TIM8_IC1            	= (0x8UL << 7U),
    COMP4_CTRL_OUTSEL_TIM8_OCrefclear     	= (0x9UL << 7U),
    COMP4_CTRL_OUTSEL_TIM8_BKIN           	= (0xAUL << 7U),
    COMP4_CTRL_OUTSEL_TIM1_BKIN_TIM8_BKIN 	= (0xBUL << 7U),
	
    /* comp5 out trig */
    COMP5_CTRL_OUTSEL_NC                  	= (0x0UL << 7U),
    COMP5_CTRL_OUTSEL_TIM1_BKIN           	= (0x1UL << 7U),
    COMP5_CTRL_OUTSEL_TIM2_IC4            	= (0x2UL << 7U),
    COMP5_CTRL_OUTSEL_TIM2_OCrefclear     	= (0x3UL << 7U),
    COMP5_CTRL_OUTSEL_TIM3_IC4            	= (0x4UL << 7U),
    COMP5_CTRL_OUTSEL_TIM3_OCrefclear     	= (0x5UL << 7U),
    COMP5_CTRL_OUTSEL_TIM4_IC4            	= (0x6UL << 7U),
    COMP5_CTRL_OUTSEL_TIM4_OCrefclear     	= (0x7UL << 7U),
    COMP5_CTRL_OUTSEL_TIM8_IC1            	= (0x8UL << 7U),
    COMP5_CTRL_OUTSEL_TIM8_OCrefclear     	= (0x9UL << 7U),
    COMP5_CTRL_OUTSEL_TIM8_BKIN           	= (0xAUL << 7U),
    COMP5_CTRL_OUTSEL_TIM1_BKIN_TIM8_BKIN 	= (0xBUL << 7U),
	
    /* comp6 out trig */
    COMP6_CTRL_OUTSEL_NC                  	= (0x0UL << 7U),
    COMP6_CTRL_OUTSEL_TIM1_BKIN           	= (0x1UL << 7U),
    COMP6_CTRL_OUTSEL_TIM2_IC1            	= (0x2UL << 7U),
    COMP6_CTRL_OUTSEL_TIM2_OCrefclear     	= (0x3UL << 7U),
    COMP6_CTRL_OUTSEL_TIM3_IC1            	= (0x4UL << 7U),
    COMP6_CTRL_OUTSEL_TIM3_OCrefclear     	= (0x5UL << 7U),
    COMP6_CTRL_OUTSEL_TIM5_IC1            	= (0x6UL << 7U),
    COMP6_CTRL_OUTSEL_TIM8_IC1            	= (0x8UL << 7U),
    COMP6_CTRL_OUTSEL_TIM8_OCrefclear     	= (0x9UL << 7U),
    COMP6_CTRL_OUTSEL_TIM8_BKIN           	= (0xAUL << 7U),
    COMP6_CTRL_OUTSEL_TIM1_BKIN_TIM8_BKIN 	= (0xBUL << 7U),
	
    /* comp7 out trig */
    COMP7_CTRL_OUTSEL_NC                  	= (0x0UL << 7U),
    COMP7_CTRL_OUTSEL_TIM1_BKIN           	= (0x1UL << 7U),
    COMP7_CTRL_OUTSEL_TIM2_IC1            	= (0x2UL << 7U),
    COMP7_CTRL_OUTSEL_TIM2_OCrefclear     	= (0x3UL << 7U),
    COMP7_CTRL_OUTSEL_TIM3_IC1            	= (0x4UL << 7U),
    COMP7_CTRL_OUTSEL_TIM3_OCrefclear     	= (0x5UL << 7U),
    COMP7_CTRL_OUTSEL_TIM5_IC1            	= (0x6UL << 7U),
    COMP7_CTRL_OUTSEL_TIM8_IC1            	= (0x8UL << 7U),
    COMP7_CTRL_OUTSEL_TIM8_OCrefclear     	= (0x9UL << 7U),
    COMP7_CTRL_OUTSEL_TIM8_BKIN           	= (0xAUL << 7U),
    COMP7_CTRL_OUTSEL_TIM1_BKIN_TIM8_BKIN 	= (0xBUL << 7U),
} COMP_CTRL_OUTTRIG_Type;


/** @def COMP_CTRL_INPSEL_Type COMP CTRL INPSEL Type
 */
typedef enum {
	COMPX_CTRL_INPSEL_RES					= (0x7UL << 4U),	/* Reserved */
	
	/* comp1 inp sel */
	COMP1_CTRL_INPSEL_PA1					= (0x0UL << 4U),
	COMP1_CTRL_INPSEL_PB10					= (0x1UL << 4U),
	
	/* comp2 inp sel */
	COMP2_CTRL_INPSEL_PA1					= (0x0UL << 4U),
	COMP2_CTRL_INPSEL_PB11					= (0x1UL << 4U),
	COMP2_CTRL_INPSEL_PA7					= (0x2UL << 4U),
	
	/* comp3 inp sel */
	COMP3_CTRL_INPSEL_PB14					= (0x0UL << 4U),
	COMP3_CTRL_INPSEL_PB0					= (0x1UL << 4U),
	
	/* comp4 inp sel */
	COMP4_CTRL_INPSEL_PB14					= (0x0UL << 4U),
	COMP4_CTRL_INPSEL_PB0					= (0x1UL << 4U),
	COMP4_CTRL_INPSEL_PC9					= (0x2UL << 4U),
	COMP4_CTRL_INPSEL_PB15					= (0x3UL << 4U),
	
	/* comp5 inp sel */
	COMP5_CTRL_INPSEL_PC4					= (0x0UL << 4U),
	COMP5_CTRL_INPSEL_PC3					= (0x1UL << 4U),
	COMP5_CTRL_INPSEL_PA3					= (0x2UL << 4U),
	
	/* comp6 inp sel */
	COMP6_CTRL_INPSEL_PC4					= (0x0UL << 4U),
	COMP6_CTRL_INPSEL_PC3					= (0x1UL << 4U),
	COMP6_CTRL_INPSEL_PC5					= (0x2UL << 4U),
	COMP6_CTRL_INPSEL_PD9					= (0x3UL << 4U),
	
	/* comp7 inp sel */
	COMP7_CTRL_INPSEL_PC1					= (0x0UL << 4U),
}COMP_CTRL_INPSEL_Type;

/** @def COMP_CTRL_INMSEL_Type COMP CTRL INMSEL Type
 */
typedef enum {
	COMPX_CTRL_INMSEL_RES					= (0x7UL << 1U),	/* Reserved */
	
	/* comp1 inm sel */
	COMP1_CTRL_INMSEL_PA0					= (0x0UL << 1U),
	COMP1_CTRL_INMSEL_DAC1_PA4				= (0x1UL << 1U),
	COMP1_CTRL_INMSEL_DAC2_PA5				= (0x2UL << 1U),
	COMP1_CTRL_INMSEL_VERF1					= (0x3UL << 1U),
	COMP1_CTRL_INMSEL_VERF2					= (0x4UL << 1U),
	
	/* comp2 inm sel */
	COMP2_CTRL_INMSEL_PB1					= (0x0UL << 1U),
	COMP2_CTRL_INMSEL_PE8					= (0x1UL << 1U),
	COMP2_CTRL_INMSEL_DAC1_PA4				= (0x2UL << 1U),
	COMP2_CTRL_INMSEL_DAC2_PA5				= (0x3UL << 1U),
	COMP2_CTRL_INMSEL_VERF1					= (0x4UL << 1U),
	COMP2_CTRL_INMSEL_VERF2					= (0x5UL << 1U),
	
	/* comp3 inm sel */
	COMP3_CTRL_INMSEL_PB12					= (0x0UL << 1U),
	COMP3_CTRL_INMSEL_PE7					= (0x1UL << 1U),
	COMP3_CTRL_INMSEL_DAC1_PA4				= (0x2UL << 1U),
	COMP3_CTRL_INMSEL_DAC2_PA5				= (0x3UL << 1U),
	COMP3_CTRL_INMSEL_VERF1					= (0x4UL << 1U),
	COMP3_CTRL_INMSEL_VERF2					= (0x5UL << 1U),
	
	/* comp4 inm sel */
	COMP4_CTRL_INMSEL_PC4					= (0x0UL << 1U),
	COMP4_CTRL_INMSEL_PB13					= (0x1UL << 1U),
	COMP4_CTRL_INMSEL_DAC1_PA4				= (0x2UL << 1U),
	COMP4_CTRL_INMSEL_DAC2_PA5				= (0x3UL << 1U),
	COMP4_CTRL_INMSEL_VERF1					= (0x4UL << 1U),
	COMP4_CTRL_INMSEL_VERF2					= (0x5UL << 1U),
	
	/* comp5 inm sel */
	COMP5_CTRL_INMSEL_PB10					= (0x0UL << 1U),
	COMP5_CTRL_INMSEL_PD10					= (0x1UL << 1U),
	COMP5_CTRL_INMSEL_DAC1_PA4				= (0x2UL << 1U),
	COMP5_CTRL_INMSEL_DAC2_PA5				= (0x3UL << 1U),
	COMP5_CTRL_INMSEL_VERF1					= (0x4UL << 1U),
	COMP5_CTRL_INMSEL_VERF2					= (0x5UL << 1U),
	
	/* comp6 inm sel */
	COMP6_CTRL_INMSEL_PA7					= (0x0UL << 1U),
	COMP6_CTRL_INMSEL_PD8					= (0x1UL << 1U),
	COMP6_CTRL_INMSEL_DAC1_PA4				= (0x2UL << 1U),
	COMP6_CTRL_INMSEL_DAC2_PA5				= (0x3UL << 1U),
	COMP6_CTRL_INMSEL_VERF1					= (0x4UL << 1U),
	COMP6_CTRL_INMSEL_VERF2					= (0x5UL << 1U),
	
	/* comp7 inm sel */
	COMP7_CTRL_INMSEL_PC0					= (0x0UL << 1U),
	COMP7_CTRL_INMSEL_DAC1_PA4				= (0x1UL << 1U),
	COMP7_CTRL_INMSEL_DAC2_PA5				= (0x2UL << 1U),
	COMP7_CTRL_INMSEL_VERF1					= (0x3UL << 1U),
	COMP7_CTRL_INMSEL_VERF2					= (0x4UL << 1U),
}COMP_CTRL_INMSEL_Type;

#define IS_COMP_VREFxSET(VvxTrim)	((VvxTrim) <= 63U)

/**
 * @}
 */

/**@defgroup COMP_Exported_Types COMP Exported Types
* @brief  COMP Init structure definition
* @{
*/

typedef struct
{
    /* ctrl */
	bool InpDacConnect;				/* only COMP1 have this bit */

    COMP_CTRL_BLKING_Type Blking;	/*see @ref COMP_CTRL_BLKING_Type */

    COMP_CTRL_HYST_Type Hyst;

    bool PolRev;					/* out polarity reverse */

    COMP_CTRL_OUTTRIG_Type OutSel;
    COMP_CTRL_INPSEL_Type InpSel;
    COMP_CTRL_INMSEL_Type InmSel;

    bool En;

    /* filter */
    uint8_t SampWindow;				/* 5bit */
    uint8_t Thresh;					/* 5bit, need > SampWindow/2 */
    bool FilterEn;

    /* filter psc */
    uint16_t ClkPsc;
} COMP_InitType;
/**
 * @}
 */




/** @defgroup COMP_Exported_Functions COMP Exported Functions
 * @{
 */

void		COMP_DeInit (void);
void		COMP_StructInit (COMP_InitType* COMP_InitStruct);
void		COMP_Init (COMP_PeriphType COMPx, COMP_InitType* COMP_InitStruct);
void		COMP_Enable (COMP_PeriphType COMPx, FunctionalState Cmd);
void		COMP_SetInpSel (COMP_PeriphType COMPx, COMP_CTRL_INPSEL_Type VpSel);
void		COMP_SetInmSel (COMP_PeriphType COMPx, COMP_CTRL_INMSEL_Type VmSel);
void		COMP_SetOutTrig (COMP_PeriphType COMPx, COMP_CTRL_OUTTRIG_Type OutTrig);
void		COMP_SetLock (uint32_t Lock);                                              /* see @COMP_LOCK_CMPLK */
void		COMP_SetIntEn (uint32_t IntEn);                                            /* see @COMP_INTEN_CMPIEN */
uint32_t	COMP_GetIntSts (void);                                                 	   /* return see @COMP_INTSTS_CMPIS */
void		COMP_SetRefScl (uint8_t Vv2Trim, bool Vv2En, uint8_t Vv1Trim, bool Vv1En); /* parma range see @COMP_VREFSCL */
FlagStatus	COMP_GetOutStatus (COMP_PeriphType COMPx);
FlagStatus	COMP_GetIntStsOneComp (COMP_PeriphType COMPx);
void		COMP_SetFilterPrescaler (COMP_PeriphType COMPx, uint16_t FilPreVal);
void		COMP_SetFilterControl (COMP_PeriphType COMPx, uint8_t FilEn, uint8_t TheresNum, uint8_t SampPW);
void		COMP_SetHyst (COMP_PeriphType COMPx, COMP_CTRL_HYST_Type HYST);
void		COMP_SetBlanking (COMP_PeriphType COMPx, COMP_CTRL_BLKING_Type BLK);
/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /*__CM32M4xxR_COMP_H */
/**
 * @}
 */
/**
 * @}
 */

