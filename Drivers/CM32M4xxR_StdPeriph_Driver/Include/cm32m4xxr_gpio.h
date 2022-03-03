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
 * @file cm32m4xxr_gpio.h
 * @author CMIOT Firmware Team
 * @brief Header file containing functions prototypes of CAN StdPeriph Library.
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */
#ifndef __CM32M4xxR_GPIO_H__
#define __CM32M4xxR_GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/** @addtogroup CM32M4xxR_StdPeriph_Driver
 * @{
 */

/** @defgroup GPIO GPIO
 * @{
 */

/* Exported types ------------------------------------------------------------*/
/** @defgroup GPIO_Exported_Types GPIO Exported Types
 * @{
 */

/**
 * @brief  Output Maximum frequency selection
 */

typedef enum
{
    GPIO_INPUT			= 0x00,
    GPIO_Speed_2MHz		= 0x01,
    GPIO_Speed_10MHz	= 0x02,
    GPIO_Speed_50MHz	= 0x03
} GPIO_SpeedType;

/**
 * @brief  Configuration Mode enumeration
 */

typedef enum
{
    GPIO_Mode_AIN			= 0x00,
    GPIO_Mode_IN_FLOATING	= 0x04,
    GPIO_Mode_IPD			= 0x28,
    GPIO_Mode_IPU			= 0x48,
    GPIO_Mode_Out_OD		= 0x14,
    GPIO_Mode_Out_PP		= 0x10,
    GPIO_Mode_AF_OD			= 0x1C,
    GPIO_Mode_AF_PP			= 0x18
} GPIO_ModeType;

/**
 * @brief  GPIO Init structure definition
 */

typedef struct
{
    uint16_t		Pin;		/*!< Specifies the GPIO pins to be configured. This parameter can be any value of @ref GPIO_pins_define			*/
    GPIO_SpeedType	GPIO_Speed;	/*!< Specifies the speed for the selected pins. This parameter can be a value of @ref GPIO_SpeedType			*/
    GPIO_ModeType	GPIO_Mode;	/*!< Specifies the operating mode for the selected pins. This parameter can be a value of @ref GPIO_ModeType	*/
} GPIO_InitType;

/**
 * @brief  Bit_SET and Bit_RESET enumeration
 */

typedef enum
{
    Bit_RESET = 0,
    Bit_SET   = 1
} Bit_OperateType;

/**
 * @}
 */

/** @defgroup GPIO_Private_Constants GPIO Private Constants
 * @{
 */
#define REGISTER_NUM0 (0UL<<10)
#define REGISTER_NUM1 (1UL<<10)
#define REGISTER_NUM2 (2UL<<10)
#define REGISTER_NUM3 (3UL<<10)
#define REGISTER_NUM4 (4UL<<10)
#define START_POS(x)  ((uint32_t)x<<5)
#define BIT_WIDTH1    (1UL<<3)
#define BIT_WIDTH2    (2UL<<3)
#define BIT_WIDTH3    (3UL<<3)
#define BIT_VALUE(x)  ((uint32_t)x)
/**
 * @}
 */
/* Exported constants --------------------------------------------------------*/
/** @defgroup GPIO_Exported_Constants GPIO Exported Constants
 * @{
 */

/** @defgroup GPIO_pins_define GPIO Pin Defines
 * @{
 */

#define GPIO_PIN_0  			((uint16_t) 0x0001) /*!< Pin 0 selected		*/
#define GPIO_PIN_1  			((uint16_t) 0x0002) /*!< Pin 1 selected		*/
#define GPIO_PIN_2  			((uint16_t) 0x0004) /*!< Pin 2 selected		*/
#define GPIO_PIN_3  			((uint16_t) 0x0008) /*!< Pin 3 selected		*/
#define GPIO_PIN_4  			((uint16_t) 0x0010) /*!< Pin 4 selected		*/
#define GPIO_PIN_5  			((uint16_t) 0x0020) /*!< Pin 5 selected		*/
#define GPIO_PIN_6  			((uint16_t) 0x0040) /*!< Pin 6 selected		*/
#define GPIO_PIN_7  			((uint16_t) 0x0080) /*!< Pin 7 selected		*/
#define GPIO_PIN_8  			((uint16_t) 0x0100) /*!< Pin 8 selected		*/
#define GPIO_PIN_9  			((uint16_t) 0x0200) /*!< Pin 9 selected		*/
#define GPIO_PIN_10 			((uint16_t) 0x0400) /*!< Pin 10 selected	*/
#define GPIO_PIN_11 			((uint16_t) 0x0800) /*!< Pin 11 selected	*/
#define GPIO_PIN_12 			((uint16_t) 0x1000) /*!< Pin 12 selected	*/
#define GPIO_PIN_13 			((uint16_t) 0x2000) /*!< Pin 13 selected	*/
#define GPIO_PIN_14 			((uint16_t) 0x4000) /*!< Pin 14 selected	*/
#define GPIO_PIN_15 			((uint16_t) 0x8000) /*!< Pin 15 selected	*/
#define GPIO_PIN_ALL			((uint16_t) 0xFFFF) /*!< All pins selected	*/

/**
 * @}
 */

/** @defgroup GPIO_Remap_define GPIO Remap Constants
 * @{
 */

/* AFIO_RMP_CFG */
#define GPIO_RMP_SPI1             	((uint32_t) (REGISTER_NUM0 | START_POS(0) | BIT_WIDTH1 | BIT_VALUE(1))) /*!< SPI1 Alternate Function mapping								*/
#define GPIO_RMP_I2C1             	((uint32_t) (REGISTER_NUM0 | START_POS(1) | BIT_WIDTH1 | BIT_VALUE(1))) /*!< I2C1 Alternate Function mapping								*/
#define GPIO_RMP_USART1           	((uint32_t) (REGISTER_NUM0 | START_POS(2) | BIT_WIDTH1 | BIT_VALUE(1))) /*!< USART1 Alternate Function mapping								*/
#define GPIO_RMP_USART2           	((uint32_t) (REGISTER_NUM0 | START_POS(3) | BIT_WIDTH1 | BIT_VALUE(1))) /*!< USART2 Alternate Function mapping							  	*/
#define GPIO_PART_RMP_USART3      	((uint32_t) (REGISTER_NUM0 | START_POS(4) | BIT_WIDTH2 | BIT_VALUE(1))) /*!< USART3 Partial Alternate Function mapping						*/
#define GPIO_ALL_RMP_USART3       	((uint32_t) (REGISTER_NUM0 | START_POS(4) | BIT_WIDTH2 | BIT_VALUE(3))) /*!< USART3 Full Alternate Function mapping							*/
#define GPIO_PART1_RMP_TIM1       	((uint32_t) (REGISTER_NUM0 | START_POS(6) | BIT_WIDTH2 | BIT_VALUE(1))) /*!< TIM1 Partial Alternate Function mapping						*/
#define GPIO_PART2_RMP_TIM1       	((uint32_t) (REGISTER_NUM0 | START_POS(6) | BIT_WIDTH2 | BIT_VALUE(2))) /*!< TIM1 Partial Alternate Function mapping						*/
#define GPIO_ALL_RMP_TIM1         	((uint32_t) (REGISTER_NUM0 | START_POS(6) | BIT_WIDTH2 | BIT_VALUE(3))) /*!< TIM1 Full Alternate Function mapping							*/
#define GPIO_PART1_RMP_TIM2   		((uint32_t) (REGISTER_NUM0 | START_POS(8) | BIT_WIDTH2 | BIT_VALUE(1))) /*!< TIM2 Partial1 Alternate Function mapping						*/
#define GPIO_PART2_RMP_TIM2       	((uint32_t) (REGISTER_NUM0 | START_POS(8) | BIT_WIDTH2 | BIT_VALUE(2))) /*!< TIM2 Partial2 Alternate Function mapping						*/
#define GPIO_ALL_RMP_TIM2         	((uint32_t) (REGISTER_NUM0 | START_POS(8) | BIT_WIDTH2 | BIT_VALUE(3))) /*!< TIM2 Full Alternate Function mapping							*/
#define GPIO_PART1_RMP_TIM3       	((uint32_t) (REGISTER_NUM0 | START_POS(10) | BIT_WIDTH2 | BIT_VALUE(2))) /*!< TIM3 Partial Alternate Function mapping						*/
#define GPIO_ALL_RMP_TIM3         	((uint32_t) (REGISTER_NUM0 | START_POS(10) | BIT_WIDTH2 | BIT_VALUE(3))) /*!< TIM3 Full Alternate Function mapping							*/
#define GPIO_RMP_TIM4             	((uint32_t) (REGISTER_NUM0 | START_POS(12) | BIT_WIDTH1 | BIT_VALUE(1))) /*!< TIM4 Alternate Function mapping								*/
#define GPIO_RMP1_CAN1            	((uint32_t) (REGISTER_NUM0 | START_POS(13) | BIT_WIDTH2 | BIT_VALUE(1))) /*!< CAN1 Alternate Function mapping								*/
#define GPIO_RMP2_CAN1          	((uint32_t) (REGISTER_NUM0 | START_POS(13) | BIT_WIDTH2 | BIT_VALUE(2))) /*!< CAN1 Alternate Function mapping								*/
#define GPIO_RMP3_CAN1          	((uint32_t) (REGISTER_NUM0 | START_POS(13) | BIT_WIDTH2 | BIT_VALUE(3))) /*!< CAN1 Alternate Function mapping								*/
#define GPIO_RMP_PD01             	((uint32_t) (REGISTER_NUM0 | START_POS(15) | BIT_WIDTH1 | BIT_VALUE(1))) /*!< PD01 Alternate Function mapping								*/
#define GPIO_RMP_TIM5CH4          	((uint32_t) (REGISTER_NUM0 | START_POS(16) | BIT_WIDTH1 | BIT_VALUE(1))) /*!< LSI connected to TIM5 Channel4 input capture for calibration	*/
#define GPIO_RMP_ADC1_ETRI        	((uint32_t) (REGISTER_NUM0 | START_POS(17) | BIT_WIDTH1 | BIT_VALUE(1))) /*!< ADC1 External Trigger Injected Conversion remapping			*/
#define GPIO_RMP_ADC1_ETRR        	((uint32_t) (REGISTER_NUM0 | START_POS(18) | BIT_WIDTH1 | BIT_VALUE(1))) /*!< ADC1 External Trigger Regular Conversion remapping				*/
#define GPIO_RMP_ADC2_ETRI        	((uint32_t) (REGISTER_NUM0 | START_POS(19) | BIT_WIDTH1 | BIT_VALUE(1))) /*!< ADC2 External Trigger Injected Conversion remapping			*/
#define GPIO_RMP_ADC2_ETRR        	((uint32_t) (REGISTER_NUM0 | START_POS(20) | BIT_WIDTH1 | BIT_VALUE(1))) /*!< ADC2 External Trigger Regular Conversion remapping				*/

#define GPIO_RMP_SW_JTAG_NO_NJTRST	((uint32_t) (REGISTER_NUM0 | START_POS(24) | BIT_WIDTH3 | BIT_VALUE(1))) /*!< Full SWJ Enabled (JTAG-DP + SW-DP) but without JTRST			*/
#define GPIO_RMP_SW_JTAG_SW_ENABLE	((uint32_t) (REGISTER_NUM0 | START_POS(24) | BIT_WIDTH3 | BIT_VALUE(2))) /*!< JTAG-DP Disabled and SW-DP Enabled								*/
#define GPIO_RMP_SW_JTAG_DISABLE  	((uint32_t) (REGISTER_NUM0 | START_POS(24) | BIT_WIDTH3 | BIT_VALUE(4))) /*!< Full SWJ Disabled (JTAG-DP + SW-DP)							*/

/* AFIO_RMP_CFG3 */
#define GPIO_RMP1_CAN2				((uint32_t) (REGISTER_NUM2 | START_POS(1) | BIT_WIDTH2 | BIT_VALUE(1))) /*!< CAN2 Alternate Function mapping								*/
#define GPIO_RMP3_CAN2				((uint32_t) (REGISTER_NUM2 | START_POS(1) | BIT_WIDTH2 | BIT_VALUE(3))) /*!< CAN2 Alternate Function mapping								*/
#define GPIO_RMP2_QSPI				((uint32_t) (REGISTER_NUM2 | START_POS(4) | BIT_WIDTH2 | BIT_VALUE(2))) /*!< QSPI Alternate Function mapping								*/
#define GPIO_RMP3_QSPI				((uint32_t) (REGISTER_NUM2 | START_POS(4) | BIT_WIDTH2 | BIT_VALUE(3))) /*!< QSPI Alternate Function mapping								*/
#define GPIO_RMP1_I2C2				((uint32_t) (REGISTER_NUM2 | START_POS(6) | BIT_WIDTH2 | BIT_VALUE(1))) /*!< I2C2 Alternate Function mapping								*/
#define GPIO_RMP3_I2C2				((uint32_t) (REGISTER_NUM2 | START_POS(6) | BIT_WIDTH2 | BIT_VALUE(3))) /*!< I2C2 Alternate Function mapping								*/
#define GPIO_RMP2_I2C3				((uint32_t) (REGISTER_NUM2 | START_POS(8) | BIT_WIDTH2 | BIT_VALUE(2))) /*!< I2C3 Alternate Function mapping								*/
#define GPIO_RMP3_I2C3				((uint32_t) (REGISTER_NUM2 | START_POS(8) | BIT_WIDTH2 | BIT_VALUE(3))) /*!< I2C3 Alternate Function mapping								*/
#define GPIO_RMP1_I2C4				((uint32_t) (REGISTER_NUM2 | START_POS(10) | BIT_WIDTH2 | BIT_VALUE(1))) /*!< I2C4 Alternate Function mapping								*/
#define GPIO_RMP3_I2C4				((uint32_t) (REGISTER_NUM2 | START_POS(10) | BIT_WIDTH2 | BIT_VALUE(3))) /*!< I2C4 Alternate Function mapping								*/
#define GPIO_RMP1_SPI2				((uint32_t) (REGISTER_NUM2 | START_POS(12) | BIT_WIDTH2 | BIT_VALUE(1))) /*!< SPI2 Alternate Function mapping								*/
#define GPIO_RMP3_SPI2				((uint32_t) (REGISTER_NUM2 | START_POS(12) | BIT_WIDTH2 | BIT_VALUE(3))) /*!< SPI2 Alternate Function mapping								*/
#define GPIO_RMP1_SPI3				((uint32_t) (REGISTER_NUM2 | START_POS(14) | BIT_WIDTH2 | BIT_VALUE(1))) /*!< SPI3 Alternate Function mapping								*/
#define GPIO_RMP2_SPI3				((uint32_t) (REGISTER_NUM2 | START_POS(14) | BIT_WIDTH2 | BIT_VALUE(2))) /*!< SPI3 Alternate Function mapping								*/
#define GPIO_RMP3_SPI3				((uint32_t) (REGISTER_NUM2 | START_POS(14) | BIT_WIDTH2 | BIT_VALUE(3))) /*!< SPI3 Alternate Function mapping								*/
#define GPIO_RMP1_SPI1				(((uint32_t) (REGISTER_NUM2 | START_POS(18) | BIT_WIDTH1 | BIT_VALUE(0))<<16) | ((uint32_t) (REGISTER_NUM0 | START_POS(0) | BIT_WIDTH1 | BIT_VALUE(1)))) /*!< SPI1 Alternate Function mapping								*/
#define GPIO_RMP2_SPI1				(((uint32_t) (REGISTER_NUM2 | START_POS(18) | BIT_WIDTH1 | BIT_VALUE(1))<<16) | ((uint32_t) (REGISTER_NUM0 | START_POS(0) | BIT_WIDTH1 | BIT_VALUE(0)))) /*!< SPI1 Alternate Function mapping								*/
#define GPIO_RMP3_SPI1				(((uint32_t) (REGISTER_NUM2 | START_POS(18) | BIT_WIDTH1 | BIT_VALUE(1))<<16) | ((uint32_t) (REGISTER_NUM0 | START_POS(0) | BIT_WIDTH1 | BIT_VALUE(1)))) /*!< SPI1 Alternate Function mapping								*/
#define GPIO_RMP1_USART2			(((uint32_t) (REGISTER_NUM2 | START_POS(19) | BIT_WIDTH1 | BIT_VALUE(0))<<16) | ((uint32_t) (REGISTER_NUM0 | START_POS(3) | BIT_WIDTH1 | BIT_VALUE(1))))  /*!< USART2 Alternate Function mapping								*/
#define GPIO_RMP2_USART2			(((uint32_t) (REGISTER_NUM2 | START_POS(19) | BIT_WIDTH1 | BIT_VALUE(1))<<16) | ((uint32_t) (REGISTER_NUM0 | START_POS(3) | BIT_WIDTH1 | BIT_VALUE(0))))  /*!< USART2 Alternate Function mapping								*/
#define GPIO_RMP3_USART2			(((uint32_t) (REGISTER_NUM2 | START_POS(19) | BIT_WIDTH1 | BIT_VALUE(1))<<16) | ((uint32_t) (REGISTER_NUM0 | START_POS(3) | BIT_WIDTH1 | BIT_VALUE(1))))  /*!< USART2 Alternate Function mapping								*/
#define GPIO_RMP1_UART4				((uint32_t) (REGISTER_NUM2 | START_POS(20) | BIT_WIDTH2 | BIT_VALUE(1))) /*!< UART4 Alternate Function mapping								*/
#define GPIO_RMP2_UART4				((uint32_t) (REGISTER_NUM2 | START_POS(20) | BIT_WIDTH2 | BIT_VALUE(2))) /*!< UART4 Alternate Function mapping								*/
#define GPIO_RMP3_UART4				((uint32_t) (REGISTER_NUM2 | START_POS(20) | BIT_WIDTH2 | BIT_VALUE(3))) /*!< UART4 Alternate Function mapping								*/
#define GPIO_RMP1_UART5				((uint32_t) (REGISTER_NUM2 | START_POS(22) | BIT_WIDTH2 | BIT_VALUE(1))) /*!< UART5 Alternate Function mapping								*/
#define GPIO_RMP2_UART5				((uint32_t) (REGISTER_NUM2 | START_POS(22) | BIT_WIDTH2 | BIT_VALUE(2))) /*!< UART5 Alternate Function mapping								*/
#define GPIO_RMP3_UART5				((uint32_t) (REGISTER_NUM2 | START_POS(22) | BIT_WIDTH2 | BIT_VALUE(3))) /*!< UART5 Alternate Function mapping								*/
#define GPIO_RMP2_UART6				((uint32_t) (REGISTER_NUM2 | START_POS(24) | BIT_WIDTH2 | BIT_VALUE(2))) /*!< UART6 Alternate Function mapping								*/
#define GPIO_RMP3_UART6				((uint32_t) (REGISTER_NUM2 | START_POS(24) | BIT_WIDTH2 | BIT_VALUE(3))) /*!< UART6 Alternate Function mapping								*/
#define GPIO_RMP1_UART7				((uint32_t) (REGISTER_NUM2 | START_POS(26) | BIT_WIDTH2 | BIT_VALUE(1))) /*!< UART7 Alternate Function mapping								*/
#define GPIO_RMP3_UART7				((uint32_t) (REGISTER_NUM2 | START_POS(26) | BIT_WIDTH2 | BIT_VALUE(3))) /*!< UART7 Alternate Function mapping								*/
#define GPIO_RMP1_TIM8 				((uint32_t) (REGISTER_NUM2 | START_POS(30) | BIT_WIDTH2 | BIT_VALUE(1))) /*!< TIM8 Alternate Function mapping								*/
#define GPIO_RMP3_TIM8 				((uint32_t) (REGISTER_NUM2 | START_POS(30) | BIT_WIDTH2 | BIT_VALUE(3))) /*!< TIM8 Alternate Function mapping								*/

/* AFIO_RMP_CFG4 */
#define GPIO_RMP1_COMP1      		((uint32_t) (REGISTER_NUM3 | START_POS(0) | BIT_WIDTH2 | BIT_VALUE(1))) /*!< COMP1 Alternate Function mapping 								*/
#define GPIO_RMP2_COMP1      		((uint32_t) (REGISTER_NUM3 | START_POS(0) | BIT_WIDTH2 | BIT_VALUE(2))) /*!< COMP1 Alternate Function mapping 								*/
#define GPIO_RMP3_COMP1      		((uint32_t) (REGISTER_NUM3 | START_POS(0) | BIT_WIDTH2 | BIT_VALUE(3))) /*!< COMP1 Alternate Function mapping 								*/
#define GPIO_RMP1_COMP2      		((uint32_t) (REGISTER_NUM3 | START_POS(2) | BIT_WIDTH2 | BIT_VALUE(1))) /*!< COMP2 Alternate Function mapping 								*/
#define GPIO_RMP2_COMP2      		((uint32_t) (REGISTER_NUM3 | START_POS(2) | BIT_WIDTH2 | BIT_VALUE(2))) /*!< COMP2 Alternate Function mapping 								*/
#define GPIO_RMP3_COMP2      		((uint32_t) (REGISTER_NUM3 | START_POS(2) | BIT_WIDTH2 | BIT_VALUE(3))) /*!< COMP2 Alternate Function mapping 								*/
#define GPIO_RMP1_COMP3      		((uint32_t) (REGISTER_NUM3 | START_POS(4) | BIT_WIDTH2 | BIT_VALUE(1))) /*!< COMP3 Alternate Function mapping 								*/
#define GPIO_RMP3_COMP3      		((uint32_t) (REGISTER_NUM3 | START_POS(4) | BIT_WIDTH2 | BIT_VALUE(3))) /*!< COMP3 Alternate Function mapping 								*/
#define GPIO_RMP1_COMP4      		((uint32_t) (REGISTER_NUM3 | START_POS(6) | BIT_WIDTH2 | BIT_VALUE(1))) /*!< COMP4 Alternate Function mapping 								*/
#define GPIO_RMP3_COMP4      		((uint32_t) (REGISTER_NUM3 | START_POS(6) | BIT_WIDTH2 | BIT_VALUE(3))) /*!< COMP4 Alternate Function mapping 								*/
#define GPIO_RMP1_COMP5      		((uint32_t) (REGISTER_NUM3 | START_POS(8) | BIT_WIDTH2 | BIT_VALUE(1))) /*!< COMP5 Alternate Function mapping 								*/
#define GPIO_RMP2_COMP5      		((uint32_t) (REGISTER_NUM3 | START_POS(8) | BIT_WIDTH2 | BIT_VALUE(2))) /*!< COMP5 Alternate Function mapping 								*/
#define GPIO_RMP3_COMP5      		((uint32_t) (REGISTER_NUM3 | START_POS(8) | BIT_WIDTH2 | BIT_VALUE(3))) /*!< COMP5 Alternate Function mapping 								*/
#define GPIO_RMP1_COMP6      		((uint32_t) (REGISTER_NUM3 | START_POS(10) | BIT_WIDTH2 | BIT_VALUE(1))) /*!< COMP6 Alternate Function mapping 								*/
#define GPIO_RMP3_COMP6      		((uint32_t) (REGISTER_NUM3 | START_POS(10) | BIT_WIDTH2 | BIT_VALUE(3))) /*!< COMP6 Alternate Function mapping 								*/
#define GPIO_RMP_COMP7       		((uint32_t) (REGISTER_NUM3 | START_POS(12) | BIT_WIDTH1 | BIT_VALUE(1))) /*!< COMP7 Alternate Function mapping 								*/
#define GPIO_RMP_ADC3_ETRI   		((uint32_t) (REGISTER_NUM3 | START_POS(14) | BIT_WIDTH1 | BIT_VALUE(1))) /*!< ADC3_ETRGINJ Alternate Function mapping 						*/
#define GPIO_RMP_ADC3_ETRR   		((uint32_t) (REGISTER_NUM3 | START_POS(15) | BIT_WIDTH1 | BIT_VALUE(1))) /*!< ADC3_ETRGREG Alternate Function mapping 						*/
#define GPIO_RMP_ADC4_ETRI   		((uint32_t) (REGISTER_NUM3 | START_POS(16) | BIT_WIDTH1 | BIT_VALUE(1))) /*!< ADC4_ETRGINJ Alternate Function mapping 						*/
#define GPIO_RMP_ADC4_ETRR   		((uint32_t) (REGISTER_NUM3 | START_POS(17) | BIT_WIDTH1 | BIT_VALUE(1))) /*!< ADC4_ETRGREG Alternate Function mapping 						*/
#define GPIO_RMP_TSC_OUT_CTRL		((uint32_t) (REGISTER_NUM3 | START_POS(18) | BIT_WIDTH1 | BIT_VALUE(1))) /*!< TSC_OUT_CTRL Alternate Function mapping 						*/
#define GPIO_RMP_QSPI_XIP_EN 		((uint32_t) (REGISTER_NUM3 | START_POS(19) | BIT_WIDTH1 | BIT_VALUE(1))) /*!< QSPI_XIP_EN Alternate Function mapping							*/
#define GPIO_RMP_SPI1_NSS  			((uint32_t) (REGISTER_NUM3 | START_POS(22) | BIT_WIDTH1 | BIT_VALUE(1))) /*!< SPI1 NSS Alternate Function mapping							*/
#define GPIO_RMP_SPI2_NSS  			((uint32_t) (REGISTER_NUM3 | START_POS(23) | BIT_WIDTH1 | BIT_VALUE(1))) /*!< SPI2 NSS Alternate Function mapping							*/
#define GPIO_RMP_SPI3_NSS  			((uint32_t) (REGISTER_NUM3 | START_POS(24) | BIT_WIDTH1 | BIT_VALUE(1))) /*!< SPI3 NSS Alternate Function mapping							*/
#define GPIO_RMP_QSPI_MISO 			((uint32_t) (REGISTER_NUM3 | START_POS(25) | BIT_WIDTH1 | BIT_VALUE(1))) /*!< QSPI MISO Alternate Function mapping							*/

/* AFIO_RMP_CFG5 */
#define GPIO_RMP_DET_EN_EGB4   		((uint32_t) (REGISTER_NUM4 | START_POS(23) | BIT_WIDTH1 | BIT_VALUE(1))) /*!< EGB4 Detect Alternate Function mapping							*/
#define GPIO_RMP_DET_EN_EGB3   		((uint32_t) (REGISTER_NUM4 | START_POS(22) | BIT_WIDTH1 | BIT_VALUE(1))) /*!< EGB4 Detect Alternate Function mapping							*/
#define GPIO_RMP_DET_EN_EGB2   		((uint32_t) (REGISTER_NUM4 | START_POS(21) | BIT_WIDTH1 | BIT_VALUE(1))) /*!< EGB4 Detect Alternate Function mapping							*/
#define GPIO_RMP_DET_EN_EGB1   		((uint32_t) (REGISTER_NUM4 | START_POS(20) | BIT_WIDTH1 | BIT_VALUE(1))) /*!< EGB4 Detect Alternate Function mapping							*/
#define GPIO_RMP_DET_EN_EGBN4  		((uint32_t) (REGISTER_NUM4 | START_POS(19) | BIT_WIDTH1 | BIT_VALUE(1))) /*!< EGBN4 Detect Alternate Function mapping						*/
#define GPIO_RMP_DET_EN_EGBN3  		((uint32_t) (REGISTER_NUM4 | START_POS(18) | BIT_WIDTH1 | BIT_VALUE(1))) /*!< EGBN3 Detect Alternate Function mapping						*/
#define GPIO_RMP_DET_EN_EGBN2  		((uint32_t) (REGISTER_NUM4 | START_POS(17) | BIT_WIDTH1 | BIT_VALUE(1))) /*!< EGBN2 Detect Alternate Function mapping						*/
#define GPIO_RMP_DET_EN_EGBN1  		((uint32_t) (REGISTER_NUM4 | START_POS(16) | BIT_WIDTH1 | BIT_VALUE(1))) /*!< EGBN1 Detect Alternate Function mapping						*/
#define GPIO_RMP_DET_EN_ECLAMP4		((uint32_t) (REGISTER_NUM4 | START_POS(15) | BIT_WIDTH1 | BIT_VALUE(1))) /*!< ECLAMP4 Detect Alternate Function mapping						*/
#define GPIO_RMP_DET_EN_ECLAMP3		((uint32_t) (REGISTER_NUM4 | START_POS(14) | BIT_WIDTH1 | BIT_VALUE(1))) /*!< ECLAMP3 Detect Alternate Function mapping						*/
#define GPIO_RMP_DET_EN_ECLAMP2		((uint32_t) (REGISTER_NUM4 | START_POS(13) | BIT_WIDTH1 | BIT_VALUE(1))) /*!< ECLAMP2 Detect Alternate Function mapping						*/
#define GPIO_RMP_DET_EN_ECLAMP1		((uint32_t) (REGISTER_NUM4 | START_POS(12) | BIT_WIDTH1 | BIT_VALUE(1))) /*!< ECLAMP1 Detect Alternate Function mapping						*/
#define GPIO_RMP_RST_EN_EGB4   		((uint32_t) (REGISTER_NUM4 | START_POS(11) | BIT_WIDTH1 | BIT_VALUE(1))) /*!< EGB4 Reset Alternate Function mapping							*/
#define GPIO_RMP_RST_EN_EGB3   		((uint32_t) (REGISTER_NUM4 | START_POS(10) | BIT_WIDTH1 | BIT_VALUE(1))) /*!< EGB3 Reset Alternate Function mapping							*/
#define GPIO_RMP_RST_EN_EGB2   		((uint32_t) (REGISTER_NUM4 | START_POS(9) | BIT_WIDTH1 | BIT_VALUE(1))) /*!< EGB2 Reset Alternate Function mapping							*/
#define GPIO_RMP_RST_EN_EGB1   		((uint32_t) (REGISTER_NUM4 | START_POS(8) | BIT_WIDTH1 | BIT_VALUE(1))) /*!< EGB1 Reset Alternate Function mapping							*/
#define GPIO_RMP_RST_EN_EGBN4  		((uint32_t) (REGISTER_NUM4 | START_POS(7) | BIT_WIDTH1 | BIT_VALUE(1))) /*!< EGBN4 Reset Alternate Function mapping							*/
#define GPIO_RMP_RST_EN_EGBN3  		((uint32_t) (REGISTER_NUM4 | START_POS(6) | BIT_WIDTH1 | BIT_VALUE(1))) /*!< EGBN3 Reset Alternate Function mapping							*/
#define GPIO_RMP_RST_EN_EGBN2  		((uint32_t) (REGISTER_NUM4 | START_POS(5) | BIT_WIDTH1 | BIT_VALUE(1))) /*!< EGBN2 Reset Alternate Function mapping							*/
#define GPIO_RMP_RST_EN_EGBN1  		((uint32_t) (REGISTER_NUM4 | START_POS(4) | BIT_WIDTH1 | BIT_VALUE(1))) /*!< EGBN1 Reset Alternate Function mapping							*/
#define GPIO_RMP_RST_EN_ECLAMP4		((uint32_t) (REGISTER_NUM4 | START_POS(3) | BIT_WIDTH1 | BIT_VALUE(1))) /*!< ECLAMP4 Reset Alternate Function mapping						*/
#define GPIO_RMP_RST_EN_ECLAMP3		((uint32_t) (REGISTER_NUM4 | START_POS(2) | BIT_WIDTH1 | BIT_VALUE(1))) /*!< ECLAMP3 Reset Alternate Function mapping						*/
#define GPIO_RMP_RST_EN_ECLAMP2		((uint32_t) (REGISTER_NUM4 | START_POS(1) | BIT_WIDTH1 | BIT_VALUE(1))) /*!< ECLAMP2 Reset Alternate Function mapping						*/
#define GPIO_RMP_RST_EN_ECLAMP1		((uint32_t) (REGISTER_NUM4 | START_POS(0) | BIT_WIDTH1 | BIT_VALUE(1))) /*!< ECLAMP1 Reset Alternate Function mapping						*/

/**
 * @}
 */

/** @defgroup GPIO_Port_Sources GPIO Port Source
 * @{
 */

#define GPIOA_PORT_SOURCE							((uint8_t) 0x00)
#define GPIOB_PORT_SOURCE							((uint8_t) 0x01)
#define GPIOC_PORT_SOURCE							((uint8_t) 0x02)
#define GPIOD_PORT_SOURCE							((uint8_t) 0x03)
#define GPIOE_PORT_SOURCE							((uint8_t) 0x04)
#define GPIOF_PORT_SOURCE							((uint8_t) 0x05)
#define GPIOG_PORT_SOURCE							((uint8_t) 0x06)

/**
 * @}
 */

/** @defgroup GPIO_Pin_sources GPIO Pin Source
 * @{
 */

#define GPIO_PIN_SOURCE0  ((uint8_t) 0x00)
#define GPIO_PIN_SOURCE1  ((uint8_t) 0x01)
#define GPIO_PIN_SOURCE2  ((uint8_t) 0x02)
#define GPIO_PIN_SOURCE3  ((uint8_t) 0x03)
#define GPIO_PIN_SOURCE4  ((uint8_t) 0x04)
#define GPIO_PIN_SOURCE5  ((uint8_t) 0x05)
#define GPIO_PIN_SOURCE6  ((uint8_t) 0x06)
#define GPIO_PIN_SOURCE7  ((uint8_t) 0x07)
#define GPIO_PIN_SOURCE8  ((uint8_t) 0x08)
#define GPIO_PIN_SOURCE9  ((uint8_t) 0x09)
#define GPIO_PIN_SOURCE10 ((uint8_t) 0x0A)
#define GPIO_PIN_SOURCE11 ((uint8_t) 0x0B)
#define GPIO_PIN_SOURCE12 ((uint8_t) 0x0C)
#define GPIO_PIN_SOURCE13 ((uint8_t) 0x0D)
#define GPIO_PIN_SOURCE14 ((uint8_t) 0x0E)
#define GPIO_PIN_SOURCE15 ((uint8_t) 0x0F)

/**
 * @}
 */


/** @defgroup GPIO_Exported_Functions GPIO Exported Function
 * @{
 */

void		GPIO_DeInit (GPIO_Module* GPIOx);
void		GPIO_AFIODeInit (void);
void		GPIO_Init(GPIO_Module* GPIOx, GPIO_InitType* GPIO_InitStruct);
void		GPIO_InitStruct (GPIO_InitType* GPIO_InitStruct);
uint8_t		GPIO_ReadInputDataBit (GPIO_Module* GPIOx, uint16_t Pin);
uint16_t	GPIO_ReadInputData (GPIO_Module* GPIOx);
uint8_t		GPIO_ReadOutputDataBit (GPIO_Module* GPIOx, uint16_t Pin);
uint16_t	GPIO_ReadOutputData (GPIO_Module* GPIOx);
void		GPIO_SetBits (GPIO_Module* GPIOx, uint16_t Pin);
void 		GPIO_SetClearBits(GPIO_Module* GPIOx, uint32_t Pin);
void		GPIO_ResetBits (GPIO_Module* GPIOx, uint16_t Pin);
void		GPIO_WriteBit (GPIO_Module* GPIOx, uint16_t Pin, Bit_OperateType BitCmd);
void		GPIO_Write (GPIO_Module* GPIOx, uint16_t PortVal);
void		GPIO_ConfigPinLock (GPIO_Module* GPIOx, uint16_t Pin);
void		GPIO_ConfigEventOutput (uint8_t PortSource, uint8_t PinSource);
void		GPIO_CtrlEventOutput (FunctionalState Cmd);
void		GPIO_ConfigPinRemap (uint32_t RmpPin, FunctionalState Cmd);
void		GPIO_ConfigEXTILine (uint8_t PortSource, uint8_t PinSource);
void		GPIO_SetBitsHigh16 (GPIO_Module* GPIOx, uint32_t Pin);

/**
 * @}
 */

/** @defgroup CAN_Private_Macros CAN Private Macros
  * @{
  */

#define IS_GPIO_ALL_PERIPH(PERIPH)	(((PERIPH) == GPIOA) || ((PERIPH) == GPIOB) || ((PERIPH) == GPIOC) || \
									 ((PERIPH) == GPIOD) || ((PERIPH) == GPIOE) || ((PERIPH) == GPIOF) || \
									 ((PERIPH) == GPIOG))

#define IS_GPIO_SPEED(SPEED)	(((SPEED) == GPIO_INPUT)      || ((SPEED) == GPIO_Speed_10MHz) || \
								 ((SPEED) == GPIO_Speed_2MHz) || ((SPEED) == GPIO_Speed_50MHz))

#define IS_GPIO_MODE(MODE)	(((MODE) == GPIO_Mode_AIN)    || ((MODE) == GPIO_Mode_IN_FLOATING) || \
							 ((MODE) == GPIO_Mode_IPD)    || ((MODE) == GPIO_Mode_IPU)         || \
							 ((MODE) == GPIO_Mode_Out_OD) || ((MODE) == GPIO_Mode_Out_PP)      || \
							 ((MODE) == GPIO_Mode_AF_OD)  || ((MODE) == GPIO_Mode_AF_PP))

#define IS_GPIO_BIT_OPERATE(OPERATE)	(((OPERATE) == Bit_RESET) || ((OPERATE) == Bit_SET))

#define IS_GPIO_PIN(PIN)		((PIN) != (uint16_t) 0x00)

#define IS_GET_GPIO_PIN(PIN)	(((PIN) == GPIO_PIN_0)  || ((PIN) == GPIO_PIN_1)  || ((PIN) == GPIO_PIN_2)  || \
								 ((PIN) == GPIO_PIN_3)  || ((PIN) == GPIO_PIN_4)  || ((PIN) == GPIO_PIN_5)  || \
								 ((PIN) == GPIO_PIN_6)  || ((PIN) == GPIO_PIN_7)  || ((PIN) == GPIO_PIN_8)  || \
								 ((PIN) == GPIO_PIN_9)  || ((PIN) == GPIO_PIN_10) || ((PIN) == GPIO_PIN_11) || \
								 ((PIN) == GPIO_PIN_12) || ((PIN) == GPIO_PIN_13) || ((PIN) == GPIO_PIN_14) || \
								 ((PIN) == GPIO_PIN_15))

#define IS_GPIO_REMAP(REMAP)		(((REMAP) == GPIO_RMP_SPI1)              || ((REMAP) == GPIO_RMP_I2C1)              || \
									 ((REMAP) == GPIO_RMP_USART1)            || ((REMAP) == GPIO_RMP_USART2)            || \
									 ((REMAP) == GPIO_PART_RMP_USART3)       || ((REMAP) == GPIO_ALL_RMP_USART3)        || \
									 ((REMAP) == GPIO_PART1_RMP_TIM1)        || ((REMAP) == GPIO_ALL_RMP_TIM1)          || \
									 ((REMAP) == GPIO_PART1_RMP_TIM2)   	 || ((REMAP) == GPIO_PART2_RMP_TIM2)        || \
									 ((REMAP) == GPIO_ALL_RMP_TIM2)          || ((REMAP) == GPIO_PART1_RMP_TIM3)        || \
									 ((REMAP) == GPIO_ALL_RMP_TIM3)          || ((REMAP) == GPIO_RMP_TIM4)              || \
									 ((REMAP) == GPIO_RMP1_CAN1)             || ((REMAP) == GPIO_RMP2_CAN1)             || \
									 ((REMAP) == GPIO_RMP3_CAN1)			 || ((REMAP) == GPIO_RMP_PD01)              || \
									 ((REMAP) == GPIO_RMP_TIM5CH4)           || ((REMAP) == GPIO_RMP_ADC1_ETRI)         || \
									 ((REMAP) == GPIO_RMP_ADC1_ETRR)         || ((REMAP) == GPIO_RMP_ADC2_ETRI)         || \
									 ((REMAP) == GPIO_RMP_ADC2_ETRR)         || ((REMAP) == GPIO_RMP_SW_JTAG_NO_NJTRST) || \
									 ((REMAP) == GPIO_RMP_SW_JTAG_SW_ENABLE) || ((REMAP) == GPIO_RMP_SW_JTAG_DISABLE)   || \
									 ((REMAP) == GPIO_RMP1_CAN2)             || \
									 ((REMAP) == GPIO_RMP3_CAN2)             || ((REMAP) == GPIO_RMP2_QSPI)             || \
									 ((REMAP) == GPIO_RMP3_QSPI)             || ((REMAP) == GPIO_RMP1_I2C2)             || \
									 ((REMAP) == GPIO_RMP3_I2C2)             || ((REMAP) == GPIO_RMP2_I2C3)             || \
									 ((REMAP) == GPIO_RMP3_I2C3)             || ((REMAP) == GPIO_RMP1_I2C4)             || \
									 ((REMAP) == GPIO_RMP3_I2C4)             || ((REMAP) == GPIO_RMP1_SPI2)             || \
									 ((REMAP) == GPIO_RMP3_SPI2)             || ((REMAP) == GPIO_RMP1_SPI3)             || \
									 ((REMAP) == GPIO_RMP2_SPI3)             || ((REMAP) == GPIO_RMP3_SPI3)             || \
									 ((REMAP) == GPIO_RMP1_SPI1)             || ((REMAP) == GPIO_RMP2_SPI1)             || \
									 ((REMAP) == GPIO_RMP3_SPI1)             || ((REMAP) == GPIO_RMP1_USART2)           || \
									 ((REMAP) == GPIO_RMP2_USART2)           || ((REMAP) == GPIO_RMP3_USART2)           || \
									 ((REMAP) == GPIO_RMP1_UART4)            || ((REMAP) == GPIO_RMP2_UART4)            || \
									 ((REMAP) == GPIO_RMP3_UART4)            || ((REMAP) == GPIO_RMP1_UART5)            || \
									 ((REMAP) == GPIO_RMP2_UART5)            || ((REMAP) == GPIO_RMP3_UART5)            || \
									 ((REMAP) == GPIO_RMP2_UART6)            || ((REMAP) == GPIO_RMP3_UART6)            || \
									 ((REMAP) == GPIO_RMP1_UART7)            || ((REMAP) == GPIO_RMP3_UART7)            || \
									 ((REMAP) == GPIO_RMP1_TIM8)             || ((REMAP) == GPIO_RMP3_TIM8)             || \
									 ((REMAP) == GPIO_RMP1_COMP1)            || ((REMAP) == GPIO_RMP2_COMP1)            || \
									 ((REMAP) == GPIO_RMP3_COMP1)            || ((REMAP) == GPIO_RMP1_COMP2)            || \
									 ((REMAP) == GPIO_RMP2_COMP2)            || ((REMAP) == GPIO_RMP3_COMP2)            || \
									 ((REMAP) == GPIO_RMP1_COMP3)            || ((REMAP) == GPIO_RMP3_COMP3)            || \
									 ((REMAP) == GPIO_RMP1_COMP4)            || ((REMAP) == GPIO_RMP3_COMP4)            || \
									 ((REMAP) == GPIO_RMP1_COMP5)            || ((REMAP) == GPIO_RMP2_COMP5)            || \
									 ((REMAP) == GPIO_RMP3_COMP5)            || ((REMAP) == GPIO_RMP1_COMP6)            || \
									 ((REMAP) == GPIO_RMP3_COMP6)            || ((REMAP) == GPIO_RMP_COMP7)             || \
									 ((REMAP) == GPIO_RMP_ADC3_ETRI)         || ((REMAP) == GPIO_RMP_ADC3_ETRR)         || \
									 ((REMAP) == GPIO_RMP_ADC4_ETRI)         || ((REMAP) == GPIO_RMP_ADC4_ETRR)         || \
									 ((REMAP) == GPIO_RMP_TSC_OUT_CTRL)      || ((REMAP) == GPIO_RMP_QSPI_XIP_EN)       || \
									 ((REMAP) == GPIO_RMP_SPI1_NSS)          || ((REMAP) == GPIO_RMP_SPI2_NSS)          || \
									 ((REMAP) == GPIO_RMP_SPI3_NSS)          || ((REMAP) == GPIO_RMP_QSPI_MISO)         || \
									 ((REMAP) == GPIO_PART2_RMP_TIM1)        || ((REMAP) == GPIO_RMP_DET_EN_EGB4)       || \
									 ((REMAP) == GPIO_RMP_DET_EN_EGB3)       || ((REMAP) == GPIO_RMP_DET_EN_EGB2)       || \
									 ((REMAP) == GPIO_RMP_DET_EN_EGB1)       || ((REMAP) == GPIO_RMP_DET_EN_EGBN4)      || \
									 ((REMAP) == GPIO_RMP_DET_EN_EGBN3)      || ((REMAP) == GPIO_RMP_DET_EN_EGBN2)      || \
									 ((REMAP) == GPIO_RMP_DET_EN_EGBN1)      || ((REMAP) == GPIO_RMP_DET_EN_ECLAMP4)    || \
									 ((REMAP) == GPIO_RMP_DET_EN_ECLAMP3)    || ((REMAP) == GPIO_RMP_DET_EN_ECLAMP2)    || \
									 ((REMAP) == GPIO_RMP_DET_EN_ECLAMP1)    || ((REMAP) == GPIO_RMP_RST_EN_EGB4)       || \
									 ((REMAP) == GPIO_RMP_RST_EN_EGB3)       || ((REMAP) == GPIO_RMP_RST_EN_EGB2)       || \
									 ((REMAP) == GPIO_RMP_RST_EN_EGB1)       || ((REMAP) == GPIO_RMP_RST_EN_EGBN4)      || \
									 ((REMAP) == GPIO_RMP_RST_EN_EGBN3)      || ((REMAP) == GPIO_RMP_RST_EN_EGBN2)      || \
									 ((REMAP) == GPIO_RMP_RST_EN_EGBN1)      || ((REMAP) == GPIO_RMP_RST_EN_ECLAMP4)    || \
									 ((REMAP) == GPIO_RMP_RST_EN_ECLAMP3)    || ((REMAP) == GPIO_RMP_RST_EN_ECLAMP2)    || \
									 ((REMAP) == GPIO_RMP_RST_EN_ECLAMP1))

#define IS_GPIO_EVENTOUT_PORT_SOURCE(PORTSOURCE)	(((PORTSOURCE) == GPIOA_PORT_SOURCE) || ((PORTSOURCE) == GPIOB_PORT_SOURCE) || \
													 ((PORTSOURCE) == GPIOC_PORT_SOURCE) || ((PORTSOURCE) == GPIOD_PORT_SOURCE) || \
													 ((PORTSOURCE) == GPIOE_PORT_SOURCE))

#define IS_GPIO_EXTI_PORT_SOURCE(PORTSOURCE)		(((PORTSOURCE) == GPIOA_PORT_SOURCE) || ((PORTSOURCE) == GPIOB_PORT_SOURCE) || \
													 ((PORTSOURCE) == GPIOC_PORT_SOURCE) || ((PORTSOURCE) == GPIOD_PORT_SOURCE) || \
													 ((PORTSOURCE) == GPIOE_PORT_SOURCE) || ((PORTSOURCE) == GPIOF_PORT_SOURCE) || \
													 ((PORTSOURCE) == GPIOG_PORT_SOURCE))

#define IS_GPIO_PIN_SOURCE(PINSOURCE)	(((PINSOURCE) == GPIO_PIN_SOURCE0)  || ((PINSOURCE) == GPIO_PIN_SOURCE1)  || \
										 ((PINSOURCE) == GPIO_PIN_SOURCE2)  || ((PINSOURCE) == GPIO_PIN_SOURCE3)  || \
										 ((PINSOURCE) == GPIO_PIN_SOURCE4)  || ((PINSOURCE) == GPIO_PIN_SOURCE5)  || \
										 ((PINSOURCE) == GPIO_PIN_SOURCE6)  || ((PINSOURCE) == GPIO_PIN_SOURCE7)  || \
										 ((PINSOURCE) == GPIO_PIN_SOURCE8)  || ((PINSOURCE) == GPIO_PIN_SOURCE9)  || \
										 ((PINSOURCE) == GPIO_PIN_SOURCE10) || ((PINSOURCE) == GPIO_PIN_SOURCE11) || \
										 ((PINSOURCE) == GPIO_PIN_SOURCE12) || ((PINSOURCE) == GPIO_PIN_SOURCE13) || \
										 ((PINSOURCE) == GPIO_PIN_SOURCE14) || ((PINSOURCE) == GPIO_PIN_SOURCE15))

/**
 * @}
 */

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

#endif /* __CM32M4xxR_GPIO_H__ */
