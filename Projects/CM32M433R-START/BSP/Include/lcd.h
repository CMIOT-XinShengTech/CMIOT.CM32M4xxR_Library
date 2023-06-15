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
 * @file lcd.h
 * @author CMIOT Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */
#ifndef __LCD_H__
#define __LCD_H__

#include <stdio.h>



#define LCD_RST_GPIO  GPIOB
#define LCD_RST_PIN   GPIO_PIN_5
#define LCD_SDI_GPIO  GPIOA
#define LCD_SDI_PIN   GPIO_PIN_1
#define LCD_SCLK_GPIO GPIOC
#define LCD_SCLK_PIN  GPIO_PIN_3
#define LCD_CS_GPIO   GPIOC
#define LCD_CS_PIN    GPIO_PIN_2
#define LCD_DCK_GPIO  GPIOF
#define LCD_DCK_PIN   GPIO_PIN_12
#define LCD_A_GPIO    GPIOE
#define LCD_A_PIN     GPIO_PIN_14

#define LCD_RST_H     GPIO_SetBits(LCD_RST_GPIO, LCD_RST_PIN)
#define LCD_RST_L     GPIO_ResetBits(LCD_RST_GPIO, LCD_RST_PIN)

#define LCD_CS_H      GPIO_SetBits(LCD_CS_GPIO, LCD_CS_PIN)
#define LCD_CS_L      GPIO_ResetBits(LCD_CS_GPIO, LCD_CS_PIN)

#define LCD_DCK_DATA  GPIO_SetBits(LCD_DCK_GPIO, LCD_DCK_PIN)
#define LCD_DCK_CMD   GPIO_ResetBits(LCD_DCK_GPIO, LCD_DCK_PIN)

#define LCD_A_H       GPIO_SetBits(LCD_A_GPIO, LCD_A_PIN)
#define LCD_A_L       GPIO_ResetBits(LCD_A_GPIO, LCD_A_PIN)


#define WHITE         	 0xFFFF
#define BLACK         	 0x0000
#define BLUE         	 0x001F
#define BRED             0xF81F
#define GRED 		     0xFFE0
#define GBLUE		     0x07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 		     0xBC40
#define BRRED 		     0xFC07
#define GRAY  		     0x8430
#define DARKBLUE      	 0x01CF
#define LIGHTBLUE      	 0x7D7C
#define GRAYBLUE       	 0x5458
#define LIGHTGREEN     	 0x841F
#define LIGHTGRAY        0XEF5B
#define LGRAY 		     0xC618
#define GRAY0            0xEF7D
#define GRAY1            0x8410
#define GRAY2            0x4208
#define LGRAYBLUE        0xA651
#define LBBLUE           0x2B12

#define BACK_COLOR       0xFFFF


extern void LCD_Init(void);
extern void BlockWrite(unsigned int Xstart,unsigned int Xend,unsigned int Ystart,unsigned int Yend, uint16_t color);
extern void PirctureWrite(unsigned int Xstart,unsigned int Xend,unsigned int Ystart,unsigned int Yend, uint16_t* data);

extern void LCD_Address_Set(uint16_t Xstart, uint16_t Xend, uint16_t Ystart, uint16_t Yend);
extern void LCD_DrawPoint(uint16_t color);
extern void LCD_ShowChar(uint16_t x, uint16_t y, uint8_t num, uint8_t size, uint16_t color, uint16_t back_color);
extern void LCD_ShowString(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t size, uint16_t color, uint16_t back_color, uint8_t *p);

#endif /* __LCD_H__ */
