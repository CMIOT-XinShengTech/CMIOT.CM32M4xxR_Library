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
#include "main.h"
#include "nuclei_sdk_soc.h"
#include "bsp.h"
/** @addtogroup CM32M4xxR_StdPeriph_Examples
 * @{
 */

/** @addtogroup I2C_Master_Int
 * @{
 */

#define TEST_BUFFER_SIZE  10
#define I2CT_FLAG_TIMEOUT ((uint32_t)0x1000)
#define I2CT_LONG_TIMEOUT ((uint32_t)(10 * I2CT_FLAG_TIMEOUT))
#define I2C_MASTER_ADDR   0x30
#define I2C_SLAVE_ADDR    0xA0

#define I2Cx I2C1
#define I2Cx_SCL_PIN GPIO_PIN_6
#define I2Cx_SDA_PIN GPIO_PIN_7
#define GPIOx        GPIOB

uint8_t tx_buf[TEST_BUFFER_SIZE] = {0};
uint8_t rx_buf[TEST_BUFFER_SIZE] = {0};
volatile Status test_status = FAILED;
static __IO uint32_t I2CTimeout;
static CommCtrl_t Comm_Flag = C_READY;

static uint8_t rx_num = 0;
static uint8_t tx_num = 0;
volatile uint8_t flag_master_recv_finish = 0;
volatile uint8_t flag_master_send_finish = 0;
uint8_t flag_trans_direct       = 0; // write

Status Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);
void Memset(void* s, uint8_t c, uint32_t count);
void CommTimeOut_CallBack(ErrCode_t errcode);

/**
 * @brief  i2c Interrupt configuration
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
 * @brief  i2c master init
 * @return 0:init finish
 *
 */
int i2c_master_init(void)
{
    I2C_InitType i2c1_master;
    GPIO_InitType i2c1_gpio;

    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_I2C1,  ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO | RCC_APB2_PERIPH_GPIOB, ENABLE);

    /*PB6 -- SCL; PB7 -- SDA*/
    GPIO_InitStruct(&i2c1_gpio);
    /* Configure IIC1 SCL pin */
    i2c1_gpio.Pin       = GPIO_PIN_6;
    i2c1_gpio.GPIO_Mode = GPIO_Mode_AF_OD;
    i2c1_gpio.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOB, &i2c1_gpio);
    /* Configure IIC1 SDA pin */
    i2c1_gpio.Pin        = GPIO_PIN_7;
    i2c1_gpio.GPIO_Mode  = GPIO_Mode_AF_OD;
    i2c1_gpio.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOB, &i2c1_gpio);

    I2C_DeInit(I2C1);
    i2c1_master.BusMode     = I2C_BUSMODE_I2C;
    i2c1_master.FmDutyCycle = I2C_FMDUTYCYCLE_2;
    i2c1_master.OwnAddr1    = I2C_MASTER_ADDR;
    i2c1_master.AckEnable   = I2C_ACKEN;
    i2c1_master.AddrMode    = I2C_ADDR_MODE_7BIT;
    i2c1_master.ClkSpeed    = 100000;

    I2C_Init(I2C1, &i2c1_master);
    // int enable
    I2C_ConfigInt(I2C1, I2C_INT_EVENT | I2C_INT_ERR, ENABLE);
    ECLIC_Config(1);
    __enable_irq();
    I2C_Enable(I2C1, ENABLE);

    return 0;
}


/**
 * @brief   Main program
 */
int main(void)
{
    uint16_t i = 0;
    
    log_init();
    log_info("\nthis is a i2c master int demo\r\n");
    /* Initialize the I2C driver  */
    i2c_master_init();

    /* Fill the buffer to send */
    for (i = 0; i < TEST_BUFFER_SIZE; i++)
    {
        tx_buf[i] = i;
    }
    /* First write in the memory followed by a read of the written data --------*/
    /* Write data*/
    log_info("i2c master int send data start...\r\n");
    flag_trans_direct = 0;
    if (Comm_Flag == C_READY)
    {
        Comm_Flag = C_START_BIT;
        I2C_GenerateStart(I2C1, ENABLE);
    }
    
    I2CTimeout = I2CT_LONG_TIMEOUT * 1000;
    while (flag_master_send_finish == 0)
    {
        if ((I2CTimeout--) == 0)
        {
            CommTimeOut_CallBack(MASTER_UNKNOW);
        }
    }
    
    delay_ms(1);
    // master send finish
    flag_master_send_finish = 0;
    I2CTimeout = I2CT_LONG_TIMEOUT;
    while (I2C_GetFlag(I2C1, I2C_FLAG_BUSY))
    {
        if ((I2CTimeout--) == 0)
        {
            CommTimeOut_CallBack(MASTER_BUSY);
        }
    }
    Comm_Flag = C_READY;
    
    log_info("i2c master int recv data start...\r\n");
    I2C_ConfigAck(I2C1, ENABLE);
    I2C_ConfigInt(I2C1, I2C_INT_BUF, ENABLE);
    I2C_GenerateStop(I2C1, DISABLE);
    /*read data*/
    flag_trans_direct = 1;
    if (Comm_Flag == C_READY)
    {
        Comm_Flag = C_START_BIT;
        I2C_GenerateStart(I2C1, ENABLE);
    }
    
    I2CTimeout = I2CT_LONG_TIMEOUT * 1000;
    while (flag_master_recv_finish == 0)
    {
        if ((I2CTimeout--) == 0)
        {
            CommTimeOut_CallBack(MASTER_UNKNOW);
        }
    }
    
    /* master recv finish */
    flag_master_recv_finish = 0;
    I2CTimeout = I2CT_LONG_TIMEOUT;
    while (I2C_GetFlag(I2C1, I2C_FLAG_BUSY))
    {
        if ((I2CTimeout--) == 0)
        {
            CommTimeOut_CallBack(MASTER_BUSY);
        }
    }
    Comm_Flag = C_READY;
    
    /* Check if the data written to the memory is read correctly */
    test_status = Buffercmp(tx_buf, rx_buf, TEST_BUFFER_SIZE);
    if (test_status == PASSED)
    {
        log_info("write and read data the same, i2c master int test pass\r\n");
		log_info("recv = ");
		for (i = 0; i < TEST_BUFFER_SIZE; i++)
		{
			log_info("%02x", rx_buf[i]);
		}
		log_info("\r\n");
    }
    else
    {
        log_info("write and read data are different, i2c master int test fail\r\n");
    }

    while (1)
    {
    }
}

/**
 * @brief  i2c Interrupt service function
 *
 */
void I2C1_EV_IRQHandler(void)
{
	uint32_t last_event;
	uint8_t MatchFlg = 0;

    last_event = I2C_GetLastEvent(I2C1);
    if((last_event & I2C_ROLE_MASTER) == I2C_ROLE_MASTER)
    {
    	if((last_event & I2C_STS1_STARTBF) != 0)
    	{
            if (flag_trans_direct == 0)    // write
            {
                I2C_SendAddr7bit(I2C1, I2C_SLAVE_ADDR, I2C_DIRECTION_SEND);
                tx_num = 0;
                rx_num = 0;
            }
            else if (flag_trans_direct == 1) // read
            {
                I2C_SendAddr7bit(I2C1, I2C_SLAVE_ADDR, I2C_DIRECTION_RECV);
                tx_num = 0;
                rx_num = 0;
            }
            MatchFlg = 1;
    	}

    	if((last_event & I2C_STS1_ADDRF) != 0)  												//The Address send finished and send the first byte
    	{
    		MatchFlg = 1;
    	}

    	if(((last_event & I2C_STS1_TXDATE) != 0) && (flag_trans_direct == 0))				//keep send bytes
    	{
    		if (tx_num < TEST_BUFFER_SIZE)
			{
				I2C_SendData(I2C1, tx_buf[tx_num++]);	//Send bytes
				if((I2C_GetLastEvent(I2C1) & I2C_STS1_TXDATE) != 0)
				{
					I2C_SendData(I2C1, tx_buf[tx_num++]);	//Send bytes
				}
			}
			else // data send finish
			{
				I2C_ConfigInt(I2C1, I2C_INT_BUF, DISABLE);
				I2C_GenerateStop(I2C1, ENABLE);					//Send StopF
				flag_master_send_finish = 1;
			}
    		MatchFlg = 1;
    	}

    	if(((last_event & I2C_STS1_RXDATNE) != 0) && (flag_trans_direct == 1))  			//Master Receive byte
    	{
            rx_buf[rx_num++] = I2C_RecvData(I2C1);
    		if (rx_num == TEST_BUFFER_SIZE)
    		{
    			I2C_ConfigInt(I2C1, I2C_INT_BUF, DISABLE);
    			flag_master_recv_finish = 1;
    		}
            // before the last data,should config NACK and STOP
            if (rx_num == (TEST_BUFFER_SIZE - 1))
            {
                I2C_ConfigAck(I2C1, DISABLE);   // Disable I2C1 acknowledgement.
                I2C_GenerateStop(I2C1, ENABLE); // Send I2C1 STOP Condition.
            }
            MatchFlg = 1;
    	}

    	if(MatchFlg == 0)																	//unknown state
    	{
    		I2C_GenerateStop(I2C1, ENABLE);
    	}
    }
    else if(((last_event & I2C_STS1_RXDATNE) != 0) && (flag_trans_direct == 0))			//IIC state may switch to Slave mode before receive the last byte
    {
    	rx_buf[rx_num++] = I2C_RecvData(I2C1);
		if (rx_num == TEST_BUFFER_SIZE)
		{
			flag_master_recv_finish = 1;
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
    	log_info("Master detect Bus Error\r\n"); 				//Bus Error
    }

    if((last_event & I2C_STS1_ARLOST) != 0)
    {
    	log_info("Master detect Arbitration Lost Error\r\n"); //Arbitration Lost Error
    }

    if((last_event & I2C_STS1_ACKFAIL) != 0)
    {
    	log_info("Master detect ACK Fail Error\r\n"); 		//ACK Fail Error
    }

    if((last_event & I2C_STS1_OVERRUN) != 0)
    {
    	log_info("Master detect Overrun/Underrun Error\r\n"); //Overrun/Underrun Error
    }

    if((last_event & I2C_STS1_PECERR) != 0)
    {
    	log_info("Master detect PEC Error\r\n"); 				//PEC Error
    }

    if((last_event & I2C_STS1_TIMOUT) != 0)
    {
    	log_info("Master detect Timeout or Tlow Error\r\n"); //Timeout or Tlow Error
    }

    if((last_event & I2C_STS1_SMBALERT) != 0)
    {
    	log_info("Master detect SMBus Alert \r\n"); 			//SMBus Alert
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
 * @brief memery set a value
 * @param s source
 * @param c value
 * @param count number
 * @return pointer of the memery
 */
void Memset(void* s, uint8_t c, uint32_t count)
{
    char* xs = (char*)s;

    while (count--) // clear 17byte buffer
    {
        *xs++ = c;
    }

    return;
}

void CommTimeOut_CallBack(ErrCode_t errcode)
{
    log_info("...ErrCode:%d\r\n", errcode);
}

/**
 * @}
 */
