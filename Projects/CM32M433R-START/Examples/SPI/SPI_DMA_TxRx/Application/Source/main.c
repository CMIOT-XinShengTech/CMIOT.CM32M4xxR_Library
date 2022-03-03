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


/** @addtogroup SPI_DMA_TxRx
 * @{
 */

typedef enum
{
    FAILED = 0,
    PASSED = !FAILED
} TestStatus;

#define BufferSize	(32)

SPI_InitType SPI_InitStructure;
DMA_InitType DMA_InitStructure;
GPIO_InitType GPIO_InitStructure;

uint8_t SPI_MASTER_Buffer_Tx[BufferSize] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
                                            0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16,
                                            0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20};
uint8_t SPI_SLAVE_Buffer_Rx[BufferSize];
__IO uint8_t TxIdx                 = 0;
volatile TestStatus TransferStatus = FAILED;

void RCC_Configuration(void);
void GPIO_Configuration(void);
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
	log_info("This is a SPI_DMA_TxRx demo-----------------------------------\r\n");
    /* System clocks configuration ---------------------------------------------*/
    RCC_Configuration();

    /* GPIO configuration ------------------------------------------------------*/
    GPIO_Configuration();

    /* SPI_SLAVE_Rx_DMA_Channel configuration ---------------------------------------------*/
    DMA_DeInit(SPI_SLAVE_Rx_DMA_Channel);
    DMA_InitStructure.PeriphAddr     = (uint32_t)SPI_SLAVE_DR_Base;
    DMA_InitStructure.MemAddr        = (uint32_t)SPI_SLAVE_Buffer_Rx;
    DMA_InitStructure.Direction      = DMA_DIR_PERIPH_SRC;
    DMA_InitStructure.BufSize        = BufferSize;
    DMA_InitStructure.PeriphInc      = DMA_PERIPH_INC_DISABLE;
    DMA_InitStructure.DMA_MemoryInc  = DMA_MEM_INC_ENABLE;
    DMA_InitStructure.PeriphDataSize = DMA_PERIPH_DATA_SIZE_BYTE;
    DMA_InitStructure.MemDataSize    = DMA_MEMORY_DATA_SIZE_BYTE;
    DMA_InitStructure.CircularMode   = DMA_MODE_NORMAL;
    DMA_InitStructure.Priority       = DMA_PRIORITY_VERY_HIGH;
    DMA_InitStructure.Mem2Mem        = DMA_M2M_DISABLE;
    DMA_Init(SPI_SLAVE_Rx_DMA_Channel, &DMA_InitStructure);

    /* SPI_MASTER_Tx_DMA_Channel configuration ---------------------------------------------*/
    DMA_DeInit(SPI_MASTER_Tx_DMA_Channel);
    DMA_InitStructure.PeriphAddr = (uint32_t)SPI_MASTER_DR_Base;
    DMA_InitStructure.MemAddr    = (uint32_t)SPI_MASTER_Buffer_Tx;
    DMA_InitStructure.Direction  = DMA_DIR_PERIPH_DST;
    DMA_Init(SPI_MASTER_Tx_DMA_Channel, &DMA_InitStructure);

    /* SPI_MASTER configuration ------------------------------------------------------*/
    SPI_InitStructure.DataDirection = SPI_DIR_SINGLELINE_TX;
    SPI_InitStructure.SpiMode       = SPI_MODE_MASTER;
    SPI_InitStructure.DataLen       = SPI_DATA_SIZE_8BITS;
    SPI_InitStructure.CLKPOL        = SPI_CLKPOL_HIGH;
    SPI_InitStructure.CLKPHA        = SPI_CLKPHA_FIRST_EDGE;
    SPI_InitStructure.NSS           = SPI_NSS_HARD;
    SPI_InitStructure.BaudRatePres  = SPI_BR_PRESCALER_16;
    SPI_InitStructure.FirstBit      = SPI_FB_MSB;
    SPI_InitStructure.CRCPoly       = 0x0007;
    SPI_Init(SPI_MASTER, &SPI_InitStructure);

    /* SPI_SLAVE configuration ------------------------------------------------------*/
    SPI_InitStructure.DataDirection = SPI_DIR_SINGLELINE_RX;
    SPI_InitStructure.SpiMode       = SPI_MODE_SLAVE;
    SPI_Init(SPI_SLAVE, &SPI_InitStructure);

    /* Enable SPI_MASTER NSS output for master mode */
    SPI_SSOutputEnable(SPI_MASTER, ENABLE);

    /* Enable SPI_SLAVE Rx request */
    SPI_I2S_EnableDma(SPI_SLAVE, SPI_I2S_DMA_RX, ENABLE);

    /* Enable SPI_MASTER Tx request */
    SPI_I2S_EnableDma(SPI_MASTER, SPI_I2S_DMA_TX, ENABLE);

    /* Enable SPI_SLAVE */
    SPI_Enable(SPI_SLAVE, ENABLE);

    /* Enable SPI_MASTER */
    SPI_Enable(SPI_MASTER, ENABLE);

    /* Enable DMA1 Channel3 */
    DMA_EnableChannel(SPI_MASTER_Tx_DMA_Channel, ENABLE);

    /* Enable DMA1 Channel4 */
    DMA_EnableChannel(SPI_SLAVE_Rx_DMA_Channel, ENABLE);

    /* Wait for DMA1 channel 3 and channel 4 transfer complete */
    while (!DMA_GetFlagStatus(SPI_MASTER_Tx_DMA_FLAG, DMA1))
        ;
    while (!DMA_GetFlagStatus(SPI_SLAVE_Rx_DMA_FLAG, DMA1))
        ;

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
    /* Enable SPI_SLAVE DMA clock */
    RCC_EnableAHBPeriphClk(SPI_SLAVE_DMA_CLK, ENABLE);

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

    /* Configure SPI_MASTER pins: NSS, SCK and MOSI */
    GPIO_InitStructure.Pin        = SPI_MASTER_PIN_NSS | SPI_MASTER_PIN_SCK | SPI_MASTER_PIN_MOSI;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_Init(SPI_MASTER_GPIO, &GPIO_InitStructure);

    GPIO_WriteBit(SPI_MASTER_GPIO, SPI_MASTER_PIN_NSS, Bit_SET);

    /* Configure SPI_SLAVE pins: NSS, SCK and MISO*/
    GPIO_InitStructure.Pin       = SPI_SLAVE_PIN_NSS;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(SPI_SLAVE_GPIO, &GPIO_InitStructure);
    GPIO_InitStructure.Pin       = SPI_SLAVE_PIN_SCK;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(SPI_SLAVE_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.Pin       = SPI_SLAVE_PIN_MISO;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(SPI_SLAVE_GPIO, &GPIO_InitStructure);

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
