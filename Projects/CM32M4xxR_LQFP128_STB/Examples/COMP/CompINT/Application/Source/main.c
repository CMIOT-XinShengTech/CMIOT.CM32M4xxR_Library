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
#include "log.h"
#include "led.h"

/** @addtogroup CM32M4xxR_StdPeriph_Examples
 * @{
 */

/** @addtogroup TIM_Input_Capture
 * @{
 */

void RCC_Configuration(void);
void GPIO_Configuration(void);
void COMP_Configuratoin(void);
void EXTI_Configuration(void);
void ECLIC_Configuration(void);
void ChangeVmVp(void);

/**
 * @brief  Main function
 */
int main(void)
{
	log_init();
    /* System Clocks Configuration */
    RCC_Configuration();

    /* ECLIC configuration */
    ECLIC_Configuration();

    /* GPIO configuration ------------------------------------------------------*/
    GPIO_Configuration();

    /* COMP configuration ------------------------------------------------------*/
    COMP_Configuratoin();

	/* TIM configuration ------------------------------------------------------*/
    EXTI_Configuration();
    printf("\r\n example of compINT. \r\n");
    /* Enable global interrupt */
    __enable_irq();
    while (1)
    {
    	ChangeVmVp();
    }
}

/**
 * @brief  Self Generate Puls ,by skip line connect to vp and vm if need.
 */
void ChangeVmVp(void)
{
	delay_ms(5000);
	/*
	 * the high 16 bits[16:31], set 1 to clear the port pin(0:15).
	 * the low 16 bits[0:15],set 1 to set the port pin(0:15).
	*/
    GPIO_SetClearBits(GPIOC, (GPIO_PIN_15<<16)|GPIO_PIN_14);
}

/**
 * @brief  Configures the comp module.
 */
void COMP_Configuratoin(void)
{
    COMP_InitType COMP_Initial;

    /*Set dac2,dac1. because dac1/PA4 is share pin line,so only PB0 puls 0/1, can find out puls*/
    COMP_SetRefScl(16, true, 32, true);
    /*Initial comp*/
    COMP_StructInit(&COMP_Initial);
    COMP_Initial.InpSel     = COMP1_CTRL_INPSEL_PB10;
    COMP_Initial.InmSel     = COMP1_CTRL_INMSEL_DAC2_PA5;
    COMP_Initial.SampWindow = 31;       //(0~31)
    COMP_Initial.Thresh     = 12;       //Thresh should be greater than half of SampWindow and should be less than SampWindow at the same time.
	COMP_Init(COMP1, &COMP_Initial);
	COMP_SetIntEn(COMP_INTEN_CMP1IEN);
    COMP_Enable(COMP1, ENABLE);
}


/**
 * @brief  Configures the different system clocks.
 */
void RCC_Configuration(void)
{
    /* TIM3 clock enable */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_COMP | RCC_APB1_PERIPH_COMP_FILT | RCC_APB1_PERIPH_TIM3, ENABLE);

    /* GPIOA and GPIOB clock enable */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO | RCC_APB2_PERIPH_GPIOA|RCC_APB2_PERIPH_GPIOB|RCC_APB2_PERIPH_GPIOC, ENABLE);

}

/**
 * @brief  Configure the GPIOD Pins.
 */
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    /* TIM3 channel 2 pin (PA.07) configuration */
    GPIO_InitStructure.Pin        = GPIO_PIN_10;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.Pin = GPIO_PIN_5;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // PC14,PC15
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.Pin       = GPIO_PIN_14 | GPIO_PIN_15;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.Pin       = GPIO_PIN_11;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_ConfigPinRemap(GPIO_RMP2_COMP1,ENABLE);//GPIO_RMP3_COMP1
}


/**
 * @brief  Configures the tim module.
 */
void TIM_Configuratoin(void)
{
	TIM_ICInitType TIM_ICInitStructure;
	TIM_TimeBaseInitType TIM_TimeBaseStructure;

	/* Time base configuration */
    TIM_TimeBaseStructure.Period    = 65535;
    TIM_TimeBaseStructure.Prescaler = 0;
    TIM_TimeBaseStructure.ClkDiv    = 0;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
	TIM_TimeBaseStructure.CapCh1FromCompEn = ENABLE;

    TIM_InitTimeBase(TIM3, &TIM_TimeBaseStructure);

	TIM_ICInitStructure.Channel     = TIM_CH_1;
    TIM_ICInitStructure.IcPolarity  = TIM_IC_POLARITY_RISING;//TIM_IC_POLARITY_RISING;
    TIM_ICInitStructure.IcSelection = TIM_IC_SELECTION_DIRECTTI;
    TIM_ICInitStructure.IcPrescaler = TIM_IC_PSC_DIV1;
    TIM_ICInitStructure.IcFilter    = 0x0;

    TIM_ICInit(TIM3, &TIM_ICInitStructure);

    /* TIM enable counter */
    TIM_Enable(TIM3, ENABLE);

    /* Enable the CC2 Interrupt Request */
    TIM_ConfigInt(TIM3, TIM_INT_CC1, ENABLE);
}


void EXTI_Configuration(void)
{
	EXTI_InitType EXTI_InitStructure;

	/* Configure Button EXTI line */
    EXTI_InitStructure.EXTI_Line    = EXTI_LINE21;
    EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;//EXTI_Trigger_Rising_Falling;//EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
}


/**
 * @brief  Configure ECLIC.
 */
void ECLIC_Configuration(void)
{
    /* Enable the TIM3 Interrupt */
	ECLIC_SetLevelIRQ(COMP_1_2_3_IRQn, 0);
	ECLIC_SetPriorityIRQ(COMP_1_2_3_IRQn, 1);
	ECLIC_SetTrigIRQ(COMP_1_2_3_IRQn, ECLIC_LEVEL_TRIGGER);
	ECLIC_EnableIRQ(COMP_1_2_3_IRQn);
}

/**
 * @}
 */

/**
 * @}
 */
