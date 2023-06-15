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
#include "lcd.h"

/** @addtogroup CM32M4xxR_StdPeriph_Examples
 * @{
 */


/** @addtogroup SPI_CRC
 * @{
 */


#define BufferSize	(32)
#define SPICRC

volatile uint32_t totalSpace, freeSpace;
volatile char buffer[100];

volatile char USERPath[4];   /* USER logical drive path */
extern const uint16_t pic_logo_data[20000];
extern const uint16_t pic_pic1_data[76800];
extern const uint16_t pic_pic2_data[76800];


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
	log_info("This is a LCD demo-----------------------------------\r\n");

	LCD_Init();
    while (1)
    {

    	BlockWrite(0,240,0,320,0x0000);
    	delay_ms(1000);
    	BlockWrite(0,240,0,320,0xF000);
    	delay_ms(1000);
    	PirctureWrite(0,240,0,320,(uint16_t*)pic_pic1_data);
    	delay_ms(1000);
    	PirctureWrite(0,240,0,320,(uint16_t*)pic_pic2_data);
    	delay_ms(1000);
    	//BlockWrite(0,240,0,320,0xFFFF);
    	//delay_ms(1000);
    	//BlockWrite(0,240,0,320,0x0000);
    	//delay_ms(1000);
    	PirctureWrite(40,240,100,200,(uint16_t*)pic_logo_data);
    	delay_ms(1000);


    	BlockWrite(0, 240, 0, 320, WHITE);

        LCD_ShowString(0, 0,  240, 320,      12, BLACK, YELLOW, "Hello World!!!!");
        LCD_ShowString(0, 12, 240, (320-12), 16, GREEN, BLACK,  "Hello World!!!!");
        LCD_ShowString(0, 28, 240, (320-28), 24, BLUE,  BROWN,  "Hello World!!!!");
        LCD_ShowString(0, 52, 240, (320-52), 32, WHITE, RED,    "Hello World!!!!");

        delay_ms(1000);

    }
}

/**
 * @}
 */

/**
 * @}
 */
