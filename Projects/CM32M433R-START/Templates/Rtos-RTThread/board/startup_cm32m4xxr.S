/*
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
 * \file     startup_cm32m4xxr.S
 * \brief    NMSIS Nuclei N/NX Class Core based Core Device Startup File for
 *           Device CM32M4xxR
 * \version  V1.00
 * \date     29. Jun 2020
 *
 ******************************************************************************/

#include "riscv_encoding.h"

.macro DECLARE_INT_HANDLER  INT_HDL_NAME
#if defined(__riscv_xlen) && (__riscv_xlen == 32)
    .word \INT_HDL_NAME
#else
    .dword \INT_HDL_NAME
#endif
.endm

/*
 * === Different Download and Running Mode ===
 * flashxip: Program will to be download into flash and run directly in Flash
 * flash: Program will be download into flash, when running, program will be copied to ilm/ram and run in ilm/ram
 * ilm: Program will be download into ilm/ram and run directly in ilm/ram, program lost when poweroff
 */

/*** Vector Table Code Section ***/
    /*
     * Put the interrupt vectors in .vtable section. According to the run mode,
     * .vtable section will be located at specific places and correct ld file
     * should be chosen as follows:
     * FlashXIP	: flash, gcc_cm32m4xxr.ld (default)
     * ILM		: ilm,   gcc_cm32m4xxr_ilm.ld
     * Flash	: ilm,   gcc_cm32m4xxr_flash.ld
     */
    .section .vtable

    .weak  eclic_msip_handler
    .weak  eclic_mtip_handler
	
	/* CM32M4xxR interrupt handlers */
    .weak  WWDG_IRQHandler
    .weak  PVD_IRQHandler
    .weak  TAMPER_IRQHandler
    .weak  RTC_IRQHandler
    .weak  FLASH_IRQHandler
    .weak  RCC_IRQHandler
    .weak  EXTI0_IRQHandler
    .weak  EXTI1_IRQHandler
    .weak  EXTI2_IRQHandler
    .weak  EXTI3_IRQHandler
    .weak  EXTI4_IRQHandler
    .weak  DMA1_Channel1_IRQHandler
    .weak  DMA1_Channel2_IRQHandler
    .weak  DMA1_Channel3_IRQHandler
    .weak  DMA1_Channel4_IRQHandler
    .weak  DMA1_Channel5_IRQHandler
    .weak  DMA1_Channel6_IRQHandler
    .weak  DMA1_Channel7_IRQHandler
    .weak  ADC1_2_IRQHandler
    .weak  USB_HP_CAN1_TX_IRQHandler
    .weak  USB_LP_CAN1_RX0_IRQHandler
    .weak  CAN1_RX1_IRQHandler
    .weak  CAN1_SCE_IRQHandler
    .weak  EXTI9_5_IRQHandler
    .weak  TIM1_BRK_IRQHandler
    .weak  TIM1_UP_IRQHandler
    .weak  TIM1_TRG_COM_IRQHandler
    .weak  TIM1_CC_IRQHandler
    .weak  TIM2_IRQHandler
    .weak  TIM3_IRQHandler
    .weak  TIM4_IRQHandler
    .weak  I2C1_EV_IRQHandler
	.weak  I2C1_ER_IRQHandler
    .weak  I2C2_EV_IRQHandler
	.weak  I2C2_ER_IRQHandler
    .weak  SPI1_IRQHandler
	.weak  SPI2_I2S2_IRQHandler
    .weak  USART1_IRQHandler
	.weak  USART2_IRQHandler
    .weak  USART3_IRQHandler
	.weak  EXTI15_10_IRQHandler
    .weak  RTCAlarm_IRQHandler
	.weak  TIM8_BRK_IRQHandler
    .weak  TIM8_UP_IRQHandler
	.weak  TIM8_TRG_COM_IRQHandler
    .weak  TIM8_CC_IRQHandler
	.weak  ADC3_4_IRQHandler
	.weak  TIM5_IRQHandler
    .weak  SPI3_I2S3_IRQHandler
	.weak  UART4_IRQHandler
    .weak  UART5_IRQHandler
	.weak  TIM6_IRQHandler
    .weak  TIM7_IRQHandler
	.weak  DMA2_Channel1_IRQHandler
    .weak  DMA2_Channel2_IRQHandler
	.weak  DMA2_Channel3_IRQHandler
    .weak  DMA2_Channel4_IRQHandler
	.weak  DMA2_Channel5_IRQHandler
    .weak  CAN2_TX_IRQHandler
	.weak  CAN2_RX0_IRQHandler
    .weak  CAN2_RX1_IRQHandler
	.weak  CAN2_SCE_IRQHandler
    .weak  QSPI_IRQHandler
	.weak  DMA2_Channel6_IRQHandler
    .weak  DMA2_Channel7_IRQHandler
	.weak  I2C3_EV_IRQHandler
    .weak  I2C3_ER_IRQHandler
	.weak  I2C4_EV_IRQHandler
    .weak  I2C4_ER_IRQHandler
	.weak  UART6_IRQHandler
    .weak  UART7_IRQHandler
	.weak  DMA1_Channel8_IRQHandler
    .weak  DMA2_Channel8_IRQHandler
	.weak  SAC_IRQHandler
	.weak  MMU_IRQHandler
    .weak  TSC_IRQHandler
	.weak  COMP_1_2_3_IRQHandler
    .weak  COMP_4_5_6_IRQHandler
	.weak  COMP7_IRQHandler
	.weak  R_SRAM_IRQHandler
	

    .globl vector_base
vector_base:
#if defined(DOWNLOAD_MODE) && (DOWNLOAD_MODE != DOWNLOAD_MODE_FLASH)
    j _start                                                /* 0: Reserved, Jump to _start when reset for ILM/FlashXIP mode.*/
    .align LOG_REGBYTES                                     /*    Need to align 4 byte for RV32, 8 Byte for RV64 */
#else
    DECLARE_INT_HANDLER     default_intexc_handler        	/* 0: Reserved, default handler for Flash download mode */
#endif
    DECLARE_INT_HANDLER     default_intexc_handler          /* 1: Reserved */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 2: Reserved */
    DECLARE_INT_HANDLER     eclic_msip_handler              /* 3: Machine software interrupt */

    DECLARE_INT_HANDLER     default_intexc_handler          /* 4: Reserved */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 5: Reserved */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 6: Reserved */
    DECLARE_INT_HANDLER     eclic_mtip_handler              /* 7: Machine timer interrupt */

    DECLARE_INT_HANDLER     default_intexc_handler          /* 8: Reserved */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 9: Reserved */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 10: Reserved */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 11: Reserved */

    DECLARE_INT_HANDLER     default_intexc_handler          /* 12: Reserved */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 13: Reserved */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 14: Reserved */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 15: Reserved */

    DECLARE_INT_HANDLER     default_intexc_handler          /* 16: Reserved */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 17: Reserved */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 18: Reserved */
	
    /* CM32M4XXR External Interrupts */
    DECLARE_INT_HANDLER		WWDG_IRQHandler					/* 19: Window WatchDog Interrupt */
    DECLARE_INT_HANDLER		PVD_IRQHandler					/* 20: PVD through EXTI Line detection Interrupt */
    DECLARE_INT_HANDLER		TAMPER_IRQHandler				/* 21: Tamper Interrupt */
    DECLARE_INT_HANDLER		RTC_IRQHandler					/* 22: RTC global Interrupt */
    DECLARE_INT_HANDLER		FLASH_IRQHandler				/* 23: FLASH global Interrupt */
    DECLARE_INT_HANDLER		RCC_IRQHandler					/* 24: RCC global Interrupt */
    DECLARE_INT_HANDLER		EXTI0_IRQHandler				/* 25: EXTI Line0 Interrupt */
    DECLARE_INT_HANDLER		EXTI1_IRQHandler				/* 26: EXTI Line1 Interrupt */
    DECLARE_INT_HANDLER		EXTI2_IRQHandler				/* 27: EXTI Line2 Interrupt */
    DECLARE_INT_HANDLER		EXTI3_IRQHandler				/* 28: EXTI Line3 Interrupt */
    DECLARE_INT_HANDLER		EXTI4_IRQHandler				/* 29: EXTI Line4 Interrupt */
    DECLARE_INT_HANDLER		DMA1_Channel1_IRQHandler		/* 30: DMA1 Channel 1 global Interrupt */
    DECLARE_INT_HANDLER		DMA1_Channel2_IRQHandler		/* 31: DMA1 Channel 2 global Interrupt */
    DECLARE_INT_HANDLER		DMA1_Channel3_IRQHandler		/* 32: DMA1 Channel 3 global Interrupt */
    DECLARE_INT_HANDLER		DMA1_Channel4_IRQHandler		/* 33: DMA1 Channel 4 global Interrupt */
    DECLARE_INT_HANDLER		DMA1_Channel5_IRQHandler		/* 34: DMA1 Channel 5 global Interrupt */
    DECLARE_INT_HANDLER		DMA1_Channel6_IRQHandler		/* 35: DMA1 Channel 6 global Interrupt */
    DECLARE_INT_HANDLER		DMA1_Channel7_IRQHandler		/* 36: DMA1 Channel 7 global Interrupt */
    DECLARE_INT_HANDLER		ADC1_2_IRQHandler				/* 37: ADC1 and ADC2 global Interrupt */
    DECLARE_INT_HANDLER		USB_HP_CAN1_TX_IRQHandler		/* 38: USB Device High Priority or CAN1 TX Interrupts */
    DECLARE_INT_HANDLER		USB_LP_CAN1_RX0_IRQHandler		/* 39: USB Device Low Priority or CAN1 RX0 Interrupts */
    DECLARE_INT_HANDLER		CAN1_RX1_IRQHandler				/* 40: CAN1 RX1 Interrupt */
    DECLARE_INT_HANDLER		CAN1_SCE_IRQHandler				/* 41: CAN1 SCE Interrupt */
    DECLARE_INT_HANDLER		EXTI9_5_IRQHandler				/* 42: External Line[9:5] Interrupts */
    DECLARE_INT_HANDLER		TIM1_BRK_IRQHandler				/* 43: TIM1 Break Interrupt */
    DECLARE_INT_HANDLER		TIM1_UP_IRQHandler				/* 44: TIM1 Update Interrupt */
    DECLARE_INT_HANDLER		TIM1_TRG_COM_IRQHandler			/* 45: TIM1 Trigger and Commutation Interrupt */
    DECLARE_INT_HANDLER		TIM1_CC_IRQHandler				/* 46: TIM1 Capture Compare Interrupt */
    DECLARE_INT_HANDLER		TIM2_IRQHandler					/* 47: TIM2 global Interrupt */
    DECLARE_INT_HANDLER		TIM3_IRQHandler					/* 48: TIM3 global Interrupt */
    DECLARE_INT_HANDLER		TIM4_IRQHandler					/* 49: TIM4 global Interrupt */
    DECLARE_INT_HANDLER		I2C1_EV_IRQHandler				/* 50: I2C1 Event Interrupt */
	DECLARE_INT_HANDLER		I2C1_ER_IRQHandler				/* 51: I2C1 Error Interrupt */
    DECLARE_INT_HANDLER		I2C2_EV_IRQHandler				/* 52: I2C2 Event Interrupt */
	DECLARE_INT_HANDLER		I2C2_ER_IRQHandler				/* 53: I2C2 Error Interrupt */
    DECLARE_INT_HANDLER		SPI1_IRQHandler					/* 54: SPI1 global Interrupt */
	DECLARE_INT_HANDLER		SPI2_I2S2_IRQHandler			/* 55: SPI2/I2S2 global Interrupt */
    DECLARE_INT_HANDLER		USART1_IRQHandler				/* 56: USART1 global Interrupt */
	DECLARE_INT_HANDLER		USART2_IRQHandler				/* 57: USART2 global Interrupt */
    DECLARE_INT_HANDLER		USART3_IRQHandler				/* 58: USART3 global Interrupt */
	DECLARE_INT_HANDLER		EXTI15_10_IRQHandler			/* 59: External Line[15:10] Interrupts */
    DECLARE_INT_HANDLER		RTCAlarm_IRQHandler				/* 60: RTC Alarm through EXTI Line Interrupt */
	DECLARE_INT_HANDLER     default_intexc_handler			/* 61: Reserved */
	DECLARE_INT_HANDLER		TIM8_BRK_IRQHandler				/* 62: TIM8 Break Interrupt */
    DECLARE_INT_HANDLER		TIM8_UP_IRQHandler				/* 63: TIM8 Update Interrupt */
	DECLARE_INT_HANDLER		TIM8_TRG_COM_IRQHandler			/* 64: TIM8 Trigger and Commutation Interrupt */
    DECLARE_INT_HANDLER		TIM8_CC_IRQHandler				/* 65: TIM8 Capture Compare Interrupt */
	DECLARE_INT_HANDLER		ADC3_4_IRQHandler				/* 66: ADC3 and ADC4 global Interrupt */
	DECLARE_INT_HANDLER		default_intexc_handler			/* 67: Reserved */
	DECLARE_INT_HANDLER     default_intexc_handler			/* 68: Reserved */
	DECLARE_INT_HANDLER		TIM5_IRQHandler					/* 69: TIM5 global Interrupt */
    DECLARE_INT_HANDLER		SPI3_I2S3_IRQHandler			/* 70: SPI3/I2S3 global Interrupt */
	DECLARE_INT_HANDLER		UART4_IRQHandler				/* 71: UART4 global Interrupt */
    DECLARE_INT_HANDLER		UART5_IRQHandler				/* 72: UART5 global Interrupt */
	DECLARE_INT_HANDLER		TIM6_IRQHandler					/* 73: TIM6 global Interrupt */
    DECLARE_INT_HANDLER		TIM7_IRQHandler					/* 74: TIM7 global Interrupt */
	DECLARE_INT_HANDLER		DMA2_Channel1_IRQHandler		/* 75: DMA2 Channel 1 global Interrupt */
    DECLARE_INT_HANDLER		DMA2_Channel2_IRQHandler		/* 76: DMA2 Channel 2 global Interrupt */
	DECLARE_INT_HANDLER		DMA2_Channel3_IRQHandler		/* 77: DMA2 Channel 3 global Interrupt */
    DECLARE_INT_HANDLER		DMA2_Channel4_IRQHandler		/* 78: DMA2 Channel 4 global Interrupt */
	DECLARE_INT_HANDLER		DMA2_Channel5_IRQHandler		/* 79: DMA2 Channel 5 global Interrupt */
	DECLARE_INT_HANDLER     default_intexc_handler			/* 80: Reserved */
	DECLARE_INT_HANDLER     default_intexc_handler			/* 81: Reserved */
    DECLARE_INT_HANDLER		CAN2_TX_IRQHandler				/* 82: CAN2 TX Interrupt */
	DECLARE_INT_HANDLER		CAN2_RX0_IRQHandler				/* 83: CAN2 RX0 Interrupt */
    DECLARE_INT_HANDLER		CAN2_RX1_IRQHandler				/* 84: CAN2 RX1 Interrupt */
	DECLARE_INT_HANDLER		CAN2_SCE_IRQHandler				/* 85: CAN2 SCE Interrupt */
    DECLARE_INT_HANDLER		QSPI_IRQHandler					/* 86: QSPI global Interrupt */
	DECLARE_INT_HANDLER		DMA2_Channel6_IRQHandler		/* 87: DMA2 Channel 6 global Interrupt */
    DECLARE_INT_HANDLER		DMA2_Channel7_IRQHandler		/* 88: DMA2 Channel 7 global Interrupt */
	DECLARE_INT_HANDLER		I2C3_EV_IRQHandler				/* 89: I2C3 Event Interrupt */
    DECLARE_INT_HANDLER		I2C3_ER_IRQHandler				/* 90: I2C3 Error Interrupt */
	DECLARE_INT_HANDLER		I2C4_EV_IRQHandler				/* 91: I2C4 Event Interrupt */
    DECLARE_INT_HANDLER		I2C4_ER_IRQHandler				/* 92: I2C4 Error Interrupt */
	DECLARE_INT_HANDLER		UART6_IRQHandler				/* 93: UART6 global Interrupt */
    DECLARE_INT_HANDLER		UART7_IRQHandler				/* 94: UART7 global Interrupt */
	DECLARE_INT_HANDLER		DMA1_Channel8_IRQHandler		/* 95: DMA1 Channel 8 global Interrupt */
    DECLARE_INT_HANDLER		DMA2_Channel8_IRQHandler		/* 96: DMA2 Channel 8 global Interrupt */
	DECLARE_INT_HANDLER     default_intexc_handler			/* 97: Reserved */
	DECLARE_INT_HANDLER		SAC_IRQHandler					/* 98: SAC global Interrupt */
	DECLARE_INT_HANDLER     MMU_IRQHandler					/* 99: MMU global Interrupt */
    DECLARE_INT_HANDLER		TSC_IRQHandler					/* 100: TSC global Interrupt */
	DECLARE_INT_HANDLER		COMP_1_2_3_IRQHandler			/* 101: COMP1 & COMP2 & COMP3 global Interrupt */
    DECLARE_INT_HANDLER		COMP_4_5_6_IRQHandler			/* 102: COMP4 & COMP5 & COMP6 global Interrupt */
	DECLARE_INT_HANDLER		COMP7_IRQHandler				/* 103: COMP7 global Interrupt */
	DECLARE_INT_HANDLER		R_SRAM_IRQHandler				/* 104: R-SRAM Error Interrupt */
	
    /* Please adjust the above part of interrupt definition code
     * according to your device interrupt number and its configuration */


/*** Startup Code Section ***/
    .section .init

    .globl _start
    .type _start,@function

/**
 * Reset Handler called on controller reset
 */
_start:
    /* ===== Startup Stage 1 ===== */
    /* Disable Global Interrupt */
    csrc CSR_MSTATUS, MSTATUS_MIE

	/* Transform logic address to actual address if necessary */
    la	 a0, _start
    li   a1, 1
 	slli a1, a1, 29
    bleu a1, a0, _start_main
    srli a1, a1, 2
    bleu a1, a0, _start_main
    la   a0, _start_main
    add  a0, a0, a1
 	jr   a0

_start_main:
    /* Initialize GP and Stack Pointer SP */
    .option push
    .option norelax
    la gp, __global_pointer$
	la tp, __tls_base
    .option pop
    la sp, _sp

    /*
     * Set the the NMI base mnvec to share
     * with mtvec by setting CSR_MMISC_CTL
     * bit 9 NMI_CAUSE_FFF to 1
     */
    li t0, MMISC_CTL_NMI_CAUSE_FFF
    csrs CSR_MMISC_CTL, t0

    /*
     * Intialize ECLIC vector interrupt
     * base address mtvt to vector_base
     */
    la t0, vector_base
    csrw CSR_MTVT, t0

    /*
     * Set ECLIC non-vector entry to be controlled
     * by mtvt2 CSR register.
     * Intialize ECLIC non-vector interrupt
     * base address mtvt2 to irq_entry.
     */
    la t0, irq_entry
    csrw CSR_MTVT2, t0
    csrs CSR_MTVT2, 0x1

    /*
     * Set Exception Entry MTVEC to exc_entry
     * Due to settings above, Exception and NMI
     * will share common entry.
     */
    la t0, exc_entry
    csrw CSR_MTVEC, t0

    /* Set the interrupt processing mode to ECLIC mode */
    li t0, 0x3f
    csrc CSR_MTVEC, t0
    csrs CSR_MTVEC, 0x3

    /* ===== Startup Stage 2 ===== */

#if defined(__riscv_flen) && __riscv_flen > 0
    /* Enable FPU */
    li t0, MSTATUS_FS
    csrs mstatus, t0
    csrw fcsr, x0
#endif

    /* Enable mcycle and minstret counter */
    csrci CSR_MCOUNTINHIBIT, 0x5

    /*
     * Call vendor defined SystemInit to
     * initialize the micro-controller system.
     * In FlashXIP and ILM mode, call SystemInit before code loading
     */
#if defined(DOWNLOAD_MODE) && (DOWNLOAD_MODE != DOWNLOAD_MODE_FLASH)
    call SystemInit
#endif

    /* ===== Startup Stage 3 ===== */
    /*
     * Load code section from FLASH to ILM
     * when code LMA is different with VMA
     */
    la a0, _ilm_lma
    la a1, _ilm
    /* If the ILM phy-address same as the logic-address, then quit */
    beq a0, a1, 2f
    la a2, _eilm
    bgeu a1, a2, 2f

1:
    /* Load code section if necessary */
    lw t0, (a0)
    sw t0, (a1)
    addi a0, a0, 4
    addi a1, a1, 4
    bltu a1, a2, 1b
2:
    /* Load data section */
    la a0, _data_lma
    la a1, _data
    la a2, _edata
    bgeu a1, a2, 2f
1:
    lw t0, (a0)
    sw t0, (a1)
    addi a0, a0, 4
    addi a1, a1, 4
    bltu a1, a2, 1b
2:
    /* Clear bss section */
    la a0, __bss_start
    la a1, _end
    bgeu a0, a1, 2f
1:
    sw zero, (a0)
    addi a0, a0, 4
    bltu a0, a1, 1b
2:
    /*
     * Call vendor defined SystemInit to
     * initialize the micro-controller system.
     * In Flash mode, call SystemInit after code loading
     */
#if defined(DOWNLOAD_MODE) && (DOWNLOAD_MODE == DOWNLOAD_MODE_FLASH)
    call SystemInit
#endif

    /* Call global constructors */
    la a0, __libc_fini_array
    call atexit
    /* Call C/C++ constructor start up code */
    call __libc_init_array

    /* do pre-init steps before main */
    call _premain_init
    /* ===== Call Main Function  ===== */
    /* argc = argv = 0 */
    li a0, 0
    li a1, 0
    call entry
    /* do post-main steps after main */
    call _postmain_fini

1:
    j 1b
