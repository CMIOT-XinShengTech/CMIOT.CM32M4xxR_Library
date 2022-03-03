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
    log_info("RTC Init");
    /* RTC date time alarm default value*/
    RTC_DateAndTimeDefaultVale();

    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_PWR | RCC_APB1_PERIPH_BKP, ENABLE);

    PWR_BackupAccessEnable(ENABLE);
    __enable_irq();

    if (BKP_ReadBkpData(BKP_DAT1) != USER_WRITE_BKP_DAT1_DATA)
    {
        /* Backup data register value is not correct or not yet programmed (when
           the first time the program is executed) */

        log_info("\r\n\n RTC not yet configured....");

        /* RTC clock source select 1:HSE/128 2:LSE 3:LSI*/
        RTC_CLKSourceConfig(RTC_CLK_SRC_TYPE_LSE, true, true);
        RTC_PrescalerConfig();
        log_info("\r\n RTC configured....");

        /* Adjust time by values entered by the user on the hyperterminal */
        RTC_DateRegulate();
        RTC_TimeRegulate();
        BKP_WriteBkpData(BKP_DAT1, USER_WRITE_BKP_DAT1_DATA);
    }

    /* Configure the PA7 pin to generate an EXTI interrupt
	in which the calendar value is printed (externally feed
	the 1HZ signal output on PC13 to PA7 to produce a 1s EXTI interrupt)
	*/
    EXTI_PA7_Configuration();
    EXTI_ClrITPendBit(EXTI_LINE7);
    /* Calibrate output 1Hz signal */
    RTC_ConfigCalibOutput(RTC_CALIB_OUTPUT_1HZ);
    /* Calibrate output config,push pull */
    RTC_ConfigOutputType(RTC_OUTPUT_PUSHPULL);
    /* Calibrate output enable*/
    RTC_EnableCalibOutput(ENABLE);
    log_info("\r\n RTC Config end....");

    while (1)
        ;
}

