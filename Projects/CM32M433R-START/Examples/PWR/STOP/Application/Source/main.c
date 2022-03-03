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

#include <stdio.h>
#include "main.h"

#include "log.h"
#include "led.h"

/** @addtogroup CM32M4xxR_StdPeriph_Examples
 * @{
 */


/** @addtogroup PWR_STOP
 * @{
 */

void delay(vu32 nCount);
void SYSCLKConfig_STOP(uint32_t RCC_PLLMULL);
void KeyInputExtiInit(GPIO_Module* GPIOx, uint16_t Pin);

#define KEEP_IN_RRAM	__attribute__ ((section (".rram_data")))

/**
* @brief  Save data in retention ram to keep their value in low-power mode.
* @return Length of saved data.
* @note   The data need to be saved should be indicated by KEEP_IN_RRAM
* 		   macro at where they are defined.
*/
uint32_t _save_to_rram(void)
{
	/* Symbols defined in .ld to indicate the address of
	 * source data and destination area */
	extern char _rram_data_start[], _rram_data_end[];
	extern char _rram_sdata_start[], _rram_sdata_end[];
	extern char _rram_srodata_start[], _rram_srodata_end[];
	extern char _rram_sbss_start[], _rram_sbss_end[];
	extern char _rram_bss_start[], _rram_bss_end[];
	extern char _rram_common_start[], _rram_common_end[];
	extern char _rram_data_area_start[], _rram_data_area_end[];
	uint32_t dl = (uint32_t)_rram_data_area_end - (uint32_t)_rram_data_area_start; /* Destination Length */
	uint32_t sl = 0;	/* Source Length */
	uint32_t lc = 0;	/* Length Counter */
	uint32_t sc = 0;	/* Sub-section Counter */
	uint32_t bc = 0;	/* Byte Counter */
	char* sa[6][2] = {{_rram_data_start,    _rram_data_end},
					  {_rram_sdata_start,   _rram_sdata_end},
					  {_rram_srodata_start, _rram_srodata_end},
					  {_rram_sbss_start,    _rram_sbss_end},
					  {_rram_bss_start,     _rram_bss_end},
					  {_rram_common_start,  _rram_common_end}}; /* Sub-section Address */
	/* Do save */
	do{
		/* Get sub-section length and compare it with
		 * remaining space in destination area */
		sl = (uint32_t)sa[sc][1] - (uint32_t)sa[sc][0];
		if(lc + sl > dl) { break; }
		/* Copy data from source(sub-section in ram) to
		 * destination(retention ram) */
		for(bc = 0; bc < sl; bc++){
			_rram_data_area_start[lc + bc] = sa[sc][0][bc];
		}
		/* Update length counter */
		lc += sl;
	}while(++sc < 6);
	/* return the length of saved data */
	return lc;
}

/**
* @brief  Restore data's value that saved in retention ram by _save_to_rram().
* @return Length of restored data.
*/
uint32_t _restore_from_rram(void)
{
	/* Symbols defined in .ld to indicate the address of
	 * source data and destination area */
	extern char _rram_data_start[], _rram_data_end[];
	extern char _rram_sdata_start[], _rram_sdata_end[];
	extern char _rram_srodata_start[], _rram_srodata_end[];
	extern char _rram_sbss_start[], _rram_sbss_end[];
	extern char _rram_bss_start[], _rram_bss_end[];
	extern char _rram_common_start[], _rram_common_end[];
	extern char _rram_data_area_start[], _rram_data_area_end[];
	uint32_t sl = (uint32_t)_rram_data_area_end - (uint32_t)_rram_data_area_start; /* Source Length */
	uint32_t dl = 0;	/* Destination Length */
	uint32_t lc = 0;	/* Length Counter */
	uint32_t sc = 0;	/* Sub-section Counter */
	uint32_t bc = 0;	/* Byte Counter */
	char* sa[6][2] = {{_rram_data_start,    _rram_data_end},
					  {_rram_sdata_start,   _rram_sdata_end},
					  {_rram_srodata_start, _rram_srodata_end},
					  {_rram_sbss_start,    _rram_sbss_end},
					  {_rram_bss_start,     _rram_bss_end},
					  {_rram_common_start,  _rram_common_end}}; /* Sub-section Address */
	/* Do restore */
	do{
		/* Get sub-section length and compare it with
		 * remaining space in destination area */
		dl = (uint32_t)sa[sc][1] - (uint32_t)sa[sc][0];
		if(lc + dl > sl) { break; }
		/* Copy data from source(retention ram) to
		 * destination(sub-section in ram) */
		for(bc = 0; bc < dl; bc++){
			sa[sc][0][bc] = _rram_data_area_start[lc + bc];
		}
		/* Update length counter */
		lc += dl;
	}while(++sc < 6);
	/* return the length of restored data */
	return lc;
}
/**
 * @brief  Main program.
 */
int main(void)
{
    /*!< At this stage the microcontroller clock setting is already configured,
         this is done through SystemInit() function which is called from startup
         file (startup_cm32m4xxr.s) before to branch to application main.
         To reconfigure the default setting of SystemInit() function, refer to
         system_cm32m4xxr.c file
       */
    /* Enable PWR Clock */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_PWR, ENABLE);

    /* Initialize LEDs on CM32M4xxR-EVAL board */
    LedInit(LED_PORT, (LED1 | LED2 | LED3));

    /* Initialize Key button Interrupt to wakeUp stop */
    KeyInputExtiInit(KEY_INPUT_PORT, KEY_INPUT_PIN);

    /* Set the LED in different status */
    LedOff(LED_PORT, LED1);
    LedOff(LED_PORT, LED3);
    LedOn(LED_PORT, LED2);

    /* Clear the EXIT Interrupt flag */
    EXTI_ClrITPendBit(EXTI_LINE0);

	/* Enable global interrupt */
	__enable_irq();

    /*  Enable the DBG_STOP to keep debug in low power  */
    DBG_ConfigPeriph(DBG_STOP, ENABLE);

    while (1)
    {
        /* Insert a long delay */
        delay(200);

        /* Set the LED */
        LedBlink(LED_PORT, LED1);
        LedOff(LED_PORT, LED2);
        LedOff(LED_PORT, LED3);

        _save_to_rram();
        /* Request to enter STOP mode with regulator in low power mode*/
        PWR_EnterStopState(PWR_REGULATOR_LOWPOWER, PWR_STOPENTRY_WFI);
        /* Request to enter STOP2 mode*/
//        PWR_EnterSTOP2Mode(PWR_STOPENTRY_WFI);
        _restore_from_rram();

        /* Configures system clock after wake-up from STOP: enable HSE, PLL and select
           PLL as system clock source (HSE and PLL are disabled in STOP mode) */
        SYSCLKConfig_STOP(RCC_CFG_PLLMULFCT18);

        LedInit(LED_PORT, LED3);
        LedOn(LED_PORT, LED3);
    }
}

/**
 * @brief  Delay function.
 *     @arg nCount
 */
void delay(vu32 nCount)
{
    volatile vu32 index = 0;
    for (index = (34000 * nCount); index != 0; index--)
    {
    }
}

/**
 * @brief  Configures system clock after wake-up from STOP: enable HSE, PLL
 *         and select PLL as system clock source.
 */
void SYSCLKConfig_STOP(uint32_t RCC_PLLMULL)
{
    __IO uint32_t StartUpCounter = 0;
    __IO uint32_t HSEStatus = 0;

    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
    /* Enable HSE */
    RCC->CTRL |= ((uint32_t)RCC_CTRL_HSEEN);

    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSEStatus = RCC->CTRL & RCC_CTRL_HSERDF;
        StartUpCounter++;
    } while ((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->CTRL & RCC_CTRL_HSERDF) != RESET)
    {
        HSEStatus = (uint32_t)0x01;
    }
    else
    {
        HSEStatus = (uint32_t)0x00;
    }

    if (HSEStatus == (uint32_t)0x01)
    {
        /* Enable Prefetch Buffer */
        FLASH->AC |= FLASH_AC_PRFTBFE;

        /* Flash wait state
            0: HCLK <= 32M
            1: HCLK <= 64M
            2: HCLK <= 96M
            3: HCLK <= 128M
            4: HCLK <= 144M
         */
        /* Flash 2 wait state */
        FLASH->AC &= (uint32_t)((uint32_t)~FLASH_AC_LATENCY);
        FLASH->AC |= (uint32_t)FLASH_LATENCY_4;

        /* HCLK = SYSCLK */
        RCC->CFG |= (uint32_t)RCC_CFG_AHBPRES_DIV1;

        /* PCLK2 = HCLK */
        RCC->CFG |= (uint32_t)RCC_CFG_APB2PRES_DIV2; // RCC_CFG_APB2PRES_DIV1

        /* PCLK1 = HCLK */
        RCC->CFG |= (uint32_t)RCC_CFG_APB1PRES_DIV4; // RCC_CFG_APB1PRES_DIV2

        /*  PLL configuration: PLLCLK = HSE * 18 = 144 MHz */
        RCC->CFG &= (uint32_t)((uint32_t) ~(RCC_CFG_PLLSRC | RCC_CFG_PLLHSEPRES | RCC_CFG_PLLMULFCT));
        RCC->CFG |= (uint32_t)(RCC_CFG_PLLSRC_HSE | RCC_PLLMULL);
    }
    else	/* If HSE fails to start-up, then use HSI_PLL as system clock */
    {
        FLASH->AC &= (uint32_t)((uint32_t)~FLASH_AC_LATENCY);
        FLASH->AC |= (uint32_t)((SystemCoreClock - 1) / 32000000);

        /* HCLK = SYSCLK */
        RCC->CFG |= (uint32_t)RCC_CFG_AHBPRES_DIV1;

        /* PCLK2 max 72M */
        RCC->CFG |= (uint32_t)RCC_CFG_APB2PRES_DIV1;

        /* PCLK1 max 36M */
        RCC->CFG |= (uint32_t)RCC_CFG_APB1PRES_DIV1;

        /* clear bits */
        RCC->CFG &= (uint32_t)((uint32_t) ~(RCC_CFG_PLLSRC | RCC_CFG_PLLHSEPRES | RCC_CFG_PLLMULFCT));

        /* set PLL source */
        RCC->CFG |= RCC_CFG_PLLSRC_HSI_DIV2;
    }

    /* Enable PLL */
    RCC->CTRL |= RCC_CTRL_PLLEN;

    /* Wait till PLL is ready */
    while ((RCC->CTRL & RCC_CTRL_PLLRDF) == 0)
    {
    }

    /* Select PLL as system clock source */
    RCC->CFG &= (uint32_t)((uint32_t) ~(RCC_CFG_SCLKSW));
    RCC->CFG |= (uint32_t)RCC_CFG_SCLKSW_PLL;

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFG & (uint32_t)RCC_CFG_SCLKSTS) != (uint32_t)0x08)
    {
    }
}

/**
 * @}
 */
