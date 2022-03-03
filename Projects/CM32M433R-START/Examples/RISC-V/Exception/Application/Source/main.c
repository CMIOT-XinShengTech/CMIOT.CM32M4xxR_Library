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

/** @addtogroup RISC-V Exception
 * @{
 */

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
 * @brief IllegalAccess Exception Handler.
 */
void IllegalAccess_Exception_Handler(unsigned long mcause, unsigned long sp)
{
	printf("illegal memory @ 0x%08X access!\r\n", __RV_CSR_READ(CSR_MBADADDR));
	while(1);
}

/**
 * @brief Ecall(System Software Call) Handler
 */
void ECALL_Exception_Handler(unsigned long mcause, unsigned long sp)
{
	uint32_t saved_regs = sp;
	uint32_t mepc = ((uint32_t *)saved_regs)[12];
	printf("ECALL Exception Trigger\r\n");
	/* Since the mepc is the ecall address when the exception is returned,
	 * there will be an endless loop in the return. The ecall is a
	 * 4-byte instruction. Modify the mepc to try to skip it. */
	((uint32_t *)saved_regs)[12] = mepc + 4;
}

/**
 * @brief  Main function.
 */
int main(void) {
	/* SystemInit() function has been called by startup file startup_cm32m4xxr.s */
	log_init();

	/* Register exception handling functions for system calls and illegal access */
	Exception_Register_EXC(MmodeEcall_EXCn, (unsigned long)ECALL_Exception_Handler);
	Exception_Register_EXC(LdFault_EXCn, (unsigned long)IllegalAccess_Exception_Handler);

	/* Call ecall to enter exception mode */
	__ECALL();
	printf("ECALL Process Completed! \r\n");

	/* Attempt to access an illegal address to trigger an exception */
	uint32_t trap = *(uint32_t *)0xFFFFFFFF;
	printf("trap : %d\r\n",trap);

	while (1) {

	}
}
/**
 * @}
 */

/**
 * @}
 */
