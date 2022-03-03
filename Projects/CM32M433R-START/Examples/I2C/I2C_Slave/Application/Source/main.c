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

/** @addtogroup I2C_Slave
 * @{
 */

#define TEST_BUFFER_SIZE	(10)
#define I2CT_FLAG_TIMEOUT 	((uint32_t) 0x1000)
#define I2CT_LONG_TIMEOUT 	((uint32_t) (10 * I2C_FLAG_TIMOUT))
#define I2C_SLAVE_ADDR    	(0xA0)

#define I2C2_TEST
#define I2C2_REMAP
//#define I2C4_TEST
//#define I2C4_REMAP

#ifdef I2C2_TEST
#define I2Cx				I2C2
#ifdef I2C2_REMAP
#define I2Cx_SCL_PIN		GPIO_PIN_2
#define I2Cx_SDA_PIN		GPIO_PIN_3
#define GPIOx        		GPIOG
#else
#define I2Cx_SCL_PIN		GPIO_PIN_10
#define I2Cx_SDA_PIN		GPIO_PIN_11
#define GPIOx       		GPIOB
#endif
#endif

#ifdef I2C4_TEST
#define I2Cx				I2C4
#ifdef I2C4_REMAP
#define I2Cx_SCL_PIN		GPIO_PIN_9
#define I2Cx_SDA_PIN		GPIO_PIN_10
#define GPIOx        		GPIOA
#else
#define I2Cx_SCL_PIN		GPIO_PIN_6
#define I2Cx_SDA_PIN		GPIO_PIN_7
#define GPIOx       		GPIOC
#endif
#endif

uint8_t data_buf[TEST_BUFFER_SIZE] = {0};
volatile Status test_status        = FAILED;

Status Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);

static __IO uint32_t I2CTimeout = I2CT_LONG_TIMEOUT;

/**
 * @brief  I2C slave init
 *
 * @return 0: initialize finish
 */
int i2c_slave_init(void)
{
    I2C_InitType i2c_slave;
    GPIO_InitType i2c_gpio;

    /* Enable clock */
#ifdef I2C2_TEST
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_I2C2, ENABLE);
#ifdef I2C2_REMAP
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOG, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
    GPIO_ConfigPinRemap(GPIO_RMP1_I2C2, ENABLE);
#else
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
#endif
#endif

#ifdef I2C4_TEST
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_I2C4, ENABLE);
#ifdef I2C4_REMAP
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
    GPIO_ConfigPinRemap(GPIO_RMP3_I2C4, ENABLE);
#else
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);
#endif
#endif

    /* PB6/PB8 -- SCL; PB7/PB9 -- SDA */
    i2c_gpio.Pin        = I2Cx_SCL_PIN;
    i2c_gpio.GPIO_Speed = GPIO_Speed_2MHz;
    i2c_gpio.GPIO_Mode  = GPIO_Mode_AF_OD;
    GPIO_Init(GPIOx, &i2c_gpio);

    i2c_gpio.Pin        = I2Cx_SDA_PIN;
    i2c_gpio.GPIO_Speed = GPIO_Speed_2MHz;
    i2c_gpio.GPIO_Mode  = GPIO_Mode_AF_OD;
    GPIO_Init(GPIOx, &i2c_gpio);

    I2C_DeInit(I2Cx);
    i2c_slave.BusMode     = I2C_BUSMODE_I2C;
    i2c_slave.FmDutyCycle = I2C_FMDUTYCYCLE_2;
    i2c_slave.OwnAddr1    = I2C_SLAVE_ADDR;
    i2c_slave.AckEnable   = I2C_ACKEN;
    i2c_slave.AddrMode    = I2C_ADDR_MODE_7BIT;
    i2c_slave.ClkSpeed    = 100000; /* Speed = 100K */

    I2C_Init(I2Cx, &i2c_slave);

    I2C_Enable(I2Cx, ENABLE);

    return 0;
}

/**
 * @brief  I2C slave send data
 *
 * @param data data buffer
 * @param len send data len
 * @return 0: send finish
 */
int i2c_slave_send(uint8_t* data, int len)
{
    uint8_t* sendBufferPtr = data;
    uint32_t tx_index      = 0;
    I2CTimeout             = I2CT_LONG_TIMEOUT;

    while (!I2C_CheckEvent(I2Cx, I2C_EVT_SLAVE_SEND_ADDR_MATCHED))
        ; /* Send addr matched */

    /* Send data */
    while (tx_index < (len - 1))
    {
        I2C_SendData(I2Cx, *sendBufferPtr++);

        I2CTimeout = I2C_FLAG_TIMOUT;
        while (!I2C_CheckEvent(I2Cx, I2C_EVT_SLAVE_DATA_SENDED))
        {
            if ((I2CTimeout--) == 0)
                return 7;
        };

        tx_index++;
    };

    /* Send last data and clear EV3 */
    I2C_SendData(I2Cx, *sendBufferPtr);
    while (!I2C_CheckEvent(I2Cx, I2C_EVT_SLAVE_ACK_MISS))
        ; /* EV3-2 */

    /* Clear I2C AF flag */
    I2C_ClrFlag(I2Cx, I2C_FLAG_ACKFAIL); /* EV3-2: AF = 1, write 0 to STS1 AF bit to clear AF flag */

    return 0;
}

/**
 * @brief  I2C slave receive data
 *
 * @param data data buffer,use to save received data
 * @param rcv_len receive data len
 * @return 0: recv finish
 */
int i2c_slave_recv(uint8_t* data, uint32_t rcv_len)
{
    uint32_t rx_index      = 0;
    I2CTimeout             = I2CT_LONG_TIMEOUT;

    while (!I2C_CheckEvent(I2Cx, I2C_EVT_SLAVE_RECV_ADDR_MATCHED))
        ; /* Receive addr matched */

    /* Receive data */
    while (rx_index < rcv_len)
    {
        while (!I2C_CheckEvent(I2Cx, I2C_EVT_SLAVE_DATA_RECVD))
            ;

        *data = I2C_RecvData(I2Cx);

        rx_index++;
        data++;
    };

    while (!I2C_CheckEvent(I2Cx, I2C_EVT_SLAVE_STOP_RECVD))
        ; /* EV4 */

    I2C_Enable(I2Cx, ENABLE);		/* Clear STOPF bit */

    return 0;
}

/**
 * @brief   Main function
 */
int main(void)
{
    uint16_t i = 0;

    log_init();
    log_info("this is a i2c slave test demo\r\n");

    /* Initialize the I2C EEPROM driver ---------------------------------------- */
    i2c_slave_init();

    /* Read data */
    log_info("i2c slave recv data start...\r\n");
    i2c_slave_recv(data_buf, TEST_BUFFER_SIZE);
    log_info("recv finish,recv len = %d", TEST_BUFFER_SIZE);
    log_info("recv = ");

    for (i = 0; i < TEST_BUFFER_SIZE; i++)
    {
        log_info("%02x", data_buf[i]);
    }

    log_info("\r\n");

    /* Write data */
    log_info("i2c slave send data start...\r\n");
    i2c_slave_send(data_buf, TEST_BUFFER_SIZE);
    log_info("tx finish,tx len = %d\r\n", TEST_BUFFER_SIZE);

    log_info("i2c slave test pass\r\n");

    while (1)
    {
    }
}

/**
 * @brief Compares two buffers.
 * @param pBuffer, pBuffer1: buffers to be compared.
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
