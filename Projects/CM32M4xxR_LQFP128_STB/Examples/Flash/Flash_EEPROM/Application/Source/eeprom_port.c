#include "eeprom_in_flash.h"

#define PAGE_SIZE     1024

//EEPROM_PART0 0x0800F000 - 0x0800F800 size 2048
//EEPROM_PART1 0x0800F800 - 0x08001000 size 2048

/* Erase from PART_BASE_ADDRESS, size EEPROM_PART_SIZE */
int EE_ErasePart(int part)
{
	//uint32_t PageError = 0;
	uint32_t time_use = HAL_GetTick();
	uint32_t loop;
	int ret;
	uint32_t erase_address = part == 0 ? PART0_BASE_ADDRESS : PART1_BASE_ADDRESS;
	uint32_t erase_size = part == 0 ? EEPROM_PART0_SIZE : EEPROM_PART1_SIZE;

	if (erase_address < PART0_BASE_ADDRESS || erase_address >= PART1_END_ADDRESS)
		return HAL_ERROR;

	log_printf(LOG_Debug, "FLASHE Erase 0x%08x size %#x\r\n", erase_address, erase_size);

	FLASH_Unlock();
	for(loop=0;loop < erase_size/PAGE_SIZE; loop++)
	{
			ret = FLASH_EraseOnePage(erase_address + loop*PAGE_SIZE);
			if (ret != FLASH_COMPL)
			{
				FLASH_Lock();
				log_printf(LOG_Error, "FLASHE Erase error %d at address %x \r\n", ret,erase_address + loop*PAGE_SIZE);
				return HAL_ERROR;
			}
	}

	FLASH_Lock();
	log_printf(LOG_Verbose, "FLASHE Erase over, use %dms\r\n", HAL_GetTick() - time_use);
	return HAL_OK;
}

/* If the write operation is not a 32-bit atomic operation,
   Write the low 16-bit first, then write the high 16-bit */
int EE_ProgramWord(uint32_t Address, uint32_t Data)
{
	int ret;

	if (Address < PART0_BASE_ADDRESS || Address >= PART1_END_ADDRESS)
		return HAL_ERROR;

	log_printf(LOG_Debug, "FLASHE Program 0x%08x 0x%08x\r\n", Address, Data);

	FLASH_Unlock();

	ret = FLASH_ProgramWord(Address,Data);
	if (ret != FLASH_COMPL)
	{
		FLASH_Lock();
		log_printf(LOG_Error, "FLASHE Program error %d\r\n", ret);
		return HAL_ERROR;
	}

	FLASH_Lock();
	return HAL_OK;
}
