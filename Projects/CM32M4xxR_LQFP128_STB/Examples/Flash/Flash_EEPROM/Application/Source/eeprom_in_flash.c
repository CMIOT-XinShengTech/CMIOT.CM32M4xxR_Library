/* eeprom in flash
 * Copyright (c) 2021-2022 epoko
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "eeprom_in_flash.h"

static uint16_t EEPROM_data[EEPROM_NUM_MAX] = {0};
static int EEPROM_PART_USE = -1;

static int EE_Init(void);
static int EE_ReadVariable(uint32_t VirtAddress, uint16_t *Data);
static int EE_WriteVariable(uint32_t VirtAddress, uint16_t Data);
static int EE_Format(int part);

//将默认数据写入内部数据暂存区，初始化分区指示标志。
//如果Flash中没有数据，则初始化分区并写入default_data，如果Flash中有数据，则从Flash中读取实际数据并覆盖内部暂存数据。
//默认数据可以置NULL。
int EEPROM_Init(void *default_data)
{
	uint32_t time_use = HAL_GetTick();
	uint32_t i;

	if (default_data)
		memcpy(EEPROM_data, default_data, sizeof(EEPROM_data));				//将默认数据写入内部数据暂存区

	if (EE_Init() != HAL_OK)																				//初始化分区指示标志
	{
		log_printf(LOG_Error, "EEPROM Init error\r\n");
		return HAL_ERROR;
	}

	for (i = 0; i < EEPROM_NUM_MAX; i++)
	{
		EE_ReadVariable(i, &EEPROM_data[i]);													//从FLASH中读出数据覆盖内部数据暂存区
	}
	
	log_printf(LOG_Verbose, "EEPROM_Init use %dms\r\n", HAL_GetTick() - time_use);
	return HAL_OK;
}

//读取EEPROM数据（半字）
uint16_t EEPROM_Read(uint16_t Address)													
{
	if (Address >= EEPROM_NUM_MAX)
		return 0;

	return EEPROM_data[Address];											//直接读取内部数据暂存区，因为运行时内部数据暂存区永远是最新的有效数据
}

//写EEPROM数据（半字）
int EEPROM_Write(uint16_t Address, uint16_t Data)
{
	if (EEPROM_PART_USE == -1 || Address >= EEPROM_NUM_MAX)
		return HAL_ERROR;

	if (EEPROM_data[Address] == Data)									//如果数据内容相同，则无需再写
		return HAL_OK;

	if (EE_WriteVariable(Address, Data) != HAL_OK)		//检查分区是否需要切换，并执行写数据操作
	{
		// EEPROM_data[Address] = Data;
		log_printf(LOG_Error, "EEPROM write error\r\n");
		return HAL_ERROR;
	}

	return HAL_OK;
}

//读取EEPROM数据（支持连续读一块数据，适用于数据表项超出半字的情况）
int EEPROM_Read_Buf(uint16_t Address, uint16_t *buf, uint16_t length)
{
	if (Address + length >= EEPROM_NUM_MAX)
		return HAL_ERROR;

	memcpy(buf, EEPROM_data + Address, length << 1);			//直接读取内部数据暂存区，因为运行时内部数据暂存区永远是最新的有效数据
	return HAL_OK;
}

//写EEPROM数据（支持连续写一块数据，适用于数据表项超出半字的情况）
int EEPROM_Write_Buf(uint16_t Address, uint16_t *buf, uint16_t length)
{
	if (EEPROM_PART_USE == -1 || Address + length >= EEPROM_NUM_MAX)
		return HAL_ERROR;

	while (length--)
	{
		if (EEPROM_data[Address] != *buf)										//如果数据内容相同，则无需再写
		{
			if (EE_WriteVariable(Address, *buf) != HAL_OK)		//检查分区是否需要切换，并执行写数据操作
			{
				// EEPROM_data[Address] = *buf;
				log_printf(LOG_Error, "EEPROM write buf error\r\n");
				return HAL_ERROR;
			}
		}

		buf++;
		Address++;
	}
	return HAL_OK;
}

//格式化EEPROM，将默认数据写入内部数据暂存区并写入flash，设置分区0为当前使用分区，擦除1分区
//默认数据可以置NULL。
int EEPROM_Format(void *default_data)
{
	if (default_data)
		memcpy(EEPROM_data, default_data, sizeof(EEPROM_data));
	else
		memset(EEPROM_data, 0, sizeof(EEPROM_data));

	if (EE_Format(0) != HAL_OK)
	{
		log_printf(LOG_Error, "EEPROM Format error\r\n");
		return HAL_ERROR;
	}

	EEPROM_PART_USE = 0;

	if (EE_ErasePart(1) != HAL_OK)
		return HAL_ERROR;
	return HAL_OK;
}

/* -------------- EE Private function -------------- */
//初始化分区内部管理
static int EE_Init(void)
{
	//根据分区状态域设置分区指示标志
	if (EE_ReadWord(PART0_BASE_ADDRESS) == PART_USED_MARK)		
	{
		EEPROM_PART_USE = 0;
	}
	else
	{
		if (EE_ReadWord(PART1_BASE_ADDRESS) == PART_USED_MARK)
		{
			EEPROM_PART_USE = 1;
		}
		else		//如果两个分区都在使用，则格式化0分区，并将内部暂存数据进行拷贝。
		{
			if (EE_Format(0) != HAL_OK)
				return HAL_ERROR;
			EEPROM_PART_USE = 0;
		}
	}

	return HAL_OK;
}

//从flash中读取有效数据，仅在初始化时使用，平时读数据可以直接读取内部数据暂存区
static int EE_ReadVariable(uint32_t VirtAddress, uint16_t *Data)
{
	uint32_t time_use = HAL_GetTick();
	uint32_t PartStartAddress = EEPROM_PART_USE == 0 ? PART0_BASE_ADDRESS : PART1_BASE_ADDRESS;
	uint32_t Address = (EEPROM_PART_USE == 0 ? PART0_END_ADDRESS : PART1_END_ADDRESS) - 4;
	uint32_t temp;

	VirtAddress <<= 16;
	for (; Address > PartStartAddress; Address -= 4)
	{
		temp = EE_ReadWord(Address);
		if ((temp & 0xffff0000) == VirtAddress)				//匹配地址
		{
			*Data = temp & 0xffff;											//获取数据
			log_printf(LOG_Verbose, "EE_ReadVariable use %dms\r\n", HAL_GetTick() - time_use);
			return HAL_OK;
		}
	}
	log_printf(LOG_Warn, "EE_ReadVariable failed, use %dms\r\n", HAL_GetTick() - time_use);
	return HAL_ERROR;
}

//检查分区满状态，如果不满直接写入，如果满则切换分区后写入。
static int EE_WriteVariable(uint32_t VirtAddress, uint16_t Data)
{
	uint32_t time_use = HAL_GetTick();
	uint32_t PartStartAddress = EEPROM_PART_USE == 0 ? PART0_BASE_ADDRESS : PART1_BASE_ADDRESS;
	uint32_t Address = (EEPROM_PART_USE == 0 ? PART0_END_ADDRESS : PART1_END_ADDRESS) - 4;

	if (EE_ReadWord(Address) != 0xffffffff)	//当前分区已满
	{
		EEPROM_data[VirtAddress] = Data;
		//开始切换分区
		if (EE_Format(EEPROM_PART_USE == 0 ? 1 : 0) != HAL_OK)	//格式化新分区并复制有效数据
			return HAL_ERROR;

		EEPROM_PART_USE = EEPROM_PART_USE == 0 ? 1 : 0;					//切换当前分区指示标志

#if PART0_BASE_ADDRESS != PART1_BASE_ADDRESS								//擦除旧分区，擦除两次？？？
		if (EE_ErasePart(EEPROM_PART_USE == 0 ? 1 : 0) != HAL_OK)
			return HAL_ERROR;
#endif

		return HAL_OK;
	}
	else
	{
		for (Address -= 4; Address > PartStartAddress; Address -= 4)		//查找当前分区的数据末端
		{
			if (EE_ReadWord(Address) != 0xffffffff)
				break;
		}

		if (EE_ProgramWord(Address + 4, (VirtAddress << 16) | Data) != HAL_OK)	//写数据
			return HAL_ERROR;

		EEPROM_data[VirtAddress] = Data;																	//更新数据暂存区
		log_printf(LOG_Verbose, "EE_WriteVariable use %dms\r\n", HAL_GetTick() - time_use);

		return HAL_OK;
	}
}

//擦除分区后，将内部暂存数据拷贝到该分区，然后设置分区状态。
static int EE_Format(int part)
{
	uint32_t i;
	uint32_t Part_Addr;
	uint32_t Address;

	if (part == 0)
		Part_Addr = PART0_BASE_ADDRESS;
	else if (part == 1)
		Part_Addr = PART1_BASE_ADDRESS;
	else
		return HAL_ERROR;

	if (EE_ErasePart(part) != HAL_OK)	//擦除分区
		return HAL_ERROR;

	log_printf(LOG_Info, "EEPROM move data to partiton %d\r\n", part);
	Address = Part_Addr + 4;
	for (i = 0; i < EEPROM_NUM_MAX; i++)
	{
		if (EE_ProgramWord(Address, (i << 16) | EEPROM_data[i]) != HAL_OK)		//复制有效数据
			return HAL_ERROR;

		Address += 4;
	}

	if (EE_ProgramWord(Part_Addr, PART_USED_MARK) != HAL_OK)								//设置分区状态
		return HAL_ERROR;

	return HAL_OK;
}
