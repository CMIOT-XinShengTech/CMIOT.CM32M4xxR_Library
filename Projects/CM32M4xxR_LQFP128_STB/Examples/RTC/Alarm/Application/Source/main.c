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

/** @addtogroup RTC_Calendar
 * @{
 */
void delay(vu32 nCount)
{
    vu32 index = 0;
    for (index = (34000 * nCount); index != 0; index--)
    {
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

#if (RTC_ALARM_TEST_TYPE   ==  RTC_ALARM_TEST_TYPE_IRQ_WAKEUP)
    log_info("Chip Reset ");
    /* Enable PWR Clock */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_PWR, ENABLE);
#endif

    log_info("RTC Init");
    /* RTC date time alarm default value*/
    RTC_DateAndTimeDefaultVale();
    /* RTC clock source select 1:HSE/128 2:LSE 3:LSI*/
    RTC_CLKSourceConfig(RTC_CLK_SRC_TYPE_LSE, true , true);//RTC_CLK_SRC_TYPE_LSE, true, true
    RTC_PrescalerConfig();
    /* RTC date time and alarm regulate*/
    RTC_DateRegulate();
    RTC_TimeRegulate();
    RTC_AlarmRegulate(RTC_B_ALARM);
    __enable_irq();
    /* Alarm out select option*/
#if (RTC_ALARM_TEST_TYPE   ==  RTC_ALARM_TEST_TYPE_IRQ) // 1.Alarm interrupt test
    EXTI17_RTCAlarm_Configuration(ENABLE);

#elif(RTC_ALARM_TEST_TYPE   ==  RTC_ALARM_TEST_TYPE_IRQ_WAKEUP) // 2.Alarm interrupt wakeup test
	/* Insert a long delay */
	delay(20);
	/* Request to enter Standby mode*/
	PWR_EnterStandbyState();

#elif(RTC_ALARM_TEST_TYPE   ==  RTC_ALARM_TEST_TYPE_OUTPUT) // 2.Alarm out test
    /* Alarm output I/O config */
    #if (RTC_ALARM_OUT_TYPE_OPEN_DRAIN == RTC_ALARM_OUT_TYPE)
       RTC_ConfigOutputType(RTC_OUTPUT_OPENDRAIN);
    #elif(RTC_ALARM_OUT_TYPE_PULL_PUSH == RTC_ALARM_OUT_TYPE)
       RTC_ConfigOutputType(RTC_OUTPUT_PUSHPULL);
    #endif
    /* Alarm output I/O polarity */
    RTC_ConfigOutput(RTC_OUTPUT_ALB, RTC_OUTPOL_HIGH);//RTC_ConfigOutput(RTC_OUTPUT_ALA, RTC_OUTPOL_LOW);
#endif

    while (1);
}
