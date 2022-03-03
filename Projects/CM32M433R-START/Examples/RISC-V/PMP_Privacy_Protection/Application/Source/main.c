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
#include "privacy.h"
#include "bsp.h"

#include <stdio.h>

#define USER_CODE_REGION_BASE 										0x08010000
#define API_CODE_REGION_BASE 									 	0x08011000
#define PRIVACY_CODE_REGION_BASE 									0x08012000
#define USER_STACK_REGION_BASE 										0x2001f800
#define MAIN_STACK_REGION_BASE 										0x2001e800

//define pmp touch test array at 0x2001A000 (address loaction setting in .ld)
//access test_arry may trigger exception
uint8_t main_stack[0x800] __attribute__((section(".mainstack")));

uint32_t user_app_main(uint8_t mode);

void configMainStack(uint8_t *addr);

void enterUserMode(void *addr);
//PMP Exception Handler
void PMP_Exception_Handler(unsigned long mcause, unsigned long sp) {
	printf(
			"PMP Exception Occures Run at 0x%lx, Fetching Memory at 0x%lx\r\n!!!",
			__RV_CSR_READ(CSR_MEPC), __RV_CSR_READ(CSR_MBADADDR));
	while (1)
		;
}

void PMP_SYSCALL_Handler(unsigned long mcause, unsigned long sp);
//Configure test_array Acess Permission on PMP
void PMP_Config() {

	PMP_ClearRegion(PMP_REGION_NUMBER0);
	PMP_ClearRegion(PMP_REGION_NUMBER7);

	PMP_Region_InitTypeDef pmp_init;

	pmp_init.Number = PMP_REGION_NUMBER0;
	pmp_init.Enable = PMP_REGION_ENABLE;                 // Enable Configuration
	pmp_init.Lock = PMP_REGION_UNLOCK; // Configuration Lock, may not modify unless reset, and also match in Machine Mode
	pmp_init.BaseAddress = PRIVACY_CODE_REGION_BASE; //Seting privacy section Base
	pmp_init.Size = PMP_REGION_SIZE_2KB;          //Setting privacy section size
	pmp_init.AddressMatching = PMP_ADDRESS_MATCHING_NAPOT; //Setting PMP Size to NAPOT mode -> 2^n
	pmp_init.AccessPermission = PMP_ACCESS_NONE; //Setting array permission is Read Only

	PMP_ConfigRegion(&pmp_init);

	pmp_init.Number = PMP_REGION_NUMBER1;
	pmp_init.Enable = PMP_REGION_ENABLE;                 // Enable Configuration
	pmp_init.Lock = PMP_REGION_UNLOCK; // Configuration Lock, may not modify unless reset, and also match in Machine Mode
	pmp_init.BaseAddress = MAIN_STACK_REGION_BASE;    //Seting System Stack Base
	pmp_init.Size = PMP_REGION_SIZE_2KB;             //Setting System Stack size
	pmp_init.AddressMatching = PMP_ADDRESS_MATCHING_NAPOT; //Setting PMP Size to NAPOT mode -> 2^n
	pmp_init.AccessPermission = PMP_ACCESS_NONE; //Setting array permission is Read Only

	PMP_ConfigRegion(&pmp_init);

	pmp_init.Number = PMP_REGION_NUMBER7;
	pmp_init.Enable = PMP_REGION_ENABLE;                 // Enable Configuration
	pmp_init.Lock = PMP_REGION_UNLOCK; // Configuration Lock, may not modify unless reset, and also match in Machine Mode
	pmp_init.BaseAddress = 0;       //Seting test_array Base
	pmp_init.Size = PMP_REGION_SIZE_4GB;                   //Setting array size
	pmp_init.AddressMatching = PMP_ADDRESS_MATCHING_NAPOT; //Setting PMP Size to NAPOT mode -> 2^n
	pmp_init.AccessPermission = PMP_ACCESS_RWX; //Setting array permission is Read Only

	PMP_ConfigRegion(&pmp_init);

	//PMP_ConfigRegion(&pmp_init);
	sPMP_ClearRegion(PMP_REGION_NUMBER7);
	sPMP_Region_InitTypeDef spmp_init;
	spmp_init.Number = SPMP_REGION_NUMBER7;
	spmp_init.UserMode = SPMP_USERMODE_RESET;
	spmp_init.Enable = SPMP_REGION_ENABLE;               // Enable Configuration
	spmp_init.Lock = SPMP_REGION_UNLOCK; // Configuration Lock, may not modify unless reset, and also match in Machine Mode
	spmp_init.BaseAddress = 0;                          //Seting test_array Base
	spmp_init.Size = SPMP_REGION_SIZE_4GB;                  //Setting array size
	spmp_init.AddressMatching = SPMP_ADDRESS_MATCHING_NAPOT; //Setting PMP Size to NAPOT mode -> 2^n
	spmp_init.AccessPermission = SPMP_ACCESS_RWX; //Setting array permission is Read Only
	sPMP_ConfigRegion(&spmp_init);
	// Register PMP Exception Handler
	Exception_Register_EXC(CAUSE_FAULT_FETCH,
			(unsigned long) PMP_Exception_Handler);
	Exception_Register_EXC(CAUSE_FAULT_LOAD,
			(unsigned long) PMP_Exception_Handler);
	Exception_Register_EXC(CAUSE_FAULT_STORE,
			(unsigned long) PMP_Exception_Handler);
	Exception_Register_EXC(CAUSE_USER_ECALL,
			(unsigned long) PMP_SYSCALL_Handler);
	Exception_Register_EXC(CAUSE_MACHINE_ECALL,
			(unsigned long) PMP_SYSCALL_Handler);
	// privacy_encrypt(test_array, 16 , test_array);
}

/** @addtogroup CM32M4xxR_StdPeriph_Examples
 * @{
 */


/**
 * @brief Main function
 */
int main(void) {

	log_init();

	///* Output a message on Hyperterminal using printf function */
	printf("\n\rPMP Example Start!!!!!!\n\r");

	PMP_Config();

	configMainStack(main_stack + sizeof(main_stack));


	printf("\n\rtry to call user method from sys call\n\r");
	enterUserMode((void*) user_app_main);

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
