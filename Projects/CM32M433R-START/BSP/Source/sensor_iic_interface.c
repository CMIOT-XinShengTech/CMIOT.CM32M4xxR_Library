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
 * @file sensor_iic_interface.c
 * @author CMIOT Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */

#include "sensor_iic_interface.h"


#define I2CT_FLAG_TIMEOUT 	((uint32_t) 0x1000)
#define I2CT_LONG_TIMEOUT 	((uint32_t) (5 * I2CT_FLAG_TIMEOUT))
#define I2C_MASTER_ADDR   	(0x30)
/**
 * @brief  interface iic bus init
 * @return status code
 *         - 0 success
 *         - 1 iic init failed
 * @note   none
 */
uint8_t sensor_interface_iic_init(void)
{
	I2C_InitType i2c_master;
	GPIO_InitType i2c_gpio;

	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_I2C4, ENABLE);
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
	GPIO_ConfigPinRemap(GPIO_RMP3_I2C4, ENABLE);

	/* PB6/PB8 -- SCL; PB7/PB9 -- SDA */
	i2c_gpio.Pin        = GPIO_PIN_9 | GPIO_PIN_10;
	i2c_gpio.GPIO_Speed = GPIO_Speed_50MHz;
	i2c_gpio.GPIO_Mode  = GPIO_Mode_AF_OD;
	GPIO_Init(GPIOA, &i2c_gpio);

	I2C_DeInit(I2C4);
	i2c_master.BusMode     = I2C_BUSMODE_I2C;
	i2c_master.FmDutyCycle = I2C_FMDUTYCYCLE_2;
	i2c_master.OwnAddr1    = I2C_MASTER_ADDR;
	i2c_master.AckEnable   = I2C_ACKEN;
	i2c_master.AddrMode    = I2C_ADDR_MODE_7BIT;
	i2c_master.ClkSpeed    = 100000; /* Speed = 100K */

	I2C_Init(I2C4, &i2c_master);
	I2C_Enable(I2C4, ENABLE);
	I2C_ConfigAck(I2C4, ENABLE);

	return 0;
}

/**
 * @brief  interface iic bus deinit
 * @return status code
 *         - 0 success
 *         - 1 iic deinit failed
 * @note   none
 */
uint8_t sensor_interface_iic_deinit(void)
{
	I2C_DeInit(I2C4);
    return 0;
}

/**
 * @brief      interface iic bus read
 * @param[in]  addr is the iic device write address
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the length of the data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t sensor_interface_iic_read_cmd(uint8_t addr, uint8_t *buf, uint16_t len)
{
	uint8_t* recvBufferPtr = buf;
	volatile uint32_t I2CTimeout ;
	I2CTimeout    = I2CT_LONG_TIMEOUT;

	while (I2C_GetFlag(I2C4, I2C_FLAG_BUSY))
	{
		if ((I2CTimeout--) == 0)
			return 9;
	}

	I2C_ConfigAck(I2C4, ENABLE);

	/* Send start */
	I2C_GenerateStart(I2C4, ENABLE);

	I2CTimeout = I2CT_FLAG_TIMEOUT;
	while (!I2C_CheckEvent(I2C4, I2C_EVT_MASTER_MODE_FLAG)) /* EV5 */
	{
		if ((I2CTimeout--) == 0)
			return 10;
	}

	/* Send address */
	I2C_SendAddr7bit(I2C4, addr, I2C_DIRECTION_RECV);

	I2CTimeout = I2CT_FLAG_TIMEOUT;
	while (!I2C_CheckEvent(I2C4, I2C_EVT_MASTER_RXMODE_FLAG)) /* EV6 */
	{
		if ((I2CTimeout--) == 0)
			return 6;
	}

	/* Receive data */
	while (len > 0)
	{
		I2CTimeout = I2CT_LONG_TIMEOUT;
		while (!I2C_CheckEvent(I2C4, I2C_EVT_MASTER_DATA_RECVD_FLAG)) /* EV7 */
		{
			if ((I2CTimeout--) == 0)
				return 14;
		}

		if (len == 1)
		{
		   I2C_ConfigAck(I2C4, DISABLE);
		   I2C_GenerateStop(I2C4, ENABLE);
		}

		*recvBufferPtr++ = I2C_RecvData(I2C4);

		len--;
	};

	return 0;
}

/**
 * @brief     interface iic bus write
 * @param[in] addr is the iic device write address
 * @param[in] *buf points to a data buffer
 * @param[in] len is the length of the data buffer
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t sensor_interface_iic_write_cmd(uint8_t addr, uint8_t *buf, uint16_t len)
{
	uint8_t* sendBufferPtr = buf;
	volatile uint32_t I2CTimeout;

	I2CTimeout    = I2CT_LONG_TIMEOUT;

	while (I2C_GetFlag(I2C4, I2C_FLAG_BUSY))
	{
		if ((I2CTimeout--) == 0)
			return 4;
	}

	I2C_GenerateStart(I2C4, ENABLE);

	I2CTimeout = I2CT_FLAG_TIMEOUT;
	while (!I2C_CheckEvent(I2C4, I2C_EVT_MASTER_MODE_FLAG)) /* EV5 */
	{
		if ((I2CTimeout--) == 0)
			return 5;
	}

	I2C_SendAddr7bit(I2C4, addr, I2C_DIRECTION_SEND);

	I2CTimeout = I2CT_FLAG_TIMEOUT;
	while (!I2C_CheckEvent(I2C4, I2C_EVT_MASTER_TXMODE_FLAG)) /* EV6 */
	{
		if ((I2CTimeout--) == 0)
			return 6;
	}

	/* Send data */
	while (len > 0)
	{
		I2C_SendData(I2C4, *sendBufferPtr++);

		I2CTimeout = I2CT_FLAG_TIMEOUT;
		while (!I2C_CheckEvent(I2C4, I2C_EVT_MASTER_DATA_SENDING)) /* EV8 */
		{
			if ((I2CTimeout--) == 0)
				return 7;
		}
		len--;
	}

	I2CTimeout = I2CT_FLAG_TIMEOUT;
	while (!I2C_CheckEvent(I2C4, I2C_EVT_MASTER_DATA_SENDED)) /* EV8-2 */
	{
		if ((I2CTimeout--) == 0)
			return 8;
	}

	I2C_GenerateStop(I2C4, ENABLE);

	return 0;
}

/**
 * @brief     interface delay ms
 * @param[in] ms
 * @note      none
 */
void sensor_interface_delay_ms(uint32_t ms)
{
	delay_ms(ms);
}

