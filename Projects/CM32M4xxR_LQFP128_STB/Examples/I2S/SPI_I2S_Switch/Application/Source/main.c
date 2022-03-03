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

/** @addtogroup SPI_I2S_Switch
 * @{
 */

#define BufferSize	(32)

I2S_InitType I2S_InitStructure;
SPI_InitType SPI_InitStructure;
uint16_t I2S3_Buffer_Tx[BufferSize] = {0x0102, 0x0304, 0x0506, 0x0708, 0x090A, 0x0B0C, 0x0D0E, 0x0F10,
                                       0x1112, 0x1314, 0x1516, 0x1718, 0x191A, 0x1B1C, 0x1D1E, 0x1F20,
                                       0x2122, 0x2324, 0x2526, 0x2728, 0x292A, 0x2B2C, 0x2D2E, 0x2F30,
                                       0x3132, 0x3334, 0x3536, 0x3738, 0x393A, 0x3B3C, 0x3D3E, 0x3F40};

uint16_t SPI3_Buffer_Tx[BufferSize] = {0x5152, 0x5354, 0x5556, 0x5758, 0x595A, 0x5B5C, 0x5D5E, 0x5F60,
                                       0x6162, 0x6364, 0x6566, 0x6768, 0x696A, 0x6B6C, 0x6D6E, 0x6F70,
                                       0x7172, 0x7374, 0x7576, 0x7778, 0x797A, 0x7B7C, 0x7D7E, 0x7F80,
                                       0x8182, 0x8384, 0x8586, 0x8788, 0x898A, 0x8B8C, 0x8D8E, 0x8F90};

__IO uint16_t I2S2_Buffer_Rx[BufferSize];
__IO uint16_t SPI2_Buffer_Rx[BufferSize];
__IO uint8_t TxIdx = 0;
__IO uint8_t RxIdx = 0;
volatile Status TransferStatus1 = FAILED;
volatile Status TransferStatus2 = FAILED;
volatile Status TransferStatus3 = FAILED;
ErrorStatus HSEStartUpStatus;

void RCC_Configuration(void);
void GPIO_Configuration(void);
Status Buffercmp(uint16_t* pBuffer1, uint16_t* pBuffer2, uint16_t BufferLength);
void Delay(__IO uint32_t nCount);

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
	log_info("SPI_I2S_Switch test start\r\n");
    /* System clocks configuration ---------------------------------------------*/
    RCC_Configuration();

    /* GPIO configuration ------------------------------------------------------*/
    GPIO_Configuration();

    /* Deinitializes the SPI2 and SPI3 peripheral registers --------------------*/
    SPI_I2S_DeInit(SPI2);
    SPI_I2S_DeInit(SPI3);

    /* I2S peripheral configuration */
    I2S_InitStructure.Standard       = I2S_STD_PHILLIPS;
    I2S_InitStructure.DataFormat     = I2S_DATA_FMT_16BITS_EXTENDED;
    I2S_InitStructure.MCLKEnable     = I2S_MCLK_DISABLE;
    I2S_InitStructure.AudioFrequency = I2S_AUDIO_FREQ_48K;
    I2S_InitStructure.CLKPOL         = I2S_CLKPOL_LOW;

    /* I2S3 Master Transmitter to I2S2 Slave Receiver communication ------------*/
    /* I2S3 configuration */
    I2S_InitStructure.I2sMode = I2S_MODE_MASTER_TX;
    I2S_Init(SPI3, &I2S_InitStructure);

    /* I2S2 configuration */
    I2S_InitStructure.I2sMode = I2S_MODE_SlAVE_RX;
    I2S_Init(SPI2, &I2S_InitStructure);

    /* Enable the I2S2 */
    I2S_Enable(SPI2, ENABLE);

    /* Enable the I2S3 */
    I2S_Enable(SPI3, ENABLE);

    /* Begin the communication in I2S mode */
    while (RxIdx < BufferSize)
    {
        /* Wait the Tx buffer to be empty */
        while (SPI_I2S_GetStatus(SPI3, SPI_I2S_TE_FLAG) == RESET)
        {
        }

        /* Send a data from I2S3 */
        SPI_I2S_TransmitData(SPI3, I2S3_Buffer_Tx[TxIdx++]);

        /* Wait the Rx buffer to be full */
        while (SPI_I2S_GetStatus(SPI2, SPI_I2S_RNE_FLAG) == RESET)
        {
        }

        /* Store the I2S2 received data in the relative data table */
        I2S2_Buffer_Rx[RxIdx++] = SPI_I2S_ReceiveData(SPI2);
    }

    /* TransferStatus1 = PASSED, if the data transmitted from I2S3 and received by
                                 I2S2 are the same
       TransferStatus1 = FAILED, if the data transmitted from I2S3 and received by
                                 I2S2 are different */
    TransferStatus1 = Buffercmp((uint16_t*)I2S2_Buffer_Rx, I2S3_Buffer_Tx, BufferSize);

    /* Reset TxIdx, RxIdx indexes */
    TxIdx = 0;
    RxIdx = 0;

    /* Switch to SPI mode communication ----------------------------------------*/
    /* SPI3 configuration */
    SPI_InitStructure.DataDirection = SPI_DIR_SINGLELINE_TX;
    SPI_InitStructure.SpiMode       = SPI_MODE_MASTER;
    SPI_InitStructure.DataLen       = SPI_DATA_SIZE_16BITS;
    SPI_InitStructure.CLKPOL        = SPI_CLKPOL_LOW;
    SPI_InitStructure.CLKPHA        = SPI_CLKPHA_SECOND_EDGE;
    SPI_InitStructure.NSS           = SPI_NSS_SOFT;
    SPI_InitStructure.BaudRatePres  = SPI_BR_PRESCALER_4;
    SPI_InitStructure.FirstBit      = SPI_FB_MSB;
    SPI_InitStructure.CRCPoly       = 7;
    SPI_Init(SPI3, &SPI_InitStructure);

    /* SPI2 configuration ------------------------------------------------------*/
    SPI_InitStructure.DataDirection = SPI_DIR_DOUBLELINE_RONLY;
    SPI_InitStructure.SpiMode       = SPI_MODE_SLAVE;
    SPI_Init(SPI2, &SPI_InitStructure);

    /* Enable SPI2 */
    SPI_Enable(SPI2, ENABLE);

    /* Enable SPI3 */
    SPI_Enable(SPI3, ENABLE);

    /* Begin the communication in SPI mode */
    while (RxIdx < BufferSize)
    {
        /* Wait the Tx buffer to be empty */
        while (SPI_I2S_GetStatus(SPI3, SPI_I2S_TE_FLAG) == RESET)
        {
        }

        /* Send a data from SPI3 */
        SPI_I2S_TransmitData(SPI3, SPI3_Buffer_Tx[TxIdx++]);

        /* Wait the Rx buffer to be full */
        while (SPI_I2S_GetStatus(SPI2, SPI_I2S_RNE_FLAG) == RESET)
        {
        }

        /* Store the SPI2 received data in the relative data table */
        SPI2_Buffer_Rx[RxIdx++] = SPI_I2S_ReceiveData(SPI2);
    }

    /* TransferStatus2 = PASSED, if the data transmitted from SPI3 and received by
                                 SPI2 are the same
       TransferStatus2 = FAILED, if the data transmitted from SPI3 and received by
                                 SPI2 are different */
    TransferStatus2 = Buffercmp((uint16_t*)SPI2_Buffer_Rx, SPI3_Buffer_Tx, BufferSize);

    /* Reset TxIdx, RxIdx indexes and receive table values */
    for (TxIdx = 0; TxIdx < BufferSize; TxIdx++)
    {
        I2S2_Buffer_Rx[TxIdx] = 0;
    }

    TxIdx = 0;
    RxIdx = 0;

    /* I2S3 Slave Transmitter to I2S2 Master Receiver communication ------------*/
    /* I2S3 configuration */
    I2S_InitStructure.I2sMode = I2S_MODE_SlAVE_TX;
    I2S_Init(SPI3, &I2S_InitStructure);

    /* I2S2 configuration */
    I2S_InitStructure.I2sMode = I2S_MODE_MASTER_RX;
    I2S_Init(SPI2, &I2S_InitStructure);

    /* Wait the Tx buffer to be empty */
    while (SPI_I2S_GetStatus(SPI3, SPI_I2S_TE_FLAG) == RESET)
    {

    }

    /* Prepare the first data to be sent from the slave */
    SPI_I2S_TransmitData(SPI3, I2S3_Buffer_Tx[TxIdx++]);

    /* Enable the I2S3 */
    I2S_Enable(SPI3, ENABLE);

    /* Enable the I2S2 */
    I2S_Enable(SPI2, ENABLE);

    /* Begin the communication in I2S mode */
    while (RxIdx < BufferSize)
    {
        I2S2_Buffer_Rx[RxIdx] = SPI_I2S_ReceiveData(SPI2); //Add this to avoid duplication of the first data

        /* Wait the Rx buffer to be full */
        while (SPI_I2S_GetStatus(SPI2, SPI_I2S_RNE_FLAG) == RESET)
        {
        }

        /* Store the I2S2 received data in the relative data table */
        I2S2_Buffer_Rx[RxIdx++] = SPI_I2S_ReceiveData(SPI2);

        /* Wait the Tx buffer to be empty */
        while (SPI_I2S_GetStatus(SPI3, SPI_I2S_TE_FLAG) == RESET)
        {
        }

        /* Send a data from I2S3 */
        SPI_I2S_TransmitData(SPI3, I2S3_Buffer_Tx[TxIdx++]);
    }

    /* TransferStatus3 = PASSED, if the data transmitted from I2S3 and received by
                                 I2S2 are the same
       TransferStatus3 = FAILED, if the data transmitted from I2S3 and received by
                                 I2S2 are different */
    TransferStatus3 = Buffercmp((uint16_t*)I2S2_Buffer_Rx, I2S3_Buffer_Tx, BufferSize);
    if((TransferStatus1 == PASSED) && (TransferStatus2 == PASSED) && (TransferStatus3 == PASSED))
        {
            log_info("SPI_I2S_Switch passed\n");
        }
        else
        {
        	if (TransferStatus1 != PASSED)
        	{
        		log_info("SPI_I2S_Switch failed:TransferStatus1\n");
        	}
        	if (TransferStatus2 != PASSED)
        	{
        		log_info("SPI_I2S_Switch failed:TransferStatus2\n");
        	}
        	if (TransferStatus3 != PASSED)
        	{
        		log_info("SPI_I2S_Switch failed:TransferStatus3\n");
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
    /* Enable peripheral clocks --------------------------------------------------*/
    /* GPIOB, GPIOC, GPIOD and AFIO clocks enable */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_GPIOC | RCC_APB2_PERIPH_GPIOD | RCC_APB2_PERIPH_AFIO, ENABLE);

    /* SPI2 and SPI3 clocks enable */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_SPI2 | RCC_APB1_PERIPH_SPI3, ENABLE);
}

/**
 * @brief  Configures the different GPIO ports.
 */
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    /* Disable the JTAG interface and enable the SWJ interface
        This operation is not necessary for Connectivity Line devices since
        SPI3 I/Os can be remapped on other GPIO pins */
//    GPIO_ConfigPinRemap(GPIO_RMP_SW_JTAG_SW_ENABLE, ENABLE);
    GPIO_ConfigPinRemap(GPIO_RMP1_SPI3, ENABLE);

    /* Configure SPI2 pins: WS, CK and SD ---------------------------------*/
    GPIO_InitStructure.Pin        = I2S_SLAVE_PIN_WS | I2S_SLAVE_PIN_CK | I2S_SLAVE_PIN_SD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* Configure SPI3 pins: CK and SD ------------------------------------*/
    GPIO_InitStructure.Pin       = I2S_MASTER_PIN_CK | I2S_MASTER_PIN_SD;
    GPIO_InitStructure.Pin = GPIO_PIN_10 | GPIO_PIN_12;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    /* Configure SPI3 pins: WS -------------------------------------------*/
    GPIO_InitStructure.Pin = I2S_MASTER_PIN_WS;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
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
 * @brief  Inserts a delay time.
 * @param nCount specifies the delay time length.
 */
void Delay(__IO uint32_t nCount)
{
    /* Decrement nCount value */
    for (; nCount != 0; nCount--)
        ;
}

/**
 * @}
 */

/**
 * @}
 */
