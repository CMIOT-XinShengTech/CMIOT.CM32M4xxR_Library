/*
 * Copyright (c) 2009-2019 Arm Limited. All rights reserved.
 * Copyright (c) 2019 Nuclei Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/******************************************************************************
 * @file     cm32m4xxr.h
 * @brief    NMSIS Nuclei N/NX Core Peripheral Access Layer Header File for
 *           Device CM32M4xxR
 * @version  V1.00
 * @date     20. Jun 2020
 ******************************************************************************/

#ifndef __CM32M4XXR_H__
#define __CM32M4XXR_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup CMIOT
  * @{
  */


/** @addtogroup CM32M4xxR
  * @{
  */



/* =========================================================================================================================== */
/* ================                                Interrupt Number Definition                                ================ */
/* =========================================================================================================================== */

/** @addtogroup Interrupt_number_definition
  * @{
  */

typedef enum IRQn {
/* ========================================  Nuclei N Specific Interrupt Numbers  ========================================= */
    Reserved0_IRQn       = 0,			/*!<  Internal reserved                                   */
    Reserved1_IRQn       = 1,			/*!<  Internal reserved                                   */
    Reserved2_IRQn       = 2,			/*!<  Internal reserved                                   */
    SysTimerSW_IRQn      = 3,			/*!<  System Timer SW interrupt                           */
    Reserved3_IRQn       = 4,			/*!<  Internal reserved                                   */
    Reserved4_IRQn       = 5,			/*!<  Internal reserved                                   */
    Reserved5_IRQn       = 6,			/*!<  Internal reserved                                   */
    SysTimer_IRQn        = 7,			/*!<  System Timer Interrupt                              */
    Reserved6_IRQn       = 8,			/*!<  Internal reserved                                   */
    Reserved7_IRQn       = 9,			/*!<  Internal reserved                                   */
    Reserved8_IRQn       = 10,			/*!<  Internal reserved                                   */
    Reserved9_IRQn       = 11,			/*!<  Internal reserved                                   */
    Reserved10_IRQn      = 12,			/*!<  Internal reserved                                   */
    Reserved11_IRQn      = 13,			/*!<  Internal reserved                                   */
    Reserved12_IRQn      = 14,			/*!<  Internal reserved                                   */
    Reserved13_IRQn      = 15,			/*!<  Internal reserved                                   */
    Reserved14_IRQn      = 16,			/*!<  Internal reserved                                   */
    Reserved15_IRQn      = 17,			/*!<  Internal reserved	                                  */
    Reserved16_IRQn      = 18,			/*!<  Internal reserved	                                  */

/* ===========================================  CM32M4xxR Specific Interrupt Numbers  ========================================= */
    WWDG_IRQn            = 19,			/*!< Window WatchDog Interrupt                            */
    PVD_IRQn             = 20,			/*!< PVD through EXTI Line detection Interrupt            */
    TAMPER_IRQn          = 21,			/*!< Tamper Interrupt                                     */
    RTC_IRQn             = 22,			/*!< RTC global Interrupt                                 */
    FLASH_IRQn           = 23,			/*!< FLASH global Interrupt                               */
    RCC_IRQn             = 24,			/*!< RCC global Interrupt                                 */
    EXTI0_IRQn           = 25,			/*!< EXTI Line0 Interrupt                                 */
    EXTI1_IRQn           = 26,			/*!< EXTI Line1 Interrupt                                 */
    EXTI2_IRQn           = 27,			/*!< EXTI Line2 Interrupt                                 */
    EXTI3_IRQn           = 28,			/*!< EXTI Line3 Interrupt                                 */
    EXTI4_IRQn           = 29,			/*!< EXTI Line4 Interrupt                                 */
    DMA1_Channel1_IRQn   = 30,			/*!< DMA1 Channel 1 global Interrupt                      */
    DMA1_Channel2_IRQn   = 31,			/*!< DMA1 Channel 2 global Interrupt                      */
    DMA1_Channel3_IRQn   = 32,			/*!< DMA1 Channel 3 global Interrupt                      */
    DMA1_Channel4_IRQn	 = 33,			/*!< DMA1 Channel 4 global Interrupt                      */
    DMA1_Channel5_IRQn   = 34,			/*!< DMA1 Channel 5 global Interrupt                      */
    DMA1_Channel6_IRQn   = 35,			/*!< DMA1 Channel 6 global Interrupt                      */
    DMA1_Channel7_IRQn   = 36,			/*!< DMA1 Channel 7 global Interrupt                      */
    ADC1_2_IRQn          = 37,			/*!< ADC1 and ADC2 global Interrupt                       */
    CAN1_TX_IRQn         = 38,			/*!< CAN1 TX Interrupts       */
    CAN1_RX0_IRQn        = 39, 			/*!< CAN1 RX0 Interrupts       */
    CAN1_RX1_IRQn        = 40,			/*!< CAN1 RX1 Interrupt                                   */
    CAN1_SCE_IRQn        = 41,			/*!< CAN1 SCE Interrupt                                   */
    EXTI9_5_IRQn         = 42,			/*!< External Line[9:5] Interrupts                        */
    TIM1_BRK_IRQn        = 43,			/*!< TIM1 Break Interrupt                                 */
    TIM1_UP_IRQn         = 44,			/*!< TIM1 Update Interrupt                                */
    TIM1_TRG_COM_IRQn    = 45,			/*!< TIM1 Trigger and Commutation Interrupt               */
    TIM1_CC_IRQn         = 46,			/*!< TIM1 Capture Compare Interrupt                       */
    TIM2_IRQn            = 47,			/*!< TIM2 global Interrupt                                */
    TIM3_IRQn            = 48,			/*!< TIM3 global Interrupt                                */
    TIM4_IRQn            = 49,			/*!< TIM4 global Interrupt                                */
    I2C1_EV_IRQn         = 50,			/*!< I2C1 Event Interrupt                                 */
    I2C1_ER_IRQn         = 51,			/*!< I2C1 Error Interrupt                                 */
    I2C2_EV_IRQn         = 52,			/*!< I2C2 Event Interrupt                                 */
    I2C2_ER_IRQn         = 53,			/*!< I2C2 Error Interrupt                                 */
    SPI1_IRQn            = 54,			/*!< SPI1 global Interrupt                                */
    SPI2_I2S2_IRQn       = 55,			/*!< SPI2/I2S2 global Interrupt                           */
    USART1_IRQn          = 56,			/*!< USART1 global Interrupt                              */
    USART2_IRQn          = 57,			/*!< USART2 global Interrupt                              */
    USART3_IRQn          = 58,			/*!< USART3 global Interrupt                              */
    EXTI15_10_IRQn       = 59,			/*!< External Line[15:10] Interrupts                      */
    RTCAlarm_IRQn        = 60,			/*!< RTC Alarm through EXTI Line Interrupt                */
										/*!< 61(for USBWakeUp) Reserved			                  */
    TIM8_BRK_IRQn        = 62,			/*!< TIM8 Break Interrupt                                 */
    TIM8_UP_IRQn         = 63,			/*!< TIM8 Update Interrupt                                */
    TIM8_TRG_COM_IRQn    = 64,			/*!< TIM8 Trigger and Commutation Interrupt               */
    TIM8_CC_IRQn         = 65,			/*!< TIM8 Capture Compare Interrupt                       */
    ADC3_4_IRQn          = 66,			/*!< ADC3 and ADC4 global Interrupt                       */
    RESERVE48_IRQn       = 67,			/*!< RESERVE                                              */
										/*!< 68(for SDIO) Reserved			                      */
	TIM5_IRQn            = 69,			/*!< TIM5 global Interrupt                                */
    SPI3_I2S3_IRQn       = 70,			/*!< SPI3/I2S3 global Interrupt                           */
    UART4_IRQn           = 71,			/*!< UART4 global Interrupt                               */
    UART5_IRQn           = 72,			/*!< UART5 global Interrupt                               */
    TIM6_IRQn            = 73,			/*!< TIM6 global Interrupt                                */
    TIM7_IRQn            = 74,			/*!< TIM7 global Interrupt                                */
    DMA2_Channel1_IRQn   = 75,			/*!< DMA2 Channel 1 global Interrupt                      */
    DMA2_Channel2_IRQn   = 76,			/*!< DMA2 Channel 2 global Interrupt                      */
    DMA2_Channel3_IRQn   = 77,			/*!< DMA2 Channel 3 global Interrupt                      */
    DMA2_Channel4_IRQn   = 78,			/*!< DMA2 Channel 4 global Interrupt                      */
    DMA2_Channel5_IRQn   = 79,			/*!< DMA2 Channel 5 global Interrupt                      */
										/*!< 80(for ETH)/81(for ETH WakeUp) Reserved			  */
	CAN2_TX_IRQn         = 82,			/*!< CAN2 TX Interrupt                                    */
    CAN2_RX0_IRQn        = 83,			/*!< CAN2 RX0 Interrupt                                   */
    CAN2_RX1_IRQn        = 84,			/*!< CAN2 RX1 Interrupt                                   */
    CAN2_SCE_IRQn        = 85,			/*!< CAN2 SCE Interrupt                                   */
    QSPI_IRQn            = 86,			/*!< QSPI global Interrupt                                */
    DMA2_Channel6_IRQn   = 87,			/*!< DMA2 Channel 6 global Interrupt                      */
    DMA2_Channel7_IRQn   = 88,			/*!< DMA2 Channel 7 global Interrupt                      */
    I2C3_EV_IRQn         = 89,			/*!< I2C3 Event Interrupt                                 */
    I2C3_ER_IRQn         = 90,			/*!< I2C3 Error Interrupt                                 */
    I2C4_EV_IRQn         = 91,			/*!< I2C4 Event Interrupt                                 */
    I2C4_ER_IRQn         = 92,			/*!< I2C4 Error Interrupt                                 */
    UART6_IRQn           = 93,			/*!< UART6 global Interrupt                               */
    UART7_IRQn           = 94,			/*!< UART7 global Interrupt                               */
    DMA1_Channel8_IRQn   = 95,			/*!< DMA1 Channel 8 global Interrupt                      */
    DMA2_Channel8_IRQn   = 96,			/*!< DMA2 Channel 8 global Interrupt                      */
										/*!< 97(for DVP) Reserved	                              */
    SAC_IRQn             = 98,			/*!< SAC global Interrupt                                 */
    MMU_IRQn             = 99,          /*!< MMU global Interrupt                                 */
    TSC_IRQn             = 100,			/*!< TSC global Interrupt                                 */
    COMP_1_2_3_IRQn      = 101,			/*!< COMP1 & COMP2 & COMP3 global Interrupt               */
    COMP_4_5_6_IRQn      = 102,			/*!< COMP4 & COMP5 & COMP6 global Interrupt               */
    COMP7_IRQn           = 103,			/*!< COMP7 global Interrupt                               */
    R_SRAM_IRQn          = 104,			/*!< R-SRAM Error Interrupt                               */

    SOC_INT_MAX,                        /* Max SoC interrupt Number */
} IRQn_Type;

/**
  * @}
  */ /* End of group Interrupt_number_definition */

/* =========================================================================================================================== */
/* ================                                  Exception Code Definition                                ================ */
/* =========================================================================================================================== */

/** @addtogroup Exception_code_definition
  * @{
  */

typedef enum EXCn {
/* =======================================  Nuclei N/NX Specific Exception Code  ======================================== */
    InsUnalign_EXCn          =   0,               /*!<  Instruction address misaligned           */
    InsAccFault_EXCn         =   1,               /*!<  Instruction access fault                 */
    IlleIns_EXCn             =   2,               /*!<  Illegal instruction                      */
    Break_EXCn               =   3,               /*!<  Breakpoint                               */
    LdAddrUnalign_EXCn       =   4,               /*!<  Load address misaligned                  */
    LdFault_EXCn             =   5,               /*!<  Load access fault                        */
    StAddrUnalign_EXCn       =   6,               /*!<  Store or AMO address misaligned          */
    StAccessFault_EXCn       =   7,               /*!<  Store or AMO access fault                */
    UmodeEcall_EXCn          =   8,               /*!<  Environment call from User mode          */
    MmodeEcall_EXCn          =   11,              /*!<  Environment call from Machine mode       */
    NMI_EXCn                 =   0xfff,           /*!<  NMI interrupt                            */
} EXCn_Type;

/**
  * @}
  */ /* End of group Exception_code_definition */

/* =========================================================================================================================== */
/* ================                           Processor and Core Peripheral Section                           ================ */
/* =========================================================================================================================== */


/** @addtogroup Configuration_of_NMSIS
  * @{
  */

/* ===========================  Configuration of the Nuclei N/NX Processor and Core Peripherals  =========================== */

/* 		 define the correct core revision
 *       __NUCLEI_N_REV if your device is a Nuclei-N Class device
 *       __NUCLEI_NX_REV if your device is a Nuclei-NX Class device
 */
#define __NUCLEI_N_REV            0x0100                /*!< Core Revision rXpY, version X.Y, change N# to N for Nuclei N class cores, change N# to NX for Nuclei NX cores */

#define __ECLIC_PRESENT           1                     /*!< ECLIC present */
#define __ECLIC_BASEADDR          0xE0010000UL          /*!< ECLIC base address */
#define __ECLIC_INTCTLBITS        4                     /*!< CM32M4xxR uses 4 bits in the clicintctl registers. */
#define __ECLIC_INTNUM            105                   /*!< 105 interrupt number of ECLIC Unit */
#define __SYSTIMER_PRESENT        1                     /*!< System Timer present */
#define __SYSTIMER_BASEADDR       0xE0020000UL          /*!< SysTimer base address */
#define __FPU_PRESENT             1                     /*!< single floating point unit present */
#define __DSP_PRESENT             1                     /*!< DSP present */
#define __PMP_PRESENT             1                     /*!< PMP present */
#define __PMP_ENTRY_NUM           8                     /*!< 8 PMP entries */
#define __ICACHE_PRESENT          0                     /*!< I-Cache not present */
#define __DCACHE_PRESENT          0                     /*!< D-Cache not present */
#define __Vendor_SysTickConfig    0                     /*!< No different SysTick Config is used */
#define __sPMP_PRESENT            1                     /*!< sPMP present */
#define __sPMP_ENTRY_NUM          8                     /*!< 8 sPMP entries */
/**
  * @}
  */ /* End of group Configuration_of_NMSIS */


#include "nmsis_core.h"
#include "system_cm32m4xxr.h"	/*!< CM32M4xxR System Initialization file */
#include <stdint.h>
#include <stdbool.h>

/* ========================================  Start of section using anonymous unions  ======================================== */
#if	defined (__GNUC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif


/* =========================================================================================================================== */
/* ================                            Device Specific Peripheral Section                             ================ */
/* =========================================================================================================================== */


/** @addtogroup Peripheral_registers_structures
  * @{
  */


/**
 * @brief Analog to Digital Converter
 */
 
typedef struct
{
    __IO uint32_t STS;		/*!< ADC status register,                           Address offset: 0x00 */
    __IO uint32_t CTRL1;	/*!< ADC control register 1,                        Address offset: 0x04 */
    __IO uint32_t CTRL2;	/*!< ADC control register 2,                        Address offset: 0x08 */
    __IO uint32_t SAMPT1;	/*!< ADC sample time register 1,                    Address offset: 0x0C */
    __IO uint32_t SAMPT2;	/*!< ADC sample time register 2,                    Address offset: 0x10 */
    __IO uint32_t JOFFSET1;	/*!< ADC injected channel data offset register 1,   Address offset: 0x14 */
    __IO uint32_t JOFFSET2;	/*!< ADC injected channel data offset register 2,   Address offset: 0x18 */
    __IO uint32_t JOFFSET3;	/*!< ADC injected channel data offset register 3,   Address offset: 0x1C */
    __IO uint32_t JOFFSET4;	/*!< ADC injected channel data offset register 4,   Address offset: 0x20 */
    __IO uint32_t WDHIGH;	/*!< ADC watchdog higher threshold register,        Address offset: 0x24 */
    __IO uint32_t WDLOW;	/*!< ADC watchdog lower threshold register,         Address offset: 0x28 */
    __IO uint32_t RSEQ1;	/*!< ADC regular sequence register 1,               Address offset: 0x2C */
    __IO uint32_t RSEQ2;	/*!< ADC regular sequence register 2,               Address offset: 0x30 */
    __IO uint32_t RSEQ3;	/*!< ADC regular sequence register 3,               Address offset: 0x34 */
    __IO uint32_t JSEQ;		/*!< ADC injected sequence register,                Address offset: 0x38 */
    __IO uint32_t JDAT1;	/*!< ADC injected data register 1,                  Address offset: 0x3C */
    __IO uint32_t JDAT2;	/*!< ADC injected data register 2,                  Address offset: 0x40 */
    __IO uint32_t JDAT3;	/*!< ADC injected data register 3,                  Address offset: 0x44 */
    __IO uint32_t JDAT4;	/*!< ADC injected data register 4,                  Address offset: 0x48 */
    __IO uint32_t DAT;		/*!< ADC regular data register,                     Address offset: 0x4C */
    __IO uint32_t DIFSEL;	/*!< ADC differential mode selection register,      Address offset: 0x50 */
    __IO uint32_t CALFACT;	/*!< ADC calibration factors register,              Address offset: 0x54 */
    __IO uint32_t CTRL3;	/*!< ADC control register 3,                        Address offset: 0x58 */
    __IO uint32_t SAMPT3;	/*!< ADC sample time register 3,                    Address offset: 0x5C */
} ADC_Module;

/**
 * @brief OPAMP
 */
 
typedef struct
{
    __IO uint32_t CS1;			/*!< OPAMP control and status register 1,	Address offset: 0x00 */
    __IO uint32_t RESERVED0[3];	/*!< Reserved, 0x04 - 0x0F 										 */
    __IO uint32_t CS2;			/*!< OPAMP control and status register 2,	Address offset: 0x10 */
    __IO uint32_t RESERVED1[3];	/*!< Reserved, 0x14 - 0x1F 										 */
    __IO uint32_t CS3;			/*!< OPAMP control and status register 3,	Address offset: 0x20 */
    __IO uint32_t RESERVED2[3];	/*!< Reserved, 0x24 - 0x2F 									     */
    __IO uint32_t CS4;			/*!< OPAMP control and status register 4,	Address offset: 0x30 */
    __IO uint32_t RESERVED3[3];	/*!< Reserved, 0x34 - 0x3F 										 */
    __IO uint32_t LOCK;			/*!< OPAMP lock register,					Address offset: 0x40 */
} OPAMP_Module;

/**
 * @brief COMP_Single
 */
 
typedef struct
{
    __IO uint32_t CTRL;		/*!< COMP control and status register 	*/
    __IO uint32_t FILC;		/*!< COMP filter control register 		*/
    __IO uint32_t FILP;		/*!< COMP filter prescaler register		*/
    __IO uint32_t RESERVED;	/*!< Reserved							*/
} COMP_SingleType;

/**
 * @brief COMP
 */
 
typedef struct
{
    __IO uint32_t   RESERVED0[4]; 	/*!< Reserved, 0x00 - 0x0F 												*/
    COMP_SingleType Cmp[7];			/*!< COMP single registers, 				Address offset: 0x10 - 0x7C */
    __IO uint32_t   WINMODE;		/*!< COMP window mode register, 			Address offset: 0x80 		*/
    __IO uint32_t   LOCK;			/*!< COMP lock register, 					Address offset: 0x84 		*/
    __IO uint32_t   RESERVED1;		/*!< Reserved,						 		Address offset: 0x88 		*/
    __IO uint32_t   INTEN;			/*!< COMP interrupt enable register, 		Address offset: 0x8C 		*/
    __IO uint32_t   INTSTS;			/*!< COMP interrupt status register, 		Address offset: 0x90 		*/
    __IO uint32_t   VREFSCL;		/*!< COMP voltage reference register, 		Address offset: 0x94 		*/
} COMP_Module;


/**
 * @brief Backup Registers
 */
 
typedef struct
{
         uint32_t RESERVED0;	/*!< Reserved,								Address offset: 0x00 */
    __IO uint16_t DAT1;			/*!< BKP data register 1,					Address offset: 0x04 */
         uint16_t RESERVED1;
    __IO uint16_t DAT2;			/*!< BKP data register 2,					Address offset: 0x08 */
         uint16_t RESERVED2;
    __IO uint16_t DAT3;			/*!< BKP data register 3,					Address offset: 0x0C */
         uint16_t RESERVED3;
    __IO uint16_t DAT4;			/*!< BKP data register 4,					Address offset: 0x10 */
         uint16_t RESERVED4;
    __IO uint16_t DAT5;			/*!< BKP data register 5,					Address offset: 0x14 */
         uint16_t RESERVED5;
    __IO uint16_t DAT6;			/*!< BKP data register 6,					Address offset: 0x18 */
         uint16_t RESERVED6;
    __IO uint16_t DAT7;			/*!< BKP data register 7,					Address offset: 0x1C */
         uint16_t RESERVED7;
    __IO uint16_t DAT8;			/*!< BKP data register 8,					Address offset: 0x20 */
         uint16_t RESERVED8;
    __IO uint16_t DAT9;			/*!< BKP data register 9,					Address offset: 0x24 */
         uint16_t RESERVED9;
    __IO uint16_t DAT10;		/*!< BKP data register 10,					Address offset: 0x28 */
         uint16_t RESERVED10;
    __IO uint16_t RESERVED11;	/*!< Reserved, 0x2C												 */
         uint16_t RESERVED12;
    __IO uint16_t CTRL;			/*!< BKP control register,					Address offset: 0x30 */
         uint16_t RESERVED13;
    __IO uint16_t CSTS;			/*!< BKP control and status register,		Address offset: 0x34 */
         uint16_t RESERVED14[5];
    __IO uint16_t DAT11;		/*!< BKP data register 11,					Address offset: 0x40 */
         uint16_t RESERVED15;
    __IO uint16_t DAT12;		/*!< BKP data register 12,					Address offset: 0x44 */
         uint16_t RESERVED16;
    __IO uint16_t DAT13;		/*!< BKP data register 13,					Address offset: 0x48 */
         uint16_t RESERVED17;
    __IO uint16_t DAT14;		/*!< BKP data register 14,					Address offset: 0x4C */
         uint16_t RESERVED18;
    __IO uint16_t DAT15;		/*!< BKP data register 15,					Address offset: 0x50 */
         uint16_t RESERVED19;
    __IO uint16_t DAT16;		/*!< BKP data register 16,					Address offset: 0x54 */
         uint16_t RESERVED20;
    __IO uint16_t DAT17;		/*!< BKP data register 17,					Address offset: 0x58 */
         uint16_t RESERVED21;
    __IO uint16_t DAT18;		/*!< BKP data register 18,					Address offset: 0x5C */
         uint16_t RESERVED22;
    __IO uint16_t DAT19;		/*!< BKP data register 19,					Address offset: 0x60 */
         uint16_t RESERVED23;
    __IO uint16_t DAT20;		/*!< BKP data register 20,					Address offset: 0x64 */
         uint16_t RESERVED24;
    __IO uint16_t DAT21;		/*!< BKP data register 21,					Address offset: 0x68 */
         uint16_t RESERVED25;
    __IO uint16_t DAT22;		/*!< BKP data register 22,					Address offset: 0x6C */
         uint16_t RESERVED26;
    __IO uint16_t DAT23;		/*!< BKP data register 23,					Address offset: 0x70 */
         uint16_t RESERVED27;
    __IO uint16_t DAT24;		/*!< BKP data register 24,					Address offset: 0x74 */
         uint16_t RESERVED28;
    __IO uint16_t DAT25;		/*!< BKP data register 25,					Address offset: 0x78 */
         uint16_t RESERVED29;
    __IO uint16_t DAT26;		/*!< BKP data register 26,					Address offset: 0x7C */
         uint16_t RESERVED30;
    __IO uint16_t DAT27;		/*!< BKP data register 27,					Address offset: 0x80 */
         uint16_t RESERVED31;
    __IO uint16_t DAT28;		/*!< BKP data register 28,					Address offset: 0x84 */
         uint16_t RESERVED32;
    __IO uint16_t DAT29;		/*!< BKP data register 29,					Address offset: 0x88 */
         uint16_t RESERVED33;
    __IO uint16_t DAT30;		/*!< BKP data register 30,					Address offset: 0x8C */
         uint16_t RESERVED34;
    __IO uint16_t DAT31;		/*!< BKP data register 31,					Address offset: 0x90 */
         uint16_t RESERVED35;
    __IO uint16_t DAT32;		/*!< BKP data register 32,					Address offset: 0x94 */
         uint16_t RESERVED36;
    __IO uint16_t DAT33;		/*!< BKP data register 33,					Address offset: 0x98 */
         uint16_t RESERVED37;
    __IO uint16_t DAT34;		/*!< BKP data register 34,					Address offset: 0x9C */
         uint16_t RESERVED38;
    __IO uint16_t DAT35;		/*!< BKP data register 35,					Address offset: 0xA0 */
         uint16_t RESERVED39;
    __IO uint16_t DAT36;		/*!< BKP data register 36,					Address offset: 0xA4 */
         uint16_t RESERVED40;
    __IO uint16_t DAT37;		/*!< BKP data register 37,					Address offset: 0xA8 */
         uint16_t RESERVED41;
    __IO uint16_t DAT38;		/*!< BKP data register 38,					Address offset: 0xAC */
         uint16_t RESERVED42;
    __IO uint16_t DAT39;		/*!< BKP data register 39,					Address offset: 0xB0 */
         uint16_t RESERVED43;
    __IO uint16_t DAT40;		/*!< BKP data register 40,					Address offset: 0xB4 */
         uint16_t RESERVED44;
    __IO uint16_t DAT41;		/*!< BKP data register 41,					Address offset: 0xB8 */
         uint16_t RESERVED45;
    __IO uint16_t DAT42;		/*!< BKP data register 42,					Address offset: 0xBC */
         uint16_t RESERVED46;
} BKP_Module;

/**
 * @brief Controller Area Network TxMailBox
 */
 
typedef struct
{
    __IO uint32_t TIR;	/*!< CAN TX mailbox identifier register							*/
    __IO uint32_t TDTR;	/*!< CAN mailbox data length control and time stamp register	*/
    __IO uint32_t TDLR;	/*!< CAN mailbox data low register								*/
    __IO uint32_t TDHR;	/*!< CAN mailbox data high register								*/
} CAN_TxMailBox_Param;

/**
 * @brief Controller Area Network FIFOMailBox
 */
 
typedef struct
{
    __IO uint32_t RIR;	/*!< CAN receive FIFO mailbox identifier register							*/
    __IO uint32_t RDTR;	/*!< CAN receive FIFO mailbox data length control and time stamp register	*/
    __IO uint32_t RDLR;	/*!< CAN receive FIFO mailbox data low register								*/
    __IO uint32_t RDHR;	/*!< CAN receive FIFO mailbox data high register							*/
} CAN_FIFOMailBox_Param;

/**
 * @brief Controller Area Network FilterRegister
 */
 
typedef struct
{
    __IO uint32_t FR1;	/*!< CAN Filter bank register 1 */
    __IO uint32_t FR2;	/*!< CAN Filter bank register 2 */
} CAN_FilterRegister_Param;

/**
 * @brief Controller Area Network
 */
 
typedef struct
{
    __IO uint32_t                 MCR;					/*!< CAN master control register,         Address offset: 0x00 			*/
    __IO uint32_t                 MSR;					/*!< CAN master status register,          Address offset: 0x04 			*/
    __IO uint32_t                 TSR;					/*!< CAN transmit status register,        Address offset: 0x08 			*/
    __IO uint32_t                 RF0R;					/*!< CAN receive FIFO 0 register,         Address offset: 0x0C 			*/
    __IO uint32_t                 RF1R;					/*!< CAN receive FIFO 1 register,         Address offset: 0x10 			*/
    __IO uint32_t                 IER;					/*!< CAN interrupt enable register,       Address offset: 0x14 			*/
    __IO uint32_t                 ESR;					/*!< CAN error status register,           Address offset: 0x18 			*/
    __IO uint32_t                 BTR;					/*!< CAN bit timing register,             Address offset: 0x1C 			*/
         uint32_t                 RESERVED0[88];		/*!< Reserved, 0x020 - 0x17F 											*/
         CAN_TxMailBox_Param      sTxMailBox[3];		/*!< CAN Tx MailBox,                      Address offset: 0x180 - 0x1AC */
         CAN_FIFOMailBox_Param    sFIFOMailBox[2];		/*!< CAN FIFO MailBox,                    Address offset: 0x1B0 - 0x1CC */
         uint32_t                 RESERVED1[12];		/*!< Reserved, 0x1D0 - 0x1FF 											*/
    __IO uint32_t                 FMR;					/*!< CAN filter master register,          Address offset: 0x200 		*/
    __IO uint32_t                 FM1R;					/*!< CAN filter mode register,            Address offset: 0x204 		*/
         uint32_t                 RESERVED2;			/*!< Reserved, 0x208 													*/
    __IO uint32_t                 FS1R;					/*!< CAN filter scale register,           Address offset: 0x20C 		*/
         uint32_t                 RESERVED3;			/*!< Reserved, 0x210 													*/
    __IO uint32_t                 FFA1R;				/*!< CAN filter FIFO assignment register, Address offset: 0x214 		*/
         uint32_t                 RESERVED4;			/*!< Reserved, 0x218 													*/
    __IO uint32_t                 FA1R;					/*!< CAN filter activation register,      Address offset: 0x21C 		*/
         uint32_t                 RESERVED5[8];			/*!< Reserved, 0x220 - 0x23F 											*/
         CAN_FilterRegister_Param sFilterRegister[14];	/*!< CAN Filter Register,                 Address offset: 0x240 - 0x2AC */
} CAN_Module;

/**
 * @brief CRC calculation unit
 */
 
typedef struct
{
    __IO uint32_t CRC32DAT;  /*!< CRC32 data register,             Address offset: 0x00 */
    __IO uint8_t  CRC32IDAT; /*!< CRC32 independent data register, Address offset: 0x04 */
         uint8_t  RESERVED0; /*!< Reserved, 0x05									    */
         uint16_t RESERVED1; /*!< Reserved, 0x06									    */
    __IO uint32_t CRC32CTRL; /*!< CRC32 control register,          Address offset: 0x08 */
    __IO uint32_t CRC16CTRL; /*!< CRC16 control register,          Address offset: 0x0C */
    __IO uint8_t  CRC16DAT;  /*!< CRC16 data register,             Address offset: 0x10 */
         uint8_t  RESERVED2; /*!< Reserved, 0x11									    */
         uint16_t RESERVED3; /*!< Reserved, 0x12									    */
    __IO uint16_t CRC16D;    /*!< CRC16 result register,           Address offset: 0x14 */
         uint16_t RESERVED4; /*!< Reserved, 0x16									    */
    __IO uint8_t  LRC;       /*!< LRC data register,               Address offset: 0x18 */
         uint8_t  RESERVED5; /*!< Reserved, 0x19									    */
         uint16_t RESERVED6; /*!< Reserved, 0x1A									    */
} CRC_Module;

/**
 * @brief Digital to Analog Converter
 */
 
typedef struct
{
    __IO uint32_t CTRL;		/*!< DAC control register,                                    Address offset: 0x00 */
    __IO uint32_t SOTTR;	/*!< DAC software trigger register,                           Address offset: 0x04 */
    __IO uint32_t DR12CH1;	/*!< DAC channel1 12-bit right-aligned data holding register, Address offset: 0x08 */
    __IO uint32_t DL12CH1;	/*!< DAC channel1 12-bit left aligned data holding register,  Address offset: 0x0C */
    __IO uint32_t DR8CH1;	/*!< DAC channel1 8-bit right aligned data holding register,  Address offset: 0x10 */
    __IO uint32_t DR12CH2;	/*!< DAC channel2 12-bit right aligned data holding register, Address offset: 0x14 */
    __IO uint32_t DL12CH2;	/*!< DAC channel2 12-bit left aligned data holding register,  Address offset: 0x18 */
    __IO uint32_t DR8CH2;	/*!< DAC channel2 8-bit right-aligned data holding register,  Address offset: 0x1C */
    __IO uint32_t DR12DCH;	/*!< Dual DAC 12-bit right-aligned data holding register,     Address offset: 0x20 */
    __IO uint32_t DL12DCH;	/*!< DUAL DAC 12-bit left aligned data holding register,      Address offset: 0x24 */
    __IO uint32_t DR8DCH;	/*!< DUAL DAC 8-bit right aligned data holding register,      Address offset: 0x28 */
    __IO uint32_t DATO1;	/*!< DAC channel1 data output register,                       Address offset: 0x2C */
    __IO uint32_t DATO2;	/*!< DAC channel2 data output register,                       Address offset: 0x30 */
} DAC_Module;

/**
 * @brief Debug MCU
 */
 
typedef struct
{
    __IO uint32_t ID;	/*!< Debug MCU device ID code,   Address offset: 0x00 */
    __IO uint32_t CTRL;	/*!< Debug MCU control register, Address offset: 0x04 */
} DBG_Module;

/**
 * @brief DMA Controller
 */
 
typedef struct
{
    __IO uint32_t CHCFG; /*!< DMA channel x configuration register      */
    __IO uint32_t TXNUM; /*!< DMA channel x number of data register     */
    __IO uint32_t PADDR; /*!< DMA channel x peripheral address register */
    __IO uint32_t MADDR; /*!< DMA channel x memory address register     */
    __IO uint32_t CHSEL; /*!< DMA channel selection register            */
} DMA_ChannelType;

typedef struct
{
    __IO uint32_t        INTSTS;			/*!< DMA interrupt status register,      Address offset: 0x00        */
    __IO uint32_t        INTCLR;			/*!< DMA interrupt flag clear register,  Address offset: 0x04        */
    __IO DMA_ChannelType DMA_Channel[8];	/*!< DMA channel,  						 Address offset: 0x08 - 0xA4 */
    __IO uint32_t        CHMAPEN;			/*!< DMA channel MAP enable register,    Address offset: 0xA8        */
} DMA_Module;

/**
 * @brief External Interrupt/Event Controller
 */
 
typedef struct
{
    __IO uint32_t IMASK;	/*!< EXTI interrupt mask register,            			Address offset: 0x00 */
    __IO uint32_t EMASK;	/*!< EXTI event mask register,                			Address offset: 0x04 */
    __IO uint32_t RT_CFG;	/*!< EXTI rising trigger selection register,  			Address offset: 0x08 */
    __IO uint32_t FT_CFG;	/*!< EXTI falling trigger selection register, 			Address offset: 0x0C */
    __IO uint32_t SWIE;		/*!< EXTI software interrupt event register,  			Address offset: 0x10 */
    __IO uint32_t PEND;		/*!< EXTI pending register,                   			Address offset: 0x14 */
    __IO uint32_t TSSEL;	/*!< EXTI time stamp trigger source selection register, Address offset: 0x18 */
} EXTI_Module;

/**
 * @brief FLASH Registers
 */
 
typedef struct
{
    __IO uint32_t AC;			/*!< FLASH access control register,   		Address offset: 0x00 */
    __IO uint32_t KEY;			/*!< FLASH key register,              		Address offset: 0x04 */
    __IO uint32_t OPTKEY;		/*!< FLASH option key register,       		Address offset: 0x08 */
    __IO uint32_t STS;			/*!< FLASH status register,           		Address offset: 0x0C */
    __IO uint32_t CTRL;			/*!< FLASH control register,          		Address offset: 0x10 */
    __IO uint32_t ADD;			/*!< FLASH address register,          		Address offset: 0x14 */
    __IO uint32_t RESERVED0;	/*!< Reserved, 0x18										   		 */
    __IO uint32_t OB;			/*!< FLASH option byte register,      		Address offset: 0x1C */
    __IO uint32_t WRP;			/*!< FLASH write protection register, 		Address offset: 0x20 */
    __IO uint32_t ECC;			/*!< FLASH ECC result register,       		Address offset: 0x24 */
    __IO uint32_t RESERVED1;	/*!< Reserved, 0x28 											 */
    __IO uint32_t RESERVED2;	/*!< Reserved, 0x2C 											 */
    __IO uint32_t CAH;			/*!< FLASH CAH register,           		Address offset: 0x30 */
} FLASH_Module;

/**
 * @brief Option Bytes Registers
 */
 
typedef struct
{
    __IO uint32_t USER_RDP;		/*!< USER/Read protection level 1 option byte 	*/
    __IO uint32_t Data1_Data0;	/*!< User data storage option byte 				*/
    __IO uint32_t WRP1_WRP0;	/*!< Flash memory write protection option bytes */
    __IO uint32_t WRP3_WRP2;	/*!< Flash memory write protection option bytes */
    __IO uint32_t RDP2;			/*!< Read protection level 2 option byte 		*/
} OPB_Module;

/**
 * @brief General Purpose I/O
 */
 
typedef struct
{
    __IO uint32_t PL_CFG;		/*!< GPIO port lower configuration register,            Address offset: 0x00 */
    __IO uint32_t PH_CFG;		/*!< GPIO port higher configuration register,           Address offset: 0x04 */
    __IO uint32_t PID;			/*!< GPIO port input data register,         			Address offset: 0x08 */
    __IO uint32_t POD;			/*!< GPIO port output data register,					Address offset: 0x0C */
    __IO uint32_t PBSC;			/*!< GPIO port bit set/clear register,     				Address offset: 0x10 */
    __IO uint32_t PBC;			/*!< GPIO port bit clear register,      				Address offset: 0x14 */
    __IO uint32_t PLOCK_CFG;	/*!< GPIO port configuration lock register, 			Address offset: 0x18 */
         uint32_t RESERVED0;	/*!< Reserved, 0x1C */
    __IO uint32_t DS_CFG;		/*!< GPIO port drive capability configuration register, Address offset: 0x20 */
    __IO uint32_t SR_CFG;		/*!< GPIO port flip rate configuration register, 	    Address offset: 0x24 */
} GPIO_Module;

/**
 * @brief Alternate Function I/O
 */
 
typedef struct
{
    __IO uint32_t ECTRL;		/*!< AFIO event control register,            			Address offset: 0x00 		*/
    __IO uint32_t RMP_CFG;		/*!< AFIO remap configuration register,            		Address offset: 0x04 		*/
    __IO uint32_t EXTI_CFG[4];	/*!< AFIO external interrupt configuration registers,	Address offset: 0x08 - 0x14 */
         uint32_t RESERVED0;	/*!< Reserved, 0x18 */
    __IO uint32_t RESERVED1;	/*!< AFIO remap configuration register 2,            	Address offset: 0x1C 		*/
    __IO uint32_t RMP_CFG3;		/*!< AFIO remap configuration register 3,            	Address offset: 0x20 		*/
    __IO uint32_t RMP_CFG4;		/*!< AFIO remap configuration register 4,            	Address offset: 0x24 		*/
    __IO uint32_t RMP_CFG5;		/*!< AFIO remap configuration register 5,            	Address offset: 0x28 		*/
} AFIO_Module;

/**
 * @brief Inter Integrated Circuit Interface
 */

typedef struct
{
    __IO uint16_t CTRL1;		/*!< I2C Control register 1,     Address offset: 0x00 */
         uint16_t RESERVED0;
    __IO uint16_t CTRL2;		/*!< I2C Control register 2,     Address offset: 0x04 */
         uint16_t RESERVED1;
    __IO uint16_t OADDR1;		/*!< I2C Own address register 1, Address offset: 0x08 */
         uint16_t RESERVED2;
    __IO uint16_t OADDR2;		/*!< I2C Own address register 2, Address offset: 0x0C */
         uint16_t RESERVED3;
    __IO uint16_t DAT;			/*!< I2C Data register,          Address offset: 0x10 */
         uint16_t RESERVED4;
    __IO uint16_t STS1;			/*!< I2C Status register 1,      Address offset: 0x14 */
         uint16_t RESERVED5;
    __IO uint16_t STS2;			/*!< I2C Status register 2,      Address offset: 0x18 */
         uint16_t RESERVED6;
    __IO uint16_t CLKCTRL;		/*!< I2C Clock control register, Address offset: 0x1C */
         uint16_t RESERVED7;
    __IO uint16_t TMRISE;		/*!< I2C TRISE register,         Address offset: 0x20 */
         uint16_t RESERVED8;
} I2C_Module;

/**
 * @brief Independent WATCHDOG
 */

typedef struct
{
    __IO uint32_t KEY;		/*!< IWDG key register,       Address offset: 0x00 */
    __IO uint32_t PREDIV;	/*!< IWDG prescaler register, Address offset: 0x04 */
    __IO uint32_t RELV;		/*!< IWDG reload register,    Address offset: 0x08 */
    __IO uint32_t STS;		/*!< IWDG status register,    Address offset: 0x0C */
} IWDG_Module;

/**
 * @brief Power Control
 */

typedef struct
{
    __IO uint32_t CTRL;		/*!< PWR power control register,        	Address offset: 0x00 */
    __IO uint32_t CTRLSTS;	/*!< PWR power control and status register, Address offset: 0x04 */
    __IO uint32_t CTRL2;	/*!< PWR power control register 2,        	Address offset: 0x08 */
    __IO uint32_t CTRL3;	/*!< PWR power control register 3,        	Address offset: 0x0C */
} PWR_Module;

/**
 * @brief Reset and Clock Control
 */

typedef struct
{								/*!< RCC Module,                              	Base Address: 0x40021000 */
    __IO uint32_t CTRL;			/*!< RCC clock control register,					Address offset: 0x00 */
    __IO uint32_t CFG;			/*!< RCC clock configuration register,				Address offset: 0x04 */
    __IO uint32_t CLKINT;		/*!< RCC clock interrupt register,					Address offset: 0x08 */
    __IO uint32_t APB2PRST;		/*!< RCC APB2 peripheral reset register,			Address offset: 0x0C */
    __IO uint32_t APB1PRST;		/*!< RCC APB1 peripheral reset register,			Address offset: 0x10 */
    __IO uint32_t AHBPCLKEN;	/*!< RCC AHB peripheral clock enable register,		Address offset: 0x14 */
    __IO uint32_t APB2PCLKEN;	/*!< RCC APB2 peripheral clock enable register,		Address offset: 0x18 */
    __IO uint32_t APB1PCLKEN;	/*!< RCC APB1 peripheral clock enable register,		Address offset: 0x1C */
    __IO uint32_t BDCTRL;		/*!< RCC backup domain control register,			Address offset: 0x20 */
    __IO uint32_t CTRLSTS;		/*!< RCC clock control and status register,			Address offset: 0x24 */
    __IO uint32_t AHBPRST;		/*!< RCC AHB peripheral reset register,				Address offset: 0x28 */
    __IO uint32_t CFG2;			/*!< RCC clock configuration register 2,			Address offset: 0x2C */
    __IO uint32_t CFG3;			/*!< RCC clock configuration register 3,			Address offset: 0x30 */
} RCC_Module;

/**
 * @brief Real-Time Clock
 */

typedef struct
{
    __IO uint32_t TSH;         /*!< RTC time register,							Address offset: 0x00 */
    __IO uint32_t DATE;        /*!< RTC date register,							Address offset: 0x04 */
    __IO uint32_t CTRL;        /*!< RTC control register,						Address offset: 0x08 */
    __IO uint32_t INITSTS;     /*!< RTC initialization and status register,		Address offset: 0x0C */
    __IO uint32_t PRE;         /*!< RTC prescaler register,						Address offset: 0x10 */
    __IO uint32_t WKUPT;       /*!< RTC wakeup timer register,					Address offset: 0x14 */
         uint32_t RESERVED0;   /*!< Reserved, 0x18 													 */
    __IO uint32_t ALARMA;      /*!< RTC alarm A register,						Address offset: 0x1C */
    __IO uint32_t ALARMB;      /*!< RTC alarm B register,						Address offset: 0x20 */
    __IO uint32_t WRP;         /*!< RTC write protection register,				Address offset: 0x24 */
    __IO uint32_t SUBS;        /*!< RTC sub second register,					Address offset: 0x28 */
    __IO uint32_t SCTRL;       /*!< RTC shift control register,					Address offset: 0x2C */
    __IO uint32_t TST;         /*!< RTC time stamp time register,				Address offset: 0x30 */
    __IO uint32_t TSD;         /*!< RTC time stamp date register,				Address offset: 0x34 */
    __IO uint32_t TSSS;        /*!< RTC time stamp sub second register,			Address offset: 0x38 */
    __IO uint32_t CALIB;       /*!< RTC calibration register,					Address offset: 0x3C */
         uint32_t RESERVED1;   /*!< Reserved, 0x40												     */
    __IO uint32_t ALRMASS;     /*!< RTC alarm A sub second register,			Address offset: 0x44 */
    __IO uint32_t ALRMBSS;     /*!< RTC alarm B sub second register,			Address offset: 0x48 */
    __IO uint32_t OPT;         /*!< RTC option register,						Address offset: 0x4C */
         uint32_t RESERVED2;   /*!< Reserved, 0x50 													 */
         uint32_t RESERVED3;   /*!< Reserved, 0x54 													 */
         uint32_t RESERVED4;   /*!< Reserved, 0x58 													 */
         uint32_t RESERVED5;   /*!< Reserved, 0x5C                                                   */
         uint32_t RESERVED6;   /*!< Reserved, 0x60                                                   */
    __IO uint32_t TSCWKUPCTRL; /*!< RTC TSC wakeup control register				Address offset: 0x64 */
    __IO uint32_t TSCWKUPCNT;  /*!< RTC TSC wakeup counter register,			Address offset: 0x68 */
} RTC_Module;


/**
 * @brief Serial Peripheral Interface
 */

typedef struct
{
    __IO uint16_t CTRL1;		/*!< SPI control register 1 (not used in I2S mode),      Address offset: 0x00 */
         uint16_t RESERVED0;
    __IO uint16_t CTRL2;		/*!< SPI control register 2,                             Address offset: 0x04 */
         uint16_t RESERVED1;
    __IO uint16_t STS;			/*!< SPI status register,                                Address offset: 0x08 */
         uint16_t RESERVED2;
    __IO uint16_t DAT;			/*!< SPI data register,                                  Address offset: 0x0C */
         uint16_t RESERVED3;
    __IO uint16_t CRCPOLY;		/*!< SPI CRC polynomial register (not used in I2S mode), Address offset: 0x10 */
         uint16_t RESERVED4;
    __IO uint16_t CRCRDAT;		/*!< SPI RX CRC register (not used in I2S mode),         Address offset: 0x14 */
         uint16_t RESERVED5;
    __IO uint16_t CRCTDAT;		/*!< SPI TX CRC register (not used in I2S mode),         Address offset: 0x18 */
         uint16_t RESERVED6;
    __IO uint16_t I2SCFG;		/*!< SPI_I2S configuration register,                     Address offset: 0x1C */
         uint16_t RESERVED7;
    __IO uint16_t I2SPREDIV;	/*!< SPI_I2S prescaler register,                         Address offset: 0x20 */
         uint16_t RESERVED8;
} SPI_Module;

/**
 * @brief TIM
 */

typedef struct
{
    __IO uint32_t CTRL1;		/*!< TIM control register 1,				Address offset: 0x00 */
    __IO uint32_t CTRL2;		/*!< TIM control register 2,				Address offset: 0x04 */
    __IO uint16_t SMCTRL;		/*!< TIM slave mode control register,		Address offset: 0x08 */
         uint16_t RESERVED1;
    __IO uint16_t DINTEN;		/*!< TIM DMA/interrupt enable register,		Address offset: 0x0C */
         uint16_t RESERVED2;
    __IO uint32_t STS;			/*!< TIM status register,					Address offset: 0x10 */
    __IO uint16_t EVTGEN;		/*!< TIM event generation register,			Address offset: 0x14 */
         uint16_t RESERVED3;
    __IO uint16_t CCMOD1;		/*!< TIM capture/compare mode register 1,	Address offset: 0x18 */
         uint16_t RESERVED4;
    __IO uint16_t CCMOD2;		/*!< TIM capture/compare mode register 2,	Address offset: 0x1C */
         uint16_t RESERVED5;
    __IO uint32_t CCEN;			/*!< TIM capture/compare enable register,	Address offset: 0x20 */
    __IO uint16_t CNT;			/*!< TIM counter register,					Address offset: 0x24 */
         uint16_t RESERVED6;
    __IO uint16_t PSC;			/*!< TIM prescaler register,				Address offset: 0x28 */
         uint16_t RESERVED7;
    __IO uint16_t AR;			/*!< TIM auto-reload register,				Address offset: 0x2C */
         uint16_t RESERVED8;
    __IO uint16_t REPCNT;		/*!< TIM repetition counter register,		Address offset: 0x30 */
         uint16_t RESERVED9;
    __IO uint16_t CCDAT1;		/*!< TIM capture/compare register 1,		Address offset: 0x34 */
         uint16_t RESERVED10;
    __IO uint16_t CCDAT2;		/*!< TIM capture/compare register 2,		Address offset: 0x38 */
         uint16_t RESERVED11;
    __IO uint16_t CCDAT3;		/*!< TIM capture/compare register 3,		Address offset: 0x3C */
         uint16_t RESERVED12;
    __IO uint16_t CCDAT4;		/*!< TIM capture/compare register 4,		Address offset: 0x40 */
         uint16_t RESERVED13;
    __IO uint16_t BKDT;			/*!< TIM break and dead-time register,		Address offset: 0x44 */
         uint16_t RESERVED14;
    __IO uint16_t DCTRL;		/*!< TIM DMA control register,				Address offset: 0x48 */
         uint16_t RESERVED15;
    __IO uint16_t DADDR;		/*!< TIM DMA address for burst transfer,	Address offset: 0x4C */
         uint16_t RESERVED16;
         uint32_t RESERVED17;
    __IO uint16_t CCMOD3;		/*!< TIM capture/compare mode register 3,	Address offset: 0x50 */
         uint16_t RESERVED18;
    __IO uint16_t CCDAT5;		/*!< TIM capture/compare register 5,		Address offset: 0x54 */
         uint16_t RESERVED19;
    __IO uint16_t CCDAT6;		/*!< TIM capture/compare register 6,		Address offset: 0x58 */
         uint16_t RESERVED20;
} TIM_Module;

/**
 * @brief Universal Synchronous Asynchronous Receiver Transmitter
 */

typedef struct
{
    __IO uint16_t STS;			/*!< USART status register,						Address offset: 0x00 */
         uint16_t RESERVED0;
    __IO uint16_t DAT;			/*!< USART data register,						Address offset: 0x04 */
         uint16_t RESERVED1;
    __IO uint16_t BRCF;			/*!< USART baud rate configuration register,	Address offset: 0x08 */
         uint16_t RESERVED2;
    __IO uint16_t CTRL1;		/*!< USART control register 1,					Address offset: 0x0C */
         uint16_t RESERVED3;
    __IO uint16_t CTRL2;		/*!< USART control register 2,					Address offset: 0x10 */
         uint16_t RESERVED4;
    __IO uint16_t CTRL3;		/*!< USART control register 3,					Address offset: 0x14 */
         uint16_t RESERVED5;
    __IO uint16_t GTP;			/*!< USART guard time and prescaler register,	Address offset: 0x18 */
         uint16_t RESERVED6;
} USART_Module;

/**
 * @brief Window WATCHDOG
 */

typedef struct
{
    __IO uint32_t CTRL;	/*!< WWDG control register,       Address offset: 0x00 */
    __IO uint32_t CFG;	/*!< WWDG configuration register, Address offset: 0x04 */
    __IO uint32_t STS;	/*!< WWDG status register,        Address offset: 0x08 */
} WWDG_Module;

/**
 * @brief QSPI
 */
 
typedef struct
{
    __IO uint32_t CTRL0;			/*!< QSPI control register 1,									Address offset: 0x00  */
    __IO uint32_t CTRL1;			/*!< QSPI control register 2,									Address offset: 0x04  */
    __IO uint32_t EN;				/*!< QSPI enable register,										Address offset: 0x08  */
    __IO uint32_t MW_CTRL;			/*!< QSPI Microwire control register,							Address offset: 0x0C  */
    __IO uint32_t SLAVE_EN;			/*!< QSPI slave device enable register,							Address offset: 0x10  */
    __IO uint32_t BAUD;				/*!< QSPI baud rate selection register,							Address offset: 0x14  */
    __IO uint32_t TXFT;				/*!< QSPI receive FIFO threshold register,						Address offset: 0x18  */
    __IO uint32_t RXFT;				/*!< QSPI transmit FIFO threshold register,						Address offset: 0x1C  */
    __IO uint32_t TXFN;				/*!< QSPI number of transmit FIFO data register,				Address offset: 0x20  */
    __IO uint32_t RXFN;				/*!< QSPI number of receive FIFO register,						Address offset: 0x24  */
    __IO uint32_t STS;				/*!< QSPI status register,										Address offset: 0x28  */
    __IO uint32_t IMASK;			/*!< QSPI interrupt mask register,								Address offset: 0x2C  */
    __IO uint32_t ISTS;				/*!< QSPI interrupt status register,							Address offset: 0x30  */
    __IO uint32_t RISTS;			/*!< QSPI raw interrupt status register,						Address offset: 0x34  */
    __IO uint32_t TXFOI_CLR;		/*!< QSPI transmit FIFO overflow interrupt clear register,		Address offset: 0x38  */
    __IO uint32_t RXFOI_CLR;		/*!< QSPI receive FIFO overflow interrupt clear register,		Address offset: 0x3C  */
    __IO uint32_t RXFUI_CLR;		/*!< QSPI receive FIFO underflow interrupt clear register,		Address offset: 0x40  */
    __IO uint32_t MMCI_CLR;			/*!< QSPI Multi-Master contention interrupt clear register,		Address offset: 0x44  */
    __IO uint32_t ICLR;				/*!< QSPI interrupt clear register,								Address offset: 0x48  */
    __IO uint32_t DMA_CTRL;			/*!< QSPI DMA control register,									Address offset: 0x4C  */
    __IO uint32_t DMATDL_CTRL;		/*!< QSPI DMA transmit data level control register,				Address offset: 0x50  */
    __IO uint32_t DMARDL_CTRL;		/*!< QSPI DMA receive data level control register,				Address offset: 0x54  */
    __IO uint32_t IDCODE;			/*!< QSPI identification code register,							Address offset: 0x58  */
    __IO uint32_t RESERVED0;		/*!< Reserved, 0x5C																      */
    __IO uint32_t DAT0;				/*!< QSPI data register 0,										Address offset: 0x60  */
    __IO uint32_t DAT1;				/*!< QSPI data register 1,										Address offset: 0x64  */
    __IO uint32_t DAT2;				/*!< QSPI data register 2,										Address offset: 0x68  */
    __IO uint32_t DAT3;				/*!< QSPI data register 3,										Address offset: 0x6C  */
    __IO uint32_t DAT4;				/*!< QSPI data register 4,										Address offset: 0x70  */
    __IO uint32_t DAT5;				/*!< QSPI data register 5,										Address offset: 0x74  */
    __IO uint32_t DAT6;				/*!< QSPI data register 6,										Address offset: 0x78  */
    __IO uint32_t DAT7;				/*!< QSPI data register 7,										Address offset: 0x7C  */
    __IO uint32_t DAT8;				/*!< QSPI data register 8,										Address offset: 0x80  */
    __IO uint32_t DAT9;				/*!< QSPI data register 9,										Address offset: 0x84  */
    __IO uint32_t DAT10;			/*!< QSPI data register 10,										Address offset: 0x88  */
    __IO uint32_t DAT11;			/*!< QSPI data register 11,										Address offset: 0x8C  */
    __IO uint32_t DAT12;			/*!< QSPI data register 12,										Address offset: 0x90  */
    __IO uint32_t DAT13;			/*!< QSPI data register 13,										Address offset: 0x94  */
    __IO uint32_t DAT14;			/*!< QSPI data register 14,										Address offset: 0x98  */
    __IO uint32_t DAT15;			/*!< QSPI data register 15,										Address offset: 0x9C  */
    __IO uint32_t DAT16;			/*!< QSPI data register 16,										Address offset: 0xA0  */
    __IO uint32_t DAT17;			/*!< QSPI data register 17,										Address offset: 0xA4  */
    __IO uint32_t DAT18;			/*!< QSPI data register 18,										Address offset: 0xA8  */
    __IO uint32_t DAT19;			/*!< QSPI data register 19,										Address offset: 0xAC  */
    __IO uint32_t DAT20;			/*!< QSPI data register 20,										Address offset: 0xB0  */
    __IO uint32_t DAT21;			/*!< QSPI data register 21,										Address offset: 0xB4  */
    __IO uint32_t DAT22;			/*!< QSPI data register 22,										Address offset: 0xB8  */
    __IO uint32_t DAT23;			/*!< QSPI data register 23,										Address offset: 0xBC  */
    __IO uint32_t DAT24;			/*!< QSPI data register 24,										Address offset: 0xC0  */
    __IO uint32_t DAT25;			/*!< QSPI data register 25,										Address offset: 0xC4  */
    __IO uint32_t DAT26;			/*!< QSPI data register 26,										Address offset: 0xC8  */
    __IO uint32_t DAT27;			/*!< QSPI data register 27,										Address offset: 0xCC  */
    __IO uint32_t DAT28;			/*!< QSPI data register 28,										Address offset: 0xD0  */
    __IO uint32_t DAT29;			/*!< QSPI data register 29,										Address offset: 0xD4  */
    __IO uint32_t DAT30;			/*!< QSPI data register 30,										Address offset: 0xD8  */
    __IO uint32_t DAT31;			/*!< QSPI data register 31,										Address offset: 0xDC  */
    __IO uint32_t RESERVED1;		/*!< Reserved, 0xE0 																  */
    __IO uint32_t RESERVED2;		/*!< Reserved, 0xE4																	  */
    __IO uint32_t RESERVED3;		/*!< Reserved, 0xE8																	  */
    __IO uint32_t RESERVED4;		/*!< Reserved, 0xEC																	  */
    __IO uint32_t RS_DELAY;			/*!< QSPI receive sampling delay register,						Address offset: 0xF0  */
    __IO uint32_t ENH_CTRL0;		/*!< QSPI enhanced SPI mode control register,					Address offset: 0xF4  */
    __IO uint32_t DDR_TXDE;			/*!< QSPI transmit drive edge register,							Address offset: 0xF8  */
    __IO uint32_t XIP_MODE;			/*!< QSPI XIP mode register,									Address offset: 0xFC  */
    __IO uint32_t XIP_INCR_TOC;		/*!< QSPI XIP INCR transfer OpCode register,					Address offset: 0x100 */
    __IO uint32_t XIP_WRAP_TOC;		/*!< QSPI XIP WRAP transfer OpCode register,					Address offset: 0x104 */
    __IO uint32_t XIP_CTRL;			/*!< QSPI XIP control register,									Address offset: 0x108 */
    __IO uint32_t XIP_SLAVE_EN;		/*!< QSPI XIP slave device enable register,						Address offset: 0x10C */
    __IO uint32_t XIP_RXFOI_CLR;	/*!< QSPI XIP receive FIFO overflow interrupt clear register,	Address offset: 0x110 */
    __IO uint32_t XIP_TOUT;			/*!< QSPI XIP continuous transfer timeout register,				Address offset: 0x114 */
} QSPI_Module;

/**
 * @brief Touch Sensor Controller
 */
 
typedef struct
{
    __IO uint32_t CTRL;			/*!< TSC control register,							Address offset: 0x00 		*/
    __IO uint32_t CHNEN;		/*!< TSC channel selection enable register,			Address offset: 0x04 		*/
    __IO uint32_t STS;			/*!< TSC status register,							Address offset: 0x08	 	*/
    __IO uint32_t RESERVED;		/*!< Reserved, 0x0C														 		*/
    __IO uint32_t ANA_CTRL;		/*!< TSC analog control register,					Address offset: 0x10 		*/
    __IO uint32_t ANA_SEL;		/*!< TSC analog selection register,					Address offset: 0x14 		*/
    __IO uint32_t RESR[3];		/*!< TSC internal resistor selection register 1,	Address offset: 0x18 - 0x20 */
    __IO uint32_t THRHD[24];	/*!< TSC threshold register 0,						Address offset: 0x24 - 0x80 */
} TSC_Module;

/**
 * @brief Random number generator
 */

typedef struct
{									/*!< RNGC Module,                              	  Base Address: 0x40005C00 */
    __IO uint32_t CTRL;             /*!< RNGC control register,                           Address offset: 0x00 */
    __IO uint32_t CTRL_WR_READY;    /*!< RNGC control register ready to write register,   Address offset: 0x04 */
    __IO uint32_t DAT;              /*!< RNGC data register,                              Address offset: 0x08 */
    __IO uint32_t DAT_READY;        /*!< RNGC data ready register,                        Address offset: 0x0C */
}RNGC_Module;


/**
  * @}
  */ /* End of group Peripheral_registers_structures */


/* =========================================  End of section using anonymous unions  ========================================= */
#if defined (__GNUC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif


/* =========================================================================================================================== */
/* ================                          Device Specific Peripheral Address Map                           ================ */
/* =========================================================================================================================== */


/** @addtogroup Peripheral_memory_map
  * @{
  */

/* Peripheral and SRAM base address */
#define FLASH_BASE			((uint32_t) 0x08000000)		/*!< FLASH base address in the alias region */
#define SRAM_BASE			((uint32_t) 0x20000000)		/*!< SRAM base address in the alias region */
#define PERIPH_BASE			((uint32_t) 0x40000000)		/*!< Peripheral base address in the alias region */

#define DBGID_BASE     		((uint32_t) 0xE0040000)		/*!< DBGID Address : 0xE0040000(DBG_BASE) */
#define DBGID_LENGTH    	((uint8_t)  0x04)			/*!< DBGID Length  : 4 Bytes */

/* Peripheral memory map */
#define APB1PERIPH_BASE		(PERIPH_BASE)
#define APB2PERIPH_BASE     (PERIPH_BASE + 0x10000U)
#define AHBPERIPH_BASE		(PERIPH_BASE + 0x18000U)

/* APB1 */
#define TIM2_BASE			(APB1PERIPH_BASE + 0x0000U)
#define TIM3_BASE			(APB1PERIPH_BASE + 0x0400U)
#define TIM4_BASE			(APB1PERIPH_BASE + 0x0800U)
#define TIM5_BASE			(APB1PERIPH_BASE + 0x0C00U)
#define TIM6_BASE			(APB1PERIPH_BASE + 0x1000U)
#define TIM7_BASE			(APB1PERIPH_BASE + 0x1400U)
#define OPAMP_BASE			(APB1PERIPH_BASE + 0x2000U)
#define COMP_BASE			(APB1PERIPH_BASE + 0x2400U)
#define RTC_BASE			(APB1PERIPH_BASE + 0x2800U)
#define WWDG_BASE			(APB1PERIPH_BASE + 0x2C00U)
#define IWDG_BASE			(APB1PERIPH_BASE + 0x3000U)
#define TSC_BASE			(APB1PERIPH_BASE + 0x3400U)
#define SPI2_BASE			(APB1PERIPH_BASE + 0x3800U)
#define SPI3_BASE			(APB1PERIPH_BASE + 0x3C00U)
#define USART2_BASE			(APB1PERIPH_BASE + 0x4400U)
#define USART3_BASE			(APB1PERIPH_BASE + 0x4800U)
#define UART4_BASE			(APB1PERIPH_BASE + 0x4C00U)
#define UART5_BASE			(APB1PERIPH_BASE + 0x5000U)
#define I2C1_BASE			(APB1PERIPH_BASE + 0x5400U)
#define I2C2_BASE			(APB1PERIPH_BASE + 0x5800U)
#define RNGC_BASE			(APB1PERIPH_BASE + 0x5C00U)
#define USB_CAN1_SRAM_BASE	(APB1PERIPH_BASE + 0x6000U)
#define CAN1_BASE			(APB1PERIPH_BASE + 0x6400U)
#define CAN2_BASE			(APB1PERIPH_BASE + 0x6800U)
#define BKP_BASE			(APB1PERIPH_BASE + 0x6C00U)
#define PWR_BASE			(APB1PERIPH_BASE + 0x7000U)
#define DAC_BASE			(APB1PERIPH_BASE + 0x7400U)

/* APB2 */
#define AFIO_BASE			(APB2PERIPH_BASE + 0x0000U)
#define EXTI_BASE			(APB2PERIPH_BASE + 0x0400U)
#define GPIOA_BASE			(APB2PERIPH_BASE + 0x0800U)
#define GPIOB_BASE			(APB2PERIPH_BASE + 0x0C00U)
#define GPIOC_BASE			(APB2PERIPH_BASE + 0x1000U)
#define GPIOD_BASE			(APB2PERIPH_BASE + 0x1400U)
#define GPIOE_BASE			(APB2PERIPH_BASE + 0x1800U)
#define GPIOF_BASE			(APB2PERIPH_BASE + 0x1C00U)
#define GPIOG_BASE			(APB2PERIPH_BASE + 0x2000U)
#define TIM1_BASE			(APB2PERIPH_BASE + 0x2C00U)
#define SPI1_BASE			(APB2PERIPH_BASE + 0x3000U)
#define TIM8_BASE			(APB2PERIPH_BASE + 0x3400U)
#define USART1_BASE			(APB2PERIPH_BASE + 0x3800U)
#define I2C3_BASE			(APB2PERIPH_BASE + 0x4400U)
#define I2C4_BASE			(APB2PERIPH_BASE + 0x4800U)
#define UART6_BASE			(APB2PERIPH_BASE + 0x5000U)
#define UART7_BASE			(APB2PERIPH_BASE + 0x5400U)

/* AHB */
#define DMA1_BASE			(AHBPERIPH_BASE + 0x8000U)
#define DMA1_CH1_BASE		(AHBPERIPH_BASE + 0x8008U)
#define DMA1_CH2_BASE		(AHBPERIPH_BASE + 0x801CU)
#define DMA1_CH3_BASE		(AHBPERIPH_BASE + 0x8030U)
#define DMA1_CH4_BASE		(AHBPERIPH_BASE + 0x8044U)
#define DMA1_CH5_BASE		(AHBPERIPH_BASE + 0x8058U)
#define DMA1_CH6_BASE		(AHBPERIPH_BASE + 0x806CU)
#define DMA1_CH7_BASE		(AHBPERIPH_BASE + 0x8080U)
#define DMA1_CH8_BASE		(AHBPERIPH_BASE + 0x8094U)
#define DMA2_BASE			(AHBPERIPH_BASE + 0x8400U)
#define DMA2_CH1_BASE		(AHBPERIPH_BASE + 0x8408U)
#define DMA2_CH2_BASE		(AHBPERIPH_BASE + 0x841CU)
#define DMA2_CH3_BASE		(AHBPERIPH_BASE + 0x8430U)
#define DMA2_CH4_BASE		(AHBPERIPH_BASE + 0x8444U)
#define DMA2_CH5_BASE		(AHBPERIPH_BASE + 0x8458U)
#define DMA2_CH6_BASE		(AHBPERIPH_BASE + 0x846CU)
#define DMA2_CH7_BASE		(AHBPERIPH_BASE + 0x8480U)
#define DMA2_CH8_BASE		(AHBPERIPH_BASE + 0x8494U)
#define ADC1_BASE			(AHBPERIPH_BASE + 0x8800U)
#define ADC2_BASE			(AHBPERIPH_BASE + 0x8C00U)
#define RCC_BASE			(AHBPERIPH_BASE + 0x9000U)
#define ADC3_BASE			(AHBPERIPH_BASE + 0x9800U)
#define ADC4_BASE			(AHBPERIPH_BASE + 0x9C00U)
#define FLASH_R_BASE		(AHBPERIPH_BASE + 0xA000U)	/*!< Flash registers base address */
#define CRC_BASE			(AHBPERIPH_BASE + 0xB000U)
#define SAC_BASE			(AHBPERIPH_BASE + 0xC000U)
#define SAC_SRAM_BASE		(AHBPERIPH_BASE + 0xC400U)
#define MMU_BASE			(AHBPERIPH_BASE + 0xCC00U)

#define QSPI_BASE			(((uint32_t)0xA0001000))	/*!< QSPI registers base address */

#define OPB_BASE				((uint32_t) 0x1FFFF800U)	/*!< Flash Option Bytes base address */
#define DBG_BASE			((uint32_t) 0xE0040000U)	/*!< Debug MCU registers base address */

/**
  * @}
  */ /* End of group Peripheral_memory_map */


/* =========================================================================================================================== */
/* ================                                  Peripheral declaration                                   ================ */
/* =========================================================================================================================== */

/** @addtogroup Peripheral_declaration
  * @{
  */
#define TIM2        		((TIM_Module*) TIM2_BASE)
#define TIM3        		((TIM_Module*) TIM3_BASE)
#define TIM4        		((TIM_Module*) TIM4_BASE)
#define TIM5        		((TIM_Module*) TIM5_BASE)
#define TIM6        		((TIM_Module*) TIM6_BASE)
#define TIM7        		((TIM_Module*) TIM7_BASE)
#define AFEC        		((AFEC_Module*) AFEC_BASE)
#define OPAMP       		((OPAMP_Module*) OPAMP_BASE)
#define COMP        		((COMP_Module*) COMP_BASE)
#define RTC         		((RTC_Module*) RTC_BASE)
#define WWDG        		((WWDG_Module*) WWDG_BASE)
#define IWDG        		((IWDG_Module*) IWDG_BASE)
#define TSC         		((TSC_Module*) TSC_BASE)
#define SPI2        		((SPI_Module*) SPI2_BASE)
#define SPI3        		((SPI_Module*) SPI3_BASE)
#define USART2      		((USART_Module*) USART2_BASE)
#define USART3      		((USART_Module*) USART3_BASE)
#define UART4       		((USART_Module*) UART4_BASE)
#define UART5       		((USART_Module*) UART5_BASE)
#define I2C1        		((I2C_Module*) I2C1_BASE)
#define I2C2        		((I2C_Module*) I2C2_BASE)
#define RNGC				((RNGC_Module*) RNGC_BASE)
#define CAN1        		((CAN_Module*) CAN1_BASE)
#define CAN2        		((CAN_Module*) CAN2_BASE)
#define BKP         		((BKP_Module*) BKP_BASE)
#define PWR         		((PWR_Module*) PWR_BASE)
#define DAC         		((DAC_Module*) DAC_BASE)
#define AFIO        		((AFIO_Module*) AFIO_BASE)
#define EXTI        		((EXTI_Module*) EXTI_BASE)
#define GPIOA       		((GPIO_Module*) GPIOA_BASE)
#define GPIOB       		((GPIO_Module*) GPIOB_BASE)
#define GPIOC       		((GPIO_Module*) GPIOC_BASE)
#define GPIOD       		((GPIO_Module*) GPIOD_BASE)
#define GPIOE       		((GPIO_Module*) GPIOE_BASE)
#define GPIOF       		((GPIO_Module*) GPIOF_BASE)
#define GPIOG       		((GPIO_Module*) GPIOG_BASE)
#define TIM1        		((TIM_Module*) TIM1_BASE)
#define SPI1        		((SPI_Module*) SPI1_BASE)
#define TIM8        		((TIM_Module*) TIM8_BASE)
#define USART1      		((USART_Module*) USART1_BASE)
#define I2C3        		((I2C_Module*) I2C3_BASE)
#define I2C4        		((I2C_Module*) I2C4_BASE)
#define UART6       		((USART_Module*) UART6_BASE)
#define UART7       		((USART_Module*) UART7_BASE)
#define DMA1        		((DMA_Module*) DMA1_BASE)
#define DMA2        		((DMA_Module*) DMA2_BASE)
#define DMA1_CH1    		((DMA_ChannelType*) DMA1_CH1_BASE)
#define DMA1_CH2    		((DMA_ChannelType*) DMA1_CH2_BASE)
#define DMA1_CH3    		((DMA_ChannelType*) DMA1_CH3_BASE)
#define DMA1_CH4    		((DMA_ChannelType*) DMA1_CH4_BASE)
#define DMA1_CH5    		((DMA_ChannelType*) DMA1_CH5_BASE)
#define DMA1_CH6    		((DMA_ChannelType*) DMA1_CH6_BASE)
#define DMA1_CH7    		((DMA_ChannelType*) DMA1_CH7_BASE)
#define DMA1_CH8    		((DMA_ChannelType*) DMA1_CH8_BASE)
#define DMA2_CH1    		((DMA_ChannelType*) DMA2_CH1_BASE)
#define DMA2_CH2    		((DMA_ChannelType*) DMA2_CH2_BASE)
#define DMA2_CH3    		((DMA_ChannelType*) DMA2_CH3_BASE)
#define DMA2_CH4    		((DMA_ChannelType*) DMA2_CH4_BASE)
#define DMA2_CH5    		((DMA_ChannelType*) DMA2_CH5_BASE)
#define DMA2_CH6    		((DMA_ChannelType*) DMA2_CH6_BASE)
#define DMA2_CH7    		((DMA_ChannelType*) DMA2_CH7_BASE)
#define DMA2_CH8    		((DMA_ChannelType*) DMA2_CH8_BASE)
#define ADC1        		((ADC_Module*) ADC1_BASE)
#define ADC2        		((ADC_Module*) ADC2_BASE)
#define RCC         		((RCC_Module*) RCC_BASE)
#define ADC3        		((ADC_Module*) ADC3_BASE)
#define ADC4        		((ADC_Module*) ADC4_BASE)
#define FLASH       		((FLASH_Module*) FLASH_R_BASE)
#define OPB          		((OPB_Module*) OPB_BASE)
#define CRC         		((CRC_Module*) CRC_BASE)

#define QSPI				((QSPI_Module*) QSPI_BASE)

#define DBG					((DBG_Module*) DBG_BASE)

/**
  * @}
  */ /* End of group Peripheral_declaration */
  
/** @addtogroup Exported_constants
* @{
*/

/** @addtogroup Peripheral_Registers_Bits_Definition
* @{
*/

/******************************************************************************/
/*                         Peripheral Registers_Bits_Definition               */
/******************************************************************************/

/******************************************************************************/
/*                                                                            */
/*                          CRC calculation unit                              */
/*                                                                            */
/******************************************************************************/
/*****************  Bit definition for CRC_CRC32DAT register  *****************/
#define CRC_CRC32DAT_CRC32DAT_Pos				(0U)
#define CRC_CRC32DAT_CRC32DAT_Msk				(0xFFFFFFFFUL << CRC_CRC32DAT_CRC32DAT_Pos)
#define CRC_CRC32DAT_CRC32DAT					CRC_CRC32DAT_CRC32DAT_Msk		/*!< Data register bits */

/****************  Bit definition for CRC_CRC32IDAT register  *****************/
#define CRC_CRC32IDAT_CRC32IDAT_Pos				(0U)
#define CRC_CRC32IDAT_CRC32IDAT_Msk				(0xFFUL << CRC_CRC32IDAT_CRC32IDAT_Pos)
#define CRC_CRC32IDAT_CRC32IDAT					CRC_CRC32IDAT_CRC32IDAT_Msk		/*!< General-purpose 8-bit data register bits */

/****************  Bit definition for CRC_CRC32CTRL register  *****************/
#define CRC_CRC32CTRL_RESET_Pos					(0U)
#define CRC_CRC32CTRL_RESET_Msk					(0x1UL << CRC_CRC32CTRL_RESET_Pos)
#define CRC_CRC32CTRL_RESET						CRC_CRC32CTRL_RESET_Msk			/*!< RESET bit */

/****************  Bit definition for CRC_CRC16CTRL register  *****************/
#define CRC_CRC16CTRL_ENDHL_Pos					(1U)
#define CRC_CRC16CTRL_ENDHL_Msk					(0x1UL << CRC_CRC16CTRL_ENDHL_Pos)
#define CRC_CRC16CTRL_ENDHL						CRC_CRC16CTRL_ENDHL_Msk			/*!< Endian of data to be verified. 1: Little Endian; 0: Big Endian */
#define CRC_CRC16CTRL_CLR_Pos					(2U)
#define CRC_CRC16CTRL_CLR_Msk					(0x1UL << CRC_CRC16CTRL_CLR_Pos)
#define CRC_CRC16CTRL_CLR						CRC_CRC16CTRL_CLR_Msk			/*!< CLEAR bit for CRC16 result */

/*****************  Bit definition for CRC_CRC16DAT register  *****************/
#define CRC_CRC16DAT_CRC16DAT_Pos				(0U)
#define CRC_CRC16DAT_CRC16DAT_Msk				(0xFFUL << CRC_CRC16DAT_CRC16DAT_Pos)
#define CRC_CRC16DAT_CRC16DAT					CRC_CRC16DAT_CRC16DAT_Msk		/*!< CRC16 data register bits */

/******************  Bit definition for CRC_CRC16D register  ******************/
#define CRC_CRC16D_CRC16D_Pos					(0U)
#define CRC_CRC16D_CRC16D_Msk					(0xFFFFUL << CRC_CRC16D_CRC16D_Pos)
#define CRC_CRC16D_CRC16D						CRC_CRC16D_CRC16D_Msk			/*!< CRC16 result register bits */

/*******************  Bit definition for CRC_LRC register  ********************/
#define CRC_LRC_LRCDAT_Pos						(0U)
#define CRC_LRC_LRCDAT_Msk						(0xFFUL << CRC_LRC_LRCDAT_Pos)
#define CRC_LRC_LRCDAT							CRC_LRC_LRCDAT_Msk				/*!< LRC data register bits */

/******************************************************************************/
/*                                                                            */
/*                             Power Control                                  */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for PWR_CTRL register  *******************/
#define PWR_CTRL_LPS_Pos						(0U)
#define PWR_CTRL_LPS_Msk						(0x1UL << PWR_CTRL_LPS_Pos)
#define PWR_CTRL_LPS							PWR_CTRL_LPS_Msk				/*!< Low-Power Deepsleep */
#define PWR_CTRL_PDS_Pos						(1U)
#define PWR_CTRL_PDS_Msk						(0x1UL << PWR_CTRL_PDS_Pos)
#define PWR_CTRL_PDS							PWR_CTRL_PDS_Msk				/*!< Power Down Deepsleep */
#define PWR_CTRL_CWKUP_Pos						(2U)
#define PWR_CTRL_CWKUP_Msk						(0x1UL << PWR_CTRL_CWKUP_Pos)
#define PWR_CTRL_CWKUP							PWR_CTRL_CWKUP_Msk				/*!< Clear Wakeup Flag */
#define PWR_CTRL_CSBVBAT_Pos					(3U)
#define PWR_CTRL_CSBVBAT_Msk					(0x1UL << PWR_CTRL_CSBVBAT_Pos)
#define PWR_CTRL_CSBVBAT						PWR_CTRL_CSBVBAT_Msk			/*!< Clear Standby Flag */
#define PWR_CTRL_PVDEN_Pos						(4U)
#define PWR_CTRL_PVDEN_Msk						(0x1UL << PWR_CTRL_PVDEN_Pos)
#define PWR_CTRL_PVDEN							PWR_CTRL_PVDEN_Msk				/*!< Power Voltage Detector Enable */

#define PWR_CTRL_PRS_Pos						(5U)
#define PWR_CTRL_PRS_Msk						(0x7UL << PWR_CTRL_PRS_Pos)
#define PWR_CTRL_PRS							PWR_CTRL_PRS_Msk				/*!< PRS[2:0] bits (PVD Level Selection) */
#define PWR_CTRL_PRS_0							((uint16_t) 0x0020)				/*!< Bit 0 */
#define PWR_CTRL_PRS_1							((uint16_t) 0x0040)				/*!< Bit 1 */
#define PWR_CTRL_PRS_2							((uint16_t) 0x0080)				/*!< Bit 2 */

#define PWR_CTRL_DBKP_Pos						(8U)
#define PWR_CTRL_DBKP_Msk						(0x1UL << PWR_CTRL_DBKP_Pos)
#define PWR_CTRL_DBKP							PWR_CTRL_DBKP_Msk				/*!< Disable Backup Domain write protection */
#define PWR_CTRL_MSB_Pos						(9U)
#define PWR_CTRL_MSB_Msk						(0x1UL << PWR_CTRL_MSB_Pos)
#define PWR_CTRL_MSB							PWR_CTRL_MSB_Msk				/*!< PRS bit 3 */

/*****************  Bit definition for PWR_CTRLSTS register  ******************/
#define PWR_CTRLSTS_WKUPF_Pos					(0U)
#define PWR_CTRLSTS_WKUPF_Msk					(0x1UL << PWR_CTRLSTS_WKUPF_Pos)
#define PWR_CTRLSTS_WKUPF						PWR_CTRLSTS_WKUPF_Msk			/*!< Wakeup Flag */
#define PWR_CTRLSTS_SBF_Pos						(1U)
#define PWR_CTRLSTS_SBF_Msk						(0x1UL << PWR_CTRLSTS_SBF_Pos)
#define PWR_CTRLSTS_SBF							PWR_CTRLSTS_SBF_Msk				/*!< Standby Flag */
#define PWR_CTRLSTS_PVDO_Pos					(2U)
#define PWR_CTRLSTS_PVDO_Msk					(0x1UL << PWR_CTRLSTS_PVDO_Pos)
#define PWR_CTRLSTS_PVDO						PWR_CTRLSTS_PVDO_Msk			/*!< PVD Output */
#define PWR_CTRLSTS_VBATF_Pos					(3U)
#define PWR_CTRLSTS_VBATF_Msk					(0x1UL << PWR_CTRLSTS_VBATF_Pos)
#define PWR_CTRLSTS_VBATF						PWR_CTRLSTS_VBATF_Msk			/*!< VBAT Flag */
#define PWR_CTRLSTS_WKUPEN_Pos					(8U)
#define PWR_CTRLSTS_WKUPEN_Msk					(0x1UL << PWR_CTRLSTS_WKUPEN_Pos)
#define PWR_CTRLSTS_WKUPEN						PWR_CTRLSTS_WKUPEN_Msk			/*!< Enable WKUP pin */

/******************  Bit definition for PWR_CTRL2 register  *******************/
#define PWR_CTRL2_STOP2S_Pos					(0U)
#define PWR_CTRL2_STOP2S_Msk					(0x1UL << PWR_CTRL2_STOP2S_Pos)
#define PWR_CTRL2_STOP2S						PWR_CTRL2_STOP2S_Msk			/*!< Enable STOP2 */
#define PWR_CTRL2_SR2VBRET_Pos					(1U)
#define PWR_CTRL2_SR2VBRET_Msk					(0x1UL << PWR_CTRL2_SR2VBRET_Pos)
#define PWR_CTRL2_SR2VBRET						PWR_CTRL2_SR2VBRET_Msk			/*!< VBAT mode SRAM2 retention */
#define PWR_CTRL2_SR2STBRET_Pos					(2U)
#define PWR_CTRL2_SR2STBRET_Msk					(0x1UL << PWR_CTRL2_SR2STBRET_Pos)
#define PWR_CTRL2_SR2STBRET						PWR_CTRL2_SR2STBRET_Msk			/*!< Standby mode SRAM2 retention */
#define PWR_CTRL2_TMPWPEN_Pos					(3U)
#define PWR_CTRL2_TMPWPEN_Msk					(0x1UL << PWR_CTRL2_TMPWPEN_Pos)
#define PWR_CTRL2_TMPWPEN						PWR_CTRL2_TMPWPEN_Msk			/*!< Enable Tamper WakeUp */
#define PWR_CTRL2_LSITRIM_Pos					(4U)
#define PWR_CTRL2_LSITRIM_Msk					(0x1FUL << PWR_CTRL2_LSITRIM_Pos)
#define PWR_CTRL2_LSITRIM						PWR_CTRL2_LSITRIM_Msk			/*!< config the LSI trimming value */
#define PWR_CTRL2_IWDGWPEN_Pos					(9U)
#define PWR_CTRL2_IWDGWPEN_Msk					(0x1UL << PWR_CTRL2_IWDGWPEN_Pos)
#define PWR_CTRL2_IWDGWPEN						PWR_CTRL2_IWDGWPEN_Msk			/*!< Enable IWDG WakeUp */
#define PWR_CTRL2_IWDGRSTEN_Pos					(10U)
#define PWR_CTRL2_IWDGRSTEN_Msk					(0x1UL << PWR_CTRL2_IWDGRSTEN_Pos)
#define PWR_CTRL2_IWDGRSTEN						PWR_CTRL2_IWDGRSTEN_Msk			/*!< Enable IWDG RST WakeUp */

/******************  Bit definition for PWR_CTRL3 register  *******************/
#define PWR_CTRL3_EXMODE_Pos					(0U)
#define PWR_CTRL3_EXMODE_Msk					(0x1UL << PWR_CTRL3_EXMODE_Pos)
#define PWR_CTRL3_EXMODE						PWR_CTRL3_EXMODE_Msk			/*!< Extend mode control bit */

/******************************************************************************/
/*                                                                            */
/*                            Backup registers                                */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for BKP_DAT1 register  *******************/
#define BKP_DAT1_DAT_Pos						(0U)
#define BKP_DAT1_DAT_Msk						(0xFFFFUL << BKP_DAT1_DAT_Pos)
#define BKP_DAT1_DAT							BKP_DAT1_DAT_Msk				/*!< Backup data 1 */

/*******************  Bit definition for BKP_DAT2 register  *******************/
#define BKP_DAT2_DAT_Pos						(0U)
#define BKP_DAT2_DAT_Msk						(0xFFFFUL << BKP_DAT2_DAT_Pos)
#define BKP_DAT2_DAT							BKP_DAT2_DAT_Msk				/*!< Backup data 2 */

/*******************  Bit definition for BKP_DAT3 register  *******************/
#define BKP_DAT3_DAT_Pos						(0U)
#define BKP_DAT3_DAT_Msk						(0xFFFFUL << BKP_DAT3_DAT_Pos)
#define BKP_DAT3_DAT							BKP_DAT3_DAT_Msk				/*!< Backup data 3 */

/*******************  Bit definition for BKP_DAT4 register  *******************/
#define BKP_DAT4_DAT_Pos						(0U)
#define BKP_DAT4_DAT_Msk						(0xFFFFUL << BKP_DAT4_DAT_Pos)
#define BKP_DAT4_DAT							BKP_DAT4_DAT_Msk				/*!< Backup data 4 */

/*******************  Bit definition for BKP_DAT5 register  *******************/
#define BKP_DAT5_DAT_Pos						(0U)
#define BKP_DAT5_DAT_Msk						(0xFFFFUL << BKP_DAT5_DAT_Pos)
#define BKP_DAT5_DAT							BKP_DAT5_DAT_Msk				/*!< Backup data 5 */

/*******************  Bit definition for BKP_DAT6 register  *******************/
#define BKP_DAT6_DAT_Pos						(0U)
#define BKP_DAT6_DAT_Msk						(0xFFFFUL << BKP_DAT6_DAT_Pos)
#define BKP_DAT6_DAT							BKP_DAT6_DAT_Msk				/*!< Backup data 6 */

/*******************  Bit definition for BKP_DAT7 register  *******************/
#define BKP_DAT7_DAT_Pos						(0U)
#define BKP_DAT7_DAT_Msk						(0xFFFFUL << BKP_DAT7_DAT_Pos)
#define BKP_DAT7_DAT							BKP_DAT7_DAT_Msk				/*!< Backup data 7 */

/*******************  Bit definition for BKP_DAT8 register  *******************/
#define BKP_DAT8_DAT_Pos						(0U)
#define BKP_DAT8_DAT_Msk						(0xFFFFUL << BKP_DAT8_DAT_Pos)
#define BKP_DAT8_DAT							BKP_DAT8_DAT_Msk				/*!< Backup data 8 */

/*******************  Bit definition for BKP_DAT9 register  *******************/
#define BKP_DAT9_DAT_Pos						(0U)
#define BKP_DAT9_DAT_Msk						(0xFFFFUL << BKP_DAT9_DAT_Pos)
#define BKP_DAT9_DAT							BKP_DAT9_DAT_Msk				/*!< Backup data 9 */

/******************  Bit definition for BKP_DAT10 register  *******************/
#define BKP_DAT10_DAT_Pos						(0U)
#define BKP_DAT10_DAT_Msk						(0xFFFFUL << BKP_DAT10_DAT_Pos)
#define BKP_DAT10_DAT							BKP_DAT10_DAT_Msk				/*!< Backup data 10 */

/******************  Bit definition for BKP_DAT11 register  *******************/
#define BKP_DAT11_DAT_Pos						(0U)
#define BKP_DAT11_DAT_Msk						(0xFFFFUL << BKP_DAT11_DAT_Pos)
#define BKP_DAT11_DAT							BKP_DAT11_DAT_Msk				/*!< Backup data 11 */

/******************  Bit definition for BKP_DAT12 register  *******************/
#define BKP_DAT12_DAT_Pos						(0U)
#define BKP_DAT12_DAT_Msk						(0xFFFFUL << BKP_DAT12_DAT_Pos)
#define BKP_DAT12_DAT							BKP_DAT12_DAT_Msk				/*!< Backup data 12 */

/******************  Bit definition for BKP_DAT13 register  *******************/
#define BKP_DAT13_DAT_Pos						(0U)
#define BKP_DAT13_DAT_Msk						(0xFFFFUL << BKP_DAT13_DAT_Pos)
#define BKP_DAT13_DAT							BKP_DAT13_DAT_Msk				/*!< Backup data 13 */

/******************  Bit definition for BKP_DAT14 register  *******************/
#define BKP_DAT14_DAT_Pos						(0U)
#define BKP_DAT14_DAT_Msk						(0xFFFFUL << BKP_DAT14_DAT_Pos)
#define BKP_DAT14_DAT							BKP_DAT14_DAT_Msk				/*!< Backup data 14 */

/******************  Bit definition for BKP_DAT15 register  *******************/
#define BKP_DAT15_DAT_Pos						(0U)
#define BKP_DAT15_DAT_Msk						(0xFFFFUL << BKP_DAT15_DAT_Pos)
#define BKP_DAT15_DAT							BKP_DAT15_DAT_Msk				/*!< Backup data 15 */

/******************  Bit definition for BKP_DAT16 register  *******************/
#define BKP_DAT16_DAT_Pos						(0U)
#define BKP_DAT16_DAT_Msk						(0xFFFFUL << BKP_DAT16_DAT_Pos)
#define BKP_DAT16_DAT							BKP_DAT16_DAT_Msk				/*!< Backup data 16 */

/******************  Bit definition for BKP_DAT17 register  *******************/
#define BKP_DAT17_DAT_Pos						(0U)
#define BKP_DAT17_DAT_Msk						(0xFFFFUL << BKP_DAT17_DAT_Pos)
#define BKP_DAT17_DAT							BKP_DAT17_DAT_Msk				/*!< Backup data 17 */

/******************  Bit definition for BKP_DAT18 register  *******************/
#define BKP_DAT18_DAT_Pos						(0U)
#define BKP_DAT18_DAT_Msk						(0xFFFFUL << BKP_DAT18_DAT_Pos)
#define BKP_DAT18_DAT							BKP_DAT18_DAT_Msk				/*!< Backup data 18 */

/******************  Bit definition for BKP_DAT19 register  *******************/
#define BKP_DAT19_DAT_Pos						(0U)
#define BKP_DAT19_DAT_Msk						(0xFFFFUL << BKP_DAT19_DAT_Pos)
#define BKP_DAT19_DAT							BKP_DAT19_DAT_Msk				/*!< Backup data 19 */

/******************  Bit definition for BKP_DAT20 register  *******************/
#define BKP_DAT20_DAT_Pos						(0U)
#define BKP_DAT20_DAT_Msk						(0xFFFFUL << BKP_DAT20_DAT_Pos)
#define BKP_DAT20_DAT							BKP_DAT20_DAT_Msk				/*!< Backup data 20 */

/******************  Bit definition for BKP_DAT21 register  *******************/
#define BKP_DAT21_DAT_Pos						(0U)
#define BKP_DAT21_DAT_Msk						(0xFFFFUL << BKP_DAT21_DAT_Pos)
#define BKP_DAT21_DAT							BKP_DAT21_DAT_Msk				/*!< Backup data 21 */

/******************  Bit definition for BKP_DAT22 register  *******************/
#define BKP_DAT22_DAT_Pos						(0U)
#define BKP_DAT22_DAT_Msk						(0xFFFFUL << BKP_DAT22_DAT_Pos)
#define BKP_DAT22_DAT							BKP_DAT22_DAT_Msk				/*!< Backup data 22 */

/******************  Bit definition for BKP_DAT23 register  *******************/
#define BKP_DAT23_DAT_Pos						(0U)
#define BKP_DAT23_DAT_Msk						(0xFFFFUL << BKP_DAT23_DAT_Pos)
#define BKP_DAT23_DAT							BKP_DAT23_DAT_Msk				/*!< Backup data 23 */

/******************  Bit definition for BKP_DAT24 register  *******************/
#define BKP_DAT24_DAT_Pos						(0U)
#define BKP_DAT24_DAT_Msk						(0xFFFFUL << BKP_DAT24_DAT_Pos)
#define BKP_DAT24_DAT							BKP_DAT24_DAT_Msk				/*!< Backup data 24 */

/******************  Bit definition for BKP_DAT25 register  *******************/
#define BKP_DAT25_DAT_Pos						(0U)
#define BKP_DAT25_DAT_Msk						(0xFFFFUL << BKP_DAT25_DAT_Pos)
#define BKP_DAT25_DAT							BKP_DAT25_DAT_Msk				/*!< Backup data 25 */

/******************  Bit definition for BKP_DAT26 register  *******************/
#define BKP_DAT26_DAT_Pos						(0U)
#define BKP_DAT26_DAT_Msk						(0xFFFFUL << BKP_DAT26_DAT_Pos)
#define BKP_DAT26_DAT							BKP_DAT26_DAT_Msk				/*!< Backup data 26 */

/******************  Bit definition for BKP_DAT27 register  *******************/
#define BKP_DAT27_DAT_Pos						(0U)
#define BKP_DAT27_DAT_Msk						(0xFFFFUL << BKP_DAT27_DAT_Pos)
#define BKP_DAT27_DAT							BKP_DAT27_DAT_Msk				/*!< Backup data 27 */

/******************  Bit definition for BKP_DAT28 register  *******************/
#define BKP_DAT28_DAT_Pos						(0U)
#define BKP_DAT28_DAT_Msk						(0xFFFFUL << BKP_DAT28_DAT_Pos)
#define BKP_DAT28_DAT							BKP_DAT28_DAT_Msk				/*!< Backup data 28 */

/******************  Bit definition for BKP_DAT29 register  *******************/
#define BKP_DAT29_DAT_Pos						(0U)
#define BKP_DAT29_DAT_Msk						(0xFFFFUL << BKP_DAT29_DAT_Pos)
#define BKP_DAT29_DAT							BKP_DAT29_DAT_Msk				/*!< Backup data 29 */

/******************  Bit definition for BKP_DAT30 register  *******************/
#define BKP_DAT30_DAT_Pos						(0U)
#define BKP_DAT30_DAT_Msk						(0xFFFFUL << BKP_DAT30_DAT_Pos)
#define BKP_DAT30_DAT							BKP_DAT30_DAT_Msk				/*!< Backup data 30 */

/******************  Bit definition for BKP_DAT31 register  *******************/
#define BKP_DAT31_DAT_Pos						(0U)
#define BKP_DAT31_DAT_Msk						(0xFFFFUL << BKP_DAT31_DAT_Pos)
#define BKP_DAT31_DAT							BKP_DAT31_DAT_Msk				/*!< Backup data 31 */

/******************  Bit definition for BKP_DAT32 register  *******************/
#define BKP_DAT32_DAT_Pos						(0U)
#define BKP_DAT32_DAT_Msk						(0xFFFFUL << BKP_DAT32_DAT_Pos)
#define BKP_DAT32_DAT							BKP_DAT32_DAT_Msk				/*!< Backup data 32 */

/******************  Bit definition for BKP_DAT33 register  *******************/
#define BKP_DAT33_DAT_Pos						(0U)
#define BKP_DAT33_DAT_Msk						(0xFFFFUL << BKP_DAT33_DAT_Pos)
#define BKP_DAT33_DAT							BKP_DAT33_DAT_Msk				/*!< Backup data 33 */

/******************  Bit definition for BKP_DAT34 register  *******************/
#define BKP_DAT34_DAT_Pos						(0U)
#define BKP_DAT34_DAT_Msk						(0xFFFFUL << BKP_DAT34_DAT_Pos)
#define BKP_DAT34_DAT							BKP_DAT34_DAT_Msk				/*!< Backup data 34 */

/******************  Bit definition for BKP_DAT35 register  *******************/
#define BKP_DAT35_DAT_Pos						(0U)
#define BKP_DAT35_DAT_Msk						(0xFFFFUL << BKP_DAT35_DAT_Pos)
#define BKP_DAT35_DAT							BKP_DAT35_DAT_Msk				/*!< Backup data 35 */

/******************  Bit definition for BKP_DAT36 register  *******************/
#define BKP_DAT36_DAT_Pos						(0U)
#define BKP_DAT36_DAT_Msk						(0xFFFFUL << BKP_DAT36_DAT_Pos)
#define BKP_DAT36_DAT							BKP_DAT36_DAT_Msk				/*!< Backup data 36 */

/******************  Bit definition for BKP_DAT37 register  *******************/
#define BKP_DAT37_DAT_Pos						(0U)
#define BKP_DAT37_DAT_Msk						(0xFFFFUL << BKP_DAT37_DAT_Pos)
#define BKP_DAT37_DAT							BKP_DAT37_DAT_Msk				/*!< Backup data 37 */

/******************  Bit definition for BKP_DAT38 register  *******************/
#define BKP_DAT38_DAT_Pos						(0U)
#define BKP_DAT38_DAT_Msk						(0xFFFFUL << BKP_DAT38_DAT_Pos)
#define BKP_DAT38_DAT							BKP_DAT38_DAT_Msk				/*!< Backup data 38 */

/******************  Bit definition for BKP_DAT39 register  *******************/
#define BKP_DAT39_DAT_Pos						(0U)
#define BKP_DAT39_DAT_Msk						(0xFFFFUL << BKP_DAT39_DAT_Pos)
#define BKP_DAT39_DAT							BKP_DAT39_DAT_Msk				/*!< Backup data 39 */

/******************  Bit definition for BKP_DAT40 register  *******************/
#define BKP_DAT40_DAT_Pos						(0U)
#define BKP_DAT40_DAT_Msk						(0xFFFFUL << BKP_DAT40_DAT_Pos)
#define BKP_DAT40_DAT							BKP_DAT40_DAT_Msk				/*!< Backup data 40 */

/******************  Bit definition for BKP_DAT41 register  *******************/
#define BKP_DAT41_DAT_Pos						(0U)
#define BKP_DAT41_DAT_Msk						(0xFFFFUL << BKP_DAT41_DAT_Pos)
#define BKP_DAT41_DAT							BKP_DAT41_DAT_Msk				/*!< Backup data 41 */

/******************  Bit definition for BKP_DAT42 register  *******************/
#define BKP_DAT42_DAT_Pos						(0U)
#define BKP_DAT42_DAT_Msk						(0xFFFFUL << BKP_DAT42_DAT_Pos)
#define BKP_DAT42_DAT							BKP_DAT42_DAT_Msk				/*!< Backup data 42 */

/*******************  Bit definition for BKP_CTRL register  *******************/
#define BKP_CTRL_TP_EN_Pos						(0U)
#define BKP_CTRL_TP_EN_Msk						(0x1UL << BKP_CTRL_TP_EN_Pos)
#define BKP_CTRL_TP_EN							BKP_CTRL_TP_EN_Msk				/*!< TAMPER pin enable */
#define BKP_CTRL_TP_ALEV_Pos					(1U)
#define BKP_CTRL_TP_ALEV_Msk					(0x1UL << BKP_CTRL_TP_ALEV_Pos)
#define BKP_CTRL_TP_ALEV						BKP_CTRL_TP_ALEV_Msk			/*!< TAMPER pin active level */

/*******************  Bit definition for BKP_CSTS register  *******************/
#define BKP_CSTS_CLRTE_Pos						(0U)
#define BKP_CSTS_CLRTE_Msk						(0x1UL << BKP_CSTS_CLRTE_Pos)
#define BKP_CSTS_CLRTE							BKP_CSTS_CLRTE_Msk				/*!< Clear Tamper event */
#define BKP_CSTS_CLRTINT_Pos					(1U)
#define BKP_CSTS_CLRTINT_Msk					(0x1UL << BKP_CSTS_CLRTINT_Pos)
#define BKP_CSTS_CLRTINT						BKP_CSTS_CLRTINT_Msk			/*!< Clear Tamper Interrupt */
#define BKP_CSTS_TPINT_EN_Pos					(2U)
#define BKP_CSTS_TPINT_EN_Msk					(0x1UL << BKP_CSTS_TPINT_EN_Pos)
#define BKP_CSTS_TPINT_EN						BKP_CSTS_TPINT_EN_Msk			/*!< TAMPER Pin interrupt enable */
#define BKP_CSTS_TEF_Pos						(8U)
#define BKP_CSTS_TEF_Msk						(0x1UL << BKP_CSTS_TEF_Pos)
#define BKP_CSTS_TEF							BKP_CSTS_TEF_Msk				/*!< Tamper Event Flag */
#define BKP_CSTS_TINTF_Pos						(9U)
#define BKP_CSTS_TINTF_Msk						(0x1UL << BKP_CSTS_TINTF_Pos)
#define BKP_CSTS_TINTF							BKP_CSTS_TINTF_Msk				/*!< Tamper Interrupt Flag */

/******************************************************************************/
/*                                                                            */
/*                         Reset and Clock Control                            */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for RCC_CTRL register  *******************/
#define RCC_CTRL_HSIEN_Pos						(0U)
#define RCC_CTRL_HSIEN_Msk						(0x1UL << RCC_CTRL_HSIEN_Pos)
#define RCC_CTRL_HSIEN							RCC_CTRL_HSIEN_Msk				/*!< Internal High Speed clock enable */
#define RCC_CTRL_HSIRDF_Pos						(1U)
#define RCC_CTRL_HSIRDF_Msk						(0x1UL << RCC_CTRL_HSIRDF_Pos)
#define RCC_CTRL_HSIRDF							RCC_CTRL_HSIRDF_Msk				/*!< Internal High Speed clock ready flag */
#define RCC_CTRL_HSITRIM_Pos					(3U)
#define RCC_CTRL_HSITRIM_Msk					(0x1FUL << RCC_CTRL_HSITRIM_Pos)
#define RCC_CTRL_HSITRIM						RCC_CTRL_HSITRIM_Msk			/*!< Internal High Speed clock trimming */
#define RCC_CTRL_HSICAL_Pos						(8U)
#define RCC_CTRL_HSICAL_Msk						(0xFFUL << RCC_CTRL_HSICAL_Pos)
#define RCC_CTRL_HSICAL							RCC_CTRL_HSICAL_Msk				/*!< Internal High Speed clock Calibration */
#define RCC_CTRL_HSEEN_Pos						(16U)
#define RCC_CTRL_HSEEN_Msk						(0x1UL << RCC_CTRL_HSEEN_Pos)
#define RCC_CTRL_HSEEN							RCC_CTRL_HSEEN_Msk				/*!< External High Speed clock enable */
#define RCC_CTRL_HSERDF_Pos						(17U)
#define RCC_CTRL_HSERDF_Msk						(0x1UL << RCC_CTRL_HSERDF_Pos)
#define RCC_CTRL_HSERDF							RCC_CTRL_HSERDF_Msk				/*!< External High Speed clock ready flag */
#define RCC_CTRL_HSEBP_Pos						(18U)
#define RCC_CTRL_HSEBP_Msk						(0x1UL << RCC_CTRL_HSEBP_Pos)
#define RCC_CTRL_HSEBP							RCC_CTRL_HSEBP_Msk				/*!< External High Speed clock Bypass */
#define RCC_CTRL_CLKSSEN_Pos					(19U)
#define RCC_CTRL_CLKSSEN_Msk					(0x1UL << RCC_CTRL_CLKSSEN_Pos)
#define RCC_CTRL_CLKSSEN						RCC_CTRL_CLKSSEN_Msk			/*!< Clock Security System enable */
#define RCC_CTRL_PLLEN_Pos						(24U)
#define RCC_CTRL_PLLEN_Msk						(0x1UL << RCC_CTRL_PLLEN_Pos)
#define RCC_CTRL_PLLEN							RCC_CTRL_PLLEN_Msk				/*!< PLL enable */
#define RCC_CTRL_PLLRDF_Pos						(25U)
#define RCC_CTRL_PLLRDF_Msk						(0x1UL << RCC_CTRL_PLLRDF_Pos)
#define RCC_CTRL_PLLRDF							RCC_CTRL_PLLRDF_Msk				/*!< PLL clock ready flag */

/*******************  Bit definition for RCC_CFG register  ********************/
/*!< SW configuration */
#define RCC_CFG_SCLKSW_Pos						(0U)
#define RCC_CFG_SCLKSW_Msk						(0x3UL << RCC_CFG_SCLKSW_Pos)
#define RCC_CFG_SCLKSW							RCC_CFG_SCLKSW_Msk				/*!< SW[1:0] bits (System clock Switch) */
#define RCC_CFG_SCLKSW_0						((uint32_t) 0x00000001)			/*!< Bit 0 */
#define RCC_CFG_SCLKSW_1						((uint32_t) 0x00000002)			/*!< Bit 1 */

#define RCC_CFG_SCLKSW_HSI						((uint32_t) 0x00000000)			/*!< HSI selected as system clock */
#define RCC_CFG_SCLKSW_HSE						((uint32_t) 0x00000001)			/*!< HSE selected as system clock */
#define RCC_CFG_SCLKSW_PLL						((uint32_t) 0x00000002)			/*!< PLL selected as system clock */

/*!< SWS configuration */
#define RCC_CFG_SCLKSTS_Pos						(2U)
#define RCC_CFG_SCLKSTS_Msk						(0x3UL << RCC_CFG_SCLKSTS_Pos)
#define RCC_CFG_SCLKSTS							RCC_CFG_SCLKSTS_Msk				/*!< SWS[1:0] bits (System Clock Switch Status) */
#define RCC_CFG_SCLKSTS_0						((uint32_t) 0x00000004)			/*!< Bit 0 */
#define RCC_CFG_SCLKSTS_1						((uint32_t) 0x00000008)			/*!< Bit 1 */

#define RCC_CFG_SCLKSTS_HSI						((uint32_t) 0x00000000)			/*!< HSI oscillator used as system clock */
#define RCC_CFG_SCLKSTS_HSE						((uint32_t) 0x00000004)			/*!< HSE oscillator used as system clock */
#define RCC_CFG_SCLKSTS_PLL						((uint32_t) 0x00000008)			/*!< PLL used as system clock */

/*!< HPRE configuration */
#define RCC_CFG_AHBPRES_Pos						(4U)
#define RCC_CFG_AHBPRES_Msk						(0xFUL << RCC_CFG_AHBPRES_Pos)
#define RCC_CFG_AHBPRES							RCC_CFG_AHBPRES_Msk				/*!< HPRE[3:0] bits (AHB prescaler) */
#define RCC_CFG_AHBPRES_0						((uint32_t) 0x00000010)			/*!< Bit 0 */
#define RCC_CFG_AHBPRES_1						((uint32_t) 0x00000020)			/*!< Bit 1 */
#define RCC_CFG_AHBPRES_2						((uint32_t) 0x00000040)			/*!< Bit 2 */
#define RCC_CFG_AHBPRES_3						((uint32_t) 0x00000080)			/*!< Bit 3 */

#define RCC_CFG_AHBPRES_DIV1					((uint32_t) 0x00000000)			/*!< SYSCLK not divided */
#define RCC_CFG_AHBPRES_DIV2					((uint32_t) 0x00000080)			/*!< SYSCLK divided by 2 */
#define RCC_CFG_AHBPRES_DIV4					((uint32_t) 0x00000090)			/*!< SYSCLK divided by 4 */
#define RCC_CFG_AHBPRES_DIV8					((uint32_t) 0x000000A0)			/*!< SYSCLK divided by 8 */
#define RCC_CFG_AHBPRES_DIV16					((uint32_t) 0x000000B0)			/*!< SYSCLK divided by 16 */
#define RCC_CFG_AHBPRES_DIV64					((uint32_t) 0x000000C0)			/*!< SYSCLK divided by 64 */
#define RCC_CFG_AHBPRES_DIV128					((uint32_t) 0x000000D0)			/*!< SYSCLK divided by 128 */
#define RCC_CFG_AHBPRES_DIV256					((uint32_t) 0x000000E0)			/*!< SYSCLK divided by 256 */
#define RCC_CFG_AHBPRES_DIV512					((uint32_t) 0x000000F0)			/*!< SYSCLK divided by 512 */

/*!< PPRE1 configuration */
#define RCC_CFG_APB1PRES_Pos					(8U)
#define RCC_CFG_APB1PRES_Msk					(0x7UL << RCC_CFG_APB1PRES_Pos)
#define RCC_CFG_APB1PRES						RCC_CFG_APB1PRES_Msk			/*!< PRE1[2:0] bits (APB1 prescaler) */
#define RCC_CFG_APB1PRES_0						((uint32_t) 0x00000100)			/*!< Bit 0 */
#define RCC_CFG_APB1PRES_1						((uint32_t) 0x00000200)			/*!< Bit 1 */
#define RCC_CFG_APB1PRES_2						((uint32_t) 0x00000400)			/*!< Bit 2 */

#define RCC_CFG_APB1PRES_DIV1					((uint32_t) 0x00000000)			/*!< HCLK not divided */
#define RCC_CFG_APB1PRES_DIV2					((uint32_t) 0x00000400)			/*!< HCLK divided by 2 */
#define RCC_CFG_APB1PRES_DIV4					((uint32_t) 0x00000500)			/*!< HCLK divided by 4 */
#define RCC_CFG_APB1PRES_DIV8					((uint32_t) 0x00000600)			/*!< HCLK divided by 8 */
#define RCC_CFG_APB1PRES_DIV16					((uint32_t) 0x00000700)			/*!< HCLK divided by 16 */

/*!< PPRE2 configuration */
#define RCC_CFG_APB2PRES_Pos					(11U)
#define RCC_CFG_APB2PRES_Msk					(0x7UL << RCC_CFG_APB2PRES_Pos)
#define RCC_CFG_APB2PRES						RCC_CFG_APB2PRES_Msk			/*!< PRE2[2:0] bits (APB2 prescaler) */
#define RCC_CFG_APB2PRES_0						((uint32_t) 0x00000800)			/*!< Bit 0 */
#define RCC_CFG_APB2PRES_1						((uint32_t) 0x00001000)			/*!< Bit 1 */
#define RCC_CFG_APB2PRES_2						((uint32_t) 0x00002000)			/*!< Bit 2 */

#define RCC_CFG_APB2PRES_DIV1					((uint32_t) 0x00000000)			/*!< HCLK not divided */
#define RCC_CFG_APB2PRES_DIV2					((uint32_t) 0x00002000)			/*!< HCLK divided by 2 */
#define RCC_CFG_APB2PRES_DIV4					((uint32_t) 0x00002800)			/*!< HCLK divided by 4 */
#define RCC_CFG_APB2PRES_DIV8					((uint32_t) 0x00003000)			/*!< HCLK divided by 8 */
#define RCC_CFG_APB2PRES_DIV16					((uint32_t) 0x00003800)			/*!< HCLK divided by 16 */

/*!< PLLSRC configuration */
#define RCC_CFG_PLLSRC_Pos						(16U)
#define RCC_CFG_PLLSRC_Msk						(0x1UL << RCC_CFG_PLLSRC_Pos)
#define RCC_CFG_PLLSRC							RCC_CFG_PLLSRC_Msk				/*!< PLL entry clock source */

#define RCC_CFG_PLLSRC_HSI_DIV2					((uint32_t) 0x00000000)			/*!< HSI clock divided by 2 selected as PLL entry clock source */
#define RCC_CFG_PLLSRC_HSE						((uint32_t) 0x00010000)			/*!< HSE clock selected as PLL entry clock source */

/*!< PLLXTPRE configuration */
#define RCC_CFG_PLLHSEPRES_Pos					(17U)
#define RCC_CFG_PLLHSEPRES_Msk					(0x1UL << RCC_CFG_PLLHSEPRES_Pos)
#define RCC_CFG_PLLHSEPRES						RCC_CFG_PLLHSEPRES_Msk			/*!< HSE divider for PLL entry */

#define RCC_CFG_PLLHSEPRES_HSE					((uint32_t) 0x00000000)			/*!< HSE clock not divided for PLL entry */
#define RCC_CFG_PLLHSEPRES_HSE_DIV2				((uint32_t) 0x00020000)			/*!< HSE clock divided by 2 for PLL entry */

/*!< PLLMUL configuration */
#define RCC_CFG_PLLMULFCT_Pos					(18U)
#define RCC_CFG_PLLMULFCT_Msk					(0x20FUL << RCC_CFG_PLLMULFCT_Pos)
#define RCC_CFG_PLLMULFCT						RCC_CFG_PLLMULFCT_Msk			/*!< PLLMUL[4:0] bits (PLL multiplication factor), bit[3:0] in CFG[21:18]; PLLMULFCT bit 4 in CFG[27] */
#define RCC_CFG_PLLMULFCT_0				 		((uint32_t) 0x00040000)			/*!< Bit 0 */
#define RCC_CFG_PLLMULFCT_1 					((uint32_t) 0x00080000)			/*!< Bit 1 */
#define RCC_CFG_PLLMULFCT_2 					((uint32_t) 0x00100000)			/*!< Bit 2 */
#define RCC_CFG_PLLMULFCT_3 					((uint32_t) 0x00200000)			/*!< Bit 3 */
#define RCC_CFG_PLLMULFCT_4 					((uint32_t) 0x08000000)			/*!< Bit 4 */

#define RCC_CFG_PLLMULFCT2						((uint32_t) 0x00000000)			/*!< PLL input clock*2 */
#define RCC_CFG_PLLMULFCT3						((uint32_t) 0x00040000)			/*!< PLL input clock*3 */
#define RCC_CFG_PLLMULFCT4						((uint32_t) 0x00080000)			/*!< PLL input clock*4 */
#define RCC_CFG_PLLMULFCT5						((uint32_t) 0x000C0000)			/*!< PLL input clock*5 */
#define RCC_CFG_PLLMULFCT6						((uint32_t) 0x00100000)			/*!< PLL input clock*6 */
#define RCC_CFG_PLLMULFCT7						((uint32_t) 0x00140000)			/*!< PLL input clock*7 */
#define RCC_CFG_PLLMULFCT8						((uint32_t) 0x00180000)			/*!< PLL input clock*8 */
#define RCC_CFG_PLLMULFCT9						((uint32_t) 0x001C0000)			/*!< PLL input clock*9 */
#define RCC_CFG_PLLMULFCT10						((uint32_t) 0x00200000)			/*!< PLL input clock*10 */
#define RCC_CFG_PLLMULFCT11						((uint32_t) 0x00240000)			/*!< PLL input clock*11 */
#define RCC_CFG_PLLMULFCT12						((uint32_t) 0x00280000)			/*!< PLL input clock*12 */
#define RCC_CFG_PLLMULFCT13						((uint32_t) 0x002C0000)			/*!< PLL input clock*13 */
#define RCC_CFG_PLLMULFCT14						((uint32_t) 0x00300000)			/*!< PLL input clock*14 */
#define RCC_CFG_PLLMULFCT15						((uint32_t) 0x00340000)			/*!< PLL input clock*15 */
#define RCC_CFG_PLLMULFCT16						((uint32_t) 0x00380000)			/*!< PLL input clock*16 */
#define RCC_CFG_PLLMULFCT16N					((uint32_t) 0x003C0000)			/*!< PLL input clock*16 */
#define RCC_CFG_PLLMULFCT17						((uint32_t) 0x08000000)			/*!< PLL input clock*17 */
#define RCC_CFG_PLLMULFCT18						((uint32_t) 0x08040000)			/*!< PLL input clock*18 */
#define RCC_CFG_PLLMULFCT19						((uint32_t) 0x08080000)			/*!< PLL input clock*19 */
#define RCC_CFG_PLLMULFCT20						((uint32_t) 0x080C0000)			/*!< PLL input clock*20 */
#define RCC_CFG_PLLMULFCT21						((uint32_t) 0x08100000)			/*!< PLL input clock*21 */
#define RCC_CFG_PLLMULFCT22						((uint32_t) 0x08140000)			/*!< PLL input clock*22 */
#define RCC_CFG_PLLMULFCT23						((uint32_t) 0x08180000)			/*!< PLL input clock*23 */
#define RCC_CFG_PLLMULFCT24						((uint32_t) 0x081C0000)			/*!< PLL input clock*24 */
#define RCC_CFG_PLLMULFCT25						((uint32_t) 0x08200000)			/*!< PLL input clock*25 */
#define RCC_CFG_PLLMULFCT26						((uint32_t) 0x08240000)			/*!< PLL input clock*26 */
#define RCC_CFG_PLLMULFCT27						((uint32_t) 0x08280000)			/*!< PLL input clock*27 */
#define RCC_CFG_PLLMULFCT28						((uint32_t) 0x082C0000)			/*!< PLL input clock*28 */
#define RCC_CFG_PLLMULFCT29						((uint32_t) 0x08300000)			/*!< PLL input clock*29 */
#define RCC_CFG_PLLMULFCT30						((uint32_t) 0x08340000)			/*!< PLL input clock*30 */
#define RCC_CFG_PLLMULFCT31						((uint32_t) 0x08380000)			/*!< PLL input clock*31 */
#define RCC_CFG_PLLMULFCT32						((uint32_t) 0x083C0000)			/*!< PLL input clock*32 */

/*!< MCO configuration */
#define RCC_CFG_MCO_Pos							(24U)
#define RCC_CFG_MCO_Msk							(0x7UL << RCC_CFG_MCO_Pos)
#define RCC_CFG_MCO								RCC_CFG_MCO_Msk					/*!< MCO[2:0] bits (Microcontroller Clock Output) */
#define RCC_CFG_MCO_0							((uint32_t) 0x01000000)			/*!< Bit 0 */
#define RCC_CFG_MCO_1							((uint32_t) 0x02000000)			/*!< Bit 1 */
#define RCC_CFG_MCO_2							((uint32_t) 0x04000000)			/*!< Bit 2 */

#define RCC_CFG_MCO_NOCLK						((uint32_t) 0x00000000)			/*!< No clock */
#define RCC_CFG_MCO_SYSCLK						((uint32_t) 0x04000000)			/*!< System clock selected as MCO source */
#define RCC_CFG_MCO_HSI							((uint32_t) 0x05000000)			/*!< HSI clock selected as MCO source */
#define RCC_CFG_MCO_HSE							((uint32_t) 0x06000000)			/*!< HSE clock selected as MCO source  */
#define RCC_CFG_MCO_PLL							((uint32_t) 0x07000000)			/*!< PLL clock divided by 2 selected as MCO source */

/*!< MCOPRE configuration */
#define RCC_CFG_MCOPRES_Pos						(28U)
#define RCC_CFG_MCOPRES_Msk						(0xFUL << RCC_CFG_MCOPRES_Pos)
#define RCC_CFG_MCOPRES							RCC_CFG_MCOPRES_Msk				/*!< MCOPRE[3:0] bits ( PLL prescaler set and cleared by software to generate MCOPRE clock.) */
#define RCC_CFG_MCOPRES_0						((uint32_t) 0x10000000)			/*!< Bit 0 */
#define RCC_CFG_MCOPRES_1						((uint32_t) 0x20000000)			/*!< Bit 1 */
#define RCC_CFG_MCOPRES_2						((uint32_t) 0x40000000)			/*!< Bit 2 */
#define RCC_CFG_MCOPRES_3						((uint32_t) 0x80000000)			/*!< Bit 3 */

#define RCC_CFG_MCOPRES_PLLDIV2					((uint32_t) 0x20000000)			/*!< PLL clock is divided by 2 */
#define RCC_CFG_MCOPRES_PLLDIV3					((uint32_t) 0x30000000)			/*!< PLL clock is divided by 3 */
#define RCC_CFG_MCOPRES_PLLDIV4					((uint32_t) 0x40000000)			/*!< PLL clock is divided by 4 */
#define RCC_CFG_MCOPRES_PLLDIV5					((uint32_t) 0x50000000)			/*!< PLL clock is divided by 5 */
#define RCC_CFG_MCOPRES_PLLDIV6					((uint32_t) 0x60000000)			/*!< PLL clock is divided by 6 */
#define RCC_CFG_MCOPRES_PLLDIV7					((uint32_t) 0x70000000)			/*!< PLL clock is divided by 7 */
#define RCC_CFG_MCOPRES_PLLDIV8					((uint32_t) 0x80000000)			/*!< PLL clock is divided by 8 */
#define RCC_CFG_MCOPRES_PLLDIV9					((uint32_t) 0x90000000)			/*!< PLL clock is divided by 9 */
#define RCC_CFG_MCOPRES_PLLDIV10				((uint32_t) 0xA0000000)			/*!< PLL clock is divided by 10 */
#define RCC_CFG_MCOPRES_PLLDIV11				((uint32_t) 0xB0000000)			/*!< PLL clock is divided by 11 */
#define RCC_CFG_MCOPRES_PLLDIV12				((uint32_t) 0xC0000000)			/*!< PLL clock is divided by 12 */
#define RCC_CFG_MCOPRES_PLLDIV13				((uint32_t) 0xD0000000)			/*!< PLL clock is divided by 13 */
#define RCC_CFG_MCOPRES_PLLDIV14				((uint32_t) 0xE0000000)			/*!< PLL clock is divided by 14 */
#define RCC_CFG_MCOPRES_PLLDIV15				((uint32_t) 0xF0000000)			/*!< PLL clock is divided by 15 */

/******************  Bit definition for RCC_CLKINT register  ******************/
#define RCC_CLKINT_LSIRDIF_Pos					(0U)
#define RCC_CLKINT_LSIRDIF_Msk					(0x1UL << RCC_CLKINT_LSIRDIF_Pos)
#define RCC_CLKINT_LSIRDIF						RCC_CLKINT_LSIRDIF_Msk			/*!< LSI Ready Interrupt flag */
#define RCC_CLKINT_LSERDIF_Pos					(1U)
#define RCC_CLKINT_LSERDIF_Msk					(0x1UL << RCC_CLKINT_LSERDIF_Pos)
#define RCC_CLKINT_LSERDIF						RCC_CLKINT_LSERDIF_Msk			/*!< LSE Ready Interrupt flag */
#define RCC_CLKINT_HSIRDIF_Pos					(2U)
#define RCC_CLKINT_HSIRDIF_Msk					(0x1UL << RCC_CLKINT_HSIRDIF_Pos)
#define RCC_CLKINT_HSIRDIF						RCC_CLKINT_HSIRDIF_Msk			/*!< HSI Ready Interrupt flag */
#define RCC_CLKINT_HSERDIF_Pos					(3U)
#define RCC_CLKINT_HSERDIF_Msk					(0x1UL << RCC_CLKINT_HSERDIF_Pos)
#define RCC_CLKINT_HSERDIF						RCC_CLKINT_HSERDIF_Msk			/*!< HSE Ready Interrupt flag */
#define RCC_CLKINT_PLLRDIF_Pos					(4U)
#define RCC_CLKINT_PLLRDIF_Msk					(0x1UL << RCC_CLKINT_PLLRDIF_Pos)
#define RCC_CLKINT_PLLRDIF						RCC_CLKINT_PLLRDIF_Msk			/*!< PLL Ready Interrupt flag */
#define RCC_CLKINT_CLKSSIF_Pos					(7U)
#define RCC_CLKINT_CLKSSIF_Msk					(0x1UL << RCC_CLKINT_CLKSSIF_Pos)
#define RCC_CLKINT_CLKSSIF						RCC_CLKINT_CLKSSIF_Msk			/*!< Clock Security System Interrupt flag */
#define RCC_CLKINT_LSIRDIEN_Pos					(8U)
#define RCC_CLKINT_LSIRDIEN_Msk					(0x1UL << RCC_CLKINT_LSIRDIEN_Pos)
#define RCC_CLKINT_LSIRDIEN						RCC_CLKINT_LSIRDIEN_Msk			/*!< LSI Ready Interrupt Enable */
#define RCC_CLKINT_LSERDIEN_Pos					(9U)
#define RCC_CLKINT_LSERDIEN_Msk					(0x1UL << RCC_CLKINT_LSERDIEN_Pos)
#define RCC_CLKINT_LSERDIEN						RCC_CLKINT_LSERDIEN_Msk			/*!< LSE Ready Interrupt Enable */
#define RCC_CLKINT_HSIRDIEN_Pos					(10U)
#define RCC_CLKINT_HSIRDIEN_Msk					(0x1UL << RCC_CLKINT_HSIRDIEN_Pos)
#define RCC_CLKINT_HSIRDIEN						RCC_CLKINT_HSIRDIEN_Msk			/*!< HSI Ready Interrupt Enable */
#define RCC_CLKINT_HSERDIEN_Pos					(11U)
#define RCC_CLKINT_HSERDIEN_Msk					(0x1UL << RCC_CLKINT_HSERDIEN_Pos)
#define RCC_CLKINT_HSERDIEN						RCC_CLKINT_HSERDIEN_Msk			/*!< HSE Ready Interrupt Enable */
#define RCC_CLKINT_PLLRDIEN_Pos					(12U)
#define RCC_CLKINT_PLLRDIEN_Msk					(0x1UL << RCC_CLKINT_PLLRDIEN_Pos)
#define RCC_CLKINT_PLLRDIEN						RCC_CLKINT_PLLRDIEN_Msk			/*!< PLL Ready Interrupt Enable */
#define RCC_CLKINT_LSIRDICLR_Pos				(16U)
#define RCC_CLKINT_LSIRDICLR_Msk				(0x1UL << RCC_CLKINT_LSIRDICLR_Pos)
#define RCC_CLKINT_LSIRDICLR					RCC_CLKINT_LSIRDICLR_Msk		/*!< LSI Ready Interrupt Clear */
#define RCC_CLKINT_LSERDICLR_Pos				(17U)
#define RCC_CLKINT_LSERDICLR_Msk				(0x1UL << RCC_CLKINT_LSERDICLR_Pos)
#define RCC_CLKINT_LSERDICLR					RCC_CLKINT_LSERDICLR_Msk		/*!< LSE Ready Interrupt Clear */
#define RCC_CLKINT_HSIRDICLR_Pos				(18U)
#define RCC_CLKINT_HSIRDICLR_Msk				(0x1UL << RCC_CLKINT_HSIRDICLR_Pos)
#define RCC_CLKINT_HSIRDICLR					RCC_CLKINT_HSIRDICLR_Msk		/*!< HSI Ready Interrupt Clear */
#define RCC_CLKINT_HSERDICLR_Pos				(19U)
#define RCC_CLKINT_HSERDICLR_Msk				(0x1UL << RCC_CLKINT_HSERDICLR_Pos)
#define RCC_CLKINT_HSERDICLR					RCC_CLKINT_HSERDICLR_Msk		/*!< HSE Ready Interrupt Clear */
#define RCC_CLKINT_PLLRDICLR_Pos				(20U)
#define RCC_CLKINT_PLLRDICLR_Msk				(0x1UL << RCC_CLKINT_PLLRDICLR_Pos)
#define RCC_CLKINT_PLLRDICLR					RCC_CLKINT_PLLRDICLR_Msk		/*!< PLL Ready Interrupt Clear */
#define RCC_CLKINT_CLKSSICLR_Pos				(23U)
#define RCC_CLKINT_CLKSSICLR_Msk				(0x1UL << RCC_CLKINT_CLKSSICLR_Pos)
#define RCC_CLKINT_CLKSSICLR					RCC_CLKINT_CLKSSICLR_Msk		/*!< Clock Security System Interrupt Clear */

/*****************  Bit definition for RCC_APB2PRST register  *****************/
#define RCC_APB2PRST_AFIORST_Pos				(0U)
#define RCC_APB2PRST_AFIORST_Msk				(0x1UL << RCC_APB2PRST_AFIORST_Pos)
#define RCC_APB2PRST_AFIORST					RCC_APB2PRST_AFIORST_Msk		/*!< Alternate Function I/O reset */
#define RCC_APB2PRST_IOPAMPRST_Pos				(2U)
#define RCC_APB2PRST_IOPAMPRST_Msk				(0x1UL << RCC_APB2PRST_IOPAMPRST_Pos)
#define RCC_APB2PRST_IOPAMPRST					RCC_APB2PRST_IOPAMPRST_Msk		/*!< I/O port A reset */
#define RCC_APB2PRST_IOPBRST_Pos				(3U)
#define RCC_APB2PRST_IOPBRST_Msk				(0x1UL << RCC_APB2PRST_IOPBRST_Pos)
#define RCC_APB2PRST_IOPBRST					RCC_APB2PRST_IOPBRST_Msk		/*!< I/O port B reset */
#define RCC_APB2PRST_IOPCRST_Pos				(4U)
#define RCC_APB2PRST_IOPCRST_Msk				(0x1UL << RCC_APB2PRST_IOPCRST_Pos)
#define RCC_APB2PRST_IOPCRST					RCC_APB2PRST_IOPCRST_Msk		/*!< I/O port C reset */
#define RCC_APB2PRST_IOPDRST_Pos				(5U)
#define RCC_APB2PRST_IOPDRST_Msk				(0x1UL << RCC_APB2PRST_IOPDRST_Pos)
#define RCC_APB2PRST_IOPDRST					RCC_APB2PRST_IOPDRST_Msk		/*!< I/O port D reset */
#define RCC_APB2PRST_IOPERST_Pos				(6U)
#define RCC_APB2PRST_IOPERST_Msk				(0x1UL << RCC_APB2PRST_IOPERST_Pos)
#define RCC_APB2PRST_IOPERST					RCC_APB2PRST_IOPERST_Msk		/*!< I/O port E reset */
#define RCC_APB2PRST_IOPFRST_Pos				(7U)
#define RCC_APB2PRST_IOPFRST_Msk				(0x1UL << RCC_APB2PRST_IOPFRST_Pos)
#define RCC_APB2PRST_IOPFRST					RCC_APB2PRST_IOPFRST_Msk		/*!< I/O port F reset */
#define RCC_APB2PRST_IOPGRST_Pos				(8U)
#define RCC_APB2PRST_IOPGRST_Msk				(0x1UL << RCC_APB2PRST_IOPGRST_Pos)
#define RCC_APB2PRST_IOPGRST					RCC_APB2PRST_IOPGRST_Msk		/*!< I/O port G reset */
#define RCC_APB2PRST_TIM1RST_Pos				(11U)
#define RCC_APB2PRST_TIM1RST_Msk				(0x1UL << RCC_APB2PRST_TIM1RST_Pos)
#define RCC_APB2PRST_TIM1RST					RCC_APB2PRST_TIM1RST_Msk		/*!< TIM1 Timer reset */
#define RCC_APB2PRST_SPI1RST_Pos				(12U)
#define RCC_APB2PRST_SPI1RST_Msk				(0x1UL << RCC_APB2PRST_SPI1RST_Pos)
#define RCC_APB2PRST_SPI1RST					RCC_APB2PRST_SPI1RST_Msk		/*!< SPI 1 reset */
#define RCC_APB2PRST_TIM8RST_Pos				(13U)
#define RCC_APB2PRST_TIM8RST_Msk				(0x1UL << RCC_APB2PRST_TIM8RST_Pos)
#define RCC_APB2PRST_TIM8RST					RCC_APB2PRST_TIM8RST_Msk		/*!< TIM8 Timer reset */
#define RCC_APB2PRST_USART1RST_Pos				(14U)
#define RCC_APB2PRST_USART1RST_Msk				(0x1UL << RCC_APB2PRST_USART1RST_Pos)
#define RCC_APB2PRST_USART1RST					RCC_APB2PRST_USART1RST_Msk		/*!< USART1 reset */
#define RCC_APB2PRST_UART6RST_Pos				(17U)
#define RCC_APB2PRST_UART6RST_Msk				(0x1UL << RCC_APB2PRST_UART6RST_Pos)
#define RCC_APB2PRST_UART6RST					RCC_APB2PRST_UART6RST_Msk		/*!< UART6 reset */
#define RCC_APB2PRST_UART7RST_Pos				(18U)
#define RCC_APB2PRST_UART7RST_Msk				(0x1UL << RCC_APB2PRST_UART7RST_Pos)
#define RCC_APB2PRST_UART7RST					RCC_APB2PRST_UART7RST_Msk		/*!< UART7 reset */
#define RCC_APB2PRST_I2C3RST_Pos				(19U)
#define RCC_APB2PRST_I2C3RST_Msk				(0x1UL << RCC_APB2PRST_I2C3RST_Pos)
#define RCC_APB2PRST_I2C3RST					RCC_APB2PRST_I2C3RST_Msk		/*!< I2C3 reset */
#define RCC_APB2PRST_I2C4RST_Pos				(20U)
#define RCC_APB2PRST_I2C4RST_Msk				(0x1UL << RCC_APB2PRST_I2C4RST_Pos)
#define RCC_APB2PRST_I2C4RST					RCC_APB2PRST_I2C4RST_Msk		/*!< I2C4 reset */

/*****************  Bit definition for RCC_APB1PRST register  *****************/
#define RCC_APB1PRST_TIM2RST_Pos				(0U)
#define RCC_APB1PRST_TIM2RST_Msk				(0x1UL << RCC_APB1PRST_TIM2RST_Pos)
#define RCC_APB1PRST_TIM2RST					RCC_APB1PRST_TIM2RST_Msk		/*!< Timer 2 reset */
#define RCC_APB1PRST_TIM3RST_Pos				(1U)
#define RCC_APB1PRST_TIM3RST_Msk				(0x1UL << RCC_APB1PRST_TIM3RST_Pos)
#define RCC_APB1PRST_TIM3RST					RCC_APB1PRST_TIM3RST_Msk		/*!< Timer 3 reset */
#define RCC_APB1PRST_TIM4RST_Pos				(2U)
#define RCC_APB1PRST_TIM4RST_Msk				(0x1UL << RCC_APB1PRST_TIM4RST_Pos)
#define RCC_APB1PRST_TIM4RST					RCC_APB1PRST_TIM4RST_Msk		/*!< Timer 4 reset */
#define RCC_APB1PRST_TIM5RST_Pos				(3U)
#define RCC_APB1PRST_TIM5RST_Msk				(0x1UL << RCC_APB1PRST_TIM5RST_Pos)
#define RCC_APB1PRST_TIM5RST					RCC_APB1PRST_TIM5RST_Msk		/*!< Timer 5 reset */
#define RCC_APB1PRST_TIM6RST_Pos				(4U)
#define RCC_APB1PRST_TIM6RST_Msk				(0x1UL << RCC_APB1PRST_TIM6RST_Pos)
#define RCC_APB1PRST_TIM6RST					RCC_APB1PRST_TIM6RST_Msk		/*!< Timer 6 reset */
#define RCC_APB1PRST_TIM7RST_Pos				(5U)
#define RCC_APB1PRST_TIM7RST_Msk				(0x1UL << RCC_APB1PRST_TIM7RST_Pos)
#define RCC_APB1PRST_TIM7RST					RCC_APB1PRST_TIM7RST_Msk		/*!< Timer 7 reset */
#define RCC_APB1PRST_TSCRST_Pos					(10U)
#define RCC_APB1PRST_TSCRST_Msk					(0x1UL << RCC_APB1PRST_TSCRST_Pos)
#define RCC_APB1PRST_TSCRST						RCC_APB1PRST_TSCRST_Msk			/*!< TSC reset */
#define RCC_APB1PRST_WWDGRST_Pos				(11U)
#define RCC_APB1PRST_WWDGRST_Msk				(0x1UL << RCC_APB1PRST_WWDGRST_Pos)
#define RCC_APB1PRST_WWDGRST					RCC_APB1PRST_WWDGRST_Msk		/*!< Window Watchdog reset */
#define RCC_APB1PRST_SPI2RST_Pos				(14U)
#define RCC_APB1PRST_SPI2RST_Msk				(0x1UL << RCC_APB1PRST_SPI2RST_Pos)
#define RCC_APB1PRST_SPI2RST					RCC_APB1PRST_SPI2RST_Msk		/*!< SPI 2 reset */
#define RCC_APB1PRST_SPI3RST_Pos				(15U)
#define RCC_APB1PRST_SPI3RST_Msk				(0x1UL << RCC_APB1PRST_SPI3RST_Pos)
#define RCC_APB1PRST_SPI3RST					RCC_APB1PRST_SPI3RST_Msk		/*!< SPI 3 reset */
#define RCC_APB1PRST_USART2RST_Pos				(17U)
#define RCC_APB1PRST_USART2RST_Msk				(0x1UL << RCC_APB1PRST_USART2RST_Pos)
#define RCC_APB1PRST_USART2RST					RCC_APB1PRST_USART2RST_Msk		/*!< USART 2 reset */
#define RCC_APB1PRST_USART3RST_Pos				(18U)
#define RCC_APB1PRST_USART3RST_Msk				(0x1UL << RCC_APB1PRST_USART3RST_Pos)
#define RCC_APB1PRST_USART3RST					RCC_APB1PRST_USART3RST_Msk		/*!< USART 3 reset */
#define RCC_APB1PRST_UART4RST_Pos				(19U)
#define RCC_APB1PRST_UART4RST_Msk				(0x1UL << RCC_APB1PRST_UART4RST_Pos)
#define RCC_APB1PRST_UART4RST					RCC_APB1PRST_UART4RST_Msk		/*!< UART 4 reset */
#define RCC_APB1PRST_UART5RST_Pos				(20U)
#define RCC_APB1PRST_UART5RST_Msk				(0x1UL << RCC_APB1PRST_UART5RST_Pos)
#define RCC_APB1PRST_UART5RST					RCC_APB1PRST_UART5RST_Msk		/*!< UART 5 reset */
#define RCC_APB1PRST_I2C1RST_Pos				(21U)
#define RCC_APB1PRST_I2C1RST_Msk				(0x1UL << RCC_APB1PRST_I2C1RST_Pos)
#define RCC_APB1PRST_I2C1RST					RCC_APB1PRST_I2C1RST_Msk		/*!< I2C 1 reset */
#define RCC_APB1PRST_I2C2RST_Pos				(22U)
#define RCC_APB1PRST_I2C2RST_Msk				(0x1UL << RCC_APB1PRST_I2C2RST_Pos)
#define RCC_APB1PRST_I2C2RST					RCC_APB1PRST_I2C2RST_Msk		/*!< I2C 2 reset */
#define RCC_APB1PRST_RNGCRST_Pos				(23U)
#define RCC_APB1PRST_RNGCRST_Msk				(0x1UL << RCC_APB1PRST_RNGCRST_Pos)
#define RCC_APB1PRST_RNGCRST					RCC_APB1PRST_RNGCRST_Msk		/*!< RNGC reset */
#define RCC_APB1PRST_CAN1RST_Pos				(25U)
#define RCC_APB1PRST_CAN1RST_Msk				(0x1UL << RCC_APB1PRST_CAN1RST_Pos)
#define RCC_APB1PRST_CAN1RST					RCC_APB1PRST_CAN1RST_Msk		/*!< CAN 1 reset */
#define RCC_APB1PRST_CAN2RST_Pos				(26U)
#define RCC_APB1PRST_CAN2RST_Msk				(0x1UL << RCC_APB1PRST_CAN2RST_Pos)
#define RCC_APB1PRST_CAN2RST					RCC_APB1PRST_CAN2RST_Msk		/*!< CAN 2 reset */
#define RCC_APB1PRST_BKPRST_Pos					(27U)
#define RCC_APB1PRST_BKPRST_Msk					(0x1UL << RCC_APB1PRST_BKPRST_Pos)
#define RCC_APB1PRST_BKPRST						RCC_APB1PRST_BKPRST_Msk			/*!< Backup interface reset */
#define RCC_APB1PRST_PWRRST_Pos					(28U)
#define RCC_APB1PRST_PWRRST_Msk					(0x1UL << RCC_APB1PRST_PWRRST_Pos)
#define RCC_APB1PRST_PWRRST						RCC_APB1PRST_PWRRST_Msk			/*!< Power interface reset */
#define RCC_APB1PRST_DACRST_Pos					(29U)
#define RCC_APB1PRST_DACRST_Msk					(0x1UL << RCC_APB1PRST_DACRST_Pos)
#define RCC_APB1PRST_DACRST						RCC_APB1PRST_DACRST_Msk			/*!< DAC interface reset */

/****************  Bit definition for RCC_AHBPCLKEN register  *****************/
#define RCC_AHBPCLKEN_DMA1EN_Pos				(0U)
#define RCC_AHBPCLKEN_DMA1EN_Msk				(0x1UL << RCC_AHBPCLKEN_DMA1EN_Pos)		/*!< 0x00000001 */
#define RCC_AHBPCLKEN_DMA1EN					RCC_AHBPCLKEN_DMA1EN_Msk		/*!< DMA1 clock enable */
#define RCC_AHBPCLKEN_DMA2EN_Pos				(1U)
#define RCC_AHBPCLKEN_DMA2EN_Msk				(0x1UL << RCC_AHBPCLKEN_DMA2EN_Pos)		/*!< 0x00000002 */
#define RCC_AHBPCLKEN_DMA2EN					RCC_AHBPCLKEN_DMA2EN_Msk		/*!< DMA2 clock enable */
#define RCC_AHBPCLKEN_SRAMEN_Pos				(2U)
#define RCC_AHBPCLKEN_SRAMEN_Msk				(0x1UL << RCC_AHBPCLKEN_SRAMEN_Pos)		/*!< 0x00000004 */
#define RCC_AHBPCLKEN_SRAMEN					RCC_AHBPCLKEN_SRAMEN_Msk		/*!< SRAM interface clock enable */
#define RCC_AHBPCLKEN_FLITFEN_Pos				(4U)
#define RCC_AHBPCLKEN_FLITFEN_Msk				(0x1UL << RCC_AHBPCLKEN_FLITFEN_Pos)	/*!< 0x00000010 */
#define RCC_AHBPCLKEN_FLITFEN					RCC_AHBPCLKEN_FLITFEN_Msk		/*!< FLITF clock enable */
#define RCC_AHBPCLKEN_CRCEN_Pos					(6U)
#define RCC_AHBPCLKEN_CRCEN_Msk					(0x1UL << RCC_AHBPCLKEN_CRCEN_Pos)		/*!< 0x00000040 */
#define RCC_AHBPCLKEN_CRCEN						RCC_AHBPCLKEN_CRCEN_Msk			/*!< CRC clock enable */
#define RCC_AHBPCLKEN_RNGCEN_Pos				(9U)
#define RCC_AHBPCLKEN_RNGCEN_Msk				(0x1UL << RCC_AHBPCLKEN_RNGCEN_Pos)		/*!< 0x00000200 */
#define RCC_AHBPCLKEN_RNGCEN					RCC_AHBPCLKEN_RNGCEN_Msk		/*!< RNGC clock enable */
#define RCC_AHBPCLKEN_SACEN_Pos					(11U)
#define RCC_AHBPCLKEN_SACEN_Msk					(0x1UL << RCC_AHBPCLKEN_SACEN_Pos)		/*!< 0x00000800 */
#define RCC_AHBPCLKEN_SACEN						RCC_AHBPCLKEN_SACEN_Msk			/*!< SAC clock enable */
#define RCC_AHBPCLKEN_ADC1EN_Pos				(12U)
#define RCC_AHBPCLKEN_ADC1EN_Msk				(0x1UL << RCC_AHBPCLKEN_ADC1EN_Pos)		/*!< 0x00001000 */
#define RCC_AHBPCLKEN_ADC1EN					RCC_AHBPCLKEN_ADC1EN_Msk		/*!< ADC1 clock enable */
#define RCC_AHBPCLKEN_ADC2EN_Pos				(13U)
#define RCC_AHBPCLKEN_ADC2EN_Msk				(0x1UL << RCC_AHBPCLKEN_ADC2EN_Pos)		/*!< 0x00002000 */
#define RCC_AHBPCLKEN_ADC2EN					RCC_AHBPCLKEN_ADC2EN_Msk		/*!< ADC2 clock enable */
#define RCC_AHBPCLKEN_ADC3EN_Pos				(14U)
#define RCC_AHBPCLKEN_ADC3EN_Msk				(0x1UL << RCC_AHBPCLKEN_ADC3EN_Pos)		/*!< 0x00004000 */
#define RCC_AHBPCLKEN_ADC3EN					RCC_AHBPCLKEN_ADC3EN_Msk		/*!< ADC3 clock enable */
#define RCC_AHBPCLKEN_ADC4EN_Pos				(15U)
#define RCC_AHBPCLKEN_ADC4EN_Msk				(0x1UL << RCC_AHBPCLKEN_ADC4EN_Pos)		/*!< 0x00008000 */
#define RCC_AHBPCLKEN_ADC4EN					RCC_AHBPCLKEN_ADC4EN_Msk		/*!< ADC4 clock enable */
#define RCC_AHBPCLKEN_QSPIEN_Pos				(17U)
#define RCC_AHBPCLKEN_QSPIEN_Msk				(0x1UL << RCC_AHBPCLKEN_QSPIEN_Pos)		/*!< 0x00020000 */
#define RCC_AHBPCLKEN_QSPIEN					RCC_AHBPCLKEN_QSPIEN_Msk		/*!< QSPI clock enable */

/****************  Bit definition for RCC_APB2PCLKEN register  ****************/
#define RCC_APB2PCLKEN_AFIOEN_Pos				(0U)
#define RCC_APB2PCLKEN_AFIOEN_Msk				(0x1UL << RCC_APB2PCLKEN_AFIOEN_Pos)	/*!< 0x00000001 */
#define RCC_APB2PCLKEN_AFIOEN					RCC_APB2PCLKEN_AFIOEN_Msk		/*!< Alternate Function I/O clock enable */
#define RCC_APB2PCLKEN_IOPAEN_Pos				(2U)
#define RCC_APB2PCLKEN_IOPAEN_Msk				(0x1UL << RCC_APB2PCLKEN_IOPAEN_Pos)	/*!< 0x00000004 */
#define RCC_APB2PCLKEN_IOPAEN					RCC_APB2PCLKEN_IOPAEN_Msk		/*!< I/O port A clock enable */
#define RCC_APB2PCLKEN_IOPBEN_Pos				(3U)
#define RCC_APB2PCLKEN_IOPBEN_Msk				(0x1UL << RCC_APB2PCLKEN_IOPBEN_Pos)	/*!< 0x00000008 */
#define RCC_APB2PCLKEN_IOPBEN					RCC_APB2PCLKEN_IOPBEN_Msk		/*!< I/O port B clock enable */
#define RCC_APB2PCLKEN_IOPCEN_Pos				(4U)
#define RCC_APB2PCLKEN_IOPCEN_Msk				(0x1UL << RCC_APB2PCLKEN_IOPCEN_Pos)	/*!< 0x00000010 */
#define RCC_APB2PCLKEN_IOPCEN					RCC_APB2PCLKEN_IOPCEN_Msk		/*!< I/O port C clock enable */
#define RCC_APB2PCLKEN_IOPDEN_Pos				(5U)
#define RCC_APB2PCLKEN_IOPDEN_Msk				(0x1UL << RCC_APB2PCLKEN_IOPDEN_Pos)	/*!< 0x00000020 */
#define RCC_APB2PCLKEN_IOPDEN					RCC_APB2PCLKEN_IOPDEN_Msk		/*!< I/O port D clock enable */
#define RCC_APB2PCLKEN_IOPEEN_Pos				(6U)
#define RCC_APB2PCLKEN_IOPEEN_Msk				(0x1UL << RCC_APB2PCLKEN_IOPEEN_Pos)	/*!< 0x00000040 */
#define RCC_APB2PCLKEN_IOPEEN					RCC_APB2PCLKEN_IOPEEN_Msk		/*!< I/O port E clock enable */
#define RCC_APB2PCLKEN_IOPFEN_Pos				(7U)
#define RCC_APB2PCLKEN_IOPFEN_Msk				(0x1UL << RCC_APB2PCLKEN_IOPFEN_Pos)	/*!< 0x00000080 */
#define RCC_APB2PCLKEN_IOPFEN					RCC_APB2PCLKEN_IOPFEN_Msk		/*!< I/O port F clock enable */
#define RCC_APB2PCLKEN_IOPGEN_Pos				(8U)
#define RCC_APB2PCLKEN_IOPGEN_Msk				(0x1UL << RCC_APB2PCLKEN_IOPGEN_Pos)	/*!< 0x00000100 */
#define RCC_APB2PCLKEN_IOPGEN					RCC_APB2PCLKEN_IOPGEN_Msk		/*!< I/O port G clock enable */
#define RCC_APB2PCLKEN_TIM1EN_Pos				(11U)
#define RCC_APB2PCLKEN_TIM1EN_Msk				(0x1UL << RCC_APB2PCLKEN_TIM1EN_Pos)	/*!< 0x00000800 */
#define RCC_APB2PCLKEN_TIM1EN					RCC_APB2PCLKEN_TIM1EN_Msk		/*!< TIM1 Timer clock enable */
#define RCC_APB2PCLKEN_SPI1EN_Pos				(12U)
#define RCC_APB2PCLKEN_SPI1EN_Msk				(0x1UL << RCC_APB2PCLKEN_SPI1EN_Pos)	/*!< 0x00001000 */
#define RCC_APB2PCLKEN_SPI1EN					RCC_APB2PCLKEN_SPI1EN_Msk		/*!< SPI1 clock enable */
#define RCC_APB2PCLKEN_TIM8EN_Pos				(13U)
#define RCC_APB2PCLKEN_TIM8EN_Msk				(0x1UL << RCC_APB2PCLKEN_TIM8EN_Pos)	/*!< 0x00002000 */
#define RCC_APB2PCLKEN_TIM8EN					RCC_APB2PCLKEN_TIM8EN_Msk		/*!< TIM8 Timer clock enable */
#define RCC_APB2PCLKEN_USART1EN_Pos				(14U)
#define RCC_APB2PCLKEN_USART1EN_Msk				(0x1UL << RCC_APB2PCLKEN_USART1EN_Pos)	/*!< 0x00004000 */
#define RCC_APB2PCLKEN_USART1EN					RCC_APB2PCLKEN_USART1EN_Msk		/*!< USART1 clock enable */
#define RCC_APB2PCLKEN_UART6EN_Pos				(17U)
#define RCC_APB2PCLKEN_UART6EN_Msk				(0x1UL << RCC_APB2PCLKEN_UART6EN_Pos)	/*!< 0x00020000 */
#define RCC_APB2PCLKEN_UART6EN					RCC_APB2PCLKEN_UART6EN_Msk		/*!< UART6 clock enable */
#define RCC_APB2PCLKEN_UART7EN_Pos				(18U)
#define RCC_APB2PCLKEN_UART7EN_Msk				(0x1UL << RCC_APB2PCLKEN_UART7EN_Pos)	/*!< 0x00040000 */
#define RCC_APB2PCLKEN_UART7EN					RCC_APB2PCLKEN_UART7EN_Msk		/*!< UART7 clock enable */
#define RCC_APB2PCLKEN_I2C3EN_Pos				(19U)
#define RCC_APB2PCLKEN_I2C3EN_Msk				(0x1UL << RCC_APB2PCLKEN_I2C3EN_Pos)	/*!< 0x00080000 */
#define RCC_APB2PCLKEN_I2C3EN					RCC_APB2PCLKEN_I2C3EN_Msk		/*!< I2C3 clock enable */
#define RCC_APB2PCLKEN_I2C4EN_Pos				(20U)
#define RCC_APB2PCLKEN_I2C4EN_Msk				(0x1UL << RCC_APB2PCLKEN_I2C4EN_Pos)	/*!< 0x00100000 */
#define RCC_APB2PCLKEN_I2C4EN					RCC_APB2PCLKEN_I2C4EN_Msk		/*!< I2C4 clock enable */

/****************  Bit definition for RCC_APB1PCLKEN register  ****************/
#define RCC_APB1PCLKEN_TIM2EN_Pos				(0U)
#define RCC_APB1PCLKEN_TIM2EN_Msk				(0x1UL << RCC_APB1PCLKEN_TIM2EN_Pos)		/*!< 0x00000001 */
#define RCC_APB1PCLKEN_TIM2EN					RCC_APB1PCLKEN_TIM2EN_Msk		/*!< Timer 2 clock enabled*/
#define RCC_APB1PCLKEN_TIM3EN_Pos				(1U)
#define RCC_APB1PCLKEN_TIM3EN_Msk				(0x1UL << RCC_APB1PCLKEN_TIM3EN_Pos)		/*!< 0x00000002 */
#define RCC_APB1PCLKEN_TIM3EN					RCC_APB1PCLKEN_TIM3EN_Msk		/*!< Timer 3 clock enable */
#define RCC_APB1PCLKEN_TIM4EN_Pos				(2U)
#define RCC_APB1PCLKEN_TIM4EN_Msk				(0x1UL << RCC_APB1PCLKEN_TIM4EN_Pos)		/*!< 0x00000004 */
#define RCC_APB1PCLKEN_TIM4EN					RCC_APB1PCLKEN_TIM4EN_Msk		/*!< Timer 4 clock enable */
#define RCC_APB1PCLKEN_TIM5EN_Pos				(3U)
#define RCC_APB1PCLKEN_TIM5EN_Msk				(0x1UL << RCC_APB1PCLKEN_TIM5EN_Pos)		/*!< 0x00000008 */
#define RCC_APB1PCLKEN_TIM5EN					RCC_APB1PCLKEN_TIM5EN_Msk		/*!< Timer 5 clock enable */
#define RCC_APB1PCLKEN_TIM6EN_Pos				(4U)
#define RCC_APB1PCLKEN_TIM6EN_Msk				(0x1UL << RCC_APB1PCLKEN_TIM6EN_Pos)		/*!< 0x00000010 */
#define RCC_APB1PCLKEN_TIM6EN					RCC_APB1PCLKEN_TIM6EN_Msk		/*!< Timer 6 clock enable */
#define RCC_APB1PCLKEN_TIM7EN_Pos				(5U)
#define RCC_APB1PCLKEN_TIM7EN_Msk				(0x1UL << RCC_APB1PCLKEN_TIM7EN_Pos)		/*!< 0x00000020 */
#define RCC_APB1PCLKEN_TIM7EN					RCC_APB1PCLKEN_TIM7EN_Msk		/*!< Timer 7 clock enable */
#define RCC_APB1PCLKEN_COMPEN_Pos				(6U)
#define RCC_APB1PCLKEN_COMPEN_Msk				(0x1UL << RCC_APB1PCLKEN_COMPEN_Pos)		/*!< 0x00000040 */
#define RCC_APB1PCLKEN_COMPEN					RCC_APB1PCLKEN_COMPEN_Msk		/*!< COMP clock enable */
#define RCC_APB1PCLKEN_COMPFILTEN_Pos			(7U)
#define RCC_APB1PCLKEN_COMPFILTEN_Msk			(0x1UL << RCC_APB1PCLKEN_COMPFILTEN_Pos)	/*!< 0x00000080 */
#define RCC_APB1PCLKEN_COMPFILTEN				RCC_APB1PCLKEN_COMPFILTEN_Msk	/*!< COMPFILT clock enable */
#define RCC_APB1PCLKEN_TSCEN_Pos				(10U)
#define RCC_APB1PCLKEN_TSCEN_Msk				(0x1UL << RCC_APB1PCLKEN_TSCEN_Pos)			/*!< 0x00000400 */
#define RCC_APB1PCLKEN_TSCEN					RCC_APB1PCLKEN_TSCEN_Msk		/*!< TSC clock enable */
#define RCC_APB1PCLKEN_WWDGEN_Pos				(11U)
#define RCC_APB1PCLKEN_WWDGEN_Msk				(0x1UL << RCC_APB1PCLKEN_WWDGEN_Pos)		/*!< 0x00000800 */
#define RCC_APB1PCLKEN_WWDGEN					RCC_APB1PCLKEN_WWDGEN_Msk		/*!< Window Watchdog clock enable */
#define RCC_APB1PCLKEN_SPI2EN_Pos				(14U)
#define RCC_APB1PCLKEN_SPI2EN_Msk				(0x1UL << RCC_APB1PCLKEN_SPI2EN_Pos)		/*!< 0x00004000 */
#define RCC_APB1PCLKEN_SPI2EN					RCC_APB1PCLKEN_SPI2EN_Msk		/*!< SPI 2 clock enable */
#define RCC_APB1PCLKEN_SPI3EN_Pos				(15U)
#define RCC_APB1PCLKEN_SPI3EN_Msk				(0x1UL << RCC_APB1PCLKEN_SPI3EN_Pos)		/*!< 0x00008000 */
#define RCC_APB1PCLKEN_SPI3EN					RCC_APB1PCLKEN_SPI3EN_Msk		/*!< SPI 3 clock enable */
#define RCC_APB1PCLKEN_USART2EN_Pos				(17U)
#define RCC_APB1PCLKEN_USART2EN_Msk				(0x1UL << RCC_APB1PCLKEN_USART2EN_Pos)		/*!< 0x00020000 */
#define RCC_APB1PCLKEN_USART2EN   				RCC_APB1PCLKEN_USART2EN_Msk		/*!< USART 2 clock enable */
#define RCC_APB1PCLKEN_USART3EN_Pos				(18U)
#define RCC_APB1PCLKEN_USART3EN_Msk				(0x1UL << RCC_APB1PCLKEN_USART3EN_Pos)		/*!< 0x00040000 */
#define RCC_APB1PCLKEN_USART3EN					RCC_APB1PCLKEN_USART3EN_Msk		/*!< USART 3 clock enable */
#define RCC_APB1PCLKEN_UART4EN_Pos				(19U)
#define RCC_APB1PCLKEN_UART4EN_Msk				(0x1UL << RCC_APB1PCLKEN_UART4EN_Pos)		/*!< 0x00080000 */
#define RCC_APB1PCLKEN_UART4EN					RCC_APB1PCLKEN_UART4EN_Msk		/*!< UART 4 clock enable */
#define RCC_APB1PCLKEN_UART5EN_Pos				(20U)
#define RCC_APB1PCLKEN_UART5EN_Msk				(0x1UL << RCC_APB1PCLKEN_UART5EN_Pos)		/*!< 0x00100000 */
#define RCC_APB1PCLKEN_UART5EN					RCC_APB1PCLKEN_UART5EN_Msk		/*!< UART 5 clock enable */
#define RCC_APB1PCLKEN_I2C1EN_Pos				(21U)
#define RCC_APB1PCLKEN_I2C1EN_Msk				(0x1UL << RCC_APB1PCLKEN_I2C1EN_Pos)		/*!< 0x00200000 */
#define RCC_APB1PCLKEN_I2C1EN					RCC_APB1PCLKEN_I2C1EN_Msk		/*!< I2C 1 clock enable */
#define RCC_APB1PCLKEN_I2C2EN_Pos				(22U)
#define RCC_APB1PCLKEN_I2C2EN_Msk				(0x1UL << RCC_APB1PCLKEN_I2C2EN_Pos)		/*!< 0x00400000 */
#define RCC_APB1PCLKEN_I2C2EN					RCC_APB1PCLKEN_I2C2EN_Msk		/*!< I2C 2 clock enable */
#define RCC_APB1PCLKEN_RNGCEN_Pos				(23U)
#define RCC_APB1PCLKEN_RNGCEN_Msk				(0x1UL << RCC_APB1PCLKEN_RNGCEN_Pos)		/*!< 0x00800000 */
#define RCC_APB1PCLKEN_RNGCEN					RCC_APB1PCLKEN_RNGCEN_Msk		/*!< RNGC clock enbale */
#define RCC_APB1PCLKEN_CAN1EN_Pos				(25U)
#define RCC_APB1PCLKEN_CAN1EN_Msk				(0x1UL << RCC_APB1PCLKEN_CAN1EN_Pos)		/*!< 0x02000000 */
#define RCC_APB1PCLKEN_CAN1EN					RCC_APB1PCLKEN_CAN1EN_Msk		/*!< CAN1 clock enable */
#define RCC_APB1PCLKEN_CAN2EN_Pos				(26U)
#define RCC_APB1PCLKEN_CAN2EN_Msk				(0x1UL << RCC_APB1PCLKEN_CAN2EN_Pos)		/*!< 0x04000000 */
#define RCC_APB1PCLKEN_CAN2EN					RCC_APB1PCLKEN_CAN2EN_Msk		/*!< CAN2 clock enable */
#define RCC_APB1PCLKEN_BKPEN_Pos				(27U)
#define RCC_APB1PCLKEN_BKPEN_Msk				(0x1UL << RCC_APB1PCLKEN_BKPEN_Pos)			/*!< 0x08000000 */
#define RCC_APB1PCLKEN_BKPEN					RCC_APB1PCLKEN_BKPEN_Msk		/*!< Backup interface clock enable */
#define RCC_APB1PCLKEN_PWREN_Pos				(28U)
#define RCC_APB1PCLKEN_PWREN_Msk				(0x1UL << RCC_APB1PCLKEN_PWREN_Pos)			/*!< 0x10000000 */
#define RCC_APB1PCLKEN_PWREN					RCC_APB1PCLKEN_PWREN_Msk		/*!< Power interface clock enable */
#define RCC_APB1PCLKEN_DACEN_Pos				(29U)
#define RCC_APB1PCLKEN_DACEN_Msk				(0x1uL << RCC_APB1PCLKEN_DACEN_Pos)			/*!< 0x20000000 */
#define RCC_APB1PCLKEN_DACEN					RCC_APB1PCLKEN_DACEN_Msk		/*!< DAC interface clock enable */
#define RCC_APB1PCLKEN_OPAMPEN_Pos				(31U)
#define RCC_APB1PCLKEN_OPAMPEN_Msk				(0x1UL << RCC_APB1ENR_OPAMPEN_Pos)			/*!< 0x80000000 */
#define RCC_APB1PCLKEN_OPAMPEN					RCC_APB1ENR_OPAMPEN_Msk			/*!< OPAMP interface clock enable */

/******************  Bit definition for RCC_BDCTRL register  ******************/
#define RCC_BDCTRL_LSEEN_Pos					(0U)
#define RCC_BDCTRL_LSEEN_Msk					(0x1UL << RCC_BDCTRL_LSEEN_Pos)
#define RCC_BDCTRL_LSEEN						RCC_BDCTRL_LSEEN_Msk			/*!< External Low Speed oscillator enable */
#define RCC_BDCTRL_LSERD_Pos					(1U)
#define RCC_BDCTRL_LSERD_Msk					(0x1UL << RCC_BDCTRL_LSERD_Pos)
#define RCC_BDCTRL_LSERD						RCC_BDCTRL_LSERD_Msk			/*!< External Low Speed oscillator Ready */
#define RCC_BDCTRL_LSEBP_Pos					(2U)
#define RCC_BDCTRL_LSEBP_Msk					(0x1UL << RCC_BDCTRL_LSEBP_Pos)
#define RCC_BDCTRL_LSEBP						RCC_BDCTRL_LSEBP_Msk			/*!< External Low Speed oscillator Bypass */

/*!< RTC congiguration */
#define RCC_BDCTRL_RTCSEL_Pos					(8U)
#define RCC_BDCTRL_RTCSEL_Msk					(0x3UL << RCC_BDCTRL_RTCSEL_Pos)
#define RCC_BDCTRL_RTCSEL						RCC_BDCTRL_RTCSEL_Msk			/*!< RTCSEL[1:0] bits (RTC clock source selection) */
#define RCC_BDCTRL_RTCSEL_0						((uint32_t)0x00000100)			/*!< Bit 0 */
#define RCC_BDCTRL_RTCSEL_1						((uint32_t)0x00000200)			/*!< Bit 1 */

#define RCC_BDCTRL_RTCSEL_NOCLOCK				((uint32_t) 0x00000000)			/*!< No clock */
#define RCC_BDCTRL_RTCSEL_LSE					((uint32_t) 0x00000100)			/*!< LSE oscillator clock used as RTC clock */
#define RCC_BDCTRL_RTCSEL_LSI					((uint32_t) 0x00000200)			/*!< LSI oscillator clock used as RTC clock */
#define RCC_BDCTRL_RTCSEL_HSE					((uint32_t) 0x00000300)			/*!< HSE oscillator clock divided by 128 used as RTC clock */

#define RCC_BDCTRL_RTCEN_Pos					(15U)
#define RCC_BDCTRL_RTCEN_Msk					(0x1UL << RCC_BDCTRL_RTCEN_Pos)
#define RCC_BDCTRL_RTCEN						RCC_BDCTRL_RTCEN_Msk			/*!< RTC clock enable */
#define RCC_BDCTRL_BDSFTRST_Pos					(16U)
#define RCC_BDCTRL_BDSFTRST_Msk					(0x1UL << RCC_BDCTRL_BDSFTRST_Pos)
#define RCC_BDCTRL_BDSFTRST						RCC_BDCTRL_BDSFTRST_Msk			/*!< Backup domain software reset */

/*****************  Bit definition for RCC_CTRLSTS register  ******************/
#define RCC_CTRLSTS_LSIEN_Pos					(0U)
#define RCC_CTRLSTS_LSIEN_Msk					(0x1UL << RCC_CTRLSTS_LSIEN_Pos)
#define RCC_CTRLSTS_LSIEN						RCC_CTRLSTS_LSIEN_Msk			/*!< Internal Low Speed oscillator enable */
#define RCC_CTRLSTS_LSIRD_Pos					(1U)
#define RCC_CTRLSTS_LSIRD_Msk					(0x1UL << RCC_CTRLSTS_LSIRD_Pos)
#define RCC_CTRLSTS_LSIRD						RCC_CTRLSTS_LSIRD_Msk			/*!< Internal Low Speed oscillator Ready */
#define RCC_CTRLSTS_BORRSTF_Pos					(19U)
#define RCC_CTRLSTS_BORRSTF_Msk					(0x1UL << RCC_CTRLSTS_BORRSTF_Pos)
#define RCC_CTRLSTS_BORRSTF						RCC_CTRLSTS_BORRSTF_Msk			/*!< BOR reset flag */
#define RCC_CTRLSTS_RETEMCF_Pos					(20U)
#define RCC_CTRLSTS_RETEMCF_Msk					(0x1UL << RCC_CTRLSTS_RETEMCF_Pos)
#define RCC_CTRLSTS_RETEMCF						RCC_CTRLSTS_RETEMCF_Msk			/*!< RET_EMC reset flag */
#define RCC_CTRLSTS_BKPEMCF_Pos					(21U)
#define RCC_CTRLSTS_BKPEMCF_Msk					(0x1UL << RCC_CTRLSTS_BKPEMCF_Pos)
#define RCC_CTRLSTS_BKPEMCF						RCC_CTRLSTS_BKPEMCF_Msk			/*!< BKP_EMC reset flag */
#define RCC_CTRLSTS_RAMRSTF_Pos					(23U)
#define RCC_CTRLSTS_RAMRSTF_Msk					(0x1UL << RCC_CTRLSTS_RAMRSTF_Pos)
#define RCC_CTRLSTS_RAMRSTF						RCC_CTRLSTS_RAMRSTF_Msk			/*!< RAM reset flag */
#define RCC_CTRLSTS_RMRSTF_Pos					(24U)
#define RCC_CTRLSTS_RMRSTF_Msk					(0x1UL << RCC_CTRLSTS_RMRSTF_Pos)
#define RCC_CTRLSTS_RMRSTF						RCC_CTRLSTS_RMRSTF_Msk			/*!< Remove reset flag */
#define RCC_CTRLSTS_MMURSTF_Pos					(25U)
#define RCC_CTRLSTS_MMURSTF_Msk					(0x1UL << RCC_CTRLSTS_MMURSTF_Pos)
#define RCC_CTRLSTS_MMURSTF						RCC_CTRLSTS_MMURSTF_Msk			/*!< MMU reset flag */
#define RCC_CTRLSTS_PINRSTF_Pos					(26U)
#define RCC_CTRLSTS_PINRSTF_Msk					(0x1UL << RCC_CTRLSTS_PINRSTF_Pos)
#define RCC_CTRLSTS_PINRSTF						RCC_CTRLSTS_PINRSTF_Msk			/*!< PIN reset flag */
#define RCC_CTRLSTS_PORRSTF_Pos					(27U)
#define RCC_CTRLSTS_PORRSTF_Msk					(0x1UL << RCC_CTRLSTS_PORRSTF_Pos)
#define RCC_CTRLSTS_PORRSTF						RCC_CTRLSTS_PORRSTF_Msk			/*!< POR/PDR reset flag */
#define RCC_CTRLSTS_SFTRSTF_Pos					(28U)
#define RCC_CTRLSTS_SFTRSTF_Msk					(0x1UL << RCC_CTRLSTS_SFTRSTF_Pos)
#define RCC_CTRLSTS_SFTRSTF						RCC_CTRLSTS_SFTRSTF_Msk			/*!< Software Reset flag */
#define RCC_CTRLSTS_IWDGRSTF_Pos				(29U)
#define RCC_CTRLSTS_IWDGRSTF_Msk				(0x1UL << RCC_CTRLSTS_IWDGRSTF_Pos)
#define RCC_CTRLSTS_IWDGRSTF					RCC_CTRLSTS_IWDGRSTF_Msk		/*!< Independent Watchdog reset flag */
#define RCC_CTRLSTS_WWDGRSTF_Pos				(30U)
#define RCC_CTRLSTS_WWDGRSTF_Msk				(0x1UL << RCC_CTRLSTS_WWDGRSTF_Pos)
#define RCC_CTRLSTS_WWDGRSTF					RCC_CTRLSTS_WWDGRSTF_Msk		/*!< Window watchdog reset flag */
#define RCC_CTRLSTS_LPWRRSTF_Pos				(31U)
#define RCC_CTRLSTS_LPWRRSTF_Msk				(0x1UL << RCC_CTRLSTS_LPWRRSTF_Pos)
#define RCC_CTRLSTS_LPWRRSTF					RCC_CTRLSTS_LPWRRSTF_Msk		/*!< Low-Power reset flag */

/*******************  Bit definition for RCC_AHBPRST register  ****************/
#define RCC_AHBRST_SACRST_Pos					(11U)
#define RCC_AHBRST_SACRST_Msk					(0x1UL << RCC_AHBRST_SACRST_Pos)	/*!< 0x00000800 */
#define RCC_AHBRST_SACRST						RCC_AHBRST_SACRST_Msk			/*!< SAC reset */
#define RCC_AHBRST_ADC1RST_Pos					(12U)
#define RCC_AHBRST_ADC1RST_Msk					(0x1UL << RCC_AHBRST_ADC1RST_Pos)	/*!< 0x00001000 */
#define RCC_AHBRST_ADC1RST						RCC_AHBRST_ADC1RST_Msk			/*!< ADC1 reset */
#define RCC_AHBRST_ADC2RST_Pos					(13U)
#define RCC_AHBRST_ADC2RST_Msk					(0x1UL << RCC_AHBRST_ADC2RST_Pos)	/*!< 0x00002000 */
#define RCC_AHBRST_ADC2RST						RCC_AHBRST_ADC2RST_Msk			/*!< ADC2 reset */
#define RCC_AHBRST_ADC3RST_Pos					(14U)
#define RCC_AHBRST_ADC3RST_Msk					(0x1UL << RCC_AHBRST_ADC3RST_Pos)	/*!< 0x00004000 */
#define RCC_AHBRST_ADC3RST						RCC_AHBRST_ADC3RST_Msk			/*!< ADC3 reset */
#define RCC_AHBRST_ADC4RST_Pos					(15U)
#define RCC_AHBRST_ADC4RST_Msk					(0x1UL << RCC_AHBRST_ADC4RST_Pos)	/*!< 0x00008000 */
#define RCC_AHBRST_ADC4RST						RCC_AHBRST_ADC4RST_Msk			/*!< ADC4 reset */
#define RCC_AHBRST_QSPIRST_Pos					(17U)
#define RCC_AHBRST_QSPIRST_Msk					(0x1UL << RCC_AHBRST_QSPIRST_Pos)	/*!< 0x00020000 */
#define RCC_AHBRST_QSPIRST						RCC_AHBRST_QSPIRST_Msk			/*!< QSPI reset */

/******************  Bit definition for RCC_CFG2 register  ********************/
/*!< ADCHPRE configuration */
#define RCC_CFG2_ADCHPRES_Pos					(0U)
#define RCC_CFG2_ADCHPRES_Msk					(0xFUL << RCC_CFG2_ADCHPRES_Pos)
#define RCC_CFG2_ADCHPRES						RCC_CFG2_ADCHPRES_Msk			/*!< ADCHPRE[3:0] bits */
#define RCC_CFG2_ADCHPRES_0						((uint32_t)0x00000001)			/*!< Bit 0 */
#define RCC_CFG2_ADCHPRES_1						((uint32_t)0x00000002)			/*!< Bit 1 */
#define RCC_CFG2_ADCHPRES_2						((uint32_t)0x00000004)			/*!< Bit 2 */
#define RCC_CFG2_ADCHPRES_3						((uint32_t)0x00000008)			/*!< Bit 3 */

#define RCC_CFG2_ADCHPRES_DIV1					((uint32_t) 0x00000000)			/*!< HCLK clock divided by 1 */
#define RCC_CFG2_ADCHPRES_DIV2					((uint32_t) 0x00000001)			/*!< HCLK clock divided by 2 */
#define RCC_CFG2_ADCHPRES_DIV4					((uint32_t) 0x00000002)			/*!< HCLK clock divided by 4 */
#define RCC_CFG2_ADCHPRES_DIV6					((uint32_t) 0x00000003)			/*!< HCLK clock divided by 6 */
#define RCC_CFG2_ADCHPRES_DIV8					((uint32_t) 0x00000004)			/*!< HCLK clock divided by 8 */
#define RCC_CFG2_ADCHPRES_DIV10					((uint32_t) 0x00000005)			/*!< HCLK clock divided by 10 */
#define RCC_CFG2_ADCHPRES_DIV12					((uint32_t) 0x00000006)			/*!< HCLK clock divided by 12 */
#define RCC_CFG2_ADCHPRES_DIV16					((uint32_t) 0x00000007)			/*!< HCLK clock divided by 16 */
#define RCC_CFG2_ADCHPRES_DIV32					((uint32_t) 0x00000008)			/*!< HCLK clock divided by 32 */
#define RCC_CFG2_ADCHPRES_OTHERS				((uint32_t) 0x00000008)			/*!< HCLK clock divided by 32 */

/*!< ADCPLLPRES configuration */
#define RCC_CFG2_ADCPLLPRES_Pos					(4U)
#define RCC_CFG2_ADCPLLPRES_Msk					(0x1FUL << RCC_CFG2_ADCPLLPRES_Pos)
#define RCC_CFG2_ADCPLLPRES						RCC_CFG2_ADCPLLPRES_Msk			/*!< ADCPLLPRES[4:0] bits */
#define RCC_CFG2_ADCPLLPRES_0					((uint32_t)0x00000010)			/*!< Bit 0 */
#define RCC_CFG2_ADCPLLPRES_1					((uint32_t)0x00000020)			/*!< Bit 1 */
#define RCC_CFG2_ADCPLLPRES_2					((uint32_t)0x00000040)			/*!< Bit 2 */
#define RCC_CFG2_ADCPLLPRES_3					((uint32_t)0x00000080)			/*!< Bit 3 */
#define RCC_CFG2_ADCPLLPRES_4					((uint32_t)0x00000100)			/*!< Bit 4 */

#define RCC_CFG2_ADCPLLCLK_DISABLE				((uint32_t) 0xFFFFFEFF)			/*!< ADC PLL clock Disable */
#define RCC_CFG2_ADCPLLPRES_DIV1				((uint32_t) 0x00000100)			/*!< PLL clock divided by 1 */
#define RCC_CFG2_ADCPLLPRES_DIV2				((uint32_t) 0x00000110)			/*!< PLL clock divided by 2 */
#define RCC_CFG2_ADCPLLPRES_DIV4				((uint32_t) 0x00000120)			/*!< PLL clock divided by 4 */
#define RCC_CFG2_ADCPLLPRES_DIV6				((uint32_t) 0x00000130)			/*!< PLL clock divided by 6 */
#define RCC_CFG2_ADCPLLPRES_DIV8				((uint32_t) 0x00000140)			/*!< PLL clock divided by 8 */
#define RCC_CFG2_ADCPLLPRES_DIV10				((uint32_t) 0x00000150)			/*!< PLL clock divided by 10 */
#define RCC_CFG2_ADCPLLPRES_DIV12				((uint32_t) 0x00000160)			/*!< PLL clock divided by 12 */
#define RCC_CFG2_ADCPLLPRES_DIV16				((uint32_t) 0x00000170)			/*!< PLL clock divided by 16 */
#define RCC_CFG2_ADCPLLPRES_DIV32				((uint32_t) 0x00000180)			/*!< PLL clock divided by 32 */
#define RCC_CFG2_ADCPLLPRES_DIV64				((uint32_t) 0x00000190)			/*!< PLL clock divided by 64 */
#define RCC_CFG2_ADCPLLPRES_DIV128				((uint32_t) 0x000001A0)			/*!< PLL clock divided by 128 */
#define RCC_CFG2_ADCPLLPRES_DIV256				((uint32_t) 0x000001B0)			/*!< PLL clock divided by 256 */
#define RCC_CFG2_ADCPLLPRES_DIV256N				((uint32_t) 0x000001C0)			/*!< PLL clock divided by 256 */

/*!< ADC1MSEL configuration */
#define RCC_CFG2_ADC1MSEL_Pos					(10U)
#define RCC_CFG2_ADC1MSEL_Msk					(0x1UL << RCC_CFG2_ADC1MSEL_Pos)
#define RCC_CFG2_ADC1MSEL						RCC_CFG2_ADC1MSEL_Msk			/*!< ADC1M clock source select */

#define RCC_CFG2_ADC1MSEL_HSI					((uint32_t) 0x00000000)			/*!< HSI clock selected as ADC1M input clock */
#define RCC_CFG2_ADC1MSEL_HSE					((uint32_t) 0x00000400)			/*!< HSE clock selected as ADC1M input clock */

/*!< ADC1MPRE configuration */
#define RCC_CFG2_ADC1MPRES_Pos					(11U)
#define RCC_CFG2_ADC1MPRES_Msk					(0x1FUL << RCC_CFG2_ADC1MPRES_Pos)
#define RCC_CFG2_ADC1MPRES						RCC_CFG2_ADC1MPRES_Msk			/*!< ADC1MPRE[4:0] bits */
#define RCC_CFG2_ADC1MPRES_0					((uint32_t) 0x00000800)			/*!< Bit 0 */
#define RCC_CFG2_ADC1MPRES_1					((uint32_t) 0x00001000)			/*!< Bit 1 */
#define RCC_CFG2_ADC1MPRES_2					((uint32_t) 0x00002000)			/*!< Bit 2 */
#define RCC_CFG2_ADC1MPRES_3					((uint32_t) 0x00004000)			/*!< Bit 3 */
#define RCC_CFG2_ADC1MPRES_4					((uint32_t) 0x00008000)			/*!< Bit 4 */

#define RCC_CFG2_ADC1MPRES_DIV1					((uint32_t) 0x00000000)			/*!< ADC1M source clock is divided by 1 */
#define RCC_CFG2_ADC1MPRES_DIV2					((uint32_t) 0x00000800)			/*!< ADC1M source clock is divided by 2 */
#define RCC_CFG2_ADC1MPRES_DIV3					((uint32_t) 0x00001000)			/*!< ADC1M source clock is divided by 3 */
#define RCC_CFG2_ADC1MPRES_DIV4					((uint32_t) 0x00001800)			/*!< ADC1M source clock is divided by 4 */
#define RCC_CFG2_ADC1MPRES_DIV5					((uint32_t) 0x00002000)			/*!< ADC1M source clock is divided by 5 */
#define RCC_CFG2_ADC1MPRES_DIV6					((uint32_t) 0x00002800)			/*!< ADC1M source clock is divided by 6 */
#define RCC_CFG2_ADC1MPRES_DIV7					((uint32_t) 0x00003000)			/*!< ADC1M source clock is divided by 7 */
#define RCC_CFG2_ADC1MPRES_DIV8					((uint32_t) 0x00003800)			/*!< ADC1M source clock is divided by 8 */
#define RCC_CFG2_ADC1MPRES_DIV9					((uint32_t) 0x00004000)			/*!< ADC1M source clock is divided by 9 */
#define RCC_CFG2_ADC1MPRES_DIV10				((uint32_t) 0x00004800)			/*!< ADC1M source clock is divided by 10 */
#define RCC_CFG2_ADC1MPRES_DIV11				((uint32_t) 0x00005000)			/*!< ADC1M source clock is divided by 11 */
#define RCC_CFG2_ADC1MPRES_DIV12				((uint32_t) 0x00005800)			/*!< ADC1M source clock is divided by 12 */
#define RCC_CFG2_ADC1MPRES_DIV13				((uint32_t) 0x00006000)			/*!< ADC1M source clock is divided by 13 */
#define RCC_CFG2_ADC1MPRES_DIV14				((uint32_t) 0x00006800)			/*!< ADC1M source clock is divided by 14 */
#define RCC_CFG2_ADC1MPRES_DIV15				((uint32_t) 0x00007000)			/*!< ADC1M source clock is divided by 15 */
#define RCC_CFG2_ADC1MPRES_DIV16				((uint32_t) 0x00007800)			/*!< ADC1M source clock is divided by 16 */
#define RCC_CFG2_ADC1MPRES_DIV17				((uint32_t) 0x00008000)			/*!< ADC1M source clock is divided by 17 */
#define RCC_CFG2_ADC1MPRES_DIV18				((uint32_t) 0x00008800)			/*!< ADC1M source clock is divided by 18 */
#define RCC_CFG2_ADC1MPRES_DIV19				((uint32_t) 0x00009000)			/*!< ADC1M source clock is divided by 19 */
#define RCC_CFG2_ADC1MPRES_DIV20				((uint32_t) 0x00009800)			/*!< ADC1M source clock is divided by 20 */
#define RCC_CFG2_ADC1MPRES_DIV21				((uint32_t) 0x0000A000)			/*!< ADC1M source clock is divided by 21 */
#define RCC_CFG2_ADC1MPRES_DIV22				((uint32_t) 0x0000A800)			/*!< ADC1M source clock is divided by 22 */
#define RCC_CFG2_ADC1MPRES_DIV23				((uint32_t) 0x0000B000)			/*!< ADC1M source clock is divided by 23 */
#define RCC_CFG2_ADC1MPRES_DIV24				((uint32_t) 0x0000B800)			/*!< ADC1M source clock is divided by 24 */
#define RCC_CFG2_ADC1MPRES_DIV25				((uint32_t) 0x0000C000)			/*!< ADC1M source clock is divided by 25 */
#define RCC_CFG2_ADC1MPRES_DIV26				((uint32_t) 0x0000C800)			/*!< ADC1M source clock is divided by 26 */
#define RCC_CFG2_ADC1MPRES_DIV27				((uint32_t) 0x0000D000)			/*!< ADC1M source clock is divided by 27 */
#define RCC_CFG2_ADC1MPRES_DIV28				((uint32_t) 0x0000D800)			/*!< ADC1M source clock is divided by 28 */
#define RCC_CFG2_ADC1MPRES_DIV29				((uint32_t) 0x0000E000)			/*!< ADC1M source clock is divided by 29 */
#define RCC_CFG2_ADC1MPRES_DIV30				((uint32_t) 0x0000E800)			/*!< ADC1M source clock is divided by 30 */
#define RCC_CFG2_ADC1MPRES_DIV31				((uint32_t) 0x0000F000)			/*!< ADC1M source clock is divided by 31 */
#define RCC_CFG2_ADC1MPRES_DIV32				((uint32_t) 0x0000F800)			/*!< ADC1M source clock is divided by 32 */

/*!< RNGCPRE configuration */
#define RCC_CFG2_RNGCPRES_Pos					(24U)
#define RCC_CFG2_RNGCPRES_Msk					(0x1FUL << RCC_CFG2_RNGCPRES_Pos)
#define RCC_CFG2_RNGCPRES						RCC_CFG2_RNGCPRES_Msk			/*!< RNGCPRE[4:0] bits */
#define RCC_CFG2_RNGCPRES_0						((uint32_t) 0x01000000)			/*!< Bit 0 */
#define RCC_CFG2_RNGCPRES_1						((uint32_t) 0x02000000)			/*!< Bit 1 */
#define RCC_CFG2_RNGCPRES_2						((uint32_t) 0x04000000)			/*!< Bit 2 */
#define RCC_CFG2_RNGCPRES_3						((uint32_t) 0x08000000)			/*!< Bit 3 */
#define RCC_CFG2_RNGCPRES_4						((uint32_t) 0x10000000)			/*!< Bit 4 */

#define RCC_CFG2_RNGCPRES_DIV1					((uint32_t) 0x00000000)			/*!< SYSCLK source clock is divided by 1 */
#define RCC_CFG2_RNGCPRES_DIV2					((uint32_t) 0x01000000)			/*!< SYSCLK source clock is divided by 2 */
#define RCC_CFG2_RNGCPRES_DIV3					((uint32_t) 0x02000000)			/*!< SYSCLK source clock is divided by 3 */
#define RCC_CFG2_RNGCPRES_DIV4					((uint32_t) 0x03000000)			/*!< SYSCLK source clock is divided by 4 */
#define RCC_CFG2_RNGCPRES_DIV5					((uint32_t) 0x04000000)			/*!< SYSCLK source clock is divided by 5 */
#define RCC_CFG2_RNGCPRES_DIV6					((uint32_t) 0x05000000)			/*!< SYSCLK source clock is divided by 6 */
#define RCC_CFG2_RNGCPRES_DIV7					((uint32_t) 0x06000000)			/*!< SYSCLK source clock is divided by 7 */
#define RCC_CFG2_RNGCPRES_DIV8					((uint32_t) 0x07000000)			/*!< SYSCLK source clock is divided by 8 */
#define RCC_CFG2_RNGCPRES_DIV9					((uint32_t) 0x08000000)			/*!< SYSCLK source clock is divided by 9 */
#define RCC_CFG2_RNGCPRES_DIV10					((uint32_t) 0x09000000)			/*!< SYSCLK source clock is divided by 10 */
#define RCC_CFG2_RNGCPRES_DIV11					((uint32_t) 0x0A000000)			/*!< SYSCLK source clock is divided by 11 */
#define RCC_CFG2_RNGCPRES_DIV12					((uint32_t) 0x0B000000)			/*!< SYSCLK source clock is divided by 12 */
#define RCC_CFG2_RNGCPRES_DIV13					((uint32_t) 0x0C000000)			/*!< SYSCLK source clock is divided by 13 */
#define RCC_CFG2_RNGCPRES_DIV14					((uint32_t) 0x0D000000)			/*!< SYSCLK source clock is divided by 14 */
#define RCC_CFG2_RNGCPRES_DIV15					((uint32_t) 0x0E000000)			/*!< SYSCLK source clock is divided by 15 */
#define RCC_CFG2_RNGCPRES_DIV16					((uint32_t) 0x0F000000)			/*!< SYSCLK source clock is divided by 16 */
#define RCC_CFG2_RNGCPRES_DIV17					((uint32_t) 0x10000000)			/*!< SYSCLK source clock is divided by 17 */
#define RCC_CFG2_RNGCPRES_DIV18					((uint32_t) 0x11000000)			/*!< SYSCLK source clock is divided by 18 */
#define RCC_CFG2_RNGCPRES_DIV19					((uint32_t) 0x12000000)			/*!< SYSCLK source clock is divided by 19 */
#define RCC_CFG2_RNGCPRES_DIV20					((uint32_t) 0x13000000)			/*!< SYSCLK source clock is divided by 20 */
#define RCC_CFG2_RNGCPRES_DIV21					((uint32_t) 0x14000000)			/*!< SYSCLK source clock is divided by 21 */
#define RCC_CFG2_RNGCPRES_DIV22					((uint32_t) 0x15000000)			/*!< SYSCLK source clock is divided by 22 */
#define RCC_CFG2_RNGCPRES_DIV23					((uint32_t) 0x16000000)			/*!< SYSCLK source clock is divided by 23 */
#define RCC_CFG2_RNGCPRES_DIV24					((uint32_t) 0x17000000)			/*!< SYSCLK source clock is divided by 24 */
#define RCC_CFG2_RNGCPRES_DIV25					((uint32_t) 0x18000000)			/*!< SYSCLK source clock is divided by 25 */
#define RCC_CFG2_RNGCPRES_DIV26					((uint32_t) 0x19000000)			/*!< SYSCLK source clock is divided by 26 */
#define RCC_CFG2_RNGCPRES_DIV27					((uint32_t) 0x1A000000)			/*!< SYSCLK source clock is divided by 27 */
#define RCC_CFG2_RNGCPRES_DIV28					((uint32_t) 0x1B000000)			/*!< SYSCLK source clock is divided by 28 */
#define RCC_CFG2_RNGCPRES_DIV29					((uint32_t) 0x1C000000)			/*!< SYSCLK source clock is divided by 29 */
#define RCC_CFG2_RNGCPRES_DIV30					((uint32_t) 0x1D000000)			/*!< SYSCLK source clock is divided by 30 */
#define RCC_CFG2_RNGCPRES_DIV31					((uint32_t) 0x1E000000)			/*!< SYSCLK source clock is divided by 31 */
#define RCC_CFG2_RNGCPRES_DIV32					((uint32_t) 0x1F000000)			/*!< SYSCLK source clock is divided by 32 */

/*!< TIMCLK_SEL configuration */
#define RCC_CFG2_TIMCLKSEL_Pos					(29U)
#define RCC_CFG2_TIMCLKSEL_Msk					(0x1UL << RCC_CFG2_TIMCLKSEL_Pos)
#define RCC_CFG2_TIMCLKSEL						RCC_CFG2_TIMCLKSEL_Msk			/*!< Timer1/8 clock source select */

#define RCC_CFG2_TIMCLKSEL_TIM18CLK				((uint32_t) 0x00000000)			/*!< Timer1/8 clock selected as tim1/8_clk input clock */
#define RCC_CFG2_TIMCLKSEL_SYSCLK				((uint32_t) 0x20000000)			/*!< Timer1/8 clock selected as sysclk input clock */

/******************  Bit definition for RCC_CFG3 register  ********************/
/*!< BORRSTEN configuration */
#define RCC_CFG3_BORRSTEN_Pos					(6U)
#define RCC_CFG3_BORRSTEN_Msk					(0x1UL << RCC_CFG3_BORRSTEN_Pos)
#define RCC_CFG3_BORRSTEN						RCC_CFG3_BORRSTEN_Msk			/*!< BOR reset enable */

#define RCC_CFG3_BORRSTEN_ENABLE				((uint32_t) 0x00000040)			/*!< BOR reset enable */
#define RCC_CFG3_BORRSTEN_DISABLE				((uint32_t) 0x00000000)			/*!< BOR reset disable */

/*!< TRNG1MPRE configuration */
#define RCC_CFG3_TRNG1MPRES_Pos					(11U)
#define RCC_CFG3_TRNG1MPRES_Msk					(0x1FUL << RCC_CFG3_TRNG1MPRES_Pos)
#define RCC_CFG3_TRNG1MPRES						RCC_CFG3_TRNG1MPRES_Msk			/*!< TRNG1MPRE[4:0] bits */
#define RCC_CFG3_TRNG1MPRES_0					((uint32_t) 0x00000800)			/*!< Bit 0 */
#define RCC_CFG3_TRNG1MPRES_1					((uint32_t) 0x00001000)			/*!< Bit 1 */
#define RCC_CFG3_TRNG1MPRES_2					((uint32_t) 0x00002000)			/*!< Bit 2 */
#define RCC_CFG3_TRNG1MPRES_3					((uint32_t) 0x00004000)			/*!< Bit 3 */
#define RCC_CFG3_TRNG1MPRES_4					((uint32_t) 0x00008000)			/*!< Bit 4 */

#define RCC_CFG3_TRNG1MPRES_DIV1				((uint32_t) 0x00000000)			/*!< TRNG 1M source clock is divided by 2 */
#define RCC_CFG3_TRNG1MPRES_DIV2				((uint32_t) 0x00000800)			/*!< TRNG 1M source clock is divided by 2 */
#define RCC_CFG3_TRNG1MPRES_DIV3				((uint32_t) 0x00001000)			/*!< TRNG 1M source clock is divided by 4 */
#define RCC_CFG3_TRNG1MPRES_DIV4				((uint32_t) 0x00001800)			/*!< TRNG 1M source clock is divided by 4 */
#define RCC_CFG3_TRNG1MPRES_DIV5				((uint32_t) 0x00002000)			/*!< TRNG 1M source clock is divided by 6 */
#define RCC_CFG3_TRNG1MPRES_DIV6				((uint32_t) 0x00002800)			/*!< TRNG 1M source clock is divided by 6 */
#define RCC_CFG3_TRNG1MPRES_DIV7				((uint32_t) 0x00003000)			/*!< TRNG 1M source clock is divided by 8 */
#define RCC_CFG3_TRNG1MPRES_DIV8				((uint32_t) 0x00003800)			/*!< TRNG 1M source clock is divided by 8 */
#define RCC_CFG3_TRNG1MPRES_DIV9				((uint32_t) 0x00004000)			/*!< TRNG 1M source clock is divided by 10 */
#define RCC_CFG3_TRNG1MPRES_DIV10				((uint32_t) 0x00004800)			/*!< TRNG 1M source clock is divided by 10 */
#define RCC_CFG3_TRNG1MPRES_DIV11				((uint32_t) 0x00005000)			/*!< TRNG 1M source clock is divided by 12 */
#define RCC_CFG3_TRNG1MPRES_DIV12				((uint32_t) 0x00005800)			/*!< TRNG 1M source clock is divided by 12 */
#define RCC_CFG3_TRNG1MPRES_DIV13				((uint32_t) 0x00006000)			/*!< TRNG 1M source clock is divided by 14 */
#define RCC_CFG3_TRNG1MPRES_DIV14				((uint32_t) 0x00006800)			/*!< TRNG 1M source clock is divided by 14 */
#define RCC_CFG3_TRNG1MPRES_DIV15				((uint32_t) 0x00007000)			/*!< TRNG 1M source clock is divided by 16 */
#define RCC_CFG3_TRNG1MPRES_DIV16				((uint32_t) 0x00007800)			/*!< TRNG 1M source clock is divided by 16 */
#define RCC_CFG3_TRNG1MPRES_DIV17				((uint32_t) 0x00008000)			/*!< TRNG 1M source clock is divided by 18 */
#define RCC_CFG3_TRNG1MPRES_DIV18				((uint32_t) 0x00008800)			/*!< TRNG 1M source clock is divided by 18 */
#define RCC_CFG3_TRNG1MPRES_DIV19				((uint32_t) 0x00009000)			/*!< TRNG 1M source clock is divided by 20 */
#define RCC_CFG3_TRNG1MPRES_DIV20				((uint32_t) 0x00009800)			/*!< TRNG 1M source clock is divided by 20 */
#define RCC_CFG3_TRNG1MPRES_DIV21				((uint32_t) 0x0000A000)			/*!< TRNG 1M source clock is divided by 22 */
#define RCC_CFG3_TRNG1MPRES_DIV22				((uint32_t) 0x0000A800)			/*!< TRNG 1M source clock is divided by 22 */
#define RCC_CFG3_TRNG1MPRES_DIV23				((uint32_t) 0x0000B000)			/*!< TRNG 1M source clock is divided by 24 */
#define RCC_CFG3_TRNG1MPRES_DIV24				((uint32_t) 0x0000B800)			/*!< TRNG 1M source clock is divided by 24 */
#define RCC_CFG3_TRNG1MPRES_DIV25				((uint32_t) 0x0000C000)			/*!< TRNG 1M source clock is divided by 26 */
#define RCC_CFG3_TRNG1MPRES_DIV26				((uint32_t) 0x0000C800)			/*!< TRNG 1M source clock is divided by 26 */
#define RCC_CFG3_TRNG1MPRES_DIV27				((uint32_t) 0x0000D000)			/*!< TRNG 1M source clock is divided by 28 */
#define RCC_CFG3_TRNG1MPRES_DIV28				((uint32_t) 0x0000D800)			/*!< TRNG 1M source clock is divided by 28 */
#define RCC_CFG3_TRNG1MPRES_DIV29				((uint32_t) 0x0000E000)			/*!< TRNG 1M source clock is divided by 30 */
#define RCC_CFG3_TRNG1MPRES_DIV30				((uint32_t) 0x0000E800)			/*!< TRNG 1M source clock is divided by 30 */
#define RCC_CFG3_TRNG1MPRES_DIV31				((uint32_t) 0x0000F000)			/*!< TRNG 1M source clock is divided by 32 */
#define RCC_CFG3_TRNG1MPRES_DIV32				((uint32_t) 0x0000F800)			/*!< TRNG 1M source clock is divided by 32 */

/*!< TRNG1MSEL configuration */
#define RCC_CFG3_TRNG1MSEL_Pos					(17U)
#define RCC_CFG3_TRNG1MSEL_Msk					(0x1UL << RCC_CFG3_TRNG1MSEL_Pos)
#define RCC_CFG3_TRNG1MSEL						RCC_CFG3_TRNG1MSEL_Msk			/*!< TRNG_1M clock source select */

#define RCC_CFG3_TRNG1MSEL_HSI					((uint32_t) 0x00000000)			/*!< HSI clock selected as TRNG_1M input clock */
#define RCC_CFG3_TRNG1MSEL_HSE					((uint32_t) 0x00020000)			/*!< HSE clock selected as TRNG_1M input clock */

/*!< TRNG1MEN configuration */
#define RCC_CFG3_TRNG1MEN_Pos					(18U)
#define RCC_CFG3_TRNG1MEN_Msk					(0x1UL << RCC_CFG3_TRNG1MEN_Pos)
#define RCC_CFG3_TRNG1MEN						RCC_CFG3_TRNG1MEN_Msk			/*!< TRNG_1M clock enable */

#define RCC_CFG3_TRNG1MEN_DISABLE				((uint32_t) 0x00000000)			/*!< TRNG_1M clock disable */
#define RCC_CFG3_TRNG1MEN_ENABLE				((uint32_t) 0x00040000)			/*!< TRNG_1M clock enable */

/******************************************************************************/
/*                                                                            */
/*                General Purpose and Alternate Function I/O                  */
/*                                                                            */
/******************************************************************************/
/*****************  Bit definition for GPIO_PL_CFG register  ******************/
#define GPIO_PL_CFG_PMODE						((uint32_t) 0x33333333)			/*!< Port x mode bits */

#define GPIO_PL_CFG_PMODE0_Pos					(0U)
#define GPIO_PL_CFG_PMODE0_Msk					(0x3UL << GPIO_PL_CFG_PMODE0_Pos)	/*!< 0x00000003 */
#define GPIO_PL_CFG_PMODE0						GPIO_PL_CFG_PMODE0_Msk			/*!< MODE0[1:0] bits (Port x mode bits, pin 0) */
#define GPIO_PL_CFG_PMODE0_0					((uint32_t) 0x00000001)			/*!< Bit 0 */
#define GPIO_PL_CFG_PMODE0_1					((uint32_t) 0x00000002)			/*!< Bit 1 */

#define GPIO_PL_CFG_PMODE1_Pos					(4U)
#define GPIO_PL_CFG_PMODE1_Msk					(0x3UL << GPIO_PL_CFG_PMODE1_Pos)	/*!< 0x00000030 */
#define GPIO_PL_CFG_PMODE1						GPIO_PL_CFG_PMODE1_Msk			/*!< MODE1[1:0] bits (Port x mode bits, pin 1) */
#define GPIO_PL_CFG_PMODE1_0					((uint32_t) 0x00000010)			/*!< Bit 0 */
#define GPIO_PL_CFG_PMODE1_1					((uint32_t) 0x00000020)			/*!< Bit 1 */

#define GPIO_PL_CFG_PMODE2_Pos					(8U)
#define GPIO_PL_CFG_PMODE2_Msk					(0x3UL << GPIO_PL_CFG_PMODE2_Pos)	/*!< 0x00000300 */
#define GPIO_PL_CFG_PMODE2						GPIO_PL_CFG_PMODE2_Msk			/*!< MODE2[1:0] bits (Port x mode bits, pin 2) */
#define GPIO_PL_CFG_PMODE2_0					((uint32_t) 0x00000100)			/*!< Bit 0 */
#define GPIO_PL_CFG_PMODE2_1					((uint32_t) 0x00000200)			/*!< Bit 1 */

#define GPIO_PL_CFG_PMODE3_Pos					(12U)
#define GPIO_PL_CFG_PMODE3_Msk					(0x3UL << GPIO_PL_CFG_PMODE3_Pos)	/*!< 0x00003000 */
#define GPIO_PL_CFG_PMODE3						GPIO_PL_CFG_PMODE3_Msk			/*!< MODE3[1:0] bits (Port x mode bits, pin 3) */
#define GPIO_PL_CFG_PMODE3_0					((uint32_t) 0x00001000)			/*!< Bit 0 */
#define GPIO_PL_CFG_PMODE3_1					((uint32_t) 0x00002000)			/*!< Bit 1 */

#define GPIO_PL_CFG_PMODE4_Pos					(16U)
#define GPIO_PL_CFG_PMODE4_Msk					(0x3UL << GPIO_PL_CFG_PMODE4_Pos)	/*!< 0x00030000 */
#define GPIO_PL_CFG_PMODE4						GPIO_PL_CFG_PMODE4_Msk			/*!< MODE4[1:0] bits (Port x mode bits, pin 4) */
#define GPIO_PL_CFG_PMODE4_0					((uint32_t) 0x00010000)			/*!< Bit 0 */
#define GPIO_PL_CFG_PMODE4_1					((uint32_t) 0x00020000)			/*!< Bit 1 */

#define GPIO_PL_CFG_PMODE5_Pos					(20U)
#define GPIO_PL_CFG_PMODE5_Msk					(0x3UL << GPIO_PL_CFG_PMODE5_Pos)	/*!< 0x00300000 */
#define GPIO_PL_CFG_PMODE5						GPIO_PL_CFG_PMODE5_Msk			/*!< MODE5[1:0] bits (Port x mode bits, pin 5) */
#define GPIO_PL_CFG_PMODE5_0					((uint32_t) 0x00100000)			/*!< Bit 0 */
#define GPIO_PL_CFG_PMODE5_1					((uint32_t) 0x00200000)			/*!< Bit 1 */

#define GPIO_PL_CFG_PMODE6_Pos					(24U)
#define GPIO_PL_CFG_PMODE6_Msk					(0x3UL << GPIO_PL_CFG_PMODE6_Pos)	/*!< 0x03000000 */
#define GPIO_PL_CFG_PMODE6						GPIO_PL_CFG_PMODE6_Msk			/*!< MODE6[1:0] bits (Port x mode bits, pin 6) */
#define GPIO_PL_CFG_PMODE6_0					((uint32_t) 0x01000000)			/*!< Bit 0 */
#define GPIO_PL_CFG_PMODE6_1					((uint32_t) 0x02000000)			/*!< Bit 1 */

#define GPIO_PL_CFG_PMODE7_Pos					(28U)
#define GPIO_PL_CFG_PMODE7_Msk					(0x3UL << GPIO_PL_CFG_PMODE7_Pos)	/*!< 0x30000000 */
#define GPIO_PL_CFG_PMODE7						GPIO_PL_CFG_PMODE7_Msk			/*!< MODE7[1:0] bits (Port x mode bits, pin 7) */
#define GPIO_PL_CFG_PMODE7_0					((uint32_t) 0x10000000)			/*!< Bit 0 */
#define GPIO_PL_CFG_PMODE7_1					((uint32_t) 0x20000000)			/*!< Bit 1 */

#define GPIO_PL_CFG_PCFG						((uint32_t) 0xCCCCCCCC)			/*!< Port x configuration bits */

#define GPIO_PL_CFG_PCFG0_Pos					(2U)
#define GPIO_PL_CFG_PCFG0_Msk					(0x3UL << GPIO_PL_CFG_PCFG0_Pos)	/*!< 0x0000000C */
#define GPIO_PL_CFG_PCFG0						GPIO_PL_CFG_PCFG0_Msk			/*!< CNF0[1:0] bits (Port x configuration bits, pin 0) */
#define GPIO_PL_CFG_PCFG0_0						((uint32_t) 0x00000004)			/*!< Bit 0 */
#define GPIO_PL_CFG_PCFG0_1						((uint32_t) 0x00000008)			/*!< Bit 1 */

#define GPIO_PL_CFG_PCFG1_Pos					(6U)
#define GPIO_PL_CFG_PCFG1_Msk					(0x3UL << GPIO_PL_CFG_PCFG1_Pos)	/*!< 0x000000C0 */
#define GPIO_PL_CFG_PCFG1						GPIO_PL_CFG_PCFG1_Msk			/*!< CNF1[1:0] bits (Port x configuration bits, pin 1) */
#define GPIO_PL_CFG_PCFG1_0						((uint32_t) 0x00000040)			/*!< Bit 0 */
#define GPIO_PL_CFG_PCFG1_1						((uint32_t) 0x00000080)			/*!< Bit 1 */

#define GPIO_PL_CFG_PCFG2_Pos					(10U)
#define GPIO_PL_CFG_PCFG2_Msk					(0x3UL << GPIO_PL_CFG_PCFG2_Pos)	/*!< 0x00000C00 */
#define GPIO_PL_CFG_PCFG2						GPIO_PL_CFG_PCFG2_Msk			/*!< CNF2[1:0] bits (Port x configuration bits, pin 2) */
#define GPIO_PL_CFG_PCFG2_0						((uint32_t) 0x00000400)			/*!< Bit 0 */
#define GPIO_PL_CFG_PCFG2_1						((uint32_t) 0x00000800)			/*!< Bit 1 */

#define GPIO_PL_CFG_PCFG3_Pos					(14U)
#define GPIO_PL_CFG_PCFG3_Msk					(0x3UL << GPIO_PL_CFG_PCFG3_Pos)	/*!< 0x0000C000 */
#define GPIO_PL_CFG_PCFG3						GPIO_PL_CFG_PCFG3_Msk			/*!< CNF3[1:0] bits (Port x configuration bits, pin 3) */
#define GPIO_PL_CFG_PCFG3_0						((uint32_t) 0x00004000)			/*!< Bit 0 */
#define GPIO_PL_CFG_PCFG3_1						((uint32_t) 0x00008000)			/*!< Bit 1 */

#define GPIO_PL_CFG_PCFG4_Pos					(18U)
#define GPIO_PL_CFG_PCFG4_Msk					(0x3UL << GPIO_PL_CFG_PCFG4_Pos)	/*!< 0x000C0000 */
#define GPIO_PL_CFG_PCFG4						GPIO_PL_CFG_PCFG4_Msk			/*!< CNF4[1:0] bits (Port x configuration bits, pin 4) */
#define GPIO_PL_CFG_PCFG4_0						((uint32_t) 0x00040000)			/*!< Bit 0 */
#define GPIO_PL_CFG_PCFG4_1						((uint32_t) 0x00080000)			/*!< Bit 1 */

#define GPIO_PL_CFG_PCFG5_Pos					(22U)
#define GPIO_PL_CFG_PCFG5_Msk					(0x3UL << GPIO_PL_CFG_PCFG5_Pos)	/*!< 0x00C00000 */
#define GPIO_PL_CFG_PCFG5						GPIO_PL_CFG_PCFG5_Msk			/*!< CNF5[1:0] bits (Port x configuration bits, pin 5) */
#define GPIO_PL_CFG_PCFG5_0						((uint32_t) 0x00400000)			/*!< Bit 0 */
#define GPIO_PL_CFG_PCFG5_1						((uint32_t) 0x00800000)			/*!< Bit 1 */

#define GPIO_PL_CFG_PCFG6_Pos					(26U)
#define GPIO_PL_CFG_PCFG6_Msk					(0x4UL << GPIO_PL_CFG_PCFG6_Pos)	/*!< 0x0C000000 */
#define GPIO_PL_CFG_PCFG6						GPIO_PL_CFG_PCFG6_Msk			/*!< CNF6[1:0] bits (Port x configuration bits, pin 6) */
#define GPIO_PL_CFG_PCFG6_0						((uint32_t) 0x04000000)			/*!< Bit 0 */
#define GPIO_PL_CFG_PCFG6_1						((uint32_t) 0x08000000)			/*!< Bit 1 */

#define GPIO_PL_CFG_PCFG7_Pos					(30U)
#define GPIO_PL_CFG_PCFG7_Msk					(0x3UL << GPIO_PL_CFG_PCFG7_Pos)	/*!< 0xC0000000 */
#define GPIO_PL_CFG_PCFG7						GPIO_PL_CFG_PCFG7_Msk			/*!< CNF7[1:0] bits (Port x configuration bits, pin 7) */
#define GPIO_PL_CFG_PCFG7_0						((uint32_t) 0x40000000)			/*!< Bit 0 */
#define GPIO_PL_CFG_PCFG7_1						((uint32_t) 0x80000000)			/*!< Bit 1 */

/*****************  Bit definition for GPIO_PH_CFG register  ******************/
#define GPIO_PH_CFG_PMODE						((uint32_t) 0x33333333)			/*!< Port x mode bits */

#define GPIO_PH_CFG_PMODE8_Pos					(0U)
#define GPIO_PH_CFG_PMODE8_Msk					(0x3UL << GPIO_PH_CFG_PMODE8_Pos)	/*!< 0x00000003 */
#define GPIO_PH_CFG_PMODE8						GPIO_PH_CFG_PMODE8_Msk			/*!< MODE8[1:0] bits (Port x mode bits, pin 8) */
#define GPIO_PH_CFG_PMODE8_0					((uint32_t) 0x00000001)			/*!< Bit 0 */
#define GPIO_PH_CFG_PMODE8_1					((uint32_t) 0x00000002)			/*!< Bit 1 */

#define GPIO_PH_CFG_PMODE9_Pos					(4U)
#define GPIO_PH_CFG_PMODE9_Msk					(0x3UL << GPIO_PH_CFG_PMODE9_Pos)	/*!< 0x00000030 */
#define GPIO_PH_CFG_PMODE9						GPIO_PH_CFG_PMODE9_Msk			/*!< MODE9[1:0] bits (Port x mode bits, pin 9) */
#define GPIO_PH_CFG_PMODE9_0					((uint32_t) 0x00000010)			/*!< Bit 0 */
#define GPIO_PH_CFG_PMODE9_1					((uint32_t) 0x00000020)			/*!< Bit 1 */

#define GPIO_PH_CFG_PMODE10_Pos					(8U)
#define GPIO_PH_CFG_PMODE10_Msk					(0x3UL << GPIO_PH_CFG_PMODE10_Pos)	/*!< 0x00000300 */
#define GPIO_PH_CFG_PMODE10						GPIO_PH_CFG_PMODE10_Msk			/*!< MODE10[1:0] bits (Port x mode bits, pin 10) */
#define GPIO_PH_CFG_PMODE10_0					((uint32_t) 0x00000100)			/*!< Bit 0 */
#define GPIO_PH_CFG_PMODE10_1					((uint32_t) 0x00000200)			/*!< Bit 1 */

#define GPIO_PH_CFG_PMODE11_Pos					(12U)
#define GPIO_PH_CFG_PMODE11_Msk					(0x3UL << GPIO_PH_CFG_PMODE11_Pos)	/*!< 0x00003000 */
#define GPIO_PH_CFG_PMODE11						GPIO_PH_CFG_PMODE11_Msk			/*!< MODE11[1:0] bits (Port x mode bits, pin 11) */
#define GPIO_PH_CFG_PMODE11_0					((uint32_t) 0x00001000)			/*!< Bit 0 */
#define GPIO_PH_CFG_PMODE11_1					((uint32_t) 0x00002000)			/*!< Bit 1 */

#define GPIO_PH_CFG_PMODE12_Pos					(16U)
#define GPIO_PH_CFG_PMODE12_Msk					(0x3UL << GPIO_PH_CFG_PMODE12_Pos)	/*!< 0x00030000 */
#define GPIO_PH_CFG_PMODE12						GPIO_PH_CFG_PMODE12_Msk			/*!< MODE12[1:0] bits (Port x mode bits, pin 12) */
#define GPIO_PH_CFG_PMODE12_0					((uint32_t) 0x00010000)			/*!< Bit 0 */
#define GPIO_PH_CFG_PMODE12_1					((uint32_t) 0x00020000)			/*!< Bit 1 */

#define GPIO_PH_CFG_PMODE13_Pos					(20U)
#define GPIO_PH_CFG_PMODE13_Msk					(0x3UL << GPIO_PH_CFG_PMODE13_Pos)	/*!< 0x00300000 */
#define GPIO_PH_CFG_PMODE13						GPIO_PH_CFG_PMODE13_Msk			/*!< MODE13[1:0] bits (Port x mode bits, pin 13) */
#define GPIO_PH_CFG_PMODE13_0					((uint32_t) 0x00100000)			/*!< Bit 0 */
#define GPIO_PH_CFG_PMODE13_1					((uint32_t) 0x00200000)			/*!< Bit 1 */

#define GPIO_PH_CFG_PMODE14_Pos					(24U)
#define GPIO_PH_CFG_PMODE14_Msk					(0x3UL << GPIO_PH_CFG_PMODE14_Pos)	/*!< 0x03000000 */
#define GPIO_PH_CFG_PMODE14						GPIO_PH_CFG_PMODE14_Msk			/*!< MODE14[1:0] bits (Port x mode bits, pin 14) */
#define GPIO_PH_CFG_PMODE14_0					((uint32_t) 0x01000000)			/*!< Bit 0 */
#define GPIO_PH_CFG_PMODE14_1					((uint32_t) 0x02000000)			/*!< Bit 1 */

#define GPIO_PH_CFG_PMODE15_Pos					(28U)
#define GPIO_PH_CFG_PMODE15_Msk					(0x3UL << GPIO_PH_CFG_PMODE15_Pos)	/*!< 0x30000000 */
#define GPIO_PH_CFG_PMODE15						GPIO_PH_CFG_PMODE15_Msk			/*!< MODE15[1:0] bits (Port x mode bits, pin 15) */
#define GPIO_PH_CFG_PMODE15_0					((uint32_t) 0x10000000)			/*!< Bit 0 */
#define GPIO_PH_CFG_PMODE15_1					((uint32_t) 0x20000000)			/*!< Bit 1 */

#define GPIO_PH_CFG_PCFG						((uint32_t) 0xCCCCCCCC)			/*!< Port x configuration bits */

#define GPIO_PH_CFG_PCFG8_Pos					(2U)
#define GPIO_PH_CFG_PCFG8_Msk					(0x3UL << GPIO_PH_CFG_PCFG8_Pos)	/*!< 0x0000000C */
#define GPIO_PH_CFG_PCFG8						GPIO_PH_CFG_PCFG8_Msk			/*!< CNF8[1:0] bits (Port x configuration bits, pin 8) */
#define GPIO_PH_CFG_PCFG8_0						((uint32_t) 0x00000004)			/*!< Bit 0 */
#define GPIO_PH_CFG_PCFG8_1						((uint32_t) 0x00000008)			/*!< Bit 1 */

#define GPIO_PH_CFG_PCFG9_Pos					(6U)
#define GPIO_PH_CFG_PCFG9_Msk					(0x3UL << GPIO_PH_CFG_PCFG9_Pos)	/*!< 0x000000C0 */
#define GPIO_PH_CFG_PCFG9						GPIO_PH_CFG_PCFG9_Msk			/*!< CNF9[1:0] bits (Port x configuration bits, pin 9) */
#define GPIO_PH_CFG_PCFG9_0						((uint32_t) 0x00000040)			/*!< Bit 0 */
#define GPIO_PH_CFG_PCFG9_1						((uint32_t) 0x00000080)			/*!< Bit 1 */

#define GPIO_PH_CFG_PCFG10_Pos					(10U)
#define GPIO_PH_CFG_PCFG10_Msk					(0x3UL << GPIO_PH_CFG_PCFG10_Pos)	/*!< 0x00000C00 */
#define GPIO_PH_CFG_PCFG10						GPIO_PH_CFG_PCFG10_Msk			/*!< CNF10[1:0] bits (Port x configuration bits, pin 10) */
#define GPIO_PH_CFG_PCFG10_0					((uint32_t) 0x00000400)			/*!< Bit 0 */
#define GPIO_PH_CFG_PCFG10_1					((uint32_t) 0x00000800)			/*!< Bit 1 */

#define GPIO_PH_CFG_PCFG11_Pos					(14U)
#define GPIO_PH_CFG_PCFG11_Msk					(0x3UL << GPIO_PH_CFG_PCFG11_Pos)	/*!< 0x0000C000 */
#define GPIO_PH_CFG_PCFG11						GPIO_PH_CFG_PCFG11_Msk			/*!< CNF11[1:0] bits (Port x configuration bits, pin 11) */
#define GPIO_PH_CFG_PCFG11_0					((uint32_t) 0x00004000)			/*!< Bit 0 */
#define GPIO_PH_CFG_PCFG11_1					((uint32_t) 0x00008000)			/*!< Bit 1 */

#define GPIO_PH_CFG_PCFG12_Pos					(18U)
#define GPIO_PH_CFG_PCFG12_Msk					(0x3UL << GPIO_PH_CFG_PCFG12_Pos)	/*!< 0x000C0000 */
#define GPIO_PH_CFG_PCFG12						GPIO_PH_CFG_PCFG12_Msk			/*!< CNF12[1:0] bits (Port x configuration bits, pin 12) */
#define GPIO_PH_CFG_PCFG12_0					((uint32_t) 0x00040000)			/*!< Bit 0 */
#define GPIO_PH_CFG_PCFG12_1					((uint32_t) 0x00080000)			/*!< Bit 1 */

#define GPIO_PH_CFG_PCFG13_Pos					(22U)
#define GPIO_PH_CFG_PCFG13_Msk					(0x3UL << GPIO_PH_CFG_PCFG13_Pos)	/*!< 0x00C00000 */
#define GPIO_PH_CFG_PCFG13						GPIO_PH_CFG_PCFG13_Msk			/*!< CNF13[1:0] bits (Port x configuration bits, pin 13) */
#define GPIO_PH_CFG_PCFG13_0					((uint32_t) 0x00400000)			/*!< Bit 0 */
#define GPIO_PH_CFG_PCFG13_1					((uint32_t) 0x00800000)			/*!< Bit 1 */

#define GPIO_PH_CFG_PCFG14_Pos					(26U)
#define GPIO_PH_CFG_PCFG14_Msk					(0x3UL << GPIO_PH_CFG_PCFG14_Pos)	/*!< 0x0C000000 */
#define GPIO_PH_CFG_PCFG14						GPIO_PH_CFG_PCFG14_Msk			/*!< CNF14[1:0] bits (Port x configuration bits, pin 14) */
#define GPIO_PH_CFG_PCFG14_0					((uint32_t) 0x04000000)			/*!< Bit 0 */
#define GPIO_PH_CFG_PCFG14_1					((uint32_t) 0x08000000)			/*!< Bit 1 */

#define GPIO_PH_CFG_PCFG15_Pos					(30U)
#define GPIO_PH_CFG_PCFG15_Msk					(0x3UL << GPIO_PH_CFG_PCFG15_Pos)	/*!< 0xC0000000 */
#define GPIO_PH_CFG_PCFG15						GPIO_PH_CFG_PCFG15_Msk			/*!< CNF15[1:0] bits (Port x configuration bits, pin 15) */
#define GPIO_PH_CFG_PCFG15_0					((uint32_t) 0x40000000)			/*!< Bit 0 */
#define GPIO_PH_CFG_PCFG15_1					((uint32_t) 0x80000000)			/*!< Bit 1 */

/*******************  Bit definition for GPIO_PID register  *******************/
#define GPIO_PID_PID0_Pos						(0U)
#define GPIO_PID_PID0_Msk						(0x1UL << GPIO_PID_PID0_Pos)	/*!< 0x00000001 */
#define GPIO_PID_PID0							GPIO_PID_PID0_Msk				/*!< Port input data, bit 0 */
#define GPIO_PID_PID1_Pos						(1U)
#define GPIO_PID_PID1_Msk						(0x1UL << GPIO_PID_PID1_Pos)	/*!< 0x00000002 */
#define GPIO_PID_PID1							GPIO_PID_PID1_Msk				/*!< Port input data, bit 1 */
#define GPIO_PID_PID2_Pos						(2U)
#define GPIO_PID_PID2_Msk						(0x1UL << GPIO_PID_PID2_Pos)	/*!< 0x00000004 */
#define GPIO_PID_PID2							GPIO_PID_PID2_Msk				/*!< Port input data, bit 2 */
#define GPIO_PID_PID3_Pos						(3U)
#define GPIO_PID_PID3_Msk						(0x1UL << GPIO_PID_PID3_Pos)	/*!< 0x00000008 */
#define GPIO_PID_PID3							GPIO_PID_PID3_Msk				/*!< Port input data, bit 3 */
#define GPIO_PID_PID4_Pos						(4U)
#define GPIO_PID_PID4_Msk						(0x1UL << GPIO_PID_PID4_Pos)	/*!< 0x00000010 */
#define GPIO_PID_PID4							GPIO_PID_PID4_Msk				/*!< Port input data, bit 4 */
#define GPIO_PID_PID5_Pos						(5U)
#define GPIO_PID_PID5_Msk						(0x1UL << GPIO_PID_PID5_Pos)	/*!< 0x00000020 */
#define GPIO_PID_PID5							GPIO_PID_PID5_Msk				/*!< Port input data, bit 5 */
#define GPIO_PID_PID6_Pos						(6U)
#define GPIO_PID_PID6_Msk						(0x1UL << GPIO_PID_PID6_Pos)	/*!< 0x00000040 */
#define GPIO_PID_PID6							GPIO_PID_PID6_Msk				/*!< Port input data, bit 6 */
#define GPIO_PID_PID7_Pos						(7U)
#define GPIO_PID_PID7_Msk						(0x1UL << GPIO_PID_PID7_Pos)	/*!< 0x00000080 */
#define GPIO_PID_PID7							GPIO_PID_PID7_Msk				/*!< Port input data, bit 7 */
#define GPIO_PID_PID8_Pos						(8U)
#define GPIO_PID_PID8_Msk						(0x1UL << GPIO_PID_PID8_Pos)	/*!< 0x00000100 */
#define GPIO_PID_PID8							GPIO_PID_PID8_Msk				/*!< Port input data, bit 8 */
#define GPIO_PID_PID9_Pos						(9U)
#define GPIO_PID_PID9_Msk						(0x1UL << GPIO_PID_PID9_Pos)	/*!< 0x00000200 */
#define GPIO_PID_PID9							GPIO_PID_PID9_Msk				/*!< Port input data, bit 9 */
#define GPIO_PID_PID10_Pos						(10U)
#define GPIO_PID_PID10_Msk						(0x1UL << GPIO_PID_PID10_Pos)	/*!< 0x00000400 */
#define GPIO_PID_PID10							GPIO_PID_PID10_Msk				/*!< Port input data, bit 10 */
#define GPIO_PID_PID11_Pos						(11U)
#define GPIO_PID_PID11_Msk						(0x1UL << GPIO_PID_PID11_Pos)	/*!< 0x00000800 */
#define GPIO_PID_PID11							GPIO_PID_PID11_Msk				/*!< Port input data, bit 11 */
#define GPIO_PID_PID12_Pos						(12U)
#define GPIO_PID_PID12_Msk						(0x1UL << GPIO_PID_PID12_Pos)	/*!< 0x00001000 */
#define GPIO_PID_PID12							GPIO_PID_PID12_Msk				/*!< Port input data, bit 12 */
#define GPIO_PID_PID13_Pos						(13U)
#define GPIO_PID_PID13_Msk						(0x1UL << GPIO_PID_PID13_Pos)	/*!< 0x00002000 */
#define GPIO_PID_PID13							GPIO_PID_PID13_Msk				/*!< Port input data, bit 13 */
#define GPIO_PID_PID14_Pos						(14U)
#define GPIO_PID_PID14_Msk						(0x1UL << GPIO_PID_PID14_Pos)	/*!< 0x00004000 */
#define GPIO_PID_PID14							GPIO_PID_PID14_Msk				/*!< Port input data, bit 14 */
#define GPIO_PID_PID15_Pos						(15U)
#define GPIO_PID_PID15_Msk						(0x1UL << GPIO_PID_PID15_Pos)	/*!< 0x00008000 */
#define GPIO_PID_PID15							GPIO_PID_PID15_Msk				/*!< Port input data, bit 15 */

/*******************  Bit definition for GPIO_POD register  *******************/
#define GPIO_POD_POD0_Pos						(0U)
#define GPIO_POD_POD0_Msk						(0x1UL << GPIO_POD_POD0_Pos)	/*!< 0x00000001 */
#define GPIO_POD_POD0  							GPIO_POD_POD0_Msk				/*!< Port output data, bit 0 */
#define GPIO_POD_POD1_Pos						(1U)
#define GPIO_POD_POD1_Msk						(0x1UL << GPIO_POD_POD1_Pos)	/*!< 0x00000002 */
#define GPIO_POD_POD1  							GPIO_POD_POD1_Msk				/*!< Port output data, bit 1 */
#define GPIO_POD_POD2_Pos						(2U)
#define GPIO_POD_POD2_Msk						(0x1UL << GPIO_POD_POD2_Pos)	/*!< 0x00000004 */
#define GPIO_POD_POD2  							GPIO_POD_POD2_Msk				/*!< Port output data, bit 2 */
#define GPIO_POD_POD3_Pos						(3U)
#define GPIO_POD_POD3_Msk						(0x1UL << GPIO_POD_POD3_Pos)	/*!< 0x00000008 */
#define GPIO_POD_POD3  							GPIO_POD_POD3_Msk				/*!< Port output data, bit 3 */
#define GPIO_POD_POD4_Pos						(4U)
#define GPIO_POD_POD4_Msk						(0x1UL << GPIO_POD_POD4_Pos)	/*!< 0x00000010 */
#define GPIO_POD_POD4  							GPIO_POD_POD4_Msk				/*!< Port output data, bit 4 */
#define GPIO_POD_POD5_Pos						(5U)
#define GPIO_POD_POD5_Msk						(0x1UL << GPIO_POD_POD5_Pos)	/*!< 0x00000020 */
#define GPIO_POD_POD5  							GPIO_POD_POD5_Msk				/*!< Port output data, bit 5 */
#define GPIO_POD_POD6_Pos						(6U)
#define GPIO_POD_POD6_Msk						(0x1UL << GPIO_POD_POD6_Pos)	/*!< 0x00000040 */
#define GPIO_POD_POD6  							GPIO_POD_POD6_Msk				/*!< Port output data, bit 6 */
#define GPIO_POD_POD7_Pos						(7U)
#define GPIO_POD_POD7_Msk						(0x1UL << GPIO_POD_POD7_Pos)	/*!< 0x00000080 */
#define GPIO_POD_POD7  							GPIO_POD_POD7_Msk				/*!< Port output data, bit 7 */
#define GPIO_POD_POD8_Pos						(8U)
#define GPIO_POD_POD8_Msk						(0x1UL << GPIO_POD_POD8_Pos)	/*!< 0x00000100 */
#define GPIO_POD_POD8  							GPIO_POD_POD8_Msk				/*!< Port output data, bit 8 */
#define GPIO_POD_POD9_Pos						(9U)
#define GPIO_POD_POD9_Msk						(0x1UL << GPIO_POD_POD9_Pos)	/*!< 0x00000200 */
#define GPIO_POD_POD9  							GPIO_POD_POD9_Msk				/*!< Port output data, bit 9 */
#define GPIO_POD_POD10_Pos						(10U)
#define GPIO_POD_POD10_Msk						(0x1UL << GPIO_POD_POD10_Pos)	/*!< 0x00000400 */
#define GPIO_POD_POD10 							GPIO_POD_POD10_Msk				/*!< Port output data, bit 10 */
#define GPIO_POD_POD11_Pos						(11U)
#define GPIO_POD_POD11_Msk						(0x1UL << GPIO_POD_POD11_Pos)	/*!< 0x00000800 */
#define GPIO_POD_POD11 							GPIO_POD_POD11_Msk				/*!< Port output data, bit 11 */
#define GPIO_POD_POD12_Pos						(12U)
#define GPIO_POD_POD12_Msk						(0x1UL << GPIO_POD_POD12_Pos)	/*!< 0x00001000 */
#define GPIO_POD_POD12 							GPIO_POD_POD12_Msk				/*!< Port output data, bit 12 */
#define GPIO_POD_POD13_Pos						(13U)
#define GPIO_POD_POD13_Msk						(0x1UL << GPIO_POD_POD13_Pos)	/*!< 0x00002000 */
#define GPIO_POD_POD13 							GPIO_POD_POD13_Msk				/*!< Port output data, bit 13 */
#define GPIO_POD_POD14_Pos						(14U)
#define GPIO_POD_POD14_Msk						(0x1UL << GPIO_POD_POD14_Pos)	/*!< 0x00004000 */
#define GPIO_POD_POD14 							GPIO_POD_POD14_Msk				/*!< Port output data, bit 14 */
#define GPIO_POD_POD15_Pos						(15U)
#define GPIO_POD_POD15_Msk						(0x1UL << GPIO_POD_POD15_Pos)	/*!< 0x00008000 */
#define GPIO_POD_POD15 							GPIO_POD_POD15_Msk				/*!< Port output data, bit 15 */

/******************  Bit definition for GPIO_PBSC register  *******************/
#define GPIO_PBSC_PBS0_Pos						(0U)
#define GPIO_PBSC_PBS0_Msk						(0x1UL << GPIO_PBSC_PBS0_Pos)	/*!< 0x00000001 */
#define GPIO_PBSC_PBS0							GPIO_PBSC_PBS0_Msk				/*!< Port x Set bit 0 */
#define GPIO_PBSC_PBS1_Pos						(1U)
#define GPIO_PBSC_PBS1_Msk						(0x1UL << GPIO_PBSC_PBS1_Pos)	/*!< 0x00000002 */
#define GPIO_PBSC_PBS1							GPIO_PBSC_PBS1_Msk				/*!< Port x Set bit 1 */
#define GPIO_PBSC_PBS2_Pos						(2U)
#define GPIO_PBSC_PBS2_Msk						(0x1UL << GPIO_PBSC_PBS2_Pos)	/*!< 0x00000004 */
#define GPIO_PBSC_PBS2							GPIO_PBSC_PBS2_Msk				/*!< Port x Set bit 2 */
#define GPIO_PBSC_PBS3_Pos						(3U)
#define GPIO_PBSC_PBS3_Msk						(0x1UL << GPIO_PBSC_PBS3_Pos)	/*!< 0x00000008 */
#define GPIO_PBSC_PBS3							GPIO_PBSC_PBS3_Msk				/*!< Port x Set bit 3 */
#define GPIO_PBSC_PBS4_Pos						(4U)
#define GPIO_PBSC_PBS4_Msk						(0x1UL << GPIO_PBSC_PBS4_Pos)	/*!< 0x00000010 */
#define GPIO_PBSC_PBS4							GPIO_PBSC_PBS4_Msk				/*!< Port x Set bit 4 */
#define GPIO_PBSC_PBS5_Pos						(5U)
#define GPIO_PBSC_PBS5_Msk						(0x1UL << GPIO_PBSC_PBS5_Pos)	/*!< 0x00000020 */
#define GPIO_PBSC_PBS5							GPIO_PBSC_PBS5_Msk				/*!< Port x Set bit 5 */
#define GPIO_PBSC_PBS6_Pos						(6U)
#define GPIO_PBSC_PBS6_Msk						(0x1UL << GPIO_PBSC_PBS6_Pos)	/*!< 0x00000040 */
#define GPIO_PBSC_PBS6							GPIO_PBSC_PBS6_Msk				/*!< Port x Set bit 6 */
#define GPIO_PBSC_PBS7_Pos						(7U)
#define GPIO_PBSC_PBS7_Msk						(0x1UL << GPIO_PBSC_PBS7_Pos)	/*!< 0x00000080 */
#define GPIO_PBSC_PBS7							GPIO_PBSC_PBS7_Msk				/*!< Port x Set bit 7 */
#define GPIO_PBSC_PBS8_Pos						(8U)
#define GPIO_PBSC_PBS8_Msk						(0x1UL << GPIO_PBSC_PBS8_Pos)	/*!< 0x00000100 */
#define GPIO_PBSC_PBS8							GPIO_PBSC_PBS8_Msk				/*!< Port x Set bit 8 */
#define GPIO_PBSC_PBS9_Pos						(9U)
#define GPIO_PBSC_PBS9_Msk						(0x1UL << GPIO_PBSC_PBS9_Pos)	/*!< 0x00000200 */
#define GPIO_PBSC_PBS9							GPIO_PBSC_PBS9_Msk				/*!< Port x Set bit 9 */
#define GPIO_PBSC_PBS10_Pos						(10U)
#define GPIO_PBSC_PBS10_Msk						(0x1UL << GPIO_PBSC_PBS10_Pos)	/*!< 0x00000400 */
#define GPIO_PBSC_PBS10							GPIO_PBSC_PBS10_Msk				/*!< Port x Set bit 10 */
#define GPIO_PBSC_PBS11_Pos						(11U)
#define GPIO_PBSC_PBS11_Msk						(0x1UL << GPIO_PBSC_PBS11_Pos)	/*!< 0x00000800 */
#define GPIO_PBSC_PBS11							GPIO_PBSC_PBS11_Msk				/*!< Port x Set bit 11 */
#define GPIO_PBSC_PBS12_Pos						(12U)
#define GPIO_PBSC_PBS12_Msk						(0x1UL << GPIO_PBSC_PBS12_Pos)	/*!< 0x00001000 */
#define GPIO_PBSC_PBS12							GPIO_PBSC_PBS12_Msk				/*!< Port x Set bit 12 */
#define GPIO_PBSC_PBS13_Pos						(13U)
#define GPIO_PBSC_PBS13_Msk						(0x1UL << GPIO_PBSC_PBS13_Pos)	/*!< 0x00002000 */
#define GPIO_PBSC_PBS13							GPIO_PBSC_PBS13_Msk				/*!< Port x Set bit 13 */
#define GPIO_PBSC_PBS14_Pos						(14U)
#define GPIO_PBSC_PBS14_Msk						(0x1UL << GPIO_PBSC_PBS14_Pos)	/*!< 0x00004000 */
#define GPIO_PBSC_PBS14							GPIO_PBSC_PBS14_Msk				/*!< Port x Set bit 14 */
#define GPIO_PBSC_PBS15_Pos						(15U)
#define GPIO_PBSC_PBS15_Msk						(0x1UL << GPIO_PBSC_PBS15_Pos)	/*!< 0x00008000 */
#define GPIO_PBSC_PBS15							GPIO_PBSC_PBS15_Msk				/*!< Port x Set bit 15 */

#define GPIO_PBSC_PBC0_Pos						(16U)
#define GPIO_PBSC_PBC0_Msk						(0x1UL << GPIO_PBSC_PBC0_Pos)	/*!< 0x00010000 */
#define GPIO_PBSC_PBC0							GPIO_PBSC_PBC0_Msk				/*!< Port x Reset bit 0 */
#define GPIO_PBSC_PBC1_Pos						(17U)
#define GPIO_PBSC_PBC1_Msk						(0x1UL << GPIO_PBSC_PBC1_Pos)	/*!< 0x00020000 */
#define GPIO_PBSC_PBC1							GPIO_PBSC_PBC1_Msk				/*!< Port x Reset bit 1 */
#define GPIO_PBSC_PBC2_Pos						(18U)
#define GPIO_PBSC_PBC2_Msk						(0x1UL << GPIO_PBSC_PBC2_Pos)	/*!< 0x00040000 */
#define GPIO_PBSC_PBC2							GPIO_PBSC_PBC2_Msk				/*!< Port x Reset bit 2 */
#define GPIO_PBSC_PBC3_Pos						(19U)
#define GPIO_PBSC_PBC3_Msk						(0x1UL << GPIO_PBSC_PBC3_Pos)	/*!< 0x00080000 */
#define GPIO_PBSC_PBC3							GPIO_PBSC_PBC3_Msk				/*!< Port x Reset bit 3 */
#define GPIO_PBSC_PBC4_Pos						(20U)
#define GPIO_PBSC_PBC4_Msk						(0x1UL << GPIO_PBSC_PBC4_Pos)	/*!< 0x00100000 */
#define GPIO_PBSC_PBC4							GPIO_PBSC_PBC4_Msk				/*!< Port x Reset bit 4 */
#define GPIO_PBSC_PBC5_Pos						(21U)
#define GPIO_PBSC_PBC5_Msk						(0x1UL << GPIO_PBSC_PBC5_Pos)	/*!< 0x00200000 */
#define GPIO_PBSC_PBC5							GPIO_PBSC_PBC5_Msk				/*!< Port x Reset bit 5 */
#define GPIO_PBSC_PBC6_Pos						(22U)
#define GPIO_PBSC_PBC6_Msk						(0x1UL << GPIO_PBSC_PBC6_Pos)	/*!< 0x00400000 */
#define GPIO_PBSC_PBC6							GPIO_PBSC_PBC6_Msk				/*!< Port x Reset bit 6 */
#define GPIO_PBSC_PBC7_Pos						(23U)
#define GPIO_PBSC_PBC7_Msk						(0x1UL << GPIO_PBSC_PBC7_Pos)	/*!< 0x00800000 */
#define GPIO_PBSC_PBC7							GPIO_PBSC_PBC7_Msk				/*!< Port x Reset bit 7 */
#define GPIO_PBSC_PBC8_Pos						(24U)
#define GPIO_PBSC_PBC8_Msk						(0x1UL << GPIO_PBSC_PBC8_Pos)	/*!< 0x01000000 */
#define GPIO_PBSC_PBC8							GPIO_PBSC_PBC8_Msk				/*!< Port x Reset bit 8 */
#define GPIO_PBSC_PBC9_Pos						(25U)
#define GPIO_PBSC_PBC9_Msk						(0x1UL << GPIO_PBSC_PBC9_Pos)	/*!< 0x02000000 */
#define GPIO_PBSC_PBC9							GPIO_PBSC_PBC9_Msk				/*!< Port x Reset bit 9 */
#define GPIO_PBSC_PBC10_Pos						(26U)
#define GPIO_PBSC_PBC10_Msk						(0x1UL << GPIO_PBSC_PBC10_Pos)	/*!< 0x04000000 */
#define GPIO_PBSC_PBC10							GPIO_PBSC_PBC10_Msk				/*!< Port x Reset bit 10 */
#define GPIO_PBSC_PBC11_Pos						(27U)
#define GPIO_PBSC_PBC11_Msk						(0x1UL << GPIO_PBSC_PBC11_Pos)	/*!< 0x08000000 */
#define GPIO_PBSC_PBC11							GPIO_PBSC_PBC11_Msk				/*!< Port x Reset bit 11 */
#define GPIO_PBSC_PBC12_Pos						(28U)
#define GPIO_PBSC_PBC12_Msk						(0x1UL << GPIO_PBSC_PBC12_Pos)	/*!< 0x10000000 */
#define GPIO_PBSC_PBC12							GPIO_PBSC_PBC12_Msk				/*!< Port x Reset bit 12 */
#define GPIO_PBSC_PBC13_Pos						(29U)
#define GPIO_PBSC_PBC13_Msk						(0x1UL << GPIO_PBSC_PBC13_Pos)	/*!< 0x20000000 */
#define GPIO_PBSC_PBC13							GPIO_PBSC_PBC13_Msk				/*!< Port x Reset bit 13 */
#define GPIO_PBSC_PBC14_Pos						(30U)
#define GPIO_PBSC_PBC14_Msk						(0x1UL << GPIO_PBSC_PBC14_Pos)	/*!< 0x40000000 */
#define GPIO_PBSC_PBC14							GPIO_PBSC_PBC14_Msk				/*!< Port x Reset bit 14 */
#define GPIO_PBSC_PBC15_Pos						(31U)
#define GPIO_PBSC_PBC15_Msk						(0x1UL << GPIO_PBSC_PBC15_Pos)	/*!< 0x80000000 */
#define GPIO_PBSC_PBC15							GPIO_PBSC_PBC15_Msk				/*!< Port x Reset bit 15 */

/*******************  Bit definition for GPIO_PBC register  *******************/
#define GPIO_PBC_PBC0_Pos						(0U)
#define GPIO_PBC_PBC0_Msk						(0x1UL << GPIO_PBC_PBC0_Pos)	/*!< 0x00000001 */
#define GPIO_PBC_PBC0							GPIO_PBC_PBC0_Msk				/*!< Port x Reset bit 0 */
#define GPIO_PBC_PBC1_Pos						(1U)
#define GPIO_PBC_PBC1_Msk						(0x1UL << GPIO_PBC_PBC1_Pos)	/*!< 0x00000002 */
#define GPIO_PBC_PBC1							GPIO_PBC_PBC1_Msk				/*!< Port x Reset bit 1 */
#define GPIO_PBC_PBC2_Pos						(2U)
#define GPIO_PBC_PBC2_Msk						(0x1UL << GPIO_PBC_PBC2_Pos)	/*!< 0x00000004 */
#define GPIO_PBC_PBC2							GPIO_PBC_PBC2_Msk				/*!< Port x Reset bit 2 */
#define GPIO_PBC_PBC3_Pos						(3U)
#define GPIO_PBC_PBC3_Msk						(0x1UL << GPIO_PBC_PBC3_Pos)	/*!< 0x00000008 */
#define GPIO_PBC_PBC3							GPIO_PBC_PBC3_Msk				/*!< Port x Reset bit 3 */
#define GPIO_PBC_PBC4_Pos						(4U)
#define GPIO_PBC_PBC4_Msk						(0x1UL << GPIO_PBC_PBC4_Pos)	/*!< 0x00000010 */
#define GPIO_PBC_PBC4							GPIO_PBC_PBC4_Msk				/*!5< Port x Reset bit 4 */
#define GPIO_PBC_PBC5_Pos						(5U)
#define GPIO_PBC_PBC5_Msk						(0x1UL << GPIO_PBC_PBC5_Pos)	/*!< 0x00000020 */
#define GPIO_PBC_PBC5							GPIO_PBC_PBC5_Msk				/*!< Port x Reset bit 5 */
#define GPIO_PBC_PBC6_Pos						(6U)
#define GPIO_PBC_PBC6_Msk						(0x1UL << GPIO_PBC_PBC6_Pos)	/*!< 0x00000040 */
#define GPIO_PBC_PBC6							GPIO_PBC_PBC6_Msk				/*!< Port x Reset bit 6 */
#define GPIO_PBC_PBC7_Pos						(7U)
#define GPIO_PBC_PBC7_Msk						(0x1UL << GPIO_PBC_PBC7_Pos)	/*!< 0x00000080 */
#define GPIO_PBC_PBC7							GPIO_PBC_PBC7_Msk				/*!< Port x Reset bit 7 */
#define GPIO_PBC_PBC8_Pos						(8U)
#define GPIO_PBC_PBC8_Msk						(0x1UL << GPIO_PBC_PBC8_Pos)	/*!< 0x00000100 */
#define GPIO_PBC_PBC8							GPIO_PBC_PBC8_Msk				/*!< Port x Reset bit 8 */
#define GPIO_PBC_PBC9_Pos						(9U)
#define GPIO_PBC_PBC9_Msk						(0x1UL << GPIO_PBC_PBC9_Pos)	/*!< 0x00000200 */
#define GPIO_PBC_PBC9							GPIO_PBC_PBC9_Msk				/*!< Port x Reset bit 9 */
#define GPIO_PBC_PBC10_Pos						(10U)
#define GPIO_PBC_PBC10_Msk						(0x1UL << GPIO_PBC_PBC10_Pos)	/*!< 0x00000400 */
#define GPIO_PBC_PBC10							GPIO_PBC_PBC10_Msk				/*!< Port x Reset bit 10 */
#define GPIO_PBC_PBC11_Pos						(11U)
#define GPIO_PBC_PBC11_Msk						(0x1UL << GPIO_PBC_PBC11_Pos)	/*!< 0x00000800 */
#define GPIO_PBC_PBC11							GPIO_PBC_PBC11_Msk				/*!< Port x Reset bit 11 */
#define GPIO_PBC_PBC12_Pos						(12U)
#define GPIO_PBC_PBC12_Msk						(0x1UL << GPIO_PBC_PBC12_Pos)	/*!< 0x00001000 */
#define GPIO_PBC_PBC12							GPIO_PBC_PBC12_Msk				/*!< Port x Reset bit 12 */
#define GPIO_PBC_PBC13_Pos						(13U)
#define GPIO_PBC_PBC13_Msk						(0x1UL << GPIO_PBC_PBC13_Pos)	/*!< 0x00002000 */
#define GPIO_PBC_PBC13							GPIO_PBC_PBC13_Msk				/*!< Port x Reset bit 13 */
#define GPIO_PBC_PBC14_Pos						(14U)
#define GPIO_PBC_PBC14_Msk						(0x1UL << GPIO_PBC_PBC14_Pos)	/*!< 0x00004000 */
#define GPIO_PBC_PBC14							GPIO_PBC_PBC14_Msk				/*!< Port x Reset bit 14 */
#define GPIO_PBC_PBC15_Pos						(15U)
#define GPIO_PBC_PBC15_Msk						(0x1UL << GPIO_PBC_PBC15_Pos)	/*!< 0x00008000 */
#define GPIO_PBC_PBC15							GPIO_PBC_PBC15_Msk				/*!< Port x Reset bit 15 */

/****************  Bit definition for GPIO_PLOCK_CFG register  ****************/
#define GPIO_PLOCK_CFG_PLOCK_CFG0_Pos			(0U)
#define GPIO_PLOCK_CFG_PLOCK_CFG0_Msk			(0x1UL << GPIO_PLOCK_CFG_PLOCK_CFG0_Pos)
#define GPIO_PLOCK_CFG_PLOCK_CFG0				GPIO_PLOCK_CFG_PLOCK_CFG0_Msk	/*!< Port x Lock bit 0 */
#define GPIO_PLOCK_CFG_PLOCK_CFG1_Pos			(1U)
#define GPIO_PLOCK_CFG_PLOCK_CFG1_Msk			(0x1UL << GPIO_PLOCK_CFG_PLOCK_CFG1_Pos)
#define GPIO_PLOCK_CFG_PLOCK_CFG1				GPIO_PLOCK_CFG_PLOCK_CFG1_Msk	/*!< Port x Lock bit 1 */
#define GPIO_PLOCK_CFG_PLOCK_CFG2_Pos			(2U)
#define GPIO_PLOCK_CFG_PLOCK_CFG2_Msk			(0x1UL << GPIO_PLOCK_CFG_PLOCK_CFG2_Pos)
#define GPIO_PLOCK_CFG_PLOCK_CFG2				GPIO_PLOCK_CFG_PLOCK_CFG2_Msk	/*!< Port x Lock bit 2 */
#define GPIO_PLOCK_CFG_PLOCK_CFG3_Pos			(3U)
#define GPIO_PLOCK_CFG_PLOCK_CFG3_Msk			(0x1UL << GPIO_PLOCK_CFG_PLOCK_CFG3_Pos)
#define GPIO_PLOCK_CFG_PLOCK_CFG3				GPIO_PLOCK_CFG_PLOCK_CFG3_Msk	/*!< Port x Lock bit 3 */
#define GPIO_PLOCK_CFG_PLOCK_CFG4_Pos			(4U)
#define GPIO_PLOCK_CFG_PLOCK_CFG4_Msk			(0x1UL << GPIO_PLOCK_CFG_PLOCK_CFG4_Pos)
#define GPIO_PLOCK_CFG_PLOCK_CFG4				GPIO_PLOCK_CFG_PLOCK_CFG4_Msk	/*!< Port x Lock bit 4 */
#define GPIO_PLOCK_CFG_PLOCK_CFG5_Pos			(5U)
#define GPIO_PLOCK_CFG_PLOCK_CFG5_Msk			(0x1UL << GPIO_PLOCK_CFG_PLOCK_CFG5_Pos)
#define GPIO_PLOCK_CFG_PLOCK_CFG5				GPIO_PLOCK_CFG_PLOCK_CFG5_Msk	/*!< Port x Lock bit 5 */
#define GPIO_PLOCK_CFG_PLOCK_CFG6_Pos			(6U)
#define GPIO_PLOCK_CFG_PLOCK_CFG6_Msk			(0x1UL << GPIO_PLOCK_CFG_PLOCK_CFG6_Pos)
#define GPIO_PLOCK_CFG_PLOCK_CFG6				GPIO_PLOCK_CFG_PLOCK_CFG6_Msk	/*!< Port x Lock bit 6 */
#define GPIO_PLOCK_CFG_PLOCK_CFG7_Pos			(7U)
#define GPIO_PLOCK_CFG_PLOCK_CFG7_Msk			(0x1UL << GPIO_PLOCK_CFG_PLOCK_CFG7_Pos)
#define GPIO_PLOCK_CFG_PLOCK_CFG7				GPIO_PLOCK_CFG_PLOCK_CFG7_Msk	/*!< Port x Lock bit 7 */
#define GPIO_PLOCK_CFG_PLOCK_CFG8_Pos			(8U)
#define GPIO_PLOCK_CFG_PLOCK_CFG8_Msk			(0x1UL << GPIO_PLOCK_CFG_PLOCK_CFG8_Pos)
#define GPIO_PLOCK_CFG_PLOCK_CFG8				GPIO_PLOCK_CFG_PLOCK_CFG8_Msk	/*!< Port x Lock bit 8 */
#define GPIO_PLOCK_CFG_PLOCK_CFG9_Pos			(9U)
#define GPIO_PLOCK_CFG_PLOCK_CFG9_Msk			(0x1UL << GPIO_PLOCK_CFG_PLOCK_CFG9_Pos)
#define GPIO_PLOCK_CFG_PLOCK_CFG9				GPIO_PLOCK_CFG_PLOCK_CFG9_Msk	/*!< Port x Lock bit 9 */
#define GPIO_PLOCK_CFG_PLOCK_CFG10_Pos			(10U)
#define GPIO_PLOCK_CFG_PLOCK_CFG10_Msk			(0x1UL << GPIO_PLOCK_CFG_PLOCK_CFG10_Pos)
#define GPIO_PLOCK_CFG_PLOCK_CFG10				GPIO_PLOCK_CFG_PLOCK_CFG10_Msk	/*!< Port x Lock bit 10 */
#define GPIO_PLOCK_CFG_PLOCK_CFG11_Pos			(11U)
#define GPIO_PLOCK_CFG_PLOCK_CFG11_Msk			(0x1UL << GPIO_PLOCK_CFG_PLOCK_CFG11_Pos)
#define GPIO_PLOCK_CFG_PLOCK_CFG11				GPIO_PLOCK_CFG_PLOCK_CFG11_Msk	/*!< Port x Lock bit 11 */
#define GPIO_PLOCK_CFG_PLOCK_CFG12_Pos			(12U)
#define GPIO_PLOCK_CFG_PLOCK_CFG12_Msk			(0x1UL << GPIO_PLOCK_CFG_PLOCK_CFG12_Pos)
#define GPIO_PLOCK_CFG_PLOCK_CFG12				GPIO_PLOCK_CFG_PLOCK_CFG12_Msk	/*!< Port x Lock bit 12 */
#define GPIO_PLOCK_CFG_PLOCK_CFG13_Pos			(13U)
#define GPIO_PLOCK_CFG_PLOCK_CFG13_Msk			(0x1UL << GPIO_PLOCK_CFG_PLOCK_CFG13_Pos)
#define GPIO_PLOCK_CFG_PLOCK_CFG13				GPIO_PLOCK_CFG_PLOCK_CFG13_Msk	/*!< Port x Lock bit 13 */
#define GPIO_PLOCK_CFG_PLOCK_CFG14_Pos			(14U)
#define GPIO_PLOCK_CFG_PLOCK_CFG14_Msk			(0x1UL << GPIO_PLOCK_CFG_PLOCK_CFG14_Pos)
#define GPIO_PLOCK_CFG_PLOCK_CFG14				GPIO_PLOCK_CFG_PLOCK_CFG14_Msk	/*!< Port x Lock bit 14 */
#define GPIO_PLOCK_CFG_PLOCK_CFG15_Pos			(15U)
#define GPIO_PLOCK_CFG_PLOCK_CFG15_Msk			(0x1UL << GPIO_PLOCK_CFG_PLOCK_CFG15_Pos)
#define GPIO_PLOCK_CFG_PLOCK_CFG15				GPIO_PLOCK_CFG_PLOCK_CFG15_Msk	/*!< Port x Lock bit 15 */
#define GPIO_PLOCK_CFG_PLOCKK_CFG_Pos			(16U)
#define GPIO_PLOCK_CFG_PLOCKK_CFG_Msk			(0x1UL << GPIO_PLOCK_CFG_PLOCKK_CFG_Pos)
#define GPIO_PLOCK_CFG_PLOCKK_CFG				GPIO_PLOCK_CFG_PLOCKK_CFG_Msk	/*!< Lock key */

/*****************  Bit definition for GPIO_DS_CFG register  ******************/
#define GPIO_DS_CFG_DS_CFG0_Pos					(0U)
#define GPIO_DS_CFG_DS_CFG0_Msk					(0x1UL << GPIO_DS_CFG_DS_CFG0_Pos)	/*!< 0x00000001 */
#define GPIO_DS_CFG_DS_CFG0						GPIO_DS_CFG_DS_CFG0_Msk			/*!< Port x Drive bit 0 */
#define GPIO_DS_CFG_DS_CFG1_Pos					(1U)
#define GPIO_DS_CFG_DS_CFG1_Msk					(0x1UL << GPIO_DS_CFG_DS_CFG1_Pos)	/*!< 0x00000002 */
#define GPIO_DS_CFG_DS_CFG1  					GPIO_DS_CFG_DS_CFG1_Msk			/*!< Port x Drive bit 1 */
#define GPIO_DS_CFG_DS_CFG2_Pos					(2U)
#define GPIO_DS_CFG_DS_CFG2_Msk					(0x1UL << GPIO_DS_CFG_DS_CFG2_Pos)	/*!< 0x00000004 */
#define GPIO_DS_CFG_DS_CFG2  					GPIO_DS_CFG_DS_CFG2_Msk			/*!< Port x Drive bit 2 */
#define GPIO_DS_CFG_DS_CFG3_Pos					(3U)
#define GPIO_DS_CFG_DS_CFG3_Msk					(0x1UL << GPIO_DS_CFG_DS_CFG3_Pos)	/*!< 0x00000008 */
#define GPIO_DS_CFG_DS_CFG3  					GPIO_DS_CFG_DS_CFG3_Msk			/*!< Port x Drive bit 3 */
#define GPIO_DS_CFG_DS_CFG4_Pos					(4U)
#define GPIO_DS_CFG_DS_CFG4_Msk					(0x1UL << GPIO_DS_CFG_DS_CFG4_Pos)	/*!< 0x00000010 */
#define GPIO_DS_CFG_DS_CFG4  					GPIO_DS_CFG_DS_CFG4_Msk			/*!< Port x Drive bit 4 */
#define GPIO_DS_CFG_DS_CFG5_Pos					(5U)
#define GPIO_DS_CFG_DS_CFG5_Msk					(0x1UL << GPIO_DS_CFG_DS_CFG5_Pos)	/*!< 0x00000020 */
#define GPIO_DS_CFG_DS_CFG5  					GPIO_DS_CFG_DS_CFG5_Msk			/*!< Port x Drive bit 5 */
#define GPIO_DS_CFG_DS_CFG6_Pos					(6U)
#define GPIO_DS_CFG_DS_CFG6_Msk					(0x1UL << GPIO_DS_CFG_DS_CFG6_Pos)	/*!< 0x00000040 */
#define GPIO_DS_CFG_DS_CFG6  					GPIO_DS_CFG_DS_CFG6_Msk			/*!< Port x Drive bit 6 */
#define GPIO_DS_CFG_DS_CFG7_Pos					(7U)
#define GPIO_DS_CFG_DS_CFG7_Msk					(0x1UL << GPIO_DS_CFG_DS_CFG7_Pos)	/*!< 0x00000080 */
#define GPIO_DS_CFG_DS_CFG7  					GPIO_DS_CFG_DS_CFG7_Msk			/*!< Port x Drive bit 7 */
#define GPIO_DS_CFG_DS_CFG8_Pos					(8U)
#define GPIO_DS_CFG_DS_CFG8_Msk					(0x1UL << GPIO_DS_CFG_DS_CFG8_Pos)	/*!< 0x00000100 */
#define GPIO_DS_CFG_DS_CFG8  					GPIO_DS_CFG_DS_CFG8_Msk			/*!< Port x Drive bit 8 */
#define GPIO_DS_CFG_DS_CFG9_Pos					(9U)
#define GPIO_DS_CFG_DS_CFG9_Msk					(0x1UL << GPIO_DS_CFG_DS_CFG9_Pos)	/*!< 0x00000200 */
#define GPIO_DS_CFG_DS_CFG9 					GPIO_DS_CFG_DS_CFG9_Msk			/*!< Port x Drive bit 9 */
#define GPIO_DS_CFG_DS_CFG10_Pos				(10U)
#define GPIO_DS_CFG_DS_CFG10_Msk				(0x1UL << GPIO_DS_CFG_DS_CFG10_Pos)	/*!< 0x00000400 */
#define GPIO_DS_CFG_DS_CFG10 					GPIO_DS_CFG_DS_CFG10_Msk		/*!< Port x Drive bit 10 */
#define GPIO_DS_CFG_DS_CFG11_Pos				(11U)
#define GPIO_DS_CFG_DS_CFG11_Msk				(0x1UL << GPIO_DS_CFG_DS_CFG11_Pos)	/*!< 0x00000800 */
#define GPIO_DS_CFG_DS_CFG11 					GPIO_DS_CFG_DS_CFG11_Msk		/*!< Port x Drive bit 11 */
#define GPIO_DS_CFG_DS_CFG12_Pos				(12U)
#define GPIO_DS_CFG_DS_CFG12_Msk				(0x1UL << GPIO_DS_CFG_DS_CFG12_Pos)	/*!< 0x00001000 */
#define GPIO_DS_CFG_DS_CFG12 					GPIO_DS_CFG_DS_CFG12_Msk		/*!< Port x Drive bit 12 */
#define GPIO_DS_CFG_DS_CFG13_Pos				(13U)
#define GPIO_DS_CFG_DS_CFG13_Msk				(0x1UL << GPIO_DS_CFG_DS_CFG13_Pos)	/*!< 0x00002000 */
#define GPIO_DS_CFG_DS_CFG13 					GPIO_DS_CFG_DS_CFG13_Msk		/*!< Port x Drive bit 13 */
#define GPIO_DS_CFG_DS_CFG14_Pos				(14U)
#define GPIO_DS_CFG_DS_CFG14_Msk				(0x1UL << GPIO_DS_CFG_DS_CFG14_Pos)	/*!< 0x00004000 */
#define GPIO_DS_CFG_DS_CFG14 					GPIO_DS_CFG_DS_CFG14_Msk		/*!< Port x Drive bit 14 */
#define GPIO_DS_CFG_DS_CFG15_Pos				(15U)
#define GPIO_DS_CFG_DS_CFG15_Msk				(0x1UL << GPIO_DS_CFG_DS_CFG15_Pos)	/*!< 0x00008000 */
#define GPIO_DS_CFG_DS_CFG15 					GPIO_DS_CFG_DS_CFG15_Msk		/*!< Port x Drive bit 15 */

/*****************  Bit definition for GPIO_SR_CFG register  ******************/
#define GPIO_SR_CFG_SR_CFG0_Pos					(0U)
#define GPIO_SR_CFG_SR_CFG0_Msk					(0x1UL << GPIO_SR_CFG_SR_CFG0_Pos)	/*!< 0x00000001 */
#define GPIO_SR_CFG_SR_CFG0  					GPIO_SR_CFG_SR_CFG0_Msk			/*!< Port x Turn bit 0 */
#define GPIO_SR_CFG_SR_CFG1_Pos					(1U)
#define GPIO_SR_CFG_SR_CFG1_Msk					(0x1UL << GPIO_SR_CFG_SR_CFG1_Pos)	/*!< 0x00000002 */
#define GPIO_SR_CFG_SR_CFG1  					GPIO_SR_CFG_SR_CFG1_Msk			/*!< Port x Turn bit 1 */
#define GPIO_SR_CFG_SR_CFG2_Pos					(2U)
#define GPIO_SR_CFG_SR_CFG2_Msk					(0x1UL << GPIO_SR_CFG_SR_CFG2_Pos)	/*!< 0x00000004 */
#define GPIO_SR_CFG_SR_CFG2 					GPIO_SR_CFG_SR_CFG2_Msk			/*!< Port x Turn bit 2 */
#define GPIO_SR_CFG_SR_CFG3_Pos					(3U)
#define GPIO_SR_CFG_SR_CFG3_Msk					(0x1UL << GPIO_SR_CFG_SR_CFG3_Pos)	/*!< 0x00000008 */
#define GPIO_SR_CFG_SR_CFG3  					GPIO_SR_CFG_SR_CFG3_Msk			/*!< Port x Turn bit 3 */
#define GPIO_SR_CFG_SR_CFG4_Pos					(4U)
#define GPIO_SR_CFG_SR_CFG4_Msk					(0x1UL << GPIO_SR_CFG_SR_CFG4_Pos)	/*!< 0x00000010 */
#define GPIO_SR_CFG_SR_CFG4  					GPIO_SR_CFG_SR_CFG4_Msk			/*!< Port x Turn bit 4 */
#define GPIO_SR_CFG_SR_CFG5_Pos					(5U)
#define GPIO_SR_CFG_SR_CFG5_Msk					(0x1UL << GPIO_SR_CFG_SR_CFG5_Pos)	/*!< 0x00000020 */
#define GPIO_SR_CFG_SR_CFG5 					GPIO_SR_CFG_SR_CFG5_Msk			/*!< Port x Turn bit 5 */
#define GPIO_SR_CFG_SR_CFG6_Pos					(6U)
#define GPIO_SR_CFG_SR_CFG6_Msk					(0x1UL << GPIO_SR_CFG_SR_CFG6_Pos)	/*!< 0x00000040 */
#define GPIO_SR_CFG_SR_CFG6  					GPIO_SR_CFG_SR_CFG6_Msk			/*!< Port x Turn bit 6 */
#define GPIO_SR_CFG_SR_CFG7_Pos					(7U)
#define GPIO_SR_CFG_SR_CFG7_Msk					(0x1UL << GPIO_SR_CFG_SR_CFG7_Pos)	/*!< 0x00000080 */
#define GPIO_SR_CFG_SR_CFG7  					GPIO_SR_CFG_SR_CFG7_Msk			/*!< Port x Turn bit 7 */
#define GPIO_SR_CFG_SR_CFG8_Pos					(8U)
#define GPIO_SR_CFG_SR_CFG8_Msk					(0x1UL << GPIO_SR_CFG_SR_CFG8_Pos)	/*!< 0x00000100 */
#define GPIO_SR_CFG_SR_CFG8  					GPIO_SR_CFG_SR_CFG8_Msk			/*!< Port x Turn bit 8 */
#define GPIO_SR_CFG_SR_CFG9_Pos					(9U)
#define GPIO_SR_CFG_SR_CFG9_Msk					(0x1UL << GPIO_SR_CFG_SR_CFG9_Pos)	/*!< 0x00000200 */
#define GPIO_SR_CFG_SR_CFG9  					GPIO_SR_CFG_SR_CFG9_Msk			/*!< Port x Turn bit 9 */
#define GPIO_SR_CFG_SR_CFG10_Pos				(10U)
#define GPIO_SR_CFG_SR_CFG10_Msk				(0x1UL << GPIO_SR_CFG_SR_CFG10_Pos)	/*!< 0x00000400 */
#define GPIO_SR_CFG_SR_CFG10 					GPIO_SR_CFG_SR_CFG10_Msk		/*!< Port x Turn bit 10 */
#define GPIO_SR_CFG_SR_CFG11_Pos				(11U)
#define GPIO_SR_CFG_SR_CFG11_Msk				(0x1UL << GPIO_SR_CFG_SR_CFG11_Pos)	/*!< 0x00000800 */
#define GPIO_SR_CFG_SR_CFG11 					GPIO_SR_CFG_SR_CFG11_Msk		/*!< Port x Turn bit 11 */
#define GPIO_SR_CFG_SR_CFG12_Pos				(12U)
#define GPIO_SR_CFG_SR_CFG12_Msk				(0x1UL << GPIO_SR_CFG_SR_CFG12_Pos)	/*!< 0x00001000 */
#define GPIO_SR_CFG_SR_CFG12 					GPIO_SR_CFG_SR_CFG12_Msk		/*!< Port x Turn bit 12 */
#define GPIO_SR_CFG_SR_CFG13_Pos				(13U)
#define GPIO_SR_CFG_SR_CFG13_Msk				(0x1UL << GPIO_SR_CFG_SR_CFG13_Pos)	/*!< 0x00002000 */
#define GPIO_SR_CFG_SR_CFG13					GPIO_SR_CFG_SR_CFG13_Msk		/*!< Port x Turn bit 13 */
#define GPIO_SR_CFG_SR_CFG14_Pos				(14U)
#define GPIO_SR_CFG_SR_CFG14_Msk				(0x1UL << GPIO_SR_CFG_SR_CFG14_Pos)	/*!< 0x00004000 */
#define GPIO_SR_CFG_SR_CFG14 					GPIO_SR_CFG_SR_CFG14_Msk		/*!< Port x Turn bit 14 */
#define GPIO_SR_CFG_SR_CFG15_Pos				(15U)
#define GPIO_SR_CFG_SR_CFG15_Msk				(0x1UL << GPIO_SR_CFG_SR_CFG15_Pos)	/*!< 0x00008000 */
#define GPIO_SR_CFG_SR_CFG15 					GPIO_SR_CFG_SR_CFG15_Msk		/*!< Port x Turn bit 15 */

/*------------------------------ AFIO registers ------------------------------*/
/******************  Bit definition for AFIO_ECTRL register  ******************/
/*!< PIN configuration */
#define AFIO_ECTRL_PIN_SEL_Pos					(0U)
#define AFIO_ECTRL_PIN_SEL_Msk					(0xFUL << AFIO_ECTRL_PIN_SEL_Pos)
#define AFIO_ECTRL_PIN_SEL						AFIO_ECTRL_PIN_SEL_Msk			/*!< PIN[3:0] bits (Pin selection) */
#define AFIO_ECTRL_PIN_SEL_0					((uint8_t) 0x01)				/*!< Bit 0 */
#define AFIO_ECTRL_PIN_SEL_1					((uint8_t) 0x02)				/*!< Bit 1 */
#define AFIO_ECTRL_PIN_SEL_2					((uint8_t) 0x04)				/*!< Bit 2 */
#define AFIO_ECTRL_PIN_SEL_3					((uint8_t) 0x08)				/*!< Bit 3 */

#define AFIO_ECTRL_PIN_SEL_PIN0					((uint8_t) 0x00)				/*!< Pin 0 selected */
#define AFIO_ECTRL_PIN_SEL_PIN1					((uint8_t) 0x01)				/*!< Pin 1 selected */
#define AFIO_ECTRL_PIN_SEL_PIN2					((uint8_t) 0x02)				/*!< Pin 2 selected */
#define AFIO_ECTRL_PIN_SEL_PIN3					((uint8_t) 0x03)				/*!< Pin 3 selected */
#define AFIO_ECTRL_PIN_SEL_PIN4					((uint8_t) 0x04)				/*!< Pin 4 selected */
#define AFIO_ECTRL_PIN_SEL_PIN5					((uint8_t) 0x05)				/*!< Pin 5 selected */
#define AFIO_ECTRL_PIN_SEL_PIN6					((uint8_t) 0x06)				/*!< Pin 6 selected */
#define AFIO_ECTRL_PIN_SEL_PIN7					((uint8_t) 0x07)				/*!< Pin 7 selected */
#define AFIO_ECTRL_PIN_SEL_PIN8					((uint8_t) 0x08)				/*!< Pin 8 selected */
#define AFIO_ECTRL_PIN_SEL_PIN9					((uint8_t) 0x09)				/*!< Pin 9 selected */
#define AFIO_ECTRL_PIN_SEL_PIN10				((uint8_t) 0x0A)				/*!< Pin 10 selected */
#define AFIO_ECTRL_PIN_SEL_PIN11				((uint8_t) 0x0B)				/*!< Pin 11 selected */
#define AFIO_ECTRL_PIN_SEL_PIN12				((uint8_t) 0x0C)				/*!< Pin 12 selected */
#define AFIO_ECTRL_PIN_SEL_PIN13				((uint8_t) 0x0D)				/*!< Pin 13 selected */
#define AFIO_ECTRL_PIN_SEL_PIN14				((uint8_t) 0x0E)				/*!< Pin 14 selected */
#define AFIO_ECTRL_PIN_SEL_PIN15				((uint8_t) 0x0F)				/*!< Pin 15 selected */

/*!< PORT configuration */
#define AFIO_ECTRL_PORT_SEL_Pos					(4U)
#define AFIO_ECTRL_PORT_SEL_Msk					(0x7UL << AFIO_ECTRL_PORT_SEL_Pos)
#define AFIO_ECTRL_PORT_SEL						AFIO_ECTRL_PORT_SEL_Msk			/*!< PORT[2:0] bits (Port selection) */
#define AFIO_ECTRL_PORT_SEL_0					((uint8_t) 0x10)				/*!< Bit 0 */
#define AFIO_ECTRL_PORT_SEL_1					((uint8_t) 0x20)				/*!< Bit 1 */
#define AFIO_ECTRL_PORT_SEL_2					((uint8_t) 0x40)				/*!< Bit 2 */

#define AFIO_ECTRL_PORT_SEL_PA					((uint8_t) 0x00)				/*!< Port A selected */
#define AFIO_ECTRL_PORT_SEL_PB					((uint8_t) 0x10)				/*!< Port B selected */
#define AFIO_ECTRL_PORT_SEL_PC					((uint8_t) 0x20)				/*!< Port C selected */
#define AFIO_ECTRL_PORT_SEL_PD					((uint8_t) 0x30)				/*!< Port D selected */
#define AFIO_ECTRL_PORT_SEL_PE					((uint8_t) 0x40)				/*!< Port E selected */

#define AFIO_ECTRL_EOE_Pos						(7U)
#define AFIO_ECTRL_EOE_Msk						(0x1UL << AFIO_ECTRL_EOE_Pos)
#define AFIO_ECTRL_EOE							AFIO_ECTRL_EOE_Msk				/*!< Event Output Enable */

/*****************  Bit definition for AFIO_RMP_CFG register  *****************/
#define AFIO_RMP_CFG_SPI1_RMP_0_Pos				(0U)
#define AFIO_RMP_CFG_SPI1_RMP_0_Msk				(0x1UL << AFIO_RMP_CFG_SPI1_RMP_0_Pos)		/*!< 0x00000001 */
#define AFIO_RMP_CFG_SPI1_RMP_0   				AFIO_RMP_CFG_SPI1_RMP_0_Msk		/*!< SPI1_RMP_0 remapping */
#define AFIO_RMP_CFG_I2C1_RMP_Pos				(1U)
#define AFIO_RMP_CFG_I2C1_RMP_Msk				(0x1UL << AFIO_RMP_CFG_I2C1_RMP_Pos)		/*!< 0x00000002 */
#define AFIO_RMP_CFG_I2C1_RMP     				AFIO_RMP_CFG_I2C1_RMP_Msk		/*!< I2C1 remapping */
#define AFIO_RMP_CFG_USART1_RMP_Pos				(2U)
#define AFIO_RMP_CFG_USART1_RMP_Msk				(0x1UL << AFIO_RMP_CFG_USART1_RMP_Pos)		/*!< 0x00000004 */
#define AFIO_RMP_CFG_USART1_RMP   				AFIO_RMP_CFG_USART1_RMP_Msk		/*!< USART1 remapping */
#define AFIO_RMP_CFG_USART2_RMP_0_Pos			(3U)
#define AFIO_RMP_CFG_USART2_RMP_0_Msk			(0x1UL << AFIO_RMP_CFG_USART2_RMP_0_Pos)	/*!< 0x00000008 */
#define AFIO_RMP_CFG_USART2_RMP_0 				AFIO_RMP_CFG_USART2_RMP_0_Msk	/*!< USART2_RMP_0 remapping */

#define AFIO_RMP_CFG_USART3_RMP_Pos				(4U)
#define AFIO_RMP_CFG_USART3_RMP_Msk				(0x3UL << AFIO_RMP_CFG_USART3_RMP_Pos)		/*!< 0x00000030 */
#define AFIO_RMP_CFG_USART3_RMP					AFIO_RMP_CFG_USART3_RMP_Msk		/*!< USART3_REMAP[1:0] bits (USART3 remapping) */
#define AFIO_RMP_CFG_USART3_RMP_0				((uint32_t) 0x00000010)			/*!< Bit 0 */
#define AFIO_RMP_CFG_USART3_RMP_1				((uint32_t) 0x00000020)			/*!< Bit 1 */

/*!< USART3_REMAP configuration */
#define AFIO_RMP_CFG_USART3_RMP_NONE			((uint32_t) 0x00000000)			/*!< No remap (TX/PB10, RX/PB11, CK/PB12, CTS/PB13, RTS/PB14) */
#define AFIO_RMP_CFG_USART3_RMP_PART			((uint32_t) 0x00000010)			/*!< Partial remap (TX/PC10, RX/PC11, CK/PC12, CTS/PB13, RTS/PB14) */
#define AFIO_RMP_CFG_USART3_RMP_ALL				((uint32_t) 0x00000030)			/*!< Full remap (TX/PD8, RX/PD9, CK/PD10, CTS/PD11, RTS/PD12) */

#define AFIO_RMP_CFG_TIM1_RMP_Pos				(6U)
#define AFIO_RMP_CFG_TIM1_RMP_Msk				(0x3UL << AFIO_RMP_CFG_TIM1_RMP_Pos)	/*!< 0x000000C0 */
#define AFIO_RMP_CFG_TIM1_RMP					AFIO_RMP_CFG_TIM1_RMP_Msk		/*!< TIM1_REMAP[1:0] bits (TIM1 remapping) */
#define AFIO_RMP_CFG_TIM1_RMP_0					((uint32_t) 0x00000040)			/*!< Bit 0 */
#define AFIO_RMP_CFG_TIM1_RMP_1					((uint32_t) 0x00000080)			/*!< Bit 1 */

/*!< TIM1_REMAP configuration */
#define AFIO_RMP_CFG_TIM1_RMP_NONE				((uint32_t) 0x00000000)			/*!< No remap (ETR/PA12, CH1/PA8, CH2/PA9, CH3/PA10, CH4/PA11, BKIN/PB12, CH1N/PB13, CH2N/PB14, CH3N/PB15) */
#define AFIO_RMP_CFG_TIM1_RMP_PART				((uint32_t) 0x00000040)			/*!< Partial remap (ETR/PA12, CH1/PA8, CH2/PA9, CH3/PA10, CH4/PA11, BKIN/PA6, CH1N/PA7, CH2N/PB0, CH3N/PB1) */
#define AFIO_RMP_CFG_TIM1_RMP_PART2				((uint32_t) 0x00000080)			/*!< Partial remap (ETR/PA12, CH1/PA8, CH2/PA9, CH3/PA10, CH4/PA11, BKIN/PB5, CH1N/PB13, CH2N/PB14, CH3N/PB15) */
#define AFIO_RMP_CFG_TIM1_RMP_ALL				((uint32_t) 0x000000C0)			/*!< Full remap (ETR/PE7, CH1/PE9, CH2/PE11, CH3/PE13, CH4/PE14, BKIN/PE15, CH1N/PE8, CH2N/PE10, CH3N/PE12) */

#define AFIO_RMP_CFG_TIM2_RMP_Pos				(8U)
#define AFIO_RMP_CFG_TIM2_RMP_Msk				(0x3UL << AFIO_RMP_CFG_TIM2_RMP_Pos)	/*!< 0x00000300 */
#define AFIO_RMP_CFG_TIM2_RMP					AFIO_RMP_CFG_TIM2_RMP_Msk		/*!< TIM2_REMAP[1:0] bits (TIM2 remapping) */
#define AFIO_RMP_CFG_TIM2_RMP_0					((uint32_t) 0x00000100)			/*!< Bit 0 */
#define AFIO_RMP_CFG_TIM2_RMP_1					((uint32_t) 0x00000200)			/*!< Bit 1 */

/*!< TIM2_REMAP configuration */
#define AFIO_RMP_CFG_TIM2_RMP_NONE				((uint32_t) 0x00000000)			/*!< No remap (CH1/ETR/PA0, CH2/PA1, CH3/PA2, CH4/PA3) */
#define AFIO_RMP_CFG_TIM2_RMP_PART1				((uint32_t) 0x00000100)			/*!< Partial remap (CH1/ETR/PA15, CH2/PB3, CH3/PA2, CH4/PA3) */
#define AFIO_RMP_CFG_TIM2_RMP_PART2				((uint32_t) 0x00000200)			/*!< Partial remap (CH1/ETR/PA0, CH2/PA1, CH3/PB10, CH4/PB11) */
#define AFIO_RMP_CFG_TIM2_RMP_ALL				((uint32_t) 0x00000300)			/*!< Full remap (CH1/ETR/PA15, CH2/PB3, CH3/PB10, CH4/PB11) */

#define AFIO_RMP_CFG_TIM3_RMP_Pos				(10U)
#define AFIO_RMP_CFG_TIM3_RMP_Msk				(0x3UL << AFIO_RMP_CFG_TIM3_RMP_Pos)	/*!< 0x00000C00 */
#define AFIO_RMP_CFG_TIM3_RMP					AFIO_RMP_CFG_TIM3_RMP_Msk		/*!< TIM3_REMAP[1:0] bits (TIM3 remapping) */
#define AFIO_RMP_CFG_TIM3_RMP_0					((uint32_t) 0x00000400)			/*!< Bit 0 */
#define AFIO_RMP_CFG_TIM3_RMP_1					((uint32_t) 0x00000800)			/*!< Bit 1 */

/*!< TIM3_REMAP configuration */
#define AFIO_RMP_CFG_TIM3_RMP_NONE				((uint32_t) 0x00000000)			/*!< No remap (CH1/PA6, CH2/PA7, CH3/PB0, CH4/PB1) */
#define AFIO_RMP_CFG_TIM3_RMP_PART				((uint32_t) 0x00000800)			/*!< Partial remap (CH1/PB4, CH2/PB5, CH3/PB0, CH4/PB1) */
#define AFIO_RMP_CFG_TIM3_RMP_ALL				((uint32_t) 0x00000C00)			/*!< Full remap (CH1/PC6, CH2/PC7, CH3/PC8, CH4/PC9) */

#define AFIO_RMP_CFG_TIM4_RMP_Pos				(12U)
#define AFIO_RMP_CFG_TIM4_RMP_Msk				(0x1UL << AFIO_RMP_CFG_TIM4_RMP_Pos)	/*!< 0x00001000 */
#define AFIO_RMP_CFG_TIM4_RMP					AFIO_RMP_CFG_TIM4_RMP_Msk		/*!< TIM4_REMAP bit (TIM4 remapping) */

#define AFIO_RMP_CFG_CAN1_RMP_Pos				(13U)
#define AFIO_RMP_CFG_CAN1_RMP_Msk				(0x3UL << AFIO_RMP_CFG_CAN1_RMP_Pos)	/*!< 0x00006000 */
#define AFIO_RMP_CFG_CAN1_RMP					AFIO_RMP_CFG_CAN1_RMP_Msk		/*!< CAN1_RMP[1:0] bits (CAN1 Alternate function remapping) */
#define AFIO_RMP_CFG_CAN1_RMP_0					((uint32_t) 0x00002000)			/*!< Bit 0 */
#define AFIO_RMP_CFG_CAN1_RMP_1					((uint32_t) 0x00004000)			/*!< Bit 1 */

/*!< CAN1_REMAP configuration */
#define AFIO_RMP_CFG_CAN1_RMP_RMP1				((uint32_t) 0x00000000)			/*!< CAN1RX mapped to PA11, CAN1TX mapped to PA12 */
#define AFIO_RMP_CFG_CAN1_RMP_RMP2				((uint32_t) 0x00002000)			/*!< CAN1RX mapped to PD8, CAN1TX mapped to PD9 */
#define AFIO_RMP_CFG_CAN1_RMP_RMP3				((uint32_t) 0x00006000)			/*!< CAN1RX mapped to PB8, CAN1TX mapped to PB9 */
#define AFIO_RMP_CFG_CAN1_RMP_RMP4				((uint32_t) 0x00004000)			/*!< CAN1RX mapped to PD0, CAN1TX mapped to PD1 */

#define AFIO_RMP_CFG_PD01_RMP_Pos				(15U)
#define AFIO_RMP_CFG_PD01_RMP_Msk				(0x1UL << AFIO_RMP_CFG_PD01_RMP_Pos)	/*!< 0x00008000 */
#define AFIO_RMP_CFG_PD01_RMP					AFIO_RMP_CFG_PD01_RMP_Msk		/*!< Port D0/Port D1 mapping on OSC_IN/OSC_OUT */
#define AFIO_RMP_CFG_TIM5CH4_RMP_Pos			(16U)
#define AFIO_RMP_CFG_TIM5CH4_RMP_Msk			(0x1UL << AFIO_RMP_CFG_TIM5CH4_RMP_Pos)	/*!< 0x00010000 */
#define AFIO_RMP_CFG_TIM5CH4_RMP				AFIO_RMP_CFG_TIM5CH4_RMP_Msk	/*!< TIM5 Channel4 Internal Remap */
#define AFIO_RMP_CFG_ADC1_ETRI_RMP_Pos			(17U)
#define AFIO_RMP_CFG_ADC1_ETRI_RMP_Msk			(0x1UL << AFIO_RMP_CFG_ADC1_ETRI_RMP_Pos)	/*!< 0x00020000 */
#define AFIO_RMP_CFG_ADC1_ETRI_RMP				AFIO_RMP_CFG_ADC1_ETRI_RMP_Msk	/*!< ADC 1 External Trigger Injected Conversion remapping */
#define AFIO_RMP_CFG_ADC1_ETRR_RMP_Pos			(18U)
#define AFIO_RMP_CFG_ADC1_ETRR_RMP_Msk			(0x1UL << AFIO_RMP_CFG_ADC1_ETRR_RMP_Pos)	/*!< 0x00040000 */
#define AFIO_RMP_CFG_ADC1_ETRR_RMP				AFIO_RMP_CFG_ADC1_ETRR_RMP_Msk	/*!< ADC 1 External Trigger Regular Conversion remapping */
#define AFIO_RMP_CFG_ADC2_ETRI_RMP_Pos			(19U)
#define AFIO_RMP_CFG_ADC2_ETRI_RMP_Msk			(0x1UL << AFIO_RMP_CFG_ADC2_ETRI_RMP_Pos)	/*!< 0x00080000 */
#define AFIO_RMP_CFG_ADC2_ETRI_RMP				AFIO_RMP_CFG_ADC2_ETRI_RMP_Msk	/*!< ADC 2 External Trigger Injected Conversion remapping */
#define AFIO_RMP_CFG_ADC2_ETRR_RMP_Pos			(20U)
#define AFIO_RMP_CFG_ADC2_ETRR_RMP_Msk			(0x1UL << AFIO_RMP_CFG_ADC2_ETRR_RMP_Pos)	/*!< 0x00100000 */
#define AFIO_RMP_CFG_ADC2_ETRR_RMP				AFIO_RMP_CFG_ADC2_ETRR_RMP_Msk	/*!< ADC 2 External Trigger Regular Conversion remapping */

/*!< SWJ_CFG configuration */
#define AFIO_RMP_CFG_SW_JTAG_CFG_Pos			(24U)
#define AFIO_RMP_CFG_SW_JTAG_CFG_Msk			(0x7UL << AFIO_RMP_CFG_SW_JTAG_CFG_Pos)	/*!< 0x07000000 */
#define AFIO_RMP_CFG_SW_JTAG_CFG				AFIO_RMP_CFG_SW_JTAG_CFG_Msk	/*!< SWJ_CFG[2:0] bits (Serial Wire JTAG configuration) */
#define AFIO_RMP_CFG_SW_JTAG_CFG0				((uint32_t) 0x01000000)			/*!< Bit 0 */
#define AFIO_RMP_CFG_SW_JTAG_CFG1				((uint32_t) 0x02000000)			/*!< Bit 1 */
#define AFIO_RMP_CFG_SW_JTAG_CFG2				((uint32_t) 0x04000000)			/*!< Bit 2 */

#define AFIO_RMP_CFG_SW_JTAG_CFG_RESET			((uint32_t) 0x00000000)			/*!< Full SWJ (JTAG-DP + SW-DP) : Reset State */
#define AFIO_RMP_CFG_SW_JTAG_CFG_NO_NJTRST		((uint32_t) 0x01000000)			/*!< Full SWJ (JTAG-DP + SW-DP) but without JNTRST */
#define AFIO_RMP_CFG_SW_JTAG_CFG_SW_ENABLE		((uint32_t) 0x02000000)			/*!< JTAG-DP Disabled and SW-DP Enabled */
#define AFIO_RMP_CFG_SW_JTAG_CFG_DISABLE		((uint32_t) 0x04000000)			/*!< JTAG-DP Disabled and SW-DP Disabled */

/****************  Bit definition for AFIO_EXTI_CFG1 register  ****************/
#define AFIO_EXTI_CFG1_EXTI0_Pos				(0U)
#define AFIO_EXTI_CFG1_EXTI0_Msk				(0xFUL << AFIO_EXTI_CFG1_EXTI0_Pos)	/*!< 0x0000000F */
#define AFIO_EXTI_CFG1_EXTI0					AFIO_EXTI_CFG1_EXTI0_Msk		/*!< EXTI 0 configuration */
#define AFIO_EXTI_CFG1_EXTI1_Pos				(4U)
#define AFIO_EXTI_CFG1_EXTI1_Msk				(0xFUL << AFIO_EXTI_CFG1_EXTI1_Pos)	/*!< 0x000000F0 */
#define AFIO_EXTI_CFG1_EXTI1					AFIO_EXTI_CFG1_EXTI1_Msk		/*!< EXTI 1 configuration */
#define AFIO_EXTI_CFG1_EXTI2_Pos				(8U)
#define AFIO_EXTI_CFG1_EXTI2_Msk				(0xFUL << AFIO_EXTI_CFG1_EXTI2_Pos)	/*!< 0x00000F00 */
#define AFIO_EXTI_CFG1_EXTI2					AFIO_EXTI_CFG1_EXTI2_Msk		/*!< EXTI 2 configuration */
#define AFIO_EXTI_CFG1_EXTI3_Pos				(12U)
#define AFIO_EXTI_CFG1_EXTI3_Msk				(0xFUL << AFIO_EXTI_CFG1_EXTI3_Pos)	/*!< 0x0000F000 */
#define AFIO_EXTI_CFG1_EXTI3					AFIO_EXTI_CFG1_EXTI3_Msk		/*!< EXTI 3 configuration */

/*!< EXTI0 configuration */
#define AFIO_EXTI_CFG1_EXTI0_PA					((uint16_t) 0x0000)				/*!< PA[0] pin */
#define AFIO_EXTI_CFG1_EXTI0_PB					((uint16_t) 0x0001)				/*!< PB[0] pin */
#define AFIO_EXTI_CFG1_EXTI0_PC					((uint16_t) 0x0002)				/*!< PC[0] pin */
#define AFIO_EXTI_CFG1_EXTI0_PD					((uint16_t) 0x0003)				/*!< PD[0] pin */
#define AFIO_EXTI_CFG1_EXTI0_PE					((uint16_t) 0x0004)				/*!< PE[0] pin */
#define AFIO_EXTI_CFG1_EXTI0_PF					((uint16_t) 0x0005)				/*!< PF[0] pin */
#define AFIO_EXTI_CFG1_EXTI0_PG					((uint16_t) 0x0006)				/*!< PG[0] pin */

/*!< EXTI1 configuration */
#define AFIO_EXTI_CFG1_EXTI1_PA					((uint16_t) 0x0000)				/*!< PA[1] pin */
#define AFIO_EXTI_CFG1_EXTI1_PB					((uint16_t) 0x0010)				/*!< PB[1] pin */
#define AFIO_EXTI_CFG1_EXTI1_PC					((uint16_t) 0x0020)				/*!< PC[1] pin */
#define AFIO_EXTI_CFG1_EXTI1_PD					((uint16_t) 0x0030)				/*!< PD[1] pin */
#define AFIO_EXTI_CFG1_EXTI1_PE					((uint16_t) 0x0040)				/*!< PE[1] pin */
#define AFIO_EXTI_CFG1_EXTI1_PF					((uint16_t) 0x0050)				/*!< PF[1] pin */
#define AFIO_EXTI_CFG1_EXTI1_PG					((uint16_t) 0x0060)				/*!< PG[1] pin */

/*!< EXTI2 configuration */
#define AFIO_EXTI_CFG1_EXTI2_PA					((uint16_t) 0x0000)				/*!< PA[2] pin */
#define AFIO_EXTI_CFG1_EXTI2_PB					((uint16_t) 0x0100)				/*!< PB[2] pin */
#define AFIO_EXTI_CFG1_EXTI2_PC					((uint16_t) 0x0200)				/*!< PC[2] pin */
#define AFIO_EXTI_CFG1_EXTI2_PD					((uint16_t) 0x0300)				/*!< PD[2] pin */
#define AFIO_EXTI_CFG1_EXTI2_PE					((uint16_t) 0x0400)				/*!< PE[2] pin */
#define AFIO_EXTI_CFG1_EXTI2_PF					((uint16_t) 0x0500)				/*!< PF[2] pin */
#define AFIO_EXTI_CFG1_EXTI2_PG					((uint16_t) 0x0600)				/*!< PG[2] pin */

/*!< EXTI3 configuration */
#define AFIO_EXTI_CFG1_EXTI3_PA					((uint16_t) 0x0000)				/*!< PA[3] pin */
#define AFIO_EXTI_CFG1_EXTI3_PB					((uint16_t) 0x1000)				/*!< PB[3] pin */
#define AFIO_EXTI_CFG1_EXTI3_PC					((uint16_t) 0x2000)				/*!< PC[3] pin */
#define AFIO_EXTI_CFG1_EXTI3_PD					((uint16_t) 0x3000)				/*!< PD[3] pin */
#define AFIO_EXTI_CFG1_EXTI3_PE					((uint16_t) 0x4000)				/*!< PE[3] pin */
#define AFIO_EXTI_CFG1_EXTI3_PF					((uint16_t) 0x5000)				/*!< PF[3] pin */
#define AFIO_EXTI_CFG1_EXTI3_PG					((uint16_t) 0x6000)				/*!< PG[3] pin */

/****************  Bit definition for AFIO_EXTI_CFG2 register  ****************/
#define AFIO_EXTI_CFG2_EXTI4_Pos				(0U)
#define AFIO_EXTI_CFG2_EXTI4_Msk				(0xFUL << AFIO_EXTI_CFG2_EXTI4_Pos)	/*!< 0x0000000F */
#define AFIO_EXTI_CFG2_EXTI4					AFIO_EXTI_CFG2_EXTI4_Msk		/*!< EXTI 4 configuration */
#define AFIO_EXTI_CFG2_EXTI5_Pos				(4U)
#define AFIO_EXTI_CFG2_EXTI5_Msk				(0xFUL << AFIO_EXTI_CFG2_EXTI5_Pos)	/*!< 0x000000F0 */
#define AFIO_EXTI_CFG2_EXTI5					AFIO_EXTI_CFG2_EXTI5_Msk		/*!< EXTI 5 configuration */
#define AFIO_EXTI_CFG2_EXTI6_Pos				(8U)
#define AFIO_EXTI_CFG2_EXTI6_Msk				(0xFUL << AFIO_EXTI_CFG2_EXTI6_Pos)	/*!< 0x00000F00 */
#define AFIO_EXTI_CFG2_EXTI6					AFIO_EXTI_CFG2_EXTI6_Msk		/*!< EXTI 6 configuration */
#define AFIO_EXTI_CFG2_EXTI7_Pos				(12U)
#define AFIO_EXTI_CFG2_EXTI7_Msk				(0xFUL << AFIO_EXTI_CFG2_EXTI7_Pos)	/*!< 0x0000F000 */
#define AFIO_EXTI_CFG2_EXTI7					AFIO_EXTI_CFG2_EXTI7_Msk		/*!< EXTI 7 configuration */

/*!< EXTI4 configuration */
#define AFIO_EXTI_CFG2_EXTI4_PA					((uint16_t) 0x0000)				/*!< PA[4] pin */
#define AFIO_EXTI_CFG2_EXTI4_PB					((uint16_t) 0x0001)				/*!< PB[4] pin */
#define AFIO_EXTI_CFG2_EXTI4_PC					((uint16_t) 0x0002)				/*!< PC[4] pin */
#define AFIO_EXTI_CFG2_EXTI4_PD					((uint16_t) 0x0003)				/*!< PD[4] pin */
#define AFIO_EXTI_CFG2_EXTI4_PE					((uint16_t) 0x0004)				/*!< PE[4] pin */
#define AFIO_EXTI_CFG2_EXTI4_PF					((uint16_t) 0x0005)				/*!< PF[4] pin */
#define AFIO_EXTI_CFG2_EXTI4_PG					((uint16_t) 0x0006)				/*!< PG[4] pin */

/*!< EXTI5 configuration */
#define AFIO_EXTI_CFG2_EXTI5_PA					((uint16_t) 0x0000)				/*!< PA[5] pin */
#define AFIO_EXTI_CFG2_EXTI5_PB					((uint16_t) 0x0010)				/*!< PB[5] pin */
#define AFIO_EXTI_CFG2_EXTI5_PC					((uint16_t) 0x0020)				/*!< PC[5] pin */
#define AFIO_EXTI_CFG2_EXTI5_PD					((uint16_t) 0x0030)				/*!< PD[5] pin */
#define AFIO_EXTI_CFG2_EXTI5_PE					((uint16_t) 0x0040)				/*!< PE[5] pin */
#define AFIO_EXTI_CFG2_EXTI5_PF					((uint16_t) 0x0050)				/*!< PF[5] pin */
#define AFIO_EXTI_CFG2_EXTI5_PG					((uint16_t) 0x0060)				/*!< PG[5] pin */

/*!< EXTI6 configuration */
#define AFIO_EXTI_CFG2_EXTI6_PA					((uint16_t) 0x0000)				/*!< PA[6] pin */
#define AFIO_EXTI_CFG2_EXTI6_PB					((uint16_t) 0x0100)				/*!< PB[6] pin */
#define AFIO_EXTI_CFG2_EXTI6_PC					((uint16_t) 0x0200)				/*!< PC[6] pin */
#define AFIO_EXTI_CFG2_EXTI6_PD					((uint16_t) 0x0300)				/*!< PD[6] pin */
#define AFIO_EXTI_CFG2_EXTI6_PE					((uint16_t) 0x0400)				/*!< PE[6] pin */
#define AFIO_EXTI_CFG2_EXTI6_PF					((uint16_t) 0x0500)				/*!< PF[6] pin */
#define AFIO_EXTI_CFG2_EXTI6_PG					((uint16_t) 0x0600)				/*!< PG[6] pin */

/*!< EXTI7 configuration */
#define AFIO_EXTI_CFG2_EXTI7_PA					((uint16_t) 0x0000)				/*!< PA[7] pin */
#define AFIO_EXTI_CFG2_EXTI7_PB					((uint16_t) 0x1000)				/*!< PB[7] pin */
#define AFIO_EXTI_CFG2_EXTI7_PC					((uint16_t) 0x2000)				/*!< PC[7] pin */
#define AFIO_EXTI_CFG2_EXTI7_PD					((uint16_t) 0x3000)				/*!< PD[7] pin */
#define AFIO_EXTI_CFG2_EXTI7_PE					((uint16_t) 0x4000)				/*!< PE[7] pin */
#define AFIO_EXTI_CFG2_EXTI7_PF					((uint16_t) 0x5000)				/*!< PF[7] pin */
#define AFIO_EXTI_CFG2_EXTI7_PG					((uint16_t) 0x6000)				/*!< PG[7] pin */

/****************  Bit definition for AFIO_EXTI_CFG3 register  ****************/
#define AFIO_EXTI_CFG3_EXTI8_Pos				(0U)
#define AFIO_EXTI_CFG3_EXTI8_Msk				(0xFUL << AFIO_EXTI_CFG3_EXTI8_Pos)		/*!< 0x0000000F */
#define AFIO_EXTI_CFG3_EXTI8					AFIO_EXTI_CFG3_EXTI8_Msk		/*!< EXTI 8 configuration */
#define AFIO_EXTI_CFG3_EXTI9_Pos				(4U)
#define AFIO_EXTI_CFG3_EXTI9_Msk				(0xFUL << AFIO_EXTI_CFG3_EXTI9_Pos)		/*!< 0x000000F0 */
#define AFIO_EXTI_CFG3_EXTI9					AFIO_EXTI_CFG3_EXTI9_Msk		/*!< EXTI 9 configuration */
#define AFIO_EXTI_CFG3_EXTI10_Pos				(8U)
#define AFIO_EXTI_CFG3_EXTI10_Msk				(0xFUL << AFIO_EXTI_CFG3_EXTI10_Pos)	/*!< 0x00000F00 */
#define AFIO_EXTI_CFG3_EXTI10					AFIO_EXTI_CFG3_EXTI10_Msk		/*!< EXTI 10 configuration */
#define AFIO_EXTI_CFG3_EXTI11_Pos				(12U)
#define AFIO_EXTI_CFG3_EXTI11_Msk				(0xFUL << AFIO_EXTI_CFG3_EXTI11_Pos)	/*!< 0x0000F000 */
#define AFIO_EXTI_CFG3_EXTI11					AFIO_EXTI_CFG3_EXTI11_Msk		/*!< EXTI 11 configuration */

/*!< EXTI8 configuration */
#define AFIO_EXTI_CFG3_EXTI8_PA					((uint16_t) 0x0000)				/*!< PA[8] pin */
#define AFIO_EXTI_CFG3_EXTI8_PB					((uint16_t) 0x0001)				/*!< PB[8] pin */
#define AFIO_EXTI_CFG3_EXTI8_PC					((uint16_t) 0x0002)				/*!< PC[8] pin */
#define AFIO_EXTI_CFG3_EXTI8_PD					((uint16_t) 0x0003)				/*!< PD[8] pin */
#define AFIO_EXTI_CFG3_EXTI8_PE					((uint16_t) 0x0004)				/*!< PE[8] pin */
#define AFIO_EXTI_CFG3_EXTI8_PF					((uint16_t) 0x0005)				/*!< PF[8] pin */
#define AFIO_EXTI_CFG3_EXTI8_PG					((uint16_t) 0x0006)				/*!< PG[8] pin */

/*!< EXTI9 configuration */
#define AFIO_EXTI_CFG3_EXTI9_PA					((uint16_t) 0x0000)				/*!< PA[9] pin */
#define AFIO_EXTI_CFG3_EXTI9_PB					((uint16_t) 0x0010)				/*!< PB[9] pin */
#define AFIO_EXTI_CFG3_EXTI9_PC					((uint16_t) 0x0020)				/*!< PC[9] pin */
#define AFIO_EXTI_CFG3_EXTI9_PD					((uint16_t) 0x0030)				/*!< PD[9] pin */
#define AFIO_EXTI_CFG3_EXTI9_PE					((uint16_t) 0x0040)				/*!< PE[9] pin */
#define AFIO_EXTI_CFG3_EXTI9_PF					((uint16_t) 0x0050)				/*!< PF[9] pin */
#define AFIO_EXTI_CFG3_EXTI9_PG					((uint16_t) 0x0060)				/*!< PG[9] pin */

/*!< EXTI10 configuration */
#define AFIO_EXTI_CFG3_EXTI10_PA				((uint16_t) 0x0000)				/*!< PA[10] pin */
#define AFIO_EXTI_CFG3_EXTI10_PB				((uint16_t) 0x0100)				/*!< PB[10] pin */
#define AFIO_EXTI_CFG3_EXTI10_PC				((uint16_t) 0x0200)				/*!< PC[10] pin */
#define AFIO_EXTI_CFG3_EXTI10_PD				((uint16_t) 0x0300)				/*!< PD[10] pin */
#define AFIO_EXTI_CFG3_EXTI10_PE				((uint16_t) 0x0400)				/*!< PE[10] pin */
#define AFIO_EXTI_CFG3_EXTI10_PF				((uint16_t) 0x0500)				/*!< PF[10] pin */
#define AFIO_EXTI_CFG3_EXTI10_PG				((uint16_t) 0x0600)				/*!< PG[10] pin */

/*!< EXTI11 configuration */
#define AFIO_EXTI_CFG3_EXTI11_PA				((uint16_t) 0x0000)				/*!< PA[11] pin */
#define AFIO_EXTI_CFG3_EXTI11_PB				((uint16_t) 0x1000)				/*!< PB[11] pin */
#define AFIO_EXTI_CFG3_EXTI11_PC				((uint16_t) 0x2000)				/*!< PC[11] pin */
#define AFIO_EXTI_CFG3_EXTI11_PD				((uint16_t) 0x3000)				/*!< PD[11] pin */
#define AFIO_EXTI_CFG3_EXTI11_PE				((uint16_t) 0x4000)				/*!< PE[11] pin */
#define AFIO_EXTI_CFG3_EXTI11_PF				((uint16_t) 0x5000)				/*!< PF[11] pin */
#define AFIO_EXTI_CFG3_EXTI11_PG				((uint16_t) 0x6000)				/*!< PG[11] pin */

/****************  Bit definition for AFIO_EXTI_CFG4 register  ****************/
#define AFIO_EXTI_CFG4_EXTI12_Pos				(0U)
#define AFIO_EXTI_CFG4_EXTI12_Msk				(0xFUL << AFIO_EXTI_CFG4_EXTI12_Pos)	/*!< 0x0000000F */
#define AFIO_EXTI_CFG4_EXTI12					AFIO_EXTI_CFG4_EXTI12_Msk		/*!< EXTI 12 configuration */
#define AFIO_EXTI_CFG4_EXTI13_Pos				(4U)
#define AFIO_EXTI_CFG4_EXTI13_Msk				(0xFUL << AFIO_EXTI_CFG4_EXTI13_Pos)	/*!< 0x000000F0 */
#define AFIO_EXTI_CFG4_EXTI13					AFIO_EXTI_CFG4_EXTI13_Msk		/*!< EXTI 13 configuration */
#define AFIO_EXTI_CFG4_EXTI14_Pos				(8U)
#define AFIO_EXTI_CFG4_EXTI14_Msk				(0xFUL << AFIO_EXTI_CFG4_EXTI14_Pos)	/*!< 0x00000F00 */
#define AFIO_EXTI_CFG4_EXTI14					AFIO_EXTI_CFG4_EXTI14_Msk		/*!< EXTI 14 configuration */
#define AFIO_EXTI_CFG4_EXTI15_Pos				(12U)
#define AFIO_EXTI_CFG4_EXTI15_Msk				(0xFUL << AFIO_EXTI_CFG4_EXTI15_Pos)	/*!< 0x0000F000 */
#define AFIO_EXTI_CFG4_EXTI15					AFIO_EXTI_CFG4_EXTI15_Msk		/*!< EXTI 15 configuration */

/*!< EXTI12 configuration */
#define AFIO_EXTI_CFG4_EXTI12_PA				((uint16_t) 0x0000)				/*!< PA[12] pin */
#define AFIO_EXTI_CFG4_EXTI12_PB				((uint16_t) 0x0001)				/*!< PB[12] pin */
#define AFIO_EXTI_CFG4_EXTI12_PC				((uint16_t) 0x0002)				/*!< PC[12] pin */
#define AFIO_EXTI_CFG4_EXTI12_PD				((uint16_t) 0x0003)				/*!< PD[12] pin */
#define AFIO_EXTI_CFG4_EXTI12_PE				((uint16_t) 0x0004)				/*!< PE[12] pin */
#define AFIO_EXTI_CFG4_EXTI12_PF				((uint16_t) 0x0005)				/*!< PF[12] pin */
#define AFIO_EXTI_CFG4_EXTI12_PG				((uint16_t) 0x0006)				/*!< PG[12] pin */

/*!< EXTI13 configuration */
#define AFIO_EXTI_CFG4_EXTI13_PA				((uint16_t) 0x0000)				/*!< PA[13] pin */
#define AFIO_EXTI_CFG4_EXTI13_PB				((uint16_t) 0x0010)				/*!< PB[13] pin */
#define AFIO_EXTI_CFG4_EXTI13_PC				((uint16_t) 0x0020)				/*!< PC[13] pin */
#define AFIO_EXTI_CFG4_EXTI13_PD				((uint16_t) 0x0030)				/*!< PD[13] pin */
#define AFIO_EXTI_CFG4_EXTI13_PE				((uint16_t) 0x0040)				/*!< PE[13] pin */
#define AFIO_EXTI_CFG4_EXTI13_PF				((uint16_t) 0x0050)				/*!< PF[13] pin */
#define AFIO_EXTI_CFG4_EXTI13_PG				((uint16_t) 0x0060)				/*!< PG[13] pin */

/*!< EXTI14 configuration */
#define AFIO_EXTI_CFG4_EXTI14_PA				((uint16_t) 0x0000)				/*!< PA[14] pin */
#define AFIO_EXTI_CFG4_EXTI14_PB				((uint16_t) 0x0100)				/*!< PB[14] pin */
#define AFIO_EXTI_CFG4_EXTI14_PC				((uint16_t) 0x0200)				/*!< PC[14] pin */
#define AFIO_EXTI_CFG4_EXTI14_PD				((uint16_t) 0x0300)				/*!< PD[14] pin */
#define AFIO_EXTI_CFG4_EXTI14_PE				((uint16_t) 0x0400)				/*!< PE[14] pin */
#define AFIO_EXTI_CFG4_EXTI14_PF				((uint16_t) 0x0500)				/*!< PF[14] pin */
#define AFIO_EXTI_CFG4_EXTI14_PG				((uint16_t) 0x0600)				/*!< PG[14] pin */

/*!< EXTI15 configuration */
#define AFIO_EXTI_CFG4_EXTI15_PA				((uint16_t) 0x0000)				/*!< PA[15] pin */
#define AFIO_EXTI_CFG4_EXTI15_PB				((uint16_t) 0x1000)				/*!< PB[15] pin */
#define AFIO_EXTI_CFG4_EXTI15_PC				((uint16_t) 0x2000)				/*!< PC[15] pin */
#define AFIO_EXTI_CFG4_EXTI15_PD				((uint16_t) 0x3000)				/*!< PD[15] pin */
#define AFIO_EXTI_CFG4_EXTI15_PE				((uint16_t) 0x4000)				/*!< PE[15] pin */
#define AFIO_EXTI_CFG4_EXTI15_PF				((uint16_t) 0x5000)				/*!< PF[15] pin */
#define AFIO_EXTI_CFG4_EXTI15_PG				((uint16_t) 0x6000)				/*!< PG[15] pin */

/****************  Bit definition for AFIO_RMP_CFG3 register  *****************/
#define AFIO_RMP_CFG3_CAN2_RMP_Pos				(1U)
#define AFIO_RMP_CFG3_CAN2_RMP_Msk				(0x3UL << AFIO_RMP_CFG3_CAN2_RMP_Pos)		/*!< 0x00000006 */
#define AFIO_RMP_CFG3_CAN2_RMP   				AFIO_RMP_CFG3_CAN2_RMP_Msk		/*!<CAN2_RMP[1:0] bits (CAN2 Alternate function remapping) */
#define AFIO_RMP_CFG3_CAN2_RMP_0 				((uint32_t) 0x00000002)			/*!< Bit 0 */
#define AFIO_RMP_CFG3_CAN2_RMP_1 				((uint32_t) 0x00000004)			/*!< Bit 1*/
#define AFIO_RMP_CFG3_QSPI_RMP_Pos				(4U)
#define AFIO_RMP_CFG3_QSPI_RMP_Msk				(0x3UL << AFIO_RMP_CFG3_QSPI_RMP_Pos)		/*!< 0x00000030 */
#define AFIO_RMP_CFG3_QSPI_RMP   				AFIO_RMP_CFG3_QSPI_RMP_Msk		/*!<QSPI_RMP[1:0] bits (QSPI Alternate function remapping) */
#define AFIO_RMP_CFG3_QSPI_RMP_0 				((uint32_t) 0x00000010)			/*!< Bit 0 */
#define AFIO_RMP_CFG3_QSPI_RMP_1 				((uint32_t) 0x00000020)			/*!< Bit 1*/
#define AFIO_RMP_CFG3_I2C2_RMP_Pos				(6U)
#define AFIO_RMP_CFG3_I2C2_RMP_Msk				(0x3UL << AFIO_RMP_CFG3_I2C2_RMP_Pos)		/*!< 0x000000C0 */
#define AFIO_RMP_CFG3_I2C2_RMP   				AFIO_RMP_CFG3_I2C2_RMP_Msk		/*!<I2C2_RMP[1:0] bits (I2C2 Alternate function remapping) */
#define AFIO_RMP_CFG3_I2C2_RMP_0 				((uint32_t) 0x00000040)			/*!< Bit 0 */
#define AFIO_RMP_CFG3_I2C2_RMP_1 				((uint32_t) 0x00000080)			/*!< Bit 1*/
#define AFIO_RMP_CFG3_I2C3_RMP_Pos				(8U)
#define AFIO_RMP_CFG3_I2C3_RMP_Msk				(0x3UL << AFIO_RMP_CFG3_I2C3_RMP_Pos)		/*!< 0x00000300 */
#define AFIO_RMP_CFG3_I2C3_RMP   				AFIO_RMP_CFG3_I2C3_RMP_Msk		/*!<I2C3_RMP[1:0] bits (I2C3 Alternate function remapping) */
#define AFIO_RMP_CFG3_I2C3_RMP_0				((uint32_t) 0x00000100)			/*!< Bit 0 */
#define AFIO_RMP_CFG3_I2C3_RMP_1 				((uint32_t) 0x00000200)			/*!< Bit 1*/
#define AFIO_RMP_CFG3_I2C4_RMP_Pos				(10U)
#define AFIO_RMP_CFG3_I2C4_RMP_Msk				(0x3UL << AFIO_RMP_CFG3_I2C4_RMP_Pos)		/*!< 0x00000C00 */
#define AFIO_RMP_CFG3_I2C4_RMP   				AFIO_RMP_CFG3_I2C4_RMP_Msk		/*!<I2C4_RMP[1:0] bits (I2C4 Alternate function remapping) */
#define AFIO_RMP_CFG3_I2C4_RMP_0 				((uint32_t) 0x00000400)			/*!< Bit 0 */
#define AFIO_RMP_CFG3_I2C4_RMP_1 				((uint32_t) 0x00000800)			/*!< Bit 1*/
#define AFIO_RMP_CFG3_SPI2_RMP_Pos				(12U)
#define AFIO_RMP_CFG3_SPI2_RMP_Msk				(0x3UL << AFIO_RMP_CFG3_SPI2_RMP_Pos)		/*!< 0x00003000 */
#define AFIO_RMP_CFG3_SPI2_RMP   				AFIO_RMP_CFG3_SPI2_RMP_Msk		/*!<SPI2_RMP[1:0] bits (SPI2 Alternate function remapping) */
#define AFIO_RMP_CFG3_SPI2_RMP_0 				((uint32_t) 0x00001000)			/*!< Bit 0 */
#define AFIO_RMP_CFG3_SPI2_RMP_1 				((uint32_t) 0x00002000)			/*!< Bit 1*/
#define AFIO_RMP_CFG3_SPI3_RMP_Pos				(14U)
#define AFIO_RMP_CFG3_SPI3_RMP_Msk				(0x3UL << AFIO_RMP_CFG3_SPI3_RMP_Pos)		/*!< 0x0000C000 */
#define AFIO_RMP_CFG3_SPI3_RMP   				AFIO_RMP_CFG3_SPI3_RMP_Msk		/*!<SPI3_RMP[1:0] bits (SPI3 Alternate function remapping) */
#define AFIO_RMP_CFG3_SPI3_RMP_0 				((uint32_t) 0x00004000)			/*!< Bit 0 */
#define AFIO_RMP_CFG3_SPI3_RMP_1 				((uint32_t) 0x00008000)			/*!< Bit 1*/
#define AFIO_RMP_CFG3_SPI1_RMP_1_Pos			(18U)
#define AFIO_RMP_CFG3_SPI1_RMP_1_Msk			(0x1UL << AFIO_RMP_CFG3_SPI1_RMP_1_Pos)		/*!< 0x00040000 */
#define AFIO_RMP_CFG3_SPI1_RMP_1 				AFIO_RMP_CFG3_SPI1_RMP_1_Msk	/*!<SPI1_RMP[1:0]  Bit 1 (SPI1 Alternate function remapping) */
#define AFIO_RMP_CFG3_USART2_RMP_1_Pos			(19U)
#define AFIO_RMP_CFG3_USART2_RMP_1_Msk			(0x1UL << AFIO_RMP_CFG3_USART2_RMP_1_Pos)	/*!< 0x00080000 */
#define AFIO_RMP_CFG3_USART2_RMP_1  			AFIO_RMP_CFG3_USART2_RMP_1_Msk	/*!<USART2_RMP[1:0]  Bit 1 (USART2 Alternate function remapping) */
#define AFIO_RMP_CFG3_UART4_RMP_Pos				(20U)
#define AFIO_RMP_CFG3_UART4_RMP_Msk				(0x3UL << AFIO_RMP_CFG3_UART4_RMP_Pos)		/*!< 0x00300000 */
#define AFIO_RMP_CFG3_UART4_RMP   				AFIO_RMP_CFG3_UART4_RMP_Msk		/*!<UART4_RMP[1:0] bits (UART4 Alternate function remapping) */
#define AFIO_RMP_CFG3_UART4_RMP_0 				((uint32_t) 0x00200000)			/*!< Bit 0 */
#define AFIO_RMP_CFG3_UART4_RMP_1 				((uint32_t) 0x00100000)			/*!< Bit 1*/
#define AFIO_RMP_CFG3_UART5_RMP_Pos				(22U)
#define AFIO_RMP_CFG3_UART5_RMP_Msk				(0x3UL << AFIO_RMP_CFG3_UART5_RMP_Pos)		/*!< 0x00C00000 */
#define AFIO_RMP_CFG3_UART5_RMP   				AFIO_RMP_CFG3_UART5_RMP_Msk		/*!<UART5_RMP[1:0] bits (UART5 Alternate function remapping) */
#define AFIO_RMP_CFG3_UART5_RMP_0 				((uint32_t) 0x00800000)			/*!< Bit 0 */
#define AFIO_RMP_CFG3_UART5_RMP_1 				((uint32_t) 0x00400000)			/*!< Bit 1*/
#define AFIO_RMP_CFG3_UART6_RMP_Pos				(24U)
#define AFIO_RMP_CFG3_UART6_RMP_Msk				(0x3UL << AFIO_RMP_CFG3_UART6_RMP_Pos)		/*!< 0x03000000 */
#define AFIO_RMP_CFG3_UART6_RMP   				AFIO_RMP_CFG3_UART6_RMP_Msk		/*!<UART6_RMP[1:0] bits (UART6 Alternate function remapping) */
#define AFIO_RMP_CFG3_UART6_RMP_0 				((uint32_t) 0x02000000)			/*!< Bit 0 */
#define AFIO_RMP_CFG3_UART6_RMP_1 				((uint32_t) 0x01000000)			/*!< Bit 1*/
#define AFIO_RMP_CFG3_UART7_RMP_Pos				(26U)
#define AFIO_RMP_CFG3_UART7_RMP_Msk				(0x3UL << AFIO_RMP_CFG3_UART7_RMP_Pos)		/*!< 0x0C000000 */
#define AFIO_RMP_CFG3_UART7_RMP   				AFIO_RMP_CFG3_UART7_RMP_Msk		/*!<UART7_RMP[1:0] bits (UART7 Alternate function remapping) */
#define AFIO_RMP_CFG3_UART7_RMP_0 				((uint32_t) 0x08000000)			/*!< Bit 0 */
#define AFIO_RMP_CFG3_UART7_RMP_1 				((uint32_t) 0x04000000)			/*!< Bit 1*/
#define AFIO_RMP_CFG3_TIM8_RMP_Pos				(30U)
#define AFIO_RMP_CFG3_TIM8_RMP_Msk				(0x3UL << AFIO_RMP_CFG3_TIM8_RMP_Pos)		/*!< 0xC0000000 */
#define AFIO_RMP_CFG3_TIM8_RMP    				AFIO_RMP_CFG3_TIM8_RMP_Msk		/*!<TIM8_RMP[1:0] bits (TIM8 Alternate function remapping) */
#define AFIO_RMP_CFG3_TIM8_RMP_0  				((uint32_t) 0x40000000)			/*!< Bit 0 */
#define AFIO_RMP_CFG3_TIM8_RMP_1  				((uint32_t) 0x80000000)			/*!< Bit 1*/

/****************  Bit definition for AFIO_RMP_CFG4 register  *****************/
#define AFIO_RMP_CFG4_COMP1_RMP_Pos				(0U)
#define AFIO_RMP_CFG4_COMP1_RMP_Msk				(0x3UL << AFIO_RMP_CFG4_COMP1_RMP_Pos)		/*!< 0x00000003 */
#define AFIO_RMP_CFG4_COMP1_RMP    				AFIO_RMP_CFG4_COMP1_RMP_Msk		/*!<COMP1_RMP[1:0] bits (COMP1 Alternate function remapping) */
#define AFIO_RMP_CFG4_COMP1_RMP_0  				((uint32_t) 0x00000001)			/*!< Bit 0 */
#define AFIO_RMP_CFG4_COMP1_RMP_1  				((uint32_t) 0x00000002)			/*!< Bit 1*/
#define AFIO_RMP_CFG4_COMP2_RMP_Pos				(2U)
#define AFIO_RMP_CFG4_COMP2_RMP_Msk				(0x3UL << AFIO_RMP_CFG4_COMP2_RMP_Pos)		/*!< 0x0000000C */
#define AFIO_RMP_CFG4_COMP2_RMP    				AFIO_RMP_CFG4_COMP2_RMP_Msk		/*!<COMP2_RMP[1:0] bits (COMP2 Alternate function remapping) */
#define AFIO_RMP_CFG4_COMP2_RMP_0  				((uint32_t) 0x00000004)			/*!< Bit 0 */
#define AFIO_RMP_CFG4_COMP2_RMP_1  				((uint32_t) 0x00000008)			/*!< Bit 1*/
#define AFIO_RMP_CFG4_COMP3_RMP_Pos				(4U)	
#define AFIO_RMP_CFG4_COMP3_RMP_Msk				(0x3UL << AFIO_RMP_CFG4_COMP3_RMP_Pos)		/*!< 0x00000030 */
#define AFIO_RMP_CFG4_COMP3_RMP    				AFIO_RMP_CFG4_COMP3_RMP_Msk		/*!<COMP3_RMP[1:0] bits (COMP3 Alternate function remapping) */
#define AFIO_RMP_CFG4_COMP3_RMP_0  				((uint32_t) 0x00000010)			/*!< Bit 0 */
#define AFIO_RMP_CFG4_COMP3_RMP_1  				((uint32_t) 0x00000020)			/*!< Bit 1*/
#define AFIO_RMP_CFG4_COMP4_RMP_Pos				(6U)
#define AFIO_RMP_CFG4_COMP4_RMP_Msk				(0x3UL << AFIO_RMP_CFG4_COMP4_RMP_Pos)		/*!< 0x000000C0 */
#define AFIO_RMP_CFG4_COMP4_RMP    				AFIO_RMP_CFG4_COMP4_RMP_Msk		/*!<COMP4_RMP[1:0] bits (COMP4 Alternate function remapping) */
#define AFIO_RMP_CFG4_COMP4_RMP_0  				((uint32_t) 0x00000040)			/*!< Bit 0 */
#define AFIO_RMP_CFG4_COMP4_RMP_1  				((uint32_t) 0x00000080)			/*!< Bit 1*/
#define AFIO_RMP_CFG4_COMP5_RMP_Pos				(8U)
#define AFIO_RMP_CFG4_COMP5_RMP_Msk				(0x3UL << AFIO_RMP_CFG4_COMP5_RMP_Pos)		/*!< 0x00000300 */
#define AFIO_RMP_CFG4_COMP5_RMP    				AFIO_RMP_CFG4_COMP5_RMP_Msk		/*!<COMP5_RMP[1:0] bits (COMP5 Alternate function remapping) */
#define AFIO_RMP_CFG4_COMP5_RMP_0 				((uint32_t) 0x00000100)			/*!< Bit 0 */
#define AFIO_RMP_CFG4_COMP5_RMP_1  				((uint32_t) 0x00000200)			/*!< Bit 1*/
#define AFIO_RMP_CFG4_COMP6_RMP_Pos				(10U)
#define AFIO_RMP_CFG4_COMP6_RMP_Msk				(0x3UL << AFIO_RMP_CFG4_COMP6_RMP_Pos)			/*!< 0x00000C00 */
#define AFIO_RMP_CFG4_COMP6_RMP    				AFIO_RMP_CFG4_COMP6_RMP_Msk		/*!<COMP6_RMP[1:0] bits (COMP6 Alternate function remapping) */
#define AFIO_RMP_CFG4_COMP6_RMP_0  				((uint32_t) 0x00000400)			/*!< Bit 0 */
#define AFIO_RMP_CFG4_COMP6_RMP_1  				((uint32_t) 0x00000800)			/*!< Bit 1*/
#define AFIO_RMP_CFG4_COMP7_RMP_Pos				(12U)
#define AFIO_RMP_CFG4_COMP7_RMP_Msk				(0x1UL << AFIO_RMP_CFG4_COMP7_RMP_Pos)			/*!< 0x00001000 */
#define AFIO_RMP_CFG4_COMP7_RMP    				AFIO_RMP_CFG4_COMP7_RMP_Msk		/*!< COMP7 remapping */
#define AFIO_RMP_CFG4_ADC3_ETRI_RMP_Pos			(14U)
#define AFIO_RMP_CFG4_ADC3_ETRI_RMP_Msk			(0x1UL << AFIO_RMP_CFG4_ADC3_ETRI_RMP_Pos)		/*!< 0x00004000 */
#define AFIO_RMP_CFG4_ADC3_ETRI_RMP    			AFIO_RMP_CFG4_ADC3_ETRI_RMP_Msk	/*!< ADC3_ETRI remapping */
#define AFIO_RMP_CFG4_ADC3_ETRR_RMP_Pos			(15U)
#define AFIO_RMP_CFG4_ADC3_ETRR_RMP_Msk			(0x1UL << AFIO_RMP_CFG4_ADC3_ETRR_RMP_Pos)		/*!< 0x00008000 */
#define AFIO_RMP_CFG4_ADC3_ETRR_RMP    			AFIO_RMP_CFG4_ADC3_ETRR_RMP_Msk	/*!< ADC3_ETRR remapping */
#define AFIO_RMP_CFG4_ADC4_ETRI_RMP_Pos			(16U)
#define AFIO_RMP_CFG4_ADC4_ETRI_RMP_Msk			(0x1UL << AFIO_RMP_CFG4_ADC4_ETRI_RMP_Pos)		/*!< 0x00010000 */
#define AFIO_RMP_CFG4_ADC4_ETRI_RMP    			AFIO_RMP_CFG4_ADC4_ETRI_RMP_Msk	/*!< ADC4_ETRI remapping */
#define AFIO_RMP_CFG4_ADC4_ETRR_RMP_Pos			(17U)
#define AFIO_RMP_CFG4_ADC4_ETRR_RMP_Msk			(0x1UL << AFIO_RMP_CFG4_ADC4_ETRR_RMP_Pos)		/*!< 0x00020000 */
#define AFIO_RMP_CFG4_ADC4_ETRR_RMP    			AFIO_RMP_CFG4_ADC4_ETRR_RMP_Msk	/*!< ADC4_ETRR remapping */
#define AFIO_RMP_CFG4_TSC_OUT_CTRL_RMP_Pos		(18U)
#define AFIO_RMP_CFG4_TSC_OUT_CTRL_RMP_Msk		(0x1UL << AFIO_RMP_CFG4_TSC_OUT_CTRL_RMP_Pos)	/*!< 0x00040000 */
#define AFIO_RMP_CFG4_TSC_OUT_CTRL_RMP 			AFIO_RMP_CFG4_TSC_OUT_CTRL_RMP_Msk	/*!< TSC_OUT_CTRL remapping */
#define AFIO_RMP_CFG4_QSPI_XIP_EN_RMP_Pos		(19U)
#define AFIO_RMP_CFG4_QSPI_XIP_EN_RMP_Msk		(0x1UL << AFIO_RMP_CFG4_QSPI_XIP_EN_RMP_Pos)	/*!< 0x00080000 */
#define AFIO_RMP_CFG4_QSPI_XIP_EN_RMP  			AFIO_RMP_CFG4_QSPI_XIP_EN_RMP_Msk	/*!< QSPI_XIP remapping */
#define AFIO_RMP_CFG4_SPI1_NSS_RMP_Pos			(22U)
#define AFIO_RMP_CFG4_SPI1_NSS_RMP_Msk			(0x1UL << AFIO_RMP_CFG4_SPI1_NSS_RMP_Pos)		/*!< 0x00400000 */
#define AFIO_RMP_CFG4_SPI1_NSS_RMP 				AFIO_RMP_CFG4_SPI1_NSS_RMP_Msk	/*!< SPI1_NSS remapping */
#define AFIO_RMP_CFG4_SPI2_NSS_RMP_Pos			(23U)
#define AFIO_RMP_CFG4_SPI2_NSS_RMP_Msk			(0x1UL << AFIO_RMP_CFG4_SPI2_NSS_RMP_Pos)		/*!< 0x00800000 */
#define AFIO_RMP_CFG4_SPI2_NSS_RMP 				AFIO_RMP_CFG4_SPI2_NSS_RMP_Msk	/*!< SPI2_NSS remapping */
#define AFIO_RMP_CFG4_SPI3_NSS_RMP_Pos			(24U)
#define AFIO_RMP_CFG4_SPI3_NSS_RMP_Msk			(0x1UL << AFIO_RMP_CFG4_SPI3_NSS_RMP_Pos)		/*!< 0x01000000 */
#define AFIO_RMP_CFG4_SPI3_NSS_RMP 				AFIO_RMP_CFG4_SPI3_NSS_RMP_Msk	/*!< SPI3_NSS remapping */
#define AFIO_RMP_CFG4_QSPI_MISO_RMP_Pos			(25U)
#define AFIO_RMP_CFG4_QSPI_MISO_RMP_Msk			(0x1UL << AFIO_RMP_CFG4_QSPI_MISO_RMP_Pos)		/*!< 0x02000000 */
#define AFIO_RMP_CFG4_QSPI_MISO_RMP 			AFIO_RMP_CFG4_QSPI_MISO_RMP_Msk	/*!< QSPI_MISO remapping */

/****************  Bit definition for AFIO_RMP_CFG5 register  *****************/
#define AFIO_RMP_CFG5_ECLAMP1_RST_EN_RMP_Pos	(0U)
#define AFIO_RMP_CFG5_ECLAMP1_RST_EN_RMP_Msk	(0x1UL << AFIO_RMP_CFG5_ECLAMP1_RST_EN_RMP_Pos)	/*!< 0x00000001 */
#define AFIO_RMP_CFG5_ECLAMP1_RST_EN_RMP    	AFIO_RMP_CFG5_ECLAMP1_RST_EN_RMP_Msk	/*!< ECLAMP1_RST_EN remapping */
#define AFIO_RMP_CFG5_ECLAMP2_RST_EN_RMP_Pos	(1U)
#define AFIO_RMP_CFG5_ECLAMP2_RST_EN_RMP_Msk	(0x1UL << AFIO_RMP_CFG5_ECLAMP2_RST_EN_RMP_Pos)	/*!< 0x00000002 */
#define AFIO_RMP_CFG5_ECLAMP2_RST_EN_RMP    	AFIO_RMP_CFG5_ECLAMP2_RST_EN_RMP_Msk	/*!< ECLAMP2_RST_EN remapping */
#define AFIO_RMP_CFG5_ECLAMP3_RST_EN_RMP_Pos	(2U)
#define AFIO_RMP_CFG5_ECLAMP3_RST_EN_RMP_Msk	(0x1UL << AFIO_RMP_CFG5_ECLAMP3_RST_EN_RMP_Pos)	/*!< 0x00000004 */
#define AFIO_RMP_CFG5_ECLAMP3_RST_EN_RMP    	AFIO_RMP_CFG5_ECLAMP3_RST_EN_RMP_Msk	/*!< ECLAMP3_RST_EN remapping */
#define AFIO_RMP_CFG5_ECLAMP4_RST_EN_RMP_Pos	(3U)
#define AFIO_RMP_CFG5_ECLAMP4_RST_EN_RMP_Msk	(0x1UL << AFIO_RMP_CFG5_ECLAMP4_RST_EN_RMP_Pos)	/*!< 0x00000008 */
#define AFIO_RMP_CFG5_ECLAMP4_RST_EN_RMP    	AFIO_RMP_CFG5_ECLAMP4_RST_EN_RMP_Msk	/*!< ECLAMP4_RST_EN remapping */
#define AFIO_RMP_CFG5_EGBN1_RST_EN_RMP_Pos		(4U)
#define AFIO_RMP_CFG5_EGBN1_RST_EN_RMP_Msk		(0x1UL << AFIO_RMP_CFG5_EGBN1_RST_EN_RMP_Pos)	/*!< 0x00000010 */
#define AFIO_RMP_CFG5_EGBN1_RST_EN_RMP      	AFIO_RMP_CFG5_EGBN1_RST_EN_RMP_Msk		/*!< EGBN1_RST_EN remapping */
#define AFIO_RMP_CFG5_EGBN2_RST_EN_RMP_Pos		(5U)
#define AFIO_RMP_CFG5_EGBN2_RST_EN_RMP_Msk		(0x1UL << AFIO_RMP_CFG5_EGBN2_RST_EN_RMP_Pos)	/*!< 0x00000020 */
#define AFIO_RMP_CFG5_EGBN2_RST_EN_RMP      	AFIO_RMP_CFG5_EGBN2_RST_EN_RMP_Msk		/*!< EGBN2_RST_EN remapping */
#define AFIO_RMP_CFG5_EGBN3_RST_EN_RMP_Pos		(6U)
#define AFIO_RMP_CFG5_EGBN3_RST_EN_RMP_Msk		(0x1UL << AFIO_RMP_CFG5_EGBN3_RST_EN_RMP_Pos)	/*!< 0x00000040 */
#define AFIO_RMP_CFG5_EGBN3_RST_EN_RMP      	AFIO_RMP_CFG5_EGBN3_RST_EN_RMP_Msk		/*!< EGBN3_RST_EN remapping */
#define AFIO_RMP_CFG5_EGBN4_RST_EN_RMP_Pos		(7U)
#define AFIO_RMP_CFG5_EGBN4_RST_EN_RMP_Msk		(0x1UL << AFIO_RMP_CFG5_EGBN4_RST_EN_RMP_Pos)	/*!< 0x00000080 */
#define AFIO_RMP_CFG5_EGBN4_RST_EN_RMP      	AFIO_RMP_CFG5_EGBN4_RST_EN_RMP_Msk		/*!< EGBN4_RST_EN remapping */
#define AFIO_RMP_CFG5_EGB1_RST_EN_RMP_Pos		(8U)
#define AFIO_RMP_CFG5_EGB1_RST_EN_RMP_Msk		(0x1UL << AFIO_RMP_CFG5_EGB1_RST_EN_RMP_Pos)	/*!< 0x00000100 */
#define AFIO_RMP_CFG5_EGB1_RST_EN_RMP       	AFIO_RMP_CFG5_EGB1_RST_EN_RMP_Msk		/*!< EGB1_RST_EN remapping */
#define AFIO_RMP_CFG5_EGB2_RST_EN_RMP_Pos		(9U)
#define AFIO_RMP_CFG5_EGB2_RST_EN_RMP_Msk		(0x1UL << AFIO_RMP_CFG5_EGB2_RST_EN_RMP_Pos)	/*!< 0x00000200 */
#define AFIO_RMP_CFG5_EGB2_RST_EN_RMP       	AFIO_RMP_CFG5_EGB2_RST_EN_RMP_Msk		/*!< EGB2_RST_EN remapping */
#define AFIO_RMP_CFG5_EGB3_RST_EN_RMP_Pos		(10U)
#define AFIO_RMP_CFG5_EGB3_RST_EN_RMP_Msk		(0x1UL << AFIO_RMP_CFG5_EGB3_RST_EN_RMP_Pos)	/*!< 0x00000400 */
#define AFIO_RMP_CFG5_EGB3_RST_EN_RMP       	AFIO_RMP_CFG5_EGB3_RST_EN_RMP_Msk		/*!< EGB3_RST_EN remapping */
#define AFIO_RMP_CFG5_EGB4_RST_EN_RMP_Pos		(11U)
#define AFIO_RMP_CFG5_EGB4_RST_EN_RMP_Msk		(0x1UL << AFIO_RMP_CFG5_EGB4_RST_EN_RMP_Pos)	/*!< 0x00000800 */
#define AFIO_RMP_CFG5_EGB4_RST_EN_RMP       	AFIO_RMP_CFG5_EGB4_RST_EN_RMP_Msk		/*!< EGB4_RST_EN remapping */
#define AFIO_RMP_CFG5_ECLAMP1_DET_EN_RMP_Pos	(12U)
#define AFIO_RMP_CFG5_ECLAMP1_DET_EN_RMP_Msk	(0x1UL << AFIO_RMP_CFG5_ECLAMP1_DET_EN_RMP_Pos)	/*!< 0x00001000 */
#define AFIO_RMP_CFG5_ECLAMP1_DET_EN_RMP    	AFIO_RMP_CFG5_ECLAMP1_DET_EN_RMP_Msk	/*!< ECLAMP1_DET_EN remapping */
#define AFIO_RMP_CFG5_ECLAMP2_DET_EN_RMP_Pos	(13U)
#define AFIO_RMP_CFG5_ECLAMP2_DET_EN_RMP_Msk	(0x1UL << AFIO_RMP_CFG5_ECLAMP2_DET_EN_RMP_Pos)	/*!< 0x00002000 */
#define AFIO_RMP_CFG5_ECLAMP2_DET_EN_RMP    	AFIO_RMP_CFG5_ECLAMP2_DET_EN_RMP_Msk	/*!< ECLAMP2_DET_EN remapping */
#define AFIO_RMP_CFG5_ECLAMP3_DET_EN_RMP_Pos	(14U)
#define AFIO_RMP_CFG5_ECLAMP3_DET_EN_RMP_Msk	(0x1UL << AFIO_RMP_CFG5_ECLAMP3_DET_EN_RMP_Pos)	/*!< 0x00004000 */
#define AFIO_RMP_CFG5_ECLAMP3_DET_EN_RMP    	AFIO_RMP_CFG5_ECLAMP3_DET_EN_RMP_Msk	/*!< ECLAMP3_DET_EN remapping */
#define AFIO_RMP_CFG5_ECLAMP4_DET_EN_RMP_Pos	(15U)
#define AFIO_RMP_CFG5_ECLAMP4_DET_EN_RMP_Msk	(0x1UL << AFIO_RMP_CFG5_ECLAMP4_DET_EN_RMP_Pos)	/*!< 0x00008000 */
#define AFIO_RMP_CFG5_ECLAMP4_DET_EN_RMP    	AFIO_RMP_CFG5_ECLAMP4_DET_EN_RMP_Msk	/*!< ECLAMP4_DET_EN remapping */
#define AFIO_RMP_CFG5_EGBN1_DET_EN_RMP_Pos		(16U)
#define AFIO_RMP_CFG5_EGBN1_DET_EN_RMP_Msk		(0x1UL << AFIO_RMP_CFG5_EGBN1_DET_EN_RMP_Pos)	/*!< 0x00010000 */
#define AFIO_RMP_CFG5_EGBN1_DET_EN_RMP      	AFIO_RMP_CFG5_EGBN1_DET_EN_RMP_Msk		/*!< EGBN1_DET_EN remapping */
#define AFIO_RMP_CFG5_EGBN2_DET_EN_RMP_Pos		(17U)
#define AFIO_RMP_CFG5_EGBN2_DET_EN_RMP_Msk		(0x1UL << AFIO_RMP_CFG5_EGBN2_DET_EN_RMP_Pos)	/*!< 0x00020000 */
#define AFIO_RMP_CFG5_EGBN2_DET_EN_RMP      	AFIO_RMP_CFG5_EGBN2_DET_EN_RMP_Msk		/*!< EGBN2_DET_EN remapping */
#define AFIO_RMP_CFG5_EGBN3_DET_EN_RMP_Pos		(18U)
#define AFIO_RMP_CFG5_EGBN3_DET_EN_RMP_Msk		(0x1UL << AFIO_RMP_CFG5_EGBN3_DET_EN_RMP_Pos)	/*!< 0x00040000 */
#define AFIO_RMP_CFG5_EGBN3_DET_EN_RMP      	AFIO_RMP_CFG5_EGBN3_DET_EN_RMP_Msk		/*!< EGBN3_DET_EN remapping */
#define AFIO_RMP_CFG5_EGBN4_DET_EN_RMP_Pos		(19U)
#define AFIO_RMP_CFG5_EGBN4_DET_EN_RMP_Msk		(0x1UL << AFIO_RMP_CFG5_EGBN4_DET_EN_RMP_Pos)	/*!< 0x00080000 */
#define AFIO_RMP_CFG5_EGBN4_DET_EN_RMP      	AFIO_RMP_CFG5_EGBN4_DET_EN_RMP_Msk		/*!< EGBN4_DET_EN remapping */
#define AFIO_RMP_CFG5_EGB1_DET_EN_RMP_Pos		(20U)
#define AFIO_RMP_CFG5_EGB1_DET_EN_RMP_Msk		(0x1UL << AFIO_RMP_CFG5_EGB1_DET_EN_RMP_Pos)	/*!< 0x00100000 */
#define AFIO_RMP_CFG5_EGB1_DET_EN_RMP       	AFIO_RMP_CFG5_EGB1_DET_EN_RMP_Msk		/*!< EGB1_DET_EN remapping */
#define AFIO_RMP_CFG5_EGB2_DET_EN_RMP_Pos		(21U)
#define AFIO_RMP_CFG5_EGB2_DET_EN_RMP_Msk		(0x1UL << AFIO_RMP_CFG5_EGB2_DET_EN_RMP_Pos)	/*!< 0x00200000 */
#define AFIO_RMP_CFG5_EGB2_DET_EN_RMP       	AFIO_RMP_CFG5_EGB2_DET_EN_RMP_Msk		/*!< EGB2_DET_EN remapping */
#define AFIO_RMP_CFG5_EGB3_DET_EN_RMP_Pos		(22U)
#define AFIO_RMP_CFG5_EGB3_DET_EN_RMP_Msk		(0x1UL << AFIO_RMP_CFG5_EGB3_DET_EN_RMP_Pos)	/*!< 0x00400000 */
#define AFIO_RMP_CFG5_EGB3_DET_EN_RMP       	AFIO_RMP_CFG5_EGB3_DET_EN_RMP_Msk		/*!< EGB3_DET_EN remapping */
#define AFIO_RMP_CFG5_EGB4_DET_EN_RMP_Pos		(23U)
#define AFIO_RMP_CFG5_EGB4_DET_EN_RMP_Msk		(0x1UL << AFIO_RMP_CFG5_EGB4_DET_EN_RMP_Pos)	/*!< 0x00800000 */
#define AFIO_RMP_CFG5_EGB4_DET_EN_RMP       	AFIO_RMP_CFG5_EGB4_DET_EN_RMP_Msk		/*!< EGB4_DET_EN remapping */

/******************************************************************************/
/*                                                                            */
/*                    External Interrupt/Event Controller                     */
/*                                                                            */
/******************************************************************************/
/******************  Bit definition for EXTI_IMASK register  ******************/
#define EXTI_IMASK_IMASK_ALL  					((uint32_t) 0x003FFFFF)			/*!< Interrupt Mask for all lines */
#define EXTI_IMASK_IMASK0_Pos					(0U)
#define EXTI_IMASK_IMASK0_Msk					(0x1UL << EXTI_IMASK_IMASK0_Pos)
#define EXTI_IMASK_IMASK0						EXTI_IMASK_IMASK0_Msk			/*!< Interrupt Mask on line 0 */
#define EXTI_IMASK_IMASK1_Pos					(1U)
#define EXTI_IMASK_IMASK1_Msk					(0x1UL << EXTI_IMASK_IMASK1_Pos)
#define EXTI_IMASK_IMASK1						EXTI_IMASK_IMASK1_Msk			/*!< Interrupt Mask on line 1 */
#define EXTI_IMASK_IMASK2_Pos					(2U)
#define EXTI_IMASK_IMASK2_Msk					(0x1UL << EXTI_IMASK_IMASK2_Pos)
#define EXTI_IMASK_IMASK2						EXTI_IMASK_IMASK2_Msk			/*!< Interrupt Mask on line 2 */
#define EXTI_IMASK_IMASK3_Pos					(3U)
#define EXTI_IMASK_IMASK3_Msk					(0x1UL << EXTI_IMASK_IMASK3_Pos)
#define EXTI_IMASK_IMASK3						EXTI_IMASK_IMASK3_Msk			/*!< Interrupt Mask on line 3 */
#define EXTI_IMASK_IMASK4_Pos					(4U)
#define EXTI_IMASK_IMASK4_Msk					(0x1UL << EXTI_IMASK_IMASK4_Pos)
#define EXTI_IMASK_IMASK4						EXTI_IMASK_IMASK4_Msk			/*!< Interrupt Mask on line 4 */
#define EXTI_IMASK_IMASK5_Pos					(5U)
#define EXTI_IMASK_IMASK5_Msk					(0x1UL << EXTI_IMASK_IMASK5_Pos)
#define EXTI_IMASK_IMASK5						EXTI_IMASK_IMASK5_Msk			/*!< Interrupt Mask on line 5 */
#define EXTI_IMASK_IMASK6_Pos					(6U)
#define EXTI_IMASK_IMASK6_Msk					(0x1UL << EXTI_IMASK_IMASK6_Pos)
#define EXTI_IMASK_IMASK6						EXTI_IMASK_IMASK6_Msk			/*!< Interrupt Mask on line 6 */
#define EXTI_IMASK_IMASK7_Pos					(7U)
#define EXTI_IMASK_IMASK7_Msk					(0x1UL << EXTI_IMASK_IMASK7_Pos)
#define EXTI_IMASK_IMASK7						EXTI_IMASK_IMASK7_Msk			/*!< Interrupt Mask on line 7 */
#define EXTI_IMASK_IMASK8_Pos					(8U)
#define EXTI_IMASK_IMASK8_Msk					(0x1UL << EXTI_IMASK_IMASK8_Pos)
#define EXTI_IMASK_IMASK8						EXTI_IMASK_IMASK8_Msk			/*!< Interrupt Mask on line 8 */
#define EXTI_IMASK_IMASK9_Pos					(9U)
#define EXTI_IMASK_IMASK9_Msk					(0x1UL << EXTI_IMASK_IMASK9_Pos)
#define EXTI_IMASK_IMASK9						EXTI_IMASK_IMASK9_Msk			/*!< Interrupt Mask on line 9 */
#define EXTI_IMASK_IMASK10_Pos					(10U)
#define EXTI_IMASK_IMASK10_Msk					(0x1UL << EXTI_IMASK_IMASK10_Pos)
#define EXTI_IMASK_IMASK10						EXTI_IMASK_IMASK10_Msk			/*!< Interrupt Mask on line 10 */
#define EXTI_IMASK_IMASK11_Pos					(11U)
#define EXTI_IMASK_IMASK11_Msk					(0x1UL << EXTI_IMASK_IMASK11_Pos)
#define EXTI_IMASK_IMASK11						EXTI_IMASK_IMASK11_Msk			/*!< Interrupt Mask on line 11 */
#define EXTI_IMASK_IMASK12_Pos					(12U)
#define EXTI_IMASK_IMASK12_Msk					(0x1UL << EXTI_IMASK_IMASK12_Pos)
#define EXTI_IMASK_IMASK12						EXTI_IMASK_IMASK12_Msk			/*!< Interrupt Mask on line 12 */
#define EXTI_IMASK_IMASK13_Pos					(13U)
#define EXTI_IMASK_IMASK13_Msk					(0x1UL << EXTI_IMASK_IMASK13_Pos)
#define EXTI_IMASK_IMASK13						EXTI_IMASK_IMASK13_Msk			/*!< Interrupt Mask on line 13 */
#define EXTI_IMASK_IMASK14_Pos					(14U)
#define EXTI_IMASK_IMASK14_Msk					(0x1UL << EXTI_IMASK_IMASK14_Pos)
#define EXTI_IMASK_IMASK14						EXTI_IMASK_IMASK14_Msk			/*!< Interrupt Mask on line 14 */
#define EXTI_IMASK_IMASK15_Pos					(15U)
#define EXTI_IMASK_IMASK15_Msk					(0x1UL << EXTI_IMASK_IMASK15_Pos)
#define EXTI_IMASK_IMASK15						EXTI_IMASK_IMASK15_Msk			/*!< Interrupt Mask on line 15 */
#define EXTI_IMASK_IMASK16_Pos					(16U)
#define EXTI_IMASK_IMASK16_Msk					(0x1UL << EXTI_IMASK_IMASK16_Pos)
#define EXTI_IMASK_IMASK16						EXTI_IMASK_IMASK16_Msk			/*!< Interrupt Mask on line 16 */
#define EXTI_IMASK_IMASK17_Pos					(17U)
#define EXTI_IMASK_IMASK17_Msk					(0x1UL << EXTI_IMASK_IMASK17_Pos)
#define EXTI_IMASK_IMASK17						EXTI_IMASK_IMASK17_Msk			/*!< Interrupt Mask on line 17 */
#define EXTI_IMASK_IMASK18_Pos					(18U)
#define EXTI_IMASK_IMASK18_Msk					(0x1UL << EXTI_IMASK_IMASK18_Pos)
#define EXTI_IMASK_IMASK18						EXTI_IMASK_IMASK18_Msk			/*!< Interrupt Mask on line 18 */
#define EXTI_IMASK_IMASK19_Pos					(19U)
#define EXTI_IMASK_IMASK19_Msk					(0x1UL << EXTI_IMASK_IMASK19_Pos)
#define EXTI_IMASK_IMASK19						EXTI_IMASK_IMASK19_Msk			/*!< Interrupt Mask on line 19 */
#define EXTI_IMASK_IMASK20_Pos					(20U)
#define EXTI_IMASK_IMASK20_Msk					(0x1UL << EXTI_IMASK_IMASK20_Pos)
#define EXTI_IMASK_IMASK20						EXTI_IMASK_IMASK20_Msk			/*!< Interrupt Mask on line 20 */
#define EXTI_IMASK_IMASK21_Pos					(21U)
#define EXTI_IMASK_IMASK21_Msk					(0x1UL << EXTI_IMASK_IMASK21_Pos)
#define EXTI_IMASK_IMASK21						EXTI_IMASK_IMASK21_Msk			/*!< Interrupt Mask on line 21 */

/******************  Bit definition for EXTI_EMASK register  ******************/
#define EXTI_EMASK_EMASK_ALL  					((uint32_t) 0x003FFFFF)			/*!< Event Mask for all lines */
#define EXTI_EMASK_EMASK0_Pos					(0U)
#define EXTI_EMASK_EMASK0_Msk					(0x1UL << EXTI_EMASK_EMASK0_Pos)
#define EXTI_EMASK_EMASK0						EXTI_EMASK_EMASK0_Msk			/*!< Event Mask on line 0 */
#define EXTI_EMASK_EMASK1_Pos					(1U)
#define EXTI_EMASK_EMASK1_Msk					(0x1UL << EXTI_EMASK_EMASK1_Pos)
#define EXTI_EMASK_EMASK1						EXTI_EMASK_EMASK1_Msk			/*!< Event Mask on line 1 */
#define EXTI_EMASK_EMASK2_Pos					(2U)
#define EXTI_EMASK_EMASK2_Msk					(0x1UL << EXTI_EMASK_EMASK2_Pos)
#define EXTI_EMASK_EMASK2						EXTI_EMASK_EMASK2_Msk			/*!< Event Mask on line 2 */
#define EXTI_EMASK_EMASK3_Pos					(3U)
#define EXTI_EMASK_EMASK3_Msk					(0x1UL << EXTI_EMASK_EMASK3_Pos)
#define EXTI_EMASK_EMASK3						EXTI_EMASK_EMASK3_Msk			/*!< Event Mask on line 3 */
#define EXTI_EMASK_EMASK4_Pos					(4U)
#define EXTI_EMASK_EMASK4_Msk					(0x1UL << EXTI_EMASK_EMASK4_Pos)
#define EXTI_EMASK_EMASK4						EXTI_EMASK_EMASK4_Msk			/*!< Event Mask on line 4 */
#define EXTI_EMASK_EMASK5_Pos					(5U)
#define EXTI_EMASK_EMASK5_Msk					(0x1UL << EXTI_EMASK_EMASK5_Pos)
#define EXTI_EMASK_EMASK5						EXTI_EMASK_EMASK5_Msk			/*!< Event Mask on line 5 */
#define EXTI_EMASK_EMASK6_Pos					(6U)
#define EXTI_EMASK_EMASK6_Msk					(0x1UL << EXTI_EMASK_EMASK6_Pos)
#define EXTI_EMASK_EMASK6						EXTI_EMASK_EMASK6_Msk			/*!< Event Mask on line 6 */
#define EXTI_EMASK_EMASK7_Pos					(7U)
#define EXTI_EMASK_EMASK7_Msk					(0x1UL << EXTI_EMASK_EMASK7_Pos)
#define EXTI_EMASK_EMASK7						EXTI_EMASK_EMASK7_Msk			/*!< Event Mask on line 7 */
#define EXTI_EMASK_EMASK8_Pos					(8U)
#define EXTI_EMASK_EMASK8_Msk					(0x1UL << EXTI_EMASK_EMASK8_Pos)
#define EXTI_EMASK_EMASK8						EXTI_EMASK_EMASK8_Msk			/*!< Event Mask on line 8 */
#define EXTI_EMASK_EMASK9_Pos					(9U)
#define EXTI_EMASK_EMASK9_Msk					(0x1UL << EXTI_EMASK_EMASK9_Pos)
#define EXTI_EMASK_EMASK9						EXTI_EMASK_EMASK9_Msk			/*!< Event Mask on line 9 */
#define EXTI_EMASK_EMASK10_Pos					(10U)
#define EXTI_EMASK_EMASK10_Msk					(0x1UL << EXTI_EMASK_EMASK10_Pos)
#define EXTI_EMASK_EMASK10						EXTI_EMASK_EMASK10_Msk			/*!< Event Mask on line 10 */
#define EXTI_EMASK_EMASK11_Pos					(11U)
#define EXTI_EMASK_EMASK11_Msk					(0x1UL << EXTI_EMASK_EMASK11_Pos)
#define EXTI_EMASK_EMASK11						EXTI_EMASK_EMASK11_Msk			/*!< Event Mask on line 11 */
#define EXTI_EMASK_EMASK12_Pos					(12U)
#define EXTI_EMASK_EMASK12_Msk					(0x1UL << EXTI_EMASK_EMASK12_Pos)
#define EXTI_EMASK_EMASK12						EXTI_EMASK_EMASK12_Msk			/*!< Event Mask on line 12 */
#define EXTI_EMASK_EMASK13_Pos					(13U)
#define EXTI_EMASK_EMASK13_Msk					(0x1UL << EXTI_EMASK_EMASK13_Pos)
#define EXTI_EMASK_EMASK13						EXTI_EMASK_EMASK13_Msk			/*!< Event Mask on line 13 */
#define EXTI_EMASK_EMASK14_Pos					(14U)
#define EXTI_EMASK_EMASK14_Msk					(0x1UL << EXTI_EMASK_EMASK14_Pos)
#define EXTI_EMASK_EMASK14						EXTI_EMASK_EMASK14_Msk			/*!< Event Mask on line 14 */
#define EXTI_EMASK_EMASK15_Pos					(15U)
#define EXTI_EMASK_EMASK15_Msk					(0x1UL << EXTI_EMASK_EMASK15_Pos)
#define EXTI_EMASK_EMASK15						EXTI_EMASK_EMASK15_Msk			/*!< Event Mask on line 15 */
#define EXTI_EMASK_EMASK16_Pos					(16U)
#define EXTI_EMASK_EMASK16_Msk					(0x1UL << EXTI_EMASK_EMASK16_Pos)
#define EXTI_EMASK_EMASK16						EXTI_EMASK_EMASK16_Msk			/*!< Event Mask on line 16 */
#define EXTI_EMASK_EMASK17_Pos					(17U)
#define EXTI_EMASK_EMASK17_Msk					(0x1UL << EXTI_EMASK_EMASK17_Pos)
#define EXTI_EMASK_EMASK17						EXTI_EMASK_EMASK17_Msk			/*!< Event Mask on line 17 */
#define EXTI_EMASK_EMASK18_Pos					(18U)
#define EXTI_EMASK_EMASK18_Msk					(0x1UL << EXTI_EMASK_EMASK18_Pos)
#define EXTI_EMASK_EMASK18						EXTI_EMASK_EMASK18_Msk			/*!< Event Mask on line 18 */
#define EXTI_EMASK_EMASK19_Pos					(19U)
#define EXTI_EMASK_EMASK19_Msk					(0x1UL << EXTI_EMASK_EMASK19_Pos)
#define EXTI_EMASK_EMASK19						EXTI_EMASK_EMASK19_Msk			/*!< Event Mask on line 19 */
#define EXTI_EMASK_EMASK20_Pos					(20U)
#define EXTI_EMASK_EMASK20_Msk					(0x1UL << EXTI_EMASK_EMASK20_Pos)
#define EXTI_EMASK_EMASK20						EXTI_EMASK_EMASK20_Msk			/*!< Event Mask on line 20 */
#define EXTI_EMASK_EMASK21_Pos					(21U)
#define EXTI_EMASK_EMASK21_Msk					(0x1UL << EXTI_EMASK_EMASK21_Pos)
#define EXTI_EMASK_EMASK21						EXTI_EMASK_EMASK21_Msk			/*!< Event Mask on line 21 */

/*****************  Bit definition for EXTI_RT_CFG register  ******************/
#define EXTI_RT_CFG_RT_CFG_ALL 					((uint32_t) 0x003FFFFF)			/*!< Rising trigger event configuration for all lines */
#define EXTI_RT_CFG_RT_CFG0_Pos					(0U)
#define EXTI_RT_CFG_RT_CFG0_Msk					(0x1UL << EXTI_RT_CFG_RT_CFG0_Pos)
#define EXTI_RT_CFG_RT_CFG0						EXTI_RT_CFG_RT_CFG0_Msk			/*!< Rising trigger event configuration bit of line 0 */
#define EXTI_RT_CFG_RT_CFG1_Pos					(1U)
#define EXTI_RT_CFG_RT_CFG1_Msk					(0x1UL << EXTI_RT_CFG_RT_CFG1_Pos)
#define EXTI_RT_CFG_RT_CFG1						EXTI_RT_CFG_RT_CFG1_Msk			/*!< Rising trigger event configuration bit of line 1 */
#define EXTI_RT_CFG_RT_CFG2_Pos					(2U)
#define EXTI_RT_CFG_RT_CFG2_Msk					(0x1UL << EXTI_RT_CFG_RT_CFG2_Pos)
#define EXTI_RT_CFG_RT_CFG2						EXTI_RT_CFG_RT_CFG2_Msk			/*!< Rising trigger event configuration bit of line 2 */
#define EXTI_RT_CFG_RT_CFG3_Pos					(3U)
#define EXTI_RT_CFG_RT_CFG3_Msk					(0x1UL << EXTI_RT_CFG_RT_CFG3_Pos)
#define EXTI_RT_CFG_RT_CFG3						EXTI_RT_CFG_RT_CFG3_Msk			/*!< Rising trigger event configuration bit of line 3 */
#define EXTI_RT_CFG_RT_CFG4_Pos					(4U)
#define EXTI_RT_CFG_RT_CFG4_Msk					(0x1UL << EXTI_RT_CFG_RT_CFG4_Pos)
#define EXTI_RT_CFG_RT_CFG4						EXTI_RT_CFG_RT_CFG4_Msk			/*!< Rising trigger event configuration bit of line 4 */
#define EXTI_RT_CFG_RT_CFG5_Pos					(5U)
#define EXTI_RT_CFG_RT_CFG5_Msk					(0x1UL << EXTI_RT_CFG_RT_CFG5_Pos)
#define EXTI_RT_CFG_RT_CFG5						EXTI_RT_CFG_RT_CFG5_Msk			/*!< Rising trigger event configuration bit of line 5 */
#define EXTI_RT_CFG_RT_CFG6_Pos					(6U)
#define EXTI_RT_CFG_RT_CFG6_Msk					(0x1UL << EXTI_RT_CFG_RT_CFG6_Pos)
#define EXTI_RT_CFG_RT_CFG6						EXTI_RT_CFG_RT_CFG6_Msk			/*!< Rising trigger event configuration bit of line 6 */
#define EXTI_RT_CFG_RT_CFG7_Pos					(7U)
#define EXTI_RT_CFG_RT_CFG7_Msk					(0x1UL << EXTI_RT_CFG_RT_CFG7_Pos)
#define EXTI_RT_CFG_RT_CFG7						EXTI_RT_CFG_RT_CFG7_Msk			/*!< Rising trigger event configuration bit of line 7 */
#define EXTI_RT_CFG_RT_CFG8_Pos					(8U)
#define EXTI_RT_CFG_RT_CFG8_Msk					(0x1UL << EXTI_RT_CFG_RT_CFG8_Pos)
#define EXTI_RT_CFG_RT_CFG8						EXTI_RT_CFG_RT_CFG8_Msk			/*!< Rising trigger event configuration bit of line 8 */
#define EXTI_RT_CFG_RT_CFG9_Pos					(9U)
#define EXTI_RT_CFG_RT_CFG9_Msk					(0x1UL << EXTI_RT_CFG_RT_CFG9_Pos)
#define EXTI_RT_CFG_RT_CFG9						EXTI_RT_CFG_RT_CFG9_Msk			/*!< Rising trigger event configuration bit of line 9 */
#define EXTI_RT_CFG_RT_CFG10_Pos				(10U)
#define EXTI_RT_CFG_RT_CFG10_Msk				(0x1UL << EXTI_RT_CFG_RT_CFG10_Pos)
#define EXTI_RT_CFG_RT_CFG10					EXTI_RT_CFG_RT_CFG10_Msk		/*!< Rising trigger event configuration bit of line 10 */
#define EXTI_RT_CFG_RT_CFG11_Pos				(11U)
#define EXTI_RT_CFG_RT_CFG11_Msk				(0x1UL << EXTI_RT_CFG_RT_CFG11_Pos)
#define EXTI_RT_CFG_RT_CFG11					EXTI_RT_CFG_RT_CFG11_Msk		/*!< Rising trigger event configuration bit of line 11 */
#define EXTI_RT_CFG_RT_CFG12_Pos				(12U)
#define EXTI_RT_CFG_RT_CFG12_Msk				(0x1UL << EXTI_RT_CFG_RT_CFG12_Pos)
#define EXTI_RT_CFG_RT_CFG12					EXTI_RT_CFG_RT_CFG12_Msk		/*!< Rising trigger event configuration bit of line 12 */
#define EXTI_RT_CFG_RT_CFG13_Pos				(13U)
#define EXTI_RT_CFG_RT_CFG13_Msk				(0x1UL << EXTI_RT_CFG_RT_CFG13_Pos)
#define EXTI_RT_CFG_RT_CFG13					EXTI_RT_CFG_RT_CFG13_Msk		/*!< Rising trigger event configuration bit of line 13 */
#define EXTI_RT_CFG_RT_CFG14_Pos				(14U)
#define EXTI_RT_CFG_RT_CFG14_Msk				(0x1UL << EXTI_RT_CFG_RT_CFG14_Pos)
#define EXTI_RT_CFG_RT_CFG14					EXTI_RT_CFG_RT_CFG14_Msk		/*!< Rising trigger event configuration bit of line 14 */
#define EXTI_RT_CFG_RT_CFG15_Pos				(15U)
#define EXTI_RT_CFG_RT_CFG15_Msk				(0x1UL << EXTI_RT_CFG_RT_CFG15_Pos)
#define EXTI_RT_CFG_RT_CFG15					EXTI_RT_CFG_RT_CFG15_Msk		/*!< Rising trigger event configuration bit of line 15 */
#define EXTI_RT_CFG_RT_CFG16_Pos				(16U)
#define EXTI_RT_CFG_RT_CFG16_Msk				(0x1UL << EXTI_RT_CFG_RT_CFG16_Pos)
#define EXTI_RT_CFG_RT_CFG16					EXTI_RT_CFG_RT_CFG16_Msk		/*!< Rising trigger event configuration bit of line 16 */
#define EXTI_RT_CFG_RT_CFG17_Pos				(17U)
#define EXTI_RT_CFG_RT_CFG17_Msk				(0x1UL << EXTI_RT_CFG_RT_CFG17_Pos)
#define EXTI_RT_CFG_RT_CFG17					EXTI_RT_CFG_RT_CFG17_Msk		/*!< Rising trigger event configuration bit of line 17 */
#define EXTI_RT_CFG_RT_CFG18_Pos				(18U)
#define EXTI_RT_CFG_RT_CFG18_Msk				(0x1UL << EXTI_RT_CFG_RT_CFG18_Pos)
#define EXTI_RT_CFG_RT_CFG18					EXTI_RT_CFG_RT_CFG18_Msk		/*!< Rising trigger event configuration bit of line 18 */
#define EXTI_RT_CFG_RT_CFG19_Pos				(19U)
#define EXTI_RT_CFG_RT_CFG19_Msk				(0x1UL << EXTI_RT_CFG_RT_CFG19_Pos)
#define EXTI_RT_CFG_RT_CFG19					EXTI_RT_CFG_RT_CFG19_Msk		/*!< Rising trigger event configuration bit of line 19 */
#define EXTI_RT_CFG_RT_CFG20_Pos				(20U)
#define EXTI_RT_CFG_RT_CFG20_Msk				(0x1UL << EXTI_RT_CFG_RT_CFG20_Pos)
#define EXTI_RT_CFG_RT_CFG20					EXTI_RT_CFG_RT_CFG20_Msk		/*!< Rising trigger event configuration bit of line 20 */
#define EXTI_RT_CFG_RT_CFG21_Pos				(21U)
#define EXTI_RT_CFG_RT_CFG21_Msk				(0x1UL << EXTI_RT_CFG_RT_CFG21_Pos)
#define EXTI_RT_CFG_RT_CFG21					EXTI_RT_CFG_RT_CFG21_Msk		/*!< Rising trigger event configuration bit of line 21 */

/*****************  Bit definition for EXTI_FT_CFG register  ******************/
#define EXTI_FT_CFG_FT_CFG_ALL  				((uint32_t) 0x003FFFFF)			/*!< Falling trigger event configuration for all lines */
#define EXTI_FT_CFG_FT_CFG0_Pos					(0U)
#define EXTI_FT_CFG_FT_CFG0_Msk					(0x1UL << EXTI_FT_CFG_FT_CFG0_Pos)
#define EXTI_FT_CFG_FT_CFG0						EXTI_FT_CFG_FT_CFG0_Msk			/*!< Falling trigger event configuration bit of line 0 */
#define EXTI_FT_CFG_FT_CFG1_Pos					(1U)
#define EXTI_FT_CFG_FT_CFG1_Msk					(0x1UL << EXTI_FT_CFG_FT_CFG1_Pos)
#define EXTI_FT_CFG_FT_CFG1						EXTI_FT_CFG_FT_CFG1_Msk			/*!< Falling trigger event configuration bit of line 1 */
#define EXTI_FT_CFG_FT_CFG2_Pos					(2U)
#define EXTI_FT_CFG_FT_CFG2_Msk					(0x1UL << EXTI_FT_CFG_FT_CFG2_Pos)
#define EXTI_FT_CFG_FT_CFG2						EXTI_FT_CFG_FT_CFG2_Msk			/*!< Falling trigger event configuration bit of line 2 */
#define EXTI_FT_CFG_FT_CFG3_Pos					(3U)
#define EXTI_FT_CFG_FT_CFG3_Msk					(0x1UL << EXTI_FT_CFG_FT_CFG3_Pos)
#define EXTI_FT_CFG_FT_CFG3						EXTI_FT_CFG_FT_CFG3_Msk			/*!< Falling trigger event configuration bit of line 3 */
#define EXTI_FT_CFG_FT_CFG4_Pos					(4U)
#define EXTI_FT_CFG_FT_CFG4_Msk					(0x1UL << EXTI_FT_CFG_FT_CFG4_Pos)
#define EXTI_FT_CFG_FT_CFG4						EXTI_FT_CFG_FT_CFG4_Msk			/*!< Falling trigger event configuration bit of line 4 */
#define EXTI_FT_CFG_FT_CFG5_Pos					(5U)
#define EXTI_FT_CFG_FT_CFG5_Msk					(0x1UL << EXTI_FT_CFG_FT_CFG5_Pos)
#define EXTI_FT_CFG_FT_CFG5						EXTI_FT_CFG_FT_CFG5_Msk			/*!< Falling trigger event configuration bit of line 5 */
#define EXTI_FT_CFG_FT_CFG6_Pos					(6U)
#define EXTI_FT_CFG_FT_CFG6_Msk					(0x1UL << EXTI_FT_CFG_FT_CFG6_Pos)
#define EXTI_FT_CFG_FT_CFG6						EXTI_FT_CFG_FT_CFG6_Msk			/*!< Falling trigger event configuration bit of line 6 */
#define EXTI_FT_CFG_FT_CFG7_Pos					(7U)
#define EXTI_FT_CFG_FT_CFG7_Msk					(0x1UL << EXTI_FT_CFG_FT_CFG7_Pos)
#define EXTI_FT_CFG_FT_CFG7						EXTI_FT_CFG_FT_CFG7_Msk			/*!< Falling trigger event configuration bit of line 7 */
#define EXTI_FT_CFG_FT_CFG8_Pos					(8U)
#define EXTI_FT_CFG_FT_CFG8_Msk					(0x1UL << EXTI_FT_CFG_FT_CFG8_Pos)
#define EXTI_FT_CFG_FT_CFG8						EXTI_FT_CFG_FT_CFG8_Msk			/*!< Falling trigger event configuration bit of line 8 */
#define EXTI_FT_CFG_FT_CFG9_Pos					(9U)
#define EXTI_FT_CFG_FT_CFG9_Msk					(0x1UL << EXTI_FT_CFG_FT_CFG9_Pos)
#define EXTI_FT_CFG_FT_CFG9						EXTI_FT_CFG_FT_CFG9_Msk			/*!< Falling trigger event configuration bit of line 9 */
#define EXTI_FT_CFG_FT_CFG10_Pos				(10U)
#define EXTI_FT_CFG_FT_CFG10_Msk				(0x1UL << EXTI_FT_CFG_FT_CFG10_Pos)
#define EXTI_FT_CFG_FT_CFG10					EXTI_FT_CFG_FT_CFG10_Msk		/*!< Falling trigger event configuration bit of line 10 */
#define EXTI_FT_CFG_FT_CFG11_Pos				(11U)
#define EXTI_FT_CFG_FT_CFG11_Msk				(0x1UL << EXTI_FT_CFG_FT_CFG11_Pos)
#define EXTI_FT_CFG_FT_CFG11					EXTI_FT_CFG_FT_CFG11_Msk		/*!< Falling trigger event configuration bit of line 11 */
#define EXTI_FT_CFG_FT_CFG12_Pos				(12U)
#define EXTI_FT_CFG_FT_CFG12_Msk				(0x1UL << EXTI_FT_CFG_FT_CFG12_Pos)
#define EXTI_FT_CFG_FT_CFG12					EXTI_FT_CFG_FT_CFG12_Msk		/*!< Falling trigger event configuration bit of line 12 */
#define EXTI_FT_CFG_FT_CFG13_Pos				(13U)
#define EXTI_FT_CFG_FT_CFG13_Msk				(0x1UL << EXTI_FT_CFG_FT_CFG13_Pos)
#define EXTI_FT_CFG_FT_CFG13					EXTI_FT_CFG_FT_CFG13_Msk		/*!< Falling trigger event configuration bit of line 13 */
#define EXTI_FT_CFG_FT_CFG14_Pos				(14U)
#define EXTI_FT_CFG_FT_CFG14_Msk				(0x1UL << EXTI_FT_CFG_FT_CFG14_Pos)
#define EXTI_FT_CFG_FT_CFG14					EXTI_FT_CFG_FT_CFG14_Msk		/*!< Falling trigger event configuration bit of line 14 */
#define EXTI_FT_CFG_FT_CFG15_Pos				(15U)
#define EXTI_FT_CFG_FT_CFG15_Msk				(0x1UL << EXTI_FT_CFG_FT_CFG15_Pos)
#define EXTI_FT_CFG_FT_CFG15					EXTI_FT_CFG_FT_CFG15_Msk		/*!< Falling trigger event configuration bit of line 15 */
#define EXTI_FT_CFG_FT_CFG16_Pos				(16U)
#define EXTI_FT_CFG_FT_CFG16_Msk				(0x1UL << EXTI_FT_CFG_FT_CFG16_Pos)
#define EXTI_FT_CFG_FT_CFG16					EXTI_FT_CFG_FT_CFG16_Msk		/*!< Falling trigger event configuration bit of line 16 */
#define EXTI_FT_CFG_FT_CFG17_Pos				(17U)
#define EXTI_FT_CFG_FT_CFG17_Msk				(0x1UL << EXTI_FT_CFG_FT_CFG17_Pos)
#define EXTI_FT_CFG_FT_CFG17					EXTI_FT_CFG_FT_CFG17_Msk		/*!< Falling trigger event configuration bit of line 17 */
#define EXTI_FT_CFG_FT_CFG18_Pos				(18U)
#define EXTI_FT_CFG_FT_CFG18_Msk				(0x1UL << EXTI_FT_CFG_FT_CFG18_Pos)
#define EXTI_FT_CFG_FT_CFG18					EXTI_FT_CFG_FT_CFG18_Msk		/*!< Falling trigger event configuration bit of line 18 */
#define EXTI_FT_CFG_FT_CFG19_Pos				(19U)
#define EXTI_FT_CFG_FT_CFG19_Msk				(0x1UL << EXTI_FT_CFG_FT_CFG19_Pos)
#define EXTI_FT_CFG_FT_CFG19					EXTI_FT_CFG_FT_CFG19_Msk		/*!< Falling trigger event configuration bit of line 19 */
#define EXTI_FT_CFG_FT_CFG20_Pos				(20U)
#define EXTI_FT_CFG_FT_CFG20_Msk				(0x1UL << EXTI_FT_CFG_FT_CFG20_Pos)
#define EXTI_FT_CFG_FT_CFG20					EXTI_FT_CFG_FT_CFG20_Msk		/*!< Falling trigger event configuration bit of line 20 */
#define EXTI_FT_CFG_FT_CFG21_Pos				(21U)
#define EXTI_FT_CFG_FT_CFG21_Msk				(0x1UL << EXTI_FT_CFG_FT_CFG21_Pos)
#define EXTI_FT_CFG_FT_CFG21					EXTI_FT_CFG_FT_CFG21_Msk		/*!< Falling trigger event configuration bit of line 21 */

/******************  Bit definition for EXTI_SWIE register  *******************/
#define EXTI_SWIE_SWIE_ALL  					((uint32_t) 0x003FFFFF)			/*!< Software Interrupt for all lines */
#define EXTI_SWIE_SWIE0_Pos						(0U)
#define EXTI_SWIE_SWIE0_Msk						(0x1UL << EXTI_SWIE_SWIE0_Pos)
#define EXTI_SWIE_SWIE0							EXTI_SWIE_SWIE0_Msk				/*!< Software Interrupt on line 0 */
#define EXTI_SWIE_SWIE1_Pos						(1U)
#define EXTI_SWIE_SWIE1_Msk						(0x1UL << EXTI_SWIE_SWIE1_Pos)
#define EXTI_SWIE_SWIE1							EXTI_SWIE_SWIE1_Msk				/*!< Software Interrupt on line 1 */
#define EXTI_SWIE_SWIE2_Pos						(2U)
#define EXTI_SWIE_SWIE2_Msk						(0x1UL << EXTI_SWIE_SWIE2_Pos)
#define EXTI_SWIE_SWIE2							EXTI_SWIE_SWIE2_Msk				/*!< Software Interrupt on line 2 */
#define EXTI_SWIE_SWIE3_Pos						(3U)
#define EXTI_SWIE_SWIE3_Msk						(0x1UL << EXTI_SWIE_SWIE3_Pos)
#define EXTI_SWIE_SWIE3							EXTI_SWIE_SWIE3_Msk				/*!< Software Interrupt on line 3 */
#define EXTI_SWIE_SWIE4_Pos						(4U)
#define EXTI_SWIE_SWIE4_Msk						(0x1UL << EXTI_SWIE_SWIE4_Pos)
#define EXTI_SWIE_SWIE4							EXTI_SWIE_SWIE4_Msk				/*!< Software Interrupt on line 4 */
#define EXTI_SWIE_SWIE5_Pos						(5U)
#define EXTI_SWIE_SWIE5_Msk						(0x1UL << EXTI_SWIE_SWIE5_Pos)
#define EXTI_SWIE_SWIE5							EXTI_SWIE_SWIE5_Msk				/*!< Software Interrupt on line 5 */
#define EXTI_SWIE_SWIE6_Pos						(6U)
#define EXTI_SWIE_SWIE6_Msk						(0x1UL << EXTI_SWIE_SWIE6_Pos)
#define EXTI_SWIE_SWIE6							EXTI_SWIE_SWIE6_Msk				/*!< Software Interrupt on line 6 */
#define EXTI_SWIE_SWIE7_Pos						(7U)
#define EXTI_SWIE_SWIE7_Msk						(0x1UL << EXTI_SWIE_SWIE7_Pos)
#define EXTI_SWIE_SWIE7							EXTI_SWIE_SWIE7_Msk				/*!< Software Interrupt on line 7 */
#define EXTI_SWIE_SWIE8_Pos						(8U)
#define EXTI_SWIE_SWIE8_Msk						(0x1UL << EXTI_SWIE_SWIE8_Pos)
#define EXTI_SWIE_SWIE8							EXTI_SWIE_SWIE8_Msk				/*!< Software Interrupt on line 8 */
#define EXTI_SWIE_SWIE9_Pos						(9U)
#define EXTI_SWIE_SWIE9_Msk						(0x1UL << EXTI_SWIE_SWIE9_Pos)
#define EXTI_SWIE_SWIE9							EXTI_SWIE_SWIE9_Msk				/*!< Software Interrupt on line 9 */
#define EXTI_SWIE_SWIE10_Pos					(10U)
#define EXTI_SWIE_SWIE10_Msk					(0x1UL << EXTI_SWIE_SWIE10_Pos)
#define EXTI_SWIE_SWIE10						EXTI_SWIE_SWIE10_Msk			/*!< Software Interrupt on line 10 */
#define EXTI_SWIE_SWIE11_Pos					(11U)
#define EXTI_SWIE_SWIE11_Msk					(0x1UL << EXTI_SWIE_SWIE11_Pos)
#define EXTI_SWIE_SWIE11						EXTI_SWIE_SWIE11_Msk			/*!< Software Interrupt on line 11 */
#define EXTI_SWIE_SWIE12_Pos					(12U)
#define EXTI_SWIE_SWIE12_Msk					(0x1UL << EXTI_SWIE_SWIE12_Pos)
#define EXTI_SWIE_SWIE12						EXTI_SWIE_SWIE12_Msk			/*!< Software Interrupt on line 12 */
#define EXTI_SWIE_SWIE13_Pos					(13U)
#define EXTI_SWIE_SWIE13_Msk					(0x1UL << EXTI_SWIE_SWIE13_Pos)
#define EXTI_SWIE_SWIE13						EXTI_SWIE_SWIE13_Msk			/*!< Software Interrupt on line 13 */
#define EXTI_SWIE_SWIE14_Pos					(14U)
#define EXTI_SWIE_SWIE14_Msk					(0x1UL << EXTI_SWIE_SWIE14_Pos)
#define EXTI_SWIE_SWIE14						EXTI_SWIE_SWIE14_Msk			/*!< Software Interrupt on line 14 */
#define EXTI_SWIE_SWIE15_Pos					(15U)
#define EXTI_SWIE_SWIE15_Msk					(0x1UL << EXTI_SWIE_SWIE15_Pos)
#define EXTI_SWIE_SWIE15						EXTI_SWIE_SWIE15_Msk			/*!< Software Interrupt on line 15 */
#define EXTI_SWIE_SWIE16_Pos					(16U)
#define EXTI_SWIE_SWIE16_Msk					(0x1UL << EXTI_SWIE_SWIE16_Pos)
#define EXTI_SWIE_SWIE16						EXTI_SWIE_SWIE16_Msk			/*!< Software Interrupt on line 16 */
#define EXTI_SWIE_SWIE17_Pos					(17U)
#define EXTI_SWIE_SWIE17_Msk					(0x1UL << EXTI_SWIE_SWIE17_Pos)
#define EXTI_SWIE_SWIE17						EXTI_SWIE_SWIE17_Msk			/*!< Software Interrupt on line 17 */
#define EXTI_SWIE_SWIE18_Pos					(18U)
#define EXTI_SWIE_SWIE18_Msk					(0x1UL << EXTI_SWIE_SWIE18_Pos)
#define EXTI_SWIE_SWIE18						EXTI_SWIE_SWIE18_Msk			/*!< Software Interrupt on line 18 */
#define EXTI_SWIE_SWIE19_Pos					(19U)
#define EXTI_SWIE_SWIE19_Msk					(0x1UL << EXTI_SWIE_SWIE19_Pos)
#define EXTI_SWIE_SWIE19						EXTI_SWIE_SWIE19_Msk			/*!< Software Interrupt on line 19 */
#define EXTI_SWIE_SWIE20_Pos					(20U)
#define EXTI_SWIE_SWIE20_Msk					(0x1UL << EXTI_SWIE_SWIE20_Pos)
#define EXTI_SWIE_SWIE20						EXTI_SWIE_SWIE20_Msk			/*!< Software Interrupt on line 20 */
#define EXTI_SWIE_SWIE21_Pos					(21U)
#define EXTI_SWIE_SWIE21_Msk					(0x1UL << EXTI_SWIE_SWIE21_Pos)
#define EXTI_SWIE_SWIE21						EXTI_SWIE_SWIE21_Msk			/*!< Software Interrupt on line 21 */

/******************  Bit definition for EXTI_PEND register  *******************/
#define EXTI_PEND_PEND_ALL  					((uint32_t) 0x003FFFFF)			/*!< Pending for all lines */
#define EXTI_PEND_PEND0_Pos						(0U)
#define EXTI_PEND_PEND0_Msk						(0x1UL << EXTI_PEND_PEND0_Pos)
#define EXTI_PEND_PEND0							EXTI_PEND_PEND0_Msk				/*!< Pending bit for line 0 */
#define EXTI_PEND_PEND1_Pos						(1U)
#define EXTI_PEND_PEND1_Msk						(0x1UL << EXTI_PEND_PEND1_Pos)
#define EXTI_PEND_PEND1							EXTI_PEND_PEND1_Msk				/*!< Pending bit for line 1 */
#define EXTI_PEND_PEND2_Pos						(2U)
#define EXTI_PEND_PEND2_Msk						(0x1UL << EXTI_PEND_PEND2_Pos)
#define EXTI_PEND_PEND2							EXTI_PEND_PEND2_Msk				/*!< Pending bit for line 2 */
#define EXTI_PEND_PEND3_Pos						(3U)
#define EXTI_PEND_PEND3_Msk						(0x1UL << EXTI_PEND_PEND3_Pos)
#define EXTI_PEND_PEND3							EXTI_PEND_PEND3_Msk				/*!< Pending bit for line 3 */
#define EXTI_PEND_PEND4_Pos						(4U)
#define EXTI_PEND_PEND4_Msk						(0x1UL << EXTI_PEND_PEND4_Pos)
#define EXTI_PEND_PEND4							EXTI_PEND_PEND4_Msk				/*!< Pending bit for line 4 */
#define EXTI_PEND_PEND5_Pos						(5U)
#define EXTI_PEND_PEND5_Msk						(0x1UL << EXTI_PEND_PEND5_Pos)
#define EXTI_PEND_PEND5							EXTI_PEND_PEND5_Msk				/*!< Pending bit for line 5 */
#define EXTI_PEND_PEND6_Pos						(6U)
#define EXTI_PEND_PEND6_Msk						(0x1UL << EXTI_PEND_PEND6_Pos)
#define EXTI_PEND_PEND6							EXTI_PEND_PEND6_Msk				/*!< Pending bit for line 6 */
#define EXTI_PEND_PEND7_Pos						(7U)
#define EXTI_PEND_PEND7_Msk						(0x1UL << EXTI_PEND_PEND7_Pos)
#define EXTI_PEND_PEND7							EXTI_PEND_PEND7_Msk				/*!< Pending bit for line 7 */
#define EXTI_PEND_PEND8_Pos						(8U)
#define EXTI_PEND_PEND8_Msk						(0x1UL << EXTI_PEND_PEND8_Pos)
#define EXTI_PEND_PEND8							EXTI_PEND_PEND8_Msk				/*!< Pending bit for line 8 */
#define EXTI_PEND_PEND9_Pos						(9U)
#define EXTI_PEND_PEND9_Msk						(0x1UL << EXTI_PEND_PEND9_Pos)
#define EXTI_PEND_PEND9							EXTI_PEND_PEND9_Msk				/*!< Pending bit for line 9 */
#define EXTI_PEND_PEND10_Pos					(10U)
#define EXTI_PEND_PEND10_Msk					(0x1UL << EXTI_PEND_PEND10_Pos)
#define EXTI_PEND_PEND10						EXTI_PEND_PEND10_Msk			/*!< Pending bit for line 10 */
#define EXTI_PEND_PEND11_Pos					(11U)
#define EXTI_PEND_PEND11_Msk					(0x1UL << EXTI_PEND_PEND11_Pos)
#define EXTI_PEND_PEND11						EXTI_PEND_PEND11_Msk			/*!< Pending bit for line 11 */
#define EXTI_PEND_PEND12_Pos					(12U)
#define EXTI_PEND_PEND12_Msk					(0x1UL << EXTI_PEND_PEND12_Pos)
#define EXTI_PEND_PEND12						EXTI_PEND_PEND12_Msk			/*!< Pending bit for line 12 */
#define EXTI_PEND_PEND13_Pos					(13U)
#define EXTI_PEND_PEND13_Msk					(0x1UL << EXTI_PEND_PEND13_Pos)
#define EXTI_PEND_PEND13						EXTI_PEND_PEND13_Msk			/*!< Pending bit for line 13 */
#define EXTI_PEND_PEND14_Pos					(14U)
#define EXTI_PEND_PEND14_Msk					(0x1UL << EXTI_PEND_PEND14_Pos)
#define EXTI_PEND_PEND14						EXTI_PEND_PEND14_Msk			/*!< Pending bit for line 14 */
#define EXTI_PEND_PEND15_Pos					(15U)
#define EXTI_PEND_PEND15_Msk					(0x1UL << EXTI_PEND_PEND15_Pos)
#define EXTI_PEND_PEND15						EXTI_PEND_PEND15_Msk			/*!< Pending bit for line 15 */
#define EXTI_PEND_PEND16_Pos					(16U)
#define EXTI_PEND_PEND16_Msk					(0x1UL << EXTI_PEND_PEND16_Pos)
#define EXTI_PEND_PEND16						EXTI_PEND_PEND16_Msk			/*!< Pending bit for line 16 */
#define EXTI_PEND_PEND17_Pos					(17U)
#define EXTI_PEND_PEND17_Msk					(0x1UL << EXTI_PEND_PEND17_Pos)
#define EXTI_PEND_PEND17						EXTI_PEND_PEND17_Msk			/*!< Pending bit for line 17 */
#define EXTI_PEND_PEND18_Pos					(18U)
#define EXTI_PEND_PEND18_Msk					(0x1UL << EXTI_PEND_PEND18_Pos)
#define EXTI_PEND_PEND18						EXTI_PEND_PEND18_Msk			/*!< Pending bit for line 18 */
#define EXTI_PEND_PEND19_Pos					(19U)
#define EXTI_PEND_PEND19_Msk					(0x1UL << EXTI_PEND_PEND19_Pos)
#define EXTI_PEND_PEND19						EXTI_PEND_PEND19_Msk			/*!< Pending bit for line 19 */
#define EXTI_PEND_PEND20_Pos					(20U)
#define EXTI_PEND_PEND20_Msk					(0x1UL << EXTI_PEND_PEND20_Pos)
#define EXTI_PEND_PEND20						EXTI_PEND_PEND20_Msk			/*!< Pending bit for line 20 */
#define EXTI_PEND_PEND21_Pos					(21U)
#define EXTI_PEND_PEND21_Msk					(0x1UL << EXTI_PEND_PEND21_Pos)
#define EXTI_PEND_PEND21						EXTI_PEND_PEND21_Msk			/*!< Pending bit for line 21 */

/*****************  Bit definition for EXTI_TS_SEL register  ******************/
#define EXTI_TS_SEL_TSSEL_Pos					(0U)
#define EXTI_TS_SEL_TSSEL_Msk					(0xFUL << EXTI_TS_SEL_TSSEL_Pos)
#define EXTI_TS_SEL_TSSEL						EXTI_TS_SEL_TSSEL_Msk			/*!< TSSEL[3:0] bits */
#define EXTI_TS_SEL_TSSEL_0						((uint32_t) 0x00001)			/*!< Bit 0 */
#define EXTI_TS_SEL_TSSEL_1						((uint32_t) 0x00002)			/*!< Bit 1 */
#define EXTI_TS_SEL_TSSEL_2						((uint32_t) 0x00004)			/*!< Bit 2 */
#define EXTI_TS_SEL_TSSEL_3						((uint32_t) 0x00008)			/*!< Bit 3 */

#define EXTI_TS_SEL_TSSEL_LINE0 				((uint32_t) 0x00000)			/*!< External interrupt line 0 */
#define EXTI_TS_SEL_TSSEL_LINE1 				((uint32_t) 0x00001)			/*!< External interrupt line 1 */
#define EXTI_TS_SEL_TSSEL_LINE2 				((uint32_t) 0x00002)			/*!< External interrupt line 2 */
#define EXTI_TS_SEL_TSSEL_LINE3 				((uint32_t) 0x00003)			/*!< External interrupt line 3 */
#define EXTI_TS_SEL_TSSEL_LINE4 				((uint32_t) 0x00004)			/*!< External interrupt line 4 */
#define EXTI_TS_SEL_TSSEL_LINE5 				((uint32_t) 0x00005)			/*!< External interrupt line 5 */
#define EXTI_TS_SEL_TSSEL_LINE6 				((uint32_t) 0x00006)			/*!< External interrupt line 6 */
#define EXTI_TS_SEL_TSSEL_LINE7 				((uint32_t) 0x00007)			/*!< External interrupt line 7 */
#define EXTI_TS_SEL_TSSEL_LINE8 				((uint32_t) 0x00008)			/*!< External interrupt line 8 */
#define EXTI_TS_SEL_TSSEL_LINE9 				((uint32_t) 0x00009)			/*!< External interrupt line 9 */
#define EXTI_TS_SEL_TSSEL_LINE10				((uint32_t) 0x0000A)			/*!< External interrupt line 10 */
#define EXTI_TS_SEL_TSSEL_LINE11				((uint32_t) 0x0000B)			/*!< External interrupt line 11 */
#define EXTI_TS_SEL_TSSEL_LINE12				((uint32_t) 0x0000C)			/*!< External interrupt line 12 */
#define EXTI_TS_SEL_TSSEL_LINE13				((uint32_t) 0x0000D)			/*!< External interrupt line 13 */
#define EXTI_TS_SEL_TSSEL_LINE14				((uint32_t) 0x0000E)			/*!< External interrupt line 14 */
#define EXTI_TS_SEL_TSSEL_LINE15				((uint32_t) 0x0000F)			/*!< External interrupt line 15 */

/******************************************************************************/
/*                                                                            */
/*                             DMA Controller                                 */
/*                                                                            */
/******************************************************************************/
/******************  Bit definition for DMA_INTSTS register  ******************/
#define DMA_INTSTS_GLBF1_Pos					(0U)
#define DMA_INTSTS_GLBF1_Msk					(0x1UL << DMA_INTSTS_GLBF1_Pos)
#define DMA_INTSTS_GLBF1						DMA_INTSTS_GLBF1_Msk			/*!< Channel 1 Global interrupt flag */
#define DMA_INTSTS_TXCF1_Pos					(1U)
#define DMA_INTSTS_TXCF1_Msk					(0x1UL << DMA_INTSTS_TXCF1_Pos)
#define DMA_INTSTS_TXCF1						DMA_INTSTS_TXCF1_Msk			/*!< Channel 1 Transfer Complete flag */
#define DMA_INTSTS_HTXF1_Pos					(2U)
#define DMA_INTSTS_HTXF1_Msk					(0x1UL << DMA_INTSTS_HTXF1_Pos)
#define DMA_INTSTS_HTXF1						DMA_INTSTS_HTXF1_Msk			/*!< Channel 1 Half Transfer flag */
#define DMA_INTSTS_ERRF1_Pos					(3U)
#define DMA_INTSTS_ERRF1_Msk					(0x1UL << DMA_INTSTS_ERRF1_Pos)
#define DMA_INTSTS_ERRF1						DMA_INTSTS_ERRF1_Msk			/*!< Channel 1 Transfer Error flag */
#define DMA_INTSTS_GLBF2_Pos					(4U)
#define DMA_INTSTS_GLBF2_Msk					(0x1UL << DMA_INTSTS_GLBF2_Pos)
#define DMA_INTSTS_GLBF2						DMA_INTSTS_GLBF2_Msk			/*!< Channel 2 Global interrupt flag */
#define DMA_INTSTS_TXCF2_Pos					(5U)
#define DMA_INTSTS_TXCF2_Msk					(0x1UL << DMA_INTSTS_TXCF2_Pos)
#define DMA_INTSTS_TXCF2						DMA_INTSTS_TXCF2_Msk			/*!< Channel 2 Transfer Complete flag */
#define DMA_INTSTS_HTXF2_Pos					(6U)
#define DMA_INTSTS_HTXF2_Msk					(0x1UL << DMA_INTSTS_HTXF2_Pos)
#define DMA_INTSTS_HTXF2						DMA_INTSTS_HTXF2_Msk			/*!< Channel 2 Half Transfer flag */
#define DMA_INTSTS_ERRF2_Pos					(7U)
#define DMA_INTSTS_ERRF2_Msk					(0x1UL << DMA_INTSTS_ERRF2_Pos)
#define DMA_INTSTS_ERRF2						DMA_INTSTS_ERRF2_Msk			/*!< Channel 2 Transfer Error flag */
#define DMA_INTSTS_GLBF3_Pos					(8U)
#define DMA_INTSTS_GLBF3_Msk					(0x1UL << DMA_INTSTS_GLBF3_Pos)
#define DMA_INTSTS_GLBF3						DMA_INTSTS_GLBF3_Msk			/*!< Channel 3 Global interrupt flag */
#define DMA_INTSTS_TXCF3_Pos					(9U)
#define DMA_INTSTS_TXCF3_Msk					(0x1UL << DMA_INTSTS_TXCF3_Pos)
#define DMA_INTSTS_TXCF3						DMA_INTSTS_TXCF3_Msk			/*!< Channel 3 Transfer Complete flag */
#define DMA_INTSTS_HTXF3_Pos					(10U)
#define DMA_INTSTS_HTXF3_Msk					(0x1UL << DMA_INTSTS_HTXF3_Pos)
#define DMA_INTSTS_HTXF3						DMA_INTSTS_HTXF3_Msk			/*!< Channel 3 Half Transfer flag */
#define DMA_INTSTS_ERRF3_Pos					(11U)
#define DMA_INTSTS_ERRF3_Msk					(0x1UL << DMA_INTSTS_ERRF3_Pos)
#define DMA_INTSTS_ERRF3						DMA_INTSTS_ERRF3_Msk			/*!< Channel 3 Transfer Error flag */
#define DMA_INTSTS_GLBF4_Pos					(12U)
#define DMA_INTSTS_GLBF4_Msk					(0x1UL << DMA_INTSTS_GLBF4_Pos)
#define DMA_INTSTS_GLBF4						DMA_INTSTS_GLBF4_Msk			/*!< Channel 4 Global interrupt flag */
#define DMA_INTSTS_TXCF4_Pos					(13U)
#define DMA_INTSTS_TXCF4_Msk					(0x1UL << DMA_INTSTS_TXCF4_Pos)
#define DMA_INTSTS_TXCF4						DMA_INTSTS_TXCF4_Msk			/*!< Channel 4 Transfer Complete flag */
#define DMA_INTSTS_HTXF4_Pos					(14U)
#define DMA_INTSTS_HTXF4_Msk					(0x1UL << DMA_INTSTS_HTXF4_Pos)
#define DMA_INTSTS_HTXF4						DMA_INTSTS_HTXF4_Msk			/*!< Channel 4 Half Transfer flag */
#define DMA_INTSTS_ERRF4_Pos					(15U)
#define DMA_INTSTS_ERRF4_Msk					(0x1UL << DMA_INTSTS_ERRF4_Pos)
#define DMA_INTSTS_ERRF4						DMA_INTSTS_ERRF4_Msk			/*!< Channel 4 Transfer Error flag */
#define DMA_INTSTS_GLBF5_Pos					(16U)
#define DMA_INTSTS_GLBF5_Msk					(0x1UL << DMA_INTSTS_GLBF5_Pos)
#define DMA_INTSTS_GLBF5						DMA_INTSTS_GLBF5_Msk			/*!< Channel 5 Global interrupt flag */
#define DMA_INTSTS_TXCF5_Pos					(17U)
#define DMA_INTSTS_TXCF5_Msk					(0x1UL << DMA_INTSTS_TXCF5_Pos)
#define DMA_INTSTS_TXCF5						DMA_INTSTS_TXCF5_Msk			/*!< Channel 5 Transfer Complete flag */
#define DMA_INTSTS_HTXF5_Pos					(18U)
#define DMA_INTSTS_HTXF5_Msk					(0x1UL << DMA_INTSTS_HTXF5_Pos)
#define DMA_INTSTS_HTXF5						DMA_INTSTS_HTXF5_Msk			/*!< Channel 5 Half Transfer flag */
#define DMA_INTSTS_ERRF5_Pos					(19U)
#define DMA_INTSTS_ERRF5_Msk					(0x1UL << DMA_INTSTS_ERRF5_Pos)
#define DMA_INTSTS_ERRF5						DMA_INTSTS_ERRF5_Msk			/*!< Channel 5 Transfer Error flag */
#define DMA_INTSTS_GLBF6_Pos					(20U)
#define DMA_INTSTS_GLBF6_Msk					(0x1UL << DMA_INTSTS_GLBF6_Pos)
#define DMA_INTSTS_GLBF6						DMA_INTSTS_GLBF6_Msk			/*!< Channel 6 Global interrupt flag */
#define DMA_INTSTS_TXCF6_Pos					(21U)
#define DMA_INTSTS_TXCF6_Msk					(0x1UL << DMA_INTSTS_TXCF6_Pos)
#define DMA_INTSTS_TXCF6						DMA_INTSTS_TXCF6_Msk			/*!< Channel 6 Transfer Complete flag */
#define DMA_INTSTS_HTXF6_Pos					(22U)
#define DMA_INTSTS_HTXF6_Msk					(0x1UL << DMA_INTSTS_HTXF6_Pos)
#define DMA_INTSTS_HTXF6						DMA_INTSTS_HTXF6_Msk			/*!< Channel 6 Half Transfer flag */
#define DMA_INTSTS_ERRF6_Pos					(23U)
#define DMA_INTSTS_ERRF6_Msk					(0x1UL << DMA_INTSTS_ERRF6_Pos)
#define DMA_INTSTS_ERRF6						DMA_INTSTS_ERRF6_Msk			/*!< Channel 6 Transfer Error flag */
#define DMA_INTSTS_GLBF7_Pos					(24U)
#define DMA_INTSTS_GLBF7_Msk					(0x1UL << DMA_INTSTS_GLBF7_Pos)
#define DMA_INTSTS_GLBF7						DMA_INTSTS_GLBF7_Msk			/*!< Channel 7 Global interrupt flag */
#define DMA_INTSTS_TXCF7_Pos					(25U)
#define DMA_INTSTS_TXCF7_Msk					(0x1UL << DMA_INTSTS_TXCF7_Pos)
#define DMA_INTSTS_TXCF7						DMA_INTSTS_TXCF7_Msk			/*!< Channel 7 Transfer Complete flag */
#define DMA_INTSTS_HTXF7_Pos					(26U)
#define DMA_INTSTS_HTXF7_Msk					(0x1UL << DMA_INTSTS_HTXF7_Pos)
#define DMA_INTSTS_HTXF7						DMA_INTSTS_HTXF7_Msk			/*!< Channel 7 Half Transfer flag */
#define DMA_INTSTS_ERRF7_Pos					(27U)
#define DMA_INTSTS_ERRF7_Msk					(0x1UL << DMA_INTSTS_ERRF7_Pos)
#define DMA_INTSTS_ERRF7						DMA_INTSTS_ERRF7_Msk			/*!< Channel 7 Transfer Error flag */
#define DMA_INTSTS_GLBF8_Pos					(28U)
#define DMA_INTSTS_GLBF8_Msk					(0x1UL << DMA_INTSTS_GLBF8_Pos)
#define DMA_INTSTS_GLBF8						DMA_INTSTS_GLBF8_Msk			/*!< Channel 7 Global interrupt flag */
#define DMA_INTSTS_TXCF8_Pos					(29U)
#define DMA_INTSTS_TXCF8_Msk					(0x1UL << DMA_INTSTS_TXCF8_Pos)
#define DMA_INTSTS_TXCF8						DMA_INTSTS_TXCF8_Msk			/*!< Channel 7 Transfer Complete flag */
#define DMA_INTSTS_HTXF8_Pos					(30U)
#define DMA_INTSTS_HTXF8_Msk					(0x1UL << DMA_INTSTS_HTXF8_Pos)
#define DMA_INTSTS_HTXF8						DMA_INTSTS_HTXF8_Msk			/*!< Channel 7 Half Transfer flag */
#define DMA_INTSTS_ERRF8_Pos					(31U)
#define DMA_INTSTS_ERRF8_Msk					(0x1UL << DMA_INTSTS_ERRF8_Pos)
#define DMA_INTSTS_ERRF8						DMA_INTSTS_ERRF8_Msk			/*!< Channel 7 Transfer Error flag */

/******************  Bit definition for DMA_INTCLR register  ******************/
#define DMA_INTCLR_CGLBF1_Pos					(0U)
#define DMA_INTCLR_CGLBF1_Msk					(0x1UL << DMA_INTCLR_CGLBF1_Pos)
#define DMA_INTCLR_CGLBF1						DMA_INTCLR_CGLBF1_Msk			/*!< Channel 1 Global interrupt clear */
#define DMA_INTCLR_CTXCF1_Pos					(1U)
#define DMA_INTCLR_CTXCF1_Msk					(0x1UL << DMA_INTCLR_CTXCF1_Pos)
#define DMA_INTCLR_CTXCF1						DMA_INTCLR_CTXCF1_Msk			/*!< Channel 1 Transfer Complete clear */
#define DMA_INTCLR_CHTXF1_Pos					(2U)
#define DMA_INTCLR_CHTXF1_Msk					(0x1UL << DMA_INTCLR_CHTXF1_Pos)
#define DMA_INTCLR_CHTXF1						DMA_INTCLR_CHTXF1_Msk			/*!< Channel 1 Half Transfer clear */
#define DMA_INTCLR_CERRF1_Pos					(3U)
#define DMA_INTCLR_CERRF1_Msk					(0x1UL << DMA_INTCLR_CERRF1_Pos)
#define DMA_INTCLR_CERRF1						DMA_INTCLR_CERRF1_Msk			/*!< Channel 1 Transfer Error clear */
#define DMA_INTCLR_CGLBF2_Pos					(4U)
#define DMA_INTCLR_CGLBF2_Msk					(0x1UL << DMA_INTCLR_CGLBF2_Pos)
#define DMA_INTCLR_CGLBF2						DMA_INTCLR_CGLBF2_Msk			/*!< Channel 2 Global interrupt clear */
#define DMA_INTCLR_CTXCF2_Pos					(5U)
#define DMA_INTCLR_CTXCF2_Msk					(0x1UL << DMA_INTCLR_CTXCF2_Pos)
#define DMA_INTCLR_CTXCF2						DMA_INTCLR_CTXCF2_Msk			/*!< Channel 2 Transfer Complete clear */
#define DMA_INTCLR_CHTXF2_Pos					(6U)
#define DMA_INTCLR_CHTXF2_Msk					(0x1UL << DMA_INTCLR_CHTXF2_Pos)
#define DMA_INTCLR_CHTXF2						DMA_INTCLR_CHTXF2_Msk			/*!< Channel 2 Half Transfer clear */
#define DMA_INTCLR_CERRF2_Pos					(7U)
#define DMA_INTCLR_CERRF2_Msk					(0x1UL << DMA_INTCLR_CERRF2_Pos)
#define DMA_INTCLR_CERRF2						DMA_INTCLR_CERRF2_Msk			/*!< Channel 2 Transfer Error clear */
#define DMA_INTCLR_CGLBF3_Pos					(8U)
#define DMA_INTCLR_CGLBF3_Msk					(0x1UL << DMA_INTCLR_CGLBF3_Pos)
#define DMA_INTCLR_CGLBF3						DMA_INTCLR_CGLBF3_Msk			/*!< Channel 3 Global interrupt clear */
#define DMA_INTCLR_CTXCF3_Pos					(9U)
#define DMA_INTCLR_CTXCF3_Msk					(0x1UL << DMA_INTCLR_CTXCF3_Pos)
#define DMA_INTCLR_CTXCF3						DMA_INTCLR_CTXCF3_Msk			/*!< Channel 3 Transfer Complete clear */
#define DMA_INTCLR_CHTXF3_Pos					(10U)
#define DMA_INTCLR_CHTXF3_Msk					(0x1UL << DMA_INTCLR_CHTXF3_Pos)
#define DMA_INTCLR_CHTXF3						DMA_INTCLR_CHTXF3_Msk			/*!< Channel 3 Half Transfer clear */
#define DMA_INTCLR_CERRF3_Pos					(11U)
#define DMA_INTCLR_CERRF3_Msk					(0x1UL << DMA_INTCLR_CERRF3_Pos)
#define DMA_INTCLR_CERRF3						DMA_INTCLR_CERRF3_Msk			/*!< Channel 3 Transfer Error clear */
#define DMA_INTCLR_CGLBF4_Pos					(12U)
#define DMA_INTCLR_CGLBF4_Msk					(0x1UL << DMA_INTCLR_CGLBF4_Pos)
#define DMA_INTCLR_CGLBF4						DMA_INTCLR_CGLBF4_Msk			/*!< Channel 4 Global interrupt clear */
#define DMA_INTCLR_CTXCF4_Pos					(13U)
#define DMA_INTCLR_CTXCF4_Msk					(0x1UL << DMA_INTCLR_CTXCF4_Pos)
#define DMA_INTCLR_CTXCF4						DMA_INTCLR_CTXCF4_Msk			/*!< Channel 4 Transfer Complete clear */
#define DMA_INTCLR_CHTXF4_Pos					(14U)
#define DMA_INTCLR_CHTXF4_Msk					(0x1UL << DMA_INTCLR_CHTXF4_Pos)
#define DMA_INTCLR_CHTXF4						DMA_INTCLR_CHTXF4_Msk			/*!< Channel 4 Half Transfer clear */
#define DMA_INTCLR_CERRF4_Pos					(15U)
#define DMA_INTCLR_CERRF4_Msk					(0x1UL << DMA_INTCLR_CERRF4_Pos)
#define DMA_INTCLR_CERRF4						DMA_INTCLR_CERRF4_Msk			/*!< Channel 4 Transfer Error clear */
#define DMA_INTCLR_CGLBF5_Pos					(16U)
#define DMA_INTCLR_CGLBF5_Msk					(0x1UL << DMA_INTCLR_CGLBF5_Pos)
#define DMA_INTCLR_CGLBF5						DMA_INTCLR_CGLBF5_Msk			/*!< Channel 5 Global interrupt clear */
#define DMA_INTCLR_CTXCF5_Pos					(17U)
#define DMA_INTCLR_CTXCF5_Msk					(0x1UL << DMA_INTCLR_CTXCF5_Pos)
#define DMA_INTCLR_CTXCF5						DMA_INTCLR_CTXCF5_Msk			/*!< Channel 5 Transfer Complete clear */
#define DMA_INTCLR_CHTXF5_Pos					(18U)
#define DMA_INTCLR_CHTXF5_Msk					(0x1UL << DMA_INTCLR_CHTXF5_Pos)
#define DMA_INTCLR_CHTXF5						DMA_INTCLR_CHTXF5_Msk			/*!< Channel 5 Half Transfer clear */
#define DMA_INTCLR_CERRF5_Pos					(19U)
#define DMA_INTCLR_CERRF5_Msk					(0x1UL << DMA_INTCLR_CERRF5_Pos)
#define DMA_INTCLR_CERRF5						DMA_INTCLR_CERRF5_Msk			/*!< Channel 5 Transfer Error clear */
#define DMA_INTCLR_CGLBF6_Pos					(20U)
#define DMA_INTCLR_CGLBF6_Msk					(0x1UL << DMA_INTCLR_CGLBF6_Pos)
#define DMA_INTCLR_CGLBF6						DMA_INTCLR_CGLBF6_Msk			/*!< Channel 6 Global interrupt clear */
#define DMA_INTCLR_CTXCF6_Pos					(21U)
#define DMA_INTCLR_CTXCF6_Msk					(0x1UL << DMA_INTCLR_CTXCF6_Pos)
#define DMA_INTCLR_CTXCF6						DMA_INTCLR_CTXCF6_Msk			/*!< Channel 6 Transfer Complete clear */
#define DMA_INTCLR_CHTXF6_Pos					(22U)
#define DMA_INTCLR_CHTXF6_Msk					(0x1UL << DMA_INTCLR_CHTXF6_Pos)
#define DMA_INTCLR_CHTXF6						DMA_INTCLR_CHTXF6_Msk			/*!< Channel 6 Half Transfer clear */
#define DMA_INTCLR_CERRF6_Pos					(23U)
#define DMA_INTCLR_CERRF6_Msk					(0x1UL << DMA_INTCLR_CERRF6_Pos)
#define DMA_INTCLR_CERRF6						DMA_INTCLR_CERRF6_Msk			/*!< Channel 6 Transfer Error clear */
#define DMA_INTCLR_CGLBF7_Pos					(24U)
#define DMA_INTCLR_CGLBF7_Msk					(0x1UL << DMA_INTCLR_CGLBF7_Pos)
#define DMA_INTCLR_CGLBF7						DMA_INTCLR_CGLBF7_Msk			/*!< Channel 7 Global interrupt clear */
#define DMA_INTCLR_CTXCF7_Pos					(25U)
#define DMA_INTCLR_CTXCF7_Msk					(0x1UL << DMA_INTCLR_CTXCF7_Pos)
#define DMA_INTCLR_CTXCF7						DMA_INTCLR_CTXCF7_Msk			/*!< Channel 7 Transfer Complete clear */
#define DMA_INTCLR_CHTXF7_Pos					(26U)
#define DMA_INTCLR_CHTXF7_Msk					(0x1UL << DMA_INTCLR_CHTXF7_Pos)
#define DMA_INTCLR_CHTXF7						DMA_INTCLR_CHTXF7_Msk			/*!< Channel 7 Half Transfer clear */
#define DMA_INTCLR_CERRF7_Pos					(27U)
#define DMA_INTCLR_CERRF7_Msk					(0x1UL << DMA_INTCLR_CERRF7_Pos)
#define DMA_INTCLR_CERRF7						DMA_INTCLR_CERRF7_Msk			/*!< Channel 7 Transfer Error clear */
#define DMA_INTCLR_CGLBF8_Pos					(28U)
#define DMA_INTCLR_CGLBF8_Msk					(0x1UL << DMA_INTCLR_CGLBF8_Pos)
#define DMA_INTCLR_CGLBF8						DMA_INTCLR_CGLBF8_Msk			/*!< Channel 7 Global interrupt clear */
#define DMA_INTCLR_CTXCF8_Pos					(29U)
#define DMA_INTCLR_CTXCF8_Msk					(0x1UL << DMA_INTCLR_CTXCF8_Pos)
#define DMA_INTCLR_CTXCF8						DMA_INTCLR_CTXCF8_Msk			/*!< Channel 7 Transfer Complete clear */
#define DMA_INTCLR_CHTXF8_Pos					(30U)
#define DMA_INTCLR_CHTXF8_Msk					(0x1UL << DMA_INTCLR_CHTXF8_Pos)
#define DMA_INTCLR_CHTXF8						DMA_INTCLR_CHTXF8_Msk			/*!< Channel 7 Half Transfer clear */
#define DMA_INTCLR_CERRF8_Pos					(31U)
#define DMA_INTCLR_CERRF8_Msk					(0x1UL << DMA_INTCLR_CERRF8_Pos)
#define DMA_INTCLR_CERRF8						DMA_INTCLR_CERRF8_Msk			/*!< Channel 7 Transfer Error clear */

/******************  Bit definition for DMA_CHCFG1 register  ******************/
#define DMA_CHCFG1_CHEN_Pos						(0U)
#define DMA_CHCFG1_CHEN_Msk						(0x1UL << DMA_CHCFG1_CHEN_Pos)		/*!< 0x00000001 */
#define DMA_CHCFG1_CHEN							DMA_CHCFG1_CHEN_Msk				/*!< Channel enable */
#define DMA_CHCFG1_TXCIE_Pos					(1U)
#define DMA_CHCFG1_TXCIE_Msk					(0x1UL << DMA_CHCFG1_TXCIE_Pos)		/*!< 0x00000002 */
#define DMA_CHCFG1_TXCIE						DMA_CHCFG1_TXCIE_Msk			/*!< Transfer complete interrupt enable */
#define DMA_CHCFG1_HTXIE_Pos					(2U)
#define DMA_CHCFG1_HTXIE_Msk					(0x1UL << DMA_CHCFG1_HTXIE_Pos)		/*!< 0x00000004 */
#define DMA_CHCFG1_HTXIE						DMA_CHCFG1_HTXIE_Msk			/*!< Half Transfer interrupt enable */
#define DMA_CHCFG1_ERRIE_Pos					(3U)
#define DMA_CHCFG1_ERRIE_Msk					(0x1UL << DMA_CHCFG1_ERRIE_Pos)		/*!< 0x00000008 */
#define DMA_CHCFG1_ERRIE						DMA_CHCFG1_ERRIE_Msk			/*!< Transfer error interrupt enable */
#define DMA_CHCFG1_DIR_Pos						(4U)
#define DMA_CHCFG1_DIR_Msk						(0x1UL << DMA_CHCFG1_DIR_Pos)		/*!< 0x00000010 */
#define DMA_CHCFG1_DIR							DMA_CHCFG1_DIR_Msk				/*!< Data transfer direction */
#define DMA_CHCFG1_CIRC_Pos						(5U)
#define DMA_CHCFG1_CIRC_Msk						(0x1UL << DMA_CHCFG1_CIRC_Pos)		/*!< 0x00000020 */
#define DMA_CHCFG1_CIRC							DMA_CHCFG1_CIRC_Msk				/*!< Circular mode */
#define DMA_CHCFG1_PINC_Pos						(6U)
#define DMA_CHCFG1_PINC_Msk						(0x1UL << DMA_CHCFG1_PINC_Pos)		/*!< 0x00000040 */
#define DMA_CHCFG1_PINC 						DMA_CHCFG1_PINC_Msk				/*!< Peripheral increment mode */
#define DMA_CHCFG1_MINC_Pos						(7U)
#define DMA_CHCFG1_MINC_Msk						(0x1UL << DMA_CHCFG1_MINC_Pos)		/*!< 0x00000080 */
#define DMA_CHCFG1_MINC							DMA_CHCFG1_MINC_Msk				/*!< Memory increment mode */
#define DMA_CHCFG1_PSIZE_Pos					(8U)
#define DMA_CHCFG1_PSIZE_Msk					(0x3UL << DMA_CHCFG1_PSIZE_Pos)		/*!< 0x00000300 */
#define DMA_CHCFG1_PSIZE						DMA_CHCFG1_PSIZE_Msk			/*!< PSIZE[1:0] bits (Peripheral size) */
#define DMA_CHCFG1_PSIZE_0						((uint16_t) 0x0100)				/*!< Bit 0 */
#define DMA_CHCFG1_PSIZE_1						((uint16_t) 0x0200)				/*!< Bit 1 */
#define DMA_CHCFG1_MSIZE_Pos					(10U)
#define DMA_CHCFG1_MSIZE_Msk					(0x3UL << DMA_CHCFG1_MSIZE_Pos)		/*!< 0x00000C00 */
#define DMA_CHCFG1_MSIZE						DMA_CHCFG1_MSIZE_Msk			/*!< MSIZE[1:0] bits (Memory size) */
#define DMA_CHCFG1_MSIZE_0						((uint16_t) 0x0400)				/*!< Bit 0 */
#define DMA_CHCFG1_MSIZE_1						((uint16_t) 0x0800)				/*!< Bit 1 */
#define DMA_CHCFG1_PRIOLVL_Pos					(12U)
#define DMA_CHCFG1_PRIOLVL_Msk					(0x3UL << DMA_CHCFG1_PRIOLVL_Pos)	/*!< 0x00003000 */
#define DMA_CHCFG1_PRIOLVL						DMA_CHCFG1_PRIOLVL_Msk			/*!< PL[1:0] bits(Channel Priority level) */
#define DMA_CHCFG1_PRIOLVL_0					((uint16_t) 0x1000)				/*!< Bit 0 */
#define DMA_CHCFG1_PRIOLVL_1					((uint16_t) 0x2000)				/*!< Bit 1 */
#define DMA_CHCFG1_MEM2MEM_Pos					(14U)
#define DMA_CHCFG1_MEM2MEM_Msk					(0x1UL << DMA_CHCFG1_MEM2MEM_Pos)	/*!< 0x00004000 */
#define DMA_CHCFG1_MEM2MEM						DMA_CHCFG1_MEM2MEM_Msk			/*!< Memory to memory mode */

/******************  Bit definition for DMA_CHCFG2 register  ******************/
#define DMA_CHCFG2_CHEN_Pos						(0U)
#define DMA_CHCFG2_CHEN_Msk						(0x1UL << DMA_CHCFG2_CHEN_Pos)		/*!< 0x00000001 */
#define DMA_CHCFG2_CHEN							DMA_CHCFG2_CHEN_Msk				/*!< Channel enable */
#define DMA_CHCFG2_TXCIE_Pos					(1U)
#define DMA_CHCFG2_TXCIE_Msk					(0x1UL << DMA_CHCFG2_TXCIE_Pos)		/*!< 0x00000002 */
#define DMA_CHCFG2_TXCIE						DMA_CHCFG2_TXCIE_Msk			/*!< Transfer complete interrupt enable */
#define DMA_CHCFG2_HTXIE_Pos					(2U)
#define DMA_CHCFG2_HTXIE_Msk					(0x1UL << DMA_CHCFG2_HTXIE_Pos)		/*!< 0x00000004 */
#define DMA_CHCFG2_HTXIE						DMA_CHCFG2_HTXIE_Msk			/*!< Half Transfer interrupt enable */
#define DMA_CHCFG2_ERRIE_Pos					(3U)
#define DMA_CHCFG2_ERRIE_Msk					(0x1UL << DMA_CHCFG2_ERRIE_Pos)		/*!< 0x00000008 */
#define DMA_CHCFG2_ERRIE						DMA_CHCFG2_ERRIE_Msk			/*!< Transfer error interrupt enable */
#define DMA_CHCFG2_DIR_Pos						(4U)
#define DMA_CHCFG2_DIR_Msk						(0x1UL << DMA_CHCFG2_DIR_Pos)		/*!< 0x00000010 */
#define DMA_CHCFG2_DIR							DMA_CHCFG2_DIR_Msk				/*!< Data transfer direction */
#define DMA_CHCFG2_CIRC_Pos						(5U)
#define DMA_CHCFG2_CIRC_Msk						(0x1UL << DMA_CHCFG2_CIRC_Pos)		/*!< 0x00000020 */
#define DMA_CHCFG2_CIRC							DMA_CHCFG2_CIRC_Msk				/*!< Circular mode */
#define DMA_CHCFG2_PINC_Pos						(6U)
#define DMA_CHCFG2_PINC_Msk						(0x1UL << DMA_CHCFG2_PINC_Pos)		/*!< 0x00000040 */
#define DMA_CHCFG2_PINC							DMA_CHCFG2_PINC_Msk				/*!< Peripheral increment mode */
#define DMA_CHCFG2_MINC_Pos						(7U)
#define DMA_CHCFG2_MINC_Msk						(0x1UL << DMA_CHCFG2_MINC_Pos)		/*!< 0x00000080 */
#define DMA_CHCFG2_MINC							DMA_CHCFG2_MINC_Msk				/*!< Memory increment mode */
#define DMA_CHCFG2_PSIZE_Pos					(8U)
#define DMA_CHCFG2_PSIZE_Msk					(0x3UL << DMA_CHCFG2_PSIZE_Pos)		/*!< 0x00000300 */
#define DMA_CHCFG2_PSIZE						DMA_CHCFG2_PSIZE_Msk			/*!< PSIZE[1:0] bits (Peripheral size) */
#define DMA_CHCFG2_PSIZE_0						((uint16_t) 0x0100)				/*!< Bit 0 */
#define DMA_CHCFG2_PSIZE_1						((uint16_t) 0x0200)				/*!< Bit 1 */
#define DMA_CHCFG2_MSIZE_Pos					(10U)
#define DMA_CHCFG2_MSIZE_Msk					(0x3UL << DMA_CHCFG2_MSIZE_Pos)		/*!< 0x00000C00 */
#define DMA_CHCFG2_MSIZE						DMA_CHCFG2_MSIZE_Msk			/*!< MSIZE[1:0] bits (Memory size) */
#define DMA_CHCFG2_MSIZE_0						((uint16_t) 0x0400)				/*!< Bit 0 */
#define DMA_CHCFG2_MSIZE_1						((uint16_t) 0x0800)				/*!< Bit 1 */
#define DMA_CHCFG2_PRIOLVL_Pos					(12U)
#define DMA_CHCFG2_PRIOLVL_Msk					(0x3UL << DMA_CHCFG2_PRIOLVL_Pos)	/*!< 0x00003000 */
#define DMA_CHCFG2_PRIOLVL						DMA_CHCFG2_PRIOLVL_Msk			/*!< PL[1:0] bits (Channel Priority level) */
#define DMA_CHCFG2_PRIOLVL_0					((uint16_t) 0x1000)				/*!< Bit 0 */
#define DMA_CHCFG2_PRIOLVL_1					((uint16_t) 0x2000)				/*!< Bit 1 */
#define DMA_CHCFG2_MEM2MEM_Pos					(14U)
#define DMA_CHCFG2_MEM2MEM_Msk					(0x1UL << DMA_CHCFG2_MEM2MEM_Pos)	/*!< 0x00004000 */
#define DMA_CHCFG2_MEM2MEM						DMA_CHCFG2_MEM2MEM_Msk			/*!< Memory to memory mode */

/******************  Bit definition for DMA_CHCFG3 register  ******************/
#define DMA_CHCFG3_CHEN_Pos						(0U)
#define DMA_CHCFG3_CHEN_Msk						(0x1UL << DMA_CHCFG3_CHEN_Pos)		/*!< 0x00000001 */
#define DMA_CHCFG3_CHEN							DMA_CHCFG3_CHEN_Msk				/*!< Channel enable */
#define DMA_CHCFG3_TXCIE_Pos					(1U)
#define DMA_CHCFG3_TXCIE_Msk					(0x1UL << DMA_CHCFG3_TXCIE_Pos)		/*!< 0x00000002 */
#define DMA_CHCFG3_TXCIE						DMA_CHCFG3_TXCIE_Msk			/*!< Transfer complete interrupt enable */
#define DMA_CHCFG3_HTXIE_Pos					(2U)
#define DMA_CHCFG3_HTXIE_Msk					(0x1UL << DMA_CHCFG3_HTXIE_Pos)		/*!< 0x00000004 */
#define DMA_CHCFG3_HTXIE						DMA_CHCFG3_HTXIE_Msk			/*!< Half Transfer interrupt enable */
#define DMA_CHCFG3_ERRIE_Pos					(3U)
#define DMA_CHCFG3_ERRIE_Msk					(0x1UL << DMA_CHCFG3_ERRIE_Pos)		/*!< 0x00000008 */
#define DMA_CHCFG3_ERRIE						DMA_CHCFG3_ERRIE_Msk			/*!< Transfer error interrupt enable */
#define DMA_CHCFG3_DIR_Pos						(4U)
#define DMA_CHCFG3_DIR_Msk						(0x1UL << DMA_CHCFG3_DIR_Pos)		/*!< 0x00000010 */
#define DMA_CHCFG3_DIR							DMA_CHCFG3_DIR_Msk				/*!< Data transfer direction */
#define DMA_CHCFG3_CIRC_Pos						(5U)
#define DMA_CHCFG3_CIRC_Msk						(0x1UL << DMA_CHCFG3_CIRC_Pos)		/*!< 0x00000020 */
#define DMA_CHCFG3_CIRC							DMA_CHCFG3_CIRC_Msk				/*!< Circular mode */
#define DMA_CHCFG3_PINC_Pos						(6U)
#define DMA_CHCFG3_PINC_Msk						(0x1UL << DMA_CHCFG3_PINC_Pos)		/*!< 0x00000040 */
#define DMA_CHCFG3_PINC							DMA_CHCFG3_PINC_Msk				/*!< Peripheral increment mode */
#define DMA_CHCFG3_MINC_Pos						(7U)
#define DMA_CHCFG3_MINC_Msk						(0x1UL << DMA_CHCFG3_MINC_Pos)		/*!< 0x00000080 */
#define DMA_CHCFG3_MINC							DMA_CHCFG3_MINC_Msk				/*!< Memory increment mode */
#define DMA_CHCFG3_PSIZE_Pos					(8U)
#define DMA_CHCFG3_PSIZE_Msk					(0x3UL << DMA_CHCFG3_PSIZE_Pos)		/*!< 0x00000300 */
#define DMA_CHCFG3_PSIZE						DMA_CHCFG3_PSIZE_Msk			/*!< PSIZE[1:0] bits (Peripheral size) */
#define DMA_CHCFG3_PSIZE_0						((uint16_t) 0x0100)				/*!< Bit 0 */
#define DMA_CHCFG3_PSIZE_1						((uint16_t) 0x0200)				/*!< Bit 1 */
#define DMA_CHCFG3_MSIZE_Pos					(10U)
#define DMA_CHCFG3_MSIZE_Msk					(0x3UL << DMA_CHCFG3_MSIZE_Pos)		/*!< 0x00000C00 */
#define DMA_CHCFG3_MSIZE						DMA_CHCFG3_MSIZE_Msk			/*!< MSIZE[1:0] bits (Memory size) */
#define DMA_CHCFG3_MSIZE_0						((uint16_t) 0x0400)				/*!< Bit 0 */
#define DMA_CHCFG3_MSIZE_1						((uint16_t) 0x0800)				/*!< Bit 1 */
#define DMA_CHCFG3_PRIOLVL_Pos					(12U)
#define DMA_CHCFG3_PRIOLVL_Msk					(0x3UL << DMA_CHCFG3_PRIOLVL_Pos)	/*!< 0x00003000 */
#define DMA_CHCFG3_PRIOLVL						DMA_CHCFG3_PRIOLVL_Msk			/*!< PL[1:0] bits (Channel Priority level) */
#define DMA_CHCFG3_PRIOLVL_0					((uint16_t) 0x1000)				/*!< Bit 0 */
#define DMA_CHCFG3_PRIOLVL_1					((uint16_t) 0x2000)				/*!< Bit 1 */
#define DMA_CHCFG3_MEM2MEM_Pos					(14U)
#define DMA_CHCFG3_MEM2MEM_Msk					(0x1UL << DMA_CHCFG3_MEM2MEM_Pos)	/*!< 0x00004000 */
#define DMA_CHCFG3_MEM2MEM						DMA_CHCFG3_MEM2MEM_Msk			/*!< Memory to memory mode */

/******************  Bit definition for DMA_CHCFG4 register  ******************/
#define DMA_CHCFG4_CHEN_Pos						(0U)
#define DMA_CHCFG4_CHEN_Msk						(0x1UL << DMA_CHCFG4_CHEN_Pos)		/*!< 0x00000001 */
#define DMA_CHCFG4_CHEN							DMA_CHCFG4_CHEN_Msk				/*!< Channel enable */
#define DMA_CHCFG4_TXCIE_Pos					(1U)
#define DMA_CHCFG4_TXCIE_Msk					(0x1UL << DMA_CHCFG4_TXCIE_Pos)		/*!< 0x00000002 */
#define DMA_CHCFG4_TXCIE						DMA_CHCFG4_TXCIE_Msk			/*!< Transfer complete interrupt enable */
#define DMA_CHCFG4_HTXIE_Pos					(2U)
#define DMA_CHCFG4_HTXIE_Msk					(0x1UL << DMA_CHCFG4_HTXIE_Pos)		/*!< 0x00000004 */
#define DMA_CHCFG4_HTXIE						DMA_CHCFG4_HTXIE_Msk			/*!< Half Transfer interrupt enable */
#define DMA_CHCFG4_ERRIE_Pos					(3U)
#define DMA_CHCFG4_ERRIE_Msk					(0x1UL << DMA_CHCFG4_ERRIE_Pos)		/*!< 0x00000008 */
#define DMA_CHCFG4_ERRIE						DMA_CHCFG4_ERRIE_Msk			/*!< Transfer error interrupt enable */
#define DMA_CHCFG4_DIR_Pos						(4U)
#define DMA_CHCFG4_DIR_Msk						(0x1UL << DMA_CHCFG4_DIR_Pos)		/*!< 0x00000010 */
#define DMA_CHCFG4_DIR							DMA_CHCFG4_DIR_Msk				/*!< Data transfer direction */
#define DMA_CHCFG4_CIRC_Pos						(5U)
#define DMA_CHCFG4_CIRC_Msk						(0x1UL << DMA_CHCFG4_CIRC_Pos)		/*!< 0x00000020 */
#define DMA_CHCFG4_CIRC							DMA_CHCFG4_CIRC_Msk				/*!< Circular mode */
#define DMA_CHCFG4_PINC_Pos						(6U)
#define DMA_CHCFG4_PINC_Msk						(0x1UL << DMA_CHCFG4_PINC_Pos)		/*!< 0x00000040 */
#define DMA_CHCFG4_PINC							DMA_CHCFG4_PINC_Msk				/*!< Peripheral increment mode */
#define DMA_CHCFG4_MINC_Pos						(7U)
#define DMA_CHCFG4_MINC_Msk						(0x1UL << DMA_CHCFG4_MINC_Pos)		/*!< 0x00000080 */
#define DMA_CHCFG4_MINC							DMA_CHCFG4_MINC_Msk				/*!< Memory increment mode */
#define DMA_CHCFG4_PSIZE_Pos					(8U)
#define DMA_CHCFG4_PSIZE_Msk					(0x3UL << DMA_CHCFG4_PSIZE_Pos)		/*!< 0x00000300 */
#define DMA_CHCFG4_PSIZE						DMA_CHCFG4_PSIZE_Msk			/*!< PSIZE[1:0] bits (Peripheral size) */
#define DMA_CHCFG4_PSIZE_0						((uint16_t) 0x0100)				/*!< Bit 0 */
#define DMA_CHCFG4_PSIZE_1						((uint16_t) 0x0200)				/*!< Bit 1 */
#define DMA_CHCFG4_MSIZE_Pos					(10U)
#define DMA_CHCFG4_MSIZE_Msk					(0x3UL << DMA_CHCFG4_MSIZE_Pos)		/*!< 0x00000C00 */
#define DMA_CHCFG4_MSIZE						DMA_CHCFG4_MSIZE_Msk			/*!< MSIZE[1:0] bits (Memory size) */
#define DMA_CHCFG4_MSIZE_0						((uint16_t) 0x0400)				/*!< Bit 0 */
#define DMA_CHCFG4_MSIZE_1						((uint16_t) 0x0800)				/*!< Bit 1 */
#define DMA_CHCFG4_PRIOLVL_Pos					(12U)
#define DMA_CHCFG4_PRIOLVL_Msk					(0x3UL << DMA_CHCFG4_PRIOLVL_Pos)	/*!< 0x00003000 */
#define DMA_CHCFG4_PRIOLVL						DMA_CHCFG4_PRIOLVL_Msk			/*!< PL[1:0] bits (Channel Priority level) */
#define DMA_CHCFG4_PRIOLVL_0					((uint16_t) 0x1000)				/*!< Bit 0 */
#define DMA_CHCFG4_PRIOLVL_1					((uint16_t) 0x2000)				/*!< Bit 1 */
#define DMA_CHCFG4_MEM2MEM_Pos					(14U)
#define DMA_CHCFG4_MEM2MEM_Msk					(0x1UL << DMA_CHCFG4_MEM2MEM_Pos)	/*!< 0x00004000 */
#define DMA_CHCFG4_MEM2MEM						DMA_CHCFG4_MEM2MEM_Msk			/*!< Memory to memory mode */

/******************  Bit definition for DMA_CHCFG5 register  ******************/
#define DMA_CHCFG5_CHEN_Pos						(0U)
#define DMA_CHCFG5_CHEN_Msk						(0x1UL << DMA_CHCFG5_CHEN_Pos)		/*!< 0x00000001 */
#define DMA_CHCFG5_CHEN							DMA_CHCFG5_CHEN_Msk				/*!< Channel enable */
#define DMA_CHCFG5_TXCIE_Pos					(1U)
#define DMA_CHCFG5_TXCIE_Msk					(0x1UL << DMA_CHCFG5_TXCIE_Pos)		/*!< 0x00000002 */
#define DMA_CHCFG5_TXCIE						DMA_CHCFG5_TXCIE_Msk			/*!< Transfer complete interrupt enable */
#define DMA_CHCFG5_HTXIE_Pos					(2U)
#define DMA_CHCFG5_HTXIE_Msk					(0x1UL << DMA_CHCFG5_HTXIE_Pos)		/*!< 0x00000004 */
#define DMA_CHCFG5_HTXIE						DMA_CHCFG5_HTXIE_Msk			/*!< Half Transfer interrupt enable */
#define DMA_CHCFG5_ERRIE_Pos					(3U)
#define DMA_CHCFG5_ERRIE_Msk					(0x1UL << DMA_CHCFG5_ERRIE_Pos)		/*!< 0x00000008 */
#define DMA_CHCFG5_ERRIE						DMA_CHCFG5_ERRIE_Msk			/*!< Transfer error interrupt enable */
#define DMA_CHCFG5_DIR_Pos						(4U)
#define DMA_CHCFG5_DIR_Msk						(0x1UL << DMA_CHCFG5_DIR_Pos)		/*!< 0x00000010 */
#define DMA_CHCFG5_DIR							DMA_CHCFG5_DIR_Msk				/*!< Data transfer direction */
#define DMA_CHCFG5_CIRC_Pos						(5U)
#define DMA_CHCFG5_CIRC_Msk						(0x1UL << DMA_CHCFG5_CIRC_Pos)		/*!< 0x00000020 */
#define DMA_CHCFG5_CIRC							DMA_CHCFG5_CIRC_Msk				/*!< Circular mode */
#define DMA_CHCFG5_PINC_Pos						(6U)
#define DMA_CHCFG5_PINC_Msk						(0x1UL << DMA_CHCFG5_PINC_Pos)		/*!< 0x00000040 */
#define DMA_CHCFG5_PINC							DMA_CHCFG5_PINC_Msk				/*!< Peripheral increment mode */
#define DMA_CHCFG5_MINC_Pos						(7U)
#define DMA_CHCFG5_MINC_Msk						(0x1UL << DMA_CHCFG5_MINC_Pos)		/*!< 0x00000080 */
#define DMA_CHCFG5_MINC							DMA_CHCFG5_MINC_Msk				/*!< Memory increment mode */
#define DMA_CHCFG5_PSIZE_Pos					(8U)
#define DMA_CHCFG5_PSIZE_Msk					(0x3UL << DMA_CHCFG5_PSIZE_Pos)		/*!< 0x00000300 */
#define DMA_CHCFG5_PSIZE						DMA_CHCFG5_PSIZE_Msk			/*!< PSIZE[1:0] bits (Peripheral size) */
#define DMA_CHCFG5_PSIZE_0						((uint16_t) 0x0100)				/*!< Bit 0 */
#define DMA_CHCFG5_PSIZE_1						((uint16_t) 0x0200)				/*!< Bit 1 */
#define DMA_CHCFG5_MSIZE_Pos					(10U)
#define DMA_CHCFG5_MSIZE_Msk					(0x3UL << DMA_CHCFG5_MSIZE_Pos)		/*!< 0x00000C00 */
#define DMA_CHCFG5_MSIZE						DMA_CHCFG5_MSIZE_Msk			/*!< MSIZE[1:0] bits (Memory size) */
#define DMA_CHCFG5_MSIZE_0						((uint16_t) 0x0400)				/*!< Bit 0 */
#define DMA_CHCFG5_MSIZE_1						((uint16_t) 0x0800)				/*!< Bit 1 */
#define DMA_CHCFG5_PRIOLVL_Pos					(12U)
#define DMA_CHCFG5_PRIOLVL_Msk					(0x3UL << DMA_CHCFG5_PRIOLVL_Pos)	/*!< 0x00003000 */
#define DMA_CHCFG5_PRIOLVL						DMA_CHCFG5_PRIOLVL_Msk			/*!< PL[1:0] bits (Channel Priority level) */
#define DMA_CHCFG5_PRIOLVL_0					((uint16_t) 0x1000)				/*!< Bit 0 */
#define DMA_CHCFG5_PRIOLVL_1					((uint16_t) 0x2000)				/*!< Bit 1 */
#define DMA_CHCFG5_MEM2MEM_Pos					(14U)
#define DMA_CHCFG5_MEM2MEM_Msk					(0x1UL << DMA_CHCFG5_MEM2MEM_Pos)	/*!< 0x00004000 */
#define DMA_CHCFG5_MEM2MEM						DMA_CHCFG5_MEM2MEM_Msk			/*!< Memory to memory mode enable */

/******************  Bit definition for DMA_CHCFG6 register  ******************/
#define DMA_CHCFG6_CHEN_Pos						(0U)
#define DMA_CHCFG6_CHEN_Msk						(0x1UL << DMA_CHCFG6_CHEN_Pos)		/*!< 0x00000001 */
#define DMA_CHCFG6_CHEN							DMA_CHCFG6_CHEN_Msk				/*!< Channel enable */
#define DMA_CHCFG6_TXCIE_Pos					(1U)
#define DMA_CHCFG6_TXCIE_Msk					(0x1UL << DMA_CHCFG6_TXCIE_Pos)		/*!< 0x00000002 */
#define DMA_CHCFG6_TXCIE						DMA_CHCFG6_TXCIE_Msk			/*!< Transfer complete interrupt enable */
#define DMA_CHCFG6_HTXIE_Pos					(2U)
#define DMA_CHCFG6_HTXIE_Msk					(0x1UL << DMA_CHCFG6_HTXIE_Pos)		/*!< 0x00000004 */
#define DMA_CHCFG6_HTXIE						DMA_CHCFG6_HTXIE_Msk			/*!< Half Transfer interrupt enable */
#define DMA_CHCFG6_ERRIE_Pos					(3U)
#define DMA_CHCFG6_ERRIE_Msk					(0x1UL << DMA_CHCFG6_ERRIE_Pos)		/*!< 0x00000008 */
#define DMA_CHCFG6_ERRIE						DMA_CHCFG6_ERRIE_Msk			/*!< Transfer error interrupt enable */
#define DMA_CHCFG6_DIR_Pos						(4U)
#define DMA_CHCFG6_DIR_Msk						(0x1UL << DMA_CHCFG6_DIR_Pos)		/*!< 0x00000010 */
#define DMA_CHCFG6_DIR							DMA_CHCFG6_DIR_Msk				/*!< Data transfer direction */
#define DMA_CHCFG6_CIRC_Pos						(5U)
#define DMA_CHCFG6_CIRC_Msk						(0x1UL << DMA_CHCFG6_CIRC_Pos)		/*!< 0x00000020 */
#define DMA_CHCFG6_CIRC							DMA_CHCFG6_CIRC_Msk				/*!< Circular mode */
#define DMA_CHCFG6_PINC_Pos						(6U)
#define DMA_CHCFG6_PINC_Msk						(0x1UL << DMA_CHCFG6_PINC_Pos)		/*!< 0x00000040 */
#define DMA_CHCFG6_PINC							DMA_CHCFG6_PINC_Msk				/*!< Peripheral increment mode */
#define DMA_CHCFG6_MINC_Pos						(7U)
#define DMA_CHCFG6_MINC_Msk						(0x1UL << DMA_CHCFG6_MINC_Pos)		/*!< 0x00000080 */
#define DMA_CHCFG6_MINC							DMA_CHCFG6_MINC_Msk				/*!< Memory increment mode */
#define DMA_CHCFG6_PSIZE_Pos					(8U)
#define DMA_CHCFG6_PSIZE_Msk					(0x3UL << DMA_CHCFG6_PSIZE_Pos)		/*!< 0x00000300 */
#define DMA_CHCFG6_PSIZE						DMA_CHCFG6_PSIZE_Msk			/*!< PSIZE[1:0] bits (Peripheral size) */
#define DMA_CHCFG6_PSIZE_0						((uint16_t) 0x0100)				/*!< Bit 0 */
#define DMA_CHCFG6_PSIZE_1						((uint16_t) 0x0200)				/*!< Bit 1 */
#define DMA_CHCFG6_MSIZE_Pos					(10U)
#define DMA_CHCFG6_MSIZE_Msk					(0x3UL << DMA_CHCFG6_MSIZE_Pos)		/*!< 0x00000C00 */
#define DMA_CHCFG6_MSIZE						DMA_CHCFG6_MSIZE_Msk			/*!< MSIZE[1:0] bits (Memory size) */
#define DMA_CHCFG6_MSIZE_0						((uint16_t) 0x0400)				/*!< Bit 0 */
#define DMA_CHCFG6_MSIZE_1						((uint16_t) 0x0800)				/*!< Bit 1 */
#define DMA_CHCFG6_PRIOLVL_Pos					(12U)
#define DMA_CHCFG6_PRIOLVL_Msk					(0x3UL << DMA_CHCFG6_PRIOLVL_Pos)	/*!< 0x00003000 */
#define DMA_CHCFG6_PRIOLVL						DMA_CHCFG6_PRIOLVL_Msk			/*!< PL[1:0] bits (Channel Priority level) */
#define DMA_CHCFG6_PRIOLVL_0					((uint16_t) 0x1000)				/*!< Bit 0 */
#define DMA_CHCFG6_PRIOLVL_1					((uint16_t) 0x2000)				/*!< Bit 1 */
#define DMA_CHCFG6_MEM2MEM_Pos					(14U)
#define DMA_CHCFG6_MEM2MEM_Msk					(0x1UL << DMA_CHCFG6_MEM2MEM_Pos)	/*!< 0x00004000 */
#define DMA_CHCFG6_MEM2MEM						DMA_CHCFG6_MEM2MEM_Msk			/*!< Memory to memory mode */

/******************  Bit definition for DMA_CHCFG7 register  ******************/
#define DMA_CHCFG7_CHEN_Pos						(0U)
#define DMA_CHCFG7_CHEN_Msk						(0x1UL << DMA_CHCFG7_CHEN_Pos)		/*!< 0x00000001 */
#define DMA_CHCFG7_CHEN							DMA_CHCFG7_CHEN_Msk				/*!< Channel enable */
#define DMA_CHCFG7_TXCIE_Pos					(1U)
#define DMA_CHCFG7_TXCIE_Msk					(0x1UL << DMA_CHCFG7_TXCIE_Pos)		/*!< 0x00000002 */
#define DMA_CHCFG7_TXCIE						DMA_CHCFG7_TXCIE_Msk			/*!< Transfer complete interrupt enable */
#define DMA_CHCFG7_HTXIE_Pos					(2U)
#define DMA_CHCFG7_HTXIE_Msk					(0x1UL << DMA_CHCFG7_HTXIE_Pos)		/*!< 0x00000004 */
#define DMA_CHCFG7_HTXIE						DMA_CHCFG7_HTXIE_Msk			/*!< Half Transfer interrupt enable */
#define DMA_CHCFG7_ERRIE_Pos					(3U)
#define DMA_CHCFG7_ERRIE_Msk					(0x1UL << DMA_CHCFG7_ERRIE_Pos)		/*!< 0x00000008 */
#define DMA_CHCFG7_ERRIE						DMA_CHCFG7_ERRIE_Msk			/*!< Transfer error interrupt enable */
#define DMA_CHCFG7_DIR_Pos						(4U)
#define DMA_CHCFG7_DIR_Msk						(0x1UL << DMA_CHCFG7_DIR_Pos)		/*!< 0x00000010 */
#define DMA_CHCFG7_DIR							DMA_CHCFG7_DIR_Msk				/*!< Data transfer direction */
#define DMA_CHCFG7_CIRC_Pos						(5U)
#define DMA_CHCFG7_CIRC_Msk						(0x1UL << DMA_CHCFG7_CIRC_Pos)		/*!< 0x00000020 */
#define DMA_CHCFG7_CIRC							DMA_CHCFG7_CIRC_Msk				/*!< Circular mode */
#define DMA_CHCFG7_PINC_Pos						(6U)
#define DMA_CHCFG7_PINC_Msk						(0x1UL << DMA_CHCFG7_PINC_Pos)		/*!< 0x00000040 */
#define DMA_CHCFG7_PINC							DMA_CHCFG7_PINC_Msk				/*!< Peripheral increment mode */
#define DMA_CHCFG7_MINC_Pos						(7U)
#define DMA_CHCFG7_MINC_Msk						(0x1UL << DMA_CHCFG7_MINC_Pos)		/*!< 0x00000080 */
#define DMA_CHCFG7_MINC							DMA_CHCFG7_MINC_Msk				/*!< Memory increment mode */
#define DMA_CHCFG7_PSIZE_Pos					(8U)
#define DMA_CHCFG7_PSIZE_Msk					(0x3UL << DMA_CHCFG7_PSIZE_Pos)		/*!< 0x00000300 */
#define DMA_CHCFG7_PSIZE						DMA_CHCFG7_PSIZE_Msk			/*!< PSIZE[1:0] bits (Peripheral size) */
#define DMA_CHCFG7_PSIZE_0						((uint16_t) 0x0100)				/*!< Bit 0 */
#define DMA_CHCFG7_PSIZE_1						((uint16_t) 0x0200)				/*!< Bit 1 */
#define DMA_CHCFG7_MSIZE_Pos					(10U)
#define DMA_CHCFG7_MSIZE_Msk					(0x3UL << DMA_CHCFG7_MSIZE_Pos)		/*!< 0x00000C00 */
#define DMA_CHCFG7_MSIZE						DMA_CHCFG7_MSIZE_Msk			/*!< MSIZE[1:0] bits (Memory size) */
#define DMA_CHCFG7_MSIZE_0						((uint16_t) 0x0400)				/*!< Bit 0 */
#define DMA_CHCFG7_MSIZE_1						((uint16_t) 0x0800)				/*!< Bit 1 */
#define DMA_CHCFG7_PRIOLVL_Pos					(12U)
#define DMA_CHCFG7_PRIOLVL_Msk					(0x3UL << DMA_CHCFG7_PRIOLVL_Pos)	/*!< 0x00003000 */
#define DMA_CHCFG7_PRIOLVL						DMA_CHCFG7_PRIOLVL_Msk			/*!< PL[1:0] bits (Channel Priority level) */
#define DMA_CHCFG7_PRIOLVL_0					((uint16_t) 0x1000)				/*!< Bit 0 */
#define DMA_CHCFG7_PRIOLVL_1					((uint16_t) 0x2000)				/*!< Bit 1 */
#define DMA_CHCFG7_MEM2MEM_Pos					(14U)
#define DMA_CHCFG7_MEM2MEM_Msk					(0x1UL << DMA_CHCFG7_MEM2MEM_Pos)	/*!< 0x00004000 */
#define DMA_CHCFG7_MEM2MEM						DMA_CHCFG7_MEM2MEM_Msk			/*!< Memory to memory mode enable */

/******************  Bit definition for DMA_CHCFG8 register  ******************/
#define DMA_CHCFG8_CHEN_Pos						(0U)
#define DMA_CHCFG8_CHEN_Msk						(0x1UL << DMA_CHCFG8_CHEN_Pos)		/*!< 0x00000001 */
#define DMA_CHCFG8_CHEN							DMA_CHCFG8_CHEN_Msk				/*!< Channel enable */
#define DMA_CHCFG8_TXCIE_Pos					(1U)
#define DMA_CHCFG8_TXCIE_Msk					(0x1UL << DMA_CHCFG8_TXCIE_Pos)		/*!< 0x00000002 */
#define DMA_CHCFG8_TXCIE						DMA_CHCFG8_TXCIE_Msk			/*!< Transfer complete interrupt enable */
#define DMA_CHCFG8_HTXIE_Pos					(2U)
#define DMA_CHCFG8_HTXIE_Msk					(0x1UL << DMA_CHCFG8_HTXIE_Pos)		/*!< 0x00000004 */
#define DMA_CHCFG8_HTXIE						DMA_CHCFG8_HTXIE_Msk			/*!< Half Transfer interrupt enable */
#define DMA_CHCFG8_ERRIE_Pos					(3U)
#define DMA_CHCFG8_ERRIE_Msk					(0x1UL << DMA_CHCFG8_ERRIE_Pos)		/*!< 0x00000008 */
#define DMA_CHCFG8_ERRIE						DMA_CHCFG8_ERRIE_Msk			/*!< Transfer error interrupt enable */
#define DMA_CHCFG8_DIR_Pos						(4U)
#define DMA_CHCFG8_DIR_Msk						(0x1UL << DMA_CHCFG8_DIR_Pos)		/*!< 0x00000010 */
#define DMA_CHCFG8_DIR							DMA_CHCFG8_DIR_Msk				/*!< Data transfer direction */
#define DMA_CHCFG8_CIRC_Pos						(5U)
#define DMA_CHCFG8_CIRC_Msk						(0x1UL << DMA_CHCFG8_CIRC_Pos)		/*!< 0x00000020 */
#define DMA_CHCFG8_CIRC							DMA_CHCFG8_CIRC_Msk				/*!< Circular mode */
#define DMA_CHCFG8_PINC_Pos						(6U)
#define DMA_CHCFG8_PINC_Msk						(0x1UL << DMA_CHCFG8_PINC_Pos)		/*!< 0x00000040 */
#define DMA_CHCFG8_PINC							DMA_CHCFG8_PINC_Msk				/*!< Peripheral increment mode */
#define DMA_CHCFG8_MINC_Pos						(7U)
#define DMA_CHCFG8_MINC_Msk						(0x1UL << DMA_CHCFG8_MINC_Pos)		/*!< 0x00000080 */
#define DMA_CHCFG8_MINC							DMA_CHCFG8_MINC_Msk				/*!< Memory increment mode */
#define DMA_CHCFG8_PSIZE_Pos					(8U)
#define DMA_CHCFG8_PSIZE_Msk					(0x3UL << DMA_CHCFG8_PSIZE_Pos)		/*!< 0x00000300 */
#define DMA_CHCFG8_PSIZE						DMA_CHCFG8_PSIZE_Msk			/*!< PSIZE[1:0] bits (Peripheral size) */
#define DMA_CHCFG8_PSIZE_0						((uint16_t) 0x0100)				/*!< Bit 0 */
#define DMA_CHCFG8_PSIZE_1						((uint16_t) 0x0200)				/*!< Bit 1 */
#define DMA_CHCFG8_MSIZE_Pos					(10U)
#define DMA_CHCFG8_MSIZE_Msk					(0x3UL << DMA_CHCFG8_MSIZE_Pos)		/*!< 0x00000C00 */
#define DMA_CHCFG8_MSIZE						DMA_CHCFG8_MSIZE_Msk			/*!< MSIZE[1:0] bits (Memory size) */
#define DMA_CHCFG8_MSIZE_0						((uint16_t) 0x0400)				/*!< Bit 0 */
#define DMA_CHCFG8_MSIZE_1						((uint16_t) 0x0800)				/*!< Bit 1 */
#define DMA_CHCFG8_PRIOLVL_Pos					(12U)
#define DMA_CHCFG8_PRIOLVL_Msk					(0x3UL << DMA_CHCFG8_PRIOLVL_Pos)	/*!< 0x00003000 */
#define DMA_CHCFG8_PRIOLVL						DMA_CHCFG8_PRIOLVL_Msk			/*!< PL[1:0] bits (Channel Priority level) */
#define DMA_CHCFG8_PRIOLVL_0					((uint16_t) 0x1000)				/*!< Bit 0 */
#define DMA_CHCFG8_PRIOLVL_1					((uint16_t) 0x2000)				/*!< Bit 1 */
#define DMA_CHCFG8_MEM2MEM_Pos					(14U)
#define DMA_CHCFG8_MEM2MEM_Msk					(0x1UL << DMA_CHCFG8_MEM2MEM_Pos)	/*!< 0x00004000 */
#define DMA_CHCFG8_MEM2MEM						DMA_CHCFG8_MEM2MEM_Msk			/*!< Memory to memory mode enable */

/******************  Bit definition for DMA_TXNUM1 register  ******************/
#define DMA_TXNUM1_NDTX_Pos						(0U)
#define DMA_TXNUM1_NDTX_Msk						(0xFFFFUL << DMA_TXNUM1_NDTX_Pos)	/*!< 0x0000FFFF */
#define DMA_TXNUM1_NDTX							DMA_TXNUM1_NDTX_Msk				/*!< Number of data to Transfer */

/******************  Bit definition for DMA_TXNUM2 register  ******************/
#define DMA_TXNUM2_NDTX_Pos						(0U)
#define DMA_TXNUM2_NDTX_Msk						(0xFFFFUL << DMA_TXNUM2_NDTX_Pos)	/*!< 0x0000FFFF */
#define DMA_TXNUM2_NDTX							DMA_TXNUM2_NDTX_Msk				/*!< Number of data to Transfer */

/******************  Bit definition for DMA_TXNUM3 register  ******************/
#define DMA_TXNUM3_NDTX_Pos						(0U)
#define DMA_TXNUM3_NDTX_Msk						(0xFFFFUL << DMA_TXNUM3_NDTX_Pos)	/*!< 0x0000FFFF */
#define DMA_TXNUM3_NDTX							DMA_TXNUM3_NDTX_Msk				/*!< Number of data to Transfer */

/******************  Bit definition for DMA_TXNUM4 register  ******************/
#define DMA_TXNUM4_NDTX_Pos						(0U)
#define DMA_TXNUM4_NDTX_Msk						(0xFFFFUL << DMA_TXNUM4_NDTX_Pos)	/*!< 0x0000FFFF */
#define DMA_TXNUM4_NDTX							DMA_TXNUM4_NDTX_Msk				/*!< Number of data to Transfer */

/******************  Bit definition for DMA_TXNUM5 register  ******************/
#define DMA_TXNUM5_NDTX_Pos						(0U)
#define DMA_TXNUM5_NDTX_Msk						(0xFFFFUL << DMA_TXNUM5_NDTX_Pos)	/*!< 0x0000FFFF */
#define DMA_TXNUM5_NDTX							DMA_TXNUM5_NDTX_Msk				/*!< Number of data to Transfer */

/******************  Bit definition for DMA_TXNUM6 register  ******************/
#define DMA_TXNUM6_NDTX_Pos						(0U)
#define DMA_TXNUM6_NDTX_Msk						(0xFFFFUL << DMA_TXNUM6_NDTX_Pos)	/*!< 0x0000FFFF */
#define DMA_TXNUM6_NDTX							DMA_TXNUM6_NDTX_Msk				/*!< Number of data to Transfer */

/******************  Bit definition for DMA_TXNUM7 register  ******************/
#define DMA_TXNUM7_NDTX_Pos						(0U)
#define DMA_TXNUM7_NDTX_Msk						(0xFFFFUL << DMA_TXNUM7_NDTX_Pos)	/*!< 0x0000FFFF */
#define DMA_TXNUM7_NDTX							DMA_TXNUM7_NDTX_Msk				/*!< Number of data to Transfer */

/******************  Bit definition for DMA_TXNUM8 register  ******************/
#define DMA_TXNUM8_NDTX_Pos						(0U)
#define DMA_TXNUM8_NDTX_Msk						(0xFFFFUL << DMA_TXNUM8_NDTX_Pos)	/*!< 0x0000FFFF */
#define DMA_TXNUM8_NDTX							DMA_TXNUM8_NDTX_Msk				/*!< Number of data to Transfer */

/******************  Bit definition for DMA_PADDR1 register  ******************/
#define DMA_PADDR1_ADDR_Pos						(0U)
#define DMA_PADDR1_ADDR_Msk						(0xFFFFFFFFUL << DMA_PADDR1_ADDR_Pos)	/*!< 0xFFFFFFFF */
#define DMA_PADDR1_ADDR							DMA_PADDR1_ADDR_Msk				/*!< Peripheral Address */

/******************  Bit definition for DMA_PADDR2 register  ******************/
#define DMA_PADDR2_ADDR_Pos						(0U)
#define DMA_PADDR2_ADDR_Msk						(0xFFFFFFFFUL << DMA_PADDR2_ADDR_Pos)	/*!< 0xFFFFFFFF */
#define DMA_PADDR2_ADDR							DMA_PADDR2_ADDR_Msk				/*!< Peripheral Address */

/******************  Bit definition for DMA_PADDR3 register  ******************/
#define DMA_PADDR3_ADDR_Pos						(0U)
#define DMA_PADDR3_ADDR_Msk						(0xFFFFFFFFUL << DMA_PADDR3_ADDR_Pos)	/*!< 0xFFFFFFFF */
#define DMA_PADDR3_ADDR							DMA_PADDR3_ADDR_Msk				/*!< Peripheral Address */

/******************  Bit definition for DMA_PADDR4 register  ******************/
#define DMA_PADDR4_ADDR_Pos						(0U)
#define DMA_PADDR4_ADDR_Msk						(0xFFFFFFFFUL << DMA_PADDR4_ADDR_Pos)	/*!< 0xFFFFFFFF */
#define DMA_PADDR4_ADDR							DMA_PADDR4_ADDR_Msk				/*!< Peripheral Address */

/******************  Bit definition for DMA_PADDR5 register  ******************/
#define DMA_PADDR5_ADDR_Pos						(0U)
#define DMA_PADDR5_ADDR_Msk						(0xFFFFFFFFUL << DMA_PADDR5_ADDR_Pos)	/*!< 0xFFFFFFFF */
#define DMA_PADDR5_ADDR							DMA_PADDR5_ADDR_Msk				/*!< Peripheral Address */

/******************  Bit definition for DMA_PADDR6 register  ******************/
#define DMA_PADDR6_ADDR_Pos						(0U)
#define DMA_PADDR6_ADDR_Msk						(0xFFFFFFFFUL << DMA_PADDR6_ADDR_Pos)	/*!< 0xFFFFFFFF */
#define DMA_PADDR6_ADDR							DMA_PADDR6_ADDR_Msk				/*!< Peripheral Address */

/******************  Bit definition for DMA_PADDR7 register  ******************/
#define DMA_PADDR7_ADDR_Pos						(0U)
#define DMA_PADDR7_ADDR_Msk						(0xFFFFFFFFUL << DMA_PADDR7_ADDR_Pos)	/*!< 0xFFFFFFFF */
#define DMA_PADDR7_ADDR							DMA_PADDR7_ADDR_Msk				/*!< Peripheral Address */

/******************  Bit definition for DMA_PADDR8 register  ******************/
#define DMA_PADDR8_ADDR_Pos						(0U)
#define DMA_PADDR8_ADDR_Msk						(0xFFFFFFFFUL << DMA_PADDR8_ADDR_Pos)	/*!< 0xFFFFFFFF */
#define DMA_PADDR8_ADDR							DMA_PADDR8_ADDR_Msk				/*!< Peripheral Address */

/******************  Bit definition for DMA_MADDR1 register  ******************/
#define DMA_MADDR1_ADDR_Pos						(0U)
#define DMA_MADDR1_ADDR_Msk						(0xFFFFFFFFUL << DMA_MADDR1_ADDR_Pos)	/*!< 0xFFFFFFFF */
#define DMA_MADDR1_ADDR							DMA_MADDR1_ADDR_Msk				/*!< Memory Address */

/******************  Bit definition for DMA_MADDR2 register  ******************/
#define DMA_MADDR2_ADDR_Pos						(0U)
#define DMA_MADDR2_ADDR_Msk						(0xFFFFFFFFUL << DMA_MADDR2_ADDR_Pos)	/*!< 0xFFFFFFFF */
#define DMA_MADDR2_ADDR							DMA_MADDR2_ADDR_Msk				/*!< Memory Address */

/******************  Bit definition for DMA_MADDR3 register  ******************/
#define DMA_MADDR3_ADDR_Pos						(0U)
#define DMA_MADDR3_ADDR_Msk						(0xFFFFFFFFUL << DMA_MADDR3_ADDR_Pos)	/*!< 0xFFFFFFFF */
#define DMA_MADDR3_ADDR							DMA_MADDR3_ADDR_Msk				/*!< Memory Address */

/******************  Bit definition for DMA_MADDR4 register  ******************/
#define DMA_MADDR4_ADDR_Pos						(0U)
#define DMA_MADDR4_ADDR_Msk						(0xFFFFFFFFUL << DMA_MADDR4_ADDR_Pos)	/*!< 0xFFFFFFFF */
#define DMA_MADDR4_ADDR							DMA_MADDR4_ADDR_Msk				/*!< Memory Address */

/******************  Bit definition for DMA_MADDR5 register  ******************/
#define DMA_MADDR5_ADDR_Pos						(0U)
#define DMA_MADDR5_ADDR_Msk						(0xFFFFFFFFUL << DMA_MADDR5_ADDR_Pos)	/*!< 0xFFFFFFFF */
#define DMA_MADDR5_ADDR							DMA_MADDR5_ADDR_Msk				/*!< Memory Address */

/******************  Bit definition for DMA_MADDR6 register  ******************/
#define DMA_MADDR6_ADDR_Pos						(0U)
#define DMA_MADDR6_ADDR_Msk						(0xFFFFFFFFUL << DMA_MADDR6_ADDR_Pos)	/*!< 0xFFFFFFFF */
#define DMA_MADDR6_ADDR							DMA_MADDR6_ADDR_Msk				/*!< Memory Address */

/******************  Bit definition for DMA_MADDR7 register  ******************/
#define DMA_MADDR7_ADDR_Pos						(0U)
#define DMA_MADDR7_ADDR_Msk						(0xFFFFFFFFUL << DMA_MADDR7_ADDR_Pos)	/*!< 0xFFFFFFFF */
#define DMA_MADDR7_ADDR							DMA_MADDR7_ADDR_Msk				/*!< Memory Address */

/******************  Bit definition for DMA_MADDR8 register  ******************/
#define DMA_MADDR8_ADDR_Pos						(0U)
#define DMA_MADDR8_ADDR_Msk						(0xFFFFFFFFUL << DMA_MADDR8_ADDR_Pos)	/*!< 0xFFFFFFFF */
#define DMA_MADDR8_ADDR							DMA_MADDR8_ADDR_Msk				/*!< Memory Address */

/******************  Bit definition for DMA_CHSEL1 register  ******************/
#define DMA_CHSEL1_CH_SEL_Pos					(0U)
#define DMA_CHSEL1_CH_SEL_Msk					(0x3FUL << DMA_CHSEL1_CH_SEL_Pos)	/*!< 0x0000003F */
#define DMA_CHSEL1_CH_SEL 						DMA_CHSEL1_CH_SEL_Msk			/*!< Channel Select */

/******************  Bit definition for DMA_CHSEL2 register  ******************/
#define DMA_CHSEL2_CH_SEL_Pos					(0U)
#define DMA_CHSEL2_CH_SEL_Msk					(0x3FUL << DMA_CHSEL2_CH_SEL_Pos)	/*!< 0x0000003F */
#define DMA_CHSEL2_CH_SEL 						DMA_CHSEL2_CH_SEL_Msk			/*!< Channel Select */

/******************  Bit definition for DMA_CHSEL3 register  ******************/
#define DMA_CHSEL3_CH_SEL_Pos					(0U)
#define DMA_CHSEL3_CH_SEL_Msk					(0x3FUL << DMA_CHSEL3_CH_SEL_Pos)	/*!< 0x0000003F */
#define DMA_CHSEL3_CH_SEL 						DMA_CHSEL3_CH_SEL_Msk			/*!< Channel Select */

/******************  Bit definition for DMA_CHSEL4 register  ******************/
#define DMA_CHSEL4_CH_SEL_Pos					(0U)
#define DMA_CHSEL4_CH_SEL_Msk					(0x3FUL << DMA_CHSEL4_CH_SEL_Pos)	/*!< 0x0000003F */
#define DMA_CHSEL4_CH_SEL 						DMA_CHSEL4_CH_SEL_Msk			/*!< Channel Select */

/******************  Bit definition for DMA_CHSEL5 register  ******************/
#define DMA_CHSEL5_CH_SEL_Pos					(0U)
#define DMA_CHSEL5_CH_SEL_Msk					(0x3FUL << DMA_CHSEL5_CH_SEL_Pos)	/*!< 0x0000003F */
#define DMA_CHSEL5_CH_SEL 						DMA_CHSEL5_CH_SEL_Msk			/*!< Channel Select */

/******************  Bit definition for DMA_CHSEL6 register  ******************/
#define DMA_CHSEL6_CH_SEL_Pos					(0U)
#define DMA_CHSEL6_CH_SEL_Msk					(0x3FUL << DMA_CHSEL6_CH_SEL_Pos)	/*!< 0x0000003F */
#define DMA_CHSEL6_CH_SEL 						DMA_CHSEL6_CH_SEL_Msk			/*!< Channel Select */

/******************  Bit definition for DMA_CHSEL7 register  ******************/
#define DMA_CHSEL7_CH_SEL_Pos					(0U)
#define DMA_CHSEL7_CH_SEL_Msk					(0x3FUL << DMA_CHSEL7_CH_SEL_Pos)	/*!< 0x0000003F */
#define DMA_CHSEL7_CH_SEL 						DMA_CHSEL7_CH_SEL_Msk			/*!< Channel Select */

/******************  Bit definition for DMA_CHSEL8 register  ******************/
#define DMA_CHSEL8_CH_SEL_Pos					(0U)
#define DMA_CHSEL8_CH_SEL_Msk					(0x3FUL << DMA_CHSEL8_CH_SEL_Pos)	/*!< 0x0000003F */
#define DMA_CHSEL8_CH_SEL 						DMA_CHSEL8_CH_SEL_Msk			/*!< Channel Select */

/*****************  Bit definition for DMA_CHMAPEN register  ******************/
#define DMA_CHMAPEN_MAP_EN_Pos					(0U)
#define DMA_CHMAPEN_MAP_EN_Msk					(0x1UL << DMA_CHMAPEN_MAP_EN_Pos)	/*!< 0x00000001 */
#define DMA_CHMAPEN_MAP_EN						DMA_CHMAPEN_MAP_EN_Msk			/*!< Channel Map Enable */

/******************************************************************************/
/*                                                                            */
/*                        Analog to Digital Converter                         */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for ADC_STS register  ********************/
#define ADC_STS_AWDG_Pos						(0U)
#define ADC_STS_AWDG_Msk						(0x1UL << ADC_STS_AWDG_Pos)
#define ADC_STS_AWDG							ADC_STS_AWDG_Msk				/*!< Analog watchdog flag */
#define ADC_STS_ENDC_Pos						(1U)
#define ADC_STS_ENDC_Msk						(0x1UL << ADC_STS_ENDC_Pos)
#define ADC_STS_ENDC							ADC_STS_ENDC_Msk				/*!< End of conversion */
#define ADC_STS_JENDC_Pos						(2U)
#define ADC_STS_JENDC_Msk						(0x1UL << ADC_STS_JENDC_Pos)
#define ADC_STS_JENDC							ADC_STS_JENDC_Msk				/*!< Injected channel end of conversion */
#define ADC_STS_JSTR_Pos						(3U)
#define ADC_STS_JSTR_Msk						(0x1UL << ADC_STS_JSTR_Pos)
#define ADC_STS_JSTR							ADC_STS_JSTR_Msk				/*!< Injected channel Start flag */
#define ADC_STS_STR_Pos							(4U)
#define ADC_STS_STR_Msk							(0x1UL << ADC_STS_STR_Pos)
#define ADC_STS_STR								ADC_STS_STR_Msk					/*!< Regular channel Start flag */
#define ADC_STS_ENDCA_Pos						(5U)
#define ADC_STS_ENDCA_Msk						(0x1UL << ADC_STS_ENDCA_Pos)
#define ADC_STS_ENDCA							ADC_STS_ENDCA_Msk				/*!< Any end of conversion */
#define ADC_STS_JENDCA_Pos						(6U)
#define ADC_STS_JENDCA_Msk						(0x1UL << ADC_STS_JENDCA_Pos)
#define ADC_STS_JENDCA							ADC_STS_JENDCA_Msk				/*!< Any injected channel end of conversion */

/******************  Bit definition for ADC_CTRL1 register  *******************/
#define ADC_CTRL1_AWDGCH_Pos					(0U)
#define ADC_CTRL1_AWDGCH_Msk					(0x1FUL << ADC_CTRL1_AWDGCH_Pos)
#define ADC_CTRL1_AWDGCH						ADC_CTRL1_AWDGCH_Msk			/*!< AWDG_CH[4:0] bits (Analog watchdog channel select bits) */
#define ADC_CTRL1_AWDGCH_0						((uint32_t) 0x00000001)			/*!< Bit 0 */
#define ADC_CTRL1_AWDGCH_1						((uint32_t) 0x00000002)			/*!< Bit 1 */
#define ADC_CTRL1_AWDGCH_2						((uint32_t) 0x00000004)			/*!< Bit 2 */
#define ADC_CTRL1_AWDGCH_3						((uint32_t) 0x00000008)			/*!< Bit 3 */
#define ADC_CTRL1_AWDGCH_4						((uint32_t) 0x00000010)			/*!< Bit 4 */
#define ADC_CTRL1_ENDCIEN_Pos					(5U)
#define ADC_CTRL1_ENDCIEN_Msk					(0x1UL << ADC_CTRL1_ENDCIEN_Pos)
#define ADC_CTRL1_ENDCIEN						ADC_CTRL1_ENDCIEN_Msk			/*!< Interrupt enable for EOC */
#define ADC_CTRL1_AWDGIEN_Pos					(6U)
#define ADC_CTRL1_AWDGIEN_Msk					(0x1UL << ADC_CTRL1_AWDGIEN_Pos)
#define ADC_CTRL1_AWDGIEN						ADC_CTRL1_AWDGIEN_Msk			/*!< Analog Watchdog interrupt enable */
#define ADC_CTRL1_JENDCIEN_Pos					(7U)
#define ADC_CTRL1_JENDCIEN_Msk					(0x1UL << ADC_CTRL1_JENDCIEN_Pos)
#define ADC_CTRL1_JENDCIEN						ADC_CTRL1_JENDCIEN_Msk			/*!< Interrupt enable for injected channels */
#define ADC_CTRL1_SCANMD_Pos					(8U)
#define ADC_CTRL1_SCANMD_Msk					(0x1UL << ADC_CTRL1_SCANMD_Pos)
#define ADC_CTRL1_SCANMD						ADC_CTRL1_SCANMD_Msk			/*!< Scan mode */
#define ADC_CTRL1_AWDGSGLEN_Pos					(9U)
#define ADC_CTRL1_AWDGSGLEN_Msk					(0x1UL << ADC_CTRL1_AWDGSGLEN_Pos)
#define ADC_CTRL1_AWDGSGLEN						ADC_CTRL1_AWDGSGLEN_Msk			/*!< Enable the watchdog on a single channel in scan mode */
#define ADC_CTRL1_AUTOJC_Pos					(10U)
#define ADC_CTRL1_AUTOJC_Msk					(0x1UL << ADC_CTRL1_AUTOJC_Pos)
#define ADC_CTRL1_AUTOJC						ADC_CTRL1_AUTOJC_Msk			/*!< Automatic injected group conversion */
#define ADC_CTRL1_DREGCH_Pos					(11U)
#define ADC_CTRL1_DREGCH_Msk					(0x1UL << ADC_CTRL1_DREGCH_Pos)
#define ADC_CTRL1_DREGCH						ADC_CTRL1_DREGCH_Msk			/*!< Discontinuous mode on regular channels */
#define ADC_CTRL1_DJCH_Pos						(12U)
#define ADC_CTRL1_DJCH_Msk						(0x1UL << ADC_CTRL1_DJCH_Pos)
#define ADC_CTRL1_DJCH							ADC_CTRL1_DJCH_Msk				/*!< Discontinuous mode on injected channels */
#define ADC_CTRL1_DCTU_Pos						(13U)
#define ADC_CTRL1_DCTU_Msk						(0x7UL << ADC_CTRL1_DCTU_Pos)
#define ADC_CTRL1_DCTU							ADC_CTRL1_DCTU_Msk				/*!< DISC_NUM[2:0] bits (Discontinuous mode channel count) */
#define ADC_CTRL1_DCTU_0						((uint32_t) 0x00002000)			/*!< Bit 0 */
#define ADC_CTRL1_DCTU_1						((uint32_t) 0x00004000)			/*!< Bit 1 */
#define ADC_CTRL1_DCTU_2						((uint32_t) 0x00008000)			/*!< Bit 2 */
#define ADC_CTRL1_DUSEL_Pos						(16U)
#define ADC_CTRL1_DUSEL_Msk						(0xFUL << ADC_CTRL1_DUSEL_Pos)
#define ADC_CTRL1_DUSEL							ADC_CTRL1_DUSEL_Msk				/*!< DUALMOD[3:0] bits (Dual mode selection) */
#define ADC_CTRL1_DUSEL_0						((uint32_t) 0x00010000)			/*!< Bit 0 */
#define ADC_CTRL1_DUSEL_1						((uint32_t) 0x00020000)			/*!< Bit 1 */
#define ADC_CTRL1_DUSEL_2						((uint32_t) 0x00040000)			/*!< Bit 2 */
#define ADC_CTRL1_DUSEL_3						((uint32_t) 0x00080000)			/*!< Bit 3 */
#define ADC_CTRL1_AWDGEJCH_Pos					(22U)
#define ADC_CTRL1_AWDGEJCH_Msk					(0x1UL << ADC_CTRL1_AWDGEJCH_Pos)
#define ADC_CTRL1_AWDGEJCH						ADC_CTRL1_AWDGEJCH_Msk			/*!< Analog watchdog enable on injected channels */
#define ADC_CTRL1_AWDGERCH_Pos					(23U)
#define ADC_CTRL1_AWDGERCH_Msk					(0x1UL << ADC_CTRL1_AWDGERCH_Pos)
#define ADC_CTRL1_AWDGERCH						ADC_CTRL1_AWDGERCH_Msk			/*!< Analog watchdog enable on regular channels */

/******************  Bit definition for ADC_CTRL2 register  *******************/
#define ADC_CTRL2_ON_Pos						(0U)
#define ADC_CTRL2_ON_Msk						(0x1UL << ADC_CTRL2_ON_Pos)
#define ADC_CTRL2_ON							ADC_CTRL2_ON_Msk				/*!< A/D Converter ON / OFF */
#define ADC_CTRL2_CTU_Pos						(1U)
#define ADC_CTRL2_CTU_Msk						(0x1UL << ADC_CTRL2_CTU_Pos)
#define ADC_CTRL2_CTU							ADC_CTRL2_CTU_Msk				/*!< Continuous Conversion */
#define ADC_CTRL2_ENCAL_Pos						(2U)
#define ADC_CTRL2_ENCAL_Msk						(0x1UL << ADC_CTRL2_ENCAL_Pos)
#define ADC_CTRL2_ENCAL							ADC_CTRL2_ENCAL_Msk				/*!< A/D Calibration */
#define ADC_CTRL2_ENDMA_Pos						(8U)
#define ADC_CTRL2_ENDMA_Msk						(0x1UL << ADC_CTRL2_ENDMA_Pos)
#define ADC_CTRL2_ENDMA							ADC_CTRL2_ENDMA_Msk				/*!< Direct Memory access mode */
#define ADC_CTRL2_ALIG_Pos						(11U)
#define ADC_CTRL2_ALIG_Msk						(0x1UL << ADC_CTRL2_ALIG_Pos)
#define ADC_CTRL2_ALIG							ADC_CTRL2_ALIG_Msk				/*!< Data Alignment */
#define ADC_CTRL2_EXTJSEL_Pos					(12U)
#define ADC_CTRL2_EXTJSEL_Msk					(0x7UL << ADC_CTRL2_EXTJSEL_Pos)
#define ADC_CTRL2_EXTJSEL						ADC_CTRL2_EXTJSEL_Msk			/*!< INJ_EXT_SEL[2:0] bits (External event select for injected group) */
#define ADC_CTRL2_EXTJSEL_0						((uint32_t) 0x00001000)			/*!< Bit 0 */
#define ADC_CTRL2_EXTJSEL_1						((uint32_t) 0x00002000)			/*!< Bit 1 */
#define ADC_CTRL2_EXTJSEL_2						((uint32_t) 0x00004000)			/*!< Bit 2 */
#define ADC_CTRL2_EXTJTRIG_Pos					(15U)
#define ADC_CTRL2_EXTJTRIG_Msk					(0x1UL << ADC_CTRL2_EXTJTRIG_Pos)
#define ADC_CTRL2_EXTJTRIG						ADC_CTRL2_EXTJTRIG_Msk			/*!< External Trigger Conversion mode for injected channels */
#define ADC_CTRL2_EXTRSEL_Pos					(17U)
#define ADC_CTRL2_EXTRSEL_Msk					(0x7UL << ADC_CTRL2_EXTRSEL_Pos)
#define ADC_CTRL2_EXTRSEL						ADC_CTRL2_EXTRSEL_Msk			/*!< EXTSEL[2:0] bits (External Event Select for regular group) */
#define ADC_CTRL2_EXTRSEL_0						((uint32_t) 0x00020000)			/*!< Bit 0 */
#define ADC_CTRL2_EXTRSEL_1						((uint32_t) 0x00040000)			/*!< Bit 1 */
#define ADC_CTRL2_EXTRSEL_2						((uint32_t) 0x00080000)			/*!< Bit 2 */
#define ADC_CTRL2_EXTRTRIG_Pos					(20U)
#define ADC_CTRL2_EXTRTRIG_Msk					(0x1UL << ADC_CTRL2_EXTRTRIG_Pos)
#define ADC_CTRL2_EXTRTRIG						ADC_CTRL2_EXTRTRIG_Msk			/*!< External Trigger Conversion mode for regular channels */
#define ADC_CTRL2_SWSTRJCH_Pos					(21U)
#define ADC_CTRL2_SWSTRJCH_Msk					(0x1UL << ADC_CTRL2_SWSTRJCH_Pos)
#define ADC_CTRL2_SWSTRJCH						ADC_CTRL2_SWSTRJCH_Msk			/*!< Start Conversion of injected channels */
#define ADC_CTRL2_SWSTRRCH_Pos					(22U)
#define ADC_CTRL2_SWSTRRCH_Msk					(0x1UL << ADC_CTRL2_SWSTRRCH_Pos)
#define ADC_CTRL2_SWSTRRCH						ADC_CTRL2_SWSTRRCH_Msk			/*!< Start Conversion of regular channels */
#define ADC_CTRL2_TEMPEN_Pos					(23U)
#define ADC_CTRL2_TEMPEN_Msk					(0x1UL << ADC_CTRL2_TEMPEN_Pos)
#define ADC_CTRL2_TEMPEN						ADC_CTRL2_TEMPEN_Msk			/*!< Temperature Sensor and VREFINT Enable */

/******************  Bit definition for ADC_SAMPT1 register  ******************/
#define ADC_SAMPT1_SAMP10_Pos					(0U)
#define ADC_SAMPT1_SAMP10_Msk					(0x7UL << ADC_SAMPT1_SAMP10_Pos)
#define ADC_SAMPT1_SAMP10						ADC_SAMPT1_SAMP10_Msk			/*!< SMP10[2:0] bits (Channel 10 Sample time selection) */
#define ADC_SAMPT1_SAMP10_0						((uint32_t) 0x00000001)			/*!< Bit 0 */
#define ADC_SAMPT1_SAMP10_1						((uint32_t) 0x00000002)			/*!< Bit 1 */
#define ADC_SAMPT1_SAMP10_2						((uint32_t) 0x00000004)			/*!< Bit 2 */
#define ADC_SAMPT1_SAMP11_Pos					(3U)
#define ADC_SAMPT1_SAMP11_Msk					(0x7UL << ADC_SAMPT1_SAMP11_Pos)
#define ADC_SAMPT1_SAMP11						ADC_SAMPT1_SAMP11_Msk			/*!< SMP11[2:0] bits (Channel 11 Sample time selection) */
#define ADC_SAMPT1_SAMP11_0						((uint32_t)0x00000008)			/*!< Bit 0 */
#define ADC_SAMPT1_SAMP11_1						((uint32_t)0x00000010)			/*!< Bit 1 */
#define ADC_SAMPT1_SAMP11_2						((uint32_t)0x00000020)			/*!< Bit 2 */
#define ADC_SAMPT1_SAMP12_Pos					(6U)
#define ADC_SAMPT1_SAMP12_Msk					(0x7UL << ADC_SAMPT1_SAMP12_Pos)
#define ADC_SAMPT1_SAMP12						ADC_SAMPT1_SAMP12_Msk			/*!< SMP12[2:0] bits (Channel 12 Sample time selection) */
#define ADC_SAMPT1_SAMP12_0						((uint32_t)0x00000040)			/*!< Bit 0 */
#define ADC_SAMPT1_SAMP12_1						((uint32_t)0x00000080)			/*!< Bit 1 */
#define ADC_SAMPT1_SAMP12_2						((uint32_t)0x00000100)			/*!< Bit 2 */
#define ADC_SAMPT1_SAMP13_Pos					(9U)
#define ADC_SAMPT1_SAMP13_Msk					(0x7UL << ADC_SAMPT1_SAMP13_Pos)
#define ADC_SAMPT1_SAMP13						ADC_SAMPT1_SAMP13_Msk			/*!< SMP13[2:0] bits (Channel 13 Sample time selection) */
#define ADC_SAMPT1_SAMP13_0						((uint32_t)0x00000200)			/*!< Bit 0 */
#define ADC_SAMPT1_SAMP13_1						((uint32_t)0x00000400)			/*!< Bit 1 */
#define ADC_SAMPT1_SAMP13_2						((uint32_t)0x00000800)			/*!< Bit 2 */
#define ADC_SAMPT1_SAMP14_Pos					(12U)
#define ADC_SAMPT1_SAMP14_Msk					(0x7UL << ADC_SAMPT1_SAMP14_Pos)
#define ADC_SAMPT1_SAMP14						ADC_SAMPT1_SAMP14_Msk			/*!< SMP14[2:0] bits (Channel 14 Sample time selection) */
#define ADC_SAMPT1_SAMP14_0						((uint32_t)0x00001000)			/*!< Bit 0 */
#define ADC_SAMPT1_SAMP14_1						((uint32_t)0x00002000)			/*!< Bit 1 */
#define ADC_SAMPT1_SAMP14_2						((uint32_t)0x00004000)			/*!< Bit 2 */
#define ADC_SAMPT1_SAMP15_Pos					(15U)
#define ADC_SAMPT1_SAMP15_Msk					(0x7UL << ADC_SAMPT1_SAMP15_Pos)
#define ADC_SAMPT1_SAMP15						ADC_SAMPT1_SAMP15_Msk			/*!< SMP15[2:0] bits (Channel 15 Sample time selection) */
#define ADC_SAMPT1_SAMP15_0						((uint32_t)0x00008000)			/*!< Bit 0 */
#define ADC_SAMPT1_SAMP15_1						((uint32_t)0x00010000)			/*!< Bit 1 */
#define ADC_SAMPT1_SAMP15_2						((uint32_t)0x00020000)			/*!< Bit 2 */
#define ADC_SAMPT1_SAMP16_Pos					(18U)
#define ADC_SAMPT1_SAMP16_Msk					(0x7UL << ADC_SAMPT1_SAMP16_Pos)
#define ADC_SAMPT1_SAMP16						ADC_SAMPT1_SAMP16_Msk			/*!< SMP16[2:0] bits (Channel 16 Sample time selection) */
#define ADC_SAMPT1_SAMP16_0						((uint32_t)0x00040000)			/*!< Bit 0 */
#define ADC_SAMPT1_SAMP16_1						((uint32_t)0x00080000)			/*!< Bit 1 */
#define ADC_SAMPT1_SAMP16_2						((uint32_t)0x00100000)			/*!< Bit 2 */
#define ADC_SAMPT1_SAMP17_Pos					(21U)
#define ADC_SAMPT1_SAMP17_Msk					(0x7UL << ADC_SAMPT1_SAMP17_Pos)
#define ADC_SAMPT1_SAMP17						ADC_SAMPT1_SAMP17_Msk			/*!< SMP17[2:0] bits (Channel 17 Sample time selection) */
#define ADC_SAMPT1_SAMP17_0						((uint32_t) 0x00200000)			/*!< Bit 0 */
#define ADC_SAMPT1_SAMP17_1						((uint32_t) 0x00400000)			/*!< Bit 1 */
#define ADC_SAMPT1_SAMP17_2						((uint32_t) 0x00800000)			/*!< Bit 2 */

/******************  Bit definition for ADC_SAMPT2 register  ******************/
#define ADC_SAMPT2_SAMP0_Pos					(0U)
#define ADC_SAMPT2_SAMP0_Msk					(0x7UL << ADC_SAMPT2_SAMP0_Pos)
#define ADC_SAMPT2_SAMP0						ADC_SAMPT2_SAMP0_Msk			/*!< SMP0[2:0] bits (Channel 0 Sample time selection) */
#define ADC_SAMPT2_SAMP0_0						((uint32_t)0x00000001)			/*!< Bit 0 */
#define ADC_SAMPT2_SAMP0_1						((uint32_t)0x00000002)			/*!< Bit 1 */
#define ADC_SAMPT2_SAMP0_2						((uint32_t)0x00000004)			/*!< Bit 2 */
#define ADC_SAMPT2_SAMP1_Pos					(3U)
#define ADC_SAMPT2_SAMP1_Msk					(0x7UL << ADC_SAMPT2_SAMP1_Pos)
#define ADC_SAMPT2_SAMP1						ADC_SAMPT2_SAMP1_Msk			/*!< SMP1[2:0] bits (Channel 1 Sample time selection) */
#define ADC_SAMPT2_SAMP1_0						((uint32_t)0x00000008)			/*!< Bit 0 */
#define ADC_SAMPT2_SAMP1_1						((uint32_t)0x00000010)			/*!< Bit 1 */
#define ADC_SAMPT2_SAMP1_2						((uint32_t)0x00000020)			/*!< Bit 2 */
#define ADC_SAMPT2_SAMP2_Pos					(6U)
#define ADC_SAMPT2_SAMP2_Msk					(0x7UL << ADC_SAMPT2_SAMP2_Pos)
#define ADC_SAMPT2_SAMP2						ADC_SAMPT2_SAMP2_Msk			/*!< SMP2[2:0] bits (Channel 2 Sample time selection) */
#define ADC_SAMPT2_SAMP2_0						((uint32_t)0x00000040)			/*!< Bit 0 */
#define ADC_SAMPT2_SAMP2_1						((uint32_t)0x00000080)			/*!< Bit 1 */
#define ADC_SAMPT2_SAMP2_2						((uint32_t)0x00000100)			/*!< Bit 2 */
#define ADC_SAMPT2_SAMP3_Pos					(9U)
#define ADC_SAMPT2_SAMP3_Msk					(0x7UL << ADC_SAMPT2_SAMP3_Pos)
#define ADC_SAMPT2_SAMP3						ADC_SAMPT2_SAMP3_Msk			/*!< SMP3[2:0] bits (Channel 3 Sample time selection) */
#define ADC_SAMPT2_SAMP3_0						((uint32_t)0x00000200)			/*!< Bit 0 */
#define ADC_SAMPT2_SAMP3_1						((uint32_t)0x00000400)			/*!< Bit 1 */
#define ADC_SAMPT2_SAMP3_2						((uint32_t)0x00000800)			/*!< Bit 2 */
#define ADC_SAMPT2_SAMP4_Pos					(12U)
#define ADC_SAMPT2_SAMP4_Msk					(0x7UL << ADC_SAMPT2_SAMP4_Pos)
#define ADC_SAMPT2_SAMP4						ADC_SAMPT2_SAMP4_Msk			/*!< SMP4[2:0] bits (Channel 4 Sample time selection) */
#define ADC_SAMPT2_SAMP4_0						((uint32_t)0x00001000)			/*!< Bit 0 */
#define ADC_SAMPT2_SAMP4_1						((uint32_t)0x00002000)			/*!< Bit 1 */
#define ADC_SAMPT2_SAMP4_2						((uint32_t)0x00004000)			/*!< Bit 2 */
#define ADC_SAMPT2_SAMP5_Pos					(15U)
#define ADC_SAMPT2_SAMP5_Msk					(0x7UL << ADC_SAMPT2_SAMP5_Pos)
#define ADC_SAMPT2_SAMP5						ADC_SAMPT2_SAMP5_Msk			/*!< SMP5[2:0] bits (Channel 5 Sample time selection) */
#define ADC_SAMPT2_SAMP5_0						((uint32_t)0x00008000)			/*!< Bit 0 */
#define ADC_SAMPT2_SAMP5_1						((uint32_t)0x00010000)			/*!< Bit 1 */
#define ADC_SAMPT2_SAMP5_2						((uint32_t)0x00020000)			/*!< Bit 2 */
#define ADC_SAMPT2_SAMP6_Pos					(18U)
#define ADC_SAMPT2_SAMP6_Msk					(0x7UL << ADC_SAMPT2_SAMP6_Pos)
#define ADC_SAMPT2_SAMP6						ADC_SAMPT2_SAMP6_Msk			/*!< SMP6[2:0] bits (Channel 6 Sample time selection) */
#define ADC_SAMPT2_SAMP6_0						((uint32_t) 0x00040000)			/*!< Bit 0 */
#define ADC_SAMPT2_SAMP6_1						((uint32_t) 0x00080000)			/*!< Bit 1 */
#define ADC_SAMPT2_SAMP6_2						((uint32_t) 0x00100000)			/*!< Bit 2 */
#define ADC_SAMPT2_SAMP7_Pos					(21U)
#define ADC_SAMPT2_SAMP7_Msk					(0x7UL << ADC_SAMPT2_SAMP7_Pos)
#define ADC_SAMPT2_SAMP7						ADC_SAMPT2_SAMP7_Msk			/*!< SMP7[2:0] bits (Channel 7 Sample time selection) */
#define ADC_SAMPT2_SAMP7_0						((uint32_t) 0x00200000)			/*!< Bit 0 */
#define ADC_SAMPT2_SAMP7_1						((uint32_t) 0x00400000)			/*!< Bit 1 */
#define ADC_SAMPT2_SAMP7_2						((uint32_t) 0x00800000)			/*!< Bit 2 */
#define ADC_SAMPT2_SAMP8_Pos					(24U)
#define ADC_SAMPT2_SAMP8_Msk					(0x7UL << ADC_SAMPT2_SAMP8_Pos)
#define ADC_SAMPT2_SAMP8						ADC_SAMPT2_SAMP8_Msk			/*!< SMP8[2:0] bits (Channel 8 Sample time selection) */
#define ADC_SAMPT2_SAMP8_0						((uint32_t) 0x01000000)			/*!< Bit 0 */
#define ADC_SAMPT2_SAMP8_1						((uint32_t) 0x02000000)			/*!< Bit 1 */
#define ADC_SAMPT2_SAMP8_2						((uint32_t) 0x04000000)			/*!< Bit 2 */
#define ADC_SAMPT2_SAMP9_Pos					(27U)
#define ADC_SAMPT2_SAMP9_Msk					(0x7UL << ADC_SAMPT2_SAMP9_Pos)
#define ADC_SAMPT2_SAMP9						ADC_SAMPT2_SAMP9_Msk			/*!< SMP9[2:0] bits (Channel 9 Sample time selection) */
#define ADC_SAMPT2_SAMP9_0						((uint32_t) 0x08000000)			/*!< Bit 0 */
#define ADC_SAMPT2_SAMP9_1						((uint32_t) 0x10000000)			/*!< Bit 1 */
#define ADC_SAMPT2_SAMP9_2						((uint32_t) 0x20000000)			/*!< Bit 2 */

/*****************  Bit definition for ADC_JOFFSET1 register  *****************/
#define ADC_JOFFSET1_OFFSETJCH1_Pos				(0U)
#define ADC_JOFFSET1_OFFSETJCH1_Msk				(0xFFFUL << ADC_JOFFSET1_OFFSETJCH1_Pos)	/*!< 0x00000FFF */
#define ADC_JOFFSET1_OFFSETJCH1					ADC_JOFFSET1_OFFSETJCH1_Msk		/*!< Data offset for injected channel 1 */

/*****************  Bit definition for ADC_JOFFSET2 register  *****************/
#define ADC_JOFFSET2_OFFSETJCH2_Pos				(0U)
#define ADC_JOFFSET2_OFFSETJCH2_Msk				(0xFFFUL << ADC_JOFFSET2_OFFSETJCH2_Pos)	/*!< 0x00000FFF */
#define ADC_JOFFSET2_OFFSETJCH2					ADC_JOFFSET2_OFFSETJCH2_Msk		/*!< Data offset for injected channel 2 */

/*****************  Bit definition for ADC_JOFFSET3 register  *****************/
#define ADC_JOFFSET3_OFFSETJCH3_Pos				(0U)
#define ADC_JOFFSET3_OFFSETJCH3_Msk				(0xFFFUL << ADC_JOFFSET3_OFFSETJCH3_Pos)	/*!< 0x00000FFF */
#define ADC_JOFFSET3_OFFSETJCH3					ADC_JOFFSET3_OFFSETJCH3_Msk		/*!< Data offset for injected channel 3 */

/*****************  Bit definition for ADC_JOFFSET4 register  *****************/
#define ADC_JOFFSET4_OFFSETJCH4_Pos				(0U)
#define ADC_JOFFSET4_OFFSETJCH4_Msk				(0xFFFUL << ADC_JOFFSET4_OFFSETJCH4_Pos)	/*!< 0x00000FFF */
#define ADC_JOFFSET4_OFFSETJCH4					ADC_JOFFSET4_OFFSETJCH4_Msk		/*!< Data offset for injected channel 4 */

/*****************  Bit definition for ADC_WDGHIGH register  ******************/
#define ADC_WDGHIGH_HTH_Pos						(0U)
#define ADC_WDGHIGH_HTH_Msk						(0xFFFUL << ADC_WDGHIGH_HTH_Pos)
#define ADC_WDGHIGH_HTH							ADC_WDGHIGH_HTH_Msk				/*!< Analog watchdog high threshold */

/******************  Bit definition for ADC_WDGLOW register  ******************/
#define ADC_WDGLOW_LTH_Pos						(0U)
#define ADC_WDGLOW_LTH_Msk						(0xFFFUL << ADC_WDGLOW_LTH_Pos)
#define ADC_WDGLOW_LTH							ADC_WDGLOW_LTH_Msk				/*!< Analog watchdog low threshold */

/******************  Bit definition for ADC_RSEQ1 register  *******************/
#define ADC_RSEQ1_SEQ13_Pos						(0U)
#define ADC_RSEQ1_SEQ13_Msk						(0x1FUL << ADC_RSEQ1_SEQ13_Pos)
#define ADC_RSEQ1_SEQ13							ADC_RSEQ1_SEQ13_Msk				/*!< SQ13[4:0] bits (13th conversion in regular sequence) */
#define ADC_RSEQ1_SEQ13_0						((uint32_t) 0x00000001)			/*!< Bit 0 */
#define ADC_RSEQ1_SEQ13_1						((uint32_t) 0x00000002)			/*!< Bit 1 */
#define ADC_RSEQ1_SEQ13_2						((uint32_t) 0x00000004)			/*!< Bit 2 */
#define ADC_RSEQ1_SEQ13_3						((uint32_t) 0x00000008)			/*!< Bit 3 */
#define ADC_RSEQ1_SEQ13_4						((uint32_t) 0x00000010)			/*!< Bit 4 */
#define ADC_RSEQ1_SEQ14_Pos						(5U)
#define ADC_RSEQ1_SEQ14_Msk						(0x1FUL << ADC_RSEQ1_SEQ14_Pos)
#define ADC_RSEQ1_SEQ14							ADC_RSEQ1_SEQ14_Msk				/*!< SQ14[4:0] bits (14th conversion in regular sequence) */
#define ADC_RSEQ1_SEQ14_0						((uint32_t) 0x00000020)			/*!< Bit 0 */
#define ADC_RSEQ1_SEQ14_1						((uint32_t) 0x00000040)			/*!< Bit 1 */
#define ADC_RSEQ1_SEQ14_2						((uint32_t) 0x00000080)			/*!< Bit 2 */
#define ADC_RSEQ1_SEQ14_3						((uint32_t) 0x00000100)			/*!< Bit 3 */
#define ADC_RSEQ1_SEQ14_4						((uint32_t) 0x00000200)			/*!< Bit 4 */
#define ADC_RSEQ1_SEQ15_Pos						(10U)
#define ADC_RSEQ1_SEQ15_Msk						(0x1FUL << ADC_RSEQ1_SEQ15_Pos)
#define ADC_RSEQ1_SEQ15							ADC_RSEQ1_SEQ15_Msk				/*!< SQ15[4:0] bits (15th conversion in regular sequence) */
#define ADC_RSEQ1_SEQ15_0						((uint32_t) 0x00000400)			/*!< Bit 0 */
#define ADC_RSEQ1_SEQ15_1						((uint32_t) 0x00000800)			/*!< Bit 1 */
#define ADC_RSEQ1_SEQ15_2						((uint32_t) 0x00001000)			/*!< Bit 2 */
#define ADC_RSEQ1_SEQ15_3						((uint32_t) 0x00002000)			/*!< Bit 3 */
#define ADC_RSEQ1_SEQ15_4						((uint32_t) 0x00004000)			/*!< Bit 4 */
#define ADC_RSEQ1_SEQ16_Pos						(15U)
#define ADC_RSEQ1_SEQ16_Msk						(0x1FUL << ADC_RSEQ1_SEQ16_Pos)
#define ADC_RSEQ1_SEQ16							ADC_RSEQ1_SEQ16_Msk				/*!< SQ16[4:0] bits (16th conversion in regular sequence) */
#define ADC_RSEQ1_SEQ16_0						((uint32_t) 0x00008000)			/*!< Bit 0 */
#define ADC_RSEQ1_SEQ16_1						((uint32_t) 0x00010000)			/*!< Bit 1 */
#define ADC_RSEQ1_SEQ16_2						((uint32_t) 0x00020000)			/*!< Bit 2 */
#define ADC_RSEQ1_SEQ16_3						((uint32_t) 0x00040000)			/*!< Bit 3 */
#define ADC_RSEQ1_SEQ16_4						((uint32_t) 0x00080000)			/*!< Bit 4 */
#define ADC_RSEQ1_LEN_Pos						(20U)
#define ADC_RSEQ1_LEN_Msk						(0xFUL << ADC_RSEQ1_LEN_Pos)
#define ADC_RSEQ1_LEN							ADC_RSEQ1_LEN_Msk				/*!< L[3:0] bits (Regular channel sequence length) */
#define ADC_RSEQ1_LEN_0							((uint32_t) 0x00100000)			/*!< Bit 0 */
#define ADC_RSEQ1_LEN_1							((uint32_t) 0x00200000)			/*!< Bit 1 */
#define ADC_RSEQ1_LEN_2							((uint32_t) 0x00400000)			/*!< Bit 2 */
#define ADC_RSEQ1_LEN_3							((uint32_t) 0x00800000)			/*!< Bit 3 */

/******************  Bit definition for ADC_RSEQ2 register  *******************/
#define ADC_RSEQ2_SEQ7_Pos						(0U)
#define ADC_RSEQ2_SEQ7_Msk						(0x1FUL << ADC_RSEQ2_SEQ7_Pos)
#define ADC_RSEQ2_SEQ7							ADC_RSEQ2_SEQ7_Msk				/*!< SQ7[4:0] bits (7th conversion in regular sequence) */
#define ADC_RSEQ2_SEQ7_0						((uint32_t) 0x00000001)			/*!< Bit 0 */
#define ADC_RSEQ2_SEQ7_1						((uint32_t) 0x00000002)			/*!< Bit 1 */
#define ADC_RSEQ2_SEQ7_2						((uint32_t) 0x00000004)			/*!< Bit 2 */
#define ADC_RSEQ2_SEQ7_3						((uint32_t) 0x00000008)			/*!< Bit 3 */
#define ADC_RSEQ2_SEQ7_4						((uint32_t) 0x00000010)			/*!< Bit 4 */
#define ADC_RSEQ2_SEQ8_Pos						(5U)
#define ADC_RSEQ2_SEQ8_Msk						(0x1FUL << ADC_RSEQ2_SEQ8_Pos)
#define ADC_RSEQ2_SEQ8							ADC_RSEQ2_SEQ8_Msk				/*!< SQ8[4:0] bits (8th conversion in regular sequence) */
#define ADC_RSEQ2_SEQ8_0						((uint32_t) 0x00000020)			/*!< Bit 0 */
#define ADC_RSEQ2_SEQ8_1						((uint32_t) 0x00000040)			/*!< Bit 1 */
#define ADC_RSEQ2_SEQ8_2						((uint32_t) 0x00000080)			/*!< Bit 2 */
#define ADC_RSEQ2_SEQ8_3						((uint32_t) 0x00000100)			/*!< Bit 3 */
#define ADC_RSEQ2_SEQ8_4						((uint32_t) 0x00000200)			/*!< Bit 4 */
#define ADC_RSEQ2_SEQ9_Pos						(10U)
#define ADC_RSEQ2_SEQ9_Msk						(0x1FUL << ADC_RSEQ2_SEQ9_Pos)
#define ADC_RSEQ2_SEQ9							ADC_RSEQ2_SEQ9_Msk				/*!< SQ9[4:0] bits (9th conversion in regular sequence) */
#define ADC_RSEQ2_SEQ9_0						((uint32_t) 0x00000400)			/*!< Bit 0 */
#define ADC_RSEQ2_SEQ9_1						((uint32_t) 0x00000800)			/*!< Bit 1 */
#define ADC_RSEQ2_SEQ9_2						((uint32_t) 0x00001000)			/*!< Bit 2 */
#define ADC_RSEQ2_SEQ9_3						((uint32_t) 0x00002000)			/*!< Bit 3 */
#define ADC_RSEQ2_SEQ9_4						((uint32_t) 0x00004000)			/*!< Bit 4 */
#define ADC_RSEQ2_SEQ10_Pos						(15U)
#define ADC_RSEQ2_SEQ10_Msk						(0x1FUL << ADC_RSEQ2_SEQ10_Pos)
#define ADC_RSEQ2_SEQ10							ADC_RSEQ2_SEQ10_Msk				/*!< SQ10[4:0] bits (10th conversion in regular sequence) */
#define ADC_RSEQ2_SEQ10_0						((uint32_t) 0x00008000)			/*!< Bit 0 */
#define ADC_RSEQ2_SEQ10_1						((uint32_t) 0x00010000)			/*!< Bit 1 */
#define ADC_RSEQ2_SEQ10_2						((uint32_t) 0x00020000)			/*!< Bit 2 */
#define ADC_RSEQ2_SEQ10_3						((uint32_t) 0x00040000)			/*!< Bit 3 */
#define ADC_RSEQ2_SEQ10_4						((uint32_t) 0x00080000)			/*!< Bit 4 */
#define ADC_RSEQ2_SEQ11_Pos						(20U)
#define ADC_RSEQ2_SEQ11_Msk						(0x1FUL << ADC_RSEQ2_SEQ11_Pos)
#define ADC_RSEQ2_SEQ11							ADC_RSEQ2_SEQ11_Msk				/*!< SQ11[4:0] bits (11th conversion in regular sequence) */
#define ADC_RSEQ2_SEQ11_0						((uint32_t) 0x00100000)			/*!< Bit 0 */
#define ADC_RSEQ2_SEQ11_1						((uint32_t) 0x00200000)			/*!< Bit 1 */
#define ADC_RSEQ2_SEQ11_2						((uint32_t) 0x00400000)			/*!< Bit 2 */
#define ADC_RSEQ2_SEQ11_3						((uint32_t) 0x00800000)			/*!< Bit 3 */
#define ADC_RSEQ2_SEQ11_4						((uint32_t) 0x01000000)			/*!< Bit 4 */
#define ADC_RSEQ2_SEQ12_Pos						(25U)
#define ADC_RSEQ2_SEQ12_Msk						(0x1FUL << ADC_RSEQ2_SEQ12_Pos)
#define ADC_RSEQ2_SEQ12							ADC_RSEQ2_SEQ12_Msk				/*!< SQ12[4:0] bits (12th conversion in regular sequence) */
#define ADC_RSEQ2_SEQ12_0						((uint32_t) 0x02000000)			/*!< Bit 0 */
#define ADC_RSEQ2_SEQ12_1						((uint32_t) 0x04000000)			/*!< Bit 1 */
#define ADC_RSEQ2_SEQ12_2						((uint32_t) 0x08000000)			/*!< Bit 2 */
#define ADC_RSEQ2_SEQ12_3						((uint32_t) 0x10000000)			/*!< Bit 3 */
#define ADC_RSEQ2_SEQ12_4						((uint32_t) 0x20000000)			/*!< Bit 4 */

/******************  Bit definition for ADC_RSEQ3 register  *******************/
#define ADC_RSEQ3_SEQ1_Pos						(0U)
#define ADC_RSEQ3_SEQ1_Msk						(0x1FUL << ADC_RSEQ3_SEQ1_Pos)
#define ADC_RSEQ3_SEQ1							ADC_RSEQ3_SEQ1_Msk				/*!< SQ1[4:0] bits (1st conversion in regular sequence) */
#define ADC_RSEQ3_SEQ1_0						((uint32_t) 0x00000001)			/*!< Bit 0 */
#define ADC_RSEQ3_SEQ1_1						((uint32_t) 0x00000002)			/*!< Bit 1 */
#define ADC_RSEQ3_SEQ1_2						((uint32_t) 0x00000004)			/*!< Bit 2 */
#define ADC_RSEQ3_SEQ1_3						((uint32_t) 0x00000008)			/*!< Bit 3 */
#define ADC_RSEQ3_SEQ1_4						((uint32_t) 0x00000010)			/*!< Bit 4 */
#define ADC_RSEQ3_SEQ2_Pos						(5U)
#define ADC_RSEQ3_SEQ2_Msk						(0x1FUL << ADC_RSEQ3_SEQ2_Pos)
#define ADC_RSEQ3_SEQ2							ADC_RSEQ3_SEQ2_Msk				/*!< SQ2[4:0] bits (2nd conversion in regular sequence) */
#define ADC_RSEQ3_SEQ2_0						((uint32_t) 0x00000020)			/*!< Bit 0 */
#define ADC_RSEQ3_SEQ2_1						((uint32_t) 0x00000040)			/*!< Bit 1 */
#define ADC_RSEQ3_SEQ2_2						((uint32_t) 0x00000080)			/*!< Bit 2 */
#define ADC_RSEQ3_SEQ2_3						((uint32_t) 0x00000100)			/*!< Bit 3 */
#define ADC_RSEQ3_SEQ2_4						((uint32_t) 0x00000200)			/*!< Bit 4 */
#define ADC_RSEQ3_SEQ3_Pos						(10U)
#define ADC_RSEQ3_SEQ3_Msk						(0x1FUL << ADC_RSEQ3_SEQ3_Pos)
#define ADC_RSEQ3_SEQ3							ADC_RSEQ3_SEQ3_Msk				/*!< SQ3[4:0] bits (3rd conversion in regular sequence) */
#define ADC_RSEQ3_SEQ3_0						((uint32_t) 0x00000400)			/*!< Bit 0 */
#define ADC_RSEQ3_SEQ3_1						((uint32_t) 0x00000800)			/*!< Bit 1 */
#define ADC_RSEQ3_SEQ3_2						((uint32_t) 0x00001000)			/*!< Bit 2 */
#define ADC_RSEQ3_SEQ3_3						((uint32_t) 0x00002000)			/*!< Bit 3 */
#define ADC_RSEQ3_SEQ3_4						((uint32_t) 0x00004000)			/*!< Bit 4 */
#define ADC_RSEQ3_SEQ4_Pos						(15U)
#define ADC_RSEQ3_SEQ4_Msk						(0x1FUL << ADC_RSEQ3_SEQ4_Pos)
#define ADC_RSEQ3_SEQ4							ADC_RSEQ3_SEQ4_Msk				/*!< SQ4[4:0] bits (4th conversion in regular sequence) */
#define ADC_RSEQ3_SEQ4_0						((uint32_t) 0x00008000)			/*!< Bit 0 */
#define ADC_RSEQ3_SEQ4_1						((uint32_t) 0x00010000)			/*!< Bit 1 */
#define ADC_RSEQ3_SEQ4_2						((uint32_t) 0x00020000)			/*!< Bit 2 */
#define ADC_RSEQ3_SEQ4_3						((uint32_t) 0x00040000)			/*!< Bit 3 */
#define ADC_RSEQ3_SEQ4_4						((uint32_t) 0x00080000)			/*!< Bit 4 */
#define ADC_RSEQ3_SEQ5_Pos						(20U)
#define ADC_RSEQ3_SEQ5_Msk						(0x1FUL << ADC_RSEQ3_SEQ5_Pos)
#define ADC_RSEQ3_SEQ5							ADC_RSEQ3_SEQ5_Msk				/*!< SQ5[4:0] bits (5th conversion in regular sequence) */
#define ADC_RSEQ3_SEQ5_0						((uint32_t) 0x00100000)			/*!< Bit 0 */
#define ADC_RSEQ3_SEQ5_1						((uint32_t) 0x00200000)			/*!< Bit 1 */
#define ADC_RSEQ3_SEQ5_2						((uint32_t) 0x00400000)			/*!< Bit 2 */
#define ADC_RSEQ3_SEQ5_3						((uint32_t) 0x00800000)			/*!< Bit 3 */
#define ADC_RSEQ3_SEQ5_4						((uint32_t) 0x01000000)			/*!< Bit 4 */
#define ADC_RSEQ3_SEQ6_Pos						(25U)
#define ADC_RSEQ3_SEQ6_Msk						(0x1FUL << ADC_RSEQ3_SEQ6_Pos)
#define ADC_RSEQ3_SEQ6							ADC_RSEQ3_SEQ6_Msk				/*!< SQ6[4:0] bits (6th conversion in regular sequence) */
#define ADC_RSEQ3_SEQ6_0						((uint32_t) 0x02000000)			/*!< Bit 0 */
#define ADC_RSEQ3_SEQ6_1						((uint32_t) 0x04000000)			/*!< Bit 1 */
#define ADC_RSEQ3_SEQ6_2						((uint32_t) 0x08000000)			/*!< Bit 2 */
#define ADC_RSEQ3_SEQ6_3						((uint32_t) 0x10000000)			/*!< Bit 3 */
#define ADC_RSEQ3_SEQ6_4						((uint32_t) 0x20000000)			/*!< Bit 4 */

/*******************  Bit definition for ADC_JSEQ register  *******************/
#define ADC_JSEQ_JSEQ1_Pos						(0U)
#define ADC_JSEQ_JSEQ1_Msk						(0x1FUL << ADC_JSEQ_JSEQ1_Pos)
#define ADC_JSEQ_JSEQ1							ADC_JSEQ_JSEQ1_Msk				/*!< JSQ1[4:0] bits (1st conversion in injected sequence) */
#define ADC_JSEQ_JSEQ1_0						((uint32_t) 0x00000001)			/*!< Bit 0 */
#define ADC_JSEQ_JSEQ1_1						((uint32_t) 0x00000002)			/*!< Bit 1 */
#define ADC_JSEQ_JSEQ1_2						((uint32_t) 0x00000004)			/*!< Bit 2 */
#define ADC_JSEQ_JSEQ1_3						((uint32_t) 0x00000008)			/*!< Bit 3 */
#define ADC_JSEQ_JSEQ1_4						((uint32_t) 0x00000010)			/*!< Bit 4 */
#define ADC_JSEQ_JSEQ2_Pos						(5U)
#define ADC_JSEQ_JSEQ2_Msk						(0x1FUL << ADC_JSEQ_JSEQ2_Pos)
#define ADC_JSEQ_JSEQ2							ADC_JSEQ_JSEQ2_Msk				/*!< JSQ2[4:0] bits (2nd conversion in injected sequence) */
#define ADC_JSEQ_JSEQ2_0						((uint32_t) 0x00000020)			/*!< Bit 0 */
#define ADC_JSEQ_JSEQ2_1						((uint32_t) 0x00000040)			/*!< Bit 1 */
#define ADC_JSEQ_JSEQ2_2						((uint32_t) 0x00000080)			/*!< Bit 2 */
#define ADC_JSEQ_JSEQ2_3						((uint32_t) 0x00000100)			/*!< Bit 3 */
#define ADC_JSEQ_JSEQ2_4						((uint32_t) 0x00000200)			/*!< Bit 4 */
#define ADC_JSEQ_JSEQ3_Pos						(10U)
#define ADC_JSEQ_JSEQ3_Msk						(0x1FUL << ADC_JSEQ_JSEQ3_Pos)
#define ADC_JSEQ_JSEQ3							ADC_JSEQ_JSEQ3_Msk				/*!< JSQ3[4:0] bits (3rd conversion in injected sequence) */
#define ADC_JSEQ_JSEQ3_0						((uint32_t) 0x00000400)			/*!< Bit 0 */
#define ADC_JSEQ_JSEQ3_1						((uint32_t) 0x00000800)			/*!< Bit 1 */
#define ADC_JSEQ_JSEQ3_2						((uint32_t) 0x00001000)			/*!< Bit 2 */
#define ADC_JSEQ_JSEQ3_3						((uint32_t) 0x00002000)			/*!< Bit 3 */
#define ADC_JSEQ_JSEQ3_4						((uint32_t) 0x00004000)			/*!< Bit 4 */
#define ADC_JSEQ_JSEQ4_Pos						(15U)
#define ADC_JSEQ_JSEQ4_Msk						(0x1FUL << ADC_JSEQ_JSEQ4_Pos)
#define ADC_JSEQ_JSEQ4							ADC_JSEQ_JSEQ4_Msk				/*!< JSQ4[4:0] bits (4th conversion in injected sequence) */
#define ADC_JSEQ_JSEQ4_0						((uint32_t) 0x00008000)			/*!< Bit 0 */
#define ADC_JSEQ_JSEQ4_1						((uint32_t) 0x00010000)			/*!< Bit 1 */
#define ADC_JSEQ_JSEQ4_2						((uint32_t) 0x00020000)			/*!< Bit 2 */
#define ADC_JSEQ_JSEQ4_3						((uint32_t) 0x00040000)			/*!< Bit 3 */
#define ADC_JSEQ_JSEQ4_4						((uint32_t) 0x00080000)			/*!< Bit 4 */
#define ADC_JSEQ_JLEN_Pos						(20U)
#define ADC_JSEQ_JLEN_Msk						(0x3UL << ADC_JSEQ_JLEN_Pos)
#define ADC_JSEQ_JLEN							ADC_JSEQ_JLEN_Msk				/*!< INJ_LEN[1:0] bits (Injected Sequence length) */
#define ADC_JSEQ_JLEN_0							((uint32_t) 0x00100000)			/*!< Bit 0 */
#define ADC_JSEQ_JLEN_1							((uint32_t) 0x00200000)			/*!< Bit 1 */

/******************  Bit definition for ADC_JDAT1 register  *******************/
#define ADC_JDAT1_JDAT_Pos						(0U)
#define ADC_JDAT1_JDAT_Msk						(0xFFFFUL << ADC_JDAT1_JDAT_Pos)	/*!< 0x0000FFFF */
#define ADC_JDAT1_JDAT							ADC_JDAT1_JDAT_Msk				/*!< Injected data */

/******************  Bit definition for ADC_JDAT2 register  *******************/
#define ADC_JDAT2_JDAT_Pos						(0U)
#define ADC_JDAT2_JDAT_Msk						(0xFFFFUL << ADC_JDAT2_JDAT_Pos)	/*!< 0x0000FFFF */
#define ADC_JDAT2_JDAT							ADC_JDAT2_JDAT_Msk				/*!< Injected data */

/******************  Bit definition for ADC_JDAT3 register  *******************/
#define ADC_JDAT3_JDAT_Pos						(0U)
#define ADC_JDAT3_JDAT_Msk						(0xFFFFUL << ADC_JDAT3_JDAT_Pos)	/*!< 0x0000FFFF */
#define ADC_JDAT3_JDAT							ADC_JDAT3_JDAT_Msk				/*!< Injected data */

/******************  Bit definition for ADC_JDAT4 register  *******************/
#define ADC_JDAT4_JDAT_Pos						(0U)
#define ADC_JDAT4_JDAT_Msk						(0xFFFFUL << ADC_JDAT4_JDAT_Pos)	/*!< 0x0000FFFF */
#define ADC_JDAT4_JDAT							ADC_JDAT4_JDAT_Msk				/*!< Injected data */

/*******************  Bit definition for ADC_DAT register  ********************/
#define ADC_DAT_DAT_Pos							(0U)
#define ADC_DAT_DAT_Msk							(0xFFFFUL << ADC_DAT_DAT_Pos)		/*!< 0x0000FFFF */
#define ADC_DAT_DAT								ADC_DAT_DAT_Msk					/*!< Regular data */
#define ADC_DAT_ADC2DAT_Pos						(16U)
#define ADC_DAT_ADC2DAT_Msk						(0xFFFFUL << ADC_DAT_ADC2DAT_Pos)	/*!< 0xFFFF0000 */
#define ADC_DAT_ADC2DAT							ADC_DAT_ADC2DAT_Msk				/*!< ADC2 data */

/******************  Bit definition for ADC_DIFSEL register  ******************/
#define ADC_DIFSEL_DIFSEL_Pos					(1U)
#define ADC_DIFSEL_DIFSEL_Msk					(0x7FFFFUL << ADC_DIFSEL_DIFSEL_Pos)	/*!< 0x000FFFFE */
#define ADC_DIFSEL_DIFSEL						ADC_DIFSEL_DIFSEL_Msk			/*!< Differential mode for channels 18 to 1 */

/*****************  Bit definition for ADC_CALFACT register  ******************/
#define ADC_CALFACT_CALFACTS_Pos				(0U)
#define ADC_CALFACT_CALFACTS_Msk				(0x7FUL << ADC_CALFACT_CALFACTS_Pos)
#define ADC_CALFACT_CALFACTS					ADC_CALFACT_CALFACTS_Msk		/*!< Calibration Factors in Single-Ended mode */

#define ADC_CALFACT_CALFACTD_Pos				(16U)
#define ADC_CALFACT_CALFACTD_Msk				(0x7FUL << ADC_CALFACT_CALFACTD_Pos)
#define ADC_CALFACT_CALFACTD					ADC_CALFACT_CALFACTD_Msk		/*!< Calibration Factors in differential mode */

/******************  Bit definition for ADC_CTRL3 register  *******************/
#define ADC_CTRL3_RES_Pos						(0U)
#define ADC_CTRL3_RES_Msk						(0x3UL << ADC_CTRL3_RES_Pos)
#define ADC_CTRL3_RES							ADC_CTRL3_RES_Msk				/*!< Data resolution */
#define ADC_CTRL3_CALDIF_Pos					(2U)
#define ADC_CTRL3_CALDIF_Msk					(0x1UL << ADC_CTRL3_CALDIF_Pos)
#define ADC_CTRL3_CALDIF						ADC_CTRL3_CALDIF_Msk			/*!< Differential mode for calibration */
#define ADC_CTRL3_CALALD_Pos					(3U)
#define ADC_CTRL3_CALALD_Msk					(0x1UL << ADC_CTRL3_CALALD_Pos)
#define ADC_CTRL3_CALALD						ADC_CTRL3_CALALD_Msk			/*!< Calibration auto load */
#define ADC_CTRL3_CKMOD_Pos						(4U)
#define ADC_CTRL3_CKMOD_Msk						(0x1UL << ADC_CTRL3_CKMOD_Pos)
#define ADC_CTRL3_CKMOD							ADC_CTRL3_CKMOD_Msk				/*!< Clock Mode */
#define ADC_CTRL3_RDY_Pos						(5U)
#define ADC_CTRL3_RDY_Msk						(0x1UL << ADC_CTRL3_RDY_Pos)
#define ADC_CTRL3_RDY							ADC_CTRL3_RDY_Msk				/*!< Ready */
#define ADC_CTRL3_PDRDY_Pos						(6U)
#define ADC_CTRL3_PDRDY_Msk						(0x1UL << ADC_CTRL3_PDRDY_Pos)
#define ADC_CTRL3_PDRDY							ADC_CTRL3_PDRDY_Msk				/*!< Power down ready */
#define ADC_CTRL3_BPCAL_Pos						(7U)
#define ADC_CTRL3_BPCAL_Msk						(0x1UL << ADC_CTRL3_BPCAL_Pos)
#define ADC_CTRL3_BPCAL							ADC_CTRL3_BPCAL_Msk				/*!< Bypass calibration */
#define ADC_CTRL3_ENDCAIEN_Pos					(8U)
#define ADC_CTRL3_ENDCAIEN_Msk					(0x1UL << ADC_CTRL3_ENDCAIEN_Pos)
#define ADC_CTRL3_ENDCAIEN						ADC_CTRL3_ENDCAIEN_Msk			/*!< Interrupt enable for any regular channels */
#define ADC_CTRL3_JENDCAIEN_Pos					(9U)
#define ADC_CTRL3_JENDCAIEN_Msk					(0x1UL << ADC_CTRL3_JENDCAIEN_Pos)
#define ADC_CTRL3_JENDCAIEN						ADC_CTRL3_JENDCAIEN_Msk			/*!< Interrupt enable for any injected channels */
#define ADC_CTRL3_DPWMOD_Pos					(10U)
#define ADC_CTRL3_DPWMOD_Msk					(0x1UL << ADC_CTRL3_DPWMOD_Pos)
#define ADC_CTRL3_DPWMOD						ADC_CTRL3_DPWMOD_Msk			/*!< Deep Power Mode */
#define ADC_CTRL3_VBATMEN_Pos					(11U)
#define ADC_CTRL3_VBATMEN_Msk					(0x1UL << ADC_CTRL3_VBATMEN_Pos)
#define ADC_CTRL3_VBATMEN						ADC_CTRL3_VBATMEN_Msk			/*!< Vbat monitor enable */

/******************  Bit definition for ADC_SAMPT3 register  ******************/
#define ADC_SAMPT3_SAMP18_Pos					(0U)
#define ADC_SAMPT3_SAMP18_Msk					(0x7UL << ADC_SAMPT3_SAMP18_Pos)
#define ADC_SAMPT3_SAMP18						ADC_SAMPT3_SAMP18_Msk			/*!< Channel Sample time */
#define ADC_SAMPT3_SAMPSEL_Pos					(3U)
#define ADC_SAMPT3_SAMPSEL_Msk					(0x1UL << ADC_SAMPT3_SAMPSEL_Pos)
#define ADC_SAMPT3_SAMPSEL						ADC_SAMPT3_SAMPSEL_Msk			/*!< Sample time selection */

/******************************************************************************/
/*                                                                            */
/*                      Digital to Analog Converter                           */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for DAC_CTRL register  *******************/
#define DAC_CTRL_CH1EN_Pos						(0U)
#define DAC_CTRL_CH1EN_Msk						(0x1UL << DAC_CTRL_CH1EN_Pos)
#define DAC_CTRL_CH1EN							DAC_CTRL_CH1EN_Msk				/*!< DAC channel1 enable */
#define DAC_CTRL_B1EN_Pos						(1U)
#define DAC_CTRL_B1EN_Msk						(0x1UL << DAC_CTRL_B1EN_Pos)
#define DAC_CTRL_B1EN							DAC_CTRL_B1EN_Msk				/*!< DAC channel1 output buffer enable */
#define DAC_CTRL_T1EN_Pos						(2U)
#define DAC_CTRL_T1EN_Msk						(0x1UL << DAC_CTRL_T1EN_Pos)
#define DAC_CTRL_T1EN							DAC_CTRL_T1EN_Msk				/*!< DAC channel1 Trigger enable */
#define DAC_CTRL_T1SEL_Pos						(3U)
#define DAC_CTRL_T1SEL_Msk						(0x7UL << DAC_CTRL_T1SEL_Pos)
#define DAC_CTRL_T1SEL							DAC_CTRL_T1SEL_Msk				/*!< TSEL1[2:0] (DAC channel1 Trigger selection) */
#define DAC_CTRL_T1SEL_0						((uint32_t) 0x00000008)			/*!< Bit 0 */
#define DAC_CTRL_T1SEL_1						((uint32_t) 0x00000010)			/*!< Bit 1 */
#define DAC_CTRL_T1SEL_2						((uint32_t) 0x00000020)			/*!< Bit 2 */
#define DAC_CTRL_W1EN_Pos						(6U)
#define DAC_CTRL_W1EN_Msk						(0x3UL << DAC_CTRL_W1EN_Pos)
#define DAC_CTRL_W1EN							DAC_CTRL_W1EN_Msk				/*!< WAVE1[1:0] (DAC channel1 noise/triangle wave generation enable) */
#define DAC_CTRL_W1EN_0							((uint32_t) 0x00000040)			/*!< Bit 0 */
#define DAC_CTRL_W1EN_1							((uint32_t) 0x00000080)			/*!< Bit 1 */
#define DAC_CTRL_MA1SEL_Pos						(8U)
#define DAC_CTRL_MA1SEL_Msk						(0xFUL << DAC_CTRL_MA1SEL_Pos)
#define DAC_CTRL_MA1SEL							DAC_CTRL_MA1SEL_Msk				/*!< MAMP1[3:0] (DAC channel1 Mask/Amplitude selector) */
#define DAC_CTRL_MA1SEL_0						((uint32_t) 0x00000100)			/*!< Bit 0 */
#define DAC_CTRL_MA1SEL_1						((uint32_t) 0x00000200)			/*!< Bit 1 */
#define DAC_CTRL_MA1SEL_2						((uint32_t) 0x00000400)			/*!< Bit 2 */
#define DAC_CTRL_MA1SEL_3						((uint32_t) 0x00000800)			/*!< Bit 3 */
#define DAC_CTRL_DMA1EN_Pos						(12U)
#define DAC_CTRL_DMA1EN_Msk						(0x1UL << DAC_CTRL_DMA1EN_Pos)
#define DAC_CTRL_DMA1EN							DAC_CTRL_DMA1EN_Msk				/*!< DAC channel1 DMA enable */
#define DAC_CTRL_CH2EN_Pos						(16U)
#define DAC_CTRL_CH2EN_Msk						(0x1UL << DAC_CTRL_CH2EN_Pos)
#define DAC_CTRL_CH2EN							DAC_CTRL_CH2EN_Msk				/*!< DAC channel2 enable */
#define DAC_CTRL_B2EN_Pos						(17U)
#define DAC_CTRL_B2EN_Msk						(0x1UL << DAC_CTRL_B2EN_Pos)
#define DAC_CTRL_B2EN							DAC_CTRL_B2EN_Msk				/*!< DAC channel2 output buffer enable */
#define DAC_CTRL_T2EN_Pos						(18U)
#define DAC_CTRL_T2EN_Msk						(0x1UL << DAC_CTRL_T2EN_Pos)
#define DAC_CTRL_T2EN							DAC_CTRL_T2EN_Msk				/*!< DAC channel2 Trigger enable */
#define DAC_CTRL_T2SEL_Pos						(19U)
#define DAC_CTRL_T2SEL_Msk						(0x7UL << DAC_CTRL_T2SEL_Pos)
#define DAC_CTRL_T2SEL							DAC_CTRL_T2SEL_Msk				/*!< TSEL2[2:0] (DAC channel2 Trigger selection) */
#define DAC_CTRL_T2SEL_0						((uint32_t) 0x00080000)			/*!< Bit 0 */
#define DAC_CTRL_T2SEL_1						((uint32_t) 0x00100000)			/*!< Bit 1 */
#define DAC_CTRL_T2SEL_2						((uint32_t) 0x00200000)			/*!< Bit 2 */
#define DAC_CTRL_W2EN_Pos						(22U)
#define DAC_CTRL_W2EN_Msk						(0x3UL << DAC_CTRL_W2EN_Pos)
#define DAC_CTRL_W2EN							DAC_CTRL_W2EN_Msk				/*!< WAVE2[1:0] (DAC channel2 noise/triangle wave generation enable) */
#define DAC_CTRL_W2EN_0							((uint32_t) 0x00400000)			/*!< Bit 0 */
#define DAC_CTRL_W2EN_1							((uint32_t) 0x00800000)			/*!< Bit 1 */
#define DAC_CTRL_MA2SEL_Pos						(24U)
#define DAC_CTRL_MA2SEL_Msk						(0xFUL << DAC_CTRL_MA2SEL_Pos)
#define DAC_CTRL_MA2SEL							DAC_CTRL_MA2SEL_Msk				/*!< MAMP2[3:0] (DAC channel2 Mask/Amplitude selector) */
#define DAC_CTRL_MA2SEL_0						((uint32_t) 0x01000000)			/*!< Bit 0 */
#define DAC_CTRL_MA2SEL_1						((uint32_t) 0x02000000)			/*!< Bit 1 */
#define DAC_CTRL_MA2SEL_2						((uint32_t) 0x04000000)			/*!< Bit 2 */
#define DAC_CTRL_MA2SEL_3						((uint32_t) 0x08000000)			/*!< Bit 3 */
#define DAC_CTRL_DMA2EN_Pos						(28U)
#define DAC_CTRL_DMA2EN_Msk						(0x1UL << DAC_CTRL_DMA2EN_Pos)
#define DAC_CTRL_DMA2EN							DAC_CTRL_DMA2EN_Msk				/*!< DAC channel2 DMA enabled */

/******************  Bit definition for DAC_SOTTR register  *******************/
#define DAC_SOTTR_TR1EN_Pos						(0U)
#define DAC_SOTTR_TR1EN_Msk						(0x1UL << DAC_SOTTR_TR1EN_Pos)
#define DAC_SOTTR_TR1EN							DAC_SOTTR_TR1EN_Msk				/*!< DAC channel1 software trigger */
#define DAC_SOTTR_TR2EN_Pos						(1U)
#define DAC_SOTTR_TR2EN_Msk						(0x1UL << DAC_SOTTR_TR2EN_Pos)
#define DAC_SOTTR_TR2EN							DAC_SOTTR_TR2EN_Msk				/*!< DAC channel2 software trigger */

/*****************  Bit definition for DAC_DR12CH1 register  ******************/
#define DAC_DR12CH1_DACCH1D_Pos					(0U)
#define DAC_DR12CH1_DACCH1D_Msk					(0xFFFUL << DAC_DR12CH1_DACCH1D_Pos)	/*!< 0x00000FFF */
#define DAC_DR12CH1_DACCH1D						DAC_DR12CH1_DACCH1D_Msk			/*!< DAC channel1 12-bit Right aligned data */

/*****************  Bit definition for DAC_DL12CH1 register  ******************/
#define DAC_DL12CH1_DACCH1D_Pos					(4U)
#define DAC_DL12CH1_DACCH1D_Msk					(0xFFFUL << DAC_DL12CH1_DACCH1D_Pos)	/*!< 0x0000FFF0 */
#define DAC_DL12CH1_DACCH1D						DAC_DL12CH1_DACCH1D_Msk			/*!< DAC channel1 12-bit Left aligned data */

/******************  Bit definition for DAC_DR8CH1 register  ******************/
#define DAC_DR8CH1_DACCH1D_Pos					(0U)
#define DAC_DR8CH1_DACCH1D_Msk					(0xFFUL << DAC_DR8CH1_DACCH1D_Pos)		/*!< 0x000000FF */
#define DAC_DR8CH1_DACCH1D						DAC_DR8CH1_DACCH1D_Msk			/*!< DAC channel1 8-bit Right aligned data */

/*****************  Bit definition for DAC_DR12CH2 register  ******************/
#define DAC_DR12CH2_DACCH2D_Pos					(0U)
#define DAC_DR12CH2_DACCH2D_Msk					(0xFFFUL << DAC_DHR12R2_DACCH2D_Pos)	/*!< 0x00000FFF */
#define DAC_DR12CH2_DACCH2D						DAC_DHR12R2_DACCH2D_Msk			/*!< DAC channel2 12-bit Right aligned data */

/*****************  Bit definition for DAC_DL12CH2 register  ******************/
#define DAC_DL12CH2_DACCH2D_Pos					(4U)
#define DAC_DL12CH2_DACCH2D_Msk					(0xFFFUL << DAC_DHR12L2_DACCH2D_Pos)	/*!< 0x0000FFF0 */
#define DAC_DL12CH2_DACCH2D						DAC_DHR12L2_DACCH2D_Msk			/*!< DAC channel2 12-bit Left aligned data */

/******************  Bit definition for DAC_DR8CH2 register  ******************/
#define DAC_DR8CH2_DACCH2D_Pos					(0U)
#define DAC_DR8CH2_DACCH2D_Msk					(0xFFUL << DAC_DHR8R2_DACCH2D_Pos)		/*!< 0x000000FF */
#define DAC_DR8CH2_DACCH2D						DAC_DHR8R2_DACCH2D_Msk			/*!< DAC channel2 8-bit Right aligned data */

/*****************  Bit definition for DAC_DR12DCH register  ******************/
#define DAC_DR12DCH_DACCH1D_Pos					(0U)
#define DAC_DR12DCH_DACCH1D_Msk					(0xFFFUL << DAC_DR12DCH_DACCH1D_Pos)	/*!< 0x00000FFF */
#define DAC_DR12DCH_DACCH1D						DAC_DR12DCH_DACCH1D_Msk			/*!< DAC channel1 12-bit Right aligned data */
#define DAC_DR12DCH_DACCH2D_Pos					(16U)
#define DAC_DR12DCH_DACCH2D_Msk					(0xFFFUL << DAC_DR12DCH_DACCH2D_Pos)	/*!< 0x0FFF0000 */
#define DAC_DR12DCH_DACCH2D						DAC_DR12DCH_DACCH2D_Msk			/*!< DAC channel2 12-bit Right aligned data */

/*****************  Bit definition for DAC_DL12DCH register  ******************/
#define DAC_DL12DCH_DACCH1D_Pos					(4U)
#define DAC_DL12DCH_DACCH1D_Msk					(0xFFFUL << DAC_DL12DCH_DACCH1D_Pos)	/*!< 0x0000FFF0 */
#define DAC_DL12DCH_DACCH1D						DAC_DL12DCH_DACCH1D_Msk			/*!< DAC channel1 12-bit Left aligned data */
#define DAC_DL12DCH_DACCH2D_Pos					(20U)
#define DAC_DL12DCH_DACCH2D_Msk					(0xFFFUL << DAC_DL12DCH_DACCH2D_Pos)	/*!< 0xFFF00000 */
#define DAC_DL12DCH_DACCH2D						DAC_DL12DCH_DACCH2D_Msk			/*!< DAC channel2 12-bit Left aligned data */

/******************  Bit definition for DAC_DR8DCH register  ******************/
#define DAC_DR8DCH_DACCH1D_Pos					(0U)
#define DAC_DR8DCH_DACCH1D_Msk					(0xFFUL << DAC_DR8DCH_DACCH1D_Pos)		/*!< 0x000000FF */
#define DAC_DR8DCH_DACCH1D						DAC_DR8DCH_DACCH1D_Msk			/*!< DAC channel1 8-bit Right aligned data */
#define DAC_DR8DCH_DACCH2D_Pos					(8U)
#define DAC_DR8DCH_DACCH2D_Msk					(0xFFUL << DAC_DR8DCH_DACCH2D_Pos)		/*!< 0x0000FF00 */
#define DAC_DR8DCH_DACCH2D						DAC_DR8DCH_DACCH2D_Msk			/*!< DAC channel2 8-bit Right aligned data */

/******************  Bit definition for DAC_DATO1 register  *******************/
#define DAC_DATO1_DACCH1D_Pos					(0U)
#define DAC_DATO1_DACCH1D_Msk					(0xFFFUL << DAC_DATO1_DACCH1D_Pos)		/*!< 0x00000FFF */
#define DAC_DATO1_DACCH1D						DAC_DATO1_DACCH1D_Msk			/*!< DAC channel1 data output */

/******************  Bit definition for DAC_DATO2 register  *******************/
#define DAC_DATO2_DACCH2D_Pos					(0U)
#define DAC_DATO2_DACCH2D_Msk					(0xFFFUL << DAC_DATO2_DACCH2D_Pos)		/*!< 0x00000FFF */
#define DAC_DATO2_DACCH2D						DAC_DATO2_DACCH2D_Msk			/*!< DAC channel2 data output */

/******************************************************************************/
/*                                                                            */
/*                                    TIM                                     */
/*                                                                            */
/******************************************************************************/
/******************  Bit definition for TIM_CTRL1 register  *******************/
#define TIM_CTRL1_CNTEN_Pos						(0U)
#define TIM_CTRL1_CNTEN_Msk						(0x1UL << TIM_CTRL1_CNTEN_Pos)
#define TIM_CTRL1_CNTEN							TIM_CTRL1_CNTEN_Msk				/*!< Counter enable */
#define TIM_CTRL1_UPDIS_Pos						(1U)
#define TIM_CTRL1_UPDIS_Msk						(0x1UL << TIM_CTRL1_UPDIS_Pos)
#define TIM_CTRL1_UPDIS							TIM_CTRL1_UPDIS_Msk				/*!< Update disable */
#define TIM_CTRL1_UPRS_Pos						(2U)
#define TIM_CTRL1_UPRS_Msk						(0x1UL << TIM_CTRL1_UPRS_Pos)
#define TIM_CTRL1_UPRS							TIM_CTRL1_UPRS_Msk				/*!< Update request source */
#define TIM_CTRL1_ONEPM_Pos						(3U)
#define TIM_CTRL1_ONEPM_Msk						(0x1UL << TIM_CTRL1_ONEPM_Pos)
#define TIM_CTRL1_ONEPM							TIM_CTRL1_ONEPM_Msk				/*!< One pulse mode */
#define TIM_CTRL1_DIR_Pos						(4U)
#define TIM_CTRL1_DIR_Msk						(0x1UL << TIM_CTRL1_DIR_Pos)
#define TIM_CTRL1_DIR							TIM_CTRL1_DIR_Msk				/*!< Direction */
#define TIM_CTRL1_CAMSEL_Pos					(5U)
#define TIM_CTRL1_CAMSEL_Msk					(0x3UL << TIM_CTRL1_CAMSEL_Pos)
#define TIM_CTRL1_CAMSEL						TIM_CTRL1_CAMSEL_Msk			/*!< CMS[1:0] bits (Center-aligned mode selection) */
#define TIM_CTRL1_CAMSEL_0						((uint32_t) 0x00000020)			/*!< Bit 0 */
#define TIM_CTRL1_CAMSEL_1						((uint32_t) 0x00000040)			/*!< Bit 1 */
#define TIM_CTRL1_ARPEN_Pos						(7U)
#define TIM_CTRL1_ARPEN_Msk						(0x1UL << TIM_CTRL1_ARPEN_Pos)
#define TIM_CTRL1_ARPEN							TIM_CTRL1_ARPEN_Msk				/*!< Auto-reload preload enable */
#define TIM_CTRL1_CLKD_Pos						(8U)
#define TIM_CTRL1_CLKD_Msk						(0x3UL << TIM_CTRL1_CLKD_Pos)
#define TIM_CTRL1_CLKD							TIM_CTRL1_CLKD_Msk				/*!< CKD[1:0] bits (clock division) */
#define TIM_CTRL1_CLKD_0						((uint32_t) 0x00000100)			/*!< Bit 0 */
#define TIM_CTRL1_CLKD_1						((uint32_t) 0x00000200)			/*!< Bit 1 */
#define TIM_CTRL1_IOMBKPEN_Pos					(10U)
#define TIM_CTRL1_IOMBKPEN_Msk					(0x1UL << TIM_CTRL1_IOMBKPEN_Pos)
#define TIM_CTRL1_IOMBKPEN						TIM_CTRL1_IOMBKPEN_Msk			/*!< Break_in selection from IOM/COMP */
#define TIM_CTRL1_C1SEL_Pos						(11U)
#define TIM_CTRL1_C1SEL_Msk						(0x1UL << TIM_CTRL1_C1SEL_Pos)
#define TIM_CTRL1_C1SEL							TIM_CTRL1_C1SEL_Msk				/*!< Channel 1 selection from IOM/COMP */
#define TIM_CTRL1_C2SEL_Pos						(12U)
#define TIM_CTRL1_C2SEL_Msk						(0x1UL << TIM_CTRL1_C2SEL_Pos)
#define TIM_CTRL1_C2SEL							TIM_CTRL1_C2SEL_Msk				/*!< Channel 2 selection from IOM/COMP */
#define TIM_CTRL1_C3SEL_Pos						(13U)
#define TIM_CTRL1_C3SEL_Msk						(0x1UL << TIM_CTRL1_C3SEL_Pos)
#define TIM_CTRL1_C3SEL							TIM_CTRL1_C3SEL_Msk				/*!< Channel 3 selection from IOM/COMP */
#define TIM_CTRL1_C4SEL_Pos						(14U)
#define TIM_CTRL1_C4SEL_Msk						(0x1UL << TIM_CTRL1_C4SEL_Pos)
#define TIM_CTRL1_C4SEL							TIM_CTRL1_C4SEL_Msk				/*!< Channel 4 selection from IOM/COMP */
#define TIM_CTRL1_CLRSEL_Pos					(15U)
#define TIM_CTRL1_CLRSEL_Msk					(0x1UL << TIM_CTRL1_CLRSEL_Pos)
#define TIM_CTRL1_CLRSEL						TIM_CTRL1_CLRSEL_Msk			/*!< OCxRef selection from ETR/COMP */
#define TIM_CTRL1_LOCKUPEN_Pos					(16U)
#define TIM_CTRL1_LOCKUPEN_Msk					(0x1UL << TIM_CTRL1_LOCKUPEN_Pos)
#define TIM_CTRL1_LOCKUPEN						TIM_CTRL1_LOCKUPEN_Msk			/*!< LOCKUP as bkp Enable*/
#define TIM_CTRL1_PBKPEN_Pos					(17U)
#define TIM_CTRL1_PBKPEN_Msk					(0x1UL << TIM_CTRL1_PBKPEN_Pos)
#define TIM_CTRL1_PBKPEN						TIM_CTRL1_PBKPEN_Msk			/*!< PVD as bkp Enable */

/******************  Bit definition for TIM_CTRL2 register  *******************/
#define TIM_CTRL2_CCPCTL_Pos					(0U)
#define TIM_CTRL2_CCPCTL_Msk					(0x1UL << TIM_CTRL2_CCPCTL_Pos)
#define TIM_CTRL2_CCPCTL						TIM_CTRL2_CCPCTL_Msk			/*!< Capture/Compare Preloaded Control */
#define TIM_CTRL2_CCUSEL_Pos					(2U)
#define TIM_CTRL2_CCUSEL_Msk					(0x1UL << TIM_CTRL2_CCUSEL_Pos)
#define TIM_CTRL2_CCUSEL						TIM_CTRL2_CCUSEL_Msk			/*!< Capture/Compare Control Update Selection */
#define TIM_CTRL2_CCDSEL_Pos					(3U)
#define TIM_CTRL2_CCDSEL_Msk					(0x1UL << TIM_CTRL2_CCDSEL_Pos)
#define TIM_CTRL2_CCDSEL						TIM_CTRL2_CCDSEL_Msk			/*!< Capture/Compare DMA Selection */
#define TIM_CTRL2_MMSEL_Pos						(4U)
#define TIM_CTRL2_MMSEL_Msk						(0x7UL << TIM_CTRL2_MMSEL_Pos)
#define TIM_CTRL2_MMSEL							TIM_CTRL2_MMSEL_Msk				/*!< MMS[2:0] bits (Master Mode Selection) */
#define TIM_CTRL2_MMSEL_0						((uint32_t) 0x00000010)			/*!< Bit 0 */
#define TIM_CTRL2_MMSEL_1						((uint32_t) 0x00000020)			/*!< Bit 1 */
#define TIM_CTRL2_MMSEL_2						((uint32_t) 0x00000040)			/*!< Bit 2 */
#define TIM_CTRL2_TI1SEL_Pos					(7U)
#define TIM_CTRL2_TI1SEL_Msk					(0x1UL << TIM_CTRL2_TI1SEL_Pos)
#define TIM_CTRL2_TI1SEL						TIM_CTRL2_TI1SEL_Msk			/*!< TI1 Selection */
#define TIM_CTRL2_OI1_Pos						(8U)
#define TIM_CTRL2_OI1_Msk						(0x1UL << TIM_CTRL2_OI1_Pos)
#define TIM_CTRL2_OI1							TIM_CTRL2_OI1_Msk				/*!< Output Idle state 1 (OC1 output) */
#define TIM_CTRL2_OI1N_Pos						(9U)
#define TIM_CTRL2_OI1N_Msk						(0x1UL << TIM_CTRL2_OI1N_Pos)
#define TIM_CTRL2_OI1N							TIM_CTRL2_OI1N_Msk				/*!< Output Idle state 1 (OC1N output) */
#define TIM_CTRL2_OI2_Pos						(10U)
#define TIM_CTRL2_OI2_Msk						(0x1UL << TIM_CTRL2_OI2_Pos)
#define TIM_CTRL2_OI2							TIM_CTRL2_OI2_Msk				/*!< Output Idle state 2 (OC2 output) */
#define TIM_CTRL2_OI2N_Pos						(11U)
#define TIM_CTRL2_OI2N_Msk						(0x1UL << TIM_CTRL2_OI2N_Pos)
#define TIM_CTRL2_OI2N							TIM_CTRL2_OI2N_Msk				/*!< Output Idle state 2 (OC2N output) */
#define TIM_CTRL2_OI3_Pos						(12U)
#define TIM_CTRL2_OI3_Msk						(0x1UL << TIM_CTRL2_OI3_Pos)
#define TIM_CTRL2_OI3							TIM_CTRL2_OI3_Msk				/*!< Output Idle state 3 (OC3 output) */
#define TIM_CTRL2_OI3N_Pos						(13U)
#define TIM_CTRL2_OI3N_Msk						(0x1UL << TIM_CTRL2_OI3N_Pos)
#define TIM_CTRL2_OI3N							TIM_CTRL2_OI3N_Msk				/*!< Output Idle state 3 (OC3N output) */
#define TIM_CTRL2_OI4_Pos						(14U)
#define TIM_CTRL2_OI4_Msk						(0x1UL << TIM_CTRL2_OI4_Pos)
#define TIM_CTRL2_OI4							TIM_CTRL2_OI4_Msk				/*!< Output Idle state 4 (OC4 output) */
#define TIM_CTRL2_OI5_Pos						(16U)
#define TIM_CTRL2_OI5_Msk						(0x1UL << TIM_CTRL2_OI5_Pos)
#define TIM_CTRL2_OI5							TIM_CTRL2_OI5_Msk				/*!< Output Idle state 5 (OC5 output) */
#define TIM_CTRL2_OI6_Pos						(18U)
#define TIM_CTRL2_OI6_Msk						(0x1UL << TIM_CTRL2_OI6_Pos)
#define TIM_CTRL2_OI6							TIM_CTRL2_OI6_Msk				/*!< Output Idle state 6 (OC6 output) */

/******************  Bit definition for TIM_SMCTRL register  ******************/
#define TIM_SMCTRL_SMSEL_Pos					(0U)
#define TIM_SMCTRL_SMSEL_Msk					(0x7UL << TIM_SMCTRL_SMSEL_Pos)
#define TIM_SMCTRL_SMSEL						TIM_SMCTRL_SMSEL_Msk			/*!< SMS[2:0] bits (Slave mode selection) */
#define TIM_SMCTRL_SMSEL_0						((uint16_t) 0x0001)				/*!< Bit 0 */
#define TIM_SMCTRL_SMSEL_1						((uint16_t) 0x0002)				/*!< Bit 1 */
#define TIM_SMCTRL_SMSEL_2						((uint16_t) 0x0004)				/*!< Bit 2 */
#define TIM_SMCTRL_TSEL_Pos						(4U)
#define TIM_SMCTRL_TSEL_Msk						(0x7UL << TIM_SMCTRL_TSEL_Pos)
#define TIM_SMCTRL_TSEL							TIM_SMCTRL_TSEL_Msk				/*!< TS[2:0] bits (Trigger selection) */
#define TIM_SMCTRL_TSEL_0						((uint16_t) 0x0010)				/*!< Bit 0 */
#define TIM_SMCTRL_TSEL_1						((uint16_t) 0x0020)				/*!< Bit 1 */
#define TIM_SMCTRL_TSEL_2						((uint16_t) 0x0040)				/*!< Bit 2 */
#define TIM_SMCTRL_MSMD_Pos						(7U)
#define TIM_SMCTRL_MSMD_Msk						(0x1UL << TIM_SMCTRL_MSMD_Pos)
#define TIM_SMCTRL_MSMD							TIM_SMCTRL_MSMD_Msk				/*!< Master/slave mode */
#define TIM_SMCTRL_EXTF_Pos						(8U)
#define TIM_SMCTRL_EXTF_Msk						(0xFUL << TIM_SMCTRL_EXTF_Pos)
#define TIM_SMCTRL_EXTF							TIM_SMCTRL_EXTF_Msk				/*!< ETF[3:0] bits (External trigger filter) */
#define TIM_SMCTRL_EXTF_0						((uint16_t) 0x0100)				/*!< Bit 0 */
#define TIM_SMCTRL_EXTF_1						((uint16_t) 0x0200)				/*!< Bit 1 */
#define TIM_SMCTRL_EXTF_2						((uint16_t) 0x0400)				/*!< Bit 2 */
#define TIM_SMCTRL_EXTF_3						((uint16_t) 0x0800)				/*!< Bit 3 */
#define TIM_SMCTRL_EXTPS_Pos					(12U)
#define TIM_SMCTRL_EXTPS_Msk					(0x3UL << TIM_SMCTRL_EXTPS_Pos)
#define TIM_SMCTRL_EXTPS						TIM_SMCTRL_EXTPS_Msk			/*!< ETPS[1:0] bits (External trigger prescaler) */
#define TIM_SMCTRL_EXTPS_0						((uint16_t) 0x1000)				/*!< Bit 0 */
#define TIM_SMCTRL_EXTPS_1						((uint16_t) 0x2000)				/*!< Bit 1 */
#define TIM_SMCTRL_EXCEN_Pos					(14U)
#define TIM_SMCTRL_EXCEN_Msk					(0x1UL << TIM_SMCTRL_EXCEN_Pos)
#define TIM_SMCTRL_EXCEN						TIM_SMCTRL_EXCEN_Msk			/*!< External clock enable */
#define TIM_SMCTRL_EXTP_Pos						(15U)
#define TIM_SMCTRL_EXTP_Msk						(0x1UL << TIM_SMCTRL_EXTP_Pos)
#define TIM_SMCTRL_EXTP							TIM_SMCTRL_EXTP_Msk				/*!< External trigger polarity */

/******************  Bit definition for TIM_DINTEN register  ******************/
#define TIM_DINTEN_UIEN_Pos						(0U)
#define TIM_DINTEN_UIEN_Msk						(0x1UL << TIM_DINTEN_UIEN_Pos)
#define TIM_DINTEN_UIEN							TIM_DINTEN_UIEN_Msk				/*!< Update interrupt enable */
#define TIM_DINTEN_CC1IEN_Pos					(1U)
#define TIM_DINTEN_CC1IEN_Msk					(0x1UL << TIM_DINTEN_CC1IEN_Pos)
#define TIM_DINTEN_CC1IEN						TIM_DINTEN_CC1IEN_Msk			/*!< Capture/Compare 1 interrupt enable */
#define TIM_DINTEN_CC2IEN_Pos					(2U)
#define TIM_DINTEN_CC2IEN_Msk					(0x1UL << TIM_DINTEN_CC2IEN_Pos)
#define TIM_DINTEN_CC2IEN						TIM_DINTEN_CC2IEN_Msk			/*!< Capture/Compare 2 interrupt enable */
#define TIM_DINTEN_CC3IEN_Pos					(3U)
#define TIM_DINTEN_CC3IEN_Msk					(0x1UL << TIM_DINTEN_CC3IEN_Pos)
#define TIM_DINTEN_CC3IEN						TIM_DINTEN_CC3IEN_Msk			/*!< Capture/Compare 3 interrupt enable */
#define TIM_DINTEN_CC4IEN_Pos					(4U)
#define TIM_DINTEN_CC4IEN_Msk					(0x1UL << TIM_DINTEN_CC4IEN_Pos)
#define TIM_DINTEN_CC4IEN						TIM_DINTEN_CC4IEN_Msk			/*!< Capture/Compare 4 interrupt enable */
#define TIM_DINTEN_COMIEN_Pos					(5U)
#define TIM_DINTEN_COMIEN_Msk					(0x1UL << TIM_DINTEN_COMIEN_Pos)
#define TIM_DINTEN_COMIEN						TIM_DINTEN_COMIEN_Msk			/*!< COM interrupt enable */
#define TIM_DINTEN_TIEN_Pos						(6U)
#define TIM_DINTEN_TIEN_Msk						(0x1UL << TIM_DINTEN_TIEN_Pos)
#define TIM_DINTEN_TIEN							TIM_DINTEN_TIEN_Msk				/*!< Trigger interrupt enable */
#define TIM_DINTEN_BIEN_Pos						(7U)
#define TIM_DINTEN_BIEN_Msk						(0x1UL << TIM_DINTEN_BIEN_Pos)
#define TIM_DINTEN_BIEN							TIM_DINTEN_BIEN_Msk				/*!< Break interrupt enable */
#define TIM_DINTEN_UDEN_Pos						(8U)
#define TIM_DINTEN_UDEN_Msk						(0x1UL << TIM_DINTEN_UDEN_Pos)
#define TIM_DINTEN_UDEN							TIM_DINTEN_UDEN_Msk				/*!< Update DMA request enable */
#define TIM_DINTEN_CC1DEN_Pos					(9U)
#define TIM_DINTEN_CC1DEN_Msk					(0x1UL << TIM_DINTEN_CC1DEN_Pos)
#define TIM_DINTEN_CC1DEN						TIM_DINTEN_CC1DEN_Msk			/*!< Capture/Compare 1 DMA request enable */
#define TIM_DINTEN_CC2DEN_Pos					(10U)
#define TIM_DINTEN_CC2DEN_Msk					(0x1UL << TIM_DINTEN_CC2DEN_Pos)
#define TIM_DINTEN_CC2DEN						TIM_DINTEN_CC2DEN_Msk			/*!< Capture/Compare 2 DMA request enable */
#define TIM_DINTEN_CC3DEN_Pos					(11U)
#define TIM_DINTEN_CC3DEN_Msk					(0x1UL << TIM_DINTEN_CC3DEN_Pos)
#define TIM_DINTEN_CC3DEN						TIM_DINTEN_CC3DEN_Msk			/*!< Capture/Compare 3 DMA request enable */
#define TIM_DINTEN_CC4DEN_Pos					(12U)
#define TIM_DINTEN_CC4DEN_Msk					(0x1UL << TIM_DINTEN_CC4DEN_Pos)
#define TIM_DINTEN_CC4DEN						TIM_DINTEN_CC4DEN_Msk			/*!< Capture/Compare 4 DMA request enable */
#define TIM_DINTEN_COMDEN_Pos					(13U)
#define TIM_DINTEN_COMDEN_Msk					(0x1UL << TIM_DINTEN_COMDEN_Pos)
#define TIM_DINTEN_COMDEN						TIM_DINTEN_COMDEN_Msk			/*!< COM DMA request enable */
#define TIM_DINTEN_TDEN_Pos						(14U)
#define TIM_DINTEN_TDEN_Msk						(0x1UL << TIM_DINTEN_TDEN_Pos)
#define TIM_DINTEN_TDEN							TIM_DINTEN_TDEN_Msk				/*!< Trigger DMA request enable */

/*******************  Bit definition for TIM_STS register  ********************/
#define TIM_STS_UDITF_Pos						(0U)
#define TIM_STS_UDITF_Msk						(0x1UL << TIM_STS_UDITF_Pos)
#define TIM_STS_UDITF							TIM_STS_UDITF_Msk				/*!< Update interrupt Flag */
#define TIM_STS_CC1ITF_Pos						(1U)
#define TIM_STS_CC1ITF_Msk						(0x1UL << TIM_STS_CC1ITF_Pos)
#define TIM_STS_CC1ITF							TIM_STS_CC1ITF_Msk				/*!< Capture/Compare 1 interrupt Flag */
#define TIM_STS_CC2ITF_Pos						(2U)
#define TIM_STS_CC2ITF_Msk						(0x1UL << TIM_STS_CC2ITF_Pos)
#define TIM_STS_CC2ITF							TIM_STS_CC2ITF_Msk				/*!< Capture/Compare 2 interrupt Flag */
#define TIM_STS_CC3ITF_Pos						(3U)
#define TIM_STS_CC3ITF_Msk						(0x1UL << TIM_STS_CC3ITF_Pos)
#define TIM_STS_CC3ITF							TIM_STS_CC3ITF_Msk				/*!< Capture/Compare 3 interrupt Flag */
#define TIM_STS_CC4ITF_Pos						(4U)
#define TIM_STS_CC4ITF_Msk						(0x1UL << TIM_STS_CC4ITF_Pos)
#define TIM_STS_CC4ITF							TIM_STS_CC4ITF_Msk				/*!< Capture/Compare 4 interrupt Flag */
#define TIM_STS_COMITF_Pos						(5U)
#define TIM_STS_COMITF_Msk						(0x1UL << TIM_STS_COMITF_Pos)
#define TIM_STS_COMITF							TIM_STS_COMITF_Msk				/*!< COM interrupt Flag */
#define TIM_STS_TITF_Pos						(6U)
#define TIM_STS_TITF_Msk						(0x1UL << TIM_STS_TITF_Pos)
#define TIM_STS_TITF							TIM_STS_TITF_Msk				/*!< Trigger interrupt Flag */
#define TIM_STS_BITF_Pos						(7U)
#define TIM_STS_BITF_Msk						(0x1UL << TIM_STS_BITF_Pos)
#define TIM_STS_BITF							TIM_STS_BITF_Msk				/*!< Break interrupt Flag */
#define TIM_STS_CC1OCF_Pos						(9U)
#define TIM_STS_CC1OCF_Msk						(0x1UL << TIM_STS_CC1OCF_Pos)
#define TIM_STS_CC1OCF							TIM_STS_CC1OCF_Msk				/*!< Capture/Compare 1 Overcapture Flag */
#define TIM_STS_CC2OCF_Pos						(10U)
#define TIM_STS_CC2OCF_Msk						(0x1UL << TIM_STS_CC2OCF_Pos)
#define TIM_STS_CC2OCF							TIM_STS_CC2OCF_Msk				/*!< Capture/Compare 2 Overcapture Flag */
#define TIM_STS_CC3OCF_Pos						(11U)
#define TIM_STS_CC3OCF_Msk						(0x1UL << TIM_STS_CC3OCF_Pos)
#define TIM_STS_CC3OCF							TIM_STS_CC3OCF_Msk				/*!< Capture/Compare 3 Overcapture Flag */
#define TIM_STS_CC4OCF_Pos						(12U)
#define TIM_STS_CC4OCF_Msk						(0x1UL << TIM_STS_CC4OCF_Pos)
#define TIM_STS_CC4OCF							TIM_STS_CC4OCF_Msk				/*!< Capture/Compare 4 Overcapture Flag */
#define TIM_STS_CC5ITF_Pos						(16U)
#define TIM_STS_CC5ITF_Msk						(0x1UL << TIM_STS_CC5ITF_Pos)
#define TIM_STS_CC5ITF							TIM_STS_CC5ITF_Msk				/*!< Capture/Compare 5 interrupt Flag */
#define TIM_STS_CC6ITF_Pos						(17U)
#define TIM_STS_CC6ITF_Msk						(0x1UL << TIM_STS_CC6ITF_Pos)
#define TIM_STS_CC6ITF							TIM_STS_CC6ITF_Msk				/*!< Capture/Compare 6 interrupt Flag */

/******************  Bit definition for TIM_EVTGEN register  ******************/
#define TIM_EVTGEN_UDGN_Pos						(0U)
#define TIM_EVTGEN_UDGN_Msk						(0x1UL << TIM_EVTGEN_UDGN_Pos)
#define TIM_EVTGEN_UDGN							TIM_EVTGEN_UDGN_Msk				/*!< Update Generation */
#define TIM_EVTGEN_CC1GN_Pos					(1U)
#define TIM_EVTGEN_CC1GN_Msk					(0x1UL << TIM_EVTGEN_CC1GN_Pos)
#define TIM_EVTGEN_CC1GN						TIM_EVTGEN_CC1GN_Msk			/*!< Capture/Compare 1 Generation */
#define TIM_EVTGEN_CC2GN_Pos					(2U)
#define TIM_EVTGEN_CC2GN_Msk					(0x1UL << TIM_EVTGEN_CC2GN_Pos)
#define TIM_EVTGEN_CC2GN						TIM_EVTGEN_CC2GN_Msk			/*!< Capture/Compare 2 Generation */
#define TIM_EVTGEN_CC3GN_Pos					(3U)
#define TIM_EVTGEN_CC3GN_Msk					(0x1UL << TIM_EVTGEN_CC3GN_Pos)
#define TIM_EVTGEN_CC3GN						TIM_EVTGEN_CC3GN_Msk			/*!< Capture/Compare 3 Generation */
#define TIM_EVTGEN_CC4GN_Pos					(4U)
#define TIM_EVTGEN_CC4GN_Msk					(0x1UL << TIM_EVTGEN_CC4GN_Pos)
#define TIM_EVTGEN_CC4GN						TIM_EVTGEN_CC4GN_Msk			/*!< Capture/Compare 4 Generation */
#define TIM_EVTGEN_CCUDGN_Pos					(5U)
#define TIM_EVTGEN_CCUDGN_Msk					(0x1UL << TIM_EVTGEN_CCUDGN_Pos)
#define TIM_EVTGEN_CCUDGN						TIM_EVTGEN_CCUDGN_Msk			/*!< Capture/Compare Control Update Generation */
#define TIM_EVTGEN_TGN_Pos						(6U)
#define TIM_EVTGEN_TGN_Msk						(0x1UL << TIM_EVTGEN_TGN_Pos)
#define TIM_EVTGEN_TGN							TIM_EVTGEN_TGN_Msk				/*!< Trigger Generation */
#define TIM_EVTGEN_BGN_Pos						(7U)
#define TIM_EVTGEN_BGN_Msk						(0x1UL << TIM_EVTGEN_BGN_Pos)
#define TIM_EVTGEN_BGN							TIM_EVTGEN_BGN_Msk				/*!< Break Generation */

/******************  Bit definition for TIM_CCMOD1 register  ******************/
/*------------------------- Output compare mode ------------------------------*/
#define TIM_CCMOD1_CC1SEL_Pos					(0U)
#define TIM_CCMOD1_CC1SEL_Msk					(0x3UL << TIM_CCMOD1_CC1SEL_Pos)
#define TIM_CCMOD1_CC1SEL						TIM_CCMOD1_CC1SEL_Msk			/*!< CC1S[1:0] bits (Capture/Compare 1 Selection) */
#define TIM_CCMOD1_CC1SEL_0						((uint16_t) 0x0001)				/*!< Bit 0 */
#define TIM_CCMOD1_CC1SEL_1						((uint16_t) 0x0002)				/*!< Bit 1 */

#define TIM_CCMOD1_OC1FEN_Pos					(2U)
#define TIM_CCMOD1_OC1FEN_Msk					(0x1UL << TIM_CCMOD1_OC1FEN_Pos)
#define TIM_CCMOD1_OC1FEN						TIM_CCMOD1_OC1FEN_Msk			/*!< Output Compare 1 Fast enable */
#define TIM_CCMOD1_OC1PEN_Pos					(3U)
#define TIM_CCMOD1_OC1PEN_Msk					(0x1UL << TIM_CCMOD1_OC1PEN_Pos)
#define TIM_CCMOD1_OC1PEN						TIM_CCMOD1_OC1PEN_Msk			/*!< Output Compare 1 Preload enable */
#define TIM_CCMOD1_OC1MD_Pos					(4U)
#define TIM_CCMOD1_OC1MD_Msk					(0x7UL << TIM_CCMOD1_OC1MD_Pos)
#define TIM_CCMOD1_OC1MD						TIM_CCMOD1_OC1MD_Msk				/*!< OC1M[2:0] bits (Output Compare 1 Mode) */
#define TIM_CCMOD1_OC1MD_0						((uint16_t) 0x0010)				/*!< Bit 0 */
#define TIM_CCMOD1_OC1MD_1						((uint16_t) 0x0020)				/*!< Bit 1 */
#define TIM_CCMOD1_OC1MD_2						((uint16_t) 0x0040)				/*!< Bit 2 */
#define TIM_CCMOD1_OC1CEN_Pos					(7U)
#define TIM_CCMOD1_OC1CEN_Msk					(0x1UL << TIM_CCMOD1_OC1CEN_Pos)
#define TIM_CCMOD1_OC1CEN						TIM_CCMOD1_OC1CEN_Msk			/*!< Output Compare 1Clear Enable */

#define TIM_CCMOD1_CC2SEL_Pos					(8U)
#define TIM_CCMOD1_CC2SEL_Msk					(0x3UL << TIM_CCMOD1_CC2SEL_Pos)
#define TIM_CCMOD1_CC2SEL						TIM_CCMOD1_CC2SEL_Msk			/*!< CC2S[1:0] bits (Capture/Compare 2 Selection) */
#define TIM_CCMOD1_CC2SEL_0						((uint16_t) 0x0100)				/*!< Bit 0 */
#define TIM_CCMOD1_CC2SEL_1						((uint16_t) 0x0200)				/*!< Bit 1 */

#define TIM_CCMOD1_OC2FEN_Pos					(10U)
#define TIM_CCMOD1_OC2FEN_Msk					(0x1UL << TIM_CCMOD1_OC2FEN_Pos)
#define TIM_CCMOD1_OC2FEN						TIM_CCMOD1_OC2FEN_Msk			/*!< Output Compare 2 Fast enable */
#define TIM_CCMOD1_OC2PEN_Pos					(11U)
#define TIM_CCMOD1_OC2PEN_Msk					(0x1UL << TIM_CCMOD1_OC2PEN_Pos)
#define TIM_CCMOD1_OC2PEN						TIM_CCMOD1_OC2PEN_Msk			/*!< Output Compare 2 Preload enable */
#define TIM_CCMOD1_OC2MD_Pos					(12U)
#define TIM_CCMOD1_OC2MD_Msk					(0x7UL << TIM_CCMOD1_OC2MD_Pos)
#define TIM_CCMOD1_OC2MD						TIM_CCMOD1_OC2MD_Msk				/*!< OC2M[2:0] bits (Output Compare 2 Mode) */
#define TIM_CCMOD1_OC2MD_0						((uint16_t) 0x1000)				/*!< Bit 0 */
#define TIM_CCMOD1_OC2MD_1						((uint16_t) 0x2000)				/*!< Bit 1 */
#define TIM_CCMOD1_OC2MD_2						((uint16_t) 0x4000)				/*!< Bit 2 */
#define TIM_CCMOD1_OC2CEN_Pos					(15U)
#define TIM_CCMOD1_OC2CEN_Msk					(0x1UL << TIM_CCMOD1_OC2CEN_Pos)
#define TIM_CCMOD1_OC2CEN						TIM_CCMOD1_OC2CEN_Msk			/*!< Output Compare 2 Clear Enable */

/*---------------------------- Input capture mode ----------------------------*/
#define TIM_CCMOD1_IC1PSC_Pos					(2U)
#define TIM_CCMOD1_IC1PSC_Msk					(0x3UL << TIM_CCMOD1_IC1PSC_Pos)
#define TIM_CCMOD1_IC1PSC						TIM_CCMOD1_IC1PSC_Msk			/*!< IC1PSC[1:0] bits (Input Capture 1 Prescaler) */
#define TIM_CCMOD1_IC1PSC_0						((uint16_t) 0x0004)				/*!< Bit 0 */
#define TIM_CCMOD1_IC1PSC_1						((uint16_t) 0x0008)				/*!< Bit 1 */
#define TIM_CCMOD1_IC1F_Pos						(4U)
#define TIM_CCMOD1_IC1F_Msk						(0xFUL << TIM_CCMOD1_IC1F_Pos)
#define TIM_CCMOD1_IC1F							TIM_CCMOD1_IC1F_Msk				/*!< IC1F[3:0] bits (Input Capture 1 Filter) */
#define TIM_CCMOD1_IC1F_0						((uint16_t) 0x0010)				/*!< Bit 0 */
#define TIM_CCMOD1_IC1F_1						((uint16_t) 0x0020)				/*!< Bit 1 */
#define TIM_CCMOD1_IC1F_2						((uint16_t) 0x0040)				/*!< Bit 2 */
#define TIM_CCMOD1_IC1F_3						((uint16_t) 0x0080)				/*!< Bit 3 */
#define TIM_CCMOD1_IC2PSC_Pos					(10U)
#define TIM_CCMOD1_IC2PSC_Msk					(0x3UL << TIM_CCMOD1_IC2PSC_Pos)
#define TIM_CCMOD1_IC2PSC						TIM_CCMOD1_IC2PSC_Msk			/*!< IC2PSC[1:0] bits (Input Capture 2 Prescaler) */
#define TIM_CCMOD1_IC2PSC_0						((uint16_t) 0x0400)				/*!< Bit 0 */
#define TIM_CCMOD1_IC2PSC_1						((uint16_t) 0x0800)				/*!< Bit 1 */
#define TIM_CCMOD1_IC2F_Pos						(12U)
#define TIM_CCMOD1_IC2F_Msk						(0xFUL << TIM_CCMOD1_IC2F_Pos)
#define TIM_CCMOD1_IC2F							TIM_CCMOD1_IC2F_Msk				/*!< IC2F[3:0] bits (Input Capture 2 Filter) */
#define TIM_CCMOD1_IC2F_0						((uint16_t) 0x1000)				/*!< Bit 0 */
#define TIM_CCMOD1_IC2F_1						((uint16_t) 0x2000)				/*!< Bit 1 */
#define TIM_CCMOD1_IC2F_2						((uint16_t) 0x4000)				/*!< Bit 2 */
#define TIM_CCMOD1_IC2F_3						((uint16_t) 0x8000)				/*!< Bit 3 */

/******************  Bit definition for TIM_CCMOD2 register  ******************/
/*--------------------------- Output compare mode ----------------------------*/
#define TIM_CCMOD2_CC3SEL_Pos					(0U)
#define TIM_CCMOD2_CC3SEL_Msk					(0x3UL << TIM_CCMOD2_CC3SEL_Pos)
#define TIM_CCMOD2_CC3SEL						TIM_CCMOD2_CC3SEL_Msk			/*!< CC3S[1:0] bits (Capture/Compare 3 Selection) */
#define TIM_CCMOD2_CC3SEL_0						((uint16_t) 0x0001)				/*!< Bit 0 */
#define TIM_CCMOD2_CC3SEL_1						((uint16_t) 0x0002)				/*!< Bit 1 */
#define TIM_CCMOD2_OC3FEN_Pos					(2U)
#define TIM_CCMOD2_OC3FEN_Msk					(0x1UL << TIM_CCMOD2_OC3FEN_Pos)
#define TIM_CCMOD2_OC3FEN						TIM_CCMOD2_OC3FEN_Msk			/*!< Output Compare 3 Fast enable */
#define TIM_CCMOD2_OC3PEN_Pos					(3U)
#define TIM_CCMOD2_OC3PEN_Msk					(0x1UL << TIM_CCMOD2_OC3PEN_Pos)
#define TIM_CCMOD2_OC3PEN						TIM_CCMOD2_OC3PEN_Msk			/*!< Output Compare 3 Preload enable */
#define TIM_CCMOD2_OC3MD_Pos					(4U)
#define TIM_CCMOD2_OC3MD_Msk					(0x7UL << TIM_CCMOD2_OC3MD_Pos)
#define TIM_CCMOD2_OC3MD						TIM_CCMOD2_OC3MD_Msk			/*!< OC3M[2:0] bits (Output Compare 3 Mode) */
#define TIM_CCMOD2_OC3MD_0						((uint16_t) 0x0010)				/*!< Bit 0 */
#define TIM_CCMOD2_OC3MD_1						((uint16_t) 0x0020)				/*!< Bit 1 */
#define TIM_CCMOD2_OC3MD_2						((uint16_t) 0x0040)				/*!< Bit 2 */
#define TIM_CCMOD2_OC3CEN_Pos					(7U)
#define TIM_CCMOD2_OC3CEN_Msk					(0x1UL << TIM_CCMOD2_OC3CEN_Pos)
#define TIM_CCMOD2_OC3CEN						TIM_CCMOD2_OC3CEN_Msk			/*!< Output Compare 3 Clear Enable */
#define TIM_CCMOD2_CC4SEL_Pos					(8U)
#define TIM_CCMOD2_CC4SEL_Msk					(0x3UL << TIM_CCMOD2_CC4SEL_Pos)
#define TIM_CCMOD2_CC4SEL						TIM_CCMOD2_CC4SEL_Msk			/*!< CC4S[1:0] bits (Capture/Compare 4 Selection) */
#define TIM_CCMOD2_CC4SEL_0						((uint16_t) 0x0100)				/*!< Bit 0 */
#define TIM_CCMOD2_CC4SEL_1						((uint16_t) 0x0200)				/*!< Bit 1 */
#define TIM_CCMOD2_OC4FEN_Pos					(10U)
#define TIM_CCMOD2_OC4FEN_Msk					(0x1UL << TIM_CCMOD2_OC4FEN_Pos)
#define TIM_CCMOD2_OC4FEN						TIM_CCMOD2_OC4FEN_Msk			/*!< Output Compare 4 Fast enable */
#define TIM_CCMOD2_OC4PEN_Pos					(11U)
#define TIM_CCMOD2_OC4PEN_Msk					(0x1UL << TIM_CCMOD2_OC4PEN_Pos)
#define TIM_CCMOD2_OC4PEN						TIM_CCMOD2_OC4PEN_Msk			/*!< Output Compare 4 Preload enable */
#define TIM_CCMOD2_OC4MD_Pos					(12U)
#define TIM_CCMOD2_OC4MD_Msk					(0x7UL << TIM_CCMOD2_OC4MD_Pos)
#define TIM_CCMOD2_OC4MD						TIM_CCMOD2_OC4MD_Msk			/*!< OC4M[2:0] bits (Output Compare 4 Mode) */
#define TIM_CCMOD2_OC4MD_0						((uint16_t) 0x1000)				/*!< Bit 0 */
#define TIM_CCMOD2_OC4MD_1						((uint16_t) 0x2000)				/*!< Bit 1 */
#define TIM_CCMOD2_OC4MD_2						((uint16_t) 0x4000)				/*!< Bit 2 */
#define TIM_CCMOD2_OC4CEN_Pos					(15U)
#define TIM_CCMOD2_OC4CEN_Msk					(0x1UL << TIM_CCMOD2_OC4CEN_Pos)
#define TIM_CCMOD2_OC4CEN						TIM_CCMOD2_OC4CEN_Msk			/*!< Output Compare 4 Clear Enable */

/*---------------------------- Input capture mode ----------------------------*/
#define TIM_CCMOD2_IC3PSC_Pos					(2U)
#define TIM_CCMOD2_IC3PSC_Msk					(0x3UL << TIM_CCMOD2_IC3PSC_Pos)
#define TIM_CCMOD2_IC3PSC						TIM_CCMOD2_IC3PSC_Msk			/*!< IC3PSC[1:0] bits (Input Capture 3 Prescaler) */
#define TIM_CCMOD2_IC3PSC_0						((uint16_t) 0x0004)				/*!< Bit 0 */
#define TIM_CCMOD2_IC3PSC_1						((uint16_t) 0x0008)				/*!< Bit 1 */
#define TIM_CCMOD2_IC3F_Pos						(4U)
#define TIM_CCMOD2_IC3F_Msk						(0xFUL << TIM_CCMOD2_IC3F_Pos)
#define TIM_CCMOD2_IC3F							TIM_CCMOD2_IC3F_Msk				/*!< IC3F[3:0] bits (Input Capture 3 Filter) */
#define TIM_CCMOD2_IC3F_0						((uint16_t) 0x0010)				/*!< Bit 0 */
#define TIM_CCMOD2_IC3F_1						((uint16_t) 0x0020)				/*!< Bit 1 */
#define TIM_CCMOD2_IC3F_2						((uint16_t) 0x0040)				/*!< Bit 2 */
#define TIM_CCMOD2_IC3F_3						((uint16_t) 0x0080)				/*!< Bit 3 */
#define TIM_CCMOD2_IC4PSC_Pos					(10U)
#define TIM_CCMOD2_IC4PSC_Msk					(0x3UL << TIM_CCMOD2_IC4PSC_Pos)
#define TIM_CCMOD2_IC4PSC						TIM_CCMOD2_IC4PSC_Msk			/*!< IC4PSC[1:0] bits (Input Capture 4 Prescaler) */
#define TIM_CCMOD2_IC4PSC_0						((uint16_t) 0x0400)				/*!< Bit 0 */
#define TIM_CCMOD2_IC4PSC_1						((uint16_t) 0x0800)				/*!< Bit 1 */
#define TIM_CCMOD2_IC4F_Pos						(12U)
#define TIM_CCMOD2_IC4F_Msk						(0xFUL << TIM_CCMOD2_IC4F_Pos)
#define TIM_CCMOD2_IC4F							TIM_CCMOD2_IC4F_Msk				/*!< IC4F[3:0] bits (Input Capture 4 Filter) */
#define TIM_CCMOD2_IC4F_0						((uint16_t) 0x1000)				/*!< Bit 0 */
#define TIM_CCMOD2_IC4F_1						((uint16_t) 0x2000)				/*!< Bit 1 */
#define TIM_CCMOD2_IC4F_2						((uint16_t) 0x4000)				/*!< Bit 2 */
#define TIM_CCMOD2_IC4F_3						((uint16_t) 0x8000)				/*!< Bit 3 */

/******************  Bit definition for TIM_CCMOD3 register  ******************/
#define TIM_CCMOD3_OC5FEN_Pos					(2U)
#define TIM_CCMOD3_OC5FEN_Msk					(0x1UL << TIM_CCMOD3_OC5FEN_Pos)
#define TIM_CCMOD3_OC5FEN						TIM_CCMOD3_OC5FEN_Msk			/*!< Output Compare 5 Fast enable */
#define TIM_CCMOD3_OC5PEN_Pos					(3U)
#define TIM_CCMOD3_OC5PEN_Msk					(0x1UL << TIM_CCMOD3_OC5PEN_Pos)
#define TIM_CCMOD3_OC5PEN						TIM_CCMOD3_OC5PEN_Msk			/*!< Output Compare 5 Preload enable */
#define TIM_CCMOD3_OC5MD_Pos					(4U)
#define TIM_CCMOD3_OC5MD_Msk					(0x7UL << TIM_CCMOD3_OC5MD_Pos)
#define TIM_CCMOD3_OC5MD						TIM_CCMOD3_OC5MD_Msk			/*!< OC5M[2:0] bits (Output Compare 5 Mode) */
#define TIM_CCMOD3_OC5MD_0						((uint16_t) 0x0010)				/*!< Bit 0 */
#define TIM_CCMOD3_OC5MD_1						((uint16_t) 0x0020)				/*!< Bit 1 */
#define TIM_CCMOD3_OC5MD_2						((uint16_t) 0x0040)				/*!< Bit 2 */
#define TIM_CCMOD3_OC5CEN_Pos					(7U)
#define TIM_CCMOD3_OC5CEN_Msk					(0x1UL << TIM_CCMOD3_OC5CEN_Pos)
#define TIM_CCMOD3_OC5CEN						TIM_CCMOD3_OC5CEN_Msk			/*!< Output Compare 5Clear Enable */
#define TIM_CCMOD3_OC6FEN_Pos					(10U)
#define TIM_CCMOD3_OC6FEN_Msk					(0x1UL << TIM_CCMOD3_OC6FEN_Pos)
#define TIM_CCMOD3_OC6FEN						TIM_CCMOD3_OC6FEN_Msk			/*!< Output Compare 6 Fast enable */
#define TIM_CCMOD3_OC6PEN_Pos					(11U)
#define TIM_CCMOD3_OC6PEN_Msk					(0x1UL << TIM_CCMOD3_OC6PEN_Pos)
#define TIM_CCMOD3_OC6PEN						TIM_CCMOD3_OC6PEN_Msk			/*!< Output Compare 6 Preload enable */
#define TIM_CCMOD3_OC6MD_Pos					(12U)
#define TIM_CCMOD3_OC6MD_Msk					(0x7UL << TIM_CCMOD3_OC6MD_Pos)
#define TIM_CCMOD3_OC6MD						TIM_CCMOD3_OC6MD_Msk			/*!< OC6M[2:0] bits (Output Compare 6 Mode) */
#define TIM_CCMOD3_OC6MD_0						((uint16_t) 0x1000)				/*!< Bit 0 */
#define TIM_CCMOD3_OC6MD_1						((uint16_t) 0x2000)				/*!< Bit 1 */
#define TIM_CCMOD3_OC6MD_2						((uint16_t) 0x4000)				/*!< Bit 2 */
#define TIM_CCMOD3_OC6CEN_Pos					(15U)
#define TIM_CCMOD3_OC6CEN_Msk					(0x1UL << TIM_CCMOD3_OC6CEN_Pos)
#define TIM_CCMOD3_OC6CEN						TIM_CCMOD3_OC6CEN_Msk			/*!< Output Compare 6 Clear Enable */

/*******************  Bit definition for TIM_CCEN register  *******************/
#define TIM_CCEN_CC1EN_Pos						(0U)
#define TIM_CCEN_CC1EN_Msk						(0x1UL << TIM_CCEN_CC1EN_Pos)
#define TIM_CCEN_CC1EN							TIM_CCEN_CC1EN_Msk				/*!< Capture/Compare 1 output enable */
#define TIM_CCEN_CC1P_Pos						(1U)
#define TIM_CCEN_CC1P_Msk						(0x1UL << TIM_CCEN_CC1P_Pos)
#define TIM_CCEN_CC1P							TIM_CCEN_CC1P_Msk				/*!< Capture/Compare 1 output Polarity */
#define TIM_CCEN_CC1NEN_Pos						(2U)
#define TIM_CCEN_CC1NEN_Msk						(0x1UL << TIM_CCEN_CC1NEN_Pos)
#define TIM_CCEN_CC1NEN							TIM_CCEN_CC1NEN_Msk				/*!< Capture/Compare 1 Complementary output enable */
#define TIM_CCEN_CC1NP_Pos						(3U)
#define TIM_CCEN_CC1NP_Msk						(0x1UL << TIM_CCEN_CC1NP_Pos)
#define TIM_CCEN_CC1NP							TIM_CCEN_CC1NP_Msk				/*!< Capture/Compare 1 Complementary output Polarity */
#define TIM_CCEN_CC2EN_Pos						(4U)
#define TIM_CCEN_CC2EN_Msk						(0x1UL << TIM_CCEN_CC2EN_Pos)
#define TIM_CCEN_CC2EN							TIM_CCEN_CC2EN_Msk				/*!< Capture/Compare 2 output enable */
#define TIM_CCEN_CC2P_Pos						(5U)
#define TIM_CCEN_CC2P_Msk						(0x1UL << TIM_CCEN_CC2P_Pos)
#define TIM_CCEN_CC2P							TIM_CCEN_CC2P_Msk				/*!< Capture/Compare 2 output Polarity */
#define TIM_CCEN_CC2NEN_Pos						(6U)
#define TIM_CCEN_CC2NEN_Msk						(0x1UL << TIM_CCEN_CC2NEN_Pos)
#define TIM_CCEN_CC2NEN							TIM_CCEN_CC2NEN_Msk				/*!< Capture/Compare 2 Complementary output enable */
#define TIM_CCEN_CC2NP_Pos						(7U)
#define TIM_CCEN_CC2NP_Msk						(0x1UL << TIM_CCEN_CC2NP_Pos)
#define TIM_CCEN_CC2NP							TIM_CCEN_CC2NP_Msk				/*!< Capture/Compare 2 Complementary output Polarity */
#define TIM_CCEN_CC3EN_Pos						(8U)
#define TIM_CCEN_CC3EN_Msk						(0x1UL << TIM_CCEN_CC3EN_Pos)
#define TIM_CCEN_CC3EN							TIM_CCEN_CC3EN_Msk				/*!< Capture/Compare 3 output enable */
#define TIM_CCEN_CC3P_Pos						(9U)
#define TIM_CCEN_CC3P_Msk						(0x1UL << TIM_CCEN_CC3P_Pos)
#define TIM_CCEN_CC3P							TIM_CCEN_CC3P_Msk				/*!< Capture/Compare 3 output Polarity */
#define TIM_CCEN_CC3NEN_Pos						(10U)
#define TIM_CCEN_CC3NEN_Msk						(0x1UL << TIM_CCEN_CC3NEN_Pos)
#define TIM_CCEN_CC3NEN							TIM_CCEN_CC3NEN_Msk				/*!< Capture/Compare 3 Complementary output enable */
#define TIM_CCEN_CC3NP_Pos						(11U)
#define TIM_CCEN_CC3NP_Msk						(0x1UL << TIM_CCEN_CC3NP_Pos)
#define TIM_CCEN_CC3NP							TIM_CCEN_CC3NP_Msk				/*!< Capture/Compare 3 Complementary output Polarity */
#define TIM_CCEN_CC4EN_Pos						(12U)
#define TIM_CCEN_CC4EN_Msk						(0x1UL << TIM_CCEN_CC4EN_Pos)
#define TIM_CCEN_CC4EN							TIM_CCEN_CC4EN_Msk				/*!< Capture/Compare 4 output enable */
#define TIM_CCEN_CC4P_Pos						(13U)
#define TIM_CCEN_CC4P_Msk						(0x1UL << TIM_CCEN_CC4P_Pos)
#define TIM_CCEN_CC4P							TIM_CCEN_CC4P_Msk				/*!< Capture/Compare 4 output Polarity */
#define TIM_CCEN_CC5EN_Pos						(16U)
#define TIM_CCEN_CC5EN_Msk						(0x1UL << TIM_CCEN_CC5EN_Pos)
#define TIM_CCEN_CC5EN							TIM_CCEN_CC5EN_Msk				/*!< Capture/Compare 5 output enable */
#define TIM_CCEN_CC5P_Pos						(17U)
#define TIM_CCEN_CC5P_Msk						(0x1UL << TIM_CCEN_CC5P_Pos)
#define TIM_CCEN_CC5P							TIM_CCEN_CC5P_Msk				/*!< Capture/Compare 5 output Polarity */
#define TIM_CCEN_CC6EN_Pos						(20U)
#define TIM_CCEN_CC6EN_Msk						(0x1UL << TIM_CCEN_CC6EN_Pos)
#define TIM_CCEN_CC6EN							TIM_CCEN_CC6EN_Msk				/*!< Capture/Compare 6 output enable */
#define TIM_CCEN_CC6P_Pos						(21U)
#define TIM_CCEN_CC6P_Msk						(0x1UL << TIM_CCEN_CC6P_Pos)
#define TIM_CCEN_CC6P							TIM_CCEN_CC6P_Msk				/*!< Capture/Compare 6 output Polarity */

/*******************  Bit definition for TIM_CNT register  ********************/
#define TIM_CNT_CNT_Pos							(0U)
#define TIM_CNT_CNT_Msk							(0xFFFFUL << TIM_CNT_CNT_Pos)	/*!< 0x0000FFFF */
#define TIM_CNT_CNT								TIM_CNT_CNT_Msk					/*!< Counter Value */

/*******************  Bit definition for TIM_PSC register  ********************/
#define TIM_PSC_PSC_Pos							(0U)
#define TIM_PSC_PSC_Msk							(0xFFFFUL << TIM_PSC_PSC_Pos)	/*!< 0x0000FFFF */
#define TIM_PSC_PSC								TIM_PSC_PSC_Msk					/*!< Prescaler Value */

/********************  Bit definition for TIM_AR register  ********************/
#define TIM_AR_AR_Pos							(0U)
#define TIM_AR_AR_Msk							(0xFFFFUL << TIM_AR_AR_Pos)		/*!< 0x0000FFFF */
#define TIM_AR_AR								TIM_AR_AR_Msk					/*!< actual auto-reload Value */

/******************  Bit definition for TIM_REPCNT register  ******************/
#define TIM_REPCNT_REPCNT_Pos					(0U)
#define TIM_REPCNT_REPCNT_Msk					(0xFFUL << TIM_REPCNT_REPCNT_Pos)	/*!< 0x000000FF */
#define TIM_REPCNT_REPCNT						TIM_REPCNT_REPCNT_Msk			/*!< Repetition Counter Value */

/******************  Bit definition for TIM_CCDAT1 register  ******************/
#define TIM_CCDAT1_CCDAT1_Pos					(0U)
#define TIM_CCDAT1_CCDAT1_Msk					(0xFFFFUL << TIM_CCDAT1_CCDAT1_Pos)	/*!< 0x0000FFFF */
#define TIM_CCDAT1_CCDAT1						TIM_CCDAT1_CCDAT1_Msk			/*!< Capture/Compare 1 Value */

/******************  Bit definition for TIM_CCDAT2 register  ******************/
#define TIM_CCDAT2_CCDAT2_Pos					(0U)
#define TIM_CCDAT2_CCDAT2_Msk					(0xFFFFUL << TIM_CCDAT2_CCDAT2_Pos)	/*!< 0x0000FFFF */
#define TIM_CCDAT2_CCDAT2						TIM_CCDAT2_CCDAT2_Msk			/*!< Capture/Compare 2 Value */

/******************  Bit definition for TIM_CCDAT3 register  ******************/
#define TIM_CCDAT3_CCDAT3_Pos					(0U)
#define TIM_CCDAT3_CCDAT3_Msk					(0xFFFFUL << TIM_CCDAT3_CCDAT3_Pos)	/*!< 0x0000FFFF */
#define TIM_CCDAT3_CCDAT3						TIM_CCDAT3_CCDAT3_Msk			/*!< Capture/Compare 3 Value */

/******************  Bit definition for TIM_CCDAT4 register  ******************/
#define TIM_CCDAT4_CCDAT4_Pos					(0U)
#define TIM_CCDAT4_CCDAT4_Msk					(0xFFFFUL << TIM_CCDAT4_CCDAT4_Pos)	/*!< 0x0000FFFF */
#define TIM_CCDAT4_CCDAT4						TIM_CCDAT4_CCDAT4_Msk			/*!< Capture/Compare 4 Value */

/******************  Bit definition for TIM_CCDAT5 register  ******************/
#define TIM_CCDAT5_CCDAT5_Pos					(0U)
#define TIM_CCDAT5_CCDAT5_Msk					(0xFFFFUL << TIM_CCDAT5_CCDAT5_Pos)	/*!< 0x0000FFFF */
#define TIM_CCDAT5_CCDAT5						TIM_CCDAT5_CCDAT5_Msk			/*!< Capture/Compare 5 Value */

/******************  Bit definition for TIM_CCDAT6 register  ******************/
#define TIM_CCDAT6_CCDAT6_Pos					(0U)
#define TIM_CCDAT6_CCDAT6_Msk					(0xFFFFUL << TIM_CCDAT6_CCDAT6_Pos)	/*!< 0x0000FFFF */
#define TIM_CCDAT6_CCDAT6						TIM_CCDAT6_CCDAT6_Msk			/*!< Capture/Compare 6 Value */

/*******************  Bit definition for TIM_BKDT register  *******************/
#define TIM_BKDT_DTGN_Pos						(0U)
#define TIM_BKDT_DTGN_Msk						(0xFFUL << TIM_BKDT_DTGN_Pos)
#define TIM_BKDT_DTGN							TIM_BKDT_DTGN_Msk				/*!< DTG[0:7] bits (Dead-Time Generator set-up) */
#define TIM_BKDT_DTGN_0							((uint16_t) 0x0001)				/*!< Bit 0 */
#define TIM_BKDT_DTGN_1							((uint16_t) 0x0002)				/*!< Bit 1 */
#define TIM_BKDT_DTGN_2							((uint16_t) 0x0004)				/*!< Bit 2 */
#define TIM_BKDT_DTGN_3							((uint16_t) 0x0008)				/*!< Bit 3 */
#define TIM_BKDT_DTGN_4							((uint16_t) 0x0010)				/*!< Bit 4 */
#define TIM_BKDT_DTGN_5							((uint16_t) 0x0020)				/*!< Bit 5 */
#define TIM_BKDT_DTGN_6							((uint16_t) 0x0040)				/*!< Bit 6 */
#define TIM_BKDT_DTGN_7							((uint16_t) 0x0080)				/*!< Bit 7 */
#define TIM_BKDT_LCKCFG_Pos						(8U)
#define TIM_BKDT_LCKCFG_Msk						(0x3UL << TIM_BKDT_LCKCFG_Pos)
#define TIM_BKDT_LCKCFG							TIM_BKDT_LCKCFG_Msk				/*!< LOCK[1:0] bits (Lock Configuration) */
#define TIM_BKDT_LCKCFG_0						((uint16_t) 0x0100)				/*!< Bit 0 */
#define TIM_BKDT_LCKCFG_1						((uint16_t) 0x0200)				/*!< Bit 1 */
#define TIM_BKDT_OSSI_Pos						(10U)
#define TIM_BKDT_OSSI_Msk						(0x1UL << TIM_BKDT_OSSI_Pos)
#define TIM_BKDT_OSSI							TIM_BKDT_OSSI_Msk				/*!< Off-State Selection for Idle mode */
#define TIM_BKDT_OSSR_Pos						(11U)
#define TIM_BKDT_OSSR_Msk						(0x1UL << TIM_BKDT_OSSR_Pos)
#define TIM_BKDT_OSSR							TIM_BKDT_OSSR_Msk				/*!< Off-State Selection for Run mode */
#define TIM_BKDT_BKEN_Pos						(12U)
#define TIM_BKDT_BKEN_Msk						(0x1UL << TIM_BKDT_BKEN_Pos)
#define TIM_BKDT_BKEN							TIM_BKDT_BKEN_Msk				/*!< Break enable */
#define TIM_BKDT_BKP_Pos						(13U)
#define TIM_BKDT_BKP_Msk						(0x1UL << TIM_BKDT_BKP_Pos)
#define TIM_BKDT_BKP							TIM_BKDT_BKP_Msk				/*!< Break Polarity */
#define TIM_BKDT_AOEN_Pos						(14U)
#define TIM_BKDT_AOEN_Msk						(0x1UL << TIM_BKDT_AOEN_Pos)
#define TIM_BKDT_AOEN							TIM_BKDT_AOEN_Msk				/*!< Automatic Output enable */
#define TIM_BKDT_MOEN_Pos						(15U)
#define TIM_BKDT_MOEN_Msk						(0x1UL << TIM_BKDT_MOEN_Pos)
#define TIM_BKDT_MOEN							TIM_BKDT_MOEN_Msk				/*!< Main Output enable */

/******************  Bit definition for TIM_DCTRL register  *******************/
#define TIM_DCTRL_DBADDR_Pos					(0U)
#define TIM_DCTRL_DBADDR_Msk					(0x1F << TIM_DCTRL_DBADDR_Pos)
#define TIM_DCTRL_DBADDR						TIM_DCTRL_DBADDR_Msk			/*!< DBA[4:0] bits (DMA Base Address) */
#define TIM_DCTRL_DBADDR_0						((uint16_t) 0x0001)				/*!< Bit 0 */
#define TIM_DCTRL_DBADDR_1						((uint16_t) 0x0002)				/*!< Bit 1 */
#define TIM_DCTRL_DBADDR_2						((uint16_t) 0x0004)				/*!< Bit 2 */
#define TIM_DCTRL_DBADDR_3						((uint16_t) 0x0008)				/*!< Bit 3 */
#define TIM_DCTRL_DBADDR_4						((uint16_t) 0x0010)				/*!< Bit 4 */
#define TIM_DCTRL_DBLEN_Pos						(8U)
#define TIM_DCTRL_DBLEN_Msk						(0x1F << TIM_DCTRL_DBLEN_Pos)
#define TIM_DCTRL_DBLEN							TIM_DCTRL_DBLEN_Msk				/*!< DBL[4:0] bits (DMA Burst Length) */
#define TIM_DCTRL_DBLEN_0						((uint16_t) 0x0100)				/*!< Bit 0 */
#define TIM_DCTRL_DBLEN_1						((uint16_t) 0x0200)				/*!< Bit 1 */
#define TIM_DCTRL_DBLEN_2						((uint16_t) 0x0400)				/*!< Bit 2 */
#define TIM_DCTRL_DBLEN_3						((uint16_t) 0x0800)				/*!< Bit 3 */
#define TIM_DCTRL_DBLEN_4						((uint16_t) 0x1000)				/*!< Bit 4 */

/******************  Bit definition for TIM_DADDR register  *******************/
#define TIM_DADDR_BURST_Pos						(0U)
#define TIM_DADDR_BURST_Msk						(0xFFFFUL << TIM_DADDR_BURST_Pos)	/*!< 0x0000FFFF */
#define TIM_DADDR_BURST							TIM_DADDR_BURST_Msk				/*!< DMA register for burst accesses */

/******************************************************************************/
/*                                                                            */
/*                           Real-Time Clock (RTC)                            */
/*                                                                            */
/******************************************************************************/
/*******************  Bits definition for RTC_TSH register  *******************/
#define RTC_TSH_SCU_Pos							(0U)
#define RTC_TSH_SCU_Msk							(0xFUL << RTC_TSH_SCU_Pos)
#define RTC_TSH_SCU								RTC_TSH_SCU_Msk					/*!< Second units in BCD format */
#define RTC_TSH_SCU_0							(0x1UL << RTC_TSH_SCU_Pos)		/*!< Bit 0 */
#define RTC_TSH_SCU_1							(0x2UL << RTC_TSH_SCU_Pos)		/*!< Bit 1 */
#define RTC_TSH_SCU_2							(0x4UL << RTC_TSH_SCU_Pos)		/*!< Bit 2 */
#define RTC_TSH_SCU_3							(0x8UL << RTC_TSH_SCU_Pos)		/*!< Bit 3 */

#define RTC_TSH_SCT_Pos							(4U)
#define RTC_TSH_SCT_Msk							(0x7UL << RTC_TSH_SCT_Pos)
#define RTC_TSH_SCT								RTC_TSH_SCT_Msk					/*!< Second tens in BCD format */
#define RTC_TSH_SCT_0							(0x1UL << RTC_TSH_SCT_Pos)		/*!< Bit 0 */
#define RTC_TSH_SCT_1							(0x2UL << RTC_TSH_SCT_Pos)		/*!< Bit 1 */
#define RTC_TSH_SCT_2							(0x4UL << RTC_TSH_SCT_Pos)		/*!< Bit 2 */

#define RTC_TSH_MIU_Pos							(8U)
#define RTC_TSH_MIU_Msk							(0xFUL << RTC_TSH_MIU_Pos)
#define RTC_TSH_MIU								RTC_TSH_MIU_Msk					/*!< Minute units in BCD format */
#define RTC_TSH_MIU_0							(0x1UL << RTC_TSH_MIU_Pos)		/*!< Bit 0 */
#define RTC_TSH_MIU_1							(0x2UL << RTC_TSH_MIU_Pos)		/*!< Bit 1 */
#define RTC_TSH_MIU_2							(0x4UL << RTC_TSH_MIU_Pos)		/*!< Bit 2 */
#define RTC_TSH_MIU_3							(0x8UL << RTC_TSH_MIU_Pos)		/*!< Bit 3 */

#define RTC_TSH_MIT_Pos							(12U)
#define RTC_TSH_MIT_Msk							(0x7UL << RTC_TSH_MIT_Pos)
#define RTC_TSH_MIT								RTC_TSH_MIT_Msk					/*!< Minute tens in BCD format */
#define RTC_TSH_MIT_0							(0x1UL << RTC_TSH_MIT_Pos)		/*!< Bit 0 */
#define RTC_TSH_MIT_1							(0x2UL << RTC_TSH_MIT_Pos)		/*!< Bit 1 */
#define RTC_TSH_MIT_2							(0x4UL << RTC_TSH_MIT_Pos)		/*!< Bit 2 */

#define RTC_TSH_HOU_Pos							(16U)
#define RTC_TSH_HOU_Msk							(0xFUL << RTC_TSH_HOU_Pos)
#define RTC_TSH_HOU								RTC_TSH_HOU_Msk					/*!< Hour units in BCD format */
#define RTC_TSH_HOU_0							(0x1UL << RTC_TSH_HOU_Pos)		/*!< Bit 0 */
#define RTC_TSH_HOU_1							(0x2UL << RTC_TSH_HOU_Pos)		/*!< Bit 1 */
#define RTC_TSH_HOU_2							(0x4UL << RTC_TSH_HOU_Pos)		/*!< Bit 2 */
#define RTC_TSH_HOU_3							(0x8UL << RTC_TSH_HOU_Pos)		/*!< Bit 3 */

#define RTC_TSH_HOT_Pos							(20U)
#define RTC_TSH_HOT_Msk							(0x3UL << RTC_TSH_HOT_Pos)
#define RTC_TSH_HOT								RTC_TSH_HOT_Msk					/*!< Hour tens in BCD format */
#define RTC_TSH_HOT_0							(0x1UL << RTC_TSH_HOT_Pos)		/*!< Bit 0 */
#define RTC_TSH_HOT_1							(0x2UL << RTC_TSH_HOT_Pos)		/*!< Bit 1 */

#define RTC_TSH_APM_Pos							(22U)
#define RTC_TSH_APM_Msk							(0x1UL << RTC_TSH_APM_Pos)
#define RTC_TSH_APM								RTC_TSH_APM_Msk					/*!< AM/PM notation */

/******************  Bits definition for RTC_DATE register  *******************/
#define RTC_DATE_DAU_Pos						(0U)
#define RTC_DATE_DAU_Msk						(0xFUL << RTC_DATE_DAU_Pos)
#define RTC_DATE_DAU							RTC_DATE_DAU_Msk				/*!< Date units in BCD format */
#define RTC_DATE_DAU_0							(0x1UL << RTC_DATE_DAU_Pos)		/*!< Bit 0 */
#define RTC_DATE_DAU_1							(0x2UL << RTC_DATE_DAU_Pos)		/*!< Bit 1 */
#define RTC_DATE_DAU_2							(0x4UL << RTC_DATE_DAU_Pos)		/*!< Bit 2 */
#define RTC_DATE_DAU_3							(0x8UL << RTC_DATE_DAU_Pos)		/*!< Bit 3 */

#define RTC_DATE_DAT_Pos						(4U)
#define RTC_DATE_DAT_Msk						(0x3UL << RTC_DATE_DAT_Pos)
#define RTC_DATE_DAT							RTC_DATE_DAT_Msk				/*!< Date tens in BCD format */
#define RTC_DATE_DAT_0							(0x1UL << RTC_DATE_DAT_Pos)		/*!< Bit 0 */
#define RTC_DATE_DAT_1							(0x2UL << RTC_DATE_DAT_Pos)		/*!< Bit 1 */

#define RTC_DATE_MOU_Pos						(8U)
#define RTC_DATE_MOU_Msk						(0xFUL << RTC_DATE_MOU_Pos)
#define RTC_DATE_MOU							RTC_DATE_MOU_Msk				/*!< Month units in BCD format */
#define RTC_DATE_MOU_0							(0x1UL << RTC_DATE_MOU_Pos)		/*!< Bit 0 */
#define RTC_DATE_MOU_1							(0x2UL << RTC_DATE_MOU_Pos)		/*!< Bit 1 */
#define RTC_DATE_MOU_2							(0x4UL << RTC_DATE_MOU_Pos)		/*!< Bit 2 */
#define RTC_DATE_MOU_3							(0x8UL << RTC_DATE_MOU_Pos)		/*!< Bit 3 */

#define RTC_DATE_MOT_Pos						(12U)
#define RTC_DATE_MOT_Msk						(0x1UL << RTC_DATE_MOT_Pos)
#define RTC_DATE_MOT							RTC_DATE_MOT_Msk				/*!< Month tens in BCD format */

#define RTC_DATE_WDU_Pos						(13U)
#define RTC_DATE_WDU_Msk						(0x7UL << RTC_DATE_WDU_Pos)
#define RTC_DATE_WDU							RTC_DATE_WDU_Msk				/*!< Week day units */
#define RTC_DATE_WDU_0							(0x1UL << RTC_DATE_WDU_Pos)		/*!< Bit 0 */
#define RTC_DATE_WDU_1							(0x2UL << RTC_DATE_WDU_Pos)		/*!< Bit 1 */
#define RTC_DATE_WDU_2							(0x4UL << RTC_DATE_WDU_Pos)		/*!< Bit 2 */

#define RTC_DATE_YRU_Pos						(16U)
#define RTC_DATE_YRU_Msk						(0xFUL << RTC_DATE_YRU_Pos)
#define RTC_DATE_YRU							RTC_DATE_YRU_Msk				/*!< Year units in BCD format */
#define RTC_DATE_YRU_0							(0x1UL << RTC_DATE_YRU_Pos)		/*!< Bit 0 */
#define RTC_DATE_YRU_1							(0x2UL << RTC_DATE_YRU_Pos)		/*!< Bit 1 */
#define RTC_DATE_YRU_2							(0x4UL << RTC_DATE_YRU_Pos)		/*!< Bit 2 */
#define RTC_DATE_YRU_3							(0x8UL << RTC_DATE_YRU_Pos)		/*!< Bit 3 */

#define RTC_DATE_YRT_Pos						(20U)
#define RTC_DATE_YRT_Msk						(0xFUL << RTC_DATE_YRT_Pos)
#define RTC_DATE_YRT							RTC_DATE_YRT_Msk				/*!< Year tens in BCD format */
#define RTC_DATE_YRT_0							(0x1UL << RTC_DATE_YRT_Pos)		/*!< Bit 0 */
#define RTC_DATE_YRT_1							(0x2UL << RTC_DATE_YRT_Pos)		/*!< Bit 1 */
#define RTC_DATE_YRT_2							(0x4UL << RTC_DATE_YRT_Pos)		/*!< Bit 2 */
#define RTC_DATE_YRT_3							(0x8UL << RTC_DATE_YRT_Pos)		/*!< Bit 3 */

/******************  Bits definition for RTC_CTRL register  *******************/
#define RTC_CTRL_WKUPSEL_Pos					(0U)
#define RTC_CTRL_WKUPSEL_Msk					(0x7UL << RTC_CTRL_WKUPSEL_Pos)
#define RTC_CTRL_WKUPSEL						RTC_CTRL_WKUPSEL_Msk			/*!< Wakeup clock selection */
#define RTC_CTRL_WKUPSEL_0						(0x1UL << RTC_CTRL_WKUPSEL_Pos)	/*!< Bit 0 */
#define RTC_CTRL_WKUPSEL_1						(0x2UL << RTC_CTRL_WKUPSEL_Pos)	/*!< Bit 1 */
#define RTC_CTRL_WKUPSEL_2						(0x4UL << RTC_CTRL_WKUPSEL_Pos)	/*!< Bit 2 */

#define RTC_CTRL_TSPOL_Pos						(3U)
#define RTC_CTRL_TSPOL_Msk						(0x1UL << RTC_CTRL_TSPOL_Pos)
#define RTC_CTRL_TSPOL							RTC_CTRL_TSPOL_Msk				/*!< Timestamp event active edge */
#define RTC_CTRL_BYPS_Pos						(5U)
#define RTC_CTRL_BYPS_Msk						(0x1UL << RTC_CTRL_BYPS_Pos)
#define RTC_CTRL_BYPS							RTC_CTRL_BYPS_Msk				/*!< Bypass the shadow registers */
#define RTC_CTRL_HFMT_Pos						(6U)
#define RTC_CTRL_HFMT_Msk						(0x1UL << RTC_CTRL_HFMT_Pos)
#define RTC_CTRL_HFMT							RTC_CTRL_HFMT_Msk				/*!< Hour format */
#define RTC_CTRL_ALAEN_Pos						(8U)
#define RTC_CTRL_ALAEN_Msk						(0x1UL << RTC_CTRL_ALAEN_Pos)
#define RTC_CTRL_ALAEN							RTC_CTRL_ALAEN_Msk				/*!< Alarm A enable */
#define RTC_CTRL_ALBEN_Pos						(9U)
#define RTC_CTRL_ALBEN_Msk						(0x1UL << RTC_CTRL_ALBEN_Pos)
#define RTC_CTRL_ALBEN							RTC_CTRL_ALBEN_Msk				/*!< Alarm B enable */
#define RTC_CTRL_WTEN_Pos						(10U)
#define RTC_CTRL_WTEN_Msk						(0x1UL << RTC_CTRL_WTEN_Pos)
#define RTC_CTRL_WTEN							RTC_CTRL_WTEN_Msk				/*!< Wakeup timer enable */
#define RTC_CTRL_TSEN_Pos						(11U)
#define RTC_CTRL_TSEN_Msk						(0x1UL << RTC_CTRL_TSEN_Pos)
#define RTC_CTRL_TSEN							RTC_CTRL_TSEN_Msk				/*!< Time stamp enable */
#define RTC_CTRL_ALAIEN_Pos						(12U)
#define RTC_CTRL_ALAIEN_Msk						(0x1UL << RTC_CTRL_ALAIEN_Pos)
#define RTC_CTRL_ALAIEN							RTC_CTRL_ALAIEN_Msk				/*!< Alarm A interrupt enable */
#define RTC_CTRL_ALBIEN_Pos						(13U)
#define RTC_CTRL_ALBIEN_Msk						(0x1UL << RTC_CTRL_ALBIEN_Pos)
#define RTC_CTRL_ALBIEN							RTC_CTRL_ALBIEN_Msk				/*!< Alarm B interrupt enable */
#define RTC_CTRL_WTIEN_Pos						(14U)
#define RTC_CTRL_WTIEN_Msk						(0x1UL << RTC_CTRL_WTIEN_Pos)
#define RTC_CTRL_WTIEN							RTC_CTRL_WTIEN_Msk				/*!< Wakeup timer interrupt enable */
#define RTC_CTRL_AD1H_Pos						(16U)
#define RTC_CTRL_AD1H_Msk						(0x1UL << RTC_CTRL_AD1H_Pos)
#define RTC_CTRL_AD1H							RTC_CTRL_AD1H_Msk				/*!< Add 1 hour (summer time change) */
#define RTC_CTRL_SU1H_Pos						(17U)
#define RTC_CTRL_SU1H_Msk						(0x1UL << RTC_CTRL_SU1H_Pos)
#define RTC_CTRL_SU1H							RTC_CTRL_SU1H_Msk				/*!< Subtract 1 hour (winter time change) */
#define RTC_CTRL_BAKP_Pos						(18U)
#define RTC_CTRL_BAKP_Msk						(0x1UL << RTC_CTRL_BAKP_Pos)
#define RTC_CTRL_BAKP							RTC_CTRL_BAKP_Msk				/*!< Backup */
#define RTC_CTRL_CALOSEL_Pos					(19U)
#define RTC_CTRL_CALOSEL_Msk					(0x1UL << RTC_CTRL_CALOSEL_Pos)
#define RTC_CTRL_CALOSEL						RTC_CTRL_CALOSEL_Msk			/*!< Calibration output selection */
#define RTC_CTRL_OPOL_Pos						(20U)
#define RTC_CTRL_OPOL_Msk						(0x1UL << RTC_CTRL_OPOL_Pos)
#define RTC_CTRL_OPOL							RTC_CTRL_OPOL_Msk				/*!< Output polarity */

#define RTC_CTRL_OUTSEL_Pos						(21U)
#define RTC_CTRL_OUTSEL_Msk						(0x3UL << RTC_CTRL_OUTSEL_Pos)
#define RTC_CTRL_OUTSEL							RTC_CTRL_OUTSEL_Msk				/*!< Output selection */
#define RTC_CTRL_OUTSEL_0						(0x1UL << RTC_CTRL_OUTSEL_Pos)	/*!< Bit 0 */
#define RTC_CTRL_OUTSEL_1						(0x2UL << RTC_CTRL_OUTSEL_Pos)	/*!< Bit 1 */

#define RTC_CTRL_COEN_Pos						(23U)
#define RTC_CTRL_COEN_Msk						(0x1UL << RTC_CTRL_COEN_Pos)
#define RTC_CTRL_COEN							RTC_CTRL_COEN_Msk				/*!< Calibration output enable */

/*****************  Bits definition for RTC_INITSTS register  *****************/
#define RTC_INITSTS_ALAWF_Pos					(0U)
#define RTC_INITSTS_ALAWF_Msk					(0x1UL << RTC_INITSTS_ALAWF_Pos)
#define RTC_INITSTS_ALAWF						RTC_INITSTS_ALAWF_Msk			/*!< Alarm A write flag */
#define RTC_INITSTS_ALBWF_Pos					(1U)
#define RTC_INITSTS_ALBWF_Msk					(0x1UL << RTC_INITSTS_ALBWF_Pos)
#define RTC_INITSTS_ALBWF						RTC_INITSTS_ALBWF_Msk			/*!< Alarm B write flag */
#define RTC_INITSTS_WTWF_Pos					(2U)
#define RTC_INITSTS_WTWF_Msk					(0x1UL << RTC_INITSTS_WTWF_Pos)
#define RTC_INITSTS_WTWF						RTC_INITSTS_WTWF_Msk			/*!< Wakeup timer write flag */
#define RTC_INITSTS_SHOPF_Pos					(3U)
#define RTC_INITSTS_SHOPF_Msk					(0x1UL << RTC_INITSTS_SHOPF_Pos)
#define RTC_INITSTS_SHOPF						RTC_INITSTS_SHOPF_Msk			/*!< Shift operation pending */
#define RTC_INITSTS_INITSF_Pos					(4U)
#define RTC_INITSTS_INITSF_Msk					(0x1UL << RTC_INITSTS_INITSF_Pos)
#define RTC_INITSTS_INITSF						RTC_INITSTS_INITSF_Msk			/*!< Initialization status flag */
#define RTC_INITSTS_RSYF_Pos					(5U)
#define RTC_INITSTS_RSYF_Msk					(0x1UL << RTC_INITSTS_RSYF_Pos)
#define RTC_INITSTS_RSYF						RTC_INITSTS_RSYF_Msk			/*!< Registers synchronization flag */
#define RTC_INITSTS_INITF_Pos					(6U)
#define RTC_INITSTS_INITF_Msk					(0x1UL << RTC_INITSTS_INITF_Pos)
#define RTC_INITSTS_INITF						RTC_INITSTS_INITF_Msk			/*!< Initialization flag */
#define RTC_INITSTS_INITM_Pos					(7U)
#define RTC_INITSTS_INITM_Msk					(0x1UL << RTC_INITSTS_INITM_Pos)
#define RTC_INITSTS_INITM						RTC_INITSTS_INITM_Msk			/*!< Initialization mode */
#define RTC_INITSTS_ALAF_Pos					(8U)
#define RTC_INITSTS_ALAF_Msk					(0x1UL << RTC_INITSTS_ALAF_Pos)
#define RTC_INITSTS_ALAF						RTC_INITSTS_ALAF_Msk			/*!< Alarm A flag */
#define RTC_INITSTS_ALBF_Pos					(9U)
#define RTC_INITSTS_ALBF_Msk					(0x1UL << RTC_INITSTS_ALBF_Pos)
#define RTC_INITSTS_ALBF						RTC_INITSTS_ALBF_Msk			/*!< Alarm B flag */
#define RTC_INITSTS_WTF_Pos						(10U)
#define RTC_INITSTS_WTF_Msk						(0x1UL << RTC_INITSTS_WTF_Pos)
#define RTC_INITSTS_WTF							RTC_INITSTS_WTF_Msk				/*!< Wakeup timer flag */
#define RTC_INITSTS_TISF_Pos					(11U)
#define RTC_INITSTS_TISF_Msk					(0x1UL << RTC_INITSTS_TISF_Pos)
#define RTC_INITSTS_TISF						RTC_INITSTS_TISF_Msk			/*!< Timestamp flag */
#define RTC_INITSTS_TISOVF_Pos					(12U)
#define RTC_INITSTS_TISOVF_Msk					(0x1UL << RTC_INITSTS_TISOVF_Pos)
#define RTC_INITSTS_TISOVF						RTC_INITSTS_TISOVF_Msk			/*!< Timestamp overflow flag */
#define RTC_INITSTS_RECPF_Pos					(16U)
#define RTC_INITSTS_RECPF_Msk					(0x1UL << RTC_INITSTS_RECPF_Pos)
#define RTC_INITSTS_RECPF						RTC_INITSTS_RECPF_Msk			/*!< Recalibration pending Flag */

/*******************  Bits definition for RTC_PRE register  *******************/
#define RTC_PRE_DIVS_Pos						(0U)
#define RTC_PRE_DIVS_Msk						(0x7FFFUL << RTC_PRE_DIVS_Pos)
#define RTC_PRE_DIVS							RTC_PRE_DIVS_Msk				/*!< Asynchronous prescaler factor */
#define RTC_PRE_DIVA_Pos						(16U)
#define RTC_PRE_DIVA_Msk						(0x7FUL << RTC_PRE_DIVA_Pos)
#define RTC_PRE_DIVA							RTC_PRE_DIVA_Msk				/*!< Synchronous prescaler factor */

/******************  Bits definition for RTC_WKUPT register  ******************/
#define RTC_WKUPT_WKUPT_Pos						(0U)
#define RTC_WKUPT_WKUPT_Msk						(0xFFFFUL << RTC_WKUPT_WKUPT_Pos)
#define RTC_WKUPT_WKUPT							RTC_WKUPT_WKUPT_Msk				/*!< Wakeup auto-reload value bit */

/********************  Bits definition for RTC_ALARMA register  ***************/
#define RTC_ALARMA_SEU_Pos						(0U)
#define RTC_ALARMA_SEU_Msk						(0xFUL << RTC_ALARMA_SEU_Pos)
#define RTC_ALARMA_SEU							RTC_ALARMA_SEU_Msk				/*!< Second units in BCD format */
#define RTC_ALARMA_SEU_0						(0x1UL << RTC_ALARMA_SEU_Pos)	/*!< Bit 0 */
#define RTC_ALARMA_SEU_1						(0x2UL << RTC_ALARMA_SEU_Pos)	/*!< Bit 1 */
#define RTC_ALARMA_SEU_2						(0x4UL << RTC_ALARMA_SEU_Pos)	/*!< Bit 2 */
#define RTC_ALARMA_SEU_3						(0x8UL << RTC_ALARMA_SEU_Pos)	/*!< Bit 3 */

#define RTC_ALARMA_SET_Pos						(4U)
#define RTC_ALARMA_SET_Msk						(0x7UL << RTC_ALARMA_SET_Pos)
#define RTC_ALARMA_SET							RTC_ALARMA_SET_Msk				/*!< Second tens in BCD format */
#define RTC_ALARMA_SET_0						(0x1UL << RTC_ALARMA_SET_Pos)	/*!< Bit 0 */
#define RTC_ALARMA_SET_1						(0x2UL << RTC_ALARMA_SET_Pos)	/*!< Bit 1 */
#define RTC_ALARMA_SET_2						(0x4UL << RTC_ALARMA_SET_Pos)	/*!< Bit 2 */

#define RTC_ALARMA_MASK1_Pos					(7U)
#define RTC_ALARMA_MASK1_Msk					(0x1UL << RTC_ALARMA_MASK1_Pos)
#define RTC_ALARMA_MASK1						RTC_ALARMA_MASK1_Msk			/*!< Alarm A seconds mask */

#define RTC_ALARMA_MIU_Pos						(8U)
#define RTC_ALARMA_MIU_Msk						(0xFUL << RTC_ALARMA_MIU_Pos)
#define RTC_ALARMA_MIU							RTC_ALARMA_MIU_Msk				/*!< Minute units in BCD format */
#define RTC_ALARMA_MIU_0						(0x1UL << RTC_ALARMA_MIU_Pos)	/*!< Bit 0 */
#define RTC_ALARMA_MIU_1						(0x2UL << RTC_ALARMA_MIU_Pos)	/*!< Bit 1 */
#define RTC_ALARMA_MIU_2						(0x4UL << RTC_ALARMA_MIU_Pos)	/*!< Bit 2 */
#define RTC_ALARMA_MIU_3						(0x8UL << RTC_ALARMA_MIU_Pos)	/*!< Bit 3 */

#define RTC_ALARMA_MIT_Pos						(12U)
#define RTC_ALARMA_MIT_Msk						(0x7UL << RTC_ALARMA_MIT_Pos)
#define RTC_ALARMA_MIT							RTC_ALARMA_MIT_Msk				/*!< Minute tens in BCD format */
#define RTC_ALARMA_MIT_0						(0x1UL << RTC_ALARMA_MIT_Pos)	/*!< Bit 0 */
#define RTC_ALARMA_MIT_1						(0x2UL << RTC_ALARMA_MIT_Pos)	/*!< Bit 1 */
#define RTC_ALARMA_MIT_2						(0x4UL << RTC_ALARMA_MIT_Pos)	/*!< Bit 2 */

#define RTC_ALARMA_MASK2_Pos					(15U)
#define RTC_ALARMA_MASK2_Msk					(0x1UL << RTC_ALARMA_MASK2_Pos)
#define RTC_ALARMA_MASK2						RTC_ALARMA_MASK2_Msk			/*!< Alarm A minutes mask */

#define RTC_ALARMA_HOU_Pos						(16U)
#define RTC_ALARMA_HOU_Msk						(0xFUL << RTC_ALARMA_HOU_Pos)
#define RTC_ALARMA_HOU							RTC_ALARMA_HOU_Msk				/*!< Hour units in BCD format */
#define RTC_ALARMA_HOU_0						(0x1UL << RTC_ALARMA_HOU_Pos)	/*!< Bit 0 */
#define RTC_ALARMA_HOU_1						(0x2UL << RTC_ALARMA_HOU_Pos)	/*!< Bit 1 */
#define RTC_ALARMA_HOU_2						(0x4UL << RTC_ALARMA_HOU_Pos)	/*!< Bit 2 */
#define RTC_ALARMA_HOU_3						(0x8UL << RTC_ALARMA_HOU_Pos)	/*!< Bit 3 */

#define RTC_ALARMA_HOT_Pos						(20U)
#define RTC_ALARMA_HOT_Msk						(0x3UL << RTC_ALARMA_HOT_Pos)
#define RTC_ALARMA_HOT							RTC_ALARMA_HOT_Msk				/*!< Hour tens in BCD format */
#define RTC_ALARMA_HOT_0						(0x1UL << RTC_ALARMA_HOT_Pos)	/*!< Bit 0 */
#define RTC_ALARMA_HOT_1						(0x2UL << RTC_ALARMA_HOT_Pos)	/*!< Bit 1 */

#define RTC_ALARMA_APM_Pos						(22U)
#define RTC_ALARMA_APM_Msk						(0x1UL << RTC_ALARMA_APM_Pos)
#define RTC_ALARMA_APM							RTC_ALARMA_APM_Msk				/*!< AM/PM notation */
#define RTC_ALARMA_MASK3_Pos					(23U)
#define RTC_ALARMA_MASK3_Msk					(0x1UL << RTC_ALARMA_MASK3_Pos)
#define RTC_ALARMA_MASK3						RTC_ALARMA_MASK3_Msk			/*!< Alarm A hours mask */

#define RTC_ALARMA_DTU_Pos						(24U)
#define RTC_ALARMA_DTU_Msk						(0xFUL << RTC_ALARMA_DTU_Pos)
#define RTC_ALARMA_DTU							RTC_ALARMA_DTU_Msk				/*!< Date units or day in BCD format */
#define RTC_ALARMA_DTU_0						(0x1UL << RTC_ALARMA_DTU_Pos)	/*!< Bit 0 */
#define RTC_ALARMA_DTU_1						(0x2UL << RTC_ALARMA_DTU_Pos)	/*!< Bit 1 */
#define RTC_ALARMA_DTU_2						(0x4UL << RTC_ALARMA_DTU_Pos)	/*!< Bit 2 */
#define RTC_ALARMA_DTU_3						(0x8UL << RTC_ALARMA_DTU_Pos)	/*!< Bit 3 */

#define RTC_ALARMA_DTT_Pos						(28U)
#define RTC_ALARMA_DTT_Msk						(0x3UL << RTC_ALARMA_DTT_Pos)
#define RTC_ALARMA_DTT							RTC_ALARMA_DTT_Msk				/*!< Date tens in BCD format */
#define RTC_ALARMA_DTT_0						(0x1UL << RTC_ALARMA_DTT_Pos)	/*!< Bit 0 */
#define RTC_ALARMA_DTT_1						(0x2UL << RTC_ALARMA_DTT_Pos)	/*!< Bit 1 */

#define RTC_ALARMA_WKDSEL_Pos					(30U)
#define RTC_ALARMA_WKDSEL_Msk					(0x1UL << RTC_ALARMA_WKDSEL_Pos)
#define RTC_ALARMA_WKDSEL						RTC_ALARMA_WKDSEL_Msk			/*!< Week day selection */
#define RTC_ALARMA_MASK4_Pos					(31U)
#define RTC_ALARMA_MASK4_Msk					(0x1UL << RTC_ALARMA_MASK4_Pos)
#define RTC_ALARMA_MASK4						RTC_ALARMA_MASK4_Msk			/*!< Alarm A date mask */

/********************  Bits definition for RTC_ALARMB register  ***************/
#define RTC_ALARMB_SEU_Pos						(0U)
#define RTC_ALARMB_SEU_Msk						(0xFUL << RTC_ALARMB_SEU_Pos)
#define RTC_ALARMB_SEU							RTC_ALARMB_SEU_Msk				/*!< Second units in BCD format */
#define RTC_ALARMB_SEU_0						(0x1UL << RTC_ALARMB_SEU_Pos)	/*!< Bit 0 */
#define RTC_ALARMB_SEU_1						(0x2UL << RTC_ALARMB_SEU_Pos)	/*!< Bit 1 */
#define RTC_ALARMB_SEU_2						(0x4UL << RTC_ALARMB_SEU_Pos)	/*!< Bit 2 */
#define RTC_ALARMB_SEU_3						(0x8UL << RTC_ALARMB_SEU_Pos)	/*!< Bit 3 */

#define RTC_ALARMB_SET_Pos						(4U)
#define RTC_ALARMB_SET_Msk						(0x7UL << RTC_ALARMB_SET_Pos)
#define RTC_ALARMB_SET							RTC_ALARMB_SET_Msk				/*!< Second tens in BCD format */
#define RTC_ALARMB_SET_0						(0x1UL << RTC_ALARMB_SET_Pos)	/*!< Bit 0 */
#define RTC_ALARMB_SET_1						(0x2UL << RTC_ALARMB_SET_Pos)	/*!< Bit 1 */
#define RTC_ALARMB_SET_2						(0x4UL << RTC_ALARMB_SET_Pos)	/*!< Bit 2 */

#define RTC_ALARMB_MASK1_Pos					(7U)
#define RTC_ALARMB_MASK1_Msk					(0x1UL << RTC_ALARMB_MASK1_Pos)
#define RTC_ALARMB_MASK1						RTC_ALARMB_MASK1_Msk			/*!< Alarm B seconds mask */

#define RTC_ALARMB_MIU_Pos						(8U)
#define RTC_ALARMB_MIU_Msk						(0xFUL << RTC_ALARMB_MIU_Pos)
#define RTC_ALARMB_MIU							RTC_ALARMB_MIU_Msk				/*!< Minute units in BCD format */
#define RTC_ALARMB_MIU_0						(0x1UL << RTC_ALARMB_MIU_Pos)	/*!< Bit 0 */
#define RTC_ALARMB_MIU_1						(0x2UL << RTC_ALARMB_MIU_Pos)	/*!< Bit 1 */
#define RTC_ALARMB_MIU_2						(0x4UL << RTC_ALARMB_MIU_Pos)	/*!< Bit 2 */
#define RTC_ALARMB_MIU_3						(0x8UL << RTC_ALARMB_MIU_Pos)	/*!< Bit 3 */

#define RTC_ALARMB_MIT_Pos						(12U)
#define RTC_ALARMB_MIT_Msk						(0x7UL << RTC_ALARMB_MIT_Pos)
#define RTC_ALARMB_MIT							RTC_ALARMB_MIT_Msk				/*!< Minute tens in BCD format */
#define RTC_ALARMB_MIT_0						(0x1UL << RTC_ALARMB_MIT_Pos)	/*!< Bit 0 */
#define RTC_ALARMB_MIT_1						(0x2UL << RTC_ALARMB_MIT_Pos)	/*!< Bit 1 */
#define RTC_ALARMB_MIT_2						(0x4UL << RTC_ALARMB_MIT_Pos)	/*!< Bit 2 */

#define RTC_ALARMB_MASK2_Pos					(15U)
#define RTC_ALARMB_MASK2_Msk					(0x1UL << RTC_ALARMB_MASK2_Pos)
#define RTC_ALARMB_MASK2						RTC_ALARMB_MASK2_Msk			/*!< Alarm B minutes mask */

#define RTC_ALARMB_HOU_Pos						(16U)
#define RTC_ALARMB_HOU_Msk						(0xFUL << RTC_ALARMB_HOU_Pos)
#define RTC_ALARMB_HOU							RTC_ALARMB_HOU_Msk				/*!< Hour units in BCD format */
#define RTC_ALARMB_HOU_0						(0x1UL << RTC_ALARMB_HOU_Pos)	/*!< Bit 0 */
#define RTC_ALARMB_HOU_1						(0x2UL << RTC_ALARMB_HOU_Pos)	/*!< Bit 1 */
#define RTC_ALARMB_HOU_2						(0x4UL << RTC_ALARMB_HOU_Pos)	/*!< Bit 2 */
#define RTC_ALARMB_HOU_3						(0x8UL << RTC_ALARMB_HOU_Pos)	/*!< Bit 3 */

#define RTC_ALARMB_HOT_Pos						(20U)
#define RTC_ALARMB_HOT_Msk						(0x3UL << RTC_ALARMB_HOT_Pos)
#define RTC_ALARMB_HOT							RTC_ALARMB_HOT_Msk				/*!< Hour tens in BCD format */
#define RTC_ALARMB_HOT_0						(0x1UL << RTC_ALARMB_HOT_Pos)	/*!< Bit 0 */
#define RTC_ALARMB_HOT_1						(0x2UL << RTC_ALARMB_HOT_Pos)	/*!< Bit 1 */

#define RTC_ALARMB_APM_Pos						(22U)
#define RTC_ALARMB_APM_Msk						(0x1UL << RTC_ALARMB_APM_Pos)
#define RTC_ALARMB_APM							RTC_ALARMB_APM_Msk				/*!< AM/PM notation */
#define RTC_ALARMB_MASK3_Pos					(23U)
#define RTC_ALARMB_MASK3_Msk					(0x1UL << RTC_ALARMB_MASK3_Pos)
#define RTC_ALARMB_MASK3						RTC_ALARMB_MASK3_Msk			/*!< Alarm B hours mask */

#define RTC_ALARMB_DTU_Pos						(24U)
#define RTC_ALARMB_DTU_Msk						(0xFUL << RTC_ALARMB_DTU_Pos)
#define RTC_ALARMB_DTU							RTC_ALARMB_DTU_Msk				/*!< Date units or day in BCD format */
#define RTC_ALARMB_DTU_0						(0x1UL << RTC_ALARMB_DTU_Pos)	/*!< Bit 0 */
#define RTC_ALARMB_DTU_1						(0x2UL << RTC_ALARMB_DTU_Pos)	/*!< Bit 1 */
#define RTC_ALARMB_DTU_2						(0x4UL << RTC_ALARMB_DTU_Pos)	/*!< Bit 2 */
#define RTC_ALARMB_DTU_3						(0x8UL << RTC_ALARMB_DTU_Pos)	/*!< Bit 3 */

#define RTC_ALARMB_DTT_Pos						(28U)
#define RTC_ALARMB_DTT_Msk						(0x3UL << RTC_ALARMB_DTT_Pos)
#define RTC_ALARMB_DTT							RTC_ALARMB_DTT_Msk				/*!< Date tens in BCD format */
#define RTC_ALARMB_DTT_0						(0x1UL << RTC_ALARMB_DTT_Pos)	/*!< Bit 0 */
#define RTC_ALARMB_DTT_1						(0x2UL << RTC_ALARMB_DTT_Pos)	/*!< Bit 1 */

#define RTC_ALARMB_WKDSEL_Pos					(30U)
#define RTC_ALARMB_WKDSEL_Msk					(0x1UL << RTC_ALARMB_WKDSEL_Pos)
#define RTC_ALARMB_WKDSEL						RTC_ALARMB_WKDSEL_Msk			/*!< Week day selection */
#define RTC_ALARMB_MASK4_Pos					(31U)
#define RTC_ALARMB_MASK4_Msk					(0x1UL << RTC_ALARMB_MASK4_Pos)
#define RTC_ALARMB_MASK4						RTC_ALARMB_MASK4_Msk			/*!< Alarm B date mask */

/********************  Bits definition for RTC_WRP register  ******************/
#define RTC_WRP_PKEY_Pos						(0U)
#define RTC_WRP_PKEY_Msk						(0xFFUL << RTC_WRP_PKEY_Pos)	/*!< 0x000000FF */
#define RTC_WRP_PKEY							RTC_WRP_PKEY_Msk				/*!< Write protection key */

/******************  Bits definition for RTC_SUBS register  *******************/
#define RTC_SUBS_SS_Pos							(0U)
#define RTC_SUBS_SS_Msk							(0xFFFFUL << RTC_SUBS_SS_Pos)	/*!< 0x0000FFFF */
#define RTC_SUBS_SS								RTC_SUBS_SS_Msk					/*!< Sub second value */

/******************  Bits definition for RTC_SCTRL register  ******************/
#define RTC_SCTRL_ADFS_Pos						(0U)
#define RTC_SCTRL_ADFS_Msk						(0x7FFFUL << RTC_SCTRL_ADFS_Pos)	/*!< 0x00007FFF */
#define RTC_SCTRL_ADFS   						RTC_SCTRL_ADFS_Msk				/*!< Add a fraction of a second */
#define RTC_SCTRL_SUB1S_Pos						(31U)
#define RTC_SCTRL_SUB1S_Msk						(0x1UL << RTC_SCTRL_SUB1S_Pos)		/*!< 0x80000000 */
#define RTC_SCTRL_SUB1S  						RTC_SCTRL_SUB1S_Msk				/*!< Subtract one second */

/*******************  Bits definition for RTC_TST register  *******************/
#define RTC_TST_SEU_Pos							(0U)
#define RTC_TST_SEU_Msk							(0xFUL << RTC_TST_SEU_Pos)		/*!< 0x0000000F */
#define RTC_TST_SEU								RTC_TST_SEU_Msk					/*!< SEU[3:0] Second units in BCD format */
#define RTC_TST_SEU_0							((uint32_t) 0x00000001)			/*!< Bit 0 */
#define RTC_TST_SEU_1							((uint32_t) 0x00000002)			/*!< Bit 1 */
#define RTC_TST_SEU_2							((uint32_t) 0x00000004)			/*!< Bit 2 */
#define RTC_TST_SEU_3							((uint32_t) 0x00000008)			/*!< Bit 3 */
#define RTC_TST_SET_Pos							(4U)
#define RTC_TST_SET_Msk							(0x7UL << RTC_TST_SET_Pos)		/*!< 0x00000070 */
#define RTC_TST_SET								RTC_TST_SET_Msk					/*!< SET[2:0] Second tens in BCD format */
#define RTC_TST_SET_0							((uint32_t) 0x00000010)			/*!< Bit 0 */
#define RTC_TST_SET_1							((uint32_t) 0x00000020)			/*!< Bit 1 */
#define RTC_TST_SET_2							((uint32_t) 0x00000040)			/*!< Bit 2 */
#define RTC_TST_MIU_Pos							(8U)
#define RTC_TST_MIU_Msk							(0xFUL << RTC_TST_MIU_Pos)		/*!< 0x00000F00 */
#define RTC_TST_MIU								RTC_TST_MIU_Msk					/*!< MIU[3:0] Minute units in BCD format */
#define RTC_TST_MIU_0							((uint32_t) 0x00000100)			/*!< Bit 0 */
#define RTC_TST_MIU_1							((uint32_t) 0x00000200)			/*!< Bit 1 */
#define RTC_TST_MIU_2							((uint32_t) 0x00000400)			/*!< Bit 2 */
#define RTC_TST_MIU_3							((uint32_t) 0x00000800)			/*!< Bit 3 */
#define RTC_TST_MIT_Pos							(12U)
#define RTC_TST_MIT_Msk							(0x7UL << RTC_TST_MIT_Pos)		/*!< 0x00007000 */
#define RTC_TST_MIT								RTC_TST_MIT_Msk					/*!< MIT[2:0] Minute tens in BCD format */
#define RTC_TST_MIT_0							((uint32_t) 0x00001000)			/*!< Bit 0 */
#define RTC_TST_MIT_1							((uint32_t) 0x00002000)			/*!< Bit 1 */
#define RTC_TST_MIT_2							((uint32_t) 0x00004000)			/*!< Bit 2 */
#define RTC_TST_HOU_Pos							(16U)
#define RTC_TST_HOU_Msk							(0xFUL << RTC_TST_HOU_Pos)		/*!< 0x000F0000 */
#define RTC_TST_HOU								RTC_TST_HOU_Msk					/*!< HOU[3:0] Hour units in BCD format */
#define RTC_TST_HOU_0							((uint32_t) 0x00010000)			/*!< Bit 0 */
#define RTC_TST_HOU_1							((uint32_t) 0x00020000)			/*!< Bit 1 */
#define RTC_TST_HOU_2							((uint32_t) 0x00040000)			/*!< Bit 2 */
#define RTC_TST_HOU_3							((uint32_t) 0x00080000)			/*!< Bit 3 */
#define RTC_TST_HOT_Pos							(20U)
#define RTC_TST_HOT_Msk							(0x3UL << RTC_TST_HOT_Pos)		/*!< 0x00300000 */
#define RTC_TST_HOT 							RTC_TST_HOT_Msk					/*!< HOT[1:0] Hour tens in BCD format */
#define RTC_TST_HOT_0							((uint32_t) 0x00100000)			/*!< Bit 0 */
#define RTC_TST_HOT_1							((uint32_t) 0x00200000)			/*!< Bit 1 */
#define RTC_TST_APM_Pos							(22U)
#define RTC_TST_APM_Msk							(0x1UL << RTC_TST_APM_Pos)		/*!< 0x00400000 */
#define RTC_TST_APM								RTC_TST_APM_Msk					/*!< AM/PM notation */

/*******************  Bits definition for RTC_TSD register  *******************/
#define RTC_TSD_DAU_Pos							(0U)
#define RTC_TSD_DAU_Msk							(0xFUL << RTC_TSD_DAU_Pos)		/*!< 0x0000000F */
#define RTC_TSD_DAU								RTC_TSD_DAU_Msk					/*!< DAU[3:0] Date units in BCD format */
#define RTC_TSD_DAU_0							((uint32_t) 0x00000001)			/*!< Bit 0 */
#define RTC_TSD_DAU_1							((uint32_t) 0x00000002)			/*!< Bit 1 */
#define RTC_TSD_DAU_2							((uint32_t) 0x00000004)			/*!< Bit 2 */
#define RTC_TSD_DAU_3							((uint32_t) 0x00000008)			/*!< Bit 3 */
#define RTC_TSD_DAT_Pos							(4U)
#define RTC_TSD_DAT_Msk							(0x3UL << RTC_TSD_DAT_Pos)		/*!< 0x00000030 */
#define RTC_TSD_DAT								RTC_TSD_DAT_Msk					/*!< DAT[1:0] Date tens in BCD format */
#define RTC_TSD_DAT_0							((uint32_t) 0x00000010)			/*!< Bit 0 */
#define RTC_TSD_DAT_1							((uint32_t) 0x00000020)			/*!< Bit 1 */
#define RTC_TSD_MOU_Pos							(8U)
#define RTC_TSD_MOU_Msk							(0xFUL << RTC_TSD_MOU_Pos)		/*!< 0x00000F00 */
#define RTC_TSD_MOU								RTC_TSD_MOU_Msk					/*!< MOU[3:0] Month units in BCD format */
#define RTC_TSD_MOU_0							((uint32_t) 0x00000100)			/*!< Bit 0 */
#define RTC_TSD_MOU_1							((uint32_t) 0x00000200)			/*!< Bit 1 */
#define RTC_TSD_MOU_2							((uint32_t) 0x00000400)			/*!< Bit 2 */
#define RTC_TSD_MOU_3							((uint32_t) 0x00000800)			/*!< Bit 3 */
#define RTC_TSD_MOT_Pos							(12U)
#define RTC_TSD_MOT_Msk							(0x1UL << RTC_TSD_MOT_Pos)		/*!< 0x00001000 */
#define RTC_TSD_MOT								RTC_TSD_MOT_Msk					/*!< Month tens in BCD format */
#define RTC_TSD_WDU_Pos							(13U)
#define RTC_TSD_WDU_Msk							(0x7UL << RTC_TSD_WDU_Pos)		/*!< 0x0000E000 */
#define RTC_TSD_WDU								RTC_TSD_WDU_Msk					/*!< WDU[2:0] Week day units */
#define RTC_TSD_WDU_0							((uint32_t) 0x00002000)			/*!< Bit 0 */
#define RTC_TSD_WDU_1							((uint32_t) 0x00004000)			/*!< Bit 1 */
#define RTC_TSD_WDU_2							((uint32_t) 0x00008000)			/*!< Bit 2 */
#define RTC_TSD_YRU_Pos							(16U)
#define RTC_TSD_YRU_Msk							(0xFUL << RTC_TSD_YRU_Pos)		/*!< 0x000F0000 */
#define RTC_TSD_YRU   							RTC_TSD_YRU_Msk					/*!< YRU[3:0] Year units in BCD format */
#define RTC_TSD_YRU_0 							((uint32_t) 0x00010000)			/*!< Bit 0 */
#define RTC_TSD_YRU_1 							((uint32_t) 0x00020000)			/*!< Bit 1 */
#define RTC_TSD_YRU_2 							((uint32_t) 0x00040000)			/*!< Bit 2 */
#define RTC_TSD_YRU_3 							((uint32_t) 0x00080000)			/*!< Bit 3 */
#define RTC_TSD_YRT_Pos							(20U)
#define RTC_TSD_YRT_Msk							(0xFUL << RTC_TSD_YRT_Pos)		/*!< 0x00F00000 */
#define RTC_TSD_YRT   							RTC_TSD_YRT_Msk					/*!< YRT[3:0] Year tens in BCD format */
#define RTC_TSD_YRT_0 							((uint32_t) 0x00100000)			/*!< Bit 0 */
#define RTC_TSD_YRT_1							((uint32_t) 0x00200000)			/*!< Bit 1 */
#define RTC_TSD_YRT_2 							((uint32_t) 0x00400000)			/*!< Bit 2 */
#define RTC_TSD_YRT_3 							((uint32_t) 0x00800000)			/*!< Bit 3 */

/******************  Bits definition for RTC_TSSS register  *******************/
#define RTC_TSSS_SSE_Pos						(0U)
#define RTC_TSSS_SSE_Msk						(0xFFFFUL << RTC_TSSS_SSE_Pos)	/*!< 0x0000FFFF */
#define RTC_TSSS_SSE							RTC_TSSS_SSE_Msk				/*!< Sub second value */

/******************  Bits definition for RTC_CALIB register  ******************/
#define RTC_CALIB_CM_Pos						(0U)
#define RTC_CALIB_CM_Msk						(0x1FFUL << RTC_CALIB_CM_Pos)	/*!< 0x000001FF */
#define RTC_CALIB_CM							RTC_CALIB_CM_Msk				/*!< CM[8:0] Calibration minus */
#define RTC_CALIB_CM_0							((uint32_t) 0x00000001)			/*!< Bit 0 */
#define RTC_CALIB_CM_1							((uint32_t) 0x00000002)			/*!< Bit 1 */
#define RTC_CALIB_CM_2							((uint32_t) 0x00000004)			/*!< Bit 2 */
#define RTC_CALIB_CM_3							((uint32_t) 0x00000008)			/*!< Bit 3 */
#define RTC_CALIB_CM_4							((uint32_t) 0x00000010)			/*!< Bit 4 */
#define RTC_CALIB_CM_5							((uint32_t) 0x00000020)			/*!< Bit 5 */
#define RTC_CALIB_CM_6							((uint32_t) 0x00000040)			/*!< Bit 6 */
#define RTC_CALIB_CM_7							((uint32_t) 0x00000080)			/*!< Bit 7 */
#define RTC_CALIB_CM_8							((uint32_t) 0x00000100)			/*!< Bit 8 */
#define RTC_CALIB_CW16_Pos						(13U)
#define RTC_CALIB_CW16_Msk						(0x1UL << RTC_CALIB_CW16_Pos)	/*!< 0x00002000 */
#define RTC_CALIB_CW16							RTC_CALIB_CW16_Msk				/*!< Use a 16-second calibration cycle period */
#define RTC_CALIB_CW8_Pos						(14U)
#define RTC_CALIB_CW8_Msk						(0x1UL << RTC_CALIB_CW8_Pos)	/*!< 0x00004000 */
#define RTC_CALIB_CW8							RTC_CALIB_CW8_Msk				/*!< Use an 8-second calibration cycle period */
#define RTC_CALIB_CP_Pos						(15U)
#define RTC_CALIB_CP_Msk						(0x1UL << RTC_CALIB_CP_Pos)		/*!< 0x00008000 */
#define RTC_CALIB_CP							RTC_CALIB_CP_Msk				/*!< Increase frequency of RTC by 488.5 ppm */

/*****************  Bits definition for RTC_ALRMASS register  *****************/
#define RTC_ALRMASS_SSV_Pos						(0U)
#define RTC_ALRMASS_SSV_Msk						(0x7FFFUL << RTC_ALRMASS_SSV_Pos)
#define RTC_ALRMASS_SSV							RTC_ALRMASS_SSV_Msk
#define RTC_ALRMASS_MASKSSB_Pos					(24U)
#define RTC_ALRMASS_MASKSSB_Msk					(0xFUL << RTC_ALRMASS_MASKSSB_Pos)
#define RTC_ALRMASS_MASKSSB						RTC_ALRMASS_MASKSSB_Msk

/*****************  Bits definition for RTC_ALRMBSS register  *****************/
#define RTC_ALRMBSS_SSV_Pos						(0U)
#define RTC_ALRMBSS_SSV_Msk						(0x7FFFUL << RTC_ALRMBSS_SSV_Pos)
#define RTC_ALRMBSS_SSV							RTC_ALRMBSS_SSV_Msk
#define RTC_ALRMBSS_MASKSSB_Pos					(24U)
#define RTC_ALRMBSS_MASKSSB_Msk					(0xFUL << RTC_ALRMBSS_MASKSSB_Pos)
#define RTC_ALRMBSS_MASKSSB						RTC_ALRMBSS_MASKSSB_Msk

/*******************  Bits definition for RTC_OPT register  *******************/
#define RTC_OPT_TYPE_Pos						(0U)
#define RTC_OPT_TYPE_Msk						(0x1UL << RTC_OPT_TYPE_Pos)
#define RTC_OPT_TYPE							RTC_OPT_TYPE_Msk

/**************  Bits definition for  RTC_TSCWKUPCTRL register  ***************/
#define RTC_TSCWKUPCTRL_WKUPEN_Pos				(0U)
#define RTC_TSCWKUPCTRL_WKUPEN_Msk				(0x1UL << RTC_TSCWKUPCTRL_WKUPEN_Pos)	/*!< 0x00000001 */
#define RTC_TSCWKUPCTRL_WKUPEN					RTC_TSCWKUPCTRL_WKUPEN_Msk		/*!< wakeup enable */
#define RTC_TSCWKUPCTRL_WKUPCNF_Pos				(2U)
#define RTC_TSCWKUPCTRL_WKUPCNF_Msk				(0x1UL << RTC_TSCWKUPCTRL_WKUPCNF_Pos)	/*!< 0x00000004 */
#define RTC_TSCWKUPCTRL_WKUPCNF					RTC_TSCWKUPCTRL_WKUPCNF_Msk		/*!< Wakeup configure flag */
#define RTC_TSCWKUPCTRL_WKUPOFF_Pos				(3U)
#define RTC_TSCWKUPCTRL_WKUPOFF_Msk				(0x1UL << RTC_TSCWKUPCTRL_WKUPOFF_Pos)	/*!< 0x00000008 */
#define RTC_TSCWKUPCTRL_WKUPOFF					RTC_TSCWKUPCTRL_WKUPOFF_Msk		/*!< Last write wakeup timer status */

/***************  Bits definition for  RTC_TSCWKUPCNT register  ***************/
#define RTC_TSCWKUPCNT_CNT_Pos					(0U)
#define RTC_TSCWKUPCNT_CNT_Msk					(0x3FFFUL << RTC_TSCWKUPCNT_CNT_Pos)	/*!< 0x00003FFF */
#define RTC_TSCWKUPCNT_CNT						RTC_TSCWKUPCNT_CNT_Msk			/*!< Wakeup timer load value */

/******************************************************************************/
/*                                                                            */
/*                           Independent WATCHDOG                             */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for IWDG_KEY register  *******************/
#define IWDG_KEY_KEYV_Pos						(0U)
#define IWDG_KEY_KEYV_Msk						(0xFFFFUL << IWDG_KEY_KEYV_Pos)
#define IWDG_KEY_KEYV							IWDG_KEY_KEYV_Msk				/*!< Key value (write only, read 0000h) */

/*****************  Bit definition for IWDG_PREDIV register  ******************/
#define IWDG_PREDIV_PD_Pos						(0U)
#define IWDG_PREDIV_PD_Msk						(0x7UL << IWDG_PREDIV_PD_Pos)
#define IWDG_PREDIV_PD							IWDG_PREDIV_PD_Msk				/*!< PEND[2:0] (Prescaler divider) */
#define IWDG_PREDIV_PD_0						((uint8_t) 0x01)				/*!< Bit 0 */
#define IWDG_PREDIV_PD_1						((uint8_t) 0x02)				/*!< Bit 1 */
#define IWDG_PREDIV_PD_2						((uint8_t) 0x04)				/*!< Bit 2 */

/******************  Bit definition for IWDG_RELY register  *******************/
#define IWDG_RELV_REL_Pos						(0U)
#define IWDG_RELV_REL_Msk						(0xFFFUL << IWDG_RELV_REL_Pos)
#define IWDG_RELV_REL							IWDG_RELV_REL_Msk				/*!< Watchdog counter reload value */

/*******************  Bit definition for IWDG_STS register  *******************/
#define IWDG_STS_PVU_Pos						(0U)
#define IWDG_STS_PVU_Msk						(0x1UL << IWDG_STS_PVU_Pos)
#define IWDG_STS_PVU							IWDG_STS_PVU_Msk				/*!< Watchdog prescaler value update */
#define IWDG_STS_CRVU_Pos						(1U)
#define IWDG_STS_CRVU_Msk						(0x1UL << IWDG_STS_CRVU_Pos)
#define IWDG_STS_CRVU							IWDG_STS_CRVU_Msk				/*!< Watchdog counter reload value update */

/******************************************************************************/
/*                                                                            */
/*                            Window WATCHDOG                                 */
/*                                                                            */
/******************************************************************************/
/******************  Bit definition for WWDG_CTRL register  *******************/
#define WWDG_CTRL_T_Pos							(0U)
#define WWDG_CTRL_T_Msk							(0x7FUL << WWDG_CTRL_T_Pos)
#define WWDG_CTRL_T								WWDG_CTRL_T_Msk					/*!< T[6:0] bits (7-Bit counter (MSB to LSB)) */
#define WWDG_CTRL_T_0							((uint8_t) 0x01)				/*!< Bit 0 */
#define WWDG_CTRL_T_1							((uint8_t) 0x02)				/*!< Bit 1 */
#define WWDG_CTRL_T_2							((uint8_t) 0x04)				/*!< Bit 2 */
#define WWDG_CTRL_T_3							((uint8_t) 0x08)				/*!< Bit 3 */
#define WWDG_CTRL_T_4							((uint8_t) 0x10)				/*!< Bit 4 */
#define WWDG_CTRL_T_5							((uint8_t) 0x20)				/*!< Bit 5 */
#define WWDG_CTRL_T_6							((uint8_t) 0x40)				/*!< Bit 6 */
#define WWDG_CTRL_ACTB_Pos						(7U)
#define WWDG_CTRL_ACTB_Msk						(0x1UL << WWDG_CTRL_ACTB_Pos)
#define WWDG_CTRL_ACTB							WWDG_CTRL_ACTB_Msk				/*!< Activation bit */

/*******************  Bit definition for WWDG_CFG register  *******************/
#define WWDG_CFG_W_Pos							(0U)
#define WWDG_CFG_W_Msk							(0x7FUL << WWDG_CFG_W_Pos)
#define WWDG_CFG_W								WWDG_CFG_W_Msk					/*!< W[6:0] bits (7-bit window value) */
#define WWDG_CFG_W_0							((uint16_t) 0x0001)				/*!< Bit 0 */
#define WWDG_CFG_W_1							((uint16_t) 0x0002)				/*!< Bit 1 */
#define WWDG_CFG_W_2							((uint16_t) 0x0004)				/*!< Bit 2 */
#define WWDG_CFG_W_3							((uint16_t) 0x0008)				/*!< Bit 3 */
#define WWDG_CFG_W_4							((uint16_t) 0x0010)				/*!< Bit 4 */
#define WWDG_CFG_W_5							((uint16_t) 0x0020)				/*!< Bit 5 */
#define WWDG_CFG_W_6							((uint16_t) 0x0040)				/*!< Bit 6 */
#define WWDG_CFG_TIMERB_Pos						(7U)
#define WWDG_CFG_TIMERB_Msk						(0x3UL << WWDG_CFG_TIMERB_Pos)
#define WWDG_CFG_TIMERB							WWDG_CFG_TIMERB_Msk				/*!< WDGTB[1:0] bits (Timer Base) */
#define WWDG_CFG_TIMERB_0						((uint16_t) 0x0080)				/*!< Bit 0 */
#define WWDG_CFG_TIMERB_1						((uint16_t) 0x0100)				/*!< Bit 1 */
#define WWDG_CFG_EWINT_Pos						(9U)
#define WWDG_CFG_EWINT_Msk						(0x1UL << WWDG_CFG_EWINT_Pos)
#define WWDG_CFG_EWINT							WWDG_CFG_EWINT_Msk				/*!< Early Wakeup Interrupt */

/*******************  Bit definition for WWDG_STS register  *******************/
#define WWDG_STS_EWINTF_Pos						(0U)
#define WWDG_STS_EWINTF_Msk						(0x1UL << WWDG_STS_EWINTF_Pos)
#define WWDG_STS_EWINTF							WWDG_STS_EWINTF_Msk				/*!< Early Wakeup Interrupt Flag */

/******************************************************************************/
/*                                                                            */
/*                         Controller Area Network                            */
/*                                                                            */
/******************************************************************************/
/*!< CAN control and status registers */
/******************  Bit definition for CAN_MCTRL register  *******************/
#define CAN_MCTRL_INIRQ_Pos						(0U)
#define CAN_MCTRL_INIRQ_Msk						(0x1UL << CAN_MCTRL_INIRQ_Pos)
#define CAN_MCTRL_INIRQ							CAN_MCTRL_INIRQ_Msk				/*!< Initialization Request */
#define CAN_MCTRL_SLPRQ_Pos						(1U)
#define CAN_MCTRL_SLPRQ_Msk						(0x1UL << CAN_MCTRL_SLPRQ_Pos)
#define CAN_MCTRL_SLPRQ							CAN_MCTRL_SLPRQ_Msk				/*!< Sleep Mode Request */
#define CAN_MCTRL_TXFP_Pos						(2U)
#define CAN_MCTRL_TXFP_Msk						(0x1UL << CAN_MCTRL_TXFP_Pos)
#define CAN_MCTRL_TXFP							CAN_MCTRL_TXFP_Msk				/*!< Transmit DATFIFO Priority */
#define CAN_MCTRL_RFLM_Pos						(3U)
#define CAN_MCTRL_RFLM_Msk						(0x1UL << CAN_MCTRL_RFLM_Pos)
#define CAN_MCTRL_RFLM							CAN_MCTRL_RFLM_Msk				/*!< Receive DATFIFO Locked Mode */
#define CAN_MCTRL_NART_Pos						(4U)
#define CAN_MCTRL_NART_Msk						(0x1UL << CAN_MCTRL_NART_Pos)
#define CAN_MCTRL_NART							CAN_MCTRL_NART_Msk				/*!< No Automatic Retransmission */
#define CAN_MCTRL_AWKUM_Pos						(5U)
#define CAN_MCTRL_AWKUM_Msk						(0x1UL << CAN_MCTRL_AWKUM_Pos)
#define CAN_MCTRL_AWKUM							CAN_MCTRL_AWKUM_Msk				/*!< Automatic Wakeup Mode */
#define CAN_MCTRL_ABOM_Pos						(6U)
#define CAN_MCTRL_ABOM_Msk						(0x1UL << CAN_MCTRL_ABOM_Pos)
#define CAN_MCTRL_ABOM							CAN_MCTRL_ABOM_Msk				/*!< Automatic Bus-Off Management */
#define CAN_MCTRL_TTCM_Pos						(7U)
#define CAN_MCTRL_TTCM_Msk						(0x1UL << CAN_MCTRL_TTCM_Pos)
#define CAN_MCTRL_TTCM							CAN_MCTRL_TTCM_Msk				/*!< Time Triggered Communication Mode */
#define CAN_MCTRL_MRST_Pos						(15U)
#define CAN_MCTRL_MRST_Msk						(0x1UL << CAN_MCTRL_MRST_Pos)
#define CAN_MCTRL_MRST							CAN_MCTRL_MRST_Msk				/*!< CAN software master reset */
#define CAN_MCTRL_DBGF_Pos						(16U)
#define CAN_MCTRL_DBGF_Msk						(0x1UL << CAN_MCTRL_DBGF_Pos)
#define CAN_MCTRL_DBGF							CAN_MCTRL_DBGF_Msk				/*!< CAN Debug freeze */

/*******************  Bit definition for CAN_MSTS register  *******************/
#define CAN_MSTS_INIAK_Pos						(0U)
#define CAN_MSTS_INIAK_Msk						(0x1UL << CAN_MSTS_INIAK_Pos)
#define CAN_MSTS_INIAK							CAN_MSTS_INIAK_Msk				/*!< Initialization Acknowledge */
#define CAN_MSTS_SLPAK_Pos						(1U)
#define CAN_MSTS_SLPAK_Msk						(0x1UL << CAN_MSTS_SLPAK_Pos)
#define CAN_MSTS_SLPAK							CAN_MSTS_SLPAK_Msk				/*!< Sleep Acknowledge */
#define CAN_MSTS_ERRINT_Pos						(2U)
#define CAN_MSTS_ERRINT_Msk						(0x1UL << CAN_MSTS_ERRINT_Pos)
#define CAN_MSTS_ERRINT							CAN_MSTS_ERRINT_Msk				/*!< Error Interrupt */
#define CAN_MSTS_WKUINT_Pos						(3U)
#define CAN_MSTS_WKUINT_Msk						(0x1UL << CAN_MSTS_WKUINT_Pos)
#define CAN_MSTS_WKUINT							CAN_MSTS_WKUINT_Msk				/*!< Wakeup Interrupt */
#define CAN_MSTS_SLAKINT_Pos					(4U)
#define CAN_MSTS_SLAKINT_Msk					(0x1UL << CAN_MSTS_SLAKINT_Pos)
#define CAN_MSTS_SLAKINT						CAN_MSTS_SLAKINT_Msk			/*!< Sleep Acknowledge Interrupt */
#define CAN_MSTS_TXMD_Pos						(8U)
#define CAN_MSTS_TXMD_Msk						(0x1UL << CAN_MSTS_TXMD_Pos)
#define CAN_MSTS_TXMD							CAN_MSTS_TXMD_Msk				/*!< Transmit Mode */
#define CAN_MSTS_RXMD_Pos						(9U)
#define CAN_MSTS_RXMD_Msk						(0x1UL << CAN_MSTS_RXMD_Pos)
#define CAN_MSTS_RXMD							CAN_MSTS_RXMD_Msk				/*!< Receive Mode */
#define CAN_MSTS_LSMP_Pos						(10U)
#define CAN_MSTS_LSMP_Msk						(0x1UL << CAN_MSTS_LSMP_Pos)
#define CAN_MSTS_LSMP							CAN_MSTS_LSMP_Msk				/*!< Last Sample Point */
#define CAN_MSTS_RXS_Pos						(11U)
#define CAN_MSTS_RXS_Msk						(0x1UL << CAN_MSTS_RXS_Pos)
#define CAN_MSTS_RXS							CAN_MSTS_RXS_Msk				/*!< CAN Rx Signal */

/*******************  Bit definition for CAN_TSTS register  *******************/
#define CAN_TSTS_RQCPM0_Pos						(0U)
#define CAN_TSTS_RQCPM0_Msk						(0x1UL << CAN_TSTS_RQCPM0_Pos)
#define CAN_TSTS_RQCPM0							CAN_TSTS_RQCPM0_Msk				/*!< Request Completed Mailbox0 */
#define CAN_TSTS_TXOKM0_Pos						(1U)
#define CAN_TSTS_TXOKM0_Msk						(0x1UL << CAN_TSTS_TXOKM0_Pos)
#define CAN_TSTS_TXOKM0							CAN_TSTS_TXOKM0_Msk				/*!< Transmission OK of Mailbox0 */
#define CAN_TSTS_ALSTM0_Pos						(2U)
#define CAN_TSTS_ALSTM0_Msk						(0x1UL << CAN_TSTS_ALSTM0_Pos)
#define CAN_TSTS_ALSTM0							CAN_TSTS_ALSTM0_Msk				/*!< Arbitration Lost for Mailbox0 */
#define CAN_TSTS_TERRM0_Pos						(3U)
#define CAN_TSTS_TERRM0_Msk						(0x1UL << CAN_TSTS_TERRM0_Pos)
#define CAN_TSTS_TERRM0							CAN_TSTS_TERRM0_Msk				/*!< Transmission Error of Mailbox0 */
#define CAN_TSTS_ABRQM0_Pos						(7U)
#define CAN_TSTS_ABRQM0_Msk						(0x1UL << CAN_TSTS_ABRQM0_Pos)
#define CAN_TSTS_ABRQM0							CAN_TSTS_ABRQM0_Msk				/*!< Abort Request for Mailbox0 */
#define CAN_TSTS_RQCPM1_Pos						(8U)
#define CAN_TSTS_RQCPM1_Msk						(0x1UL << CAN_TSTS_RQCPM1_Pos)
#define CAN_TSTS_RQCPM1							CAN_TSTS_RQCPM1_Msk				/*!< Request Completed Mailbox1 */
#define CAN_TSTS_TXOKM1_Pos						(9U)
#define CAN_TSTS_TXOKM1_Msk						(0x1UL << CAN_TSTS_TXOKM1_Pos)
#define CAN_TSTS_TXOKM1							CAN_TSTS_TXOKM1_Msk				/*!< Transmission OK of Mailbox1 */
#define CAN_TSTS_ALSTM1_Pos						(10U)
#define CAN_TSTS_ALSTM1_Msk						(0x1UL << CAN_TSTS_ALSTM1_Pos)
#define CAN_TSTS_ALSTM1							CAN_TSTS_ALSTM1_Msk				/*!< Arbitration Lost for Mailbox1 */
#define CAN_TSTS_TERRM1_Pos						(11U)
#define CAN_TSTS_TERRM1_Msk						(0x1UL << CAN_TSTS_TERRM1_Pos)
#define CAN_TSTS_TERRM1							CAN_TSTS_TERRM1_Msk				/*!< Transmission Error of Mailbox1 */
#define CAN_TSTS_ABRQM1_Pos						(15U)
#define CAN_TSTS_ABRQM1_Msk						(0x1UL << CAN_TSTS_ABRQM1_Pos)
#define CAN_TSTS_ABRQM1							CAN_TSTS_ABRQM1_Msk				/*!< Abort Request for Mailbox 1 */
#define CAN_TSTS_RQCPM2_Pos						(16U)
#define CAN_TSTS_RQCPM2_Msk						(0x1UL << CAN_TSTS_RQCPM2_Pos)
#define CAN_TSTS_RQCPM2							CAN_TSTS_RQCPM2_Msk				/*!< Request Completed Mailbox2 */
#define CAN_TSTS_TXOKM2_Pos						(17U)
#define CAN_TSTS_TXOKM2_Msk						(0x1UL << CAN_TSTS_TXOKM2_Pos)
#define CAN_TSTS_TXOKM2							CAN_TSTS_TXOKM2_Msk				/*!< Transmission OK of Mailbox 2 */
#define CAN_TSTS_ALSTM2_Pos						(18U)
#define CAN_TSTS_ALSTM2_Msk						(0x1UL << CAN_TSTS_ALSTM2_Pos)
#define CAN_TSTS_ALSTM2							CAN_TSTS_ALSTM2_Msk				/*!< Arbitration Lost for mailbox 2 */
#define CAN_TSTS_TERRM2_Pos						(19U)
#define CAN_TSTS_TERRM2_Msk						(0x1UL << CAN_TSTS_TERRM2_Pos)
#define CAN_TSTS_TERRM2							CAN_TSTS_TERRM2_Msk				/*!< Transmission Error of Mailbox 2 */
#define CAN_TSTS_ABRQM2_Pos						(23U)
#define CAN_TSTS_ABRQM2_Msk						(0x1UL << CAN_TSTS_ABRQM2_Pos)
#define CAN_TSTS_ABRQM2							CAN_TSTS_ABRQM2_Msk				/*!< Abort Request for Mailbox 2 */
#define CAN_TSTS_CODE_Pos						(24U)
#define CAN_TSTS_CODE_Msk						(0x3UL << CAN_TSTS_CODE_Pos)
#define CAN_TSTS_CODE							CAN_TSTS_CODE_Msk				/*!< Mailbox Code */
#define CAN_TSTS_TMEM0_Pos						(26U)
#define CAN_TSTS_TMEM0_Msk						(0x1UL << CAN_TSTS_TMEM0_Pos)
#define CAN_TSTS_TMEM0							CAN_TSTS_TMEM0_Msk				/*!< Transmit Mailbox 0 Empty */
#define CAN_TSTS_TMEM1_Pos						(27U)
#define CAN_TSTS_TMEM1_Msk						(0x1UL << CAN_TSTS_TMEM1_Pos)
#define CAN_TSTS_TMEM1							CAN_TSTS_TMEM1_Msk				/*!< Transmit Mailbox 1 Empty */
#define CAN_TSTS_TMEM2_Pos						(28U)
#define CAN_TSTS_TMEM2_Msk						(0x1UL << CAN_TSTS_TMEM2_Pos)
#define CAN_TSTS_TMEM2							CAN_TSTS_TMEM2_Msk				/*!< Transmit Mailbox 2 Empty */
#define CAN_TSTS_LOWM0_Pos						(29U)
#define CAN_TSTS_LOWM0_Msk						(0x1UL << CAN_TSTS_LOWM0_Pos)
#define CAN_TSTS_LOWM0							CAN_TSTS_LOWM0_Msk				/*!< Lowest Priority Flag for Mailbox 0 */
#define CAN_TSTS_LOWM1_Pos						(30U)
#define CAN_TSTS_LOWM1_Msk						(0x1UL << CAN_TSTS_LOWM1_Pos)
#define CAN_TSTS_LOWM1							CAN_TSTS_LOWM1_Msk				/*!< Lowest Priority Flag for Mailbox 1 */
#define CAN_TSTS_LOWM2_Pos						(31U)
#define CAN_TSTS_LOWM2_Msk						(0x1UL << CAN_TSTS_LOWM2_Pos)
#define CAN_TSTS_LOWM2							CAN_TSTS_LOWM2_Msk				/*!< Lowest Priority Flag for Mailbox 2 */

/*******************  Bit definition for CAN_RFF0 register  *******************/
#define CAN_RFF0_FFMP0_Pos						(0U)
#define CAN_RFF0_FFMP0_Msk						(0x3UL << CAN_RFF0_FFMP0_Pos)
#define CAN_RFF0_FFMP0							CAN_RFF0_FFMP0_Msk				/*!< DATFIFO 0 Message Pending */
#define CAN_RFF0_FFULL0_Pos						(3U)
#define CAN_RFF0_FFULL0_Msk						(0x1UL << CAN_RFF0_FFULL0_Pos)
#define CAN_RFF0_FFULL0							CAN_RFF0_FFULL0_Msk				/*!< DATFIFO 0 Full */
#define CAN_RFF0_FFOVR0_Pos						(4U)
#define CAN_RFF0_FFOVR0_Msk						(0x1UL << CAN_RFF0_FFOVR0_Pos)
#define CAN_RFF0_FFOVR0							CAN_RFF0_FFOVR0_Msk				/*!< DATFIFO 0 Overrun */
#define CAN_RFF0_RFFOM0_Pos						(5U)
#define CAN_RFF0_RFFOM0_Msk						(0x1UL << CAN_RFF0_RFFOM0_Pos)
#define CAN_RFF0_RFFOM0							CAN_RFF0_RFFOM0_Msk				/*!< Release DATFIFO 0 Output Mailbox */

/*******************  Bit definition for CAN_RFF1 register  *******************/
#define CAN_RFF1_FFMP1_Pos						(0U)
#define CAN_RFF1_FFMP1_Msk						(0x3UL << CAN_RFF1_FFMP1_Pos)
#define CAN_RFF1_FFMP1							CAN_RFF1_FFMP1_Msk				/*!< DATFIFO 1 Message Pending */
#define CAN_RFF1_FFULL1_Pos						(3U)
#define CAN_RFF1_FFULL1_Msk						(0x1UL << CAN_RFF1_FFULL1_Pos)
#define CAN_RFF1_FFULL1							CAN_RFF1_FFULL1_Msk				/*!< DATFIFO 1 Full */
#define CAN_RFF1_FFOVR1_Pos						(4U)
#define CAN_RFF1_FFOVR1_Msk						(0x1UL << CAN_RFF1_FFOVR1_Pos)
#define CAN_RFF1_FFOVR1							CAN_RFF1_FFOVR1_Msk				/*!< DATFIFO 1 Overrun */
#define CAN_RFF1_RFFOM1_Pos						(5U)
#define CAN_RFF1_RFFOM1_Msk						(0x1UL << CAN_RFF1_RFFOM1_Pos)
#define CAN_RFF1_RFFOM1							CAN_RFF1_RFFOM1_Msk				/*!< Release DATFIFO 1 Output Mailbox */

/*******************  Bit definition for CAN_INTE register  *******************/
#define CAN_INTE_TMEITE_Pos						(0U)
#define CAN_INTE_TMEITE_Msk						(0x1UL << CAN_INTE_TMEITE_Pos)
#define CAN_INTE_TMEITE							CAN_INTE_TMEITE_Msk				/*!< Transmit Mailbox Empty Interrupt Enable */
#define CAN_INTE_FMPITE0_Pos					(1U)
#define CAN_INTE_FMPITE0_Msk					(0x1UL << CAN_INTE_FMPITE0_Pos)
#define CAN_INTE_FMPITE0						CAN_INTE_FMPITE0_Msk			/*!< DATFIFO Message Pending Interrupt Enable */
#define CAN_INTE_FFITE0_Pos						(2U)
#define CAN_INTE_FFITE0_Msk						(0x1UL << CAN_INTE_FFITE0_Pos)
#define CAN_INTE_FFITE0							CAN_INTE_FFITE0_Msk				/*!< DATFIFO Full Interrupt Enable */
#define CAN_INTE_FOVITE0_Pos					(3U)
#define CAN_INTE_FOVITE0_Msk					(0x1UL << CAN_INTE_FOVITE0_Pos)
#define CAN_INTE_FOVITE0						CAN_INTE_FOVITE0_Msk			/*!< DATFIFO Overrun Interrupt Enable */
#define CAN_INTE_FMPITE1_Pos					(4U)
#define CAN_INTE_FMPITE1_Msk					(0x1UL << CAN_INTE_FMPITE1_Pos)
#define CAN_INTE_FMPITE1						CAN_INTE_FMPITE1_Msk			/*!< DATFIFO Message Pending Interrupt Enable */
#define CAN_INTE_FFITE1_Pos						(5U)
#define CAN_INTE_FFITE1_Msk						(0x1UL << CAN_INTE_FFITE1_Pos)
#define CAN_INTE_FFITE1							CAN_INTE_FFITE1_Msk				/*!< DATFIFO Full Interrupt Enable */
#define CAN_INTE_FOVITE1_Pos					(6U)
#define CAN_INTE_FOVITE1_Msk					(0x1UL << CAN_INTE_FOVITE1_Pos)
#define CAN_INTE_FOVITE1						CAN_INTE_FOVITE1_Msk			/*!< DATFIFO Overrun Interrupt Enable */
#define CAN_INTE_EWGITE_Pos						(8U)
#define CAN_INTE_EWGITE_Msk						(0x1UL << CAN_INTE_EWGITE_Pos)
#define CAN_INTE_EWGITE							CAN_INTE_EWGITE_Msk				/*!< Error Warning Interrupt Enable */
#define CAN_INTE_EPVITE_Pos						(9U)
#define CAN_INTE_EPVITE_Msk						(0x1UL << CAN_INTE_EPVITE_Pos)
#define CAN_INTE_EPVITE							CAN_INTE_EPVITE_Msk				/*!< Error Passive Interrupt Enable */
#define CAN_INTE_BOFITE_Pos						(10U)
#define CAN_INTE_BOFITE_Msk						(0x1UL << CAN_INTE_BOFITE_Pos)
#define CAN_INTE_BOFITE							CAN_INTE_BOFITE_Msk				/*!< Bus-Off Interrupt Enable */
#define CAN_INTE_LECITE_Pos						(11U)
#define CAN_INTE_LECITE_Msk						(0x1UL << CAN_INTE_LECITE_Pos)
#define CAN_INTE_LECITE							CAN_INTE_LECITE_Msk				/*!< Last Error Code Interrupt Enable */
#define CAN_INTE_ERRITE_Pos						(15U)
#define CAN_INTE_ERRITE_Msk						(0x1UL << CAN_INTE_ERRITE_Pos)
#define CAN_INTE_ERRITE							CAN_INTE_ERRITE_Msk				/*!< Error Interrupt Enable */
#define CAN_INTE_WKUITE_Pos						(16U)
#define CAN_INTE_WKUITE_Msk						(0x1UL << CAN_INTE_WKUITE_Pos)
#define CAN_INTE_WKUITE							CAN_INTE_WKUITE_Msk				/*!< Wakeup Interrupt Enable */
#define CAN_INTE_SLKITE_Pos						(17U)
#define CAN_INTE_SLKITE_Msk						(0x1UL << CAN_INTE_SLKITE_Pos)
#define CAN_INTE_SLKITE							CAN_INTE_SLKITE_Msk				/*!< Sleep Interrupt Enable */

/*******************  Bit definition for CAN_ESTS register  *******************/
#define CAN_ESTS_EWGFL_Pos						(0U)
#define CAN_ESTS_EWGFL_Msk						(0x1UL << CAN_ESTS_EWGFL_Pos)
#define CAN_ESTS_EWGFL							CAN_ESTS_EWGFL_Msk				/*!< Error Warning Flag */
#define CAN_ESTS_EPVFL_Pos						(1U)
#define CAN_ESTS_EPVFL_Msk						(0x1UL << CAN_ESTS_EPVFL_Pos)
#define CAN_ESTS_EPVFL							CAN_ESTS_EPVFL_Msk				/*!< Error Passive Flag */
#define CAN_ESTS_BOFFL_Pos						(2U)
#define CAN_ESTS_BOFFL_Msk						(0x1UL << CAN_ESTS_BOFFL_Pos)
#define CAN_ESTS_BOFFL							CAN_ESTS_BOFFL_Msk				/*!< Bus-Off Flag */
#define CAN_ESTS_LEC_Pos						(4U)
#define CAN_ESTS_LEC_Msk						(0x7UL << CAN_ESTS_LEC_Pos)
#define CAN_ESTS_LEC							CAN_ESTS_LEC_Msk				/*!< LEC[2:0] bits (Last Error Code) */
#define CAN_ESTS_LEC_0							((uint32_t) 0x00000010)			/*!< Bit 0 */
#define CAN_ESTS_LEC_1							((uint32_t) 0x00000020)			/*!< Bit 1 */
#define CAN_ESTS_LEC_2							((uint32_t) 0x00000040)			/*!< Bit 2 */
#define CAN_ESTS_TXEC_Pos						(16U)
#define CAN_ESTS_TXEC_Msk						(0xFFUL << CAN_ESTS_TXEC_Pos)
#define CAN_ESTS_TXEC							CAN_ESTS_TXEC_Msk				/*!< Least significant byte of the 9-bit Transmit Error Counter */
#define CAN_ESTS_RXEC_Pos						(24U)
#define CAN_ESTS_RXEC_Msk						(0xFFUL << CAN_ESTS_RXEC_Pos)
#define CAN_ESTS_RXEC							CAN_ESTS_RXEC_Msk				/*!< Receive Error Counter */

/*******************  Bit definition for CAN_BTIM register  *******************/
#define CAN_BTIM_BRTP_Pos						(0U)
#define CAN_BTIM_BRTP_Msk						(0x3FFUL << CAN_BTIM_BRTP_Pos)
#define CAN_BTIM_BRTP							CAN_BTIM_BRTP_Msk				/*!< Baud Rate Prescaler */
#define CAN_BTIM_TBS1_Pos						(16U)
#define CAN_BTIM_TBS1_Msk						(0xFUL << CAN_BTIM_TBS1_Pos)
#define CAN_BTIM_TBS1							CAN_BTIM_TBS1_Msk				/*!< Time Segment 1 */
#define CAN_BTIM_TBS2_Pos						(20U)
#define CAN_BTIM_TBS2_Msk						(0x7UL << CAN_BTIM_TBS2_Pos)
#define CAN_BTIM_TBS2							CAN_BTIM_TBS2_Msk				/*!< Time Segment 2 */
#define CAN_BTIM_RSJW_Pos						(24U)
#define CAN_BTIM_RSJW_Msk						(0x3UL << CAN_BTIM_RSJW_Pos)
#define CAN_BTIM_RSJW							CAN_BTIM_RSJW_Msk				/*!< Resynchronization Jump Width */
#define CAN_BTIM_LBM_Pos						(30U)
#define CAN_BTIM_LBM_Msk						(0x1UL << CAN_BTIM_LBM_Pos)
#define CAN_BTIM_LBM							CAN_BTIM_LBM_Msk				/*!< Loop Back Mode (Debug) */
#define CAN_BTIM_SLM_Pos						(31U)
#define CAN_BTIM_SLM_Msk						(0x1UL << CAN_BTIM_SLM_Pos)
#define CAN_BTIM_SLM							CAN_BTIM_SLM_Msk				/*!< Silent Mode */

/*!< Mailbox registers */
/*******************  Bit definition for CAN_TMI0 register  *******************/
#define CAN_TMI0_TXRQ_Pos						(0U)
#define CAN_TMI0_TXRQ_Msk						(0x1UL << CAN_TMI0_TXRQ_Pos)
#define CAN_TMI0_TXRQ							CAN_TMI0_TXRQ_Msk				/*!< Transmit Mailbox Request */
#define CAN_TMI0_RTRQ_Pos						(1U)
#define CAN_TMI0_RTRQ_Msk						(0x1UL << CAN_TMI0_RTRQ_Pos)
#define CAN_TMI0_RTRQ							CAN_TMI0_RTRQ_Msk				/*!< Remote Transmission Request */
#define CAN_TMI0_IDE_Pos						(2U)
#define CAN_TMI0_IDE_Msk						(0x1UL << CAN_TMI0_IDE_Pos)
#define CAN_TMI0_IDE							CAN_TMI0_IDE_Msk				/*!< Identifier Extension */
#define CAN_TMI0_EXTID_Pos						(3U)
#define CAN_TMI0_EXTID_Msk						(0x3FFFFUL << CAN_TMI0_EXTID_Pos)
#define CAN_TMI0_EXTID							CAN_TMI0_EXTID_Msk				/*!< Extended Identifier */
#define CAN_TMI0_STDID_Pos						(21U)
#define CAN_TMI0_STDID_Msk						(0x7FFUL << CAN_TMI0_STDID_Pos)
#define CAN_TMI0_STDID							CAN_TMI0_STDID_Msk				/*!< Standard Identifier or Extended Identifier */

/******************  Bit definition for CAN_TMDT0 register  *******************/
#define CAN_TMDT0_DLC_Pos						(0U)
#define CAN_TMDT0_DLC_Msk						(0xFUL << CAN_TMDT0_DLC_Pos)
#define CAN_TMDT0_DLC							CAN_TMDT0_DLC_Msk				/*!< Data Length Code */
#define CAN_TMDT0_TGT_Pos						(8U)
#define CAN_TMDT0_TGT_Msk						(0x1UL << CAN_TMDT0_TGT_Pos)
#define CAN_TMDT0_TGT							CAN_TMDT0_TGT_Msk				/*!< Transmit Global Time */
#define CAN_TMDT0_MTIM_Pos						(16U)
#define CAN_TMDT0_MTIM_Msk						(0xFFFFUL << CAN_TMDT0_MTIM_Pos)
#define CAN_TMDT0_MTIM							CAN_TMDT0_MTIM_Msk				/*!< Message Time Stamp */

/******************  Bit definition for CAN_TMDL0 register  *******************/
#define CAN_TMDL0_DATA0_Pos						(0U)
#define CAN_TMDL0_DATA0_Msk						(0xFFUL << CAN_TMDL0_DATA0_Pos)
#define CAN_TMDL0_DATA0							CAN_TMDL0_DATA0_Msk				/*!< Data byte 0 */
#define CAN_TMDL0_DATA1_Pos						(8U)
#define CAN_TMDL0_DATA1_Msk						(0xFFUL << CAN_TMDL0_DATA1_Pos)
#define CAN_TMDL0_DATA1							CAN_TMDL0_DATA1_Msk				/*!< Data byte 1 */
#define CAN_TMDL0_DATA2_Pos						(16U)
#define CAN_TMDL0_DATA2_Msk						(0xFFUL << CAN_TMDL0_DATA2_Pos)
#define CAN_TMDL0_DATA2							CAN_TMDL0_DATA2_Msk				/*!< Data byte 2 */
#define CAN_TMDL0_DATA3_Pos						(24U)
#define CAN_TMDL0_DATA3_Msk						(0xFFUL << CAN_TMDL0_DATA3_Pos)
#define CAN_TMDL0_DATA3							CAN_TMDL0_DATA3_Msk				/*!< Data byte 3 */

/******************  Bit definition for CAN_TMDH0 register  *******************/
#define CAN_TMDH0_DATA4_Pos						(0U)
#define CAN_TMDH0_DATA4_Msk						(0xFFUL << CAN_TMDH0_DATA4_Pos)
#define CAN_TMDH0_DATA4							CAN_TMDH0_DATA4_Msk				/*!< Data byte 4 */
#define CAN_TMDH0_DATA5_Pos						(8U)
#define CAN_TMDH0_DATA5_Msk						(0xFFUL << CAN_TMDH0_DATA5_Pos)
#define CAN_TMDH0_DATA5							CAN_TMDH0_DATA5_Msk				/*!< Data byte 5 */
#define CAN_TMDH0_DATA6_Pos						(16U)
#define CAN_TMDH0_DATA6_Msk						(0xFFUL << CAN_TMDH0_DATA6_Pos)
#define CAN_TMDH0_DATA6							CAN_TMDH0_DATA6_Msk				/*!< Data byte 6 */
#define CAN_TMDH0_DATA7_Pos						(24U)
#define CAN_TMDH0_DATA7_Msk						(0xFFUL << CAN_TMDH0_DATA7_Pos)
#define CAN_TMDH0_DATA7							CAN_TMDH0_DATA7_Msk				/*!< Data byte 7 */

/*******************  Bit definition for CAN_TMI1 register  *******************/
#define CAN_TMI1_TXRQ_Pos						(0U)
#define CAN_TMI1_TXRQ_Msk						(0x1UL << CAN_TMI1_TXRQ_Pos)
#define CAN_TMI1_TXRQ							CAN_TMI1_TXRQ_Msk				/*!< Transmit Mailbox Request */
#define CAN_TMI1_RTRQ_Pos						(1U)
#define CAN_TMI1_RTRQ_Msk						(0x1UL << CAN_TMI1_RTRQ_Pos)
#define CAN_TMI1_RTRQ							CAN_TMI1_RTRQ_Msk				/*!< Remote Transmission Request */
#define CAN_TMI1_IDE_Pos						(2U)
#define CAN_TMI1_IDE_Msk						(0x1UL << CAN_TMI1_IDE_Pos)
#define CAN_TMI1_IDE							CAN_TMI1_IDE_Msk				/*!< Identifier Extension */
#define CAN_TMI1_EXTID_Pos						(3U)
#define CAN_TMI1_EXTID_Msk						(0x3FFFFUL << CAN_TMI1_EXTID_Pos)
#define CAN_TMI1_EXTID							CAN_TMI1_EXTID_Msk				/*!< Extended Identifier */
#define CAN_TMI1_STDID_Pos						(21U)
#define CAN_TMI1_STDID_Msk						(0x7FFUL << CAN_TMI1_STDID_Pos)
#define CAN_TMI1_STDID							CAN_TMI1_STDID_Msk				/*!< Standard Identifier or Extended Identifier */

/******************  Bit definition for CAN_TMDT1 register  *******************/
#define CAN_TMDT1_DLC_Pos						(0U)
#define CAN_TMDT1_DLC_Msk						(0xFUL << CAN_TMDT1_DLC_Pos)
#define CAN_TMDT1_DLC							CAN_TMDT1_DLC_Msk				/*!< Data Length Code */
#define CAN_TMDT1_TGT_Pos						(8U)
#define CAN_TMDT1_TGT_Msk						(0x1UL << CAN_TMDT1_TGT_Pos)
#define CAN_TMDT1_TGT							CAN_TMDT1_TGT_Msk				/*!< Transmit Global Time */
#define CAN_TMDT1_MTIM_Pos						(16U)
#define CAN_TMDT1_MTIM_Msk						(0xFFFFUL << CAN_TMDT1_MTIM_Pos)
#define CAN_TMDT1_MTIM							CAN_TMDT1_MTIM_Msk				/*!< Message Time Stamp */

/******************  Bit definition for CAN_TMDL1 register  *******************/
#define CAN_TMDL1_DATA0_Pos						(0U)
#define CAN_TMDL1_DATA0_Msk						(0xFFUL << CAN_TMDL1_DATA0_Pos)
#define CAN_TMDL1_DATA0							CAN_TMDL1_DATA0_Msk				/*!< Data byte 0 */
#define CAN_TMDL1_DATA1_Pos						(8U)
#define CAN_TMDL1_DATA1_Msk						(0xFFUL << CAN_TMDL1_DATA1_Pos)
#define CAN_TMDL1_DATA1							CAN_TMDL1_DATA1_Msk				/*!< Data byte 1 */
#define CAN_TMDL1_DATA2_Pos						(16U)
#define CAN_TMDL1_DATA2_Msk						(0xFFUL << CAN_TMDL1_DATA2_Pos)
#define CAN_TMDL1_DATA2							CAN_TMDL1_DATA2_Msk				/*!< Data byte 2 */
#define CAN_TMDL1_DATA3_Pos						(24U)
#define CAN_TMDL1_DATA3_Msk						(0xFFUL << CAN_TMDL1_DATA3_Pos)
#define CAN_TMDL1_DATA3							CAN_TMDL1_DATA3_Msk				/*!< Data byte 3 */

/******************  Bit definition for CAN_TMDH1 register  *******************/
#define CAN_TMDH1_DATA4_Pos						(0U)
#define CAN_TMDH1_DATA4_Msk						(0xFFUL << CAN_TMDH1_DATA4_Pos)
#define CAN_TMDH1_DATA4							CAN_TMDH1_DATA4_Msk				/*!< Data byte 4 */
#define CAN_TMDH1_DATA5_Pos						(8U)
#define CAN_TMDH1_DATA5_Msk						(0xFFUL << CAN_TMDH1_DATA5_Pos)
#define CAN_TMDH1_DATA5							CAN_TMDH1_DATA5_Msk				/*!< Data byte 5 */
#define CAN_TMDH1_DATA6_Pos						(16U)
#define CAN_TMDH1_DATA6_Msk						(0xFFUL << CAN_TMDH1_DATA6_Pos)
#define CAN_TMDH1_DATA6							CAN_TMDH1_DATA6_Msk				/*!< Data byte 6 */
#define CAN_TMDH1_DATA7_Pos						(24U)
#define CAN_TMDH1_DATA7_Msk						(0xFFUL << CAN_TMDH1_DATA7_Pos)
#define CAN_TMDH1_DATA7							CAN_TMDH1_DATA7_Msk				/*!< Data byte 7 */

/*******************  Bit definition for CAN_TMI2 register  *******************/
#define CAN_TMI2_TXRQ_Pos						(0U)
#define CAN_TMI2_TXRQ_Msk						(0x1UL << CAN_TMI2_TXRQ_Pos)
#define CAN_TMI2_TXRQ							CAN_TMI12_TXRQ_Msk				/*!< Transmit Mailbox Request */
#define CAN_TMI2_RTRQ_Pos						(1U)
#define CAN_TMI2_RTRQ_Msk						(0x1UL << CAN_TMI2_RTRQ_Pos)
#define CAN_TMI2_RTRQ							CAN_TMI2_RTRQ_Msk				/*!< Remote Transmission Request */
#define CAN_TMI2_IDE_Pos						(2U)
#define CAN_TMI2_IDE_Msk						(0x1UL << CAN_TMI2_IDE_Pos)
#define CAN_TMI2_IDE							CAN_TMI2_IDE_Msk				/*!< Identifier Extension */
#define CAN_TMI2_EXTID_Pos						(3U)
#define CAN_TMI2_EXTID_Msk						(0x3FFFFUL << CAN_TMI2_EXTID_Pos)
#define CAN_TMI2_EXTID							CAN_TMI2_EXTID_Msk				/*!< Extended identifier */
#define CAN_TMI2_STDID_Pos						(21U)
#define CAN_TMI2_STDID_Msk						(0x7FFUL << CAN_TMI2_STDID_Pos)
#define CAN_TMI2_STDID							CAN_TMI2_STDID_Msk				/*!< Standard Identifier or Extended Identifier */

/******************  Bit definition for CAN_TMDT2 register  *******************/
#define CAN_TMDT2_DLC_Pos						(0U)
#define CAN_TMDT2_DLC_Msk						(0xFUL << CAN_TMDT2_DLC_Pos)
#define CAN_TMDT2_DLC							CAN_TMDT2_DLC_Msk				/*!< Data Length Code */
#define CAN_TMDT2_TGT_Pos						(8U)
#define CAN_TMDT2_TGT_Msk						(0x1UL << CAN_TMDT2_TGT_Pos)
#define CAN_TMDT2_TGT							CAN_TMDT2_TGT_Msk				/*!< Transmit Global Time */
#define CAN_TMDT2_MTIM_Pos						(16U)
#define CAN_TMDT2_MTIM_Msk						(0xFFFFUL << CAN_TMDT2_MTIM_Pos)
#define CAN_TMDT2_MTIM							CAN_TMDT2_MTIM_Msk				/*!< Message Time Stamp */

/******************  Bit definition for CAN_TMDL2 register  *******************/
#define CAN_TMDL2_DATA0_Pos						(0U)
#define CAN_TMDL2_DATA0_Msk						(0xFFUL << CAN_TMDL2_DATA0_Pos)
#define CAN_TMDL2_DATA0							CAN_TMDL2_DATA0_Msk				/*!< Data byte 0 */
#define CAN_TMDL2_DATA1_Pos						(8U)
#define CAN_TMDL2_DATA1_Msk						(0xFFUL << CAN_TMDL2_DATA1_Pos)
#define CAN_TMDL2_DATA1							CAN_TMDL2_DATA1_Msk				/*!< Data byte 1 */
#define CAN_TMDL2_DATA2_Pos						(16U)
#define CAN_TMDL2_DATA2_Msk						(0xFFUL << CAN_TMDL2_DATA2_Pos)
#define CAN_TMDL2_DATA2							CAN_TMDL2_DATA2_Msk				/*!< Data byte 2 */
#define CAN_TMDL2_DATA3_Pos						(24U)
#define CAN_TMDL2_DATA3_Msk						(0xFFUL << CAN_TMDL2_DATA3_Pos)
#define CAN_TMDL2_DATA3							CAN_TMDL2_DATA3_Msk				/*!< Data byte 3 */

/******************  Bit definition for CAN_TMDH2 register  *******************/
#define CAN_TMDH2_DATA4_Pos						(0U)
#define CAN_TMDH2_DATA4_Msk						(0xFFUL << CAN_TMDH2_DATA4_Pos)
#define CAN_TMDH2_DATA4							CAN_TMDH2_DATA4_Msk				/*!< Data byte 4 */
#define CAN_TMDH2_DATA5_Pos						(8U)
#define CAN_TMDH2_DATA5_Msk						(0xFFUL << CAN_TMDH2_DATA5_Pos)
#define CAN_TMDH2_DATA5							CAN_TMDH2_DATA5_Msk				/*!< Data byte 5 */
#define CAN_TMDH2_DATA6_Pos						(16U)
#define CAN_TMDH2_DATA6_Msk						(0xFFUL << CAN_TMDH2_DATA6_Pos)
#define CAN_TMDH2_DATA6							CAN_TMDH2_DATA6_Msk				/*!< Data byte 6 */
#define CAN_TMDH2_DATA7_Pos						(24U)
#define CAN_TMDH2_DATA7_Msk						(0xFFUL << CAN_TMDH2_DATA7_Pos)
#define CAN_TMDH2_DATA7							CAN_TMDH2_DATA7_Msk				/*!< Data byte 7 */

/*******************  Bit definition for CAN_RMI0 register  *******************/
#define CAN_RMI0_RTRQ_Pos						(1U)
#define CAN_RMI0_RTRQ_Msk						(0x1UL << CAN_RMI0_RTRQ_Pos)
#define CAN_RMI0_RTRQ							CAN_RMI0_RTRQ_Msk				/*!< Remote Transmission Request */	
#define CAN_RMI0_IDE_Pos						(2U)
#define CAN_RMI0_IDE_Msk						(0x1UL << CAN_RMI0_IDE_Pos)
#define CAN_RMI0_IDE							CAN_RMI0_IDE_Msk				/*!< Identifier Extension */
#define CAN_RMI0_EXTID_Pos						(3U)
#define CAN_RMI0_EXTID_Msk						(0x3FFFFUL << CAN_RMI0_EXTID_Pos)
#define CAN_RMI0_EXTID							CAN_RMI0_EXTID_Msk				/*!< Extended Identifier */
#define CAN_RMI0_STDID_Pos						(21U)
#define CAN_RMI0_STDID_Msk						(0x7FFUL << CAN_RMI0_STDID_Pos)
#define CAN_RMI0_STDID							CAN_RMI0_STDID_Msk				/*!< Standard Identifier or Extended Identifier */

/******************  Bit definition for CAN_RMDT0 register  *******************/
#define CAN_RMDT0_DLC_Pos						(0U)
#define CAN_RMDT0_DLC_Msk						(0xFUL << CAN_RMDT0_DLC_Pos)
#define CAN_RMDT0_DLC							CAN_RMDT0_DLC_Msk				/*!< Data Length Code */
#define CAN_RMDT0_FMI_Pos						(8U)
#define CAN_RMDT0_FMI_Msk						(0xFFUL << CAN_RMDT0_FMI_Pos)
#define CAN_RMDT0_FMI							CAN_RMDT0_FMI_Msk				/*!< Filter Match Index */
#define CAN_RMDT0_MTIM_Pos						(16U)
#define CAN_RMDT0_MTIM_Msk						(0xFFFFUL << CAN_RMDT0_MTIM_Pos)
#define CAN_RMDT0_MTIM							CAN_RMDT0_MTIM_Msk				/*!< Message Time Stamp */

/******************  Bit definition for CAN_RMDL0 register  *******************/
#define CAN_RMDL0_DATA0_Pos						(0U)
#define CAN_RMDL0_DATA0_Msk						(0xFFUL << CAN_RMDL0_DATA0_Pos)
#define CAN_RMDL0_DATA0							CAN_RMDL0_DATA0_Msk				/*!< Data byte 0 */
#define CAN_RMDL0_DATA1_Pos						(8U)
#define CAN_RMDL0_DATA1_Msk						(0xFFUL << CAN_RMDL0_DATA1_Pos)
#define CAN_RMDL0_DATA1							CAN_RMDL0_DATA1_Msk				/*!< Data byte 1 */
#define CAN_RMDL0_DATA2_Pos						(16U)
#define CAN_RMDL0_DATA2_Msk						(0xFFUL << CAN_RMDL0_DATA2_Pos)
#define CAN_RMDL0_DATA2							CAN_RMDL0_DATA2_Msk				/*!< Data byte 2 */
#define CAN_RMDL0_DATA3_Pos						(24U)
#define CAN_RMDL0_DATA3_Msk						(0xFFUL << CAN_RMDL0_DATA3_Pos)
#define CAN_RMDL0_DATA3							CAN_RMDL0_DATA3_Msk				/*!< Data byte 3 */

/******************  Bit definition for CAN_RMDH0 register  *******************/
#define CAN_RMDH0_DATA4_Pos						(0U)
#define CAN_RMDH0_DATA4_Msk						(0xFFUL << CAN_RMDH0_DATA4_Pos)
#define CAN_RMDH0_DATA4							CAN_RMDH0_DATA4_Msk				/*!< Data byte 4 */
#define CAN_RMDH0_DATA5_Pos						(8U)
#define CAN_RMDH0_DATA5_Msk						(0xFFUL << CAN_RMDH0_DATA5_Pos)
#define CAN_RMDH0_DATA5							CAN_RMDH0_DATA5_Msk				/*!< Data byte 5 */
#define CAN_RMDH0_DATA6_Pos						(16U)
#define CAN_RMDH0_DATA6_Msk						(0xFFUL << CAN_RMDH0_DATA6_Pos)
#define CAN_RMDH0_DATA6							CAN_RMDH0_DATA6_Msk				/*!< Data byte 6 */
#define CAN_RMDH0_DATA7_Pos						(24U)
#define CAN_RMDH0_DATA7_Msk						(0xFFUL << CAN_RMDH0_DATA7_Pos)
#define CAN_RMDH0_DATA7							CAN_RMDH0_DATA7_Msk				/*!< Data byte 7 */

/*******************  Bit definition for CAN_RMI1 register  *******************/
#define CAN_RMI1_RTRQ_Pos						(1U)
#define CAN_RMI1_RTRQ_Msk						(0x1UL << CAN_RMI1_RTRQ_Pos)
#define CAN_RMI1_RTRQ							CAN_RMI1_RTRQ_Msk				/*!< Remote Transmission Request */
#define CAN_RMI1_IDE_Pos						(2U)
#define CAN_RMI1_IDE_Msk						(0x1UL << CAN_RMI1_IDE_Pos)
#define CAN_RMI1_IDE							CAN_RMI1_IDE_Msk				/*!< Identifier Extension */
#define CAN_RMI1_EXTID_Pos						(3U)
#define CAN_RMI1_EXTID_Msk						(0x3FFFFUL << CAN_RMI1_EXTID_Pos)
#define CAN_RMI1_EXTID							CAN_RMI1_EXTID_Msk				/*!< Extended identifier */
#define CAN_RMI1_STDID_Pos						(21U)
#define CAN_RMI1_STDID_Msk						(0x7FFUL << CAN_RMI1_STDID_Pos)
#define CAN_RMI1_STDID							CAN_RMI1_STDID_Msk				/*!< Standard Identifier or Extended Identifier */

/******************  Bit definition for CAN_RMDT1 register  *******************/
#define CAN_RMDT1_DLC_Pos						(0U)
#define CAN_RMDT1_DLC_Msk						(0xFUL << CAN_RMDT1_DLC_Pos)
#define CAN_RMDT1_DLC							CAN_RMDT1_DLC_Msk				/*!< Data Length Code */
#define CAN_RMDT1_FMI_Pos						(8U)
#define CAN_RMDT1_FMI_Msk						(0xFFUL << CAN_RMDT1_FMI_Pos)
#define CAN_RMDT1_FMI							CAN_RMDT1_FMI_Msk				/*!< Filter Match Index */
#define CAN_RMDT1_MTIM_Pos						(16U)
#define CAN_RMDT1_MTIM_Msk						(0xFFFFUL << CAN_RMDT1_MTIM_Pos)
#define CAN_RMDT1_MTIM							CAN_RMDT1_MTIM_Msk				/*!< Message Time Stamp */

/******************  Bit definition for CAN_RMDL1 register  *******************/
#define CAN_RMDL1_DATA0_Pos						(0U)
#define CAN_RMDL1_DATA0_Msk						(0xFFUL << CAN_RMDL1_DATA0_Pos)
#define CAN_RMDL1_DATA0							CAN_RMDL1_DATA0_Msk				/*!< Data byte 0 */
#define CAN_RMDL1_DATA1_Pos						(8U)
#define CAN_RMDL1_DATA1_Msk						(0xFFUL << CAN_RMDL1_DATA1_Pos)
#define CAN_RMDL1_DATA1							CAN_RMDL1_DATA1_Msk				/*!< Data byte 1 */
#define CAN_RMDL1_DATA2_Pos						(16U)
#define CAN_RMDL1_DATA2_Msk						(0xFFUL << CAN_RMDL1_DATA2_Pos)
#define CAN_RMDL1_DATA2							CAN_RMDL1_DATA2_Msk				/*!< Data byte 2 */
#define CAN_RMDL1_DATA3_Pos						(24U)
#define CAN_RMDL1_DATA3_Msk						(0xFFUL << CAN_RMDL1_DATA3_Pos)
#define CAN_RMDL1_DATA3							CAN_RMDL1_DATA3_Msk				/*!< Data byte 3 */

/******************  Bit definition for CAN_RMDH1 register  *******************/
#define CAN_RMDH1_DATA4_Pos						(0U)
#define CAN_RMDH1_DATA4_Msk						(0xFFUL << CAN_RMDH1_DATA4_Pos)
#define CAN_RMDH1_DATA4							CAN_RMDH1_DATA4_Msk				/*!< Data byte 4 */
#define CAN_RMDH1_DATA5_Pos						(8U)
#define CAN_RMDH1_DATA5_Msk						(0xFFUL << CAN_RMDH1_DATA5_Pos)
#define CAN_RMDH1_DATA5							CAN_RMDH1_DATA5_Msk				/*!< Data byte 5 */
#define CAN_RMDH1_DATA6_Pos						(16U)
#define CAN_RMDH1_DATA6_Msk						(0xFFUL << CAN_RMDH1_DATA6_Pos)
#define CAN_RMDH1_DATA6							CAN_RMDH1_DATA6_Msk				/*!< Data byte 6 */
#define CAN_RMDH1_DATA7_Pos						(24U)
#define CAN_RMDH1_DATA7_Msk						(0xFFUL << CAN_RMDH1_DATA7_Pos)
#define CAN_RMDH1_DATA7							CAN_RMDH1_DATA7_Msk				/*!< Data byte 7 */

/*!< CAN filter registers */
/*******************  Bit definition for CAN_FMC register  ********************/
#define CAN_FMC_FINITM_Pos						(0U)
#define CAN_FMC_FINITM_Msk						(0x1UL << CAN_FMC_FINITM_Pos)
#define CAN_FMC_FINITM							CAN_FMC_FINITM_Msk				/*!< Filter Init Mode */

/*******************  Bit definition for CAN_FM1 register  ********************/
#define CAN_FM1_FB0_Pos							(0U)
#define CAN_FM1_FB0_Msk							(0x1UL << CAN_FM1_FB0_Pos)
#define CAN_FM1_FB0								CAN_FM1_FB0_Msk					/*!< Filter Init Mode bit 0 */
#define CAN_FM1_FB1_Pos							(1U)
#define CAN_FM1_FB1_Msk							(0x1UL << CAN_FM1_FB1_Pos)
#define CAN_FM1_FB1								CAN_FM1_FB1_Msk					/*!< Filter Init Mode bit 1 */
#define CAN_FM1_FB2_Pos							(2U)
#define CAN_FM1_FB2_Msk							(0x1UL << CAN_FM1_FB2_Pos)
#define CAN_FM1_FB2								CAN_FM1_FB2_Msk					/*!< Filter Init Mode bit 2 */
#define CAN_FM1_FB3_Pos							(3U)
#define CAN_FM1_FB3_Msk							(0x1UL << CAN_FM1_FB3_Pos)
#define CAN_FM1_FB3								CAN_FM1_FB3_Msk					/*!< Filter Init Mode bit 3 */
#define CAN_FM1_FB4_Pos							(4U)
#define CAN_FM1_FB4_Msk							(0x1UL << CAN_FM1_FB4_Pos)
#define CAN_FM1_FB4								CAN_FM1_FB4_Msk					/*!< Filter Init Mode bit 4 */
#define CAN_FM1_FB5_Pos							(5U)
#define CAN_FM1_FB5_Msk							(0x1UL << CAN_FM1_FB5_Pos)
#define CAN_FM1_FB5								CAN_FM1_FB5_Msk					/*!< Filter Init Mode bit 5 */
#define CAN_FM1_FB6_Pos							(6U)
#define CAN_FM1_FB6_Msk							(0x1UL << CAN_FM1_FB6_Pos)
#define CAN_FM1_FB6								CAN_FM1_FB6_Msk					/*!< Filter Init Mode bit 6 */
#define CAN_FM1_FB7_Pos							(7U)
#define CAN_FM1_FB7_Msk							(0x1UL << CAN_FM1_FB7_Pos)
#define CAN_FM1_FB7								CAN_FM1_FB7_Msk					/*!< Filter Init Mode bit 7 */
#define CAN_FM1_FB8_Pos							(8U)
#define CAN_FM1_FB8_Msk							(0x1UL << CAN_FM1_FB8_Pos)
#define CAN_FM1_FB8								CAN_FM1_FB8_Msk					/*!< Filter Init Mode bit 8 */
#define CAN_FM1_FB9_Pos							(9U)
#define CAN_FM1_FB9_Msk							(0x1UL << CAN_FM1_FB9_Pos)
#define CAN_FM1_FB9								CAN_FM1_FB9_Msk					/*!< Filter Init Mode bit 9 */
#define CAN_FM1_FB10_Pos						(10U)
#define CAN_FM1_FB10_Msk						(0x1UL << CAN_FM1_FB10_Pos)
#define CAN_FM1_FB10							CAN_FM1_FB10_Msk				/*!< Filter Init Mode bit 10 */
#define CAN_FM1_FB11_Pos						(11U)
#define CAN_FM1_FB11_Msk						(0x1UL << CAN_FM1_FB11_Pos)
#define CAN_FM1_FB11							CAN_FM1_FB11_Msk				/*!< Filter Init Mode bit 11 */
#define CAN_FM1_FB12_Pos						(12U)
#define CAN_FM1_FB12_Msk						(0x1UL << CAN_FM1_FB12_Pos)
#define CAN_FM1_FB12							CAN_FM1_FB12_Msk				/*!< Filter Init Mode bit 12 */
#define CAN_FM1_FB13_Pos						(13U)
#define CAN_FM1_FB13_Msk						(0x1UL << CAN_FM1_FB13_Pos)
#define CAN_FM1_FB13							CAN_FM1_FB13_Msk				/*!< Filter Init Mode bit 13 */

/*******************  Bit definition for CAN_FS1 register  ********************/
#define CAN_FS1_FSC0_Pos						(0U)
#define CAN_FS1_FSC0_Msk						(0x1UL << CAN_FS1_FSC0_Pos)
#define CAN_FS1_FSC0							CAN_FS1_FSC0_Msk				/*!< Filter Scale Configuration bit 0 */
#define CAN_FS1_FSC1_Pos						(1U)
#define CAN_FS1_FSC1_Msk						(0x1UL << CAN_FS1_FSC1_Pos)
#define CAN_FS1_FSC1							CAN_FS1_FSC1_Msk				/*!< Filter Scale Configuration bit 1 */
#define CAN_FS1_FSC2_Pos						(2U)
#define CAN_FS1_FSC2_Msk						(0x1UL << CAN_FS1_FSC2_Pos)
#define CAN_FS1_FSC2							CAN_FS1_FSC2_Msk				/*!< Filter Scale Configuration bit 2 */
#define CAN_FS1_FSC3_Pos						(3U)
#define CAN_FS1_FSC3_Msk						(0x1UL << CAN_FS1_FSC3_Pos)
#define CAN_FS1_FSC3							CAN_FS1_FSC3_Msk				/*!< Filter Scale Configuration bit 3 */
#define CAN_FS1_FSC4_Pos						(4U)
#define CAN_FS1_FSC4_Msk						(0x1UL << CAN_FS1_FSC4_Pos)
#define CAN_FS1_FSC4							CAN_FS1_FSC4_Msk				/*!< Filter Scale Configuration bit 4 */
#define CAN_FS1_FSC5_Pos						(5U)
#define CAN_FS1_FSC5_Msk						(0x1UL << CAN_FS1_FSC5_Pos)
#define CAN_FS1_FSC5							CAN_FS1_FSC5_Msk				/*!< Filter Scale Configuration bit 5 */
#define CAN_FS1_FSC6_Pos						(6U)
#define CAN_FS1_FSC6_Msk						(0x1UL << CAN_FS1_FSC6_Pos)
#define CAN_FS1_FSC6							CAN_FS1_FSC6_Msk				/*!< Filter Scale Configuration bit 6 */
#define CAN_FS1_FSC7_Pos						(7U)
#define CAN_FS1_FSC7_Msk						(0x1UL << CAN_FS1_FSC7_Pos)
#define CAN_FS1_FSC7							CAN_FS1_FSC7_Msk				/*!< Filter Scale Configuration bit 7 */
#define CAN_FS1_FSC8_Pos						(8U)
#define CAN_FS1_FSC8_Msk						(0x1UL << CAN_FS1_FSC8_Pos)
#define CAN_FS1_FSC8							CAN_FS1_FSC8_Msk				/*!< Filter Scale Configuration bit 8 */
#define CAN_FS1_FSC9_Pos						(9U)
#define CAN_FS1_FSC9_Msk						(0x1UL << CAN_FS1_FSC9_Pos)
#define CAN_FS1_FSC9							CAN_FS1_FSC9_Msk				/*!< Filter Scale Configuration bit 9 */
#define CAN_FS1_FSC10_Pos						(10U)
#define CAN_FS1_FSC10_Msk						(0x1UL << CAN_FS1_FSC10_Pos)
#define CAN_FS1_FSC10							CAN_FS1_FSC10_Msk				/*!< Filter Scale Configuration bit 10 */
#define CAN_FS1_FSC11_Pos						(11U)
#define CAN_FS1_FSC11_Msk						(0x1UL << CAN_FS1_FSC11_Pos)
#define CAN_FS1_FSC11							CAN_FS1_FSC11_Msk				/*!< Filter Scale Configuration bit 11 */
#define CAN_FS1_FSC12_Pos						(12U)
#define CAN_FS1_FSC12_Msk						(0x1UL << CAN_FS1_FSC12_Pos)
#define CAN_FS1_FSC12							CAN_FS1_FSC12_Msk				/*!< Filter Scale Configuration bit 12 */
#define CAN_FS1_FSC13_Pos						(13U)
#define CAN_FS1_FSC13_Msk						(0x1UL << CAN_FS1_FSC13_Pos)
#define CAN_FS1_FSC13							CAN_FS1_FSC13_Msk				/*!< Filter Scale Configuration bit 13 */

/*******************  Bit definition for CAN_FFA1 register  *******************/
#define CAN_FFA1_FAF0_Pos						(0U)
#define CAN_FFA1_FAF0_Msk						(0x1UL << CAN_FFA1_FAF0_Pos)
#define CAN_FFA1_FAF0							CAN_FFA1_FAF0_Msk				/*!< Filter DATFIFO Assignment for Filter 0 */
#define CAN_FFA1_FAF1_Pos						(1U)
#define CAN_FFA1_FAF1_Msk						(0x1UL << CAN_FFA1_FAF1_Pos)
#define CAN_FFA1_FAF1							CAN_FFA1_FAF1_Msk				/*!< Filter DATFIFO Assignment for Filter 1 */
#define CAN_FFA1_FAF2_Pos						(2U)
#define CAN_FFA1_FAF2_Msk						(0x1UL << CAN_FFA1_FAF2_Pos)
#define CAN_FFA1_FAF2							CAN_FFA1_FAF2_Msk				/*!< Filter DATFIFO Assignment for Filter 2 */
#define CAN_FFA1_FAF3_Pos						(3U)
#define CAN_FFA1_FAF3_Msk						(0x1UL << CAN_FFA1_FAF3_Pos)
#define CAN_FFA1_FAF3							CAN_FFA1_FAF3_Msk				/*!< Filter DATFIFO Assignment for Filter 3 */
#define CAN_FFA1_FAF4_Pos						(4U)
#define CAN_FFA1_FAF4_Msk						(0x1UL << CAN_FFA1_FAF4_Pos)
#define CAN_FFA1_FAF4							CAN_FFA1_FAF4_Msk				/*!< Filter DATFIFO Assignment for Filter 4 */
#define CAN_FFA1_FAF5_Pos						(5U)
#define CAN_FFA1_FAF5_Msk						(0x1UL << CAN_FFA1_FAF5_Pos)
#define CAN_FFA1_FAF5							CAN_FFA1_FAF5_Msk				/*!< Filter DATFIFO Assignment for Filter 5 */
#define CAN_FFA1_FAF6_Pos						(6U)
#define CAN_FFA1_FAF6_Msk						(0x1UL << CAN_FFA1_FAF6_Pos)
#define CAN_FFA1_FAF6							CAN_FFA1_FAF6_Msk				/*!< Filter DATFIFO Assignment for Filter 6 */
#define CAN_FFA1_FAF7_Pos						(7U)
#define CAN_FFA1_FAF7_Msk						(0x1UL << CAN_FFA1_FAF7_Pos)
#define CAN_FFA1_FAF7							CAN_FFA1_FAF7_Msk				/*!< Filter DATFIFO Assignment for Filter 7 */
#define CAN_FFA1_FAF8_Pos						(8U)
#define CAN_FFA1_FAF8_Msk						(0x1UL << CAN_FFA1_FAF8_Pos)
#define CAN_FFA1_FAF8							CAN_FFA1_FAF8_Msk				/*!< Filter DATFIFO Assignment for Filter 8 */
#define CAN_FFA1_FAF9_Pos						(9U)
#define CAN_FFA1_FAF9_Msk						(0x1UL << CAN_FFA1_FAF9_Pos)
#define CAN_FFA1_FAF9							CAN_FFA1_FAF9_Msk				/*!< Filter DATFIFO Assignment for Filter 9 */
#define CAN_FFA1_FAF10_Pos						(10U)
#define CAN_FFA1_FAF10_Msk						(0x1UL << CAN_FFA1_FAF10_Pos)
#define CAN_FFA1_FAF10							CAN_FFA1_FAF10_Msk				/*!< Filter DATFIFO Assignment for Filter 10 */
#define CAN_FFA1_FAF11_Pos						(11U)
#define CAN_FFA1_FAF11_Msk						(0x1UL << CAN_FFA1_FAF11_Pos)
#define CAN_FFA1_FAF11							CAN_FFA1_FAF11_Msk				/*!< Filter DATFIFO Assignment for Filter 11 */
#define CAN_FFA1_FAF12_Pos						(12U)
#define CAN_FFA1_FAF12_Msk						(0x1UL << CAN_FFA1_FAF12_Pos)
#define CAN_FFA1_FAF12							CAN_FFA1_FAF12_Msk				/*!< Filter DATFIFO Assignment for Filter 12 */
#define CAN_FFA1_FAF13_Pos						(13U)
#define CAN_FFA1_FAF13_Msk						(0x1UL << CAN_FFA1_FAF13_Pos)
#define CAN_FFA1_FAF13							CAN_FFA1_FAF13_Msk				/*!< Filter DATFIFO Assignment for Filter 13 */

/*******************  Bit definition for CAN_FA1 register  ********************/
#define CAN_FA1_FAC0_Pos						(0U)
#define CAN_FA1_FAC0_Msk						(0x1UL << CAN_FA1_FAC0_Pos)
#define CAN_FA1_FAC0							CAN_FA1_FAC0_Msk				/*!< Filter 0 Active */
#define CAN_FA1_FAC1_Pos						(1U)
#define CAN_FA1_FAC1_Msk						(0x1UL << CAN_FA1_FAC1_Pos)
#define CAN_FA1_FAC1							CAN_FA1_FAC1_Msk				/*!< Filter 1 Active */
#define CAN_FA1_FAC2_Pos						(2U)
#define CAN_FA1_FAC2_Msk						(0x1UL << CAN_FA1_FAC2_Pos)
#define CAN_FA1_FAC2							CAN_FA1_FAC2_Msk				/*!< Filter 2 Active */
#define CAN_FA1_FAC3_Pos						(3U)
#define CAN_FA1_FAC3_Msk						(0x1UL << CAN_FA1_FAC3_Pos)
#define CAN_FA1_FAC3							CAN_FA1_FAC3_Msk				/*!< Filter 3 Active */
#define CAN_FA1_FAC4_Pos						(4U)
#define CAN_FA1_FAC4_Msk						(0x1UL << CAN_FA1_FAC4_Pos)
#define CAN_FA1_FAC4							CAN_FA1_FAC4_Msk				/*!< Filter 4 Active */
#define CAN_FA1_FAC5_Pos						(5U)
#define CAN_FA1_FAC5_Msk						(0x1UL << CAN_FA1_FAC5_Pos)
#define CAN_FA1_FAC5							CAN_FA1_FAC5_Msk				/*!< Filter 5 Active */
#define CAN_FA1_FAC6_Pos						(6U)
#define CAN_FA1_FAC6_Msk						(0x1UL << CAN_FA1_FAC6_Pos)
#define CAN_FA1_FAC6							CAN_FA1_FAC6_Msk				/*!< Filter 6 Active */
#define CAN_FA1_FAC7_Pos						(7U)
#define CAN_FA1_FAC7_Msk						(0x1UL << CAN_FA1_FAC7_Pos)
#define CAN_FA1_FAC7							CAN_FA1_FAC7_Msk				/*!< Filter 7 Active */
#define CAN_FA1_FAC8_Pos						(8U)
#define CAN_FA1_FAC8_Msk						(0x1UL << CAN_FA1_FAC8_Pos)
#define CAN_FA1_FAC8							CAN_FA1_FAC8_Msk				/*!< Filter 8 Active */
#define CAN_FA1_FAC9_Pos						(9U)
#define CAN_FA1_FAC9_Msk						(0x1UL << CAN_FA1_FAC9_Pos)
#define CAN_FA1_FAC9							CAN_FA1_FAC9_Msk				/*!< Filter 9 Active */
#define CAN_FA1_FAC10_Pos						(10U)
#define CAN_FA1_FAC10_Msk						(0x1UL << CAN_FA1_FAC10_Pos)
#define CAN_FA1_FAC10							CAN_FA1_FAC10_Msk				/*!< Filter 10 Active */
#define CAN_FA1_FAC11_Pos						(11U)
#define CAN_FA1_FAC11_Msk						(0x1UL << CAN_FA1_FAC11_Pos)
#define CAN_FA1_FAC11							CAN_FA1_FAC11_Msk				/*!< Filter 11 Active */
#define CAN_FA1_FAC12_Pos						(12U)
#define CAN_FA1_FAC12_Msk						(0x1UL << CAN_FA1_FAC12_Pos)
#define CAN_FA1_FAC12							CAN_FA1_FAC12_Msk				/*!< Filter 12 Active */
#define CAN_FA1_FAC13_Pos						(13U)
#define CAN_FA1_FAC13_Msk						(0x1UL << CAN_FA1_FAC13_Pos)
#define CAN_FA1_FAC13							CAN_FA1_FAC13_Msk				/*!< Filter 13 Active */

/*******************  Bit definition for CAN_F0R1 register  *******************/
#define CAN_F0B1_FBC0_Pos						(0U)
#define CAN_F0B1_FBC0_Msk						(0x1UL << CAN_F0B1_FBC0_Pos)
#define CAN_F0B1_FBC0							CAN_F0B1_FBC0_Msk				/*!< Filter 0 register 1 bit 0 */
#define CAN_F0B1_FBC1_Pos						(1U)
#define CAN_F0B1_FBC1_Msk						(0x1UL << CAN_F0B1_FBC1_Pos)
#define CAN_F0B1_FBC1							CAN_F0B1_FBC1_Msk				/*!< Filter 0 register 1 bit 1 */
#define CAN_F0B1_FBC2_Pos						(2U)
#define CAN_F0B1_FBC2_Msk						(0x1UL << CAN_F0B1_FBC2_Pos)
#define CAN_F0B1_FBC2							CAN_F0B1_FBC2_Msk				/*!< Filter 0 register 1 bit 2 */
#define CAN_F0B1_FBC3_Pos						(3U)
#define CAN_F0B1_FBC3_Msk						(0x1UL << CAN_F0B1_FBC3_Pos)
#define CAN_F0B1_FBC3							CAN_F0B1_FBC3_Msk				/*!< Filter 0 register 1 bit 3 */
#define CAN_F0B1_FBC4_Pos						(4U)
#define CAN_F0B1_FBC4_Msk						(0x1UL << CAN_F0B1_FBC4_Pos)
#define CAN_F0B1_FBC4							CAN_F0B1_FBC4_Msk				/*!< Filter 0 register 1 bit 4 */
#define CAN_F0B1_FBC5_Pos						(5U)
#define CAN_F0B1_FBC5_Msk						(0x1UL << CAN_F0B1_FBC5_Pos)
#define CAN_F0B1_FBC5							CAN_F0B1_FBC5_Msk				/*!< Filter 0 register 1 bit 5 */
#define CAN_F0B1_FBC6_Pos						(6U)
#define CAN_F0B1_FBC6_Msk						(0x1UL << CAN_F0B1_FBC6_Pos)
#define CAN_F0B1_FBC6							CAN_F0B1_FBC6_Msk				/*!< Filter 0 register 1 bit 6 */
#define CAN_F0B1_FBC7_Pos						(7U)
#define CAN_F0B1_FBC7_Msk						(0x1UL << CAN_F0B1_FBC7_Pos)
#define CAN_F0B1_FBC7							CAN_F0B1_FBC7_Msk				/*!< Filter 0 register 1 bit 7 */
#define CAN_F0B1_FBC8_Pos						(8U)
#define CAN_F0B1_FBC8_Msk						(0x1UL << CAN_F0B1_FBC8_Pos)
#define CAN_F0B1_FBC8							CAN_F0B1_FBC8_Msk				/*!< Filter 0 register 1 bit 8 */
#define CAN_F0B1_FBC9_Pos						(9U)
#define CAN_F0B1_FBC9_Msk						(0x1UL << CAN_F0B1_FBC9_Pos)
#define CAN_F0B1_FBC9							CAN_F0B1_FBC9_Msk				/*!< Filter 0 register 1 bit 9 */
#define CAN_F0B1_FBC10_Pos						(10U)
#define CAN_F0B1_FBC10_Msk						(0x1UL << CAN_F0B1_FBC10_Pos)
#define CAN_F0B1_FBC10							CAN_F0B1_FBC10_Msk				/*!< Filter 0 register 1 bit 10 */
#define CAN_F0B1_FBC11_Pos						(11U)
#define CAN_F0B1_FBC11_Msk						(0x1UL << CAN_F0B1_FBC11_Pos)
#define CAN_F0B1_FBC11							CAN_F0B1_FBC11_Msk				/*!< Filter 0 register 1 bit 11 */
#define CAN_F0B1_FBC12_Pos						(12U)
#define CAN_F0B1_FBC12_Msk						(0x1UL << CAN_F0B1_FBC12_Pos)
#define CAN_F0B1_FBC12							CAN_F0B1_FBC12_Msk				/*!< Filter 0 register 1 bit 12 */
#define CAN_F0B1_FBC13_Pos						(13U)
#define CAN_F0B1_FBC13_Msk						(0x1UL << CAN_F0B1_FBC13_Pos)
#define CAN_F0B1_FBC13							CAN_F0B1_FBC13_Msk				/*!< Filter 0 register 1 bit 13 */
#define CAN_F0B1_FBC14_Pos						(14U)
#define CAN_F0B1_FBC14_Msk						(0x1UL << CAN_F0B1_FBC14_Pos)
#define CAN_F0B1_FBC14							CAN_F0B1_FBC14_Msk				/*!< Filter 0 register 1 bit 14 */
#define CAN_F0B1_FBC15_Pos						(15U)
#define CAN_F0B1_FBC15_Msk						(0x1UL << CAN_F0B1_FBC15_Pos)
#define CAN_F0B1_FBC15							CAN_F0B1_FBC15_Msk				/*!< Filter 0 register 1 bit 15 */
#define CAN_F0B1_FBC16_Pos						(16U)
#define CAN_F0B1_FBC16_Msk						(0x1UL << CAN_F0B1_FBC16_Pos)
#define CAN_F0B1_FBC16							CAN_F0B1_FBC16_Msk				/*!< Filter 0 register 1 bit 16 */
#define CAN_F0B1_FBC17_Pos						(17U)
#define CAN_F0B1_FBC17_Msk						(0x1UL << CAN_F0B1_FBC17_Pos)
#define CAN_F0B1_FBC17							CAN_F0B1_FBC17_Msk				/*!< Filter 0 register 1 bit 17 */
#define CAN_F0B1_FBC18_Pos						(18U)
#define CAN_F0B1_FBC18_Msk						(0x1UL << CAN_F0B1_FBC18_Pos)
#define CAN_F0B1_FBC18							CAN_F0B1_FBC18_Msk				/*!< Filter 0 register 1 bit 18 */
#define CAN_F0B1_FBC19_Pos						(19U)
#define CAN_F0B1_FBC19_Msk						(0x1UL << CAN_F0B1_FBC19_Pos)
#define CAN_F0B1_FBC19							CAN_F0B1_FBC19_Msk				/*!< Filter 0 register 1 bit 19 */
#define CAN_F0B1_FBC20_Pos						(20U)
#define CAN_F0B1_FBC20_Msk						(0x1UL << CAN_F0B1_FBC20_Pos)
#define CAN_F0B1_FBC20							CAN_F0B1_FBC20_Msk				/*!< Filter 0 register 1 bit 20 */
#define CAN_F0B1_FBC21_Pos						(21U)
#define CAN_F0B1_FBC21_Msk						(0x1UL << CAN_F0B1_FBC21_Pos)
#define CAN_F0B1_FBC21							CAN_F0B1_FBC21_Msk				/*!< Filter 0 register 1 bit 21 */
#define CAN_F0B1_FBC22_Pos						(22U)
#define CAN_F0B1_FBC22_Msk						(0x1UL << CAN_F0B1_FBC22_Pos)
#define CAN_F0B1_FBC22							CAN_F0B1_FBC22_Msk				/*!< Filter 0 register 1 bit 22 */
#define CAN_F0B1_FBC23_Pos						(23U)
#define CAN_F0B1_FBC23_Msk						(0x1UL << CAN_F0B1_FBC23_Pos)
#define CAN_F0B1_FBC23							CAN_F0B1_FBC23_Msk				/*!< Filter 0 register 1 bit 23 */
#define CAN_F0B1_FBC24_Pos						(24U)
#define CAN_F0B1_FBC24_Msk						(0x1UL << CAN_F0B1_FBC24_Pos)
#define CAN_F0B1_FBC24							CAN_F0B1_FBC24_Msk				/*!< Filter 0 register 1 bit 24 */
#define CAN_F0B1_FBC25_Pos						(25U)
#define CAN_F0B1_FBC25_Msk						(0x1UL << CAN_F0B1_FBC25_Pos)
#define CAN_F0B1_FBC25							CAN_F0B1_FBC25_Msk				/*!< Filter 0 register 1 bit 25 */
#define CAN_F0B1_FBC26_Pos						(26U)
#define CAN_F0B1_FBC26_Msk						(0x1UL << CAN_F0B1_FBC26_Pos)
#define CAN_F0B1_FBC26							CAN_F0B1_FBC26_Msk				/*!< Filter 0 register 1 bit 26 */
#define CAN_F0B1_FBC27_Pos						(27U)
#define CAN_F0B1_FBC27_Msk						(0x1UL << CAN_F0B1_FBC27_Pos)
#define CAN_F0B1_FBC27							CAN_F0B1_FBC27_Msk				/*!< Filter 0 register 1 bit 27 */
#define CAN_F0B1_FBC28_Pos						(28U)
#define CAN_F0B1_FBC28_Msk						(0x1UL << CAN_F0B1_FBC28_Pos)
#define CAN_F0B1_FBC28							CAN_F0B1_FBC28_Msk				/*!< Filter 0 register 1 bit 28 */
#define CAN_F0B1_FBC29_Pos						(29U)
#define CAN_F0B1_FBC29_Msk						(0x1UL << CAN_F0B1_FBC29_Pos)
#define CAN_F0B1_FBC29							CAN_F0B1_FBC29_Msk				/*!< Filter 0 register 1 bit 29 */
#define CAN_F0B1_FBC30_Pos						(30U)
#define CAN_F0B1_FBC30_Msk						(0x1UL << CAN_F0B1_FBC30_Pos)
#define CAN_F0B1_FBC30							CAN_F0B1_FBC30_Msk				/*!< Filter 0 register 1 bit 30 */
#define CAN_F0B1_FBC31_Pos						(31U)
#define CAN_F0B1_FBC31_Msk						(0x1UL << CAN_F0B1_FBC31_Pos)
#define CAN_F0B1_FBC31							CAN_F0B1_FBC31_Msk				/*!< Filter 0 register 1 bit 31 */

/*******************  Bit definition for CAN_F1R1 register  *******************/
#define CAN_F1B1_FBC0_Pos						(0U)
#define CAN_F1B1_FBC0_Msk						(0x1UL << CAN_F1B1_FBC0_Pos)
#define CAN_F1B1_FBC0							CAN_F1B1_FBC0_Msk				/*!< Filter 1 register 1 bit 0 */
#define CAN_F1B1_FBC1_Pos						(1U)                            
#define CAN_F1B1_FBC1_Msk						(0x1UL << CAN_F1B1_FBC1_Pos)    
#define CAN_F1B1_FBC1							CAN_F1B1_FBC1_Msk               /*!< Filter 1 register 1 bit 1 */
#define CAN_F1B1_FBC2_Pos						(2U)                            
#define CAN_F1B1_FBC2_Msk						(0x1UL << CAN_F1B1_FBC2_Pos)    
#define CAN_F1B1_FBC2							CAN_F1B1_FBC2_Msk               /*!< Filter 1 register 1 bit 2 */
#define CAN_F1B1_FBC3_Pos						(3U)                            
#define CAN_F1B1_FBC3_Msk						(0x1UL << CAN_F1B1_FBC3_Pos)    
#define CAN_F1B1_FBC3							CAN_F1B1_FBC3_Msk               /*!< Filter 1 register 1 bit 3 */
#define CAN_F1B1_FBC4_Pos						(4U)                            
#define CAN_F1B1_FBC4_Msk						(0x1UL << CAN_F1B1_FBC4_Pos)    
#define CAN_F1B1_FBC4							CAN_F1B1_FBC4_Msk               /*!< Filter 1 register 1 bit 4 */
#define CAN_F1B1_FBC5_Pos						(5U)                            
#define CAN_F1B1_FBC5_Msk						(0x1UL << CAN_F1B1_FBC5_Pos)    
#define CAN_F1B1_FBC5							CAN_F1B1_FBC5_Msk               /*!< Filter 1 register 1 bit 5 */
#define CAN_F1B1_FBC6_Pos						(6U)                            
#define CAN_F1B1_FBC6_Msk						(0x1UL << CAN_F1B1_FBC6_Pos)    
#define CAN_F1B1_FBC6							CAN_F1B1_FBC6_Msk               /*!< Filter 1 register 1 bit 6 */
#define CAN_F1B1_FBC7_Pos						(7U)                            
#define CAN_F1B1_FBC7_Msk						(0x1UL << CAN_F1B1_FBC7_Pos)    
#define CAN_F1B1_FBC7							CAN_F1B1_FBC7_Msk               /*!< Filter 1 register 1 bit 7 */
#define CAN_F1B1_FBC8_Pos						(8U)                            
#define CAN_F1B1_FBC8_Msk						(0x1UL << CAN_F1B1_FBC8_Pos)    
#define CAN_F1B1_FBC8							CAN_F1B1_FBC8_Msk               /*!< Filter 1 register 1 bit 8 */
#define CAN_F1B1_FBC9_Pos						(9U)                            
#define CAN_F1B1_FBC9_Msk						(0x1UL << CAN_F1B1_FBC9_Pos)    
#define CAN_F1B1_FBC9							CAN_F1B1_FBC9_Msk               /*!< Filter 1 register 1 bit 9 */
#define CAN_F1B1_FBC10_Pos						(10U)                           
#define CAN_F1B1_FBC10_Msk						(0x1UL << CAN_F1B1_FBC10_Pos)   
#define CAN_F1B1_FBC10							CAN_F1B1_FBC10_Msk              /*!< Filter 1 register 1 bit 10 */
#define CAN_F1B1_FBC11_Pos						(11U)                           
#define CAN_F1B1_FBC11_Msk						(0x1UL << CAN_F1B1_FBC11_Pos)   
#define CAN_F1B1_FBC11							CAN_F1B1_FBC11_Msk              /*!< Filter 1 register 1 bit 11 */
#define CAN_F1B1_FBC12_Pos						(12U)                           
#define CAN_F1B1_FBC12_Msk						(0x1UL << CAN_F1B1_FBC12_Pos)   
#define CAN_F1B1_FBC12							CAN_F1B1_FBC12_Msk              /*!< Filter 1 register 1 bit 12 */
#define CAN_F1B1_FBC13_Pos						(13U)                           
#define CAN_F1B1_FBC13_Msk						(0x1UL << CAN_F1B1_FBC13_Pos)   
#define CAN_F1B1_FBC13							CAN_F1B1_FBC13_Msk              /*!< Filter 1 register 1 bit 13 */
#define CAN_F1B1_FBC14_Pos						(14U)                           
#define CAN_F1B1_FBC14_Msk						(0x1UL << CAN_F1B1_FBC14_Pos)   
#define CAN_F1B1_FBC14							CAN_F1B1_FBC14_Msk              /*!< Filter 1 register 1 bit 14 */
#define CAN_F1B1_FBC15_Pos						(15U)                           
#define CAN_F1B1_FBC15_Msk						(0x1UL << CAN_F1B1_FBC15_Pos)   
#define CAN_F1B1_FBC15							CAN_F1B1_FBC15_Msk              /*!< Filter 1 register 1 bit 15 */
#define CAN_F1B1_FBC16_Pos						(16U)                           
#define CAN_F1B1_FBC16_Msk						(0x1UL << CAN_F1B1_FBC16_Pos)   
#define CAN_F1B1_FBC16							CAN_F1B1_FBC16_Msk              /*!< Filter 1 register 1 bit 16 */
#define CAN_F1B1_FBC17_Pos						(17U)                           
#define CAN_F1B1_FBC17_Msk						(0x1UL << CAN_F1B1_FBC17_Pos)   
#define CAN_F1B1_FBC17							CAN_F1B1_FBC17_Msk              /*!< Filter 1 register 1 bit 17 */
#define CAN_F1B1_FBC18_Pos						(18U)                           
#define CAN_F1B1_FBC18_Msk						(0x1UL << CAN_F1B1_FBC18_Pos)   
#define CAN_F1B1_FBC18							CAN_F1B1_FBC18_Msk              /*!< Filter 1 register 1 bit 18 */
#define CAN_F1B1_FBC19_Pos						(19U)                           
#define CAN_F1B1_FBC19_Msk						(0x1UL << CAN_F1B1_FBC19_Pos)   
#define CAN_F1B1_FBC19							CAN_F1B1_FBC19_Msk              /*!< Filter 1 register 1 bit 19 */
#define CAN_F1B1_FBC20_Pos						(20U)                           
#define CAN_F1B1_FBC20_Msk						(0x1UL << CAN_F1B1_FBC20_Pos)   
#define CAN_F1B1_FBC20							CAN_F1B1_FBC20_Msk              /*!< Filter 1 register 1 bit 20 */
#define CAN_F1B1_FBC21_Pos						(21U)                           
#define CAN_F1B1_FBC21_Msk						(0x1UL << CAN_F1B1_FBC21_Pos)   
#define CAN_F1B1_FBC21							CAN_F1B1_FBC21_Msk              /*!< Filter 1 register 1 bit 21 */
#define CAN_F1B1_FBC22_Pos						(22U)                           
#define CAN_F1B1_FBC22_Msk						(0x1UL << CAN_F1B1_FBC22_Pos)   
#define CAN_F1B1_FBC22							CAN_F1B1_FBC22_Msk              /*!< Filter 1 register 1 bit 22 */
#define CAN_F1B1_FBC23_Pos						(23U)                           
#define CAN_F1B1_FBC23_Msk						(0x1UL << CAN_F1B1_FBC23_Pos)   
#define CAN_F1B1_FBC23							CAN_F1B1_FBC23_Msk              /*!< Filter 1 register 1 bit 23 */
#define CAN_F1B1_FBC24_Pos						(24U)                           
#define CAN_F1B1_FBC24_Msk						(0x1UL << CAN_F1B1_FBC24_Pos)   
#define CAN_F1B1_FBC24							CAN_F1B1_FBC24_Msk              /*!< Filter 1 register 1 bit 24 */
#define CAN_F1B1_FBC25_Pos						(25U)                           
#define CAN_F1B1_FBC25_Msk						(0x1UL << CAN_F1B1_FBC25_Pos)   
#define CAN_F1B1_FBC25							CAN_F1B1_FBC25_Msk              /*!< Filter 1 register 1 bit 25 */
#define CAN_F1B1_FBC26_Pos						(26U)                           
#define CAN_F1B1_FBC26_Msk						(0x1UL << CAN_F1B1_FBC26_Pos)   
#define CAN_F1B1_FBC26							CAN_F1B1_FBC26_Msk              /*!< Filter 1 register 1 bit 26 */
#define CAN_F1B1_FBC27_Pos						(27U)                           
#define CAN_F1B1_FBC27_Msk						(0x1UL << CAN_F1B1_FBC27_Pos)   
#define CAN_F1B1_FBC27							CAN_F1B1_FBC27_Msk              /*!< Filter 1 register 1 bit 27 */
#define CAN_F1B1_FBC28_Pos						(28U)                           
#define CAN_F1B1_FBC28_Msk						(0x1UL << CAN_F1B1_FBC28_Pos)   
#define CAN_F1B1_FBC28							CAN_F1B1_FBC28_Msk              /*!< Filter 1 register 1 bit 28 */
#define CAN_F1B1_FBC29_Pos						(29U)                           
#define CAN_F1B1_FBC29_Msk						(0x1UL << CAN_F1B1_FBC29_Pos)   
#define CAN_F1B1_FBC29							CAN_F1B1_FBC29_Msk              /*!< Filter 1 register 1 bit 29 */
#define CAN_F1B1_FBC30_Pos						(30U)                           
#define CAN_F1B1_FBC30_Msk						(0x1UL << CAN_F1B1_FBC30_Pos)   
#define CAN_F1B1_FBC30							CAN_F1B1_FBC30_Msk              /*!< Filter 1 register 1 bit 30 */
#define CAN_F1B1_FBC31_Pos						(31U)                           
#define CAN_F1B1_FBC31_Msk						(0x1UL << CAN_F1B1_FBC31_Pos)   
#define CAN_F1B1_FBC31							CAN_F1B1_FBC31_Msk              /*!< Filter 1 register 1 bit 31 */

/*******************  Bit definition for CAN_F2R1 register  *******************/
#define CAN_F2B1_FBC0_Pos						(0U)
#define CAN_F2B1_FBC0_Msk						(0x1UL << CAN_F2B1_FBC0_Pos)
#define CAN_F2B1_FBC0							CAN_F2B1_FBC0_Msk				/*!< Filter 2 register 1 bit 0 */
#define CAN_F2B1_FBC1_Pos						(1U)                            
#define CAN_F2B1_FBC1_Msk						(0x1UL << CAN_F2B1_FBC1_Pos)    
#define CAN_F2B1_FBC1							CAN_F2B1_FBC1_Msk               /*!< Filter 2 register 1 bit 1 */
#define CAN_F2B1_FBC2_Pos						(2U)                            
#define CAN_F2B1_FBC2_Msk						(0x1UL << CAN_F2B1_FBC2_Pos)    
#define CAN_F2B1_FBC2							CAN_F2B1_FBC2_Msk               /*!< Filter 2 register 1 bit 2 */
#define CAN_F2B1_FBC3_Pos						(3U)                            
#define CAN_F2B1_FBC3_Msk						(0x1UL << CAN_F2B1_FBC3_Pos)    
#define CAN_F2B1_FBC3							CAN_F2B1_FBC3_Msk               /*!< Filter 2 register 1 bit 3 */
#define CAN_F2B1_FBC4_Pos						(4U)                            
#define CAN_F2B1_FBC4_Msk						(0x1UL << CAN_F2B1_FBC4_Pos)    
#define CAN_F2B1_FBC4							CAN_F2B1_FBC4_Msk               /*!< Filter 2 register 1 bit 4 */
#define CAN_F2B1_FBC5_Pos						(5U)                            
#define CAN_F2B1_FBC5_Msk						(0x1UL << CAN_F2B1_FBC5_Pos)    
#define CAN_F2B1_FBC5							CAN_F2B1_FBC5_Msk               /*!< Filter 2 register 1 bit 5 */
#define CAN_F2B1_FBC6_Pos						(6U)                            
#define CAN_F2B1_FBC6_Msk						(0x1UL << CAN_F2B1_FBC6_Pos)    
#define CAN_F2B1_FBC6							CAN_F2B1_FBC6_Msk               /*!< Filter 2 register 1 bit 6 */
#define CAN_F2B1_FBC7_Pos						(7U)                            
#define CAN_F2B1_FBC7_Msk						(0x1UL << CAN_F2B1_FBC7_Pos)    
#define CAN_F2B1_FBC7							CAN_F2B1_FBC7_Msk               /*!< Filter 2 register 1 bit 7 */
#define CAN_F2B1_FBC8_Pos						(8U)                            
#define CAN_F2B1_FBC8_Msk						(0x1UL << CAN_F2B1_FBC8_Pos)    
#define CAN_F2B1_FBC8							CAN_F2B1_FBC8_Msk               /*!< Filter 2 register 1 bit 8 */
#define CAN_F2B1_FBC9_Pos						(9U)                            
#define CAN_F2B1_FBC9_Msk						(0x1UL << CAN_F2B1_FBC9_Pos)    
#define CAN_F2B1_FBC9							CAN_F2B1_FBC9_Msk               /*!< Filter 2 register 1 bit 9 */
#define CAN_F2B1_FBC10_Pos						(10U)                           
#define CAN_F2B1_FBC10_Msk						(0x1UL << CAN_F2B1_FBC10_Pos)   
#define CAN_F2B1_FBC10							CAN_F2B1_FBC10_Msk              /*!< Filter 2 register 1 bit 10 */
#define CAN_F2B1_FBC11_Pos						(11U)                           
#define CAN_F2B1_FBC11_Msk						(0x1UL << CAN_F2B1_FBC11_Pos)   
#define CAN_F2B1_FBC11							CAN_F2B1_FBC11_Msk              /*!< Filter 2 register 1 bit 11 */
#define CAN_F2B1_FBC12_Pos						(12U)                           
#define CAN_F2B1_FBC12_Msk						(0x1UL << CAN_F2B1_FBC12_Pos)   
#define CAN_F2B1_FBC12							CAN_F2B1_FBC12_Msk              /*!< Filter 2 register 1 bit 12 */
#define CAN_F2B1_FBC13_Pos						(13U)                           
#define CAN_F2B1_FBC13_Msk						(0x1UL << CAN_F2B1_FBC13_Pos)   
#define CAN_F2B1_FBC13							CAN_F2B1_FBC13_Msk              /*!< Filter 2 register 1 bit 13 */
#define CAN_F2B1_FBC14_Pos						(14U)                           
#define CAN_F2B1_FBC14_Msk						(0x1UL << CAN_F2B1_FBC14_Pos)   
#define CAN_F2B1_FBC14							CAN_F2B1_FBC14_Msk              /*!< Filter 2 register 1 bit 14 */
#define CAN_F2B1_FBC15_Pos						(15U)                           
#define CAN_F2B1_FBC15_Msk						(0x1UL << CAN_F2B1_FBC15_Pos)   
#define CAN_F2B1_FBC15							CAN_F2B1_FBC15_Msk              /*!< Filter 2 register 1 bit 15 */
#define CAN_F2B1_FBC16_Pos						(16U)                           
#define CAN_F2B1_FBC16_Msk						(0x1UL << CAN_F2B1_FBC16_Pos)   
#define CAN_F2B1_FBC16							CAN_F2B1_FBC16_Msk              /*!< Filter 2 register 1 bit 16 */
#define CAN_F2B1_FBC17_Pos						(17U)                           
#define CAN_F2B1_FBC17_Msk						(0x1UL << CAN_F2B1_FBC17_Pos)   
#define CAN_F2B1_FBC17							CAN_F2B1_FBC17_Msk              /*!< Filter 2 register 1 bit 17 */
#define CAN_F2B1_FBC18_Pos						(18U)                           
#define CAN_F2B1_FBC18_Msk						(0x1UL << CAN_F2B1_FBC18_Pos)   
#define CAN_F2B1_FBC18							CAN_F2B1_FBC18_Msk              /*!< Filter 2 register 1 bit 18 */
#define CAN_F2B1_FBC19_Pos						(19U)                           
#define CAN_F2B1_FBC19_Msk						(0x1UL << CAN_F2B1_FBC19_Pos)   
#define CAN_F2B1_FBC19							CAN_F2B1_FBC19_Msk              /*!< Filter 2 register 1 bit 19 */
#define CAN_F2B1_FBC20_Pos						(20U)                           
#define CAN_F2B1_FBC20_Msk						(0x1UL << CAN_F2B1_FBC20_Pos)   
#define CAN_F2B1_FBC20							CAN_F2B1_FBC20_Msk              /*!< Filter 2 register 1 bit 20 */
#define CAN_F2B1_FBC21_Pos						(21U)                           
#define CAN_F2B1_FBC21_Msk						(0x1UL << CAN_F2B1_FBC21_Pos)   
#define CAN_F2B1_FBC21							CAN_F2B1_FBC21_Msk              /*!< Filter 2 register 1 bit 21 */
#define CAN_F2B1_FBC22_Pos						(22U)                           
#define CAN_F2B1_FBC22_Msk						(0x1UL << CAN_F2B1_FBC22_Pos)   
#define CAN_F2B1_FBC22							CAN_F2B1_FBC22_Msk              /*!< Filter 2 register 1 bit 22 */
#define CAN_F2B1_FBC23_Pos						(23U)                           
#define CAN_F2B1_FBC23_Msk						(0x1UL << CAN_F2B1_FBC23_Pos)   
#define CAN_F2B1_FBC23							CAN_F2B1_FBC23_Msk              /*!< Filter 2 register 1 bit 23 */
#define CAN_F2B1_FBC24_Pos						(24U)                           
#define CAN_F2B1_FBC24_Msk						(0x1UL << CAN_F2B1_FBC24_Pos)   
#define CAN_F2B1_FBC24							CAN_F2B1_FBC24_Msk              /*!< Filter 2 register 1 bit 24 */
#define CAN_F2B1_FBC25_Pos						(25U)                           
#define CAN_F2B1_FBC25_Msk						(0x1UL << CAN_F2B1_FBC25_Pos)   
#define CAN_F2B1_FBC25							CAN_F2B1_FBC25_Msk              /*!< Filter 2 register 1 bit 25 */
#define CAN_F2B1_FBC26_Pos						(26U)                           
#define CAN_F2B1_FBC26_Msk						(0x1UL << CAN_F2B1_FBC26_Pos)   
#define CAN_F2B1_FBC26							CAN_F2B1_FBC26_Msk              /*!< Filter 2 register 1 bit 26 */
#define CAN_F2B1_FBC27_Pos						(27U)                           
#define CAN_F2B1_FBC27_Msk						(0x1UL << CAN_F2B1_FBC27_Pos)   
#define CAN_F2B1_FBC27							CAN_F2B1_FBC27_Msk              /*!< Filter 2 register 1 bit 27 */
#define CAN_F2B1_FBC28_Pos						(28U)                           
#define CAN_F2B1_FBC28_Msk						(0x1UL << CAN_F2B1_FBC28_Pos)   
#define CAN_F2B1_FBC28							CAN_F2B1_FBC28_Msk              /*!< Filter 2 register 1 bit 28 */
#define CAN_F2B1_FBC29_Pos						(29U)                           
#define CAN_F2B1_FBC29_Msk						(0x1UL << CAN_F2B1_FBC29_Pos)   
#define CAN_F2B1_FBC29							CAN_F2B1_FBC29_Msk              /*!< Filter 2 register 1 bit 29 */
#define CAN_F2B1_FBC30_Pos						(30U)                           
#define CAN_F2B1_FBC30_Msk						(0x1UL << CAN_F2B1_FBC30_Pos)   
#define CAN_F2B1_FBC30							CAN_F2B1_FBC30_Msk              /*!< Filter 2 register 1 bit 30 */
#define CAN_F2B1_FBC31_Pos						(31U)                           
#define CAN_F2B1_FBC31_Msk						(0x1UL << CAN_F2B1_FBC31_Pos)   
#define CAN_F2B1_FBC31							CAN_F2B1_FBC31_Msk              /*!< Filter 2 register 1 bit 31 */

/*******************  Bit definition for CAN_F3R1 register  *******************/
#define CAN_F3B1_FBC0_Pos						(0U)
#define CAN_F3B1_FBC0_Msk						(0x1UL << CAN_F3B1_FBC0_Pos)
#define CAN_F3B1_FBC0							CAN_F3B1_FBC0_Msk				/*!< Filter 3 register 1 bit 0 */
#define CAN_F3B1_FBC1_Pos						(1U)                            
#define CAN_F3B1_FBC1_Msk						(0x1UL << CAN_F3B1_FBC1_Pos)    
#define CAN_F3B1_FBC1							CAN_F3B1_FBC1_Msk               /*!< Filter 3 register 1 bit 1 */
#define CAN_F3B1_FBC2_Pos						(2U)                            
#define CAN_F3B1_FBC2_Msk						(0x1UL << CAN_F3B1_FBC2_Pos)    
#define CAN_F3B1_FBC2							CAN_F3B1_FBC2_Msk               /*!< Filter 3 register 1 bit 2 */
#define CAN_F3B1_FBC3_Pos						(3U)                            
#define CAN_F3B1_FBC3_Msk						(0x1UL << CAN_F3B1_FBC3_Pos)    
#define CAN_F3B1_FBC3							CAN_F3B1_FBC3_Msk               /*!< Filter 3 register 1 bit 3 */
#define CAN_F3B1_FBC4_Pos						(4U)                            
#define CAN_F3B1_FBC4_Msk						(0x1UL << CAN_F3B1_FBC4_Pos)    
#define CAN_F3B1_FBC4							CAN_F3B1_FBC4_Msk               /*!< Filter 3 register 1 bit 4 */
#define CAN_F3B1_FBC5_Pos						(5U)                            
#define CAN_F3B1_FBC5_Msk						(0x1UL << CAN_F3B1_FBC5_Pos)    
#define CAN_F3B1_FBC5							CAN_F3B1_FBC5_Msk               /*!< Filter 3 register 1 bit 5 */
#define CAN_F3B1_FBC6_Pos						(6U)                            
#define CAN_F3B1_FBC6_Msk						(0x1UL << CAN_F3B1_FBC6_Pos)    
#define CAN_F3B1_FBC6							CAN_F3B1_FBC6_Msk               /*!< Filter 3 register 1 bit 6 */
#define CAN_F3B1_FBC7_Pos						(7U)                            
#define CAN_F3B1_FBC7_Msk						(0x1UL << CAN_F3B1_FBC7_Pos)    
#define CAN_F3B1_FBC7							CAN_F3B1_FBC7_Msk               /*!< Filter 3 register 1 bit 7 */
#define CAN_F3B1_FBC8_Pos						(8U)                            
#define CAN_F3B1_FBC8_Msk						(0x1UL << CAN_F3B1_FBC8_Pos)    
#define CAN_F3B1_FBC8							CAN_F3B1_FBC8_Msk               /*!< Filter 3 register 1 bit 8 */
#define CAN_F3B1_FBC9_Pos						(9U)                            
#define CAN_F3B1_FBC9_Msk						(0x1UL << CAN_F3B1_FBC9_Pos)    
#define CAN_F3B1_FBC9							CAN_F3B1_FBC9_Msk               /*!< Filter 3 register 1 bit 9 */
#define CAN_F3B1_FBC10_Pos						(10U)                           
#define CAN_F3B1_FBC10_Msk						(0x1UL << CAN_F3B1_FBC10_Pos)   
#define CAN_F3B1_FBC10							CAN_F3B1_FBC10_Msk              /*!< Filter 3 register 1 bit 10 */
#define CAN_F3B1_FBC11_Pos						(11U)                           
#define CAN_F3B1_FBC11_Msk						(0x1UL << CAN_F3B1_FBC11_Pos)   
#define CAN_F3B1_FBC11							CAN_F3B1_FBC11_Msk              /*!< Filter 3 register 1 bit 11 */
#define CAN_F3B1_FBC12_Pos						(12U)                           
#define CAN_F3B1_FBC12_Msk						(0x1UL << CAN_F3B1_FBC12_Pos)   
#define CAN_F3B1_FBC12							CAN_F3B1_FBC12_Msk              /*!< Filter 3 register 1 bit 12 */
#define CAN_F3B1_FBC13_Pos						(13U)                           
#define CAN_F3B1_FBC13_Msk						(0x1UL << CAN_F3B1_FBC13_Pos)   
#define CAN_F3B1_FBC13							CAN_F3B1_FBC13_Msk              /*!< Filter 3 register 1 bit 13 */
#define CAN_F3B1_FBC14_Pos						(14U)                           
#define CAN_F3B1_FBC14_Msk						(0x1UL << CAN_F3B1_FBC14_Pos)   
#define CAN_F3B1_FBC14							CAN_F3B1_FBC14_Msk              /*!< Filter 3 register 1 bit 14 */
#define CAN_F3B1_FBC15_Pos						(15U)                           
#define CAN_F3B1_FBC15_Msk						(0x1UL << CAN_F3B1_FBC15_Pos)   
#define CAN_F3B1_FBC15							CAN_F3B1_FBC15_Msk              /*!< Filter 3 register 1 bit 15 */
#define CAN_F3B1_FBC16_Pos						(16U)                           
#define CAN_F3B1_FBC16_Msk						(0x1UL << CAN_F3B1_FBC16_Pos)   
#define CAN_F3B1_FBC16							CAN_F3B1_FBC16_Msk              /*!< Filter 3 register 1 bit 16 */
#define CAN_F3B1_FBC17_Pos						(17U)                           
#define CAN_F3B1_FBC17_Msk						(0x1UL << CAN_F3B1_FBC17_Pos)   
#define CAN_F3B1_FBC17							CAN_F3B1_FBC17_Msk              /*!< Filter 3 register 1 bit 17 */
#define CAN_F3B1_FBC18_Pos						(18U)                           
#define CAN_F3B1_FBC18_Msk						(0x1UL << CAN_F3B1_FBC18_Pos)   
#define CAN_F3B1_FBC18							CAN_F3B1_FBC18_Msk              /*!< Filter 3 register 1 bit 18 */
#define CAN_F3B1_FBC19_Pos						(19U)                           
#define CAN_F3B1_FBC19_Msk						(0x1UL << CAN_F3B1_FBC19_Pos)   
#define CAN_F3B1_FBC19							CAN_F3B1_FBC19_Msk              /*!< Filter 3 register 1 bit 19 */
#define CAN_F3B1_FBC20_Pos						(20U)                           
#define CAN_F3B1_FBC20_Msk						(0x1UL << CAN_F3B1_FBC20_Pos)   
#define CAN_F3B1_FBC20							CAN_F3B1_FBC20_Msk              /*!< Filter 3 register 1 bit 20 */
#define CAN_F3B1_FBC21_Pos						(21U)                           
#define CAN_F3B1_FBC21_Msk						(0x1UL << CAN_F3B1_FBC21_Pos)   
#define CAN_F3B1_FBC21							CAN_F3B1_FBC21_Msk              /*!< Filter 3 register 1 bit 21 */
#define CAN_F3B1_FBC22_Pos						(22U)                           
#define CAN_F3B1_FBC22_Msk						(0x1UL << CAN_F3B1_FBC22_Pos)   
#define CAN_F3B1_FBC22							CAN_F3B1_FBC22_Msk              /*!< Filter 3 register 1 bit 22 */
#define CAN_F3B1_FBC23_Pos						(23U)                           
#define CAN_F3B1_FBC23_Msk						(0x1UL << CAN_F3B1_FBC23_Pos)   
#define CAN_F3B1_FBC23							CAN_F3B1_FBC23_Msk              /*!< Filter 3 register 1 bit 23 */
#define CAN_F3B1_FBC24_Pos						(24U)                           
#define CAN_F3B1_FBC24_Msk						(0x1UL << CAN_F3B1_FBC24_Pos)   
#define CAN_F3B1_FBC24							CAN_F3B1_FBC24_Msk              /*!< Filter 3 register 1 bit 24 */
#define CAN_F3B1_FBC25_Pos						(25U)                           
#define CAN_F3B1_FBC25_Msk						(0x1UL << CAN_F3B1_FBC25_Pos)   
#define CAN_F3B1_FBC25							CAN_F3B1_FBC25_Msk              /*!< Filter 3 register 1 bit 25 */
#define CAN_F3B1_FBC26_Pos						(26U)                           
#define CAN_F3B1_FBC26_Msk						(0x1UL << CAN_F3B1_FBC26_Pos)   
#define CAN_F3B1_FBC26							CAN_F3B1_FBC26_Msk              /*!< Filter 3 register 1 bit 26 */
#define CAN_F3B1_FBC27_Pos						(27U)                           
#define CAN_F3B1_FBC27_Msk						(0x1UL << CAN_F3B1_FBC27_Pos)   
#define CAN_F3B1_FBC27							CAN_F3B1_FBC27_Msk              /*!< Filter 3 register 1 bit 27 */
#define CAN_F3B1_FBC28_Pos						(28U)                           
#define CAN_F3B1_FBC28_Msk						(0x1UL << CAN_F3B1_FBC28_Pos)   
#define CAN_F3B1_FBC28							CAN_F3B1_FBC28_Msk              /*!< Filter 3 register 1 bit 28 */
#define CAN_F3B1_FBC29_Pos						(29U)                           
#define CAN_F3B1_FBC29_Msk						(0x1UL << CAN_F3B1_FBC29_Pos)   
#define CAN_F3B1_FBC29							CAN_F3B1_FBC29_Msk              /*!< Filter 3 register 1 bit 29 */
#define CAN_F3B1_FBC30_Pos						(30U)                           
#define CAN_F3B1_FBC30_Msk						(0x1UL << CAN_F3B1_FBC30_Pos)   
#define CAN_F3B1_FBC30							CAN_F3B1_FBC30_Msk              /*!< Filter 3 register 1 bit 30 */
#define CAN_F3B1_FBC31_Pos						(31U)                           
#define CAN_F3B1_FBC31_Msk						(0x1UL << CAN_F3B1_FBC31_Pos)   
#define CAN_F3B1_FBC31							CAN_F3B1_FBC31_Msk              /*!< Filter 3 register 1 bit 31 */

/*******************  Bit definition for CAN_F4R1 register  *******************/
#define CAN_F4B1_FBC0_Pos						(0U)
#define CAN_F4B1_FBC0_Msk						(0x1UL << CAN_F4B1_FBC0_Pos)
#define CAN_F4B1_FBC0							CAN_F4B1_FBC0_Msk				/*!< Filter 4 register 1 bit 0 */
#define CAN_F4B1_FBC1_Pos						(1U)                            
#define CAN_F4B1_FBC1_Msk						(0x1UL << CAN_F4B1_FBC1_Pos)    
#define CAN_F4B1_FBC1							CAN_F4B1_FBC1_Msk               /*!< Filter 4 register 1 bit 1 */
#define CAN_F4B1_FBC2_Pos						(2U)                            
#define CAN_F4B1_FBC2_Msk						(0x1UL << CAN_F4B1_FBC2_Pos)    
#define CAN_F4B1_FBC2							CAN_F4B1_FBC2_Msk               /*!< Filter 4 register 1 bit 2 */
#define CAN_F4B1_FBC3_Pos						(3U)                            
#define CAN_F4B1_FBC3_Msk						(0x1UL << CAN_F4B1_FBC3_Pos)    
#define CAN_F4B1_FBC3							CAN_F4B1_FBC3_Msk               /*!< Filter 4 register 1 bit 3 */
#define CAN_F4B1_FBC4_Pos						(4U)                            
#define CAN_F4B1_FBC4_Msk						(0x1UL << CAN_F4B1_FBC4_Pos)    
#define CAN_F4B1_FBC4							CAN_F4B1_FBC4_Msk               /*!< Filter 4 register 1 bit 4 */
#define CAN_F4B1_FBC5_Pos						(5U)                            
#define CAN_F4B1_FBC5_Msk						(0x1UL << CAN_F4B1_FBC5_Pos)    
#define CAN_F4B1_FBC5							CAN_F4B1_FBC5_Msk               /*!< Filter 4 register 1 bit 5 */
#define CAN_F4B1_FBC6_Pos						(6U)                            
#define CAN_F4B1_FBC6_Msk						(0x1UL << CAN_F4B1_FBC6_Pos)    
#define CAN_F4B1_FBC6							CAN_F4B1_FBC6_Msk               /*!< Filter 4 register 1 bit 6 */
#define CAN_F4B1_FBC7_Pos						(7U)                            
#define CAN_F4B1_FBC7_Msk						(0x1UL << CAN_F4B1_FBC7_Pos)    
#define CAN_F4B1_FBC7							CAN_F4B1_FBC7_Msk               /*!< Filter 4 register 1 bit 7 */
#define CAN_F4B1_FBC8_Pos						(8U)                            
#define CAN_F4B1_FBC8_Msk						(0x1UL << CAN_F4B1_FBC8_Pos)    
#define CAN_F4B1_FBC8							CAN_F4B1_FBC8_Msk               /*!< Filter 4 register 1 bit 8 */
#define CAN_F4B1_FBC9_Pos						(9U)                            
#define CAN_F4B1_FBC9_Msk						(0x1UL << CAN_F4B1_FBC9_Pos)    
#define CAN_F4B1_FBC9							CAN_F4B1_FBC9_Msk               /*!< Filter 4 register 1 bit 9 */
#define CAN_F4B1_FBC10_Pos						(10U)                           
#define CAN_F4B1_FBC10_Msk						(0x1UL << CAN_F4B1_FBC10_Pos)   
#define CAN_F4B1_FBC10							CAN_F4B1_FBC10_Msk              /*!< Filter 4 register 1 bit 10 */
#define CAN_F4B1_FBC11_Pos						(11U)                           
#define CAN_F4B1_FBC11_Msk						(0x1UL << CAN_F4B1_FBC11_Pos)   
#define CAN_F4B1_FBC11							CAN_F4B1_FBC11_Msk              /*!< Filter 4 register 1 bit 11 */
#define CAN_F4B1_FBC12_Pos						(12U)                           
#define CAN_F4B1_FBC12_Msk						(0x1UL << CAN_F4B1_FBC12_Pos)   
#define CAN_F4B1_FBC12							CAN_F4B1_FBC12_Msk              /*!< Filter 4 register 1 bit 12 */
#define CAN_F4B1_FBC13_Pos						(13U)                           
#define CAN_F4B1_FBC13_Msk						(0x1UL << CAN_F4B1_FBC13_Pos)   
#define CAN_F4B1_FBC13							CAN_F4B1_FBC13_Msk              /*!< Filter 4 register 1 bit 13 */
#define CAN_F4B1_FBC14_Pos						(14U)                           
#define CAN_F4B1_FBC14_Msk						(0x1UL << CAN_F4B1_FBC14_Pos)   
#define CAN_F4B1_FBC14							CAN_F4B1_FBC14_Msk              /*!< Filter 4 register 1 bit 14 */
#define CAN_F4B1_FBC15_Pos						(15U)                           
#define CAN_F4B1_FBC15_Msk						(0x1UL << CAN_F4B1_FBC15_Pos)   
#define CAN_F4B1_FBC15							CAN_F4B1_FBC15_Msk              /*!< Filter 4 register 1 bit 15 */
#define CAN_F4B1_FBC16_Pos						(16U)                           
#define CAN_F4B1_FBC16_Msk						(0x1UL << CAN_F4B1_FBC16_Pos)   
#define CAN_F4B1_FBC16							CAN_F4B1_FBC16_Msk              /*!< Filter 4 register 1 bit 16 */
#define CAN_F4B1_FBC17_Pos						(17U)                           
#define CAN_F4B1_FBC17_Msk						(0x1UL << CAN_F4B1_FBC17_Pos)   
#define CAN_F4B1_FBC17							CAN_F4B1_FBC17_Msk              /*!< Filter 4 register 1 bit 17 */
#define CAN_F4B1_FBC18_Pos						(18U)                           
#define CAN_F4B1_FBC18_Msk						(0x1UL << CAN_F4B1_FBC18_Pos)   
#define CAN_F4B1_FBC18							CAN_F4B1_FBC18_Msk              /*!< Filter 4 register 1 bit 18 */
#define CAN_F4B1_FBC19_Pos						(19U)                           
#define CAN_F4B1_FBC19_Msk						(0x1UL << CAN_F4B1_FBC19_Pos)   
#define CAN_F4B1_FBC19							CAN_F4B1_FBC19_Msk              /*!< Filter 4 register 1 bit 19 */
#define CAN_F4B1_FBC20_Pos						(20U)                           
#define CAN_F4B1_FBC20_Msk						(0x1UL << CAN_F4B1_FBC20_Pos)   
#define CAN_F4B1_FBC20							CAN_F4B1_FBC20_Msk              /*!< Filter 4 register 1 bit 20 */
#define CAN_F4B1_FBC21_Pos						(21U)                           
#define CAN_F4B1_FBC21_Msk						(0x1UL << CAN_F4B1_FBC21_Pos)   
#define CAN_F4B1_FBC21							CAN_F4B1_FBC21_Msk              /*!< Filter 4 register 1 bit 21 */
#define CAN_F4B1_FBC22_Pos						(22U)                           
#define CAN_F4B1_FBC22_Msk						(0x1UL << CAN_F4B1_FBC22_Pos)   
#define CAN_F4B1_FBC22							CAN_F4B1_FBC22_Msk              /*!< Filter 4 register 1 bit 22 */
#define CAN_F4B1_FBC23_Pos						(23U)                           
#define CAN_F4B1_FBC23_Msk						(0x1UL << CAN_F4B1_FBC23_Pos)   
#define CAN_F4B1_FBC23							CAN_F4B1_FBC23_Msk              /*!< Filter 4 register 1 bit 23 */
#define CAN_F4B1_FBC24_Pos						(24U)                           
#define CAN_F4B1_FBC24_Msk						(0x1UL << CAN_F4B1_FBC24_Pos)   
#define CAN_F4B1_FBC24							CAN_F4B1_FBC24_Msk              /*!< Filter 4 register 1 bit 24 */
#define CAN_F4B1_FBC25_Pos						(25U)                           
#define CAN_F4B1_FBC25_Msk						(0x1UL << CAN_F4B1_FBC25_Pos)   
#define CAN_F4B1_FBC25							CAN_F4B1_FBC25_Msk              /*!< Filter 4 register 1 bit 25 */
#define CAN_F4B1_FBC26_Pos						(26U)                           
#define CAN_F4B1_FBC26_Msk						(0x1UL << CAN_F4B1_FBC26_Pos)   
#define CAN_F4B1_FBC26							CAN_F4B1_FBC26_Msk              /*!< Filter 4 register 1 bit 26 */
#define CAN_F4B1_FBC27_Pos						(27U)                           
#define CAN_F4B1_FBC27_Msk						(0x1UL << CAN_F4B1_FBC27_Pos)   
#define CAN_F4B1_FBC27							CAN_F4B1_FBC27_Msk              /*!< Filter 4 register 1 bit 27 */
#define CAN_F4B1_FBC28_Pos						(28U)                           
#define CAN_F4B1_FBC28_Msk						(0x1UL << CAN_F4B1_FBC28_Pos)   
#define CAN_F4B1_FBC28							CAN_F4B1_FBC28_Msk              /*!< Filter 4 register 1 bit 28 */
#define CAN_F4B1_FBC29_Pos						(29U)                           
#define CAN_F4B1_FBC29_Msk						(0x1UL << CAN_F4B1_FBC29_Pos)   
#define CAN_F4B1_FBC29							CAN_F4B1_FBC29_Msk              /*!< Filter 4 register 1 bit 29 */
#define CAN_F4B1_FBC30_Pos						(30U)                           
#define CAN_F4B1_FBC30_Msk						(0x1UL << CAN_F4B1_FBC30_Pos)   
#define CAN_F4B1_FBC30							CAN_F4B1_FBC30_Msk              /*!< Filter 4 register 1 bit 30 */
#define CAN_F4B1_FBC31_Pos						(31U)                           
#define CAN_F4B1_FBC31_Msk						(0x1UL << CAN_F4B1_FBC31_Pos)   
#define CAN_F4B1_FBC31							CAN_F4B1_FBC31_Msk              /*!< Filter 4 register 1 bit 31 */

/*******************  Bit definition for CAN_F5R1 register  *******************/
#define CAN_F5B1_FBC0_Pos						(0U)
#define CAN_F5B1_FBC0_Msk						(0x1UL << CAN_F5B1_FBC0_Pos)
#define CAN_F5B1_FBC0							CAN_F5B1_FBC0_Msk				/*!< Filter 5 register 1 bit 0 */
#define CAN_F5B1_FBC1_Pos						(1U)                            
#define CAN_F5B1_FBC1_Msk						(0x1UL << CAN_F5B1_FBC1_Pos)    
#define CAN_F5B1_FBC1							CAN_F5B1_FBC1_Msk               /*!< Filter 5 register 1 bit 1 */
#define CAN_F5B1_FBC2_Pos						(2U)                            
#define CAN_F5B1_FBC2_Msk						(0x1UL << CAN_F5B1_FBC2_Pos)    
#define CAN_F5B1_FBC2							CAN_F5B1_FBC2_Msk               /*!< Filter 5 register 1 bit 2 */
#define CAN_F5B1_FBC3_Pos						(3U)                            
#define CAN_F5B1_FBC3_Msk						(0x1UL << CAN_F5B1_FBC3_Pos)    
#define CAN_F5B1_FBC3							CAN_F5B1_FBC3_Msk               /*!< Filter 5 register 1 bit 3 */
#define CAN_F5B1_FBC4_Pos						(4U)                            
#define CAN_F5B1_FBC4_Msk						(0x1UL << CAN_F5B1_FBC4_Pos)    
#define CAN_F5B1_FBC4							CAN_F5B1_FBC4_Msk               /*!< Filter 5 register 1 bit 4 */
#define CAN_F5B1_FBC5_Pos						(5U)                            
#define CAN_F5B1_FBC5_Msk						(0x1UL << CAN_F5B1_FBC5_Pos)    
#define CAN_F5B1_FBC5							CAN_F5B1_FBC5_Msk               /*!< Filter 5 register 1 bit 5 */
#define CAN_F5B1_FBC6_Pos						(6U)                            
#define CAN_F5B1_FBC6_Msk						(0x1UL << CAN_F5B1_FBC6_Pos)    
#define CAN_F5B1_FBC6							CAN_F5B1_FBC6_Msk               /*!< Filter 5 register 1 bit 6 */
#define CAN_F5B1_FBC7_Pos						(7U)                            
#define CAN_F5B1_FBC7_Msk						(0x1UL << CAN_F5B1_FBC7_Pos)    
#define CAN_F5B1_FBC7							CAN_F5B1_FBC7_Msk               /*!< Filter 5 register 1 bit 7 */
#define CAN_F5B1_FBC8_Pos						(8U)                            
#define CAN_F5B1_FBC8_Msk						(0x1UL << CAN_F5B1_FBC8_Pos)    
#define CAN_F5B1_FBC8							CAN_F5B1_FBC8_Msk               /*!< Filter 5 register 1 bit 8 */
#define CAN_F5B1_FBC9_Pos						(9U)                            
#define CAN_F5B1_FBC9_Msk						(0x1UL << CAN_F5B1_FBC9_Pos)    
#define CAN_F5B1_FBC9							CAN_F5B1_FBC9_Msk               /*!< Filter 5 register 1 bit 9 */
#define CAN_F5B1_FBC10_Pos						(10U)                           
#define CAN_F5B1_FBC10_Msk						(0x1UL << CAN_F5B1_FBC10_Pos)   
#define CAN_F5B1_FBC10							CAN_F5B1_FBC10_Msk              /*!< Filter 5 register 1 bit 10 */
#define CAN_F5B1_FBC11_Pos						(11U)                           
#define CAN_F5B1_FBC11_Msk						(0x1UL << CAN_F5B1_FBC11_Pos)   
#define CAN_F5B1_FBC11							CAN_F5B1_FBC11_Msk              /*!< Filter 5 register 1 bit 11 */
#define CAN_F5B1_FBC12_Pos						(12U)                           
#define CAN_F5B1_FBC12_Msk						(0x1UL << CAN_F5B1_FBC12_Pos)   
#define CAN_F5B1_FBC12							CAN_F5B1_FBC12_Msk              /*!< Filter 5 register 1 bit 12 */
#define CAN_F5B1_FBC13_Pos						(13U)                           
#define CAN_F5B1_FBC13_Msk						(0x1UL << CAN_F5B1_FBC13_Pos)   
#define CAN_F5B1_FBC13							CAN_F5B1_FBC13_Msk              /*!< Filter 5 register 1 bit 13 */
#define CAN_F5B1_FBC14_Pos						(14U)                           
#define CAN_F5B1_FBC14_Msk						(0x1UL << CAN_F5B1_FBC14_Pos)   
#define CAN_F5B1_FBC14							CAN_F5B1_FBC14_Msk              /*!< Filter 5 register 1 bit 14 */
#define CAN_F5B1_FBC15_Pos						(15U)                           
#define CAN_F5B1_FBC15_Msk						(0x1UL << CAN_F5B1_FBC15_Pos)   
#define CAN_F5B1_FBC15							CAN_F5B1_FBC15_Msk              /*!< Filter 5 register 1 bit 15 */
#define CAN_F5B1_FBC16_Pos						(16U)                           
#define CAN_F5B1_FBC16_Msk						(0x1UL << CAN_F5B1_FBC16_Pos)   
#define CAN_F5B1_FBC16							CAN_F5B1_FBC16_Msk              /*!< Filter 5 register 1 bit 16 */
#define CAN_F5B1_FBC17_Pos						(17U)                           
#define CAN_F5B1_FBC17_Msk						(0x1UL << CAN_F5B1_FBC17_Pos)   
#define CAN_F5B1_FBC17							CAN_F5B1_FBC17_Msk              /*!< Filter 5 register 1 bit 17 */
#define CAN_F5B1_FBC18_Pos						(18U)                           
#define CAN_F5B1_FBC18_Msk						(0x1UL << CAN_F5B1_FBC18_Pos)   
#define CAN_F5B1_FBC18							CAN_F5B1_FBC18_Msk              /*!< Filter 5 register 1 bit 18 */
#define CAN_F5B1_FBC19_Pos						(19U)                           
#define CAN_F5B1_FBC19_Msk						(0x1UL << CAN_F5B1_FBC19_Pos)   
#define CAN_F5B1_FBC19							CAN_F5B1_FBC19_Msk              /*!< Filter 5 register 1 bit 19 */
#define CAN_F5B1_FBC20_Pos						(20U)                           
#define CAN_F5B1_FBC20_Msk						(0x1UL << CAN_F5B1_FBC20_Pos)   
#define CAN_F5B1_FBC20							CAN_F5B1_FBC20_Msk              /*!< Filter 5 register 1 bit 20 */
#define CAN_F5B1_FBC21_Pos						(21U)                           
#define CAN_F5B1_FBC21_Msk						(0x1UL << CAN_F5B1_FBC21_Pos)   
#define CAN_F5B1_FBC21							CAN_F5B1_FBC21_Msk              /*!< Filter 5 register 1 bit 21 */
#define CAN_F5B1_FBC22_Pos						(22U)                           
#define CAN_F5B1_FBC22_Msk						(0x1UL << CAN_F5B1_FBC22_Pos)   
#define CAN_F5B1_FBC22							CAN_F5B1_FBC22_Msk              /*!< Filter 5 register 1 bit 22 */
#define CAN_F5B1_FBC23_Pos						(23U)                           
#define CAN_F5B1_FBC23_Msk						(0x1UL << CAN_F5B1_FBC23_Pos)   
#define CAN_F5B1_FBC23							CAN_F5B1_FBC23_Msk              /*!< Filter 5 register 1 bit 23 */
#define CAN_F5B1_FBC24_Pos						(24U)                           
#define CAN_F5B1_FBC24_Msk						(0x1UL << CAN_F5B1_FBC24_Pos)   
#define CAN_F5B1_FBC24							CAN_F5B1_FBC24_Msk              /*!< Filter 5 register 1 bit 24 */
#define CAN_F5B1_FBC25_Pos						(25U)                           
#define CAN_F5B1_FBC25_Msk						(0x1UL << CAN_F5B1_FBC25_Pos)   
#define CAN_F5B1_FBC25							CAN_F5B1_FBC25_Msk              /*!< Filter 5 register 1 bit 25 */
#define CAN_F5B1_FBC26_Pos						(26U)                           
#define CAN_F5B1_FBC26_Msk						(0x1UL << CAN_F5B1_FBC26_Pos)   
#define CAN_F5B1_FBC26							CAN_F5B1_FBC26_Msk              /*!< Filter 5 register 1 bit 26 */
#define CAN_F5B1_FBC27_Pos						(27U)                           
#define CAN_F5B1_FBC27_Msk						(0x1UL << CAN_F5B1_FBC27_Pos)   
#define CAN_F5B1_FBC27							CAN_F5B1_FBC27_Msk              /*!< Filter 5 register 1 bit 27 */
#define CAN_F5B1_FBC28_Pos						(28U)                           
#define CAN_F5B1_FBC28_Msk						(0x1UL << CAN_F5B1_FBC28_Pos)   
#define CAN_F5B1_FBC28							CAN_F5B1_FBC28_Msk              /*!< Filter 5 register 1 bit 28 */
#define CAN_F5B1_FBC29_Pos						(29U)                           
#define CAN_F5B1_FBC29_Msk						(0x1UL << CAN_F5B1_FBC29_Pos)   
#define CAN_F5B1_FBC29							CAN_F5B1_FBC29_Msk              /*!< Filter 5 register 1 bit 29 */
#define CAN_F5B1_FBC30_Pos						(30U)                           
#define CAN_F5B1_FBC30_Msk						(0x1UL << CAN_F5B1_FBC30_Pos)   
#define CAN_F5B1_FBC30							CAN_F5B1_FBC30_Msk              /*!< Filter 5 register 1 bit 30 */
#define CAN_F5B1_FBC31_Pos						(31U)                           
#define CAN_F5B1_FBC31_Msk						(0x1UL << CAN_F5B1_FBC31_Pos)   
#define CAN_F5B1_FBC31							CAN_F5B1_FBC31_Msk              /*!< Filter 5 register 1 bit 31 */

/*******************  Bit definition for CAN_F6R1 register  *******************/
#define CAN_F6B1_FBC0_Pos						(0U)
#define CAN_F6B1_FBC0_Msk						(0x1UL << CAN_F6B1_FBC0_Pos)
#define CAN_F6B1_FBC0							CAN_F6B1_FBC0_Msk				/*!< Filter 6 register 1 bit 0 */
#define CAN_F6B1_FBC1_Pos						(1U)                            
#define CAN_F6B1_FBC1_Msk						(0x1UL << CAN_F6B1_FBC1_Pos)    
#define CAN_F6B1_FBC1							CAN_F6B1_FBC1_Msk               /*!< Filter 6 register 1 bit 1 */
#define CAN_F6B1_FBC2_Pos						(2U)                            
#define CAN_F6B1_FBC2_Msk						(0x1UL << CAN_F6B1_FBC2_Pos)    
#define CAN_F6B1_FBC2							CAN_F6B1_FBC2_Msk               /*!< Filter 6 register 1 bit 2 */
#define CAN_F6B1_FBC3_Pos						(3U)                            
#define CAN_F6B1_FBC3_Msk						(0x1UL << CAN_F6B1_FBC3_Pos)    
#define CAN_F6B1_FBC3							CAN_F6B1_FBC3_Msk               /*!< Filter 6 register 1 bit 3 */
#define CAN_F6B1_FBC4_Pos						(4U)                            
#define CAN_F6B1_FBC4_Msk						(0x1UL << CAN_F6B1_FBC4_Pos)    
#define CAN_F6B1_FBC4							CAN_F6B1_FBC4_Msk               /*!< Filter 6 register 1 bit 4 */
#define CAN_F6B1_FBC5_Pos						(5U)                            
#define CAN_F6B1_FBC5_Msk						(0x1UL << CAN_F6B1_FBC5_Pos)    
#define CAN_F6B1_FBC5							CAN_F6B1_FBC5_Msk               /*!< Filter 6 register 1 bit 5 */
#define CAN_F6B1_FBC6_Pos						(6U)                            
#define CAN_F6B1_FBC6_Msk						(0x1UL << CAN_F6B1_FBC6_Pos)    
#define CAN_F6B1_FBC6							CAN_F6B1_FBC6_Msk               /*!< Filter 6 register 1 bit 6 */
#define CAN_F6B1_FBC7_Pos						(7U)                            
#define CAN_F6B1_FBC7_Msk						(0x1UL << CAN_F6B1_FBC7_Pos)    
#define CAN_F6B1_FBC7							CAN_F6B1_FBC7_Msk               /*!< Filter 6 register 1 bit 7 */
#define CAN_F6B1_FBC8_Pos						(8U)                            
#define CAN_F6B1_FBC8_Msk						(0x1UL << CAN_F6B1_FBC8_Pos)    
#define CAN_F6B1_FBC8							CAN_F6B1_FBC8_Msk               /*!< Filter 6 register 1 bit 8 */
#define CAN_F6B1_FBC9_Pos						(9U)                            
#define CAN_F6B1_FBC9_Msk						(0x1UL << CAN_F6B1_FBC9_Pos)    
#define CAN_F6B1_FBC9							CAN_F6B1_FBC9_Msk               /*!< Filter 6 register 1 bit 9 */
#define CAN_F6B1_FBC10_Pos						(10U)                           
#define CAN_F6B1_FBC10_Msk						(0x1UL << CAN_F6B1_FBC10_Pos)   
#define CAN_F6B1_FBC10							CAN_F6B1_FBC10_Msk              /*!< Filter 6 register 1 bit 10 */
#define CAN_F6B1_FBC11_Pos						(11U)                           
#define CAN_F6B1_FBC11_Msk						(0x1UL << CAN_F6B1_FBC11_Pos)   
#define CAN_F6B1_FBC11							CAN_F6B1_FBC11_Msk              /*!< Filter 6 register 1 bit 11 */
#define CAN_F6B1_FBC12_Pos						(12U)                           
#define CAN_F6B1_FBC12_Msk						(0x1UL << CAN_F6B1_FBC12_Pos)   
#define CAN_F6B1_FBC12							CAN_F6B1_FBC12_Msk              /*!< Filter 6 register 1 bit 12 */
#define CAN_F6B1_FBC13_Pos						(13U)                           
#define CAN_F6B1_FBC13_Msk						(0x1UL << CAN_F6B1_FBC13_Pos)   
#define CAN_F6B1_FBC13							CAN_F6B1_FBC13_Msk              /*!< Filter 6 register 1 bit 13 */
#define CAN_F6B1_FBC14_Pos						(14U)                           
#define CAN_F6B1_FBC14_Msk						(0x1UL << CAN_F6B1_FBC14_Pos)   
#define CAN_F6B1_FBC14							CAN_F6B1_FBC14_Msk              /*!< Filter 6 register 1 bit 14 */
#define CAN_F6B1_FBC15_Pos						(15U)                           
#define CAN_F6B1_FBC15_Msk						(0x1UL << CAN_F6B1_FBC15_Pos)   
#define CAN_F6B1_FBC15							CAN_F6B1_FBC15_Msk              /*!< Filter 6 register 1 bit 15 */
#define CAN_F6B1_FBC16_Pos						(16U)                           
#define CAN_F6B1_FBC16_Msk						(0x1UL << CAN_F6B1_FBC16_Pos)   
#define CAN_F6B1_FBC16							CAN_F6B1_FBC16_Msk              /*!< Filter 6 register 1 bit 16 */
#define CAN_F6B1_FBC17_Pos						(17U)                           
#define CAN_F6B1_FBC17_Msk						(0x1UL << CAN_F6B1_FBC17_Pos)   
#define CAN_F6B1_FBC17							CAN_F6B1_FBC17_Msk              /*!< Filter 6 register 1 bit 17 */
#define CAN_F6B1_FBC18_Pos						(18U)                           
#define CAN_F6B1_FBC18_Msk						(0x1UL << CAN_F6B1_FBC18_Pos)   
#define CAN_F6B1_FBC18							CAN_F6B1_FBC18_Msk              /*!< Filter 6 register 1 bit 18 */
#define CAN_F6B1_FBC19_Pos						(19U)                           
#define CAN_F6B1_FBC19_Msk						(0x1UL << CAN_F6B1_FBC19_Pos)   
#define CAN_F6B1_FBC19							CAN_F6B1_FBC19_Msk              /*!< Filter 6 register 1 bit 19 */
#define CAN_F6B1_FBC20_Pos						(20U)                           
#define CAN_F6B1_FBC20_Msk						(0x1UL << CAN_F6B1_FBC20_Pos)   
#define CAN_F6B1_FBC20							CAN_F6B1_FBC20_Msk              /*!< Filter 6 register 1 bit 20 */
#define CAN_F6B1_FBC21_Pos						(21U)                           
#define CAN_F6B1_FBC21_Msk						(0x1UL << CAN_F6B1_FBC21_Pos)   
#define CAN_F6B1_FBC21							CAN_F6B1_FBC21_Msk              /*!< Filter 6 register 1 bit 21 */
#define CAN_F6B1_FBC22_Pos						(22U)                           
#define CAN_F6B1_FBC22_Msk						(0x1UL << CAN_F6B1_FBC22_Pos)   
#define CAN_F6B1_FBC22							CAN_F6B1_FBC22_Msk              /*!< Filter 6 register 1 bit 22 */
#define CAN_F6B1_FBC23_Pos						(23U)                           
#define CAN_F6B1_FBC23_Msk						(0x1UL << CAN_F6B1_FBC23_Pos)   
#define CAN_F6B1_FBC23							CAN_F6B1_FBC23_Msk              /*!< Filter 6 register 1 bit 23 */
#define CAN_F6B1_FBC24_Pos						(24U)                           
#define CAN_F6B1_FBC24_Msk						(0x1UL << CAN_F6B1_FBC24_Pos)   
#define CAN_F6B1_FBC24							CAN_F6B1_FBC24_Msk              /*!< Filter 6 register 1 bit 24 */
#define CAN_F6B1_FBC25_Pos						(25U)                           
#define CAN_F6B1_FBC25_Msk						(0x1UL << CAN_F6B1_FBC25_Pos)   
#define CAN_F6B1_FBC25							CAN_F6B1_FBC25_Msk              /*!< Filter 6 register 1 bit 25 */
#define CAN_F6B1_FBC26_Pos						(26U)                           
#define CAN_F6B1_FBC26_Msk						(0x1UL << CAN_F6B1_FBC26_Pos)   
#define CAN_F6B1_FBC26							CAN_F6B1_FBC26_Msk              /*!< Filter 6 register 1 bit 26 */
#define CAN_F6B1_FBC27_Pos						(27U)                           
#define CAN_F6B1_FBC27_Msk						(0x1UL << CAN_F6B1_FBC27_Pos)   
#define CAN_F6B1_FBC27							CAN_F6B1_FBC27_Msk              /*!< Filter 6 register 1 bit 27 */
#define CAN_F6B1_FBC28_Pos						(28U)                           
#define CAN_F6B1_FBC28_Msk						(0x1UL << CAN_F6B1_FBC28_Pos)   
#define CAN_F6B1_FBC28							CAN_F6B1_FBC28_Msk              /*!< Filter 6 register 1 bit 28 */
#define CAN_F6B1_FBC29_Pos						(29U)                           
#define CAN_F6B1_FBC29_Msk						(0x1UL << CAN_F6B1_FBC29_Pos)   
#define CAN_F6B1_FBC29							CAN_F6B1_FBC29_Msk              /*!< Filter 6 register 1 bit 29 */
#define CAN_F6B1_FBC30_Pos						(30U)                           
#define CAN_F6B1_FBC30_Msk						(0x1UL << CAN_F6B1_FBC30_Pos)   
#define CAN_F6B1_FBC30							CAN_F6B1_FBC30_Msk              /*!< Filter 6 register 1 bit 30 */
#define CAN_F6B1_FBC31_Pos						(31U)                           
#define CAN_F6B1_FBC31_Msk						(0x1UL << CAN_F6B1_FBC31_Pos)   
#define CAN_F6B1_FBC31							CAN_F6B1_FBC31_Msk              /*!< Filter 6 register 1 bit 31 */

/*******************  Bit definition for CAN_F7R1 register  *******************/
#define CAN_F7B1_FBC0_Pos						(0U)
#define CAN_F7B1_FBC0_Msk						(0x1UL << CAN_F7B1_FBC0_Pos)
#define CAN_F7B1_FBC0							CAN_F7B1_FBC0_Msk				/*!< Filter 7 register 1 bit 0 */
#define CAN_F7B1_FBC1_Pos						(1U)                            
#define CAN_F7B1_FBC1_Msk						(0x1UL << CAN_F7B1_FBC1_Pos)    
#define CAN_F7B1_FBC1							CAN_F7B1_FBC1_Msk               /*!< Filter 7 register 1 bit 1 */
#define CAN_F7B1_FBC2_Pos						(2U)                            
#define CAN_F7B1_FBC2_Msk						(0x1UL << CAN_F7B1_FBC2_Pos)    
#define CAN_F7B1_FBC2							CAN_F7B1_FBC2_Msk               /*!< Filter 7 register 1 bit 2 */
#define CAN_F7B1_FBC3_Pos						(3U)                            
#define CAN_F7B1_FBC3_Msk						(0x1UL << CAN_F7B1_FBC3_Pos)    
#define CAN_F7B1_FBC3							CAN_F7B1_FBC3_Msk               /*!< Filter 7 register 1 bit 3 */
#define CAN_F7B1_FBC4_Pos						(4U)                            
#define CAN_F7B1_FBC4_Msk						(0x1UL << CAN_F7B1_FBC4_Pos)    
#define CAN_F7B1_FBC4							CAN_F7B1_FBC4_Msk               /*!< Filter 7 register 1 bit 4 */
#define CAN_F7B1_FBC5_Pos						(5U)                            
#define CAN_F7B1_FBC5_Msk						(0x1UL << CAN_F7B1_FBC5_Pos)    
#define CAN_F7B1_FBC5							CAN_F7B1_FBC5_Msk               /*!< Filter 7 register 1 bit 5 */
#define CAN_F7B1_FBC6_Pos						(6U)                            
#define CAN_F7B1_FBC6_Msk						(0x1UL << CAN_F7B1_FBC6_Pos)    
#define CAN_F7B1_FBC6							CAN_F7B1_FBC6_Msk               /*!< Filter 7 register 1 bit 6 */
#define CAN_F7B1_FBC7_Pos						(7U)                            
#define CAN_F7B1_FBC7_Msk						(0x1UL << CAN_F7B1_FBC7_Pos)    
#define CAN_F7B1_FBC7							CAN_F7B1_FBC7_Msk               /*!< Filter 7 register 1 bit 7 */
#define CAN_F7B1_FBC8_Pos						(8U)                            
#define CAN_F7B1_FBC8_Msk						(0x1UL << CAN_F7B1_FBC8_Pos)    
#define CAN_F7B1_FBC8							CAN_F7B1_FBC8_Msk               /*!< Filter 7 register 1 bit 8 */
#define CAN_F7B1_FBC9_Pos						(9U)                            
#define CAN_F7B1_FBC9_Msk						(0x1UL << CAN_F7B1_FBC9_Pos)    
#define CAN_F7B1_FBC9							CAN_F7B1_FBC9_Msk               /*!< Filter 7 register 1 bit 9 */
#define CAN_F7B1_FBC10_Pos						(10U)                           
#define CAN_F7B1_FBC10_Msk						(0x1UL << CAN_F7B1_FBC10_Pos)   
#define CAN_F7B1_FBC10							CAN_F7B1_FBC10_Msk              /*!< Filter 7 register 1 bit 10 */
#define CAN_F7B1_FBC11_Pos						(11U)                           
#define CAN_F7B1_FBC11_Msk						(0x1UL << CAN_F7B1_FBC11_Pos)   
#define CAN_F7B1_FBC11							CAN_F7B1_FBC11_Msk              /*!< Filter 7 register 1 bit 11 */
#define CAN_F7B1_FBC12_Pos						(12U)                           
#define CAN_F7B1_FBC12_Msk						(0x1UL << CAN_F7B1_FBC12_Pos)   
#define CAN_F7B1_FBC12							CAN_F7B1_FBC12_Msk              /*!< Filter 7 register 1 bit 12 */
#define CAN_F7B1_FBC13_Pos						(13U)                           
#define CAN_F7B1_FBC13_Msk						(0x1UL << CAN_F7B1_FBC13_Pos)   
#define CAN_F7B1_FBC13							CAN_F7B1_FBC13_Msk              /*!< Filter 7 register 1 bit 13 */
#define CAN_F7B1_FBC14_Pos						(14U)                           
#define CAN_F7B1_FBC14_Msk						(0x1UL << CAN_F7B1_FBC14_Pos)   
#define CAN_F7B1_FBC14							CAN_F7B1_FBC14_Msk              /*!< Filter 7 register 1 bit 14 */
#define CAN_F7B1_FBC15_Pos						(15U)                           
#define CAN_F7B1_FBC15_Msk						(0x1UL << CAN_F7B1_FBC15_Pos)   
#define CAN_F7B1_FBC15							CAN_F7B1_FBC15_Msk              /*!< Filter 7 register 1 bit 15 */
#define CAN_F7B1_FBC16_Pos						(16U)                           
#define CAN_F7B1_FBC16_Msk						(0x1UL << CAN_F7B1_FBC16_Pos)   
#define CAN_F7B1_FBC16							CAN_F7B1_FBC16_Msk              /*!< Filter 7 register 1 bit 16 */
#define CAN_F7B1_FBC17_Pos						(17U)                           
#define CAN_F7B1_FBC17_Msk						(0x1UL << CAN_F7B1_FBC17_Pos)   
#define CAN_F7B1_FBC17							CAN_F7B1_FBC17_Msk              /*!< Filter 7 register 1 bit 17 */
#define CAN_F7B1_FBC18_Pos						(18U)                           
#define CAN_F7B1_FBC18_Msk						(0x1UL << CAN_F7B1_FBC18_Pos)   
#define CAN_F7B1_FBC18							CAN_F7B1_FBC18_Msk              /*!< Filter 7 register 1 bit 18 */
#define CAN_F7B1_FBC19_Pos						(19U)                           
#define CAN_F7B1_FBC19_Msk						(0x1UL << CAN_F7B1_FBC19_Pos)   
#define CAN_F7B1_FBC19							CAN_F7B1_FBC19_Msk              /*!< Filter 7 register 1 bit 19 */
#define CAN_F7B1_FBC20_Pos						(20U)                           
#define CAN_F7B1_FBC20_Msk						(0x1UL << CAN_F7B1_FBC20_Pos)   
#define CAN_F7B1_FBC20							CAN_F7B1_FBC20_Msk              /*!< Filter 7 register 1 bit 20 */
#define CAN_F7B1_FBC21_Pos						(21U)                           
#define CAN_F7B1_FBC21_Msk						(0x1UL << CAN_F7B1_FBC21_Pos)   
#define CAN_F7B1_FBC21							CAN_F7B1_FBC21_Msk              /*!< Filter 7 register 1 bit 21 */
#define CAN_F7B1_FBC22_Pos						(22U)                           
#define CAN_F7B1_FBC22_Msk						(0x1UL << CAN_F7B1_FBC22_Pos)   
#define CAN_F7B1_FBC22							CAN_F7B1_FBC22_Msk              /*!< Filter 7 register 1 bit 22 */
#define CAN_F7B1_FBC23_Pos						(23U)                           
#define CAN_F7B1_FBC23_Msk						(0x1UL << CAN_F7B1_FBC23_Pos)   
#define CAN_F7B1_FBC23							CAN_F7B1_FBC23_Msk              /*!< Filter 7 register 1 bit 23 */
#define CAN_F7B1_FBC24_Pos						(24U)                           
#define CAN_F7B1_FBC24_Msk						(0x1UL << CAN_F7B1_FBC24_Pos)   
#define CAN_F7B1_FBC24							CAN_F7B1_FBC24_Msk              /*!< Filter 7 register 1 bit 24 */
#define CAN_F7B1_FBC25_Pos						(25U)                           
#define CAN_F7B1_FBC25_Msk						(0x1UL << CAN_F7B1_FBC25_Pos)   
#define CAN_F7B1_FBC25							CAN_F7B1_FBC25_Msk              /*!< Filter 7 register 1 bit 25 */
#define CAN_F7B1_FBC26_Pos						(26U)                           
#define CAN_F7B1_FBC26_Msk						(0x1UL << CAN_F7B1_FBC26_Pos)   
#define CAN_F7B1_FBC26							CAN_F7B1_FBC26_Msk              /*!< Filter 7 register 1 bit 26 */
#define CAN_F7B1_FBC27_Pos						(27U)                           
#define CAN_F7B1_FBC27_Msk						(0x1UL << CAN_F7B1_FBC27_Pos)   
#define CAN_F7B1_FBC27							CAN_F7B1_FBC27_Msk              /*!< Filter 7 register 1 bit 27 */
#define CAN_F7B1_FBC28_Pos						(28U)                           
#define CAN_F7B1_FBC28_Msk						(0x1UL << CAN_F7B1_FBC28_Pos)   
#define CAN_F7B1_FBC28							CAN_F7B1_FBC28_Msk              /*!< Filter 7 register 1 bit 28 */
#define CAN_F7B1_FBC29_Pos						(29U)                           
#define CAN_F7B1_FBC29_Msk						(0x1UL << CAN_F7B1_FBC29_Pos)   
#define CAN_F7B1_FBC29							CAN_F7B1_FBC29_Msk              /*!< Filter 7 register 1 bit 29 */
#define CAN_F7B1_FBC30_Pos						(30U)                           
#define CAN_F7B1_FBC30_Msk						(0x1UL << CAN_F7B1_FBC30_Pos)
#define CAN_F7B1_FBC30							CAN_F7B1_FBC30_Msk              /*!< Filter 7 register 1 bit 30 */
#define CAN_F7B1_FBC31_Pos						(31U)                           
#define CAN_F7B1_FBC31_Msk						(0x1UL << CAN_F7B1_FBC31_Pos)   
#define CAN_F7B1_FBC31							CAN_F7B1_FBC31_Msk              /*!< Filter 7 register 1 bit 31 */

/*******************  Bit definition for CAN_F8R1 register  *******************/
#define CAN_F8B1_FBC0_Pos						(0U)
#define CAN_F8B1_FBC0_Msk						(0x1UL << CAN_F8B1_FBC0_Pos)
#define CAN_F8B1_FBC0							CAN_F8B1_FBC0_Msk				/*!< Filter 8 register 1 bit 0 */
#define CAN_F8B1_FBC1_Pos						(1U)                            
#define CAN_F8B1_FBC1_Msk						(0x1UL << CAN_F8B1_FBC1_Pos)    
#define CAN_F8B1_FBC1							CAN_F8B1_FBC1_Msk               /*!< Filter 8 register 1 bit 1 */
#define CAN_F8B1_FBC2_Pos						(2U)                            
#define CAN_F8B1_FBC2_Msk						(0x1UL << CAN_F8B1_FBC2_Pos)    
#define CAN_F8B1_FBC2							CAN_F8B1_FBC2_Msk               /*!< Filter 8 register 1 bit 2 */
#define CAN_F8B1_FBC3_Pos						(3U)                            
#define CAN_F8B1_FBC3_Msk						(0x1UL << CAN_F8B1_FBC3_Pos)    
#define CAN_F8B1_FBC3							CAN_F8B1_FBC3_Msk               /*!< Filter 8 register 1 bit 3 */
#define CAN_F8B1_FBC4_Pos						(4U)                            
#define CAN_F8B1_FBC4_Msk						(0x1UL << CAN_F8B1_FBC4_Pos)    
#define CAN_F8B1_FBC4							CAN_F8B1_FBC4_Msk               /*!< Filter 8 register 1 bit 4 */
#define CAN_F8B1_FBC5_Pos						(5U)                            
#define CAN_F8B1_FBC5_Msk						(0x1UL << CAN_F8B1_FBC5_Pos)    
#define CAN_F8B1_FBC5							CAN_F8B1_FBC5_Msk               /*!< Filter 8 register 1 bit 5 */
#define CAN_F8B1_FBC6_Pos						(6U)                            
#define CAN_F8B1_FBC6_Msk						(0x1UL << CAN_F8B1_FBC6_Pos)    
#define CAN_F8B1_FBC6							CAN_F8B1_FBC6_Msk               /*!< Filter 8 register 1 bit 6 */
#define CAN_F8B1_FBC7_Pos						(7U)                            
#define CAN_F8B1_FBC7_Msk						(0x1UL << CAN_F8B1_FBC7_Pos)    
#define CAN_F8B1_FBC7							CAN_F8B1_FBC7_Msk               /*!< Filter 8 register 1 bit 7 */
#define CAN_F8B1_FBC8_Pos						(8U)                            
#define CAN_F8B1_FBC8_Msk						(0x1UL << CAN_F8B1_FBC8_Pos)    
#define CAN_F8B1_FBC8							CAN_F8B1_FBC8_Msk               /*!< Filter 8 register 1 bit 8 */
#define CAN_F8B1_FBC9_Pos						(9U)                            
#define CAN_F8B1_FBC9_Msk						(0x1UL << CAN_F8B1_FBC9_Pos)    
#define CAN_F8B1_FBC9							CAN_F8B1_FBC9_Msk               /*!< Filter 8 register 1 bit 9 */
#define CAN_F8B1_FBC10_Pos						(10U)                           
#define CAN_F8B1_FBC10_Msk						(0x1UL << CAN_F8B1_FBC10_Pos)   
#define CAN_F8B1_FBC10							CAN_F8B1_FBC10_Msk              /*!< Filter 8 register 1 bit 10 */
#define CAN_F8B1_FBC11_Pos						(11U)                           
#define CAN_F8B1_FBC11_Msk						(0x1UL << CAN_F8B1_FBC11_Pos)   
#define CAN_F8B1_FBC11							CAN_F8B1_FBC11_Msk              /*!< Filter 8 register 1 bit 11 */
#define CAN_F8B1_FBC12_Pos						(12U)                           
#define CAN_F8B1_FBC12_Msk						(0x1UL << CAN_F8B1_FBC12_Pos)   
#define CAN_F8B1_FBC12							CAN_F8B1_FBC12_Msk              /*!< Filter 8 register 1 bit 12 */
#define CAN_F8B1_FBC13_Pos						(13U)                           
#define CAN_F8B1_FBC13_Msk						(0x1UL << CAN_F8B1_FBC13_Pos)   
#define CAN_F8B1_FBC13							CAN_F8B1_FBC13_Msk              /*!< Filter 8 register 1 bit 13 */
#define CAN_F8B1_FBC14_Pos						(14U)                           
#define CAN_F8B1_FBC14_Msk						(0x1UL << CAN_F8B1_FBC14_Pos)   
#define CAN_F8B1_FBC14							CAN_F8B1_FBC14_Msk              /*!< Filter 8 register 1 bit 14 */
#define CAN_F8B1_FBC15_Pos						(15U)                           
#define CAN_F8B1_FBC15_Msk						(0x1UL << CAN_F8B1_FBC15_Pos)   
#define CAN_F8B1_FBC15							CAN_F8B1_FBC15_Msk              /*!< Filter 8 register 1 bit 15 */
#define CAN_F8B1_FBC16_Pos						(16U)                           
#define CAN_F8B1_FBC16_Msk						(0x1UL << CAN_F8B1_FBC16_Pos)   
#define CAN_F8B1_FBC16							CAN_F8B1_FBC16_Msk              /*!< Filter 8 register 1 bit 16 */
#define CAN_F8B1_FBC17_Pos						(17U)                           
#define CAN_F8B1_FBC17_Msk						(0x1UL << CAN_F8B1_FBC17_Pos)   
#define CAN_F8B1_FBC17							CAN_F8B1_FBC17_Msk              /*!< Filter 8 register 1 bit 17 */
#define CAN_F8B1_FBC18_Pos						(18U)                           
#define CAN_F8B1_FBC18_Msk						(0x1UL << CAN_F8B1_FBC18_Pos)   
#define CAN_F8B1_FBC18							CAN_F8B1_FBC18_Msk              /*!< Filter 8 register 1 bit 18 */
#define CAN_F8B1_FBC19_Pos						(19U)                           
#define CAN_F8B1_FBC19_Msk						(0x1UL << CAN_F8B1_FBC19_Pos)   
#define CAN_F8B1_FBC19							CAN_F8B1_FBC19_Msk              /*!< Filter 8 register 1 bit 19 */
#define CAN_F8B1_FBC20_Pos						(20U)                           
#define CAN_F8B1_FBC20_Msk						(0x1UL << CAN_F8B1_FBC20_Pos)   
#define CAN_F8B1_FBC20							CAN_F8B1_FBC20_Msk              /*!< Filter 8 register 1 bit 20 */
#define CAN_F8B1_FBC21_Pos						(21U)                           
#define CAN_F8B1_FBC21_Msk						(0x1UL << CAN_F8B1_FBC21_Pos)   
#define CAN_F8B1_FBC21							CAN_F8B1_FBC21_Msk              /*!< Filter 8 register 1 bit 21 */
#define CAN_F8B1_FBC22_Pos						(22U)                           
#define CAN_F8B1_FBC22_Msk						(0x1UL << CAN_F8B1_FBC22_Pos)   
#define CAN_F8B1_FBC22							CAN_F8B1_FBC22_Msk              /*!< Filter 8 register 1 bit 22 */
#define CAN_F8B1_FBC23_Pos						(23U)                           
#define CAN_F8B1_FBC23_Msk						(0x1UL << CAN_F8B1_FBC23_Pos)   
#define CAN_F8B1_FBC23							CAN_F8B1_FBC23_Msk              /*!< Filter 8 register 1 bit 23 */
#define CAN_F8B1_FBC24_Pos						(24U)                           
#define CAN_F8B1_FBC24_Msk						(0x1UL << CAN_F8B1_FBC24_Pos)   
#define CAN_F8B1_FBC24							CAN_F8B1_FBC24_Msk              /*!< Filter 8 register 1 bit 24 */
#define CAN_F8B1_FBC25_Pos						(25U)                           
#define CAN_F8B1_FBC25_Msk						(0x1UL << CAN_F8B1_FBC25_Pos)   
#define CAN_F8B1_FBC25							CAN_F8B1_FBC25_Msk              /*!< Filter 8 register 1 bit 25 */
#define CAN_F8B1_FBC26_Pos						(26U)                           
#define CAN_F8B1_FBC26_Msk						(0x1UL << CAN_F8B1_FBC26_Pos)   
#define CAN_F8B1_FBC26							CAN_F8B1_FBC26_Msk              /*!< Filter 8 register 1 bit 26 */
#define CAN_F8B1_FBC27_Pos						(27U)                           
#define CAN_F8B1_FBC27_Msk						(0x1UL << CAN_F8B1_FBC27_Pos)   
#define CAN_F8B1_FBC27							CAN_F8B1_FBC27_Msk              /*!< Filter 8 register 1 bit 27 */
#define CAN_F8B1_FBC28_Pos						(28U)                           
#define CAN_F8B1_FBC28_Msk						(0x1UL << CAN_F8B1_FBC28_Pos)   
#define CAN_F8B1_FBC28							CAN_F8B1_FBC28_Msk              /*!< Filter 8 register 1 bit 28 */
#define CAN_F8B1_FBC29_Pos						(29U)                           
#define CAN_F8B1_FBC29_Msk						(0x1UL << CAN_F8B1_FBC29_Pos)   
#define CAN_F8B1_FBC29							CAN_F8B1_FBC29_Msk              /*!< Filter 8 register 1 bit 29 */
#define CAN_F8B1_FBC30_Pos						(30U)                           
#define CAN_F8B1_FBC30_Msk						(0x1UL << CAN_F8B1_FBC30_Pos)   
#define CAN_F8B1_FBC30							CAN_F8B1_FBC30_Msk              /*!< Filter 8 register 1 bit 30 */
#define CAN_F8B1_FBC31_Pos						(31U)                           
#define CAN_F8B1_FBC31_Msk						(0x1UL << CAN_F8B1_FBC31_Pos)   
#define CAN_F8B1_FBC31							CAN_F8B1_FBC31_Msk              /*!< Filter 8 register 1 bit 31 */

/*******************  Bit definition for CAN_F9R1 register  *******************/
#define CAN_F9B1_FBC0_Pos						(0U)
#define CAN_F9B1_FBC0_Msk						(0x1UL << CAN_F9B1_FBC0_Pos)
#define CAN_F9B1_FBC0							CAN_F9B1_FBC0_Msk				/*!< Filter 9 register 1 bit 0 */
#define CAN_F9B1_FBC1_Pos						(1U)                            
#define CAN_F9B1_FBC1_Msk						(0x1UL << CAN_F9B1_FBC1_Pos)    
#define CAN_F9B1_FBC1							CAN_F9B1_FBC1_Msk               /*!< Filter 9 register 1 bit 1 */
#define CAN_F9B1_FBC2_Pos						(2U)                            
#define CAN_F9B1_FBC2_Msk						(0x1UL << CAN_F9B1_FBC2_Pos)    
#define CAN_F9B1_FBC2							CAN_F9B1_FBC2_Msk               /*!< Filter 9 register 1 bit 2 */
#define CAN_F9B1_FBC3_Pos						(3U)                            
#define CAN_F9B1_FBC3_Msk						(0x1UL << CAN_F9B1_FBC3_Pos)    
#define CAN_F9B1_FBC3							CAN_F9B1_FBC3_Msk               /*!< Filter 9 register 1 bit 3 */
#define CAN_F9B1_FBC4_Pos						(4U)                            
#define CAN_F9B1_FBC4_Msk						(0x1UL << CAN_F9B1_FBC4_Pos)    
#define CAN_F9B1_FBC4							CAN_F9B1_FBC4_Msk               /*!< Filter 9 register 1 bit 4 */
#define CAN_F9B1_FBC5_Pos						(5U)                            
#define CAN_F9B1_FBC5_Msk						(0x1UL << CAN_F9B1_FBC5_Pos)    
#define CAN_F9B1_FBC5							CAN_F9B1_FBC5_Msk               /*!< Filter 9 register 1 bit 5 */
#define CAN_F9B1_FBC6_Pos						(6U)                            
#define CAN_F9B1_FBC6_Msk						(0x1UL << CAN_F9B1_FBC6_Pos)    
#define CAN_F9B1_FBC6							CAN_F9B1_FBC6_Msk               /*!< Filter 9 register 1 bit 6 */
#define CAN_F9B1_FBC7_Pos						(7U)                            
#define CAN_F9B1_FBC7_Msk						(0x1UL << CAN_F9B1_FBC7_Pos)    
#define CAN_F9B1_FBC7							CAN_F9B1_FBC7_Msk               /*!< Filter 9 register 1 bit 7 */
#define CAN_F9B1_FBC8_Pos						(8U)                            
#define CAN_F9B1_FBC8_Msk						(0x1UL << CAN_F9B1_FBC8_Pos)    
#define CAN_F9B1_FBC8							CAN_F9B1_FBC8_Msk               /*!< Filter 9 register 1 bit 8 */
#define CAN_F9B1_FBC9_Pos						(9U)                            
#define CAN_F9B1_FBC9_Msk						(0x1UL << CAN_F9B1_FBC9_Pos)    
#define CAN_F9B1_FBC9							CAN_F9B1_FBC9_Msk               /*!< Filter 9 register 1 bit 9 */
#define CAN_F9B1_FBC10_Pos						(10U)                           
#define CAN_F9B1_FBC10_Msk						(0x1UL << CAN_F9B1_FBC10_Pos)   
#define CAN_F9B1_FBC10							CAN_F9B1_FBC10_Msk              /*!< Filter 9 register 1 bit 10 */
#define CAN_F9B1_FBC11_Pos						(11U)                           
#define CAN_F9B1_FBC11_Msk						(0x1UL << CAN_F9B1_FBC11_Pos)   
#define CAN_F9B1_FBC11							CAN_F9B1_FBC11_Msk              /*!< Filter 9 register 1 bit 11 */
#define CAN_F9B1_FBC12_Pos						(12U)                           
#define CAN_F9B1_FBC12_Msk						(0x1UL << CAN_F9B1_FBC12_Pos)   
#define CAN_F9B1_FBC12							CAN_F9B1_FBC12_Msk              /*!< Filter 9 register 1 bit 12 */
#define CAN_F9B1_FBC13_Pos						(13U)                           
#define CAN_F9B1_FBC13_Msk						(0x1UL << CAN_F9B1_FBC13_Pos)   
#define CAN_F9B1_FBC13							CAN_F9B1_FBC13_Msk              /*!< Filter 9 register 1 bit 13 */
#define CAN_F9B1_FBC14_Pos						(14U)                           
#define CAN_F9B1_FBC14_Msk						(0x1UL << CAN_F9B1_FBC14_Pos)   
#define CAN_F9B1_FBC14							CAN_F9B1_FBC14_Msk              /*!< Filter 9 register 1 bit 14 */
#define CAN_F9B1_FBC15_Pos						(15U)                           
#define CAN_F9B1_FBC15_Msk						(0x1UL << CAN_F9B1_FBC15_Pos)
#define CAN_F9B1_FBC15							CAN_F9B1_FBC15_Msk              /*!< Filter 9 register 1 bit 15 */
#define CAN_F9B1_FBC16_Pos						(16U)                           
#define CAN_F9B1_FBC16_Msk						(0x1UL << CAN_F9B1_FBC16_Pos)   
#define CAN_F9B1_FBC16							CAN_F9B1_FBC16_Msk              /*!< Filter 9 register 1 bit 16 */
#define CAN_F9B1_FBC17_Pos						(17U)                           
#define CAN_F9B1_FBC17_Msk						(0x1UL << CAN_F9B1_FBC17_Pos)   
#define CAN_F9B1_FBC17							CAN_F9B1_FBC17_Msk              /*!< Filter 9 register 1 bit 17 */
#define CAN_F9B1_FBC18_Pos						(18U)                           
#define CAN_F9B1_FBC18_Msk						(0x1UL << CAN_F9B1_FBC18_Pos)   
#define CAN_F9B1_FBC18							CAN_F9B1_FBC18_Msk              /*!< Filter 9 register 1 bit 18 */
#define CAN_F9B1_FBC19_Pos						(19U)                           
#define CAN_F9B1_FBC19_Msk						(0x1UL << CAN_F9B1_FBC19_Pos)   
#define CAN_F9B1_FBC19							CAN_F9B1_FBC19_Msk              /*!< Filter 9 register 1 bit 19 */
#define CAN_F9B1_FBC20_Pos						(20U)                           
#define CAN_F9B1_FBC20_Msk						(0x1UL << CAN_F9B1_FBC20_Pos)   
#define CAN_F9B1_FBC20							CAN_F9B1_FBC20_Msk              /*!< Filter 9 register 1 bit 20 */
#define CAN_F9B1_FBC21_Pos						(21U)                           
#define CAN_F9B1_FBC21_Msk						(0x1UL << CAN_F9B1_FBC21_Pos)   
#define CAN_F9B1_FBC21							CAN_F9B1_FBC21_Msk              /*!< Filter 9 register 1 bit 21 */
#define CAN_F9B1_FBC22_Pos						(22U)                           
#define CAN_F9B1_FBC22_Msk						(0x1UL << CAN_F9B1_FBC22_Pos)   
#define CAN_F9B1_FBC22							CAN_F9B1_FBC22_Msk              /*!< Filter 9 register 1 bit 22 */
#define CAN_F9B1_FBC23_Pos						(23U)                           
#define CAN_F9B1_FBC23_Msk						(0x1UL << CAN_F9B1_FBC23_Pos)   
#define CAN_F9B1_FBC23							CAN_F9B1_FBC23_Msk              /*!< Filter 9 register 1 bit 23 */
#define CAN_F9B1_FBC24_Pos						(24U)                           
#define CAN_F9B1_FBC24_Msk						(0x1UL << CAN_F9B1_FBC24_Pos)   
#define CAN_F9B1_FBC24							CAN_F9B1_FBC24_Msk              /*!< Filter 9 register 1 bit 24 */
#define CAN_F9B1_FBC25_Pos						(25U)                           
#define CAN_F9B1_FBC25_Msk						(0x1UL << CAN_F9B1_FBC25_Pos)   
#define CAN_F9B1_FBC25							CAN_F9B1_FBC25_Msk              /*!< Filter 9 register 1 bit 25 */
#define CAN_F9B1_FBC26_Pos						(26U)                           
#define CAN_F9B1_FBC26_Msk						(0x1UL << CAN_F9B1_FBC26_Pos)   
#define CAN_F9B1_FBC26							CAN_F9B1_FBC26_Msk              /*!< Filter 9 register 1 bit 26 */
#define CAN_F9B1_FBC27_Pos						(27U)                           
#define CAN_F9B1_FBC27_Msk						(0x1UL << CAN_F9B1_FBC27_Pos)   
#define CAN_F9B1_FBC27							CAN_F9B1_FBC27_Msk              /*!< Filter 9 register 1 bit 27 */
#define CAN_F9B1_FBC28_Pos						(28U)                           
#define CAN_F9B1_FBC28_Msk						(0x1UL << CAN_F9B1_FBC28_Pos)   
#define CAN_F9B1_FBC28							CAN_F9B1_FBC28_Msk              /*!< Filter 9 register 1 bit 28 */
#define CAN_F9B1_FBC29_Pos						(29U)                           
#define CAN_F9B1_FBC29_Msk						(0x1UL << CAN_F9B1_FBC29_Pos)   
#define CAN_F9B1_FBC29							CAN_F9B1_FBC29_Msk              /*!< Filter 9 register 1 bit 29 */
#define CAN_F9B1_FBC30_Pos						(30U)                           
#define CAN_F9B1_FBC30_Msk						(0x1UL << CAN_F9B1_FBC30_Pos)   
#define CAN_F9B1_FBC30							CAN_F9B1_FBC30_Msk              /*!< Filter 9 register 1 bit 30 */
#define CAN_F9B1_FBC31_Pos						(31U)                           
#define CAN_F9B1_FBC31_Msk						(0x1UL << CAN_F9B1_FBC31_Pos)   
#define CAN_F9B1_FBC31							CAN_F9B1_FBC31_Msk              /*!< Filter 9 register 1 bit 31 */

/******************  Bit definition for CAN_F10R1 register  *******************/
#define CAN_F10B1_FBC0_Pos						(0U)
#define CAN_F10B1_FBC0_Msk						(0x1UL << CAN_F10B1_FBC0_Pos)
#define CAN_F10B1_FBC0							CAN_F10B1_FBC0_Msk				/*!< Filter 10 register 1 bit 0 */
#define CAN_F10B1_FBC1_Pos						(1U)                            
#define CAN_F10B1_FBC1_Msk						(0x1UL << CAN_F10B1_FBC1_Pos)   
#define CAN_F10B1_FBC1							CAN_F10B1_FBC1_Msk              /*!< Filter 10 register 1 bit 1 */
#define CAN_F10B1_FBC2_Pos						(2U)                            
#define CAN_F10B1_FBC2_Msk						(0x1UL << CAN_F10B1_FBC2_Pos)   
#define CAN_F10B1_FBC2							CAN_F10B1_FBC2_Msk              /*!< Filter 10 register 1 bit 2 */
#define CAN_F10B1_FBC3_Pos						(3U)                            
#define CAN_F10B1_FBC3_Msk						(0x1UL << CAN_F10B1_FBC3_Pos)   
#define CAN_F10B1_FBC3							CAN_F10B1_FBC3_Msk              /*!< Filter 10 register 1 bit 3 */
#define CAN_F10B1_FBC4_Pos						(4U)                            
#define CAN_F10B1_FBC4_Msk						(0x1UL << CAN_F10B1_FBC4_Pos)   
#define CAN_F10B1_FBC4							CAN_F10B1_FBC4_Msk              /*!< Filter 10 register 1 bit 4 */
#define CAN_F10B1_FBC5_Pos						(5U)                            
#define CAN_F10B1_FBC5_Msk						(0x1UL << CAN_F10B1_FBC5_Pos)   
#define CAN_F10B1_FBC5							CAN_F10B1_FBC5_Msk              /*!< Filter 10 register 1 bit 5 */
#define CAN_F10B1_FBC6_Pos						(6U)                            
#define CAN_F10B1_FBC6_Msk						(0x1UL << CAN_F10B1_FBC6_Pos)   
#define CAN_F10B1_FBC6							CAN_F10B1_FBC6_Msk              /*!< Filter 10 register 1 bit 6 */
#define CAN_F10B1_FBC7_Pos						(7U)                            
#define CAN_F10B1_FBC7_Msk						(0x1UL << CAN_F10B1_FBC7_Pos)   
#define CAN_F10B1_FBC7							CAN_F10B1_FBC7_Msk              /*!< Filter 10 register 1 bit 7 */
#define CAN_F10B1_FBC8_Pos						(8U)                            
#define CAN_F10B1_FBC8_Msk						(0x1UL << CAN_F10B1_FBC8_Pos)   
#define CAN_F10B1_FBC8							CAN_F10B1_FBC8_Msk              /*!< Filter 10 register 1 bit 8 */
#define CAN_F10B1_FBC9_Pos						(9U)                            
#define CAN_F10B1_FBC9_Msk						(0x1UL << CAN_F10B1_FBC9_Pos)   
#define CAN_F10B1_FBC9							CAN_F10B1_FBC9_Msk              /*!< Filter 10 register 1 bit 9 */
#define CAN_F10B1_FBC10_Pos						(10U)                           
#define CAN_F10B1_FBC10_Msk						(0x1UL << CAN_F10B1_FBC10_Pos)  
#define CAN_F10B1_FBC10							CAN_F10B1_FBC10_Msk             /*!< Filter 10 register 1 bit 10 */
#define CAN_F10B1_FBC11_Pos						(11U)                           
#define CAN_F10B1_FBC11_Msk						(0x1UL << CAN_F10B1_FBC11_Pos)  
#define CAN_F10B1_FBC11							CAN_F10B1_FBC11_Msk             /*!< Filter 10 register 1 bit 11 */
#define CAN_F10B1_FBC12_Pos						(12U)                           
#define CAN_F10B1_FBC12_Msk						(0x1UL << CAN_F10B1_FBC12_Pos)  
#define CAN_F10B1_FBC12							CAN_F10B1_FBC12_Msk             /*!< Filter 10 register 1 bit 12 */
#define CAN_F10B1_FBC13_Pos						(13U)                           
#define CAN_F10B1_FBC13_Msk						(0x1UL << CAN_F10B1_FBC13_Pos)  
#define CAN_F10B1_FBC13							CAN_F10B1_FBC13_Msk             /*!< Filter 10 register 1 bit 13 */
#define CAN_F10B1_FBC14_Pos						(14U)                           
#define CAN_F10B1_FBC14_Msk						(0x1UL << CAN_F10B1_FBC14_Pos)  
#define CAN_F10B1_FBC14							CAN_F10B1_FBC14_Msk             /*!< Filter 10 register 1 bit 14 */
#define CAN_F10B1_FBC15_Pos						(15U)                           
#define CAN_F10B1_FBC15_Msk						(0x1UL << CAN_F10B1_FBC15_Pos)  
#define CAN_F10B1_FBC15							CAN_F10B1_FBC15_Msk             /*!< Filter 10 register 1 bit 15 */
#define CAN_F10B1_FBC16_Pos						(16U)                           
#define CAN_F10B1_FBC16_Msk						(0x1UL << CAN_F10B1_FBC16_Pos)  
#define CAN_F10B1_FBC16							CAN_F10B1_FBC16_Msk             /*!< Filter 10 register 1 bit 16 */
#define CAN_F10B1_FBC17_Pos						(17U)                           
#define CAN_F10B1_FBC17_Msk						(0x1UL << CAN_F10B1_FBC17_Pos)  
#define CAN_F10B1_FBC17							CAN_F10B1_FBC17_Msk             /*!< Filter 10 register 1 bit 17 */
#define CAN_F10B1_FBC18_Pos						(18U)                           
#define CAN_F10B1_FBC18_Msk						(0x1UL << CAN_F10B1_FBC18_Pos)  
#define CAN_F10B1_FBC18							CAN_F10B1_FBC18_Msk             /*!< Filter 10 register 1 bit 18 */
#define CAN_F10B1_FBC19_Pos						(19U)                           
#define CAN_F10B1_FBC19_Msk						(0x1UL << CAN_F10B1_FBC19_Pos)  
#define CAN_F10B1_FBC19							CAN_F10B1_FBC19_Msk             /*!< Filter 10 register 1 bit 19 */
#define CAN_F10B1_FBC20_Pos						(20U)                           
#define CAN_F10B1_FBC20_Msk						(0x1UL << CAN_F10B1_FBC20_Pos)  
#define CAN_F10B1_FBC20							CAN_F10B1_FBC20_Msk             /*!< Filter 10 register 1 bit 20 */
#define CAN_F10B1_FBC21_Pos						(21U)                           
#define CAN_F10B1_FBC21_Msk						(0x1UL << CAN_F10B1_FBC21_Pos)  
#define CAN_F10B1_FBC21							CAN_F10B1_FBC21_Msk             /*!< Filter 10 register 1 bit 21 */
#define CAN_F10B1_FBC22_Pos						(22U)                           
#define CAN_F10B1_FBC22_Msk						(0x1UL << CAN_F10B1_FBC22_Pos)  
#define CAN_F10B1_FBC22							CAN_F10B1_FBC22_Msk             /*!< Filter 10 register 1 bit 22 */
#define CAN_F10B1_FBC23_Pos						(23U)                           
#define CAN_F10B1_FBC23_Msk						(0x1UL << CAN_F10B1_FBC23_Pos)  
#define CAN_F10B1_FBC23							CAN_F10B1_FBC23_Msk             /*!< Filter 10 register 1 bit 23 */
#define CAN_F10B1_FBC24_Pos						(24U)                           
#define CAN_F10B1_FBC24_Msk						(0x1UL << CAN_F10B1_FBC24_Pos)  
#define CAN_F10B1_FBC24							CAN_F10B1_FBC24_Msk             /*!< Filter 10 register 1 bit 24 */
#define CAN_F10B1_FBC25_Pos						(25U)                           
#define CAN_F10B1_FBC25_Msk						(0x1UL << CAN_F10B1_FBC25_Pos)  
#define CAN_F10B1_FBC25							CAN_F10B1_FBC25_Msk             /*!< Filter 10 register 1 bit 25 */
#define CAN_F10B1_FBC26_Pos						(26U)                           
#define CAN_F10B1_FBC26_Msk						(0x1UL << CAN_F10B1_FBC26_Pos)  
#define CAN_F10B1_FBC26							CAN_F10B1_FBC26_Msk             /*!< Filter 10 register 1 bit 26 */
#define CAN_F10B1_FBC27_Pos						(27U)                           
#define CAN_F10B1_FBC27_Msk						(0x1UL << CAN_F10B1_FBC27_Pos)  
#define CAN_F10B1_FBC27							CAN_F10B1_FBC27_Msk             /*!< Filter 10 register 1 bit 27 */
#define CAN_F10B1_FBC28_Pos						(28U)                           
#define CAN_F10B1_FBC28_Msk						(0x1UL << CAN_F10B1_FBC28_Pos)  
#define CAN_F10B1_FBC28							CAN_F10B1_FBC28_Msk             /*!< Filter 10 register 1 bit 28 */
#define CAN_F10B1_FBC29_Pos						(29U)                           
#define CAN_F10B1_FBC29_Msk						(0x1UL << CAN_F10B1_FBC29_Pos)  
#define CAN_F10B1_FBC29							CAN_F10B1_FBC29_Msk             /*!< Filter 10 register 1 bit 29 */
#define CAN_F10B1_FBC30_Pos						(30U)                           
#define CAN_F10B1_FBC30_Msk						(0x1UL << CAN_F10B1_FBC30_Pos)  
#define CAN_F10B1_FBC30							CAN_F10B1_FBC30_Msk             /*!< Filter 10 register 1 bit 30 */
#define CAN_F10B1_FBC31_Pos						(31U)                           
#define CAN_F10B1_FBC31_Msk						(0x1UL << CAN_F10B1_FBC31_Pos)  
#define CAN_F10B1_FBC31							CAN_F10B1_FBC31_Msk             /*!< Filter 10 register 1 bit 31 */

/******************  Bit definition for CAN_F11R1 register  *******************/
#define CAN_F11B1_FBC0_Pos						(0U)
#define CAN_F11B1_FBC0_Msk						(0x1UL << CAN_F11B1_FBC0_Pos)
#define CAN_F11B1_FBC0							CAN_F11B1_FBC0_Msk				/*!< Filter 11 register 1 bit 0 */
#define CAN_F11B1_FBC1_Pos						(1U)                            
#define CAN_F11B1_FBC1_Msk						(0x1UL << CAN_F11B1_FBC1_Pos)   
#define CAN_F11B1_FBC1							CAN_F11B1_FBC1_Msk              /*!< Filter 11 register 1 bit 1 */
#define CAN_F11B1_FBC2_Pos						(2U)                            
#define CAN_F11B1_FBC2_Msk						(0x1UL << CAN_F11B1_FBC2_Pos)   
#define CAN_F11B1_FBC2							CAN_F11B1_FBC2_Msk              /*!< Filter 11 register 1 bit 2 */
#define CAN_F11B1_FBC3_Pos						(3U)                            
#define CAN_F11B1_FBC3_Msk						(0x1UL << CAN_F11B1_FBC3_Pos)   
#define CAN_F11B1_FBC3							CAN_F11B1_FBC3_Msk              /*!< Filter 11 register 1 bit 3 */
#define CAN_F11B1_FBC4_Pos						(4U)                            
#define CAN_F11B1_FBC4_Msk						(0x1UL << CAN_F11B1_FBC4_Pos)   
#define CAN_F11B1_FBC4							CAN_F11B1_FBC4_Msk              /*!< Filter 11 register 1 bit 4 */
#define CAN_F11B1_FBC5_Pos						(5U)                            
#define CAN_F11B1_FBC5_Msk						(0x1UL << CAN_F11B1_FBC5_Pos)   
#define CAN_F11B1_FBC5							CAN_F11B1_FBC5_Msk              /*!< Filter 11 register 1 bit 5 */
#define CAN_F11B1_FBC6_Pos						(6U)                            
#define CAN_F11B1_FBC6_Msk						(0x1UL << CAN_F11B1_FBC6_Pos)   
#define CAN_F11B1_FBC6							CAN_F11B1_FBC6_Msk              /*!< Filter 11 register 1 bit 6 */
#define CAN_F11B1_FBC7_Pos						(7U)                            
#define CAN_F11B1_FBC7_Msk						(0x1UL << CAN_F11B1_FBC7_Pos)   
#define CAN_F11B1_FBC7							CAN_F11B1_FBC7_Msk              /*!< Filter 11 register 1 bit 7 */
#define CAN_F11B1_FBC8_Pos						(8U)                            
#define CAN_F11B1_FBC8_Msk						(0x1UL << CAN_F11B1_FBC8_Pos)   
#define CAN_F11B1_FBC8							CAN_F11B1_FBC8_Msk              /*!< Filter 11 register 1 bit 8 */
#define CAN_F11B1_FBC9_Pos						(9U)                            
#define CAN_F11B1_FBC9_Msk						(0x1UL << CAN_F11B1_FBC9_Pos)   
#define CAN_F11B1_FBC9							CAN_F11B1_FBC9_Msk              /*!< Filter 11 register 1 bit 9 */
#define CAN_F11B1_FBC10_Pos						(10U)                           
#define CAN_F11B1_FBC10_Msk						(0x1UL << CAN_F11B1_FBC10_Pos)  
#define CAN_F11B1_FBC10							CAN_F11B1_FBC10_Msk             /*!< Filter 11 register 1 bit 10 */
#define CAN_F11B1_FBC11_Pos						(11U)                           
#define CAN_F11B1_FBC11_Msk						(0x1UL << CAN_F11B1_FBC11_Pos)  
#define CAN_F11B1_FBC11							CAN_F11B1_FBC11_Msk             /*!< Filter 11 register 1 bit 11 */
#define CAN_F11B1_FBC12_Pos						(12U)                           
#define CAN_F11B1_FBC12_Msk						(0x1UL << CAN_F11B1_FBC12_Pos)  
#define CAN_F11B1_FBC12							CAN_F11B1_FBC12_Msk             /*!< Filter 11 register 1 bit 12 */
#define CAN_F11B1_FBC13_Pos						(13U)                           
#define CAN_F11B1_FBC13_Msk						(0x1UL << CAN_F11B1_FBC13_Pos)  
#define CAN_F11B1_FBC13							CAN_F11B1_FBC13_Msk             /*!< Filter 11 register 1 bit 13 */
#define CAN_F11B1_FBC14_Pos						(14U)                           
#define CAN_F11B1_FBC14_Msk						(0x1UL << CAN_F11B1_FBC14_Pos)  
#define CAN_F11B1_FBC14							CAN_F11B1_FBC14_Msk             /*!< Filter 11 register 1 bit 14 */
#define CAN_F11B1_FBC15_Pos						(15U)                           
#define CAN_F11B1_FBC15_Msk						(0x1UL << CAN_F11B1_FBC15_Pos)  
#define CAN_F11B1_FBC15							CAN_F11B1_FBC15_Msk             /*!< Filter 11 register 1 bit 15 */
#define CAN_F11B1_FBC16_Pos						(16U)                           
#define CAN_F11B1_FBC16_Msk						(0x1UL << CAN_F11B1_FBC16_Pos)  
#define CAN_F11B1_FBC16							CAN_F11B1_FBC16_Msk             /*!< Filter 11 register 1 bit 16 */
#define CAN_F11B1_FBC17_Pos						(17U)                           
#define CAN_F11B1_FBC17_Msk						(0x1UL << CAN_F11B1_FBC17_Pos)  
#define CAN_F11B1_FBC17							CAN_F11B1_FBC17_Msk             /*!< Filter 11 register 1 bit 17 */
#define CAN_F11B1_FBC18_Pos						(18U)                           
#define CAN_F11B1_FBC18_Msk						(0x1UL << CAN_F11B1_FBC18_Pos)  
#define CAN_F11B1_FBC18							CAN_F11B1_FBC18_Msk             /*!< Filter 11 register 1 bit 18 */
#define CAN_F11B1_FBC19_Pos						(19U)                           
#define CAN_F11B1_FBC19_Msk						(0x1UL << CAN_F11B1_FBC19_Pos)  
#define CAN_F11B1_FBC19							CAN_F11B1_FBC19_Msk             /*!< Filter 11 register 1 bit 19 */
#define CAN_F11B1_FBC20_Pos						(20U)                           
#define CAN_F11B1_FBC20_Msk						(0x1UL << CAN_F11B1_FBC20_Pos)  
#define CAN_F11B1_FBC20							CAN_F11B1_FBC20_Msk             /*!< Filter 11 register 1 bit 20 */
#define CAN_F11B1_FBC21_Pos						(21U)                           
#define CAN_F11B1_FBC21_Msk						(0x1UL << CAN_F11B1_FBC21_Pos)  
#define CAN_F11B1_FBC21							CAN_F11B1_FBC21_Msk             /*!< Filter 11 register 1 bit 21 */
#define CAN_F11B1_FBC22_Pos						(22U)                          
#define CAN_F11B1_FBC22_Msk						(0x1UL << CAN_F11B1_FBC22_Pos)  
#define CAN_F11B1_FBC22							CAN_F11B1_FBC22_Msk             /*!< Filter 11 register 1 bit 22 */
#define CAN_F11B1_FBC23_Pos						(23U)                           
#define CAN_F11B1_FBC23_Msk						(0x1UL << CAN_F11B1_FBC23_Pos)  
#define CAN_F11B1_FBC23							CAN_F11B1_FBC23_Msk             /*!< Filter 11 register 1 bit 23 */
#define CAN_F11B1_FBC24_Pos						(24U)                           
#define CAN_F11B1_FBC24_Msk						(0x1UL << CAN_F11B1_FBC24_Pos)  
#define CAN_F11B1_FBC24							CAN_F11B1_FBC24_Msk             /*!< Filter 11 register 1 bit 24 */
#define CAN_F11B1_FBC25_Pos						(25U)                           
#define CAN_F11B1_FBC25_Msk						(0x1UL << CAN_F11B1_FBC25_Pos)  
#define CAN_F11B1_FBC25							CAN_F11B1_FBC25_Msk             /*!< Filter 11 register 1 bit 25 */
#define CAN_F11B1_FBC26_Pos						(26U)                           
#define CAN_F11B1_FBC26_Msk						(0x1UL << CAN_F11B1_FBC26_Pos)  
#define CAN_F11B1_FBC26							CAN_F11B1_FBC26_Msk             /*!< Filter 11 register 1 bit 26 */
#define CAN_F11B1_FBC27_Pos						(27U)                           
#define CAN_F11B1_FBC27_Msk						(0x1UL << CAN_F11B1_FBC27_Pos)  
#define CAN_F11B1_FBC27							CAN_F11B1_FBC27_Msk             /*!< Filter 11 register 1 bit 27 */
#define CAN_F11B1_FBC28_Pos						(28U)                           
#define CAN_F11B1_FBC28_Msk						(0x1UL << CAN_F11B1_FBC28_Pos)  
#define CAN_F11B1_FBC28							CAN_F11B1_FBC28_Msk             /*!< Filter 11 register 1 bit 28 */
#define CAN_F11B1_FBC29_Pos						(29U)                           
#define CAN_F11B1_FBC29_Msk						(0x1UL << CAN_F11B1_FBC29_Pos)  
#define CAN_F11B1_FBC29							CAN_F11B1_FBC29_Msk             /*!< Filter 11 register 1 bit 29 */
#define CAN_F11B1_FBC30_Pos						(30U)                           
#define CAN_F11B1_FBC30_Msk						(0x1UL << CAN_F11B1_FBC30_Pos)  
#define CAN_F11B1_FBC30							CAN_F11B1_FBC30_Msk             /*!< Filter 11 register 1 bit 30 */
#define CAN_F11B1_FBC31_Pos						(31U)                           
#define CAN_F11B1_FBC31_Msk						(0x1UL << CAN_F11B1_FBC31_Pos)  
#define CAN_F11B1_FBC31							CAN_F11B1_FBC31_Msk             /*!< Filter 11 register 1 bit 31 */

/******************  Bit definition for CAN_F12R1 register  *******************/
#define CAN_F12B1_FBC0_Pos						(0U)
#define CAN_F12B1_FBC0_Msk						(0x1UL << CAN_F12B1_FBC0_Pos)
#define CAN_F12B1_FBC0							CAN_F12B1_FBC0_Msk				/*!< Filter 12 register 1 bit 0 */
#define CAN_F12B1_FBC1_Pos						(1U)                            
#define CAN_F12B1_FBC1_Msk						(0x1UL << CAN_F12B1_FBC1_Pos)   
#define CAN_F12B1_FBC1							CAN_F12B1_FBC1_Msk              /*!< Filter 12 register 1 bit 1 */
#define CAN_F12B1_FBC2_Pos						(2U)                            
#define CAN_F12B1_FBC2_Msk						(0x1UL << CAN_F12B1_FBC2_Pos)   
#define CAN_F12B1_FBC2							CAN_F12B1_FBC2_Msk              /*!< Filter 12 register 1 bit 2 */
#define CAN_F12B1_FBC3_Pos						(3U)                            
#define CAN_F12B1_FBC3_Msk						(0x1UL << CAN_F12B1_FBC3_Pos)   
#define CAN_F12B1_FBC3							CAN_F12B1_FBC3_Msk              /*!< Filter 12 register 1 bit 3 */
#define CAN_F12B1_FBC4_Pos						(4U)                            
#define CAN_F12B1_FBC4_Msk						(0x1UL << CAN_F12B1_FBC4_Pos)   
#define CAN_F12B1_FBC4							CAN_F12B1_FBC4_Msk              /*!< Filter 12 register 1 bit 4 */
#define CAN_F12B1_FBC5_Pos						(5U)                            
#define CAN_F12B1_FBC5_Msk						(0x1UL << CAN_F12B1_FBC5_Pos)   
#define CAN_F12B1_FBC5							CAN_F12B1_FBC5_Msk              /*!< Filter 12 register 1 bit 5 */
#define CAN_F12B1_FBC6_Pos						(6U)                            
#define CAN_F12B1_FBC6_Msk						(0x1UL << CAN_F12B1_FBC6_Pos)   
#define CAN_F12B1_FBC6							CAN_F12B1_FBC6_Msk              /*!< Filter 12 register 1 bit 6 */
#define CAN_F12B1_FBC7_Pos						(7U)                            
#define CAN_F12B1_FBC7_Msk						(0x1UL << CAN_F12B1_FBC7_Pos)   
#define CAN_F12B1_FBC7							CAN_F12B1_FBC7_Msk              /*!< Filter 12 register 1 bit 7 */
#define CAN_F12B1_FBC8_Pos						(8U)                            
#define CAN_F12B1_FBC8_Msk						(0x1UL << CAN_F12B1_FBC8_Pos)   
#define CAN_F12B1_FBC8							CAN_F12B1_FBC8_Msk              /*!< Filter 12 register 1 bit 8 */
#define CAN_F12B1_FBC9_Pos						(9U)                            
#define CAN_F12B1_FBC9_Msk						(0x1UL << CAN_F12B1_FBC9_Pos)   
#define CAN_F12B1_FBC9							CAN_F12B1_FBC9_Msk              /*!< Filter 12 register 1 bit 9 */
#define CAN_F12B1_FBC10_Pos						(10U)                           
#define CAN_F12B1_FBC10_Msk						(0x1UL << CAN_F12B1_FBC10_Pos)  
#define CAN_F12B1_FBC10							CAN_F12B1_FBC10_Msk             /*!< Filter 12 register 1 bit 10 */
#define CAN_F12B1_FBC11_Pos						(11U)                           
#define CAN_F12B1_FBC11_Msk						(0x1UL << CAN_F12B1_FBC11_Pos)  
#define CAN_F12B1_FBC11							CAN_F12B1_FBC11_Msk             /*!< Filter 12 register 1 bit 11 */
#define CAN_F12B1_FBC12_Pos						(12U)                           
#define CAN_F12B1_FBC12_Msk						(0x1UL << CAN_F12B1_FBC12_Pos)  
#define CAN_F12B1_FBC12							CAN_F12B1_FBC12_Msk             /*!< Filter 12 register 1 bit 12 */
#define CAN_F12B1_FBC13_Pos						(13U)                           
#define CAN_F12B1_FBC13_Msk						(0x1UL << CAN_F12B1_FBC13_Pos)  
#define CAN_F12B1_FBC13							CAN_F12B1_FBC13_Msk             /*!< Filter 12 register 1 bit 13 */
#define CAN_F12B1_FBC14_Pos						(14U)                           
#define CAN_F12B1_FBC14_Msk						(0x1UL << CAN_F12B1_FBC14_Pos)  
#define CAN_F12B1_FBC14							CAN_F12B1_FBC14_Msk             /*!< Filter 12 register 1 bit 14 */
#define CAN_F12B1_FBC15_Pos						(15U)                           
#define CAN_F12B1_FBC15_Msk						(0x1UL << CAN_F12B1_FBC15_Pos)  
#define CAN_F12B1_FBC15							CAN_F12B1_FBC15_Msk             /*!< Filter 12 register 1 bit 15 */
#define CAN_F12B1_FBC16_Pos						(16U)                           
#define CAN_F12B1_FBC16_Msk						(0x1UL << CAN_F12B1_FBC16_Pos)  
#define CAN_F12B1_FBC16							CAN_F12B1_FBC16_Msk             /*!< Filter 12 register 1 bit 16 */
#define CAN_F12B1_FBC17_Pos						(17U)                           
#define CAN_F12B1_FBC17_Msk						(0x1UL << CAN_F12B1_FBC17_Pos)  
#define CAN_F12B1_FBC17							CAN_F12B1_FBC17_Msk             /*!< Filter 12 register 1 bit 17 */
#define CAN_F12B1_FBC18_Pos						(18U)                           
#define CAN_F12B1_FBC18_Msk						(0x1UL << CAN_F12B1_FBC18_Pos)  
#define CAN_F12B1_FBC18							CAN_F12B1_FBC18_Msk             /*!< Filter 12 register 1 bit 18 */
#define CAN_F12B1_FBC19_Pos						(19U)                           
#define CAN_F12B1_FBC19_Msk						(0x1UL << CAN_F12B1_FBC19_Pos)  
#define CAN_F12B1_FBC19							CAN_F12B1_FBC19_Msk             /*!< Filter 12 register 1 bit 19 */
#define CAN_F12B1_FBC20_Pos						(20U)                           
#define CAN_F12B1_FBC20_Msk						(0x1UL << CAN_F12B1_FBC20_Pos)  
#define CAN_F12B1_FBC20							CAN_F12B1_FBC20_Msk             /*!< Filter 12 register 1 bit 20 */
#define CAN_F12B1_FBC21_Pos						(21U)                           
#define CAN_F12B1_FBC21_Msk						(0x1UL << CAN_F12B1_FBC21_Pos)  
#define CAN_F12B1_FBC21							CAN_F12B1_FBC21_Msk             /*!< Filter 12 register 1 bit 21 */
#define CAN_F12B1_FBC22_Pos						(22U)                           
#define CAN_F12B1_FBC22_Msk						(0x1UL << CAN_F12B1_FBC22_Pos)  
#define CAN_F12B1_FBC22							CAN_F12B1_FBC22_Msk             /*!< Filter 12 register 1 bit 22 */
#define CAN_F12B1_FBC23_Pos						(23U)                           
#define CAN_F12B1_FBC23_Msk						(0x1UL << CAN_F12B1_FBC23_Pos)  
#define CAN_F12B1_FBC23							CAN_F12B1_FBC23_Msk             /*!< Filter 12 register 1 bit 23 */
#define CAN_F12B1_FBC24_Pos						(24U)                           
#define CAN_F12B1_FBC24_Msk						(0x1UL << CAN_F12B1_FBC24_Pos)  
#define CAN_F12B1_FBC24							CAN_F12B1_FBC24_Msk             /*!< Filter 12 register 1 bit 24 */
#define CAN_F12B1_FBC25_Pos						(25U)                           
#define CAN_F12B1_FBC25_Msk						(0x1UL << CAN_F12B1_FBC25_Pos)  
#define CAN_F12B1_FBC25							CAN_F12B1_FBC25_Msk             /*!< Filter 12 register 1 bit 25 */
#define CAN_F12B1_FBC26_Pos						(26U)                           
#define CAN_F12B1_FBC26_Msk						(0x1UL << CAN_F12B1_FBC26_Pos)  
#define CAN_F12B1_FBC26							CAN_F12B1_FBC26_Msk             /*!< Filter 12 register 1 bit 26 */
#define CAN_F12B1_FBC27_Pos						(27U)                           
#define CAN_F12B1_FBC27_Msk						(0x1UL << CAN_F12B1_FBC27_Pos)  
#define CAN_F12B1_FBC27							CAN_F12B1_FBC27_Msk             /*!< Filter 12 register 1 bit 27 */
#define CAN_F12B1_FBC28_Pos						(28U)                           
#define CAN_F12B1_FBC28_Msk						(0x1UL << CAN_F12B1_FBC28_Pos)  
#define CAN_F12B1_FBC28							CAN_F12B1_FBC28_Msk             /*!< Filter 12 register 1 bit 28 */
#define CAN_F12B1_FBC29_Pos						(29U)                           
#define CAN_F12B1_FBC29_Msk						(0x1UL << CAN_F12B1_FBC29_Pos)  
#define CAN_F12B1_FBC29							CAN_F12B1_FBC29_Msk             /*!< Filter 12 register 1 bit 29 */
#define CAN_F12B1_FBC30_Pos						(30U)                           
#define CAN_F12B1_FBC30_Msk						(0x1UL << CAN_F12B1_FBC30_Pos)  
#define CAN_F12B1_FBC30							CAN_F12B1_FBC30_Msk             /*!< Filter 12 register 1 bit 30 */
#define CAN_F12B1_FBC31_Pos						(31U)                           
#define CAN_F12B1_FBC31_Msk						(0x1UL << CAN_F12B1_FBC31_Pos)  
#define CAN_F12B1_FBC31							CAN_F12B1_FBC31_Msk             /*!< Filter 12 register 1 bit 31 */

/******************  Bit definition for CAN_F13R1 register  *******************/
#define CAN_F13B1_FBC0_Pos						(0U)
#define CAN_F13B1_FBC0_Msk						(0x1UL << CAN_F13B1_FBC0_Pos)
#define CAN_F13B1_FBC0							CAN_F13B1_FBC0_Msk				/*!< Filter 13 register 1 bit 0 */
#define CAN_F13B1_FBC1_Pos						(1U)                            
#define CAN_F13B1_FBC1_Msk						(0x1UL << CAN_F13B1_FBC1_Pos)   
#define CAN_F13B1_FBC1							CAN_F13B1_FBC1_Msk              /*!< Filter 13 register 1 bit 1 */
#define CAN_F13B1_FBC2_Pos						(2U)                            
#define CAN_F13B1_FBC2_Msk						(0x1UL << CAN_F13B1_FBC2_Pos)   
#define CAN_F13B1_FBC2							CAN_F13B1_FBC2_Msk              /*!< Filter 13 register 1 bit 2 */
#define CAN_F13B1_FBC3_Pos						(3U)                            
#define CAN_F13B1_FBC3_Msk						(0x1UL << CAN_F13B1_FBC3_Pos)   
#define CAN_F13B1_FBC3							CAN_F13B1_FBC3_Msk              /*!< Filter 13 register 1 bit 3 */
#define CAN_F13B1_FBC4_Pos						(4U)                            
#define CAN_F13B1_FBC4_Msk						(0x1UL << CAN_F13B1_FBC4_Pos)   
#define CAN_F13B1_FBC4							CAN_F13B1_FBC4_Msk              /*!< Filter 13 register 1 bit 4 */
#define CAN_F13B1_FBC5_Pos						(5U)                            
#define CAN_F13B1_FBC5_Msk						(0x1UL << CAN_F13B1_FBC5_Pos)   
#define CAN_F13B1_FBC5							CAN_F13B1_FBC5_Msk              /*!< Filter 13 register 1 bit 5 */
#define CAN_F13B1_FBC6_Pos						(6U)                            
#define CAN_F13B1_FBC6_Msk						(0x1UL << CAN_F13B1_FBC6_Pos)   
#define CAN_F13B1_FBC6							CAN_F13B1_FBC6_Msk              /*!< Filter 13 register 1 bit 6 */
#define CAN_F13B1_FBC7_Pos						(7U)                            
#define CAN_F13B1_FBC7_Msk						(0x1UL << CAN_F13B1_FBC7_Pos)   
#define CAN_F13B1_FBC7							CAN_F13B1_FBC7_Msk              /*!< Filter 13 register 1 bit 7 */
#define CAN_F13B1_FBC8_Pos						(8U)                            
#define CAN_F13B1_FBC8_Msk						(0x1UL << CAN_F13B1_FBC8_Pos)   
#define CAN_F13B1_FBC8							CAN_F13B1_FBC8_Msk              /*!< Filter 13 register 1 bit 8 */
#define CAN_F13B1_FBC9_Pos						(9U)                            
#define CAN_F13B1_FBC9_Msk						(0x1UL << CAN_F13B1_FBC9_Pos)   
#define CAN_F13B1_FBC9							CAN_F13B1_FBC9_Msk              /*!< Filter 13 register 1 bit 9 */
#define CAN_F13B1_FBC10_Pos						(10U)                           
#define CAN_F13B1_FBC10_Msk						(0x1UL << CAN_F13B1_FBC10_Pos)  
#define CAN_F13B1_FBC10							CAN_F13B1_FBC10_Msk             /*!< Filter 13 register 1 bit 10 */
#define CAN_F13B1_FBC11_Pos						(11U)                           
#define CAN_F13B1_FBC11_Msk						(0x1UL << CAN_F13B1_FBC11_Pos)  
#define CAN_F13B1_FBC11							CAN_F13B1_FBC11_Msk             /*!< Filter 13 register 1 bit 11 */
#define CAN_F13B1_FBC12_Pos						(12U)                           
#define CAN_F13B1_FBC12_Msk						(0x1UL << CAN_F13B1_FBC12_Pos)  
#define CAN_F13B1_FBC12							CAN_F13B1_FBC12_Msk             /*!< Filter 13 register 1 bit 12 */
#define CAN_F13B1_FBC13_Pos						(13U)                           
#define CAN_F13B1_FBC13_Msk						(0x1UL << CAN_F13B1_FBC13_Pos)  
#define CAN_F13B1_FBC13							CAN_F13B1_FBC13_Msk             /*!< Filter 13 register 1 bit 13 */
#define CAN_F13B1_FBC14_Pos						(14U)                           
#define CAN_F13B1_FBC14_Msk						(0x1UL << CAN_F13B1_FBC14_Pos)  
#define CAN_F13B1_FBC14							CAN_F13B1_FBC14_Msk             /*!< Filter 13 register 1 bit 14 */
#define CAN_F13B1_FBC15_Pos						(15U)                           
#define CAN_F13B1_FBC15_Msk						(0x1UL << CAN_F13B1_FBC15_Pos)  
#define CAN_F13B1_FBC15							CAN_F13B1_FBC15_Msk             /*!< Filter 13 register 1 bit 15 */
#define CAN_F13B1_FBC16_Pos						(16U)                           
#define CAN_F13B1_FBC16_Msk						(0x1UL << CAN_F13B1_FBC16_Pos)  
#define CAN_F13B1_FBC16							CAN_F13B1_FBC16_Msk             /*!< Filter 13 register 1 bit 16 */
#define CAN_F13B1_FBC17_Pos						(17U)                           
#define CAN_F13B1_FBC17_Msk						(0x1UL << CAN_F13B1_FBC17_Pos)  
#define CAN_F13B1_FBC17							CAN_F13B1_FBC17_Msk             /*!< Filter 13 register 1 bit 17 */
#define CAN_F13B1_FBC18_Pos						(18U)                           
#define CAN_F13B1_FBC18_Msk						(0x1UL << CAN_F13B1_FBC18_Pos)  
#define CAN_F13B1_FBC18							CAN_F13B1_FBC18_Msk             /*!< Filter 13 register 1 bit 18 */
#define CAN_F13B1_FBC19_Pos						(19U)                           
#define CAN_F13B1_FBC19_Msk						(0x1UL << CAN_F13B1_FBC19_Pos)  
#define CAN_F13B1_FBC19							CAN_F13B1_FBC19_Msk             /*!< Filter 13 register 1 bit 19 */
#define CAN_F13B1_FBC20_Pos						(20U)                           
#define CAN_F13B1_FBC20_Msk						(0x1UL << CAN_F13B1_FBC20_Pos)  
#define CAN_F13B1_FBC20							CAN_F13B1_FBC20_Msk             /*!< Filter 13 register 1 bit 20 */
#define CAN_F13B1_FBC21_Pos						(21U)                           
#define CAN_F13B1_FBC21_Msk						(0x1UL << CAN_F13B1_FBC21_Pos)  
#define CAN_F13B1_FBC21							CAN_F13B1_FBC21_Msk             /*!< Filter 13 register 1 bit 21 */
#define CAN_F13B1_FBC22_Pos						(22U)                           
#define CAN_F13B1_FBC22_Msk						(0x1UL << CAN_F13B1_FBC22_Pos)  
#define CAN_F13B1_FBC22							CAN_F13B1_FBC22_Msk             /*!< Filter 13 register 1 bit 22 */
#define CAN_F13B1_FBC23_Pos						(23U)                           
#define CAN_F13B1_FBC23_Msk						(0x1UL << CAN_F13B1_FBC23_Pos)  
#define CAN_F13B1_FBC23							CAN_F13B1_FBC23_Msk             /*!< Filter 13 register 1 bit 23 */
#define CAN_F13B1_FBC24_Pos						(24U)                           
#define CAN_F13B1_FBC24_Msk						(0x1UL << CAN_F13B1_FBC24_Pos)  
#define CAN_F13B1_FBC24							CAN_F13B1_FBC24_Msk             /*!< Filter 13 register 1 bit 24 */
#define CAN_F13B1_FBC25_Pos						(25U)                           
#define CAN_F13B1_FBC25_Msk						(0x1UL << CAN_F13B1_FBC25_Pos)  
#define CAN_F13B1_FBC25							CAN_F13B1_FBC25_Msk             /*!< Filter 13 register 1 bit 25 */
#define CAN_F13B1_FBC26_Pos						(26U)                           
#define CAN_F13B1_FBC26_Msk						(0x1UL << CAN_F13B1_FBC26_Pos)  
#define CAN_F13B1_FBC26							CAN_F13B1_FBC26_Msk             /*!< Filter 13 register 1 bit 26 */
#define CAN_F13B1_FBC27_Pos						(27U)                           
#define CAN_F13B1_FBC27_Msk						(0x1UL << CAN_F13B1_FBC27_Pos)  
#define CAN_F13B1_FBC27							CAN_F13B1_FBC27_Msk             /*!< Filter 13 register 1 bit 27 */
#define CAN_F13B1_FBC28_Pos						(28U)                           
#define CAN_F13B1_FBC28_Msk						(0x1UL << CAN_F13B1_FBC28_Pos)  
#define CAN_F13B1_FBC28							CAN_F13B1_FBC28_Msk             /*!< Filter 13 register 1 bit 28 */
#define CAN_F13B1_FBC29_Pos						(29U)                           
#define CAN_F13B1_FBC29_Msk						(0x1UL << CAN_F13B1_FBC29_Pos)  
#define CAN_F13B1_FBC29							CAN_F13B1_FBC29_Msk             /*!< Filter 13 register 1 bit 29 */
#define CAN_F13B1_FBC30_Pos						(30U)                           
#define CAN_F13B1_FBC30_Msk						(0x1UL << CAN_F13B1_FBC30_Pos)  
#define CAN_F13B1_FBC30							CAN_F13B1_FBC30_Msk             /*!< Filter 13 register 1 bit 30 */
#define CAN_F13B1_FBC31_Pos						(31U)                           
#define CAN_F13B1_FBC31_Msk						(0x1UL << CAN_F13B1_FBC31_Pos)  
#define CAN_F13B1_FBC31							CAN_F13B1_FBC31_Msk             /*!< Filter 13 register 1 bit 31 */

/*******************  Bit definition for CAN_F0R2 register  *******************/
#define CAN_F0B2_FBC0_Pos						(0U)
#define CAN_F0B2_FBC0_Msk						(0x1UL << CAN_F0B2_FBC0_Pos)
#define CAN_F0B2_FBC0							CAN_F0B2_FBC0_Msk				/*!< Filter 0 register 2 bit 0 */
#define CAN_F0B2_FBC1_Pos						(1U)                            
#define CAN_F0B2_FBC1_Msk						(0x1UL << CAN_F0B2_FBC1_Pos)    
#define CAN_F0B2_FBC1							CAN_F0B2_FBC1_Msk               /*!< Filter 0 register 2 bit 1 */
#define CAN_F0B2_FBC2_Pos						(2U)                            
#define CAN_F0B2_FBC2_Msk						(0x1UL << CAN_F0B2_FBC2_Pos)    
#define CAN_F0B2_FBC2							CAN_F0B2_FBC2_Msk               /*!< Filter 0 register 2 bit 2 */
#define CAN_F0B2_FBC3_Pos						(3U)                            
#define CAN_F0B2_FBC3_Msk						(0x1UL << CAN_F0B2_FBC3_Pos)    
#define CAN_F0B2_FBC3							CAN_F0B2_FBC3_Msk               /*!< Filter 0 register 2 bit 3 */
#define CAN_F0B2_FBC4_Pos						(4U)                            
#define CAN_F0B2_FBC4_Msk						(0x1UL << CAN_F0B2_FBC4_Pos)    
#define CAN_F0B2_FBC4							CAN_F0B2_FBC4_Msk               /*!< Filter 0 register 2 bit 4 */
#define CAN_F0B2_FBC5_Pos						(5U)                            
#define CAN_F0B2_FBC5_Msk						(0x1UL << CAN_F0B2_FBC5_Pos)    
#define CAN_F0B2_FBC5							CAN_F0B2_FBC5_Msk               /*!< Filter 0 register 2 bit 5 */
#define CAN_F0B2_FBC6_Pos						(6U)                            
#define CAN_F0B2_FBC6_Msk						(0x1UL << CAN_F0B2_FBC6_Pos)    
#define CAN_F0B2_FBC6							CAN_F0B2_FBC6_Msk               /*!< Filter 0 register 2 bit 6 */
#define CAN_F0B2_FBC7_Pos						(7U)                            
#define CAN_F0B2_FBC7_Msk						(0x1UL << CAN_F0B2_FBC7_Pos)    
#define CAN_F0B2_FBC7							CAN_F0B2_FBC7_Msk               /*!< Filter 0 register 2 bit 7 */
#define CAN_F0B2_FBC8_Pos						(8U)                            
#define CAN_F0B2_FBC8_Msk						(0x1UL << CAN_F0B2_FBC8_Pos)    
#define CAN_F0B2_FBC8							CAN_F0B2_FBC8_Msk               /*!< Filter 0 register 2 bit 8 */
#define CAN_F0B2_FBC9_Pos						(9U)                            
#define CAN_F0B2_FBC9_Msk						(0x1UL << CAN_F0B2_FBC9_Pos)    
#define CAN_F0B2_FBC9							CAN_F0B2_FBC9_Msk               /*!< Filter 0 register 2 bit 9 */
#define CAN_F0B2_FBC10_Pos						(10U)                           
#define CAN_F0B2_FBC10_Msk						(0x1UL << CAN_F0B2_FBC10_Pos)   
#define CAN_F0B2_FBC10							CAN_F0B2_FBC10_Msk              /*!< Filter 0 register 2 bit 10 */
#define CAN_F0B2_FBC11_Pos						(11U)                           
#define CAN_F0B2_FBC11_Msk						(0x1UL << CAN_F0B2_FBC11_Pos)   
#define CAN_F0B2_FBC11							CAN_F0B2_FBC11_Msk              /*!< Filter 0 register 2 bit 11 */
#define CAN_F0B2_FBC12_Pos						(12U)                           
#define CAN_F0B2_FBC12_Msk						(0x1UL << CAN_F0B2_FBC12_Pos)   
#define CAN_F0B2_FBC12							CAN_F0B2_FBC12_Msk              /*!< Filter 0 register 2 bit 12 */
#define CAN_F0B2_FBC13_Pos						(13U)                           
#define CAN_F0B2_FBC13_Msk						(0x1UL << CAN_F0B2_FBC13_Pos)   
#define CAN_F0B2_FBC13							CAN_F0B2_FBC13_Msk              /*!< Filter 0 register 2 bit 13 */
#define CAN_F0B2_FBC14_Pos						(14U)                           
#define CAN_F0B2_FBC14_Msk						(0x1UL << CAN_F0B2_FBC14_Pos)   
#define CAN_F0B2_FBC14							CAN_F0B2_FBC14_Msk              /*!< Filter 0 register 2 bit 14 */
#define CAN_F0B2_FBC15_Pos						(15U)                           
#define CAN_F0B2_FBC15_Msk						(0x1UL << CAN_F0B2_FBC15_Pos)   
#define CAN_F0B2_FBC15							CAN_F0B2_FBC15_Msk              /*!< Filter 0 register 2 bit 15 */
#define CAN_F0B2_FBC16_Pos						(16U)                           
#define CAN_F0B2_FBC16_Msk						(0x1UL << CAN_F0B2_FBC16_Pos)   
#define CAN_F0B2_FBC16							CAN_F0B2_FBC16_Msk              /*!< Filter 0 register 2 bit 16 */
#define CAN_F0B2_FBC17_Pos						(17U)                           
#define CAN_F0B2_FBC17_Msk						(0x1UL << CAN_F0B2_FBC17_Pos)   
#define CAN_F0B2_FBC17							CAN_F0B2_FBC17_Msk              /*!< Filter 0 register 2 bit 17 */
#define CAN_F0B2_FBC18_Pos						(18U)                           
#define CAN_F0B2_FBC18_Msk						(0x1UL << CAN_F0B2_FBC18_Pos)   
#define CAN_F0B2_FBC18							CAN_F0B2_FBC18_Msk              /*!< Filter 0 register 2 bit 18 */
#define CAN_F0B2_FBC19_Pos						(19U)                           
#define CAN_F0B2_FBC19_Msk						(0x1UL << CAN_F0B2_FBC19_Pos)   
#define CAN_F0B2_FBC19							CAN_F0B2_FBC19_Msk              /*!< Filter 0 register 2 bit 19 */
#define CAN_F0B2_FBC20_Pos						(20U)                           
#define CAN_F0B2_FBC20_Msk						(0x1UL << CAN_F0B2_FBC20_Pos)   
#define CAN_F0B2_FBC20							CAN_F0B2_FBC20_Msk              /*!< Filter 0 register 2 bit 20 */
#define CAN_F0B2_FBC21_Pos						(21U)                           
#define CAN_F0B2_FBC21_Msk						(0x1UL << CAN_F0B2_FBC21_Pos)   
#define CAN_F0B2_FBC21							CAN_F0B2_FBC21_Msk              /*!< Filter 0 register 2 bit 21 */
#define CAN_F0B2_FBC22_Pos						(22U)                           
#define CAN_F0B2_FBC22_Msk						(0x1UL << CAN_F0B2_FBC22_Pos)   
#define CAN_F0B2_FBC22							CAN_F0B2_FBC22_Msk              /*!< Filter 0 register 2 bit 22 */
#define CAN_F0B2_FBC23_Pos						(23U)                           
#define CAN_F0B2_FBC23_Msk						(0x1UL << CAN_F0B2_FBC23_Pos)   
#define CAN_F0B2_FBC23							CAN_F0B2_FBC23_Msk              /*!< Filter 0 register 2 bit 23 */
#define CAN_F0B2_FBC24_Pos						(24U)                           
#define CAN_F0B2_FBC24_Msk						(0x1UL << CAN_F0B2_FBC24_Pos)   
#define CAN_F0B2_FBC24							CAN_F0B2_FBC24_Msk              /*!< Filter 0 register 2 bit 24 */
#define CAN_F0B2_FBC25_Pos						(25U)                           
#define CAN_F0B2_FBC25_Msk						(0x1UL << CAN_F0B2_FBC25_Pos)   
#define CAN_F0B2_FBC25							CAN_F0B2_FBC25_Msk              /*!< Filter 0 register 2 bit 25 */
#define CAN_F0B2_FBC26_Pos						(26U)                           
#define CAN_F0B2_FBC26_Msk						(0x1UL << CAN_F0B2_FBC26_Pos)   
#define CAN_F0B2_FBC26							CAN_F0B2_FBC26_Msk              /*!< Filter 0 register 2 bit 26 */
#define CAN_F0B2_FBC27_Pos						(27U)                           
#define CAN_F0B2_FBC27_Msk						(0x1UL << CAN_F0B2_FBC27_Pos)   
#define CAN_F0B2_FBC27							CAN_F0B2_FBC27_Msk              /*!< Filter 0 register 2 bit 27 */
#define CAN_F0B2_FBC28_Pos						(28U)                           
#define CAN_F0B2_FBC28_Msk						(0x1UL << CAN_F0B2_FBC28_Pos)   
#define CAN_F0B2_FBC28							CAN_F0B2_FBC28_Msk              /*!< Filter 0 register 2 bit 28 */
#define CAN_F0B2_FBC29_Pos						(29U)                           
#define CAN_F0B2_FBC29_Msk						(0x1UL << CAN_F0B2_FBC29_Pos)   
#define CAN_F0B2_FBC29							CAN_F0B2_FBC29_Msk              /*!< Filter 0 register 2 bit 29 */
#define CAN_F0B2_FBC30_Pos						(30U)                           
#define CAN_F0B2_FBC30_Msk						(0x1UL << CAN_F0B2_FBC30_Pos)   
#define CAN_F0B2_FBC30							CAN_F0B2_FBC30_Msk              /*!< Filter 0 register 2 bit 30 */
#define CAN_F0B2_FBC31_Pos						(31U)                           
#define CAN_F0B2_FBC31_Msk						(0x1UL << CAN_F0B2_FBC31_Pos)   
#define CAN_F0B2_FBC31							CAN_F0B2_FBC31_Msk              /*!< Filter 0 register 2 bit 31 */

/*******************  Bit definition for CAN_F1R2 register  *******************/
#define CAN_F1B2_FBC0_Pos						(0U)
#define CAN_F1B2_FBC0_Msk						(0x1UL << CAN_F1B2_FBC0_Pos)
#define CAN_F1B2_FBC0							CAN_F1B2_FBC0_Msk				/*!< Filter 1 register 2 bit 0 */
#define CAN_F1B2_FBC1_Pos						(1U)                            
#define CAN_F1B2_FBC1_Msk						(0x1UL << CAN_F1B2_FBC1_Pos)    
#define CAN_F1B2_FBC1							CAN_F1B2_FBC1_Msk               /*!< Filter 1 register 2 bit 1 */
#define CAN_F1B2_FBC2_Pos						(2U)                            
#define CAN_F1B2_FBC2_Msk						(0x1UL << CAN_F1B2_FBC2_Pos)    
#define CAN_F1B2_FBC2							CAN_F1B2_FBC2_Msk               /*!< Filter 1 register 2 bit 2 */
#define CAN_F1B2_FBC3_Pos						(3U)                            
#define CAN_F1B2_FBC3_Msk						(0x1UL << CAN_F1B2_FBC3_Pos)    
#define CAN_F1B2_FBC3							CAN_F1B2_FBC3_Msk               /*!< Filter 1 register 2 bit 3 */
#define CAN_F1B2_FBC4_Pos						(4U)                            
#define CAN_F1B2_FBC4_Msk						(0x1UL << CAN_F1B2_FBC4_Pos)    
#define CAN_F1B2_FBC4							CAN_F1B2_FBC4_Msk               /*!< Filter 1 register 2 bit 4 */
#define CAN_F1B2_FBC5_Pos						(5U)                            
#define CAN_F1B2_FBC5_Msk						(0x1UL << CAN_F1B2_FBC5_Pos)    
#define CAN_F1B2_FBC5							CAN_F1B2_FBC5_Msk               /*!< Filter 1 register 2 bit 5 */
#define CAN_F1B2_FBC6_Pos						(6U)                            
#define CAN_F1B2_FBC6_Msk						(0x1UL << CAN_F1B2_FBC6_Pos)    
#define CAN_F1B2_FBC6							CAN_F1B2_FBC6_Msk               /*!< Filter 1 register 2 bit 6 */
#define CAN_F1B2_FBC7_Pos						(7U)                            
#define CAN_F1B2_FBC7_Msk						(0x1UL << CAN_F1B2_FBC7_Pos)    
#define CAN_F1B2_FBC7							CAN_F1B2_FBC7_Msk               /*!< Filter 1 register 2 bit 7 */
#define CAN_F1B2_FBC8_Pos						(8U)                            
#define CAN_F1B2_FBC8_Msk						(0x1UL << CAN_F1B2_FBC8_Pos)    
#define CAN_F1B2_FBC8							CAN_F1B2_FBC8_Msk               /*!< Filter 1 register 2 bit 8 */
#define CAN_F1B2_FBC9_Pos						(9U)                            
#define CAN_F1B2_FBC9_Msk						(0x1UL << CAN_F1B2_FBC9_Pos)    
#define CAN_F1B2_FBC9							CAN_F1B2_FBC9_Msk               /*!< Filter 1 register 2 bit 9 */
#define CAN_F1B2_FBC10_Pos						(10U)                           
#define CAN_F1B2_FBC10_Msk						(0x1UL << CAN_F1B2_FBC10_Pos)   
#define CAN_F1B2_FBC10							CAN_F1B2_FBC10_Msk              /*!< Filter 1 register 2 bit 10 */
#define CAN_F1B2_FBC11_Pos						(11U)                           
#define CAN_F1B2_FBC11_Msk						(0x1UL << CAN_F1B2_FBC11_Pos)   
#define CAN_F1B2_FBC11							CAN_F1B2_FBC11_Msk              /*!< Filter 1 register 2 bit 11 */
#define CAN_F1B2_FBC12_Pos						(12U)                           
#define CAN_F1B2_FBC12_Msk						(0x1UL << CAN_F1B2_FBC12_Pos)   
#define CAN_F1B2_FBC12							CAN_F1B2_FBC12_Msk              /*!< Filter 1 register 2 bit 12 */
#define CAN_F1B2_FBC13_Pos						(13U)                           
#define CAN_F1B2_FBC13_Msk						(0x1UL << CAN_F1B2_FBC13_Pos)   
#define CAN_F1B2_FBC13							CAN_F1B2_FBC13_Msk              /*!< Filter 1 register 2 bit 13 */
#define CAN_F1B2_FBC14_Pos						(14U)                           
#define CAN_F1B2_FBC14_Msk						(0x1UL << CAN_F1B2_FBC14_Pos)   
#define CAN_F1B2_FBC14							CAN_F1B2_FBC14_Msk              /*!< Filter 1 register 2 bit 14 */
#define CAN_F1B2_FBC15_Pos						(15U)                           
#define CAN_F1B2_FBC15_Msk						(0x1UL << CAN_F1B2_FBC15_Pos)   
#define CAN_F1B2_FBC15							CAN_F1B2_FBC15_Msk              /*!< Filter 1 register 2 bit 15 */
#define CAN_F1B2_FBC16_Pos						(16U)                           
#define CAN_F1B2_FBC16_Msk						(0x1UL << CAN_F1B2_FBC16_Pos)   
#define CAN_F1B2_FBC16							CAN_F1B2_FBC16_Msk              /*!< Filter 1 register 2 bit 16 */
#define CAN_F1B2_FBC17_Pos						(17U)                           
#define CAN_F1B2_FBC17_Msk						(0x1UL << CAN_F1B2_FBC17_Pos)   
#define CAN_F1B2_FBC17							CAN_F1B2_FBC17_Msk              /*!< Filter 1 register 2 bit 17 */
#define CAN_F1B2_FBC18_Pos						(18U)                           
#define CAN_F1B2_FBC18_Msk						(0x1UL << CAN_F1B2_FBC18_Pos)   
#define CAN_F1B2_FBC18							CAN_F1B2_FBC18_Msk              /*!< Filter 1 register 2 bit 18 */
#define CAN_F1B2_FBC19_Pos						(19U)                           
#define CAN_F1B2_FBC19_Msk						(0x1UL << CAN_F1B2_FBC19_Pos)   
#define CAN_F1B2_FBC19							CAN_F1B2_FBC19_Msk              /*!< Filter 1 register 2 bit 19 */
#define CAN_F1B2_FBC20_Pos						(20U)                           
#define CAN_F1B2_FBC20_Msk						(0x1UL << CAN_F1B2_FBC20_Pos)   
#define CAN_F1B2_FBC20							CAN_F1B2_FBC20_Msk              /*!< Filter 1 register 2 bit 20 */
#define CAN_F1B2_FBC21_Pos						(21U)                           
#define CAN_F1B2_FBC21_Msk						(0x1UL << CAN_F1B2_FBC21_Pos)   
#define CAN_F1B2_FBC21							CAN_F1B2_FBC21_Msk              /*!< Filter 1 register 2 bit 21 */
#define CAN_F1B2_FBC22_Pos						(22U)                           
#define CAN_F1B2_FBC22_Msk						(0x1UL << CAN_F1B2_FBC22_Pos)   
#define CAN_F1B2_FBC22							CAN_F1B2_FBC22_Msk              /*!< Filter 1 register 2 bit 22 */
#define CAN_F1B2_FBC23_Pos						(23U)                           
#define CAN_F1B2_FBC23_Msk						(0x1UL << CAN_F1B2_FBC23_Pos)   
#define CAN_F1B2_FBC23							CAN_F1B2_FBC23_Msk              /*!< Filter 1 register 2 bit 23 */
#define CAN_F1B2_FBC24_Pos						(24U)                           
#define CAN_F1B2_FBC24_Msk						(0x1UL << CAN_F1B2_FBC24_Pos)   
#define CAN_F1B2_FBC24							CAN_F1B2_FBC24_Msk              /*!< Filter 1 register 2 bit 24 */
#define CAN_F1B2_FBC25_Pos						(25U)                           
#define CAN_F1B2_FBC25_Msk						(0x1UL << CAN_F1B2_FBC25_Pos)   
#define CAN_F1B2_FBC25							CAN_F1B2_FBC25_Msk              /*!< Filter 1 register 2 bit 25 */
#define CAN_F1B2_FBC26_Pos						(26U)                           
#define CAN_F1B2_FBC26_Msk						(0x1UL << CAN_F1B2_FBC26_Pos)   
#define CAN_F1B2_FBC26							CAN_F1B2_FBC26_Msk              /*!< Filter 1 register 2 bit 26 */
#define CAN_F1B2_FBC27_Pos						(27U)                           
#define CAN_F1B2_FBC27_Msk						(0x1UL << CAN_F1B2_FBC27_Pos)   
#define CAN_F1B2_FBC27							CAN_F1B2_FBC27_Msk              /*!< Filter 1 register 2 bit 27 */
#define CAN_F1B2_FBC28_Pos						(28U)                           
#define CAN_F1B2_FBC28_Msk						(0x1UL << CAN_F1B2_FBC28_Pos)   
#define CAN_F1B2_FBC28							CAN_F1B2_FBC28_Msk              /*!< Filter 1 register 2 bit 28 */
#define CAN_F1B2_FBC29_Pos						(29U)                           
#define CAN_F1B2_FBC29_Msk						(0x1UL << CAN_F1B2_FBC29_Pos)   
#define CAN_F1B2_FBC29							CAN_F1B2_FBC29_Msk              /*!< Filter 1 register 2 bit 29 */
#define CAN_F1B2_FBC30_Pos						(30U)                           
#define CAN_F1B2_FBC30_Msk						(0x1UL << CAN_F1B2_FBC30_Pos)   
#define CAN_F1B2_FBC30							CAN_F1B2_FBC30_Msk              /*!< Filter 1 register 2 bit 30 */
#define CAN_F1B2_FBC31_Pos						(31U)                           
#define CAN_F1B2_FBC31_Msk						(0x1UL << CAN_F1B2_FBC31_Pos)   
#define CAN_F1B2_FBC31							CAN_F1B2_FBC31_Msk              /*!< Filter 1 register 2 bit 31 */

/*******************  Bit definition for CAN_F2R2 register  *******************/
#define CAN_F2B2_FBC0_Pos						(0U)
#define CAN_F2B2_FBC0_Msk						(0x1UL << CAN_F2B2_FBC0_Pos)
#define CAN_F2B2_FBC0							CAN_F2B2_FBC0_Msk				/*!< Filter 2 register 2 bit 0 */
#define CAN_F2B2_FBC1_Pos						(1U)                            
#define CAN_F2B2_FBC1_Msk						(0x1UL << CAN_F2B2_FBC1_Pos)    
#define CAN_F2B2_FBC1							CAN_F2B2_FBC1_Msk               /*!< Filter 2 register 2 bit 1 */
#define CAN_F2B2_FBC2_Pos						(2U)                            
#define CAN_F2B2_FBC2_Msk						(0x1UL << CAN_F2B2_FBC2_Pos)    
#define CAN_F2B2_FBC2							CAN_F2B2_FBC2_Msk               /*!< Filter 2 register 2 bit 2 */
#define CAN_F2B2_FBC3_Pos						(3U)                            
#define CAN_F2B2_FBC3_Msk						(0x1UL << CAN_F2B2_FBC3_Pos)    
#define CAN_F2B2_FBC3							CAN_F2B2_FBC3_Msk               /*!< Filter 2 register 2 bit 3 */
#define CAN_F2B2_FBC4_Pos						(4U)                            
#define CAN_F2B2_FBC4_Msk						(0x1UL << CAN_F2B2_FBC4_Pos)    
#define CAN_F2B2_FBC4							CAN_F2B2_FBC4_Msk               /*!< Filter 2 register 2 bit 4 */
#define CAN_F2B2_FBC5_Pos						(5U)                            
#define CAN_F2B2_FBC5_Msk						(0x1UL << CAN_F2B2_FBC5_Pos)    
#define CAN_F2B2_FBC5							CAN_F2B2_FBC5_Msk               /*!< Filter 2 register 2 bit 5 */
#define CAN_F2B2_FBC6_Pos						(6U)                            
#define CAN_F2B2_FBC6_Msk						(0x1UL << CAN_F2B2_FBC6_Pos)    
#define CAN_F2B2_FBC6							CAN_F2B2_FBC6_Msk               /*!< Filter 2 register 2 bit 6 */
#define CAN_F2B2_FBC7_Pos						(7U)                            
#define CAN_F2B2_FBC7_Msk						(0x1UL << CAN_F2B2_FBC7_Pos)    
#define CAN_F2B2_FBC7							CAN_F2B2_FBC7_Msk               /*!< Filter 2 register 2 bit 7 */
#define CAN_F2B2_FBC8_Pos						(8U)                            
#define CAN_F2B2_FBC8_Msk						(0x1UL << CAN_F2B2_FBC8_Pos)    
#define CAN_F2B2_FBC8							CAN_F2B2_FBC8_Msk               /*!< Filter 2 register 2 bit 8 */
#define CAN_F2B2_FBC9_Pos						(9U)                            
#define CAN_F2B2_FBC9_Msk						(0x1UL << CAN_F2B2_FBC9_Pos)    
#define CAN_F2B2_FBC9							CAN_F2B2_FBC9_Msk               /*!< Filter 2 register 2 bit 9 */
#define CAN_F2B2_FBC10_Pos						(10U)                           
#define CAN_F2B2_FBC10_Msk						(0x1UL << CAN_F2B2_FBC10_Pos)   
#define CAN_F2B2_FBC10							CAN_F2B2_FBC10_Msk              /*!< Filter 2 register 2 bit 10 */
#define CAN_F2B2_FBC11_Pos						(11U)                           
#define CAN_F2B2_FBC11_Msk						(0x1UL << CAN_F2B2_FBC11_Pos)   
#define CAN_F2B2_FBC11							CAN_F2B2_FBC11_Msk              /*!< Filter 2 register 2 bit 11 */
#define CAN_F2B2_FBC12_Pos						(12U)                           
#define CAN_F2B2_FBC12_Msk						(0x1UL << CAN_F2B2_FBC12_Pos)   
#define CAN_F2B2_FBC12							CAN_F2B2_FBC12_Msk              /*!< Filter 2 register 2 bit 12 */
#define CAN_F2B2_FBC13_Pos						(13U)                           
#define CAN_F2B2_FBC13_Msk						(0x1UL << CAN_F2B2_FBC13_Pos)   
#define CAN_F2B2_FBC13							CAN_F2B2_FBC13_Msk              /*!< Filter 2 register 2 bit 13 */
#define CAN_F2B2_FBC14_Pos						(14U)                           
#define CAN_F2B2_FBC14_Msk						(0x1UL << CAN_F2B2_FBC14_Pos)   
#define CAN_F2B2_FBC14							CAN_F2B2_FBC14_Msk              /*!< Filter 2 register 2 bit 14 */
#define CAN_F2B2_FBC15_Pos						(15U)                           
#define CAN_F2B2_FBC15_Msk						(0x1UL << CAN_F2B2_FBC15_Pos)   
#define CAN_F2B2_FBC15							CAN_F2B2_FBC15_Msk              /*!< Filter 2 register 2 bit 15 */
#define CAN_F2B2_FBC16_Pos						(16U)                           
#define CAN_F2B2_FBC16_Msk						(0x1UL << CAN_F2B2_FBC16_Pos)   
#define CAN_F2B2_FBC16							CAN_F2B2_FBC16_Msk              /*!< Filter 2 register 2 bit 16 */
#define CAN_F2B2_FBC17_Pos						(17U)                           
#define CAN_F2B2_FBC17_Msk						(0x1UL << CAN_F2B2_FBC17_Pos)   
#define CAN_F2B2_FBC17							CAN_F2B2_FBC17_Msk              /*!< Filter 2 register 2 bit 17 */
#define CAN_F2B2_FBC18_Pos						(18U)                           
#define CAN_F2B2_FBC18_Msk						(0x1UL << CAN_F2B2_FBC18_Pos)   
#define CAN_F2B2_FBC18							CAN_F2B2_FBC18_Msk              /*!< Filter 2 register 2 bit 18 */
#define CAN_F2B2_FBC19_Pos						(19U)                           
#define CAN_F2B2_FBC19_Msk						(0x1UL << CAN_F2B2_FBC19_Pos)   
#define CAN_F2B2_FBC19							CAN_F2B2_FBC19_Msk              /*!< Filter 2 register 2 bit 19 */
#define CAN_F2B2_FBC20_Pos						(20U)                           
#define CAN_F2B2_FBC20_Msk						(0x1UL << CAN_F2B2_FBC20_Pos)   
#define CAN_F2B2_FBC20							CAN_F2B2_FBC20_Msk              /*!< Filter 2 register 2 bit 20 */
#define CAN_F2B2_FBC21_Pos						(21U)                           
#define CAN_F2B2_FBC21_Msk						(0x1UL << CAN_F2B2_FBC21_Pos)   
#define CAN_F2B2_FBC21							CAN_F2B2_FBC21_Msk              /*!< Filter 2 register 2 bit 21 */
#define CAN_F2B2_FBC22_Pos						(22U)                           
#define CAN_F2B2_FBC22_Msk						(0x1UL << CAN_F2B2_FBC22_Pos)   
#define CAN_F2B2_FBC22							CAN_F2B2_FBC22_Msk              /*!< Filter 2 register 2 bit 22 */
#define CAN_F2B2_FBC23_Pos						(23U)                           
#define CAN_F2B2_FBC23_Msk						(0x1UL << CAN_F2B2_FBC23_Pos)   
#define CAN_F2B2_FBC23							CAN_F2B2_FBC23_Msk              /*!< Filter 2 register 2 bit 23 */
#define CAN_F2B2_FBC24_Pos						(24U)                           
#define CAN_F2B2_FBC24_Msk						(0x1UL << CAN_F2B2_FBC24_Pos)   
#define CAN_F2B2_FBC24							CAN_F2B2_FBC24_Msk              /*!< Filter 2 register 2 bit 24 */
#define CAN_F2B2_FBC25_Pos						(25U)                           
#define CAN_F2B2_FBC25_Msk						(0x1UL << CAN_F2B2_FBC25_Pos)   
#define CAN_F2B2_FBC25							CAN_F2B2_FBC25_Msk              /*!< Filter 2 register 2 bit 25 */
#define CAN_F2B2_FBC26_Pos						(26U)                           
#define CAN_F2B2_FBC26_Msk						(0x1UL << CAN_F2B2_FBC26_Pos)   
#define CAN_F2B2_FBC26							CAN_F2B2_FBC26_Msk              /*!< Filter 2 register 2 bit 26 */
#define CAN_F2B2_FBC27_Pos						(27U)                           
#define CAN_F2B2_FBC27_Msk						(0x1UL << CAN_F2B2_FBC27_Pos)   
#define CAN_F2B2_FBC27							CAN_F2B2_FBC27_Msk              /*!< Filter 2 register 2 bit 27 */
#define CAN_F2B2_FBC28_Pos						(28U)                           
#define CAN_F2B2_FBC28_Msk						(0x1UL << CAN_F2B2_FBC28_Pos)   
#define CAN_F2B2_FBC28							CAN_F2B2_FBC28_Msk              /*!< Filter 2 register 2 bit 28 */
#define CAN_F2B2_FBC29_Pos						(29U)                           
#define CAN_F2B2_FBC29_Msk						(0x1UL << CAN_F2B2_FBC29_Pos)   
#define CAN_F2B2_FBC29							CAN_F2B2_FBC29_Msk              /*!< Filter 2 register 2 bit 29 */
#define CAN_F2B2_FBC30_Pos						(30U)                           
#define CAN_F2B2_FBC30_Msk						(0x1UL << CAN_F2B2_FBC30_Pos)   
#define CAN_F2B2_FBC30							CAN_F2B2_FBC30_Msk              /*!< Filter 2 register 2 bit 30 */
#define CAN_F2B2_FBC31_Pos						(31U)                           
#define CAN_F2B2_FBC31_Msk						(0x1UL << CAN_F2B2_FBC31_Pos)   
#define CAN_F2B2_FBC31							CAN_F2B2_FBC31_Msk              /*!< Filter 2 register 2 bit 31 */

/*******************  Bit definition for CAN_F3R2 register  *******************/
#define CAN_F3B2_FBC0_Pos						(0U)
#define CAN_F3B2_FBC0_Msk						(0x1UL << CAN_F3B2_FBC0_Pos)
#define CAN_F3B2_FBC0							CAN_F3B2_FBC0_Msk				/*!< Filter 3 register 2 bit 0 */
#define CAN_F3B2_FBC1_Pos						(1U)                            
#define CAN_F3B2_FBC1_Msk						(0x1UL << CAN_F3B2_FBC1_Pos)    
#define CAN_F3B2_FBC1							CAN_F3B2_FBC1_Msk               /*!< Filter 3 register 2 bit 1 */
#define CAN_F3B2_FBC2_Pos						(2U)                            
#define CAN_F3B2_FBC2_Msk						(0x1UL << CAN_F3B2_FBC2_Pos)    
#define CAN_F3B2_FBC2							CAN_F3B2_FBC2_Msk               /*!< Filter 3 register 2 bit 2 */
#define CAN_F3B2_FBC3_Pos						(3U)                            
#define CAN_F3B2_FBC3_Msk						(0x1UL << CAN_F3B2_FBC3_Pos)    
#define CAN_F3B2_FBC3							CAN_F3B2_FBC3_Msk               /*!< Filter 3 register 2 bit 3 */
#define CAN_F3B2_FBC4_Pos						(4U)                            
#define CAN_F3B2_FBC4_Msk						(0x1UL << CAN_F3B2_FBC4_Pos)    
#define CAN_F3B2_FBC4							CAN_F3B2_FBC4_Msk               /*!< Filter 3 register 2 bit 4 */
#define CAN_F3B2_FBC5_Pos						(5U)                            
#define CAN_F3B2_FBC5_Msk						(0x1UL << CAN_F3B2_FBC5_Pos)    
#define CAN_F3B2_FBC5							CAN_F3B2_FBC5_Msk               /*!< Filter 3 register 2 bit 5 */
#define CAN_F3B2_FBC6_Pos						(6U)                            
#define CAN_F3B2_FBC6_Msk						(0x1UL << CAN_F3B2_FBC6_Pos)    
#define CAN_F3B2_FBC6							CAN_F3B2_FBC6_Msk               /*!< Filter 3 register 2 bit 6 */
#define CAN_F3B2_FBC7_Pos						(7U)                            
#define CAN_F3B2_FBC7_Msk						(0x1UL << CAN_F3B2_FBC7_Pos)    
#define CAN_F3B2_FBC7							CAN_F3B2_FBC7_Msk               /*!< Filter 3 register 2 bit 7 */
#define CAN_F3B2_FBC8_Pos						(8U)                            
#define CAN_F3B2_FBC8_Msk						(0x1UL << CAN_F3B2_FBC8_Pos)    
#define CAN_F3B2_FBC8							CAN_F3B2_FBC8_Msk               /*!< Filter 3 register 2 bit 8 */
#define CAN_F3B2_FBC9_Pos						(9U)                            
#define CAN_F3B2_FBC9_Msk						(0x1UL << CAN_F3B2_FBC9_Pos)    
#define CAN_F3B2_FBC9							CAN_F3B2_FBC9_Msk               /*!< Filter 3 register 2 bit 9 */
#define CAN_F3B2_FBC10_Pos						(10U)                           
#define CAN_F3B2_FBC10_Msk						(0x1UL << CAN_F3B2_FBC10_Pos)   
#define CAN_F3B2_FBC10							CAN_F3B2_FBC10_Msk              /*!< Filter 3 register 2 bit 10 */
#define CAN_F3B2_FBC11_Pos						(11U)                           
#define CAN_F3B2_FBC11_Msk						(0x1UL << CAN_F3B2_FBC11_Pos)   
#define CAN_F3B2_FBC11							CAN_F3B2_FBC11_Msk              /*!< Filter 3 register 2 bit 11 */
#define CAN_F3B2_FBC12_Pos						(12U)                           
#define CAN_F3B2_FBC12_Msk						(0x1UL << CAN_F3B2_FBC12_Pos)   
#define CAN_F3B2_FBC12							CAN_F3B2_FBC12_Msk              /*!< Filter 3 register 2 bit 12 */
#define CAN_F3B2_FBC13_Pos						(13U)                           
#define CAN_F3B2_FBC13_Msk						(0x1UL << CAN_F3B2_FBC13_Pos)   
#define CAN_F3B2_FBC13							CAN_F3B2_FBC13_Msk              /*!< Filter 3 register 2 bit 13 */
#define CAN_F3B2_FBC14_Pos						(14U)                           
#define CAN_F3B2_FBC14_Msk						(0x1UL << CAN_F3B2_FBC14_Pos)   
#define CAN_F3B2_FBC14							CAN_F3B2_FBC14_Msk              /*!< Filter 3 register 2 bit 14 */
#define CAN_F3B2_FBC15_Pos						(15U)                           
#define CAN_F3B2_FBC15_Msk						(0x1UL << CAN_F3B2_FBC15_Pos)   
#define CAN_F3B2_FBC15							CAN_F3B2_FBC15_Msk              /*!< Filter 3 register 2 bit 15 */
#define CAN_F3B2_FBC16_Pos						(16U)                           
#define CAN_F3B2_FBC16_Msk						(0x1UL << CAN_F3B2_FBC16_Pos)   
#define CAN_F3B2_FBC16							CAN_F3B2_FBC16_Msk              /*!< Filter 3 register 2 bit 16 */
#define CAN_F3B2_FBC17_Pos						(17U)                           
#define CAN_F3B2_FBC17_Msk						(0x1UL << CAN_F3B2_FBC17_Pos)   
#define CAN_F3B2_FBC17							CAN_F3B2_FBC17_Msk              /*!< Filter 3 register 2 bit 17 */
#define CAN_F3B2_FBC18_Pos						(18U)                           
#define CAN_F3B2_FBC18_Msk						(0x1UL << CAN_F3B2_FBC18_Pos)   
#define CAN_F3B2_FBC18							CAN_F3B2_FBC18_Msk              /*!< Filter 3 register 2 bit 18 */
#define CAN_F3B2_FBC19_Pos						(19U)                           
#define CAN_F3B2_FBC19_Msk						(0x1UL << CAN_F3B2_FBC19_Pos)   
#define CAN_F3B2_FBC19							CAN_F3B2_FBC19_Msk              /*!< Filter 3 register 2 bit 19 */
#define CAN_F3B2_FBC20_Pos						(20U)                           
#define CAN_F3B2_FBC20_Msk						(0x1UL << CAN_F3B2_FBC20_Pos)   
#define CAN_F3B2_FBC20							CAN_F3B2_FBC20_Msk              /*!< Filter 3 register 2 bit 20 */
#define CAN_F3B2_FBC21_Pos						(21U)                           
#define CAN_F3B2_FBC21_Msk						(0x1UL << CAN_F3B2_FBC21_Pos)   
#define CAN_F3B2_FBC21							CAN_F3B2_FBC21_Msk              /*!< Filter 3 register 2 bit 21 */
#define CAN_F3B2_FBC22_Pos						(22U)                           
#define CAN_F3B2_FBC22_Msk						(0x1UL << CAN_F3B2_FBC22_Pos)   
#define CAN_F3B2_FBC22							CAN_F3B2_FBC22_Msk              /*!< Filter 3 register 2 bit 22 */
#define CAN_F3B2_FBC23_Pos						(23U)                           
#define CAN_F3B2_FBC23_Msk						(0x1UL << CAN_F3B2_FBC23_Pos)   
#define CAN_F3B2_FBC23							CAN_F3B2_FBC23_Msk              /*!< Filter 3 register 2 bit 23 */
#define CAN_F3B2_FBC24_Pos						(24U)                           
#define CAN_F3B2_FBC24_Msk						(0x1UL << CAN_F3B2_FBC24_Pos)   
#define CAN_F3B2_FBC24							CAN_F3B2_FBC24_Msk              /*!< Filter 3 register 2 bit 24 */
#define CAN_F3B2_FBC25_Pos						(25U)                           
#define CAN_F3B2_FBC25_Msk						(0x1UL << CAN_F3B2_FBC25_Pos)   
#define CAN_F3B2_FBC25							CAN_F3B2_FBC25_Msk              /*!< Filter 3 register 2 bit 25 */
#define CAN_F3B2_FBC26_Pos						(26U)                           
#define CAN_F3B2_FBC26_Msk						(0x1UL << CAN_F3B2_FBC26_Pos)   
#define CAN_F3B2_FBC26							CAN_F3B2_FBC26_Msk              /*!< Filter 3 register 2 bit 26 */
#define CAN_F3B2_FBC27_Pos						(27U)                           
#define CAN_F3B2_FBC27_Msk						(0x1UL << CAN_F3B2_FBC27_Pos)   
#define CAN_F3B2_FBC27							CAN_F3B2_FBC27_Msk              /*!< Filter 3 register 2 bit 27 */
#define CAN_F3B2_FBC28_Pos						(28U)                           
#define CAN_F3B2_FBC28_Msk						(0x1UL << CAN_F3B2_FBC28_Pos)   
#define CAN_F3B2_FBC28							CAN_F3B2_FBC28_Msk              /*!< Filter 3 register 2 bit 28 */
#define CAN_F3B2_FBC29_Pos						(29U)                           
#define CAN_F3B2_FBC29_Msk						(0x1UL << CAN_F3B2_FBC29_Pos)   
#define CAN_F3B2_FBC29							CAN_F3B2_FBC29_Msk              /*!< Filter 3 register 2 bit 29 */
#define CAN_F3B2_FBC30_Pos						(30U)                           
#define CAN_F3B2_FBC30_Msk						(0x1UL << CAN_F3B2_FBC30_Pos)   
#define CAN_F3B2_FBC30							CAN_F3B2_FBC30_Msk              /*!< Filter 3 register 2 bit 30 */
#define CAN_F3B2_FBC31_Pos						(31U)                           
#define CAN_F3B2_FBC31_Msk						(0x1UL << CAN_F3B2_FBC31_Pos)   
#define CAN_F3B2_FBC31							CAN_F3B2_FBC31_Msk              /*!< Filter 3 register 2 bit 31 */

/*******************  Bit definition for CAN_F4R2 register  *******************/
#define CAN_F4B2_FBC0_Pos						(0U)
#define CAN_F4B2_FBC0_Msk						(0x1UL << CAN_F4B2_FBC0_Pos)
#define CAN_F4B2_FBC0							CAN_F4B2_FBC0_Msk				/*!< Filter 4 register 2 bit 0 */
#define CAN_F4B2_FBC1_Pos						(1U)                            
#define CAN_F4B2_FBC1_Msk						(0x1UL << CAN_F4B2_FBC1_Pos)    
#define CAN_F4B2_FBC1							CAN_F4B2_FBC1_Msk               /*!< Filter 4 register 2 bit 1 */
#define CAN_F4B2_FBC2_Pos						(2U)                            
#define CAN_F4B2_FBC2_Msk						(0x1UL << CAN_F4B2_FBC2_Pos)    
#define CAN_F4B2_FBC2							CAN_F4B2_FBC2_Msk               /*!< Filter 4 register 2 bit 2 */
#define CAN_F4B2_FBC3_Pos						(3U)                            
#define CAN_F4B2_FBC3_Msk						(0x1UL << CAN_F4B2_FBC3_Pos)    
#define CAN_F4B2_FBC3							CAN_F4B2_FBC3_Msk               /*!< Filter 4 register 2 bit 3 */
#define CAN_F4B2_FBC4_Pos						(4U)                            
#define CAN_F4B2_FBC4_Msk						(0x1UL << CAN_F4B2_FBC4_Pos)    
#define CAN_F4B2_FBC4							CAN_F4B2_FBC4_Msk               /*!< Filter 4 register 2 bit 4 */
#define CAN_F4B2_FBC5_Pos						(5U)                            
#define CAN_F4B2_FBC5_Msk						(0x1UL << CAN_F4B2_FBC5_Pos)    
#define CAN_F4B2_FBC5							CAN_F4B2_FBC5_Msk               /*!< Filter 4 register 2 bit 5 */
#define CAN_F4B2_FBC6_Pos						(6U)                            
#define CAN_F4B2_FBC6_Msk						(0x1UL << CAN_F4B2_FBC6_Pos)    
#define CAN_F4B2_FBC6							CAN_F4B2_FBC6_Msk               /*!< Filter 4 register 2 bit 6 */
#define CAN_F4B2_FBC7_Pos						(7U)                            
#define CAN_F4B2_FBC7_Msk						(0x1UL << CAN_F4B2_FBC7_Pos)    
#define CAN_F4B2_FBC7							CAN_F4B2_FBC7_Msk               /*!< Filter 4 register 2 bit 7 */
#define CAN_F4B2_FBC8_Pos						(8U)                            
#define CAN_F4B2_FBC8_Msk						(0x1UL << CAN_F4B2_FBC8_Pos)    
#define CAN_F4B2_FBC8							CAN_F4B2_FBC8_Msk               /*!< Filter 4 register 2 bit 8 */
#define CAN_F4B2_FBC9_Pos						(9U)                            
#define CAN_F4B2_FBC9_Msk						(0x1UL << CAN_F4B2_FBC9_Pos)    
#define CAN_F4B2_FBC9							CAN_F4B2_FBC9_Msk               /*!< Filter 4 register 2 bit 9 */
#define CAN_F4B2_FBC10_Pos						(10U)                           
#define CAN_F4B2_FBC10_Msk						(0x1UL << CAN_F4B2_FBC10_Pos)   
#define CAN_F4B2_FBC10							CAN_F4B2_FBC10_Msk              /*!< Filter 4 register 2 bit 10 */
#define CAN_F4B2_FBC11_Pos						(11U)                           
#define CAN_F4B2_FBC11_Msk						(0x1UL << CAN_F4B2_FBC11_Pos)   
#define CAN_F4B2_FBC11							CAN_F4B2_FBC11_Msk              /*!< Filter 4 register 2 bit 11 */
#define CAN_F4B2_FBC12_Pos						(12U)                           
#define CAN_F4B2_FBC12_Msk						(0x1UL << CAN_F4B2_FBC12_Pos)   
#define CAN_F4B2_FBC12							CAN_F4B2_FBC12_Msk              /*!< Filter 4 register 2 bit 12 */
#define CAN_F4B2_FBC13_Pos						(13U)                           
#define CAN_F4B2_FBC13_Msk						(0x1UL << CAN_F4B2_FBC13_Pos)   
#define CAN_F4B2_FBC13							CAN_F4B2_FBC13_Msk              /*!< Filter 4 register 2 bit 13 */
#define CAN_F4B2_FBC14_Pos						(14U)                           
#define CAN_F4B2_FBC14_Msk						(0x1UL << CAN_F4B2_FBC14_Pos)   
#define CAN_F4B2_FBC14							CAN_F4B2_FBC14_Msk              /*!< Filter 4 register 2 bit 14 */
#define CAN_F4B2_FBC15_Pos						(15U)                           
#define CAN_F4B2_FBC15_Msk						(0x1UL << CAN_F4B2_FBC15_Pos)   
#define CAN_F4B2_FBC15							CAN_F4B2_FBC15_Msk              /*!< Filter 4 register 2 bit 15 */
#define CAN_F4B2_FBC16_Pos						(16U)                           
#define CAN_F4B2_FBC16_Msk						(0x1UL << CAN_F4B2_FBC16_Pos)   
#define CAN_F4B2_FBC16							CAN_F4B2_FBC16_Msk              /*!< Filter 4 register 2 bit 16 */
#define CAN_F4B2_FBC17_Pos						(17U)                           
#define CAN_F4B2_FBC17_Msk						(0x1UL << CAN_F4B2_FBC17_Pos)   
#define CAN_F4B2_FBC17							CAN_F4B2_FBC17_Msk              /*!< Filter 4 register 2 bit 17 */
#define CAN_F4B2_FBC18_Pos						(18U)                           
#define CAN_F4B2_FBC18_Msk						(0x1UL << CAN_F4B2_FBC18_Pos)   
#define CAN_F4B2_FBC18							CAN_F4B2_FBC18_Msk              /*!< Filter 4 register 2 bit 18 */
#define CAN_F4B2_FBC19_Pos						(19U)                           
#define CAN_F4B2_FBC19_Msk						(0x1UL << CAN_F4B2_FBC19_Pos)   
#define CAN_F4B2_FBC19							CAN_F4B2_FBC19_Msk              /*!< Filter 4 register 2 bit 19 */
#define CAN_F4B2_FBC20_Pos						(20U)                           
#define CAN_F4B2_FBC20_Msk						(0x1UL << CAN_F4B2_FBC20_Pos)   
#define CAN_F4B2_FBC20							CAN_F4B2_FBC20_Msk              /*!< Filter 4 register 2 bit 20 */
#define CAN_F4B2_FBC21_Pos						(21U)                           
#define CAN_F4B2_FBC21_Msk						(0x1UL << CAN_F4B2_FBC21_Pos)   
#define CAN_F4B2_FBC21							CAN_F4B2_FBC21_Msk              /*!< Filter 4 register 2 bit 21 */
#define CAN_F4B2_FBC22_Pos						(22U)                           
#define CAN_F4B2_FBC22_Msk						(0x1UL << CAN_F4B2_FBC22_Pos)   
#define CAN_F4B2_FBC22							CAN_F4B2_FBC22_Msk              /*!< Filter 4 register 2 bit 22 */
#define CAN_F4B2_FBC23_Pos						(23U)                           
#define CAN_F4B2_FBC23_Msk						(0x1UL << CAN_F4B2_FBC23_Pos)   
#define CAN_F4B2_FBC23							CAN_F4B2_FBC23_Msk              /*!< Filter 4 register 2 bit 23 */
#define CAN_F4B2_FBC24_Pos						(24U)                           
#define CAN_F4B2_FBC24_Msk						(0x1UL << CAN_F4B2_FBC24_Pos)   
#define CAN_F4B2_FBC24							CAN_F4B2_FBC24_Msk              /*!< Filter 4 register 2 bit 24 */
#define CAN_F4B2_FBC25_Pos						(25U)                           
#define CAN_F4B2_FBC25_Msk						(0x1UL << CAN_F4B2_FBC25_Pos)   
#define CAN_F4B2_FBC25							CAN_F4B2_FBC25_Msk              /*!< Filter 4 register 2 bit 25 */
#define CAN_F4B2_FBC26_Pos						(26U)                           
#define CAN_F4B2_FBC26_Msk						(0x1UL << CAN_F4B2_FBC26_Pos)   
#define CAN_F4B2_FBC26							CAN_F4B2_FBC26_Msk              /*!< Filter 4 register 2 bit 26 */
#define CAN_F4B2_FBC27_Pos						(27U)                           
#define CAN_F4B2_FBC27_Msk						(0x1UL << CAN_F4B2_FBC27_Pos)   
#define CAN_F4B2_FBC27							CAN_F4B2_FBC27_Msk              /*!< Filter 4 register 2 bit 27 */
#define CAN_F4B2_FBC28_Pos						(28U)                           
#define CAN_F4B2_FBC28_Msk						(0x1UL << CAN_F4B2_FBC28_Pos)   
#define CAN_F4B2_FBC28							CAN_F4B2_FBC28_Msk              /*!< Filter 4 register 2 bit 28 */
#define CAN_F4B2_FBC29_Pos						(29U)                           
#define CAN_F4B2_FBC29_Msk						(0x1UL << CAN_F4B2_FBC29_Pos)   
#define CAN_F4B2_FBC29							CAN_F4B2_FBC29_Msk              /*!< Filter 4 register 2 bit 29 */
#define CAN_F4B2_FBC30_Pos						(30U)                           
#define CAN_F4B2_FBC30_Msk						(0x1UL << CAN_F4B2_FBC30_Pos)   
#define CAN_F4B2_FBC30							CAN_F4B2_FBC30_Msk              /*!< Filter 4 register 2 bit 30 */
#define CAN_F4B2_FBC31_Pos						(31U)                           
#define CAN_F4B2_FBC31_Msk						(0x1UL << CAN_F4B2_FBC31_Pos)   
#define CAN_F4B2_FBC31							CAN_F4B2_FBC31_Msk              /*!< Filter 4 register 2 bit 31 */

/*******************  Bit definition for CAN_F5R2 register  *******************/
#define CAN_F5B2_FBC0_Pos						(0U)
#define CAN_F5B2_FBC0_Msk						(0x1UL << CAN_F5B2_FBC0_Pos)
#define CAN_F5B2_FBC0							CAN_F5B2_FBC0_Msk				/*!< Filter 5 register 2 bit 0 */
#define CAN_F5B2_FBC1_Pos						(1U)                            
#define CAN_F5B2_FBC1_Msk						(0x1UL << CAN_F5B2_FBC1_Pos)    
#define CAN_F5B2_FBC1							CAN_F5B2_FBC1_Msk               /*!< Filter 5 register 2 bit 1 */
#define CAN_F5B2_FBC2_Pos						(2U)                            
#define CAN_F5B2_FBC2_Msk						(0x1UL << CAN_F5B2_FBC2_Pos)    
#define CAN_F5B2_FBC2							CAN_F5B2_FBC2_Msk               /*!< Filter 5 register 2 bit 2 */
#define CAN_F5B2_FBC3_Pos						(3U)                            
#define CAN_F5B2_FBC3_Msk						(0x1UL << CAN_F5B2_FBC3_Pos)    
#define CAN_F5B2_FBC3							CAN_F5B2_FBC3_Msk               /*!< Filter 5 register 2 bit 3 */
#define CAN_F5B2_FBC4_Pos						(4U)                            
#define CAN_F5B2_FBC4_Msk						(0x1UL << CAN_F5B2_FBC4_Pos)    
#define CAN_F5B2_FBC4							CAN_F5B2_FBC4_Msk               /*!< Filter 5 register 2 bit 4 */
#define CAN_F5B2_FBC5_Pos						(5U)                            
#define CAN_F5B2_FBC5_Msk						(0x1UL << CAN_F5B2_FBC5_Pos)    
#define CAN_F5B2_FBC5							CAN_F5B2_FBC5_Msk               /*!< Filter 5 register 2 bit 5 */
#define CAN_F5B2_FBC6_Pos						(6U)                            
#define CAN_F5B2_FBC6_Msk						(0x1UL << CAN_F5B2_FBC6_Pos)    
#define CAN_F5B2_FBC6							CAN_F5B2_FBC6_Msk               /*!< Filter 5 register 2 bit 6 */
#define CAN_F5B2_FBC7_Pos						(7U)                            
#define CAN_F5B2_FBC7_Msk						(0x1UL << CAN_F5B2_FBC7_Pos)    
#define CAN_F5B2_FBC7							CAN_F5B2_FBC7_Msk               /*!< Filter 5 register 2 bit 7 */
#define CAN_F5B2_FBC8_Pos						(8U)                            
#define CAN_F5B2_FBC8_Msk						(0x1UL << CAN_F5B2_FBC8_Pos)    
#define CAN_F5B2_FBC8							CAN_F5B2_FBC8_Msk               /*!< Filter 5 register 2 bit 8 */
#define CAN_F5B2_FBC9_Pos						(9U)                            
#define CAN_F5B2_FBC9_Msk						(0x1UL << CAN_F5B2_FBC9_Pos)    
#define CAN_F5B2_FBC9							CAN_F5B2_FBC9_Msk               /*!< Filter 5 register 2 bit 9 */
#define CAN_F5B2_FBC10_Pos						(10U)                           
#define CAN_F5B2_FBC10_Msk						(0x1UL << CAN_F5B2_FBC10_Pos)   
#define CAN_F5B2_FBC10							CAN_F5B2_FBC10_Msk              /*!< Filter 5 register 2 bit 10 */
#define CAN_F5B2_FBC11_Pos						(11U)                           
#define CAN_F5B2_FBC11_Msk						(0x1UL << CAN_F5B2_FBC11_Pos)   
#define CAN_F5B2_FBC11							CAN_F5B2_FBC11_Msk              /*!< Filter 5 register 2 bit 11 */
#define CAN_F5B2_FBC12_Pos						(12U)                           
#define CAN_F5B2_FBC12_Msk						(0x1UL << CAN_F5B2_FBC12_Pos)   
#define CAN_F5B2_FBC12							CAN_F5B2_FBC12_Msk              /*!< Filter 5 register 2 bit 12 */
#define CAN_F5B2_FBC13_Pos						(13U)                           
#define CAN_F5B2_FBC13_Msk						(0x1UL << CAN_F5B2_FBC13_Pos)   
#define CAN_F5B2_FBC13							CAN_F5B2_FBC13_Msk              /*!< Filter 5 register 2 bit 13 */
#define CAN_F5B2_FBC14_Pos						(14U)                           
#define CAN_F5B2_FBC14_Msk						(0x1UL << CAN_F5B2_FBC14_Pos)   
#define CAN_F5B2_FBC14							CAN_F5B2_FBC14_Msk              /*!< Filter 5 register 2 bit 14 */
#define CAN_F5B2_FBC15_Pos						(15U)                           
#define CAN_F5B2_FBC15_Msk						(0x1UL << CAN_F5B2_FBC15_Pos)   
#define CAN_F5B2_FBC15							CAN_F5B2_FBC15_Msk              /*!< Filter 5 register 2 bit 15 */
#define CAN_F5B2_FBC16_Pos						(16U)                           
#define CAN_F5B2_FBC16_Msk						(0x1UL << CAN_F5B2_FBC16_Pos)   
#define CAN_F5B2_FBC16							CAN_F5B2_FBC16_Msk              /*!< Filter 5 register 2 bit 16 */
#define CAN_F5B2_FBC17_Pos						(17U)                           
#define CAN_F5B2_FBC17_Msk						(0x1UL << CAN_F5B2_FBC17_Pos)   
#define CAN_F5B2_FBC17							CAN_F5B2_FBC17_Msk              /*!< Filter 5 register 2 bit 17 */
#define CAN_F5B2_FBC18_Pos						(18U)                           
#define CAN_F5B2_FBC18_Msk						(0x1UL << CAN_F5B2_FBC18_Pos)   
#define CAN_F5B2_FBC18							CAN_F5B2_FBC18_Msk              /*!< Filter 5 register 2 bit 18 */
#define CAN_F5B2_FBC19_Pos						(19U)                           
#define CAN_F5B2_FBC19_Msk						(0x1UL << CAN_F5B2_FBC19_Pos)   
#define CAN_F5B2_FBC19							CAN_F5B2_FBC19_Msk              /*!< Filter 5 register 2 bit 19 */
#define CAN_F5B2_FBC20_Pos						(20U)                           
#define CAN_F5B2_FBC20_Msk						(0x1UL << CAN_F5B2_FBC20_Pos)   
#define CAN_F5B2_FBC20							CAN_F5B2_FBC20_Msk              /*!< Filter 5 register 2 bit 20 */
#define CAN_F5B2_FBC21_Pos						(21U)                           
#define CAN_F5B2_FBC21_Msk						(0x1UL << CAN_F5B2_FBC21_Pos)   
#define CAN_F5B2_FBC21							CAN_F5B2_FBC21_Msk              /*!< Filter 5 register 2 bit 21 */
#define CAN_F5B2_FBC22_Pos						(22U)                           
#define CAN_F5B2_FBC22_Msk						(0x1UL << CAN_F5B2_FBC22_Pos)   
#define CAN_F5B2_FBC22							CAN_F5B2_FBC22_Msk              /*!< Filter 5 register 2 bit 22 */
#define CAN_F5B2_FBC23_Pos						(23U)                           
#define CAN_F5B2_FBC23_Msk						(0x1UL << CAN_F5B2_FBC23_Pos)   
#define CAN_F5B2_FBC23							CAN_F5B2_FBC23_Msk              /*!< Filter 5 register 2 bit 23 */
#define CAN_F5B2_FBC24_Pos						(24U)                           
#define CAN_F5B2_FBC24_Msk						(0x1UL << CAN_F5B2_FBC24_Pos)   
#define CAN_F5B2_FBC24							CAN_F5B2_FBC24_Msk              /*!< Filter 5 register 2 bit 24 */
#define CAN_F5B2_FBC25_Pos						(25U)                           
#define CAN_F5B2_FBC25_Msk						(0x1UL << CAN_F5B2_FBC25_Pos)   
#define CAN_F5B2_FBC25							CAN_F5B2_FBC25_Msk              /*!< Filter 5 register 2 bit 25 */
#define CAN_F5B2_FBC26_Pos						(26U)                           
#define CAN_F5B2_FBC26_Msk						(0x1UL << CAN_F5B2_FBC26_Pos)   
#define CAN_F5B2_FBC26							CAN_F5B2_FBC26_Msk              /*!< Filter 5 register 2 bit 26 */
#define CAN_F5B2_FBC27_Pos						(27U)                           
#define CAN_F5B2_FBC27_Msk						(0x1UL << CAN_F5B2_FBC27_Pos)   
#define CAN_F5B2_FBC27							CAN_F5B2_FBC27_Msk              /*!< Filter 5 register 2 bit 27 */
#define CAN_F5B2_FBC28_Pos						(28U)                           
#define CAN_F5B2_FBC28_Msk						(0x1UL << CAN_F5B2_FBC28_Pos)   
#define CAN_F5B2_FBC28							CAN_F5B2_FBC28_Msk              /*!< Filter 5 register 2 bit 28 */
#define CAN_F5B2_FBC29_Pos						(29U)                           
#define CAN_F5B2_FBC29_Msk						(0x1UL << CAN_F5B2_FBC29_Pos)   
#define CAN_F5B2_FBC29							CAN_F5B2_FBC29_Msk              /*!< Filter 5 register 2 bit 29 */
#define CAN_F5B2_FBC30_Pos						(30U)                           
#define CAN_F5B2_FBC30_Msk						(0x1UL << CAN_F5B2_FBC30_Pos)   
#define CAN_F5B2_FBC30							CAN_F5B2_FBC30_Msk              /*!< Filter 5 register 2 bit 30 */
#define CAN_F5B2_FBC31_Pos						(31U)                           
#define CAN_F5B2_FBC31_Msk						(0x1UL << CAN_F5B2_FBC31_Pos)   
#define CAN_F5B2_FBC31							CAN_F5B2_FBC31_Msk              /*!< Filter 5 register 2 bit 31 */

/*******************  Bit definition for CAN_F6R2 register  *******************/
#define CAN_F6B2_FBC0_Pos						(0U)
#define CAN_F6B2_FBC0_Msk						(0x1UL << CAN_F6B2_FBC0_Pos)
#define CAN_F6B2_FBC0							CAN_F6B2_FBC0_Msk				/*!< Filter 6 register 2 bit 0 */
#define CAN_F6B2_FBC1_Pos						(1U)                            
#define CAN_F6B2_FBC1_Msk						(0x1UL << CAN_F6B2_FBC1_Pos)    
#define CAN_F6B2_FBC1							CAN_F6B2_FBC1_Msk               /*!< Filter 6 register 2 bit 1 */
#define CAN_F6B2_FBC2_Pos						(2U)                            
#define CAN_F6B2_FBC2_Msk						(0x1UL << CAN_F6B2_FBC2_Pos)    
#define CAN_F6B2_FBC2							CAN_F6B2_FBC2_Msk               /*!< Filter 6 register 2 bit 2 */
#define CAN_F6B2_FBC3_Pos						(3U)                            
#define CAN_F6B2_FBC3_Msk						(0x1UL << CAN_F6B2_FBC3_Pos)    
#define CAN_F6B2_FBC3							CAN_F6B2_FBC3_Msk               /*!< Filter 6 register 2 bit 3 */
#define CAN_F6B2_FBC4_Pos						(4U)                            
#define CAN_F6B2_FBC4_Msk						(0x1UL << CAN_F6B2_FBC4_Pos)    
#define CAN_F6B2_FBC4							CAN_F6B2_FBC4_Msk               /*!< Filter 6 register 2 bit 4 */
#define CAN_F6B2_FBC5_Pos						(5U)                            
#define CAN_F6B2_FBC5_Msk						(0x1UL << CAN_F6B2_FBC5_Pos)    
#define CAN_F6B2_FBC5							CAN_F6B2_FBC5_Msk               /*!< Filter 6 register 2 bit 5 */
#define CAN_F6B2_FBC6_Pos						(6U)                            
#define CAN_F6B2_FBC6_Msk						(0x1UL << CAN_F6B2_FBC6_Pos)    
#define CAN_F6B2_FBC6							CAN_F6B2_FBC6_Msk               /*!< Filter 6 register 2 bit 6 */
#define CAN_F6B2_FBC7_Pos						(7U)                            
#define CAN_F6B2_FBC7_Msk						(0x1UL << CAN_F6B2_FBC7_Pos)    
#define CAN_F6B2_FBC7							CAN_F6B2_FBC7_Msk               /*!< Filter 6 register 2 bit 7 */
#define CAN_F6B2_FBC8_Pos						(8U)                            
#define CAN_F6B2_FBC8_Msk						(0x1UL << CAN_F6B2_FBC8_Pos)    
#define CAN_F6B2_FBC8							CAN_F6B2_FBC8_Msk               /*!< Filter 6 register 2 bit 8 */
#define CAN_F6B2_FBC9_Pos						(9U)                            
#define CAN_F6B2_FBC9_Msk						(0x1UL << CAN_F6B2_FBC9_Pos)    
#define CAN_F6B2_FBC9							CAN_F6B2_FBC9_Msk               /*!< Filter 6 register 2 bit 9 */
#define CAN_F6B2_FBC10_Pos						(10U)                           
#define CAN_F6B2_FBC10_Msk						(0x1UL << CAN_F6B2_FBC10_Pos)   
#define CAN_F6B2_FBC10							CAN_F6B2_FBC10_Msk              /*!< Filter 6 register 2 bit 10 */
#define CAN_F6B2_FBC11_Pos						(11U)                           
#define CAN_F6B2_FBC11_Msk						(0x1UL << CAN_F6B2_FBC11_Pos)   
#define CAN_F6B2_FBC11							CAN_F6B2_FBC11_Msk              /*!< Filter 6 register 2 bit 11 */
#define CAN_F6B2_FBC12_Pos						(12U)                           
#define CAN_F6B2_FBC12_Msk						(0x1UL << CAN_F6B2_FBC12_Pos)   
#define CAN_F6B2_FBC12							CAN_F6B2_FBC12_Msk              /*!< Filter 6 register 2 bit 12 */
#define CAN_F6B2_FBC13_Pos						(13U)                           
#define CAN_F6B2_FBC13_Msk						(0x1UL << CAN_F6B2_FBC13_Pos)   
#define CAN_F6B2_FBC13							CAN_F6B2_FBC13_Msk              /*!< Filter 6 register 2 bit 13 */
#define CAN_F6B2_FBC14_Pos						(14U)                           
#define CAN_F6B2_FBC14_Msk						(0x1UL << CAN_F6B2_FBC14_Pos)   
#define CAN_F6B2_FBC14							CAN_F6B2_FBC14_Msk              /*!< Filter 6 register 2 bit 14 */
#define CAN_F6B2_FBC15_Pos						(15U)                           
#define CAN_F6B2_FBC15_Msk						(0x1UL << CAN_F6B2_FBC15_Pos)   
#define CAN_F6B2_FBC15							CAN_F6B2_FBC15_Msk              /*!< Filter 6 register 2 bit 15 */
#define CAN_F6B2_FBC16_Pos						(16U)                           
#define CAN_F6B2_FBC16_Msk						(0x1UL << CAN_F6B2_FBC16_Pos)   
#define CAN_F6B2_FBC16							CAN_F6B2_FBC16_Msk              /*!< Filter 6 register 2 bit 16 */
#define CAN_F6B2_FBC17_Pos						(17U)                           
#define CAN_F6B2_FBC17_Msk						(0x1UL << CAN_F6B2_FBC17_Pos)   
#define CAN_F6B2_FBC17							CAN_F6B2_FBC17_Msk              /*!< Filter 6 register 2 bit 17 */
#define CAN_F6B2_FBC18_Pos						(18U)                           
#define CAN_F6B2_FBC18_Msk						(0x1UL << CAN_F6B2_FBC18_Pos)   
#define CAN_F6B2_FBC18							CAN_F6B2_FBC18_Msk              /*!< Filter 6 register 2 bit 18 */
#define CAN_F6B2_FBC19_Pos						(19U)                           
#define CAN_F6B2_FBC19_Msk						(0x1UL << CAN_F6B2_FBC19_Pos)   
#define CAN_F6B2_FBC19							CAN_F6B2_FBC19_Msk              /*!< Filter 6 register 2 bit 19 */
#define CAN_F6B2_FBC20_Pos						(20U)                           
#define CAN_F6B2_FBC20_Msk						(0x1UL << CAN_F6B2_FBC20_Pos)   
#define CAN_F6B2_FBC20							CAN_F6B2_FBC20_Msk              /*!< Filter 6 register 2 bit 20 */
#define CAN_F6B2_FBC21_Pos						(21U)                           
#define CAN_F6B2_FBC21_Msk						(0x1UL << CAN_F6B2_FBC21_Pos)   
#define CAN_F6B2_FBC21							CAN_F6B2_FBC21_Msk              /*!< Filter 6 register 2 bit 21 */
#define CAN_F6B2_FBC22_Pos						(22U)                           
#define CAN_F6B2_FBC22_Msk						(0x1UL << CAN_F6B2_FBC22_Pos)   
#define CAN_F6B2_FBC22							CAN_F6B2_FBC22_Msk              /*!< Filter 6 register 2 bit 22 */
#define CAN_F6B2_FBC23_Pos						(23U)                           
#define CAN_F6B2_FBC23_Msk						(0x1UL << CAN_F6B2_FBC23_Pos)   
#define CAN_F6B2_FBC23							CAN_F6B2_FBC23_Msk              /*!< Filter 6 register 2 bit 23 */
#define CAN_F6B2_FBC24_Pos						(24U)                           
#define CAN_F6B2_FBC24_Msk						(0x1UL << CAN_F6B2_FBC24_Pos)   
#define CAN_F6B2_FBC24							CAN_F6B2_FBC24_Msk              /*!< Filter 6 register 2 bit 24 */
#define CAN_F6B2_FBC25_Pos						(25U)                           
#define CAN_F6B2_FBC25_Msk						(0x1UL << CAN_F6B2_FBC25_Pos)   
#define CAN_F6B2_FBC25							CAN_F6B2_FBC25_Msk              /*!< Filter 6 register 2 bit 25 */
#define CAN_F6B2_FBC26_Pos						(26U)                           
#define CAN_F6B2_FBC26_Msk						(0x1UL << CAN_F6B2_FBC26_Pos)   
#define CAN_F6B2_FBC26							CAN_F6B2_FBC26_Msk              /*!< Filter 6 register 2 bit 26 */
#define CAN_F6B2_FBC27_Pos						(27U)                           
#define CAN_F6B2_FBC27_Msk						(0x1UL << CAN_F6B2_FBC27_Pos)   
#define CAN_F6B2_FBC27							CAN_F6B2_FBC27_Msk              /*!< Filter 6 register 2 bit 27 */
#define CAN_F6B2_FBC28_Pos						(28U)                           
#define CAN_F6B2_FBC28_Msk						(0x1UL << CAN_F6B2_FBC28_Pos)   
#define CAN_F6B2_FBC28							CAN_F6B2_FBC28_Msk              /*!< Filter 6 register 2 bit 28 */
#define CAN_F6B2_FBC29_Pos						(29U)                           
#define CAN_F6B2_FBC29_Msk						(0x1UL << CAN_F6B2_FBC29_Pos)   
#define CAN_F6B2_FBC29							CAN_F6B2_FBC29_Msk              /*!< Filter 6 register 2 bit 29 */
#define CAN_F6B2_FBC30_Pos						(30U)                           
#define CAN_F6B2_FBC30_Msk						(0x1UL << CAN_F6B2_FBC30_Pos)   
#define CAN_F6B2_FBC30							CAN_F6B2_FBC30_Msk              /*!< Filter 6 register 2 bit 30 */
#define CAN_F6B2_FBC31_Pos						(31U)                           
#define CAN_F6B2_FBC31_Msk						(0x1UL << CAN_F6B2_FBC31_Pos)   
#define CAN_F6B2_FBC31							CAN_F6B2_FBC31_Msk              /*!< Filter 6 register 2 bit 31 */

/*******************  Bit definition for CAN_F7R2 register  *******************/
#define CAN_F7B2_FBC0_Pos						(0U)
#define CAN_F7B2_FBC0_Msk						(0x1UL << CAN_F7B2_FBC0_Pos)
#define CAN_F7B2_FBC0							CAN_F7B2_FBC0_Msk				/*!< Filter 7 register 2 bit 0 */
#define CAN_F7B2_FBC1_Pos						(1U)                            
#define CAN_F7B2_FBC1_Msk						(0x1UL << CAN_F7B2_FBC1_Pos)    
#define CAN_F7B2_FBC1							CAN_F7B2_FBC1_Msk               /*!< Filter 7 register 2 bit 1 */
#define CAN_F7B2_FBC2_Pos						(2U)                            
#define CAN_F7B2_FBC2_Msk						(0x1UL << CAN_F7B2_FBC2_Pos)    
#define CAN_F7B2_FBC2							CAN_F7B2_FBC2_Msk               /*!< Filter 7 register 2 bit 2 */
#define CAN_F7B2_FBC3_Pos						(3U)                            
#define CAN_F7B2_FBC3_Msk						(0x1UL << CAN_F7B2_FBC3_Pos)    
#define CAN_F7B2_FBC3							CAN_F7B2_FBC3_Msk               /*!< Filter 7 register 2 bit 3 */
#define CAN_F7B2_FBC4_Pos						(4U)                            
#define CAN_F7B2_FBC4_Msk						(0x1UL << CAN_F7B2_FBC4_Pos)    
#define CAN_F7B2_FBC4							CAN_F7B2_FBC4_Msk               /*!< Filter 7 register 2 bit 4 */
#define CAN_F7B2_FBC5_Pos						(5U)                            
#define CAN_F7B2_FBC5_Msk						(0x1UL << CAN_F7B2_FBC5_Pos)    
#define CAN_F7B2_FBC5							CAN_F7B2_FBC5_Msk               /*!< Filter 7 register 2 bit 5 */
#define CAN_F7B2_FBC6_Pos						(6U)                            
#define CAN_F7B2_FBC6_Msk						(0x1UL << CAN_F7B2_FBC6_Pos)    
#define CAN_F7B2_FBC6							CAN_F7B2_FBC6_Msk               /*!< Filter 7 register 2 bit 6 */
#define CAN_F7B2_FBC7_Pos						(7U)                            
#define CAN_F7B2_FBC7_Msk						(0x1UL << CAN_F7B2_FBC7_Pos)    
#define CAN_F7B2_FBC7							CAN_F7B2_FBC7_Msk               /*!< Filter 7 register 2 bit 7 */
#define CAN_F7B2_FBC8_Pos						(8U)                            
#define CAN_F7B2_FBC8_Msk						(0x1UL << CAN_F7B2_FBC8_Pos)    
#define CAN_F7B2_FBC8							CAN_F7B2_FBC8_Msk               /*!< Filter 7 register 2 bit 8 */
#define CAN_F7B2_FBC9_Pos						(9U)                            
#define CAN_F7B2_FBC9_Msk						(0x1UL << CAN_F7B2_FBC9_Pos)    
#define CAN_F7B2_FBC9							CAN_F7B2_FBC9_Msk               /*!< Filter 7 register 2 bit 9 */
#define CAN_F7B2_FBC10_Pos						(10U)                           
#define CAN_F7B2_FBC10_Msk						(0x1UL << CAN_F7B2_FBC10_Pos)   
#define CAN_F7B2_FBC10							CAN_F7B2_FBC10_Msk              /*!< Filter 7 register 2 bit 10 */
#define CAN_F7B2_FBC11_Pos						(11U)                           
#define CAN_F7B2_FBC11_Msk						(0x1UL << CAN_F7B2_FBC11_Pos)   
#define CAN_F7B2_FBC11							CAN_F7B2_FBC11_Msk              /*!< Filter 7 register 2 bit 11 */
#define CAN_F7B2_FBC12_Pos						(12U)                           
#define CAN_F7B2_FBC12_Msk						(0x1UL << CAN_F7B2_FBC12_Pos)   
#define CAN_F7B2_FBC12							CAN_F7B2_FBC12_Msk              /*!< Filter 7 register 2 bit 12 */
#define CAN_F7B2_FBC13_Pos						(13U)                           
#define CAN_F7B2_FBC13_Msk						(0x1UL << CAN_F7B2_FBC13_Pos)   
#define CAN_F7B2_FBC13							CAN_F7B2_FBC13_Msk              /*!< Filter 7 register 2 bit 13 */
#define CAN_F7B2_FBC14_Pos						(14U)                           
#define CAN_F7B2_FBC14_Msk						(0x1UL << CAN_F7B2_FBC14_Pos)   
#define CAN_F7B2_FBC14							CAN_F7B2_FBC14_Msk              /*!< Filter 7 register 2 bit 14 */
#define CAN_F7B2_FBC15_Pos						(15U)                           
#define CAN_F7B2_FBC15_Msk						(0x1UL << CAN_F7B2_FBC15_Pos)   
#define CAN_F7B2_FBC15							CAN_F7B2_FBC15_Msk              /*!< Filter 7 register 2 bit 15 */
#define CAN_F7B2_FBC16_Pos						(16U)                           
#define CAN_F7B2_FBC16_Msk						(0x1UL << CAN_F7B2_FBC16_Pos)   
#define CAN_F7B2_FBC16							CAN_F7B2_FBC16_Msk              /*!< Filter 7 register 2 bit 16 */
#define CAN_F7B2_FBC17_Pos						(17U)                           
#define CAN_F7B2_FBC17_Msk						(0x1UL << CAN_F7B2_FBC17_Pos)   
#define CAN_F7B2_FBC17							CAN_F7B2_FBC17_Msk              /*!< Filter 7 register 2 bit 17 */
#define CAN_F7B2_FBC18_Pos						(18U)                           
#define CAN_F7B2_FBC18_Msk						(0x1UL << CAN_F7B2_FBC18_Pos)   
#define CAN_F7B2_FBC18							CAN_F7B2_FBC18_Msk              /*!< Filter 7 register 2 bit 18 */
#define CAN_F7B2_FBC19_Pos						(19U)                           
#define CAN_F7B2_FBC19_Msk						(0x1UL << CAN_F7B2_FBC19_Pos)   
#define CAN_F7B2_FBC19							CAN_F7B2_FBC19_Msk              /*!< Filter 7 register 2 bit 19 */
#define CAN_F7B2_FBC20_Pos						(20U)                           
#define CAN_F7B2_FBC20_Msk						(0x1UL << CAN_F7B2_FBC20_Pos)   
#define CAN_F7B2_FBC20							CAN_F7B2_FBC20_Msk              /*!< Filter 7 register 2 bit 20 */
#define CAN_F7B2_FBC21_Pos						(21U)                           
#define CAN_F7B2_FBC21_Msk						(0x1UL << CAN_F7B2_FBC21_Pos)   
#define CAN_F7B2_FBC21							CAN_F7B2_FBC21_Msk              /*!< Filter 7 register 2 bit 21 */
#define CAN_F7B2_FBC22_Pos						(22U)                           
#define CAN_F7B2_FBC22_Msk						(0x1UL << CAN_F7B2_FBC22_Pos)   
#define CAN_F7B2_FBC22							CAN_F7B2_FBC22_Msk              /*!< Filter 7 register 2 bit 22 */
#define CAN_F7B2_FBC23_Pos						(23U)                           
#define CAN_F7B2_FBC23_Msk						(0x1UL << CAN_F7B2_FBC23_Pos)   
#define CAN_F7B2_FBC23							CAN_F7B2_FBC23_Msk              /*!< Filter 7 register 2 bit 23 */
#define CAN_F7B2_FBC24_Pos						(24U)                           
#define CAN_F7B2_FBC24_Msk						(0x1UL << CAN_F7B2_FBC24_Pos)   
#define CAN_F7B2_FBC24							CAN_F7B2_FBC24_Msk              /*!< Filter 7 register 2 bit 24 */
#define CAN_F7B2_FBC25_Pos						(25U)                           
#define CAN_F7B2_FBC25_Msk						(0x1UL << CAN_F7B2_FBC25_Pos)   
#define CAN_F7B2_FBC25							CAN_F7B2_FBC25_Msk              /*!< Filter 7 register 2 bit 25 */
#define CAN_F7B2_FBC26_Pos						(26U)                           
#define CAN_F7B2_FBC26_Msk						(0x1UL << CAN_F7B2_FBC26_Pos)   
#define CAN_F7B2_FBC26							CAN_F7B2_FBC26_Msk              /*!< Filter 7 register 2 bit 26 */
#define CAN_F7B2_FBC27_Pos						(27U)                           
#define CAN_F7B2_FBC27_Msk						(0x1UL << CAN_F7B2_FBC27_Pos)   
#define CAN_F7B2_FBC27							CAN_F7B2_FBC27_Msk              /*!< Filter 7 register 2 bit 27 */
#define CAN_F7B2_FBC28_Pos						(28U)                           
#define CAN_F7B2_FBC28_Msk						(0x1UL << CAN_F7B2_FBC28_Pos)   
#define CAN_F7B2_FBC28							CAN_F7B2_FBC28_Msk              /*!< Filter 7 register 2 bit 28 */
#define CAN_F7B2_FBC29_Pos						(29U)                           
#define CAN_F7B2_FBC29_Msk						(0x1UL << CAN_F7B2_FBC29_Pos)   
#define CAN_F7B2_FBC29							CAN_F7B2_FBC29_Msk              /*!< Filter 7 register 2 bit 29 */
#define CAN_F7B2_FBC30_Pos						(30U)                           
#define CAN_F7B2_FBC30_Msk						(0x1UL << CAN_F7B2_FBC30_Pos)   
#define CAN_F7B2_FBC30							CAN_F7B2_FBC30_Msk              /*!< Filter 7 register 2 bit 30 */
#define CAN_F7B2_FBC31_Pos						(31U)                           
#define CAN_F7B2_FBC31_Msk						(0x1UL << CAN_F7B2_FBC31_Pos)   
#define CAN_F7B2_FBC31							CAN_F7B2_FBC31_Msk              /*!< Filter 7 register 2 bit 31 */

/*******************  Bit definition for CAN_F8R2 register  *******************/
#define CAN_F8B2_FBC0_Pos						(0U)
#define CAN_F8B2_FBC0_Msk						(0x1UL << CAN_F8B2_FBC0_Pos)
#define CAN_F8B2_FBC0							CAN_F8B2_FBC0_Msk				/*!< Filter 8 register 2 bit 0 */
#define CAN_F8B2_FBC1_Pos						(1U)                            
#define CAN_F8B2_FBC1_Msk						(0x1UL << CAN_F8B2_FBC1_Pos)    
#define CAN_F8B2_FBC1							CAN_F8B2_FBC1_Msk               /*!< Filter 8 register 2 bit 1 */
#define CAN_F8B2_FBC2_Pos						(2U)                            
#define CAN_F8B2_FBC2_Msk						(0x1UL << CAN_F8B2_FBC2_Pos)    
#define CAN_F8B2_FBC2							CAN_F8B2_FBC2_Msk               /*!< Filter 8 register 2 bit 2 */
#define CAN_F8B2_FBC3_Pos						(3U)                            
#define CAN_F8B2_FBC3_Msk						(0x1UL << CAN_F8B2_FBC3_Pos)    
#define CAN_F8B2_FBC3							CAN_F8B2_FBC3_Msk               /*!< Filter 8 register 2 bit 3 */
#define CAN_F8B2_FBC4_Pos						(4U)                            
#define CAN_F8B2_FBC4_Msk						(0x1UL << CAN_F8B2_FBC4_Pos)    
#define CAN_F8B2_FBC4							CAN_F8B2_FBC4_Msk               /*!< Filter 8 register 2 bit 4 */
#define CAN_F8B2_FBC5_Pos						(5U)                            
#define CAN_F8B2_FBC5_Msk						(0x1UL << CAN_F8B2_FBC5_Pos)    
#define CAN_F8B2_FBC5							CAN_F8B2_FBC5_Msk               /*!< Filter 8 register 2 bit 5 */
#define CAN_F8B2_FBC6_Pos						(6U)                            
#define CAN_F8B2_FBC6_Msk						(0x1UL << CAN_F8B2_FBC6_Pos)    
#define CAN_F8B2_FBC6							CAN_F8B2_FBC6_Msk               /*!< Filter 8 register 2 bit 6 */
#define CAN_F8B2_FBC7_Pos						(7U)                            
#define CAN_F8B2_FBC7_Msk						(0x1UL << CAN_F8B2_FBC7_Pos)    
#define CAN_F8B2_FBC7							CAN_F8B2_FBC7_Msk               /*!< Filter 8 register 2 bit 7 */
#define CAN_F8B2_FBC8_Pos						(8U)                            
#define CAN_F8B2_FBC8_Msk						(0x1UL << CAN_F8B2_FBC8_Pos)    
#define CAN_F8B2_FBC8							CAN_F8B2_FBC8_Msk               /*!< Filter 8 register 2 bit 8 */
#define CAN_F8B2_FBC9_Pos						(9U)                            
#define CAN_F8B2_FBC9_Msk						(0x1UL << CAN_F8B2_FBC9_Pos)    
#define CAN_F8B2_FBC9							CAN_F8B2_FBC9_Msk               /*!< Filter 8 register 2 bit 9 */
#define CAN_F8B2_FBC10_Pos						(10U)                           
#define CAN_F8B2_FBC10_Msk						(0x1UL << CAN_F8B2_FBC10_Pos)   
#define CAN_F8B2_FBC10							CAN_F8B2_FBC10_Msk              /*!< Filter 8 register 2 bit 10 */
#define CAN_F8B2_FBC11_Pos						(11U)                           
#define CAN_F8B2_FBC11_Msk						(0x1UL << CAN_F8B2_FBC11_Pos)   
#define CAN_F8B2_FBC11							CAN_F8B2_FBC11_Msk              /*!< Filter 8 register 2 bit 11 */
#define CAN_F8B2_FBC12_Pos						(12U)                           
#define CAN_F8B2_FBC12_Msk						(0x1UL << CAN_F8B2_FBC12_Pos)   
#define CAN_F8B2_FBC12							CAN_F8B2_FBC12_Msk              /*!< Filter 8 register 2 bit 12 */
#define CAN_F8B2_FBC13_Pos						(13U)                           
#define CAN_F8B2_FBC13_Msk						(0x1UL << CAN_F8B2_FBC13_Pos)   
#define CAN_F8B2_FBC13							CAN_F8B2_FBC13_Msk              /*!< Filter 8 register 2 bit 13 */
#define CAN_F8B2_FBC14_Pos						(14U)                           
#define CAN_F8B2_FBC14_Msk						(0x1UL << CAN_F8B2_FBC14_Pos)   
#define CAN_F8B2_FBC14							CAN_F8B2_FBC14_Msk              /*!< Filter 8 register 2 bit 14 */
#define CAN_F8B2_FBC15_Pos						(15U)                           
#define CAN_F8B2_FBC15_Msk						(0x1UL << CAN_F8B2_FBC15_Pos)   
#define CAN_F8B2_FBC15							CAN_F8B2_FBC15_Msk              /*!< Filter 8 register 2 bit 15 */
#define CAN_F8B2_FBC16_Pos						(16U)                           
#define CAN_F8B2_FBC16_Msk						(0x1UL << CAN_F8B2_FBC16_Pos)   
#define CAN_F8B2_FBC16							CAN_F8B2_FBC16_Msk              /*!< Filter 8 register 2 bit 16 */
#define CAN_F8B2_FBC17_Pos						(17U)                           
#define CAN_F8B2_FBC17_Msk						(0x1UL << CAN_F8B2_FBC17_Pos)   
#define CAN_F8B2_FBC17							CAN_F8B2_FBC17_Msk              /*!< Filter 8 register 2 bit 17 */
#define CAN_F8B2_FBC18_Pos						(18U)                           
#define CAN_F8B2_FBC18_Msk						(0x1UL << CAN_F8B2_FBC18_Pos)   
#define CAN_F8B2_FBC18							CAN_F8B2_FBC18_Msk              /*!< Filter 8 register 2 bit 18 */
#define CAN_F8B2_FBC19_Pos						(19U)                           
#define CAN_F8B2_FBC19_Msk						(0x1UL << CAN_F8B2_FBC19_Pos)   
#define CAN_F8B2_FBC19							CAN_F8B2_FBC19_Msk              /*!< Filter 8 register 2 bit 19 */
#define CAN_F8B2_FBC20_Pos						(20U)                           
#define CAN_F8B2_FBC20_Msk						(0x1UL << CAN_F8B2_FBC20_Pos)   
#define CAN_F8B2_FBC20							CAN_F8B2_FBC20_Msk              /*!< Filter 8 register 2 bit 20 */
#define CAN_F8B2_FBC21_Pos						(21U)                           
#define CAN_F8B2_FBC21_Msk						(0x1UL << CAN_F8B2_FBC21_Pos)   
#define CAN_F8B2_FBC21							CAN_F8B2_FBC21_Msk              /*!< Filter 8 register 2 bit 21 */
#define CAN_F8B2_FBC22_Pos						(22U)                           
#define CAN_F8B2_FBC22_Msk						(0x1UL << CAN_F8B2_FBC22_Pos)   
#define CAN_F8B2_FBC22							CAN_F8B2_FBC22_Msk              /*!< Filter 8 register 2 bit 22 */
#define CAN_F8B2_FBC23_Pos						(23U)                           
#define CAN_F8B2_FBC23_Msk						(0x1UL << CAN_F8B2_FBC23_Pos)   
#define CAN_F8B2_FBC23							CAN_F8B2_FBC23_Msk              /*!< Filter 8 register 2 bit 23 */
#define CAN_F8B2_FBC24_Pos						(24U)                           
#define CAN_F8B2_FBC24_Msk						(0x1UL << CAN_F8B2_FBC24_Pos)   
#define CAN_F8B2_FBC24							CAN_F8B2_FBC24_Msk              /*!< Filter 8 register 2 bit 24 */
#define CAN_F8B2_FBC25_Pos						(25U)                           
#define CAN_F8B2_FBC25_Msk						(0x1UL << CAN_F8B2_FBC25_Pos)   
#define CAN_F8B2_FBC25							CAN_F8B2_FBC25_Msk              /*!< Filter 8 register 2 bit 25 */
#define CAN_F8B2_FBC26_Pos						(26U)                           
#define CAN_F8B2_FBC26_Msk						(0x1UL << CAN_F8B2_FBC26_Pos)   
#define CAN_F8B2_FBC26							CAN_F8B2_FBC26_Msk              /*!< Filter 8 register 2 bit 26 */
#define CAN_F8B2_FBC27_Pos						(27U)                           
#define CAN_F8B2_FBC27_Msk						(0x1UL << CAN_F8B2_FBC27_Pos)   
#define CAN_F8B2_FBC27							CAN_F8B2_FBC27_Msk              /*!< Filter 8 register 2 bit 27 */
#define CAN_F8B2_FBC28_Pos						(28U)                           
#define CAN_F8B2_FBC28_Msk						(0x1UL << CAN_F8B2_FBC28_Pos)   
#define CAN_F8B2_FBC28							CAN_F8B2_FBC28_Msk              /*!< Filter 8 register 2 bit 28 */
#define CAN_F8B2_FBC29_Pos						(29U)                           
#define CAN_F8B2_FBC29_Msk						(0x1UL << CAN_F8B2_FBC29_Pos)   
#define CAN_F8B2_FBC29							CAN_F8B2_FBC29_Msk              /*!< Filter 8 register 2 bit 29 */
#define CAN_F8B2_FBC30_Pos						(30U)                           
#define CAN_F8B2_FBC30_Msk						(0x1UL << CAN_F8B2_FBC30_Pos)   
#define CAN_F8B2_FBC30							CAN_F8B2_FBC30_Msk              /*!< Filter 8 register 2 bit 30 */
#define CAN_F8B2_FBC31_Pos						(31U)                           
#define CAN_F8B2_FBC31_Msk						(0x1UL << CAN_F8B2_FBC31_Pos)   
#define CAN_F8B2_FBC31							CAN_F8B2_FBC31_Msk              /*!< Filter 8 register 2 bit 31 */

/*******************  Bit definition for CAN_F9R2 register  *******************/
#define CAN_F9B2_FBC0_Pos						(0U)
#define CAN_F9B2_FBC0_Msk						(0x1UL << CAN_F9B2_FBC0_Pos)
#define CAN_F9B2_FBC0							CAN_F9B2_FBC0_Msk				/*!< Filter 9 register 2 bit 0 */
#define CAN_F9B2_FBC1_Pos						(1U)                            
#define CAN_F9B2_FBC1_Msk						(0x1UL << CAN_F9B2_FBC1_Pos)    
#define CAN_F9B2_FBC1							CAN_F9B2_FBC1_Msk               /*!< Filter 9 register 2 bit 1 */
#define CAN_F9B2_FBC2_Pos						(2U)                            
#define CAN_F9B2_FBC2_Msk						(0x1UL << CAN_F9B2_FBC2_Pos)    
#define CAN_F9B2_FBC2							CAN_F9B2_FBC2_Msk               /*!< Filter 9 register 2 bit 2 */
#define CAN_F9B2_FBC3_Pos						(3U)                            
#define CAN_F9B2_FBC3_Msk						(0x1UL << CAN_F9B2_FBC3_Pos)    
#define CAN_F9B2_FBC3							CAN_F9B2_FBC3_Msk               /*!< Filter 9 register 2 bit 3 */
#define CAN_F9B2_FBC4_Pos						(4U)                            
#define CAN_F9B2_FBC4_Msk						(0x1UL << CAN_F9B2_FBC4_Pos)    
#define CAN_F9B2_FBC4							CAN_F9B2_FBC4_Msk               /*!< Filter 9 register 2 bit 4 */
#define CAN_F9B2_FBC5_Pos						(5U)                            
#define CAN_F9B2_FBC5_Msk						(0x1UL << CAN_F9B2_FBC5_Pos)    
#define CAN_F9B2_FBC5							CAN_F9B2_FBC5_Msk               /*!< Filter 9 register 2 bit 5 */
#define CAN_F9B2_FBC6_Pos						(6U)                            
#define CAN_F9B2_FBC6_Msk						(0x1UL << CAN_F9B2_FBC6_Pos)    
#define CAN_F9B2_FBC6							CAN_F9B2_FBC6_Msk               /*!< Filter 9 register 2 bit 6 */
#define CAN_F9B2_FBC7_Pos						(7U)                            
#define CAN_F9B2_FBC7_Msk						(0x1UL << CAN_F9B2_FBC7_Pos)    
#define CAN_F9B2_FBC7							CAN_F9B2_FBC7_Msk               /*!< Filter 9 register 2 bit 7 */
#define CAN_F9B2_FBC8_Pos						(8U)                            
#define CAN_F9B2_FBC8_Msk						(0x1UL << CAN_F9B2_FBC8_Pos)    
#define CAN_F9B2_FBC8							CAN_F9B2_FBC8_Msk               /*!< Filter 9 register 2 bit 8 */
#define CAN_F9B2_FBC9_Pos						(9U)                            
#define CAN_F9B2_FBC9_Msk						(0x1UL << CAN_F9B2_FBC9_Pos)    
#define CAN_F9B2_FBC9							CAN_F9B2_FBC9_Msk               /*!< Filter 9 register 2 bit 9 */
#define CAN_F9B2_FBC10_Pos						(10U)                           
#define CAN_F9B2_FBC10_Msk						(0x1UL << CAN_F9B2_FBC10_Pos)   
#define CAN_F9B2_FBC10							CAN_F9B2_FBC10_Msk              /*!< Filter 9 register 2 bit 10 */
#define CAN_F9B2_FBC11_Pos						(11U)                           
#define CAN_F9B2_FBC11_Msk						(0x1UL << CAN_F9B2_FBC11_Pos)   
#define CAN_F9B2_FBC11							CAN_F9B2_FBC11_Msk              /*!< Filter 9 register 2 bit 11 */
#define CAN_F9B2_FBC12_Pos						(12U)                           
#define CAN_F9B2_FBC12_Msk						(0x1UL << CAN_F9B2_FBC12_Pos)   
#define CAN_F9B2_FBC12							CAN_F9B2_FBC12_Msk              /*!< Filter 9 register 2 bit 12 */
#define CAN_F9B2_FBC13_Pos						(13U)                           
#define CAN_F9B2_FBC13_Msk						(0x1UL << CAN_F9B2_FBC13_Pos)   
#define CAN_F9B2_FBC13							CAN_F9B2_FBC13_Msk              /*!< Filter 9 register 2 bit 13 */
#define CAN_F9B2_FBC14_Pos						(14U)                           
#define CAN_F9B2_FBC14_Msk						(0x1UL << CAN_F9B2_FBC14_Pos)   
#define CAN_F9B2_FBC14							CAN_F9B2_FBC14_Msk              /*!< Filter 9 register 2 bit 14 */
#define CAN_F9B2_FBC15_Pos						(15U)                           
#define CAN_F9B2_FBC15_Msk						(0x1UL << CAN_F9B2_FBC15_Pos)   
#define CAN_F9B2_FBC15							CAN_F9B2_FBC15_Msk              /*!< Filter 9 register 2 bit 15 */
#define CAN_F9B2_FBC16_Pos						(16U)                           
#define CAN_F9B2_FBC16_Msk						(0x1UL << CAN_F9B2_FBC16_Pos)   
#define CAN_F9B2_FBC16							CAN_F9B2_FBC16_Msk              /*!< Filter 9 register 2 bit 16 */
#define CAN_F9B2_FBC17_Pos						(17U)                           
#define CAN_F9B2_FBC17_Msk						(0x1UL << CAN_F9B2_FBC17_Pos)   
#define CAN_F9B2_FBC17							CAN_F9B2_FBC17_Msk              /*!< Filter 9 register 2 bit 17 */
#define CAN_F9B2_FBC18_Pos						(18U)                           
#define CAN_F9B2_FBC18_Msk						(0x1UL << CAN_F9B2_FBC18_Pos)   
#define CAN_F9B2_FBC18							CAN_F9B2_FBC18_Msk              /*!< Filter 9 register 2 bit 18 */
#define CAN_F9B2_FBC19_Pos						(19U)                           
#define CAN_F9B2_FBC19_Msk						(0x1UL << CAN_F9B2_FBC19_Pos)   
#define CAN_F9B2_FBC19							CAN_F9B2_FBC19_Msk              /*!< Filter 9 register 2 bit 19 */
#define CAN_F9B2_FBC20_Pos						(20U)                           
#define CAN_F9B2_FBC20_Msk						(0x1UL << CAN_F9B2_FBC20_Pos)   
#define CAN_F9B2_FBC20							CAN_F9B2_FBC20_Msk              /*!< Filter 9 register 2 bit 20 */
#define CAN_F9B2_FBC21_Pos						(21U)                           
#define CAN_F9B2_FBC21_Msk						(0x1UL << CAN_F9B2_FBC21_Pos)   
#define CAN_F9B2_FBC21							CAN_F9B2_FBC21_Msk              /*!< Filter 9 register 2 bit 21 */
#define CAN_F9B2_FBC22_Pos						(22U)                           
#define CAN_F9B2_FBC22_Msk						(0x1UL << CAN_F9B2_FBC22_Pos)   
#define CAN_F9B2_FBC22							CAN_F9B2_FBC22_Msk              /*!< Filter 9 register 2 bit 22 */
#define CAN_F9B2_FBC23_Pos						(23U)                           
#define CAN_F9B2_FBC23_Msk						(0x1UL << CAN_F9B2_FBC23_Pos)   
#define CAN_F9B2_FBC23							CAN_F9B2_FBC23_Msk              /*!< Filter 9 register 2 bit 23 */
#define CAN_F9B2_FBC24_Pos						(24U)                           
#define CAN_F9B2_FBC24_Msk						(0x1UL << CAN_F9B2_FBC24_Pos)   
#define CAN_F9B2_FBC24							CAN_F9B2_FBC24_Msk              /*!< Filter 9 register 2 bit 24 */
#define CAN_F9B2_FBC25_Pos						(25U)                           
#define CAN_F9B2_FBC25_Msk						(0x1UL << CAN_F9B2_FBC25_Pos)   
#define CAN_F9B2_FBC25							CAN_F9B2_FBC25_Msk              /*!< Filter 9 register 2 bit 25 */
#define CAN_F9B2_FBC26_Pos						(26U)                           
#define CAN_F9B2_FBC26_Msk						(0x1UL << CAN_F9B2_FBC26_Pos)   
#define CAN_F9B2_FBC26							CAN_F9B2_FBC26_Msk              /*!< Filter 9 register 2 bit 26 */
#define CAN_F9B2_FBC27_Pos						(27U)                           
#define CAN_F9B2_FBC27_Msk						(0x1UL << CAN_F9B2_FBC27_Pos)   
#define CAN_F9B2_FBC27							CAN_F9B2_FBC27_Msk              /*!< Filter 9 register 2 bit 27 */
#define CAN_F9B2_FBC28_Pos						(28U)                           
#define CAN_F9B2_FBC28_Msk						(0x1UL << CAN_F9B2_FBC28_Pos)   
#define CAN_F9B2_FBC28							CAN_F9B2_FBC28_Msk              /*!< Filter 9 register 2 bit 28 */
#define CAN_F9B2_FBC29_Pos						(29U)                           
#define CAN_F9B2_FBC29_Msk						(0x1UL << CAN_F9B2_FBC29_Pos)   
#define CAN_F9B2_FBC29							CAN_F9B2_FBC29_Msk              /*!< Filter 9 register 2 bit 29 */
#define CAN_F9B2_FBC30_Pos						(30U)                           
#define CAN_F9B2_FBC30_Msk						(0x1UL << CAN_F9B2_FBC30_Pos)   
#define CAN_F9B2_FBC30							CAN_F9B2_FBC30_Msk              /*!< Filter 9 register 2 bit 30 */
#define CAN_F9B2_FBC31_Pos						(31U)                           
#define CAN_F9B2_FBC31_Msk						(0x1UL << CAN_F9B2_FBC31_Pos)   
#define CAN_F9B2_FBC31							CAN_F9B2_FBC31_Msk              /*!< Filter 9 register 2 bit 31 */

/******************  Bit definition for CAN_F10R2 register  *******************/
#define CAN_F10B2_FBC0_Pos						(0U)
#define CAN_F10B2_FBC0_Msk						(0x1UL << CAN_F10B2_FBC0_Pos)
#define CAN_F10B2_FBC0							CAN_F10B2_FBC0_Msk				/*!< Filter 10 register 2 bit 0 */
#define CAN_F10B2_FBC1_Pos						(1U)                            
#define CAN_F10B2_FBC1_Msk						(0x1UL << CAN_F10B2_FBC1_Pos)   
#define CAN_F10B2_FBC1							CAN_F10B2_FBC1_Msk              /*!< Filter 10 register 2 bit 1 */
#define CAN_F10B2_FBC2_Pos						(2U)                            
#define CAN_F10B2_FBC2_Msk						(0x1UL << CAN_F10B2_FBC2_Pos)   
#define CAN_F10B2_FBC2							CAN_F10B2_FBC2_Msk              /*!< Filter 10 register 2 bit 2 */
#define CAN_F10B2_FBC3_Pos						(3U)                            
#define CAN_F10B2_FBC3_Msk						(0x1UL << CAN_F10B2_FBC3_Pos)   
#define CAN_F10B2_FBC3							CAN_F10B2_FBC3_Msk              /*!< Filter 10 register 2 bit 3 */
#define CAN_F10B2_FBC4_Pos						(4U)                            
#define CAN_F10B2_FBC4_Msk						(0x1UL << CAN_F10B2_FBC4_Pos)   
#define CAN_F10B2_FBC4							CAN_F10B2_FBC4_Msk              /*!< Filter 10 register 2 bit 4 */
#define CAN_F10B2_FBC5_Pos						(5U)                            
#define CAN_F10B2_FBC5_Msk						(0x1UL << CAN_F10B2_FBC5_Pos)   
#define CAN_F10B2_FBC5							CAN_F10B2_FBC5_Msk              /*!< Filter 10 register 2 bit 5 */
#define CAN_F10B2_FBC6_Pos						(6U)                            
#define CAN_F10B2_FBC6_Msk						(0x1UL << CAN_F10B2_FBC6_Pos)   
#define CAN_F10B2_FBC6							CAN_F10B2_FBC6_Msk              /*!< Filter 10 register 2 bit 6 */
#define CAN_F10B2_FBC7_Pos						(7U)                            
#define CAN_F10B2_FBC7_Msk						(0x1UL << CAN_F10B2_FBC7_Pos)   
#define CAN_F10B2_FBC7							CAN_F10B2_FBC7_Msk              /*!< Filter 10 register 2 bit 7 */
#define CAN_F10B2_FBC8_Pos						(8U)                            
#define CAN_F10B2_FBC8_Msk						(0x1UL << CAN_F10B2_FBC8_Pos)   
#define CAN_F10B2_FBC8							CAN_F10B2_FBC8_Msk              /*!< Filter 10 register 2 bit 8 */
#define CAN_F10B2_FBC9_Pos						(9U)                            
#define CAN_F10B2_FBC9_Msk						(0x1UL << CAN_F10B2_FBC9_Pos)   
#define CAN_F10B2_FBC9							CAN_F10B2_FBC9_Msk              /*!< Filter 10 register 2 bit 9 */
#define CAN_F10B2_FBC10_Pos						(10U)                           
#define CAN_F10B2_FBC10_Msk						(0x1UL << CAN_F10B2_FBC10_Pos)  
#define CAN_F10B2_FBC10							CAN_F10B2_FBC10_Msk             /*!< Filter 10 register 2 bit 10 */
#define CAN_F10B2_FBC11_Pos						(11U)                           
#define CAN_F10B2_FBC11_Msk						(0x1UL << CAN_F10B2_FBC11_Pos)  
#define CAN_F10B2_FBC11							CAN_F10B2_FBC11_Msk             /*!< Filter 10 register 2 bit 11 */
#define CAN_F10B2_FBC12_Pos						(12U)                           
#define CAN_F10B2_FBC12_Msk						(0x1UL << CAN_F10B2_FBC12_Pos)  
#define CAN_F10B2_FBC12							CAN_F10B2_FBC12_Msk             /*!< Filter 10 register 2 bit 12 */
#define CAN_F10B2_FBC13_Pos						(13U)                           
#define CAN_F10B2_FBC13_Msk						(0x1UL << CAN_F10B2_FBC13_Pos)  
#define CAN_F10B2_FBC13							CAN_F10B2_FBC13_Msk             /*!< Filter 10 register 2 bit 13 */
#define CAN_F10B2_FBC14_Pos						(14U)                           
#define CAN_F10B2_FBC14_Msk						(0x1UL << CAN_F10B2_FBC14_Pos)  
#define CAN_F10B2_FBC14							CAN_F10B2_FBC14_Msk             /*!< Filter 10 register 2 bit 14 */
#define CAN_F10B2_FBC15_Pos						(15U)                           
#define CAN_F10B2_FBC15_Msk						(0x1UL << CAN_F10B2_FBC15_Pos)  
#define CAN_F10B2_FBC15							CAN_F10B2_FBC15_Msk             /*!< Filter 10 register 2 bit 15 */
#define CAN_F10B2_FBC16_Pos						(16U)                           
#define CAN_F10B2_FBC16_Msk						(0x1UL << CAN_F10B2_FBC16_Pos)  
#define CAN_F10B2_FBC16							CAN_F10B2_FBC16_Msk             /*!< Filter 10 register 2 bit 16 */
#define CAN_F10B2_FBC17_Pos						(17U)                           
#define CAN_F10B2_FBC17_Msk						(0x1UL << CAN_F10B2_FBC17_Pos)  
#define CAN_F10B2_FBC17							CAN_F10B2_FBC17_Msk             /*!< Filter 10 register 2 bit 17 */
#define CAN_F10B2_FBC18_Pos						(18U)                           
#define CAN_F10B2_FBC18_Msk						(0x1UL << CAN_F10B2_FBC18_Pos)  
#define CAN_F10B2_FBC18							CAN_F10B2_FBC18_Msk             /*!< Filter 10 register 2 bit 18 */
#define CAN_F10B2_FBC19_Pos						(19U)                           
#define CAN_F10B2_FBC19_Msk						(0x1UL << CAN_F10B2_FBC19_Pos)  
#define CAN_F10B2_FBC19							CAN_F10B2_FBC19_Msk             /*!< Filter 10 register 2 bit 19 */
#define CAN_F10B2_FBC20_Pos						(20U)                           
#define CAN_F10B2_FBC20_Msk						(0x1UL << CAN_F10B2_FBC20_Pos)  
#define CAN_F10B2_FBC20							CAN_F10B2_FBC20_Msk             /*!< Filter 10 register 2 bit 20 */
#define CAN_F10B2_FBC21_Pos						(21U)                           
#define CAN_F10B2_FBC21_Msk						(0x1UL << CAN_F10B2_FBC21_Pos)  
#define CAN_F10B2_FBC21							CAN_F10B2_FBC21_Msk             /*!< Filter 10 register 2 bit 21 */
#define CAN_F10B2_FBC22_Pos						(22U)                           
#define CAN_F10B2_FBC22_Msk						(0x1UL << CAN_F10B2_FBC22_Pos)  
#define CAN_F10B2_FBC22							CAN_F10B2_FBC22_Msk             /*!< Filter 10 register 2 bit 22 */
#define CAN_F10B2_FBC23_Pos						(23U)                           
#define CAN_F10B2_FBC23_Msk						(0x1UL << CAN_F10B2_FBC23_Pos)  
#define CAN_F10B2_FBC23							CAN_F10B2_FBC23_Msk             /*!< Filter 10 register 2 bit 23 */
#define CAN_F10B2_FBC24_Pos						(24U)                           
#define CAN_F10B2_FBC24_Msk						(0x1UL << CAN_F10B2_FBC24_Pos)  
#define CAN_F10B2_FBC24							CAN_F10B2_FBC24_Msk             /*!< Filter 10 register 2 bit 24 */
#define CAN_F10B2_FBC25_Pos						(25U)                           
#define CAN_F10B2_FBC25_Msk						(0x1UL << CAN_F10B2_FBC25_Pos)  
#define CAN_F10B2_FBC25							CAN_F10B2_FBC25_Msk             /*!< Filter 10 register 2 bit 25 */
#define CAN_F10B2_FBC26_Pos						(26U)                           
#define CAN_F10B2_FBC26_Msk						(0x1UL << CAN_F10B2_FBC26_Pos)  
#define CAN_F10B2_FBC26							CAN_F10B2_FBC26_Msk             /*!< Filter 10 register 2 bit 26 */
#define CAN_F10B2_FBC27_Pos						(27U)                           
#define CAN_F10B2_FBC27_Msk						(0x1UL << CAN_F10B2_FBC27_Pos)  
#define CAN_F10B2_FBC27							CAN_F10B2_FBC27_Msk             /*!< Filter 10 register 2 bit 27 */
#define CAN_F10B2_FBC28_Pos						(28U)                           
#define CAN_F10B2_FBC28_Msk						(0x1UL << CAN_F10B2_FBC28_Pos)  
#define CAN_F10B2_FBC28							CAN_F10B2_FBC28_Msk             /*!< Filter 10 register 2 bit 28 */
#define CAN_F10B2_FBC29_Pos						(29U)                           
#define CAN_F10B2_FBC29_Msk						(0x1UL << CAN_F10B2_FBC29_Pos)  
#define CAN_F10B2_FBC29							CAN_F10B2_FBC29_Msk             /*!< Filter 10 register 2 bit 29 */
#define CAN_F10B2_FBC30_Pos						(30U)                           
#define CAN_F10B2_FBC30_Msk						(0x1UL << CAN_F10B2_FBC30_Pos)  
#define CAN_F10B2_FBC30							CAN_F10B2_FBC30_Msk             /*!< Filter 10 register 2 bit 30 */
#define CAN_F10B2_FBC31_Pos						(31U)                           
#define CAN_F10B2_FBC31_Msk						(0x1UL << CAN_F10B2_FBC31_Pos)  
#define CAN_F10B2_FBC31							CAN_F10B2_FBC31_Msk             /*!< Filter 10 register 2 bit 31 */

/******************  Bit definition for CAN_F11R2 register  *******************/
#define CAN_F11B2_FBC0_Pos						(0U)
#define CAN_F11B2_FBC0_Msk						(0x1UL << CAN_F11B2_FBC0_Pos)
#define CAN_F11B2_FBC0							CAN_F11B2_FBC0_Msk				/*!< Filter 11 register 2 bit 0 */
#define CAN_F11B2_FBC1_Pos						(1U)                            
#define CAN_F11B2_FBC1_Msk						(0x1UL << CAN_F11B2_FBC1_Pos)   
#define CAN_F11B2_FBC1							CAN_F11B2_FBC1_Msk              /*!< Filter 11 register 2 bit 1 */
#define CAN_F11B2_FBC2_Pos						(2U)                            
#define CAN_F11B2_FBC2_Msk						(0x1UL << CAN_F11B2_FBC2_Pos)   
#define CAN_F11B2_FBC2							CAN_F11B2_FBC2_Msk              /*!< Filter 11 register 2 bit 2 */
#define CAN_F11B2_FBC3_Pos						(3U)                            
#define CAN_F11B2_FBC3_Msk						(0x1UL << CAN_F11B2_FBC3_Pos)   
#define CAN_F11B2_FBC3							CAN_F11B2_FBC3_Msk              /*!< Filter 11 register 2 bit 3 */
#define CAN_F11B2_FBC4_Pos						(4U)                            
#define CAN_F11B2_FBC4_Msk						(0x1UL << CAN_F11B2_FBC4_Pos)   
#define CAN_F11B2_FBC4							CAN_F11B2_FBC4_Msk              /*!< Filter 11 register 2 bit 4 */
#define CAN_F11B2_FBC5_Pos						(5U)                            
#define CAN_F11B2_FBC5_Msk						(0x1UL << CAN_F11B2_FBC5_Pos)   
#define CAN_F11B2_FBC5							CAN_F11B2_FBC5_Msk              /*!< Filter 11 register 2 bit 5 */
#define CAN_F11B2_FBC6_Pos						(6U)                            
#define CAN_F11B2_FBC6_Msk						(0x1UL << CAN_F11B2_FBC6_Pos)   
#define CAN_F11B2_FBC6							CAN_F11B2_FBC6_Msk              /*!< Filter 11 register 2 bit 6 */
#define CAN_F11B2_FBC7_Pos						(7U)                            
#define CAN_F11B2_FBC7_Msk						(0x1UL << CAN_F11B2_FBC7_Pos)   
#define CAN_F11B2_FBC7							CAN_F11B2_FBC7_Msk              /*!< Filter 11 register 2 bit 7 */
#define CAN_F11B2_FBC8_Pos						(8U)                            
#define CAN_F11B2_FBC8_Msk						(0x1UL << CAN_F11B2_FBC8_Pos)   
#define CAN_F11B2_FBC8							CAN_F11B2_FBC8_Msk              /*!< Filter 11 register 2 bit 8 */
#define CAN_F11B2_FBC9_Pos						(9U)                            
#define CAN_F11B2_FBC9_Msk						(0x1UL << CAN_F11B2_FBC9_Pos)   
#define CAN_F11B2_FBC9							CAN_F11B2_FBC9_Msk              /*!< Filter 11 register 2 bit 9 */
#define CAN_F11B2_FBC10_Pos						(10U)                           
#define CAN_F11B2_FBC10_Msk						(0x1UL << CAN_F11B2_FBC10_Pos)  
#define CAN_F11B2_FBC10							CAN_F11B2_FBC10_Msk             /*!< Filter 11 register 2 bit 10 */
#define CAN_F11B2_FBC11_Pos						(11U)                           
#define CAN_F11B2_FBC11_Msk						(0x1UL << CAN_F11B2_FBC11_Pos)  
#define CAN_F11B2_FBC11							CAN_F11B2_FBC11_Msk             /*!< Filter 11 register 2 bit 11 */
#define CAN_F11B2_FBC12_Pos						(12U)                           
#define CAN_F11B2_FBC12_Msk						(0x1UL << CAN_F11B2_FBC12_Pos)  
#define CAN_F11B2_FBC12							CAN_F11B2_FBC12_Msk             /*!< Filter 11 register 2 bit 12 */
#define CAN_F11B2_FBC13_Pos						(13U)                           
#define CAN_F11B2_FBC13_Msk						(0x1UL << CAN_F11B2_FBC13_Pos)  
#define CAN_F11B2_FBC13							CAN_F11B2_FBC13_Msk             /*!< Filter 11 register 2 bit 13 */
#define CAN_F11B2_FBC14_Pos						(14U)                           
#define CAN_F11B2_FBC14_Msk						(0x1UL << CAN_F11B2_FBC14_Pos)  
#define CAN_F11B2_FBC14							CAN_F11B2_FBC14_Msk             /*!< Filter 11 register 2 bit 14 */
#define CAN_F11B2_FBC15_Pos						(15U)                           
#define CAN_F11B2_FBC15_Msk						(0x1UL << CAN_F11B2_FBC15_Pos)  
#define CAN_F11B2_FBC15							CAN_F11B2_FBC15_Msk             /*!< Filter 11 register 2 bit 15 */
#define CAN_F11B2_FBC16_Pos						(16U)                           
#define CAN_F11B2_FBC16_Msk						(0x1UL << CAN_F11B2_FBC16_Pos)  
#define CAN_F11B2_FBC16							CAN_F11B2_FBC16_Msk             /*!< Filter 11 register 2 bit 16 */
#define CAN_F11B2_FBC17_Pos						(17U)                           
#define CAN_F11B2_FBC17_Msk						(0x1UL << CAN_F11B2_FBC17_Pos)  
#define CAN_F11B2_FBC17							CAN_F11B2_FBC17_Msk             /*!< Filter 11 register 2 bit 17 */
#define CAN_F11B2_FBC18_Pos						(18U)                           
#define CAN_F11B2_FBC18_Msk						(0x1UL << CAN_F11B2_FBC18_Pos)  
#define CAN_F11B2_FBC18							CAN_F11B2_FBC18_Msk             /*!< Filter 11 register 2 bit 18 */
#define CAN_F11B2_FBC19_Pos						(19U)                           
#define CAN_F11B2_FBC19_Msk						(0x1UL << CAN_F11B2_FBC19_Pos)  
#define CAN_F11B2_FBC19							CAN_F11B2_FBC19_Msk             /*!< Filter 11 register 2 bit 19 */
#define CAN_F11B2_FBC20_Pos						(20U)                           
#define CAN_F11B2_FBC20_Msk						(0x1UL << CAN_F11B2_FBC20_Pos)  
#define CAN_F11B2_FBC20							CAN_F11B2_FBC20_Msk             /*!< Filter 11 register 2 bit 20 */
#define CAN_F11B2_FBC21_Pos						(21U)                           
#define CAN_F11B2_FBC21_Msk						(0x1UL << CAN_F11B2_FBC21_Pos)  
#define CAN_F11B2_FBC21							CAN_F11B2_FBC21_Msk             /*!< Filter 11 register 2 bit 21 */
#define CAN_F11B2_FBC22_Pos						(22U)                           
#define CAN_F11B2_FBC22_Msk						(0x1UL << CAN_F11B2_FBC22_Pos)  
#define CAN_F11B2_FBC22							CAN_F11B2_FBC22_Msk             /*!< Filter 11 register 2 bit 22 */
#define CAN_F11B2_FBC23_Pos						(23U)                           
#define CAN_F11B2_FBC23_Msk						(0x1UL << CAN_F11B2_FBC23_Pos)  
#define CAN_F11B2_FBC23							CAN_F11B2_FBC23_Msk             /*!< Filter 11 register 2 bit 23 */
#define CAN_F11B2_FBC24_Pos						(24U)                           
#define CAN_F11B2_FBC24_Msk						(0x1UL << CAN_F11B2_FBC24_Pos)  
#define CAN_F11B2_FBC24							CAN_F11B2_FBC24_Msk             /*!< Filter 11 register 2 bit 24 */
#define CAN_F11B2_FBC25_Pos						(25U)                           
#define CAN_F11B2_FBC25_Msk						(0x1UL << CAN_F11B2_FBC25_Pos)  
#define CAN_F11B2_FBC25							CAN_F11B2_FBC25_Msk             /*!< Filter 11 register 2 bit 25 */
#define CAN_F11B2_FBC26_Pos						(26U)                           
#define CAN_F11B2_FBC26_Msk						(0x1UL << CAN_F11B2_FBC26_Pos)  
#define CAN_F11B2_FBC26							CAN_F11B2_FBC26_Msk             /*!< Filter 11 register 2 bit 26 */
#define CAN_F11B2_FBC27_Pos						(27U)                           
#define CAN_F11B2_FBC27_Msk						(0x1UL << CAN_F11B2_FBC27_Pos)  
#define CAN_F11B2_FBC27							CAN_F11B2_FBC27_Msk             /*!< Filter 11 register 2 bit 27 */
#define CAN_F11B2_FBC28_Pos						(28U)                           
#define CAN_F11B2_FBC28_Msk						(0x1UL << CAN_F11B2_FBC28_Pos)  
#define CAN_F11B2_FBC28							CAN_F11B2_FBC28_Msk             /*!< Filter 11 register 2 bit 28 */
#define CAN_F11B2_FBC29_Pos						(29U)                           
#define CAN_F11B2_FBC29_Msk						(0x1UL << CAN_F11B2_FBC29_Pos)  
#define CAN_F11B2_FBC29							CAN_F11B2_FBC29_Msk             /*!< Filter 11 register 2 bit 29 */
#define CAN_F11B2_FBC30_Pos						(30U)                           
#define CAN_F11B2_FBC30_Msk						(0x1UL << CAN_F11B2_FBC30_Pos)  
#define CAN_F11B2_FBC30							CAN_F11B2_FBC30_Msk             /*!< Filter 11 register 2 bit 30 */
#define CAN_F11B2_FBC31_Pos						(31U)                           
#define CAN_F11B2_FBC31_Msk						(0x1UL << CAN_F11B2_FBC31_Pos)  
#define CAN_F11B2_FBC31							CAN_F11B2_FBC31_Msk             /*!< Filter 11 register 2 bit 31 */

/******************  Bit definition for CAN_F12R2 register  *******************/
#define CAN_F12B2_FBC0_Pos						(0U)
#define CAN_F12B2_FBC0_Msk						(0x1UL << CAN_F12B2_FBC0_Pos)
#define CAN_F12B2_FBC0							CAN_F12B2_FBC0_Msk				/*!< Filter 12 register 2 bit 0 */
#define CAN_F12B2_FBC1_Pos						(1U)                            
#define CAN_F12B2_FBC1_Msk						(0x1UL << CAN_F12B2_FBC1_Pos)   
#define CAN_F12B2_FBC1							CAN_F12B2_FBC1_Msk              /*!< Filter 12 register 2 bit 1 */
#define CAN_F12B2_FBC2_Pos						(2U)                            
#define CAN_F12B2_FBC2_Msk						(0x1UL << CAN_F12B2_FBC2_Pos)   
#define CAN_F12B2_FBC2							CAN_F12B2_FBC2_Msk              /*!< Filter 12 register 2 bit 2 */
#define CAN_F12B2_FBC3_Pos						(3U)                            
#define CAN_F12B2_FBC3_Msk						(0x1UL << CAN_F12B2_FBC3_Pos)   
#define CAN_F12B2_FBC3							CAN_F12B2_FBC3_Msk              /*!< Filter 12 register 2 bit 3 */
#define CAN_F12B2_FBC4_Pos						(4U)                            
#define CAN_F12B2_FBC4_Msk						(0x1UL << CAN_F12B2_FBC4_Pos)   
#define CAN_F12B2_FBC4							CAN_F12B2_FBC4_Msk              /*!< Filter 12 register 2 bit 4 */
#define CAN_F12B2_FBC5_Pos						(5U)                            
#define CAN_F12B2_FBC5_Msk						(0x1UL << CAN_F12B2_FBC5_Pos)   
#define CAN_F12B2_FBC5							CAN_F12B2_FBC5_Msk              /*!< Filter 12 register 2 bit 5 */
#define CAN_F12B2_FBC6_Pos						(6U)                            
#define CAN_F12B2_FBC6_Msk						(0x1UL << CAN_F12B2_FBC6_Pos)   
#define CAN_F12B2_FBC6							CAN_F12B2_FBC6_Msk              /*!< Filter 12 register 2 bit 6 */
#define CAN_F12B2_FBC7_Pos						(7U)                            
#define CAN_F12B2_FBC7_Msk						(0x1UL << CAN_F12B2_FBC7_Pos)   
#define CAN_F12B2_FBC7							CAN_F12B2_FBC7_Msk              /*!< Filter 12 register 2 bit 7 */
#define CAN_F12B2_FBC8_Pos						(8U)                            
#define CAN_F12B2_FBC8_Msk						(0x1UL << CAN_F12B2_FBC8_Pos)   
#define CAN_F12B2_FBC8							CAN_F12B2_FBC8_Msk              /*!< Filter 12 register 2 bit 8 */
#define CAN_F12B2_FBC9_Pos						(9U)                            
#define CAN_F12B2_FBC9_Msk						(0x1UL << CAN_F12B2_FBC9_Pos)   
#define CAN_F12B2_FBC9							CAN_F12B2_FBC9_Msk              /*!< Filter 12 register 2 bit 9 */
#define CAN_F12B2_FBC10_Pos						(10U)                           
#define CAN_F12B2_FBC10_Msk						(0x1UL << CAN_F12B2_FBC10_Pos)  
#define CAN_F12B2_FBC10							CAN_F12B2_FBC10_Msk             /*!< Filter 12 register 2 bit 10 */
#define CAN_F12B2_FBC11_Pos						(11U)                           
#define CAN_F12B2_FBC11_Msk						(0x1UL << CAN_F12B2_FBC11_Pos)  
#define CAN_F12B2_FBC11							CAN_F12B2_FBC11_Msk             /*!< Filter 12 register 2 bit 11 */
#define CAN_F12B2_FBC12_Pos						(12U)                           
#define CAN_F12B2_FBC12_Msk						(0x1UL << CAN_F12B2_FBC12_Pos)  
#define CAN_F12B2_FBC12							CAN_F12B2_FBC12_Msk             /*!< Filter 12 register 2 bit 12 */
#define CAN_F12B2_FBC13_Pos						(13U)                           
#define CAN_F12B2_FBC13_Msk						(0x1UL << CAN_F12B2_FBC13_Pos)  
#define CAN_F12B2_FBC13							CAN_F12B2_FBC13_Msk             /*!< Filter 12 register 2 bit 13 */
#define CAN_F12B2_FBC14_Pos						(14U)                           
#define CAN_F12B2_FBC14_Msk						(0x1UL << CAN_F12B2_FBC14_Pos)  
#define CAN_F12B2_FBC14							CAN_F12B2_FBC14_Msk             /*!< Filter 12 register 2 bit 14 */
#define CAN_F12B2_FBC15_Pos						(15U)                           
#define CAN_F12B2_FBC15_Msk						(0x1UL << CAN_F12B2_FBC15_Pos)  
#define CAN_F12B2_FBC15							CAN_F12B2_FBC15_Msk             /*!< Filter 12 register 2 bit 15 */
#define CAN_F12B2_FBC16_Pos						(16U)                           
#define CAN_F12B2_FBC16_Msk						(0x1UL << CAN_F12B2_FBC16_Pos)  
#define CAN_F12B2_FBC16							CAN_F12B2_FBC16_Msk             /*!< Filter 12 register 2 bit 16 */
#define CAN_F12B2_FBC17_Pos						(17U)                           
#define CAN_F12B2_FBC17_Msk						(0x1UL << CAN_F12B2_FBC17_Pos)  
#define CAN_F12B2_FBC17							CAN_F12B2_FBC17_Msk             /*!< Filter 12 register 2 bit 17 */
#define CAN_F12B2_FBC18_Pos						(18U)                           
#define CAN_F12B2_FBC18_Msk						(0x1UL << CAN_F12B2_FBC18_Pos)  
#define CAN_F12B2_FBC18							CAN_F12B2_FBC18_Msk             /*!< Filter 12 register 2 bit 18 */
#define CAN_F12B2_FBC19_Pos						(19U)                           
#define CAN_F12B2_FBC19_Msk						(0x1UL << CAN_F12B2_FBC19_Pos)  
#define CAN_F12B2_FBC19							CAN_F12B2_FBC19_Msk             /*!< Filter 12 register 2 bit 19 */
#define CAN_F12B2_FBC20_Pos						(20U)                           
#define CAN_F12B2_FBC20_Msk						(0x1UL << CAN_F12B2_FBC20_Pos)  
#define CAN_F12B2_FBC20							CAN_F12B2_FBC20_Msk             /*!< Filter 12 register 2 bit 20 */
#define CAN_F12B2_FBC21_Pos						(21U)                           
#define CAN_F12B2_FBC21_Msk						(0x1UL << CAN_F12B2_FBC21_Pos)  
#define CAN_F12B2_FBC21							CAN_F12B2_FBC21_Msk             /*!< Filter 12 register 2 bit 21 */
#define CAN_F12B2_FBC22_Pos						(22U)                           
#define CAN_F12B2_FBC22_Msk						(0x1UL << CAN_F12B2_FBC22_Pos)  
#define CAN_F12B2_FBC22							CAN_F12B2_FBC22_Msk             /*!< Filter 12 register 2 bit 22 */
#define CAN_F12B2_FBC23_Pos						(23U)                           
#define CAN_F12B2_FBC23_Msk						(0x1UL << CAN_F12B2_FBC23_Pos)  
#define CAN_F12B2_FBC23							CAN_F12B2_FBC23_Msk             /*!< Filter 12 register 2 bit 23 */
#define CAN_F12B2_FBC24_Pos						(24U)                           
#define CAN_F12B2_FBC24_Msk						(0x1UL << CAN_F12B2_FBC24_Pos)  
#define CAN_F12B2_FBC24							CAN_F12B2_FBC24_Msk             /*!< Filter 12 register 2 bit 24 */
#define CAN_F12B2_FBC25_Pos						(25U)                           
#define CAN_F12B2_FBC25_Msk						(0x1UL << CAN_F12B2_FBC25_Pos)  
#define CAN_F12B2_FBC25							CAN_F12B2_FBC25_Msk             /*!< Filter 12 register 2 bit 25 */
#define CAN_F12B2_FBC26_Pos						(26U)                           
#define CAN_F12B2_FBC26_Msk						(0x1UL << CAN_F12B2_FBC26_Pos)  
#define CAN_F12B2_FBC26							CAN_F12B2_FBC26_Msk             /*!< Filter 12 register 2 bit 26 */
#define CAN_F12B2_FBC27_Pos						(27U)                           
#define CAN_F12B2_FBC27_Msk						(0x1UL << CAN_F12B2_FBC27_Pos)  
#define CAN_F12B2_FBC27							CAN_F12B2_FBC27_Msk             /*!< Filter 12 register 2 bit 27 */
#define CAN_F12B2_FBC28_Pos						(28U)                           
#define CAN_F12B2_FBC28_Msk						(0x1UL << CAN_F12B2_FBC28_Pos)  
#define CAN_F12B2_FBC28							CAN_F12B2_FBC28_Msk             /*!< Filter 12 register 2 bit 28 */
#define CAN_F12B2_FBC29_Pos						(29U)                           
#define CAN_F12B2_FBC29_Msk						(0x1UL << CAN_F12B2_FBC29_Pos)  
#define CAN_F12B2_FBC29							CAN_F12B2_FBC29_Msk             /*!< Filter 12 register 2 bit 29 */
#define CAN_F12B2_FBC30_Pos						(30U)                           
#define CAN_F12B2_FBC30_Msk						(0x1UL << CAN_F12B2_FBC30_Pos)  
#define CAN_F12B2_FBC30							CAN_F12B2_FBC30_Msk             /*!< Filter 12 register 2 bit 30 */
#define CAN_F12B2_FBC31_Pos						(31U)                           
#define CAN_F12B2_FBC31_Msk						(0x1UL << CAN_F12B2_FBC31_Pos)  
#define CAN_F12B2_FBC31							CAN_F12B2_FBC31_Msk             /*!< Filter 12 register 2 bit 31 */

/******************  Bit definition for CAN_F13R2 register  *******************/
#define CAN_F13B2_FBC0_Pos						(0U)
#define CAN_F13B2_FBC0_Msk						(0x1UL << CAN_F13B2_FBC0_Pos)
#define CAN_F13B2_FBC0							CAN_F13B2_FBC0_Msk				/*!< Filter 13 register 2 bit 0 */
#define CAN_F13B2_FBC1_Pos						(1U)                            
#define CAN_F13B2_FBC1_Msk						(0x1UL << CAN_F13B2_FBC1_Pos)   
#define CAN_F13B2_FBC1							CAN_F13B2_FBC1_Msk              /*!< Filter 13 register 2 bit 1 */
#define CAN_F13B2_FBC2_Pos						(2U)                            
#define CAN_F13B2_FBC2_Msk						(0x1UL << CAN_F13B2_FBC2_Pos)   
#define CAN_F13B2_FBC2							CAN_F13B2_FBC2_Msk              /*!< Filter 13 register 2 bit 2 */
#define CAN_F13B2_FBC3_Pos						(3U)                            
#define CAN_F13B2_FBC3_Msk						(0x1UL << CAN_F13B2_FBC3_Pos)   
#define CAN_F13B2_FBC3							CAN_F13B2_FBC3_Msk              /*!< Filter 13 register 2 bit 3 */
#define CAN_F13B2_FBC4_Pos						(4U)                            
#define CAN_F13B2_FBC4_Msk						(0x1UL << CAN_F13B2_FBC4_Pos)   
#define CAN_F13B2_FBC4							CAN_F13B2_FBC4_Msk              /*!< Filter 13 register 2 bit 4 */
#define CAN_F13B2_FBC5_Pos						(5U)                            
#define CAN_F13B2_FBC5_Msk						(0x1UL << CAN_F13B2_FBC5_Pos)   
#define CAN_F13B2_FBC5							CAN_F13B2_FBC5_Msk              /*!< Filter 13 register 2 bit 5 */
#define CAN_F13B2_FBC6_Pos						(6U)                            
#define CAN_F13B2_FBC6_Msk						(0x1UL << CAN_F13B2_FBC6_Pos)   
#define CAN_F13B2_FBC6							CAN_F13B2_FBC6_Msk              /*!< Filter 13 register 2 bit 6 */
#define CAN_F13B2_FBC7_Pos						(7U)                            
#define CAN_F13B2_FBC7_Msk						(0x1UL << CAN_F13B2_FBC7_Pos)   
#define CAN_F13B2_FBC7							CAN_F13B2_FBC7_Msk              /*!< Filter 13 register 2 bit 7 */
#define CAN_F13B2_FBC8_Pos						(8U)                            
#define CAN_F13B2_FBC8_Msk						(0x1UL << CAN_F13B2_FBC8_Pos)   
#define CAN_F13B2_FBC8							CAN_F13B2_FBC8_Msk              /*!< Filter 13 register 2 bit 8 */
#define CAN_F13B2_FBC9_Pos						(9U)                            
#define CAN_F13B2_FBC9_Msk						(0x1UL << CAN_F13B2_FBC9_Pos)   
#define CAN_F13B2_FBC9							CAN_F13B2_FBC9_Msk              /*!< Filter 13 register 2 bit 9 */
#define CAN_F13B2_FBC10_Pos						(10U)                           
#define CAN_F13B2_FBC10_Msk						(0x1UL << CAN_F13B2_FBC10_Pos)  
#define CAN_F13B2_FBC10							CAN_F13B2_FBC10_Msk             /*!< Filter 13 register 2 bit 10 */
#define CAN_F13B2_FBC11_Pos						(11U)                           
#define CAN_F13B2_FBC11_Msk						(0x1UL << CAN_F13B2_FBC11_Pos)  
#define CAN_F13B2_FBC11							CAN_F13B2_FBC11_Msk             /*!< Filter 13 register 2 bit 11 */
#define CAN_F13B2_FBC12_Pos						(12U)                           
#define CAN_F13B2_FBC12_Msk						(0x1UL << CAN_F13B2_FBC12_Pos)  
#define CAN_F13B2_FBC12							CAN_F13B2_FBC12_Msk             /*!< Filter 13 register 2 bit 12 */
#define CAN_F13B2_FBC13_Pos						(13U)                           
#define CAN_F13B2_FBC13_Msk						(0x1UL << CAN_F13B2_FBC13_Pos)  
#define CAN_F13B2_FBC13							CAN_F13B2_FBC13_Msk             /*!< Filter 13 register 2 bit 13 */
#define CAN_F13B2_FBC14_Pos						(14U)                           
#define CAN_F13B2_FBC14_Msk						(0x1UL << CAN_F13B2_FBC14_Pos)  
#define CAN_F13B2_FBC14							CAN_F13B2_FBC14_Msk             /*!< Filter 13 register 2 bit 14 */
#define CAN_F13B2_FBC15_Pos						(15U)                           
#define CAN_F13B2_FBC15_Msk						(0x1UL << CAN_F13B2_FBC15_Pos)  
#define CAN_F13B2_FBC15							CAN_F13B2_FBC15_Msk             /*!< Filter 13 register 2 bit 15 */
#define CAN_F13B2_FBC16_Pos						(16U)                           
#define CAN_F13B2_FBC16_Msk						(0x1UL << CAN_F13B2_FBC16_Pos)  
#define CAN_F13B2_FBC16							CAN_F13B2_FBC16_Msk             /*!< Filter 13 register 2 bit 16 */
#define CAN_F13B2_FBC17_Pos						(17U)                           
#define CAN_F13B2_FBC17_Msk						(0x1UL << CAN_F13B2_FBC17_Pos)  
#define CAN_F13B2_FBC17							CAN_F13B2_FBC17_Msk             /*!< Filter 13 register 2 bit 17 */
#define CAN_F13B2_FBC18_Pos						(18U)                           
#define CAN_F13B2_FBC18_Msk						(0x1UL << CAN_F13B2_FBC18_Pos)  
#define CAN_F13B2_FBC18							CAN_F13B2_FBC18_Msk             /*!< Filter 13 register 2 bit 18 */
#define CAN_F13B2_FBC19_Pos						(19U)                           
#define CAN_F13B2_FBC19_Msk						(0x1UL << CAN_F13B2_FBC19_Pos)  
#define CAN_F13B2_FBC19							CAN_F13B2_FBC19_Msk             /*!< Filter 13 register 2 bit 19 */
#define CAN_F13B2_FBC20_Pos						(20U)                           
#define CAN_F13B2_FBC20_Msk						(0x1UL << CAN_F13B2_FBC20_Pos)  
#define CAN_F13B2_FBC20							CAN_F13B2_FBC20_Msk             /*!< Filter 13 register 2 bit 20 */
#define CAN_F13B2_FBC21_Pos						(21U)                           
#define CAN_F13B2_FBC21_Msk						(0x1UL << CAN_F13B2_FBC21_Pos)  
#define CAN_F13B2_FBC21							CAN_F13B2_FBC21_Msk             /*!< Filter 13 register 2 bit 21 */
#define CAN_F13B2_FBC22_Pos						(22U)                           
#define CAN_F13B2_FBC22_Msk						(0x1UL << CAN_F13B2_FBC22_Pos)  
#define CAN_F13B2_FBC22							CAN_F13B2_FBC22_Msk             /*!< Filter 13 register 2 bit 22 */
#define CAN_F13B2_FBC23_Pos						(23U)                           
#define CAN_F13B2_FBC23_Msk						(0x1UL << CAN_F13B2_FBC23_Pos)  
#define CAN_F13B2_FBC23							CAN_F13B2_FBC23_Msk             /*!< Filter 13 register 2 bit 23 */
#define CAN_F13B2_FBC24_Pos						(24U)                           
#define CAN_F13B2_FBC24_Msk						(0x1UL << CAN_F13B2_FBC24_Pos)  
#define CAN_F13B2_FBC24							CAN_F13B2_FBC24_Msk             /*!< Filter 13 register 2 bit 24 */
#define CAN_F13B2_FBC25_Pos						(25U)                           
#define CAN_F13B2_FBC25_Msk						(0x1UL << CAN_F13B2_FBC25_Pos)  
#define CAN_F13B2_FBC25							CAN_F13B2_FBC25_Msk             /*!< Filter 13 register 2 bit 25 */
#define CAN_F13B2_FBC26_Pos						(26U)                           
#define CAN_F13B2_FBC26_Msk						(0x1UL << CAN_F13B2_FBC26_Pos)  
#define CAN_F13B2_FBC26							CAN_F13B2_FBC26_Msk             /*!< Filter 13 register 2 bit 26 */
#define CAN_F13B2_FBC27_Pos						(27U)                           
#define CAN_F13B2_FBC27_Msk						(0x1UL << CAN_F13B2_FBC27_Pos)  
#define CAN_F13B2_FBC27							CAN_F13B2_FBC27_Msk             /*!< Filter 13 register 2 bit 27 */
#define CAN_F13B2_FBC28_Pos						(28U)                           
#define CAN_F13B2_FBC28_Msk						(0x1UL << CAN_F13B2_FBC28_Pos)  
#define CAN_F13B2_FBC28							CAN_F13B2_FBC28_Msk             /*!< Filter 13 register 2 bit 28 */
#define CAN_F13B2_FBC29_Pos						(29U)                           
#define CAN_F13B2_FBC29_Msk						(0x1UL << CAN_F13B2_FBC29_Pos)  
#define CAN_F13B2_FBC29							CAN_F13B2_FBC29_Msk             /*!< Filter 13 register 2 bit 29 */
#define CAN_F13B2_FBC30_Pos						(30U)                           
#define CAN_F13B2_FBC30_Msk						(0x1UL << CAN_F13B2_FBC30_Pos)  
#define CAN_F13B2_FBC30							CAN_F13B2_FBC30_Msk             /*!< Filter 13 register 2 bit 30 */
#define CAN_F13B2_FBC31_Pos						(31U)                           
#define CAN_F13B2_FBC31_Msk						(0x1UL << CAN_F13B2_FBC31_Pos)  
#define CAN_F13B2_FBC31							CAN_F13B2_FBC31_Msk             /*!< Filter 13 register 2 bit 31 */

/******************************************************************************/
/*                                                                            */
/*                        Serial Peripheral Interface                         */
/*                                                                            */
/******************************************************************************/
/******************  Bit definition for SPI_CTRL1 register  *******************/
#define SPI_CTRL1_CLKPHA_Pos					(0U)
#define SPI_CTRL1_CLKPHA_Msk					(0x1UL << SPI_CTRL1_CLKPHA_Pos)		/*!< 0x00000001 */	
#define SPI_CTRL1_CLKPHA						SPI_CTRL1_CLKPHA_Msk			/*!< Clock Phase */
#define SPI_CTRL1_CLKPOL_Pos					(1U)
#define SPI_CTRL1_CLKPOL_Msk					(0x1UL << SPI_CTRL1_CLKPOL_Pos)		/*!< 0x00000002 */
#define SPI_CTRL1_CLKPOL						SPI_CTRL1_CLKPOL_Msk			/*!< Clock Polarity */
#define SPI_CTRL1_MSEL_Pos						(2U)
#define SPI_CTRL1_MSEL_Msk						(0x1UL << SPI_CTRL1_MSEL_Pos)		/*!< 0x00000004 */
#define SPI_CTRL1_MSEL							SPI_CTRL1_MSEL_Msk				/*!< Master Selection */

#define SPI_CTRL1_BR_Pos						(3U)
#define SPI_CTRL1_BR_Msk						(0x7UL << SPI_CTRL1_BR_Pos)			/*!< 0x00000038 */
#define SPI_CTRL1_BR							SPI_CTRL1_BR_Msk				/*!< BR[2:0] bits (Baud Rate Control) */
#define SPI_CTRL1_BR_0							((uint16_t) 0x0008)				/*!< Bit 0 */
#define SPI_CTRL1_BR_1							((uint16_t) 0x0010)				/*!< Bit 1 */
#define SPI_CTRL1_BR_2							((uint16_t) 0x0020)				/*!< Bit 2 */

#define SPI_CTRL1_SPIEN_Pos						(6U)
#define SPI_CTRL1_SPIEN_Msk						(0x1UL << SPI_CTRL1_SPIEN_Pos)		/*!< 0x00000040 */
#define SPI_CTRL1_SPIEN							SPI_CTRL1_SPIEN_Msk				/*!< SPI Enable */
#define SPI_CTRL1_LSBFF_Pos						(7U)
#define SPI_CTRL1_LSBFF_Msk						(0x1UL << SPI_CTRL1_LSBFF_Pos)		/*!< 0x00000080 */
#define SPI_CTRL1_LSBFF							SPI_CTRL1_LSBFF_Msk				/*!< Frame Format */
#define SPI_CTRL1_SSEL_Pos						(8U)
#define SPI_CTRL1_SSEL_Msk						(0x1UL << SPI_CTRL1_SSEL_Pos)		/*!< 0x00000100 */
#define SPI_CTRL1_SSEL							SPI_CTRL1_SSEL_Msk				/*!< Internal slave select */
#define SPI_CTRL1_SSMEN_Pos						(9U)
#define SPI_CTRL1_SSMEN_Msk						(0x1UL << SPI_CTRL1_SSMEN_Pos)		/*!< 0x00000200 */
#define SPI_CTRL1_SSMEN							SPI_CTRL1_SSMEN_Msk				/*!< Software slave management */
#define SPI_CTRL1_RONLY_Pos						(10U)
#define SPI_CTRL1_RONLY_Msk						(0x1UL << SPI_CTRL1_RONLY_Pos)		/*!< 0x00000400 */
#define SPI_CTRL1_RONLY							SPI_CTRL1_RONLY_Msk				/*!< Receive only */
#define SPI_CTRL1_DATFF_Pos						(11U)
#define SPI_CTRL1_DATFF_Msk						(0x1UL << SPI_CTRL1_DATFF_Pos)		/*!< 0x00000800 */
#define SPI_CTRL1_DATFF							SPI_CTRL1_DATFF_Msk				/*!< Data Frame Format */
#define SPI_CTRL1_CRCNEXT_Pos					(12U)
#define SPI_CTRL1_CRCNEXT_Msk					(0x1UL << SPI_CTRL1_CRCNEXT_Pos)	/*!< 0x00001000 */
#define SPI_CTRL1_CRCNEXT						SPI_CTRL1_CRCNEXT_Msk			/*!< Transmit CRC next */
#define SPI_CTRL1_CRCEN_Pos						(13U)
#define SPI_CTRL1_CRCEN_Msk						(0x1UL << SPI_CTRL1_CRCEN_Pos)		/*!< 0x00002000 */
#define SPI_CTRL1_CRCEN							SPI_CTRL1_CRCEN_Msk				/*!< Hardware CRC calculation enable */
#define SPI_CTRL1_BIDIROEN_Pos					(14U)
#define SPI_CTRL1_BIDIROEN_Msk					(0x1UL << SPI_CTRL1_BIDIROEN_Pos)	/*!< 0x00004000 */
#define SPI_CTRL1_BIDIROEN						SPI_CTRL1_BIDIROEN_Msk			/*!< Output enable in bidirectional mode */
#define SPI_CTRL1_BIDIRMODE_Pos					(15U)
#define SPI_CTRL1_BIDIRMODE_Msk					(0x1UL << SPI_CTRL1_BIDIRMODE_Pos)	/*!< 0x00008000 */
#define SPI_CTRL1_BIDIRMODE						SPI_CTRL1_BIDIRMODE_Msk			/*!< Bidirectional data mode enable */

/******************  Bit definition for SPI_CTRL2 register  *******************/
#define SPI_CTRL2_RDMAEN_Pos					(0U)
#define SPI_CTRL2_RDMAEN_Msk					(0x1UL << SPI_CTRL2_RDMAEN_Pos)		/*!< 0x00000001 */
#define SPI_CTRL2_RDMAEN						SPI_CTRL2_RDMAEN_Msk			/*!< Rx Buffer DMA Enable */
#define SPI_CTRL2_TDMAEN_Pos					(1U)
#define SPI_CTRL2_TDMAEN_Msk					(0x1UL << SPI_CTRL2_TDMAEN_Pos)		/*!< 0x00000002 */
#define SPI_CTRL2_TDMAEN						SPI_CTRL2_TDMAEN_Msk			/*!< Tx Buffer DMA Enable */
#define SPI_CTRL2_SSOEN_Pos						(2U)
#define SPI_CTRL2_SSOEN_Msk						(0x1UL << SPI_CTRL2_SSOEN_Pos)		/*!< 0x00000004 */
#define SPI_CTRL2_SSOEN							SPI_CTRL2_SSOEN_Msk				/*!< SS Output Enable */
#define SPI_CTRL2_ERRINTEN_Pos					(5U)
#define SPI_CTRL2_ERRINTEN_Msk					(0x1UL << SPI_CTRL2_ERRINTEN_Pos)	/*!< 0x00000020 */
#define SPI_CTRL2_ERRINTEN						SPI_CTRL2_ERRINTEN_Msk			/*!< Error Interrupt Enable */
#define SPI_CTRL2_RNEINTEN_Pos					(6U)
#define SPI_CTRL2_RNEINTEN_Msk					(0x1UL << SPI_CTRL2_RNEINTEN_Pos)	/*!< 0x00000040 */
#define SPI_CTRL2_RNEINTEN						SPI_CTRL2_RNEINTEN_Msk			/*!< RX buffer Not Empty Interrupt Enable */
#define SPI_CTRL2_TEINTEN_Pos					(7U)
#define SPI_CTRL2_TEINTEN_Msk					(0x1UL << SPI_CTRL2_TEINTEN_Pos)	/*!< 0x00000080 */
#define SPI_CTRL2_TEINTEN						SPI_CTRL2_TEINTEN_Msk			/*!< Tx buffer Empty Interrupt Enable */

/*******************  Bit definition for SPI_STS register  ********************/
#define SPI_STS_RNE_Pos							(0U)
#define SPI_STS_RNE_Msk							(0x1UL << SPI_STS_RNE_Pos)		/*!< 0x00000001 */
#define SPI_STS_RNE								SPI_STS_RNE_Msk					/*!< Receive buffer Not Empty */
#define SPI_STS_TE_Pos							(1U)
#define SPI_STS_TE_Msk							(0x1UL << SPI_STS_TE_Pos)		/*!< 0x00000002 */
#define SPI_STS_TE								SPI_STS_TE_Msk					/*!< Transmit buffer Empty */
#define SPI_STS_CHSIDE_Pos						(2U)
#define SPI_STS_CHSIDE_Msk						(0x1UL << SPI_STS_CHSIDE_Pos)	/*!< 0x00000004 */
#define SPI_STS_CHSIDE							SPI_STS_CHSIDE_Msk				/*!< Channel side */
#define SPI_STS_UNDER_Pos						(3U)
#define SPI_STS_UNDER_Msk						(0x1UL << SPI_STS_UNDER_Pos)	/*!< 0x00000008 */
#define SPI_STS_UNDER							SPI_STS_UNDER_Msk				/*!< Underrun flag */
#define SPI_STS_CRCERR_Pos						(4U)
#define SPI_STS_CRCERR_Msk						(0x1UL << SPI_STS_CRCERR_Pos)	/*!< 0x00000010 */
#define SPI_STS_CRCERR							SPI_STS_CRCERR_Msk				/*!< CRC Error flag */
#define SPI_STS_MODERR_Pos						(5U)
#define SPI_STS_MODERR_Msk						(0x1UL << SPI_STS_MODERR_Pos)	/*!< 0x00000020 */
#define SPI_STS_MODERR							SPI_STS_MODERR_Msk				/*!< Mode fault */
#define SPI_STS_OVER_Pos						(6U)
#define SPI_STS_OVER_Msk						(0x1UL << SPI_STS_OVER_Pos)		/*!< 0x00000040 */
#define SPI_STS_OVER							SPI_STS_OVER_Msk				/*!< Overrun flag */
#define SPI_STS_BUSY_Pos						(7U)
#define SPI_STS_BUSY_Msk						(0x1UL << SPI_STS_BUSY_Pos)		/*!< 0x00000080 */
#define SPI_STS_BUSY							SPI_STS_BUSY_Msk				/*!< Busy flag */

/*******************  Bit definition for SPI_DAT register  ********************/
#define SPI_DAT_DAT_Pos							(0U)
#define SPI_DAT_DAT_Msk							(0xFFFFUL << SPI_DAT_DAT_Pos)	/*!< 0x0000FFFF */
#define SPI_DAT_DAT								SPI_DAT_DAT_Msk					/*!< Data Register */

/*****************  Bit definition for SPI_CRCPOLY register  ******************/
#define SPI_CRCPOLY_CRCPOLY_Pos					(0U)
#define SPI_CRCPOLY_CRCPOLY_Msk					(0xFFFFUL << SPI_CRCPOLY_CRCPOLY_Pos)	/*!< 0x0000FFFF */
#define SPI_CRCPOLY_CRCPOLY						SPI_CRCPOLY_CRCPOLY_Msk			/*!< CRC polynomial register */

/*****************  Bit definition for SPI_CRCRDAT register  ******************/
#define SPI_CRCRDAT_CRCRDAT_Pos					(0U)
#define SPI_CRCRDAT_CRCRDAT_Msk					(0xFFFFUL << SPI_CRCRDAT_CRCRDAT_Pos)	/*!< 0x0000FFFF */
#define SPI_CRCRDAT_CRCRDAT						SPI_CRCRDAT_CRCRDAT_Msk			/*!< Rx CRC Register */

/*****************  Bit definition for SPI_CRCTDAT register  ******************/
#define SPI_CRCTDAT_CRCTDAT_Pos					(0U)
#define SPI_CRCTDAT_CRCTDAT_Msk					(0xFFFFUL << SPI_CRCTDAT_CRCTDAT_Pos)	/*!< 0x0000FFFF */
#define SPI_CRCTDAT_CRCTDAT						SPI_CRCTDAT_CRCTDAT_Msk			/*!< Tx CRC Register */

/******************  Bit definition for SPI_I2SCFG register  ******************/
#define SPI_I2SCFG_CHBITS_Pos					(0U)
#define SPI_I2SCFG_CHBITS_Msk					(0x1UL << SPI_I2SCFG_CHBITS_Pos)	/*!< 0x00000001 */
#define SPI_I2SCFG_CHBITS						SPI_I2SCFG_CHBITS_Msk			/*!< Channel length (number of bits per audio channel) */

#define SPI_I2SCFG_TDATLEN_Pos					(1U)
#define SPI_I2SCFG_TDATLEN_Msk					(0x3UL << SPI_I2SCFG_TDATLEN_Pos)	/*!< 0x00000006 */
#define SPI_I2SCFG_TDATLEN						SPI_I2SCFG_TDATLEN_Msk			/*!< TDATLEN[1:0] bits (Data length to be transferred) */
#define SPI_I2SCFG_TDATLEN0						((uint16_t) 0x0002)				/*!< Bit 0 */
#define SPI_I2SCFG_TDATLEN1						((uint16_t) 0x0004)				/*!< Bit 1 */

#define SPI_I2SCFG_CLKPOL_Pos					(3U)
#define SPI_I2SCFG_CLKPOL_Msk					(0x1UL << SPI_I2SCFG_CLKPOL_Pos)	/*!< 0x00000008 */
#define SPI_I2SCFG_CLKPOL						SPI_I2SCFG_CLKPOL_Msk			/*!< steady state clock polarity */

#define SPI_I2SCFG_STDSEL_Pos					(4U)
#define SPI_I2SCFG_STDSEL_Msk					(0x3UL << SPI_I2SCFG_STDSEL_Pos)	/*!< 0x00000030 */
#define SPI_I2SCFG_STDSEL						SPI_I2SCFG_STDSEL_Msk			/*!< STDSEL[1:0] bits (I2S standard selection) */
#define SPI_I2SCFG_STDSEL0						((uint16_t) 0x0010)				/*!< Bit 0 */
#define SPI_I2SCFG_STDSEL1						((uint16_t) 0x0020)				/*!< Bit 1 */

#define SPI_I2SCFG_PCMFSYNC_Pos					(7U)
#define SPI_I2SCFG_PCMFSYNC_Msk					(0x1UL << SPI_I2SCFG_PCMFSYNC_Pos)	/*!< 0x00000080 */
#define SPI_I2SCFG_PCMFSYNC						SPI_I2SCFG_PCMFSYNC_Msk			/*!< PCM frame synchronization */

#define SPI_I2SCFG_MODCFG_Pos					(8U)
#define SPI_I2SCFG_MODCFG_Msk					(0x3UL << SPI_I2SCFG_MODCFG_Pos)	/*!< 0x00000300 */
#define SPI_I2SCFG_MODCFG						SPI_I2SCFG_MODCFG_Msk			/*!< MODCFG[1:0] bits (I2S configuration mode) */
#define SPI_I2SCFG_MODCFG0						((uint16_t) 0x0100)				/*!< Bit 0 */
#define SPI_I2SCFG_MODCFG1						((uint16_t) 0x0200)				/*!< Bit 1 */

#define SPI_I2SCFG_I2SEN_Pos					(10U)
#define SPI_I2SCFG_I2SEN_Msk					(0x1UL << SPI_I2SCFG_I2SEN_Pos)		/*!< 0x00000400 */
#define SPI_I2SCFG_I2SEN						SPI_I2SCFG_I2SEN_Msk			/*!< I2S Enable */
#define SPI_I2SCFG_MODSEL_Pos					(11U)
#define SPI_I2SCFG_MODSEL_Msk					(0x1UL << SPI_I2SCFG_MODSEL_Pos)	/*!< 0x00000800 */
#define SPI_I2SCFG_MODSEL						SPI_I2SCFG_MODSEL_Msk			/*!< I2S mode selection */

/****************  Bit definition for SPI_I2SPREDIV register  *****************/
#define SPI_I2SPREDIV_LDIV_Pos					(0U)
#define SPI_I2SPREDIV_LDIV_Msk					(0xFFUL << SPI_I2SPREDIV_LDIV_Pos)		/*!< 0x000000FF */
#define SPI_I2SPREDIV_LDIV						SPI_I2SPREDIV_LDIV_Msk			/*!< I2S Linear prescaler */
#define SPI_I2SPREDIV_ODD_EVEN_Pos				(8U)
#define SPI_I2SPREDIV_ODD_EVEN_Msk				(0x1UL << SPI_I2SPREDIV_ODD_EVEN_Pos)	/*!< 0x00000100 */
#define SPI_I2SPREDIV_ODD_EVEN					SPI_I2SPREDIV_ODD_EVEN_Msk		/*!< Odd factor for the prescaler */
#define SPI_I2SPREDIV_MCLKOEN_Pos				(9U)
#define SPI_I2SPREDIV_MCLKOEN_Msk				(0x1UL << SPI_I2SPREDIV_MCLKOEN_Pos)	/*!< 0x00000200 */
#define SPI_I2SPREDIV_MCLKOEN					SPI_I2SPREDIV_MCLKOEN_Msk		/*!< Master Clock Output Enable */

/******************************************************************************/
/*                                                                            */
/*                      Inter-integrated Circuit Interface                    */
/*                                                                            */
/******************************************************************************/
/******************  Bit definition for I2C_CTRL1 register  *******************/
#define I2C_CTRL1_EN_Pos						(0U)
#define I2C_CTRL1_EN_Msk						(0x1UL << I2C_CTRL1_EN_Pos)
#define I2C_CTRL1_EN							I2C_CTRL1_EN_Msk				/*!< Peripheral Enable */
#define I2C_CTRL1_SMBMODE_Pos					(1U)
#define I2C_CTRL1_SMBMODE_Msk					(0x1UL << I2C_CTRL1_SMBMODE_Pos)
#define I2C_CTRL1_SMBMODE						I2C_CTRL1_SMBMODE_Msk			/*!< SMBus Mode */
#define I2C_CTRL1_SMBTYPE_Pos					(3U)
#define I2C_CTRL1_SMBTYPE_Msk					(0x1UL << I2C_CTRL1_SMBTYPE_Pos)
#define I2C_CTRL1_SMBTYPE						I2C_CTRL1_SMBTYPE_Msk			/*!< SMBus Type */
#define I2C_CTRL1_ARPEN_Pos						(4U)
#define I2C_CTRL1_ARPEN_Msk						(0x1UL << I2C_CTRL1_ARPEN_Pos)
#define I2C_CTRL1_ARPEN							I2C_CTRL1_ARPEN_Msk				/*!< ARP Enable */
#define I2C_CTRL1_PECEN_Pos						(5U)
#define I2C_CTRL1_PECEN_Msk						(0x1UL << I2C_CTRL1_PECEN_Pos)
#define I2C_CTRL1_PECEN							I2C_CTRL1_PECEN_Msk				/*!< PEC Enable */
#define I2C_CTRL1_GCEN_Pos						(6U)
#define I2C_CTRL1_GCEN_Msk						(0x1UL << I2C_CTRL1_GCEN_Pos)
#define I2C_CTRL1_GCEN							I2C_CTRL1_GCEN_Msk				/*!< General Call Enable */
#define I2C_CTRL1_NOEXTEND_Pos					(7U)
#define I2C_CTRL1_NOEXTEND_Msk					(0x1UL << I2C_CTRL1_NOEXTEND_Pos)
#define I2C_CTRL1_NOEXTEND						I2C_CTRL1_NOEXTEND_Msk			/*!< Clock Stretching Disable (Slave mode) */
#define I2C_CTRL1_STARTGEN_Pos					(8U)
#define I2C_CTRL1_STARTGEN_Msk					(0x1UL << I2C_CTRL1_STARTGEN_Pos)
#define I2C_CTRL1_STARTGEN						I2C_CTRL1_STARTGEN_Msk			/*!< Start Generation */
#define I2C_CTRL1_STOPGEN_Pos					(9U)
#define I2C_CTRL1_STOPGEN_Msk					(0x1UL << I2C_CTRL1_STOPGEN_Pos)
#define I2C_CTRL1_STOPGEN						I2C_CTRL1_STOPGEN_Msk			/*!< Stop Generation */
#define I2C_CTRL1_ACKEN_Pos						(10U)
#define I2C_CTRL1_ACKEN_Msk						(0x1UL << I2C_CTRL1_ACKEN_Pos)
#define I2C_CTRL1_ACKEN							I2C_CTRL1_ACKEN_Msk				/*!< Acknowledge Enable */
#define I2C_CTRL1_ACKPOS_Pos					(11U)
#define I2C_CTRL1_ACKPOS_Msk					(0x1UL << I2C_CTRL1_ACKPOS_Pos)
#define I2C_CTRL1_ACKPOS						I2C_CTRL1_ACKPOS_Msk			/*!< Acknowledge/PEC Position (for data reception) */
#define I2C_CTRL1_PEC_Pos						(12U)
#define I2C_CTRL1_PEC_Msk						(0x1UL << I2C_CTRL1_PEC_Pos)
#define I2C_CTRL1_PEC							I2C_CTRL1_PEC_Msk				/*!< Packet Error Checking */
#define I2C_CTRL1_SMBALERT_Pos					(13U)
#define I2C_CTRL1_SMBALERT_Msk					(0x1UL << I2C_CTRL1_SMBALERT_Pos)
#define I2C_CTRL1_SMBALERT						I2C_CTRL1_SMBALERT_Msk			/*!< SMBus Alert */
#define I2C_CTRL1_SWRESET_Pos					(15U)
#define I2C_CTRL1_SWRESET_Msk					(0x1UL << I2C_CTRL1_SWRESET_Pos)
#define I2C_CTRL1_SWRESET						I2C_CTRL1_SWRESET_Msk			/*!< Software Reset */

/******************  Bit definition for I2C_CTRL2 register  *******************/
#define I2C_CTRL2_CLKFREQ_Pos					(0U)
#define I2C_CTRL2_CLKFREQ_Msk					(0x3FUL << I2C_CTRL2_CLKFREQ_Pos)
#define I2C_CTRL2_CLKFREQ						I2C_CTRL2_CLKFREQ_Msk			/*!< FREQ[5:0] bits (Peripheral Clock Frequency) */
#define I2C_CTRL2_CLKFREQ_0						((uint16_t) 0x0001)				/*!< Bit 0 */
#define I2C_CTRL2_CLKFREQ_1						((uint16_t) 0x0002)				/*!< Bit 1 */
#define I2C_CTRL2_CLKFREQ_2						((uint16_t) 0x0004)				/*!< Bit 2 */
#define I2C_CTRL2_CLKFREQ_3						((uint16_t) 0x0008)				/*!< Bit 3 */
#define I2C_CTRL2_CLKFREQ_4						((uint16_t) 0x0010)				/*!< Bit 4 */
#define I2C_CTRL2_CLKFREQ_5						((uint16_t) 0x0020)				/*!< Bit 5 */

#define I2C_CTRL2_ERRINTEN_Pos					(8U)
#define I2C_CTRL2_ERRINTEN_Msk					(0x1UL << I2C_CTRL2_ERRINTEN_Pos)
#define I2C_CTRL2_ERRINTEN						I2C_CTRL2_ERRINTEN_Msk			/*!< Error Interrupt Enable */
#define I2C_CTRL2_EVTINTEN_Pos					(9U)
#define I2C_CTRL2_EVTINTEN_Msk					(0x1UL << I2C_CTRL2_EVTINTEN_Pos)
#define I2C_CTRL2_EVTINTEN						I2C_CTRL2_EVTINTEN_Msk			/*!< Event Interrupt Enable */
#define I2C_CTRL2_BUFINTEN_Pos					(10U)
#define I2C_CTRL2_BUFINTEN_Msk					(0x1UL << I2C_CTRL2_BUFINTEN_Pos)
#define I2C_CTRL2_BUFINTEN						I2C_CTRL2_BUFINTEN_Msk			/*!< Buffer Interrupt Enable */
#define I2C_CTRL2_DMAEN_Pos						(11U)
#define I2C_CTRL2_DMAEN_Msk						(0x1UL << I2C_CTRL2_DMAEN_Pos)
#define I2C_CTRL2_DMAEN							I2C_CTRL2_DMAEN_Msk				/*!< DMA Requests Enable */
#define I2C_CTRL2_DMALAST_Pos					(12U)
#define I2C_CTRL2_DMALAST_Msk					(0x1UL << I2C_CTRL2_DMALAST_Pos)
#define I2C_CTRL2_DMALAST						I2C_CTRL2_DMALAST_Msk			/*!< DMA Last Transfer */

/******************  Bit definition for I2C_OADDR1 register  ******************/
#define I2C_OADDR1_ADDR0_Pos					(0U)
#define I2C_OADDR1_ADDR0_Msk					(0x1UL << I2C_OADDR1_ADDR0_Pos)
#define I2C_OADDR1_ADDR0						I2C_OADDR1_ADDR0_Msk			/*!< Interface Address bit 0 */
#define I2C_OADDR1_ADDR1_7_Pos					(1U)
#define I2C_OADDR1_ADDR1_7_Msk					(0x7FUL << I2C_OADDR1_ADDR1_7_Pos)
#define I2C_OADDR1_ADDR1_7						I2C_OADDR1_ADDR1_7_Msk			/*!< Interface Address bit[7:1] */
#define I2C_OADDR1_ADDR8_9_Pos					(8U)
#define I2C_OADDR1_ADDR8_9_Msk					(0x3UL << I2C_OADDR1_ADDR8_9_Pos)
#define I2C_OADDR1_ADDR8_9						I2C_OADDR1_ADDR8_9_Msk			/*!< Interface Address bit[9:8] */
#define I2C_OADDR1_ADDR_0						((uint16_t) 0x0001)				/*!< Bit 0 */
#define I2C_OADDR1_ADDR_1						((uint16_t) 0x0002)				/*!< Bit 1 */
#define I2C_OADDR1_ADDR_2						((uint16_t) 0x0004)				/*!< Bit 2 */
#define I2C_OADDR1_ADDR_3						((uint16_t) 0x0008)				/*!< Bit 3 */
#define I2C_OADDR1_ADDR_4						((uint16_t) 0x0010)				/*!< Bit 4 */
#define I2C_OADDR1_ADDR_5						((uint16_t) 0x0020)				/*!< Bit 5 */
#define I2C_OADDR1_ADDR_6						((uint16_t) 0x0040)				/*!< Bit 6 */
#define I2C_OADDR1_ADDR_7						((uint16_t) 0x0080)				/*!< Bit 7 */
#define I2C_OADDR1_ADDR_8						((uint16_t) 0x0100)				/*!< Bit 8 */
#define I2C_OADDR1_ADDR_9						((uint16_t) 0x0200)				/*!< Bit 9 */

#define I2C_OADDR1_ADDRMODE_Pos					(15U)
#define I2C_OADDR1_ADDRMODE_Msk					(0x1UL << I2C_OADDR1_ADDRMODE_Pos)
#define I2C_OADDR1_ADDRMODE						I2C_OADDR1_ADDRMODE_Msk			/*!< Addressing Mode (Slave mode) */

/******************  Bit definition for I2C_OADDR2 register  ******************/
#define I2C_OADDR2_DUALEN_Pos					(0U)
#define I2C_OADDR2_DUALEN_Msk					(0x1UL << I2C_OADDR2_DUALEN_Pos)
#define I2C_OADDR2_DUALEN						I2C_OADDR2_DUALEN_Msk			/*!< Dual addressing mode enable */
#define I2C_OADDR2_ADDR2_Pos					(1U)
#define I2C_OADDR2_ADDR2_Msk					(0x7FUL << I2C_OADDR2_ADDR2_Pos)
#define I2C_OADDR2_ADDR2						I2C_OADDR2_ADDR2_Msk			/*!< Interface address */

/*******************  Bit definition for I2C_DAT register  ********************/
#define I2C_DAT_DATA_Pos						(0U)
#define I2C_DAT_DATA_Msk						(0xFFUL << I2C_DAT_DATA_Pos)
#define I2C_DAT_DATA							I2C_DAT_DATA_Msk				/*!< 8-bit Data Register */

/*******************  Bit definition for I2C_STS1 register  *******************/
#define I2C_STS1_STARTBF_Pos					(0U)
#define I2C_STS1_STARTBF_Msk					(0x1UL << I2C_STS1_STARTBF_Pos)
#define I2C_STS1_STARTBF						I2C_STS1_STARTBF_Msk			/*!< Start Bit (Master mode) */
#define I2C_STS1_ADDRF_Pos						(1U)
#define I2C_STS1_ADDRF_Msk						(0x1UL << I2C_STS1_ADDRF_Pos)
#define I2C_STS1_ADDRF							I2C_STS1_ADDRF_Msk				/*!< Address sent (master mode)/matched (slave mode) */
#define I2C_STS1_BSF_Pos						(2U)
#define I2C_STS1_BSF_Msk						(0x1UL << I2C_STS1_BSF_Pos)
#define I2C_STS1_BSF							I2C_STS1_BSF_Msk				/*!< Byte Transfer Finished */
#define I2C_STS1_ADDR10F_Pos					(3U)
#define I2C_STS1_ADDR10F_Msk					(0x1UL << I2C_STS1_ADDR10F_Pos)
#define I2C_STS1_ADDR10F						I2C_STS1_ADDR10F_Msk			/*!< 10-bit header sent (Master mode) */
#define I2C_STS1_STOPF_Pos						(4U)
#define I2C_STS1_STOPF_Msk						(0x1UL << I2C_STS1_STOPF_Pos)
#define I2C_STS1_STOPF							I2C_STS1_STOPF_Msk				/*!< Stop detection (Slave mode) */
#define I2C_STS1_RXDATNE_Pos					(6U)
#define I2C_STS1_RXDATNE_Msk					(0x1UL << I2C_STS1_RXDATNE_Pos)
#define I2C_STS1_RXDATNE						I2C_STS1_RXDATNE_Msk			/*!< Data Register not Empty (receivers) */
#define I2C_STS1_TXDATE_Pos						(7U)
#define I2C_STS1_TXDATE_Msk						(0x1UL << I2C_STS1_TXDATE_Pos)
#define I2C_STS1_TXDATE							I2C_STS1_TXDATE_Msk				/*!< Data Register Empty (transmitters) */
#define I2C_STS1_BUSERR_Pos						(8U)
#define I2C_STS1_BUSERR_Msk						(0x1UL << I2C_STS1_BUSERR_Pos)
#define I2C_STS1_BUSERR							I2C_STS1_BUSERR_Msk				/*!< Bus Error */
#define I2C_STS1_ARLOST_Pos						(9U)
#define I2C_STS1_ARLOST_Msk						(0x1UL << I2C_STS1_ARLOST_Pos)
#define I2C_STS1_ARLOST							I2C_STS1_ARLOST_Msk				/*!< Arbitration Lost (master mode) */
#define I2C_STS1_ACKFAIL_Pos					(10U)
#define I2C_STS1_ACKFAIL_Msk					(0x1UL << I2C_STS1_ACKFAIL_Pos)
#define I2C_STS1_ACKFAIL						I2C_STS1_ACKFAIL_Msk			/*!< Acknowledge Failure */
#define I2C_STS1_OVERRUN_Pos					(11U)
#define I2C_STS1_OVERRUN_Msk					(0x1UL << I2C_STS1_OVERRUN_Pos)
#define I2C_STS1_OVERRUN						I2C_STS1_OVERRUN_Msk			/*!< Overrun/Underrun */
#define I2C_STS1_PECERR_Pos						(12U)
#define I2C_STS1_PECERR_Msk						(0x1UL << I2C_STS1_PECERR_Pos)
#define I2C_STS1_PECERR							I2C_STS1_PECERR_Msk				/*!< PEC Error in reception */
#define I2C_STS1_TIMOUT_Pos						(14U)
#define I2C_STS1_TIMOUT_Msk						(0x1UL << I2C_STS1_TIMOUT_Pos)
#define I2C_STS1_TIMOUT							I2C_STS1_TIMOUT_Msk				/*!< Timeout or Tlow Error */
#define I2C_STS1_SMBALERT_Pos					(15U)
#define I2C_STS1_SMBALERT_Msk					(0x1UL << I2C_STS1_SMBALERT_Pos)
#define I2C_STS1_SMBALERT						I2C_STS1_SMBALERT_Msk			/*!< SMBus Alert */

/*******************  Bit definition for I2C_STS2 register  *******************/
#define I2C_STS2_MSMODE_Pos						(0U)
#define I2C_STS2_MSMODE_Msk						(0x1UL << I2C_STS2_MSMODE_Pos)
#define I2C_STS2_MSMODE							I2C_STS2_MSMODE_Msk				/*!< Master/Slave */
#define I2C_STS2_BUSY_Pos						(1U)
#define I2C_STS2_BUSY_Msk						(0x1UL << I2C_STS2_BUSY_Pos)
#define I2C_STS2_BUSY							I2C_STS2_BUSY_Msk				/*!< Bus Busy */
#define I2C_STS2_TRF_Pos						(2U)
#define I2C_STS2_TRF_Msk						(0x1UL << I2C_STS2_TRF_Pos)
#define I2C_STS2_TRF							I2C_STS2_TRF_Msk				/*!< Transmitter/Receiver */
#define I2C_STS2_GCALLADDR_Pos					(4U)
#define I2C_STS2_GCALLADDR_Msk					(0x1UL << I2C_STS2_GCALLADDR_Pos)
#define I2C_STS2_GCALLADDR						I2C_STS2_GCALLADDR_Msk			/*!< General Call Address (Slave mode) */
#define I2C_STS2_SMBDADDR_Pos					(5U)
#define I2C_STS2_SMBDADDR_Msk					(0x1UL << I2C_STS2_SMBDADDR_Pos)
#define I2C_STS2_SMBDADDR						I2C_STS2_SMBDADDR_Msk			/*!< SMBus Device Default Address (Slave mode) */
#define I2C_STS2_SMBHADDR_Pos					(6U)
#define I2C_STS2_SMBHADDR_Msk					(0x1UL << I2C_STS2_SMBHADDR_Pos)
#define I2C_STS2_SMBHADDR						I2C_STS2_SMBHADDR_Msk			/*!< SMBus Host Header (Slave mode) */
#define I2C_STS2_DUALFLAG_Pos					(7U)
#define I2C_STS2_DUALFLAG_Msk					(0x1UL << I2C_STS2_DUALFLAG_Pos)
#define I2C_STS2_DUALFLAG						I2C_STS2_DUALFLAG_Msk			/*!< Dual Flag (Slave mode) */
#define I2C_STS2_PECVAL_Pos						(8U)
#define I2C_STS2_PECVAL_Msk						(0xFFUL << I2C_STS2_PECVAL_Pos)
#define I2C_STS2_PECVAL							I2C_STS2_PECVAL_Msk				/*!< Packet Error Checking Register */

/*****************  Bit definition for I2C_CLKCTRL register  ******************/
#define I2C_CLKCTRL_CLKCTRL_Pos					(0U)
#define I2C_CLKCTRL_CLKCTRL_Msk					(0xFFFUL << I2C_CLKCTRL_CLKCTRL_Pos)
#define I2C_CLKCTRL_CLKCTRL						I2C_CLKCTRL_CLKCTRL_Msk			/*!< Clock Control Register in Fast/Standard mode (Master mode) */
#define I2C_CLKCTRL_DUTY_Pos					(14U)
#define I2C_CLKCTRL_DUTY_Msk					(0x1UL << I2C_CLKCTRL_DUTY_Pos)
#define I2C_CLKCTRL_DUTY						I2C_CLKCTRL_DUTY_Msk			/*!< Fast Mode Duty Cycle */
#define I2C_CLKCTRL_FSMODE_Pos					(15U)
#define I2C_CLKCTRL_FSMODE_Msk					(0x1UL << I2C_CLKCTRL_FSMODE_Pos)
#define I2C_CLKCTRL_FSMODE						I2C_CLKCTRL_FSMODE_Msk			/*!< I2C Master Mode Selection */

/******************  Bit definition for I2C_TMRISE register  ******************/
#define I2C_TMRISE_TMRISE_Pos					(0U)
#define I2C_TMRISE_TMRISE_Msk					(0x3FUL << I2C_TMRISE_TMRISE_Pos)
#define I2C_TMRISE_TMRISE						I2C_TMRISE_TMRISE_Msk			/*!< Maximum Rise Time in Fast/Standard mode (Master mode) */

/******************************************************************************/
/*                                                                            */
/*         Universal Synchronous Asynchronous Receiver Transmitter            */
/*                                                                            */
/******************************************************************************/
/******************  Bit definition for USART_STS register  *******************/
#define USART_STS_PEF_Pos						(0U)
#define USART_STS_PEF_Msk						(0x1UL << USART_STS_PEF_Pos)	/*!< 0x00000001 */
#define USART_STS_PEF							USART_STS_PEF_Msk				/*!< Parity Error */
#define USART_STS_FEF_Pos						(1U)
#define USART_STS_FEF_Msk						(0x1UL << USART_STS_FEF_Pos)	/*!< 0x00000002 */
#define USART_STS_FEF							USART_STS_FEF_Msk				/*!< Framing Error */
#define USART_STS_NEF_Pos						(2U)
#define USART_STS_NEF_Msk						(0x1UL << USART_STS_NEF_Pos)	/*!< 0x00000004 */
#define USART_STS_NEF							USART_STS_NEF_Msk				/*!< Noise Error Flag */
#define USART_STS_OREF_Pos						(3U)
#define USART_STS_OREF_Msk						(0x1UL << USART_STS_OREF_Pos)	/*!< 0x00000008 */
#define USART_STS_OREF							USART_STS_OREF_Msk				/*!< OverRun Error */
#define USART_STS_IDLEF_Pos						(4U)
#define USART_STS_IDLEF_Msk						(0x1UL << USART_STS_IDLEF_Pos)	/*!< 0x00000010 */
#define USART_STS_IDLEF							USART_STS_IDLEF_Msk				/*!< IDLE line detected */
#define USART_STS_RXDNE_Pos						(5U)
#define USART_STS_RXDNE_Msk						(0x1UL << USART_STS_RXDNE_Pos)	/*!< 0x00000020 */
#define USART_STS_RXDNE							USART_STS_RXDNE_Msk				/*!< Read Data Register Not Empty */
#define USART_STS_TXC_Pos						(6U)
#define USART_STS_TXC_Msk						(0x1UL << USART_STS_TXC_Pos)	/*!< 0x00000040 */
#define USART_STS_TXC							USART_STS_TXC_Msk				/*!< Transmission Complete */
#define USART_STS_TXDE_Pos						(7U)
#define USART_STS_TXDE_Msk						(0x1UL << USART_STS_TXDE_Pos)	/*!< 0x00000080 */
#define USART_STS_TXDE							USART_STS_TXDE_Msk				/*!< Transmit Data Register Empty */
#define USART_STS_LINBDF_Pos					(8U)
#define USART_STS_LINBDF_Msk					(0x1UL << USART_STS_LINBDF_Pos)	/*!< 0x00000100 */
#define USART_STS_LINBDF						USART_STS_LINBDF_Msk			/*!< LIN Break Detection Flag */
#define USART_STS_CTSF_Pos						(9U)
#define USART_STS_CTSF_Msk						(0x1UL << USART_STS_CTSF_Pos)	/*!< 0x00000200 */
#define USART_STS_CTSF							USART_STS_CTSF_Msk				/*!< CTS Flag */

/******************  Bit definition for USART_DAT register  *******************/
#define USART_DAT_DATV_Pos						(0U)
#define USART_DAT_DATV_Msk						(0x1FFUL << USART_DAT_DATV_Pos)	/*!< 0x000001FF */
#define USART_DAT_DATV							USART_DAT_DATV_Msk				/*!< Data value */

/******************  Bit definition for USART_BRCF register  ******************/
#define USART_BRCF_DIV_Decimal_Pos				(0U)
#define USART_BRCF_DIV_Decimal_Msk				(0xFUL << USART_BRCF_DIV_Decimal_Pos)	/*!< 0x0000000F */
#define USART_BRCF_DIV_Decimal					USART_BRCF_DIV_Decimal_Msk		/*!< Fraction of USARTDIV */
#define USART_BRCF_DIV_Integer_Pos				(4U)
#define USART_BRCF_DIV_Integer_Msk				(0xFFFUL << USART_BRCF_DIV_Integer_Pos)	/*!< 0x000FFF0 */
#define USART_BRCF_DIV_Integer					USART_BRCF_DIV_Integer_Msk		/*!< Mantissa of USARTDIV */

/*****************  Bit definition for USART_CTRL1 register  ******************/
#define USART_CTRL1_SDBRK_Pos					(0U)
#define USART_CTRL1_SDBRK_Msk					(0x1UL << USART_CTRL1_SDBRK_Pos)	/*!< 0x00000001 */	
#define USART_CTRL1_SDBRK						USART_CTRL1_SDBRK_Msk			/*!< Send Break */
#define USART_CTRL1_RCVWU_Pos					(1U)
#define USART_CTRL1_RCVWU_Msk					(0x1UL << USART_CTRL1_RCVWU_Pos)	/*!< 0x00000002 */
#define USART_CTRL1_RCVWU						USART_CTRL1_RCVWU_Msk			/*!< Receiver wakeup */
#define USART_CTRL1_RXEN_Pos					(2U)
#define USART_CTRL1_RXEN_Msk					(0x1UL << USART_CTRL1_RXEN_Pos)		/*!< 0x00000004 */
#define USART_CTRL1_RXEN						USART_CTRL1_RXEN_Msk			/*!< Receiver Enable */
#define USART_CTRL1_TXEN_Pos					(3U)
#define USART_CTRL1_TXEN_Msk					(0x1UL << USART_CTRL1_TXEN_Pos)		/*!< 0x00000008 */
#define USART_CTRL1_TXEN						USART_CTRL1_TXEN_Msk			/*!< Transmitter Enable */
#define USART_CTRL1_IDLEIEN_Pos					(4U)
#define USART_CTRL1_IDLEIEN_Msk					(0x1UL << USART_CTRL1_IDLEIEN_Pos)	/*!< 0x00000010 */
#define USART_CTRL1_IDLEIEN						USART_CTRL1_IDLEIEN_Msk			/*!< IDLE Interrupt Enable */
#define USART_CTRL1_RXDNEIEN_Pos				(5U)
#define USART_CTRL1_RXDNEIEN_Msk				(0x1UL << USART_CTRL1_RXDNEIEN_Pos)	/*!< 0x00000020 */
#define USART_CTRL1_RXDNEIEN					USART_CTRL1_RXDNEIEN_Msk		/*!< RXNE Interrupt Enable */
#define USART_CTRL1_TXCIEN_Pos					(6U)
#define USART_CTRL1_TXCIEN_Msk					(0x1UL << USART_CTRL1_TXCIEN_Pos)	/*!< 0x00000040 */
#define USART_CTRL1_TXCIEN						USART_CTRL1_TXCIEN_Msk			/*!< Transmission Complete Interrupt Enable */
#define USART_CTRL1_TXDEIEN_Pos					(7U)
#define USART_CTRL1_TXDEIEN_Msk					(0x1UL << USART_CTRL1_TXDEIEN_Pos)	/*!< 0x00000080 */
#define USART_CTRL1_TXDEIEN						USART_CTRL1_TXDEIEN_Msk			/*!< TXDE interrupt enable*/
#define USART_CTRL1_PEIEN_Pos					(8U)
#define USART_CTRL1_PEIEN_Msk					(0x1UL << USART_CTRL1_PEIEN_Pos)	/*!< 0x00000100 */
#define USART_CTRL1_PEIEN						USART_CTRL1_PEIEN_Msk			/*!< PE Interrupt Enable */
#define USART_CTRL1_PSEL_Pos					(9U)
#define USART_CTRL1_PSEL_Msk					(0x1UL << USART_CTRL1_PSEL_Pos)		/*!< 0x00000200 */
#define USART_CTRL1_PSEL						USART_CTRL1_PSEL_Msk			/*!< Parity Selection */
#define USART_CTRL1_PCEN_Pos					(10U)
#define USART_CTRL1_PCEN_Msk					(0x1UL << USART_CTRL1_PCEN_Pos)		/*!< 0x00000400 */
#define USART_CTRL1_PCEN						USART_CTRL1_PCEN_Msk			/*!< Parity Control Enable */
#define USART_CTRL1_WUM_Pos						(11U)
#define USART_CTRL1_WUM_Msk						(0x1UL << USART_CTRL1_WUM_Pos)		/*!< 0x00000800 */
#define USART_CTRL1_WUM							USART_CTRL1_WUM_Msk				/*!< Wakeup method */
#define USART_CTRL1_WL_Pos						(12U)
#define USART_CTRL1_WL_Msk						(0x1UL << USART_CTRL1_WL_Pos)		/*!< 0x00001000 */
#define USART_CTRL1_WL							USART_CTRL1_WL_Msk				/*!< Word length */
#define USART_CTRL1_UEN_Pos						(13U)
#define USART_CTRL1_UEN_Msk						(0x1UL << USART_CTRL1_UEN_Pos)		/*!< 0x00002000 */
#define USART_CTRL1_UEN							USART_CTRL1_UEN_Msk				/*!< USART Enable */

/*****************  Bit definition for USART_CTRL2 register  ******************/
#define USART_CTRL2_ADDR_Pos					(0U)
#define USART_CTRL2_ADDR_Msk					(0xFUL << USART_CTRL2_ADDR_Pos)		/*!< 0x0000000F */
#define USART_CTRL2_ADDR						USART_CTRL2_ADDR_Msk			/*!< Address of the USART node */
#define USART_CTRL2_LINBDL_Pos					(5U)
#define USART_CTRL2_LINBDL_Msk					(0x1UL << USART_CTRL2_LINBDL_Pos)	/*!< 0x00000020 */
#define USART_CTRL2_LINBDL						USART_CTRL2_LINBDL_Msk			/*!< LIN Break Detection Length */
#define USART_CTRL2_LINBDIE_Pos					(6U)
#define USART_CTRL2_LINBDIE_Msk					(0x1UL << USART_CTRL2_LINBDIE_Pos)	/*!< 0x00000040 */
#define USART_CTRL2_LINBDIE						USART_CTRL2_LINBDIE_Msk			/*!< LIN Break Detection Interrupt Enable */
#define USART_CTRL2_LBCLK_Pos					(8U)
#define USART_CTRL2_LBCLK_Msk					(0x1UL << USART_CTRL2_LBCLK_Pos)	/*!< 0x00000100 */
#define USART_CTRL2_LBCLK						USART_CTRL2_LBCLK_Msk			/*!< Last Bit Clock pulse */
#define USART_CTRL2_CLKPHA_Pos					(9U)
#define USART_CTRL2_CLKPHA_Msk					(0x1UL << USART_CTRL2_CLKPHA_Pos)	/*!< 0x00000200 */
#define USART_CTRL2_CLKPHA						USART_CTRL2_CLKPHA_Msk			/*!< Clock Phase */
#define USART_CTRL2_CLKPOL_Pos					(10U)
#define USART_CTRL2_CLKPOL_Msk					(0x1UL << USART_CTRL2_CLKPOL_Pos)	/*!< 0x00000400 */
#define USART_CTRL2_CLKPOL						USART_CTRL2_CLKPOL_Msk			/*!< Clock Polarity */
#define USART_CTRL2_CLKEN_Pos					(11U)
#define USART_CTRL2_CLKEN_Msk					(0x1UL << USART_CTRL2_CLKEN_Pos)	/*!< 0x00000800 */
#define USART_CTRL2_CLKEN						USART_CTRL2_CLKEN_Msk			/*!< Clock Enable */

#define USART_CTRL2_STPB_Pos					(12U)
#define USART_CTRL2_STPB_Msk					(0x3UL << USART_CTRL2_STPB_Pos)		/*!< 0x00003000 */
#define USART_CTRL2_STPB						USART_CTRL2_STPB_Msk			/*!< STOP[1:0] bits (STOP bits) */
#define USART_CTRL2_STPB_0						((uint16_t) 0x1000)				/*!< Bit 0 */
#define USART_CTRL2_STPB_1						((uint16_t) 0x2000)				/*!< Bit 1 */

#define USART_CTRL2_LINMEN_Pos					(14U)
#define USART_CTRL2_LINMEN_Msk					(0x1UL << USART_CTRL2_LINMEN_Pos)	/*!< 0x00004000 */
#define USART_CTRL2_LINMEN						USART_CTRL2_LINMEN_Msk			/*!< LIN mode enable */

/*****************  Bit definition for USART_CTRL3 register  ******************/
#define USART_CTRL3_ERRIEN_Pos					(0U)
#define USART_CTRL3_ERRIEN_Msk					(0x1UL << USART_CTRL3_ERRIEN_Pos)	/*!< 0x00000001 */
#define USART_CTRL3_ERRIEN						USART_CTRL3_ERRIEN_Msk			/*!< Error Interrupt Enable */
#define USART_CTRL3_IRDAMEN_Pos					(1U)
#define USART_CTRL3_IRDAMEN_Msk					(0x1UL << USART_CTRL3_IRDAMEN_Pos)	/*!< 0x00000002 */
#define USART_CTRL3_IRDAMEN						USART_CTRL3_IRDAMEN_Msk			/*!< IrDA mode Enable */
#define USART_CTRL3_IRDALP_Pos					(2U)
#define USART_CTRL3_IRDALP_Msk					(0x1UL << USART_CTRL3_IRDALP_Pos)	/*!< 0x00000004 */
#define USART_CTRL3_IRDALP						USART_CTRL3_IRDALP_Msk			/*!< IrDA Low-Power */
#define USART_CTRL3_HDMEN_Pos					(3U)
#define USART_CTRL3_HDMEN_Msk					(0x1UL << USART_CTRL3_HDMEN_Pos)	/*!< 0x00000008 */
#define USART_CTRL3_HDMEN						USART_CTRL3_HDMEN_Msk			/*!< Half-Duplex Selection */
#define USART_CTRL3_SCNACK_Pos					(4U)
#define USART_CTRL3_SCNACK_Msk					(0x1UL << USART_CTRL3_SCNACK_Pos)	/*!< 0x00000010 */
#define USART_CTRL3_SCNACK						USART_CTRL3_SCNACK_Msk			/*!< Smartcard NACK enable */
#define USART_CTRL3_SCMEN_Pos					(5U)
#define USART_CTRL3_SCMEN_Msk					(0x1UL << USART_CTRL3_SCMEN_Pos)	/*!< 0x00000020 */
#define USART_CTRL3_SCMEN						USART_CTRL3_SCMEN_Msk			/*!< Smartcard mode enable */
#define USART_CTRL3_DMARXEN_Pos					(6U)
#define USART_CTRL3_DMARXEN_Msk					(0x1UL << USART_CTRL3_DMARXEN_Pos)	/*!< 0x00000040 */
#define USART_CTRL3_DMARXEN						USART_CTRL3_DMARXEN_Msk			/*!< DMA Enable Receiver */
#define USART_CTRL3_DMATXEN_Pos					(7U)
#define USART_CTRL3_DMATXEN_Msk					(0x1UL << USART_CTRL3_DMATXEN_Pos)	/*!< 0x00000080 */
#define USART_CTRL3_DMATXEN						USART_CTRL3_DMATXEN_Msk			/*!< DMA Enable Transmitter */
#define USART_CTRL3_RTSEN_Pos					(8U)
#define USART_CTRL3_RTSEN_Msk					(0x1UL << USART_CTRL3_RTSEN_Pos)	/*!< 0x00000100 */
#define USART_CTRL3_RTSEN						USART_CTRL3_RTSEN_Msk			/*!< RTS Enable */
#define USART_CTRL3_CTSEN_Pos					(9U)
#define USART_CTRL3_CTSEN_Msk					(0x1UL << USART_CTRL3_CTSEN_Pos)	/*!< 0x00000200 */
#define USART_CTRL3_CTSEN						USART_CTRL3_CTSEN_Msk			/*!< CTS Enable */
#define USART_CTRL3_CTSIEN_Pos					(10U)
#define USART_CTRL3_CTSIEN_Msk					(0x1UL << USART_CTRL3_CTSIEN_Pos)	/*!< 0x00000400 */
#define USART_CTRL3_CTSIEN						USART_CTRL3_CTSIEN_Msk			/*!< CTS Interrupt Enable */

/******************  Bit definition for USART_GTP register  *******************/
#define USART_GTP_PSCV_Pos						(0U)
#define USART_GTP_PSCV_Msk						(0xFFUL << USART_GTP_PSCV_Pos)	/*!< 0x000000FF */
#define USART_GTP_PSCV							USART_GTP_PSCV_Msk				/*!< PSC[7:0] bits (Prescaler value) */
#define USART_GTP_PSCV_0						((uint16_t) 0x0001)				/*!< Bit 0 */
#define USART_GTP_PSCV_1						((uint16_t) 0x0002)				/*!< Bit 1 */
#define USART_GTP_PSCV_2						((uint16_t) 0x0004)				/*!< Bit 2 */
#define USART_GTP_PSCV_3						((uint16_t) 0x0008)				/*!< Bit 3 */
#define USART_GTP_PSCV_4						((uint16_t) 0x0010)				/*!< Bit 4 */
#define USART_GTP_PSCV_5						((uint16_t) 0x0020)				/*!< Bit 5 */
#define USART_GTP_PSCV_6						((uint16_t) 0x0040)				/*!< Bit 6 */
#define USART_GTP_PSCV_7						((uint16_t) 0x0080)				/*!< Bit 7 */

#define USART_GTP_GTV_Pos						(8U)
#define USART_GTP_GTV_Msk						(0xFFUL << USART_GTP_GTV_Pos)	/*!< 0x0000FF00 */
#define USART_GTP_GTV							USART_GTP_GTV_Msk				/*!< Guard time value */

/******************************************************************************/
/*                                                                            */
/*                                 Debug MCU                                  */
/*                                                                            */
/******************************************************************************/
/********************  Bit definition for DBG_ID register  ********************/
#define DBG_ID_REV_NUM_L_Pos					(0U)
#define DBG_ID_REV_NUM_L_Msk					(0xFUL << DBG_ID_REV_NUM_L_Pos)
#define DBG_ID_REV_NUM_L						DBG_ID_REV_NUM_L_Msk			/*!< Revision identifier(lower 4 bits)  */
#define DBG_ID_REV_NUM_H_Pos					(4U)
#define DBG_ID_REV_NUM_H_Msk					(0xFUL << DBG_ID_REV_NUM_H_Pos)
#define DBG_ID_REV_NUM_H						DBG_ID_REV_NUM_H_Msk			/*!< Revision identifier(upper 4 bits) */
#define DBG_ID_DEV_NUM_M_Pos					(8U)
#define DBG_ID_DEV_NUM_M_Msk					(0xFUL << DBG_ID_DEV_NUM_M_Pos)
#define DBG_ID_DEV_NUM_M						DBG_ID_DEV_NUM_M_Msk			/*!< Device identifier(middle 4 bits) */
#define DBG_ID_DEV_NUM_H_Pos					(12U)
#define DBG_ID_DEV_NUM_H_Msk					(0xFUL << DBG_ID_DEV_NUM_H_Pos)
#define DBG_ID_DEV_NUM_H						DBG_ID_DEV_NUM_H_Msk			/*!< Device identifier(upper 4 bits) */
#define DBG_ID_FLASH_Pos						(16U)
#define DBG_ID_FLASH_Msk						(0xFUL << DBG_ID_FLASH_Pos)
#define DBG_ID_FLASH							DBG_ID_FLASH_Msk				/*!< Flash capacity indication bit */	
#define DBG_ID_DEV_NUM_L_Pos					(20U)
#define DBG_ID_DEV_NUM_L_Msk					(0xFUL << DBG_ID_DEV_NUM_L_Pos)
#define DBG_ID_DEV_NUM_L						DBG_ID_DEV_NUM_L_Msk			/*!< Device identifier(lower 4 bits) */
#define DBG_ID_SRAM_Pos							(28U)
#define DBG_ID_SRAM_Msk							(0xFUL << DBG_ID_SRAM_Pos)
#define DBG_ID_SRAM								DBG_ID_SRAM_Msk					/*!< SRAM capacity indication bit */

/*******************  Bit definition for DBG_CTRL register  *******************/
#define DBG_CTRL_SLEEP_Pos						(0U)
#define DBG_CTRL_SLEEP_Msk						(0x1UL << DBG_CTRL_SLEEP_Pos)
#define DBG_CTRL_SLEEP							DBG_CTRL_SLEEP_Msk				/*!< Debug Sleep Mode */
#define DBG_CTRL_STOP_Pos						(1U)
#define DBG_CTRL_STOP_Msk						(0x1UL << DBG_CTRL_STOP_Pos)
#define DBG_CTRL_STOP							DBG_CTRL_STOP_Msk				/*!< Debug Stop Mode */
#define DBG_CTRL_STDBY_Pos						(2U)
#define DBG_CTRL_STDBY_Msk						(0x1UL << DBG_CTRL_STDBY_Pos)
#define DBG_CTRL_STDBY							DBG_CTRL_STDBY_Msk				/*!< Debug Standby mode */
#define DBG_CTRL_IWDG_STOP_Pos					(8U)
#define DBG_CTRL_IWDG_STOP_Msk					(0x1UL << DBG_CTRL_IWDG_STOP_Pos)
#define DBG_CTRL_IWDG_STOP						DBG_CTRL_IWDG_STOP_Msk			/*!< Debug Independent Watchdog stopped when Core is halted */
#define DBG_CTRL_WWDG_STOP_Pos					(9U)
#define DBG_CTRL_WWDG_STOP_Msk					(0x1UL << DBG_CTRL_WWDG_STOP_Pos)
#define DBG_CTRL_WWDG_STOP						DBG_CTRL_WWDG_STOP_Msk			/*!< Debug Window Watchdog stopped when Core is halted */
#define DBG_CTRL_TIM1_STOP_Pos					(10U)
#define DBG_CTRL_TIM1_STOP_Msk					(0x1UL << DBG_CTRL_TIM1_STOP_Pos)
#define DBG_CTRL_TIM1_STOP						DBG_CTRL_TIM1_STOP_Msk			/*!< TIM1 counter stopped when core is halted */
#define DBG_CTRL_TIM2_STOP_Pos					(11U)
#define DBG_CTRL_TIM2_STOP_Msk					(0x1UL << DBG_CTRL_TIM2_STOP_Pos)
#define DBG_CTRL_TIM2_STOP						DBG_CTRL_TIM2_STOP_Msk			/*!< TIM2 counter stopped when core is halted */
#define DBG_CTRL_TIM3_STOP_Pos					(12U)
#define DBG_CTRL_TIM3_STOP_Msk					(0x1UL << DBG_CTRL_TIM3_STOP_Pos)
#define DBG_CTRL_TIM3_STOP						DBG_CTRL_TIM3_STOP_Msk			/*!< TIM3 counter stopped when core is halted */
#define DBG_CTRL_TIM4_STOP_Pos					(13U)
#define DBG_CTRL_TIM4_STOP_Msk					(0x1UL << DBG_CTRL_TIM4_STOP_Pos)
#define DBG_CTRL_TIM4_STOP						DBG_CTRL_TIM4_STOP_Msk			/*!< TIM4 counter stopped when core is halted */
#define DBG_CTRL_CAN1_STOP_Pos					(14U)
#define DBG_CTRL_CAN1_STOP_Msk					(0x1UL << DBG_CTRL_CAN1_STOP_Pos)
#define DBG_CTRL_CAN1_STOP						DBG_CTRL_CAN1_STOP_Msk			/*!< Debug CAN1 stopped when Core is halted */
#define DBG_CTRL_I2C1SMBUS_TIMEOUT_Pos			(15U)
#define DBG_CTRL_I2C1SMBUS_TIMEOUT_Msk			(0x1UL << DBG_CTRL_I2C1SMBUS_TIMEOUT_Pos)
#define DBG_CTRL_I2C1SMBUS_TIMEOUT				DBG_CTRL_I2C1SMBUS_TIMEOUT_Msk	/*!< I2C1SMBUS timeout mode stopped when Core is halted */
#define DBG_CTRL_I2C2SMBUS_TIMEOUT_Pos			(16U)
#define DBG_CTRL_I2C2SMBUS_TIMEOUT_Msk			(0x1UL << DBG_CTRL_I2C2SMBUS_TIMEOUT_Pos)
#define DBG_CTRL_I2C2SMBUS_TIMEOUT				DBG_CTRL_I2C2SMBUS_TIMEOUT_Msk	/*!< I2C2SMBUS timeout mode stopped when Core is halted */
#define DBG_CTRL_TIM8_STOP_Pos					(17U)
#define DBG_CTRL_TIM8_STOP_Msk					(0x1UL << DBG_CTRL_TIM8_STOP_Pos)
#define DBG_CTRL_TIM8_STOP						DBG_CTRL_TIM8_STOP_Msk			/*!< TIM5 counter stopped when core is halted */
#define DBG_CTRL_TIM5_STOP_Pos					(18U)
#define DBG_CTRL_TIM5_STOP_Msk					(0x1UL << DBG_CTRL_TIM5_STOP_Pos)
#define DBG_CTRL_TIM5_STOP						DBG_CTRL_TIM5_STOP_Msk			/*!< TIM6 counter stopped when core is halted */
#define DBG_CTRL_TIM6_STOP_Pos					(19U)
#define DBG_CTRL_TIM6_STOP_Msk					(0x1UL << DBG_CTRL_TIM6_STOP_Pos)
#define DBG_CTRL_TIM6_STOP						DBG_CTRL_TIM6_STOP_Msk			/*!< TIM7 counter stopped when core is halted */
#define DBG_CTRL_TIM7_STOP_Pos					(20U)
#define DBG_CTRL_TIM7_STOP_Msk					(0x1UL << DBG_CTRL_TIM7_STOP_Pos)
#define DBG_CTRL_TIM7_STOP						DBG_CTRL_TIM7_STOP_Msk			/*!< TIM8 counter stopped when core is halted */
#define DBG_CTRL_CAN2_STOP_Pos					(21U)
#define DBG_CTRL_CAN2_STOP_Msk					(0x1UL << DBG_CTRL_CAN2_STOP_Pos)
#define DBG_CTRL_CAN2_STOP						DBG_CTRL_CAN2_STOP_Msk			/*!< Debug CAN2 stopped when Core is halted */
#define DBG_CTRL_DWJTAG_BYPASS_Pos				(22U)
#define DBG_CTRL_DWJTAG_BYPASS_Msk				(0x1UL << DBG_CTRL_DWJTAG_BYPASS_Pos)
#define DBG_CTRL_DWJTAG_BYPASS					DBG_CTRL_DWJTAG_BYPASS_Msk		/*!< 2-wire JTAG stopped when core is halted */
#define DBG_CTRL_DBG_DSLEEP_EN_Pos				(23U)
#define DBG_CTRL_DBG_DSLEEP_EN_Msk				(0x1UL << DBG_CTRL_DBG_DSLEEP_EN_Pos)
#define DBG_CTRL_DBG_DSLEEP_EN					DBG_CTRL_DBG_DSLEEP_EN_Msk		/*!< Debug Deep Sleep Mode */

/******************************************************************************/
/*                                                                            */
/*                      FLASH and Option Bytes Registers                      */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for FLASH_AC register  *******************/
#define FLASH_AC_LATENCY_Pos					(0U)
#define FLASH_AC_LATENCY_Msk					(0x7UL << FLASH_AC_LATENCY_Pos)
#define FLASH_AC_LATENCY						FLASH_AC_LATENCY_Msk			/*!< LATENCY[2:0] bits (Latency) */
#define FLASH_AC_LATENCY_0						((uint8_t) 0x01)				/*!< Bit 0 */
#define FLASH_AC_LATENCY_1						((uint8_t) 0x02)				/*!< Bit 1 */
#define FLASH_AC_LATENCY_2						((uint8_t) 0x04)				/*!< Bit 2 */

#define FLASH_AC_PRFTBFE_Pos					(4U)
#define FLASH_AC_PRFTBFE_Msk					(0x1UL << FLASH_AC_PRFTBFE_Pos)
#define FLASH_AC_PRFTBFE						FLASH_AC_PRFTBFE_Msk			/*!< Prefetch Buffer Enable */
#define FLASH_AC_PRFTBFS_Pos					(5U)
#define FLASH_AC_PRFTBFS_Msk					(0x1UL << FLASH_AC_PRFTBFS_Pos)
#define FLASH_AC_PRFTBFS						FLASH_AC_PRFTBFS_Msk			/*!< Prefetch Buffer Status */
#define FLASH_AC_ICAHRST_Pos					(6U)
#define FLASH_AC_ICAHRST_Msk					(0x1UL << FLASH_AC_ICAHRST_Pos)
#define FLASH_AC_ICAHRST						FLASH_AC_ICAHRST_Msk			/*!< Icache Reset */
#define FLASH_AC_ICAHEN_Pos						(7U)
#define FLASH_AC_ICAHEN_Msk						(0x1UL << FLASH_AC_ICAHEN_Pos)
#define FLASH_AC_ICAHEN							FLASH_AC_ICAHEN_Msk				/*!< Icache Enable */

/******************  Bit definition for FLASH_KEY register  *******************/
#define FLASH_KEY_FKEY_Pos						(0U)
#define FLASH_KEY_FKEY_Msk						(0xFFFFFFFFUL << FLASH_KEY_FKEY_Pos)	/*!< 0xFFFFFFFF */
#define FLASH_KEY_FKEY							FLASH_KEY_FKEY_Msk				/*!< FPEC Key */

/*****************  Bit definition for FLASH_OPTKEY register  *****************/
#define FLASH_OPTKEY_OPTKEY_Pos					(0U)
#define FLASH_OPTKEY_OPTKEY_Msk					(0xFFFFFFFFUL << FLASH_OPTKEY_OPTKEY_Pos)	/*!< 0xFFFFFFFF */
#define FLASH_OPTKEY_OPTKEY						FLASH_OPTKEY_OPTKEY_Msk			/*!< Option Byte Key */

/******************  Bit definition for FLASH_STS register  *******************/
#define FLASH_STS_BUSY_Pos						(0U)
#define FLASH_STS_BUSY_Msk						(0x1UL << FLASH_STS_BUSY_Pos)
#define FLASH_STS_BUSY							FLASH_STS_BUSY_Msk				/*!< Busy */
#define FLASH_STS_PGERR_Pos						(2U)
#define FLASH_STS_PGERR_Msk						(0x1UL << FLASH_STS_PGERR_Pos)
#define FLASH_STS_PGERR							FLASH_STS_PGERR_Msk				/*!< Programming Error */
#define FLASH_STS_PVERR_Pos						(3U)
#define FLASH_STS_PVERR_Msk						(0x1UL << FLASH_STS_PVERR_Pos)
#define FLASH_STS_PVERR							FLASH_STS_PVERR_Msk				/*!< Programming Verify ERROR after program */
#define FLASH_STS_WRPEER_Pos					(4U)
#define FLASH_STS_WRPEER_Msk					(0x1UL << FLASH_STS_WRPEER_Pos)
#define FLASH_STS_WRPEER						FLASH_STS_WRPEER_Msk			/*!< Write Protection Error */
#define FLASH_STS_EOP_Pos						(5U)
#define FLASH_STS_EOP_Msk						(0x1UL << FLASH_STS_EOP_Pos)
#define FLASH_STS_EOP							FLASH_STS_EOP_Msk				/*!< End of operation */
#define FLASH_STS_EVERR_Pos						(6U)
#define FLASH_STS_EVERR_Msk						(0x1UL << FLASH_STS_EVERR_Pos)
#define FLASH_STS_EVERR							FLASH_STS_EVERR_Msk				/*!< Erase Verify ERROR after page erase */
#define FLASH_STS_ECCERR_Pos					(7U)
#define FLASH_STS_ECCERR_Msk					(0x1UL << FLASH_STS_ECCERR_Pos)
#define FLASH_STS_ECCERR						FLASH_STS_ECCERR_Msk			/*!< ECC ERROR when Flash Reading */

/******************  Bit definition for FLASH_CTRL register  ******************/
#define FLASH_CTRL_PG_Pos						(0U)
#define FLASH_CTRL_PG_Msk						(0x1UL << FLASH_CTRL_PG_Pos)
#define FLASH_CTRL_PG							FLASH_CTRL_PG_Msk				/*!< Programming */
#define FLASH_CTRL_PER_Pos						(1U)
#define FLASH_CTRL_PER_Msk						(0x1UL << FLASH_CTRL_PER_Pos)
#define FLASH_CTRL_PER							FLASH_CTRL_PER_Msk				/*!< Page Erase */
#define FLASH_CTRL_MER_Pos						(2U)
#define FLASH_CTRL_MER_Msk						(0x1UL << FLASH_CTRL_MER_Pos)
#define FLASH_CTRL_MER							FLASH_CTRL_MER_Msk				/*!< Mass Erase */
#define FLASH_CTRL_OPTPG_Pos					(4U)
#define FLASH_CTRL_OPTPG_Msk					(0x1UL << FLASH_CTRL_OPTPG_Pos)
#define FLASH_CTRL_OPTPG						FLASH_CTRL_OPTPG_Msk			/*!< Option Byte Programming */
#define FLASH_CTRL_OPTER_Pos					(5U)
#define FLASH_CTRL_OPTER_Msk					(0x1UL << FLASH_CTRL_OPTER_Pos)
#define FLASH_CTRL_OPTER						FLASH_CTRL_OPTER_Msk			/*!< Option Byte Erase */
#define FLASH_CTRL_START_Pos					(6U)
#define FLASH_CTRL_START_Msk					(0x1UL << FLASH_CTRL_START_Pos)
#define FLASH_CTRL_START						FLASH_CTRL_START_Msk			/*!< Start */
#define FLASH_CTRL_LOCK_Pos						(7U)
#define FLASH_CTRL_LOCK_Msk						(0x1UL << FLASH_CTRL_LOCK_Pos)
#define FLASH_CTRL_LOCK							FLASH_CTRL_LOCK_Msk				/*!< Lock */
#define FLASH_CTRL_SMPSEL_Pos					(8U)
#define FLASH_CTRL_SMPSEL_Msk					(0x1UL << FLASH_CTRL_SMPSEL_Pos)
#define FLASH_CTRL_SMPSEL						FLASH_CTRL_SMPSEL_Msk			/*!< Flash Program Option Select */
#define FLASH_CTRL_OPTWE_Pos					(9U)
#define FLASH_CTRL_OPTWE_Msk					(0x1UL << FLASH_CTRL_OPTWE_Pos)
#define FLASH_CTRL_OPTWE						FLASH_CTRL_OPTWE_Msk			/*!< Option Bytes Write Enable */
#define FLASH_CTRL_ERRITE_Pos					(10U)
#define FLASH_CTRL_ERRITE_Msk					(0x1UL << FLASH_CTRL_ERRITE_Pos)
#define FLASH_CTRL_ERRITE						FLASH_CTRL_ERRITE_Msk			/*!< Error Interrupt Enable */
#define FLASH_CTRL_FERRITE_Pos					(11U)
#define FLASH_CTRL_FERRITE_Msk					(0x1UL << FLASH_CTRL_FERRITE_Pos)
#define FLASH_CTRL_FERRITE						FLASH_CTRL_FERRITE_Msk			/*!< EVERR PVERR Error Interrupt Enable */
#define FLASH_CTRL_EOPITE_Pos					(12U)
#define FLASH_CTRL_EOPITE_Msk 					(0x1UL << FLASH_CTRL_EOPITE_Pos)
#define FLASH_CTRL_EOPITE						FLASH_CTRL_EOPITE_Msk			/*!< End of operation Interrupt Enable */
#define FLASH_CTRL_ECCERRITE_Pos				(13U)
#define FLASH_CTRL_ECCERRITE_Msk				(0x1UL << FLASH_CTRL_ECCERRITE_Pos)
#define FLASH_CTRL_ECCERRITE					FLASH_CTRL_ECCERRITE_Msk			/*!< ECC Error Interrupt Enable */

/*******************  Bit definition for FLASH_AR register  *******************/
#define FLASH_ADD_FADD_Pos						(0U)
#define FLASH_ADD_FADD_Msk						(0xFFFFFFFFUL << FLASH_ADD_FADD_Pos)	/*!< 0xFFFFFFFF */
#define FLASH_ADD_FADD							FLASH_ADD_FADD_Msk				/*!< Flash Address */

/*******************  Bit definition for FLASH_OB register  *******************/
#define FLASH_OB_OBERR_Pos						(0U)
#define FLASH_OB_OBERR_Msk						(0x1UL << FLASH_OB_OBERR_Pos)
#define FLASH_OB_OBERR							FLASH_OB_OBERR_Msk				/*!< Option Byte Error */
#define FLASH_OB_RDPRT1_Pos						(1U)
#define FLASH_OB_RDPRT1_Msk						(0x1UL << FLASH_OB_RDPRT1_Pos)
#define FLASH_OB_RDPRT1							FLASH_OB_RDPRT1_Msk				/*!< Read Protection */
#define FLASH_OB_WDG_SW_Pos						(2U)
#define FLASH_OB_WDG_SW_Msk						(0x1UL << FLASH_OB_WDG_SW_Pos)
#define FLASH_OB_WDG_SW							FLASH_OB_WDG_SW_Msk				/*!< WDG_SW */
#define FLASH_OB_nRST_STOP0_Pos					(3U)
#define FLASH_OB_nRST_STOP0_Msk					(0x1UL << FLASH_OB_nRST_STOP0_Pos)
#define FLASH_OB_nRST_STOP0						FLASH_OB_nRST_STOP0_Msk			/*!< nRST_STOP0 */	
#define FLASH_OB_nRST_STDBY_Pos					(4U)
#define FLASH_OB_nRST_STDBY_Msk					(0x1UL << FLASH_OB_nRST_STDBY_Pos)
#define FLASH_OB_nRST_STDBY						FLASH_OB_nRST_STDBY_Msk			/*!< nRST_STDBY */	
#define FLASH_OB_USER_Pos						(2U)
#define FLASH_OB_USER_Msk						(0x7UL << FLASH_OB_USER_Pos)
#define FLASH_OB_USER							FLASH_OB_USER_Msk				/*!< User Option Bytes, Include WDG_SW, nRST_STOP0 and nRST_STDBY bits */
#define FLASH_OB_Data0_Pos						(10U)
#define FLASH_OB_Data0_Msk						(0xFFUL << FLASH_OB_Data0_Pos)
#define FLASH_OB_Data0							FLASH_OB_Data0_Msk				/*!< Data 0 */
#define FLASH_OB_Data1_Pos						(18U)
#define FLASH_OB_Data1_Msk						(0xFFUL << FLASH_OB_Data1_Pos)
#define FLASH_OB_Data1							FLASH_OB_Data1_Msk				/*!< Data 1 */
#define FLASH_OB_RDPRT2_Pos						(31U)
#define FLASH_OB_RDPRT2_Msk						(0x1UL << FLASH_OB_RDPRT2_Pos)
#define FLASH_OB_RDPRT2							FLASH_OB_RDPRT2_Msk				/*!< Read Protection Level 2 */

/******************  Bit definition for FLASH_WRP register  *******************/
#define FLASH_WRP_WRPT_Pos						(0U)
#define FLASH_WRP_WRPT_Msk						(0xFFFFFFFFUL << FLASH_WRP_WRPT_Pos)	/*!< 0xFFFFFFFF */
#define FLASH_WRP_WRPT							FLASH_WRP_WRPT_Msk				/*!< Write Protect */
#define FLASH_WRP_WRPT_0_7						((uint32_t) 0x000000FF)			/*!< Bit 0 - 7 */
#define FLASH_WRP_WRPT_8_15						((uint32_t) 0x0000FF00)			/*!< Bit 8 - 15 */
#define FLASH_WRP_WRPT_16_23					((uint32_t) 0x00FF0000)			/*!< Bit 16 - 23 */
#define FLASH_WRP_WRPT_24_31					((uint32_t) 0xFF000000)			/*!< Bit 24 - 31 */

/******************  Bit definition for FLASH_ECC register  *******************/
#define FLASH_ECC_ECCLW_Pos						(0U)
#define FLASH_ECC_ECCLW_Msk						(0x3FUL << FLASH_ECC_ECCLW_Pos)
#define FLASH_ECC_ECCLW							FLASH_ECC_ECCLW_Msk				/*!< Upper 6 bits of ECC value */
#define FLASH_ECC_ECCHW_Pos						(8U)
#define FLASH_ECC_ECCHW_Msk						(0x3FUL << FLASH_ECC_ECCHW_Pos)
#define FLASH_ECC_ECCHW							FLASH_ECC_ECCHW_Msk				/*!< Lower 6 bits of ECC value */

/******************  Bit definition for FLASH_RDN register  *******************/
#define FLASH_RDN_FLASH_RDN0_Pos				(0U)
#define FLASH_RDN_FLASH_RDN0_Msk				(0x1FFUL << FLASH_RDN_FLASH_RDN0_Pos)
#define FLASH_RDN_FLASH_RDN0					FLASH_RDN_FLASH_RDN0_Msk		/*!< Address of flash redundancy page 0 */
#define FLASH_RDN_FLASH_RDN1_Pos				(16U)
#define FLASH_RDN_FLASH_RDN1_Msk				(0x1FFUL << FLASH_RDN_FLASH_RDN1_Pos)
#define FLASH_RDN_FLASH_RDN1					FLASH_RDN_FLASH_RDN1_Msk		/*!< Address of flash redundancy page 1 */

/******************  Bit definition for FLASH_CAHR register  ******************/
#define FLASH_CAHR_LOCKSTRT_Pos					(0U)
#define FLASH_CAHR_LOCKSTRT_Msk					(0xFUL << FLASH_CAHR_LOCKSTRT_Pos)	/*!< 0x0000000F */
#define FLASH_CAHR_LOCKSTRT						FLASH_CAHR_LOCKSTRT_Msk			/*!< iCache lock start */
#define FLASH_CAHR_LOCKSTOP_Pos					(4U)
#define FLASH_CAHR_LOCKSTOP_Msk					(0xFUL << FLASH_CAHR_LOCKSTOP_Pos)	/*!< 0x000000F0 */
#define FLASH_CAHR_LOCKSTOP						FLASH_CAHR_LOCKSTOP_Msk			/*!< iCache lock stop */

/* ------------------------ Option Bytes definition ------------------------- */
/**********************  Bit definition for OB_RDP byte  **********************/
#define OB_RDP1_USER_RDP1_Pos					(0U)
#define OB_RDP1_USER_RDP1_Msk					(0xFFUL << OB_RDP1_USER_RDP1_Pos)
#define OB_RDP1_USER_RDP1						OB_RDP1_USER_RDP1_Msk			/*!< Read protection option byte */
#define OB_RDP1_USER_nRDP1_Pos					(8U)
#define OB_RDP1_USER_nRDP1_Msk					(0xFFUL << OB_RDP1_USER_nRDP1_Pos)
#define OB_RDP1_USER_nRDP1						OB_RDP1_USER_nRDP1_Msk			/*!< Read protection complemented option byte */
#define OB_RDP1_USER_RDP1_nRDP1_Pos				(0U)
#define OB_RDP1_USER_RDP1_nRDP1_Msk				(0xFFFFUL << OB_RDP1_USER_RDP1_nRDP1_Pos)
#define OB_RDP1_USER_RDP1_nRDP1					OB_RDP1_USER_RDP1_nRDP1_Msk		/*!< Read protection option byte and complemented option byte */

/*********************  Bit definition for OB_USER byte  **********************/
#define OB_RDP1_USER_USER_Pos					(16U)
#define OB_RDP1_USER_USER_Msk					(0xFFUL << OB_RDP1_USER_USER_Pos)
#define OB_RDP1_USER_USER						OB_RDP1_USER_USER_Msk			/*!< User option byte */
#define OB_RDP1_USER_nUSER_Pos					(24U)
#define OB_RDP1_USER_nUSER_Msk					(0xFFUL << OB_RDP1_USER_nUSER_Pos)
#define OB_RDP1_USER_nUSER						OB_RDP1_USER_nUSER_Msk			/*!< User complemented option byte */
#define OB_RDP1_USER_USER_nUSER_Pos				(16U)
#define OB_RDP1_USER_USER_nUSER_Msk				(0xFFFFUL << OB_RDP1_USER_USER_nUSER_Pos)
#define OB_RDP1_USER_USER_nUSER					OB_RDP1_USER_USER_nUSER_Msk		/*!< User option byte and complemented option byte */

/*********************  Bit definition for OB_Data0 byte  *********************/
#define OB_Data0_Data1_Data0_Pos				(0U)
#define OB_Data0_Data1_Data0_Msk				(0xFFUL << OB_Data0_Data1_Data0_Pos)
#define OB_Data0_Data1_Data0					OB_Data0_Data1_Data0_Msk		/*!< User data 0 storage option byte */
#define OB_Data0_Data1_nData0_Pos				(8U)
#define OB_Data0_Data1_nData0_Msk				(0xFFUL << OB_Data0_Data1_nData0_Pos)
#define OB_Data0_Data1_nData0					OB_Data0_Data1_nData0_Msk		/*!< User data 0 storage complemented option byte */
#define OB_Data0_Data1_Data0_nData0_Pos			(0U)
#define OB_Data0_Data1_Data0_nData0_Msk			(0xFFFFUL << OB_Data0_Data1_Data0_nData0_Pos)
#define OB_Data0_Data1_Data0_nData0				OB_Data0_Data1_Data0_nData0_Msk	/*!< User data 0 storage option byte and complemented option byte */

/*********************  Bit definition for OB_Data1 Byte  *********************/
#define OB_Data0_Data1_Data1_Pos				(16U)
#define OB_Data0_Data1_Data1_Msk				(0xFFUL << OB_Data0_Data1_Data1_Pos)
#define OB_Data0_Data1_Data1					OB_Data0_Data1_Data1_Msk		/*!< User data 1 storage option byte */
#define OB_Data0_Data1_nData1_Pos				(24U)
#define OB_Data0_Data1_nData1_Msk				(0xFFUL << OB_Data0_Data1_nData1_Pos)
#define OB_Data0_Data1_nData1					OB_Data0_Data1_nData1_Msk		/*!< User data 1 storage complemented option byte */
#define OB_Data0_Data1_Data1_nData1_Pos			(16U)
#define OB_Data0_Data1_Data1_nData1_Msk			(0xFFFFUL << OB_Data0_Data1_Data1_nData1_Pos)
#define OB_Data0_Data1_Data1_nData1				OB_Data0_Data1_Data1_nData1_Msk	/*!< User data 1 storage option byte and complemented option byte */

/*********************  Bit definition for OB_WRP0 Byte  **********************/
#define OB_WRP1_WRP0_WRP0_Pos					(0U)
#define OB_WRP1_WRP0_WRP0_Msk					(0xFFUL << OB_WRP1_WRP0_WRP0_Pos)
#define OB_WRP1_WRP0_WRP0						OB_WRP1_WRP0_WRP0_Msk			/*!< Flash memory write protection 0 option bytes */
#define OB_WRP1_WRP0_nWRP0_Pos					(8U)
#define OB_WRP1_WRP0_nWRP0_Msk					(0xFFUL << OB_WRP1_WRP0_nWRP0_Pos)
#define OB_WRP1_WRP0_nWRP0						OB_WRP1_WRP0_nWRP0_Msk			/*!< Flash memory write protection 0 complemented option bytes */
#define OB_WRP1_WRP0_WRP0_nWRP0_Pos				(0U)
#define OB_WRP1_WRP0_WRP0_nWRP0_Msk				(0xFFFFUL << OB_WRP1_WRP0_WRP0_nWRP0_Pos)
#define OB_WRP1_WRP0_WRP0_nWRP0					OB_WRP1_WRP0_WRP0_nWRP0_Msk		/*!< Flash memory write protection 0 option bytes and complemented option bytes */

/*********************  Bit definition for OB_WRP1 Byte  **********************/
#define OB_WRP1_WRP0_WRP1_Pos					(16U)
#define OB_WRP1_WRP0_WRP1_Msk					(0xFFUL << OB_WRP1_WRP0_WRP1_Pos)
#define OB_WRP1_WRP0_WRP1						OB_WRP1_WRP0_WRP1_Msk			/*!< Flash memory write protection 1 option bytes */
#define OB_WRP1_WRP0_nWRP1_Pos					(24U)
#define OB_WRP1_WRP0_nWRP1_Msk					(0xFFUL << OB_WRP1_WRP0_nWRP1_Pos)
#define OB_WRP1_WRP0_nWRP1						OB_WRP1_WRP0_nWRP1_Msk			/*!< Flash memory write protection 1 complemented option bytes */
#define OB_WRP1_WRP0_WRP1_nWRP1_Pos				(16U)
#define OB_WRP1_WRP0_WRP1_nWRP1_Msk				(0xFFFFUL << OB_WRP1_WRP0_WRP1_nWRP1_Pos)
#define OB_WRP1_WRP0_WRP1_nWRP1					OB_WRP1_WRP0_WRP1_nWRP1_Msk		/*!< Flash memory write protection 1 option bytes and complemented option bytes */

/*********************  Bit definition for OB_WRP2 Byte  **********************/
#define OB_WRP3_WRP2_WRP2_Pos					(0U)
#define OB_WRP3_WRP2_WRP2_Msk					(0xFFUL << OB_WRP3_WRP2_WRP2_Pos)
#define OB_WRP3_WRP2_WRP2						OB_WRP3_WRP2_WRP2_Msk			/*!< Flash memory write protection 2 option bytes */
#define OB_WRP3_WRP2_nWRP2_Pos					(8U)
#define OB_WRP3_WRP2_nWRP2_Msk					(0xFFUL << OB_WRP3_WRP2_nWRP2_Pos)
#define OB_WRP3_WRP2_nWRP2						OB_WRP3_WRP2_nWRP2_Msk			/*!< Flash memory write protection 2 complemented option bytes */
#define OB_WRP3_WRP2_WRP2_nWRP2_Pos				(0U)
#define OB_WRP3_WRP2_WRP2_nWRP2_Msk				(0xFFFFUL << OB_WRP3_WRP2_WRP2_nWRP2_Pos)
#define OB_WRP3_WRP2_WRP2_nWRP2					OB_WRP3_WRP2_WRP2_nWRP2_Msk		/*!< Flash memory write protection 2 option bytes and complemented option bytes */

/*********************  Bit definition for OB_WRP3 Byte  **********************/
#define OB_WRP3_WRP2_WRP3_Pos					(16U)
#define OB_WRP3_WRP2_WRP3_Msk					(0xFFUL << OB_WRP3_WRP2_WRP3_Pos)
#define OB_WRP3_WRP2_WRP3						OB_WRP3_WRP2_WRP3_Msk			/*!< Flash memory write protection 3 option bytes */
#define OB_WRP3_WRP2_nWRP3_Pos					(24U)
#define OB_WRP3_WRP2_nWRP3_Msk					(0xFFUL << OB_WRP3_WRP2_nWRP3_Pos)
#define OB_WRP3_WRP2_nWRP3						OB_WRP3_WRP2_nWRP3_Msk			/*!< Flash memory write protection 3 complemented option bytes */
#define OB_WRP3_WRP2_WRP3_nWRP3_Pos				(16U)
#define OB_WRP3_WRP2_WRP3_nWRP3_Msk				(0xFFFFUL << OB_WRP3_WRP2_WRP3_nWRP3_Pos)
#define OB_WRP3_WRP2_WRP3_nWRP3					OB_WRP3_WRP2_WRP3_nWRP3_Msk		/*!< Flash memory write protection 3 option bytes and complemented option bytes */

/*********************  Bit definition for OB_RDP2 Byte  **********************/
#define OB_RDP2_RDP2_Pos						(0U)
#define OB_RDP2_RDP2_Msk						(0xFFUL << OB_RDP2_RDP2_Pos)
#define OB_RDP2_RDP2							OB_RDP2_RDP2_Msk				/*!< Read protection level 2 option byte */
#define OB_RDP2_nRDP2_Pos						(8U)
#define OB_RDP2_nRDP2_Msk						(0xFFUL << OB_RDP2_nRDP2_Pos)
#define OB_RDP2_nRDP2							OB_RDP2_nRDP2_Msk				/*!< Read protection level 2 complemented option byte */
#define OB_RDP2_RDP2_nRDP2_Pos					(0U)
#define OB_RDP2_RDP2_nRDP2_Msk					(0xFFFFUL << OB_RDP2_RDP2_nRDP2_Pos)
#define OB_RDP2_RDP2_nRDP2						OB_RDP2_RDP2_nRDP2_Msk			/*!< Read protection level 2 option byte and complemented option byte */

/******************************************************************************/
/*                                                                            */
/*                                 QSPI Registers           	              */
/*                                                                            */
/******************************************************************************/
/******************  Bit definition for QSPI_CTRL0 register  ******************/
#define QSPI_CTRL0_DFS_Pos						(0U)
#define QSPI_CTRL0_DFS_Msk						(0x1FUL << QSPI_CTRL0_DFS_Pos)
#define QSPI_CTRL0_DFS							QSPI_CTRL0_DFS_Msk				/*!< DFS[4:0] bits (Data Frame Size) */
#define QSPI_CTRL0_DFS_0                        ((uint32_t) 0x00000001)			/*!< Bit 0 */
#define QSPI_CTRL0_DFS_1                        ((uint32_t) 0x00000002)			/*!< Bit 1 */
#define QSPI_CTRL0_DFS_2                        ((uint32_t) 0x00000004)			/*!< Bit 2 */
#define QSPI_CTRL0_DFS_3                        ((uint32_t) 0x00000008)			/*!< Bit 3 */
#define QSPI_CTRL0_DFS_4                        ((uint32_t) 0x00000010)			/*!< Bit 4 */

/*!< Data Frame Size configuration */
#define QSPI_CTRL0_DFS_4_BIT               		((uint32_t) 0x00000003)			/*!< 4 bits */
#define QSPI_CTRL0_DFS_5_BIT               		((uint32_t) 0x00000004)			/*!< 5 bits */
#define QSPI_CTRL0_DFS_6_BIT               		((uint32_t) 0x00000005)			/*!< 6 bits */
#define QSPI_CTRL0_DFS_7_BIT               		((uint32_t) 0x00000006)			/*!< 7 bits */
#define QSPI_CTRL0_DFS_8_BIT               		((uint32_t) 0x00000007)			/*!< 8 bits */
#define QSPI_CTRL0_DFS_9_BIT               		((uint32_t) 0x00000008)			/*!< 9 bits */
#define QSPI_CTRL0_DFS_10_BIT              		((uint32_t) 0x00000009)			/*!< 10 bits */
#define QSPI_CTRL0_DFS_11_BIT              		((uint32_t) 0x0000000A)			/*!< 11 bits */
#define QSPI_CTRL0_DFS_12_BIT              		((uint32_t) 0x0000000B)			/*!< 12 bits */
#define QSPI_CTRL0_DFS_13_BIT              		((uint32_t) 0x0000000C)			/*!< 13 bits */
#define QSPI_CTRL0_DFS_14_BIT              		((uint32_t) 0x0000000D)			/*!< 14 bits */
#define QSPI_CTRL0_DFS_15_BIT              		((uint32_t) 0x0000000E)			/*!< 15 bits */
#define QSPI_CTRL0_DFS_16_BIT              		((uint32_t) 0x0000000F)			/*!< 16 bits */
#define QSPI_CTRL0_DFS_17_BIT              		((uint32_t) 0x00000010)			/*!< 17 bits */
#define QSPI_CTRL0_DFS_18_BIT              		((uint32_t) 0x00000011)			/*!< 18 bits */
#define QSPI_CTRL0_DFS_19_BIT              		((uint32_t) 0x00000012)			/*!< 19 bits */
#define QSPI_CTRL0_DFS_20_BIT              		((uint32_t) 0x00000013)			/*!< 20 bits */
#define QSPI_CTRL0_DFS_21_BIT              		((uint32_t) 0x00000014)			/*!< 21 bits */
#define QSPI_CTRL0_DFS_22_BIT              		((uint32_t) 0x00000015)			/*!< 22 bits */
#define QSPI_CTRL0_DFS_23_BIT              		((uint32_t) 0x00000016)			/*!< 23 bits */
#define QSPI_CTRL0_DFS_24_BIT              		((uint32_t) 0x00000017)			/*!< 24 bits */
#define QSPI_CTRL0_DFS_25_BIT              		((uint32_t) 0x00000018)			/*!< 25 bits */
#define QSPI_CTRL0_DFS_26_BIT              		((uint32_t) 0x00000019)			/*!< 26 bits */
#define QSPI_CTRL0_DFS_27_BIT              		((uint32_t) 0x0000001A)			/*!< 27 bits */
#define QSPI_CTRL0_DFS_28_BIT              		((uint32_t) 0x0000001B)			/*!< 28 bits */
#define QSPI_CTRL0_DFS_29_BIT              		((uint32_t) 0x0000001C)			/*!< 29 bits */
#define QSPI_CTRL0_DFS_30_BIT              		((uint32_t) 0x0000001D)			/*!< 30 bits */
#define QSPI_CTRL0_DFS_31_BIT              		((uint32_t) 0x0000001E)			/*!< 31 bits */
#define QSPI_CTRL0_DFS_32_BIT              		((uint32_t) 0x0000001F)			/*!< 32 bits */

#define QSPI_CTRL0_FRF_Pos						(6U)
#define QSPI_CTRL0_FRF_Msk						(0x3UL << QSPI_CTRL0_FRF_Pos)
#define QSPI_CTRL0_FRF							QSPI_CTRL0_FRF_Msk				/*!< FRF[1:0] bits (Frame Format) */
#define QSPI_CTRL0_FRF_0                        ((uint32_t) 0x00000040)			/*!< Bit 0 */
#define QSPI_CTRL0_FRF_1                        ((uint32_t) 0x00000080)			/*!< Bit 1 */

/*!< Frame Format configuration */
#define QSPI_CTRL0_FRF_MOTOROLA            		((uint32_t) 0x00000000)			/*!< Motorola SPI frame format */
#define QSPI_CTRL0_FRF_TI                  		((uint32_t) 0x00000040)			/*!< TI SSP frame format */
#define QSPI_CTRL0_FRF_MICROWIRE           		((uint32_t) 0x00000080)			

#define QSPI_CTRL0_SCPH_Pos						(8U)
#define QSPI_CTRL0_SCPH_Msk						(0x1UL << QSPI_CTRL0_SCPH_Pos)
#define QSPI_CTRL0_SCPH							QSPI_CTRL0_SCPH_Msk				/*!< SCPH (Serial Clock Phase) */

/*!< Serial Clock Phase configuration */
#define QSPI_CTRL0_SCPH_FIRST_EDGE         		((uint32_t) 0x00000000)			/*!< Capture data at the first edge of serial clock */
#define QSPI_CTRL0_SCPH_SECOND_EDGE        		((uint32_t) 0x00000100)			/*!< Capture data at the second edge of serial clock */

#define QSPI_CTRL0_SCPOL_Pos					(9U)
#define QSPI_CTRL0_SCPOL_Msk					(0x1UL << QSPI_CTRL0_SCPOL_Pos)
#define QSPI_CTRL0_SCPOL						QSPI_CTRL0_SCPOL_Msk			/*!< SCPOL(Serial Clock Polarity) */

/*!< Serial Clock Polarity configuration */
#define QSPI_CTRL0_SCPOL_LOW               		((uint32_t) 0x00000000)			/*!< Serial Clock inactive low */
#define QSPI_CTRL0_SCPOL_HIGH              		((uint32_t) 0x00000200)			/*!< Serial Clock inactive high */

#define QSPI_CTRL0_TMOD_Pos						(10U)
#define QSPI_CTRL0_TMOD_Msk						(0x3UL << QSPI_CTRL0_TMOD_Pos)
#define QSPI_CTRL0_TMOD							QSPI_CTRL0_TMOD_Msk				/*!< TMOD[1:0] bits (Transfer Mode) */
#define QSPI_CTRL0_TMOD_0                       ((uint32_t)0x00000400)			/*!< Bit 0 */
#define QSPI_CTRL0_TMOD_1                       ((uint32_t)0x00000800)			/*!< Bit 1 */

/*!< Transfer Mode configuration */
#define QSPI_CTRL0_TMOD_TX_AND_RX          		((uint32_t) 0x00000000)			/*!< Tx and Rx */
#define QSPI_CTRL0_TMOD_TX_ONLY            		((uint32_t) 0x00000400)			/*!< Tx only */
#define QSPI_CTRL0_TMOD_RX_ONLY            		((uint32_t) 0x00000800)			/*!< Rx only */
#define QSPI_CTRL0_TMOD_EEPROM_READ        		((uint32_t) 0x00000C00)			/*!< EERPOM read */

#define QSPI_CTRL0_SRL_Pos						(13U)
#define QSPI_CTRL0_SRL_Msk						(0x1UL << QSPI_CTRL0_SRL_Pos)
#define QSPI_CTRL0_SRL							QSPI_CTRL0_SRL_Msk				/*!< SRL (Shift Register Loop) */
#define QSPI_CTRL0_SSTE_Pos						(14U)
#define QSPI_CTRL0_SSTE_Msk						(0x1UL << QSPI_CTRL0_SSTE_Pos)
#define QSPI_CTRL0_SSTE							QSPI_CTRL0_SSTE_Msk				/*!< SSTE(Slave Select Toggle Enable) */

#define QSPI_CTRL0_CFS_Pos						(16U)
#define QSPI_CTRL0_CFS_Msk						(0xFUL << QSPI_CTRL0_CFS_Pos)
#define QSPI_CTRL0_CFS							QSPI_CTRL0_CFS_Msk				/*!< CFS[3:0] bits (Control Frame Size) */
#define QSPI_CTRL0_CFS_0                        ((uint32_t) 0x00010000)			/*!< Bit 0 */
#define QSPI_CTRL0_CFS_1                        ((uint32_t) 0x00020000)			/*!< Bit 1 */
#define QSPI_CTRL0_CFS_2                        ((uint32_t) 0x00040000)			/*!< Bit 2 */
#define QSPI_CTRL0_CFS_3                        ((uint32_t) 0x00080000)			/*!< Bit 3 */

/*!< Control Frame Size configuration */
#define QSPI_CTRL0_CFS_1_BIT          	   		((uint32_t) 0x00000000)			/*!< 1 bit */
#define QSPI_CTRL0_CFS_2_BIT          	   		((uint32_t) 0x00010000)			/*!< 2 bits */
#define QSPI_CTRL0_CFS_3_BIT          	   		((uint32_t) 0x00020000)			/*!< 3 bits */
#define QSPI_CTRL0_CFS_4_BIT          	   		((uint32_t) 0x00030000)			/*!< 4 bits */
#define QSPI_CTRL0_CFS_5_BIT          	   		((uint32_t) 0x00040000)			/*!< 5 bits */
#define QSPI_CTRL0_CFS_6_BIT          	   		((uint32_t) 0x00050000)			/*!< 6 bits */
#define QSPI_CTRL0_CFS_7_BIT          	   		((uint32_t) 0x00060000)			/*!< 7 bits */
#define QSPI_CTRL0_CFS_8_BIT          	   		((uint32_t) 0x00070000)			/*!< 8 bits */
#define QSPI_CTRL0_CFS_9_BIT          	   		((uint32_t) 0x00080000)			/*!< 9 bits */
#define QSPI_CTRL0_CFS_10_BIT         	   		((uint32_t) 0x00090000)			/*!< 10 bits */
#define QSPI_CTRL0_CFS_11_BIT         	   		((uint32_t) 0x000A0000)			/*!< 11 bits */
#define QSPI_CTRL0_CFS_12_BIT         	   		((uint32_t) 0x000B0000)			/*!< 12 bits */
#define QSPI_CTRL0_CFS_13_BIT         	   		((uint32_t) 0x000C0000)			/*!< 13 bits */
#define QSPI_CTRL0_CFS_14_BIT         	   		((uint32_t) 0x000D0000)			/*!< 14 bits */
#define QSPI_CTRL0_CFS_15_BIT         	   		((uint32_t) 0x000E0000)			/*!< 15 bits */
#define QSPI_CTRL0_CFS_16_BIT         	   		((uint32_t) 0x000F0000)			/*!< 16 bits */

#define QSPI_CTRL0_SPI_FRF_Pos					(22U)
#define QSPI_CTRL0_SPI_FRF_Msk					(0x3UL << QSPI_CTRL0_SPI_FRF_Pos)
#define QSPI_CTRL0_SPI_FRF						QSPI_CTRL0_SPI_FRF_Msk			/*!< SPI_FRF[1:0] bits (SPI Frame Format) */
#define QSPI_CTRL0_SPI_FRF_0                    ((uint32_t) 0x00400000)			/*!< Bit 0 */
#define QSPI_CTRL0_SPI_FRF_1                    ((uint32_t) 0x00800000)			/*!< Bit 1 */

/*!< SPI Frame Format configuration */
#define QSPI_CTRL0_SPI_FRF_STANDARD_FORMAT 		((uint32_t) 0x00000000)			/*!< Standard SPI */
#define QSPI_CTRL0_SPI_FRF_DUAL_FORMAT     		((uint32_t) 0x00400000)			/*!< Dual-line SPI */
#define QSPI_CTRL0_SPI_FRF_QUAD_FORMAT     		((uint32_t) 0x00800000)			/*!< Quad-line SPI */
 
/******************  Bit definition for QSPI_CTRL1 register  ******************/
#define QSPI_CTRL1_NDF_Pos						(0U)
#define QSPI_CTRL1_NDF_Msk						(0xFFFFUL << QSPI_CTRL1_NDF_Pos)
#define QSPI_CTRL1_NDF							QSPI_CTRL1_NDF_Msk				/*!< NDF[15:0] bits (Numver of Data Frames) */
#define QSPI_CTRL1_NDF_0                        ((uint32_t) 0x00000001)			/*!< Bit 0 */
#define QSPI_CTRL1_NDF_1                        ((uint32_t) 0x00000002)			/*!< Bit 1 */
#define QSPI_CTRL1_NDF_2                        ((uint32_t) 0x00000004)			/*!< Bit 2 */
#define QSPI_CTRL1_NDF_3                        ((uint32_t) 0x00000008)			/*!< Bit 3 */
#define QSPI_CTRL1_NDF_4                        ((uint32_t) 0x00000010)			/*!< Bit 4 */
#define QSPI_CTRL1_NDF_5                        ((uint32_t) 0x00000020)			/*!< Bit 5 */
#define QSPI_CTRL1_NDF_6                        ((uint32_t) 0x00000040)			/*!< Bit 6 */
#define QSPI_CTRL1_NDF_7                        ((uint32_t) 0x00000080)			/*!< Bit 7 */
#define QSPI_CTRL1_NDF_8                        ((uint32_t) 0x00000100)			/*!< Bit 8 */
#define QSPI_CTRL1_NDF_9                        ((uint32_t) 0x00000200)			/*!< Bit 9 */
#define QSPI_CTRL1_NDF_10                       ((uint32_t) 0x00000400)			/*!< Bit 10 */
#define QSPI_CTRL1_NDF_11                       ((uint32_t) 0x00000800)			/*!< Bit 11 */
#define QSPI_CTRL1_NDF_12                       ((uint32_t) 0x00001000)			/*!< Bit 12 */
#define QSPI_CTRL1_NDF_13                       ((uint32_t) 0x00002000)			/*!< Bit 13 */
#define QSPI_CTRL1_NDF_14                       ((uint32_t) 0x00004000)			/*!< Bit 14 */
#define QSPI_CTRL1_NDF_15                       ((uint32_t) 0x00008000)			/*!< Bit 15 */

/*******************  Bit definition for QSPI_EN register  ********************/
#define QSPI_EN_QEN_Pos							(0U)
#define QSPI_EN_QEN_Msk							(0x1UL << QSPI_EN_QEN_Pos)
#define QSPI_EN_QEN								QSPI_EN_QEN_Msk					/*!< QEN (QSPI Enable) */

/*****************  Bit definition for QSPI_MW_CTRL register  *****************/
#define QSPI_MW_CTRL_MWMOD_Pos					(0U)
#define QSPI_MW_CTRL_MWMOD_Msk					(0x1UL << QSPI_MW_CTRL_MWMOD_Pos)
#define QSPI_MW_CTRL_MWMOD						QSPI_MW_CTRL_MWMOD_Msk			/*!< MWMO (Microwire Transfer Mode) */

/*!< Microwire Transfer Mode configuration */
#define QSPI_MW_CTRL_MWMOD_UNSEQUENTIAL		  	((uint32_t) 0x00000000)			/*!< Unsequential transfer */	
#define QSPI_MW_CTRL_MWMOD_SEQUENTIAL		  	((uint32_t) 0x00000001)			/*!< Sequential transfer */

#define QSPI_MW_CTRL_MC_DIR_Pos					(1U)
#define QSPI_MW_CTRL_MC_DIR_Msk					(0x1UL << QSPI_MW_CTRL_MC_DIR_Pos)
#define QSPI_MW_CTRL_MC_DIR						QSPI_MW_CTRL_MC_DIR_Msk			/*!< MC_DIR (Direction of Data when Microwire Control) */

/*!< Direction of Data configuration */
#define QSPI_MW_CTRL_MC_DIR_RX              	((uint32_t) 0x00000000)			/*!< Rx */
#define QSPI_MW_CTRL_MC_DIR_TX              	((uint32_t) 0x00000002)			/*!< Tx */

#define QSPI_MW_CTRL_MHS_EN_Pos					(2U)
#define QSPI_MW_CTRL_MHS_EN_Msk					(0x1UL << QSPI_MW_CTRL_MHS_EN_Pos)
#define QSPI_MW_CTRL_MHS_EN						QSPI_MW_CTRL_MHS_EN_Msk			/*!< MHS_EN (Microwire Handshaking Enable) */

/****************  Bit definition for QSPI_SLAVE_EN register  *****************/
#define QSPI_SLAVE_EN_SEN_Pos					(0U)
#define QSPI_SLAVE_EN_SEN_Msk					(0x1UL << QSPI_SLAVE_EN_SEN_Pos)
#define QSPI_SLAVE_EN_SEN						QSPI_SLAVE_EN_SEN_Msk			/*!< SEN (Slave Enable) */
			
/******************  Bit definition for QSPI_BAUD register  *******************/
#define QSPI_BAUD_CLK_DIV_Pos					(0U)
#define QSPI_BAUD_CLK_DIV_Msk					(0xFFFFUL << QSPI_BAUD_CLK_DIV_Pos)
#define QSPI_BAUD_CLK_DIV						QSPI_BAUD_CLK_DIV_Msk			/*!< CLK_DIV[15:0] (Clock Divider) */
#define QSPI_BAUD_CLK_DIV_0                     ((uint32_t) 0x00000001)			/*!< Bit 0 */
#define QSPI_BAUD_CLK_DIV_1                     ((uint32_t) 0x00000002)			/*!< Bit 1 */
#define QSPI_BAUD_CLK_DIV_2                     ((uint32_t) 0x00000004)			/*!< Bit 2 */
#define QSPI_BAUD_CLK_DIV_3                     ((uint32_t) 0x00000008)			/*!< Bit 3 */
#define QSPI_BAUD_CLK_DIV_4                     ((uint32_t) 0x00000010)			/*!< Bit 4 */
#define QSPI_BAUD_CLK_DIV_5                     ((uint32_t) 0x00000020)			/*!< Bit 5 */
#define QSPI_BAUD_CLK_DIV_6                     ((uint32_t) 0x00000040)			/*!< Bit 6 */
#define QSPI_BAUD_CLK_DIV_7                     ((uint32_t) 0x00000080)			/*!< Bit 7 */
#define QSPI_BAUD_CLK_DIV_8                     ((uint32_t) 0x00000100)			/*!< Bit 8 */
#define QSPI_BAUD_CLK_DIV_9                     ((uint32_t) 0x00000200)			/*!< Bit 9 */
#define QSPI_BAUD_CLK_DIV_10                    ((uint32_t) 0x00000400)			/*!< Bit 10 */
#define QSPI_BAUD_CLK_DIV_11                    ((uint32_t) 0x00000800)			/*!< Bit 11 */
#define QSPI_BAUD_CLK_DIV_12                    ((uint32_t) 0x00001000)			/*!< Bit 12 */
#define QSPI_BAUD_CLK_DIV_13                    ((uint32_t) 0x00002000)			/*!< Bit 13 */
#define QSPI_BAUD_CLK_DIV_14                    ((uint32_t) 0x00004000)			/*!< Bit 14 */
#define QSPI_BAUD_CLK_DIV_15                    ((uint32_t) 0x00008000)			/*!< Bit 15 */

/******************  Bit definition for QSPI_TXFT register  *******************/
#define QSPI_TXFT_TEI_Pos						(0U)
#define QSPI_TXFT_TEI_Msk						(0x1FUL << QSPI_TXFT_TEI_Pos)
#define QSPI_TXFT_TEI							QSPI_TXFT_TEI_Msk				/*!< TXFT_TEI[4:0] (Transmit FIFO Threshold to Trigger Empty Interrupt) */
#define QSPI_TXFT_TEI_0                         ((uint32_t) 0x00000001)			/*!< Bit 0 */
#define QSPI_TXFT_TEI_1                         ((uint32_t) 0x00000002)			/*!< Bit 1 */
#define QSPI_TXFT_TEI_2                         ((uint32_t) 0x00000004)			/*!< Bit 2 */
#define QSPI_TXFT_TEI_3                         ((uint32_t) 0x00000008)			/*!< Bit 3 */
#define QSPI_TXFT_TEI_4                         ((uint32_t) 0x00000010)			/*!< Bit 4 */

#define QSPI_TXFT_ST_Pos						(16U)
#define QSPI_TXFT_ST_Msk						(0x1FUL << QSPI_TXFT_ST_Pos)
#define QSPI_TXFT_ST							QSPI_TXFT_ST_Msk				/*!< TXFT_ST[4:0] (Transmit FIFO Threshold to Start to Transfer) */
#define QSPI_TXFT_ST_0                          ((uint32_t) 0x00010000)			/*!< Bit 0 */
#define QSPI_TXFT_ST_1                          ((uint32_t) 0x00020000)			/*!< Bit 1 */
#define QSPI_TXFT_ST_2                          ((uint32_t) 0x00040000)			/*!< Bit 2 */
#define QSPI_TXFT_ST_3                          ((uint32_t) 0x00080000)			/*!< Bit 3 */
#define QSPI_TXFT_ST_4                          ((uint32_t) 0x00100000)			/*!< Bit 4 */

/******************  Bit definition for QSPI_RXFT register  *******************/
#define QSPI_RXFT_TFI_Pos						(0U)
#define QSPI_RXFT_TFI_Msk						(0x1FUL << QSPI_RXFT_TFI_Pos)
#define QSPI_RXFT_TFI							QSPI_RXFT_TFI_Msk				/*!< RXFT_TFI[4:0] (Receive FIFO Threshold to Trigger Full Interrupt) */
#define QSPI_RXFT_TFI_0                         ((uint32_t) 0x00000001)			/*!< Bit 0 */
#define QSPI_RXFT_TFI_1                         ((uint32_t) 0x00000002)			/*!< Bit 1 */
#define QSPI_RXFT_TFI_2                         ((uint32_t) 0x00000004)			/*!< Bit 2 */
#define QSPI_RXFT_TFI_3                         ((uint32_t) 0x00000008)			/*!< Bit 3 */
#define QSPI_RXFT_TFI_4                         ((uint32_t) 0x00000010)			/*!< Bit 4 */

/******************  Bit definition for QSPI_TXFN register  *******************/
#define QSPI_TXFN_TXFN_Pos						(0U)
#define QSPI_TXFN_TXFN_Msk						(0x3FUL << QSPI_TXFN_TXFN_Pos)
#define QSPI_TXFN_TXFN							QSPI_TXFN_TXFN_Msk				/*!< TXFN[5:0] (Numver of Transmit FIFO) */
#define QSPI_TXFN_0                             ((uint32_t) 0x00000001)			/*!< Bit 0 */
#define QSPI_TXFN_1                             ((uint32_t) 0x00000002)			/*!< Bit 1 */
#define QSPI_TXFN_2                             ((uint32_t) 0x00000004)			/*!< Bit 2 */
#define QSPI_TXFN_3                             ((uint32_t) 0x00000008)			/*!< Bit 3 */
#define QSPI_TXFN_4                             ((uint32_t) 0x00000010)			/*!< Bit 4 */
#define QSPI_TXFN_5                             ((uint32_t) 0x00000020)			/*!< Bit 5 */

/******************  Bit definition for QSPI_RXFN register  *******************/
#define QSPI_RXFN_RXFN_Pos						(0U)
#define QSPI_RXFN_RXFN_Msk						(0x3FUL << QSPI_RXFN_RXFN_Pos)
#define QSPI_RXFN_RXFN							QSPI_RXFN_RXFN_Msk				/*!< RXFN[5:0] (Numver of Receive FIFO) */
#define QSPI_RXFN_0                             ((uint32_t) 0x00000001)			/*!< Bit 0 */
#define QSPI_RXFN_1                             ((uint32_t) 0x00000002)			/*!< Bit 1 */
#define QSPI_RXFN_2                             ((uint32_t) 0x00000004)			/*!< Bit 2 */
#define QSPI_RXFN_3                             ((uint32_t) 0x00000008)			/*!< Bit 3 */
#define QSPI_RXFN_4                             ((uint32_t) 0x00000010)			/*!< Bit 4 */
#define QSPI_RXFN_5                             ((uint32_t) 0x00000020)			/*!< Bit 5 */

/*******************  Bit definition for QSPI_STS register  *******************/
#define QSPI_STS_BUSY_Pos						(0U)
#define QSPI_STS_BUSY_Msk						(0x1UL << QSPI_STS_BUSY_Pos)
#define QSPI_STS_BUSY							QSPI_STS_BUSY_Msk				/*!< BUSY (Transfer Busy Flag) */
#define QSPI_STS_TXFNF_Pos						(1U)
#define QSPI_STS_TXFNF_Msk						(0x1UL << QSPI_STS_TXFNF_Pos)
#define QSPI_STS_TXFNF							QSPI_STS_TXFNF_Msk				/*!< TXFNF (Transmit FIFO not Full) */
#define QSPI_STS_TXFE_Pos						(2U)
#define QSPI_STS_TXFE_Msk						(0x1UL << QSPI_STS_TXFE_Pos)
#define QSPI_STS_TXFE							QSPI_STS_TXFE_Msk				/*!< TXFE (Transmit FIFO not Empty) */
#define QSPI_STS_RXFNE_Pos						(3U)
#define QSPI_STS_RXFNE_Msk						(0x1UL << QSPI_STS_RXFNE_Pos)
#define QSPI_STS_RXFNE							QSPI_STS_RXFNE_Msk				/*!< RXFNE (Receive FIFO not Empty) */
#define QSPI_STS_RXFF_Pos						(4U)
#define QSPI_STS_RXFF_Msk						(0x1UL << QSPI_STS_RXFF_Pos)
#define QSPI_STS_RXFF							QSPI_STS_RXFF_Msk				/*!< RXFF (Receive FIFO not Full) */
#define QSPI_STS_TX_ERR_Pos						(5U)
#define QSPI_STS_TX_ERR_Msk						(0x1UL << QSPI_STS_TX_ERR_Pos)
#define QSPI_STS_TX_ERR							QSPI_STS_TX_ERR_Msk				/*!< TX_ERR (Transmit Error) */
#define QSPI_STS_DC_ERR_Pos						(6U)
#define QSPI_STS_DC_ERR_Msk						(0x1UL << QSPI_STS_DC_ERR_Pos)
#define QSPI_STS_DC_ERR							QSPI_STS_DC_ERR_Msk				/*!< DC_ERR (Data Conflict Error) */

/******************  Bit definition for QSPI_IMASK register  ******************/
#define QSPI_IMASK_TXFEIM_Pos					(0U)
#define QSPI_IMASK_TXFEIM_Msk					(0x1UL << QSPI_IMASK_TXFEIM_Pos)
#define QSPI_IMASK_TXFEIM						QSPI_IMASK_TXFEIM_Msk			/*!< TXFEIM (Transmit FIFO Empty Interrupt Mask) */
#define QSPI_IMASK_TXFOIM_Pos					(1U)
#define QSPI_IMASK_TXFOIM_Msk					(0x1UL << QSPI_IMASK_TXFOIM_Pos)
#define QSPI_IMASK_TXFOIM						QSPI_IMASK_TXFOIM_Msk			/*!< TXFOIM (Transmit FIFO Overflow Interrupt Mask) */
#define QSPI_IMASK_RXFUIM_Pos					(2U)
#define QSPI_IMASK_RXFUIM_Msk					(0x1UL << QSPI_IMASK_RXFUIM_Pos)
#define QSPI_IMASK_RXFUIM						QSPI_IMASK_RXFUIM_Msk			/*!< RXFUIM (Receive FIFO Underflow Interrupt Mask) */
#define QSPI_IMASK_RXFOIM_Pos					(3U)
#define QSPI_IMASK_RXFOIM_Msk					(0x1UL << QSPI_IMASK_RXFOIM_Pos)
#define QSPI_IMASK_RXFOIM						QSPI_IMASK_RXFOIM_Msk			/*!< RXFOIM (Receive FIFO Overflow Interrupt Mask) */
#define QSPI_IMASK_RXFFIM_Pos					(4U)
#define QSPI_IMASK_RXFFIM_Msk					(0x1UL << QSPI_IMASK_RXFFIM_Pos)
#define QSPI_IMASK_RXFFIM						QSPI_IMASK_RXFFIM_Msk			/*!< RXFFIM (Receive FIFO Full Interrupt Mask) */
#define QSPI_IMASK_MMCIM_Pos					(5U)
#define QSPI_IMASK_MMCIM_Msk					(0x1UL << QSPI_IMASK_MMCIM_Pos)
#define QSPI_IMASK_MMCIM						QSPI_IMASK_MMCIM_Msk			/*!< MMCIM (Multi-Master Contention Interrupt Mask) */
#define QSPI_IMASK_XRXOIM_Pos					(6U)
#define QSPI_IMASK_XRXOIM_Msk					(0x1UL << QSPI_IMASK_XRXOIM_Pos)
#define QSPI_IMASK_XRXOIM						QSPI_IMASK_XRXOIM_Msk			/*!< XRXOIM (XIP Receive FIFO Overflow Interrupt Mask) */

/******************  Bit definition for QSPI_ISTS register  *******************/
#define QSPI_ISTS_TXFEIS_Pos					(0U)
#define QSPI_ISTS_TXFEIS_Msk					(0x1UL << QSPI_ISTS_TXFEIS_Pos)
#define QSPI_ISTS_TXFEIS						QSPI_ISTS_TXFEIS_Msk			/*!< TXFEIS (Transmit FIFO Empty Interrupt Stasus) */
#define QSPI_ISTS_TXFOIS_Pos					(1U)
#define QSPI_ISTS_TXFOIS_Msk					(0x1UL << QSPI_ISTS_TXFOIS_Pos)
#define QSPI_ISTS_TXFOIS						QSPI_ISTS_TXFOIS_Msk			/*!< TXFOIS (Transmit FIFO Overflow Interrupt Stasus) */
#define QSPI_ISTS_RXFUIS_Pos					(2U)
#define QSPI_ISTS_RXFUIS_Msk					(0x1UL << QSPI_ISTS_RXFUIS_Pos)
#define QSPI_ISTS_RXFUIS						QSPI_ISTS_RXFUIS_Msk			/*!< RXFUIS (Receive FIFO Underflow Interrupt Stasus) */
#define QSPI_ISTS_RXFOIS_Pos					(3U)
#define QSPI_ISTS_RXFOIS_Msk					(0x1UL << QSPI_ISTS_RXFOIS_Pos)
#define QSPI_ISTS_RXFOIS						QSPI_ISTS_RXFOIS_Msk			/*!< RXFOIS (Receive FIFO Overflow Interrupt Stasus) */
#define QSPI_ISTS_RXFFIS_Pos					(4U)
#define QSPI_ISTS_RXFFIS_Msk					(0x1UL << QSPI_ISTS_RXFFIS_Pos)
#define QSPI_ISTS_RXFFIS						QSPI_ISTS_RXFFIS_Msk			/*!< RXFFIS (Receive FIFO Full Interrupt Stasus) */
#define QSPI_ISTS_MMCIS_Pos						(5U)
#define QSPI_ISTS_MMCIS_Msk						(0x1UL << QSPI_ISTS_MMCIS_Pos)
#define QSPI_ISTS_MMCIS							QSPI_ISTS_MMCIS_Msk				/*!< MMCIS (Multi-Master Contention Interrupt Stasus) */
#define QSPI_ISTS_XRXOIS_Pos					(6U)
#define QSPI_ISTS_XRXOIS_Msk					(0x1UL << QSPI_ISTS_XRXOIS_Pos)
#define QSPI_ISTS_XRXOIS						QSPI_ISTS_XRXOIS_Msk			/*!< XRXOIS (XIP Receive FIFO Overflow Interrupt Stasus) */
#define QSPI_ISTS_ICRS                          ((uint32_t) 0x0000007F)			/*!< All bits of interrupt stasus */

/******************  Bit definition for QSPI_RISTS register  ******************/
#define QSPI_RISTS_TXFERIS_Pos					(0U)
#define QSPI_RISTS_TXFERIS_Msk					(0x1UL << QSPI_RISTS_TXFERIS_Pos)
#define QSPI_RISTS_TXFERIS						QSPI_RISTS_TXFERIS_Msk			/*!< TXFERIS (Transmit FIFO Empty Raw Interrupt Stasus) */
#define QSPI_RISTS_TXFORIS_Pos					(1U)
#define QSPI_RISTS_TXFORIS_Msk					(0x1UL << QSPI_RISTS_TXFORIS_Pos)
#define QSPI_RISTS_TXFORIS						QSPI_RISTS_TXFORIS_Msk			/*!< TXFORIS (Transmit FIFO Overflow Raw Interrupt Stasus) */
#define QSPI_RISTS_RXFURIS_Pos					(2U)
#define QSPI_RISTS_RXFURIS_Msk					(0x1UL << QSPI_RISTS_RXFURIS_Pos)
#define QSPI_RISTS_RXFURIS						QSPI_RISTS_RXFURIS_Msk			/*!< RXFURIS (Receive FIFO Underflow Raw Interrupt Stasus) */
#define QSPI_RISTS_RXFORIS_Pos					(3U)
#define QSPI_RISTS_RXFORIS_Msk					(0x1UL << QSPI_RISTS_RXFORIS_Pos)
#define QSPI_RISTS_RXFORIS						QSPI_RISTS_RXFORIS_Msk			/*!< RXFORIS (Receive FIFO Overflow Raw Interrupt Stasus) */
#define QSPI_RISTS_RXFFRIS_Pos					(4U)
#define QSPI_RISTS_RXFFRIS_Msk					(0x1UL << QSPI_RISTS_RXFFRIS_Pos)
#define QSPI_RISTS_RXFFRIS						QSPI_RISTS_RXFFRIS_Msk			/*!< RXFFRIS (Receive FIFO Full Raw Interrupt Stasus) */
#define QSPI_RISTS_MMCRIS_Pos					(5U)
#define QSPI_RISTS_MMCRIS_Msk					(0x1UL << QSPI_RISTS_MMCRIS_Pos)
#define QSPI_RISTS_MMCRIS						QSPI_RISTS_MMCRIS_Msk			/*!< MMCRIS (Multi-Master Contention Raw Interrupt Stasus) */
#define QSPI_RISTS_XRXORIS_Pos					(6U)
#define QSPI_RISTS_XRXORIS_Msk					(0x1UL << QSPI_RISTS_XRXORIS_Pos)
#define QSPI_RISTS_XRXORIS						QSPI_RISTS_XRXORIS_Msk			/*!< XRXORIS (XIP Receive FIFO Overflow Raw Interrupt Stasus) */

/****************  Bit definition for QSPI_TXFOI_CLR register  ****************/
#define QSPI_TXFOI_CLR_TXFOIC_Pos				(0U)
#define QSPI_TXFOI_CLR_TXFOIC_Msk				(0x1UL << QSPI_TXFOI_CLR_TXFOIC_Pos)
#define QSPI_TXFOI_CLR_TXFOIC					QSPI_TXFOI_CLR_TXFOIC_Msk		/*!< TXFOIC (Clear Transmit FIFO Overflow Interrupt) */

/****************  Bit definition for QSPI_RXFOI_CLR register  ****************/
#define QSPI_RXFOI_CLR_RXFOIC_Pos				(0U)
#define QSPI_RXFOI_CLR_RXFOIC_Msk				(0x1UL << QSPI_RXFOI_CLR_RXFOIC_Pos)
#define QSPI_RXFOI_CLR_RXFOIC					QSPI_RXFOI_CLR_RXFOIC_Msk		/*!< RXFOIC (Clear Receive FIFO Overflow Interrupt) */

/****************  Bit definition for QSPI_RXFUI_CLR register  ****************/
#define QSPI_RXFUI_CLR_RXFUIC_Pos				(0U)
#define QSPI_RXFUI_CLR_RXFUIC_Msk				(0x1UL << QSPI_RXFUI_CLR_RXFUIC_Pos)
#define QSPI_RXFUI_CLR_RXFUIC					QSPI_RXFUI_CLR_RXFUIC_Msk		/*!< RXFUIC (Clear Receive FIFO Underflow Interrupt) */

/****************  Bit definition for QSPI_MMCI_CLR register  *****************/
#define QSPI_MMCI_CLR_MMCIC_Pos					(0U)
#define QSPI_MMCI_CLR_MMCIC_Msk					(0x1UL << QSPI_MMCI_CLR_MMCIC_Pos)
#define QSPI_MMCI_CLR_MMCIC						QSPI_MMCI_CLR_MMCIC_Msk			/*!< MMCIC (Clear Multi-Master Contention Interrupt) */

/******************  Bit definition for QSPI_ICLR register  *******************/
#define QSPI_ICLR_INTC_Pos						(0U)
#define QSPI_ICLR_INTC_Msk						(0x1UL << QSPI_ICLR_INTC_Pos)
#define QSPI_ICLR_INTC							QSPI_ICLR_INTC_Msk				/*!< INTC (Clear Interrupts) */

/****************  Bit definition for QSPI_DMA_CTRL register  *****************/
#define QSPI_DMA_CTRL_RX_DMA_EN_Pos				(0U)
#define QSPI_DMA_CTRL_RX_DMA_EN_Msk				(0x1UL << QSPI_DMA_CTRL_RX_DMA_EN_Pos)
#define QSPI_DMA_CTRL_RX_DMA_EN					QSPI_DMA_CTRL_RX_DMA_EN_Msk		/*!< RX_DMA_EN (Receive DMA Enable) */
#define QSPI_DMA_CTRL_TX_DMA_EN_Pos				(1U)
#define QSPI_DMA_CTRL_TX_DMA_EN_Msk				(0x1UL << QSPI_DMA_CTRL_TX_DMA_EN_Pos)
#define QSPI_DMA_CTRL_TX_DMA_EN					QSPI_DMA_CTRL_TX_DMA_EN_Msk		/*!< TX_DMA_EN (Transmit DMA Enable) */

/***************  Bit definition for QSPI_DMATDL_CTRL register  ***************/
#define QSPI_DMATDL_CTRL_DMATDL_Pos				(0U)
#define QSPI_DMATDL_CTRL_DMATDL_Msk				(0x3FUL << QSPI_DMATDL_CTRL_DMATDL_Pos)
#define QSPI_DMATDL_CTRL_DMATDL					QSPI_DMATDL_CTRL_DMATDL_Msk		/*!< DMATDL[5:0] (DMA Transmit Data Level) */
#define QSPI_DMATDL_CTRL_DMATDL_0               ((uint32_t) 0x00000001)			/*!< Bit 0 */
#define QSPI_DMATDL_CTRL_DMATDL_1               ((uint32_t) 0x00000002)			/*!< Bit 1 */
#define QSPI_DMATDL_CTRL_DMATDL_2               ((uint32_t) 0x00000004)			/*!< Bit 2 */
#define QSPI_DMATDL_CTRL_DMATDL_3               ((uint32_t) 0x00000008)			/*!< Bit 3 */
#define QSPI_DMATDL_CTRL_DMATDL_4               ((uint32_t) 0x00000010)			/*!< Bit 4 */
#define QSPI_DMATDL_CTRL_DMATDL_5               ((uint32_t) 0x00000020)			/*!< Bit 5 */

/***************  Bit definition for QSPI_DMARDL_CTRL register  ***************/
#define QSPI_DMARDL_CTRL_DMARDL_Pos				(0U)
#define QSPI_DMARDL_CTRL_DMARDL_Msk				(0x3FUL << QSPI_DMARDL_CTRL_DMARDL_Pos)
#define QSPI_DMARDL_CTRL_DMARDL					QSPI_DMARDL_CTRL_DMARDL_Msk		/*!< DMARDL[5:0] (DMA Receive Data Level) */
#define QSPI_DMARDL_CTRL_DMARDL_0               ((uint32_t) 0x00000001)			/*!< Bit 0 */
#define QSPI_DMARDL_CTRL_DMARDL_1               ((uint32_t) 0x00000002)			/*!< Bit 1 */
#define QSPI_DMARDL_CTRL_DMARDL_2               ((uint32_t) 0x00000004)			/*!< Bit 2 */
#define QSPI_DMARDL_CTRL_DMARDL_3               ((uint32_t) 0x00000008)			/*!< Bit 3 */
#define QSPI_DMARDL_CTRL_DMARDL_4               ((uint32_t) 0x00000010)			/*!< Bit 4 */
#define QSPI_DMARDL_CTRL_DMARDL_5               ((uint32_t) 0x00000020)			/*!< Bit 5 */

/*****************  Bit definition for QSPI_IDCODE register  ******************/
#define QSPI_IDCODE_IDCODE_Pos					(0U)
#define QSPI_IDCODE_IDCODE_Msk					(0xFFFFFFFFUL << QSPI_IDCODE_IDCODE_Pos)
#define QSPI_IDCODE_IDCODE						QSPI_IDCODE_IDCODE_Msk			/*!< IDCODE[31:0] (Identification Code) */
#define QSPI_IDCODE_IDCODE_0 					((uint32_t) 0x00000001)			/*!< Bit 0  */
#define QSPI_IDCODE_IDCODE_1 					((uint32_t) 0x00000002)			/*!< Bit 1  */
#define QSPI_IDCODE_IDCODE_2 					((uint32_t) 0x00000004)			/*!< Bit 2  */
#define QSPI_IDCODE_IDCODE_3 					((uint32_t) 0x00000008)			/*!< Bit 3  */
#define QSPI_IDCODE_IDCODE_4 					((uint32_t) 0x00000010)			/*!< Bit 4  */
#define QSPI_IDCODE_IDCODE_5 					((uint32_t) 0x00000020)			/*!< Bit 5  */
#define QSPI_IDCODE_IDCODE_6 					((uint32_t) 0x00000040)			/*!< Bit 6  */
#define QSPI_IDCODE_IDCODE_7 					((uint32_t) 0x00000080)			/*!< Bit 7  */
#define QSPI_IDCODE_IDCODE_8 					((uint32_t) 0x00000100)			/*!< Bit 8  */
#define QSPI_IDCODE_IDCODE_9 					((uint32_t) 0x00000200)			/*!< Bit 9  */
#define QSPI_IDCODE_IDCODE_10					((uint32_t) 0x00000400)			/*!< Bit 10 */
#define QSPI_IDCODE_IDCODE_11					((uint32_t) 0x00000800)			/*!< Bit 11 */
#define QSPI_IDCODE_IDCODE_12					((uint32_t) 0x00001000)			/*!< Bit 12 */
#define QSPI_IDCODE_IDCODE_13					((uint32_t) 0x00002000)			/*!< Bit 13 */
#define QSPI_IDCODE_IDCODE_14					((uint32_t) 0x00004000)			/*!< Bit 14 */
#define QSPI_IDCODE_IDCODE_15					((uint32_t) 0x00008000)			/*!< Bit 15 */
#define QSPI_IDCODE_IDCODE_16					((uint32_t) 0x00010000)			/*!< Bit 16 */
#define QSPI_IDCODE_IDCODE_17					((uint32_t) 0x00020000)			/*!< Bit 17 */
#define QSPI_IDCODE_IDCODE_18					((uint32_t) 0x00040000)			/*!< Bit 18 */
#define QSPI_IDCODE_IDCODE_19					((uint32_t) 0x00080000)			/*!< Bit 19 */
#define QSPI_IDCODE_IDCODE_20					((uint32_t) 0x00100000)			/*!< Bit 20 */
#define QSPI_IDCODE_IDCODE_21					((uint32_t) 0x00200000)			/*!< Bit 21 */
#define QSPI_IDCODE_IDCODE_22					((uint32_t) 0x00400000)			/*!< Bit 22 */
#define QSPI_IDCODE_IDCODE_23					((uint32_t) 0x00800000)			/*!< Bit 23 */
#define QSPI_IDCODE_IDCODE_24					((uint32_t) 0x01000000)			/*!< Bit 24 */
#define QSPI_IDCODE_IDCODE_25					((uint32_t) 0x02000000)			/*!< Bit 25 */
#define QSPI_IDCODE_IDCODE_26					((uint32_t) 0x04000000)			/*!< Bit 26 */
#define QSPI_IDCODE_IDCODE_27					((uint32_t) 0x08000000)			/*!< Bit 27 */
#define QSPI_IDCODE_IDCODE_28					((uint32_t) 0x10000000)			/*!< Bit 28 */
#define QSPI_IDCODE_IDCODE_29					((uint32_t) 0x20000000)			/*!< Bit 29 */
#define QSPI_IDCODE_IDCODE_30					((uint32_t) 0x40000000)			/*!< Bit 30 */
#define QSPI_IDCODE_IDCODE_31					((uint32_t) 0x80000000)			/*!< Bit 31 */

/*************  Bit definition for QSPI_DAT0~QSPI_DAT31 register  *************/
#define QSPI_DATA_DATA_Pos						(0U)
#define QSPI_DATA_DATA_Msk						(0xFFFFFFFFUL << QSPI_DATA_DATA_Pos)
#define QSPI_DATA_DATA							QSPI_DATA_DATA_Msk				/*!< QSPI_DAT[31:0] (DATA Register) */
#define QSPI_DATA_DATA_0 						((uint32_t) 0x00000001)			/*!< Bit 0  */
#define QSPI_DATA_DATA_1 						((uint32_t) 0x00000002)			/*!< Bit 1  */
#define QSPI_DATA_DATA_2 						((uint32_t) 0x00000004)			/*!< Bit 2  */
#define QSPI_DATA_DATA_3 						((uint32_t) 0x00000008)			/*!< Bit 3  */
#define QSPI_DATA_DATA_4 						((uint32_t) 0x00000010)			/*!< Bit 4  */
#define QSPI_DATA_DATA_5 						((uint32_t) 0x00000020)			/*!< Bit 5  */
#define QSPI_DATA_DATA_6 						((uint32_t) 0x00000040)			/*!< Bit 6  */
#define QSPI_DATA_DATA_7 						((uint32_t) 0x00000080)			/*!< Bit 7  */
#define QSPI_DATA_DATA_8 						((uint32_t) 0x00000100)			/*!< Bit 8  */
#define QSPI_DATA_DATA_9 						((uint32_t) 0x00000200)			/*!< Bit 9  */
#define QSPI_DATA_DATA_10						((uint32_t) 0x00000400)			/*!< Bit 10 */
#define QSPI_DATA_DATA_11						((uint32_t) 0x00000800)			/*!< Bit 11 */
#define QSPI_DATA_DATA_12						((uint32_t) 0x00001000)			/*!< Bit 12 */
#define QSPI_DATA_DATA_13						((uint32_t) 0x00002000)			/*!< Bit 13 */
#define QSPI_DATA_DATA_14						((uint32_t) 0x00004000)			/*!< Bit 14 */
#define QSPI_DATA_DATA_15						((uint32_t) 0x00008000)			/*!< Bit 15 */
#define QSPI_DATA_DATA_16						((uint32_t) 0x00010000)			/*!< Bit 16 */
#define QSPI_DATA_DATA_17						((uint32_t) 0x00020000)			/*!< Bit 17 */
#define QSPI_DATA_DATA_18						((uint32_t) 0x00040000)			/*!< Bit 18 */
#define QSPI_DATA_DATA_19						((uint32_t) 0x00080000)			/*!< Bit 19 */
#define QSPI_DATA_DATA_20						((uint32_t) 0x00100000)			/*!< Bit 20 */
#define QSPI_DATA_DATA_21						((uint32_t) 0x00200000)			/*!< Bit 21 */
#define QSPI_DATA_DATA_22						((uint32_t) 0x00400000)			/*!< Bit 22 */
#define QSPI_DATA_DATA_23						((uint32_t) 0x00800000)			/*!< Bit 23 */
#define QSPI_DATA_DATA_24						((uint32_t) 0x01000000)			/*!< Bit 24 */
#define QSPI_DATA_DATA_25						((uint32_t) 0x02000000)			/*!< Bit 25 */
#define QSPI_DATA_DATA_26						((uint32_t) 0x04000000)			/*!< Bit 26 */
#define QSPI_DATA_DATA_27						((uint32_t) 0x08000000)			/*!< Bit 27 */
#define QSPI_DATA_DATA_28						((uint32_t) 0x10000000)			/*!< Bit 28 */
#define QSPI_DATA_DATA_29						((uint32_t) 0x20000000)			/*!< Bit 29 */
#define QSPI_DATA_DATA_30						((uint32_t) 0x40000000)			/*!< Bit 30 */
#define QSPI_DATA_DATA_31						((uint32_t) 0x80000000)			/*!< Bit 31 */

/****************  Bit definition for QSPI_RS_DELAY register  *****************/
#define QSPI_RS_DELAY_SDCN_Pos					(0U)
#define QSPI_RS_DELAY_SDCN_Msk					(0xFFUL << QSPI_RS_DELAY_SDCN_Pos)
#define QSPI_RS_DELAY_SDCN						QSPI_RS_DELAY_SDCN_Msk			/*!< SDCN[7:0] (Sample Delay Cycle Number) */
#define QSPI_RS_DELAY_SDCN_0                    ((uint32_t) 0x00000001)			/*!< Bit 0 */
#define QSPI_RS_DELAY_SDCN_1                    ((uint32_t) 0x00000002)			/*!< Bit 1 */
#define QSPI_RS_DELAY_SDCN_2                    ((uint32_t) 0x00000004)			/*!< Bit 2 */
#define QSPI_RS_DELAY_SDCN_3                    ((uint32_t) 0x00000008)			/*!< Bit 3 */
#define QSPI_RS_DELAY_SDCN_4                    ((uint32_t) 0x00000010)			/*!< Bit 4 */
#define QSPI_RS_DELAY_SDCN_5                    ((uint32_t) 0x00000020)			/*!< Bit 5 */
#define QSPI_RS_DELAY_SDCN_6                    ((uint32_t) 0x00000040)			/*!< Bit 6 */
#define QSPI_RS_DELAY_SDCN_7                    ((uint32_t) 0x00000080)			/*!< Bit 7 */

/*!< Sample Delay Cycle Number configuration */
#define QSPI_RS_DELAY_SDCN_0_CYCLES    			((uint32_t) 0x00)				/*!< Delay 0 ssi_clk cycles */
#define QSPI_RS_DELAY_SDCN_1_CYCLES    			((uint32_t) 0x01)				/*!< Delay 1 ssi_clk cycles */
#define QSPI_RS_DELAY_SDCN_2_CYCLES    			((uint32_t) 0x02)				/*!< Delay 2 ssi_clk cycles */
#define QSPI_RS_DELAY_SDCN_3_CYCLES    			((uint32_t) 0x03)				/*!< Delay 3 ssi_clk cycles */
#define QSPI_RS_DELAY_SDCN_4_CYCLES    			((uint32_t) 0x04)				/*!< Delay 4 ssi_clk cycles */
#define QSPI_RS_DELAY_SDCN_5_CYCLES    			((uint32_t) 0x05)				/*!< Delay 5 ssi_clk cycles */
#define QSPI_RS_DELAY_SDCN_6_CYCLES    			((uint32_t) 0x06)				/*!< Delay 6 ssi_clk cycles */

#define QSPI_RS_DELAY_SES_Pos					(16U)
#define QSPI_RS_DELAY_SES_MSk					(0x1UL << QSPI_RS_DELAY_SES_Pos)
#define QSPI_RS_DELAY_SES						QSPI_RS_DELAY_SES_MSk			/*!< SES (Sample Edge Select of Receive Data) */

/*!< Sample Edge Select of Receive Data configuration */
#define QSPI_RS_DELAY_SES_RISING_EDGE  			((uint32_t) 0x00000000)			/*!< Sample at rising edge */
#define QSPI_RS_DELAY_SES_FALLING_EDGE 			((uint32_t) 0x00010000)			/*!< Sample at falling edge */

/****************  Bit definition for QSPI_ENH_CTRL0 register  ****************/
#define QSPI_ENH_CTRL0_TRANS_TYPE_Pos			(0U)
#define QSPI_ENH_CTRL0_TRANS_TYPE_Msk			(0x3UL << QSPI_ENH_CTRL0_TRANS_TYPE_Pos)
#define QSPI_ENH_CTRL0_TRANS_TYPE				QSPI_ENH_CTRL0_TRANS_TYPE_Msk	/*!< TRANS_TYPE[1:0] (Address and instruction transfer format) */
#define QSPI_ENH_CTRL0_TRANS_TYPE_0             ((uint32_t) 0x00000001)			/*!< Bit 0 */
#define QSPI_ENH_CTRL0_TRANS_TYPE_1             ((uint32_t) 0x00000002)			/*!< Bit 1 */

/*!< Address and instruction transfer format configuration */
#define QSPI_ENH_CTRL0_TRANS_TYPE_STANDARD       ((uint32_t) 0x00000000)		/*!< Both instruction and address transfer by standard SPI mode */
#define QSPI_ENH_CTRL0_TRANS_TYPE_ADDRESS_BY_FRF ((uint32_t) 0x00000001)        /*!< Instruction transfer by standard SPI mode, address transfer by QSPI_ CTRL0.SPI_FRF customized mode */
#define QSPI_ENH_CTRL0_TRANS_TYPE_ALL_BY_FRF     ((uint32_t) 0x00000002)        /*!< Both instruction and address transfer by QSPI_ CTRL0.SPI_FRF customized mode */

#define QSPI_ENH_CTRL0_ADDR_LEN_Pos				(2U)
#define QSPI_ENH_CTRL0_ADDR_LEN_Msk				(0xFUL << QSPI_ENH_CTRL0_ADDR_LEN_Pos)
#define QSPI_ENH_CTRL0_ADDR_LEN					QSPI_ENH_CTRL0_ADDR_LEN_Msk		/*!< ADDR_LEN[3:0] (Length of Address to transmit) */
#define QSPI_ENH_CTRL0_ADDR_LEN_0               ((uint32_t) 0x00000004)			/*!< Bit 0 */
#define QSPI_ENH_CTRL0_ADDR_LEN_1               ((uint32_t) 0x00000008)			/*!< Bit 1 */
#define QSPI_ENH_CTRL0_ADDR_LEN_2               ((uint32_t) 0x00000010)			/*!< Bit 2 */
#define QSPI_ENH_CTRL0_ADDR_LEN_3               ((uint32_t) 0x00000020)			/*!< Bit 3 */

/*!< Length of Address to transmit configuration */
#define QSPI_ENH_CTRL0_ADDR_LEN_4_BIT           ((uint32_t) 0x00000004)			/*!< 4 bits  */
#define QSPI_ENH_CTRL0_ADDR_LEN_8_BIT           ((uint32_t) 0x00000008)         /*!< 8 bits  */
#define QSPI_ENH_CTRL0_ADDR_LEN_12_BIT          ((uint32_t) 0x0000000C)         /*!< 12 bits */
#define QSPI_ENH_CTRL0_ADDR_LEN_16_BIT          ((uint32_t) 0x00000010)         /*!< 16 bits */
#define QSPI_ENH_CTRL0_ADDR_LEN_20_BIT          ((uint32_t) 0x00000014)         /*!< 20 bits */
#define QSPI_ENH_CTRL0_ADDR_LEN_24_BIT          ((uint32_t) 0x00000018)         /*!< 24 bits */
#define QSPI_ENH_CTRL0_ADDR_LEN_28_BIT          ((uint32_t) 0x0000001C)         /*!< 28 bits */
#define QSPI_ENH_CTRL0_ADDR_LEN_32_BIT          ((uint32_t) 0x00000020)         /*!< 32 bits */
#define QSPI_ENH_CTRL0_ADDR_LEN_36_BIT          ((uint32_t) 0x00000024)         /*!< 36 bits */
#define QSPI_ENH_CTRL0_ADDR_LEN_40_BIT          ((uint32_t) 0x00000028)         /*!< 40 bits */
#define QSPI_ENH_CTRL0_ADDR_LEN_44_BIT          ((uint32_t) 0x0000002C)         /*!< 44 bits */
#define QSPI_ENH_CTRL0_ADDR_LEN_48_BIT          ((uint32_t) 0x00000030)         /*!< 48 bits */
#define QSPI_ENH_CTRL0_ADDR_LEN_52_BIT          ((uint32_t) 0x00000034)         /*!< 52 bits */
#define QSPI_ENH_CTRL0_ADDR_LEN_56_BIT          ((uint32_t) 0x00000038)         /*!< 56 bits */
#define QSPI_ENH_CTRL0_ADDR_LEN_60_BIT          ((uint32_t) 0x0000003C)         /*!< 60 bits */

#define QSPI_ENH_CTRL0_MD_BIT_EN_Pos			(7U)
#define QSPI_ENH_CTRL0_MD_BIT_EN_Msk			(0x1UL << QSPI_ENH_CTRL0_MD_BIT_EN_Pos)
#define QSPI_ENH_CTRL0_MD_BIT_EN				QSPI_ENH_CTRL0_MD_BIT_EN_Msk	/*!< MD_BIT_EN (Mode bits enable in XIP mode) */

#define QSPI_ENH_CTRL0_INST_L_Pos				(8U)
#define QSPI_ENH_CTRL0_INST_L_Msk				(0x3UL << QSPI_ENH_CTRL0_INST_L_Pos)
#define QSPI_ENH_CTRL0_INST_L					QSPI_ENH_CTRL0_INST_L_Msk		/*!< INST_L[1:0] (Dual/Quad mode instruction length in bits) */
#define QSPI_ENH_CTRL0_INST_L_0                 ((uint32_t) 0x00000100)			/*!< Bit 0 */
#define QSPI_ENH_CTRL0_INST_L_1                 ((uint32_t) 0x00000200)			/*!< Bit 1 */

/*!< Dual/Quad mode instruction length configuration */
#define QSPI_ENH_CTRL0_INST_L_0_LINE       		((uint32_t) 0x00000000)			/*!< 0 bit  */
#define QSPI_ENH_CTRL0_INST_L_4_LINE       		((uint32_t) 0x00000100)         /*!< 4 bits  */
#define QSPI_ENH_CTRL0_INST_L_8_LINE       		((uint32_t) 0x00000200)         /*!< 8 bits  */
#define QSPI_ENH_CTRL0_INST_L_16_LINE      		((uint32_t) 0x00000300)         /*!< 16 bits */

#define QSPI_ENH_CTRL0_WAIT_CYCLES_Pos			(11U)
#define QSPI_ENH_CTRL0_WAIT_CYCLES_Msk			(0x1FUL << QSPI_ENH_CTRL0_WAIT_CYCLES_Pos)
#define QSPI_ENH_CTRL0_WAIT_CYCLES				QSPI_ENH_CTRL0_WAIT_CYCLES_Msk	/*!< WAIT_CYCLES[4:0] (Wait Cycles in Dual/Quad mode between control frames transmit and data reception) */
#define QSPI_ENH_CTRL0_WAIT_CYCLES_0            ((uint32_t) 0x00000800)			/*!< Bit 0 */
#define QSPI_ENH_CTRL0_WAIT_CYCLES_1            ((uint32_t) 0x00001000)			/*!< Bit 1 */
#define QSPI_ENH_CTRL0_WAIT_CYCLES_2            ((uint32_t) 0x00002000)			/*!< Bit 2 */
#define QSPI_ENH_CTRL0_WAIT_CYCLES_3            ((uint32_t) 0x00004000)			/*!< Bit 3 */
#define QSPI_ENH_CTRL0_WAIT_CYCLES_4            ((uint32_t) 0x00008000)			/*!< Bit 4 */
#define QSPI_ENH_CTRL0_WAIT_1CYCLES             ((uint32_t) 0x00000800)			/*!< Wait 1 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_ENH_CTRL0_WAIT_2CYCLES             ((uint32_t) 0x00001000)			/*!< Wait 2 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_ENH_CTRL0_WAIT_3CYCLES             ((uint32_t) 0x00001800)			/*!< Wait 3 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_ENH_CTRL0_WAIT_4CYCLES             ((uint32_t) 0x00002000)			/*!< Wait 4 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_ENH_CTRL0_WAIT_5CYCLES             ((uint32_t) 0x00002800)			/*!< Wait 5 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_ENH_CTRL0_WAIT_6CYCLES             ((uint32_t) 0x00003000)			/*!< Wait 6 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_ENH_CTRL0_WAIT_7CYCLES             ((uint32_t) 0x00003800)			/*!< Wait 7 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_ENH_CTRL0_WAIT_8CYCLES             ((uint32_t) 0x00004000)			/*!< Wait 8 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_ENH_CTRL0_WAIT_9CYCLES             ((uint32_t) 0x00004800)			/*!< Wait 9 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_ENH_CTRL0_WAIT_10CYCLES            ((uint32_t) 0x00005000)			/*!< Wait 10 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_ENH_CTRL0_WAIT_11CYCLES            ((uint32_t) 0x00005800)			/*!< Wait 11 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_ENH_CTRL0_WAIT_12CYCLES            ((uint32_t) 0x00006000)			/*!< Wait 12 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_ENH_CTRL0_WAIT_13CYCLES            ((uint32_t) 0x00006800)			/*!< Wait 13 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_ENH_CTRL0_WAIT_14CYCLES            ((uint32_t) 0x00007000)			/*!< Wait 14 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_ENH_CTRL0_WAIT_15CYCLES            ((uint32_t) 0x00007800)			/*!< Wait 15 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_ENH_CTRL0_WAIT_16CYCLES            ((uint32_t) 0x00008000)			/*!< Wait 16 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_ENH_CTRL0_WAIT_17CYCLES            ((uint32_t) 0x00008800)			/*!< Wait 17 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_ENH_CTRL0_WAIT_18CYCLES            ((uint32_t) 0x00009000)			/*!< Wait 18 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_ENH_CTRL0_WAIT_19CYCLES            ((uint32_t) 0x00009800)			/*!< Wait 19 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_ENH_CTRL0_WAIT_20CYCLES            ((uint32_t) 0x0000A000)			/*!< Wait 20 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_ENH_CTRL0_WAIT_21CYCLES            ((uint32_t) 0x0000A800)			/*!< Wait 21 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_ENH_CTRL0_WAIT_22CYCLES            ((uint32_t) 0x0000B000)			/*!< Wait 22 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_ENH_CTRL0_WAIT_23CYCLES            ((uint32_t) 0x0000B800)			/*!< Wait 23 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_ENH_CTRL0_WAIT_24CYCLES            ((uint32_t) 0x0000C000)			/*!< Wait 24 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_ENH_CTRL0_WAIT_25CYCLES            ((uint32_t) 0x0000C800)			/*!< Wait 25 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_ENH_CTRL0_WAIT_26CYCLES            ((uint32_t) 0x0000D000)			/*!< Wait 26 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_ENH_CTRL0_WAIT_27CYCLES            ((uint32_t) 0x0000D800)			/*!< Wait 27 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_ENH_CTRL0_WAIT_28CYCLES            ((uint32_t) 0x0000E000)			/*!< Wait 28 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_ENH_CTRL0_WAIT_29CYCLES            ((uint32_t) 0x0000E800)			/*!< Wait 29 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_ENH_CTRL0_WAIT_30CYCLES            ((uint32_t) 0x0000F000)			/*!< Wait 30 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_ENH_CTRL0_WAIT_31CYCLES            ((uint32_t) 0x0000F800)			/*!< Wait 31 Cycles in Dual/Duad mode between control frames transmit and data reception */

#define QSPI_ENH_CTRL0_SPI_DDR_EN_Pos			(16U)
#define QSPI_ENH_CTRL0_SPI_DDR_EN_Msk			(0x1UL << QSPI_ENH_CTRL0_SPI_DDR_EN_Pos)
#define QSPI_ENH_CTRL0_SPI_DDR_EN				QSPI_ENH_CTRL0_SPI_DDR_EN_Msk	/*!< SPI_DDR_EN (SPI DDR Enable) */
#define QSPI_ENH_CTRL0_INST_DDR_EN_Pos			(17U)
#define QSPI_ENH_CTRL0_INST_DDR_EN_Msk			(0x1UL << QSPI_ENH_CTRL0_INST_DDR_EN_Pos)
#define QSPI_ENH_CTRL0_INST_DDR_EN				QSPI_ENH_CTRL0_INST_DDR_EN_Msk	/*!< INST_DDR_EN (XIP instruction enable) */
#define QSPI_ENH_CTRL0_XIP_DFS_HC_Pos			(19U)
#define QSPI_ENH_CTRL0_XIP_DFS_HC_Msk			(0x1UL << QSPI_ENH_CTRL0_XIP_DFS_HC_Pos)
#define QSPI_ENH_CTRL0_XIP_DFS_HC				QSPI_ENH_CTRL0_XIP_DFS_HC_Msk	/*!< XIP_DFS_HC (Fix DFS for XIP transfers) */
#define QSPI_ENH_CTRL0_XIP_INST_EN_Pos			(20U)
#define QSPI_ENH_CTRL0_XIP_INST_EN_Msk			(0x1UL << QSPI_ENH_CTRL0_XIP_INST_EN_Pos)
#define QSPI_ENH_CTRL0_XIP_INST_EN				QSPI_ENH_CTRL0_XIP_INST_EN_Msk	/*!< XIP_INST_EN (XIP instruction enable) */
#define QSPI_ENH_CTRL0_XIP_CT_EN_Pos			(21U)
#define QSPI_ENH_CTRL0_XIP_CT_EN_Msk			(0x1UL << QSPI_ENH_CTRL0_XIP_CT_EN_Pos)
#define QSPI_ENH_CTRL0_XIP_CT_EN				QSPI_ENH_CTRL0_XIP_CT_EN_Msk	/*!< XIP_CT_EN (Enable Continuous Transfer in XIP mode) */

#define QSPI_ENH_CTRL0_XIP_MBL_Pos				(26U)
#define QSPI_ENH_CTRL0_XIP_MBL_Msk				(0x3UL << QSPI_ENH_CTRL0_XIP_MBL_Pos)
#define QSPI_ENH_CTRL0_XIP_MBL					QSPI_ENH_CTRL0_XIP_MBL_Msk		/*!< XIP_MBL[1:0] (XIP Mode bits length) */
#define QSPI_ENH_CTRL0_XIP_MBL_0                ((uint32_t) 0x04000000)			/*!< Bit 0 */
#define QSPI_ENH_CTRL0_XIP_MBL_1                ((uint32_t) 0x08000000)			/*!< Bit 1 */

/*!< XIP Mode bits length configuration */
#define QSPI_ENH_CTRL0_XIP_MBL_2_BIT   			((uint32_t) 0x00000000)			/*!< 2 bits  */
#define QSPI_ENH_CTRL0_XIP_MBL_4_BIT   			((uint32_t) 0x04000000)         /*!< 4 bits  */
#define QSPI_ENH_CTRL0_XIP_MBL_8_BIT   			((uint32_t) 0x08000000)         /*!< 8 bits  */
#define QSPI_ENH_CTRL0_XIP_MBL_16_BIT  			((uint32_t) 0x0C000000)         /*!< 16 bits */

#define QSPI_ENH_CTRL0_CLK_STRETCH_EN_Pos		(30U)
#define QSPI_ENH_CTRL0_CLK_STRETCH_EN_Msk		(0x1UL << QSPI_ENH_CTRL0_CLK_STRETCH_EN_Pos)
#define QSPI_ENH_CTRL0_CLK_STRETCH_EN			QSPI_ENH_CTRL0_CLK_STRETCH_EN_Msk	/*!< CLK_STRETCH_EN (Enable Continuous Transfer in XIP mode) */

/****************  Bit definition for QSPI_DDR_TXDE register  *****************/
#define QSPI_DDR_TXDE_TXDE_Pos					(0U)
#define QSPI_DDR_TXDE_TXDE_Msk					(0xFFUL << QSPI_DDR_TXDE_TXDE_Pos)
#define QSPI_DDR_TXDE_TXDE						QSPI_DDR_TXDE_TXDE_Msk			/*!< TXDE[7:0] (Transmit Drive Edge) */
#define QSPI_DDR_TXDE_TXDE_0                    ((uint32_t) 0x00000001)			/*!< Bit 0 */
#define QSPI_DDR_TXDE_TXDE_1                    ((uint32_t) 0x00000002)			/*!< Bit 1 */
#define QSPI_DDR_TXDE_TXDE_2                    ((uint32_t) 0x00000004)			/*!< Bit 2 */
#define QSPI_DDR_TXDE_TXDE_3                    ((uint32_t) 0x00000008)			/*!< Bit 3 */
#define QSPI_DDR_TXDE_TXDE_4                    ((uint32_t) 0x00000010)			/*!< Bit 4 */
#define QSPI_DDR_TXDE_TXDE_5                    ((uint32_t) 0x00000020)			/*!< Bit 5 */
#define QSPI_DDR_TXDE_TXDE_6                    ((uint32_t) 0x00000040)			/*!< Bit 6 */
#define QSPI_DDR_TXDE_TXDE_7                    ((uint32_t) 0x00000080)			/*!< Bit 7 */

/****************  Bit definition for QSPI_XIP_MODE register  *****************/
#define QSPI_XIP_MODE_XIP_MD_BITS_Pos			(0U)
#define QSPI_XIP_MODE_XIP_MD_BITS_Msk			(0xFFFFUL << QSPI_XIP_MODE_XIP_MD_BITS_Pos)
#define QSPI_XIP_MODE_XIP_MD_BITS				QSPI_XIP_MODE_XIP_MD_BITS_Msk	/*!< XIP_MD_BITS[15:0] (XIP mode bits to be sent after address phase of XIP transfer) */
#define QSPI_XIP_MODE_XIP_MD_BITS_0        		((uint32_t) 0x00000001)			/*!< Bit 0  */
#define QSPI_XIP_MODE_XIP_MD_BITS_1        		((uint32_t) 0x00000002)			/*!< Bit 1  */
#define QSPI_XIP_MODE_XIP_MD_BITS_2        		((uint32_t) 0x00000004)			/*!< Bit 2  */
#define QSPI_XIP_MODE_XIP_MD_BITS_3        		((uint32_t) 0x00000008)			/*!< Bit 3  */
#define QSPI_XIP_MODE_XIP_MD_BITS_4        		((uint32_t) 0x00000010)			/*!< Bit 4  */
#define QSPI_XIP_MODE_XIP_MD_BITS_5        		((uint32_t) 0x00000020)			/*!< Bit 5  */
#define QSPI_XIP_MODE_XIP_MD_BITS_6        		((uint32_t) 0x00000040)			/*!< Bit 6  */
#define QSPI_XIP_MODE_XIP_MD_BITS_7        		((uint32_t) 0x00000080)			/*!< Bit 7  */
#define QSPI_XIP_MODE_XIP_MD_BITS_8        		((uint32_t) 0x00000100)			/*!< Bit 8  */
#define QSPI_XIP_MODE_XIP_MD_BITS_9        		((uint32_t) 0x00000200)			/*!< Bit 9  */
#define QSPI_XIP_MODE_XIP_MD_BITS_10       		((uint32_t) 0x00000400)			/*!< Bit 10 */
#define QSPI_XIP_MODE_XIP_MD_BITS_11       		((uint32_t) 0x00000800)			/*!< Bit 11 */
#define QSPI_XIP_MODE_XIP_MD_BITS_12       		((uint32_t) 0x00001000)			/*!< Bit 12 */
#define QSPI_XIP_MODE_XIP_MD_BITS_13       		((uint32_t) 0x00002000)			/*!< Bit 13 */
#define QSPI_XIP_MODE_XIP_MD_BITS_14       		((uint32_t) 0x00004000)			/*!< Bit 14 */
#define QSPI_XIP_MODE_XIP_MD_BITS_15       		((uint32_t) 0x00008000)			/*!< Bit 15 */

/**************  Bit definition for QSPI_XIP_INCR_TOC register  ***************/
#define QSPI_XIP_INCR_TOC_ITOC_Pos				(0U)
#define QSPI_XIP_INCR_TOC_ITOC_Msk				(0xFFFFUL << QSPI_XIP_INCR_TOC_ITOC_Pos)
#define QSPI_XIP_INCR_TOC_ITOC					QSPI_XIP_INCR_TOC_ITOC_Msk		/*!< ITOC[15:0] (XIP INCR transfer OpCode) */
#define QSPI_XIP_INCR_TOC_ITOC_0           		((uint32_t) 0x00000001)			/*!< Bit 0  */
#define QSPI_XIP_INCR_TOC_ITOC_1           		((uint32_t) 0x00000002)			/*!< Bit 1  */
#define QSPI_XIP_INCR_TOC_ITOC_2           		((uint32_t) 0x00000004)			/*!< Bit 2  */
#define QSPI_XIP_INCR_TOC_ITOC_3           		((uint32_t) 0x00000008)			/*!< Bit 3  */
#define QSPI_XIP_INCR_TOC_ITOC_4           		((uint32_t) 0x00000010)			/*!< Bit 4  */
#define QSPI_XIP_INCR_TOC_ITOC_5           		((uint32_t) 0x00000020)			/*!< Bit 5  */
#define QSPI_XIP_INCR_TOC_ITOC_6           		((uint32_t) 0x00000040)			/*!< Bit 6  */
#define QSPI_XIP_INCR_TOC_ITOC_7           		((uint32_t) 0x00000080)			/*!< Bit 7  */
#define QSPI_XIP_INCR_TOC_ITOC_8           		((uint32_t) 0x00000100)			/*!< Bit 8  */
#define QSPI_XIP_INCR_TOC_ITOC_9           		((uint32_t) 0x00000200)			/*!< Bit 9  */
#define QSPI_XIP_INCR_TOC_ITOC_10          		((uint32_t) 0x00000400)			/*!< Bit 10 */
#define QSPI_XIP_INCR_TOC_ITOC_11          		((uint32_t) 0x00000800)			/*!< Bit 11 */
#define QSPI_XIP_INCR_TOC_ITOC_12          		((uint32_t) 0x00001000)			/*!< Bit 12 */
#define QSPI_XIP_INCR_TOC_ITOC_13          		((uint32_t) 0x00002000)			/*!< Bit 13 */
#define QSPI_XIP_INCR_TOC_ITOC_14          		((uint32_t) 0x00004000)			/*!< Bit 14 */
#define QSPI_XIP_INCR_TOC_ITOC_15          		((uint32_t) 0x00008000)			/*!< Bit 15 */

/**************  Bit definition for QSPI_XIP_WRAP_TOC register  ***************/
#define QSPI_XIP_WRAP_TOC_WTOC_Pos				(0U)
#define QSPI_XIP_WRAP_TOC_WTOC_Msk				(0xFFFFUL << QSPI_XIP_WRAP_TOC_WTOC_Pos)
#define QSPI_XIP_WRAP_TOC_WTOC					QSPI_XIP_WRAP_TOC_WTOC_Msk		/*!< WTOC[15:0] (XIP WRAP transfer OpCode) */
#define QSPI_XIP_WRAP_TOC_WTOC_0           		((uint32_t) 0x00000001)			/*!< Bit 0  */
#define QSPI_XIP_WRAP_TOC_WTOC_1           		((uint32_t) 0x00000002)			/*!< Bit 1  */
#define QSPI_XIP_WRAP_TOC_WTOC_2           		((uint32_t) 0x00000004)			/*!< Bit 2  */
#define QSPI_XIP_WRAP_TOC_WTOC_3           		((uint32_t) 0x00000008)			/*!< Bit 3  */
#define QSPI_XIP_WRAP_TOC_WTOC_4           		((uint32_t) 0x00000010)			/*!< Bit 4  */
#define QSPI_XIP_WRAP_TOC_WTOC_5           		((uint32_t) 0x00000020)			/*!< Bit 5  */
#define QSPI_XIP_WRAP_TOC_WTOC_6           		((uint32_t) 0x00000040)			/*!< Bit 6  */
#define QSPI_XIP_WRAP_TOC_WTOC_7           		((uint32_t) 0x00000080)			/*!< Bit 7  */
#define QSPI_XIP_WRAP_TOC_WTOC_8           		((uint32_t) 0x00000100)			/*!< Bit 8  */
#define QSPI_XIP_WRAP_TOC_WTOC_9           		((uint32_t) 0x00000200)			/*!< Bit 9  */
#define QSPI_XIP_WRAP_TOC_WTOC_10          		((uint32_t) 0x00000400)			/*!< Bit 10 */
#define QSPI_XIP_WRAP_TOC_WTOC_11          		((uint32_t) 0x00000800)			/*!< Bit 11 */
#define QSPI_XIP_WRAP_TOC_WTOC_12          		((uint32_t) 0x00001000)			/*!< Bit 12 */
#define QSPI_XIP_WRAP_TOC_WTOC_13          		((uint32_t) 0x00002000)			/*!< Bit 13 */
#define QSPI_XIP_WRAP_TOC_WTOC_14          		((uint32_t) 0x00004000)			/*!< Bit 14 */
#define QSPI_XIP_WRAP_TOC_WTOC_15          		((uint32_t) 0x00008000)			/*!< Bit 15 */

/****************  Bit definition for QSPI_XIP_CTRL register  *****************/
#define QSPI_XIP_CTRL_FRF_Pos					(0U)
#define QSPI_XIP_CTRL_FRF_Msk					(0x3UL << QSPI_XIP_CTRL_FRF_Pos)
#define QSPI_XIP_CTRL_FRF						QSPI_XIP_CTRL_FRF_Msk			/*!< FRF[1:0] (Frame format) */
#define QSPI_XIP_CTRL_FRF_0                		((uint32_t) 0x00000001)			/*!< Bit 0 */
#define QSPI_XIP_CTRL_FRF_1                		((uint32_t) 0x00000002)			/*!< Bit 1 */

/*!< Frame format configuration */
#define QSPI_XIP_CTRL_FRF_2_LINE           		((uint32_t) 0x00000001)			/*!< 2-line */
#define QSPI_XIP_CTRL_FRF_4_LINE           		((uint32_t) 0x00000002)			/*!< 4-line */

#define QSPI_XIP_CTRL_TRANS_TYPE_Pos			(2U)
#define QSPI_XIP_CTRL_TRANS_TYPE_Msk			(0x3UL << QSPI_XIP_CTRL_TRANS_TYPE_Pos)
#define QSPI_XIP_CTRL_TRANS_TYPE				QSPI_XIP_CTRL_TRANS_TYPE_Msk	/*!< TRANS_TYPE[1:0] (Address and instruction transfer format) */
#define QSPI_XIP_CTRL_TRANS_TYPE_0        		((uint32_t) 0x00000001)			/*!< Bit 0 */
#define QSPI_XIP_CTRL_TRANS_TYPE_1        		((uint32_t) 0x00000002)			/*!< Bit 1 */

/*!< Address and instruction transfer format configuration */
#define QSPI_XIP_CTRL_TRANS_TYPE_STANDARD_SPI    		((uint32_t) 0x00000000)	/*!< Both instruction and address transfer by standard SPI mode */
#define QSPI_XIP_CTRL_TRANS_TYPE_ADDRESS_BY_XIP_FRF 	((uint32_t) 0x00000004)	/*!< Instruction transfer by standard SPI mode, address transfer by QSPI_XIP_CTRL.FRF customized mode */
#define QSPI_XIP_CTRL_TRANS_TYPE_INSTRUCT_BY_XIP_FRF	((uint32_t) 0x00000008)	/*!< Both instruction and address transfer by QSPI_XIP_CTRL.FRF customized mode */

#define QSPI_XIP_CTRL_ADDR_LEN_Pos				(4U)
#define QSPI_XIP_CTRL_ADDR_LEN_Msk				(0xFUL << QSPI_XIP_CTRL_ADDR_LEN_Pos)
#define QSPI_XIP_CTRL_ADDR_LEN					QSPI_XIP_CTRL_ADDR_LEN_Msk		/*!< ADDR_LEN[3:0] (Length of Address to transmit) */
#define QSPI_XIP_CTRL_ADDR_LEN_0				((uint32_t) 0x00000004)			/*!< Bit 0 */
#define QSPI_XIP_CTRL_ADDR_LEN_1				((uint32_t) 0x00000008)			/*!< Bit 1 */
#define QSPI_XIP_CTRL_ADDR_LEN_2				((uint32_t) 0x00000010)			/*!< Bit 2 */
#define QSPI_XIP_CTRL_ADDR_LEN_3				((uint32_t) 0x00000020)			/*!< Bit 3 */
#define QSPI_XIP_CTRL_ADDR_4BIT 				((uint32_t) 0x00000010)			/*!< 4 bits address */	
#define QSPI_XIP_CTRL_ADDR_8BIT 				((uint32_t) 0x00000020)			/*!< 8 bits address */	
#define QSPI_XIP_CTRL_ADDR_12BIT				((uint32_t) 0x00000030)			/*!< 12 bits address */	
#define QSPI_XIP_CTRL_ADDR_16BIT				((uint32_t) 0x00000040)			/*!< 16 bits address */	
#define QSPI_XIP_CTRL_ADDR_20BIT				((uint32_t) 0x00000050)			/*!< 20 bits address */	
#define QSPI_XIP_CTRL_ADDR_24BIT				((uint32_t) 0x00000060)			/*!< 24 bits address */	
#define QSPI_XIP_CTRL_ADDR_28BIT				((uint32_t) 0x00000070)			/*!< 28 bits address */	
#define QSPI_XIP_CTRL_ADDR_32BIT				((uint32_t) 0x00000080)			/*!< 32 bits address */	
#define QSPI_XIP_CTRL_ADDR_36BIT				((uint32_t) 0x00000090)			/*!< 36 bits address */	
#define QSPI_XIP_CTRL_ADDR_40BIT				((uint32_t) 0x000000A0)			/*!< 40 bits address */	
#define QSPI_XIP_CTRL_ADDR_44BIT				((uint32_t) 0x000000B0)			/*!< 44 bits address */	
#define QSPI_XIP_CTRL_ADDR_48BIT				((uint32_t) 0x000000C0)			/*!< 48 bits address */	
#define QSPI_XIP_CTRL_ADDR_52BIT				((uint32_t) 0x000000D0)			/*!< 52 bits address */	
#define QSPI_XIP_CTRL_ADDR_56BIT				((uint32_t) 0x000000E0)			/*!< 56 bits address */	
#define QSPI_XIP_CTRL_ADDR_60BIT				((uint32_t) 0x000000F0)			/*!< 60 bits address */	

#define QSPI_XIP_CTRL_INST_L_Pos				(9U)
#define QSPI_XIP_CTRL_INST_L_Msk				(0x3UL << QSPI_XIP_CTRL_INST_L_Pos)
#define QSPI_XIP_CTRL_INST_L					QSPI_XIP_CTRL_INST_L_Msk		/*!< INST_L[1:0] (Dual/Quad mode instruction length in bits) */
#define QSPI_XIP_CTRL_INST_L_0            		((uint32_t) 0x00000200)			/*!< Bit 0 */
#define QSPI_XIP_CTRL_INST_L_1            		((uint32_t) 0x00000400)			/*!< Bit 1 */

/*!< Dual/Quad mode instruction length configuration */
#define QSPI_XIP_CTRL_INST_L_0_LINE       		((uint32_t) 0x00000000)			/*!< 0 bit   */
#define QSPI_XIP_CTRL_INST_L_4_LINE       		((uint32_t) 0x00000200)			/*!< 4 bits  */
#define QSPI_XIP_CTRL_INST_L_8_LINE       		((uint32_t) 0x00000400)			/*!< 8 bits  */
#define QSPI_XIP_CTRL_INST_L_16_LINE      		((uint32_t) 0x00000600)			/*!< 16 bits */

#define QSPI_XIP_CTRL_MD_BITS_EN_Pos			(12U)
#define QSPI_XIP_CTRL_MD_BITS_EN_Msk			(0x1UL << QSPI_XIP_CTRL_MD_BITS_EN_Pos)
#define QSPI_XIP_CTRL_MD_BITS_EN				QSPI_XIP_CTRL_MD_BITS_EN_Msk	/*!< MD_BIT_EN (Mode bits enable in XIP mode) */

#define QSPI_XIP_CTRL_WAIT_CYCLES_Pos			(13U)
#define QSPI_XIP_CTRL_WAIT_CYCLES_Msk			(0x1FUL << QSPI_XIP_CTRL_WAIT_CYCLES_Pos)
#define QSPI_XIP_CTRL_WAIT_CYCLES				QSPI_XIP_CTRL_WAIT_CYCLES_Msk	/*!< WAIT_CYCLES[4:0] (Wait Cycles in Dual/Quad mode between control frames transmit and data reception) */
#define QSPI_XIP_CTRL_WAIT_CYCLES_0      		((uint32_t) 0x00002000)			/*!< Bit 0 */
#define QSPI_XIP_CTRL_WAIT_CYCLES_1      		((uint32_t) 0x00004000)			/*!< Bit 1 */
#define QSPI_XIP_CTRL_WAIT_CYCLES_2      		((uint32_t) 0x00008000)			/*!< Bit 2 */
#define QSPI_XIP_CTRL_WAIT_CYCLES_3      		((uint32_t) 0x00010000)			/*!< Bit 3 */
#define QSPI_XIP_CTRL_WAIT_CYCLES_4      		((uint32_t) 0x00020000)			/*!< Bit 4 */
#define QSPI_XIP_CTRL_WAIT_1CYCLES        		((uint32_t) 0x00002000)			/*!< Wait 1 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_XIP_CTRL_WAIT_2CYCLES        		((uint32_t) 0x00004000)			/*!< Wait 2 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_XIP_CTRL_WAIT_3CYCLES        		((uint32_t) 0x00006000)			/*!< Wait 3 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_XIP_CTRL_WAIT_4CYCLES        		((uint32_t) 0x00008000)			/*!< Wait 4 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_XIP_CTRL_WAIT_5CYCLES        		((uint32_t) 0x0000A000)			/*!< Wait 5 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_XIP_CTRL_WAIT_6CYCLES        		((uint32_t) 0x0000C000)			/*!< Wait 6 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_XIP_CTRL_WAIT_7CYCLES        		((uint32_t) 0x0000E000)			/*!< Wait 7 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_XIP_CTRL_WAIT_8CYCLES        		((uint32_t) 0x00010000)			/*!< Wait 8 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_XIP_CTRL_WAIT_9CYCLES        		((uint32_t) 0x00012000)			/*!< Wait 9 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_XIP_CTRL_WAIT_10CYCLES       		((uint32_t) 0x00014000)			/*!< Wait 10 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_XIP_CTRL_WAIT_11CYCLES       		((uint32_t) 0x00016000)			/*!< Wait 11 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_XIP_CTRL_WAIT_12CYCLES       		((uint32_t) 0x00018000)			/*!< Wait 12 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_XIP_CTRL_WAIT_13CYCLES       		((uint32_t) 0x0001A000)			/*!< Wait 13 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_XIP_CTRL_WAIT_14CYCLES       		((uint32_t) 0x0001C000)			/*!< Wait 14 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_XIP_CTRL_WAIT_15CYCLES       		((uint32_t) 0x0001E000)			/*!< Wait 15 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_XIP_CTRL_WAIT_16CYCLES       		((uint32_t) 0x00020000)			/*!< Wait 16 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_XIP_CTRL_WAIT_17CYCLES       		((uint32_t) 0x00022000)			/*!< Wait 17 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_XIP_CTRL_WAIT_18CYCLES       		((uint32_t) 0x00024000)			/*!< Wait 18 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_XIP_CTRL_WAIT_19CYCLES       		((uint32_t) 0x00026000)			/*!< Wait 19 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_XIP_CTRL_WAIT_20CYCLES       		((uint32_t) 0x00028000)			/*!< Wait 20 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_XIP_CTRL_WAIT_21CYCLES       		((uint32_t) 0x0002A000)			/*!< Wait 21 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_XIP_CTRL_WAIT_22CYCLES       		((uint32_t) 0x0002C000)			/*!< Wait 22 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_XIP_CTRL_WAIT_23CYCLES       		((uint32_t) 0x0002E000)			/*!< Wait 23 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_XIP_CTRL_WAIT_24CYCLES       		((uint32_t) 0x00030000)			/*!< Wait 24 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_XIP_CTRL_WAIT_25CYCLES       		((uint32_t) 0x00032000)			/*!< Wait 25 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_XIP_CTRL_WAIT_26CYCLES       		((uint32_t) 0x00034000)			/*!< Wait 26 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_XIP_CTRL_WAIT_27CYCLES       		((uint32_t) 0x00036000)			/*!< Wait 27 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_XIP_CTRL_WAIT_28CYCLES       		((uint32_t) 0x00038000)			/*!< Wait 28 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_XIP_CTRL_WAIT_29CYCLES       		((uint32_t) 0x0003A000)			/*!< Wait 29 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_XIP_CTRL_WAIT_30CYCLES       		((uint32_t) 0x0003C000)			/*!< Wait 30 Cycles in Dual/Duad mode between control frames transmit and data reception */
#define QSPI_XIP_CTRL_WAIT_31CYCLES       		((uint32_t) 0x0003E000)			/*!< Wait 31 Cycles in Dual/Duad mode between control frames transmit and data reception */

#define QSPI_XIP_CTRL_DFS_HC_Pos				(18U)
#define QSPI_XIP_CTRL_DFS_HC_Msk				(0x1UL << QSPI_XIP_CTRL_DFS_HC_Pos)
#define QSPI_XIP_CTRL_DFS_HC					QSPI_XIP_CTRL_DFS_HC_Msk		/*!< DFS_HC (Fix DFS for XIP transfers) */
#define QSPI_XIP_CTRL_DDR_EN_Pos				(19U)
#define QSPI_XIP_CTRL_DDR_EN_Msk				(0x1UL << QSPI_XIP_CTRL_DDR_EN_Pos)
#define QSPI_XIP_CTRL_DDR_EN					QSPI_XIP_CTRL_DDR_EN_Msk		/*!< DDR_EN (SPI DDR Enable) */
#define QSPI_XIP_CTRL_INST_DDR_EN_Pos			(20U)
#define QSPI_XIP_CTRL_INST_DDR_EN_Msk			(0x1UL << QSPI_XIP_CTRL_INST_DDR_EN_Pos)
#define QSPI_XIP_CTRL_INST_DDR_EN				QSPI_XIP_CTRL_INST_DDR_EN_Msk	/*!< INST_DDR_EN (XIP instruction enable) */
#define QSPI_XIP_CTRL_XIP_INST_EN_Pos			(22U)
#define QSPI_XIP_CTRL_XIP_INST_EN_Msk			(0x1UL << QSPI_XIP_CTRL_XIP_INST_EN_Pos)
#define QSPI_XIP_CTRL_XIP_INST_EN				QSPI_XIP_CTRL_XIP_INST_EN_Msk	/*!< XIP_INST_EN (XIP instruction enable) */
#define QSPI_XIP_CTRL_XIP_CT_EN_Pos				(23U)
#define QSPI_XIP_CTRL_XIP_CT_EN_Msk				(0x1UL << QSPI_XIP_CTRL_XIP_CT_EN_Pos)
#define QSPI_XIP_CTRL_XIP_CT_EN					QSPI_XIP_CTRL_XIP_CT_EN_Msk		/*!< XIP_CT_EN (Enable Continuous Transfer in XIP mode) */

#define QSPI_XIP_CTRL_XIP_MBL_Pos				(26U)
#define QSPI_XIP_CTRL_XIP_MBL_Msk				(0x3UL << QSPI_XIP_CTRL_XIP_MBL_Pos)
#define QSPI_XIP_CTRL_XIP_MBL					QSPI_XIP_CTRL_XIP_MBL_Msk		/*!< XIP_MBL[1:0] (XIP Mode bits length) */
#define QSPI_XIP_CTRL_XIP_MBL_0           		((uint32_t) 0x04000000)			/*!< Bit 0 */
#define QSPI_XIP_CTRL_XIP_MBL_1           		((uint32_t) 0x08000000)			/*!< Bit 1 */

/*!< XIP Mode bits length configuration */
#define QSPI_XIP_CTRL_XIP_MBL_LEN_2_BIT   		((uint32_t) 0x00000000)			/*!< 2 bits  */
#define QSPI_XIP_CTRL_XIP_MBL_LEN_4_BIT   		((uint32_t) 0x04000000)			/*!< 4 bits  */
#define QSPI_XIP_CTRL_XIP_MBL_LEN_8_BIT   		((uint32_t) 0x08000000)			/*!< 8 bits  */
#define QSPI_XIP_CTRL_XIP_MBL_LEN_16_BIT  		((uint32_t) 0x0C000000)			/*!< 16 bits */

/**************  Bit definition for QSPI_XIP_SLAVE_EN register  ***************/
#define QSPI_XIP_SLAVE_EN_SEN_Pos				(0U)
#define QSPI_XIP_SLAVE_EN_SEN_Msk				(0x1UL << QSPI_XIP_SLAVE_EN_SEN_Pos)
#define QSPI_XIP_SLAVE_EN_SEN					QSPI_XIP_SLAVE_EN_SEN_Msk		/*!< SEN (Slave Enable) */

/**************  Bit definition for QSPI_XIP_RXFOI_CLR register  **************/
#define QSPI_XIP_RXFOI_CLR_XRXFOIC_Pos			(0U)
#define QSPI_XIP_RXFOI_CLR_XRXFOIC_Msk			(0x1UL << QSPI_XIP_RXFOI_CLR_XRXFOIC_Pos)
#define QSPI_XIP_RXFOI_CLR_XRXFOIC				QSPI_XIP_RXFOI_CLR_XRXFOIC_Msk	/*!< XRXFOIC (Clear XIP Receive FIFO Overflow Interrupt) */
	
/*****************  Bit definition for QSPI_XIP_OUT register  *****************/
#define QSPI_XIP_OUT_XTOUT_Pos					(0U)
#define QSPI_XIP_OUT_XTOUT_Msk					(0xFFUL << QSPI_XIP_OUT_XTOUT_Pos)
#define QSPI_XIP_OUT_XTOUT						QSPI_XIP_OUT_XTOUT_Msk			/*!< XTOUT[7:0] (XIP time out value in terms of HCLK) */
#define QSPI_XIP_OUT_XTOUT_0					((uint32_t) 0x00000001)			/*!< Bit 0 */
#define QSPI_XIP_OUT_XTOUT_1					((uint32_t) 0x00000002)			/*!< Bit 1 */
#define QSPI_XIP_OUT_XTOUT_2					((uint32_t) 0x00000004)			/*!< Bit 2 */
#define QSPI_XIP_OUT_XTOUT_3					((uint32_t) 0x00000008)			/*!< Bit 3 */
#define QSPI_XIP_OUT_XTOUT_4					((uint32_t) 0x00000010)			/*!< Bit 4 */
#define QSPI_XIP_OUT_XTOUT_5					((uint32_t) 0x00000020)			/*!< Bit 5 */
#define QSPI_XIP_OUT_XTOUT_6					((uint32_t) 0x00000040)			/*!< Bit 6 */
#define QSPI_XIP_OUT_XTOUT_7					((uint32_t) 0x00000080)			/*!< Bit 7 */

/******************************************************************************/
/*                                                                            */
/*                                 COMP Registers           	              */
/*                                                                            */
/******************************************************************************/
/******************  Bit definition for COMP_CTRL register  *******************/
#define COMP_CTRL_EN_Pos						(0U)
#define COMP_CTRL_EN_Msk						(0x1UL << COMP_CTRL_EN_Pos)
#define COMP_CTRL_EN							COMP_CTRL_EN_Msk
#define COMP_CTRL_INMSEL_Pos					(1U)
#define COMP_CTRL_INMSEL_Msk					(0x7UL << COMP_CTRL_INMSEL_Pos)
#define COMP_CTRL_INMSEL						COMP_CTRL_INMSEL_Msk
#define COMP_CTRL_INPSEL_Pos					(4U)
#define COMP_CTRL_INPSEL_Msk					(0x7UL << COMP_CTRL_INPSEL_Pos)
#define COMP_CTRL_INPSEL						COMP_CTRL_INPSEL_Msk
#define COMP_CTRL_OUTTRG_Pos					(7U)
#define COMP_CTRL_OUTTRG_Msk					(0xFUL << COMP_CTRL_OUTTRG_Pos)
#define COMP_CTRL_OUTTRG						COMP_CTRL_OUTTRG_Msk
#define COMP_CTRL_POL_Pos						(11U)
#define COMP_CTRL_POL_Msk						(0x1UL << COMP_CTRL_POL_Pos)
#define COMP_CTRL_POL							COMP_CTRL_POL_Msk
#define COMP_CTRL_HYST_Pos						(12U)
#define COMP_CTRL_HYST_Msk						(0x3UL << COMP_CTRL_HYST_Pos)
#define COMP_CTRL_HYST							COMP_CTRL_HYST_Msk
#define COMP_CTRL_BLKING_Pos					(14U)
#define COMP_CTRL_BLKING_Msk					(0x7UL << COMP_CTRL_BLKING_Pos)
#define COMP_CTRL_BLKING						COMP_CTRL_BLKING_Msk
#define COMP_CTRL_OUT_Pos						(17U)
#define COMP_CTRL_OUT_Msk						(0x1UL << COMP_CTRL_OUT_Pos)
#define COMP_CTRL_OUT							COMP_CTRL_OUT_Msk
#define COMP_CTRL_INPDAC_Pos					(18U)
#define COMP_CTRL_INPDAC_Msk					(0x1UL << COMP_CTRL_INPDAC_Pos)
#define COMP_CTRL_INPDAC						COMP_CTRL_INPDAC_Msk

/*****************  Bit definition for COMP_WINMODE register  *****************/
#define COMP_WINMODE_CMP12MD_Pos				(0U)
#define COMP_WINMODE_CMP12MD_Msk				(0x1UL << COMP_WINMODE_CMP12MD_Pos)
#define COMP_WINMODE_CMP12MD					COMP_WINMODE_CMP12MD_Msk	/* 1: Comparators 1 and 2 can be used in window mode. */
#define COMP_WINMODE_CMP34MD_Pos				(1U)
#define COMP_WINMODE_CMP34MD_Msk				(0x1UL << COMP_WINMODE_CMP34MD_Pos)
#define COMP_WINMODE_CMP34MD					COMP_WINMODE_CMP34MD_Msk	/* 1: Comparators 3 and 4 can be used in window mode. */
#define COMP_WINMODE_CMP56MD_Pos				(2U)
#define COMP_WINMODE_CMP56MD_Msk				(0x1UL << COMP_WINMODE_CMP56MD_Pos)
#define COMP_WINMODE_CMP56MD					COMP_WINMODE_CMP56MD_Msk	/* 1: Comparators 5 and 6 can be used in window mode. */

/******************  Bit definition for COMP_LOCK register  *******************/
#define COMP_LOCK_CMP1LK_Pos					(0U)
#define COMP_LOCK_CMP1LK_Msk					(0x1UL << COMP_LOCK_CMP1LK_Pos)
#define COMP_LOCK_CMP1LK						COMP_LOCK_CMP1LK_Msk
#define COMP_LOCK_CMP2LK_Pos					(1U)
#define COMP_LOCK_CMP2LK_Msk					(0x1UL << COMP_LOCK_CMP2LK_Pos)
#define COMP_LOCK_CMP2LK						COMP_LOCK_CMP2LK_Msk
#define COMP_LOCK_CMP3LK_Pos					(2U)
#define COMP_LOCK_CMP3LK_Msk					(0x1UL << COMP_LOCK_CMP3LK_Pos)
#define COMP_LOCK_CMP3LK						COMP_LOCK_CMP3LK_Msk
#define COMP_LOCK_CMP4LK_Pos					(3U)
#define COMP_LOCK_CMP4LK_Msk					(0x1UL << COMP_LOCK_CMP4LK_Pos)
#define COMP_LOCK_CMP4LK						COMP_LOCK_CMP4LK_Msk
#define COMP_LOCK_CMP5LK_Pos					(4U)
#define COMP_LOCK_CMP5LK_Msk					(0x1UL << COMP_LOCK_CMP5LK_Pos)
#define COMP_LOCK_CMP5LK						COMP_LOCK_CMP5LK_Msk
#define COMP_LOCK_CMP6LK_Pos					(5U)
#define COMP_LOCK_CMP6LK_Msk					(0x1UL << COMP_LOCK_CMP6LK_Pos)
#define COMP_LOCK_CMP6LK						COMP_LOCK_CMP6LK_Msk
#define COMP_LOCK_CMP7LK_Pos					(6U)
#define COMP_LOCK_CMP7LK_Msk					(0x1UL << COMP_LOCK_CMP7LK_Pos)
#define COMP_LOCK_CMP7LK						COMP_LOCK_CMP7LK_Msk

/******************  Bit definition for COMP_INTEN register  ******************/
#define COMP_INTEN_CMP1IEN_Pos					(0U)
#define COMP_INTEN_CMP1IEN_Msk					(0x1UL << COMP_INTEN_CMP1IEN_Pos)
#define COMP_INTEN_CMP1IEN						COMP_INTEN_CMP1IEN_Msk	/* This bit control Interrput enable of COMP. */
#define COMP_INTEN_CMP2IEN_Pos					(1U)
#define COMP_INTEN_CMP2IEN_Msk					(0x1UL << COMP_INTEN_CMP2IEN_Pos)
#define COMP_INTEN_CMP2IEN						COMP_INTEN_CMP2IEN_Msk
#define COMP_INTEN_CMP3IEN_Pos     				(2U)
#define COMP_INTEN_CMP3IEN_Msk					(0x1UL << COMP_INTEN_CMP3IEN_Pos)
#define COMP_INTEN_CMP3IEN						COMP_INTEN_CMP3IEN_Msk
#define COMP_INTEN_CMP4IEN_Pos     				(3U)
#define COMP_INTEN_CMP4IEN_Msk					(0x1UL << COMP_INTEN_CMP4IEN_Pos)
#define COMP_INTEN_CMP4IEN						COMP_INTEN_CMP4IEN_Msk
#define COMP_INTEN_CMP5IEN_Pos     				(4U)
#define COMP_INTEN_CMP5IEN_Msk					(0x1UL << COMP_INTEN_CMP5IEN_Pos)
#define COMP_INTEN_CMP5IEN						COMP_INTEN_CMP5IEN_Msk
#define COMP_INTEN_CMP6IEN_Pos     				(5U)
#define COMP_INTEN_CMP6IEN_Msk					(0x1UL << COMP_INTEN_CMP6IEN_Pos)
#define COMP_INTEN_CMP6IEN						COMP_INTEN_CMP6IEN_Msk
#define COMP_INTEN_CMP7IEN_Pos     				(6U)
#define COMP_INTEN_CMP7IEN_Msk					(0x1UL << COMP_INTEN_CMP7IEN_Pos)
#define COMP_INTEN_CMP7IEN						COMP_INTEN_CMP7IEN_Msk

/*****************  Bit definition for COMP_INTSTS register  ******************/
#define COMP_INTSTS_CMP1IS_Pos					(0U)
#define COMP_INTSTS_CMP1IS_Msk					(0x1UL << COMP_INTSTS_CMP1IS_Pos)
#define COMP_INTSTS_CMP1IS						COMP_INTSTS_CMP1IS_Msk	/* This bit control Interrput enable of COMP. */
#define COMP_INTSTS_CMP2IS_Pos      			(1U)
#define COMP_INTSTS_CMP2IS_Msk					(0x1UL << COMP_INTSTS_CMP2IS_Pos)
#define COMP_INTSTS_CMP2IS						COMP_INTSTS_CMP2IS_Msk
#define COMP_INTSTS_CMP3IS_Pos      			(2U)
#define COMP_INTSTS_CMP3IS_Msk					(0x1UL << COMP_INTSTS_CMP3IS_Pos)
#define COMP_INTSTS_CMP3IS						COMP_INTSTS_CMP3IS_Msk
#define COMP_INTSTS_CMP4IS_Pos      			(3U)
#define COMP_INTSTS_CMP4IS_Msk					(0x1UL << COMP_INTSTS_CMP4IS_Pos)
#define COMP_INTSTS_CMP4IS						COMP_INTSTS_CMP4IS_Msk
#define COMP_INTSTS_CMP5IS_Pos      			(4U)
#define COMP_INTSTS_CMP5IS_Msk					(0x1UL << COMP_INTSTS_CMP5IS_Pos)
#define COMP_INTSTS_CMP5IS						COMP_INTSTS_CMP5IS_Msk
#define COMP_INTSTS_CMP6IS_Pos      			(5U)
#define COMP_INTSTS_CMP6IS_Msk					(0x1UL << COMP_INTSTS_CMP6IS_Pos)
#define COMP_INTSTS_CMP6IS						COMP_INTSTS_CMP6IS_Msk
#define COMP_INTSTS_CMP7IS_Pos      			(6U)
#define COMP_INTSTS_CMP7IS_Msk					(0x1UL << COMP_INTSTS_CMP7IS_Pos)
#define COMP_INTSTS_CMP7IS						COMP_INTSTS_CMP7IS_Msk

/******************  Bit definition for COMP_FILC register  *******************/
#define COMP_FILC_FILEN_Pos						(0U)
#define COMP_FILC_FILEN_Msk						(0x1UL << COMP_FILC_FILEN_Pos)
#define COMP_FILC_FILEN							COMP_FILC_FILEN_Msk
#define COMP_FILC_THRESH_Pos					(1U)
#define COMP_FILC_THRESH_Msk					(0x1FUL << COMP_FILC_THRESH_Pos)
#define COMP_FILC_THRESH						COMP_FILC_THRESH_Msk
#define COMP_FILC_SAMPW_Pos						(6U)
#define COMP_FILC_SAMPW_Msk						(0x1FUL << COMP_FILC_SAMPW_Pos)
#define COMP_FILC_SAMPW							COMP_FILC_SAMPW_Msk

/******************  Bit definition for COMP_FILP register  *******************/
#define COMP_FILP_CLKPSC_Pos					(0U)
#define COMP_FILP_CLKPSC_Msk					(0xFFFFUL << COMP_FILP_CLKPSC_Pos)
#define COMP_FILP_CLKPSC						COMP_FILP_CLKPSC_Msk

/*****************  Bit definition for COMP_VREFSCL register  *****************/
#define COMP_VREFSCL_VREF1EN_Pos				(0U)
#define COMP_VREFSCL_VREF1EN_Msk				(0x1UL << COMP_VREFSCL_VREF1EN_Pos)
#define COMP_VREFSCL_VREF1EN					COMP_VREFSCL_VREF1EN_Msk
#define COMP_VREFSCL_VREF1SET_Pos				(1U)
#define COMP_VREFSCL_VREF1SET_Msk				(0x3FUL << COMP_VREFSCL_VREF1SET_Pos)
#define COMP_VREFSCL_VREF1SET					COMP_VREFSCL_VREF1SET_Msk
#define COMP_VREFSCL_VREF2EN_Pos				(7U)
#define COMP_VREFSCL_VREF2EN_Msk				(0x1UL << COMP_VREFSCL_VREF2EN_Pos)
#define COMP_VREFSCL_VREF2EN					COMP_VREFSCL_VREF2EN_Msk
#define COMP_VREFSCL_VREF2SET_Pos				(8U)
#define COMP_VREFSCL_VREF2SET_Msk				(0x3FUL << COMP_VREFSCL_VREF2SET_Pos)
#define COMP_VREFSCL_VREF2SET					COMP_VREFSCL_VREF2SET_Msk

/******************************************************************************/
/*                                                                            */
/*                                OPAMP Registers           	              */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for OPAMP_CS register  *******************/
#define OPAMP_CS_EN_Pos							(0U)
#define OPAMP_CS_EN_Msk							(0x1UL << OPAMP_CS_EN_Pos)		/*!< OPAMP enable */
#define OPAMP_CS_EN								OPAMP_CS_EN_Msk
#define OPAMP_CS_MOD_Pos						(1U)
#define OPAMP_CS_MOD_Msk						(0x3UL << OPAMP_CS_MOD_Pos)
#define OPAMP_CS_MOD							OPAMP_CS_MOD_Msk				/*!< OPAMP mode selection */
#define OPAMP_CS_PGAGAN_Pos						(3U)
#define OPAMP_CS_PGAGAN_Msk						(0x7UL << OPAMP_CS_PGAGAN_Pos)
#define OPAMP_CS_PGAGAN							OPAMP_CS_PGAGAN_Msk				/*!< OPAMP PGA gain value */
#define OPAMP_CS_VMSEL_Pos						(6U)
#define OPAMP_CS_VMSEL_Msk						(0x3UL << OPAMP_CS_VMSEL_Pos)
#define OPAMP_CS_VMSEL							OPAMP_CS_VMSEL_Msk				/*!< Inverted input selection */
#define OPAMP_CS_VPSEL_Pos						(8U)
#define OPAMP_CS_VPSEL_Msk						(0x7UL << OPAMP_CS_VPSEL_Pos)
#define OPAMP_CS_VPSEL							OPAMP_CS_VPSEL_Msk				/*!< Non-Inverted input selection */
#define OPAMP_CS_CALON_Pos						(11U)
#define OPAMP_CS_CALON_Msk						(0x1UL << OPAMP_CS_CALON_Pos)
#define OPAMP_CS_CALON							OPAMP_CS_CALON_Msk				/*!< Calibration mode enable */
#define OPAMP_CS_TSTREF_Pos						(13U)
#define OPAMP_CS_TSTREF_Msk						(0x1UL << OPAMP_CS_TSTREF_Pos)
#define OPAMP_CS_TSTREF							OPAMP_CS_TSTREF_Msk				/*!< Reserved for internal use, set to zero */
#define OPAMP_CS_CALOUT_Pos						(14U)
#define OPAMP_CS_CALOUT_Msk						(0x1UL << OPAMP_CS_CALOUT_Pos)
#define OPAMP_CS_CALOUT							OPAMP_CS_CALOUT_Msk				/*!< OPAMP calibration output */
#define OPAMP_CS_RANGE_Pos						(15U)
#define OPAMP_CS_RANGE_Msk						(0x1UL << OPAMP_CS_RANGE_Pos)
#define OPAMP_CS_RANGE							OPAMP_CS_RANGE_Msk				/*!< OPAMP power supply range */
#define OPAMP_CS_TCMEN_Pos						(16U)
#define OPAMP_CS_TCMEN_Msk						(0x1UL << OPAMP_CS_TCMEN_Pos)
#define OPAMP_CS_TCMEN							OPAMP_CS_TCMEN_Msk				/*!< Timer controlled Mux mode enable */
#define OPAMP_CS_VMSSEL_Pos						(17U)
#define OPAMP_CS_VMSSEL_Msk						(0x3UL << OPAMP_CS_VMSSEL_Pos)
#define OPAMP_CS_VMSSEL							OPAMP_CS_VMSSEL_Msk				/*!< Inverted input secondary selection */
#define OPAMP_CS_VPSSEL_Pos						(19U)
#define OPAMP_CS_VPSSEL_Msk						(0x7UL << OPAMP_CS_VPSSEL_Pos)
#define OPAMP_CS_VPSSEL							OPAMP_CS_VPSSEL_Msk				/*!< Non-Inverted input secondary selection */

/******************  Bit definition for OPAMP_LOCK register  ******************/
#define OPAMP_LOCK_OPAMP1LK_Pos					(0U)
#define OPAMP_LOCK_OPAMP1LK_Msk					(0x1UL << OPAMP_LOCK_OPAMP1LK_Pos)
#define OPAMP_LOCK_OPAMP1LK						OPAMP_LOCK_OPAMP1LK_Msk			/*!< OPAMP1 lock bit */
#define OPAMP_LOCK_OPAMP2LK_Pos					(1U)
#define OPAMP_LOCK_OPAMP2LK_Msk					(0x1UL << OPAMP_LOCK_OPAMP2LK_Pos)
#define OPAMP_LOCK_OPAMP2LK						OPAMP_LOCK_OPAMP2LK_Msk			/*!< OPAMP2 lock bit */
#define OPAMP_LOCK_OPAMP3LK_Pos					(2U)
#define OPAMP_LOCK_OPAMP3LK_Msk					(0x1UL << OPAMP_LOCK_OPAMP3LK_Pos)
#define OPAMP_LOCK_OPAMP3LK						OPAMP_LOCK_OPAMP3LK_Msk			/*!< OPAMP3 lock bit */
#define OPAMP_LOCK_OPAMP4LK_Pos					(3U)
#define OPAMP_LOCK_OPAMP4LK_Msk					(0x1UL << OPAMP_LOCK_OPAMP4LK_Pos)
#define OPAMP_LOCK_OPAMP4LK						OPAMP_LOCK_OPAMP4LK_Msk			/*!< OPAMP4 lock bit */

/******************************************************************************/
/*                                                                            */
/*                                 TSC Registers           	                  */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for TSC_CTRL register  *******************/
#define TSC_CTRL_DET_PERIOD_Pos					(0U)
#define TSC_CTRL_DET_PERIOD_Msk					(0xFUL << TSC_CTRL_DET_PERIOD_Pos)
#define TSC_CTRL_DET_PERIOD                		TSC_CTRL_DET_PERIOD_Msk			/*!< DET_PERIOD[3:0] (Detect period) */
#define TSC_CTRL_DET_PERIOD_0              		((uint32_t) 0x00000001)			/*!< Bit 0 */
#define TSC_CTRL_DET_PERIOD_1              		((uint32_t) 0x00000002)			/*!< Bit 1 */
#define TSC_CTRL_DET_PERIOD_2              		((uint32_t) 0x00000004)			/*!< Bit 2 */
#define TSC_CTRL_DET_PERIOD_3              		((uint32_t) 0x00000008)			/*!< Bit 3 */

/*!< Detect period configuration, TSC_CLK = 32.768kHz */
#define TSC_CTRL_DET_PERIOD_8_32KHZ        		(0x00U)							/*!< 8   x 32kHz = 244.1us				*/
#define TSC_CTRL_DET_PERIOD_16_32KHZ       		(0x01U)							/*!< 16  x 32kHz = 488.28us         	*/
#define TSC_CTRL_DET_PERIOD_24_32KHZ       		(0x02U)							/*!< 24  x 32kHz = 732.42us         	*/
#define TSC_CTRL_DET_PERIOD_32_32KHZ       		(0x03U)							/*!< 32  x 32kHz = 976.56us(default)	*/
#define TSC_CTRL_DET_PERIOD_40_32KHZ       		(0x04U)							/*!< 40  x 32kHz = 1220.7us         	*/
#define TSC_CTRL_DET_PERIOD_48_32KHZ       		(0x05U)							/*!< 48  x 32kHz = 1464.84us        	*/
#define TSC_CTRL_DET_PERIOD_56_32KHZ       		(0x06U)							/*!< 56  x 32kHz = 1708.98us        	*/
#define TSC_CTRL_DET_PERIOD_64_32KHZ       		(0x07U)							/*!< 64  x 32kHz = 1953.13us        	*/
#define TSC_CTRL_DET_PERIOD_72_32KHZ       		(0x08U)							/*!< 72  x 32kHz = 2197.27us        	*/
#define TSC_CTRL_DET_PERIOD_80_32KHZ       		(0x09U)							/*!< 80  x 32kHz = 2441.41us        	*/
#define TSC_CTRL_DET_PERIOD_88_32KHZ       		(0x0AU)							/*!< 88  x 32kHz = 2685.55us        	*/
#define TSC_CTRL_DET_PERIOD_96_32KHZ       		(0x0BU)							/*!< 96  x 32kHz = 2929.69us        	*/
#define TSC_CTRL_DET_PERIOD_104_32KHZ      		(0x0CU)							/*!< 104 x 32kHz = 3173.83us        	*/

/*!< Detect period configuration, TSC_CLK = 40kHz */
#define TSC_CTRL_DET_PERIOD_8_40KHZ        		(0x00U)							/*!< 8   x 40kHz = 200us				*/
#define TSC_CTRL_DET_PERIOD_16_40KHZ       		(0x01U)							/*!< 16  x 40kHz = 400us          		*/
#define TSC_CTRL_DET_PERIOD_24_40KHZ       		(0x02U)							/*!< 24  x 40kHz = 600us          		*/
#define TSC_CTRL_DET_PERIOD_32_40KHZ       		(0x03U)							/*!< 32  x 40kHz = 800us(default) 		*/
#define TSC_CTRL_DET_PERIOD_40_40KHZ       		(0x04U)							/*!< 40  x 40kHz = 1000us          		*/
#define TSC_CTRL_DET_PERIOD_48_40KHZ       		(0x05U)							/*!< 48  x 40kHz = 1200us         		*/
#define TSC_CTRL_DET_PERIOD_56_40KHZ       		(0x06U)							/*!< 56  x 40kHz = 1400us         		*/
#define TSC_CTRL_DET_PERIOD_64_40KHZ       		(0x07U)							/*!< 64  x 40kHz = 1600us         		*/
#define TSC_CTRL_DET_PERIOD_72_40KHZ       		(0x08U)							/*!< 72  x 40kHz = 1800us         		*/
#define TSC_CTRL_DET_PERIOD_80_40KHZ       		(0x09U)							/*!< 80  x 40kHz = 2000us         		*/
#define TSC_CTRL_DET_PERIOD_88_40KHZ       		(0x0AU)							/*!< 88  x 40kHz = 2200us         		*/
#define TSC_CTRL_DET_PERIOD_96_40KHZ       		(0x0BU)							/*!< 96  x 40kHz = 2400us         		*/
#define TSC_CTRL_DET_PERIOD_104_40KHZ      		(0x0CU)							/*!< 104 x 40kHz = 2600us         		*/

#define TSC_CTRL_DET_FILTER_Pos					(4U)
#define TSC_CTRL_DET_FILTER_Msk					(0x3UL << TSC_CTRL_DET_FILTER_Pos)
#define TSC_CTRL_DET_FILTER                		TSC_CTRL_DET_FILTER_Msk			/*!< DET_FILTER[1:0] (Detect filter) */
#define TSC_CTRL_DET_FILTER_0              		((uint32_t) 0x00000010)			/*!< Bit 0 */
#define TSC_CTRL_DET_FILTER_1              		((uint32_t) 0x00000020)			/*!< Bit 1 */

/*!< Detect filter configuration */
#define TSC_CTRL_DET_FILTER_ONCE           		((uint32_t) 0x00000000)			/*!< 1 time */
#define TSC_CTRL_DET_FILTER_TWICE          		((uint32_t) 0x00000010)         /*!< 2 times */
#define TSC_CTRL_DET_FILTER_THREE_TIMES    		((uint32_t) 0x00000020)         /*!< 3 times */
#define TSC_CTRL_DET_FILTER_FOUR_TIMES     		((uint32_t) 0x00000030)         /*!< 4 times */

#define TSC_CTRL_HW_DET_MODE_Pos				(6U)
#define TSC_CTRL_HW_DET_MODE_Msk				(0x1UL << TSC_CTRL_HW_DET_MODE_Pos)
#define TSC_CTRL_HW_DET_MODE               		TSC_CTRL_HW_DET_MODE_Msk		/*!< HW_DET_MODE (Hardware detect mode) */
#define TSC_CTRL_HW_DET_ST_Pos					(7U)
#define TSC_CTRL_HW_DET_ST_Msk					(0x1UL << TSC_CTRL_HW_DET_ST_Pos)
#define TSC_CTRL_HW_DET_ST                 		TSC_CTRL_HW_DET_ST_Msk			/*!< HW_DET_ST (Hardware detect status) */
#define TSC_CTRL_LESS_DET_SEL_Pos				(8U)
#define TSC_CTRL_LESS_DET_SEL_Msk				(0x1UL << TSC_CTRL_LESS_DET_SEL_Pos)
#define TSC_CTRL_LESS_DET_SEL              		TSC_CTRL_LESS_DET_SEL_Msk		/*!< LESS_DET_SEL (Enable less threshold compare) */
#define TSC_CTRL_GREAT_DET_SEL_Pos				(9U)
#define TSC_CTRL_GREAT_DET_SEL_Msk				(0x1UL << TSC_CTRL_GREAT_DET_SEL_Pos)
#define TSC_CTRL_GREAT_DET_SEL             		TSC_CTRL_GREAT_DET_SEL_Msk		/*!< GREAT_DET_SEL (Enable great threshold compare) */
#define TSC_CTRL_DET_INTEN_Pos					(10U)
#define TSC_CTRL_DET_INTEN_Msk					(0x1UL << TSC_CTRL_DET_INTEN_Pos)
#define TSC_CTRL_DET_INTEN                 		TSC_CTRL_DET_INTEN_Msk			/*!< DET_INTEN (Enable detect interrupt) */
#define TSC_CTRL_TIM4_ETR_Pos					(12U)
#define TSC_CTRL_TIM4_ETR_Msk					(0x1UL << TSC_CTRL_TIM4_ETR_Pos)
#define TSC_CTRL_TIM4_ETR                   	TSC_CTRL_TIM4_ETR_Msk			/*!< TM4_ETR (TSC_OUT output to TIM4_ETR) */
#define TSC_CTRL_TIM2_ETR_CH1_Pos				(13U)
#define TSC_CTRL_TIM2_ETR_CH1_Msk				(0x1UL << TSC_CTRL_TIM2_ETR_CH1_Pos)
#define TSC_CTRL_TIM2_ETR_CH1               	TSC_CTRL_TIM2_ETR_CH1_Msk		/*!< TM2_ETR_CH1 (TSC_OUT output to TIM2_ETR and TIM2_CH1) */

/******************  Bit definition for TSC_CHNEN register  *******************/
#define TSC_CHNEN_CHN_SEL_ALL_Pos				(0U)
#define TSC_CHNEN_CHN_SEL_ALL_Msk				(0xFFFFFFUL << TSC_CHNEN_CHN_SEL_ALL_Pos)	/*!< 0x00FFFFFF */
#define TSC_CHNEN_CHN_SEL_ALL                   TSC_CHNEN_CHN_SEL_ALL_Msk		/*!< TSC_CHNEN_SEL[23:0] (Select hardware channel) */
#define TSC_CHNEN_CHN_SEL0_Pos					(0U)
#define TSC_CHNEN_CHN_SEL0_Msk					(0x1UL << TSC_CHNEN_CHN_SEL0_Pos)	/*!< 0x00000001 */
#define TSC_CHNEN_CHN_SEL0                     	TSC_CHNEN_CHN_SEL0_Msk			/*!< bit 0 */
#define TSC_CHNEN_CHN_SEL1_Pos					(1U)
#define TSC_CHNEN_CHN_SEL1_Msk					(0x1UL << TSC_CHNEN_CHN_SEL1_Pos)	/*!< 0x00000002 */
#define TSC_CHNEN_CHN_SEL1                     	TSC_CHNEN_CHN_SEL1_Msk 			/*!< bit 1 */
#define TSC_CHNEN_CHN_SEL2_Pos					(2U)
#define TSC_CHNEN_CHN_SEL2_Msk					(0x1UL << TSC_CHNEN_CHN_SEL2_Pos)	/*!< 0x00000004 */
#define TSC_CHNEN_CHN_SEL2                     	TSC_CHNEN_CHN_SEL2_Msk 			/*!< bit 2 */
#define TSC_CHNEN_CHN_SEL3_Pos					(3U)
#define TSC_CHNEN_CHN_SEL3_Msk					(0x1UL << TSC_CHNEN_CHN_SEL3_Pos)	/*!< 0x00000008 */
#define TSC_CHNEN_CHN_SEL3                     	TSC_CHNEN_CHN_SEL3_Msk 			/*!< bit 3 */
#define TSC_CHNEN_CHN_SEL4_Pos					(4U)
#define TSC_CHNEN_CHN_SEL4_Msk					(0x1UL << TSC_CHNEN_CHN_SEL4_Pos)	/*!< 0x00000010 */
#define TSC_CHNEN_CHN_SEL4                     	TSC_CHNEN_CHN_SEL4_Msk 			/*!< bit 4 */
#define TSC_CHNEN_CHN_SEL5_Pos					(5U)
#define TSC_CHNEN_CHN_SEL5_Msk					(0x1UL << TSC_CHNEN_CHN_SEL5_Pos)	/*!< 0x00000020 */
#define TSC_CHNEN_CHN_SEL5                     	TSC_CHNEN_CHN_SEL5_Msk 			/*!< bit 5 */
#define TSC_CHNEN_CHN_SEL6_Pos					(6U)
#define TSC_CHNEN_CHN_SEL6_Msk					(0x1UL << TSC_CHNEN_CHN_SEL6_Pos)	/*!< 0x00000020 */
#define TSC_CHNEN_CHN_SEL6                     	TSC_CHNEN_CHN_SEL6_Msk 			/*!< bit 6 */
#define TSC_CHNEN_CHN_SEL7_Pos					(7U)
#define TSC_CHNEN_CHN_SEL7_Msk					(0x1UL << TSC_CHNEN_CHN_SEL7_Pos)	/*!< 0x00000080 */
#define TSC_CHNEN_CHN_SEL7                     	TSC_CHNEN_CHN_SEL7_Msk 			/*!< bit 7 */
#define TSC_CHNEN_CHN_SEL8_Pos					(8U)
#define TSC_CHNEN_CHN_SEL8_Msk					(0x1UL << TSC_CHNEN_CHN_SEL8_Pos)	/*!< 0x00000100 */
#define TSC_CHNEN_CHN_SEL8                     	TSC_CHNEN_CHN_SEL8_Msk 			/*!< bit 8 */
#define TSC_CHNEN_CHN_SEL9_Pos					(9U)
#define TSC_CHNEN_CHN_SEL9_Msk					(0x1UL << TSC_CHNEN_CHN_SEL9_Pos)	/*!< 0x00000200 */
#define TSC_CHNEN_CHN_SEL9                     	TSC_CHNEN_CHN_SEL9_Msk 			/*!< bit 9 */
#define TSC_CHNEN_CHN_SEL10_Pos					(10U)
#define TSC_CHNEN_CHN_SEL10_Msk					(0x1UL << TSC_CHNEN_CHN_SEL10_Pos)	/*!< 0x00000400 */
#define TSC_CHNEN_CHN_SEL10                    	TSC_CHNEN_CHN_SEL10_Msk 		/*!< bit 10 */
#define TSC_CHNEN_CHN_SEL11_Pos					(11U)
#define TSC_CHNEN_CHN_SEL11_Msk					(0x1UL << TSC_CHNEN_CHN_SEL11_Pos)	/*!< 0x00000800 */
#define TSC_CHNEN_CHN_SEL11                    	TSC_CHNEN_CHN_SEL11_Msk 		/*!< bit 11 */
#define TSC_CHNEN_CHN_SEL12_Pos					(12U)
#define TSC_CHNEN_CHN_SEL12_Msk					(0x1UL << TSC_CHNEN_CHN_SEL12_Pos)	/*!< 0x00001000 */
#define TSC_CHNEN_CHN_SEL12                    	TSC_CHNEN_CHN_SEL12_Msk 		/*!< bit 12 */
#define TSC_CHNEN_CHN_SEL13_Pos					(13U)
#define TSC_CHNEN_CHN_SEL13_Msk					(0x1UL << TSC_CHNEN_CHN_SEL13_Pos)	/*!< 0x00002000 */
#define TSC_CHNEN_CHN_SEL13                    	TSC_CHNEN_CHN_SEL13_Msk 		/*!< bit 13 */
#define TSC_CHNEN_CHN_SEL14_Pos					(14U)
#define TSC_CHNEN_CHN_SEL14_Msk					(0x1UL << TSC_CHNEN_CHN_SEL14_Pos)	/*!< 0x00004000 */
#define TSC_CHNEN_CHN_SEL14                    	TSC_CHNEN_CHN_SEL14_Msk 		/*!< bit 14 */
#define TSC_CHNEN_CHN_SEL15_Pos					(15U)
#define TSC_CHNEN_CHN_SEL15_Msk					(0x1UL << TSC_CHNEN_CHN_SEL15_Pos)	/*!< 0x00008000 */
#define TSC_CHNEN_CHN_SEL15                    	TSC_CHNEN_CHN_SEL15_Msk 		/*!< bit 15 */
#define TSC_CHNEN_CHN_SEL16_Pos					(16U)
#define TSC_CHNEN_CHN_SEL16_Msk					(0x1UL << TSC_CHNEN_CHN_SEL16_Pos)	/*!< 0x00010000 */
#define TSC_CHNEN_CHN_SEL16                    	TSC_CHNEN_CHN_SEL16_Msk 		/*!< bit 16 */
#define TSC_CHNEN_CHN_SEL17_Pos					(17U)
#define TSC_CHNEN_CHN_SEL17_Msk					(0x1UL << TSC_CHNEN_CHN_SEL17_Pos)	/*!< 0x00020000 */
#define TSC_CHNEN_CHN_SEL17                    	TSC_CHNEN_CHN_SEL17_Msk 		/*!< bit 17 */
#define TSC_CHNEN_CHN_SEL18_Pos					(18U)
#define TSC_CHNEN_CHN_SEL18_Msk					(0x1UL << TSC_CHNEN_CHN_SEL18_Pos)	/*!< 0x00040000 */
#define TSC_CHNEN_CHN_SEL18                    	TSC_CHNEN_CHN_SEL18_Msk 		/*!< bit 18 */
#define TSC_CHNEN_CHN_SEL19_Pos					(19U)
#define TSC_CHNEN_CHN_SEL19_Msk					(0x1UL << TSC_CHNEN_CHN_SEL19_Pos)	/*!< 0x00080000 */
#define TSC_CHNEN_CHN_SEL19                    	TSC_CHNEN_CHN_SEL19_Msk 		/*!< bit 19 */
#define TSC_CHNEN_CHN_SEL20_Pos					(20U)
#define TSC_CHNEN_CHN_SEL20_Msk					(0x1UL << TSC_CHNEN_CHN_SEL20_Pos)	/*!< 0x00100000 */
#define TSC_CHNEN_CHN_SEL20                    	TSC_CHNEN_CHN_SEL20_Msk 		/*!< bit 20 */
#define TSC_CHNEN_CHN_SEL21_Pos					(21U)
#define TSC_CHNEN_CHN_SEL21_Msk					(0x1UL << TSC_CHNEN_CHN_SEL21_Pos)	/*!< 0x00200000 */
#define TSC_CHNEN_CHN_SEL21                    	TSC_CHNEN_CHN_SEL21_Msk 		/*!< bit 21 */
#define TSC_CHNEN_CHN_SEL22_Pos					(22U)
#define TSC_CHNEN_CHN_SEL22_Msk					(0x1UL << TSC_CHNEN_CHN_SEL22_Pos)	/*!< 0x00400000 */
#define TSC_CHNEN_CHN_SEL22                    	TSC_CHNEN_CHN_SEL22_Msk 		/*!< bit 22 */
#define TSC_CHNEN_CHN_SEL23_Pos					(23U)
#define TSC_CHNEN_CHN_SEL23_Msk					(0x1UL << TSC_CHNEN_CHN_SEL23_Pos)	/*!< 0x00800000 */
#define TSC_CHNEN_CHN_SEL23                    	TSC_CHNEN_CHN_SEL23_Msk 		/*!< bit 23 */

/*******************  Bit definition for TSC_STS register  ********************/
#define TSC_STS_CNT_VAL_Pos                 	(0U) 
#define TSC_STS_CNT_VAL_Msk						(0x7FFUL << TSC_STS_CNT_VAL_Pos)
#define TSC_STS_CNT_VAL							TSC_STS_CNT_VAL_Msk				/*!< CNT_VAL[10:0] (Count of value) */
#define TSC_STS_CNT_VAL_0                   	((uint32_t) 0x00000001)			/*!< Bit 0 */
#define TSC_STS_CNT_VAL_1                   	((uint32_t) 0x00000002)			/*!< Bit 1 */
#define TSC_STS_CNT_VAL_2                   	((uint32_t) 0x00000004)			/*!< Bit 2 */
#define TSC_STS_CNT_VAL_3                   	((uint32_t) 0x00000008)			/*!< Bit 3 */
#define TSC_STS_CNT_VAL_4                   	((uint32_t) 0x00000010)			/*!< Bit 4 */
#define TSC_STS_CNT_VAL_5                   	((uint32_t) 0x00000020)			/*!< Bit 5 */
#define TSC_STS_CNT_VAL_6                   	((uint32_t) 0x00000040)			/*!< Bit 6 */
#define TSC_STS_CNT_VAL_7                   	((uint32_t) 0x00000080)			/*!< Bit 7 */
#define TSC_STS_CNT_VAL_8                   	((uint32_t) 0x00000100)			/*!< Bit 8 */
#define TSC_STS_CNT_VAL_9                   	((uint32_t) 0x00000200)			/*!< Bit 9 */
#define TSC_STS_CNT_VAL_10                  	((uint32_t) 0x00000400)			/*!< Bit 10 */

#define TSC_STS_LESS_DET_Pos					(12U)
#define TSC_STS_LESS_DET_Msk					(0x1UL << TSC_STS_LESS_DET_Pos)
#define TSC_STS_LESS_DET                 		TSC_STS_LESS_DET_Msk			/*!< LESS_DET (Less threshold compare status) */
#define TSC_STS_GREAT_DET_Pos					(13U)
#define TSC_STS_GREAT_DET_Msk					(0x1UL << TSC_STS_GREAT_DET_Pos)
#define TSC_STS_GREAT_DET               		TSC_STS_GREAT_DET_Msk			/*!< GREAT_DET (Great threshold compare status) */

#define TSC_STS_CHN_NUM_Pos						(16U)
#define TSC_STS_CHN_NUM_Msk						(0x1FUL << TSC_STS_CHN_NUM_Pos)
#define TSC_STS_CHN_NUM                 		TSC_STS_CHN_NUM_Msk				/*!< CHN_NUM[4:0] (Number of detecting channel) */
#define TSC_STS_CHN_NUM_0                   	((uint32_t) 0x00010000)			/*!< Bit 0 */
#define TSC_STS_CHN_NUM_1                   	((uint32_t) 0x00020000)			/*!< Bit 1 */
#define TSC_STS_CHN_NUM_2                   	((uint32_t) 0x00040000)			/*!< Bit 2 */
#define TSC_STS_CHN_NUM_3                   	((uint32_t) 0x00080000)			/*!< Bit 3 */
#define TSC_STS_CHN_NUM_4                   	((uint32_t) 0x00100000)			/*!< Bit 4 */

/*****************  Bit definition for TSC_ANA_CTRL register  *****************/
#define TSC_ANA_CTRL_SW_PAD_MUX_Pos				(0U)
#define TSC_ANA_CTRL_SW_PAD_MUX_Msk				(0x1FUL << TSC_ANA_CTRL_SW_PAD_MUX_Pos)
#define TSC_ANA_CTRL_SW_PAD_MUX             	TSC_ANA_CTRL_SW_PAD_MUX_Msk		/*!< SW_PAD_MUX[4:0] (Select TSC channel) */
#define TSC_ANA_CTRL_SW_PAD_MUX_0           	((uint32_t) 0x00000001)			/*!< bit 0 */ 
#define TSC_ANA_CTRL_SW_PAD_MUX_1           	((uint32_t) 0x00000002)			/*!< bit 1 */ 
#define TSC_ANA_CTRL_SW_PAD_MUX_2           	((uint32_t) 0x00000004)			/*!< bit 2 */ 
#define TSC_ANA_CTRL_SW_PAD_MUX_3           	((uint32_t) 0x00000008)			/*!< bit 3 */ 
#define TSC_ANA_CTRL_SW_PAD_MUX_4           	((uint32_t) 0x00000010)			/*!< bit 4 */
 
 /*!< Select TSC channel configuration */
#define TSC_ANA_CTRL_SW_PAD_MUX_CH0         	((uint32_t) 0x00000000)			/*!< Channel 0  */
#define TSC_ANA_CTRL_SW_PAD_MUX_CH1         	((uint32_t) 0x00000001)			/*!< Channel 1  */
#define TSC_ANA_CTRL_SW_PAD_MUX_CH2         	((uint32_t) 0x00000002)			/*!< Channel 2  */
#define TSC_ANA_CTRL_SW_PAD_MUX_CH3         	((uint32_t) 0x00000003)			/*!< Channel 3  */
#define TSC_ANA_CTRL_SW_PAD_MUX_CH4         	((uint32_t) 0x00000004)			/*!< Channel 4  */
#define TSC_ANA_CTRL_SW_PAD_MUX_CH5         	((uint32_t) 0x00000005)			/*!< Channel 5  */
#define TSC_ANA_CTRL_SW_PAD_MUX_CH6         	((uint32_t) 0x00000006)			/*!< Channel 6  */
#define TSC_ANA_CTRL_SW_PAD_MUX_CH7         	((uint32_t) 0x00000007)			/*!< Channel 7  */
#define TSC_ANA_CTRL_SW_PAD_MUX_CH8         	((uint32_t) 0x00000008)			/*!< Channel 8  */
#define TSC_ANA_CTRL_SW_PAD_MUX_CH9         	((uint32_t) 0x00000009)			/*!< Channel 9  */
#define TSC_ANA_CTRL_SW_PAD_MUX_CH10        	((uint32_t) 0x0000000A)			/*!< Channel 10 */
#define TSC_ANA_CTRL_SW_PAD_MUX_CH11        	((uint32_t) 0x0000000B)			/*!< Channel 11 */
#define TSC_ANA_CTRL_SW_PAD_MUX_CH12        	((uint32_t) 0x0000000C)			/*!< Channel 12 */
#define TSC_ANA_CTRL_SW_PAD_MUX_CH13        	((uint32_t) 0x0000000D)			/*!< Channel 13 */
#define TSC_ANA_CTRL_SW_PAD_MUX_CH14        	((uint32_t) 0x0000000E)			/*!< Channel 14 */
#define TSC_ANA_CTRL_SW_PAD_MUX_CH15        	((uint32_t) 0x0000000F)			/*!< Channel 15 */
#define TSC_ANA_CTRL_SW_PAD_MUX_CH16        	((uint32_t) 0x00000010)			/*!< Channel 16 */
#define TSC_ANA_CTRL_SW_PAD_MUX_CH17        	((uint32_t) 0x00000011)			/*!< Channel 17 */
#define TSC_ANA_CTRL_SW_PAD_MUX_CH18        	((uint32_t) 0x00000012)			/*!< Channel 18 */
#define TSC_ANA_CTRL_SW_PAD_MUX_CH19        	((uint32_t) 0x00000013)			/*!< Channel 19 */
#define TSC_ANA_CTRL_SW_PAD_MUX_CH20        	((uint32_t) 0x00000014)			/*!< Channel 20 */
#define TSC_ANA_CTRL_SW_PAD_MUX_CH21        	((uint32_t) 0x00000015)			/*!< Channel 21 */
#define TSC_ANA_CTRL_SW_PAD_MUX_CH22        	((uint32_t) 0x00000016)			/*!< Channel 22 */
#define TSC_ANA_CTRL_SW_PAD_MUX_CH23        	((uint32_t) 0x00000017)			/*!< Channel 23 */

#define TSC_ANA_CTRL_SW_TSC_EN_Pos				(5U)
#define TSC_ANA_CTRL_SW_TSC_EN_Msk				(0x1UL << TSC_ANA_CTRL_SW_TSC_EN_Pos)
#define TSC_ANA_CTRL_SW_TSC_EN              	TSC_ANA_CTRL_SW_TSC_EN_Msk		/*!< PAD_OPT (Enable TSC software mode) */

/*****************  Bit definition for TSC_ANA_SEL register  ******************/
#define TSC_ANA_SEL_SP_OPT_Pos					(4U)
#define TSC_ANA_SEL_SP_OPT_Msk					(0x3UL << TSC_ANA_SEL_SP_OPT_Pos)
#define TSC_ANA_SEL_SP_OPT                  	TSC_ANA_SEL_SP_OPT_Msk			/*!< SP_OPT[1:0] (TSC speed configuration) */
#define TSC_ANA_SEL_SP_OPT_0                	((uint32_t) 0x00000010)			/*!< Bit 0 */
#define TSC_ANA_SEL_SP_OPT_1                	((uint32_t) 0x00000020)			/*!< Bit 1 */

/*!< TSC speed configuration */
#define TSC_ANA_SEL_SP_OPT_LOW_SPEED        	((uint32_t) 0x00000000)			/*!< Low speed tsc(about 100kHz) */
#define TSC_ANA_SEL_SP_OPT_MIDDLE_SPEED1    	((uint32_t) 0x00000010)			/*!< middle speed tsc */
#define TSC_ANA_SEL_SP_OPT_MIDDLE_SPEED2    	((uint32_t) 0x00000020)			/*!< middle speed tsc */
#define TSC_ANA_SEL_SP_OPT_HIGH_SPEED       	((uint32_t) 0x00000030)			/*!< high speed tsc */

#define TSC_ANA_SEL_PAD_OPT_Pos					(6U)
#define TSC_ANA_SEL_PAD_OPT_Msk					(0x1UL << TSC_ANA_SEL_PAD_OPT_Pos)
#define TSC_ANA_SEL_PAD_OPT                 	TSC_ANA_SEL_PAD_OPT_Msk			/*!< PAD_OPT (TSC charge options) */

/******************  Bit definition for TSC_RESR0 register  *******************/
#define TSC_RESR0_CHN_RESIST0_Pos				(0U)
#define TSC_RESR0_CHN_RESIST0_Msk				(0x7UL << TSC_RESR0_CHN_RESIST0_Pos)
#define TSC_RESR0_CHN_RESIST0               	TSC_RESR0_CHN_RESIST0_Msk		/*!< CHN_RESIST0[2:0] (Select internal resistance) */
#define TSC_RESR0_CHN_RESIST0_0             	((uint32_t) 0x00000001)			/*!< Bit 0 */
#define TSC_RESR0_CHN_RESIST0_1             	((uint32_t) 0x00000002)			/*!< Bit 1 */
#define TSC_RESR0_CHN_RESIST0_2             	((uint32_t) 0x00000004)			/*!< Bit 2 */

/*!< CHN_RESIST0 configuration */
#define TSC_RESR0_CHN_RESIST0_1M            	((uint32_t) 0x00000000)			/*!< 1M	   */
#define TSC_RESR0_CHN_RESIST0_875K          	((uint32_t) 0x00000001)			/*!< 875K  */
#define TSC_RESR0_CHN_RESIST0_750K          	((uint32_t) 0x00000002)			/*!< 750K  */
#define TSC_RESR0_CHN_RESIST0_625K          	((uint32_t) 0x00000003)			/*!< 625K  */
#define TSC_RESR0_CHN_RESIST0_500K          	((uint32_t) 0x00000004)			/*!< 500K  */
#define TSC_RESR0_CHN_RESIST0_375K          	((uint32_t) 0x00000005)			/*!< 375K  */
#define TSC_RESR0_CHN_RESIST0_250K          	((uint32_t) 0x00000006)			/*!< 250K  */
#define TSC_RESR0_CHN_RESIST0_125K          	((uint32_t) 0x00000007)			/*!< 125K  */

#define TSC_RESR0_CHN_RESIST1_Pos				(4U)
#define TSC_RESR0_CHN_RESIST1_Msk				(0x7UL << TSC_RESR0_CHN_RESIST1_Pos)
#define TSC_RESR0_CHN_RESIST1               	TSC_RESR0_CHN_RESIST1_Msk		/*!< CHN_RESIST1[2:0] (Select internal resistance) */
#define TSC_RESR0_CHN_RESIST1_0             	((uint32_t) 0x00000010)			/*!< Bit 0 */
#define TSC_RESR0_CHN_RESIST1_1             	((uint32_t) 0x00000020)			/*!< Bit 1 */
#define TSC_RESR0_CHN_RESIST1_2             	((uint32_t) 0x00000040)			/*!< Bit 2 */

/*!< CHN_RESIST1 configuration */
#define TSC_RESR0_CHN_RESIST1_1M            	((uint32_t) 0x00000000) 		/*!< 1M   */
#define TSC_RESR0_CHN_RESIST1_882K          	((uint32_t) 0x00000010) 		/*!< 882K */
#define TSC_RESR0_CHN_RESIST1_756K          	((uint32_t) 0x00000020) 		/*!< 756K */
#define TSC_RESR0_CHN_RESIST1_630K          	((uint32_t) 0x00000030) 		/*!< 630K */
#define TSC_RESR0_CHN_RESIST1_504K          	((uint32_t) 0x00000040) 		/*!< 504K */
#define TSC_RESR0_CHN_RESIST1_378K          	((uint32_t) 0x00000050) 		/*!< 378K */
#define TSC_RESR0_CHN_RESIST1_252K          	((uint32_t) 0x00000060) 		/*!< 252K */
#define TSC_RESR0_CHN_RESIST1_126K          	((uint32_t) 0x00000070) 		/*!< 126K */

#define TSC_RESR0_CHN_RESIST2_Pos				(8U)
#define TSC_RESR0_CHN_RESIST2_Msk				(0x7UL << TSC_RESR0_CHN_RESIST2_Pos)
#define TSC_RESR0_CHN_RESIST2               	TSC_RESR0_CHN_RESIST2_Msk		/*!< CHN_RESIST2[2:0] (Select internal resistance) */
#define TSC_RESR0_CHN_RESIST2_0             	((uint32_t) 0x00000100)			/*!< Bit 0 */
#define TSC_RESR0_CHN_RESIST2_1             	((uint32_t) 0x00000200)			/*!< Bit 1 */
#define TSC_RESR0_CHN_RESIST2_2             	((uint32_t) 0x00000400)			/*!< Bit 2 */

/*!< CHN_RESIST2 configuration */
#define TSC_RESR0_CHN_RESIST2_1M            	((uint32_t) 0x00000000)			/*!< 1M   */
#define TSC_RESR0_CHN_RESIST2_882K          	((uint32_t) 0x00000100)			/*!< 882K */
#define TSC_RESR0_CHN_RESIST2_756K          	((uint32_t) 0x00000200)			/*!< 756K */
#define TSC_RESR0_CHN_RESIST2_630K          	((uint32_t) 0x00000300)			/*!< 630K */
#define TSC_RESR0_CHN_RESIST2_504K          	((uint32_t) 0x00000400)			/*!< 504K */
#define TSC_RESR0_CHN_RESIST2_378K          	((uint32_t) 0x00000500)			/*!< 378K */
#define TSC_RESR0_CHN_RESIST2_252K          	((uint32_t) 0x00000600)			/*!< 252K */
#define TSC_RESR0_CHN_RESIST2_126K          	((uint32_t) 0x00000700)			/*!< 126K */

#define TSC_RESR0_CHN_RESIST3_Pos				(12U)
#define TSC_RESR0_CHN_RESIST3_Msk				(0x7UL << TSC_RESR0_CHN_RESIST3_Pos)
#define TSC_RESR0_CHN_RESIST3               	TSC_RESR0_CHN_RESIST3_Msk		/*!< CHN_RESIST3[2:0] (Select internal resistance) */
#define TSC_RESR0_CHN_RESIST3_0             	((uint32_t) 0x00001000)			/*!< Bit 0 */
#define TSC_RESR0_CHN_RESIST3_1             	((uint32_t) 0x00002000)			/*!< Bit 1 */
#define TSC_RESR0_CHN_RESIST3_2             	((uint32_t) 0x00004000)			/*!< Bit 2 */

/*!< CHN_RESIST3 configuration */
#define TSC_RESR0_CHN_RESIST3_1M            	((uint32_t) 0x00000000)			/*!< 1M   */
#define TSC_RESR0_CHN_RESIST3_882K          	((uint32_t) 0x00001000)			/*!< 882K */
#define TSC_RESR0_CHN_RESIST3_756K          	((uint32_t) 0x00002000)			/*!< 756K */
#define TSC_RESR0_CHN_RESIST3_630K          	((uint32_t) 0x00003000)			/*!< 630K */
#define TSC_RESR0_CHN_RESIST3_504K          	((uint32_t) 0x00004000)			/*!< 504K */
#define TSC_RESR0_CHN_RESIST3_378K          	((uint32_t) 0x00005000)			/*!< 378K */
#define TSC_RESR0_CHN_RESIST3_252K          	((uint32_t) 0x00006000)			/*!< 252K */
#define TSC_RESR0_CHN_RESIST3_126K          	((uint32_t) 0x00007000)			/*!< 126K */

#define TSC_RESR0_CHN_RESIST4_Pos				(16U)
#define TSC_RESR0_CHN_RESIST4_Msk				(0x7UL << TSC_RESR0_CHN_RESIST4_Pos)
#define TSC_RESR0_CHN_RESIST4               	TSC_RESR0_CHN_RESIST4_Msk		/*!< CHN_RESIST4[2:0] (Select internal resistance) */
#define TSC_RESR0_CHN_RESIST4_0             	((uint32_t) 0x00010000)			/*!< Bit 0 */
#define TSC_RESR0_CHN_RESIST4_1             	((uint32_t) 0x00020000)			/*!< Bit 1 */
#define TSC_RESR0_CHN_RESIST4_2             	((uint32_t) 0x00040000)			/*!< Bit 2 */

/*!< CHN_RESIST4 configuration */
#define TSC_RESR0_CHN_RESIST4_1M            	((uint32_t) 0x00000000)			/*!< 1M   */
#define TSC_RESR0_CHN_RESIST4_882K          	((uint32_t) 0x00010000)			/*!< 882K */
#define TSC_RESR0_CHN_RESIST4_756K          	((uint32_t) 0x00020000)			/*!< 756K */
#define TSC_RESR0_CHN_RESIST4_630K          	((uint32_t) 0x00030000)			/*!< 630K */
#define TSC_RESR0_CHN_RESIST4_504K          	((uint32_t) 0x00040000)			/*!< 504K */
#define TSC_RESR0_CHN_RESIST4_378K          	((uint32_t) 0x00050000)			/*!< 378K */
#define TSC_RESR0_CHN_RESIST4_252K          	((uint32_t) 0x00060000)			/*!< 252K */
#define TSC_RESR0_CHN_RESIST4_126K          	((uint32_t) 0x00070000)			/*!< 126K */

#define TSC_RESR0_CHN_RESIST5_Pos				(20U)
#define TSC_RESR0_CHN_RESIST5_Msk				(0x7UL << TSC_RESR0_CHN_RESIST5_Pos)
#define TSC_RESR0_CHN_RESIST5               	TSC_RESR0_CHN_RESIST5_Msk		/*!< CHN_RESIST5[2:0] (Select internal resistance) */
#define TSC_RESR0_CHN_RESIST5_0             	((uint32_t) 0x00100000)			/*!< Bit 0 */
#define TSC_RESR0_CHN_RESIST5_1             	((uint32_t) 0x00200000)			/*!< Bit 1 */
#define TSC_RESR0_CHN_RESIST5_2             	((uint32_t) 0x00400000)			/*!< Bit 2 */

/*!< CHN_RESIST5 configuration */
#define TSC_RESR0_CHN_RESIST5_1M            	((uint32_t) 0x00000000)			/*!< 1M   */
#define TSC_RESR0_CHN_RESIST5_882K          	((uint32_t) 0x00100000)			/*!< 882K */
#define TSC_RESR0_CHN_RESIST5_756K          	((uint32_t) 0x00200000)			/*!< 756K */
#define TSC_RESR0_CHN_RESIST5_630K          	((uint32_t) 0x00300000)			/*!< 630K */
#define TSC_RESR0_CHN_RESIST5_504K          	((uint32_t) 0x00400000)			/*!< 504K */
#define TSC_RESR0_CHN_RESIST5_378K          	((uint32_t) 0x00500000)			/*!< 378K */
#define TSC_RESR0_CHN_RESIST5_252K          	((uint32_t) 0x00600000)			/*!< 252K */
#define TSC_RESR0_CHN_RESIST5_126K          	((uint32_t) 0x00700000)			/*!< 126K */

#define TSC_RESR0_CHN_RESIST6_Pos				(24U)
#define TSC_RESR0_CHN_RESIST6_Msk				(0x7UL << TSC_RESR0_CHN_RESIST6_Pos)
#define TSC_RESR0_CHN_RESIST6               	TSC_RESR0_CHN_RESIST6_Msk		/*!< CHN_RESIST6[2:0] (Select internal resistance) */
#define TSC_RESR0_CHN_RESIST6_0             	((uint32_t) 0x01000000)			/*!< Bit 0 */
#define TSC_RESR0_CHN_RESIST6_1             	((uint32_t) 0x02000000)			/*!< Bit 1 */
#define TSC_RESR0_CHN_RESIST6_2             	((uint32_t) 0x04000000)			/*!< Bit 2 */

/*!< CHN_RESIST6 configuration */
#define TSC_RESR0_CHN_RESIST6_1M            	((uint32_t) 0x00000000)			/*!< 1M   */
#define TSC_RESR0_CHN_RESIST6_882K          	((uint32_t) 0x01000000)			/*!< 882K */
#define TSC_RESR0_CHN_RESIST6_756K          	((uint32_t) 0x02000000)			/*!< 756K */
#define TSC_RESR0_CHN_RESIST6_630K          	((uint32_t) 0x03000000)			/*!< 630K */
#define TSC_RESR0_CHN_RESIST6_504K          	((uint32_t) 0x04000000)			/*!< 504K */
#define TSC_RESR0_CHN_RESIST6_378K          	((uint32_t) 0x05000000)			/*!< 378K */
#define TSC_RESR0_CHN_RESIST6_252K          	((uint32_t) 0x06000000)			/*!< 252K */
#define TSC_RESR0_CHN_RESIST6_126K          	((uint32_t) 0x07000000)			/*!< 126K */

#define TSC_RESR0_CHN_RESIST7_Pos				(28U)
#define TSC_RESR0_CHN_RESIST7_Msk				(0x7UL << TSC_RESR0_CHN_RESIST7_Pos)
#define TSC_RESR0_CHN_RESIST7               	TSC_RESR0_CHN_RESIST7_Msk		/*!< CHN_RESIST7[2:0] (Select internal resistance) */
#define TSC_RESR0_CHN_RESIST7_0             	((uint32_t) 0x10000000)			/*!< Bit 0 */
#define TSC_RESR0_CHN_RESIST7_1             	((uint32_t) 0x20000000)			/*!< Bit 1 */
#define TSC_RESR0_CHN_RESIST7_2             	((uint32_t) 0x40000000)			/*!< Bit 2 */

/*!< CHN_RESIST7 configuration */
#define TSC_RESR0_CHN_RESIST7_1M            	((uint32_t) 0x00000000)			/*!< 1M   */
#define TSC_RESR0_CHN_RESIST7_882K          	((uint32_t) 0x10000000)			/*!< 882K */
#define TSC_RESR0_CHN_RESIST7_756K          	((uint32_t) 0x20000000)			/*!< 756K */
#define TSC_RESR0_CHN_RESIST7_630K          	((uint32_t) 0x30000000)			/*!< 630K */
#define TSC_RESR0_CHN_RESIST7_504K          	((uint32_t) 0x40000000)			/*!< 504K */
#define TSC_RESR0_CHN_RESIST7_378K          	((uint32_t) 0x50000000)			/*!< 378K */
#define TSC_RESR0_CHN_RESIST7_252K          	((uint32_t) 0x60000000)			/*!< 252K */
#define TSC_RESR0_CHN_RESIST7_126K          	((uint32_t) 0x70000000)			/*!< 126K */

/******************  Bit definition for TSC_RESR1 register  *******************/
#define TSC_RESR1_CHN_RESIST8_Pos				(0U)
#define TSC_RESR1_CHN_RESIST8_Msk				(0x7UL << TSC_RESR1_CHN_RESIST8_Pos)
#define TSC_RESR1_CHN_RESIST8               	TSC_RESR1_CHN_RESIST8_Msk		/*!< CHN_RESIST8[2:0] (Select internal resistance) */
#define TSC_RESR1_CHN_RESIST8_0             	((uint32_t) 0x00000001)			/*!< Bit 0 */
#define TSC_RESR1_CHN_RESIST8_1             	((uint32_t) 0x00000002)			/*!< Bit 1 */
#define TSC_RESR1_CHN_RESIST8_2             	((uint32_t) 0x00000004)			/*!< Bit 2 */

/*!< CHN_RESIST8 configuration */
#define TSC_RESR1_CHN_RESIST8_1M            	((uint32_t) 0x00000000)			/*!< 1M   */
#define TSC_RESR1_CHN_RESIST8_882K          	((uint32_t) 0x00000001)			/*!< 882K */
#define TSC_RESR1_CHN_RESIST8_756K          	((uint32_t) 0x00000002)			/*!< 756K */
#define TSC_RESR1_CHN_RESIST8_630K          	((uint32_t) 0x00000003)			/*!< 630K */
#define TSC_RESR1_CHN_RESIST8_504K          	((uint32_t) 0x00000004)			/*!< 504K */
#define TSC_RESR1_CHN_RESIST8_378K          	((uint32_t) 0x00000005)			/*!< 378K */
#define TSC_RESR1_CHN_RESIST8_252K          	((uint32_t) 0x00000006)			/*!< 252K */
#define TSC_RESR1_CHN_RESIST8_126K          	((uint32_t) 0x00000007)			/*!< 126K */

#define TSC_RESR1_CHN_RESIST9_Pos				(4U)
#define TSC_RESR1_CHN_RESIST9_Msk				(0x7UL << TSC_RESR1_CHN_RESIST9_Pos)
#define TSC_RESR1_CHN_RESIST9               	TSC_RESR1_CHN_RESIST9_Msk		/*!< CHN_RESIST9[2:0] (Select internal resistance) */
#define TSC_RESR1_CHN_RESIST9_0             	((uint32_t) 0x00000010)			/*!< Bit 0 */
#define TSC_RESR1_CHN_RESIST9_1             	((uint32_t) 0x00000020)			/*!< Bit 1 */
#define TSC_RESR1_CHN_RESIST9_2             	((uint32_t) 0x00000040)			/*!< Bit 2 */

/*!< CHN_RESIST9 configuration */
#define TSC_RESR1_CHN_RESIST9_1M            	((uint32_t) 0x00000000)			/*!< 1M   */
#define TSC_RESR1_CHN_RESIST9_882K          	((uint32_t) 0x00000010)			/*!< 882K */
#define TSC_RESR1_CHN_RESIST9_756K          	((uint32_t) 0x00000020)			/*!< 756K */
#define TSC_RESR1_CHN_RESIST9_630K          	((uint32_t) 0x00000030)			/*!< 630K */
#define TSC_RESR1_CHN_RESIST9_504K          	((uint32_t) 0x00000040)			/*!< 504K */
#define TSC_RESR1_CHN_RESIST9_378K          	((uint32_t) 0x00000050)			/*!< 378K */
#define TSC_RESR1_CHN_RESIST9_252K          	((uint32_t) 0x00000060)			/*!< 252K */
#define TSC_RESR1_CHN_RESIST9_126K          	((uint32_t) 0x00000070)			/*!< 126K */

#define TSC_RESR1_CHN_RESIST10_Pos				(8U)
#define TSC_RESR1_CHN_RESIST10_Msk				(0x7UL << TSC_RESR1_CHN_RESIST10_Pos)
#define TSC_RESR1_CHN_RESIST10               	TSC_RESR1_CHN_RESIST10_Msk		/*!< CHN_RESIST10[2:0] (Select internal resistance) */
#define TSC_RESR1_CHN_RESIST10_0             	((uint32_t) 0x00000100)			/*!< Bit 0 */
#define TSC_RESR1_CHN_RESIST10_1             	((uint32_t) 0x00000200)			/*!< Bit 1 */
#define TSC_RESR1_CHN_RESIST10_2             	((uint32_t) 0x00000400)			/*!< Bit 2 */

/*!< CHN_RESIST10 configuration */
#define TSC_RESR1_CHN_RESIST10_1M            	((uint32_t) 0x00000000)			/*!< 1M   */
#define TSC_RESR1_CHN_RESIST10_882K          	((uint32_t) 0x00000100)			/*!< 882K */
#define TSC_RESR1_CHN_RESIST10_756K          	((uint32_t) 0x00000200)			/*!< 756K */
#define TSC_RESR1_CHN_RESIST10_630K          	((uint32_t) 0x00000300)			/*!< 630K */
#define TSC_RESR1_CHN_RESIST10_504K          	((uint32_t) 0x00000400)			/*!< 504K */
#define TSC_RESR1_CHN_RESIST10_378K          	((uint32_t) 0x00000500)			/*!< 378K */
#define TSC_RESR1_CHN_RESIST10_252K          	((uint32_t) 0x00000600)			/*!< 252K */
#define TSC_RESR1_CHN_RESIST10_126K          	((uint32_t) 0x00000700)			/*!< 126K */

#define TSC_RESR1_CHN_RESIST11_Pos				(12U)
#define TSC_RESR1_CHN_RESIST11_Msk				(0x7UL << TSC_RESR1_CHN_RESIST11_Pos)
#define TSC_RESR1_CHN_RESIST11               	TSC_RESR1_CHN_RESIST11_Msk		/*!< CHN_RESIST11[2:0] (Select internal resistance) */
#define TSC_RESR1_CHN_RESIST11_0             	((uint32_t) 0x00001000)			/*!< Bit 0 */
#define TSC_RESR1_CHN_RESIST11_1             	((uint32_t) 0x00002000)			/*!< Bit 1 */
#define TSC_RESR1_CHN_RESIST11_2             	((uint32_t) 0x00004000)			/*!< Bit 2 */

/*!< CHN_RESIST11 configuration */
#define TSC_RESR1_CHN_RESIST11_1M            	((uint32_t) 0x00000000)			/*!< 1M   */
#define TSC_RESR1_CHN_RESIST11_882K          	((uint32_t) 0x00001000)			/*!< 882K */
#define TSC_RESR1_CHN_RESIST11_756K          	((uint32_t) 0x00002000)			/*!< 756K */
#define TSC_RESR1_CHN_RESIST11_630K          	((uint32_t) 0x00003000)			/*!< 630K */
#define TSC_RESR1_CHN_RESIST11_504K          	((uint32_t) 0x00004000)			/*!< 504K */
#define TSC_RESR1_CHN_RESIST11_378K          	((uint32_t) 0x00005000)			/*!< 378K */
#define TSC_RESR1_CHN_RESIST11_252K          	((uint32_t) 0x00006000)			/*!< 252K */
#define TSC_RESR1_CHN_RESIST11_126K          	((uint32_t) 0x00007000)			/*!< 126K */

#define TSC_RESR1_CHN_RESIST12_Pos				(16U)
#define TSC_RESR1_CHN_RESIST12_Msk				(0x7UL << TSC_RESR1_CHN_RESIST12_Pos)
#define TSC_RESR1_CHN_RESIST12               	TSC_RESR1_CHN_RESIST12_Msk		/*!< CHN_RESIST12[2:0] (Select internal resistance) */
#define TSC_RESR1_CHN_RESIST12_0             	((uint32_t) 0x00010000)			/*!< Bit 0 */
#define TSC_RESR1_CHN_RESIST12_1             	((uint32_t) 0x00020000)			/*!< Bit 1 */
#define TSC_RESR1_CHN_RESIST12_2             	((uint32_t) 0x00040000)			/*!< Bit 2 */

/*!< CHN_RESIST12 configuration */
#define TSC_RESR1_CHN_RESIST12_1M            	((uint32_t) 0x00000000)			/*!< 1M   */
#define TSC_RESR1_CHN_RESIST12_882K          	((uint32_t) 0x00010000)			/*!< 882K */
#define TSC_RESR1_CHN_RESIST12_756K          	((uint32_t) 0x00020000)			/*!< 756K */
#define TSC_RESR1_CHN_RESIST12_630K          	((uint32_t) 0x00030000)			/*!< 630K */
#define TSC_RESR1_CHN_RESIST12_504K          	((uint32_t) 0x00040000)			/*!< 504K */
#define TSC_RESR1_CHN_RESIST12_378K          	((uint32_t) 0x00050000)			/*!< 378K */
#define TSC_RESR1_CHN_RESIST12_252K          	((uint32_t) 0x00060000)			/*!< 252K */
#define TSC_RESR1_CHN_RESIST12_126K          	((uint32_t) 0x00070000)			/*!< 126K */

#define TSC_RESR1_CHN_RESIST13_Pos				(20U)
#define TSC_RESR1_CHN_RESIST13_Msk				(0x7UL << TSC_RESR1_CHN_RESIST13_Pos)
#define TSC_RESR1_CHN_RESIST13               	TSC_RESR1_CHN_RESIST13_Msk		/*!< CHN_RESIST13[2:0] (Select internal resistance) */
#define TSC_RESR1_CHN_RESIST13_0             	((uint32_t) 0x00100000)			/*!< Bit 0 */
#define TSC_RESR1_CHN_RESIST13_1             	((uint32_t) 0x00200000)			/*!< Bit 1 */
#define TSC_RESR1_CHN_RESIST13_2             	((uint32_t) 0x00400000)			/*!< Bit 2 */

/*!< CHN_RESIST13 configuration */
#define TSC_RESR1_CHN_RESIST13_1M            	((uint32_t) 0x00000000)			/*!< 1M   */
#define TSC_RESR1_CHN_RESIST13_882K          	((uint32_t) 0x00100000)			/*!< 882K */
#define TSC_RESR1_CHN_RESIST13_756K          	((uint32_t) 0x00200000)			/*!< 756K */
#define TSC_RESR1_CHN_RESIST13_630K          	((uint32_t) 0x00300000)			/*!< 630K */
#define TSC_RESR1_CHN_RESIST13_504K          	((uint32_t) 0x00400000)			/*!< 504K */
#define TSC_RESR1_CHN_RESIST13_378K          	((uint32_t) 0x00500000)			/*!< 378K */
#define TSC_RESR1_CHN_RESIST13_252K          	((uint32_t) 0x00600000)			/*!< 252K */
#define TSC_RESR1_CHN_RESIST13_126K          	((uint32_t) 0x00700000)			/*!< 126K */

#define TSC_RESR1_CHN_RESIST14_Pos				(24U)
#define TSC_RESR1_CHN_RESIST14_Msk				(0x7UL << TSC_RESR1_CHN_RESIST14_Pos)
#define TSC_RESR1_CHN_RESIST14               	TSC_RESR1_CHN_RESIST14_Msk		/*!< CHN_RESIST14[2:0] (Select internal resistance) */
#define TSC_RESR1_CHN_RESIST14_0             	((uint32_t) 0x01000000)			/*!< Bit 0 */
#define TSC_RESR1_CHN_RESIST14_1             	((uint32_t) 0x02000000)			/*!< Bit 1 */
#define TSC_RESR1_CHN_RESIST14_2             	((uint32_t) 0x04000000)			/*!< Bit 2 */

/*!< CHN_RESIST14 configuration */
#define TSC_RESR1_CHN_RESIST14_1M            	((uint32_t) 0x00000000)			/*!< 1M   */
#define TSC_RESR1_CHN_RESIST14_882K          	((uint32_t) 0x01000000)			/*!< 882K */
#define TSC_RESR1_CHN_RESIST14_756K          	((uint32_t) 0x02000000)			/*!< 756K */
#define TSC_RESR1_CHN_RESIST14_630K          	((uint32_t) 0x03000000)			/*!< 630K */
#define TSC_RESR1_CHN_RESIST14_504K          	((uint32_t) 0x04000000)			/*!< 504K */
#define TSC_RESR1_CHN_RESIST14_378K          	((uint32_t) 0x05000000)			/*!< 378K */
#define TSC_RESR1_CHN_RESIST14_252K          	((uint32_t) 0x06000000)			/*!< 252K */
#define TSC_RESR1_CHN_RESIST14_126K          	((uint32_t) 0x07000000)			/*!< 126K */

#define TSC_RESR1_CHN_RESIST15_Pos				(28U)
#define TSC_RESR1_CHN_RESIST15_Msk				(0x7UL << TSC_RESR1_CHN_RESIST15_Pos)
#define TSC_RESR1_CHN_RESIST15               	TSC_RESR1_CHN_RESIST15_Msk		/*!< CHN_RESIST15[2:0] (Select internal resistance) */
#define TSC_RESR1_CHN_RESIST15_0             	((uint32_t) 0x10000000)			/*!< Bit 0 */
#define TSC_RESR1_CHN_RESIST15_1             	((uint32_t) 0x20000000)			/*!< Bit 1 */
#define TSC_RESR1_CHN_RESIST15_2             	((uint32_t) 0x40000000)			/*!< Bit 2 */

/*!< CHN_RESIST15 configuration */
#define TSC_RESR1_CHN_RESIST15_1M            	((uint32_t) 0x00000000)			/*!< 1M   */
#define TSC_RESR1_CHN_RESIST15_882K          	((uint32_t) 0x10000000)			/*!< 882K */
#define TSC_RESR1_CHN_RESIST15_756K          	((uint32_t) 0x20000000)			/*!< 756K */
#define TSC_RESR1_CHN_RESIST15_630K          	((uint32_t) 0x30000000)			/*!< 630K */
#define TSC_RESR1_CHN_RESIST15_504K          	((uint32_t) 0x40000000)			/*!< 504K */
#define TSC_RESR1_CHN_RESIST15_378K          	((uint32_t) 0x50000000)			/*!< 378K */
#define TSC_RESR1_CHN_RESIST15_252K          	((uint32_t) 0x60000000)			/*!< 252K */
#define TSC_RESR1_CHN_RESIST15_126K          	((uint32_t) 0x70000000)			/*!< 126K */

/******************  Bit definition for TSC_RESR2 register  *******************/
#define TSC_RESR2_CHN_RESIST16_Pos				(0U)
#define TSC_RESR2_CHN_RESIST16_Msk				(0x7UL << TSC_RESR2_CHN_RESIST16_Pos)
#define TSC_RESR2_CHN_RESIST16               	TSC_RESR2_CHN_RESIST16_Msk		/*!< CHN_RESIST16[2:0] (Select internal resistance) */
#define TSC_RESR2_CHN_RESIST16_0             	((uint32_t) 0x00000001)			/*!< Bit 0 */
#define TSC_RESR2_CHN_RESIST16_1             	((uint32_t) 0x00000002)			/*!< Bit 1 */
#define TSC_RESR2_CHN_RESIST16_2             	((uint32_t) 0x00000004)			/*!< Bit 2 */

/*!< CHN_RESIST16 configuration */
#define TSC_RESR2_CHN_RESIST16_1M            	((uint32_t) 0x00000000)			/*!< 1M   */
#define TSC_RESR2_CHN_RESIST16_882K          	((uint32_t) 0x00000001)			/*!< 882K */
#define TSC_RESR2_CHN_RESIST16_756K          	((uint32_t) 0x00000002)			/*!< 756K */
#define TSC_RESR2_CHN_RESIST16_630K          	((uint32_t) 0x00000003)			/*!< 630K */
#define TSC_RESR2_CHN_RESIST16_504K          	((uint32_t) 0x00000004)			/*!< 504K */
#define TSC_RESR2_CHN_RESIST16_378K          	((uint32_t) 0x00000005)			/*!< 378K */
#define TSC_RESR2_CHN_RESIST16_252K          	((uint32_t) 0x00000006)			/*!< 252K */
#define TSC_RESR2_CHN_RESIST16_126K          	((uint32_t) 0x00000007)			/*!< 126K */

#define TSC_RESR2_CHN_RESIST17_Pos				(4U)
#define TSC_RESR2_CHN_RESIST17_Msk				(0x7UL << TSC_RESR2_CHN_RESIST17_Pos)
#define TSC_RESR2_CHN_RESIST17               	TSC_RESR2_CHN_RESIST17_Msk		/*!< CHN_RESIST17[2:0] (Select internal resistance) */
#define TSC_RESR2_CHN_RESIST17_0             	((uint32_t) 0x00000010)			/*!< Bit 0 */
#define TSC_RESR2_CHN_RESIST17_1             	((uint32_t) 0x00000020)			/*!< Bit 1 */
#define TSC_RESR2_CHN_RESIST17_2             	((uint32_t) 0x00000040)			/*!< Bit 2 */

/*!< CHN_RESIST17 configuration */
#define TSC_RESR2_CHN_RESIST17_1M            	((uint32_t) 0x00000000)			/*!< 1M   */
#define TSC_RESR2_CHN_RESIST17_882K          	((uint32_t) 0x00000010)			/*!< 882K */
#define TSC_RESR2_CHN_RESIST17_756K          	((uint32_t) 0x00000020)			/*!< 756K */
#define TSC_RESR2_CHN_RESIST17_630K          	((uint32_t) 0x00000030)			/*!< 630K */
#define TSC_RESR2_CHN_RESIST17_504K          	((uint32_t) 0x00000040)			/*!< 504K */
#define TSC_RESR2_CHN_RESIST17_378K          	((uint32_t) 0x00000050)			/*!< 378K */
#define TSC_RESR2_CHN_RESIST17_252K          	((uint32_t) 0x00000060)			/*!< 252K */
#define TSC_RESR2_CHN_RESIST17_126K          	((uint32_t) 0x00000070)			/*!< 126K */

#define TSC_RESR2_CHN_RESIST18_Pos				(8U)
#define TSC_RESR2_CHN_RESIST18_Msk				(0x7UL << TSC_RESR2_CHN_RESIST18_Pos)
#define TSC_RESR2_CHN_RESIST18              	TSC_RESR2_CHN_RESIST18_Msk		/*!< CHN_RESIST18[2:0] (Select internal resistance) */
#define TSC_RESR2_CHN_RESIST18_0            	((uint32_t) 0x00000100)			/*!< Bit 0 */
#define TSC_RESR2_CHN_RESIST18_1            	((uint32_t) 0x00000200)			/*!< Bit 1 */
#define TSC_RESR2_CHN_RESIST18_2            	((uint32_t) 0x00000400)			/*!< Bit 2 */

/*!< CHN_RESIST18 configuration */
#define TSC_RESR2_CHN_RESIST18_1M           	((uint32_t) 0x00000000)			/*!< 1M   */
#define TSC_RESR2_CHN_RESIST18_882K         	((uint32_t) 0x00000100)			/*!< 882K */
#define TSC_RESR2_CHN_RESIST18_756K         	((uint32_t) 0x00000200)			/*!< 756K */
#define TSC_RESR2_CHN_RESIST18_630K         	((uint32_t) 0x00000300)			/*!< 630K */
#define TSC_RESR2_CHN_RESIST18_504K         	((uint32_t) 0x00000400)			/*!< 504K */
#define TSC_RESR2_CHN_RESIST18_378K         	((uint32_t) 0x00000500)			/*!< 378K */
#define TSC_RESR2_CHN_RESIST18_252K         	((uint32_t) 0x00000600)			/*!< 252K */
#define TSC_RESR2_CHN_RESIST18_126K         	((uint32_t) 0x00000700)			/*!< 126K */

#define TSC_RESR2_CHN_RESIST19_Pos				(12U)
#define TSC_RESR2_CHN_RESIST19_Msk				(0x7UL << TSC_RESR2_CHN_RESIST19_Pos)
#define TSC_RESR2_CHN_RESIST19               	TSC_RESR2_CHN_RESIST19_Msk		/*!< CHN_RESIST19[2:0] (Select internal resistance) */
#define TSC_RESR2_CHN_RESIST19_0             	((uint32_t) 0x00001000)			/*!< Bit 0 */
#define TSC_RESR2_CHN_RESIST19_1             	((uint32_t) 0x00002000)			/*!< Bit 1 */
#define TSC_RESR2_CHN_RESIST19_2             	((uint32_t) 0x00004000)			/*!< Bit 2 */

/*!< CHN_RESIST19 configuration */
#define TSC_RESR2_CHN_RESIST19_1M            	((uint32_t) 0x00000000)			/*!< 1M   */
#define TSC_RESR2_CHN_RESIST19_882K          	((uint32_t) 0x00001000)			/*!< 882K */
#define TSC_RESR2_CHN_RESIST19_756K          	((uint32_t) 0x00002000)			/*!< 756K */
#define TSC_RESR2_CHN_RESIST19_630K          	((uint32_t) 0x00003000)			/*!< 630K */
#define TSC_RESR2_CHN_RESIST19_504K          	((uint32_t) 0x00004000)			/*!< 504K */
#define TSC_RESR2_CHN_RESIST19_378K          	((uint32_t) 0x00005000)			/*!< 378K */
#define TSC_RESR2_CHN_RESIST19_252K          	((uint32_t) 0x00006000)			/*!< 252K */
#define TSC_RESR2_CHN_RESIST19_126K          	((uint32_t) 0x00007000)			/*!< 126K */

#define TSC_RESR2_CHN_RESIST20_Pos				(16U)
#define TSC_RESR2_CHN_RESIST20_Msk				(0x7UL << TSC_RESR2_CHN_RESIST20_Pos)
#define TSC_RESR2_CHN_RESIST20               	TSC_RESR2_CHN_RESIST20_Msk		/*!< CHN_RESIST20[2:0] (Select internal resistance) */
#define TSC_RESR2_CHN_RESIST20_0             	((uint32_t) 0x00010000)			/*!< Bit 0 */
#define TSC_RESR2_CHN_RESIST20_1             	((uint32_t) 0x00020000)			/*!< Bit 1 */
#define TSC_RESR2_CHN_RESIST20_2             	((uint32_t) 0x00040000)			/*!< Bit 2 */

/*!< CHN_RESIST20 configuration */
#define TSC_RESR2_CHN_RESIST20_1M            	((uint32_t) 0x00000000)			/*!< 1M   */
#define TSC_RESR2_CHN_RESIST20_882K          	((uint32_t) 0x00010000)			/*!< 882K */
#define TSC_RESR2_CHN_RESIST20_756K          	((uint32_t) 0x00020000)			/*!< 756K */
#define TSC_RESR2_CHN_RESIST20_630K          	((uint32_t) 0x00030000)			/*!< 630K */
#define TSC_RESR2_CHN_RESIST20_504K          	((uint32_t) 0x00040000)			/*!< 504K */
#define TSC_RESR2_CHN_RESIST20_378K          	((uint32_t) 0x00050000)			/*!< 378K */
#define TSC_RESR2_CHN_RESIST20_252K          	((uint32_t) 0x00060000)			/*!< 252K */
#define TSC_RESR2_CHN_RESIST20_126K          	((uint32_t) 0x00070000)			/*!< 126K */

#define TSC_RESR2_CHN_RESIST21_Pos				(20U)
#define TSC_RESR2_CHN_RESIST21_Msk				(0x7UL << TSC_RESR2_CHN_RESIST21_Pos)
#define TSC_RESR2_CHN_RESIST21               	TSC_RESR2_CHN_RESIST21_Msk		/*!< CHN_RESIST21[2:0] (Select internal resistance) */
#define TSC_RESR2_CHN_RESIST21_0             	((uint32_t) 0x00100000)			/*!< Bit 0 */
#define TSC_RESR2_CHN_RESIST21_1             	((uint32_t) 0x00200000)			/*!< Bit 1 */
#define TSC_RESR2_CHN_RESIST21_2             	((uint32_t) 0x00400000)			/*!< Bit 2 */

/*!< CHN_RESIST21 configuration */
#define TSC_RESR2_CHN_RESIST21_1M            	((uint32_t) 0x00000000)			/*!< 1M   */
#define TSC_RESR2_CHN_RESIST21_882K          	((uint32_t) 0x00100000)			/*!< 882K */
#define TSC_RESR2_CHN_RESIST21_756K          	((uint32_t) 0x00200000)			/*!< 756K */
#define TSC_RESR2_CHN_RESIST21_630K          	((uint32_t) 0x00300000)			/*!< 630K */
#define TSC_RESR2_CHN_RESIST21_504K          	((uint32_t) 0x00400000)			/*!< 504K */
#define TSC_RESR2_CHN_RESIST21_378K          	((uint32_t) 0x00500000)			/*!< 378K */
#define TSC_RESR2_CHN_RESIST21_252K          	((uint32_t) 0x00600000)			/*!< 252K */
#define TSC_RESR2_CHN_RESIST21_126K          	((uint32_t) 0x00700000)			/*!< 126K */

#define TSC_RESR2_CHN_RESIST22_Pos				(24U)
#define TSC_RESR2_CHN_RESIST22_Msk				(0x7UL << TSC_RESR2_CHN_RESIST22_Pos)
#define TSC_RESR2_CHN_RESIST22               	TSC_RESR2_CHN_RESIST22_Msk		/*!< CHN_RESIST22[2:0] (Select internal resistance) */
#define TSC_RESR2_CHN_RESIST22_0             	((uint32_t) 0x01000000)			/*!< Bit 0 */
#define TSC_RESR2_CHN_RESIST22_1             	((uint32_t) 0x02000000)			/*!< Bit 1 */
#define TSC_RESR2_CHN_RESIST22_2             	((uint32_t) 0x04000000)			/*!< Bit 2 */

/*!< CHN_RESIST22 configuration */
#define TSC_RESR2_CHN_RESIST22_1M            	((uint32_t) 0x00000000)			/*!< 1M   */
#define TSC_RESR2_CHN_RESIST22_882K          	((uint32_t) 0x01000000)			/*!< 882K */
#define TSC_RESR2_CHN_RESIST22_756K          	((uint32_t) 0x02000000)			/*!< 756K */
#define TSC_RESR2_CHN_RESIST22_630K          	((uint32_t) 0x03000000)			/*!< 630K */
#define TSC_RESR2_CHN_RESIST22_504K          	((uint32_t) 0x04000000)			/*!< 504K */
#define TSC_RESR2_CHN_RESIST22_378K          	((uint32_t) 0x05000000)			/*!< 378K */
#define TSC_RESR2_CHN_RESIST22_252K          	((uint32_t) 0x06000000)			/*!< 252K */
#define TSC_RESR2_CHN_RESIST22_126K          	((uint32_t) 0x07000000)			/*!< 126K */

#define TSC_RESR2_CHN_RESIST23_Pos				(28U)
#define TSC_RESR2_CHN_RESIST23_Msk				(0x7UL << TSC_RESR2_CHN_RESIST23_Pos)
#define TSC_RESR2_CHN_RESIST23               	TSC_RESR2_CHN_RESIST23_Msk		/*!< CHN_RESIST23[2:0] (Select internal resistance) */
#define TSC_RESR2_CHN_RESIST23_0             	((uint32_t) 0x10000000)			/*!< Bit 0 */
#define TSC_RESR2_CHN_RESIST23_1             	((uint32_t) 0x20000000)			/*!< Bit 1 */
#define TSC_RESR2_CHN_RESIST23_2             	((uint32_t) 0x40000000)			/*!< Bit 2 */

/*!< CHN_RESIST23 configuration */
#define TSC_RESR2_CHN_RESIST23_1M            	((uint32_t) 0x00000000)			/*!< 1M   */
#define TSC_RESR2_CHN_RESIST23_882K          	((uint32_t) 0x10000000)			/*!< 882K */
#define TSC_RESR2_CHN_RESIST23_756K          	((uint32_t) 0x20000000)			/*!< 756K */
#define TSC_RESR2_CHN_RESIST23_630K          	((uint32_t) 0x30000000)			/*!< 630K */
#define TSC_RESR2_CHN_RESIST23_504K          	((uint32_t) 0x40000000)			/*!< 504K */
#define TSC_RESR2_CHN_RESIST23_378K          	((uint32_t) 0x50000000)			/*!< 378K */
#define TSC_RESR2_CHN_RESIST23_252K          	((uint32_t) 0x60000000)			/*!< 252K */
#define TSC_RESR2_CHN_RESIST23_126K          	((uint32_t) 0x70000000)			/*!< 126K */

/******************  Bit definition for TSC_THRHD0 register  ******************/
#define TSC_THRHD0_BASE0_Pos					(0U)
#define TSC_THRHD0_BASE0_Msk					(0x7FFUL << TSC_THRHD0_BASE0_Pos)
#define TSC_THRHD0_BASE0						TSC_THRHD0_BASE0_Msk			/*!< BASE0[10:0] (value of base) */
#define TSC_THRHD0_BASE0_0						((uint32_t) 0x00000001)			/*!< Bit 0 */
#define TSC_THRHD0_BASE0_1                      ((uint32_t) 0x00000002)			/*!< Bit 1 */
#define TSC_THRHD0_BASE0_2                      ((uint32_t) 0x00000004)			/*!< Bit 2 */
#define TSC_THRHD0_BASE0_3                      ((uint32_t) 0x00000008)			/*!< Bit 3 */
#define TSC_THRHD0_BASE0_4                      ((uint32_t) 0x00000010)			/*!< Bit 4 */
#define TSC_THRHD0_BASE0_5                      ((uint32_t) 0x00000020)			/*!< Bit 5 */
#define TSC_THRHD0_BASE0_6                      ((uint32_t) 0x00000040)			/*!< Bit 6 */
#define TSC_THRHD0_BASE0_7                      ((uint32_t) 0x00000080)			/*!< Bit 7 */
#define TSC_THRHD0_BASE0_8                      ((uint32_t) 0x00000100)			/*!< Bit 8 */
#define TSC_THRHD0_BASE0_9                      ((uint32_t) 0x00000200)			/*!< Bit 9 */
#define TSC_THRHD0_BASE0_10                     ((uint32_t) 0x00000400)			/*!< Bit 10 */

#define TSC_THRHD0_DELTA0_Pos					(16U)
#define TSC_THRHD0_DELTA0_Msk					(0xFFUL << TSC_THRHD0_DELTA0_Pos)
#define TSC_THRHD0_DELTA0						TSC_THRHD0_DELTA0_Msk			/*!< DELTA0[7:0] (value of delta) */
#define TSC_THRHD0_DELTA0_0                  	((uint32_t) 0x00010000)			/*!< Bit 0 */
#define TSC_THRHD0_DELTA0_1                  	((uint32_t) 0x00020000)			/*!< Bit 1 */
#define TSC_THRHD0_DELTA0_2                  	((uint32_t) 0x00040000)			/*!< Bit 2 */
#define TSC_THRHD0_DELTA0_3                  	((uint32_t) 0x00080000)			/*!< Bit 3 */
#define TSC_THRHD0_DELTA0_4                  	((uint32_t) 0x00100000)			/*!< Bit 4 */
#define TSC_THRHD0_DELTA0_5                  	((uint32_t) 0x00200000)			/*!< Bit 5 */
#define TSC_THRHD0_DELTA0_6                  	((uint32_t) 0x00400000)			/*!< Bit 6 */
#define TSC_THRHD0_DELTA0_7                  	((uint32_t) 0x00800000)			/*!< Bit 7 */

/******************  Bit definition for TSC_THRHD1 register  ******************/
#define TSC_THRHD1_BASE1_Pos					(0U)
#define TSC_THRHD1_BASE1_Msk					(0x7FFUL << TSC_THRHD1_BASE1_Pos)
#define TSC_THRHD1_BASE1						TSC_THRHD1_BASE1_Msk			/*!< BASE1[10:0] (value of base) */
#define TSC_THRHD1_BASE1_0						((uint32_t) 0x00000001)			/*!< Bit 0 */
#define TSC_THRHD1_BASE1_1                      ((uint32_t) 0x00000002)			/*!< Bit 1 */
#define TSC_THRHD1_BASE1_2                      ((uint32_t) 0x00000004)			/*!< Bit 2 */
#define TSC_THRHD1_BASE1_3                      ((uint32_t) 0x00000008)			/*!< Bit 3 */
#define TSC_THRHD1_BASE1_4                      ((uint32_t) 0x00000010)			/*!< Bit 4 */
#define TSC_THRHD1_BASE1_5                      ((uint32_t) 0x00000020)			/*!< Bit 5 */
#define TSC_THRHD1_BASE1_6                      ((uint32_t) 0x00000040)			/*!< Bit 6 */
#define TSC_THRHD1_BASE1_7                      ((uint32_t) 0x00000080)			/*!< Bit 7 */
#define TSC_THRHD1_BASE1_8                      ((uint32_t) 0x00000100)			/*!< Bit 8 */
#define TSC_THRHD1_BASE1_9                      ((uint32_t) 0x00000200)			/*!< Bit 9 */
#define TSC_THRHD1_BASE1_10                     ((uint32_t) 0x00000400)			/*!< Bit 10 */

#define TSC_THRHD1_DELTA1_Pos					(16U)
#define TSC_THRHD1_DELTA1_Msk					(0xFFUL << TSC_THRHD1_DELTA1_Pos)
#define TSC_THRHD1_DELTA1						TSC_THRHD1_DELTA1_Msk			/*!< DELTA1[7:0] (value of delta) */
#define TSC_THRHD1_DELTA1_0                  	((uint32_t) 0x00010000)			/*!< Bit 0 */
#define TSC_THRHD1_DELTA1_1                  	((uint32_t) 0x00020000)			/*!< Bit 1 */
#define TSC_THRHD1_DELTA1_2                  	((uint32_t) 0x00040000)			/*!< Bit 2 */
#define TSC_THRHD1_DELTA1_3                  	((uint32_t) 0x00080000)			/*!< Bit 3 */
#define TSC_THRHD1_DELTA1_4                  	((uint32_t) 0x00100000)			/*!< Bit 4 */
#define TSC_THRHD1_DELTA1_5                  	((uint32_t) 0x00200000)			/*!< Bit 5 */
#define TSC_THRHD1_DELTA1_6                  	((uint32_t) 0x00400000)			/*!< Bit 6 */
#define TSC_THRHD1_DELTA1_7                  	((uint32_t) 0x00800000)			/*!< Bit 7 */

/******************  Bit definition for TSC_THRHD2 register  ******************/
#define TSC_THRHD2_BASE2_Pos					(0U)
#define TSC_THRHD2_BASE2_Msk					(0x7FFUL << TSC_THRHD2_BASE2_Pos)
#define TSC_THRHD2_BASE2						TSC_THRHD2_BASE2_Msk			/*!< BASE2[10:0] (value of base) */
#define TSC_THRHD2_BASE2_0						((uint32_t) 0x00000001)			/*!< Bit 0 */
#define TSC_THRHD2_BASE2_1                      ((uint32_t) 0x00000002)			/*!< Bit 1 */
#define TSC_THRHD2_BASE2_2                      ((uint32_t) 0x00000004)			/*!< Bit 2 */
#define TSC_THRHD2_BASE2_3                      ((uint32_t) 0x00000008)			/*!< Bit 3 */
#define TSC_THRHD2_BASE2_4                      ((uint32_t) 0x00000010)			/*!< Bit 4 */
#define TSC_THRHD2_BASE2_5                      ((uint32_t) 0x00000020)			/*!< Bit 5 */
#define TSC_THRHD2_BASE2_6                      ((uint32_t) 0x00000040)			/*!< Bit 6 */
#define TSC_THRHD2_BASE2_7                      ((uint32_t) 0x00000080)			/*!< Bit 7 */
#define TSC_THRHD2_BASE2_8                      ((uint32_t) 0x00000100)			/*!< Bit 8 */
#define TSC_THRHD2_BASE2_9                      ((uint32_t) 0x00000200)			/*!< Bit 9 */
#define TSC_THRHD2_BASE2_10                     ((uint32_t) 0x00000400)			/*!< Bit 10 */

#define TSC_THRHD2_DELTA2_Pos					(16U)
#define TSC_THRHD2_DELTA2_Msk					(0xFFUL << TSC_THRHD2_DELTA2_Pos)
#define TSC_THRHD2_DELTA2						TSC_THRHD2_DELTA2_Msk			/*!< DELTA2[7:0] (value of delta) */
#define TSC_THRHD2_DELTA2_0                  	((uint32_t) 0x00010000)			/*!< Bit 0 */
#define TSC_THRHD2_DELTA2_1                  	((uint32_t) 0x00020000)			/*!< Bit 1 */
#define TSC_THRHD2_DELTA2_2                  	((uint32_t) 0x00040000)			/*!< Bit 2 */
#define TSC_THRHD2_DELTA2_3                  	((uint32_t) 0x00080000)			/*!< Bit 3 */
#define TSC_THRHD2_DELTA2_4                  	((uint32_t) 0x00100000)			/*!< Bit 4 */
#define TSC_THRHD2_DELTA2_5                  	((uint32_t) 0x00200000)			/*!< Bit 5 */
#define TSC_THRHD2_DELTA2_6                  	((uint32_t) 0x00400000)			/*!< Bit 6 */
#define TSC_THRHD2_DELTA2_7                  	((uint32_t) 0x00800000)			/*!< Bit 7 */

/******************  Bit definition for TSC_THRHD3 register  ******************/
#define TSC_THRHD3_BASE3_Pos					(0U)
#define TSC_THRHD3_BASE3_Msk					(0x7FFUL << TSC_THRHD3_BASE3_Pos)
#define TSC_THRHD3_BASE3						TSC_THRHD3_BASE3_Msk			/*!< BASE3[10:0] (value of base) */
#define TSC_THRHD3_BASE3_0						((uint32_t) 0x00000001)			/*!< Bit 0 */
#define TSC_THRHD3_BASE3_1                      ((uint32_t) 0x00000002)			/*!< Bit 1 */
#define TSC_THRHD3_BASE3_2                      ((uint32_t) 0x00000004)			/*!< Bit 2 */
#define TSC_THRHD3_BASE3_3                      ((uint32_t) 0x00000008)			/*!< Bit 3 */
#define TSC_THRHD3_BASE3_4                      ((uint32_t) 0x00000010)			/*!< Bit 4 */
#define TSC_THRHD3_BASE3_5                      ((uint32_t) 0x00000020)			/*!< Bit 5 */
#define TSC_THRHD3_BASE3_6                      ((uint32_t) 0x00000040)			/*!< Bit 6 */
#define TSC_THRHD3_BASE3_7                      ((uint32_t) 0x00000080)			/*!< Bit 7 */
#define TSC_THRHD3_BASE3_8                      ((uint32_t) 0x00000100)			/*!< Bit 8 */
#define TSC_THRHD3_BASE3_9                      ((uint32_t) 0x00000200)			/*!< Bit 9 */
#define TSC_THRHD3_BASE3_10                     ((uint32_t) 0x00000400)			/*!< Bit 10 */

#define TSC_THRHD3_DELTA3_Pos					(16U)
#define TSC_THRHD3_DELTA3_Msk					(0xFFUL << TSC_THRHD3_DELTA3_Pos)
#define TSC_THRHD3_DELTA3						TSC_THRHD3_DELTA3_Msk			/*!< DELTA3[7:0] (value of delta) */
#define TSC_THRHD3_DELTA3_0                  	((uint32_t) 0x00010000)			/*!< Bit 0 */
#define TSC_THRHD3_DELTA3_1                  	((uint32_t) 0x00020000)			/*!< Bit 1 */
#define TSC_THRHD3_DELTA3_2                  	((uint32_t) 0x00040000)			/*!< Bit 2 */
#define TSC_THRHD3_DELTA3_3                  	((uint32_t) 0x00080000)			/*!< Bit 3 */
#define TSC_THRHD3_DELTA3_4                  	((uint32_t) 0x00100000)			/*!< Bit 4 */
#define TSC_THRHD3_DELTA3_5                  	((uint32_t) 0x00200000)			/*!< Bit 5 */
#define TSC_THRHD3_DELTA3_6                  	((uint32_t) 0x00400000)			/*!< Bit 6 */
#define TSC_THRHD3_DELTA3_7                  	((uint32_t) 0x00800000)			/*!< Bit 7 */

/******************  Bit definition for TSC_THRHD4 register  ******************/
#define TSC_THRHD4_BASE4_Pos					(0U)
#define TSC_THRHD4_BASE4_Msk					(0x7FFUL << TSC_THRHD4_BASE4_Pos)
#define TSC_THRHD4_BASE4						TSC_THRHD4_BASE4_Msk			/*!< BASE4[10:0] (value of base) */
#define TSC_THRHD4_BASE4_0						((uint32_t) 0x00000001)			/*!< Bit 0 */
#define TSC_THRHD4_BASE4_1                      ((uint32_t) 0x00000002)			/*!< Bit 1 */
#define TSC_THRHD4_BASE4_2                      ((uint32_t) 0x00000004)			/*!< Bit 2 */
#define TSC_THRHD4_BASE4_3                      ((uint32_t) 0x00000008)			/*!< Bit 3 */
#define TSC_THRHD4_BASE4_4                      ((uint32_t) 0x00000010)			/*!< Bit 4 */
#define TSC_THRHD4_BASE4_5                      ((uint32_t) 0x00000020)			/*!< Bit 5 */
#define TSC_THRHD4_BASE4_6                      ((uint32_t) 0x00000040)			/*!< Bit 6 */
#define TSC_THRHD4_BASE4_7                      ((uint32_t) 0x00000080)			/*!< Bit 7 */
#define TSC_THRHD4_BASE4_8                      ((uint32_t) 0x00000100)			/*!< Bit 8 */
#define TSC_THRHD4_BASE4_9                      ((uint32_t) 0x00000200)			/*!< Bit 9 */
#define TSC_THRHD4_BASE4_10                     ((uint32_t) 0x00000400)			/*!< Bit 10 */

#define TSC_THRHD4_DELTA4_Pos					(16U)
#define TSC_THRHD4_DELTA4_Msk					(0xFFUL << TSC_THRHD4_DELTA4_Pos)
#define TSC_THRHD4_DELTA4						TSC_THRHD4_DELTA4_Msk			/*!< DELTA4[7:0] (value of delta) */
#define TSC_THRHD4_DELTA4_0                  	((uint32_t) 0x00010000)			/*!< Bit 0 */
#define TSC_THRHD4_DELTA4_1                  	((uint32_t) 0x00020000)			/*!< Bit 1 */
#define TSC_THRHD4_DELTA4_2                  	((uint32_t) 0x00040000)			/*!< Bit 2 */
#define TSC_THRHD4_DELTA4_3                  	((uint32_t) 0x00080000)			/*!< Bit 3 */
#define TSC_THRHD4_DELTA4_4                  	((uint32_t) 0x00100000)			/*!< Bit 4 */
#define TSC_THRHD4_DELTA4_5                  	((uint32_t) 0x00200000)			/*!< Bit 5 */
#define TSC_THRHD4_DELTA4_6                  	((uint32_t) 0x00400000)			/*!< Bit 6 */
#define TSC_THRHD4_DELTA4_7                  	((uint32_t) 0x00800000)			/*!< Bit 7 */

/******************  Bit definition for TSC_THRHD5 register  ******************/
#define TSC_THRHD5_BASE5_Pos					(0U)
#define TSC_THRHD5_BASE5_Msk					(0x7FFUL << TSC_THRHD5_BASE5_Pos)
#define TSC_THRHD5_BASE5						TSC_THRHD5_BASE5_Msk			/*!< BASE5[10:0] (value of base) */
#define TSC_THRHD5_BASE5_0						((uint32_t) 0x00000001)			/*!< Bit 0 */
#define TSC_THRHD5_BASE5_1                      ((uint32_t) 0x00000002)			/*!< Bit 1 */
#define TSC_THRHD5_BASE5_2                      ((uint32_t) 0x00000004)			/*!< Bit 2 */
#define TSC_THRHD5_BASE5_3                      ((uint32_t) 0x00000008)			/*!< Bit 3 */
#define TSC_THRHD5_BASE5_4                      ((uint32_t) 0x00000010)			/*!< Bit 4 */
#define TSC_THRHD5_BASE5_5                      ((uint32_t) 0x00000020)			/*!< Bit 5 */
#define TSC_THRHD5_BASE5_6                      ((uint32_t) 0x00000040)			/*!< Bit 6 */
#define TSC_THRHD5_BASE5_7                      ((uint32_t) 0x00000080)			/*!< Bit 7 */
#define TSC_THRHD5_BASE5_8                      ((uint32_t) 0x00000100)			/*!< Bit 8 */
#define TSC_THRHD5_BASE5_9                      ((uint32_t) 0x00000200)			/*!< Bit 9 */
#define TSC_THRHD5_BASE5_10                     ((uint32_t) 0x00000400)			/*!< Bit 10 */

#define TSC_THRHD5_DELTA5_Pos					(16U)
#define TSC_THRHD5_DELTA5_Msk					(0xFFUL << TSC_THRHD5_DELTA5_Pos)
#define TSC_THRHD5_DELTA5						TSC_THRHD5_DELTA5_Msk			/*!< DELTA5[7:0] (value of delta) */
#define TSC_THRHD5_DELTA5_0                  	((uint32_t) 0x00010000)			/*!< Bit 0 */
#define TSC_THRHD5_DELTA5_1                  	((uint32_t) 0x00020000)			/*!< Bit 1 */
#define TSC_THRHD5_DELTA5_2                  	((uint32_t) 0x00040000)			/*!< Bit 2 */
#define TSC_THRHD5_DELTA5_3                  	((uint32_t) 0x00080000)			/*!< Bit 3 */
#define TSC_THRHD5_DELTA5_4                  	((uint32_t) 0x00100000)			/*!< Bit 4 */
#define TSC_THRHD5_DELTA5_5                  	((uint32_t) 0x00200000)			/*!< Bit 5 */
#define TSC_THRHD5_DELTA5_6                  	((uint32_t) 0x00400000)			/*!< Bit 6 */
#define TSC_THRHD5_DELTA5_7                  	((uint32_t) 0x00800000)			/*!< Bit 7 */

/******************  Bit definition for TSC_THRHD6 register  ******************/
#define TSC_THRHD6_BASE6_Pos					(0U)
#define TSC_THRHD6_BASE6_Msk					(0x7FFUL << TSC_THRHD6_BASE6_Pos)
#define TSC_THRHD6_BASE6						TSC_THRHD6_BASE6_Msk			/*!< BASE6[10:0] (value of base) */
#define TSC_THRHD6_BASE6_0						((uint32_t) 0x00000001)			/*!< Bit 0 */
#define TSC_THRHD6_BASE6_1                      ((uint32_t) 0x00000002)			/*!< Bit 1 */
#define TSC_THRHD6_BASE6_2                      ((uint32_t) 0x00000004)			/*!< Bit 2 */
#define TSC_THRHD6_BASE6_3                      ((uint32_t) 0x00000008)			/*!< Bit 3 */
#define TSC_THRHD6_BASE6_4                      ((uint32_t) 0x00000010)			/*!< Bit 4 */
#define TSC_THRHD6_BASE6_5                      ((uint32_t) 0x00000020)			/*!< Bit 5 */
#define TSC_THRHD6_BASE6_6                      ((uint32_t) 0x00000040)			/*!< Bit 6 */
#define TSC_THRHD6_BASE6_7                      ((uint32_t) 0x00000080)			/*!< Bit 7 */
#define TSC_THRHD6_BASE6_8                      ((uint32_t) 0x00000100)			/*!< Bit 8 */
#define TSC_THRHD6_BASE6_9                      ((uint32_t) 0x00000200)			/*!< Bit 9 */
#define TSC_THRHD6_BASE6_10                     ((uint32_t) 0x00000400)			/*!< Bit 10 */

#define TSC_THRHD6_DELTA6_Pos					(16U)
#define TSC_THRHD6_DELTA6_Msk					(0xFFUL << TSC_THRHD6_DELTA6_Pos)
#define TSC_THRHD6_DELTA6						TSC_THRHD6_DELTA6_Msk			/*!< DELTA6[7:0] (value of delta) */
#define TSC_THRHD6_DELTA6_0                  	((uint32_t) 0x00010000)			/*!< Bit 0 */
#define TSC_THRHD6_DELTA6_1                  	((uint32_t) 0x00020000)			/*!< Bit 1 */
#define TSC_THRHD6_DELTA6_2                  	((uint32_t) 0x00040000)			/*!< Bit 2 */
#define TSC_THRHD6_DELTA6_3                  	((uint32_t) 0x00080000)			/*!< Bit 3 */
#define TSC_THRHD6_DELTA6_4                  	((uint32_t) 0x00100000)			/*!< Bit 4 */
#define TSC_THRHD6_DELTA6_5                  	((uint32_t) 0x00200000)			/*!< Bit 5 */
#define TSC_THRHD6_DELTA6_6                  	((uint32_t) 0x00400000)			/*!< Bit 6 */
#define TSC_THRHD6_DELTA6_7                  	((uint32_t) 0x00800000)			/*!< Bit 7 */

/******************  Bit definition for TSC_THRHD7 register  ******************/
#define TSC_THRHD7_BASE7_Pos					(0U)
#define TSC_THRHD7_BASE7_Msk					(0x7FFUL << TSC_THRHD7_BASE7_Pos)
#define TSC_THRHD7_BASE7						TSC_THRHD7_BASE7_Msk			/*!< BASE7[10:0] (value of base) */
#define TSC_THRHD7_BASE7_0						((uint32_t) 0x00000001)			/*!< Bit 0 */
#define TSC_THRHD7_BASE7_1                      ((uint32_t) 0x00000002)			/*!< Bit 1 */
#define TSC_THRHD7_BASE7_2                      ((uint32_t) 0x00000004)			/*!< Bit 2 */
#define TSC_THRHD7_BASE7_3                      ((uint32_t) 0x00000008)			/*!< Bit 3 */
#define TSC_THRHD7_BASE7_4                      ((uint32_t) 0x00000010)			/*!< Bit 4 */
#define TSC_THRHD7_BASE7_5                      ((uint32_t) 0x00000020)			/*!< Bit 5 */
#define TSC_THRHD7_BASE7_6                      ((uint32_t) 0x00000040)			/*!< Bit 6 */
#define TSC_THRHD7_BASE7_7                      ((uint32_t) 0x00000080)			/*!< Bit 7 */
#define TSC_THRHD7_BASE7_8                      ((uint32_t) 0x00000100)			/*!< Bit 8 */
#define TSC_THRHD7_BASE7_9                      ((uint32_t) 0x00000200)			/*!< Bit 9 */
#define TSC_THRHD7_BASE7_10                     ((uint32_t) 0x00000400)			/*!< Bit 10 */

#define TSC_THRHD7_DELTA7_Pos					(16U)
#define TSC_THRHD7_DELTA7_Msk					(0xFFUL << TSC_THRHD7_DELTA7_Pos)
#define TSC_THRHD7_DELTA7						TSC_THRHD7_DELTA7_Msk			/*!< DELTA7[7:0] (value of delta) */
#define TSC_THRHD7_DELTA7_0                  	((uint32_t) 0x00010000)			/*!< Bit 0 */
#define TSC_THRHD7_DELTA7_1                  	((uint32_t) 0x00020000)			/*!< Bit 1 */
#define TSC_THRHD7_DELTA7_2                  	((uint32_t) 0x00040000)			/*!< Bit 2 */
#define TSC_THRHD7_DELTA7_3                  	((uint32_t) 0x00080000)			/*!< Bit 3 */
#define TSC_THRHD7_DELTA7_4                  	((uint32_t) 0x00100000)			/*!< Bit 4 */
#define TSC_THRHD7_DELTA7_5                  	((uint32_t) 0x00200000)			/*!< Bit 5 */
#define TSC_THRHD7_DELTA7_6                  	((uint32_t) 0x00400000)			/*!< Bit 6 */
#define TSC_THRHD7_DELTA7_7                  	((uint32_t) 0x00800000)			/*!< Bit 7 */

/******************  Bit definition for TSC_THRHD8 register  ******************/
#define TSC_THRHD8_BASE8_Pos					(0U)
#define TSC_THRHD8_BASE8_Msk					(0x7FFUL << TSC_THRHD8_BASE8_Pos)
#define TSC_THRHD8_BASE8						TSC_THRHD8_BASE8_Msk			/*!< BASE8[10:0] (value of base) */
#define TSC_THRHD8_BASE8_0						((uint32_t) 0x00000001)			/*!< Bit 0 */
#define TSC_THRHD8_BASE8_1                      ((uint32_t) 0x00000002)			/*!< Bit 1 */
#define TSC_THRHD8_BASE8_2                      ((uint32_t) 0x00000004)			/*!< Bit 2 */
#define TSC_THRHD8_BASE8_3                      ((uint32_t) 0x00000008)			/*!< Bit 3 */
#define TSC_THRHD8_BASE8_4                      ((uint32_t) 0x00000010)			/*!< Bit 4 */
#define TSC_THRHD8_BASE8_5                      ((uint32_t) 0x00000020)			/*!< Bit 5 */
#define TSC_THRHD8_BASE8_6                      ((uint32_t) 0x00000040)			/*!< Bit 6 */
#define TSC_THRHD8_BASE8_7                      ((uint32_t) 0x00000080)			/*!< Bit 7 */
#define TSC_THRHD8_BASE8_8                      ((uint32_t) 0x00000100)			/*!< Bit 8 */
#define TSC_THRHD8_BASE8_9                      ((uint32_t) 0x00000200)			/*!< Bit 9 */
#define TSC_THRHD8_BASE8_10                     ((uint32_t) 0x00000400)			/*!< Bit 10 */

#define TSC_THRHD8_DELTA8_Pos					(16U)
#define TSC_THRHD8_DELTA8_Msk					(0xFFUL << TSC_THRHD8_DELTA8_Pos)
#define TSC_THRHD8_DELTA8						TSC_THRHD8_DELTA8_Msk			/*!< DELTA8[7:0] (value of delta) */
#define TSC_THRHD8_DELTA8_0                  	((uint32_t) 0x00010000)			/*!< Bit 0 */
#define TSC_THRHD8_DELTA8_1                  	((uint32_t) 0x00020000)			/*!< Bit 1 */
#define TSC_THRHD8_DELTA8_2                  	((uint32_t) 0x00040000)			/*!< Bit 2 */
#define TSC_THRHD8_DELTA8_3                  	((uint32_t) 0x00080000)			/*!< Bit 3 */
#define TSC_THRHD8_DELTA8_4                  	((uint32_t) 0x00100000)			/*!< Bit 4 */
#define TSC_THRHD8_DELTA8_5                  	((uint32_t) 0x00200000)			/*!< Bit 5 */
#define TSC_THRHD8_DELTA8_6                  	((uint32_t) 0x00400000)			/*!< Bit 6 */
#define TSC_THRHD8_DELTA8_7                  	((uint32_t) 0x00800000)			/*!< Bit 7 */

/******************  Bit definition for TSC_THRHD9 register  ******************/
#define TSC_THRHD9_BASE9_Pos					(0U)
#define TSC_THRHD9_BASE9_Msk					(0x7FFUL << TSC_THRHD9_BASE9_Pos)
#define TSC_THRHD9_BASE9						TSC_THRHD9_BASE9_Msk			/*!< BASE9[10:0] (value of base) */
#define TSC_THRHD9_BASE9_0						((uint32_t) 0x00000001)			/*!< Bit 0 */
#define TSC_THRHD9_BASE9_1                      ((uint32_t) 0x00000002)			/*!< Bit 1 */
#define TSC_THRHD9_BASE9_2                      ((uint32_t) 0x00000004)			/*!< Bit 2 */
#define TSC_THRHD9_BASE9_3                      ((uint32_t) 0x00000008)			/*!< Bit 3 */
#define TSC_THRHD9_BASE9_4                      ((uint32_t) 0x00000010)			/*!< Bit 4 */
#define TSC_THRHD9_BASE9_5                      ((uint32_t) 0x00000020)			/*!< Bit 5 */
#define TSC_THRHD9_BASE9_6                      ((uint32_t) 0x00000040)			/*!< Bit 6 */
#define TSC_THRHD9_BASE9_7                      ((uint32_t) 0x00000080)			/*!< Bit 7 */
#define TSC_THRHD9_BASE9_8                      ((uint32_t) 0x00000100)			/*!< Bit 8 */
#define TSC_THRHD9_BASE9_9                      ((uint32_t) 0x00000200)			/*!< Bit 9 */
#define TSC_THRHD9_BASE9_10                     ((uint32_t) 0x00000400)			/*!< Bit 10 */

#define TSC_THRHD9_DELTA9_Pos					(16U)
#define TSC_THRHD9_DELTA9_Msk					(0xFFUL << TSC_THRHD9_DELTA9_Pos)
#define TSC_THRHD9_DELTA9						TSC_THRHD9_DELTA9_Msk			/*!< DELTA9[7:0] (value of delta) */
#define TSC_THRHD9_DELTA9_0                  	((uint32_t) 0x00010000)			/*!< Bit 0 */
#define TSC_THRHD9_DELTA9_1                  	((uint32_t) 0x00020000)			/*!< Bit 1 */
#define TSC_THRHD9_DELTA9_2                  	((uint32_t) 0x00040000)			/*!< Bit 2 */
#define TSC_THRHD9_DELTA9_3                  	((uint32_t) 0x00080000)			/*!< Bit 3 */
#define TSC_THRHD9_DELTA9_4                  	((uint32_t) 0x00100000)			/*!< Bit 4 */
#define TSC_THRHD9_DELTA9_5                  	((uint32_t) 0x00200000)			/*!< Bit 5 */
#define TSC_THRHD9_DELTA9_6                  	((uint32_t) 0x00400000)			/*!< Bit 6 */
#define TSC_THRHD9_DELTA9_7                  	((uint32_t) 0x00800000)			/*!< Bit 7 */

/*****************  Bit definition for TSC_THRHD10 register  ******************/
#define TSC_THRHD10_BASE10_Pos					(0U)
#define TSC_THRHD10_BASE10_Msk					(0x7FFUL << TSC_THRHD10_BASE10_Pos)
#define TSC_THRHD10_BASE10						TSC_THRHD10_BASE10_Msk			/*!< BASE10[10:0] (value of base) */
#define TSC_THRHD10_BASE10_0					((uint32_t) 0x00000001)			/*!< Bit 0 */
#define TSC_THRHD10_BASE10_1                    ((uint32_t) 0x00000002)			/*!< Bit 1 */
#define TSC_THRHD10_BASE10_2                    ((uint32_t) 0x00000004)			/*!< Bit 2 */
#define TSC_THRHD10_BASE10_3                    ((uint32_t) 0x00000008)			/*!< Bit 3 */
#define TSC_THRHD10_BASE10_4                    ((uint32_t) 0x00000010)			/*!< Bit 4 */
#define TSC_THRHD10_BASE10_5                    ((uint32_t) 0x00000020)			/*!< Bit 5 */
#define TSC_THRHD10_BASE10_6                    ((uint32_t) 0x00000040)			/*!< Bit 6 */
#define TSC_THRHD10_BASE10_7                    ((uint32_t) 0x00000080)			/*!< Bit 7 */
#define TSC_THRHD10_BASE10_8                    ((uint32_t) 0x00000100)			/*!< Bit 8 */
#define TSC_THRHD10_BASE10_9                    ((uint32_t) 0x00000200)			/*!< Bit 9 */
#define TSC_THRHD10_BASE10_10                   ((uint32_t) 0x00000400)			/*!< Bit 10 */

#define TSC_THRHD10_DELTA10_Pos					(16U)
#define TSC_THRHD10_DELTA10_Msk					(0xFFUL << TSC_THRHD10_DELTA10_Pos)
#define TSC_THRHD10_DELTA10						TSC_THRHD10_DELTA10_Msk			/*!< DELTA10[7:0] (value of delta) */
#define TSC_THRHD10_DELTA10_0                  	((uint32_t) 0x00010000)			/*!< Bit 0 */
#define TSC_THRHD10_DELTA10_1                  	((uint32_t) 0x00020000)			/*!< Bit 1 */
#define TSC_THRHD10_DELTA10_2                  	((uint32_t) 0x00040000)			/*!< Bit 2 */
#define TSC_THRHD10_DELTA10_3                  	((uint32_t) 0x00080000)			/*!< Bit 3 */
#define TSC_THRHD10_DELTA10_4                  	((uint32_t) 0x00100000)			/*!< Bit 4 */
#define TSC_THRHD10_DELTA10_5                  	((uint32_t) 0x00200000)			/*!< Bit 5 */
#define TSC_THRHD10_DELTA10_6                  	((uint32_t) 0x00400000)			/*!< Bit 6 */
#define TSC_THRHD10_DELTA10_7                  	((uint32_t) 0x00800000)			/*!< Bit 7 */

/*****************  Bit definition for TSC_THRHD11 register  ******************/
#define TSC_THRHD11_BASE11_Pos					(0U)
#define TSC_THRHD11_BASE11_Msk					(0x7FFUL << TSC_THRHD11_BASE11_Pos)
#define TSC_THRHD11_BASE11						TSC_THRHD11_BASE11_Msk			/*!< BASE11[10:0] (value of base) */
#define TSC_THRHD11_BASE11_0					((uint32_t) 0x00000001)			/*!< Bit 0 */
#define TSC_THRHD11_BASE11_1                    ((uint32_t) 0x00000002)			/*!< Bit 1 */
#define TSC_THRHD11_BASE11_2                    ((uint32_t) 0x00000004)			/*!< Bit 2 */
#define TSC_THRHD11_BASE11_3                    ((uint32_t) 0x00000008)			/*!< Bit 3 */
#define TSC_THRHD11_BASE11_4                    ((uint32_t) 0x00000010)			/*!< Bit 4 */
#define TSC_THRHD11_BASE11_5                    ((uint32_t) 0x00000020)			/*!< Bit 5 */
#define TSC_THRHD11_BASE11_6                    ((uint32_t) 0x00000040)			/*!< Bit 6 */
#define TSC_THRHD11_BASE11_7                    ((uint32_t) 0x00000080)			/*!< Bit 7 */
#define TSC_THRHD11_BASE11_8                    ((uint32_t) 0x00000100)			/*!< Bit 8 */
#define TSC_THRHD11_BASE11_9                    ((uint32_t) 0x00000200)			/*!< Bit 9 */
#define TSC_THRHD11_BASE11_10                   ((uint32_t) 0x00000400)			/*!< Bit 10 */

#define TSC_THRHD11_DELTA11_Pos					(16U)
#define TSC_THRHD11_DELTA11_Msk					(0xFFUL << TSC_THRHD11_DELTA11_Pos)
#define TSC_THRHD11_DELTA11						TSC_THRHD11_DELTA11_Msk			/*!< DELTA11[7:0] (value of delta) */
#define TSC_THRHD11_DELTA11_0                  	((uint32_t) 0x00010000)			/*!< Bit 0 */
#define TSC_THRHD11_DELTA11_1                  	((uint32_t) 0x00020000)			/*!< Bit 1 */
#define TSC_THRHD11_DELTA11_2                  	((uint32_t) 0x00040000)			/*!< Bit 2 */
#define TSC_THRHD11_DELTA11_3                  	((uint32_t) 0x00080000)			/*!< Bit 3 */
#define TSC_THRHD11_DELTA11_4                  	((uint32_t) 0x00100000)			/*!< Bit 4 */
#define TSC_THRHD11_DELTA11_5                  	((uint32_t) 0x00200000)			/*!< Bit 5 */
#define TSC_THRHD11_DELTA11_6                  	((uint32_t) 0x00400000)			/*!< Bit 6 */
#define TSC_THRHD11_DELTA11_7                  	((uint32_t) 0x00800000)			/*!< Bit 7 */

/*****************  Bit definition for TSC_THRHD12 register  ******************/
#define TSC_THRHD12_BASE12_Pos					(0U)
#define TSC_THRHD12_BASE12_Msk					(0x7FFUL << TSC_THRHD12_BASE12_Pos)
#define TSC_THRHD12_BASE12						TSC_THRHD12_BASE12_Msk			/*!< BASE12[10:0] (value of base) */
#define TSC_THRHD12_BASE12_0					((uint32_t) 0x00000001)			/*!< Bit 0 */
#define TSC_THRHD12_BASE12_1                    ((uint32_t) 0x00000002)			/*!< Bit 1 */
#define TSC_THRHD12_BASE12_2                    ((uint32_t) 0x00000004)			/*!< Bit 2 */
#define TSC_THRHD12_BASE12_3                    ((uint32_t) 0x00000008)			/*!< Bit 3 */
#define TSC_THRHD12_BASE12_4                    ((uint32_t) 0x00000010)			/*!< Bit 4 */
#define TSC_THRHD12_BASE12_5                    ((uint32_t) 0x00000020)			/*!< Bit 5 */
#define TSC_THRHD12_BASE12_6                    ((uint32_t) 0x00000040)			/*!< Bit 6 */
#define TSC_THRHD12_BASE12_7                    ((uint32_t) 0x00000080)			/*!< Bit 7 */
#define TSC_THRHD12_BASE12_8                    ((uint32_t) 0x00000100)			/*!< Bit 8 */
#define TSC_THRHD12_BASE12_9                    ((uint32_t) 0x00000200)			/*!< Bit 9 */
#define TSC_THRHD12_BASE12_10                   ((uint32_t) 0x00000400)			/*!< Bit 10 */

#define TSC_THRHD12_DELTA12_Pos					(16U)
#define TSC_THRHD12_DELTA12_Msk					(0xFFUL << TSC_THRHD12_DELTA12_Pos)
#define TSC_THRHD12_DELTA12						TSC_THRHD12_DELTA12_Msk			/*!< DELTA12[7:0] (value of delta) */
#define TSC_THRHD12_DELTA12_0                  	((uint32_t) 0x00010000)			/*!< Bit 0 */
#define TSC_THRHD12_DELTA12_1                  	((uint32_t) 0x00020000)			/*!< Bit 1 */
#define TSC_THRHD12_DELTA12_2                  	((uint32_t) 0x00040000)			/*!< Bit 2 */
#define TSC_THRHD12_DELTA12_3                  	((uint32_t) 0x00080000)			/*!< Bit 3 */
#define TSC_THRHD12_DELTA12_4                  	((uint32_t) 0x00100000)			/*!< Bit 4 */
#define TSC_THRHD12_DELTA12_5                  	((uint32_t) 0x00200000)			/*!< Bit 5 */
#define TSC_THRHD12_DELTA12_6                  	((uint32_t) 0x00400000)			/*!< Bit 6 */
#define TSC_THRHD12_DELTA12_7                  	((uint32_t) 0x00800000)			/*!< Bit 7 */

/*****************  Bit definition for TSC_THRHD13 register  ******************/
#define TSC_THRHD13_BASE13_Pos					(0U)
#define TSC_THRHD13_BASE13_Msk					(0x7FFUL << TSC_THRHD13_BASE13_Pos)
#define TSC_THRHD13_BASE13						TSC_THRHD13_BASE13_Msk			/*!< BASE13[10:0] (value of base) */
#define TSC_THRHD13_BASE13_0					((uint32_t) 0x00000001)			/*!< Bit 0 */
#define TSC_THRHD13_BASE13_1                    ((uint32_t) 0x00000002)			/*!< Bit 1 */
#define TSC_THRHD13_BASE13_2                    ((uint32_t) 0x00000004)			/*!< Bit 2 */
#define TSC_THRHD13_BASE13_3                    ((uint32_t) 0x00000008)			/*!< Bit 3 */
#define TSC_THRHD13_BASE13_4                    ((uint32_t) 0x00000010)			/*!< Bit 4 */
#define TSC_THRHD13_BASE13_5                    ((uint32_t) 0x00000020)			/*!< Bit 5 */
#define TSC_THRHD13_BASE13_6                    ((uint32_t) 0x00000040)			/*!< Bit 6 */
#define TSC_THRHD13_BASE13_7                    ((uint32_t) 0x00000080)			/*!< Bit 7 */
#define TSC_THRHD13_BASE13_8                    ((uint32_t) 0x00000100)			/*!< Bit 8 */
#define TSC_THRHD13_BASE13_9                    ((uint32_t) 0x00000200)			/*!< Bit 9 */
#define TSC_THRHD13_BASE13_10                   ((uint32_t) 0x00000400)			/*!< Bit 10 */

#define TSC_THRHD13_DELTA13_Pos					(16U)
#define TSC_THRHD13_DELTA13_Msk					(0xFFUL << TSC_THRHD13_DELTA13_Pos)
#define TSC_THRHD13_DELTA13						TSC_THRHD13_DELTA13_Msk			/*!< DELTA13[7:0] (value of delta) */
#define TSC_THRHD13_DELTA13_0                  	((uint32_t) 0x00010000)			/*!< Bit 0 */
#define TSC_THRHD13_DELTA13_1                  	((uint32_t) 0x00020000)			/*!< Bit 1 */
#define TSC_THRHD13_DELTA13_2                  	((uint32_t) 0x00040000)			/*!< Bit 2 */
#define TSC_THRHD13_DELTA13_3                  	((uint32_t) 0x00080000)			/*!< Bit 3 */
#define TSC_THRHD13_DELTA13_4                  	((uint32_t) 0x00100000)			/*!< Bit 4 */
#define TSC_THRHD13_DELTA13_5                  	((uint32_t) 0x00200000)			/*!< Bit 5 */
#define TSC_THRHD13_DELTA13_6                  	((uint32_t) 0x00400000)			/*!< Bit 6 */
#define TSC_THRHD13_DELTA13_7                  	((uint32_t) 0x00800000)			/*!< Bit 7 */

/*****************  Bit definition for TSC_THRHD14 register  ******************/
#define TSC_THRHD14_BASE14_Pos					(0U)
#define TSC_THRHD14_BASE14_Msk					(0x7FFUL << TSC_THRHD14_BASE14_Pos)
#define TSC_THRHD14_BASE14						TSC_THRHD14_BASE14_Msk			/*!< BASE14[10:0] (value of base) */
#define TSC_THRHD14_BASE14_0					((uint32_t) 0x00000001)			/*!< Bit 0 */
#define TSC_THRHD14_BASE14_1                    ((uint32_t) 0x00000002)			/*!< Bit 1 */
#define TSC_THRHD14_BASE14_2                    ((uint32_t) 0x00000004)			/*!< Bit 2 */
#define TSC_THRHD14_BASE14_3                    ((uint32_t) 0x00000008)			/*!< Bit 3 */
#define TSC_THRHD14_BASE14_4                    ((uint32_t) 0x00000010)			/*!< Bit 4 */
#define TSC_THRHD14_BASE14_5                    ((uint32_t) 0x00000020)			/*!< Bit 5 */
#define TSC_THRHD14_BASE14_6                    ((uint32_t) 0x00000040)			/*!< Bit 6 */
#define TSC_THRHD14_BASE14_7                    ((uint32_t) 0x00000080)			/*!< Bit 7 */
#define TSC_THRHD14_BASE14_8                    ((uint32_t) 0x00000100)			/*!< Bit 8 */
#define TSC_THRHD14_BASE14_9                    ((uint32_t) 0x00000200)			/*!< Bit 9 */
#define TSC_THRHD14_BASE14_10                   ((uint32_t) 0x00000400)			/*!< Bit 10 */

#define TSC_THRHD14_DELTA14_Pos					(16U)
#define TSC_THRHD14_DELTA14_Msk					(0xFFUL << TSC_THRHD14_DELTA14_Pos)
#define TSC_THRHD14_DELTA14						TSC_THRHD14_DELTA14_Msk			/*!< DELTA14[7:0] (value of delta) */
#define TSC_THRHD14_DELTA14_0                  	((uint32_t) 0x00010000)			/*!< Bit 0 */
#define TSC_THRHD14_DELTA14_1                  	((uint32_t) 0x00020000)			/*!< Bit 1 */
#define TSC_THRHD14_DELTA14_2                  	((uint32_t) 0x00040000)			/*!< Bit 2 */
#define TSC_THRHD14_DELTA14_3                  	((uint32_t) 0x00080000)			/*!< Bit 3 */
#define TSC_THRHD14_DELTA14_4                  	((uint32_t) 0x00100000)			/*!< Bit 4 */
#define TSC_THRHD14_DELTA14_5                  	((uint32_t) 0x00200000)			/*!< Bit 5 */
#define TSC_THRHD14_DELTA14_6                  	((uint32_t) 0x00400000)			/*!< Bit 6 */
#define TSC_THRHD14_DELTA14_7                  	((uint32_t) 0x00800000)			/*!< Bit 7 */

/*****************  Bit definition for TSC_THRHD15 register  ******************/
#define TSC_THRHD15_BASE15_Pos					(0U)
#define TSC_THRHD15_BASE15_Msk					(0x7FFUL << TSC_THRHD15_BASE15_Pos)
#define TSC_THRHD15_BASE15						TSC_THRHD15_BASE15_Msk			/*!< BASE15[10:0] (value of base) */
#define TSC_THRHD15_BASE15_0					((uint32_t) 0x00000001)			/*!< Bit 0 */
#define TSC_THRHD15_BASE15_1                    ((uint32_t) 0x00000002)			/*!< Bit 1 */
#define TSC_THRHD15_BASE15_2                    ((uint32_t) 0x00000004)			/*!< Bit 2 */
#define TSC_THRHD15_BASE15_3                    ((uint32_t) 0x00000008)			/*!< Bit 3 */
#define TSC_THRHD15_BASE15_4                    ((uint32_t) 0x00000010)			/*!< Bit 4 */
#define TSC_THRHD15_BASE15_5                    ((uint32_t) 0x00000020)			/*!< Bit 5 */
#define TSC_THRHD15_BASE15_6                    ((uint32_t) 0x00000040)			/*!< Bit 6 */
#define TSC_THRHD15_BASE15_7                    ((uint32_t) 0x00000080)			/*!< Bit 7 */
#define TSC_THRHD15_BASE15_8                    ((uint32_t) 0x00000100)			/*!< Bit 8 */
#define TSC_THRHD15_BASE15_9                    ((uint32_t) 0x00000200)			/*!< Bit 9 */
#define TSC_THRHD15_BASE15_10                   ((uint32_t) 0x00000400)			/*!< Bit 10 */

#define TSC_THRHD15_DELTA15_Pos					(16U)
#define TSC_THRHD15_DELTA15_Msk					(0xFFUL << TSC_THRHD15_DELTA15_Pos)
#define TSC_THRHD15_DELTA15						TSC_THRHD15_DELTA15_Msk			/*!< DELTA15[7:0] (value of delta) */
#define TSC_THRHD15_DELTA15_0                  	((uint32_t) 0x00010000)			/*!< Bit 0 */
#define TSC_THRHD15_DELTA15_1                  	((uint32_t) 0x00020000)			/*!< Bit 1 */
#define TSC_THRHD15_DELTA15_2                  	((uint32_t) 0x00040000)			/*!< Bit 2 */
#define TSC_THRHD15_DELTA15_3                  	((uint32_t) 0x00080000)			/*!< Bit 3 */
#define TSC_THRHD15_DELTA15_4                  	((uint32_t) 0x00100000)			/*!< Bit 4 */
#define TSC_THRHD15_DELTA15_5                  	((uint32_t) 0x00200000)			/*!< Bit 5 */
#define TSC_THRHD15_DELTA15_6                  	((uint32_t) 0x00400000)			/*!< Bit 6 */
#define TSC_THRHD15_DELTA15_7                  	((uint32_t) 0x00800000)			/*!< Bit 7 */

/*****************  Bit definition for TSC_THRHD16 register  ******************/
#define TSC_THRHD16_BASE16_Pos					(0U)
#define TSC_THRHD16_BASE16_Msk					(0x7FFUL << TSC_THRHD16_BASE16_Pos)
#define TSC_THRHD16_BASE16						TSC_THRHD16_BASE16_Msk			/*!< BASE16[10:0] (value of base) */
#define TSC_THRHD16_BASE16_0					((uint32_t) 0x00000001)			/*!< Bit 0 */
#define TSC_THRHD16_BASE16_1                    ((uint32_t) 0x00000002)			/*!< Bit 1 */
#define TSC_THRHD16_BASE16_2                    ((uint32_t) 0x00000004)			/*!< Bit 2 */
#define TSC_THRHD16_BASE16_3                    ((uint32_t) 0x00000008)			/*!< Bit 3 */
#define TSC_THRHD16_BASE16_4                    ((uint32_t) 0x00000010)			/*!< Bit 4 */
#define TSC_THRHD16_BASE16_5                    ((uint32_t) 0x00000020)			/*!< Bit 5 */
#define TSC_THRHD16_BASE16_6                    ((uint32_t) 0x00000040)			/*!< Bit 6 */
#define TSC_THRHD16_BASE16_7                    ((uint32_t) 0x00000080)			/*!< Bit 7 */
#define TSC_THRHD16_BASE16_8                    ((uint32_t) 0x00000100)			/*!< Bit 8 */
#define TSC_THRHD16_BASE16_9                    ((uint32_t) 0x00000200)			/*!< Bit 9 */
#define TSC_THRHD16_BASE16_10                   ((uint32_t) 0x00000400)			/*!< Bit 10 */

#define TSC_THRHD16_DELTA16_Pos					(16U)
#define TSC_THRHD16_DELTA16_Msk					(0xFFUL << TSC_THRHD16_DELTA16_Pos)
#define TSC_THRHD16_DELTA16						TSC_THRHD16_DELTA16_Msk			/*!< DELTA16[7:0] (value of delta) */
#define TSC_THRHD16_DELTA16_0                  	((uint32_t) 0x00010000)			/*!< Bit 0 */
#define TSC_THRHD16_DELTA16_1                  	((uint32_t) 0x00020000)			/*!< Bit 1 */
#define TSC_THRHD16_DELTA16_2                  	((uint32_t) 0x00040000)			/*!< Bit 2 */
#define TSC_THRHD16_DELTA16_3                  	((uint32_t) 0x00080000)			/*!< Bit 3 */
#define TSC_THRHD16_DELTA16_4                  	((uint32_t) 0x00100000)			/*!< Bit 4 */
#define TSC_THRHD16_DELTA16_5                  	((uint32_t) 0x00200000)			/*!< Bit 5 */
#define TSC_THRHD16_DELTA16_6                  	((uint32_t) 0x00400000)			/*!< Bit 6 */
#define TSC_THRHD16_DELTA16_7                  	((uint32_t) 0x00800000)			/*!< Bit 7 */

/*****************  Bit definition for TSC_THRHD17 register  ******************/
#define TSC_THRHD17_BASE17_Pos					(0U)
#define TSC_THRHD17_BASE17_Msk					(0x7FFUL << TSC_THRHD17_BASE17_Pos)
#define TSC_THRHD17_BASE17						TSC_THRHD17_BASE17_Msk			/*!< BASE17[10:0] (value of base) */
#define TSC_THRHD17_BASE17_0					((uint32_t) 0x00000001)			/*!< Bit 0 */
#define TSC_THRHD17_BASE17_1                    ((uint32_t) 0x00000002)			/*!< Bit 1 */
#define TSC_THRHD17_BASE17_2                    ((uint32_t) 0x00000004)			/*!< Bit 2 */
#define TSC_THRHD17_BASE17_3                    ((uint32_t) 0x00000008)			/*!< Bit 3 */
#define TSC_THRHD17_BASE17_4                    ((uint32_t) 0x00000010)			/*!< Bit 4 */
#define TSC_THRHD17_BASE17_5                    ((uint32_t) 0x00000020)			/*!< Bit 5 */
#define TSC_THRHD17_BASE17_6                    ((uint32_t) 0x00000040)			/*!< Bit 6 */
#define TSC_THRHD17_BASE17_7                    ((uint32_t) 0x00000080)			/*!< Bit 7 */
#define TSC_THRHD17_BASE17_8                    ((uint32_t) 0x00000100)			/*!< Bit 8 */
#define TSC_THRHD17_BASE17_9                    ((uint32_t) 0x00000200)			/*!< Bit 9 */
#define TSC_THRHD17_BASE17_10                   ((uint32_t) 0x00000400)			/*!< Bit 10 */

#define TSC_THRHD17_DELTA17_Pos					(16U)
#define TSC_THRHD17_DELTA17_Msk					(0xFFUL << TSC_THRHD17_DELTA17_Pos)
#define TSC_THRHD17_DELTA17						TSC_THRHD17_DELTA17_Msk			/*!< DELTA17[7:0] (value of delta) */
#define TSC_THRHD17_DELTA17_0                  	((uint32_t) 0x00010000)			/*!< Bit 0 */
#define TSC_THRHD17_DELTA17_1                  	((uint32_t) 0x00020000)			/*!< Bit 1 */
#define TSC_THRHD17_DELTA17_2                  	((uint32_t) 0x00040000)			/*!< Bit 2 */
#define TSC_THRHD17_DELTA17_3                  	((uint32_t) 0x00080000)			/*!< Bit 3 */
#define TSC_THRHD17_DELTA17_4                  	((uint32_t) 0x00100000)			/*!< Bit 4 */
#define TSC_THRHD17_DELTA17_5                  	((uint32_t) 0x00200000)			/*!< Bit 5 */
#define TSC_THRHD17_DELTA17_6                  	((uint32_t) 0x00400000)			/*!< Bit 6 */
#define TSC_THRHD17_DELTA17_7                  	((uint32_t) 0x00800000)			/*!< Bit 7 */

/*****************  Bit definition for TSC_THRHD18 register  ******************/
#define TSC_THRHD18_BASE18_Pos					(0U)
#define TSC_THRHD18_BASE18_Msk					(0x7FFUL << TSC_THRHD18_BASE18_Pos)
#define TSC_THRHD18_BASE18						TSC_THRHD18_BASE18_Msk			/*!< BASE18[10:0] (value of base) */
#define TSC_THRHD18_BASE18_0					((uint32_t) 0x00000001)			/*!< Bit 0 */
#define TSC_THRHD18_BASE18_1                    ((uint32_t) 0x00000002)			/*!< Bit 1 */
#define TSC_THRHD18_BASE18_2                    ((uint32_t) 0x00000004)			/*!< Bit 2 */
#define TSC_THRHD18_BASE18_3                    ((uint32_t) 0x00000008)			/*!< Bit 3 */
#define TSC_THRHD18_BASE18_4                    ((uint32_t) 0x00000010)			/*!< Bit 4 */
#define TSC_THRHD18_BASE18_5                    ((uint32_t) 0x00000020)			/*!< Bit 5 */
#define TSC_THRHD18_BASE18_6                    ((uint32_t) 0x00000040)			/*!< Bit 6 */
#define TSC_THRHD18_BASE18_7                    ((uint32_t) 0x00000080)			/*!< Bit 7 */
#define TSC_THRHD18_BASE18_8                    ((uint32_t) 0x00000100)			/*!< Bit 8 */
#define TSC_THRHD18_BASE18_9                    ((uint32_t) 0x00000200)			/*!< Bit 9 */
#define TSC_THRHD18_BASE18_10                   ((uint32_t) 0x00000400)			/*!< Bit 10 */

#define TSC_THRHD18_DELTA18_Pos					(16U)
#define TSC_THRHD18_DELTA18_Msk					(0xFFUL << TSC_THRHD18_DELTA18_Pos)
#define TSC_THRHD18_DELTA18						TSC_THRHD18_DELTA18_Msk			/*!< DELTA18[7:0] (value of delta) */
#define TSC_THRHD18_DELTA18_0                  	((uint32_t) 0x00010000)			/*!< Bit 0 */
#define TSC_THRHD18_DELTA18_1                  	((uint32_t) 0x00020000)			/*!< Bit 1 */
#define TSC_THRHD18_DELTA18_2                  	((uint32_t) 0x00040000)			/*!< Bit 2 */
#define TSC_THRHD18_DELTA18_3                  	((uint32_t) 0x00080000)			/*!< Bit 3 */
#define TSC_THRHD18_DELTA18_4                  	((uint32_t) 0x00100000)			/*!< Bit 4 */
#define TSC_THRHD18_DELTA18_5                  	((uint32_t) 0x00200000)			/*!< Bit 5 */
#define TSC_THRHD18_DELTA18_6                  	((uint32_t) 0x00400000)			/*!< Bit 6 */
#define TSC_THRHD18_DELTA18_7                  	((uint32_t) 0x00800000)			/*!< Bit 7 */

/*****************  Bit definition for TSC_THRHD19 register  ******************/
#define TSC_THRHD19_BASE19_Pos					(0U)
#define TSC_THRHD19_BASE19_Msk					(0x7FFUL << TSC_THRHD19_BASE19_Pos)
#define TSC_THRHD19_BASE19						TSC_THRHD19_BASE19_Msk			/*!< BASE19[10:0] (value of base) */
#define TSC_THRHD19_BASE19_0					((uint32_t) 0x00000001)			/*!< Bit 0 */
#define TSC_THRHD19_BASE19_1                    ((uint32_t) 0x00000002)			/*!< Bit 1 */
#define TSC_THRHD19_BASE19_2                    ((uint32_t) 0x00000004)			/*!< Bit 2 */
#define TSC_THRHD19_BASE19_3                    ((uint32_t) 0x00000008)			/*!< Bit 3 */
#define TSC_THRHD19_BASE19_4                    ((uint32_t) 0x00000010)			/*!< Bit 4 */
#define TSC_THRHD19_BASE19_5                    ((uint32_t) 0x00000020)			/*!< Bit 5 */
#define TSC_THRHD19_BASE19_6                    ((uint32_t) 0x00000040)			/*!< Bit 6 */
#define TSC_THRHD19_BASE19_7                    ((uint32_t) 0x00000080)			/*!< Bit 7 */
#define TSC_THRHD19_BASE19_8                    ((uint32_t) 0x00000100)			/*!< Bit 8 */
#define TSC_THRHD19_BASE19_9                    ((uint32_t) 0x00000200)			/*!< Bit 9 */
#define TSC_THRHD19_BASE19_10                   ((uint32_t) 0x00000400)			/*!< Bit 10 */

#define TSC_THRHD19_DELTA19_Pos					(16U)
#define TSC_THRHD19_DELTA19_Msk					(0xFFUL << TSC_THRHD19_DELTA19_Pos)
#define TSC_THRHD19_DELTA19						TSC_THRHD19_DELTA19_Msk			/*!< DELTA19[7:0] (value of delta) */
#define TSC_THRHD19_DELTA19_0                  	((uint32_t) 0x00010000)			/*!< Bit 0 */
#define TSC_THRHD19_DELTA19_1                  	((uint32_t) 0x00020000)			/*!< Bit 1 */
#define TSC_THRHD19_DELTA19_2                  	((uint32_t) 0x00040000)			/*!< Bit 2 */
#define TSC_THRHD19_DELTA19_3                  	((uint32_t) 0x00080000)			/*!< Bit 3 */
#define TSC_THRHD19_DELTA19_4                  	((uint32_t) 0x00100000)			/*!< Bit 4 */
#define TSC_THRHD19_DELTA19_5                  	((uint32_t) 0x00200000)			/*!< Bit 5 */
#define TSC_THRHD19_DELTA19_6                  	((uint32_t) 0x00400000)			/*!< Bit 6 */
#define TSC_THRHD19_DELTA19_7                  	((uint32_t) 0x00800000)			/*!< Bit 7 */

/*****************  Bit definition for TSC_THRHD20 register  ******************/
#define TSC_THRHD20_BASE20_Pos					(0U)
#define TSC_THRHD20_BASE20_Msk					(0x7FFUL << TSC_THRHD20_BASE20_Pos)
#define TSC_THRHD20_BASE20						TSC_THRHD20_BASE20_Msk			/*!< BASE20[10:0] (value of base) */
#define TSC_THRHD20_BASE20_0					((uint32_t) 0x00000001)			/*!< Bit 0 */
#define TSC_THRHD20_BASE20_1                    ((uint32_t) 0x00000002)			/*!< Bit 1 */
#define TSC_THRHD20_BASE20_2                    ((uint32_t) 0x00000004)			/*!< Bit 2 */
#define TSC_THRHD20_BASE20_3                    ((uint32_t) 0x00000008)			/*!< Bit 3 */
#define TSC_THRHD20_BASE20_4                    ((uint32_t) 0x00000010)			/*!< Bit 4 */
#define TSC_THRHD20_BASE20_5                    ((uint32_t) 0x00000020)			/*!< Bit 5 */
#define TSC_THRHD20_BASE20_6                    ((uint32_t) 0x00000040)			/*!< Bit 6 */
#define TSC_THRHD20_BASE20_7                    ((uint32_t) 0x00000080)			/*!< Bit 7 */
#define TSC_THRHD20_BASE20_8                    ((uint32_t) 0x00000100)			/*!< Bit 8 */
#define TSC_THRHD20_BASE20_9                    ((uint32_t) 0x00000200)			/*!< Bit 9 */
#define TSC_THRHD20_BASE20_10                   ((uint32_t) 0x00000400)			/*!< Bit 10 */

#define TSC_THRHD20_DELTA20_Pos					(16U)
#define TSC_THRHD20_DELTA20_Msk					(0xFFUL << TSC_THRHD20_DELTA20_Pos)
#define TSC_THRHD20_DELTA20						TSC_THRHD20_DELTA20_Msk			/*!< DELTA20[7:0] (value of delta) */
#define TSC_THRHD20_DELTA20_0                  	((uint32_t) 0x00010000)			/*!< Bit 0 */
#define TSC_THRHD20_DELTA20_1                  	((uint32_t) 0x00020000)			/*!< Bit 1 */
#define TSC_THRHD20_DELTA20_2                  	((uint32_t) 0x00040000)			/*!< Bit 2 */
#define TSC_THRHD20_DELTA20_3                  	((uint32_t) 0x00080000)			/*!< Bit 3 */
#define TSC_THRHD20_DELTA20_4                  	((uint32_t) 0x00100000)			/*!< Bit 4 */
#define TSC_THRHD20_DELTA20_5                  	((uint32_t) 0x00200000)			/*!< Bit 5 */
#define TSC_THRHD20_DELTA20_6                  	((uint32_t) 0x00400000)			/*!< Bit 6 */
#define TSC_THRHD20_DELTA20_7                  	((uint32_t) 0x00800000)			/*!< Bit 7 */

/*****************  Bit definition for TSC_THRHD21 register  ******************/
#define TSC_THRHD21_BASE21_Pos					(0U)
#define TSC_THRHD21_BASE21_Msk					(0x7FFUL << TSC_THRHD21_BASE21_Pos)
#define TSC_THRHD21_BASE21						TSC_THRHD21_BASE21_Msk			/*!< BASE21[10:0] (value of base) */
#define TSC_THRHD21_BASE21_0					((uint32_t) 0x00000001)			/*!< Bit 0 */
#define TSC_THRHD21_BASE21_1                    ((uint32_t) 0x00000002)			/*!< Bit 1 */
#define TSC_THRHD21_BASE21_2                    ((uint32_t) 0x00000004)			/*!< Bit 2 */
#define TSC_THRHD21_BASE21_3                    ((uint32_t) 0x00000008)			/*!< Bit 3 */
#define TSC_THRHD21_BASE21_4                    ((uint32_t) 0x00000010)			/*!< Bit 4 */
#define TSC_THRHD21_BASE21_5                    ((uint32_t) 0x00000020)			/*!< Bit 5 */
#define TSC_THRHD21_BASE21_6                    ((uint32_t) 0x00000040)			/*!< Bit 6 */
#define TSC_THRHD21_BASE21_7                    ((uint32_t) 0x00000080)			/*!< Bit 7 */
#define TSC_THRHD21_BASE21_8                    ((uint32_t) 0x00000100)			/*!< Bit 8 */
#define TSC_THRHD21_BASE21_9                    ((uint32_t) 0x00000200)			/*!< Bit 9 */
#define TSC_THRHD21_BASE21_10                   ((uint32_t) 0x00000400)			/*!< Bit 10 */

#define TSC_THRHD21_DELTA21_Pos					(16U)
#define TSC_THRHD21_DELTA21_Msk					(0xFFUL << TSC_THRHD21_DELTA21_Pos)
#define TSC_THRHD21_DELTA21						TSC_THRHD21_DELTA21_Msk			/*!< DELTA21[7:0] (value of delta) */
#define TSC_THRHD21_DELTA21_0                  	((uint32_t) 0x00010000)			/*!< Bit 0 */
#define TSC_THRHD21_DELTA21_1                  	((uint32_t) 0x00020000)			/*!< Bit 1 */
#define TSC_THRHD21_DELTA21_2                  	((uint32_t) 0x00040000)			/*!< Bit 2 */
#define TSC_THRHD21_DELTA21_3                  	((uint32_t) 0x00080000)			/*!< Bit 3 */
#define TSC_THRHD21_DELTA21_4                  	((uint32_t) 0x00100000)			/*!< Bit 4 */
#define TSC_THRHD21_DELTA21_5                  	((uint32_t) 0x00200000)			/*!< Bit 5 */
#define TSC_THRHD21_DELTA21_6                  	((uint32_t) 0x00400000)			/*!< Bit 6 */
#define TSC_THRHD21_DELTA21_7                  	((uint32_t) 0x00800000)			/*!< Bit 7 */

/*****************  Bit definition for TSC_THRHD22 register  ******************/
#define TSC_THRHD22_BASE22_Pos					(0U)
#define TSC_THRHD22_BASE22_Msk					(0x7FFUL << TSC_THRHD22_BASE22_Pos)
#define TSC_THRHD22_BASE22						TSC_THRHD22_BASE22_Msk			/*!< BASE22[10:0] (value of base) */
#define TSC_THRHD22_BASE22_0					((uint32_t) 0x00000001)			/*!< Bit 0 */
#define TSC_THRHD22_BASE22_1                    ((uint32_t) 0x00000002)			/*!< Bit 1 */
#define TSC_THRHD22_BASE22_2                    ((uint32_t) 0x00000004)			/*!< Bit 2 */
#define TSC_THRHD22_BASE22_3                    ((uint32_t) 0x00000008)			/*!< Bit 3 */
#define TSC_THRHD22_BASE22_4                    ((uint32_t) 0x00000010)			/*!< Bit 4 */
#define TSC_THRHD22_BASE22_5                    ((uint32_t) 0x00000020)			/*!< Bit 5 */
#define TSC_THRHD22_BASE22_6                    ((uint32_t) 0x00000040)			/*!< Bit 6 */
#define TSC_THRHD22_BASE22_7                    ((uint32_t) 0x00000080)			/*!< Bit 7 */
#define TSC_THRHD22_BASE22_8                    ((uint32_t) 0x00000100)			/*!< Bit 8 */
#define TSC_THRHD22_BASE22_9                    ((uint32_t) 0x00000200)			/*!< Bit 9 */
#define TSC_THRHD22_BASE22_10                   ((uint32_t) 0x00000400)			/*!< Bit 10 */

#define TSC_THRHD22_DELTA22_Pos					(16U)
#define TSC_THRHD22_DELTA22_Msk					(0xFFUL << TSC_THRHD22_DELTA22_Pos)
#define TSC_THRHD22_DELTA22						TSC_THRHD22_DELTA22_Msk			/*!< DELTA22[7:0] (value of delta) */
#define TSC_THRHD22_DELTA22_0                  	((uint32_t) 0x00010000)			/*!< Bit 0 */
#define TSC_THRHD22_DELTA22_1                  	((uint32_t) 0x00020000)			/*!< Bit 1 */
#define TSC_THRHD22_DELTA22_2                  	((uint32_t) 0x00040000)			/*!< Bit 2 */
#define TSC_THRHD22_DELTA22_3                  	((uint32_t) 0x00080000)			/*!< Bit 3 */
#define TSC_THRHD22_DELTA22_4                  	((uint32_t) 0x00100000)			/*!< Bit 4 */
#define TSC_THRHD22_DELTA22_5                  	((uint32_t) 0x00200000)			/*!< Bit 5 */
#define TSC_THRHD22_DELTA22_6                  	((uint32_t) 0x00400000)			/*!< Bit 6 */
#define TSC_THRHD22_DELTA22_7                  	((uint32_t) 0x00800000)			/*!< Bit 7 */

/*****************  Bit definition for TSC_THRHD23 register  ******************/
#define TSC_THRHD23_BASE23_Pos					(0U)
#define TSC_THRHD23_BASE23_Msk					(0x7FFUL << TSC_THRHD23_BASE23_Pos)
#define TSC_THRHD23_BASE23						TSC_THRHD23_BASE23_Msk			/*!< BASE23[10:0] (value of base) */
#define TSC_THRHD23_BASE23_0					((uint32_t) 0x00000001)			/*!< Bit 0 */
#define TSC_THRHD23_BASE23_1                    ((uint32_t) 0x00000002)			/*!< Bit 1 */
#define TSC_THRHD23_BASE23_2                    ((uint32_t) 0x00000004)			/*!< Bit 2 */
#define TSC_THRHD23_BASE23_3                    ((uint32_t) 0x00000008)			/*!< Bit 3 */
#define TSC_THRHD23_BASE23_4                    ((uint32_t) 0x00000010)			/*!< Bit 4 */
#define TSC_THRHD23_BASE23_5                    ((uint32_t) 0x00000020)			/*!< Bit 5 */
#define TSC_THRHD23_BASE23_6                    ((uint32_t) 0x00000040)			/*!< Bit 6 */
#define TSC_THRHD23_BASE23_7                    ((uint32_t) 0x00000080)			/*!< Bit 7 */
#define TSC_THRHD23_BASE23_8                    ((uint32_t) 0x00000100)			/*!< Bit 8 */
#define TSC_THRHD23_BASE23_9                    ((uint32_t) 0x00000200)			/*!< Bit 9 */
#define TSC_THRHD23_BASE23_10                   ((uint32_t) 0x00000400)			/*!< Bit 10 */

#define TSC_THRHD23_DELTA23_Pos					(16U)
#define TSC_THRHD23_DELTA23_Msk					(0xFFUL << TSC_THRHD23_DELTA23_Pos)
#define TSC_THRHD23_DELTA23						TSC_THRHD23_DELTA23_Msk			/*!< DELTA23[7:0] (value of delta) */
#define TSC_THRHD23_DELTA23_0                  	((uint32_t) 0x00010000)			/*!< Bit 0 */
#define TSC_THRHD23_DELTA23_1                  	((uint32_t) 0x00020000)			/*!< Bit 1 */
#define TSC_THRHD23_DELTA23_2                  	((uint32_t) 0x00040000)			/*!< Bit 2 */
#define TSC_THRHD23_DELTA23_3                  	((uint32_t) 0x00080000)			/*!< Bit 3 */
#define TSC_THRHD23_DELTA23_4                  	((uint32_t) 0x00100000)			/*!< Bit 4 */
#define TSC_THRHD23_DELTA23_5                  	((uint32_t) 0x00200000)			/*!< Bit 5 */
#define TSC_THRHD23_DELTA23_6                  	((uint32_t) 0x00400000)			/*!< Bit 6 */
#define TSC_THRHD23_DELTA23_7                  	((uint32_t) 0x00800000)			/*!< Bit 7 */

/******************************************************************************/
/*                                                                            */
/*                                 RNGC Registers           	              */
/*                                                                            */
/******************************************************************************/
/******************  Bit definition for RNGC_CTRL register  *******************/
#define RNGC_CTRL_RING0_EN_Pos					(0U)
#define RNGC_CTRL_RING0_EN_Msk					(0x1UL << RNGC_CTRL_RING0_EN_Pos)		/*!< 0x00000001 */
#define RNGC_CTRL_RING0_EN						RNGC_CTRL_RING0_EN_Msk			/*!< Inverter ring 0 enable */
#define RNGC_CTRL_RING1_EN_Pos					(1U)
#define RNGC_CTRL_RING1_EN_Msk					(0x1UL << RNGC_CTRL_RING1_EN_Pos)		/*!< 0x00000002 */
#define RNGC_CTRL_RING1_EN						RNGC_CTRL_RING1_EN_Msk			/*!< Inverter ring 1 enable */
#define RNGC_CTRL_RNG_MODE_Pos					(5U)
#define RNGC_CTRL_RNG_MODE_Msk					(0x3UL << RNGC_CTRL_RNG_MODE_Pos)		/*!< 0x00000060 */
#define RNGC_CTRL_RNG_MODE						RNGC_CTRL_RNG_MODE_Msk			/*!< RNGC mode */
#define RNGC_CTRL_RNG_MODE_0					((uint32_t) 0x00000020)			/*!< Bit 0 */
#define RNGC_CTRL_RNG_MODE_1					((uint32_t) 0x00000040)			/*!< Bit 1 */

/**************  Bit definition for RNGC_CTRL_WR_READY register  **************/
#define RNGC_CTRL_WR_READY_READY_Pos			(0U)
#define RNGC_CTRL_WR_READY_READY_Msk			(0x1UL << RNGC_CTRL_WR_READY_READY_Pos)	/*!< 0x00000001 */
#define RNGC_CTRL_WR_READY_READY				RNGC_CTRL_WR_READY_READY_Msk	/*!< Control register ready to write */

/******************  Bit definition for RNGC_DATA register  *******************/
#define RNGC_DAT_DATA_Pos						(0U)
#define RNGC_DAT_DATA_Msk						(0xFFFFFFFFUL << RNGC_DAT_DATA_Pos)		/*!< 0xFFFFFFFF */
#define RNGC_DAT_DATA							RNGC_DAT_DATA_Msk				/*!< Random data */

/***************  Bit definition for RNGC_DAT_READY register  ****************/
#define RNGC_DAT_READY_READY_Pos				(0U)
#define RNGC_DAT_READY_READY_Msk				(0x1UL << RNGC_DAT_READY_READY_Pos)		/*!< 0x00000001 */
#define RNGC_DAT_READY_READY					RNGC_DAT_READY_READY_Msk		/*!< Random data ready */

/**
  * @}
  */ /* End of group Peripheral_Registers_Bits_Definition */

/**
  * @}
  */ /* End of group Exported_constants */

/** @addtogroup Exported_macros
  * @{
  */
  
  
  
/**
  * @}
  */ /* End of group Exported_macros */
  

/**
  * @}
  */ /* End of group CM32M4xxR */

/**
  * @}
  */ /* End of group CMIOT */

#ifdef __cplusplus
}
#endif

#endif  /* __CM32M4xxR_H__ */
