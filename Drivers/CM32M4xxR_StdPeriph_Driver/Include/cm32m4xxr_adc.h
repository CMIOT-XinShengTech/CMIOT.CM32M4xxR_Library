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
 * @file cm32m4xxr_adc.h
 * @author CMIOT Firmware Team
 * @version v1.0.1
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */
#ifndef __CM32M4xxR_ADC_H__
#define __CM32M4xxR_ADC_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup CM32M4xxR_StdPeriph_Driver
 * @{
 */
/** @addtogroup ADC
 * @{
 */

/** @defgroup ADC_Exported_Types ADC Exported Types
 * @{
 */

/**
 * @brief  ADC Init structure definition
 */
typedef struct
{
	uint32_t WorkMode;				/*!< Configures the ADC to operate in independent or
										dual mode. This parameter can be a value of @ref ADC_mode */

    FunctionalState MultiChEn;		/*!< Specifies whether the conversion is performed in
										Scan (multichannels) or Single (one channel) mode.
										This parameter can be set to ENABLE or DISABLE */

    FunctionalState ContinueConvEn;	/*!< Specifies whether the conversion is performed in
										Continuous or Single mode. This parameter can be set to ENABLE or DISABLE. */

    uint32_t ExtTrigSelect;			/*!< Defines the external trigger used to start the analog
										to digital conversion of regular channels. This parameter can be a value 
										of @ref	ADC_external_trigger_sources_for_regular_channels_conversion */

    uint32_t DatAlign;				/*!< Specifies whether the ADC data alignment is left or right.
										This parameter can be a value of @ref ADC_data_align */

    uint8_t ChsNumber;				/*!< Specifies the number of ADC channels that will be converted
										using the sequencer for regular channel group.
										This parameter must range from 1 to 16. */
} ADC_InitType;
/**
 * @}
 */

/** @defgroup ADC_Exported_Constants ADC Exported Constants
 * @{
 */

#define IsAdcModule(PERIPH) (((PERIPH) == ADC1) || ((PERIPH) == ADC2) || ((PERIPH) == ADC3) || ((PERIPH) == ADC4))

#define IsAdcDmaModule(PERIPH) (((PERIPH) == ADC1) || ((PERIPH) == ADC2) || ((PERIPH) == ADC3) || ((PERIPH) == ADC4))


#define VREF1P2_CTRL	(*(uint32_t *)(0x40001820))
#define _EnVref1p2() \
	do{ \
		VREF1P2_CTRL |= (0x01L << 10); \
	}while(0)
#define _DisVref1p2() \
	do{ \
		VREF1P2_CTRL &= ~(0x01L << 10); \
	}while(0)
	

/** @defgroup ADC_mode ADC mode
 * @{
 */

#define ADC_WORKMODE_INDEPENDENT            ((uint32_t)0x00000000)
#define ADC_WORKMODE_REG_INJECT_SIMULT      ((uint32_t)0x00010000)
#define ADC_WORKMODE_REG_SIMULT_ALTER_TRIG  ((uint32_t)0x00020000)
#define ADC_WORKMODE_INJ_SIMULT_FAST_INTERL ((uint32_t)0x00030000)
#define ADC_WORKMODE_INJ_SIMULT_SLOW_INTERL ((uint32_t)0x00040000)
#define ADC_WORKMODE_INJ_SIMULT             ((uint32_t)0x00050000)
#define ADC_WORKMODE_REG_SIMULT             ((uint32_t)0x00060000)
#define ADC_WORKMODE_FAST_INTERL            ((uint32_t)0x00070000)
#define ADC_WORKMODE_SLOW_INTERL            ((uint32_t)0x00080000)
#define ADC_WORKMODE_ALTER_TRIG             ((uint32_t)0x00090000)

#define IsAdcWorkMode(MODE)		(((MODE) == ADC_WORKMODE_INDEPENDENT)            || ((MODE) == ADC_WORKMODE_REG_INJECT_SIMULT)      || \
								 ((MODE) == ADC_WORKMODE_REG_SIMULT_ALTER_TRIG)  || ((MODE) == ADC_WORKMODE_INJ_SIMULT_FAST_INTERL) || \
								 ((MODE) == ADC_WORKMODE_INJ_SIMULT_SLOW_INTERL) || ((MODE) == ADC_WORKMODE_INJ_SIMULT)             || \
								 ((MODE) == ADC_WORKMODE_REG_SIMULT)             || ((MODE) == ADC_WORKMODE_FAST_INTERL)            || \
								 ((MODE) == ADC_WORKMODE_SLOW_INTERL)            || ((MODE) == ADC_WORKMODE_ALTER_TRIG))
/**
 * @}
 */

/** @defgroup ADC_external_trigger_sources_for_regular_channels_conversion ADC external trigger sources for regular channels conversion
 * @{
 */

#define ADC_EXT_TRIGCONV_T1_CC1             	((uint32_t) 0x00000000) /*!< For ADC1 and ADC2 */
#define ADC_EXT_TRIGCONV_T1_CC2             	((uint32_t) 0x00020000) /*!< For ADC1 and ADC2 */
#define ADC_EXT_TRIGCONV_T2_CC2             	((uint32_t) 0x00060000) /*!< For ADC1 and ADC2 */
#define ADC_EXT_TRIGCONV_T3_TRGO            	((uint32_t) 0x00080000) /*!< For ADC1 and ADC2 */
#define ADC_EXT_TRIGCONV_T4_CC4             	((uint32_t) 0x000A0000) /*!< For ADC1 and ADC2 */
#define ADC_EXT_TRIGCONV_EXT_INT11_TIM8_TRGO	((uint32_t) 0x000C0000) /*!< For ADC1 and ADC2 */

#define ADC_EXT_TRIGCONV_T1_CC3					((uint32_t) 0x00040000) /*!< For ADC1, ADC2, ADC3 and ADC4 */
#define ADC_EXT_TRIGCONV_NONE					((uint32_t) 0x000E0000) /*!< For ADC1, ADC2, ADC3 and ADC4(SWSTRRCH) */
														    
#define ADC_EXT_TRIGCONV_T3_CC1 				((uint32_t) 0x00000000) /*!< For ADC3 and ADC4 */
#define ADC_EXT_TRIGCONV_T2_CC3 				((uint32_t) 0x00020000) /*!< For ADC3 and ADC4 */
#define ADC_EXT_TRIGCONV_T8_CC1 				((uint32_t) 0x00060000) /*!< For ADC3 and ADC4 */
#define ADC_EXT_TRIGCONV_T8_TRGO				((uint32_t) 0x00080000) /*!< For ADC3 and ADC4 */
#define ADC_EXT_TRIGCONV_T5_CC1 				((uint32_t) 0x000A0000) /*!< For ADC3 and ADC4 */
#define ADC_EXT_TRIGCONV_EXT_INT10_T5_CC3		((uint32_t) 0x000C0000) /*!< For ADC3 and ADC4 */

#define IsAdcExtTrig(REGTRIG)		(((REGTRIG) == ADC_EXT_TRIGCONV_T1_CC1)              || ((REGTRIG) == ADC_EXT_TRIGCONV_T1_CC2)  || \
									 ((REGTRIG) == ADC_EXT_TRIGCONV_T1_CC3)              || ((REGTRIG) == ADC_EXT_TRIGCONV_T2_CC2)  || \
									 ((REGTRIG) == ADC_EXT_TRIGCONV_T3_TRGO)             || ((REGTRIG) == ADC_EXT_TRIGCONV_T4_CC4)  || \
									 ((REGTRIG) == ADC_EXT_TRIGCONV_EXT_INT11_TIM8_TRGO) || ((REGTRIG) == ADC_EXT_TRIGCONV_NONE)    || \
									 ((REGTRIG) == ADC_EXT_TRIGCONV_T3_CC1)              || ((REGTRIG) == ADC_EXT_TRIGCONV_T2_CC3)  || \
									 ((REGTRIG) == ADC_EXT_TRIGCONV_T8_CC1)              || ((REGTRIG) == ADC_EXT_TRIGCONV_T8_TRGO) || \
									 ((REGTRIG) == ADC_EXT_TRIGCONV_T5_CC1)              || ((REGTRIG) == ADC_EXT_TRIGCONV_EXT_INT10_T5_CC3))
/**
 * @}
 */

/** @defgroup ADC_data_align ADC data align
 * @{
 */

#define ADC_DAT_ALIGN_R			((uint32_t) 0x00000000)
#define ADC_DAT_ALIGN_L			((uint32_t) 0x00000800)
#define IsAdcDatAlign(ALIGN)	(((ALIGN) == ADC_DAT_ALIGN_R) || ((ALIGN) == ADC_DAT_ALIGN_L))
/**
 * @}
 */

/** @defgroup ADC_channels ADC channels
 * @{
 */

#define ADC_CH_0 				((uint8_t) 0x00)
#define ADC_CH_1 				((uint8_t) 0x01)
#define ADC_CH_2 				((uint8_t) 0x02)
#define ADC_CH_3 				((uint8_t) 0x03)
#define ADC_CH_4 				((uint8_t) 0x04)
#define ADC_CH_5 				((uint8_t) 0x05)
#define ADC_CH_6 				((uint8_t) 0x06)
#define ADC_CH_7 				((uint8_t) 0x07)
#define ADC_CH_8 				((uint8_t) 0x08)
#define ADC_CH_9 				((uint8_t) 0x09)
#define ADC_CH_10				((uint8_t) 0x0A)
#define ADC_CH_11				((uint8_t) 0x0B)
#define ADC_CH_12				((uint8_t) 0x0C)
#define ADC_CH_13				((uint8_t) 0x0D)
#define ADC_CH_14				((uint8_t) 0x0E)
#define ADC_CH_15				((uint8_t) 0x0F)
#define ADC_CH_16				((uint8_t) 0x10)
#define ADC_CH_17				((uint8_t) 0x11)
#define ADC_CH_18				((uint8_t) 0x12)

#define ADC_CH_TEMP_SENSOR		((uint8_t) ADC_CH_16)
#define ADC_CH_INT_VREF   		((uint8_t) ADC_CH_18)

#define IsAdcChannel(CHANNEL)	(((CHANNEL) == ADC_CH_0)  || ((CHANNEL) == ADC_CH_1)  || ((CHANNEL) == ADC_CH_2)  || \
								 ((CHANNEL) == ADC_CH_3)  || ((CHANNEL) == ADC_CH_4)  || ((CHANNEL) == ADC_CH_5)  || \
								 ((CHANNEL) == ADC_CH_6)  || ((CHANNEL) == ADC_CH_7)  || ((CHANNEL) == ADC_CH_8)  || \
								 ((CHANNEL) == ADC_CH_9)  || ((CHANNEL) == ADC_CH_10) || ((CHANNEL) == ADC_CH_11) || \
								 ((CHANNEL) == ADC_CH_12) || ((CHANNEL) == ADC_CH_13) || ((CHANNEL) == ADC_CH_14) || \
								 ((CHANNEL) == ADC_CH_15) || ((CHANNEL) == ADC_CH_16) || ((CHANNEL) == ADC_CH_17) || \
								 ((CHANNEL) == ADC_CH_18))
/**
 * @}
 */

/** @defgroup ADC_sampling_time ADC sampling time
 * @{
 */

#define ADC_SAMP_TIME_1CYCLES5  	((uint8_t) 0x00)/* 1.5cycles when SAMPSEL is 0,   1.5cycles when SAMPSEL is 0,*/
#define ADC_SAMP_TIME_7CYCLES5  	((uint8_t) 0x01)/* 7.5cycles when SAMPSEL is 0,   2.5cycles when SAMPSEL is 0,*/
#define ADC_SAMP_TIME_13CYCLES5 	((uint8_t) 0x02)/* 13.5cycles when SAMPSEL is 0,  4.5cycles when SAMPSEL is 0,*/
#define ADC_SAMP_TIME_28CYCLES5 	((uint8_t) 0x03)/* 28.5cycles when SAMPSEL is 0,  7.5cycles when SAMPSEL is 0,*/
#define ADC_SAMP_TIME_41CYCLES5 	((uint8_t) 0x04)/* 41.5cycles when SAMPSEL is 0,  19.5cycles when SAMPSEL is 0,*/
#define ADC_SAMP_TIME_55CYCLES5 	((uint8_t) 0x05)/* 55.5cycles when SAMPSEL is 0,  61.5cycles when SAMPSEL is 0,*/
#define ADC_SAMP_TIME_71CYCLES5 	((uint8_t) 0x06)/* 71.5cycles when SAMPSEL is 0,  181.5cycles when SAMPSEL is 0,*/
#define ADC_SAMP_TIME_239CYCLES5	((uint8_t) 0x07)/* 239.5cycles when SAMPSEL is 0, 601.5cycles when SAMPSEL is 0,*/

#define IsAdcSampleTime(TIME)		(((TIME) == ADC_SAMP_TIME_1CYCLES5)  || ((TIME) == ADC_SAMP_TIME_7CYCLES5)  || \
									 ((TIME) == ADC_SAMP_TIME_13CYCLES5) || ((TIME) == ADC_SAMP_TIME_28CYCLES5) || \
									 ((TIME) == ADC_SAMP_TIME_41CYCLES5) || ((TIME) == ADC_SAMP_TIME_55CYCLES5) || \
									 ((TIME) == ADC_SAMP_TIME_71CYCLES5) || ((TIME) == ADC_SAMP_TIME_239CYCLES5))
/**
 * @}
 */

/** @defgroup ADC_external_trigger_sources_for_injected_channels_conversion ADC external trigger sources for injected channels conversion
 * @{
 */

#define ADC_EXT_TRIG_INJ_CONV_T2_TRGO           	((uint32_t) 0x00002000) /*!< For ADC1 and ADC2 */
#define ADC_EXT_TRIG_INJ_CONV_T2_CC1            	((uint32_t) 0x00003000) /*!< For ADC1 and ADC2 */
#define ADC_EXT_TRIG_INJ_CONV_T3_CC4            	((uint32_t) 0x00004000) /*!< For ADC1 and ADC2 */
#define ADC_EXT_TRIG_INJ_CONV_T4_TRGO           	((uint32_t) 0x00005000) /*!< For ADC1 and ADC2 */
#define ADC_EXT_TRIG_INJ_CONV_EXT_INT15_TIM8_CC4	((uint32_t) 0x00006000) /*!< For ADC1 and ADC2 */

#define ADC_EXT_TRIG_INJ_CONV_T1_TRGO				((uint32_t) 0x00000000) /*!< For ADC1, ADC2, ADC3 and ADC4 */
#define ADC_EXT_TRIG_INJ_CONV_T1_CC4 				((uint32_t) 0x00001000) /*!< For ADC1, ADC2, ADC3 and ADC4 */
#define ADC_EXT_TRIG_INJ_CONV_NONE   				((uint32_t) 0x00007000) /*!< For ADC1, ADC2, ADC3 and ADC4 */
															    
#define ADC_EXT_TRIG_INJ_CONV_T4_CC3 				((uint32_t) 0x00002000) /*!< For ADC3 and ADC4 */
#define ADC_EXT_TRIG_INJ_CONV_T8_CC2 				((uint32_t) 0x00003000) /*!< For ADC3 and ADC4 */
#define ADC_EXT_TRIG_INJ_CONV_T8_CC4 				((uint32_t) 0x00004000) /*!< For ADC3 and ADC4 */
#define ADC_EXT_TRIG_INJ_CONV_T5_TRGO				((uint32_t) 0x00005000) /*!< For ADC3 and ADC4 */
#define ADC_EXT_TRIG_INJ_CONV_EXT_INT14_T5_CC4		((uint32_t) 0x00006000) /*!< For ADC3 and ADC4 */

#define IsAdcExtInjTrig(INJTRIG)		(((INJTRIG) == ADC_EXT_TRIG_INJ_CONV_T1_TRGO)            || ((INJTRIG) == ADC_EXT_TRIG_INJ_CONV_T1_CC4)  || \
										 ((INJTRIG) == ADC_EXT_TRIG_INJ_CONV_T2_TRGO)            || ((INJTRIG) == ADC_EXT_TRIG_INJ_CONV_T2_CC1)  || \
										 ((INJTRIG) == ADC_EXT_TRIG_INJ_CONV_T3_CC4)             || ((INJTRIG) == ADC_EXT_TRIG_INJ_CONV_T4_TRGO) || \
										 ((INJTRIG) == ADC_EXT_TRIG_INJ_CONV_EXT_INT15_TIM8_CC4) || ((INJTRIG) == ADC_EXT_TRIG_INJ_CONV_NONE)    || \
										 ((INJTRIG) == ADC_EXT_TRIG_INJ_CONV_T4_CC3)             || ((INJTRIG) == ADC_EXT_TRIG_INJ_CONV_T8_CC2)  || \
										 ((INJTRIG) == ADC_EXT_TRIG_INJ_CONV_T8_CC4)             || ((INJTRIG) == ADC_EXT_TRIG_INJ_CONV_T5_TRGO) || \
										 ((INJTRIG) == ADC_EXT_TRIG_INJ_CONV_EXT_INT14_T5_CC4))
/**
 * @}
 */

/** @defgroup ADC_injected_channel_selection ADC injected channel selection
 * @{
 */

#define ADC_INJ_CH_1		((uint8_t) 0x14)
#define ADC_INJ_CH_2		((uint8_t) 0x18)
#define ADC_INJ_CH_3		((uint8_t) 0x1C)
#define ADC_INJ_CH_4		((uint8_t) 0x20)
#define IsAdcInjCh(CHANNEL)	(((CHANNEL) == ADC_INJ_CH_1) || ((CHANNEL) == ADC_INJ_CH_2) || \
							 ((CHANNEL) == ADC_INJ_CH_3) || ((CHANNEL) == ADC_INJ_CH_4))
/**
 * @}
 */

/** @defgroup ADC_analog_watchdog_selection ADC analog watchdog selection
 * @{
 */

#define ADC_ANALOG_WTDG_SINGLEREG_ENABLE         	((uint32_t) 0x00800200) /* Bit23: Analog watchdog enable on regular channels */
#define ADC_ANALOG_WTDG_SINGLEINJEC_ENABLE       	((uint32_t) 0x00400200) /* Bit22: Analog watchdog enable on injected channels */
#define ADC_ANALOG_WTDG_SINGLEREG_OR_INJEC_ENABLE	((uint32_t) 0x00C00200) /* Bit9 : Enable the watchdog on a single channel in scan mode */
#define ADC_ANALOG_WTDG_ALLREG_ENABLE            	((uint32_t) 0x00800000)
#define ADC_ANALOG_WTDG_ALLINJEC_ENABLE          	((uint32_t) 0x00400000)
#define ADC_ANALOG_WTDG_ALLREG_ALLINJEC_ENABLE   	((uint32_t) 0x00C00000)
#define ADC_ANALOG_WTDG_NONE                     	((uint32_t) 0x00000000)

#define IsAdcAnalogWatchdog(WATCHDOG)	(((WATCHDOG) == ADC_ANALOG_WTDG_SINGLEREG_ENABLE)          || ((WATCHDOG) == ADC_ANALOG_WTDG_SINGLEINJEC_ENABLE)     || \
										 ((WATCHDOG) == ADC_ANALOG_WTDG_SINGLEREG_OR_INJEC_ENABLE) || ((WATCHDOG) == ADC_ANALOG_WTDG_ALLREG_ENABLE)          || \
										 ((WATCHDOG) == ADC_ANALOG_WTDG_ALLINJEC_ENABLE)           || ((WATCHDOG) == ADC_ANALOG_WTDG_ALLREG_ALLINJEC_ENABLE) || \
										 ((WATCHDOG) == ADC_ANALOG_WTDG_NONE))
/**
 * @}
 */

/** @defgroup ADC_interrupts_definition ADC interrupts definition
 * @{
 */
/* lower 8bit uesd to set and get CTRL1 register, higher 8bit used to get and clear the status in STS register */
#define ADC_INT_ENDC 	((uint16_t) 0x0220) /* This macro value include interrupt enable bit and flag bit, the same below */
#define ADC_INT_AWD  	((uint16_t) 0x0140)
#define ADC_INT_JENDC	((uint16_t) 0x0480)

#define IsAdcInt(IT)	((((IT) & (uint16_t)0xF81F) == 0x00) && ((IT) != 0x00))

#define IsAdcGetInt(IT)	(((IT) == ADC_INT_ENDC) || ((IT) == ADC_INT_AWD) || ((IT) == ADC_INT_JENDC))
/**
 * @}
 */

/** @defgroup ADC_flags_definition ADC flags definition
 * @{
 */

#define ADC_FLAG_AWDG    	((uint8_t) 0x01)
#define ADC_FLAG_ENDC    	((uint8_t) 0x02)
#define ADC_FLAG_JENDC   	((uint8_t) 0x04)
#define ADC_FLAG_JSTR    	((uint8_t) 0x08)
#define ADC_FLAG_STR     	((uint8_t) 0x10)
#define ADC_FLAG_EOC_ANY 	((uint8_t) 0x20)
#define ADC_FLAG_JEOC_ANY	((uint8_t) 0x40)
#define IsAdcClrFlag(FLAG)	((((FLAG) & (uint8_t)0x80) == 0x00) && ((FLAG) != 0x00))
#define IsAdcGetFlag(FLAG)	(((FLAG) == ADC_FLAG_AWDG) || ((FLAG) == ADC_FLAG_ENDC) || ((FLAG) == ADC_FLAG_JENDC)   || \
							 ((FLAG) == ADC_FLAG_JSTR) || ((FLAG) == ADC_FLAG_STR)  || ((FLAG) == ADC_FLAG_EOC_ANY) || \
							 ((FLAG) == ADC_FLAG_JEOC_ANY))
/**
 * @}
 */






/** @defgroup ADC_thresholds ADC thresholds
 * @{
 */
#define IsAdcThresholdValid(THRESHOLD)	((THRESHOLD) <= 0xFFF)
/**
 * @}
 */

/** @defgroup ADC_injected_offset ADC injected offset
 * @{
 */

#define IsAdcOffsetValid(OFFSET)	((OFFSET) <= 0xFFF)

/**
 * @}
 */

/** @defgroup ADC_injected_length ADC injected length
 * @{
 */

#define IsAdcInjLenValid(LENGTH)	(((LENGTH) >= 0x1) && ((LENGTH) <= 0x4))

/**
 * @}
 */

/** @defgroup ADC_injected_rank ADC injected rank
 * @{
 */

#define IsAdcInjRankValid(RANK)	(((RANK) >= 0x1) && ((RANK) <= 0x4))

/**
 * @}
 */

/** @defgroup ADC_regular_length ADC regular length
 * @{
 */

#define IsAdcSeqLenValid(LENGTH)	(((LENGTH) >= 0x1) && ((LENGTH) <= 0x10))
/**
 * @}
 */

/** @defgroup ADC_regular_rank ADC regular rank
 * @{
 */

#define IsAdcReqRankValid(RANK)	(((RANK) >= 0x1) && ((RANK) <= 0x10))

/**
 * @}
 */

/** @defgroup ADC_regular_discontinuous_mode_number ADC regular discontinuous mode number
 * @{
 */

#define IsAdcSeqDiscNumberValid(NUMBER)	(((NUMBER) >= 0x1) && ((NUMBER) <= 0x8))

/**
 * @}
 */

/********************* following bit seg in ex register  **********************/
/**@defgroup ADC_channels_ex_style ADC channels ex style
 * @{
 */
#define ADC1_Channel_01_PA0		((uint8_t) 0x01)
#define ADC1_Channel_02_PA1 	((uint8_t) 0x02)
#define ADC1_Channel_03_PA6 	((uint8_t) 0x03)
#define ADC1_Channel_04_PA3 	((uint8_t) 0x04)
#define ADC1_Channel_05_PF4 	((uint8_t) 0x05)
#define ADC1_Channel_06_PC0 	((uint8_t) 0x06)
#define ADC1_Channel_07_PC1 	((uint8_t) 0x07)
#define ADC1_Channel_08_PC2 	((uint8_t) 0x08)
#define ADC1_Channel_09_PC3 	((uint8_t) 0x09)
#define ADC1_Channel_10_PF2 	((uint8_t) 0x0A)
#define ADC1_Channel_11_PA2 	((uint8_t) 0x0B)
										
#define ADC2_Channel_01_PA4 	((uint8_t) 0x01)
#define ADC2_Channel_02_PA5 	((uint8_t) 0x02)
#define ADC2_Channel_03_PB1 	((uint8_t) 0x03)
#define ADC2_Channel_04_PA7 	((uint8_t) 0x04)
#define ADC2_Channel_05_PC4 	((uint8_t) 0x05)
#define ADC2_Channel_06_PC0 	((uint8_t) 0x06)
#define ADC2_Channel_07_PC1 	((uint8_t) 0x07)
#define ADC2_Channel_08_PC2 	((uint8_t) 0x08)
#define ADC2_Channel_09_PC3 	((uint8_t) 0x09)
#define ADC2_Channel_10_PF2 	((uint8_t) 0x0A)
#define ADC2_Channel_11_PA2 	((uint8_t) 0x0B)
#define ADC2_Channel_12_PC5 	((uint8_t) 0x0C)
#define ADC2_Channel_13_PB2 	((uint8_t) 0x0D)

#define ADC3_Channel_01_PB11	((uint8_t) 0x01)
#define ADC3_Channel_02_PE9  	((uint8_t) 0x02)
#define ADC3_Channel_03_PE13 	((uint8_t) 0x03)
#define ADC3_Channel_04_PE12 	((uint8_t) 0x04)
#define ADC3_Channel_05_PB13 	((uint8_t) 0x05)
#define ADC3_Channel_06_PE8  	((uint8_t) 0x06)
#define ADC3_Channel_07_PD10 	((uint8_t) 0x07)
#define ADC3_Channel_08_PD11 	((uint8_t) 0x08)
#define ADC3_Channel_09_PD12 	((uint8_t) 0x09)
#define ADC3_Channel_10_PD13 	((uint8_t) 0x0A)
#define ADC3_Channel_11_PD14 	((uint8_t) 0x0B)
#define ADC3_Channel_12_PB0  	((uint8_t) 0x0C)
#define ADC3_Channel_13_PE7  	((uint8_t) 0x0D)
#define ADC3_Channel_14_PE10 	((uint8_t) 0x0E)
#define ADC3_Channel_15_PE11 	((uint8_t) 0x0F)
										   
#define ADC4_Channel_01_PE14 	((uint8_t) 0x01)
#define ADC4_Channel_02_PE15 	((uint8_t) 0x02)
#define ADC4_Channel_03_PB12 	((uint8_t) 0x03)
#define ADC4_Channel_04_PB14 	((uint8_t) 0x04)
#define ADC4_Channel_05_PB15 	((uint8_t) 0x05)
#define ADC4_Channel_06_PE8  	((uint8_t) 0x06)
#define ADC4_Channel_07_PD10 	((uint8_t) 0x07)
#define ADC4_Channel_08_PD11 	((uint8_t) 0x08)
#define ADC4_Channel_09_PD12 	((uint8_t) 0x09)
#define ADC4_Channel_10_PD13 	((uint8_t) 0x0A)
#define ADC4_Channel_11_PD14 	((uint8_t) 0x0B)
#define ADC4_Channel_12_PD8  	((uint8_t) 0x0C)
#define ADC4_Channel_13_PD9  	((uint8_t) 0x0D)

#define ADC_CH_0 				((uint8_t) 0x00)
#define ADC_CH_1 				((uint8_t) 0x01)
#define ADC_CH_2 				((uint8_t) 0x02)
#define ADC_CH_3 				((uint8_t) 0x03)
#define ADC_CH_4 				((uint8_t) 0x04)
#define ADC_CH_5 				((uint8_t) 0x05)
#define ADC_CH_6 				((uint8_t) 0x06)
#define ADC_CH_7 				((uint8_t) 0x07)
#define ADC_CH_8 				((uint8_t) 0x08)
#define ADC_CH_9 				((uint8_t) 0x09)
#define ADC_CH_10				((uint8_t) 0x0A)
#define ADC_CH_11				((uint8_t) 0x0B)
#define ADC_CH_12				((uint8_t) 0x0C)
#define ADC_CH_13				((uint8_t) 0x0D)
#define ADC_CH_14				((uint8_t) 0x0E)
#define ADC_CH_15				((uint8_t) 0x0F)
#define ADC_CH_16				((uint8_t) 0x10)
#define ADC_CH_17				((uint8_t) 0x11)
#define ADC_CH_18				((uint8_t) 0x12)
/**
 * @}
 */

/**@defgroup ADC_dif_sel_ch_definition ADC dif sel ch definition
 * @{
 */
#define ADC_DIFSEL_CHS_MASK	((uint32_t) 0x0007FFFF)
#define ADC_DIFSEL_CHS_0    ((uint32_t) 0x00000001)
#define ADC_DIFSEL_CHS_1    ((uint32_t) 0x00000002)
#define ADC_DIFSEL_CHS_2    ((uint32_t) 0x00000004)
#define ADC_DIFSEL_CHS_3    ((uint32_t) 0x00000008)
#define ADC_DIFSEL_CHS_4    ((uint32_t) 0x00000010)
#define ADC_DIFSEL_CHS_5    ((uint32_t) 0x00000020)
#define ADC_DIFSEL_CHS_6    ((uint32_t) 0x00000040)
#define ADC_DIFSEL_CHS_7    ((uint32_t) 0x00000080)
#define ADC_DIFSEL_CHS_8    ((uint32_t) 0x00000100)
#define ADC_DIFSEL_CHS_9    ((uint32_t) 0x00000200)
#define ADC_DIFSEL_CHS_10   ((uint32_t) 0x00000400)
#define ADC_DIFSEL_CHS_11   ((uint32_t) 0x00000800)
#define ADC_DIFSEL_CHS_12   ((uint32_t) 0x00001000)
#define ADC_DIFSEL_CHS_13   ((uint32_t) 0x00002000)
#define ADC_DIFSEL_CHS_14   ((uint32_t) 0x00004000)
#define ADC_DIFSEL_CHS_15   ((uint32_t) 0x00008000)
#define ADC_DIFSEL_CHS_16   ((uint32_t) 0x00010000)
#define ADC_DIFSEL_CHS_17   ((uint32_t) 0x00020000)
#define ADC_DIFSEL_CHS_18   ((uint32_t) 0x00040000)

#define IS_ADC_DIFSEL_CHS(CHS) (((CHS & ADC_DIFSEL_CHS_MASK) == 0) && (CHS != 0))
/**
 * @}
 */

/** @defgroup ADC_flags_ex_definition ADC flags ex definition
 * @{
 */
#define ADC_FLAG_RDY			((uint8_t) 0x20)
#define ADC_FLAG_PD_RDY			((uint8_t) 0x40)
#define IS_ADC_GET_READY(FLAG)	(((FLAG) == ADC_FLAG_RDY) || ((FLAG) == ADC_FLAG_PD_RDY))
/**
 * @}
 */

/**@defgroup ADC_ctrl3_definition ADC ctrl3 definition
 * @{
 */

typedef enum
{
    ADC_CTRL3_CKMOD_AHB = 0,
    ADC_CTRL3_CKMOD_PLL = 1,
} ADC_CTRL3_CKMOD_T;

#define IS_ADC_CTRL3_CKMOD(MODE)	(((MODE) == ADC_CTRL3_CKMOD_AHB) || ((MODE) == ADC_CTRL3_CKMOD_PLL))

typedef enum
{
    ADC_CTRL3_RES_12BIT = 3,
    ADC_CTRL3_RES_10BIT = 2,
    ADC_CTRL3_RES_8BIT  = 1,
    ADC_CTRL3_RES_6BIT  = 0,
} ADC_CTRL3_RES_T;
#define IS_ADC_CTRL3_RES(BIT)	(((BIT) == ADC_CTRL3_RES_12BIT) || ((BIT) == ADC_CTRL3_RES_10BIT) || ((BIT) == ADC_CTRL3_RES_8BIT) || ((BIT) == ADC_CTRL3_RES_6BIT))
 
/**
 * @}
 */

/**@defgroup ADC_Init_Ex_structure_definition ADC Init Ex structure definition
 * @{
 */
typedef struct
{
    FunctionalState		VbatMinitEn;
    FunctionalState 	DeepPowerModEn;
    FunctionalState 	JendcIntEn;
    FunctionalState 	EndcIntEn;
    ADC_CTRL3_CKMOD_T 	ClkMode;
    FunctionalState 	CalAtuoLoadEn;
    bool				DifModCal;
    ADC_CTRL3_RES_T		ResBit;
    bool				SampSecondStyle;
} ADC_InitTypeEx;

#define IS_BOOL_STATE(status) (((status) == 0) || ((status) == 1))

/**
 * @}
 */

/**
 * @}
 */

/** @addtogroup ADC_Exported_Functions
 * @{
 */

void		ADC_DeInit (ADC_Module* ADCx);
void		ADC_Init (ADC_Module* ADCx, ADC_InitType* ADC_InitStruct);
void		ADC_InitStruct (ADC_InitType* ADC_InitStruct);
void		ADC_Enable (ADC_Module* ADCx, FunctionalState Cmd);
void		ADC_EnableDMA (ADC_Module* ADCx, FunctionalState Cmd);
void		ADC_ConfigInt (ADC_Module* ADCx, uint16_t ADC_IT, FunctionalState Cmd);
void		ADC_StartCalibration (ADC_Module* ADCx);
FlagStatus	ADC_GetCalibrationStatus (ADC_Module* ADCx);
void		ADC_EnableSoftwareStartConv (ADC_Module* ADCx, FunctionalState Cmd);
void		ADC_ConfigDiscModeChannelCount (ADC_Module* ADCx, uint8_t Number);
void		ADC_EnableRegularDiscMode (ADC_Module* ADCx, FunctionalState Cmd);
void		ADC_ConfigRegularChannel (ADC_Module* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime);
void		ADC_EnableExternalTrigConv (ADC_Module* ADCx, FunctionalState Cmd);
uint16_t	ADC_GetDat (ADC_Module* ADCx);
uint32_t	ADC_GetDualModeConversionDat (ADC_Module* ADCx);
void		ADC_EnableAutoInjectedConv (ADC_Module* ADCx, FunctionalState Cmd);
void		ADC_EnableInjectedDiscMode (ADC_Module* ADCx, FunctionalState Cmd);
void		ADC_ConfigExternalTrigInjectedConv (ADC_Module* ADCx, uint32_t ADC_ExternalTrigInjecConv);
void		ADC_EnableExternalTrigInjectedConv (ADC_Module* ADCx, FunctionalState Cmd);
void		ADC_EnableSoftwareStartInjectedConv (ADC_Module* ADCx, FunctionalState Cmd);
FlagStatus	ADC_GetSoftwareStartInjectedConvCmdStatus (ADC_Module* ADCx);
void		ADC_ConfigInjectedChannel (ADC_Module* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime);
void		ADC_ConfigInjectedSequencerLength (ADC_Module* ADCx, uint8_t Length);
void		ADC_SetInjectedOffsetDat (ADC_Module* ADCx, uint8_t ADC_InjectedChannel, uint16_t Offset);
uint16_t	ADC_GetInjectedConversionDat (ADC_Module* ADCx, uint8_t ADC_InjectedChannel);
void		ADC_ConfigAnalogWatchdogWorkChannelType (ADC_Module* ADCx, uint32_t ADC_AnalogWatchdog);
void		ADC_ConfigAnalogWatchdogThresholds (ADC_Module* ADCx, uint16_t HighThreshold, uint16_t LowThreshold);
void		ADC_ConfigAnalogWatchdogSingleChannel (ADC_Module* ADCx, uint8_t ADC_Channel);
void		ADC_EnableTempSensorVrefint (FunctionalState Cmd);
FlagStatus	ADC_GetFlagStatus (ADC_Module* ADCx, uint8_t ADC_FLAG);
void		ADC_ClearFlag (ADC_Module* ADCx, uint8_t ADC_FLAG);
INTStatus	ADC_GetIntStatus (ADC_Module* ADCx, uint16_t ADC_IT);
void		ADC_ClearIntPendingBit (ADC_Module* ADCx, uint16_t ADC_IT);

void		ADC_InitEx (ADC_Module* ADCx, ADC_InitTypeEx* ADC_InitStructEx);
void		ADC_SetDifChsEnable(ADC_Module* ADCx, uint32_t DifChs, FunctionalState Cmd);
FlagStatus	ADC_GetFlagStatusReady (ADC_Module* ADCx, uint8_t ReadyFlag);
void		ADC_SetBypassCalibration (ADC_Module* ADCx, FunctionalState en);
void		ADC_SetConvResultBitNum (ADC_Module* ADCx, uint32_t ResultBitNum);

void		ADC_ConfigClk (ADC_Module* ADCx, ADC_CTRL3_CKMOD_T ADC_ClkMode, uint32_t RCC_ADCHCLKPrescaler);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

/**
 * @}
 */
#endif /*__CM32M4xxR_ADC_H__ */

