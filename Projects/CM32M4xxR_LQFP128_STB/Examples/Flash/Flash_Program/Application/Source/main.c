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
#include "log.h"

#include <string.h>

/** @addtogroup CM32M4xxR_StdPeriph_Examples
 * @{
 */

/**
 *  Flash_Program
 */

#define FLASH_PAGE_SIZE       	((uint16_t) 0x800)	/* 2K bytes per page */
#define FLASH_WRITE_START_ADDR	((uint32_t) 0x08010000)
#define FLASH_WRITE_END_ADDR  	((uint32_t) 0x08018000)

/**
 * @brief  Main function.
 */
int main(void)
{
    uint32_t Counter_Num = 0;
    uint32_t Erase_Data  = 0xCDEF89AB;

    /* Log initialize */
    log_init();

    log_info("Flash Program Test Start\r\n");

    /* Program FLASH */
    /* Unlocks the FLASH Program Erase Controller */
    FLASH_Unlock();

    /* Erase */
    if (FLASH_COMPL != FLASH_EraseOnePage(FLASH_WRITE_START_ADDR))
    {
        while(1)
        {
        	log_info("Flash EraseOnePage Error. Please Deal With This Error Promptly\r\n");
        }
    }

    /* Program */
    for (Counter_Num = 0; Counter_Num < FLASH_PAGE_SIZE; Counter_Num += 4)
    {
        if (FLASH_COMPL != FLASH_ProgramWord(FLASH_WRITE_START_ADDR + Counter_Num, Erase_Data))
        {
            while(1)
            {
            	log_info("Flash ProgramWord Error. Please Deal With This Error Promptly\r\n");
            }
        }
    }

    /* Locks the FLASH Program Erase Controller */
    FLASH_Lock();

    /* Check */
    for (Counter_Num = 0; Counter_Num < FLASH_PAGE_SIZE; Counter_Num += 4)
    {
        if (Erase_Data != (*(__IO uint32_t*)(FLASH_WRITE_START_ADDR + Counter_Num)))
        {
        	log_info("Flash Program Test Failed\r\n");
            break;
        }
    }

    log_info("Flash Program Test End\r\n");

    while (1)
    {
    }
}

/**
 * @}
 */

