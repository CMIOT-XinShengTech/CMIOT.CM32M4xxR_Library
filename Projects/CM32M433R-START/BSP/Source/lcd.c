
#include "nuclei_sdk_soc.h"
#include "lcd.h"

//RST(IO) PB5
//SDI     PA1
//SCLK    PC3
//CS      PC2
//D/CK    PF12
//A+(IO)  PE14

extern const unsigned char asc2_1206[95][12];   //12*12 ASCII
extern const unsigned char asc2_1608[95][16];   //16*16 ASCII
extern const unsigned char asc2_2412[95][48];   //24*24 ASCII
extern const unsigned char asc2_3216[95][64];   //32*32 ASCII



void WriteComm(uint8_t data)
{
	LCD_DCK_CMD;
	//delay_ms(1);
	while (SPI_I2S_GetStatus(SPI3, SPI_I2S_TE_FLAG) == RESET)
	;
	SPI_I2S_TransmitData(SPI3, data);
}

void WriteData(uint8_t data)
{
	LCD_DCK_DATA;
	//delay_ms(1);
	while (SPI_I2S_GetStatus(SPI3, SPI_I2S_TE_FLAG) == RESET)
	;
	SPI_I2S_TransmitData(SPI3, data);
}

void LCD_Init(void)
{
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA | \
    		                RCC_APB2_PERIPH_GPIOB | \
							RCC_APB2_PERIPH_GPIOC | \
							RCC_APB2_PERIPH_GPIOE | \
							RCC_APB2_PERIPH_GPIOF | \
							RCC_APB2_PERIPH_AFIO, ENABLE);
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_SPI3, ENABLE);

    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_DMA2, ENABLE);

    GPIO_ConfigPinRemap(GPIO_RMP3_SPI3, ENABLE);

    GPIO_InitType GPIO_InitStructure;
    GPIO_InitStructure.Pin        = LCD_SDI_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_Init(LCD_SDI_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.Pin        = LCD_SCLK_PIN;
    GPIO_Init(LCD_SCLK_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.Pin       = LCD_RST_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(LCD_RST_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.Pin       = LCD_CS_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(LCD_CS_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.Pin       = LCD_DCK_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(LCD_DCK_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.Pin       = LCD_A_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(LCD_A_GPIO, &GPIO_InitStructure);

    LCD_CS_H;

    SPI_InitType SPI_InitStructure;
    SPI_InitStructure.DataDirection = SPI_DIR_DOUBLELINE_FULLDUPLEX;
    SPI_InitStructure.SpiMode       = SPI_MODE_MASTER;
    SPI_InitStructure.DataLen       = SPI_DATA_SIZE_8BITS;
    SPI_InitStructure.CLKPOL        = SPI_CLKPOL_LOW;
    SPI_InitStructure.CLKPHA        = SPI_CLKPHA_FIRST_EDGE;
    SPI_InitStructure.NSS           = SPI_NSS_SOFT;
    SPI_InitStructure.BaudRatePres  = SPI_BR_PRESCALER_2;
    SPI_InitStructure.FirstBit      = SPI_FB_MSB;
    SPI_InitStructure.CRCPoly       = 0x0007;
    SPI_Init(SPI3, (SPI_InitType*)&SPI_InitStructure);

    /* Enable SPI1 */
    SPI_Enable(SPI3, ENABLE);


	//CS0=0;
    LCD_A_L;
	delay_ms(200);

    LCD_RST_H;
	delay_ms(200);

	LCD_RST_L;
	delay_ms(800);

	LCD_RST_H;
	delay_ms(800);

    LCD_CS_L;
	delay_ms(200);
//-------------------------------------//
	WriteComm(0x11);
	delay_ms(800);  //Delay 120ms

	//---------------display and color format setting--------------//
	WriteComm(0x36);
	WriteData(0xC0);
	delay_ms(20);

	WriteComm(0x3a);
	WriteData(0x65);
	delay_ms(20);

	//---------------ST7789V Frame rate setting---------------//
	WriteComm(0xb2);
	WriteData(0x0c);
	WriteData(0x0c);
	WriteData(0x00);
	WriteData(0x33);
	WriteData(0x33);
	delay_ms(20);

	WriteComm(0xb7);
	WriteData(0x35);
	delay_ms(20);

	//---------------ST7789V Power setting---------------//
	WriteComm(0xbb);
	WriteData(0x35);
	delay_ms(20);

	WriteComm(0xc0);
	WriteData(0x2c);
	delay_ms(20);

	WriteComm(0xc2);
	WriteData(0x01);
	delay_ms(20);

	WriteComm(0xc3);
	WriteData(0x0b);
	delay_ms(20);

	WriteComm(0xc4);
	WriteData(0x20);
	delay_ms(20);

	WriteComm(0xc6);
	WriteData(0x0f);
	delay_ms(20);

	WriteComm(0xd0);
	WriteData(0xa4);
	WriteData(0xa1);
	delay_ms(20);

	//---------------ST7789V gamma setting---------------//
	WriteComm(0xe0);
	WriteData(0xd0);
	WriteData(0x00);
	WriteData(0x02);
	WriteData(0x07);
	WriteData(0x0b);
	WriteData(0x1a);
	WriteData(0x31);
	WriteData(0x54);
	WriteData(0x40);
	WriteData(0x29);
	WriteData(0x12);
	WriteData(0x12);
	WriteData(0x12);
	WriteData(0x17);
	delay_ms(20);

	WriteComm(0xe1);
	WriteData(0xd0);
	WriteData(0x00);
	WriteData(0x02);
	WriteData(0x07);
	WriteData(0x05);
	WriteData(0x25);
	WriteData(0x2d);
	WriteData(0x44);
	WriteData(0x45);
	WriteData(0x1c);
	WriteData(0x18);
	WriteData(0x16);
	WriteData(0x1c);
	WriteData(0x1d);
	delay_ms(20);

//	WriteComm(0x29);
	delay_ms(20);

}

void BlockWrite(unsigned int Xstart,unsigned int Xend,unsigned int Ystart,unsigned int Yend, uint16_t color)
{
	//ILI9163C

	WriteComm(0x2A);
    WriteData(Xstart>>8);
	WriteData(Xstart);
	WriteData(Xend>>8);
	WriteData(Xend);
	delay_us(1);
	delay_ms(1);

	WriteComm(0x2B);
	WriteData(Ystart>>8);
	WriteData(Ystart);
	WriteData(Yend>>8);
	WriteData(Yend);
	delay_us(1);
	delay_ms(1);

	WriteComm(0x3A);    // 16/18 bits
    WriteData(0x05);
	delay_us(1);
	delay_ms(1);

	WriteComm(0x2c);
	delay_us(1);
	delay_ms(1);

	uint32_t i,j;
	uint32_t w = Xend - Xstart;
	uint32_t h = Yend - Ystart;


    for (i = 0; i < h*w; i++)
    {
        //for (j = 0; j < w; j++)
        {
        	WriteData((uint8_t)(color >> 8));
        	WriteData((uint8_t)color);
        	//delay_ms(1);
        }
    }
	delay_us(1);
	delay_ms(1);


	WriteComm(0x29);
	delay_us(1);
	delay_ms(1);
}


void PirctureWrite(unsigned int Xstart,unsigned int Xend,unsigned int Ystart,unsigned int Yend, uint16_t* data)
{
	//ILI9163C
	DMA_InitType DMA_InitStructure;

	WriteComm(0x2A);
    WriteData(Xstart>>8);
	WriteData(Xstart);
	WriteData(Xend>>8);
	WriteData(Xend);
	delay_us(1);
	delay_ms(1);

	WriteComm(0x2B);
	WriteData(Ystart>>8);
	WriteData(Ystart);
	WriteData(Yend>>8);
	WriteData(Yend);
	delay_us(1);
	delay_ms(1);

	WriteComm(0x3A);    // 16/18 bits
    WriteData(0x05);
	delay_us(1);
	delay_ms(1);

	WriteComm(0x2c);
	delay_us(1);
	delay_ms(1);

	uint32_t i,j;
	uint32_t len = (Xend - Xstart) * (Yend - Ystart);
	LCD_DCK_DATA;
	//delay_ms(1);
#if 0
	while(i < len)
	{
		while (SPI_I2S_GetStatus(SPI3, SPI_I2S_TE_FLAG) == RESET)
		;
		SPI_I2S_TransmitData(SPI3, (uint8_t)(data[i]>>8));
		while (SPI_I2S_GetStatus(SPI3, SPI_I2S_TE_FLAG) == RESET)
		;
		SPI_I2S_TransmitData(SPI3, (uint8_t)(data[i++]));
	}

	delay_us(1);
	delay_ms(1);
#else
	len = len * 2;
	uint32_t len_trans  = 0;
	uint8_t* data_p  = (uint8_t*)data;

    SPI_Enable(SPI3, DISABLE);
    SPI_I2S_EnableDma(SPI3, SPI_I2S_DMA_TX, ENABLE);
    SPI_Enable(SPI3, ENABLE);
	while(1)
	{
		if (((uint32_t)data + len - (uint32_t)data_p) >= 65535)
		{
			len_trans = 65535;
		}
		else
		{
			len_trans = (uint32_t)data + len - (uint32_t)data_p;
		}
		DMA_DeInit(DMA2_CH2);
	    DMA_InitStructure.PeriphAddr     = (uint32_t)(SPI3_BASE + 0x0C);
	    DMA_InitStructure.Direction      = DMA_DIR_PERIPH_DST;
	    DMA_InitStructure.PeriphInc      = DMA_PERIPH_INC_DISABLE;
	    DMA_InitStructure.DMA_MemoryInc  = DMA_MEM_INC_ENABLE;
	    DMA_InitStructure.PeriphDataSize = DMA_PERIPH_DATA_SIZE_BYTE;
	    DMA_InitStructure.MemDataSize    = DMA_MEMORY_DATA_SIZE_BYTE;
	    DMA_InitStructure.CircularMode   = DMA_MODE_NORMAL;
	    DMA_InitStructure.Priority       = DMA_PRIORITY_VERY_HIGH;
	    DMA_InitStructure.Mem2Mem        = DMA_M2M_DISABLE;
    	DMA_InitStructure.MemAddr        = (uint32_t)data_p;
    	DMA_InitStructure.BufSize        = len_trans;
    	DMA_Init(DMA2_CH2, &DMA_InitStructure);
    	DMA_EnableChannel(DMA2_CH2, ENABLE);

    	while (!DMA_GetFlagStatus(DMA2_FLAG_TC2, DMA2))
    		;
    	data_p = data_p + len_trans;
    	if (((uint32_t)data + len) == (uint32_t)data_p)
    	{
    		break;
    	}
	}
    SPI_Enable(SPI3, DISABLE);
    SPI_I2S_EnableDma(SPI3, SPI_I2S_DMA_TX, DISABLE);
    SPI_Enable(SPI3, ENABLE);
#endif

	WriteComm(0x29);
	delay_us(1);
	delay_ms(1);
}



//*******************************************************************/
//Function: Set address in LCD
//*******************************************************************/
void LCD_Address_Set(uint16_t Xstart, uint16_t Xend, uint16_t Ystart, uint16_t Yend)
{
	WriteComm(0x2A);
    WriteData(Xstart >> 8);
    WriteData(Xstart);
    WriteData(Xend >> 8);
    WriteData(Xend);
	delay_ms(20);

	WriteComm(0x2B);
    WriteData(Ystart >> 8);
    WriteData(Ystart);
    WriteData(Yend >> 8);
    WriteData(Yend);
	delay_ms(20);

	WriteComm(0x3A);    // 16/18 bits
    WriteData(0x65);
	delay_ms(20);

	WriteComm(0x2C);
}

//*******************************************************************/
//Function: DrawPoint in LCD
//*******************************************************************/
void LCD_DrawPoint(uint16_t color)
{
    WriteData(color >> 8);
    WriteData(color);
}

/*******************************************************************************/
//Function: Show char in LCD
/*******************************************************************************/
void LCD_ShowChar(uint16_t x, uint16_t y, uint8_t num, uint8_t size, uint16_t color, uint16_t back_color)
{
    uint8_t temp,i,j,t;
    uint8_t csize;

	if((x > (240 - size / 2)) || (y > (320 - size)))
		 return;

	num=num-' ';
    LCD_Address_Set(x, x + size/2 - 1, y, y + size - 1);

    if(size==24) csize= 48;
    else         csize= (size/8+((size%8)?1:0))*(size/2);

    for(i=0;i<csize;i++)
    {
        if(size==12)
        {
        	temp=asc2_1206[num][i];
            for(j=0;j<6;j++)
            {
                if(temp&0x80) LCD_DrawPoint(color);
                else          LCD_DrawPoint(back_color);

                temp<<=1;
            }
        }
        else if(size==16)
        {
        	temp=asc2_1608[num][i];
            for(j=0;j<8;j++)
            {
                if(temp&0x80) LCD_DrawPoint(color);
                else          LCD_DrawPoint(back_color);

                temp<<=1;
            }
        }
        else if(size==24)
        {
        	temp=asc2_2412[num][i];
			if(i % 2 == 0) t = 8;
			else t = 4;
            for(j=0;j<t;j++)
            {
                if(temp&0x80) LCD_DrawPoint(color);
                else          LCD_DrawPoint(back_color);

                temp<<=1;
            }
        }

        else if(size==32)
        {
        	temp=asc2_3216[num][i];
            for(j=0;j<8;j++)
            {
                if(temp&0x80) LCD_DrawPoint(color);
                else          LCD_DrawPoint(back_color);

                temp<<=1;
            }
        }
        else return;


    }
}


/*******************************************************************************/
//Function: Show string in LCD
/*******************************************************************************/
void LCD_ShowString(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t size, uint16_t color, uint16_t back_color, uint8_t *p)
{
    uint8_t x0=x;
    width+=x;
    height+=y;

    if((size!=12) & (size!=16) & (size!=24) & (size!=32)) return;

    while((*p<='~')&&(*p>=' '))
    {
        if(x>=width)  {x=x0;y+=size;}
        if(y>=height) break;

        LCD_ShowChar(x,y,*p,size,color,back_color);
        x+=size/2;
        p++;
    }
}
