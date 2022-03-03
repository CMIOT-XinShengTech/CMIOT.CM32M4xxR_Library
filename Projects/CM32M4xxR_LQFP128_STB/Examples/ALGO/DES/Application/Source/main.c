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
#include "cm32m4xxr_des.h"
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

int demo_des_1key_ecb() {
	__attribute__ ((aligned (4))) uint8_t key[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	__attribute__ ((aligned (4))) uint8_t plain[16] = { 0x11, 0x22, 0x33, 0x44,
			0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF,
			0x00 };
	__attribute__ ((aligned (4))) uint8_t cipher[16];
	__attribute__ ((aligned (4))) uint8_t plainOut[16];

	DES_PARM param = { 0 };

	// des ecb mode
	param.in = (uint32_t*) plain;
	param.out = (uint32_t*) cipher;
	param.key = (uint32_t*) key;
	param.iv = NULL; // IV is not needed in ECB mode
	param.inWordLen = sizeof(plain) / sizeof(uint32_t);
	param.keyMode = DES_KEY;
	param.Mode = DES_ECB;
	param.En_De = DES_ENC;

	// encrypt data
	if (DES_Init_OK != DES_Init(&param)) {
		log_error("DES_Init failed.\n");
		return -1;
	}
	if (DES_Crypto_OK != DES_Crypto(&param)) {
		DES_Close();
		log_error("DES_Crypto failed\n");
		return -1;
	}
	DES_Close();

	log_info("DES 1KEY ECB encrypt:\n");
	log_info("key = ");
	DumpBytes(key, sizeof(key));
	log_info("\n");
	log_info("plain = ");
	DumpBytes(plain, sizeof(plain));
	log_info("\n");
	log_info("cipher = ");
	DumpBytes(cipher, sizeof(cipher));
	log_info("\n");

	param.in = (uint32_t*) cipher;
	param.out = (uint32_t*) plainOut;
	param.En_De = DES_DEC;

	// decrypt data
	if (DES_Init_OK != DES_Init(&param)) {
		log_error("DES_Init failed.\n");
		return -1;
	}
	if (DES_Crypto_OK != DES_Crypto(&param)) {
		DES_Close();
		log_error("DES_Crypto failed\n");
		return -1;
	}
	DES_Close();

	log_info("DES 1KEY ECB decrypt:\n");
	log_info("plainOut = ");
	DumpBytes(plainOut, sizeof(plainOut));
	log_info("\n");
	if (memcmp(plain, plainOut, sizeof(plain)) != 0) {
		log_error("DES decrypt result do not equal plain data.\n");
		return -1;
	}
	return 0;
}

int demo_des_1key_cbc() {
	__attribute__ ((aligned (4))) uint8_t key[8] = { 1, 2, 3, 4, 5, 6, 7, 8, };
	__attribute__ ((aligned (4))) uint8_t plain[16] = { 0x11, 0x22, 0x33, 0x44,
			0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF,
			0x00 };
	__attribute__ ((aligned (4))) uint8_t cipher[16];
	__attribute__ ((aligned (4))) uint8_t plainOut[16];
	__attribute__ ((aligned (4))) uint8_t iv[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };

	DES_PARM param = { 0 };

	// des cbc mode
	param.in = (uint32_t*) plain;
	param.out = (uint32_t*) cipher;
	param.key = (uint32_t*) key;
	param.iv = (uint32_t *)iv;
	param.inWordLen = sizeof(plain) / sizeof(uint32_t);
	param.keyMode = TDES_2KEY;
	param.Mode = DES_CBC;
	param.En_De = DES_ENC;

	// encrypt data
	if (DES_Init_OK != DES_Init(&param)) {
		log_error("DES_Init failed.\n");
		return -1;
	}
	if (DES_Crypto_OK != DES_Crypto(&param)) {
		DES_Close();
		log_error("DES_Crypto failed\n");
		return -1;
	}
	DES_Close();

	log_info("DES 1KEY CBC encrypt:\n");
	log_info("key = ");
	DumpBytes(key, sizeof(key));
	log_info("\n");
	log_info("plain = ");
	DumpBytes(plain, sizeof(plain));
	log_info("\n");
	log_info("cipher = ");
	DumpBytes(cipher, sizeof(cipher));
	log_info("\n");

	param.in = (uint32_t*) cipher;
	param.out = (uint32_t*) plainOut;
	param.En_De = DES_DEC;

	// decrypt data
	if (DES_Init_OK != DES_Init(&param)) {
		log_error("DES_Init failed.\n");
		return -1;
	}
	if (DES_Crypto_OK != DES_Crypto(&param)) {
		DES_Close();
		log_error("DES_Crypto failed\n");
		return -1;
	}
	DES_Close();

	log_info("DES 1KEY CBC decrypt:\n");
	log_info("plainOut = ");
	DumpBytes(plainOut, sizeof(plainOut));
	log_info("\n");
	if (memcmp(plain, plainOut, sizeof(plain)) != 0) {
		log_error("DES decrypt result do not equal plain data.\n");
		return -1;
	}
	return 0;
}

int demo_3des_2key_ecb() {
	__attribute__ ((aligned (4))) uint8_t key[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9,
			10, 11, 12, 13, 14, 15, 16 };
	__attribute__ ((aligned (4))) uint8_t plain[16] = { 0x11, 0x22, 0x33, 0x44,
			0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF,
			0x00 };
	__attribute__ ((aligned (4))) uint8_t cipher[16];
	__attribute__ ((aligned (4))) uint8_t plainOut[16];

	DES_PARM param = { 0 };

	// des ecb mode
	param.in = (uint32_t*) plain;
	param.out = (uint32_t*) cipher;
	param.key = (uint32_t*) key;
	param.iv = NULL; // IV is not needed in ECB mode
	param.inWordLen = sizeof(plain) / sizeof(uint32_t);
	param.keyMode = TDES_2KEY;
	param.Mode = DES_ECB;
	param.En_De = DES_ENC;

	// encrypt data
	if (DES_Init_OK != DES_Init(&param)) {
		log_error("DES_Init failed.\n");
		return -1;
	}
	if (DES_Crypto_OK != DES_Crypto(&param)) {
		DES_Close();
		log_error("DES_Crypto failed\n");
		return -1;
	}
	DES_Close();

	log_info("3DES 2KEY ECB encrypt:\n");
	log_info("key = ");
	DumpBytes(key, sizeof(key));
	log_info("\n");
	log_info("plain = ");
	DumpBytes(plain, sizeof(plain));
	log_info("\n");
	log_info("cipher = ");
	DumpBytes(cipher, sizeof(cipher));
	log_info("\n");

	param.in = (uint32_t*) cipher;
	param.out = (uint32_t*) plainOut;
	param.En_De = DES_DEC;

	// decrypt data
	if (DES_Init_OK != DES_Init(&param)) {
		log_error("DES_Init failed.\n");
		return -1;
	}
	if (DES_Crypto_OK != DES_Crypto(&param)) {
		DES_Close();
		log_error("DES_Crypto failed\n");
		return -1;
	}
	DES_Close();

	log_info("3DES 2KEY ECB decrypt:\n");
	log_info("plainOut = ");
	DumpBytes(plainOut, sizeof(plainOut));
	log_info("\n");
	if (memcmp(plain, plainOut, sizeof(plain)) != 0) {
		log_error("DES decrypt result do not equal plain data.\n");
		return -1;
	}
	return 0;
}

int demo_3des_2key_cbc() {
	__attribute__ ((aligned (4))) uint8_t key[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9,
			10, 11, 12, 13, 14, 15, 16 };
	__attribute__ ((aligned (4))) uint8_t plain[16] = { 0x11, 0x22, 0x33, 0x44,
			0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF,
			0x00 };
	__attribute__ ((aligned (4))) uint8_t cipher[16];
	__attribute__ ((aligned (4))) uint8_t plainOut[16];
	__attribute__ ((aligned (4))) uint8_t iv[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };

	DES_PARM param = { 0 };

	// des cbc mode
	param.in = (uint32_t*) plain;
	param.out = (uint32_t*) cipher;
	param.key = (uint32_t*) key;
	param.iv = (uint32_t *)iv;
	param.inWordLen = sizeof(plain) / sizeof(uint32_t);
	param.keyMode = TDES_2KEY;
	param.Mode = DES_CBC;
	param.En_De = DES_ENC;

	// encrypt data
	if (DES_Init_OK != DES_Init(&param)) {
		log_error("DES_Init failed.\n");
		return -1;
	}
	if (DES_Crypto_OK != DES_Crypto(&param)) {
		DES_Close();
		log_error("DES_Crypto failed\n");
		return -1;
	}
	DES_Close();

	log_info("3DES 2KEY CBC encrypt:\n");
	log_info("key = ");
	DumpBytes(key, sizeof(key));
	log_info("\n");
	log_info("plain = ");
	DumpBytes(plain, sizeof(plain));
	log_info("\n");
	log_info("cipher = ");
	DumpBytes(cipher, sizeof(cipher));
	log_info("\n");

	param.in = (uint32_t*) cipher;
	param.out = (uint32_t*) plainOut;
	param.En_De = DES_DEC;

	// decrypt data
	if (DES_Init_OK != DES_Init(&param)) {
		log_error("DES_Init failed.\n");
		return -1;
	}
	if (DES_Crypto_OK != DES_Crypto(&param)) {
		DES_Close();
		log_error("DES_Crypto failed\n");
		return -1;
	}
	DES_Close();

	log_info("3DES 2KEY CBC decrypt:\n");
	log_info("plainOut = ");
	DumpBytes(plainOut, sizeof(plainOut));
	log_info("\n");
	if (memcmp(plain, plainOut, sizeof(plain)) != 0) {
		log_error("DES decrypt result do not equal plain data.\n");
		return -1;
	}
	return 0;
}

int demo_3des_3key_ecb() {
	__attribute__ ((aligned (4))) uint8_t key[24] = { 1, 2, 3, 4, 5, 6, 7, 8, 9,
			10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24 };
	__attribute__ ((aligned (4))) uint8_t plain[16] = { 0x11, 0x22, 0x33, 0x44,
			0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF,
			0x00 };
	__attribute__ ((aligned (4))) uint8_t cipher[16];
	__attribute__ ((aligned (4))) uint8_t plainOut[16];

	DES_PARM param = { 0 };

	// des ecb mode
	param.in = (uint32_t*) plain;
	param.out = (uint32_t*) cipher;
	param.key = (uint32_t*) key;
	param.iv = NULL; // IV is not needed in ECB mode
	param.inWordLen = sizeof(plain) / sizeof(uint32_t);
	param.keyMode = TDES_3KEY;
	param.Mode = DES_ECB;
	param.En_De = DES_ENC;

	// encrypt data
	if (DES_Init_OK != DES_Init(&param)) {
		log_error("DES_Init failed.\n");
		return -1;
	}
	if (DES_Crypto_OK != DES_Crypto(&param)) {
		DES_Close();
		log_error("DES_Crypto failed\n");
		return -1;
	}
	DES_Close();

	log_info("3DES 3KEY ECB encrypt:\n");
	log_info("key = ");
	DumpBytes(key, sizeof(key));
	log_info("\n");
	log_info("plain = ");
	DumpBytes(plain, sizeof(plain));
	log_info("\n");
	log_info("cipher = ");
	DumpBytes(cipher, sizeof(cipher));
	log_info("\n");

	param.in = (uint32_t*) cipher;
	param.out = (uint32_t*) plainOut;
	param.En_De = DES_DEC;

	// decrypt data
	if (DES_Init_OK != DES_Init(&param)) {
		log_error("DES_Init failed.\n");
		return -1;
	}
	if (DES_Crypto_OK != DES_Crypto(&param)) {
		DES_Close();
		log_error("DES_Crypto failed\n");
		return -1;
	}
	DES_Close();

	log_info("3DES 3KEY ECB decrypt:\n");
	log_info("plainOut = ");
	DumpBytes(plainOut, sizeof(plainOut));
	log_info("\n");
	if (memcmp(plain, plainOut, sizeof(plain)) != 0) {
		log_error("DES decrypt result do not equal plain data.\n");
		return -1;
	}
	return 0;
}

int demo_3des_3key_cbc() {
	__attribute__ ((aligned (4))) uint8_t key[24] = { 1, 2, 3, 4, 5, 6, 7, 8, 9,
			10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24 };
	__attribute__ ((aligned (4))) uint8_t plain[16] = { 0x11, 0x22, 0x33, 0x44,
			0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF,
			0x00 };
	__attribute__ ((aligned (4))) uint8_t cipher[16];
	__attribute__ ((aligned (4))) uint8_t plainOut[16];
	__attribute__ ((aligned (4))) uint8_t iv[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };

	DES_PARM param = { 0 };

	// des cbc mode
	param.in = (uint32_t*) plain;
	param.out = (uint32_t*) cipher;
	param.key = (uint32_t*) key;
	param.iv = (uint32_t *)iv;
	param.inWordLen = sizeof(plain) / sizeof(uint32_t);
	param.keyMode = TDES_3KEY;
	param.Mode = DES_CBC;
	param.En_De = DES_ENC;

	// encrypt data
	if (DES_Init_OK != DES_Init(&param)) {
		log_error("DES_Init failed.\n");
		return -1;
	}
	if (DES_Crypto_OK != DES_Crypto(&param)) {
		DES_Close();
		log_error("DES_Crypto failed\n");
		return -1;
	}
	DES_Close();

	log_info("3DES 3KEY CBC encrypt:\n");
	log_info("key = ");
	DumpBytes(key, sizeof(key));
	log_info("\n");
	log_info("plain = ");
	DumpBytes(plain, sizeof(plain));
	log_info("\n");
	log_info("cipher = ");
	DumpBytes(cipher, sizeof(cipher));
	log_info("\n");

	param.in = (uint32_t*) cipher;
	param.out = (uint32_t*) plainOut;
	param.En_De = DES_DEC;

	// decrypt data
	if (DES_Init_OK != DES_Init(&param)) {
		log_error("DES_Init failed.\n");
		return -1;
	}
	if (DES_Crypto_OK != DES_Crypto(&param)) {
		DES_Close();
		log_error("DES_Crypto failed\n");
		return -1;
	}
	DES_Close();

	log_info("3DES 3KEY CBC decrypt:\n");
	log_info("plainOut = ");
	DumpBytes(plainOut, sizeof(plainOut));
	log_info("\n");
	if (memcmp(plain, plainOut, sizeof(plain)) != 0) {
		log_error("DES decrypt result do not equal plain data.\n");
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

	ret = demo_des_1key_ecb();
	if (ret != 0) {
		log_error("demo_des_1key_ecb fail.\n");
	}
	ret = demo_des_1key_cbc();
	if (ret != 0) {
		log_error("demo_des_1key_cbc fail.\n");
	}

	ret = demo_3des_2key_ecb();
	if (ret != 0) {
		log_error("demo_3des_2key_ecb fail.\n");
	}
	ret = demo_3des_2key_cbc();
	if (ret != 0) {
		log_error("demo_3des_2key_cbc fail.\n");
	}
	ret = demo_3des_3key_ecb();
	if (ret != 0) {
		log_error("demo_3des_3key_ecb fail.\n");
	}
	ret = demo_3des_3key_cbc();
	if (ret != 0) {
		log_error("demo_3des_3key_cbc fail.\n");
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
