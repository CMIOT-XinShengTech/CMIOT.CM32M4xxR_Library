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
 * @file flash.h
 * @author CMIOT Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FLASH_H
#define __FLASH_H

/* Includes ------------------------------------------------------------------*/
#include "nuclei_sdk_soc.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/


/* Error code */
enum 
{
  FLASH_OK = 0,
  FLASH_ERASE_ERROR,
  FLASH_WRITING_ERROR,
  FLASH_PROTECTION_ERRROR
};


/* Define the address from where user application will be loaded.
   Note: this area is reserved for the IAP code                  */

//#define FLASH_BASE    			(0x08000000)
#define FLASH_PAGE_SIZE       	((uint16_t) 0x800)	/* 2K bytes per page */
#define FLASH_SIZE       		((uint32_t) 0x80000)	/* 512K bytes  */
#define FLASH_PAGE_NUM  		((uint16_t)(FLASH_SIZE / FLASH_PAGE_SIZE))

#define BOOT_FLASH_BASE			FLASH_BASE
#define BOOT_FLASH_SIZE			0x10000

#define USER_FLASH_BASE			(BOOT_FLASH_BASE + BOOT_FLASH_SIZE)
#define USER_FLASH_SIZE			(FLASH_SIZE - BOOT_FLASH_SIZE)

/* Exported functions ------------------------------------------------------- */
void FLASH_Init(void);
uint32_t FLASH_EraseUser();
uint32_t FLASH_WriteUser(uint32_t destination, uint32_t *p_source, uint32_t length);

#endif  /* __FLASH_IF_H */

