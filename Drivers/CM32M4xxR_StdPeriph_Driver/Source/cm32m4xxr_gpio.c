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
 * @file cm32m4xxr_gpio.c
 * @author CMIOT Firmware Team
 * @brief Source file containing functions prototypes of GPIO stdperiph library.
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */
#include "nuclei_sdk_soc.h"


/** @addtogroup CM32M4xxR_StdPeriph_Driver
 * @{
 */

/** @defgroup GPIO GPIO
 * @brief GPIO driver modules
 * @{
 */

#ifdef	DRIVER_MODULE_ENABLED_GPIO

/** @defgroup GPIO_Private_Constants GPIO Private Constants
 * @{
 */

#define AFIO_ECTRL_ADDR					(AFIO_BASE + 0x00UL)	/* AFIO_ECTRL register address */

#define LSB_MASK						((uint16_t) 0xFFFF)
#define REGNUM_MASK						((uint16_t) 0x7C00)
#define POS_MASK						((uint16_t) 0x03E0)
#define BITWIDTH_MASK					((uint16_t) 0x0018)
#define VAL_MASK						((uint16_t) 0x0007)
#define DBGAFR_SWJCFG_MASK        		((uint32_t) 0xF8FFFFFF)
/**
 * @}
 */

/** @defgroup GPIO_Private_Functions GPIO Private Functions
 * @{
 */
static void ConfigPinRemap(uint16_t BitSeg, FunctionalState Cmd)
{
  uint32_t regnum;
  uint32_t pos;
  uint32_t bitwidth;
  uint32_t val;
  uint32_t tmp;

  uint32_t tmpregister	= 0x00;

  /* Check the parameters */
  if(BitSeg == 0)
  {
	  return;
  }

  regnum = (BitSeg & REGNUM_MASK)>>10;
  pos = (BitSeg & POS_MASK)>>5;
  bitwidth = (BitSeg & BITWIDTH_MASK)>>3;
  val = BitSeg & VAL_MASK;

  /* Check RmpPin relate AFIO RMP_CFG */
  switch(regnum)
  {
  	  case 0:
  		  tmpregister = AFIO->RMP_CFG;
  		  tmpregister |= ~DBGAFR_SWJCFG_MASK;  /* SW_JTAG_CFG is write only, the read value is undefined. write 7 has no effect on the original value */
  		  break;
	  case 2:
		  tmpregister = AFIO->RMP_CFG3;
		  break;
	  case 3:
		  tmpregister = AFIO->RMP_CFG4;
		  break;
	  case 4:
		  tmpregister = AFIO->RMP_CFG5;
		  break;
	  default:
		  return;
  }

  /* find the bit field and clear it */
  switch(bitwidth)
  {
  	  case 1:
  		  tmp = ((uint32_t)0x01) << pos;
  		  tmpregister &= ~tmp;
  		  break;
  	  case 2:
  		  tmp = ((uint32_t)0x03) << pos;
  		  tmpregister &= ~tmp;
  		  break;
  	  case 3:
  		  tmp = ((uint32_t)0x07) << pos;
  		  tmpregister &= ~tmp;
  		  if((BitSeg == GPIO_RMP_SW_JTAG_NO_NJTRST) || (BitSeg == GPIO_RMP_SW_JTAG_SW_ENABLE) || (BitSeg == GPIO_RMP_SW_JTAG_DISABLE))
  		  {
  			  AFIO->RMP_CFG &= DBGAFR_SWJCFG_MASK;
  		  }
  		  break;
  	  default:
  		  return;

  }

  /* write the setting value to the bit field. if Cmd is disable,keep the clear value */
  if (Cmd != DISABLE)
  {
	  tmpregister |= (val << pos);
  }

/* configuration AFIO RMP_CFG~RMP_CFG5 */
  switch(regnum)
  {
  	  case 0:
  		  AFIO->RMP_CFG = tmpregister;
  		  break;
	  case 2:
		  AFIO->RMP_CFG3 = tmpregister;
		  break;
	  case 3:
		  AFIO->RMP_CFG4 = tmpregister;
		  break;
	  case 4:
		  AFIO->RMP_CFG5 = tmpregister;
		  break;
  }
}

/**
 * @}
 */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup GPIO_Exported_Functions
  * @{
  */

/**
 * @brief Deinitializes the GPIOx peripheral registers to their default reset values.
 * @param GPIOx where x can be (A..G) to select the GPIO peripheral.
 */
void GPIO_DeInit(GPIO_Module* GPIOx)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

	/* Reset GPIOx */
    if (GPIOx == GPIOA)
    {
        RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_GPIOA, ENABLE);
        RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_GPIOA, DISABLE);
    }
    else if (GPIOx == GPIOB)
    {
        RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_GPIOB, ENABLE);
        RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_GPIOB, DISABLE);
    }
    else if (GPIOx == GPIOC)
    {
        RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_GPIOC, ENABLE);
        RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_GPIOC, DISABLE);
    }
    else if (GPIOx == GPIOD)
    {
        RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_GPIOD, ENABLE);
        RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_GPIOD, DISABLE);
    }
    else if (GPIOx == GPIOE)
    {
        RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_GPIOE, ENABLE);
        RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_GPIOE, DISABLE);
    }
    else if (GPIOx == GPIOF)
    {
        RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_GPIOF, ENABLE);
        RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_GPIOF, DISABLE);
    }
    else if (GPIOx == GPIOG)
    {
        RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_GPIOG, ENABLE);
        RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_GPIOG, DISABLE);
    }
    else
    {

    }
}

/**
 * @brief Deinitializes the Alternate Functions (remap, event control
 *   and EXTI configuration) registers to their default reset values.
 */
void GPIO_AFIODeInit(void)
{
    RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_AFIO, ENABLE);
    RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_AFIO, DISABLE);
}

/**
 * @brief Initializes the GPIOx peripheral according to the specified
 *        parameters in the GPIO_InitStruct.
 * @param GPIOx where x can be (A..G) to select the GPIO peripheral.
 * @param GPIO_InitStruct pointer to a GPIO_InitType structure that
 *         contains the configuration information for the specified GPIO peripheral.
 */
void GPIO_Init(GPIO_Module* GPIOx, GPIO_InitType* GPIO_InitStruct)
{
    uint32_t currentmode	= 0x00;
	uint32_t currentpin		= 0x00;
	uint32_t pinpos			= 0x00;
	uint32_t pos			= 0x00;
    uint32_t tmpregister	= 0x00;
	uint32_t pinmask		= 0x00;
	
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_MODE(GPIO_InitStruct->GPIO_Mode));
    assert_param(IS_GPIO_PIN(GPIO_InitStruct->Pin));

    /*---------------------------- GPIO Mode Configuration -----------------------*/
    currentmode = ((uint32_t) GPIO_InitStruct->GPIO_Mode) & ((uint32_t) 0x0F);
    if ((((uint32_t) GPIO_InitStruct->GPIO_Mode) & ((uint32_t) 0x10)) != 0x00) /* Output mode */
    {
        /* Check the parameters */
        assert_param(IS_GPIO_SPEED(GPIO_InitStruct->GPIO_Speed));
		
        /* Output mode */
        currentmode |= ((uint32_t) GPIO_InitStruct->GPIO_Speed);
    }
	
    /*---------------------------- GPIO PL_CFG Configuration ------------------------*/
    /* Configure the eight low port pins */
    if (((uint32_t)GPIO_InitStruct->Pin & ((uint32_t)0x00FF)) != 0x00)
    {
        tmpregister = GPIOx->PL_CFG;
        for (pinpos = 0x00; pinpos < 0x08; pinpos++)
        {
			/* Pin logic position to pin bit-mask position */
            pos = ((uint32_t) 0x01) << pinpos;
			
            /* Get the port pins position */
            currentpin = (GPIO_InitStruct->Pin) & pos;
            if (currentpin == pos)
            {
				/* Calculate the corresponding low control register bits position */
                pos = pinpos << 2;
				
                /* Clear the corresponding low control register bits */
                pinmask = ((uint32_t) 0x0F) << pos;
                tmpregister &= ~pinmask;
				
                /* Write the mode configuration in the corresponding bits */
                tmpregister |= (currentmode << pos);
				
                /* Reset the corresponding POD bit */
                if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
                {
                    GPIOx->PBC = (((uint32_t) 0x01) << pinpos); /* Input Pull-Down Mode */
                }
                else
                {
                    /* Set the corresponding POD bit */
                    if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU)
                    {
                        GPIOx->PBSC = (((uint32_t) 0x01) << pinpos); /* Input Pull-Up Mode */
                    }
                }
            }
        }

        GPIOx->PL_CFG = tmpregister;
    }
    /*---------------------------- GPIO PH_CFG Configuration ------------------------*/
    /* Configure the eight high port pins */
    if (GPIO_InitStruct->Pin > 0x00FF)
    {
        tmpregister = GPIOx->PH_CFG;
        for (pinpos = 0x00; pinpos < 0x08; pinpos++)
        {
            pos = (((uint32_t) 0x01) << (pinpos + 0x08));
			
            /* Get the port pins position */
            currentpin = ((GPIO_InitStruct->Pin) & pos);
            if (currentpin == pos)
            {
                pos = pinpos << 2;
				
                /* Clear the corresponding high control register bits */
                pinmask = ((uint32_t) 0x0F) << pos;
                tmpregister &= ~pinmask;
				
                /* Write the mode configuration in the corresponding bits */
                tmpregister |= (currentmode << pos);
				
                /* Reset the corresponding POD bit */
                if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
                {
                    GPIOx->PBC = (((uint32_t) 0x01) << (pinpos + 0x08));
                }
                /* Set the corresponding POD bit */
                if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU)
                {
                    GPIOx->PBSC = (((uint32_t) 0x01) << (pinpos + 0x08));
                }
            }
        }

        GPIOx->PH_CFG = tmpregister;
    }
}

/**
 * @brief Fills each GPIO_InitStruct member with its default value.
 * @param GPIO_InitStruct pointer to a GPIO_InitType structure which will
 *         be initialized.
 */
void GPIO_InitStruct(GPIO_InitType* GPIO_InitStruct)
{
    /* Reset GPIO init structure parameters values */
    GPIO_InitStruct->Pin        = GPIO_PIN_ALL;
    GPIO_InitStruct->GPIO_Speed = GPIO_INPUT;
    GPIO_InitStruct->GPIO_Mode  = GPIO_Mode_AIN;
}

/**
 * @brief Reads the specified input port pin.
 * @param GPIOx where x can be (A..G) to select the GPIO peripheral.
 * @param Pin specifies the port bit to read.
 *   This parameter can be GPIO_Pin_x where x can be (0..15).
 * @return The input port pin value.
 */
uint8_t GPIO_ReadInputDataBit(GPIO_Module* GPIOx, uint16_t Pin)
{
    uint8_t bitstatus = 0x00;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(Pin));

    if ((GPIOx->PID & Pin) != (uint32_t)Bit_RESET)
    {
        bitstatus = (uint8_t)Bit_SET;
    }
    else
    {
        bitstatus = (uint8_t)Bit_RESET;
    }
	
    return bitstatus;
}

/**
 * @brief  Reads the specified GPIO input data port.
 * @param  GPIOx where x can be (A..G) to select the GPIO peripheral.
 * @return GPIO input data port value.
 */
uint16_t GPIO_ReadInputData(GPIO_Module* GPIOx)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    return ((uint16_t) GPIOx->PID);
}

/**
 * @brief Reads the specified output data port bit.
 * @param GPIOx where x can be (A..G) to select the GPIO peripheral.
 * @param Pin specifies the port bit to read.
 *   This parameter can be GPIO_Pin_x where x can be (0..15).
 * @return The output port pin value.
 */
uint8_t GPIO_ReadOutputDataBit(GPIO_Module* GPIOx, uint16_t Pin)
{
    uint8_t bitstatus = 0x00;
	
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(Pin));

    if ((GPIOx->POD & Pin) != (uint32_t)Bit_RESET)
    {
        bitstatus = (uint8_t)Bit_SET;
    }
    else
    {
        bitstatus = (uint8_t)Bit_RESET;
    }
	
    return bitstatus;
}

/**
 * @brief  Reads the specified GPIO output data port.
 * @param  GPIOx where x can be (A..G) to select the GPIO peripheral.
 * @return GPIO output data port value.
 */
uint16_t GPIO_ReadOutputData(GPIO_Module* GPIOx)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    return ((uint16_t) GPIOx->POD);
}

/**
 * @brief Sets the selected data port bits.
 * @param GPIOx where x can be (A..G) to select the GPIO peripheral.
 * @param Pin specifies the port bits to be written.
 *   This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
 */
void GPIO_SetBits(GPIO_Module* GPIOx, uint16_t Pin)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(Pin));

    GPIOx->PBSC = Pin;
}

/**
 * @brief Sets and clear the bits at the same time.
 * @param GPIOx where x can be (A..G) to select the GPIO peripheral.
 * @param Pin specifies the port bits to be set and clear at the same time.
 *        the high 16 bits[16:31], set 1 to clear the port pin(0:15).
 *        the low 16 bits[0:15],set 1 to set the port pin(0:15).
 *        if set and clear one pin at the same time,it will be set.
 */
void GPIO_SetClearBits(GPIO_Module* GPIOx, uint32_t Pin)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    GPIOx->PBSC = Pin;
}

/**
 * @brief Clears the selected data port bits.
 * @param GPIOx where x can be (A..G) to select the GPIO peripheral.
 * @param Pin specifies the port bits to be written.
 *   This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
 */
void GPIO_ResetBits(GPIO_Module* GPIOx, uint16_t Pin)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(Pin));

    GPIOx->PBC = Pin;
}

/**
 * @brief Sets or clears the selected data port bit.
 * @param GPIOx where x can be (A..G) to select the GPIO peripheral.
 * @param Pin specifies the port bit to be written.
 *   This parameter can be one of GPIO_Pin_x where x can be (0..15).
 * @param BitCmd specifies the value to be written to the selected bit.
 *   This parameter can be one of the Bit_OperateType enum values:
 *     @arg Bit_RESET to clear the port pin
 *     @arg Bit_SET to set the port pin
 */
void GPIO_WriteBit(GPIO_Module* GPIOx, uint16_t Pin, Bit_OperateType BitCmd)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(Pin));
    assert_param(IS_GPIO_BIT_OPERATE(BitCmd));

    if (BitCmd != Bit_RESET)
    {
        GPIOx->PBSC = Pin;
    }
    else
    {
        GPIOx->PBC = Pin;
    }
}

/**
 * @brief Writes data to the specified GPIO data port.
 * @param GPIOx where x can be (A..G) to select the GPIO peripheral.
 * @param PortVal specifies the value to be written to the port output data register.
 */
void GPIO_Write(GPIO_Module* GPIOx, uint16_t PortVal)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    GPIOx->POD = PortVal;
}

/**
 * @brief Locks GPIO Pins configuration registers.
 * @param GPIOx where x can be (A..G) to select the GPIO peripheral.
 * @param Pin specifies the port bit to be written.
 *   This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
 */
void GPIO_ConfigPinLock(GPIO_Module* GPIOx, uint16_t Pin)
{
    uint32_t tmp = ((uint32_t) Pin) | GPIO_PLOCK_CFG_PLOCKK_CFG; /* Bit 16: Lock Key(PLOCKK_CFG) */

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(Pin));

	/* LCKK write sequence: write 1 -> write 0 -> write 1 -> read 0 -> read 1 */
    /* Set LCKK bit */
    GPIOx->PLOCK_CFG = tmp;
	
    /* Reset LCKK bit */
	tmp &= (~GPIO_PLOCK_CFG_PLOCKK_CFG);
    GPIOx->PLOCK_CFG = tmp;
	
    /* Set LCKK bit */
	tmp |= GPIO_PLOCK_CFG_PLOCKK_CFG;
    GPIOx->PLOCK_CFG = tmp;
	
    /* Read LCKK bit*/
    tmp = GPIOx->PLOCK_CFG;
	
    /* Read LCKK bit*/
    tmp = GPIOx->PLOCK_CFG;
}

/**
 * @brief Selects the GPIO pin used as Event output.
 * @param PortSource selects the GPIO port to be used as source
 *   for Event output.
 *   This parameter can be GPIO_PortSourceGPIOx where x can be (A..E).
 * @param PinSource specifies the pin for the Event output.
 *   This parameter can be GPIO_PinSourcex where x can be (0..15).
 */
void GPIO_ConfigEventOutput(uint8_t PortSource, uint8_t PinSource)
{
    uint32_t tmpregister = 0x00;
	
    /* Check the parameters */
    assert_param(IS_GPIO_EVENTOUT_PORT_SOURCE(PortSource));
    assert_param(IS_GPIO_PIN_SOURCE(PinSource));

    tmpregister = AFIO->ECTRL;
	
    /* Clear the PORT_SEL[6:4] and PIN_SEL[3:0] bits */
    tmpregister &= (~(AFIO_ECTRL_PIN_SEL | AFIO_ECTRL_PORT_SEL));
    tmpregister |= ((uint32_t) PortSource << 0x04);
    tmpregister |= PinSource;
    AFIO->ECTRL = tmpregister;
}

/**
 * @brief Enables or disables the Event Output.
 * @param Cmd new state of the Event output.
 *   This parameter can be: ENABLE or DISABLE.
 */
void GPIO_CtrlEventOutput(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

	if(ENABLE == Cmd){
		__AMOOR_W((__IO int32_t *)AFIO_ECTRL_ADDR, AFIO_ECTRL_EOE); /* Atomic OR operation */
	}else{
		__AMOAND_W((__IO int32_t *)AFIO_ECTRL_ADDR, ~AFIO_ECTRL_EOE); /* Atomic AND operation */
	}
}

/**
 * @brief Changes the mapping of the specified pin.
 * @param RmpPin selects the pin to remap.
 *   This parameter can be one of the following values:
 *     @arg GPIO_RMP_SPI1 SPI1 Alternate Function mapping
 *     @arg GPIO_RMP_I2C1 I2C1 Alternate Function mapping
 *     @arg GPIO_RMP_USART1 USART1 Alternate Function mapping
 *     @arg GPIO_RMP_USART2 USART2 Alternate Function mapping
 *     @arg GPIO_PART_RMP_USART3 USART3 Partial Alternate Function mapping
 *     @arg GPIO_ALL_RMP_USART3 USART3 Full Alternate Function mapping
 *     @arg GPIO_PART1_RMP_TIM1 TIM1 Partial Alternate Function mapping
 *     @arg GPIO_PART2_RMP_TIM1 TIM1 Partial Alternate Function mapping
 *     @arg GPIO_ALL_RMP_TIM1 TIM1 Full Alternate Function mapping
 *     @arg GPIO_PART1_RMP_TIM2 TIM2 Partial1 Alternate Function mapping
 *     @arg GPIO_PART2_RMP_TIM2 TIM2 Partial2 Alternate Function mapping
 *     @arg GPIO_ALL_RMP_TIM2 TIM2 Full Alternate Function mapping
 *     @arg GPIO_PART1_RMP_TIM3 TIM3 Partial Alternate Function mapping
 *     @arg GPIO_ALL_RMP_TIM3 TIM3 Full Alternate Function mapping
 *     @arg GPIO_RMP_TIM4 TIM4 Alternate Function mapping
 *     @arg GPIO_RMP1_CAN1 CAN1 Alternate Function mapping
 *     @arg GPIO_RMP2_CAN1 CAN1 Alternate Function mapping
 *     @arg GPIO_RMP_PD01 PD01 Alternate Function mapping
 *     @arg GPIO_RMP_TIM5CH4 LSI connected to TIM5 Channel4 input capture for calibration
 *     @arg GPIO_RMP_ADC1_ETRI ADC1 External Trigger Injected Conversion remapping
 *     @arg GPIO_RMP_ADC1_ETRR ADC1 External Trigger Regular Conversion remapping
 *     @arg GPIO_RMP_ADC2_ETRI ADC2 External Trigger Injected Conversion remapping
 *     @arg GPIO_RMP_ADC2_ETRR ADC2 External Trigger Regular Conversion remapping
 *     @arg GPIO_RMP_SW_JTAG_NO_NJTRST Full SWJ Enabled (JTAG-DP + SW-DP) but without JTRST
 *     @arg GPIO_RMP_SW_JTAG_SW_ENABLE JTAG-DP Disabled and SW-DP Enabled
 *     @arg GPIO_RMP_SW_JTAG_DISABLE Full SWJ Disabled (JTAG-DP + SW-DP)
 *     @arg GPIO_RMP1_CAN2 CAN2 Alternate Function mapping
 *     @arg GPIO_RMP3_CAN2 CAN2 Alternate Function mapping
 *     @arg GPIO_RMP2_QSPI QSPI Alternate Function mapping
 *     @arg GPIO_RMP3_QSPI QSPI Alternate Function mapping
 *     @arg GPIO_RMP1_I2C2 I2C2 Alternate Function mapping
 *     @arg GPIO_RMP3_I2C2 I2C2 Alternate Function mapping
 *     @arg GPIO_RMP2_I2C3 I2C3 Alternate Function mapping
 *     @arg GPIO_RMP3_I2C3 I2C3 Alternate Function mapping
 *     @arg GPIO_RMP1_I2C4 I2C4 Alternate Function mapping
 *     @arg GPIO_RMP3_I2C4 I2C4 Alternate Function mapping
 *     @arg GPIO_RMP1_SPI2 SPI2 Alternate Function mapping
 *     @arg GPIO_RMP2_SPI2 SPI2 Alternate Function mapping
 *     @arg GPIO_RMP1_SPI3 SPI3 Alternate Function mapping
 *     @arg GPIO_RMP2_SPI3 SPI3 Alternate Function mapping
 *     @arg GPIO_RMP1_SPI1 SPI1 Alternate Function mapping
 *     @arg GPIO_RMP2_SPI1 SPI1 Alternate Function mapping
 *     @arg GPIO_RMP3_SPI1 SPI1 Alternate Function mapping
 *     @arg GPIO_RMP1_USART2 USART2 Alternate Function mapping
 *     @arg GPIO_RMP2_USART2 USART2 Alternate Function mapping
 *     @arg GPIO_RMP3_USART2 USART2 Alternate Function mapping
 *     @arg GPIO_RMP1_UART4 UART4 Alternate Function mapping
 *     @arg GPIO_RMP2_UART4 UART4 Alternate Function mapping
 *     @arg GPIO_RMP3_UART4 UART4 Alternate Function mapping
 *     @arg GPIO_RMP1_UART5 UART5 Alternate Function mapping
 *     @arg GPIO_RMP2_UART5 UART5 Alternate Function mapping
 *     @arg GPIO_RMP3_UART5 UART5 Alternate Function mapping
 *     @arg GPIO_RMP2_UART6 UART6 Alternate Function mapping
 *     @arg GPIO_RMP3_UART6 UART6 Alternate Function mapping
 *     @arg GPIO_RMP1_UART7 UART7 Alternate Function mapping
 *     @arg GPIO_RMP3_UART7 UART7 Alternate Function mapping
 *     @arg GPIO_RMP1_TIM8 TIM8 Alternate Function mapping
 *     @arg GPIO_RMP3_TIM8 TIM8 Alternate Function mapping
 *     @arg GPIO_RMP1_COMP1 COMP1 Alternate Function mapping
 *     @arg GPIO_RMP2_COMP1 COMP1 Alternate Function mapping
 *     @arg GPIO_RMP3_COMP1 COMP1 Alternate Function mapping
 *     @arg GPIO_RMP1_COMP2 COMP2 Alternate Function mapping
 *     @arg GPIO_RMP2_COMP2 COMP2 Alternate Function mapping
 *     @arg GPIO_RMP3_COMP2 COMP2 Alternate Function mapping
 *     @arg GPIO_RMP1_COMP3 COMP3 Alternate Function mapping
 *     @arg GPIO_RMP3_COMP3 COMP3 Alternate Function mapping
 *     @arg GPIO_RMP1_COMP4 COMP4 Alternate Function mapping
 *     @arg GPIO_RMP3_COMP4 COMP4 Alternate Function mapping
 *     @arg GPIO_RMP1_COMP5 COMP5 Alternate Function mapping
 *     @arg GPIO_RMP2_COMP5 COMP5 Alternate Function mapping
 *     @arg GPIO_RMP3_COMP5 COMP5 Alternate Function mapping
 *     @arg GPIO_RMP3_UART5 UART5 Alternate Function mapping
 *     @arg GPIO_RMP1_COMP6 COMP6 Alternate Function mapping
 *     @arg GPIO_RMP3_COMP6 COMP6 Alternate Function mapping
 *     @arg GPIO_RMP_COMP7 COMP7 Alternate Function mapping
 *     @arg GPIO_RMP_ADC3_ETRI ADC3_ETRGINJ  Alternate Function mapping
 *     @arg GPIO_RMP_ADC3_ETRR ADC3_ETRGREG  Alternate Function mapping
 *     @arg GPIO_RMP_ADC4_ETRI ADC4_ETRGINJ  Alternate Function mapping
 *     @arg GPIO_RMP_ADC4_ETRR ADC4_ETRGREG  Alternate Function mapping
 *     @arg GPIO_RMP_TSC_OUT_CTRL TSC_OUT_CTRL  Alternate Function mapping
 *     @arg GPIO_RMP_QSPI_XIP_EN QSPI_XIP_EN  Alternate Function mapping
 *     @arg GPIO_RMP_SPI1_NSS SPI1 NSS Alternate Function mapping
 *     @arg GPIO_RMP_SPI2_NSS SPI2 NSS Alternate Function mapping
 *     @arg GPIO_RMP_SPI3_NSS SPI3 NSS Alternate Function mapping
 *     @arg GPIO_RMP_QSPI_MISO QSPI MISO Alternate Function mapping
 *     @arg GPIO_RMP_DET_EN_EGB4 EGB4 Detect Alternate Function mapping
 *     @arg GPIO_RMP_DET_EN_EGB3 EGB3 Detect Alternate Function mapping
 *     @arg GPIO_RMP_DET_EN_EGB2 EGB2 Detect Alternate Function mapping
 *     @arg GPIO_RMP_DET_EN_EGB1 EGB1 Detect Alternate Function mapping
 *     @arg GPIO_RMP_DET_EN_EGBN4 EGBN4 Detect Alternate Function mapping
 *     @arg GPIO_RMP_DET_EN_EGBN3 EGBN3 Detect Alternate Function mapping
 *     @arg GPIO_RMP_DET_EN_EGBN2 EGBN2 Detect Alternate Function mapping
 *     @arg GPIO_RMP_DET_EN_EGBN1 EGBN1 Detect Alternate Function mapping
 *     @arg GPIO_RMP_DET_EN_ECLAMP4 ECLAMP4 Detect Alternate Function mapping
 *     @arg GPIO_RMP_DET_EN_ECLAMP3 ECLAMP3 Detect Alternate Function mapping
 *     @arg GPIO_RMP_DET_EN_ECLAMP2 ECLAMP2 Detect Alternate Function mapping
 *     @arg GPIO_RMP_DET_EN_ECLAMP1 ECLAMP1 Detect Alternate Function mapping
 *     @arg GPIO_RMP_RST_EN_EGB4 EGB4 Reset Alternate Function mapping
 *     @arg GPIO_RMP_RST_EN_EGB3 EGB3 Reset Alternate Function mapping
 *     @arg GPIO_RMP_RST_EN_EGB2 EGB2 Reset Alternate Function mapping
 *     @arg GPIO_RMP_RST_EN_EGB1 EGB1 Reset Alternate Function mapping
 *     @arg GPIO_RMP_RST_EN_EGBN4 EGBN4 Reset Alternate Function mapping
 *     @arg GPIO_RMP_RST_EN_EGBN3 EGBN3 Reset Alternate Function mapping
 *     @arg GPIO_RMP_RST_EN_EGBN2 EGBN2 Reset Alternate Function mapping
 *     @arg GPIO_RMP_RST_EN_EGBN1 EGBN1 Reset Alternate Function mapping
 *     @arg GPIO_RMP_RST_EN_ECLAMP4 ECLAMP4 Reset Alternate Function mapping
 *     @arg GPIO_RMP_RST_EN_ECLAMP3 ECLAMP3 Reset Alternate Function mapping
 *     @arg GPIO_RMP_RST_EN_ECLAMP2 ECLAMP2 Reset Alternate Function mapping
 *     @arg GPIO_RMP_RST_EN_ECLAMP1 ECLAMP1 Reset Alternate Function mapping
 * @param Cmd new state of the port pin remapping.
 *   This parameter can be: ENABLE or DISABLE.
 */
void GPIO_ConfigPinRemap(uint32_t RmpPin, FunctionalState Cmd)
{
	uint16_t bitsegH, bitsegL;

	/* Check the parameters */
	assert_param(IS_GPIO_REMAP(RmpPin));
	assert_param(IS_FUNCTIONAL_STATE(Cmd));

	bitsegL = RmpPin & LSB_MASK;
	bitsegH = RmpPin >> 16;

	ConfigPinRemap(bitsegH, Cmd);
	ConfigPinRemap(bitsegL, Cmd);
}

/**
 * @brief Selects the GPIO pin used as EXTI Line.
 * @param PortSource selects the GPIO port to be used as source for EXTI lines.
 *   This parameter can be GPIO_PortSourceGPIOx where x can be (A..G).
 * @param PinSource specifies the EXTI line to be configured.
 *   This parameter can be GPIO_PinSourcex where x can be (0..15).
 */
void GPIO_ConfigEXTILine(uint8_t PortSource, uint8_t PinSource)
{
    uint32_t mask = 0x00;
	
    /* Check the parameters */
    assert_param(IS_GPIO_EXTI_PORT_SOURCE(PortSource));
    assert_param(IS_GPIO_PIN_SOURCE(PinSource));

	/* Calculate bit-mask position */
    mask = ((uint32_t) 0x0F) << (0x04 * (PinSource & ((uint8_t) 0x03)));
	
	/* Configure EXTIx input source */
    AFIO->EXTI_CFG[PinSource >> 0x02] &= ~mask;
    AFIO->EXTI_CFG[PinSource >> 0x02] |= (((uint32_t) PortSource) << (0x04 * (PinSource & ((uint8_t) 0x03))));
}

/**
 * @}
 */

#endif

/**
 * @}
 */

/**
 * @}
 */
