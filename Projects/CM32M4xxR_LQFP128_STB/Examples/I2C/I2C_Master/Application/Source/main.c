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
#include "bsp.h"

/** @addtogroup CM32M4xxR_StdPeriph_Examples
 * @{
 */

/** @addtogroup I2C_Master
 * @{
 */

#define TEST_BUFFER_SIZE  	(10)
#define I2CT_FLAG_TIMEOUT 	((uint32_t) 0x1000)
#define I2CT_LONG_TIMEOUT 	((uint32_t) (10 * I2C_FLAG_TIMOUT))
#define I2C_MASTER_ADDR   	(0x30)
#define I2C_SLAVE_ADDR    	(0xA0)

#define I2C1_TEST
//#define I2C1_REMAP

#ifdef I2C1_TEST
#define I2Cx				I2C1
#ifdef I2C1_REMAP
#define I2Cx_SCL_PIN		GPIO_PIN_8
#define I2Cx_SDA_PIN		GPIO_PIN_9
#define GPIOx        		GPIOB
#else
#define I2Cx_SCL_PIN		GPIO_PIN_6
#define I2Cx_SDA_PIN		GPIO_PIN_7
#define GPIOx       		GPIOB
#endif
#endif

uint8_t tx_buf[TEST_BUFFER_SIZE] = {0};
uint8_t rx_buf[TEST_BUFFER_SIZE] = {0};
volatile Status test_status      = FAILED;

Status Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);

static __IO uint32_t I2CTimeout = I2CT_LONG_TIMEOUT;

void Delay(uint32_t nCount)
{
    uint32_t tcnt = 144000;

    while(nCount--)
    {
        for (; tcnt != 0; tcnt--)
            ;
    }
}

int i2c_master_init(void)
{
    I2C_InitType i2c1_master;
    GPIO_InitType i2c1_gpio;

    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_I2C1, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
#ifdef I2C1_REMAP
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
    GPIO_ConfigPinRemap(GPIO_RMP_I2C1, ENABLE);
#endif

    /* PB6/PB8 -- SCL; PB7/PB9 -- SDA */
    i2c1_gpio.Pin        = I2Cx_SCL_PIN | I2Cx_SDA_PIN;
    i2c1_gpio.GPIO_Speed = GPIO_Speed_2MHz;
    i2c1_gpio.GPIO_Mode  = GPIO_Mode_AF_OD;
    GPIO_Init(GPIOx, &i2c1_gpio);

    I2C_DeInit(I2Cx);
    i2c1_master.BusMode     = I2C_BUSMODE_I2C;
    i2c1_master.FmDutyCycle = I2C_FMDUTYCYCLE_2;
    i2c1_master.OwnAddr1    = I2C_MASTER_ADDR;
    i2c1_master.AckEnable   = I2C_ACKEN;
    i2c1_master.AddrMode    = I2C_ADDR_MODE_7BIT;
    i2c1_master.ClkSpeed    = 100000; /* Speed = 100K */

    I2C_Init(I2Cx, &i2c1_master);
    I2C_Enable(I2Cx, ENABLE);
    I2C_ConfigAck(I2Cx, ENABLE);

    return 0;
}

int i2c_master_send(uint8_t* data, int len)
{
    uint8_t* sendBufferPtr = data;
    I2CTimeout             = I2CT_LONG_TIMEOUT;

    while (I2C_GetFlag(I2Cx, I2C_FLAG_BUSY))
    {
        if ((I2CTimeout--) == 0)
            return 4;
    };

    I2C_GenerateStart(I2Cx, ENABLE);

    I2CTimeout = I2C_FLAG_TIMOUT;
    while (!I2C_CheckEvent(I2Cx, I2C_EVT_MASTER_MODE_FLAG)) /* EV5 */
    {
        if ((I2CTimeout--) == 0)
            return 5;
    };

    I2C_SendAddr7bit(I2Cx, I2C_SLAVE_ADDR, I2C_DIRECTION_SEND);

    I2CTimeout = I2C_FLAG_TIMOUT;
    while (!I2C_CheckEvent(I2Cx, I2C_EVT_MASTER_TXMODE_FLAG)) /* EV6 */
    {
        if ((I2CTimeout--) == 0)
            return 6;
    };

    /* Send data */
    while (len-- > 0)
    {
        I2C_SendData(I2Cx, *sendBufferPtr++);

        I2CTimeout = I2C_FLAG_TIMOUT;
        while (!I2C_CheckEvent(I2Cx, I2C_EVT_MASTER_DATA_SENDING)) /* EV8 */
        {
            if ((I2CTimeout--) == 0)
                return 7;
        };
    };

    I2CTimeout = I2C_FLAG_TIMOUT;
    while (!I2C_CheckEvent(I2Cx, I2C_EVT_MASTER_DATA_SENDED)) /* EV8-2 */
    {
        if ((I2CTimeout--) == 0)
            return 8;
    };

    I2C_GenerateStop(I2Cx, ENABLE);

    return 0;
}

int i2c_master_recv(uint8_t* data, int len)
{
    uint8_t* recvBufferPtr = data;
    I2CTimeout             = I2CT_LONG_TIMEOUT;

    while (I2C_GetFlag(I2Cx, I2C_FLAG_BUSY))
    {
        if ((I2CTimeout--) == 0)
            return 9;
    };

    I2C_ConfigAck(I2Cx, ENABLE);

    /* Send start */
    I2C_GenerateStart(I2Cx, ENABLE);

    I2CTimeout = I2C_FLAG_TIMOUT;
    while (!I2C_CheckEvent(I2Cx, I2C_EVT_MASTER_MODE_FLAG)) /* EV5 */
    {
        if ((I2CTimeout--) == 0)
            return 10;
    };

    /* Send address */
    I2C_SendAddr7bit(I2Cx, I2C_SLAVE_ADDR, I2C_DIRECTION_RECV);

    I2CTimeout = I2C_FLAG_TIMOUT;
    while (!I2C_CheckEvent(I2Cx, I2C_EVT_MASTER_RXMODE_FLAG)) /* EV6 */
    {
        if ((I2CTimeout--) == 0)
            return 6;
    };

    /* Receive data */
    while (len-- > 0)
    {
        I2CTimeout = I2CT_LONG_TIMEOUT;
        while (!I2C_CheckEvent(I2Cx, I2C_EVT_MASTER_DATA_RECVD_FLAG)) /* EV7 */
        {
            if ((I2CTimeout--) == 0)
                return 14;
        };

		if (len == 1)
        {
           I2C_ConfigAck(I2Cx, DISABLE);
           I2C_GenerateStop(I2Cx, ENABLE);
        }

        *recvBufferPtr++ = I2C_RecvData(I2Cx);
    };

    return 0;
}

/**
 * @brief   Main function
 */
int main(void)
{
    uint16_t i = 0;

    log_init();
    log_info("this is a i2c master demo\r\n");

    /* Initialize the I2C EEPROM driver ----------------------------------------*/
    i2c_master_init();

    /* Fill the buffer to send */
    for (i = 0; i < TEST_BUFFER_SIZE; i++)
    {
        tx_buf[i] = i;
    }

    log_info("i2c master send data start...\r\n");
    /* First write in the memory followed by a read of the written data --------*/
    /* Write data*/
    i2c_master_send(tx_buf, TEST_BUFFER_SIZE);

    Delay(100);

    log_info("i2c master recv data start...\r\n");
    /* Read data */
    i2c_master_recv(rx_buf, TEST_BUFFER_SIZE);

    /* Check if the data written to the memory is read correctly */
    test_status = Buffercmp(tx_buf, rx_buf, TEST_BUFFER_SIZE);
    if (test_status == PASSED)
    {
        log_info("write and read data the same, i2c master test pass\r\n");
		log_info("recv = ");
		for (i = 0; i < TEST_BUFFER_SIZE; i++)
		{
			log_info("%02x", rx_buf[i]);
		}
		log_info("\r\n");
    }
    else
    {
        log_info("write and read data are different, i2c master test fail\r\n");
    }

    /* test_status = PASSED, if the write and read data are the same  */
    /* test_status = FAILED, if the write and read data are different */
    while (1)
    {
    }
}

/**
 * @brief  Compares two buffers.
 * @param  pBuffer, pBuffer1: buffers to be compared.
 * @param BufferLength buffer's length
 * @return PASSED: pBuffer identical to pBuffer1
 *         FAILED: pBuffer differs from pBuffer1
 */
Status Buffercmp(uint8_t* pBuffer, uint8_t* pBuffer1, uint16_t BufferLength)
{
    while (BufferLength--)
    {
        if (*pBuffer != *pBuffer1)
        {
            return FAILED;
        }

        pBuffer++;
        pBuffer1++;
    }

    return PASSED;
}

/**
 * @}
 */

/**
 * @}
 */
