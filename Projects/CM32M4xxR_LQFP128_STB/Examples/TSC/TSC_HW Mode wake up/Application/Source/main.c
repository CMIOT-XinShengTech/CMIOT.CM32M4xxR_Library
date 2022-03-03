/*
  ******************************************************************************
  *
  * COPYRIGHT(c) 2020, China Mobile IOT
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of China Mobile IOT nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
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
  ******************************************************************************
  */ 

/**
 * @file main.c
 * @author CMIOT
 * @version v1.0.1
 *
 * @COPYRIGHT(c) 2020, China Mobile IOT. All rights reserved.
 */
#include "main.h"
#include "bsp.h"

void *_sbrk(ptrdiff_t incr)
{
    extern char _heap_start[];
    extern char _heap_end[];
    static char *curbrk = _heap_start;

    if ((curbrk + incr < _heap_start) || (curbrk + incr > _heap_end)) {
        return NULL - 1;
    }

    curbrk += incr;
    return curbrk - incr;
}

/**
 * @brief  Set system clock again,use HSE as clock source,and enable pll
 * &param  pllmul:pll multiply factor,as HSE is 8MHz
 * @retval: None
 */
static void SetSysClock_HSE_PLL(uint32_t pllmul)
{
    __IO uint32_t StartUpCounter = 0, HSEStartUpStatus = 0;

    // It is necessary to initialize the RCC peripheral to the reset state.
    RCC_DeInit();

    // Enable HSE, open external crystal oscillator.
    RCC_ConfigHse(RCC_HSE_ENABLE);

    // Wait for HSE to be stable.
    HSEStartUpStatus = RCC_WaitHseStable();

    // Go on until the HSE is stable.
    if (HSEStartUpStatus == SUCCESS)
    {
        //----------------------------------------------------------------------//
        // Enable flash Prefetch buffer
        FLASH_PrefetchBufSet(FLASH_PrefetchBuf_EN);

        FLASH_SetLatency(FLASH_LATENCY_3);
        //----------------------------------------------------------------------//

        // AHB prescaler factor set to 1,HCLK = SYSCLK = 16M
        RCC_ConfigHclk(RCC_SYSCLK_DIV1);
        // AHB prescaler factor set to 1,PCLK2 = HCLK/1 = 16M
        RCC_ConfigPclk2(RCC_HCLK_DIV1);
        // AHB prescaler factor set to 1,PCLK1 = HCLK/1 = 16M
        RCC_ConfigPclk1(RCC_HCLK_DIV1);

        //-----------------Set PLL clock source as HSE, set PLL frequency multiplication factor.-------------------//
        // PLLCLK = 8MHz * pllmul
        RCC_ConfigPll(RCC_PLL_SRC_HSE_DIV1, pllmul);
        //------------------------------------------------------------------//

        // Enable PLL
        RCC_EnablePll(ENABLE);
        // Wait for PLL to be stable.
        while (RCC_GetFlagStatus(RCC_FLAG_PLLRD) == RESET)
        {
        }

        // Switch PLL clock to SYSCLK.
        RCC_ConfigSysclk(RCC_SYSCLK_SRC_PLLCLK);

        // Read the clock switch status bit and make sure pllclk is selected as the system clock.
        while (RCC_GetSysclkSrc() != RCC_CFG_SCLKSTS_PLL)
        {
        }
    }
    else
    {   // If HSE fails to open, the program will come here, where the user can add the error code to handle.
        // When HSE fails or breaks down,mcu will automatically set HSI as the system clock.HSI is an internal high speed
        // clock of 8MHz.
        while (1)
        {
        }
    }

    SystemCoreClockUpdate();
}

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

    // HSE,SYSCLK = 8M * RCC_PLLMul_x,
    SetSysClock_HSE_PLL(RCC_PLL_MUL_2);

    log_init();
    LedInit(LED1_PORT, LED1_PIN);
    LedInit(LED2_PORT, LED2_PIN);
    LedInit(LED3_PORT, LED3_PIN);

    LedOn(LED1_PORT, LED1_PIN);
    delay_ms(500);
    LedOff(LED1_PORT, LED1_PIN);
    delay_ms(500);
    
    printf("TSC HW mode demo start!\r\n");


  #ifdef TSC_LOWPOWER_DEBUG
    DBG_ConfigPeriph(DBG_SLEEP|DBG_STOP,ENABLE);
  #endif
  
    while (1)
    {
        printf("TSC wake up loop start!\r\n");

        BSP_TSC_HwInit();   /* Init TSC mode */

        LedOn(LED1_PORT, LED1_PIN);
        LedOn(LED2_PORT, LED2_PIN);
        LedOn(LED3_PORT, LED3_PIN);
        delay_ms(500);
        BSP_TSC_AutoAdjust();   /* Config TSC threshold */
        BSP_TSC_ConfigInt();
        BSP_TSC_HwEnable();     /* Enable hw detect*/
        LedOff(LED1_PORT, LED1_PIN);
        LedOff(LED2_PORT, LED2_PIN);
        LedOff(LED3_PORT, LED3_PIN);

        printf("Enter sleep mode!\r\n");
        PWR_EnterSLEEPMode(PWR_STOPENTRY_WFI);   /* Enter sleep mode */

        printf("K%d press,exit sleep mode!\r\n",BSP_TSC_GetKeyNum());
        LedOn(LED1_PORT, LED1_PIN);
        delay_ms(500);
        LedOff(LED1_PORT, LED1_PIN);
        delay_ms(500);

        BSP_TSC_HwEnable();              		 /* Enable hw detect*/
        printf("Enter stop0 mode!\r\n");
        PWR_EnterStopState(PWR_REGULATOR_ON,PWR_STOPENTRY_WFI);   /* Enter low power sleep mode */

        SetSysClock_HSE_PLL(RCC_PLL_MUL_2);      /* Config PLL */
        printf("T%d press,exit stop0 mode!\r\n",BSP_TSC_GetKeyNum());
        LedOn(LED2_PORT, LED2_PIN);
        delay_ms(500);
        LedOff(LED2_PORT, LED2_PIN);
        delay_ms(500);

        BSP_TSC_HwEnable();              		/* Enable hw detect*/
        RCC_EnableRtcClk(ENABLE);
        printf("Enter stop2 mode!\r\n");
    	_save_to_rram();
        PWR_EnterSTOP2Mode(PWR_STOPENTRY_WFI);  /* Enter stop2 mode */
        _restore_from_rram();

        SetSysClock_HSE_PLL(RCC_PLL_MUL_2);
        log_init();
		LedInit(LED1_PORT, LED1_PIN);
		LedInit(LED2_PORT, LED2_PIN);
		LedInit(LED3_PORT, LED3_PIN);

        printf("T%d press,exit stop2 mode!\r\n",BSP_TSC_GetKeyNum());
        LedOn(LED3_PORT, LED3_PIN);
        delay_ms(500);
        LedOff(LED3_PORT, LED3_PIN);
        delay_ms(500);

    }

}

/******************************************************************/
