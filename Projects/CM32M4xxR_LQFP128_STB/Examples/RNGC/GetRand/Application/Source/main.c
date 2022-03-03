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
#include <stdio.h>
#include "log.h"

/** @addtogroup CM32M4xxR_StdPeriph_Examples
 * @{
 */

/** @addtogroup GetRand
 * @{
 */


void Delay(__IO uint32_t nCount);

/**
 * @brief  Main function.
 */
void RNGC_configure(void)
{
	RNGC_InitType Rngc_Init;

    /* Enable RNGC clock */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_RNGC, ENABLE);
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_RNGC, ENABLE);

    RNGC_DeInit();

	Rngc_Init.Prescaler = RCC_RNGCCLK_SYSCLK_DIV1;
	Rngc_Init.Ring0En = true;	/* Default true */
	Rngc_Init.Ring1En = true;	/* Default true */
	RNGC_Init(&Rngc_Init);
}



/**
 * @brief  Main function.
 */
int main(void)
{
    /*!< At this stage the microcontroller clock setting is already configured,
         this is done through SystemInit() function which is called from startup
         file (startup_cm32m4xxr.s) before to branch to application main.
         To reconfigure the default setting of SystemInit() function, refer to
         system_cm32m4xxr.c file
    */

	uint32_t Rand_Value = INVALID_RANDOM_VALUE;

	log_init();
	log_info("This is a RNGC demo\r\n");

	/* Configure RNGC */
	RNGC_configure();

	/* Set RNGC true random mode */
	RNGC_SetRngMode(RNG_MODE_RANDOM_SOURCE);
	RNGC_SetRngMode(RNG_MODE_TRNG);

	Delay(0xFF);

    while (1)
    {
    	Rand_Value = RNGC_GetRand();

    	log_info("random = %u\r\n", Rand_Value);
    }
}

/**
 * @brief  Inserts a delay time.
 * @param nCount specifies the delay time length.
 */
void Delay(__IO uint32_t nCount)
{
    for (; nCount != 0; nCount--)
        ;
}


/**
 * @}
 */

/**
 * @}
 */
