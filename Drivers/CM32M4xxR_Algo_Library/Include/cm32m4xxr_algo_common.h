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
 * @file cm32m4xxr_algo_common.h
 * @author CMIOT Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */
#ifndef __CM32M4xxR_ALGO_COMMON_H__
#define __CM32M4xxR_ALGO_COMMON_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup CM32M4xxR_Algorithm_Library
 * @{
 */
 
enum{
	Cpy_OK		= 0,	/* Copy success */
	SetZero_OK  = 0,	/* Set zero success */
	XOR_OK		= 0,	/* XOR success */
	Reverse_OK	= 0,	/* Reverse success */
	Cmp_EQUAL	= 0,	/* Two big number are equal */
	Cmp_UNEQUAL	= 1,	/* Two big number are not equal */

};

/**
 * @brief disturb the sequence order
 * @param[in] order pointer to the sequence to be disturbed
 * @param[in] rand pointer to random number
 * @param[in] the length of order
 * @return RandomSort_OK:  disturb order success;  Others: disturb order fail;
 * @note 
 */
uint32_t RandomSort(uint8_t *order, const uint8_t *rand, uint32_t len);

/**
 * @brief Copy data by byte
 * @param[in]  dst pointer to destination data
 * @param[in]  src pointer to source data
 * @param[in]  byte length 
 * @return Cpy_OK: success; others: fail.
 * @note 1. dst and  src cannot be same
 */
uint32_t Cpy_U8(uint8_t *dst, uint8_t *src, uint32_t byteLen);

/**
 * @brief Copy data by word
 * @param[in]  dst pointer to destination data
 * @param[in]  src pointer to source data
 * @param[in]  word length 
 * @return Cpy_OK: success; others: fail.
 * @note 1. dst and  src must be aligned by word
 */
uint32_t Cpy_U32(uint32_t *dst, const uint32_t *src, uint32_t wordLen);

 /**
 * @brief XOR
 * @param[in] a pointer to one data to be XORed
 * @param[in] b pointer to another data to be XORed
 * @param[in] the length of order
 * @return XOR_OK:  operation success;  Others: operation fail;
 * @note 
 */
uint32_t XOR_U8(uint8_t *a, uint8_t *b, uint8_t *c, uint32_t byteLen);

 /**
 * @brief XORed two u32 arrays
 * @param[in] a pointer to one data to be XORed
 * @param[in] b pointer to another data to be XORed
 * @param[in] the length of order
 * @return XOR_OK:  operation success;  Others: operation fail;
 * @note 
 */
uint32_t XOR_U32(uint32_t *a,uint32_t *b,uint32_t *c,uint32_t wordLen);

/**
 * @brief set zero by byte
 * @param[in] dst pointer to the address to be set zero 
 * @param[in]  byte length 
 * @return SetZero_OK: success; others: fail.
 * @note 
 */
uint32_t SetZero_U8(uint8_t *dst, uint32_t byteLen);

/**
 * @brief set zero by word
 * @param[in] dst pointer to the address to be set zero 
 * @param[in]  word length 
 * @return SetZero_OK: success; others: fail.
 * @note 
 */
uint32_t SetZero_U32(uint32_t *dst, uint32_t wordLen);

/**
 * @brief reverse byte order of every word, the words stay the same
 * @param[in]  dst pointer to the destination address
 * @param[in]  src pointer to the source address 
 * @param[in]  word length 
 * @return Reverse_OK: success; others: fail.
 * @note 1.dst and src can be same
 */
uint32_t ReverseBytesInWord_U32(uint32_t *dst, const uint32_t *src, uint32_t wordLen);

/**
 * @brief compare two big number
 * @param[in] a pointer to one big number
 * @param[in] word length of a
 * @param[in] b pointer to another big number
 * @param[in]  word length of b
 * @return Cmp_UNEQUAL:a!=b;Cmp_EQUAL: a==b.
 * 
 */
int32_t Cmp_U32(const uint32_t *a, uint32_t aWordLen, const uint32_t *b, uint32_t bWordLen);

/**
 * @brief compare two big number
 * @param[in] a pointer to one big number
 * @param[in] word length of a
 * @param[in] b pointer to another big number
 * @param[in]  word length of b
 * @return Cmp_UNEQUAL:a!=b;Cmp_EQUAL: a==b.
 * 
 */
int32_t Cmp_U8(const uint8_t *a, uint32_t aByteLen, const uint8_t *b, uint32_t bByteLen);

#ifdef __cplusplus
}
#endif

#endif

