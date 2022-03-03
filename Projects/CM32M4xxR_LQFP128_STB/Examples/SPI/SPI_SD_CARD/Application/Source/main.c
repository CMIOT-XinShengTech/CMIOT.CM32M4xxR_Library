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
#include "fatfs.h"
#include "user_diskio.h" /* defines USER_Driver as external */

/** @addtogroup CM32M4xxR_StdPeriph_Examples
 * @{
 */


/** @addtogroup SPI_CRC
 * @{
 */


#define BufferSize	(32)
#define SPICRC

volatile SPI_InitType SPI_InitStructure;
void RCC_Configuration(void);
void GPIO_Configuration(void);

volatile FATFS fs;
volatile FATFS *pfs;
volatile FIL fil;
volatile FRESULT fres;
volatile DWORD fre_clust;
volatile uint32_t totalSpace, freeSpace;
volatile char buffer[100];


volatile char USERPath[4];   /* USER logical drive path */


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
	log_info("This is a SPI_SD_CARD demo-----------------------------------\r\n");
	SysTick_Config(144000000/100);
    /* System clocks configuration ---------------------------------------------*/
    RCC_Configuration();

    /* GPIO configuration ------------------------------------------------------*/
    GPIO_Configuration();

    /* SPI1 configuration ------------------------------------------------------*/
    SPI_InitStructure.DataDirection = SPI_DIR_DOUBLELINE_FULLDUPLEX;
    SPI_InitStructure.SpiMode       = SPI_MODE_MASTER;
    SPI_InitStructure.DataLen       = SPI_DATA_SIZE_8BITS;
    SPI_InitStructure.CLKPOL        = SPI_CLKPOL_LOW;
    SPI_InitStructure.CLKPHA        = SPI_CLKPHA_FIRST_EDGE;
    SPI_InitStructure.NSS           = SPI_NSS_SOFT;
    SPI_InitStructure.BaudRatePres  = SPI_BR_PRESCALER_16;
    SPI_InitStructure.FirstBit      = SPI_FB_MSB;
    SPI_InitStructure.CRCPoly       = 0x0007;
    SPI_Init(SPI1, (SPI_InitType*)&SPI_InitStructure);

    /* Enable SPI1 */
    SPI_Enable(SPI1, ENABLE);


    FATFS_LinkDriver((Diskio_drvTypeDef*)&USER_Driver, (char*)USERPath);

    delay_ms(500);

    if(f_mount((FATFS*)&fs, "", 0) != FR_OK)
    {
    	printf("error %s,line %d\r\n",__FILE__, __LINE__);
    }

    /* Open file to write */
    if(f_open((FIL*)&fil, "first.txt", FA_OPEN_APPEND | FA_READ | FA_WRITE) != FR_OK)
    {
    	printf("error %s,line %d\r\n",__FILE__, __LINE__);
    }

    /* Check freeSpace space */
   	if(f_getfree("", (DWORD*)&fre_clust, (FATFS **)&pfs) != FR_OK)
    {
    	printf("error %s,line %d\r\n",__FILE__, __LINE__);
    }

    totalSpace = (uint32_t)((pfs->n_fatent - 2) * pfs->csize * 0.5);
    freeSpace = (uint32_t)(fre_clust * pfs->csize * 0.5);

    /* free space is less than 1kb */
    if(freeSpace < 1)
    {
    	printf("error %s,line %d\r\n",__FILE__, __LINE__);
    }

    /* Writing text */
    f_puts("XinSheng Tech SD Card I/O Example via SPI\n", (FIL*)&fil);
    f_puts("test!!!\n", (FIL*)&fil);

    /* Close file */
    if(f_close((FIL*)&fil) != FR_OK)
    {
    	printf("error %s,line %d\r\n",__FILE__, __LINE__);
    }

    /* Open file to read */
    if(f_open((FIL*)&fil, "first.txt", FA_READ) != FR_OK)
    {
    	printf("error %s,line %d\r\n",__FILE__, __LINE__);
    }

    while(f_gets((char*)buffer, sizeof(buffer), (FIL*)&fil))
    {
    	/* SWV output */
    	printf("%s", buffer);
    	fflush(stdout);
    }

    /* Close file */
    if(f_close((FIL*)&fil) != FR_OK)
    {
    	printf("error %s,line %d\r\n",__FILE__, __LINE__);
    }

    /* Unmount SDCARD */
    if(f_mount(NULL, "", 1) != FR_OK)
    {
    	printf("error %s,line %d\r\n",__FILE__, __LINE__);
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
    /* GPIOA, GPIOB and SPI1 clock enable */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_SPI1, ENABLE);

    /* SPI2 Periph clock enable */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_SPI2, ENABLE);
}

/**
 * @brief  Configures the different GPIO ports.
 */
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    /* Configure SPI1 pins: SCK, MISO and MOSI ---------------------------------*/
    /* Confugure SCK and MOSI pins as Alternate Function Push Pull */
    GPIO_InitStructure.Pin        = GPIO_PIN_5 | GPIO_PIN_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Confugure MISO pin as Input Floating  */
    GPIO_InitStructure.Pin       = GPIO_PIN_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Confugure NSS pin as Output Push Pull */
    GPIO_InitStructure.Pin       = GPIO_PIN_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/**
 * @}
 */

/**
 * @}
 */
