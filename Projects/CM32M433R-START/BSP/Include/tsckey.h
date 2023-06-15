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
 * @file tsckey.h
 * @author CMIOT
 * @version v1.0.1
 *
 * @COPYRIGHT(c) 2020, China Mobile IOT. All rights reserved.
 */
#ifndef __TSCKEY_H__
#define __TSCKEY_H__

#include "nuclei_sdk_soc.h"

#define KEY_NUM     (5)
#define TSC_CH_USED (TSC_CHNEN_CHN_SEL21| TSC_CHNEN_CHN_SEL22 | TSC_CHNEN_CHN_SEL23 | TSC_CHNEN_CHN_SEL2 | TSC_CHNEN_CHN_SEL3)
#define SUM_NUM  10     /* The number of samples for each channel during every check period */

typedef struct
{
    uint32_t EtrCnt;                        // ETR value of this time count by TIMER(TIMx->CNT)
    uint32_t EtrCntPre;                     // ETR value of last time
    uint32_t PulseSample[KEY_NUM][SUM_NUM]; // ETR sample cnt, KEY_NUM:channel SUM_NUM:samples of each channel
    uint32_t EtrSumThreshold[KEY_NUM];      // Threshold of the sum of all samples for each channel.
    uint32_t key_status;                    // Key status for each channel,bitx =1 release =0 press  x=0~(KEY_NUM-1)
    uint32_t key_status_pre;                // Last key status
    uint32_t KeyHoldCnt[KEY_NUM];           // The hold time when key pressed,reserved
    /*for test*/
    uint32_t MaxPressSum[KEY_NUM];
    uint32_t MinPressSum[KEY_NUM];
    uint32_t MaxReleaseSum[KEY_NUM];
    uint32_t MinReleaseSum[KEY_NUM];
} TSC_ETR_KEY_PARA;


void BSP_TSC_HwInit(void);
void BSP_TSC_AutoAdjust(void);
void BSP_TSC_HwEnable(void);
void BSP_TSC_ConfigInt(void);
uint32_t BSP_TSC_GetKeyNum(void);
void BSP_TSC_GpioInit(void);

void BSP_TSC_SW_Init(void);
void BSP_TSC_KeyCheck(void);
void BSP_TSC_KeyPrint(uint32_t current_key, uint32_t last_key);
void BSP_TSC_TimIrqCheck(void);

#endif /* __TSCKEY_H__ */

