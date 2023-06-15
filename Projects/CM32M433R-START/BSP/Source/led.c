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
 * @file led.c
 * @author CMIOT Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */
#include "nuclei_sdk_soc.h"
#include "led.h"

static uint8_t RGBDuty[3];
static uint16_t DutyCnt;

/**
 * @brief Configures LED GPIO.
 * @param GPIOx x can be A to G to select the GPIO port.
 * @param Pin This parameter can be GPIO_PIN_0 ~ GPIO_PIN_15.
 */
void LedInit(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIO_InitType GPIO_InitStructure;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    /* Enable the GPIO Clock */
    if (GPIOx == GPIOA)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
    }
    else if (GPIOx == GPIOB)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
    }
    else if (GPIOx == GPIOC)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);
    }
    else if (GPIOx == GPIOD)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOD, ENABLE);
    }
    else if (GPIOx == GPIOE)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOE, ENABLE);
    }
    else if (GPIOx == GPIOF)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOF, ENABLE);
    }
    else
    {
        if (GPIOx == GPIOG)
        {
            RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOG, ENABLE);
        }
    }

    /* Configure the GPIO pin */
    if (Pin <= GPIO_PIN_ALL)
    {
        GPIO_InitStructure.Pin        = Pin;
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOx, &GPIO_InitStructure);
    }
    LedOff(GPIOx, Pin);

}

/**
 * @brief Turns selected Led on.
 * @param GPIOx x can be A to G to select the GPIO port.
 * @param Pin This parameter can be GPIO_PIN_0 ~ GPIO_PIN_15.
 */
void LedOn(GPIO_Module* GPIOx, uint16_t Pin)
{
	if(GPIOB == GPIOx)
	{
		GPIO_WriteBit(GPIOx, Pin, Bit_SET);
	}
	else
	{
		GPIO_WriteBit(GPIOx, Pin, Bit_RESET);
	}
}

/**
 * @brief Turns selected Led Off.
 * @param GPIOx x can be A to G to select the GPIO port.
 * @param Pin This parameter can be GPIO_PIN_0 ~ GPIO_PIN_15.
 */
void LedOff(GPIO_Module* GPIOx, uint16_t Pin)
{
	if(GPIOB == GPIOx)
	{
		GPIO_WriteBit(GPIOx, Pin, Bit_RESET);
	}
	else
	{
		GPIO_WriteBit(GPIOx, Pin, Bit_SET);
	}
}

/**
 * @brief Turns selected Led on or off.
 * @param GPIOx x can be A to G to select the GPIO port.
 * @param Pin This parameter can be one of the following values:
 *  @arg GPIO_PIN_0 ~ GPIO_PIN_15: set related pin high(LED off)
 *  @arg (GPIO_PIN_0 << 16) ~ (GPIO_PIN_15 << 16): clear related pin low(LED on)
 */
void LedOnOff(GPIO_Module* GPIOx, uint32_t Pin)
{
	uint32_t temp;
	if(GPIOB == GPIOx)
	{
		GPIO_SetClearBits(GPIOx, Pin);
	}
	else
	{
		temp = Pin >> 16 | Pin << 16;
		GPIO_SetClearBits(GPIOx, Pin);
	}
}

/**
 * @brief Toggles the selected Led.
 * @param GPIOx x can be A to G to select the GPIO port.
 * @param Pin This parameter can be GPIO_PIN_0 ~ GPIO_PIN_15.
 */
void LedBlink(GPIO_Module* GPIOx, uint16_t Pin)
{
	GPIO_Write(GPIOx,GPIO_ReadOutputData(GPIOx)^Pin);
}

/**
 * @brief Init timer x for PWM output to drive RGBLED.
 *        LedInit should be used before.
 * @param TIMx: TIM1 ~ TIM8
 * @param Freq: PWM Output Frequency。The recommended value is 70Hz or higher
 * @retval An Error Status enumuration value:
 * - LED_ERROR_OK: PWM init success
 * - LED_ERROR_PARA: Parameter error
 */
LED_ErrorTypeDef RGBLEDPwmInit(TIM_Module* TIMx, uint32_t Freq)
{
	TIM_TimeBaseInitType TIM_TimeBaseStructure;
	RCC_ClocksType RCC_ClockValue = {0};
	uint16_t PrescalerValue = 0;
	IRQn_Type IrqType;
	uint32_t TimFreq;

	/* Get the Clock of RCC*/
	RCC_GetClocksFreqValue(&RCC_ClockValue);

	switch ((uint32_t)TIMx)
	{
		case (uint32_t)TIM1:
			RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_TIM1, ENABLE);
			IrqType = TIM1_UP_IRQn;
			break;
		case (uint32_t)TIM2:
			RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM2, ENABLE);
			IrqType = TIM2_IRQn;
			break;
		case (uint32_t)TIM3:
			RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM3, ENABLE);
			IrqType = TIM3_IRQn;
			break;
		case (uint32_t)TIM4:
			RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM4, ENABLE);
			IrqType = TIM4_IRQn;
			break;
		case (uint32_t)TIM5:
			RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM5, ENABLE);
			IrqType = TIM5_IRQn;
			break;
		case (uint32_t)TIM6:
			RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM6, ENABLE);
			IrqType = TIM6_IRQn;
			break;
		case (uint32_t)TIM7:
			RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM7, ENABLE);
			IrqType = TIM7_IRQn;
			break;
		case (uint32_t)TIM8:
			RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_TIM8, ENABLE);
			IrqType = TIM8_UP_IRQn;
			break;
		default:
			return LED_ERROR_PARA;
			break;
	}

	if((TIMx == TIM2) || (TIMx == TIM3) || (TIMx == TIM4) ||(TIMx == TIM5) || (TIMx == TIM6) || (TIMx == TIM7))
	{
		if(RCC_GetPclk1Psc() == RCC_HCLK_DIV1)
		{
			TimFreq = RCC_ClockValue.Pclk1Freq;
		}
		else
		{
			TimFreq = RCC_ClockValue.Pclk1Freq * 2;
		}
	}
	else if((TIMx == TIM1) || (TIMx == TIM8))
	{
		if(RCC_GetTim18Clk() == RCC_TIM18CLK_SRC_SYSCLK)
		{
			TimFreq = RCC_ClockValue.SysclkFreq;
		}
		else
		{
			if(RCC_GetPclk2Psc() == RCC_HCLK_DIV1)
			{
				TimFreq = RCC_ClockValue.Pclk2Freq;
			}
			else
			{
				TimFreq = RCC_ClockValue.Pclk2Freq * 2;
			}
		}
	}
	else
	{
		return LED_ERROR_PARA;
	}

	/* Compute the Timer prescaler value according to TIMER2_CNT_CLK = (PCLK1*2 / (PrescalerValue + 1))*/
	PrescalerValue = (uint16_t)(TimFreq / (Freq * 256 * 100)) - 1;

	TIM_InitTimBaseStruct(&TIM_TimeBaseStructure);
	/* Time base configuration */
	TIM_TimeBaseStructure.Period    = 99; /* Max value to guarantee continuous counting */
	TIM_TimeBaseStructure.Prescaler = PrescalerValue;
	TIM_TimeBaseStructure.ClkDiv    = 0;
	TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;

	TIM_InitTimeBase(TIMx, &TIM_TimeBaseStructure);
	/* TIM IT enable */
	TIM_ConfigInt(TIMx, TIM_INT_UPDATE , ENABLE);

	/* Enable Interrupt */
	__enable_irq();

	/* Enable the TIM2 Interrupt */
	ECLIC_SetLevelIRQ(IrqType, 0);
	ECLIC_SetPriorityIRQ(IrqType, 1);
	ECLIC_SetTrigIRQ(IrqType, ECLIC_LEVEL_TRIGGER);
	ECLIC_EnableIRQ(IrqType);

	return LED_ERROR_OK;
}

/**
 * @brief Configure the RGB Value.
 * @param Red Value(0~255)
 * @param Green Value(0~255)
 * @param Blue Value(0~255)
 */
void RGBLEDValueCfg(uint8_t Red, uint8_t Green, uint8_t Blue)
{
	RGBDuty[0] = Red;
	RGBDuty[1] = Green;
	RGBDuty[2] = Blue;
}

/**
 * @brief Start RGB LED PWM output as RGB value.
 * @param TIMx: TIM1 ~ TIM8
 */
void RGBLEDPwmStart(TIM_Module* TIMx)
{
	DutyCnt = 0;
	TIM_Enable(TIMx, ENABLE);
}

/**
 * @brief Stop RGB LED PWM output as RGB value.
 * @param TIMx: TIM1 ~ TIM8
 */
void RGBLEDPwmStop(TIM_Module* TIMx)
{
	TIM_Enable(TIMx, DISABLE);
	LedOff(RGBLED_R_PORT, RGBLED_R_PIN);
	LedOff(RGBLED_G_PORT, RGBLED_G_PIN);
	LedOff(RGBLED_B_PORT, RGBLED_B_PIN);
}

/**
 * @brief Interrupt handler
          Please put it in update interrupt handling of TIMx_IRQHandler .
 */
void RGBLEDIntHandle(void)
{
	DutyCnt++;
	if(DutyCnt > 254)
	{
		DutyCnt = 0;
		LedOn(RGBLED_R_PORT, RGBLED_R_PIN);
		LedOn(RGBLED_G_PORT, RGBLED_G_PIN);
		LedOn(RGBLED_B_PORT, RGBLED_B_PIN);
	}

	if(DutyCnt == RGBDuty[0])
	{
		LedOff(RGBLED_R_PORT, RGBLED_R_PIN);
	}

	if(DutyCnt == RGBDuty[1])
	{
		LedOff(RGBLED_G_PORT, RGBLED_G_PIN);
	}

	if(DutyCnt == RGBDuty[2])
	{
		LedOff(RGBLED_B_PORT, RGBLED_B_PIN);
	}
}
