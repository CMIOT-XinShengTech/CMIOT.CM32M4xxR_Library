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
 * @file serial.c
 * @author CMIOT Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */
/** @addtogroup CM32M4xxR_IAP_Bootloader
  * @{
  */
#include "serial.h"

void serial_flushdr(void) {
	USART_ReceiveData(UART5);
}

/**
 * @brief  Receive bytes from Terminal
 * @param  data	receive buffer
 * @param  len	Expected length of reception
 * @param  timeout	Receive timeout(ms)
 * @retval The reception is completed and the return is successful, otherwise the return fails.
 */
ErrorStatus serial_receive(uint8_t *data, uint32_t len, uint32_t timeout) {
	uint64_t start_tick = SysTimer_GetLoadValue();
	uint32_t i = 0;
	for (i = 0; i < len; i++) {
		while (USART_GetFlagStatus(UART5, USART_FLAG_RXDNE) == RESET) {
			if (timeout != 0xFFFFFFFF
					&& (SysTimer_GetLoadValue() - start_tick)
							> timeout * (SystemCoreClock / 1000)) {
				return ERROR;
			}
		}
		data[i] = USART_ReceiveData(UART5);
	}
	return SUCCESS;
}

/**
 * @brief  Print a string on the HyperTerminal
 * @param  str: The string to be printed
 * @retval None
 */
void serial_putstring(uint8_t *str) {

	while (*str != '\0') {
		USART_SendData(UART5, (uint8_t) *str++);

		/* Loop until the end of transmission */
		while (USART_GetFlagStatus(UART5, USART_FLAG_TXDE) == RESET) {

		}
	}

}

/**
 * @brief  Transmit a byte to the HyperTerminal
 * @param  param The byte to be sent
 */
void serial_transmitbyte(uint8_t param) {
	USART_SendData(UART5, (uint8_t) param);

	/* Loop until the end of transmission */
	while (USART_GetFlagStatus(UART5, USART_FLAG_TXDE) == RESET) {

	}
}

/**
 * @brief  Transmit a byte array to the HyperTerminal
 * @param  data The byte array to be sent
 * @param  len The data length to be sent
 */
void serial_transmit(uint8_t *data, uint32_t len) {
	uint32_t i = 0;
	for (i = 0; i < len; i++) {
		USART_SendData(UART5, (uint8_t) data[i]);

		/* Loop until the end of transmission */
		while (USART_GetFlagStatus(UART5, USART_FLAG_TXDE) == RESET) {

		}
	}

}
