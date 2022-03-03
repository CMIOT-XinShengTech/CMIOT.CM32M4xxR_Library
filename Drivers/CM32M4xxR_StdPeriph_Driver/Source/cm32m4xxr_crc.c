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
 * @file cm32m4xxr_crc.c
 * @author CMIOT Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */
#include "nuclei_sdk_soc.h"

/** @addtogroup CM32M4xxR_StdPeriph_Driver
 * @{
 */

/** @defgroup CRC CRC
 * @brief CRC driver modules
 * @{
 */

#ifdef	DRIVER_MODULE_ENABLED_CRC

/** @defgroup CRC_Exported_Functions CRC Exported Functions
 * @{
 */

/**
 * @brief Resets the CRC Data register (CRC32DAT).
 */
void CRC32_ResetCrc(void)
{
    /* Reset CRC generator */
    CRC->CRC32CTRL = CRC_CRC32CTRL_RESET;
}

/**
 * @brief Computes the 32-bit CRC of a given data word(32-bit).
 * @param Data data word(32-bit) to compute its CRC
 * @retval 32-bit CRC
 */
uint32_t CRC32_CalcCrc(uint32_t Data)
{
    CRC->CRC32DAT = Data;

    return (CRC->CRC32DAT);
}

/**
 * @brief Computes the 32-bit CRC of a given buffer of data word(32-bit).
 * @param pBuffer pointer to the buffer containing the data to be computed
 * @param BufferLength length of the buffer to be computed
 * @retval 32-bit CRC
 */
uint32_t CRC32_CalcBufCrc(uint32_t pBuffer[], uint32_t BufferLength)
{
    uint32_t index = 0;

	assert_param(pBuffer != 0);

    for (index = 0; index < BufferLength; index++)
    {
        CRC->CRC32DAT = pBuffer[index];
    }
	
    return (CRC->CRC32DAT);
}

/**
 * @brief  Returns the current CRC value.
 * @retval 32-bit CRC
 */
uint32_t CRC32_GetCrc(void)
{
    return (CRC->CRC32DAT);
}

/**
 * @brief Stores a 8-bit data in the Independent Data(ID) register.
 * @param IDValue 8-bit value to be stored in the ID register
 */
void CRC32_SetIDat(uint8_t IDValue)
{
    CRC->CRC32IDAT = IDValue;
}

/**
 * @brief  Returns the 8-bit data stored in the Independent Data(ID) register
 * @retval 8-bit value of the ID register
 */
uint8_t CRC32_GetIDat(void)
{
    return (CRC->CRC32IDAT);
}

/**
 * @brief Set little/big endian format of the 8-bit data to compute its CRC
 */
void CRC16_SetEndianFmt(uint32_t EndianFormat)
{
	assert_param(IS_CRC_ENDIAN_FMT(EndianFormat));

	if (EndianFormat == CRC_LITTLE_ENDIAN_FMT)
	{
    	CRC->CRC16CTRL |= CRC_CRC16CTRL_ENDHL;
	}
	else
	{
    	CRC->CRC16CTRL &= ~CRC_CRC16CTRL_ENDHL;
	}
}

/**
 * @brief Clear CRC value in CRC result register(CRC16D)
 */
void CRC16_SetCleanEnable(void)
{
	CRC->CRC16CTRL |= CRC_CRC16CTRL_CLR;
}

/**
 * @brief Set the data byte value to compute its CRC
 * @param Data data byte(8-bit) to compute its CRC
 */
void CRC16_SetCrc(uint8_t Data)
{
    CRC->CRC16DAT = Data;
}

/**
 * @brief  Returns the current CRC value.
 * @retval 16-bit CRC
 */
uint16_t CRC16_GetCrc(void)
{
    return (CRC->CRC16D);
}

/**
 * @brief Set initial LRC value
 * @param Data initial LRC value
 */
void CRC16_SetLRC(uint8_t Data)
{
    CRC->LRC = Data;
}

/**
 * @brief  Returns the current LRC value.
 * @retval 8-bit LRC
 */
uint8_t CRC16_GetLRC(void)
{
    return (CRC->LRC);
}

/**
 * @brief Computes the 16-bit CRC of a given buffer of data byte(8-bit).
 * @param pBuffer pointer to the buffer containing the data to be computed
 * @param BufferLength length of the buffer to be computed
 * @retval 16-bit CRC
 */
uint16_t CRC16_CalcBufCrc(uint8_t pBuffer[], uint32_t BufferLength)
{
    uint32_t index = 0;

    for (index = 0; index < BufferLength; index++)
    {
        CRC->CRC16DAT = pBuffer[index];
    }
	
    return (CRC->CRC16D);
}

/**
 * @brief Computes the 16-bit CRC of a given data byte(8-bit).
 * @param Data data byte(8-bit) to compute its CRC
 * @retval 16-bit CRC
 */
uint16_t CRC16_CalcCRC(uint8_t Data)
{
    CRC->CRC16DAT = Data;

    return (CRC->CRC16D);
}

/**
 * @}
 */

#endif

/**
 * @}
 */

/**
 * @}
 */
