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
 * @file cm32m4xxr_conf.h
 * @author CMIOT Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */
#ifndef __CM32M4xxR_CONF_H__
#define __CM32M4xxR_CONF_H__

/* ---------------------------- Module Selection ---------------------------- */

#define	DRIVER_MODULE_ENABLED_ADC
#define	DRIVER_MODULE_ENABLED_BKP
#define	DRIVER_MODULE_ENABLED_CAN
#define	DRIVER_MODULE_ENABLED_COMP
#define	DRIVER_MODULE_ENABLED_CRC
#define	DRIVER_MODULE_ENABLED_DAC
#define	DRIVER_MODULE_ENABLED_DBG
#define	DRIVER_MODULE_ENABLED_DMA
#define	DRIVER_MODULE_ENABLED_EXTI
#define	DRIVER_MODULE_ENABLED_FLASH
#define	DRIVER_MODULE_ENABLED_GPIO
#define	DRIVER_MODULE_ENABLED_I2C
#define	DRIVER_MODULE_ENABLED_IWDG
#define	DRIVER_MODULE_ENABLED_OPAMP
#define	DRIVER_MODULE_ENABLED_PWR
#define	DRIVER_MODULE_ENABLED_QSPI
#define	DRIVER_MODULE_ENABLED_RCC
#define	DRIVER_MODULE_ENABLED_RNGC
#define	DRIVER_MODULE_ENABLED_RTC
#define	DRIVER_MODULE_ENABLED_SPI
#define	DRIVER_MODULE_ENABLED_TIM
#define	DRIVER_MODULE_ENABLED_TSC
#define	DRIVER_MODULE_ENABLED_USART
#define	DRIVER_MODULE_ENABLED_WWDG
#define DRIVER_MODULE_ENABLED_MISC


/* ----------------------- HSE/HSI Values adaptation ------------------------ */
/**
  * @brief Adjust the value of External High Speed oscillator (HSE) used in your application.
  *        This value is used by the RCC module to compute the system frequency
  *        (when HSE is used as system clock source, directly or through the PLL).
  */
#if !defined  (HSE_VALUE)
  #define HSE_VALUE              (8000000)  /*!< Value of the External oscillator in Hz */
#endif /* HSE_VALUE */

#if !defined  (HSE_STARTUP_TIMEOUT)
  #define HSE_STARTUP_TIMEOUT    ((uint16_t) 0x0500)      /*!< Time out for HSE start up, in ms */
#endif /* HSE_STARTUP_TIMEOUT */

/**
  * @brief Internal High Speed oscillator (HSI) value.
  *        This value is used by the RCC module to compute the system frequency
  *        (when HSI is used as system clock source, directly or through the PLL).
  */
#if !defined  (HSI_VALUE)
  #define HSI_VALUE              (8000000) /*!< Value of the Internal oscillator in Hz */
#endif /* HSI_VALUE */

/**
  * @brief Internal Low Speed oscillator (LSI) value.
  */
#if !defined  (LSI_VALUE)
 #define LSI_VALUE               ((uint32_t) 40000)	/*!< LSI Typical Value in Hz */
#endif /* LSI_VALUE */								/*!< Value of the Internal Low Speed oscillator in Hz
														The real value may vary depending on the variations
														in voltage and temperature. */
/**
  * @brief External Low Speed oscillator (LSE) value.
  */
#if !defined  (LSE_VALUE)
 #define LSE_VALUE               ((uint32_t) 32768)    /*!< Value of the External Low Speed oscillator in Hz */
#endif /* LSE_VALUE */

#if !defined  (LSE_STARTUP_TIMEOUT)
  #define LSE_STARTUP_TIMEOUT    ((uint32_t) 0x8000)     /*!< Time out for LSE start up, in ms */
#endif /* LSE_STARTUP_TIMEOUT */

/* Tip: To avoid modifying this file each time you need to use different HSE,
   ===  you can define the HSE value in your toolchain compiler preprocessor. */


/* -------------------------- Module's Header File -------------------------- */

#ifdef	DRIVER_MODULE_ENABLED_ADC
	#include "cm32m4xxr_adc.h"
#endif	/* DRIVER_MODULE_ENABLED_ADC */

#ifdef	DRIVER_MODULE_ENABLED_BKP
	#include "cm32m4xxr_bkp.h"
#endif	/* DRIVER_MODULE_ENABLED_BKP */

#ifdef	DRIVER_MODULE_ENABLED_CAN
	#include "cm32m4xxr_can.h"
#endif	/* DRIVER_MODULE_ENABLED_CAN */

#ifdef	DRIVER_MODULE_ENABLED_COMP
	#include "cm32m4xxr_comp.h"
#endif	/* DRIVER_MODULE_ENABLED_COMP */

#ifdef	DRIVER_MODULE_ENABLED_CRC
	#include "cm32m4xxr_crc.h"
#endif	/* DRIVER_MODULE_ENABLED_CRC */

#ifdef	DRIVER_MODULE_ENABLED_DAC
	#include "cm32m4xxr_dac.h"
#endif	/* DRIVER_MODULE_ENABLED_DAC */

#ifdef	DRIVER_MODULE_ENABLED_DBG
	#include "cm32m4xxr_dbg.h"
#endif	/* DRIVER_MODULE_ENABLED_DBG */

#ifdef	DRIVER_MODULE_ENABLED_DMA
	#include "cm32m4xxr_dma.h"
#endif	/* DRIVER_MODULE_ENABLED_DMA */

#ifdef	DRIVER_MODULE_ENABLED_EXTI
	#include "cm32m4xxr_exti.h"
#endif	/* DRIVER_MODULE_ENABLED_EXTI */

#ifdef	DRIVER_MODULE_ENABLED_FLASH
	#include "cm32m4xxr_flash.h"
#endif	/* DRIVER_MODULE_ENABLED_FLASH */

#ifdef	DRIVER_MODULE_ENABLED_GPIO
	#include "cm32m4xxr_gpio.h"
#endif	/* DRIVER_MODULE_ENABLED_GPIO */

#ifdef	DRIVER_MODULE_ENABLED_I2C
	#include "cm32m4xxr_i2c.h"
#endif	/* DRIVER_MODULE_ENABLED_I2C */

#ifdef	DRIVER_MODULE_ENABLED_IWDG
	#include "cm32m4xxr_iwdg.h"
#endif	/* DRIVER_MODULE_ENABLED_IWDG */

#ifdef	DRIVER_MODULE_ENABLED_OPAMP
	#include "cm32m4xxr_opamp.h"
#endif	/* DRIVER_MODULE_ENABLED_OPAMP */

#ifdef	DRIVER_MODULE_ENABLED_PWR
	#include "cm32m4xxr_pwr.h"
#endif	/* DRIVER_MODULE_ENABLED_PWR */

#ifdef	DRIVER_MODULE_ENABLED_QSPI
	#include "cm32m4xxr_qspi.h"
#endif	/* DRIVER_MODULE_ENABLED_QSPI */

#ifdef	DRIVER_MODULE_ENABLED_RCC
	#include "cm32m4xxr_rcc.h"
#endif	/* DRIVER_MODULE_ENABLED_RCC */

#ifdef	DRIVER_MODULE_ENABLED_RNGC
	#include "cm32m4xxr_rngc.h"
#endif	/* DRIVER_MODULE_ENABLED_RNGC */

#ifdef	DRIVER_MODULE_ENABLED_RTC
	#include "cm32m4xxr_rtc.h"
#endif	/* DRIVER_MODULE_ENABLED_RTC */

#ifdef	DRIVER_MODULE_ENABLED_SPI
	#include "cm32m4xxr_spi.h"
#endif	/* DRIVER_MODULE_ENABLED_SPI */

#ifdef	DRIVER_MODULE_ENABLED_TIM
	#include "cm32m4xxr_tim.h"
#endif	/* DRIVER_MODULE_ENABLED_TIM */

#ifdef	DRIVER_MODULE_ENABLED_TSC
	#include "cm32m4xxr_tsc.h"
#endif	/* DRIVER_MODULE_ENABLED_TSC */

#ifdef	DRIVER_MODULE_ENABLED_USART
	#include "cm32m4xxr_usart.h"
#endif	/* DRIVER_MODULE_ENABLED_USART */

#ifdef	DRIVER_MODULE_ENABLED_WWDG
	#include "cm32m4xxr_wwdg.h"
#endif	/* DRIVER_MODULE_ENABLED_WWDG */

#ifdef   DRIVER_MODULE_ENABLED_MISC
	#include "misc.h"
#endif /* DRIVER_MODULE_ENABLED_MISC */

/* Uncomment the line below to expanse the "assert_param" macro in the
   Standard Peripheral Library drivers code */
#define USE_FULL_ASSERT    1

#ifdef USE_FULL_ASSERT

/**
 * @brief  The assert_param macro is used for function's parameters check.
 * @param expr If expr is false, it calls assert_failed function which reports
 *         the name of the source file and the source line number of the call
 *         that failed. If expr is true, it returns no value.
 */
#define assert_param(expr) ((expr) ? (void)0 : assert_failed((const uint8_t*)#expr, (const uint8_t*)__FILE__, __LINE__))

void assert_failed(const uint8_t* expr, const uint8_t* file, uint32_t line);
#else
#define assert_param(expr) ((void) 0)
#endif /* USE_FULL_ASSERT */

#endif /* __CM32M4xxR_CONF_H__ */
