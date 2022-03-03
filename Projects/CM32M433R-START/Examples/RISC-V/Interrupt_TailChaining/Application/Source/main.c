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

/** @addtogroup Interrupt_TailChaining
 * @{
 */

/**
 * @brief  global Interrupt counter, record the number of interrupts entered
 */
uint32_t g_interruptCnt = 0;


/**
 * @brief  Configures the different system clocks.
 */
void RCC_Configuration(void) {
	/* TIM2&3 clock enable */
	RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM2, ENABLE);
	RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM3, ENABLE);
	RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM4, ENABLE);
}

/**
 * @brief  Configures Timer2, 0.5s timeout
 */
void TIM2_Configuration(void) {
	TIM_TimeBaseInitType TIM_TimeBaseStructure = { 0 };
	/* Time base configuration */
	TIM_TimeBaseStructure.Period = 5000 - 1;	//0.5s
	TIM_TimeBaseStructure.Prescaler = 7200 - 1;	//10Khz
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
 * @brief  Configures Timer3, timeout Immediately
 */
void TIM3_Configuration(void) {
	TIM_TimeBaseInitType TIM_TimeBaseStructure = { 0 };
	/* Time base configuration */
	TIM_TimeBaseStructure.Period = 1;		//immediately
	TIM_TimeBaseStructure.Prescaler = 7200 - 1;		//10Khz
	TIM_TimeBaseStructure.ClkDiv = 0;
	TIM_TimeBaseStructure.CntMode = TIM_CNT_MODE_UP;

	TIM_InitTimeBase(TIM3, &TIM_TimeBaseStructure);

	/* TIM3 enable update irq */
	TIM_ConfigInt(TIM3, TIM_INT_UPDATE, ENABLE);

	/* ECLIC Interrupt Config */
	ECLIC_SetLevelIRQ(TIM3_IRQn, 0);
	ECLIC_SetPriorityIRQ(TIM3_IRQn, 1);
	ECLIC_SetTrigIRQ(TIM3_IRQn, ECLIC_LEVEL_TRIGGER);
	ECLIC_SetShvIRQ(TIM3_IRQn, ECLIC_NON_VECTOR_INTERRUPT);
	ECLIC_EnableIRQ(TIM3_IRQn);

}
/**
 * @brief  Configures Timer4, timeout Immediately
 */
void TIM4_Configuration(void) {
	TIM_TimeBaseInitType TIM_TimeBaseStructure = { 0 };
	/* Time base configuration */
	TIM_TimeBaseStructure.Period = 1;		//immediately
	TIM_TimeBaseStructure.Prescaler = 7200 - 1;	//10Khz
	TIM_TimeBaseStructure.ClkDiv = 0;
	TIM_TimeBaseStructure.CntMode = TIM_CNT_MODE_UP;

	TIM_InitTimeBase(TIM4, &TIM_TimeBaseStructure);

	/* TIM4 enable update irq */
	TIM_ConfigInt(TIM4, TIM_INT_UPDATE, ENABLE);

	/* ECLIC Interrupt Config */
	ECLIC_SetLevelIRQ(TIM4_IRQn, 0);
	ECLIC_SetPriorityIRQ(TIM4_IRQn, 1);
	ECLIC_SetTrigIRQ(TIM4_IRQn, ECLIC_LEVEL_TRIGGER);
	ECLIC_SetShvIRQ(TIM4_IRQn, ECLIC_NON_VECTOR_INTERRUPT);
	ECLIC_EnableIRQ(TIM4_IRQn);

}

/**
 * @brief  Main function.
 */
int main(void) {
	/* SystemInit() function has been called by startup file startup_cm32m4xxr.s */
	log_init();
	/* Peripherals Clock Configuration */
	RCC_Configuration();

	__enable_irq();
	/* Initialize Led1&2  as output pushpull mode */
	LedInit(LED1_PORT, LED1_PIN);
	LedInit(LED2_PORT, LED2_PIN);
	LedInit(LED3_PORT, LED3_PIN);

	LedOff(LED1_PORT, LED1_PIN);
	LedOff(LED2_PORT, LED2_PIN);
	LedOff(LED3_PORT, LED3_PIN);

	TIM2_Configuration();
	TIM3_Configuration();
	TIM4_Configuration();

	while (1) {

	}
}

/**
 * @brief  Timer2 IRQ Handler
 */
void TIM2_IRQHandler() {

	if (TIM_GetIntStatus(TIM2, TIM_INT_UPDATE) != RESET) {
		TIM_ClrIntPendingBit(TIM2, TIM_INT_UPDATE);
		/* Enable TIM3, should trigger the interrupt immediately*/
		TIM_Enable(TIM3, ENABLE);
		printf("TIM2_IRQHandler :%d\r\n", g_interruptCnt);
		LedBlink(LED1_PORT, LED1_PIN);
	}
}

/**
 * @brief  Timer3 IRQ Handler
 */
void TIM3_IRQHandler() {

	if (TIM_GetIntStatus(TIM3, TIM_INT_UPDATE) != RESET) {
		TIM_ClrIntPendingBit(TIM3, TIM_INT_UPDATE);
		TIM_Enable(TIM3, DISABLE);
		/* Enable TIM4, should trigger the interrupt immediately*/
		TIM_Enable(TIM4, ENABLE);
		printf("TIM3_IRQHandler :%d\r\n", g_interruptCnt);
		LedBlink(LED2_PORT, LED2_PIN);


	}

}

/**
 * @brief  Timer4 IRQ Handler
 */
void TIM4_IRQHandler() {
	if (TIM_GetIntStatus(TIM4, TIM_INT_UPDATE) != RESET) {
		TIM_ClrIntPendingBit(TIM4, TIM_INT_UPDATE);
		TIM_Enable(TIM4, DISABLE);
		printf("TIM4_IRQHandler :%d\r\n", g_interruptCnt);
		LedBlink(LED3_PORT, LED3_PIN);

	}
}

/**
 * @}
 */

/**
 * @}
 */
