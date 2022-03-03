/**
 ***********************************************************************************************************************
 * Copyright (c) 2020, China Mobile Communications Group Co.,Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with 
 * the License. You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on
 * an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License.
 *
 * @file        fal_cfg.h
 *
 * @brief       Flash abstract layer partition definition
 *
 * @revision
 * Date          Author          Notes
 * 2020-02-20    OneOS Team      First Version
 ***********************************************************************************************************************
 */

#ifndef _FAL_CFG_H_
#define _FAL_CFG_H_

#include <board.h>

#define FAL_PART_HAS_TABLE_CFG

/* bootloader partition name */
#define OS_BL_PART_NAME "bootloader"
#define OS_CFG_NAME     "cfg"
#define OS_APP_NAME     "app"
#define OS_DL_PART_NAME "download"

/* Flash device Configuration */
#define OS_ONCHIP_FLASH_NAME "onchip_flash"
#define OS_EXTERN_FLASH_NAME "nor_flash"


#define MCU_SRAM_BEGIN ((uint32_t)0x20000000)
#define MCU_SRAM_SIZE  (32 * 1024)
#define MCU_SRAM_END   (MCU_SRAM_BEGIN + MCU_SRAM_SIZE)

#define MCU_ROM_BEGIN ((uint32_t)0x00000000)
#define MCU_ROM_SIZE  (256 * 1024)
#define MCU_ROM_END   (MCU_ROM_BEGIN + MCU_ROM_SIZE)

#define MCU_SPI_FLASH_BEGIN       ((uint32_t)0x00)
#define MCU_SPI_FLASH_SIZE        (512 * 1024)
#define MCU_SPI_FLASH_SECTOR_SIZE 256
#define MCU_SPI_FLASH_END         (MCU_SPI_FLASH_BEGIN + MCU_SPI_FLASH_SIZE)

/* bootloader */
#define MCU_BOOT_ENTRY MCU_ROM_BEGIN
#define MCU_BOOT_SIZE  (124 * 1024)
#define MCU_BOOT_END   (MCU_BOOT_ENTRY + MCU_BOOT_SIZE)

/* download */
#define OS_DL_PART_ADDR     ((uint32_t)MCU_BOOT_END)
#define OS_DL_PART_SIZE     (4 * 1024)
#define OS_DL_PART_END_ADDR (OS_DL_PART_ADDR + OS_DL_PART_SIZE)

#ifdef FAL_PART_HAS_TABLE_CFG
/* partition table */
#define FAL_PART_TABLE                                                                                                 \
    {                                                                                                                  \
        {OS_BL_PART_NAME, OS_ONCHIP_FLASH_NAME,        (MCU_BOOT_ENTRY - MCU_ROM_BEGIN),    MCU_BOOT_SIZE, 0}, \
        {OS_DL_PART_NAME, OS_ONCHIP_FLASH_NAME,       (OS_DL_PART_ADDR - MCU_ROM_BEGIN),  OS_DL_PART_SIZE, 0}, \
    }
#endif /* FAL_PART_HAS_TABLE_CFG */

#endif /* _FAL_CFG_H_ */
