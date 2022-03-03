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

/** @addtogroup CM32M4xxR_StdPeriph_Examples
 * @{
 */


/** @addtogroup AlarmWakeUp
 * @{
 */
RTC_InitType	RTC_InitStructure;
RTC_DateType	RTC_DateStructure;
RTC_DateType	RTC_DateDefault;
RTC_TimeType	RTC_TimeStructure;
RTC_TimeType	RTC_TimeDefault;
RTC_AlarmType	RTC_AlarmStructure;
RTC_AlarmType	RTC_AlarmDefault;
uint32_t		SynchPrediv;
uint32_t		AsynchPrediv;

static void RTC_PrescalerConfig(void);

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

    /* Initialize USART and LEDs on CM32M4xxR-EVAL board */
    log_init();
    log_info("This is an AlarmWakeUp demo---------------------------------\r\n");

    LedInit(LED1_PORT, LED1_PIN);
    LedOff(LED1_PORT, LED1_PIN);

    /* RTC time and Date default Value */
    RTC_DateAndTimeDefaultVale();

    /* RTC Clock Select, 1: HSE  2:LSE 3: LSI */
    RTC_CLKSourceConfig(RCC_RTCCLK_SRC_LSI, 0, 1); /* LSI */

    RTC_PrescalerConfig();

    /* RTC Date time and Alarm value set */
    RTC_DateRegulate();
    RTC_TimeRegulate();
    RTC_AlarmRegulate(RTC_A_ALARM);

    /* Enable RTC Alarm Interrupt */
    EXTI17_RTCAlarm_Configuration(ENABLE);

    /* Enable global interrupt */
    __enable_irq();

    /* Keep debugger connection during SLEEP, STOP and STANDBY mode */
    DBG_ConfigPeriph(DBG_SLEEP | DBG_STOP | DBG_STDBY, ENABLE);

    /* Enable PWR clock */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_PWR, ENABLE);

    while (1)
    {
        /* Turn on LED and printf some flag imformation */
    	LedBlink(LED1_PORT, LED1_PIN);
        delay(400);
        log_info("\r\n start low power! \r\n");

        /* Request to enter STOP mode with regulator in low power mode */
        // PWR_EnterStopState(PWR_REGULATOR_LOWPOWER, PWR_STOPENTRY_WFI);
        PWR_EnterSLEEPMode(PWR_STOPENTRY_WFI);
        // PWR_EnterStandbyState();
        // PWR_EnterSTOP2Mode(PWR_STOPENTRY_WFI);

        /* Exit the low power, need to reconfigure the system clock */
        SYSCLKConfig_STOP(RCC_CFG_PLLMULFCT18);

        log_init();
        log_info("\r\n Exit low power! \r\n");

        delay(400);
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
        //FLASH->AC &= (uint32_t)((uint32_t)~FLASH_AC_LATENCY);
        //FLASH->AC |= (uint32_t)FLASH_LATENCY_4;
        uint32_t temp = FLASH->AC;
        temp &= (uint32_t)((uint32_t)~FLASH_AC_LATENCY);
        temp |= (uint32_t)((SystemCoreClock - 1) / 32000000);
        FLASH->AC = temp;

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
        //FLASH->AC &= (uint32_t)((uint32_t)~FLASH_AC_LATENCY);
        //FLASH->AC |= (uint32_t)((SystemCoreClock - 1) / 32000000);
        uint32_t temp = FLASH->AC;
        temp &= (uint32_t)((uint32_t)~FLASH_AC_LATENCY);
        temp |= (uint32_t)((SystemCoreClock - 1) / 32000000);
        FLASH->AC = temp;

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
    RCC->CFG |= (uint32_t)RCC_CFG_SCLKSW_PLL;//RCC_CFG_SCLKSW_HSI; //RCC_CFG_SCLKSW_PLL

    /* Wait till PLL is used as system clock source */
        while ((RCC->CFG & (uint32_t)RCC_CFG_SCLKSTS) != (uint32_t)0x08)
    {
    }
}

/**
 * @brief  Delay function.
 */
void delay(vu32 nCount)
{
    vu32 index = 0;
    for (index = (34000 * nCount); index != 0; index--)
    {
    }
}

void EXTI17_RTCAlarm_Configuration(FunctionalState Cmd)
{
    EXTI_InitType EXTI_InitStructure;

    EXTI_ClrITPendBit(EXTI_LINE17);
    EXTI_InitStructure.EXTI_Line    = EXTI_LINE17;
    EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    /* Enable the RTC Alarm Interrupt */
	ECLIC_SetLevelIRQ(RTCAlarm_IRQn, 1);
	ECLIC_SetPriorityIRQ(RTCAlarm_IRQn, 1);
	ECLIC_SetTrigIRQ(RTCAlarm_IRQn, ECLIC_LEVEL_TRIGGER);
	ECLIC_EnableIRQ(RTCAlarm_IRQn);
}

/**
 * @brief  Display the current time on the Hyperterminal.
 */
void RTC_AlarmShow(uint8_t AlarmX)
{
    /* Get the current Alarm */
    if (AlarmX == 0x01)
        RTC_GetAlarm(RTC_FORMAT_BIN, RTC_A_ALARM, &RTC_AlarmStructure);
    else
        RTC_GetAlarm(RTC_FORMAT_BIN, RTC_B_ALARM, &RTC_AlarmStructure);

    log_info("\n\r //=========== Current Alarm Display ==============// \n\r");
    log_info("\n\r The current alarm is :  %0.2d:%0.2d:%0.2d \n\r",
    		 RTC_AlarmStructure.AlarmTime.Hours,
             RTC_AlarmStructure.AlarmTime.Minutes,
             RTC_AlarmStructure.AlarmTime.Seconds);
}

/**
 * @brief  Display the current Date on the Hyperterminal.
 */
void RTC_DateShow(void)
{
    /* Get the current Date */
    RTC_GetDate(RTC_FORMAT_BIN, &RTC_DateStructure);
    log_info("\n\r //=========== Current Date Display ==============// \n\r");
    log_info("\n\r The current date (WeekDay-Date-Month-Year) is :  %0.2d-%0.2d-%0.2d-%0.2d \n\r",
             RTC_DateStructure.WeekDay,
             RTC_DateStructure.Date,
             RTC_DateStructure.Month,
             RTC_DateStructure.Year);
}

/**
 * @brief  Display the current time on the Hyperterminal.
 */
void RTC_TimeShow(void)
{
    /* Get the current Time and Date */
    RTC_GetTime(RTC_FORMAT_BIN, &RTC_TimeStructure);
    log_info("\n\r //============ Current Time Display ===============// \n\r");
    log_info("\n\r The current time (Hour-Minute-Second) is :  %0.2d:%0.2d:%0.2d \n\r",
             RTC_TimeStructure.Hours,
             RTC_TimeStructure.Minutes,
             RTC_TimeStructure.Seconds);

    /* Unfreeze the RTC DAT Register */
    (void)RTC->DATE;
}

/**
 * @brief  RTC time date and Alarm Value config.
 */
void RTC_DateAndTimeDefaultVale(void)
{
	/* Date */
    RTC_DateDefault.WeekDay = RTC_WEEKDAY_SUNDAY;
    RTC_DateDefault.Date    = 22;
    RTC_DateDefault.Month   = 11;
    RTC_DateDefault.Year    = 20;

    /* Time */
    RTC_TimeDefault.H12     = RTC_AM_H12;
    RTC_TimeDefault.Hours   = 16;
    RTC_TimeDefault.Minutes = 59;
    RTC_TimeDefault.Seconds = 00;

    /* Alarm */
    RTC_AlarmDefault.AlarmTime.H12     = RTC_AM_H12;
    RTC_AlarmDefault.AlarmTime.Hours   = 17;
    RTC_AlarmDefault.AlarmTime.Minutes = 00;
    RTC_AlarmDefault.AlarmTime.Seconds = 00;
    RTC_AlarmDefault.DateWeekMode      = RTC_ALARM_SEL_WEEKDAY_DATE;
    RTC_AlarmDefault.DateWeekValue     = 22;
    RTC_AlarmDefault.AlarmMask         = RTC_ALARMMASK_MINUTES;
}

/**
 * @brief  RTC alarm value configure, and print the configure information.
 */
ErrorStatus RTC_AlarmRegulate(uint32_t RTC_Alarm)
{
    uint32_t tmp_hh = 0xFF;
    uint32_t tmp_mm = 0xFF;
    uint32_t tmp_ss = 0xFF;

    /* Disable the AlarmX */
    RTC_EnableAlarm(RTC_Alarm, DISABLE);

    log_info("\n\r //==============Alarm X Settings================// \n\r");
    RTC_AlarmStructure.AlarmTime.H12 = RTC_AM_H12;
    RTC_TimeStructure.H12            = RTC_AM_H12;

    log_info("\n\r Please Set Alarm Hours \n\r");
    tmp_hh = RTC_AlarmDefault.AlarmTime.Hours;
    if (tmp_hh == 0xff)
    {
        return ERROR;
    }
    else
    {
        RTC_AlarmStructure.AlarmTime.Hours = tmp_hh;
    }

    log_info(": %0.2d\n\r", tmp_hh);

    log_info("\n\r Please Set Alarm Minutes \n\r");
    tmp_mm = RTC_AlarmDefault.AlarmTime.Minutes;
    if (tmp_mm == 0xff)
    {
        return ERROR;
    }
    else
    {
        RTC_AlarmStructure.AlarmTime.Minutes = tmp_mm;
    }

    log_info(": %0.2d\n\r", tmp_mm);

    log_info("\n\r Please Set Alarm Seconds \n\r");
    tmp_ss = RTC_AlarmDefault.AlarmTime.Seconds;
    if (tmp_ss == 0xff)
    {
        return ERROR;
    }
    else
    {
        RTC_AlarmStructure.AlarmTime.Seconds = tmp_ss;
    }

    log_info(": %0.2d\n\r", tmp_ss);

    /* Set the Alarm X */
    RTC_AlarmStructure.DateWeekValue = RTC_AlarmDefault.DateWeekValue;

    RTC_AlarmStructure.DateWeekMode = RTC_AlarmDefault.DateWeekMode;

    // RTC_AlarmStructure.AlarmMask = RTC_ALARMMASK_WEEKDAY | RTC_ALARMMASK_HOURS | RTC_ALARMMASK_SECONDS;
    RTC_AlarmStructure.AlarmMask = RTC_ALARMMASK_WEEKDAY | RTC_ALARMMASK_HOURS | RTC_ALARMMASK_MINUTES;
    // RTC_AlarmStructure.AlarmMask = RTC_ALARMMASK_WEEKDAY;

    /* Configure the RTC Alarm A register */
    RTC_SetAlarm(RTC_FORMAT_BIN, RTC_Alarm, &RTC_AlarmStructure);
    log_info("\n\r>> !! RTC Set Alarm_X success. !! <<\n\r");

    if (RTC_Alarm == RTC_A_ALARM)
    {
        /* Enable the RTC Alarm A Interrupt */
        RTC_ConfigInt(RTC_INT_ALRA, ENABLE);
        RTC_AlarmShow(1);
    }
    else
    {
        /* Enable the RTC Alarm B Interrupt */
        RTC_ConfigInt(RTC_INT_ALRB, ENABLE);
        RTC_AlarmShow(2);
    }

    /* Enable the alarm   */
    RTC_EnableAlarm(RTC_Alarm, ENABLE);
    return SUCCESS;

}

/**
 * @brief  RTC date value configure, and print the configure information.
 */
ErrorStatus RTC_DateRegulate(void)
{
	uint32_t tmp_yy = 0xFF;
	uint32_t tmp_mm = 0xFF;
	uint32_t tmp_ww = 0xFF;
	uint32_t tmp_dd = 0xFF;

    log_info("\n\r //=============Date Settings================// \n\r");

    log_info("\n\r Please Set WeekDay (01-07) \n\r");
    tmp_ww = RTC_DateDefault.WeekDay;
    if (tmp_ww == 0xff)
    {
        return ERROR;
    }
    else
    {
        RTC_DateStructure.WeekDay = tmp_ww;
    }

    log_info(": %0.2d\n\r", tmp_ww);

    log_info("\n\r Please Set Date (01-31) \n\r");
    tmp_dd = RTC_DateDefault.Date;
    if (tmp_dd == 0xff)
    {
        return ERROR;
    }
    else
    {
        RTC_DateStructure.Date = tmp_dd;
    }

    log_info(": %0.2d\n\r", tmp_dd);

    log_info("\n\r Please Set Month (01-12)\n\r");
    tmp_mm = RTC_DateDefault.Month;
    if (tmp_mm == 0xff)
    {
        return ERROR;
    }
    else
    {
        RTC_DateStructure.Month = tmp_mm;
    }

    log_info(": %0.2d\n\r", tmp_mm);

    log_info("\n\r Please Set Year (00-99)\n\r");
    tmp_yy = RTC_DateDefault.Year;
    if (tmp_yy == 0xff)
    {
        return ERROR;
    }
    else
    {
        RTC_DateStructure.Year = tmp_yy;
    }

    log_info(": %0.2d\n\r", tmp_yy);

    /* Configure the RTC date register */
    if (RTC_SetDate(RTC_FORMAT_BIN, &RTC_DateStructure) == ERROR)
    {
        log_info("\n\r>> !! RTC Set Date failed. !! <<\n\r");
        return ERROR;
    }
    else
    {
        log_info("\n\r>> !! RTC Set Date success. !! <<\n\r");
        RTC_DateShow();
        return SUCCESS;
    }
}

/**
 * @brief  RTC time value configure, and print the configure information.
 */
ErrorStatus RTC_TimeRegulate(void)
{
    uint32_t tmp_hh = 0xFF;
    uint32_t tmp_mm = 0xFF;
    uint32_t tmp_ss = 0xFF;

    log_info("\n\r //==============Time Settings=================// \n\r");

    RTC_TimeStructure.H12 = RTC_TimeDefault.H12;

    log_info("\n\r Please Set Hours \n\r");
    tmp_hh = RTC_TimeDefault.Hours;
    if (tmp_hh == 0xff)
    {
        return ERROR;
    }
    else
    {
        RTC_TimeStructure.Hours = tmp_hh;
    }

    log_info(": %0.2d\n\r", tmp_hh);

    log_info("\n\r Please Set Minutes \n\r");
    tmp_mm = RTC_TimeDefault.Minutes;
    if (tmp_mm == 0xff)
    {
        return ERROR;
    }
    else
    {
        RTC_TimeStructure.Minutes = tmp_mm;
    }

    log_info(": %0.2d\n\r", tmp_mm);

    log_info("\n\r Please Set Seconds \n\r");
    tmp_ss = RTC_TimeDefault.Seconds;
    if (tmp_ss == 0xff)
    {
        return ERROR;
    }
    else
    {
        RTC_TimeStructure.Seconds = tmp_ss;
    }

    log_info(": %0.2d\n\r", tmp_ss);

    /* Configure the RTC time register */
    if (RTC_ConfigTime(RTC_FORMAT_BIN, &RTC_TimeStructure) == ERROR)
    {
        log_info("\n\r>> !! RTC Set Time failed. !! <<\n\r");
        return ERROR;
    }
    else
    {
        log_info("\n\r>> !! RTC Set Time success. !! <<\n\r");
        RTC_TimeShow();
        return SUCCESS;
    }
}

/**
 * @brief  RTC Prescaler config.
 */
static void RTC_PrescalerConfig(void)
{
    /* Configure the RTC data register and RTC prescaler */
    RTC_InitStructure.RTC_AsynchPrediv = AsynchPrediv;
    RTC_InitStructure.RTC_SynchPrediv  = SynchPrediv;
    RTC_InitStructure.RTC_HourFormat   = RTC_24HOUR_FORMAT;

    /* Check on RTC init */
    if (RTC_Init(&RTC_InitStructure) == ERROR)
    {
        log_info("\r\n //******* RTC Prescaler Config failed **********// \r\n");
    }
}

/**
 * @brief  Configures RTC.
 *   Configure the RTC peripheral by selecting the clock source
 */

void RTC_CLKSourceConfig(uint32_t ClkSrc, uint8_t FirstLastCfg, uint8_t RstBKP)
{
    assert_param(IS_RCC_RTCCLK_SRC(ClkSrc));

    /* Enable the PWR clock */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_PWR | RCC_APB1_PERIPH_BKP, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);

    /* Allow access to RTC */
    PWR_BackupAccessEnable(ENABLE);

    /* Reset Backup */
    if (RstBKP == 1)
    {
        BKP_DeInit();
    }

    /* Disable RTC clock */
    RCC_EnableRtcClk(DISABLE);

    if (ClkSrc == RCC_RTCCLK_SRC_HSE_DIV128)
    {
        log_info("\r\n RTC_ClkSrc Is Set HSE128! \r\n");
        if (FirstLastCfg == 0)
        {
            /* Enable HSE */
            RCC_EnableLsi(DISABLE);
            RCC_ConfigHse(RCC_HSE_ENABLE);
            while (RCC_WaitHseStable() == ERROR)
            {
            }

            RCC_ConfigRtcClk(RCC_RTCCLK_SRC_HSE_DIV128);
        }
        else
        {
            RCC_EnableLsi(DISABLE);
            RCC_ConfigRtcClk(RCC_RTCCLK_SRC_HSE_DIV128);

            /* Enable HSE */
            RCC_ConfigHse(RCC_HSE_ENABLE);

            while (RCC_WaitHseStable() == ERROR)
            {
            }
        }

        SynchPrediv  = 0x1E8; /* 8M / 128 = 62.5KHz */
        AsynchPrediv = 0x7F;  /* value range: 0x00 - 0x7F */
    }
    else if (ClkSrc == RCC_RTCCLK_SRC_LSE)
    {
        log_info("\r\n RTC_ClkSrc Is Set LSE! \r\n");

        if (FirstLastCfg == 0)
        {
            /* Enable the LSE OSC32_IN PC14 */
            RCC_EnableLsi(DISABLE); /* LSI is turned off here to ensure that only one clock is turned on */

#if (_TEST_LSE_BYPASS_)
            RCC_ConfigLse(RCC_LSE_BYPASS);
#else
            RCC_ConfigLse(RCC_LSE_ENABLE);
#endif

            while (RCC_GetFlagStatus(RCC_FLAG_LSERD) == RESET)
            {
            }

            RCC_ConfigRtcClk(RCC_RTCCLK_SRC_LSE);
        }
        else
        {
            /* Enable the LSE OSC32_IN PC14 */
            RCC_EnableLsi(DISABLE);
            RCC_ConfigRtcClk(RCC_RTCCLK_SRC_LSE);

#if (_TEST_LSE_BYPASS_)
            RCC_ConfigLse(RCC_LSE_BYPASS);
#else
            RCC_ConfigLse(RCC_LSE_ENABLE);
#endif

            while (RCC_GetFlagStatus(RCC_FLAG_LSERD) == RESET)
            {
            }
        }

        SynchPrediv  = 0xFF; /* 32.768KHz */
        AsynchPrediv = 0x7F; /* value range: 0x00 - 0x7F */
    }
    else if (ClkSrc == RCC_RTCCLK_SRC_LSI)
    {
        log_info("\r\n RTC_ClkSrc Is Set LSI! \r\n");
        if (FirstLastCfg == 0)
        {
            /* Enable the LSI OSC */
            RCC_EnableLsi(ENABLE);

            while (RCC_GetFlagStatus(RCC_FLAG_LSIRD) == RESET)
            {
            }

            RCC_ConfigRtcClk(RCC_RTCCLK_SRC_LSI);
        }
        else
        {
            RCC_ConfigRtcClk(RCC_RTCCLK_SRC_LSI);

            /* Enable the LSI OSC */
            RCC_EnableLsi(ENABLE);

            while (RCC_GetFlagStatus(RCC_FLAG_LSIRD) == RESET)
            {
            }
        }

        SynchPrediv  = 0x136; /* 39.64928KHz */
        AsynchPrediv = 0x7F;  /* value range: 0x00 - 0x7F */
    }
    else
    {
        log_info("\r\n RTC_ClkSrc Value is error! \r\n");
    }

    /* Enable the RTC Clock */
    RCC_EnableRtcClk(ENABLE);
    RTC_WaitForSynchro();
}


/**
 * @}
 */

/**
 * @}
 */
