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

/** @addtogroup TIM_OnePulse
 * @{
 */

TIM_TimeBaseInitType TIM_TimeBaseStructure;
TIM_ICInitType TIM_ICInitStructure;
TIM_OCInitType TIM_OCInitStructure;
uint16_t PrescalerValue = 0;

void RCC_Configuration(void);
void GPIO_Configuration(void);
void SendOneTrig(void);
uint16_t gSendTrigEn = 1;

/**
 * @brief  Main function
 */
int main(void)
{
    /* System Clocks Configuration */
    RCC_Configuration();

    /* Configure the GPIO ports */
    GPIO_Configuration();

    /* TIM4 configuration: One Pulse mode ------------------------
     The external signal is connected to TIM4_CH2 pin (PB.07),
     The Rising edge is used as active edge,
     The One Pulse signal is output on TIM4_CH1 pin (PB.06)
     The Pulse defines the delay value
     The (Period -  Pulse) defines the One Pulse value.
     TIM2CLK = SystemCoreClock, we want to get TIM2 counter clock at 8 MHz:
     - Prescaler = (TIM2CLK / TIM2 counter clock) - 1
     The Autoreload value is 65535 (TIM4->AR), so the maximum frequency value
     to trigger the TIM4 input is 8000000 / (65535 + 1) = 122 Hz.

     The Pulse defines the delay value, the delay value is fixed
     to 6.144 ms:
     delay =  CCDAT1 / TIM4 counter clock = 6.144 ms.
     The (Period + 1 - Pulse) defines the One Pulse value,
     the pulse value is fixed to 2.048 ms:
     One Pulse value = (Period + 1 - Pulse) / TIM4 counter clock = 2.048 ms.

    ------------------------------------------------------------ */

    /* Compute the prescaler value */
    PrescalerValue = (uint16_t)(SystemCoreClock / 8000000) - 1;

    /* Time base configuration */
    TIM_TimeBaseStructure.Period    = 65535;
    TIM_TimeBaseStructure.Prescaler = PrescalerValue;
    TIM_TimeBaseStructure.ClkDiv    = 0;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;

    TIM_InitTimeBase(TIM4, &TIM_TimeBaseStructure);

    /* TIM4 PWM2 Mode configuration: Channel1 */
    TIM_OCInitStructure.OcMode      = TIM_OCMODE_PWM2;
    TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.Pulse       = 49152;
    TIM_OCInitStructure.OcPolarity  = TIM_OC_POLARITY_HIGH;

    TIM_InitOc1(TIM4, &TIM_OCInitStructure);

    /* TIM4 configuration in Input Capture Mode */
    TIM_InitIcStruct(&TIM_ICInitStructure);

    TIM_ICInitStructure.Channel     = TIM_CH_2;
    TIM_ICInitStructure.IcPolarity  = TIM_IC_POLARITY_RISING;
    TIM_ICInitStructure.IcSelection = TIM_IC_SELECTION_DIRECTTI;
    TIM_ICInitStructure.IcPrescaler = TIM_IC_PSC_DIV1;
    TIM_ICInitStructure.IcFilter    = 0;

    TIM_ICInit(TIM4, &TIM_ICInitStructure);

    /* One Pulse Mode selection */
    TIM_SelectOnePulseMode(TIM4, TIM_OPMODE_SINGLE);

    /* Input Trigger selection */
    TIM_SelectInputTrig(TIM4, TIM_TRIG_SEL_TI2FP2);

    /* Slave Mode selection: Trigger Mode */
    TIM_SelectSlaveMode(TIM4, TIM_SLAVE_MODE_TRIG);

    while (1)
    {
        SendOneTrig();
    }
}

/**
 * @brief  Send one trig byself.
 */
void SendOneTrig(void)
{
    if (gSendTrigEn)
    {
        gSendTrigEn = 0;

        GPIO_SetBits(GPIOA, GPIO_PIN_3);

        {
            uint32_t i;
			i = 0;
            while (i++ < 10)
                ;
        }

        GPIO_ResetBits(GPIOA, GPIO_PIN_3);
    }
}

/**
 * @brief  Configures the different system clocks.
 */
void RCC_Configuration(void)
{
	/* PCLK1 = PCLK2 = HCLK = SYSCLK */

    /* TIM4 clock enable */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM4, ENABLE);

    /* GPIOB clock enable */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOD | RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_AFIO, ENABLE);
}

/**
 * @brief  Configure the GPIOD Pins.
 */
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    /* TIM4_CH1 pin (PB.06) configuration as out */
    GPIO_InitStructure.Pin        = GPIO_PIN_12;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

    GPIO_Init(GPIOD, &GPIO_InitStructure);

    /* TIM4_CH2 pin (PB.07) configuration as trig */
    GPIO_InitStructure.Pin       = GPIO_PIN_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    GPIO_ConfigPinRemap(GPIO_RMP_TIM4, ENABLE);

    /* PA.03 configuration as send trig */
    GPIO_InitStructure.Pin       = GPIO_PIN_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/**
 * @}
 */

/**
 * @}
 */
