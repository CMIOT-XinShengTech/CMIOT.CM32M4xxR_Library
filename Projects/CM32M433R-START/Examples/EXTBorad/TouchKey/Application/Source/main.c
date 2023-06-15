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
#include "cm32m4xxr_it.h"

void tim3_init(uint16_t Period, uint16_t Prescaler);
/**
* @brief  Main program.
*/
int main(void)
{
    static uint32_t Cnt1s = 0;

    /*Initialize USART as 115200 bps, 8 bit length,1 stop bit,no check bit,enable receive by interrupt */
    log_init();
    LedInit(RGBLED_B_PORT, RGBLED_B_PIN);
    LedInit(RGBLED_G_PORT, RGBLED_G_PIN);
    LedInit(RGBLED_R_PORT, RGBLED_R_PIN);
    RGBLEDPwmInit(TIM4,100);
    RGBLEDValueCfg(0, 0, 0);
    RGBLEDPwmStart(TIM4);

    LedInit(LED_RED_PORT, LED_RED_PIN);
    LedInit(LED_GREEN_PORT, LED_GREEN_PIN);
    LedInit(LED_BLUE_PORT, LED_BLUE_PIN);

    printf("System Startup ...\n");

    BSP_TSC_SW_Init();

    tim3_init(199, 71); // 72MHz/(71+1)=1MHz;(199+1)/1MHz=200us,with irq

    while (1)       
    {

        while(0==b_10ms_flag);

        b_10ms_flag = 0;

        BSP_TSC_KeyCheck();	  //check key every 10ms
    }
}

/**
 * @brief  Timer3 initialization configuration.
 */
void tim3_init(uint16_t Period, uint16_t Prescaler)
{
    TIM_TimeBaseInitType timInitStruct;

    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM3, ENABLE);

    timInitStruct.Period    = Period;
    timInitStruct.Prescaler = Prescaler;
    timInitStruct.ClkDiv    = 0;
    timInitStruct.CntMode   = TIM_CNT_MODE_UP;
    TIM_InitTimeBase(TIM3, &timInitStruct);

    TIM_ConfigInt(TIM3, TIM_INT_UPDATE, ENABLE);

    /* Configure the ECLIC level and priority Bits */
    ECLIC_SetCfgNlbits(0); /* 0 bits for level, 4 bits for priority */

    /* Enable the USARTy Interrupt */
    ECLIC_SetPriorityIRQ(TIM3_IRQn, 1);
    ECLIC_SetTrigIRQ(TIM3_IRQn, ECLIC_LEVEL_TRIGGER);
    ECLIC_EnableIRQ(TIM3_IRQn);

    /* Enable global interrupt */
    __enable_irq();

    TIM_Enable(TIM3, ENABLE);
}






