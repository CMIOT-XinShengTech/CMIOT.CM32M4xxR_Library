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

/** @addtogroup CM32M4xxR_StdPeriph_Examples
 * @{
 */

/** @addtogroup I2S_Interrupt
 * @{
 */

I2S_InitType I2S_InitStructure;
const uint16_t I2S3_Buffer_Tx[32] = {0x0102, 0x0304, 0x0506, 0x0708, 0x090A, 0x0B0C, 0x0D0E, 0x0F10,
                                     0x1112, 0x1314, 0x1516, 0x1718, 0x191A, 0x1B1C, 0x1D1E, 0x1F20,
                                     0x2122, 0x2324, 0x2526, 0x2728, 0x292A, 0x2B2C, 0x2D2E, 0x2F30,
                                     0x3132, 0x3334, 0x3536, 0x3738, 0x393A, 0x3B3C, 0x3D3E, 0x3F40};

uint16_t I2S2_Buffer_Rx[32];
__IO uint32_t TxIdx = 0;
__IO uint32_t RxIdx = 0;
Status TransferStatus1 = FAILED;
Status TransferStatus2 = FAILED;
ErrorStatus HSEStartUpStatus;

void RCC_Configuration(void);
void GPIO_Configuration(void);
void ECLIC_Configuration(void);
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

	log_init();
	log_info("I2S_Interrupt test start\r\n");

	/* Disable global interrupt */
	__disable_irq();

    /* System clocks configuration ---------------------------------------------*/
    RCC_Configuration();

    /* NVIC configuration ------------------------------------------------------*/
    ECLIC_Configuration();

    /* GPIO configuration ------------------------------------------------------*/
    GPIO_Configuration();

    SPI_I2S_DeInit(I2S_MASTER);
    SPI_I2S_DeInit(I2S_SLAVE);

    /* I2S peripheral configuration */
    I2S_InitStructure.Standard       = I2S_STD_PHILLIPS;
    I2S_InitStructure.DataFormat     = I2S_DATA_FMT_16BITS_EXTENDED;
    I2S_InitStructure.MCLKEnable     = I2S_MCLK_DISABLE;
    I2S_InitStructure.AudioFrequency = I2S_AUDIO_FREQ_48K;
    I2S_InitStructure.CLKPOL         = I2S_CLKPOL_LOW;

    /* I2S3 Master Transmitter to I2S2 Slave Receiver communication -----------*/
    /* I2S3 configuration */
    I2S_InitStructure.I2sMode = I2S_MODE_MASTER_TX;
    I2S_Init(I2S_MASTER, &I2S_InitStructure);

    /* I2S2 configuration */
    I2S_InitStructure.I2sMode = I2S_MODE_SlAVE_RX;
    I2S_Init(I2S_SLAVE, &I2S_InitStructure);

    /* Enable the I2S3 TxE interrupt */
    SPI_I2S_EnableInt(I2S_MASTER, SPI_I2S_INT_TE, ENABLE);

    /* Enable the I2S2 RxNE interrupt */
    SPI_I2S_EnableInt(I2S_SLAVE, SPI_I2S_INT_RNE, ENABLE);

    /* Enable the I2S2 */
    I2S_Enable(I2S_SLAVE, ENABLE);

    /* Enable the I2S3 */
    I2S_Enable(I2S_MASTER, ENABLE);

    /* Enable global interrupt */
    __enable_irq();

    /* Wait the end of communication */
    while (RxIdx < 32)
    {
    }


    /* TransferStatus1 = PASSED, if the data transmitted from I2S3 and received by
                                 I2S2 are the same
       TransferStatus1 = FAILED, if the data transmitted from I2S3 and received by
                                 I2S2 are different */
    TransferStatus1 = Buffercmp(I2S2_Buffer_Rx, (uint16_t*)I2S3_Buffer_Tx, 32);

    /* Reinitialize the buffers */
    for (RxIdx = 0; RxIdx < 32; RxIdx++)
    {
        I2S2_Buffer_Rx[RxIdx] = 0;
    }

    TxIdx = 0;
    RxIdx = 0;

    SPI_I2S_DeInit(I2S_MASTER);
    SPI_I2S_DeInit(I2S_SLAVE);

    /* I2S peripheral configuration */
    I2S_InitStructure.Standard       = I2S_STD_PHILLIPS;
    I2S_InitStructure.DataFormat     = I2S_DATA_FMT_24BITS;
    I2S_InitStructure.MCLKEnable     = I2S_MCLK_DISABLE;
    I2S_InitStructure.AudioFrequency = I2S_AUDIO_FREQ_16K;
    I2S_InitStructure.CLKPOL         = I2S_CLKPOL_LOW;

    /* I2S3 Master Transmitter to I2S2 Slave Receiver communication -----------*/
    /* I2S3 configuration */
    I2S_InitStructure.I2sMode = I2S_MODE_MASTER_TX;
    I2S_Init(I2S_MASTER, &I2S_InitStructure);

    /* I2S2 configuration */
    I2S_InitStructure.I2sMode = I2S_MODE_SlAVE_RX;
    I2S_Init(I2S_SLAVE, &I2S_InitStructure);

    /* Enable the I2S3 TxE interrupt */
    SPI_I2S_EnableInt(I2S_MASTER, SPI_I2S_INT_TE, ENABLE);

    /* Enable the I2S2 RxNE interrupt */
    SPI_I2S_EnableInt(I2S_SLAVE, SPI_I2S_INT_RNE, ENABLE);

    /* Enable the I2S2 */
    I2S_Enable(I2S_SLAVE, ENABLE);

    /* Enable the I2S3 */
    I2S_Enable(I2S_MASTER, ENABLE);

    /* Wait the end of communication */
    while (RxIdx < 32)
    {
    }

    /* TransferStatus2 = PASSED, if the data transmitted from I2S3 and received by
                                 I2S2 are the same
       TransferStatus2 = FAILED, if the data transmitted from I2S3 and received by
                                 I2S2 are different */
    TransferStatus2 = Buffercmp24bits(I2S2_Buffer_Rx, (uint16_t*)I2S3_Buffer_Tx, 32);
    if((TransferStatus1 == PASSED) && (TransferStatus2 == PASSED))
    {
        log_info("I2S_Interrupt passed\n");
    }
    else
    {
    	if (TransferStatus1 != PASSED)
    	{
    		log_info("I2S_Interrupt failed:TransferStatus1\n");
    	}
    	if (TransferStatus2 != PASSED)
    	{
    		log_info("I2S_Interrupt failed:TransferStatus2\n");
    	}
    }
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
}

/**
 * @brief  Configures the different GPIO ports.
 */
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_ConfigPinRemap(GPIO_RMP1_SPI3, ENABLE);

    /* Configure SPI2 pins: WS, CK and SD ---------------------------------*/
    GPIO_InitStructure.Pin        = I2S_SLAVE_PIN_WS | I2S_SLAVE_PIN_CK | I2S_SLAVE_PIN_SD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* Configure SPI3 pins: CK and SD ------------------------------------*/
    GPIO_InitStructure.Pin       = I2S_MASTER_PIN_CK | I2S_MASTER_PIN_SD;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    /* Configure SPI3 pins: WS -------------------------------------------*/
    GPIO_InitStructure.Pin = I2S_MASTER_PIN_WS;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
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
