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
#include "bsp.h"
/** @addtogroup CM32M4xxR_StdPeriph_Examples
 * @{
 */

/** @addtogroup I2C_Master_Int
 * @{
 */

typedef enum
{
    NONE = 0,
    TRANSMIT,
    RECEIVE
} TR_STA;

#define TEST_BUFFER_SIZE  20
#define I2CT_FLAG_TIMEOUT ((uint32_t)0x1000)
#define I2CT_LONG_TIMEOUT ((uint32_t)(10 * I2CT_FLAG_TIMEOUT))
#define I2C_MASTER_ADDR   0x30
#define I2C_SLAVE_ADDR    0xA0
volatile Status test_status = FAILED;

static uint8_t master_tx_buf[TEST_BUFFER_SIZE] = {0};
static uint8_t master_rx_buf[TEST_BUFFER_SIZE] = {0};
static uint8_t slave_tx_buf[TEST_BUFFER_SIZE] = {0};
static uint8_t slave_rx_buf[TEST_BUFFER_SIZE] = {0};

static volatile uint8_t flag_master_complete = 0;
static TR_STA flag_master_dir = TRANSMIT;
static volatile uint8_t flag_slave_complete = 0;
static uint8_t rx_num = 0;
static uint8_t tx_num = 0;

/* to record and watch the interrupt flag when interrupt happens */
static uint32_t MasterFlagRec[100];
static uint32_t SlaveFlagRec[100];
static uint8_t MasterRecCnt = 0;
static uint8_t SlaveRecCnt = 0;

Status Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);

/**
 * @brief  system delay function
 * @param 
 */
void Delay(uint32_t nCount)
{
    while (nCount--)
    {
        uint32_t tcnt = 108000;
        while (tcnt--){;}
    }
}

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

	if(ch == 3)
	{
		/* Enable the IIC2 event Interrupt */
		ECLIC_SetLevelIRQ(I2C3_EV_IRQn, 4);
		ECLIC_SetPriorityIRQ(I2C3_EV_IRQn, 1);
		ECLIC_SetTrigIRQ(I2C3_EV_IRQn, ECLIC_LEVEL_TRIGGER);
		ECLIC_EnableIRQ(I2C3_EV_IRQn);

		/* Enable the IIC2 error Interrupt */
		ECLIC_SetLevelIRQ(I2C3_ER_IRQn, 3);
		ECLIC_SetPriorityIRQ(I2C3_ER_IRQn, 1);
		ECLIC_SetTrigIRQ(I2C3_ER_IRQn, ECLIC_LEVEL_TRIGGER);
		ECLIC_EnableIRQ(I2C3_ER_IRQn);
	}

	if(ch == 4)
	{
		/* Enable the IIC2 event Interrupt */
		ECLIC_SetLevelIRQ(I2C4_EV_IRQn, 4);
		ECLIC_SetPriorityIRQ(I2C4_EV_IRQn, 1);
		ECLIC_SetTrigIRQ(I2C4_EV_IRQn, ECLIC_LEVEL_TRIGGER);
		ECLIC_EnableIRQ(I2C4_EV_IRQn);

		/* Enable the IIC2 error Interrupt */
		ECLIC_SetLevelIRQ(I2C4_ER_IRQn, 3);
		ECLIC_SetPriorityIRQ(I2C4_ER_IRQn, 1);
		ECLIC_SetTrigIRQ(I2C4_ER_IRQn, ECLIC_LEVEL_TRIGGER);
		ECLIC_EnableIRQ(I2C4_ER_IRQn);
	}
}
/**
 * @brief  i2c Interrupt service function
 *
 */
void I2C4_EV_IRQHandler(void)
{
	uint32_t last_event;
	uint8_t MatchFlg = 0;

    last_event = I2C_GetLastEvent(I2C4);
    MasterFlagRec[MasterRecCnt++] = last_event;
    if((last_event & I2C_ROLE_MASTER) == I2C_ROLE_MASTER)
    {
    	if((last_event & I2C_STS1_STARTBF) != 0)
    	{
            if (flag_master_dir == TRANSMIT)    // write
            {
                I2C_SendAddr7bit(I2C4, I2C_SLAVE_ADDR, I2C_DIRECTION_SEND);
                tx_num = 0;
                rx_num = 0;
            }
            else if (flag_master_dir == RECEIVE) // read
            {
                I2C_SendAddr7bit(I2C4, I2C_SLAVE_ADDR, I2C_DIRECTION_RECV);
                tx_num = 0;
                rx_num = 0;
            }
            MatchFlg = 1;
    	}

    	if((last_event & I2C_STS1_ADDRF) != 0)  												//The Address send finished and send the first byte
    	{
    		MatchFlg = 1;
    	}

    	if(((last_event & I2C_STS1_TXDATE) != 0) && (flag_master_dir == TRANSMIT))				//keep send bytes
    	{
    		if (tx_num < TEST_BUFFER_SIZE)
			{
				I2C_SendData(I2C4, master_tx_buf[tx_num++]);	//Send bytes
				if((I2C_GetLastEvent(I2C4) & I2C_STS1_TXDATE) != 0)
				{
					I2C_SendData(I2C4, master_tx_buf[tx_num++]);	//Send bytes
				}
			}
			else // data send finish
			{
				I2C_ConfigInt(I2C4, I2C_INT_BUF, DISABLE);
				I2C_GenerateStop(I2C4, ENABLE);					//Send StopF
				flag_master_complete = 1;
			}
    		MatchFlg = 1;
    	}

    	if(((last_event & I2C_STS1_RXDATNE) != 0) && (flag_master_dir == RECEIVE))  			//Master Receive byte
    	{
            master_rx_buf[rx_num++] = I2C_RecvData(I2C4);
    		if (rx_num == TEST_BUFFER_SIZE)
    		{
    			I2C_ConfigInt(I2C4, I2C_INT_BUF, DISABLE);
    			flag_master_complete = 1;
    		}
            // before the last data,should config NACK and STOP
            if (rx_num == (TEST_BUFFER_SIZE - 1))
            {
                I2C_ConfigAck(I2C4, DISABLE);   // Disable I2C4 acknowledgement.
                I2C_GenerateStop(I2C4, ENABLE); // Send I2C4 STOP Condition.
            }
            MatchFlg = 1;
    	}

    	if(MatchFlg == 0)																	//unknown state
    	{
    		I2C_GenerateStop(I2C4, ENABLE);
    	}
    }
    else if(((last_event & I2C_STS1_RXDATNE) != 0) && (flag_master_dir == RECEIVE))			//IIC state may switch to Slave mode before receive the last byte
    {
    	master_rx_buf[rx_num++] = I2C_RecvData(I2C4);
		if (rx_num == TEST_BUFFER_SIZE)
		{
			flag_master_complete = 1;
		}
    }

}

void I2C4_ER_IRQHandler(void)
{
    uint32_t last_event;
    last_event = I2C_GetLastEvent(I2C4);
    I2C_ClrIntPendingBit(I2C4, I2C_INT_SMBALERT|I2C_INT_TIMOUT|I2C_INT_PECERR|I2C_INT_OVERRUN|I2C_INT_ACKFAIL|I2C_INT_ARLOST|I2C_INT_BUSERR);

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
    	printf("Master detect ACK Fail Error\r\n"); 		//ACK Fail Error
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

void I2C2_EV_IRQHandler(void)
{
	uint32_t last_event;
	uint8_t MatchFlg = 0;

    last_event = I2C_GetLastEvent(I2C2);
    SlaveFlagRec[SlaveRecCnt++] = last_event;
    if((last_event & I2C_STS2_MSMODE) != I2C_STS2_MSMODE)		//Slave Mode
    {
    	if((last_event & I2C_STS1_ADDRF) != 0)
    	{
    		MatchFlg = 1;

    	}

    	if((last_event & I2C_STS1_TXDATE) != 0)
		{
            if (tx_num == TEST_BUFFER_SIZE)
            {
                I2C_ConfigInt(I2C2, I2C_INT_BUF, DISABLE);
                flag_slave_complete = 1;
            }
            else
            {
                I2C2->DAT = slave_tx_buf[tx_num++];
            }
            MatchFlg = 1;
		}

    	if((last_event & I2C_STS1_RXDATNE) != 0)
		{
            slave_rx_buf[rx_num++] = I2C2->DAT;
            if (rx_num == TEST_BUFFER_SIZE)
            {
            	I2C_ConfigInt(I2C2, I2C_INT_BUF, DISABLE);
                flag_slave_complete = 1;
            }
            MatchFlg = 1;
		}

    	if((last_event & I2C_STS1_STOPF) != 0)
		{
			I2C_Enable(I2C2, ENABLE);	// clear STOPF bit
			MatchFlg = 1;
		}

    	if(MatchFlg == 0)
		{
			I2C_Enable(I2C2, ENABLE);	//unknown state
		}
    }

}

void I2C2_ER_IRQHandler(void)
{
    uint32_t last_event;
    last_event = I2C_GetLastEvent(I2C2);
    I2C_ClrIntPendingBit(I2C2, I2C_INT_SMBALERT|I2C_INT_TIMOUT|I2C_INT_PECERR|I2C_INT_OVERRUN|I2C_INT_ACKFAIL|I2C_INT_ARLOST|I2C_INT_BUSERR);

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
        if(flag_slave_complete == 1)  //slave send the last data and recv NACK
        {
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

/**
 * @brief  i2c master init
 * @return 0:init finish
 *
 */
int i2c_master_init(void)
{
    I2C_InitType i2c4_master;
    GPIO_InitType i2c4_gpio;

    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_I2C4, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
    GPIO_ConfigPinRemap(GPIO_RMP3_I2C4, ENABLE);

    /*PB6 -- SCL; PB7 -- SDA*/
    i2c4_gpio.Pin               = GPIO_PIN_9;
    i2c4_gpio.GPIO_Mode         = GPIO_Mode_AF_OD;
    i2c4_gpio.GPIO_Speed        = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &i2c4_gpio);

    i2c4_gpio.Pin               = GPIO_PIN_10;
    i2c4_gpio.GPIO_Mode         = GPIO_Mode_AF_OD;
    i2c4_gpio.GPIO_Speed        = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &i2c4_gpio);

    I2C_DeInit(I2C4);
    i2c4_master.BusMode     = I2C_BUSMODE_I2C;
    i2c4_master.FmDutyCycle = I2C_FMDUTYCYCLE_2;
    i2c4_master.OwnAddr1    = I2C_MASTER_ADDR;
    i2c4_master.AckEnable   = I2C_ACKEN;
    i2c4_master.AddrMode    = I2C_ADDR_MODE_7BIT;
    i2c4_master.ClkSpeed    = 100000; // 100K

    I2C_Init(I2C4, &i2c4_master);
    // int enable
    I2C_ConfigInt(I2C4, I2C_INT_EVENT | I2C_INT_ERR | I2C_INT_BUF, ENABLE);
    ECLIC_Config(4);
    I2C_Enable(I2C4, ENABLE);
    return 0;
}

/**
 * @brief  i2c slave init
 * @return 0:init finish
 */
int i2c_slave_init(void)
{
    I2C_InitType i2c2_slave;
    GPIO_InitType i2c2_gpio;

    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_I2C2, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOG, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
    GPIO_ConfigPinRemap(GPIO_RMP1_I2C2, ENABLE);

    /*PB10 -- SCL; PB11 -- SDA*/
    i2c2_gpio.Pin               = GPIO_PIN_2;
    i2c2_gpio.GPIO_Mode         = GPIO_Mode_AF_OD;
    i2c2_gpio.GPIO_Speed        = GPIO_Speed_2MHz;
    GPIO_Init(GPIOG, &i2c2_gpio);

    i2c2_gpio.Pin               = GPIO_PIN_3;
    i2c2_gpio.GPIO_Mode         = GPIO_Mode_AF_OD;
    i2c2_gpio.GPIO_Speed        = GPIO_Speed_2MHz;
    GPIO_Init(GPIOG, &i2c2_gpio);
    
    I2C_DeInit(I2C2);
    i2c2_slave.BusMode     = I2C_BUSMODE_I2C;
    i2c2_slave.FmDutyCycle = I2C_FMDUTYCYCLE_2;
    i2c2_slave.OwnAddr1    = I2C_SLAVE_ADDR;
    i2c2_slave.AckEnable   = I2C_ACKEN;
    i2c2_slave.AddrMode    = I2C_ADDR_MODE_7BIT;
    i2c2_slave.ClkSpeed    = 100000;

    I2C_Init(I2C2, &i2c2_slave);
    // int enable
    I2C_ConfigInt(I2C2, I2C_INT_EVENT | I2C_INT_ERR | I2C_INT_BUF, ENABLE);
    ECLIC_Config(2);
    I2C_Enable(I2C2, ENABLE);
    return 0;
}

/**
 * @brief   Main program
 */
int main(void)
{
    uint16_t i = 0;

    log_init();
    log_info("this is a i2c master slave int demo\r\n");

    i2c_master_init();
    i2c_slave_init();
    __enable_irq();
    
    /* Fill the buffer to send */
    for (i = 0; i < TEST_BUFFER_SIZE; i++)
    {
        master_tx_buf[i] = i;
    }
    
    log_info("I2C4 Master write data to I2C2 Slave...\r\n");
    log_info("I2C4 -->> I2C2\r\n");

    /*Wait until no busy*/
    while (I2C_GetFlag(I2C4, I2C_FLAG_BUSY))
        ;
    
    /* Write data*/
    I2C_GenerateStart(I2C4, ENABLE);
    /* Wait write/Read data complete*/
    while((!flag_master_complete) || (!flag_slave_complete))
        ;
    
    /* Check if the data written to the memory is read correctly */
    test_status = Buffercmp(master_tx_buf, slave_rx_buf, TEST_BUFFER_SIZE);
    if (test_status == PASSED)
    {
        log_info("i2c write data test pass!\r\n");
    }
    else
    {
        log_info("i2c write data test fail!\r\n");
    }

    delay_ms(1);
    log_info("-----------------------------------\r\n");
    /*----------I2C4 Master Read and I2C2 Slave Write data-----------*/
    for (i = 0; i < TEST_BUFFER_SIZE; i++)
    {
        slave_tx_buf[i] = (0x80 + i);
    }
    
    flag_master_complete = 0;
    flag_slave_complete = 0;
    flag_master_dir = RECEIVE;
    
    log_info("I2C4 Master Read Data From I2C2 Slave...\r\n");
    log_info("I2C4 <<-- I2C2\r\n");
    
    /*Wait until no busy*/
    while (I2C_GetFlag(I2C4, I2C_FLAG_BUSY))
        ;
    I2C_ConfigInt(I2C4, I2C_INT_BUF, ENABLE);
    I2C_ConfigInt(I2C2, I2C_INT_BUF, ENABLE);
    I2C_GenerateStop(I2C4, DISABLE);
    I2C_GenerateStart(I2C4, ENABLE);
    /* Wait write/Read data complete*/
    while((!flag_master_complete) || (!flag_slave_complete))
        ;

    /* Check if the data written to the memory is read correctly */
    test_status = Buffercmp(master_rx_buf, slave_tx_buf, TEST_BUFFER_SIZE);
    if (test_status == PASSED) /* test_status = PASSED, if the write and read dataare the same  */
    {
        log_info("i2c read data test pass!\r\n");
    }
    else /* test_status = FAILED, if the write and read data are different */
    {
        log_info("i2c read data test fail!\r\n");
    }

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
