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
#include "log.h"
#include "decode_wm8960.h"

/** @addtogroup CM32M4xxR_StdPeriph_Examples
 * @{
 */

/** @addtogroup I2S_Interrupt
 * @{
 */

I2S_InitType I2S_InitStructure;
extern const uint16_t I2S3_Buffer_Tx[102400];

__IO uint32_t TxIdx = 0;
Status TransferStatus1 = FAILED;
ErrorStatus HSEStartUpStatus;

void RCC_Configuration(void);
void GPIO_Configuration(void);
void ECLIC_Configuration(void);
void I2C_Configuration(void);
Status Buffercmp(uint16_t* pBuffer1, uint16_t* pBuffer2, uint16_t BufferLength);
Status Buffercmp24bits(uint16_t* pBuffer1, uint16_t* pBuffer2, uint16_t BufferLength);

/**
 * @brief  Main function.
 */
int main(void)
{
    /*!< At this stage the microcontroller clock setting is already configured,
          this is done through SystemInit() function which is called from startup
          file (startup_cm32m4xxr.s) before to branch to application main.
          To reconfigure the default setting of SystemInit() function, refer to
          system_cm32m4xxr.c file
        */

	/* Disable global interrupt */
	__disable_irq();

    /* System clocks configuration ---------------------------------------------*/
    RCC_Configuration();

    /* NVIC configuration ------------------------------------------------------*/
    ECLIC_Configuration();

    /* GPIO configuration ------------------------------------------------------*/
    GPIO_Configuration();

    /* GPIO configuration ------------------------------------------------------*/
    I2C_Configuration();

    mtb_wm8960_init(I2Cx, WM8960_FEATURE_MICROPHONE | WM8960_FEATURE_HEADPHONE);

    mtb_wm8960_configure_clocking(11289600, true, WM8960_ADC_DAC_SAMPLE_RATE_22_05_KHZ, WM8960_AUDIO_INTF0_WL_16BITS, WM8960_AUDIO_INTF0_MS_SLAVE);

    mtb_wm8960_adjust_heaphone_output_volume(0x70);
    mtb_wm8960_activate();

    SPI_I2S_DeInit(I2S_MASTER);

    /* I2S peripheral configuration */
    I2S_InitStructure.Standard       = I2S_STD_PHILLIPS;
    I2S_InitStructure.DataFormat     = I2S_DATA_FMT_16BITS;
    I2S_InitStructure.MCLKEnable     = I2S_MCLK_ENABLE;
    I2S_InitStructure.AudioFrequency = I2S_AUDIO_FREQ_22K;
    I2S_InitStructure.CLKPOL         = I2S_CLKPOL_LOW;

    /* I2S3 Master Transmitter to I2S2 Slave Receiver communication -----------*/
    /* I2S3 configuration */
    I2S_InitStructure.I2sMode = I2S_MODE_MASTER_TX;
    I2S_Init(I2S_MASTER, &I2S_InitStructure);

    /* Enable the I2S3 TxE interrupt */
    SPI_I2S_EnableInt(I2S_MASTER, SPI_I2S_INT_TE, ENABLE);

    /* Enable the I2S3 */
    I2S_Enable(I2S_MASTER, ENABLE);

    /* Enable global interrupt */
    __enable_irq();


    while (1)
    {
    }
}

/**
 * @brief  Configures the different system clocks.
 */
void RCC_Configuration(void)
{
    /* Enable peripheral clocks ------------------------------------------------*/
    /* GPIOB, GPIOC, GPIOD and AFIO clocks enable */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_GPIOC | RCC_APB2_PERIPH_GPIOD | RCC_APB2_PERIPH_AFIO, ENABLE);

    /* SPI3 and SPI2 clocks enable */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_SPI3 | RCC_APB1_PERIPH_SPI2, ENABLE);

    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_I2C3, ENABLE);

#ifdef I2C1_REMAP
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
    GPIO_ConfigPinRemap(GPIO_RMP3_I2C3, ENABLE);
#endif
}

/**
 * @brief  Configures the different GPIO ports.
 */
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;
    GPIO_InitType i2c_gpio;

    GPIO_ConfigPinRemap(GPIO_RMP2_SPI3, ENABLE);

    /* Configure SPI3 pins: CK and SD ------------------------------------*/
    GPIO_InitStructure.Pin       = I2S_MASTER_PIN_CK | I2S_MASTER_PIN_SD;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    /* Configure SPI3 pins: WS -------------------------------------------*/
    GPIO_InitStructure.Pin = I2S_MASTER_PIN_WS;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    /* Configure SPI3 pins: MCLK -----------------------------------------*/
    GPIO_InitStructure.Pin = I2S_MASTER_PIN_MCLK;
    GPIO_Init(GPIOC, &GPIO_InitStructure);


    /* PB6/PB8 -- SCL; PB7/PB9 -- SDA */
    i2c_gpio.Pin        = I2Cx_SCL_PIN | I2Cx_SDA_PIN;
    i2c_gpio.GPIO_Speed = GPIO_Speed_2MHz;
    i2c_gpio.GPIO_Mode  = GPIO_Mode_AF_OD;
    GPIO_Init(I2Cx_GPIOx, &i2c_gpio);
}

/**
 * @brief  Configures the different GPIO ports.
 */
void I2C_Configuration(void)
{
    I2C_InitType i2c_master;

    I2C_DeInit(I2Cx);
    i2c_master.BusMode     = I2C_BUSMODE_I2C;
    i2c_master.FmDutyCycle = I2C_FMDUTYCYCLE_2;
    i2c_master.OwnAddr1    = I2C_MASTER_ADDR;
    i2c_master.AckEnable   = I2C_ACKEN;
    i2c_master.AddrMode    = I2C_ADDR_MODE_7BIT;
    i2c_master.ClkSpeed    = 100000; /* Speed = 100K */

    I2C_Init(I2Cx, &i2c_master);
    I2C_Enable(I2Cx, ENABLE);
    I2C_ConfigAck(I2Cx, ENABLE);
}


/**
 * @brief  Configure the enhanced core local interrupt controller.
 */
void ECLIC_Configuration(void)
{
    /* Configure the SPI3_I2S3 Interrupt */
	ECLIC_SetLevelIRQ(SPI3_I2S3_IRQn, 0);
	ECLIC_SetPriorityIRQ(SPI3_I2S3_IRQn, 0);
	ECLIC_SetTrigIRQ(SPI3_I2S3_IRQn, ECLIC_LEVEL_TRIGGER);

    /* Configure the SPI2_I2S2 Interrupt */
	ECLIC_SetLevelIRQ(SPI2_I2S2_IRQn, 1);
	ECLIC_SetPriorityIRQ(SPI2_I2S2_IRQn, 0);
	ECLIC_SetTrigIRQ(SPI2_I2S2_IRQn, ECLIC_LEVEL_TRIGGER);

    /* Enable SPI3_I2S3 and SPI2_I2S2 Interrupt */
	ECLIC_EnableIRQ(SPI3_I2S3_IRQn);
	ECLIC_EnableIRQ(SPI2_I2S2_IRQn);
}

/**
 * @brief  Compares two buffers.
 * @param  pBuffer1, pBuffer2: buffers to be compared.
 * @param BufferLength buffer's length
 * @return PASSED: pBuffer1 identical to pBuffer2
 *         FAILED: pBuffer1 differs from pBuffer2
 */
Status Buffercmp(uint16_t* pBuffer1, uint16_t* pBuffer2, uint16_t BufferLength)
{
    while (BufferLength--)
    {
        if (*pBuffer1 != *pBuffer2)
        {
            return FAILED;
        }

        pBuffer1++;
        pBuffer2++;
    }

    return PASSED;
}

/**
 * @brief  Compares two buffers in 24 bits data format.
 * @param  pBuffer1, pBuffer2: buffers to be compared.
 * @param BufferLength buffer's length
 * @return PASSED: pBuffer1 identical to pBuffer2
 *         FAILED: pBuffer1 differs from pBuffer2
 */
Status Buffercmp24bits(uint16_t* pBuffer1, uint16_t* pBuffer2, uint16_t BufferLength)
{
    while (BufferLength--)
    {
        if (*pBuffer1 != *pBuffer2)
        {
            if (*pBuffer1 != (*pBuffer2 & 0xFF00))
            {
                return FAILED;
            }
        }

        pBuffer1++;
        pBuffer2++;
    }

    return PASSED;
}

/**
 * @}
 */

/**
 * @}
 */
