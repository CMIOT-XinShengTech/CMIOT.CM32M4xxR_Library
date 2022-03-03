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
 * @file main.c
 * @author CMIOT Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */

#include <main.h>
#include "bsp.h"

/** @addtogroup CM32M4xxR_StdPeriph_Examples
 * @{
 */

/** @addtogroup Interrupt Nesting * @{
 */

/**
 * @brief  Configures the different system clocks.
 */
void RCC_Configuration(void) {
	/* TIM2,3,4 clock enable */
	RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM2, ENABLE);
	RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM3, ENABLE);
	RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM4, ENABLE);
}
/**
 * @brief  Configures TIM2
 */
void TIM2_Configuration(void) {
	TIM_TimeBaseInitType TIM_TimeBaseStructure = { 0 };
	/* Time base configuration */
	TIM_TimeBaseStructure.Period = 50000 - 1;	//5s
	TIM_TimeBaseStructure.Prescaler = 7200 - 1;	// 10KHz
	TIM_TimeBaseStructure.ClkDiv = 0;
	TIM_TimeBaseStructure.CntMode = TIM_CNT_MODE_UP;

	TIM_InitTimeBase(TIM2, &TIM_TimeBaseStructure);
	/* TIM2 enable update irq */
	TIM_ConfigInt(TIM2, TIM_INT_UPDATE, ENABLE);

	/* TIM2 enable counter */
	TIM_Enable(TIM2, ENABLE);

	/* ECLIC Interrupt Config */
	ECLIC_SetLevelIRQ(TIM2_IRQn, 0);
	ECLIC_SetPriorityIRQ(TIM2_IRQn, 1);
	ECLIC_SetTrigIRQ(TIM2_IRQn, ECLIC_LEVEL_TRIGGER);
	ECLIC_SetShvIRQ(TIM2_IRQn, ECLIC_NON_VECTOR_INTERRUPT);
	ECLIC_EnableIRQ(TIM2_IRQn);
}
/**
 * @brief  Configures TIM3
 */
void TIM3_Configuration(void) {
	TIM_TimeBaseInitType TIM_TimeBaseStructure = { 0 };
	/* Time base configuration */
	TIM_TimeBaseStructure.Period = 5000 - 1;		//0.5s
	TIM_TimeBaseStructure.Prescaler = 7200 - 1;		// 10KHz
	TIM_TimeBaseStructure.ClkDiv = 0;
	TIM_TimeBaseStructure.CntMode = TIM_CNT_MODE_UP;

	TIM_InitTimeBase(TIM3, &TIM_TimeBaseStructure);

	/* TIM3 enable update irq */
	TIM_ConfigInt(TIM3, TIM_INT_UPDATE, ENABLE);
	/* TIM3 enable counter */
	TIM_Enable(TIM3, ENABLE);

	/* ECLIC Interrupt Config */
	ECLIC_SetLevelIRQ(TIM3_IRQn, 1);
	ECLIC_SetPriorityIRQ(TIM3_IRQn, 2);
	ECLIC_SetTrigIRQ(TIM3_IRQn, ECLIC_LEVEL_TRIGGER);
	ECLIC_SetShvIRQ(TIM3_IRQn, ECLIC_VECTOR_INTERRUPT);
	ECLIC_EnableIRQ(TIM3_IRQn);

}
/**
 * @brief  Configures TIM4
 */
void TIM4_Configuration(void) {
	TIM_TimeBaseInitType TIM_TimeBaseStructure = { 0 };
	/* Time base configuration */
	TIM_TimeBaseStructure.Period = 2500 - 1;		//0.25s
	TIM_TimeBaseStructure.Prescaler = 7200 - 1;		// 10KHz
	TIM_TimeBaseStructure.ClkDiv = 0;
	TIM_TimeBaseStructure.CntMode = TIM_CNT_MODE_UP;

	TIM_InitTimeBase(TIM4, &TIM_TimeBaseStructure);

	/* TIM4 enable update irq */
	TIM_ConfigInt(TIM4, TIM_INT_UPDATE, ENABLE);
	/* TIM3 enable counter */
	TIM_Enable(TIM4, ENABLE);

	/* ECLIC Interrupt Config */
	ECLIC_SetLevelIRQ(TIM4_IRQn, 2);
	ECLIC_SetPriorityIRQ(TIM4_IRQn, 3);
	ECLIC_SetTrigIRQ(TIM4_IRQn, ECLIC_LEVEL_TRIGGER);
	ECLIC_SetShvIRQ(TIM4_IRQn, ECLIC_NON_VECTOR_INTERRUPT);
	ECLIC_EnableIRQ(TIM4_IRQn);

}

/**
 * @brief  Main function.
 */
int main(void) {
	/* SystemInit() function has been called by startup file startup_cm32m4xxr.s */

	/* Peripherals Clock Configuration */
	RCC_Configuration();

	__enable_irq();

	/* Initialize Led1,2,3  as output pushpull mode */
	LedInit(LED1_PORT, LED1_PIN);
	LedInit(LED2_PORT, LED2_PIN);
	LedInit(LED3_PORT, LED3_PIN);

	LedOff(LED1_PORT, LED1_PIN);
	LedOff(LED2_PORT, LED2_PIN);
	LedOff(LED3_PORT, LED3_PIN);

	/* Start Timer */
	TIM2_Configuration();
	TIM3_Configuration();
	TIM4_Configuration();

	while (1) {

	}
}
/**
 * @brief  TIM2 IRQ Handler Non-Vector Interrupt
 */
void TIM2_IRQHandler() {
	if (TIM_GetIntStatus(TIM2, TIM_INT_UPDATE) != RESET) {
		TIM_ClrIntPendingBit(TIM2, TIM_INT_UPDATE);

		LedBlink(LED1_PORT, LED1_PIN);
		delay_ms(1000);		//delay to wait other Timer Interrupt
	}
}

/**
 * @brief  TIM3 IRQ Handler	Vector Interrupt
 * @note Vector interrupt does not support nesting.
 * If you need to support nesting, add SAVE_IRQ_CSR_CONTEXT() / RESTORE_IRQ_CSR_CONTEXT()
 * in the interrupt response.
 */
__INTERRUPT void TIM3_IRQHandler() {

	SAVE_IRQ_CSR_CONTEXT();	// Save necessary CSRs into variables for vector interrupt nesting

	if (TIM_GetIntStatus(TIM3, TIM_INT_UPDATE) != RESET) {
		TIM_ClrIntPendingBit(TIM3, TIM_INT_UPDATE);

		LedBlink(LED2_PORT, LED2_PIN);
	}

	RESTORE_IRQ_CSR_CONTEXT();	//Restore necessary CSRs from variables for vector interrupt nesting
}

/**
 * @brief  TIM4 IRQ Handler	Non-Vector Interrupt
 */
void TIM4_IRQHandler() {
	if (TIM_GetIntStatus(TIM4, TIM_INT_UPDATE) != RESET) {
		TIM_ClrIntPendingBit(TIM4, TIM_INT_UPDATE);
		LedBlink(LED3_PORT, LED3_PIN);

	}
}

/**
 * @}
 */

/**
 * @}
 */
