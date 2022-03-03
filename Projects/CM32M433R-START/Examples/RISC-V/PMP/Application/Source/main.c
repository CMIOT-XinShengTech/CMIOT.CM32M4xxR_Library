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
#define USER_REGION_BASE 0x2001A000

//define pmp touch test array at 0x2001A000 (address loaction setting in .ld)
//access test_arry may trigger exception
uint8_t test_array[128] __attribute__((section(".user")));

//PMP Exception Handler
void PMP_Exception_Handler() {
	printf(
			"PMP Exception Occures Run at 0x%lx, Fetching Memory at 0x%lx\r\n!!!",
			__RV_CSR_READ(CSR_MEPC), __RV_CSR_READ(CSR_MBADADDR));
	while (1)
		;
}

//Configure test_array Acess Permission on PMP
void PMP_Config() {
	PMP_Region_InitTypeDef pmp_init;

	pmp_init.Number = PMP_REGION_NUMBER0;
	pmp_init.Enable = PMP_REGION_ENABLE;   // Enable Configuration
	pmp_init.Lock = PMP_REGION_LOCK; // Configuration Lock, may not modify unless reset, and also match in Machine Mode
	pmp_init.BaseAddress = USER_REGION_BASE;  //Seting test_array Base
	pmp_init.Size = PMP_REGION_SIZE_128B;    //Setting array size
	pmp_init.AddressMatching = PMP_ADDRESS_MATCHING_NAPOT; //Setting PMP Size to NAPOT mode -> 2^n
	pmp_init.AccessPermission = PMP_ACCESS_R; //Setting array permission is Read Only

	PMP_ConfigRegion(&pmp_init);

	// Register PMP Exception Handler
	Exception_Register_EXC(CAUSE_FAULT_FETCH,
			(unsigned long) PMP_Exception_Handler);
	Exception_Register_EXC(CAUSE_FAULT_LOAD,
			(unsigned long) PMP_Exception_Handler);
	Exception_Register_EXC(CAUSE_FAULT_STORE,
			(unsigned long) PMP_Exception_Handler);
}

/**
 * @brief Main function
 */
int main(void) {
	/* System Clocks Configuration */

	log_init();
	/* Output a message on Hyperterminal using printf function */
	printf("\n\rPMP Example Start!!!!!!\n\r");

	char temp = test_array[15];
	printf("\n\r Reading test_array Success, before PMP Configuration\n\r");
	//try to write test_array without PMP Configuration, may be pass
	test_array[15] = 1;
	printf("\n\r Write test_array Success, before PMP Configuration\n\r");

	//Configure test_array PMP, set to Read Only
	PMP_Config();
	printf("\n\r Setting PMP Configuration!\n\r");

	//try to read test_array with read-only permission, may be pass
	temp = test_array[15];
	printf(
			"\n\r Reading  test_array with read-only permission Success, after PMP Configuration\n\r");

	//try to write test_array with read-only permission, could be failure
	test_array[15] = 1;
	//could not run to here
	printf("\n\r !!!!!!!!!!!!!!!!!!!!!!!!!!Fail!!!!!!!!!!!!!!!!!!!!!\n\r");
	printf(
			"\n\r Writting test_array with read-only permission , after PMP Configuration\n\r");

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
