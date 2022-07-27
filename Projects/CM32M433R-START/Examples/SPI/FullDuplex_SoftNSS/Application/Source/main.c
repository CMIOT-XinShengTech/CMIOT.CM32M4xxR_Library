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

#include <stdio.h>
#include "main.h"

#include "log.h"

/** @addtogroup CM32M4xxR_StdPeriph_Examples
 * @{
 */


/** @addtogroup FullDuplex_SoftNSS
 * @{
 */

typedef enum
{
    FAILED = 0,
    PASSED = !FAILED
} TestStatus;

#define BufferSize (32)

SPI_InitType SPI_InitStructure;
uint8_t SPIy_Buffer_Tx[BufferSize] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
                                      0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16,
                                      0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20};
uint8_t SPIz_Buffer_Tx[BufferSize] = {0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B,
                                      0x5C, 0x5D, 0x5E, 0x5F, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
                                      0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70};
uint8_t SPIy_Buffer_Rx[BufferSize];
uint8_t SPIz_Buffer_Rx[BufferSize];
__IO uint8_t TxIdx = 0;
__IO uint8_t RxIdx = 0;
volatile TestStatus TransferStatus1  = FAILED;
volatile TestStatus  TransferStatus2 = FAILED;
volatile TestStatus TransferStatus3  = FAILED;
volatile TestStatus  TransferStatus4 = FAILED;

void RCC_Configuration(void);
void GPIO_Configuration(uint16_t SPIy_Mode, uint16_t SPIz_Mode);
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);

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
	log_info("This is a FullDuplex_SoftNSS demo-----------------------------------\r\n");
    /* System clocks configuration ---------------------------------------------*/
    RCC_Configuration();

    /* 1st phase: SPIy Master and SPIz Slave */
    /* GPIO configuration ------------------------------------------------------*/
    GPIO_Configuration(SPI_MODE_MASTER, SPI_MODE_SLAVE);

    /* SPIy Config -------------------------------------------------------------*/
    SPI_InitStructure.DataDirection = SPI_DIR_DOUBLELINE_FULLDUPLEX;
    SPI_InitStructure.SpiMode       = SPI_MODE_MASTER;
    SPI_InitStructure.DataLen       = SPI_DATA_SIZE_8BITS;
    SPI_InitStructure.CLKPOL        = SPI_CLKPOL_LOW;
    SPI_InitStructure.CLKPHA        = SPI_CLKPHA_SECOND_EDGE;
    SPI_InitStructure.NSS           = SPI_NSS_SOFT;
    SPI_InitStructure.BaudRatePres  = SPI_BR_PRESCALER_4;
    SPI_InitStructure.FirstBit      = SPI_FB_LSB;
    SPI_InitStructure.CRCPoly       = 0x0007;
    SPI_Init(SPIy, &SPI_InitStructure);

    /* SPIz Config -------------------------------------------------------------*/
    SPI_InitStructure.SpiMode = SPI_MODE_SLAVE;
    SPI_Init(SPIz, &SPI_InitStructure);

    /* Enable SPIy */
    SPI_Enable(SPIy, ENABLE);

    /* Enable SPIz */
    SPI_Enable(SPIz, ENABLE);

    /* Transfer procedure */
    while (TxIdx < BufferSize)
    {
        /* Wait for SPIy Tx buffer empty */
        while (SPI_I2S_GetStatus(SPIy, SPI_I2S_TE_FLAG) == RESET)
            ;

        /* Send SPIz data */
        SPI_I2S_TransmitData(SPIz, SPIz_Buffer_Tx[TxIdx]); /* The slave should prepares the data first before master start transmitting */

        /* Send SPIy data */
        SPI_I2S_TransmitData(SPIy, SPIy_Buffer_Tx[TxIdx++]);

        /* Wait for SPIz data reception */
        while (SPI_I2S_GetStatus(SPIz, SPI_I2S_RNE_FLAG) == RESET)
            ;

        /* Read SPIz received data */
        SPIz_Buffer_Rx[RxIdx] = SPI_I2S_ReceiveData(SPIz);

        /* Wait for SPIy data reception */
        while (SPI_I2S_GetStatus(SPIy, SPI_I2S_RNE_FLAG) == RESET)
            ;

        /* Read SPIy received data */
        SPIy_Buffer_Rx[RxIdx++] = SPI_I2S_ReceiveData(SPIy);
    }

    /* Check the correctness of written dada */
    /* TransferStatus1, TransferStatus2 = PASSED, if the transmitted and received data
       are equal */
    /* TransferStatus1, TransferStatus2 = FAILED, if the transmitted and received data
       are different */
    TransferStatus1 = Buffercmp(SPIz_Buffer_Rx, SPIy_Buffer_Tx, BufferSize);
    TransferStatus2 = Buffercmp(SPIy_Buffer_Rx, SPIz_Buffer_Tx, BufferSize);

    /* 2nd phase: SPIy Slave and SPIz Master */
    /* GPIO configuration ------------------------------------------------------*/
    GPIO_Configuration(SPI_MODE_SLAVE, SPI_MODE_MASTER);

    /* SPIy Re-configuration ---------------------------------------------------*/
    SPI_InitStructure.SpiMode = SPI_MODE_SLAVE;
    SPI_Init(SPIy, &SPI_InitStructure);

    /* SPIz Re-configuration ---------------------------------------------------*/
    SPI_InitStructure.SpiMode = SPI_MODE_MASTER;
    SPI_Init(SPIz, &SPI_InitStructure);

    /* Reset TxIdx, RxIdx indexes and receive tables values */
    TxIdx = 0;
    RxIdx = 0;
    for (uint32_t i = 0; i < BufferSize; i++)
        SPIz_Buffer_Rx[i] = 0;

    for (uint32_t i = 0; i < BufferSize; i++)
        SPIy_Buffer_Rx[i] = 0;

    /* Transfer procedure */
    while (TxIdx < BufferSize)
    {
        /* Wait for SPIz Tx buffer empty */
        while (SPI_I2S_GetStatus(SPIz, SPI_I2S_TE_FLAG) == RESET)
            ;
        /* Send SPIy data */
        SPI_I2S_TransmitData(SPIy, SPIy_Buffer_Tx[TxIdx]);

        /* Send SPIz data */
        SPI_I2S_TransmitData(SPIz, SPIz_Buffer_Tx[TxIdx++]);

        /* Wait for SPIy data reception */
        while (SPI_I2S_GetStatus(SPIy, SPI_I2S_RNE_FLAG) == RESET)
            ;

        /* Read SPIy received data */
        SPIy_Buffer_Rx[RxIdx] = SPI_I2S_ReceiveData(SPIy);

        /* Wait for SPIz data reception */
        while (SPI_I2S_GetStatus(SPIz, SPI_I2S_RNE_FLAG) == RESET)
            ;

        /* Read SPIz received data */
        SPIz_Buffer_Rx[RxIdx++] = SPI_I2S_ReceiveData(SPIz);
    }

    /* Check the correctness of written dada */
    /* TransferStatus3, TransferStatus4 = PASSED, if the transmitted and received data
       are equal */
    /* TransferStatus3, TransferStatus4 = FAILED, if the transmitted and received data
       are different */
    TransferStatus3 = Buffercmp(SPIz_Buffer_Rx, SPIy_Buffer_Tx, BufferSize);
    TransferStatus4 = Buffercmp(SPIy_Buffer_Rx, SPIz_Buffer_Tx, BufferSize);

    log_info("TransferStatus1:%s\r\n", (TransferStatus1?"PASSED":"FAILED"));
    log_info("TransferStatus2:%s\r\n", (TransferStatus2?"PASSED":"FAILED"));
    log_info("TransferStatus3:%s\r\n", (TransferStatus3?"PASSED":"FAILED"));
    log_info("TransferStatus4:%s\r\n", (TransferStatus4?"PASSED":"FAILED"));
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

    /* Enable SPIy clock and GPIO clock for SPIy and SPIz */
    RCC_EnableAPB2PeriphClk(SPIy_GPIO_CLK | SPIz_GPIO_CLK | SPIy_CLK, ENABLE);

    /* Enable SPIz Periph clock */
    RCC_EnableAPB1PeriphClk(SPIz_CLK, ENABLE);
}

/**
 * @brief  Configures the different SPIy and SPIz GPIO ports.
 * @param SPIy_Mode Specifies the SPIy operating mode.
 *            This parameter can be:
 *              -  SPIy_Mode_Master
 *              -  SPIy_Mode_Slave
 * @param SPIz_Mode Specifies the SPIz operating mode.
 *            This parameter can be:
 *              -  SPIz_Mode_Master
 *              -  SPIz_Mode_Slave
 */
void GPIO_Configuration(uint16_t SPIy_Mode, uint16_t SPIz_Mode)
{
    GPIO_InitType GPIO_InitStructure;

    /* Configure SPIy pins: SCK, MISO and MOSI ---------------------------------*/
    GPIO_InitStructure.Pin        = SPIy_PIN_SCK | SPIy_PIN_MOSI;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

    if (SPIy_Mode == SPI_MODE_MASTER)
    {
        /* Configure SCK and MOSI pins as Alternate Function Push Pull */
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    }
    else
    {
        /* Configure SCK and MOSI pins as Input Floating */
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    }

    GPIO_Init(SPIy_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.Pin = SPIy_PIN_MISO;

    if (SPIy_Mode == SPI_MODE_MASTER)
    {
        /* Configure MISO pin as Input Floating  */
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    }
    else
    {
        /* Configure MISO pin as Alternate Function Push Pull */
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    }

    GPIO_Init(SPIy_GPIO, &GPIO_InitStructure);

    /* Configure SPIz pins: SCK, MISO and MOSI ---------------------------------*/
    GPIO_InitStructure.Pin = SPIz_PIN_SCK | SPIz_PIN_MOSI;

    if (SPIz_Mode == SPI_MODE_SLAVE)
    {
        /* Configure SCK and MOSI pins as Input Floating */
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    }
    else
    {
        /* Configure SCK and MOSI pins as Alternate Function Push Pull */
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    }

    GPIO_Init(SPIz_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.Pin = SPIz_PIN_MISO;

    if (SPIz_Mode == SPI_MODE_SLAVE)
    {
        /* Configure MISO pin as Alternate Function Push Pull */
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    }
    else
    { /* Configure MISO pin as Input Floating  */
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    }

    GPIO_Init(SPIz_GPIO, &GPIO_InitStructure);

    GPIO_ConfigPinRemap(GPIO_RMP1_SPI2,ENABLE);
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
