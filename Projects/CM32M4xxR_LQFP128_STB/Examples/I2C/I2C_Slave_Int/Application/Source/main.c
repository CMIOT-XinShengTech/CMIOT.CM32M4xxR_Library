/*
  ******************************************************************************
  *
  * COPYRIGHT(c) 2020, China Mobile IOT
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of China Mobile IOT nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
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
  ******************************************************************************
  */ 

/**
 * @file main.c
 * @author CMIOT
 * @version v1.0.1
 *
 * @COPYRIGHT(c) 2020, China Mobile IOT. All rights reserved.
 */
#include "nuclei_sdk_soc.h"
#include "main.h"
#include "bsp.h"
/** @addtogroup CM32M4xxR_StdPeriph_Examples
 * @{
 */

/** @addtogroup I2C_Slave_Int
 * @{
 */

#define TEST_BUFFER_SIZE  10
#define I2CT_FLAG_TIMEOUT ((uint32_t)0x1000)
#define I2CT_LONG_TIMEOUT ((uint32_t)(10 * I2CT_FLAG_TIMEOUT))
#define I2C_SLAVE_ADDR    (0xA0)

#define I2C1_TEST
#define I2C1_REMAP
#define I2Cx I2C1
#define I2Cx_SCL_PIN GPIO_PIN_6
#define I2Cx_SDA_PIN GPIO_PIN_7
#define GPIOx        GPIOB

uint8_t data_buf[TEST_BUFFER_SIZE] = {0};
static __IO uint32_t I2CTimeout;
volatile uint8_t flag_slave_recv_finish         = 0;
volatile uint8_t flag_slave_send_finish         = 0;
static uint8_t rxDataNum = 0;
static uint8_t RCC_RESET_Flag = 0;

void CommTimeOut_CallBack(ErrCode_t errcode);

/**
 * @brief  i2c slave Interrupt configuration
 * @param ch I2C channel
 */
void ECLIC_Config(uint8_t ch)
{
	if(ch == 1)
	{
		/* Enable the IIC1 event Interrupt */
		ECLIC_SetLevelIRQ(I2C1_EV_IRQn, 4);
		ECLIC_SetPriorityIRQ(I2C1_EV_IRQn, 1);
		ECLIC_SetTrigIRQ(I2C1_EV_IRQn, ECLIC_LEVEL_TRIGGER);
		ECLIC_EnableIRQ(I2C1_EV_IRQn);

		/* Enable the IIC1 error Interrupt */
		ECLIC_SetLevelIRQ(I2C1_ER_IRQn, 3);
		ECLIC_SetPriorityIRQ(I2C1_ER_IRQn, 1);
		ECLIC_SetTrigIRQ(I2C1_ER_IRQn, ECLIC_LEVEL_TRIGGER);
		ECLIC_EnableIRQ(I2C1_ER_IRQn);
	}

	if(ch == 2)
	{
		/* Enable the IIC2 event Interrupt */
		ECLIC_SetLevelIRQ(I2C2_EV_IRQn, 4);
		ECLIC_SetPriorityIRQ(I2C2_EV_IRQn, 1);
		ECLIC_SetTrigIRQ(I2C2_EV_IRQn, ECLIC_LEVEL_TRIGGER);
		ECLIC_EnableIRQ(I2C2_EV_IRQn);

		/* Enable the IIC2 error Interrupt */
		ECLIC_SetLevelIRQ(I2C2_ER_IRQn, 3);
		ECLIC_SetPriorityIRQ(I2C2_ER_IRQn, 1);
		ECLIC_SetTrigIRQ(I2C2_ER_IRQn, ECLIC_LEVEL_TRIGGER);
		ECLIC_EnableIRQ(I2C2_ER_IRQn);
	}
}

/**
 * @brief  i2c slave init
 * @return 0:init finish
 */
int i2c_slave_init(void)
{
    I2C_InitType i2c1_master;
    GPIO_InitType i2c1_gpio;
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_I2C1, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);

    /*PB8 -- SCL; PB9 -- SDA*/
    GPIO_InitStruct(&i2c1_gpio);
    i2c1_gpio.Pin               = GPIO_PIN_6;
    i2c1_gpio.GPIO_Mode         = GPIO_Mode_AF_OD;
    i2c1_gpio.GPIO_Speed        = GPIO_Speed_2MHz;
    GPIO_Init(GPIOB, &i2c1_gpio);

    i2c1_gpio.Pin               = GPIO_PIN_7;
    i2c1_gpio.GPIO_Mode         = GPIO_Mode_AF_OD;
    i2c1_gpio.GPIO_Speed        = GPIO_Speed_2MHz;
    GPIO_Init(GPIOB, &i2c1_gpio);
    
    I2C_DeInit(I2C1);
    i2c1_master.BusMode     = I2C_BUSMODE_I2C;
    i2c1_master.FmDutyCycle = I2C_FMDUTYCYCLE_2;
    i2c1_master.OwnAddr1    = I2C_SLAVE_ADDR;
    i2c1_master.AckEnable   = I2C_ACKEN;
    i2c1_master.AddrMode    = I2C_ADDR_MODE_7BIT;
    i2c1_master.ClkSpeed    = 100000; //100K

    I2C_Init(I2C1, &i2c1_master);
    // int enable
    I2C_ConfigInt(I2C1, I2C_INT_EVENT | I2C_INT_BUF | I2C_INT_ERR, ENABLE);
    ECLIC_Config((uint8_t)1);
    __enable_irq();
    I2C_Enable(I2C1, ENABLE);
    return 0;
}

/**
 * @brief   Main program
 */
int main(void)
{
	uint16_t i;
    log_init();
    log_info("\nthis is a i2c slave int demo\r\n");

    /* Initialize the I2C slave driver ----------------------------------------*/
    i2c_slave_init();

    I2CTimeout = I2CT_LONG_TIMEOUT * 1000;
    // recive data
    log_info("i2c slave int recv data start...\r\n");
    while (flag_slave_recv_finish == 0) // wait for recv data finish
    {
        if ((I2CTimeout--) == 0)
            CommTimeOut_CallBack(SLAVE_UNKNOW);
    }
    
    log_info("recv finish,recv len = %d", rxDataNum);
    log_info("recv = ");

    for (i = 0; i < rxDataNum; i++)
    {
        log_info("%02x", data_buf[i]);
    }
    flag_slave_recv_finish = 0;
    
    I2CTimeout = I2CT_LONG_TIMEOUT * 1000;
    // send data
    log_info("i2c slave int send data start...\r\n");
    while (flag_slave_send_finish == 0) // wait for send data finish
    {
        if ((I2CTimeout--) == 0)
            CommTimeOut_CallBack(SLAVE_UNKNOW);
    }
        
    log_info("tx finish,tx len = %d\r\n", rxDataNum);
    flag_slave_send_finish = 0;
    
    log_info("i2c slave int test pass\r\n");

    while (1)
    {;}
}

/**
 * @brief  i2c slave Interrupt service function
 */
void I2C1_EV_IRQHandler(void)
{
	uint32_t last_event;
	uint8_t MatchFlg = 0;

    last_event = I2C_GetLastEvent(I2C1);

    if((last_event & I2C_STS2_MSMODE) != I2C_STS2_MSMODE)		//Slave Mode
    {
    	if((last_event & I2C_STS1_ADDRF) != 0)
    	{
    		rxDataNum = 0;
    		MatchFlg = 1;
    	}

    	if((last_event & I2C_STS1_TXDATE) != 0)
		{
            if (rxDataNum == TEST_BUFFER_SIZE)
            {
                I2C_ConfigInt(I2C1, I2C_INT_BUF, DISABLE);
                flag_slave_recv_finish = 1;
            }
            else
            {
                I2C1->DAT = data_buf[rxDataNum++];
            }
            MatchFlg = 1;
		}

    	if((last_event & I2C_STS1_RXDATNE) != 0)
		{
    		data_buf[rxDataNum++] = I2C1->DAT;
            if (rxDataNum == TEST_BUFFER_SIZE)
            {
            	I2C_ConfigInt(I2C1, I2C_INT_BUF, DISABLE);
            	flag_slave_recv_finish = 1;
            }
            MatchFlg = 1;
		}

    	if((last_event & I2C_STS1_STOPF) != 0)
		{
			I2C_Enable(I2C1, ENABLE);	// clear STOPF bit
			MatchFlg = 1;
		}

    	if(MatchFlg == 0)
		{
			I2C_Enable(I2C1, ENABLE);	//unknown state
		}
    }
}

void I2C1_ER_IRQHandler(void)
{
	uint32_t last_event;
	last_event = I2C_GetLastEvent(I2C1);
	I2C_ClrIntPendingBit(I2C1, I2C_INT_SMBALERT|I2C_INT_TIMOUT|I2C_INT_PECERR|I2C_INT_OVERRUN|I2C_INT_ACKFAIL|I2C_INT_ARLOST|I2C_INT_BUSERR);

	if((last_event & I2C_STS1_BUSERR) != 0)
	{

		printf("Master detect Bus Error\r\n"); 				//Bus Error
	}

	if((last_event & I2C_STS1_ARLOST) != 0)
	{
		printf("Master detect Arbitration Lost Error\r\n"); //Arbitration Lost Error
	}

	if((last_event & I2C_STS1_ACKFAIL) != 0)
	{
		if(rxDataNum == TEST_BUFFER_SIZE)  //slave send the last data and recv NACK
		{
			flag_slave_send_finish = 1;
			printf("send data finish, send pass!\r\n");			//slave send OK
		}
		else //not the last data recv nack, send fail
		{
			printf("Master detect ACK Fail Error\r\n"); 		//ACK Fail Error
		}
	}

	if((last_event & I2C_STS1_OVERRUN) != 0)
	{
		printf("Master detect Overrun/Underrun Error\r\n"); //Overrun/Underrun Error
	}

	if((last_event & I2C_STS1_PECERR) != 0)
	{
		printf("Master detect PEC Error\r\n"); 				//PEC Error
	}

	if((last_event & I2C_STS1_TIMOUT) != 0)
	{
		printf("Master detect Timeout or Tlow Error\r\n"); //Timeout or Tlow Error
	}

	if((last_event & I2C_STS1_SMBALERT) != 0)
	{
		printf("Master detect SMBus Alert \r\n"); 			//SMBus Alert
	}
}
void CommTimeOut_CallBack(ErrCode_t errcode)
{
    log_info("...ErrCode:%d\r\n", errcode);
}

/**
 * @}
 */
