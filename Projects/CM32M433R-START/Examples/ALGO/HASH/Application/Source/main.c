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
#include "cm32m4xxr_hash.h"
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

#define HASH_TEST_MSG "Hello!"

static const uint8_t md5_result[16] = { 0x95, 0x2D, 0x2C, 0x56, 0xD0, 0x48,
		0x59, 0x58, 0x33, 0x67, 0x47, 0xBC, 0xDD, 0x98, 0x59, 0x0D };
static const uint8_t sha1_result[20] = { 0x69, 0x34, 0x2C, 0x5C, 0x39, 0xE5,
		0xAE, 0x5F, 0x00, 0x77, 0xAE, 0xCC, 0x32, 0xC0, 0xF8, 0x18, 0x11, 0xFB,
		0x81, 0x93 };
static const uint8_t sha224_result[28] = { 0xE2, 0x50, 0xE4, 0x33, 0x99, 0x55,
		0xF0, 0x22, 0x94, 0xCE, 0xB6, 0x23, 0x86, 0x0A, 0xE5, 0xF9, 0x37, 0x4B,
		0x93, 0xF4, 0x33, 0x5B, 0xD6, 0x05, 0xAD, 0xA5, 0x11, 0x3A };
static const uint8_t sha256_result[32] = { 0x33, 0x4D, 0x01, 0x6F, 0x75, 0x5C,
		0xD6, 0xDC, 0x58, 0xC5, 0x3A, 0x86, 0xE1, 0x83, 0x88, 0x2F, 0x8E, 0xC1,
		0x4F, 0x52, 0xFB, 0x05, 0x34, 0x58, 0x87, 0xC8, 0xA5, 0xED, 0xD4, 0x2C,
		0x87, 0xB7 };

void hash(const HASH_ALG *hashAlg, char *msg, uint8_t *result) {
	HASH_CTX ctx;
	ctx.hashAlg = hashAlg;
	ctx.sequence = HASH_SEQUENCE_FALSE;
	if (HASH_Init_OK != HASH_Init(&ctx)) {
		log_error("HASH_Init failed.\n");
		return;
	}
	if (HASH_Start_OK != HASH_Start(&ctx)) {
		log_error("HASH_Start failed.\n");
		return;
	}
	if (HASH_Update_OK != HASH_Update(&ctx, (uint8_t*) msg, strlen(msg))) {
		log_error("HASH_Update failed.\n");
		return;
	}
	if (HASH_Complete_OK != HASH_Complete(&ctx, result)) {
		log_error("HASH_Complete failed.\n");
		return;
	}
	HASH_Close();
}

int md5() {
	uint8_t result[16];
	hash(HASH_ALG_MD5, HASH_TEST_MSG, result);
	log_info("MD5 of message `%s` is: ", HASH_TEST_MSG);
	DumpBytes(result, 16);
	log_info("\n");

	if (memcmp(result, md5_result, 16)) {
		log_error("md5 result error\n");
		return -1;
	}
	return 0;
}

int sha1() {
	uint8_t result[20];
	hash(HASH_ALG_SHA1, HASH_TEST_MSG, result);
	log_info("SHA1 of message `%s` is: ", HASH_TEST_MSG);
	DumpBytes(result, 20);
	log_info("\n");
	if (memcmp(result, sha1_result, 20)) {
		log_error("sha1 result error\n");
		return -1;
	}
	return 0;
}

int sha224() {
	uint8_t result[28];
	hash(HASH_ALG_SHA224, HASH_TEST_MSG, result);
	log_info("SHA224 of message `%s` is: ", HASH_TEST_MSG);
	DumpBytes(result, 28);
	log_info("\n");

	if (memcmp(result, sha224_result, 28)) {
		log_error("sha224 result error\n");
		return -1;
	}
	return 0;
}

int sha256() {
	uint8_t result[32];
	hash(HASH_ALG_SHA256, HASH_TEST_MSG, result);
	log_info("SHA256 of message `%s` is: ", HASH_TEST_MSG);
	DumpBytes(result, 32);
	log_info("\n");

	if (memcmp(result, sha256_result, 32)) {
		log_error("sha256 result error\n");
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

	ret = md5();
	if (ret != 0) {
		log_error("md5 error");
	}

	ret = sha1();
	if (ret != 0) {
		log_error("sha1 error");
	}

	ret = sha224();
	if (ret != 0) {
		log_error("sha224 error");
	}

	ret = sha256();
	if (ret != 0) {
		log_error("sha256 error");
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
