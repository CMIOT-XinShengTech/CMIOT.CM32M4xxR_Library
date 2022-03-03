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

#include "main.h"
#include "log.h"
#include "led.h"
#include "eeprom_in_flash.h"

/** @addtogroup CM32M4xxR_StdPeriph_Examples
 * @{
 */

#define halfword_data1_addr  	0
#define word_data2_addr			1
#define word_data3_addr 		3
#define halfword_data4_addr		5

#pragma pack(1)
typedef struct
{
	 uint16_t halfword_data1;	//virtual address 0
	 uint32_t word_data2;			//virtual address 1
	 uint32_t word_data3;			//virtual address 3
	 uint16_t halfword_data4;	//virtual address 5
}NV_data_s;
#pragma pack()

uint8_t Check_All_Data(NV_data_s *NV_data)
{
	uint32_t temp_data2;
	uint32_t temp_data3;
	//log_info("halfword_data1 is %x\r\n",EEPROM_Read(halfword_data1_addr));
	//log_info("halfword_data4 is %x\r\n",EEPROM_Read(halfword_data4_addr));
	EEPROM_Read_Buf(word_data2_addr, (uint16_t*)&temp_data2, sizeof(temp_data2)/2);
	//log_info("word_data2 is %x\r\n",temp_data2);
	EEPROM_Read_Buf(word_data3_addr, (uint16_t*)&temp_data3, sizeof(temp_data3)/2);
	//log_info("word_data3 is %x\r\n",temp_data3);
	if ((EEPROM_Read(halfword_data1_addr) != NV_data->halfword_data1)
		|| (EEPROM_Read(halfword_data4_addr) != NV_data->halfword_data4)
		|| (temp_data2 != NV_data->word_data2)
		|| (temp_data3 != NV_data->word_data3))
	{
	    LedOn(LED1_PORT, LED1_PIN);
		log_info("Check_All_Data ERROR\r\n");
		return 1;
	}
	return 0;
}

/**
 * @brief  Main function.
 */
int main(void)
{
	uint8_t ret = 0;
	NV_data_s NV_data;
	uint16_t loop;

    LedInit(LED1_PORT, LED1_PIN);
    LedInit(LED2_PORT, LED2_PIN);
    LedOff(LED1_PORT, LED1_PIN);
    LedOff(LED2_PORT, LED2_PIN);

    /* Log initialize */
    log_init();

    log_info("Flash EEPROM Test Start\r\n");

    FLASH_Unlock();
    FLASH_EraseOnePage(PART0_BASE_ADDRESS);
    FLASH_EraseOnePage(PART1_BASE_ADDRESS);
    FLASH_Lock();
    //EEPROM_Format(NULL);
	NV_data.halfword_data1 = 0x1111;
	NV_data.word_data2 = 0x22222222;
	NV_data.word_data3 = 0x33333333;
	NV_data.halfword_data4 = 0x4444;

	EEPROM_Init((void*)&NV_data);	//如果EEPROM中无数据，则写入NV_data；如果有数据，NV_data参数则无效。
	log_info("EEPROM_Init Finished\r\n");

	ret |= Check_All_Data(&NV_data);

	//写EEPROM数据，如果待写入数据与EEPROM中存储的数据相同，则不会实际执行写操作（eeprom_in_flash中的log不会输出）
	EEPROM_Write(halfword_data1_addr, NV_data.halfword_data1);
	EEPROM_Write_Buf(word_data2_addr, (uint16_t*)&NV_data.word_data2, sizeof(NV_data.word_data2)/2);
	EEPROM_Write_Buf(word_data3_addr, (uint16_t*)&NV_data.word_data3, sizeof(NV_data.word_data3)/2);
	EEPROM_Write(halfword_data4_addr, NV_data.halfword_data4);
	log_info("EEPROM_Write Finished\r\n");

	ret |= Check_All_Data(&NV_data);

	//写EEPROM数据，待写入数据与EEPROM中存储的数据不同
	NV_data.halfword_data1 += 0x0001;
	NV_data.word_data2 += 0x00010001;
	NV_data.word_data3 += 0x00010001;
	NV_data.halfword_data4 += 0x0001;
	EEPROM_Write(halfword_data1_addr, NV_data.halfword_data1);
	EEPROM_Write_Buf(word_data2_addr, (uint16_t*)&NV_data.word_data2, sizeof(NV_data.word_data2)/2);
	EEPROM_Write_Buf(word_data3_addr, (uint16_t*)&NV_data.word_data3, sizeof(NV_data.word_data3)/2);
	EEPROM_Write(halfword_data4_addr, NV_data.halfword_data4);
	log_info("EEPROM_Write Finished\r\n");
	ret |= Check_All_Data(&NV_data);

	//一页Flash为2K空间即512个字，分区管理占用1个字，前面的写操作占用了12个字，因此再写499次后，会发生分区切换操作，切换至1分区。
	for(loop=0; loop < 499/6+1; loop++)		//实际写了504次
	{
		NV_data.halfword_data1 += 0x0001;
		NV_data.word_data2 += 0x00010001;
		NV_data.word_data3 += 0x00010001;
		NV_data.halfword_data4 += 0x0001;
		EEPROM_Write(halfword_data1_addr, NV_data.halfword_data1);
		EEPROM_Write_Buf(word_data2_addr, (uint16_t*)&NV_data.word_data2, sizeof(NV_data.word_data2)/2);
		EEPROM_Write_Buf(word_data3_addr, (uint16_t*)&NV_data.word_data3, sizeof(NV_data.word_data3)/2);
		EEPROM_Write(halfword_data4_addr, NV_data.halfword_data4);
	}
	ret |= Check_All_Data(&NV_data);

	//再写501次后，会发生分区切换操作，切换回0分区。
	for(loop=0; loop < 501/6+1; loop++)	//实际写了504次
	{
		NV_data.halfword_data1 += 0x0001;
		NV_data.word_data2 += 0x00010001;
		NV_data.word_data3 += 0x00010001;
		NV_data.halfword_data4 += 0x0001;
		EEPROM_Write(halfword_data1_addr, NV_data.halfword_data1);
		EEPROM_Write_Buf(word_data2_addr, (uint16_t*)&NV_data.word_data2, sizeof(NV_data.word_data2)/2);
		EEPROM_Write_Buf(word_data3_addr, (uint16_t*)&NV_data.word_data3, sizeof(NV_data.word_data3)/2);
		EEPROM_Write(halfword_data4_addr, NV_data.halfword_data4);
	}
	ret |= Check_All_Data(&NV_data);

    if (0 == ret)
    {
    	LedOn(LED2_PORT, LED2_PIN);
    }
    log_info("Flash EEPROM Test End\r\n");

    while (1)
    {
    }
}

/**
 * @}
 */

