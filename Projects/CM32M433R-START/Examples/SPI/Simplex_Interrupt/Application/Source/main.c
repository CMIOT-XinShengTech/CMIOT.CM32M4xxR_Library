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
#include <stdio.h>
#include "log.h"

/** @addtogroup CM32M4xxR_StdPeriph_Examples
 * @{
 */


/** @addtogroup Simplex_Interrupt
 * @{
 */

typedef enum
{
    FAILED = 0,
    PASSED = !FAILED
} TestStatus;

SPI_InitType SPI_InitStructure;
uint8_t SPI_MASTER_Buffer_Tx[BufferSize] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
                                            0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16,
                                            0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20};
uint8_t SPI_SLAVE_Buffer_Rx[BufferSize];
__IO uint8_t TxIdx = 0;
__IO uint8_t RxIdx = 0;
volatile TestStatus TransferStatus = FAILED;

void RCC_Configuration(void);
void GPIO_Configuration(void);
void ECLIC_Configuration(void);
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);

/**
 * @brief  Main program.
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
	log_info("This is a Simplex_Interrupt demo-----------------------------------\r\n");
    /* System clocks configuration ---------------------------------------------*/
    RCC_Configuration();

    /* ECLIC configuration ------------------------------------------------------*/
    ECLIC_Configuration();

    /* GPIO configuration ------------------------------------------------------*/
    GPIO_Configuration();

    /* SPI_MASTER configuration ------------------------------------------------*/
    SPI_InitStructure.DataDirection = SPI_DIR_SINGLELINE_TX;
    SPI_InitStructure.SpiMode       = SPI_MODE_MASTER;
    SPI_InitStructure.DataLen       = SPI_DATA_SIZE_8BITS;
    SPI_InitStructure.CLKPOL        = SPI_CLKPOL_HIGH;
    SPI_InitStructure.CLKPHA        = SPI_CLKPHA_SECOND_EDGE;
    SPI_InitStructure.NSS           = SPI_NSS_SOFT;
    SPI_InitStructure.BaudRatePres  = SPI_BR_PRESCALER_16;
    SPI_InitStructure.FirstBit      = SPI_FB_MSB;
    SPI_InitStructure.CRCPoly       = 0x0007;
    SPI_Init(SPI_MASTER, &SPI_InitStructure);

    /* SPI_SLAVE configuration -------------------------------------------------*/
    SPI_InitStructure.DataDirection = SPI_DIR_SINGLELINE_RX;
    SPI_InitStructure.SpiMode       = SPI_MODE_SLAVE;
    SPI_Init(SPI_SLAVE, &SPI_InitStructure);

    /* Enable SPI_MASTER TXE interrupt */
    SPI_I2S_EnableInt(SPI_MASTER, SPI_I2S_INT_TE, ENABLE);

    /* Enable SPI_SLAVE RXNE interrupt */
    SPI_I2S_EnableInt(SPI_SLAVE, SPI_I2S_INT_RNE, ENABLE);

    /* Enable global interrupt */
    __enable_irq();

    /* Enable SPI_SLAVE */
    SPI_Enable(SPI_SLAVE, ENABLE);

    /* Enable SPI_MASTER */
    SPI_Enable(SPI_MASTER, ENABLE);

    /* Transfer procedure */
    while (RxIdx < BufferSize)
    {
    }

    /* Check the correctness of written data */
    /* TransferStatus = PASSED, if the transmitted and received data
       are equal */
    /* TransferStatus = FAILED, if the transmitted and received data
       are different */
    TransferStatus = Buffercmp(SPI_SLAVE_Buffer_Rx, SPI_MASTER_Buffer_Tx, BufferSize);

    log_info("TransferStatus:%s\r\n", (TransferStatus?"PASSED":"FAILED"));
    while (1)
    {
    }
}

/**
 * @brief  Configures the different system clocks.
 */
void RCC_Configuration(void)
{
    /* Enable peripheral clocks --------------------------------------------------*/

    /* Enable SPI_MASTER clock and GPIO clock for SPI_MASTER and SPI_SLAVE */
    RCC_EnableAPB2PeriphClk(SPI_MASTER_GPIO_CLK | SPI_SLAVE_GPIO_CLK | SPI_MASTER_CLK, ENABLE);

    /* Enable SPI_SLAVE Periph clock */
    RCC_EnableAPB1PeriphClk(SPI_SLAVE_CLK, ENABLE);
}

/**
 * @brief  Configures the different GPIO ports.
 */
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    /* Configure SPI_MASTER pins: SCK and MOSI ---------------------------------*/
    /* Configure SCK and MOSI pins as Alternate Function Push Pull */
    GPIO_InitStructure.Pin        = SPI_MASTER_PIN_SCK | SPI_MASTER_PIN_MOSI;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_Init(SPI_MASTER_GPIO, &GPIO_InitStructure);

    /* Configure SPI_SLAVE pins: SCK and MISO ---------------------------------*/
    /* Configure SCK pin as Input Floating */
    GPIO_InitStructure.Pin       = SPI_SLAVE_PIN_SCK;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(SPI_SLAVE_GPIO, &GPIO_InitStructure);

    /* Configure MISO pin as Alternate Function Push Pull */
    GPIO_InitStructure.Pin       = SPI_SLAVE_PIN_MISO;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(SPI_SLAVE_GPIO, &GPIO_InitStructure);

    GPIO_ConfigPinRemap(GPIO_RMP1_SPI2,ENABLE);
}

/**
 * @brief  Configure ECLIC.
 */
void ECLIC_Configuration(void)
{
    /* Enable the SPI_MASTER Interrupt */
	ECLIC_SetLevelIRQ(SPI_MASTER_IRQn, 0);
	ECLIC_SetPriorityIRQ(SPI_MASTER_IRQn, 0);
	ECLIC_SetTrigIRQ(SPI_MASTER_IRQn, ECLIC_LEVEL_TRIGGER);
	ECLIC_EnableIRQ(SPI_MASTER_IRQn);

    /* Enable the SPI_SLAVE Interrupt */
	ECLIC_SetLevelIRQ(SPI_SLAVE_IRQn, 1);
	ECLIC_SetPriorityIRQ(SPI_SLAVE_IRQn, 0);
	ECLIC_SetTrigIRQ(SPI_SLAVE_IRQn, ECLIC_LEVEL_TRIGGER);
	ECLIC_EnableIRQ(SPI_SLAVE_IRQn);
}

/**
 * @brief  Compares two buffers.
 * @param  pBuffer1, pBuffer2: buffers to be compared.
 * @param BufferLength buffer's length
 * @return PASSED: pBuffer1 identical to pBuffer2
 *         FAILED: pBuffer1 differs from pBuffer2
 */
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
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
 * @}
 */

/**
 * @}
 */
