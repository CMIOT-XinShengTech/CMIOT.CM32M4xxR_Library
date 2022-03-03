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
 * @file flash.c
 * @author CMIOT Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */

/** @addtogroup CM32M4xxR_IAP_Bootloader
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "flash.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  clear flash errors
 * @param  None
 * @retval None
 */
void FLASH_Init(void) {
	/* Unlock the Program memory */
	FLASH_Unlock();

	/* Clear all FLASH flags */
	FLASH_ClearFlag(
			FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR
					| FLASH_FLAG_EVERR | FLASH_FLAG_PVERR);
	/* Unlock the Program memory */
	FLASH_Lock();
}

/**
 * @brief  This function does an erase of all user flash area
 * @retval FLASHIF_OK : user flash area successfully erased
 *         FLASHIF_ERASEKO : error occurred
 */
uint32_t FLASH_EraseUser() {
	uint32_t pageAddr = 0;

	/* Unlock the Flash to enable the flash control register access *************/
	FLASH_Unlock();

	/* Get the number of page to  erase */

	for (pageAddr = USER_FLASH_BASE;
			pageAddr < USER_FLASH_BASE + USER_FLASH_SIZE;
			pageAddr += FLASH_PAGE_SIZE)
					{
		if (FLASH_COMPL != FLASH_EraseOnePage(pageAddr)) {
			FLASH_Lock();
			return FLASH_ERASE_ERROR;
		}
	}

	/* Lock the Flash to disable the flash control register access (recommended
	 to protect the FLASH memory against possible unwanted operation) *********/
	FLASH_Lock();

	return FLASH_OK;
}

/* Public functions ---------------------------------------------------------*/
/**
 * @brief  This function writes a data buffer in flash (data are 32-bit aligned).
 * @note   After writing data buffer, the flash content is checked.
 * @param  addr: start address for target location
 * @param  data: pointer on buffer with data to write
 * @param  length: length of data buffer (unit is 32-bit word)
 * @retval uint32_t 0: Data successfully written to Flash memory
 *         1: Error occurred while writing data in Flash memory
 *         2: Written Data in flash memory is different from expected one
 */
uint32_t FLASH_WriteUser(uint32_t addr, uint32_t *data,
		uint32_t length) {
	uint32_t status = FLASH_OK;
	uint32_t i = 0;

	/* Unlock the Flash to enable the flash control register access *************/
	FLASH_Unlock();

	/* DataLength must be a multiple of 32 bit */
	for (i = 0;
			(i < length) && (addr <= (USER_FLASH_BASE + USER_FLASH_SIZE - 4));
			i++) {

		if (FLASH_ProgramWord(addr, *((data + i))) == FLASH_COMPL) {
			/* Check the written value */
			if (*(uint32_t*) addr != *(data + i)) {
				/* Flash content doesn't match SRAM content */
				status = FLASH_WRITING_ERROR;
				break;
			}
			/* Increment FLASH destination address */
			addr += 4;
		} else {
			/* Error occurred while writing data in Flash memory */
			status = FLASH_WRITING_ERROR;
			break;
		}
	}

	/* Lock the Flash to disable the flash control register access (recommended
	 to protect the FLASH memory against possible unwanted operation) *********/
	FLASH_Lock();

	return status;
}

/**
 * @}
 */
