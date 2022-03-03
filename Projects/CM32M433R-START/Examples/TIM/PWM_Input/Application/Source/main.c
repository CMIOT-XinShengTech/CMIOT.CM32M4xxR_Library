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

/** @addtogroup TIM_PWM_Input
 * @{
 */

TIM_TimeBaseInitType TIM_TimeBaseStructure;
TIM_OCInitType TIM_OCInitStructure;
TIM_ICInitType TIM_ICInitStructure;
uint16_t PrescalerValue = 0;
RCC_ClocksType RCCClock;

__IO uint16_t DutyCycle = 0;	//DutyCycle = (TIM_GetCap1(TIM3) * 100) / IC2Value;
__IO uint32_t Frequency = 0;	//Frequency = PCLK1*2/72 / IC2Value;

void RCC_Configuration(void);
void GPIO_Configuration(void);
void ECLIC_Configuration(void);


/**
 * @brief   Main function
 */
int main(void)
{

    /*!< At this stage the microcontroller clock setting is already configured,
       this is done through SystemInit() function which is called from startup
       file (startup_cm32m4xxr.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_cm32m4xxr.c file
     */

    /* System Clocks Configuration */
    RCC_Configuration();

    /* ECLIC configuration */
    ECLIC_Configuration();

    /* Configure the GPIO ports */
    GPIO_Configuration();

    /* TIM2 configuration: PWM Output mode ------------------------
     The dutycycle = 2 / (4 + 1) = 40%
     The frequency = 2000 Hz / (4 + 1) = 400 Hz
    ------------------------------------------------------------ */
    /* Compute the prescaler value */
    RCC_GetClocksFreqValue(&RCCClock);
    PrescalerValue = (uint16_t)(RCCClock.Pclk1Freq*2 / 2000) - 1;

    /* Time base configuration */
    TIM_TimeBaseStructure.Period    = 4;
    TIM_TimeBaseStructure.Prescaler = PrescalerValue;
    TIM_TimeBaseStructure.ClkDiv    = TIM_CLK_DIV1;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;

    TIM_InitTimeBase(TIM2, &TIM_TimeBaseStructure);

    /* PWM1 Mode configuration: Channel1 */
    TIM_OCInitStructure.OcMode      = TIM_OCMODE_PWM1;
    TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.Pulse       = 2;
    TIM_OCInitStructure.OcPolarity  = TIM_OC_POLARITY_HIGH;

    TIM_InitOc1(TIM2, &TIM_OCInitStructure);

    /* TIM3 configuration: PWM Input mode ------------------------
     The external signal is connected to TIM3 CH2 pin (PA.01),
     The Rising edge is used as active edge,
     The TIM3 CCDAT2 is used to compute the frequency value
     The TIM3 CCDAT1 is used to compute the duty cycle value
     frequency value =  (PCLK1*2/72)/CCDAT2
     duty cycle value = CCDAT1/CCDAT2
    ------------------------------------------------------------ */

    /* Time base configuration */
    /* TIM3 CLK 1M */
    TIM_TimeBaseStructure.Period    = 65535;
    TIM_TimeBaseStructure.Prescaler = 71;
    TIM_TimeBaseStructure.ClkDiv    = TIM_CLK_DIV1;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;

    TIM_InitTimeBase(TIM3, &TIM_TimeBaseStructure);

    TIM_ICInitStructure.Channel     = TIM_CH_2;
    TIM_ICInitStructure.IcPolarity  = TIM_IC_POLARITY_RISING;
    TIM_ICInitStructure.IcSelection = TIM_IC_SELECTION_DIRECTTI;
    TIM_ICInitStructure.IcPrescaler = TIM_IC_PSC_DIV1;
    TIM_ICInitStructure.IcFilter    = 0x0;

    TIM_ConfigPwmIc(TIM3, &TIM_ICInitStructure);

    /* Select the TIM3 Input Trigger: TI2FP2 */
    TIM_SelectInputTrig(TIM3, TIM_TRIG_SEL_TI2FP2);

    /* Select the slave Mode: Reset Mode */
    TIM_SelectSlaveMode(TIM3, TIM_SLAVE_MODE_RESET);

    /* Enable the Master/Slave Mode */
    TIM_SelectMasterSlaveMode(TIM3, TIM_MASTER_SLAVE_MODE_ENABLE);

    /* TIM3 enable counter */
    TIM_Enable(TIM3, ENABLE);

    /* Enable the CC2 Interrupt Request */
    TIM_ConfigInt(TIM3, TIM_INT_CC2, ENABLE);

    /* Enable global interrupt */
    __enable_irq();

    /* TIM2 enable counter */
    TIM_Enable(TIM2, ENABLE);


    while(1)
    {
	}
}

/**
 * @brief  Configures the different system clocks.
 */
void RCC_Configuration(void)
{
	/* PCLK1 = PCLK2 = HCLK */

    /* TIM3 clock enable */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM2 | RCC_APB1_PERIPH_TIM3, ENABLE);

    /* GPIOA clock enable */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_GPIOC | RCC_APB2_PERIPH_AFIO, ENABLE);
}

/**
 * @brief  Configure the GPIO Pins.
 */
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    /* TIM3 channel 2 pin (PC.07) configuration */
    GPIO_InitStructure.Pin        = GPIO_PIN_7;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_ConfigPinRemap(GPIO_ALL_RMP_TIM3, ENABLE);

    /* TIM2 channel 1 pin (PA.00) */
    GPIO_InitStructure.Pin        = GPIO_PIN_0;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/**
 * @brief  Configure ECLIC.
 */
void ECLIC_Configuration(void)
{
    /* Enable the TIM3 Interrupt */
	ECLIC_SetLevelIRQ(TIM3_IRQn, 0);
	ECLIC_SetPriorityIRQ(TIM3_IRQn, 1);
	ECLIC_SetTrigIRQ(TIM3_IRQn, ECLIC_LEVEL_TRIGGER);
	ECLIC_EnableIRQ(TIM3_IRQn);
}

/**
 * @}
 */

/**
 * @}
 */
