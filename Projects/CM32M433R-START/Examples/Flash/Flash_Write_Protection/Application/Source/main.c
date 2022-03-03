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

#include "main.h"
#include "log.h"

#include <string.h>

/** @addtogroup CM32M4xxR_StdPeriph_Examples
 * @{
 */

/**
 *  Flash_Write_Protection
 */

#define FLASH_PAGE_SIZE       	((uint16_t) 0x800)
#define FLASH_WRITE_START_ADDR	((uint32_t) 0x08010000)
#define FLASH_WRITE_END_ADDR  	((uint32_t) 0x08012000)

#define FLASH_PROTECTED_PAGES	FLASH_WRP_Pages32to33	/* FLASH_WRITE_START_ADDR ~ FLASH_WRITE_END_ADDR */

/* Uncomment this line to Enable Write Protection */
#define WRITE_PROTECTION_ENABLE

/* Uncomment this line to Disable Write Protection */
//#define WRITE_PROTECTION_DISABLE

/**
 * @brief  Main program.
 */
int main(void)
{
    uint8_t Test_Result 	= 0;
    uint32_t WRPR_Value 	= 0xFFFFFFFF;
    uint32_t ProtectedPages = 0;
    uint32_t ProgramData 	= 0xCDEF89AB;

    /* Log initialize */
    log_init();

    log_info("Flash Write Protection Test Start\r\n");

    /* Write Protection */
    /* Unlocks the FLASH Program Erase Controller */
    FLASH_Unlock();

    /* Get pages already write protection */
    WRPR_Value = FLASH_GetWriteProtectionOB();

#ifdef WRITE_PROTECTION_DISABLE

    log_info("Write Protection Disable\r\n");

    /* Get pages already write protected */
    ProtectedPages = ~(WRPR_Value | FLASH_PROTECTED_PAGES);

    /* Check if desired pages are already write protected */
    if ((WRPR_Value | (~FLASH_PROTECTED_PAGES)) != 0xFFFFFFFF)
    {
        /* Erase all the option Bytes */
        FLASH_EraseOB();

        /* Check if there is write protected pages */
        if (ProtectedPages != 0x0)
        {
            /* Restore write protected pages */
            FLASH_EnWriteProtection(ProtectedPages);
        }

        /* Generate System Reset to load the new option byte values */
        SysTimer_SoftwareReset();
    }
    else
    {
        /* FLASH Write Protection Test */
    	log_info("Flash Page Erase/Program\r\n");

        /* Clear All pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);

        /* Erase */
        if (FLASH_ERR_WRP == FLASH_EraseOnePage(FLASH_WRITE_START_ADDR))
        {
        	/* Test Fail */
            Test_Result = FAILED;
        }
        else
        {
            /* Clear All pending flags */
            FLASH_ClearFlag(FLASH_STS_CLRFLAG);

            /* Program */
            if (FLASH_ERR_WRP == FLASH_ProgramWord(FLASH_WRITE_START_ADDR, ProgramData))
            {
            	/* Test Fail */
                Test_Result = FAILED;
            }
            else
            {
                /* Check */
                if (ProgramData == (*(__IO uint32_t*)FLASH_WRITE_START_ADDR))
                {
                    /* Test passed */
                    Test_Result = PASSED;
                }
                else
                {
                    /* Test failed */
                    Test_Result = FAILED;
                }
            }
        }
    }

#elif defined WRITE_PROTECTION_ENABLE

    log_info("Write Protection Enable\r\n");

    /* Set write protected pages */
    ProtectedPages = (~WRPR_Value) | FLASH_PROTECTED_PAGES;

    /* Check if desired pages are not yet write protected */
    if (((~WRPR_Value) & FLASH_PROTECTED_PAGES) != FLASH_PROTECTED_PAGES)
    {
        /* Erase all the option Bytes */
        FLASH_EraseOB();

        /* Erase */
        if (FLASH_COMPL != FLASH_EraseOnePage(FLASH_WRITE_START_ADDR))
        {
        	log_info("Flash Page Erase error\r\n");
        }

        /* Enable the pages write protection */
        FLASH_EnWriteProtection(ProtectedPages);

        /* Generate System Reset to load the new option byte values */
        SysTimer_SoftwareReset();
    }
    else
    {
        /* FLASH Write Protection Test */
    	log_info("Flash Page Erase/Program\r\n");

        /* Clear All pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);

        /* Erase */
        if (FLASH_ERR_WRP == FLASH_EraseOnePage(FLASH_WRITE_START_ADDR))
        {
            /* Clear All pending flags */
            FLASH_ClearFlag(FLASH_STS_CLRFLAG);

            /* Program */
            if (FLASH_ERR_WRP == FLASH_ProgramWord(FLASH_WRITE_START_ADDR, ProgramData))
            {
                /* Check */
                if (ProgramData == (*(__IO uint32_t*)FLASH_WRITE_START_ADDR))
                {
                    /* Test Fail */
                    Test_Result = FAILED;
                }
                else
                {
                    /* Test PASSED */
                    Test_Result = PASSED;
                }
            }
            else
            {
            	/* Test Fail */
                Test_Result = FAILED;
            }
        }
        else
        {
        	/* Test Fail */
            Test_Result = FAILED;
        }
    }

#endif

    if (Test_Result == FAILED)
    {
    	log_info("Test_Result = FAILED\r\n");
    }
    else
    {
    	log_info("Test_Result = PASSED\r\n");
    }

    while (1)
    {
    }
}


/**
 * @}
 */
