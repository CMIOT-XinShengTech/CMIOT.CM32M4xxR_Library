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
 * @file cm32m4xxr_exti.h
 * @author CMIOT Firmware Team
 * @version v1.0.0
 * @brief Header file containing functions prototypes of CAN StdPeriph Library.
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */
#ifndef __CM32M4xxR_EXTI_H__
#define __CM32M4xxR_EXTI_H__

#ifdef __cplusplus
extern "C" {
#endif


/** @addtogroup CM32M4xxR_StdPeriph_Driver
 * @{
 */

/** @addtogroup EXTI
 * @{
 */

/* Exported types ------------------------------------------------------------*/
/** @defgroup EXTI_Exported_Types EXTI Exported Types
 * @{
 */

/**
 * @brief  EXTI mode enumeration
 */

typedef enum
{
    EXTI_Mode_Interrupt		= 0x00,
    EXTI_Mode_Event			= 0x04
} EXTI_ModeType;


/**
 * @brief  EXTI Trigger enumeration
 */

typedef enum
{
    EXTI_Trigger_Rising				= 0x08,
    EXTI_Trigger_Falling			= 0x0C,
    EXTI_Trigger_Rising_Falling		= 0x10
} EXTI_TriggerType;

/**
 * @brief  EXTI Init Structure definition
 */

typedef struct
{
    uint32_t			EXTI_Line; 		/*!< Specifies the EXTI lines to be enabled or disabled.
											This parameter can be a value of @ref EXTI_Lines */

    EXTI_ModeType		EXTI_Mode; 		/*!< Specifies the mode for the EXTI lines.
											This parameter can be a value of @ref EXTI_ModeType */

    EXTI_TriggerType	EXTI_Trigger;	/*!< Specifies the trigger signal active edge for the EXTI lines.
											This parameter can be a value of @ref EXTI_TriggerType */

    FunctionalState		EXTI_LineCmd;	/*!< Specifies the new state of the selected EXTI lines.
											This parameter can be set either to ENABLE or DISABLE */
} EXTI_InitType;

/**
 * @}
 */

/** @defgroup EXTI_Exported_Constants EXTI Exported Constants
 * @{
 */

/**
  * @brief  EXTI Line property definition
  */
#define EXTI_PROPERTY_SHIFT                 (24U)
#define EXTI_CONFIG                         (0x02UL << EXTI_PROPERTY_SHIFT)
#define EXTI_GPIO                           ((0x04UL << EXTI_PROPERTY_SHIFT) | EXTI_CONFIG)
#define EXTI_RESERVED                       (0x08UL << EXTI_PROPERTY_SHIFT)
#define EXTI_PROPERTY_MASK                  (EXTI_CONFIG | EXTI_GPIO)

/**
  * @brief  EXTI bit usage
  */
#define EXTI_PIN_MASK                       (0x0000001FUL)

/**
  * @brief  EXTI Line number
  */
#define EXTI_LINE_NB                        (22U)


/** @addtogroup EXTI_Lines
 * @{
 */
#define EXTI_LINENONE			((uint32_t) 0x00000000)
#define EXTI_LINE0 				(EXTI_GPIO     | 0x00UL)	/*!< External interrupt line 0 */
#define EXTI_LINE1 				(EXTI_GPIO     | 0x01UL)	/*!< External interrupt line 1 */
#define EXTI_LINE2 				(EXTI_GPIO     | 0x02UL)	/*!< External interrupt line 2 */
#define EXTI_LINE3 				(EXTI_GPIO     | 0x03UL)	/*!< External interrupt line 3 */
#define EXTI_LINE4 				(EXTI_GPIO     | 0x04UL)	/*!< External interrupt line 4 */
#define EXTI_LINE5 				(EXTI_GPIO     | 0x05UL)	/*!< External interrupt line 5 */
#define EXTI_LINE6 				(EXTI_GPIO     | 0x06UL)	/*!< External interrupt line 6 */
#define EXTI_LINE7 				(EXTI_GPIO     | 0x07UL)	/*!< External interrupt line 7 */
#define EXTI_LINE8 				(EXTI_GPIO     | 0x08UL)	/*!< External interrupt line 8 */
#define EXTI_LINE9 				(EXTI_GPIO     | 0x09UL)	/*!< External interrupt line 9 */
#define EXTI_LINE10				(EXTI_GPIO     | 0x0AUL)	/*!< External interrupt line 10 */
#define EXTI_LINE11				(EXTI_GPIO     | 0x0BUL)	/*!< External interrupt line 11 */
#define EXTI_LINE12				(EXTI_GPIO     | 0x0CUL)	/*!< External interrupt line 12 */
#define EXTI_LINE13				(EXTI_GPIO     | 0x0DUL)	/*!< External interrupt line 13 */
#define EXTI_LINE14				(EXTI_GPIO     | 0x0EUL)	/*!< External interrupt line 14 */
#define EXTI_LINE15				(EXTI_GPIO     | 0x0FUL)	/*!< External interrupt line 15 */

#define EXTI_LINE16				(EXTI_CONFIG   | 0x10UL)	/*!< External interrupt line 16 Connected to the PVD Output */
#define EXTI_LINE17				(EXTI_CONFIG   | 0x11UL)	/*!< External interrupt line 17 Connected to the RTC Alarm event */

#define EXTI_LINE18				(EXTI_RESERVED | 0x12UL)	/*!< No interrupt supported in this line(Reserved) */
#define EXTI_LINE19				(EXTI_RESERVED | 0x13UL)	/*!< No interrupt supported in this line(Reserved) */

#define EXTI_LINE20				(EXTI_CONFIG   | 0x14UL)	/*!< External interrupt line 20 Connected to the RTC Wakeup event */
#define EXTI_LINE21				(EXTI_CONFIG   | 0x15UL)	/*!< External interrupt line 21 Connected to the TSC event */

/**
 * @}
 */


/**
 * @}
 */

/** @defgroup EXTI_Private_Macros EXTI Private Macros
 * @{
 */
#define IS_EXTI_MODE(MODE)	(((MODE) == EXTI_Mode_Interrupt) || ((MODE) == EXTI_Mode_Event))

#define IS_EXTI_TRIGGER(TRIGGER)	(((TRIGGER) == EXTI_Trigger_Rising) || ((TRIGGER) == EXTI_Trigger_Falling) || \
									 ((TRIGGER) == EXTI_Trigger_Rising_Falling))

#define IS_EXTI_LINE(LINE)		((((LINE) & ~(EXTI_PROPERTY_MASK | EXTI_PIN_MASK)) == 0x00u) && \
                                ((((LINE) & EXTI_PROPERTY_MASK) == EXTI_CONFIG)              || \
                                 (((LINE) & EXTI_PROPERTY_MASK) == EXTI_GPIO))               && \
                                 (((LINE) & EXTI_PIN_MASK) < EXTI_LINE_NB))
								 
#define IS_GET_EXTI_LINE(LINE)	(((LINE) == EXTI_LINE0)  || ((LINE) == EXTI_LINE1)  || ((LINE) == EXTI_LINE2)  || \
								 ((LINE) == EXTI_LINE3)  || ((LINE) == EXTI_LINE4)  || ((LINE) == EXTI_LINE5)  || \
								 ((LINE) == EXTI_LINE6)  || ((LINE) == EXTI_LINE7)  || ((LINE) == EXTI_LINE8)  || \
								 ((LINE) == EXTI_LINE9)  || ((LINE) == EXTI_LINE10) || ((LINE) == EXTI_LINE11) || \
								 ((LINE) == EXTI_LINE12) || ((LINE) == EXTI_LINE13) || ((LINE) == EXTI_LINE14) || \
								 ((LINE) == EXTI_LINE15) || ((LINE) == EXTI_LINE16) || ((LINE) == EXTI_LINE17) || \
								 ((LINE) == EXTI_LINE20) || ((LINE) == EXTI_LINE21))

#define IS_EXTI_TSSEL_LINE(LINE)	(((LINE) == EXTI_TS_SEL_TSSEL_LINE0)  || ((LINE) == EXTI_TS_SEL_TSSEL_LINE1)  || \
									 ((LINE) == EXTI_TS_SEL_TSSEL_LINE2)  || ((LINE) == EXTI_TS_SEL_TSSEL_LINE3)  || \
									 ((LINE) == EXTI_TS_SEL_TSSEL_LINE4)  || ((LINE) == EXTI_TS_SEL_TSSEL_LINE5)  || \
									 ((LINE) == EXTI_TS_SEL_TSSEL_LINE6)  || ((LINE) == EXTI_TS_SEL_TSSEL_LINE7)  || \
									 ((LINE) == EXTI_TS_SEL_TSSEL_LINE8)  || ((LINE) == EXTI_TS_SEL_TSSEL_LINE9)  || \
									 ((LINE) == EXTI_TS_SEL_TSSEL_LINE10) || ((LINE) == EXTI_TS_SEL_TSSEL_LINE11) || \
									 ((LINE) == EXTI_TS_SEL_TSSEL_LINE12) || ((LINE) == EXTI_TS_SEL_TSSEL_LINE13) || \
									 ((LINE) == EXTI_TS_SEL_TSSEL_LINE14) || ((LINE) == EXTI_TS_SEL_TSSEL_LINE15))

/**
 * @}
 */

/** @defgroup EXTI_Exported_Functions EXTI Exported Functions
 * @{
 */

void		EXTI_DeInit (void);
void		EXTI_Init (EXTI_InitType* EXTI_InitStruct);
void		EXTI_InitStruct (EXTI_InitType* EXTI_InitStruct);
void		EXTI_TriggerSWInt (uint32_t EXTI_Line);
FlagStatus	EXTI_GetStatusFlag (uint32_t EXTI_Line);
void		EXTI_ClrStatusFlag (uint32_t EXTI_Line);
INTStatus	EXTI_GetITStatus (uint32_t EXTI_Line);
void		EXTI_ClrITPendBit (uint32_t EXTI_Line);
void		EXTI_RTCTimeStampSel (uint32_t EXTI_TSSEL_Line);
/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __CM32M4xxR_EXTI_H__ */

/**
 * @}
 */

/**
 * @}
 */
