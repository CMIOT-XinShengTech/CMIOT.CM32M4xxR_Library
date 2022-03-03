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

#include "main.h"
#include "bsp.h"

/** @addtogroup CM32M4xxR_StdPeriph_Examples
 * @{
 */

/** @addtogroup TIM_7PWM_Output
 * @{
 */

TIM_TimeBaseInitType TIM_TimeBaseStructure;
TIM_OCInitType TIM_OCInitStructure;
uint16_t TimerPeriod   = 0;
uint16_t Channel1Pulse = 0;
uint16_t Channel2Pulse = 0;
uint16_t Channel3Pulse = 0;
uint16_t Channel4Pulse = 0;

void RCC_Configuration(void);
void GPIO_Configuration(void);
void WritePuls(void);

#define	CC4_GPIO	(0)	/* TIM1 CH4 as GPIO or TIM_Output */

/**
 * @brief   Initialize TIMx(TIM1 or TIM8) function
 */
void TIM_Intial(TIM_Module* TIMx)
{
    /* TIMx Configuration ---------------------------------------------------
    Generate 7 PWM signals with 4 different duty cycles:
    TIM1CLK = PCLK2 = SystemCoreClock, Prescaler = 0, TIM1 counter clock = SystemCoreClock
    SystemCoreClock is set to 8 MHz

    The objective is to generate 7 PWM signal at 17.57 KHz:
     - TIMx_Period = (SystemCoreClock / 17570) - 1
    The channel 1 and channel 1N duty cycle is set to 50%
    The channel 2 and channel 2N duty cycle is set to 37.5%
    The channel 3 and channel 3N duty cycle is set to 25%
    The channel 4 duty cycle is set to 12.5%
    The Timer pulse is calculated as follows:
     - ChannelxPulse = DutyCycle * (TIM1_Period + 1) / 100
    ----------------------------------------------------------------------- */
    /* Compute the value to be set in AR register to generate signal frequency at 17.57 KHz */
    TimerPeriod = (SystemCoreClock / 17570 ) - 1;

    /* Compute CCDAT1 value to generate a duty cycle at 50% for channel 1 and 1N */
    Channel1Pulse = (uint16_t)(((uint32_t)5 * (TimerPeriod + 1)) / 10);

    /* Compute CCDAT2 value to generate a duty cycle at 37.5%  for channel 2 and 2N */
    Channel2Pulse = (uint16_t)(((uint32_t)375 * (TimerPeriod + 1)) / 1000);

    /* Compute CCDAT3 value to generate a duty cycle at 25%  for channel 3 and 3N */
    Channel3Pulse = (uint16_t)(((uint32_t)25 * (TimerPeriod + 1)) / 100);

    /* Compute CCDAT4 value to generate a duty cycle at 12.5%  for channel 4 */
    Channel4Pulse = (uint16_t)(((uint32_t)125 * (TimerPeriod + 1)) / 1000);

    /* Time Base configuration */
    TIM_TimeBaseStructure.Prescaler = 0;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
    TIM_TimeBaseStructure.Period    = TimerPeriod;
    TIM_TimeBaseStructure.ClkDiv    = 0;
    TIM_TimeBaseStructure.RepetCnt  = 0;

    TIM_InitTimeBase(TIMx, &TIM_TimeBaseStructure);

    /* Channel 1, 2,3 and 4 Configuration in PWM mode */
    TIM_OCInitStructure.OcMode       = TIM_OCMODE_PWM2;
    TIM_OCInitStructure.OutputState  = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.OutputNState = TIM_OUTPUT_NSTATE_ENABLE;
    TIM_OCInitStructure.Pulse        = Channel1Pulse;
    TIM_OCInitStructure.OcPolarity   = TIM_OC_POLARITY_LOW;
    TIM_OCInitStructure.OcNPolarity  = TIM_OCN_POLARITY_LOW;
    TIM_OCInitStructure.OcIdleState  = TIM_OC_IDLE_STATE_SET;
    TIM_OCInitStructure.OcNIdleState = TIM_OC_IDLE_STATE_RESET;
    TIM_InitOc1(TIMx, &TIM_OCInitStructure);

    TIM_OCInitStructure.Pulse = Channel2Pulse;
    TIM_InitOc2(TIMx, &TIM_OCInitStructure);

    TIM_OCInitStructure.Pulse = Channel3Pulse;
    TIM_InitOc3(TIMx, &TIM_OCInitStructure);

    TIM_OCInitStructure.Pulse = Channel4Pulse;
    TIM_InitOc4(TIMx, &TIM_OCInitStructure);

    /* TIMx counter enable */
    TIM_Enable(TIMx, ENABLE);

    /* TIMx Main Output Enable */
    TIM_EnableCtrlPwmOutputs(TIMx, ENABLE);
}

/**
 * @brief   Main function
 */
int main(void)
{
    /* System Clocks Configuration */
    RCC_Configuration();

    /* GPIO Configuration */
    GPIO_Configuration();

    TIM_Intial(TIM1);
    TIM_Intial(TIM8);

    while (1)
    {
#if CC4_GPIO
        WritePuls();
#endif
    }
}

void WritePuls(void)
{
    GPIO_SetBits(GPIOA, GPIO_PIN_11);

    {
        int i = 0;
        while (i++ < 100)
            ;
    }

    GPIO_ResetBits(GPIOA, GPIO_PIN_11);

    {
        int i = 0;
        while (i++ < 100)
            ;
    }
}


/**
 * @brief  Configures the different system clocks.
 */
void RCC_Configuration(void)
{
	/* PCLK1 = PCLK2 = HCLK = SYSCLK */

    /* GPIOA, GPIOB, GPIOC, GPIOD, GPIOE and AFIO clocks enable */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_GPIOC |
    						RCC_APB2_PERIPH_GPIOD | RCC_APB2_PERIPH_GPIOE | RCC_APB2_PERIPH_AFIO,
                            ENABLE);

    /* TIM1, TIM8 clocks enable */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_TIM1 | RCC_APB2_PERIPH_TIM8, ENABLE);

    /* TIM1 and TIM8 stop working when the core stops in debug mode */
	DBG_ConfigPeriph(DBG_TIM1_STOP | DBG_TIM8_STOP , ENABLE);
}

/**
 * @brief  Configure the TIM1 Pins.
 */
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    /* GPIOA Configuration: TIM1 Channel 1, 2 and 3 as alternate function push-pull */
    GPIO_InitStructure.Pin        = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* GPIOB Configuration: TIM1 Channel 1N, 2N and 3N as alternate function push-pull */
    GPIO_InitStructure.Pin = GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* GPIOA Configuration: TIM1 Channel 4 as alternate function push-pull */
    GPIO_InitStructure.Pin = GPIO_PIN_11;
#if CC4_GPIO
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
#endif
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* GPIOC Configuration: TIM8 Channel 1, 2, 3 and 4 as alternate function push-pull */
#if CC4_GPIO
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; /* Restore original settings */
#endif

    GPIO_InitStructure.Pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    /* GPIOA Configuration: TIM8 Channel 1N as alternate function push-pull */
    GPIO_InitStructure.Pin = GPIO_PIN_7;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* GPIOB Configuration: TIM8 Channel 2N and 3N as alternate function push-pull */
    GPIO_InitStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}


/**
 * @}
 */

/**
 * @}
 */
