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
 *  Flash_Read_Protection
 */

#define FLASH_WRITE_ADDR ((uint32_t)0x08000000)

__IO uint32_t TimingDelay = 0;

/**
 * @brief  Inserts a delay time.
 * @param nTime specifies the delay time length, in milliseconds.
 */
void Delayms(__IO uint32_t nTime)
{
    TimingDelay = nTime;
    while (TimingDelay != 0);
}

/**
 * @brief  Main program.
 */
int main(void)
{
    FLASH_STS status = FLASH_COMPL;
    uint8_t Test_Result = 0;
    uint32_t ProgramData = 0xCDEF89AB;

    /* Log initialize */
    log_init();

    log_info("Flash Read Protection Test Start\r\n");

    /* Enable global interrupt */
    __enable_irq();

    /* Use core_aon_clk as systimer clock */
    SysTimer_SetControlValue(SysTimer_GetControlValue() | SysTimer_MTIMECTL_CLKSRC_Msk);

    /* Setup SysTick Timer for 1 msec interrupts  */
    if (SysTick_Config(SystemCoreClock / 1000))
    {
        /* Capture error */
        while (1)
            ;
    }

    if (FLASH_GetReadOutProtectionSTS() == RESET)
    {
		log_info("Change Flash Read Protection L0->L1.\r\n");

		/* Unlocks the FLASH Program Erase Controller */
		FLASH_Unlock();

		/* Change Flash Read Protection to L1 */
		status = FLASH_ReadOutProtectionL1(ENABLE);
		if (status == FLASH_COMPL)
		{
			/* Generate System Reset to load the new option byte values */
			SysTimer_SoftwareReset();
		}

		/* Test Fail */
		Test_Result = FAILED;

    }
	else
	{
		log_info("Flash Read Protection L1.\r\n");

		/* Unlocks the FLASH Program Erase Controller */
		FLASH_Unlock();

		/* Clear All pending flags */
		FLASH_ClearFlag(FLASH_STS_CLRFLAG);

		/* Erase */
		if (FLASH_ERR_WRP == FLASH_EraseOnePage(FLASH_WRITE_ADDR))
		{
			/* Clear All pending flags */
			FLASH_ClearFlag(FLASH_STS_CLRFLAG);

			/* Program */
			if (FLASH_ERR_WRP == FLASH_ProgramWord(FLASH_WRITE_ADDR, ProgramData))
			{
				/* Check */
				if (ProgramData == (*(__IO uint32_t*)FLASH_WRITE_ADDR))
				{
					/* Test Fail */
					Test_Result = FAILED;
				}
				else
				{
					/* Can not erase or program data in first page */
					log_info("\r\n\r\nTest_Result = PASSED.\r\n\r\n\r\n");
					log_info("Change to Flash Read Protection L0 in 5 seconds.\r\n");
					Delayms(5000);

					/* Change Flash Read Protection to L1 */
					log_info("FLASH will be erased automatically.\r\n");
					status = FLASH_ReadOutProtectionL1(DISABLE);
					if (status == FLASH_COMPL)
					{
						/* Generate System Reset to load the new option byte values */
						SysTimer_SoftwareReset();
					}
					log_info("Change Flash Read Protection L1->L0 failed.\r\n");

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
		else
		{
			/* Test Fail */
			Test_Result = FAILED;
		}

	}


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
