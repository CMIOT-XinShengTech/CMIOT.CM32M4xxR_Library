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
 * @file User_RTC_Config.h
 * @author CMIOT Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */


#ifndef __USER_RTC_CONFIG_H__
#define __USER_RTC_CONFIG_H__

#ifdef __cplusplus
extern "C" {
#endif


#define    RTC_ALARM_TEST_TYPE_IRQ        0x01
#define    RTC_ALARM_TEST_TYPE_OUTPUT     0x02
#define    RTC_ALARM_TEST_TYPE            RTC_ALARM_TEST_TYPE_IRQ

#define    RTC_ALARM_OUT_TYPE_OPEN_DRAIN  0x01
#define    RTC_ALARM_OUT_TYPE_PULL_PUSH   0x02
#define    RTC_ALARM_OUT_TYPE             RTC_ALARM_OUT_TYPE_PULL_PUSH

typedef enum {
    RTC_CLK_SRC_TYPE_HSE128=0x01,
    RTC_CLK_SRC_TYPE_LSE=0x02,
    RTC_CLK_SRC_TYPE_LSI=0x03,
}RTC_CLK_SRC_TYPE;


extern void RTC_CLKSourceConfig(RTC_CLK_SRC_TYPE Clk_Src_Type, bool Is_First_Cfg_RCC, bool Is_Rst_Bkp);
extern ErrorStatus RTC_TimeRegulate(void);
extern ErrorStatus RTC_DateRegulate(void);
extern ErrorStatus RTC_AlarmRegulate(uint32_t RTC_Alarm);
extern void RTC_DateAndTimeDefaultVale(void);
extern  void RTC_PrescalerConfig(void);

extern void RTC_TimeShow(void);
extern void RTC_DateShow(void);
extern void RTC_AlarmShow(uint8_t AlarmX);
extern void EXTI17_RTCAlarm_Configuration(FunctionalState Cmd);
extern void EXTI_PA7_Configuration(void);
extern void EXTI20_RTCWKUP_Configuration(FunctionalState Cmd);

#ifdef __cplusplus
}
#endif


#endif/*__USER_RTC_CONFIG_H__*/
