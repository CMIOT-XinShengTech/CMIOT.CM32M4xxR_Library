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
#include "led.h"
#include "User_RTC_Config.h"
/** @addtogroup CM32M4xxR_StdPeriph_Examples
 * @{
 */
/**
 * @brief  Delay function.
 *     @arg nCount
 */
void delay(vu32 nCount)
{
    vu32 index = 0;
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
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;
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
       /* Flash 2 wait state */
       FLASH->AC &= (uint32_t)((uint32_t)~FLASH_AC_LATENCY);
       FLASH->AC |= (uint32_t)FLASH_AC_LATENCY_2;
       /* HCLK = SYSCLK */
       RCC->CFG |= (uint32_t)RCC_CFG_AHBPRES_DIV1;
       /* PCLK2 = HCLK */
       RCC->CFG |= (uint32_t)RCC_CFG_APB2PRES_DIV2; // RCC_CFG_APB2PRES_DIV1
       /* PCLK1 = HCLK */
       RCC->CFG |= (uint32_t)RCC_CFG_APB1PRES_DIV4; // RCC_CFG_APB1PRES_DIV2
       /*  PLL configuration: PLLCLK = HSE * 18 = 144 MHz */
       RCC->CFG &= (uint32_t)((uint32_t) ~(RCC_CFG_PLLSRC | RCC_CFG_PLLHSEPRES | RCC_CFG_PLLMULFCT));
       RCC->CFG |= (uint32_t)(RCC_CFG_PLLSRC_HSE | RCC_PLLMULL);
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
    else
    { /* If HSE fails to start-up, the application will have wrong clock
         configuration. User can add here some code to deal with this error */
    }
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
    /* Initialize LEDs on board */
    LedInit(LED1_PORT,LED1_PIN);
    LedOff(LED1_PORT,LED1_PIN);
    /* Initialize USART,TX: PC10 RX: PC11*/
    log_init();
    log_info("RTC Init\r\n");
    /* Enable PWR Clock */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_PWR, ENABLE);
    /* RTC date time alarm default value*/
    RTC_DateAndTimeDefaultVale();
    /* RTC clock source select 1:HSE/128 2:LSE 3:LSI*/
    RTC_CLKSourceConfig(RTC_CLK_SRC_TYPE_LSE, true, true);
    RTC_PrescalerConfig();
    log_info("RTC configured....\r\n");

    /* Adjust time by values entered by the user on the hyperterminal */
    RTC_DateRegulate();
    RTC_TimeRegulate();
    /* wake up clock select */
    RTC_ConfigWakeUpClock(RTC_WKUPCLK_CK_SPRE_16BITS);
    /* wake up timer value */
    RTC_SetWakeUpCounter(4);
    __enable_irq();
#if (RTC_ALARM_TEST_TYPE   ==  RTC_ALARM_TEST_TYPE_IRQ) // 1.Alarm interrupt test

	EXTI20_RTCWKUP_Configuration(ENABLE);
	/* Enable the RTC Wakeup Interrupt */
	RTC_ConfigInt(RTC_INT_WUT, ENABLE);
	RTC_EnableWakeUp(ENABLE);
	DBG_ConfigPeriph(DBG_STOP, ENABLE);
	while (1)
	{
		/* Insert a long delay */
		delay(20);
		/* Request to enter STOP2 mode*/
		PWR_EnterSTOP2Mode(PWR_STOPENTRY_WFI);
		/* Configures system clock after wake-up from STOP: enable HSE, PLL and select
		  PLL as system clock source (HSE and PLL are disabled in STOP mode) */
		SYSCLKConfig_STOP(RCC_CFG_PLLMULFCT18);
		log_init();
		/* Insert a delay */
		log_info("\r\n Stop2 Wakeup From RTC \r\n");
		RTC_TimeShow();
		LedBlink(LED1_PORT,LED1_PIN);
	}

#elif(RTC_ALARM_TEST_TYPE   ==  RTC_ALARM_TEST_TYPE_OUTPUT) // 2.Alarm out test

	/* Set the output type (open-drain output + push-pull output).
	  When setting OD, external  should be added pull-up resistor to PC13
	*/
#if (RTC_ALARM_OUT_TYPE_OPEN_DRAIN == RTC_ALARM_OUT_TYPE)
	RTC_ConfigOutputType(RTC_OUTPUT_OPENDRAIN);
#elif(RTC_ALARM_OUT_TYPE_PULL_PUSH == RTC_ALARM_OUT_TYPE)
	RTC_ConfigOutputType(RTC_OUTPUT_PUSHPULL);
#endif
	RTC_EnableWakeUp(ENABLE);
	RTC_ConfigOutput(RTC_OUTPUT_WKUP, RTC_OUTPOL_LOW);


	while (1)
	{
		if (RTC_GetFlagStatus(RTC_FLAG_WTF) == SET)
		{
			LedBlink(LED1_PORT,LED1_PIN);
			RTC_ClrFlag(RTC_FLAG_WTF);
		}
	}
#endif
}

