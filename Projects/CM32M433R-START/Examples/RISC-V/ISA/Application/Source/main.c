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

/** @addtogroup ISA
 * @{
 */

/**
 * @brief  Main function.
 */
int main(void) {
	/* SystemInit() function has been called by startup file startup_cm32m4xxr.s */
	log_init();

	CSR_MISA_Type misa_bits = (CSR_MISA_Type) __RV_CSR_READ(CSR_MISA);
	char misa_chars[30] = {0};
	uint8_t index = 0;
	if (misa_bits.b.mxl == 1) {
		misa_chars[index++] = '3';
		misa_chars[index++] = '2';
	} else if (misa_bits.b.mxl == 2) {
		misa_chars[index++] = '6';
		misa_chars[index++] = '4';
	} else if (misa_bits.b.mxl == 3) {
		misa_chars[index++] = '1';
		misa_chars[index++] = '2';
		misa_chars[index++] = '8';
	}
	if (misa_bits.b.i) {
		misa_chars[index++] = 'I';
	}
	if (misa_bits.b.m) {
		misa_chars[index++] = 'M';
	}
	if (misa_bits.b.a) {
		misa_chars[index++] = 'A';
	}
	if (misa_bits.b.b) {
		misa_chars[index++] = 'B';
	}
	if (misa_bits.b.c) {
		misa_chars[index++] = 'C';
	}
	if (misa_bits.b.e) {
		misa_chars[index++] = 'E';
	}
	if (misa_bits.b.f) {
		misa_chars[index++] = 'F';
	}
	if (misa_bits.b.d) {
		misa_chars[index++] = 'D';
	}
	if (misa_bits.b.q) {
		misa_chars[index++] = 'Q';
	}
	if (misa_bits.b.h) {
		misa_chars[index++] = 'H';
	}
	if (misa_bits.b.j) {
		misa_chars[index++] = 'J';
	}
	if (misa_bits.b.l) {
		misa_chars[index++] = 'L';
	}
	if (misa_bits.b.n) {
		misa_chars[index++] = 'N';
	}
	if (misa_bits.b.s) {
		misa_chars[index++] = 'S';
	}
	if (misa_bits.b.p) {
		misa_chars[index++] = 'P';
	}
	if (misa_bits.b.t) {
		misa_chars[index++] = 'T';
	}
	if (misa_bits.b.u) {
		misa_chars[index++] = 'U';
	}
	if (misa_bits.b.v) {
		misa_chars[index++] = 'V';
	}
	if (misa_bits.b.x) {
		misa_chars[index++] = 'X';
	}

	misa_chars[index++] = '\0';

	printf("MISA: RV%s\r\n", misa_chars);

	while (1) {

	}
}
/**
 * @}
 */

/**
 * @}
 */
