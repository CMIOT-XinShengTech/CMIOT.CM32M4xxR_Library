#include "nuclei_sdk_soc.h"
#include "log.h"


#define TEST_BUFFER_SIZE  	(10)
#define I2CT_FLAG_TIMEOUT 	((uint32_t) 0x1000)
#define I2CT_LONG_TIMEOUT 	((uint32_t) (10 * I2C_FLAG_TIMOUT))
#define I2C_MASTER_ADDR   	(0x30)

#define I2Cx				I2C3
#define I2Cx_SCL_PIN		GPIO_PIN_4
#define I2Cx_SDA_PIN		GPIO_PIN_5
#define GPIOx        		GPIOF

static __IO uint32_t I2CTimeout = I2CT_LONG_TIMEOUT;

int i2c_master_init(void)
{
    I2C_InitType i2c_master;
    GPIO_InitType i2c_gpio;

    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_I2C3, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOF, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
    GPIO_ConfigPinRemap(GPIO_RMP2_I2C3, ENABLE);

    /* PB6/PB8 -- SCL; PB7/PB9 -- SDA */
    i2c_gpio.Pin        = I2Cx_SCL_PIN | I2Cx_SDA_PIN;
    i2c_gpio.GPIO_Speed = GPIO_Speed_50MHz;
    i2c_gpio.GPIO_Mode  = GPIO_Mode_AF_OD;
    GPIO_Init(GPIOx, &i2c_gpio);

    I2C_DeInit(I2Cx);
    i2c_master.BusMode     = I2C_BUSMODE_I2C;
    i2c_master.FmDutyCycle = I2C_FMDUTYCYCLE_2;
    i2c_master.OwnAddr1    = I2C_MASTER_ADDR;
    i2c_master.AckEnable   = I2C_ACKEN;
    i2c_master.AddrMode    = I2C_ADDR_MODE_7BIT;
    i2c_master.ClkSpeed    = 100000; /* Speed = 100K */

    I2C_Init(I2Cx, &i2c_master);
    I2C_Enable(I2Cx, ENABLE);
    I2C_ConfigAck(I2Cx, ENABLE);

    return 0;
}

int32_t i2c_master_send(uint8_t addr, uint8_t *data, uint32_t date_len)
{
	uint32_t len = date_len;
    uint8_t* sendBufferPtr = data;
    I2CTimeout             = I2CT_LONG_TIMEOUT;

    while (I2C_GetFlag(I2Cx, I2C_FLAG_BUSY))
    {
        if ((I2CTimeout--) == 0)
            return -4;
    };

    I2C_GenerateStart(I2Cx, ENABLE);

    I2CTimeout = I2C_FLAG_TIMOUT;
    while (!I2C_CheckEvent(I2Cx, I2C_EVT_MASTER_MODE_FLAG)) /* EV5 */
    {
        if ((I2CTimeout--) == 0)
            return -5;
    };

    I2C_SendAddr7bit(I2Cx, addr, I2C_DIRECTION_SEND);

    I2CTimeout = I2C_FLAG_TIMOUT;
    while (!I2C_CheckEvent(I2Cx, I2C_EVT_MASTER_TXMODE_FLAG)) /* EV6 */
    {
        if ((I2CTimeout--) == 0)
            return -6;
    };

    /* Send data */
    while (len-- > 0)
    {
        I2C_SendData(I2Cx, *sendBufferPtr++);

        I2CTimeout = I2C_FLAG_TIMOUT;
        while (!I2C_CheckEvent(I2Cx, I2C_EVT_MASTER_DATA_SENDING)) /* EV8 */
        {
            if ((I2CTimeout--) == 0)
                return -7;
        };
    };

    I2CTimeout = I2C_FLAG_TIMOUT;
    while (!I2C_CheckEvent(I2Cx, I2C_EVT_MASTER_DATA_SENDED)) /* EV8-2 */
    {
        if ((I2CTimeout--) == 0)
            return -8;
    };

    I2C_GenerateStop(I2Cx, ENABLE);

    return date_len;
}

int32_t i2c_master_recv(uint8_t addr, uint8_t *data, uint32_t date_len)
{
	uint32_t len = date_len;
    uint8_t* recvBufferPtr = data;
    I2CTimeout             = I2CT_LONG_TIMEOUT;

    while (I2C_GetFlag(I2Cx, I2C_FLAG_BUSY))
    {
        if ((I2CTimeout--) == 0)
            return -9;
    };

    I2C_ConfigAck(I2Cx, ENABLE);

    /* Send start */
    I2C_GenerateStart(I2Cx, ENABLE);

    I2CTimeout = I2C_FLAG_TIMOUT;
    while (!I2C_CheckEvent(I2Cx, I2C_EVT_MASTER_MODE_FLAG)) /* EV5 */
    {
        if ((I2CTimeout--) == 0)
            return -10;
    };

    /* Send address */
    I2C_SendAddr7bit(I2Cx, addr, I2C_DIRECTION_RECV);

    I2CTimeout = I2C_FLAG_TIMOUT;
    while (!I2C_CheckEvent(I2Cx, I2C_EVT_MASTER_RXMODE_FLAG)) /* EV6 */
    {
        if ((I2CTimeout--) == 0)
            return -6;
    };

    /* Receive data */
    while (len-- > 0)
    {
        I2CTimeout = I2CT_LONG_TIMEOUT;
        while (!I2C_CheckEvent(I2Cx, I2C_EVT_MASTER_DATA_RECVD_FLAG)) /* EV7 */
        {
            if ((I2CTimeout--) == 0)
                return -14;
        };

		if (len == 1)
        {
           I2C_ConfigAck(I2Cx, DISABLE);
           I2C_GenerateStop(I2Cx, ENABLE);
        }

        *recvBufferPtr++ = I2C_RecvData(I2Cx);
    };

    return date_len;
}

int32_t i2c_master_send_recv(uint8_t addr, uint8_t *data_write, uint32_t date_len_write, uint8_t *data_read, uint32_t date_len_read)
{
	uint32_t len = date_len_write;
	uint8_t* sendBufferPtr = data_write;
	I2CTimeout             = I2CT_LONG_TIMEOUT;

	while (I2C_GetFlag(I2Cx, I2C_FLAG_BUSY))
	{
	    if ((I2CTimeout--) == 0)
	        return -4;
	};

	I2C_GenerateStart(I2Cx, ENABLE);

	I2CTimeout = I2C_FLAG_TIMOUT;
	while (!I2C_CheckEvent(I2Cx, I2C_EVT_MASTER_MODE_FLAG)) /* EV5 */
	{
	    if ((I2CTimeout--) == 0)
	        return -5;
	};

	I2C_SendAddr7bit(I2Cx, addr, I2C_DIRECTION_SEND);

	I2CTimeout = I2C_FLAG_TIMOUT;
	while (!I2C_CheckEvent(I2Cx, I2C_EVT_MASTER_TXMODE_FLAG)) /* EV6 */
	{
	    if ((I2CTimeout--) == 0)
	        return -6;
	};

	/* Send data */
	while (len-- > 0)
	{
	    I2C_SendData(I2Cx, *sendBufferPtr++);

	    I2CTimeout = I2C_FLAG_TIMOUT;
	    while (!I2C_CheckEvent(I2Cx, I2C_EVT_MASTER_DATA_SENDING)) /* EV8 */
	    {
	        if ((I2CTimeout--) == 0)
	            return -7;
	    };
	};

	I2CTimeout = I2C_FLAG_TIMOUT;
	while (!I2C_CheckEvent(I2Cx, I2C_EVT_MASTER_DATA_SENDED)) /* EV8-2 */
	{
	    if ((I2CTimeout--) == 0)
	        return -8;
	};

	len = date_len_read;
	uint8_t* recvBufferPtr = data_read;
	I2CTimeout             = I2CT_LONG_TIMEOUT;

	/* Send start */
	I2C_GenerateStart(I2Cx, ENABLE);

	I2CTimeout = I2C_FLAG_TIMOUT;
	while (!I2C_CheckEvent(I2Cx, I2C_EVT_MASTER_MODE_FLAG)) /* EV5 */
	{
	    if ((I2CTimeout--) == 0)
	        return -10;
	};

	/* Send address */
	I2C_SendAddr7bit(I2Cx, addr, I2C_DIRECTION_RECV);

	I2CTimeout = I2C_FLAG_TIMOUT;
	while (!I2C_CheckEvent(I2Cx, I2C_EVT_MASTER_RXMODE_FLAG)) /* EV6 */
	{
	    if ((I2CTimeout--) == 0)
	        return -6;
	};

	/* Receive data */
	while (len > 0)
	{
	    I2CTimeout = I2CT_LONG_TIMEOUT;
	    while (!I2C_CheckEvent(I2Cx, I2C_EVT_MASTER_DATA_RECVD_FLAG)) /* EV7 */
	    {
	        if ((I2CTimeout--) == 0)
	            return -14;
	    };

	    if (len == 1)
		{
			I2C_ConfigAck(I2Cx, DISABLE);
			I2C_GenerateStop(I2Cx, ENABLE);
		}

		*recvBufferPtr++ = I2C_RecvData(I2Cx);
		len--;
	};

	return (date_len_write+date_len_read);
}

#define I2S_TX_MASTER       			SPI2
#define I2S_TX_MASTER_GPIO_CK			GPIOE
#define I2S_TX_MASTER_PIN_CK			GPIO_PIN_11
#define I2S_TX_MASTER_GPIO_SD			GPIOE
#define I2S_TX_MASTER_PIN_SD			GPIO_PIN_13
#define I2S_TX_MASTER_GPIO_WS			GPIOE
#define I2S_TX_MASTER_PIN_WS			GPIO_PIN_10
#define I2S_TX_MASTER_GPIO_MCLK		GPIOC
#define I2S_TX_MASTER_PIN_MCLK			GPIO_PIN_6

#define I2S_TX_MASTER_IRQn				SPI2_I2S2_IRQn
#define I2S_TX_MASTER_IRQHandler		SPI2_I2S2_IRQHandler

void i2s_to_dac_init(void)
{
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC | RCC_APB2_PERIPH_GPIOE, ENABLE);

	/* SPI3 and SPI2 clocks enable */
	RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_SPI2, ENABLE);
	GPIO_ConfigPinRemap(GPIO_RMP3_SPI2, ENABLE);

    GPIO_InitType GPIO_InitStructure;

    /* Configure SPI3 pins: CK and SD ------------------------------------*/
    GPIO_InitStructure.Pin       = I2S_TX_MASTER_PIN_CK;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(I2S_TX_MASTER_GPIO_CK, &GPIO_InitStructure);

    GPIO_InitStructure.Pin       = I2S_TX_MASTER_PIN_SD;
    GPIO_Init(I2S_TX_MASTER_GPIO_SD, &GPIO_InitStructure);

    /* Configure SPI3 pins: WS -------------------------------------------*/
    GPIO_InitStructure.Pin = I2S_TX_MASTER_PIN_WS;
    GPIO_Init(I2S_TX_MASTER_GPIO_WS, &GPIO_InitStructure);

    /* Configure SPI3 pins: MCLK -----------------------------------------*/
    GPIO_InitStructure.Pin = I2S_TX_MASTER_PIN_MCLK;
    GPIO_Init(I2S_TX_MASTER_GPIO_MCLK, &GPIO_InitStructure);

    /* Configure the SPI2_I2S2 Interrupt */
	ECLIC_SetLevelIRQ(I2S_TX_MASTER_IRQn, 1);
	ECLIC_SetPriorityIRQ(I2S_TX_MASTER_IRQn, 0);
	ECLIC_SetTrigIRQ(I2S_TX_MASTER_IRQn, ECLIC_LEVEL_TRIGGER);

	ECLIC_EnableIRQ(I2S_TX_MASTER_IRQn);

    SPI_I2S_DeInit(I2S_TX_MASTER);

    I2S_InitType I2S_InitStructure;
    /* I2S peripheral configuration */
    I2S_InitStructure.Standard       = I2S_STD_PHILLIPS;
    I2S_InitStructure.DataFormat     = I2S_DATA_FMT_16BITS;
    I2S_InitStructure.MCLKEnable     = I2S_MCLK_ENABLE;
    I2S_InitStructure.AudioFrequency = I2S_AUDIO_FREQ_22K;
    I2S_InitStructure.CLKPOL         = I2S_CLKPOL_LOW;

    /* I2S3 Master Transmitter to I2S2 Slave Receiver communication -----------*/
    /* I2S3 configuration */
    I2S_InitStructure.I2sMode = I2S_MODE_MASTER_TX;
    I2S_Init(I2S_TX_MASTER, &I2S_InitStructure);

    /* Enable the I2S3 TxE interrupt */
    SPI_I2S_EnableInt(I2S_TX_MASTER, SPI_I2S_INT_TE, ENABLE);

    /* Enable the I2S3 */
    I2S_Enable(I2S_TX_MASTER, ENABLE);

    /* Enable global interrupt */
    __enable_irq();
}


#define I2S_RX_MASTER       			SPI3
#define I2S_RX_MASTER_GPIO_CK			GPIOD
#define I2S_RX_MASTER_PIN_CK			GPIO_PIN_9
#define I2S_RX_MASTER_GPIO_SD			GPIOD
#define I2S_RX_MASTER_PIN_SD			GPIO_PIN_12
#define I2S_RX_MASTER_GPIO_WS			GPIOD
#define I2S_RX_MASTER_PIN_WS			GPIO_PIN_8
#define I2S_RX_MASTER_GPIO_MCLK			GPIOC
#define I2S_RX_MASTER_PIN_MCLK			GPIO_PIN_7

#define I2S_RX_MASTER_IRQn				SPI3_I2S3_IRQn
#define I2S_RX_MASTER_IRQHandler		SPI3_I2S3_IRQHandler

void i2s_to_adc_init(void)
{
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC | RCC_APB2_PERIPH_GPIOD | RCC_APB2_PERIPH_AFIO, ENABLE);

	/* SPI3 and SPI2 clocks enable */
	RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_SPI3, ENABLE);
	GPIO_ConfigPinRemap(GPIO_RMP2_SPI3, ENABLE);

    GPIO_InitType GPIO_InitStructure;

    /* Configure SPI3 pins: CK and SD ------------------------------------*/
    GPIO_InitStructure.Pin       = I2S_RX_MASTER_PIN_CK;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(I2S_RX_MASTER_GPIO_CK, &GPIO_InitStructure);

    GPIO_InitStructure.Pin       = I2S_RX_MASTER_PIN_SD;
    GPIO_Init(I2S_RX_MASTER_GPIO_SD, &GPIO_InitStructure);

    /* Configure SPI3 pins: WS -------------------------------------------*/
    GPIO_InitStructure.Pin = I2S_RX_MASTER_PIN_WS;
    GPIO_Init(I2S_RX_MASTER_GPIO_WS, &GPIO_InitStructure);

    /* Configure SPI3 pins: MCLK -----------------------------------------*/
    GPIO_InitStructure.Pin = I2S_RX_MASTER_PIN_MCLK;
    GPIO_Init(I2S_RX_MASTER_GPIO_MCLK, &GPIO_InitStructure);

    /* Configure the SPI2_I2S2 Interrupt */
	ECLIC_SetLevelIRQ(I2S_RX_MASTER_IRQn, 1);
	ECLIC_SetPriorityIRQ(I2S_RX_MASTER_IRQn, 0);
	ECLIC_SetTrigIRQ(I2S_RX_MASTER_IRQn, ECLIC_LEVEL_TRIGGER);

	ECLIC_EnableIRQ(I2S_RX_MASTER_IRQn);

    SPI_I2S_DeInit(I2S_RX_MASTER);

    I2S_InitType I2S_InitStructure;
    /* I2S peripheral configuration */
    I2S_InitStructure.Standard       = I2S_STD_PHILLIPS;
    I2S_InitStructure.DataFormat     = I2S_DATA_FMT_16BITS;
    I2S_InitStructure.MCLKEnable     = I2S_MCLK_ENABLE;
    I2S_InitStructure.AudioFrequency = I2S_AUDIO_FREQ_22K;
    I2S_InitStructure.CLKPOL         = I2S_CLKPOL_LOW;

    /* I2S3 Master Transmitter to I2S2 Slave Receiver communication -----------*/
    /* I2S3 configuration */
    I2S_InitStructure.I2sMode = I2S_MODE_MASTER_RX;
    I2S_Init(I2S_RX_MASTER, &I2S_InitStructure);

    /* Enable the I2S3 TxE interrupt */
    SPI_I2S_EnableInt(I2S_RX_MASTER, SPI_I2S_INT_RNE, ENABLE);

    /* Enable the I2S3 */
    I2S_Enable(I2S_RX_MASTER, ENABLE);

    /* Enable global interrupt */
    __enable_irq();
}

extern __IO uint32_t TxIdx;
extern const uint16_t I2S_Buffer_Tx[249986];
__IO uint32_t RxIdx = 0;
uint16_t I2S_Buffer_temp_new;
uint16_t I2S_Buffer_temp;
uint16_t I2S_Buffer_Rx[50986];
__IO uint32_t RxIdx__ = 0;

void I2S_TX_MASTER_IRQHandler(void)
{
    /* Check the interrupt source */
    if (SPI_I2S_GetIntStatus(I2S_TX_MASTER, SPI_I2S_INT_TE) == SET)
    {
        /* Send a data from I2S3 */
        SPI_I2S_TransmitData(I2S_TX_MASTER, I2S_Buffer_Tx[TxIdx++]);
    }

    /* Check the end of buffer transfer */
    if (TxIdx == 249986)
    {
    	TxIdx = 0;
    }
}

void I2S_RX_MASTER_IRQHandler(void)
{
    /* Check the interrupt source */
    if (SPI_I2S_GetIntStatus(I2S_RX_MASTER, SPI_I2S_INT_RNE) == SET)
    {
        /* Send a data from I2S3 */
    	I2S_Buffer_temp_new = SPI_I2S_ReceiveData(I2S_RX_MASTER);
    	if ((I2S_RX_MASTER->STS & 0x04) == 0x00)
    	{
    		I2S_Buffer_temp = I2S_Buffer_temp_new;
    	}
    	I2S_Buffer_Rx[RxIdx++] = I2S_Buffer_temp_new;
    	if (RxIdx >= 50986)
    	{
    		RxIdx = 0;
    		if (I2S_Buffer_Rx[2046] == 1)
    		{
    			log_info("0x%04x\r\n",I2S_Buffer_temp_new);
    		}
    	}
    	//log_info("0x%04x\r\n",I2S_Buffer_temp);
    }

}
