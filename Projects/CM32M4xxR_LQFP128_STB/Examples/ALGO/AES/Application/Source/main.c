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
#include "cm32m4xxr_aes.h"
#include "cm32m4xxr_algo_common.h"
#include <string.h>

/** @addtogroup CM32M4xxR_StdPeriph_Examples
 * @{
 */

/** @addtogroup AES
 * @{
 */
void DumpWords(const uint32_t *words, uint32_t len) {
	for (uint32_t i = 0; i < len; ++i) {
		log_info("0x%08x, ", words[i]);
	}
}

void DumpBytes(const uint8_t *bytes, uint32_t len) {
	for (uint32_t i = 0; i < len; ++i) {
		log_info("%02x", bytes[i]);
	}
}

int demo_aes_ecb() {
	__attribute__ ((aligned (4))) uint8_t key[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9,
			10, 11, 12, 13, 14, 15, 16 };
	__attribute__ ((aligned (4))) uint8_t plain[16] = { 0x11, 0x22, 0x33, 0x44,
			0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF,
			0x00 };
	__attribute__ ((aligned (4))) uint8_t cipher[16];
	__attribute__ ((aligned (4))) uint8_t plainOut[16];
	__attribute__ ((aligned (4))) uint8_t iv[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9,
			10, 11, 12, 13, 14, 15, 16 };

	AES_PARM AES_Parm = { 0 };

	// aes ecb mode
	AES_Parm.in = (uint32_t*) plain;
	AES_Parm.out = (uint32_t*) cipher;
	AES_Parm.key = (uint32_t*) key;
	AES_Parm.iv = NULL; // IV is not needed in ECB mode
	AES_Parm.inWordLen = sizeof(plain) / sizeof(uint32_t);
	AES_Parm.keyWordLen = sizeof(key) / sizeof(uint32_t);
	AES_Parm.Mode = AES_ECB;
	AES_Parm.En_De = AES_ENC;

	// encrypt data
	if (AES_Init_OK != AES_Init(&AES_Parm)) {
		log_error("AES_Init failed.\n");
		return -1;
	}
	if (AES_Crypto_OK != AES_Crypto(&AES_Parm)) {
		AES_Close();
		log_error("AES_Crypto failed\n");
		return -1;
	}
	AES_Close();

	log_info("AES ECB encrypt:\n");
	log_info("key = ");
	DumpBytes(key, sizeof(key));
	log_info("\n");
	log_info("plain = ");
	DumpBytes(plain, sizeof(plain));
	log_info("\n");
	log_info("cipher = ");
	DumpBytes(cipher, sizeof(cipher));
	log_info("\n");

	AES_Parm.in = (uint32_t*) cipher;
	AES_Parm.out = (uint32_t*) plainOut;
	AES_Parm.En_De = AES_DEC;

	// decrypt data
	if (AES_Init_OK != AES_Init(&AES_Parm)) {
		log_error("AES_Init failed.\n");
		return -1;
	}
	if (AES_Crypto_OK != AES_Crypto(&AES_Parm)) {
		AES_Close();
		log_error("AES_Crypto failed\n");
		return -1;
	}
	AES_Close();
	log_info("AES ECB decrypt:\n");
	log_info("plainOut = ");
	DumpBytes(plainOut, sizeof(plainOut));
	log_info("\n");
	if (memcmp(plain, plainOut, sizeof(plain)) != 0) {
		log_error("AES decrypt result do not equal plain data.\n");
		return -1;
	}
	return 0;
}

int demo_aes_cbc() {
	__attribute__ ((aligned (4))) uint8_t key[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9,
			10, 11, 12, 13, 14, 15, 16 };
	__attribute__ ((aligned (4))) uint8_t plain[16] = { 0x11, 0x22, 0x33, 0x44,
			0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF,
			0x00 };
	__attribute__ ((aligned (4))) uint8_t cipher[16];
	__attribute__ ((aligned (4))) uint8_t plainOut[16];
	__attribute__ ((aligned (4))) uint8_t iv[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9,
			10, 11, 12, 13, 14, 15, 16 };
	AES_PARM AES_Parm = { 0 };
	// aes cbc mode
	AES_Parm.in = (uint32_t*) plain;
	AES_Parm.out = (uint32_t*) cipher;
	AES_Parm.key = (uint32_t*) key;
	AES_Parm.iv = (uint32_t*) iv;
	AES_Parm.inWordLen = sizeof(plain) / sizeof(uint32_t);
	AES_Parm.keyWordLen = sizeof(key) / sizeof(uint32_t);
	AES_Parm.Mode = AES_CBC;
	AES_Parm.En_De = AES_ENC;

	// encrypt data
	if (AES_Init_OK != AES_Init(&AES_Parm)) {
		log_error("AES_Init failed.\n");
		return -1;
	}
	if (AES_Crypto_OK != AES_Crypto(&AES_Parm)) {
		AES_Close();
		log_error("AES_Crypto failed\n");
		return -1;
	}
	AES_Close();

	log_info("AES CBC encrypt:\n");
	log_info("key = ");
	DumpBytes(key, sizeof(key));
	log_info("\n");
	log_info("plain = ");
	DumpBytes(plain, sizeof(plain));
	log_info("\n");
	log_info("iv = ");
	DumpBytes(iv, sizeof(iv));
	log_info("\n");
	log_info("cipher = ");
	DumpBytes(cipher, sizeof(cipher));
	log_info("\n");

	AES_Parm.in = (uint32_t*) cipher;
	AES_Parm.out = (uint32_t*) plainOut;
	AES_Parm.En_De = AES_DEC;

	// decrypt data
	if (AES_Init_OK != AES_Init(&AES_Parm)) {
		log_error("AES_Init failed.\n");
		return -1;
	}
	if (AES_Crypto_OK != AES_Crypto(&AES_Parm)) {
		AES_Close();
		log_error("AES_Crypto failed\n");
		return -1;
	}
	AES_Close();
	log_info("AES CBC decrypt:\n");
	log_info("plainOut = ");
	DumpBytes(plainOut, sizeof(plainOut));
	log_info("\n");
	if (memcmp(plain, plainOut, sizeof(plain)) != 0) {
		log_error("AES decrypt result do not equal plain data.\n");
		return -1;
	}
	return 0;
}

int demo_aes_ctr() {
	__attribute__ ((aligned (4))) uint8_t key[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9,
			10, 11, 12, 13, 14, 15, 16 };
	__attribute__ ((aligned (4))) uint8_t plain[24] = { 0x11, 0x22, 0x33, 0x44,
			0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF,
			0x00, 0X32, 0X34, 0x35, 0X83, 0X33, 0X22, 0X32, 0x22 };
	__attribute__ ((aligned (4))) uint8_t cipher[24];
	__attribute__ ((aligned (4))) uint8_t plainOut[24];
	__attribute__ ((aligned (4))) uint8_t counter[16] = { 0 }; //Set the initial counter to 0
	AES_PARM AES_Parm = { 0 };

	// aes ctr mode
	AES_Parm.in = (uint32_t*) plain;
	AES_Parm.out = (uint32_t*) cipher;
	AES_Parm.key = (uint32_t*) key;
	AES_Parm.iv = (uint32_t*) counter;
	AES_Parm.inWordLen = sizeof(plain) / sizeof(uint32_t);
	AES_Parm.keyWordLen = sizeof(key) / sizeof(uint32_t);
	AES_Parm.Mode = AES_CTR;
	AES_Parm.En_De = AES_ENC;

	// encrypt data
	if (AES_Init_OK != AES_Init(&AES_Parm)) {
		log_error("AES_Init failed.\n");
		return -1;
	}
	if (AES_Crypto_OK != AES_Crypto(&AES_Parm)) {
		AES_Close();
		log_error("AES_Crypto failed\n");
		return -1;
	}
	AES_Close();

	log_info("AES CTR encrypt:\n");
	log_info("key = ");
	DumpBytes(key, sizeof(key));
	log_info("\n");
	log_info("plain = ");
	DumpBytes(plain, sizeof(plain));
	log_info("\n");
	log_info("counter = ");
	DumpBytes(counter, sizeof(counter));
	log_info("\n");
	log_info("cipher = ");
	DumpBytes(cipher, sizeof(cipher));
	log_info("\n");

	AES_Parm.in = (uint32_t*) cipher;
	AES_Parm.out = (uint32_t*) plainOut;
	AES_Parm.En_De = AES_DEC;

	// decrypt data
	if (AES_Init_OK != AES_Init(&AES_Parm)) {
		log_error("AES_Init failed.\n");
		return -1;
	}
	if (AES_Crypto_OK != AES_Crypto(&AES_Parm)) {
		AES_Close();
		log_error("AES_Crypto failed\n");
		return -1;
	}
	AES_Close();
	log_info("AES CTR decrypt:\n");
	log_info("plainOut = ");
	DumpBytes(plainOut, sizeof(plainOut));
	log_info("\n");
	if (memcmp(plain, plainOut, sizeof(plain)) != 0) {
		log_error("AES decrypt result do not equal plain data.\n");
		return -1;
	}
	return 0;
}
/**
 * @brief  Main function.
 */
int main(void) {
	/* SystemInit() function has been called by startup file startup_cm32m4xxr.s */
	int ret = 0;
	/* Initialize Log */
	log_init();

	ret = demo_aes_ecb();
	if (ret != 0) {
		log_error("demo_aes_ecb fail.\n");
	}
	demo_aes_cbc();
	if (ret != 0) {
		log_error("demo_aes_cbc fail.\n");
	}
	demo_aes_ctr();
	if (ret != 0) {
		log_error("demo_aes_ctr fail.\n");
	}

	while (1) {

	}
}

/**
 * @}
 */

/**
 * @}
 */
