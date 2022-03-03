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
 * @file cm32m4xxr_tsc.h
 * @author CMIOT Firmware Team
 * @brief Header file containing functions prototypes of CAN StdPeriph Library.
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CM32M4xxR_TSC_H__
#define __CM32M4xxR_TSC_H__

#ifdef __cplusplus
extern "C" {
#endif


/** @addtogroup CM32M4xxR_StdPeriph_Driver
 * @{
 */

/** @defgroup TSC TSC
 * @{
 */

/* Exported types ------------------------------------------------------------*/
/** @defgroup TSC_Exported_Types TSC Exported Types
  * @{
  */

/**
 * @brief   TSC error code
 */
 typedef enum {
	TSC_ERROR_OK            = 0x00U,  /*!< No error   */
	TSC_ERROR_CLOCK         = 0x01U,  /*!< clock config error */
	TSC_ERROR_PARAMETER     = 0x02U,  /*!< parameter error */
	TSC_ERROR_HW_MODE       = 0x03U,  /*!< Exit hw mode timeout */

 }TSC_ErrorTypeDef;

 /**
 * @brief TSC Init structure definition
 */
 typedef struct
 {
     uint32_t Period;    /*!< Configures the TSC check period for a sample.
                             This parameter can be one value of @ref Detect_Period */
     uint32_t Filter;    /*!< Configures the TSC filter.
                             This parameter can be one value of @ref Detect_Filter */
     uint32_t Type;      /*!< Configures the TSC check type
                             This parameter can be one value of @ref Detect_Type */
     uint32_t Out;       /*!< Configures the TSC_OUT etr
                             This parameter can be one value of @ref TSC_Out */
     uint32_t Int;       /*!< Configures the TSC interrupt
                             This parameter can be one value of @ref TSC_Interrupt */
     uint32_t PadOpt;    /*!< Configures the TSC charge resistor
                             This parameter can be one value of @ref TSC_PadOption */
     uint32_t Speed;     /*!< Configures the TSC detect speed
                             This parameter can be one value of @ref TSC_PadSpeed */
 }TSC_InitType;

 /**
  * @brief Channels setting of hardware detection
  */
 typedef struct
 {
     uint16_t    TSC_Base;       /*!< base value */
     uint8_t     TSC_Delta;      /*!< offset value  */
     uint8_t     TSC_Resistor;   /*!< resistance value configuration*/
 } TSC_ChnCfg;

 /**
  * @brief define tsc status type
  */
 typedef enum
 {
     TSC_STS_TYP_CNTVALUE  = 0, /*!< tsc count of hardware detect */
     TSC_STS_TYP_LESS_DET  = 1, /*!< tsc less flag of hardware detect */
     TSC_STS_TYP_GREAT_DET = 2, /*!< tsc great flag of hardware detect */
     TSC_STS_TYP_CHN_NUM   = 3, /*!< tsc chn number of hardware detect */
     TSC_STS_TYP_DET_ST    = 4, /*!< tsc heardware detect mode status */
 } TSC_Status;

 /**
  * @brief Analog parameter configuration
  */
 typedef struct
 {
     uint8_t TSC_AnaSpeedOption; /*!< speed option */
     uint8_t TSC_AnaResisOption; /*!< internal or external resistance option select */
 } TSC_AnaCfg;

/**
* @}
*/

/* Exported constants --------------------------------------------------------*/
/** @defgroup TSC_Exported_Constants TSC Exported Constants
* @{
*/

/**
 * @defgroup TSC_CLK_Source TSC clock source
 * @{
 */
#define TSC_CLK_SRC_LSI                 (0x00000000)            /*!< LSI*/
#define TSC_CLK_SRC_LSE                 (0x00000001)            /*!< LSE OSC or bypass */
/**
 * @}
 */


/**
 * @defgroup Detect_Period Detection Period
 * @{
 */
#define TSC_DET_PERIOD_8	(0x00000000UL)						/*!< DET_PERIOD[3:0] = 8/TSC_CLOCK   */
#define TSC_DET_PERIOD_16   (0x01UL << TSC_CTRL_DET_PERIOD_Pos)	/*!< 0x00000001U DET_PERIOD[3:0] = 16/TSC_CLOCK  */
#define TSC_DET_PERIOD_24   (0x02UL << TSC_CTRL_DET_PERIOD_Pos) /*!< 0x00000002U DET_PERIOD[3:0] = 24/TSC_CLOCK  */
#define TSC_DET_PERIOD_32   (0x03UL << TSC_CTRL_DET_PERIOD_Pos) /*!< 0x00000003U DET_PERIOD[3:0] = 32/TSC_CLOCK(default)  */
#define TSC_DET_PERIOD_40   (0x04UL << TSC_CTRL_DET_PERIOD_Pos) /*!< 0x00000004U DET_PERIOD[3:0] = 40/TSC_CLOCK  */
#define TSC_DET_PERIOD_48   (0x05UL << TSC_CTRL_DET_PERIOD_Pos) /*!< 0x00000005U DET_PERIOD[3:0] = 48/TSC_CLOCK  */
#define TSC_DET_PERIOD_56   (0x06UL << TSC_CTRL_DET_PERIOD_Pos) /*!< 0x00000006U DET_PERIOD[3:0] = 56/TSC_CLOCK  */
#define TSC_DET_PERIOD_64   (0x07UL << TSC_CTRL_DET_PERIOD_Pos) /*!< 0x00000007U DET_PERIOD[3:0] = 64/TSC_CLOCK  */
#define TSC_DET_PERIOD_72   (0x08UL << TSC_CTRL_DET_PERIOD_Pos) /*!< 0x00000008U DET_PERIOD[3:0] = 72/TSC_CLOCK  */
#define TSC_DET_PERIOD_80   (0x09UL << TSC_CTRL_DET_PERIOD_Pos) /*!< 0x00000009U DET_PERIOD[3:0] = 80/TSC_CLOCK  */
#define TSC_DET_PERIOD_88   (0x0AUL << TSC_CTRL_DET_PERIOD_Pos) /*!< 0x0000000AU DET_PERIOD[3:0] = 88/TSC_CLOCK  */
#define TSC_DET_PERIOD_96   (0x0BUL << TSC_CTRL_DET_PERIOD_Pos) /*!< 0x0000000BU DET_PERIOD[3:0] = 96/TSC_CLOCK  */
#define TSC_DET_PERIOD_104  (0x0CUL << TSC_CTRL_DET_PERIOD_Pos) /*!< 0x0000000CU DET_PERIOD[3:0] = 104/TSC_CLOCK   */
/**
 * @}
 */

/**
 * @defgroup Detect_Filter Detection Filter
 * @{
 */
#define TSC_DET_FILTER_1	(0x00000000UL)						/*!< DET_FILTER[3:0] = 1 sample   */
#define TSC_DET_FILTER_2    (0x01UL << TSC_CTRL_DET_FILTER_Pos) /*!< 0x00000010U DET_FILTER[3:0] = 2 samples  */
#define TSC_DET_FILTER_3    (0x02UL << TSC_CTRL_DET_FILTER_Pos) /*!< 0x00000020U DET_FILTER[3:0] = 3 samples  */
#define TSC_DET_FILTER_4    (0x03UL << TSC_CTRL_DET_FILTER_Pos) /*!< 0x00000030U DET_FILTER[3:0] = 4 samples  */
/**
 * @}
 */

/**
 * @defgroup HW_Detect_Mode Hardware Detection Mode
 * @{
 */
#define TSC_HW_DET_MODE_DISABLE	(0x00000000UL)							/*!< Hardware detect mode disable   */
#define TSC_HW_DET_MODE_ENABLE	(0x01UL << TSC_CTRL_HW_DET_MODE_Pos)    /*!< 0x00000040U Hardware detect mode enable */
/**
 * @}
 */

/**
 * @defgroup Detect_Type Detection Type
 * @{
 */
#define TSC_DET_TYPE_Msk    (TSC_CTRL_LESS_DET_SEL_Msk | TSC_CTRL_GREAT_DET_SEL_Msk)
#define TSC_DET_TYPE_Pos    (TSC_CTRL_LESS_DET_SEL_Pos)

#define TSC_DET_TYPE_NONE   (0UL)                           /*!< 0x00000000U Disable detect */
#define TSC_DET_TYPE_LESS   (0x01UL << TSC_DET_TYPE_Pos)    /*!< 0x00000100U Less detect enable */
#define TSC_DET_TYPE_GREAT  (0x02UL << TSC_DET_TYPE_Pos)    /*!< 0x00000200U Great detect enable */
#define TSC_DET_TYPE_PERIOD (0x03UL << TSC_DET_TYPE_Pos)    /*!< 0x00000300U Both great and less detct enable */
/**
 * @}
 */
 
/**
 * @defgroup TSC_Interrupt TSC Interrupt Enable
 * @{
 */
#define TSC_IT_DET_ENABLE       (TSC_CTRL_DET_INTEN)    /*!< Enable TSC detect interrupt */
#define TSC_IT_DET_DISABLE      (0UL)                   /*!< Disable TSC detect interrupt */
/**
 * @}
 */

/**
 * @defgroup TSC_Out TSC Output Direction
 * @{
 */
#define TSC_OUT_PIN          (0x00000000UL)						/*!< TSC output to TSC_OUT pin */
#define TSC_OUT_TIM4_ETR     (0x1UL << TSC_CTRL_TIM4_ETR_Pos)	/*!< TSC output to TIM4 ETR */
#define TSC_OUT_TIM2_ETR     (0x2UL << TSC_CTRL_TIM4_ETR_Pos)	/*!< TSC output to TIM2 ETR and TIM2 CH1*/
#define TSC_OUT_TIM2TIM4_ETR (0x3UL << TSC_CTRL_TIM4_ETR_Pos)   /*!< TSC output to TIM4 ETR and TIM2 ETR and TIM2 CH1*/
/**
 * @}
 */

/**
 * @defgroup TSC_Flag TSC Flag
 * @{
 */
#define TSC_FLAG_HW         (0x1UL << TSC_CTRL_HW_DET_ST_Pos)			/*!< Flag of hardware detect mode */

#define TSC_FLAG_GREAT_DET  (0x1UL << TSC_STS_GREAT_DET_Pos)			/*!< Flag of great detect type */
#define TSC_FLAG_LESS_DET   (0x1UL << TSC_STS_LESS_DET_Pos)				/*!< Flag of less detect type */
#define TSC_FLAG_PERIOD_DET (TSC_FLAG_GREAT_DET | TSC_FLAG_LESS_DET)	/*!< Flag of period detect type */
/**
 * @}
 */

/**
 * @defgroup TSC_SW_Detect TSC Software Detection Enable
 * @{
 */
#define TSC_SW_MODE_DISABLE (0x00000000UL)							/*!< Disable software detect mode */
#define TSC_SW_MODE_ENABLE  (0x1UL << TSC_ANA_CTRL_SW_TSC_EN_Pos)   /*!< Enable software detect mode */
/**
 * @}
 */

/**
 * @defgroup TSC_PadOption TSC Pad Option
 * @{
 */
#define TSC_PAD_INTERNAL_RES    (0x00000000UL)						/*!< Use internal resistor */
#define TSC_PAD_EXTERNAL_RES    (0x1UL << TSC_ANA_SEL_PAD_OPT_Pos)  /*!< Use external resistor */
/**
 * @}
 */

/**
 * @defgroup TSC_PadSpeed TSC Pad Speed
 * @{
 */
#define TSC_PAD_SPEED_0     (0x00000000UL)						/*!< Low speed, about 100K */
#define TSC_PAD_SPEED_1     (0x1UL << TSC_ANA_SEL_SP_OPT_Pos)   /*!< Middle spped */
#define TSC_PAD_SPEED_2     (0x2UL << TSC_ANA_SEL_SP_OPT_Pos)   /*!< Middle spped */
#define TSC_PAD_SPEED_3     (0x3UL << TSC_ANA_SEL_SP_OPT_Pos)   /*!< High spped */
/**
 * @}
 */

/**
 * @defgroup TSC_Constant TSC Constant
 * @{
 */
#define TSC_CHN_SEL_ALL             (TSC_CHNEN_CHN_SEL_ALL_Msk)
#define MAX_TSC_HW_CHN              (24)						/*!< Maximum number of tsc pin */
#define MAX_TSC_THRESHOLD_BASE      (2047)						/*!< Maximum detect base value of threshold */
#define MAX_TSC_THRESHOLD_DELTA     (255)						/*!< Maximum detect delta value of threshold */
#define TSC_TIMEOUT                 (SystemCoreClock >> 4)		/*!< TSC normal timeout */
#define TSC_DELAY                   2000						/*!< TSC Delay for channel input stable */
/**
 * @}
 */

/**
 * @defgroup TSC_DetectMode TSC Detection Mode
 * @{
 */
#define TSC_HW_DETECT_MODE      (0x00000001UL)	/*!< TSC hardware detect mode */
#define TSC_SW_DETECT_MODE      (0x00000000UL)	/*!< TSC software detect mode */
/**
 * @}
 */

/**
* @}
*/

/* TSC Exported macros -----------------------------------------------------------*/
/** @defgroup TSC_Exported_Macros TSC Exported Macros
 * @{
 */

/** @brief  Enable the TSC HW detect mode
 */
#define __TSC_HW_ENABLE()					SET_BIT(TSC->CTRL, TSC_HW_DET_MODE_ENABLE)

/** @brief  Disable the TSC HW detect mode
 */
#define __TSC_HW_DISABLE()					CLEAR_BIT(TSC->CTRL, TSC_HW_DET_MODE_ENABLE)

/** @brief  Config TSC detect period for HW detect mode
 * @param  __PERIOD__  specifies the TSC detect period during HW detect mode
 *     @arg TSC_DET_PERIOD_8:  Detect period = 8/TSC_CLK
 *     @arg TSC_DET_PERIOD_16: Detect Period = 1/TSC_CLK
 *     @arg TSC_DET_PERIOD_24: Detect Period = 2/TSC_CLK
 *     @arg TSC_DET_PERIOD_32: Detect Period = 3/TSC_CLK
 *     @arg TSC_DET_PERIOD_40: Detect Period = 4/TSC_CLK
 *     @arg TSC_DET_PERIOD_48: Detect Period = 5/TSC_CLK
 *     @arg TSC_DET_PERIOD_56: Detect Period = 6/TSC_CLK
 *     @arg TSC_DET_PERIOD_64: Detect Period = 7/TSC_CLK
 *     @arg TSC_DET_PERIOD_72: Detect Period = 7/TSC_CLK
 *     @arg TSC_DET_PERIOD_80: Detect Period = 7/TSC_CLK
 *     @arg TSC_DET_PERIOD_88: Detect Period = 7/TSC_CLK
 *     @arg TSC_DET_PERIOD_96: Detect Period = 7/TSC_CLK
 *     @arg TSC_DET_PERIOD_104:Detect Period = 7/TSC_CLK
 * @retval None
 */
#define __TSC_PERIOD_CONFIG(__PERIOD__)		MODIFY_REG(TSC->CTRL, TSC_CTRL_DET_PERIOD_Msk, __PERIOD__)

/** @brief  Config TSC detect filter for HW detect mode
 * @param  __FILTER__  specifies the least usefull continuous samples during HW detect mode
 *     @arg TSC_DET_FILTER_1: Detect filter = 1 pulse
 *     @arg TSC_DET_FILTER_2: Detect filter = 2 pulse
 *     @arg TSC_DET_FILTER_3: Detect filter = 3 pulse
 *     @arg TSC_DET_FILTER_4: Detect filter = 4 pulse
 * @retval None
 */
#define __TSC_FILTER_CONFIG(__FILTER__)		MODIFY_REG(TSC->CTRL, TSC_CTRL_DET_FILTER_Msk, __FILTER__)

/** @brief  Config TSC detect type for HW detect mode, less great or both
 * @param  __TYPE__  specifies the detect type of a sample during HW detect mode
 *     @arg TSC_DET_TYPE_NONE:  Detect disable
 *     @arg TSC_DET_TYPE_LESS:  Pulse number must be greater than the threshold(basee-delta) during a sample time
 *     @arg TSC_DET_TYPE_GREAT: Pulse number must be less than the threshold(basee+delta) during a sample time
 *     @arg TSC_DET_TYPE_PERIOD:Pulse number must be greater than (basee-delta) 
                                 and also be less than (basee+delta) during a sample time
 * @retval None
 */
#define __TSC_LESS_GREAT_CONFIG(__TYPE__)   MODIFY_REG(TSC->CTRL,                                           		\
                                                       (TSC_CTRL_LESS_DET_SEL_Msk | TSC_CTRL_GREAT_DET_SEL_Msk),	\
                                                       __TYPE__)

/** @brief  Enable TSC interrupt
 */
#define __TSC_INT_ENABLE()                  SET_BIT(TSC->CTRL, TSC_IT_DET_ENABLE)

/** @brief  Disable TSC interrupt
 */
#define __TSC_INT_DISABLE()					CLEAR_BIT(TSC->CTRL, TSC_IT_DET_ENABLE)

/** @brief  Config the TSC output
 * @param  __OUT__  specifies where the TSC output should go
 *     @arg TSC_OUT_PIN:      TSC output to the TSC_OUT pin
 *     @arg TSC_OUT_TIM4_ETR: TSC output to TIM4 as ETR
 *     @arg TSC_OUT_TIM2_ETR: TSC output to TIM2 as ETR 
 * @retval None
 */
#define __TSC_OUT_CONFIG(__OUT__)           MODIFY_REG( TSC->CTRL,												\
                                                        (TSC_CTRL_TIM4_ETR_Msk | TSC_CTRL_TIM2_ETR_CH1_Msk),	\
                                                        __OUT__)

/** @brief  Config the TSC channel
 * @param  __CHN__  specifies the pin of channels used for detect
 *     @arg CHNx: bitx,This parameter:bit[0:23] used,bit[24:31] must be 0
 * @retval None
 */
#define __TSC_CHN_CONFIG(__CHN__)           WRITE_REG(TSC->CHNEN,  __CHN__)

/** @brief  Enable the TSC SW detect mode
 */
#define __TSC_SW_ENABLE()					SET_BIT(TSC->ANA_CTRL, TSC_ANA_CTRL_SW_TSC_EN)

/** @brief  Disable the TSC SW detect mode
 */
#define __TSC_SW_DISABLE()					CLEAR_BIT(TSC->ANA_CTRL, TSC_ANA_CTRL_SW_TSC_EN)

/** @brief  Config the detect channel number during SW detect mode
 * @param  __NUM__  specifies channel number, must be less than MAX_TSC_HW_CHN
 * @retval None
 */
#define __TSC_SW_CHN_NUM_CONFIG(__NUM__)	MODIFY_REG(TSC->ANA_CTRL, TSC_ANA_CTRL_SW_PAD_MUX_Msk, __NUM__)

/** @brief  Config the pad charge type
 * @param  __OPT__  specifies which resistor is used for charge
 *     @arg TSC_PAD_INTERNAL_RES: Internal resistor is used
 *     @arg TSC_PAD_EXTERNAL_RES: External resistor is used
 * @retval None
 */
#define __TSC_PAD_OPT_CONFIG(__OPT__)       MODIFY_REG(TSC->ANA_SEL, TSC_ANA_SEL_PAD_OPT_Msk, __OPT__)

/** @brief  Config TSC speed
 * @param  __SPEED__  specifies the TSC speed range
 *     @arg TSC_PAD_SPEED_0: Low speed
 *     @arg TSC_PAD_SPEED_1: Middle speed
 *     @arg TSC_PAD_SPEED_2: Middle speed
 *     @arg TSC_PAD_SPEED_3: High speed
 * @retval None
 */
#define __TSC_PAD_SPEED_CONFIG(__SPEED__)   MODIFY_REG(TSC->ANA_SEL, TSC_ANA_SEL_SP_OPT_Msk, __SPEED__)


/** @brief  Check if the HW detect mode is enable
 * @param  None
 * @retval Current state of HW detect mode
 */
#define __TSC_GET_HW_MODE()                 (((TSC->CTRL) & TSC_FLAG_HW) == (TSC_FLAG_HW))

/** @brief  Check the detect type during HW detect mode
 * @param  __FLAG__  specifies the flag of detect type
 *     @arg TSC_FLAG_LESS_DET:   Flag of less detect type
 *     @arg TSC_FLAG_GREAT_DET:  Flag of great detect type
 *     @arg TSC_FLAG_PERIOD_DET: Flag of priod detect type
 * @retval Current state of flag
 */
#define __TSC_GET_HW_DET_TYPE(__FLAG__)     (((TSC->STS) & __FLAG__) == (__FLAG__))

/** @brief  Get the number of channel which is detected now
 * @retval Current channel number
 */
#define __TSC_GET_CHN_NUMBER()              (((TSC->STS) & TSC_STS_CHN_NUM_Msk) >> TSC_STS_CHN_NUM_Pos )

/** @brief  Get the count value of pulse
 * @retval Pulse count of current channel
 */
#define __TSC_GET_CHN_CNT()                 (((TSC->STS) & TSC_STS_CNT_VAL_Msk ) >> TSC_STS_CNT_VAL_Pos )

/** @brief  Get the base value of one channel
 * @param  __NUM__  specifies channel number, must be less than MAX_TSC_HW_CHN
 * @retval base value of the channel
 */
#define __TSC_GET_CHN_BASE(__NUM__)			((TSC->THRHD[__NUM__] & TSC_THRHD0_BASE0_Msk ) >> TSC_THRHD0_BASE0_Pos)

/** @brief  Get the delta value of one channel
 * @param  __NUM__  specifies channel number, must be less than MAX_TSC_HW_CHN
 * @retval delta value of the channel
 */
#define __TSC_GET_CHN_DELTA(__NUM__)		((TSC->THRHD[__NUM__] & TSC_THRHD0_DELTA0_Msk ) >> TSC_THRHD0_DELTA0_Pos )

/** @brief  Get the internal resist value of one channel
 * @param  __NUM__  specifies channel number, must be less than MAX_TSC_HW_CHN
 * @retval resist value of the channel
 */
#define __TSC_GET_CHN_RESIST(__NUM__)		((TSC->RESR[__NUM__ >> 3] >> ((__NUM__ & 0x7UL) * 4)) & TSC_RESR0_CHN_RESIST0_Msk)

 /**
* @}
*/

/* Private macros ------------------------------------------------------------*/
/** @addtogroup TSC Private Macros
 * @{
 */
#define IS_TSC_CLK_SOURCE(_CLK_)            (((_CLK_) == TSC_CLK_SRC_LSI) || ((_CLK_) == TSC_CLK_SRC_LSE))

#define IS_TSC_DET_PERIOD(_PERIOD_)         (((_PERIOD_) == TSC_DET_PERIOD_8)  || ((_PERIOD_) == TSC_DET_PERIOD_16) || \
                                             ((_PERIOD_) == TSC_DET_PERIOD_24) || ((_PERIOD_) == TSC_DET_PERIOD_32) || \
                                             ((_PERIOD_) == TSC_DET_PERIOD_40) || ((_PERIOD_) == TSC_DET_PERIOD_48) || \
                                             ((_PERIOD_) == TSC_DET_PERIOD_56) || ((_PERIOD_) == TSC_DET_PERIOD_64) || \
                                             ((_PERIOD_) == TSC_DET_PERIOD_72) || ((_PERIOD_) == TSC_DET_PERIOD_80) || \
                                             ((_PERIOD_) == TSC_DET_PERIOD_88) || ((_PERIOD_) == TSC_DET_PERIOD_96) || \
                                             ((_PERIOD_) == TSC_DET_PERIOD_104))

#define IS_TSC_FILTER(_FILTER_)				(((_FILTER_) == TSC_DET_FILTER_1) || ((_FILTER_) == TSC_DET_FILTER_2) || \
											 ((_FILTER_) == TSC_DET_FILTER_3) || ((_FILTER_) == TSC_DET_FILTER_4) )

#define IS_TSC_DET_MODE(_MODE_)				(((_MODE_) == TSC_HW_DETECT_MODE) || ((_MODE_) == TSC_SW_DETECT_MODE))

#define IS_TSC_DET_TYPE(_TYPE_)				(((_TYPE_) == TSC_DET_TYPE_GREAT)  || ((_TYPE_) == TSC_DET_TYPE_LESS) || \
											 ((_TYPE_) == TSC_DET_TYPE_PERIOD) || ((_TYPE_) == TSC_DET_TYPE_NONE) )

#define IS_TSC_INT(_INT_)					(((_INT_) == TSC_IT_DET_ENABLE) || ((_INT_) == TSC_IT_DET_DISABLE))

#define IS_TSC_OUT(_ETR_)					(((_ETR_) == TSC_OUT_PIN) || ((_ETR_) == TSC_OUT_TIM2_ETR) || ((_ETR_) == TSC_OUT_TIM4_ETR)|| ((_ETR_) == TSC_OUT_TIM2TIM4_ETR))

#define IS_TSC_CHN(_CHN_)					(0 == ((_CHN_) & (~TSC_CHNEN_CHN_SEL_ALL_Msk)))

#define IS_TSC_CHN_NUMBER(_NUM_)			((uint32_t)(_NUM_) < MAX_TSC_HW_CHN)

#define IS_TSC_PAD_OPTION(_OPT_)			(((_OPT_) == TSC_PAD_INTERNAL_RES) || ((_OPT_) == TSC_PAD_EXTERNAL_RES))

#define IS_TSC_PAD_SPEED(_SPEED_)			(((_SPEED_) == TSC_PAD_SPEED_0) || ((_SPEED_) == TSC_PAD_SPEED_1) || \
											 ((_SPEED_) == TSC_PAD_SPEED_2) || ((_SPEED_) == TSC_PAD_SPEED_3))

#define IS_TSC_RESISTOR_VALUE(_RES_)		(((_RES_) == TSC_RESR0_CHN_RESIST0_1M)   || ((_RES_) == TSC_RESR0_CHN_RESIST0_875K) || \
											 ((_RES_) == TSC_RESR0_CHN_RESIST0_750K) || ((_RES_) == TSC_RESR0_CHN_RESIST0_625K) || \
											 ((_RES_) == TSC_RESR0_CHN_RESIST0_500K) || ((_RES_) == TSC_RESR0_CHN_RESIST0_375K) || \
											 ((_RES_) == TSC_RESR0_CHN_RESIST0_250K) || ((_RES_) == TSC_RESR0_CHN_RESIST0_125K))

#define IS_TSC_THRESHOLD_BASE(_BASE_)       ((_BASE_) <= MAX_TSC_THRESHOLD_BASE)

#define IS_TSC_THRESHOLD_DELTA(_DELTA_)     ((_DELTA_) <= MAX_TSC_THRESHOLD_DELTA)

#define IS_TSC_STS_TPYE(_STSTYPE_)           (((_STSTYPE_) == TSC_STS_TYP_CNTVALUE) || ((_STSTYPE_) == TSC_STS_TYP_LESS_DET) || \
											  ((_STSTYPE_) == TSC_STS_TYP_GREAT_DET) || ((_STSTYPE_) == TSC_STS_TYP_CHN_NUM) || \
											  ((_STSTYPE_) == TSC_STS_TYP_DET_ST))

#define IS_TSC_PTR_NONNULL(_PTR_)				(_PTR_ != 0)

/**
* @}
*/

/* Exported functions --------------------------------------------------------*/

/** @defgroup TSC_Exported_Functions TSC Exported Functions
* @{
*/
void                TSC_DeInit(void);
TSC_ErrorTypeDef	TSC_Init (TSC_InitType* TSC_Init);
void                TSC_InitStruct(TSC_InitType* TSC_InitStruct);
TSC_ErrorTypeDef	TSC_ConfigClock (uint32_t TSC_ClkSource);
TSC_ErrorTypeDef	TSC_ConfigInternalResistor (uint32_t Channels, uint32_t res );
TSC_ErrorTypeDef	TSC_ConfigThreshold (uint32_t Channels, uint32_t base, uint32_t delta);
TSC_ErrorTypeDef    TSC_GetChannelCfg(uint32_t Channels, TSC_ChnCfg* ChnCfg);
uint32_t 			TSC_GetStatus(TSC_Status type);
TSC_ErrorTypeDef    TSC_ConfigHWMode(uint32_t Channels, FunctionalState Cmd);
TSC_ErrorTypeDef    TSC_ConfigSWMode(uint32_t ChannelNum, uint32_t OutDir, FunctionalState Cmd);
TSC_ErrorTypeDef 	TSC_SwitchChannel(uint32_t ChannelNum);
TSC_ErrorTypeDef 	TSC_ConfigAna(TSC_AnaCfg* AnaCfg);
TSC_ErrorTypeDef 	TSC_ConfigChannel(uint32_t Channels,TSC_ChnCfg* ChnCfg);

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __CM32M4xxR_TSC_H__ */
