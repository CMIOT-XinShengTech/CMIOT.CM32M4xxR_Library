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

#include "main.h"
#include <stdio.h>
#include "bsp.h"

/** @addtogroup CM32M4xxR_StdPeriph_Examples
 * @{
 */
#define MACHINE_MODE_STACK_SIZE			0x400
static uint8_t sMachineModeStack[MACHINE_MODE_STACK_SIZE] = {0};

//Configure test_array Acess Permission on PMP
void PMP_Config() {
	PMP_Region_InitTypeDef pmp_init;

	pmp_init.Number = PMP_REGION_NUMBER0;
	pmp_init.Enable = PMP_REGION_ENABLE;   // Enable Configuration
	pmp_init.Lock = PMP_REGION_UNLOCK; //
	pmp_init.BaseAddress = 0;  //
	pmp_init.Size = PMP_REGION_SIZE_4GB;    //Setting array size
	pmp_init.AddressMatching = PMP_ADDRESS_MATCHING_NAPOT; //Setting PMP Size to NAPOT mode -> 2^n
	pmp_init.AccessPermission = PMP_ACCESS_RWX; //Setting array permission is Read Only

	PMP_ConfigRegion(&pmp_init);

	sPMP_Region_InitTypeDef spmp_init;
	spmp_init.Number = SPMP_REGION_NUMBER0;
	spmp_init.Enable = SPMP_REGION_ENABLE;
	spmp_init.Lock = SPMP_REGION_UNLOCK;
	spmp_init.BaseAddress = 0;
	spmp_init.Size = SPMP_REGION_SIZE_4GB;
	spmp_init.AddressMatching = SPMP_ADDRESS_MATCHING_NAPOT;
	spmp_init.UserMode = SPMP_USERMODE_RESET;
	spmp_init.AccessPermission = SPMP_ACCESS_RWX;

	sPMP_ConfigRegion(&spmp_init);
}
/**
 * @brief Jump User Mode
 */
void JumpUserMode(uint32_t func)
{
	__RV_CSR_WRITE(CSR_MSCRATCH, sMachineModeStack + MACHINE_MODE_STACK_SIZE);
	__RV_CSR_CLEAR(CSR_MSTATUS, MSTATUS_MPP);
	__RV_CSR_WRITE(CSR_MEPC, func);
	__ASM  volatile ( "mret ");
}

/**
 * @brief User Mode Application
 */
void Led()
{
	LedInit(LED2_PORT, LED2_PIN);
	while (1)
	{
	    LedBlink(LED2_PORT, LED2_PIN);
	    delay_ms(1000);
	}
}

/**
 * @brief Main function
 */
int main(void) {
	/* System Clocks Configuration */
	PMP_Config();

	JumpUserMode((uint32_t)Led);
	while (1) {
	}
}


#ifdef USE_FULL_ASSERT

/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param file pointer to the source file name
 * @param line assert_param error line source number
 */
void assert_failed(const uint8_t *expr, const uint8_t *file, uint32_t line) {
	/* User can add his own implementation to report the file name and line number,
	 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while (1) {
	}
}

#endif

/**
 * @}
 */

/**
 * @}
 */
