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
 * @file qspi_flash.h
 * @author CMIOT Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */

#ifndef __QSPI_FLASH_H__
#define __QSPI_FLASH_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup Utilities
 * @{
 */

/** @addtogroup
 * @{
 */

/** @addtogroup Common
 * @{
 */

/** @addtogroup QSPI_FLASH
 * @{
 */

/** @addtogroup QSPI_FLASH_Exported_Types
 * @{
 */
/**
 * @}
 */

/** @addtogroup QSPI_FLASH_Exported_Constants
 * @{
 */

/**
 * @brief  QSPI Flash device
 */
#define GD25Q32C	0	/*!< GigaDevice 32M-bit SPI Flash */
#define GD25Q40C	1	/*!< GigaDevice 4M-bit SPI Flash */

/* Chosen qFlash device */
#define qFLASH_DEV		GD25Q40C

/**
 * @brief  QSPI Flash supported commands
 */
#define qFLASH_CMD_WRITE			((uint8_t) 0x02) /*!< Write to flash(program) instruction */
#define qFLASH_CMD_Q_WRITE			((uint8_t) 0x32) /*!< Write to flash(program) in quad mode instruction */
#define qFLASH_CMD_WRSR_1st			((uint8_t) 0x01) /*!< Write first Status Register instruction */
#if qFLASH_DEV == GD25Q32C
#define qFLASH_CMD_WRSR_2nd			((uint8_t) 0x31) /*!< Write second Status Register instruction */
#define qFLASH_CMD_WRSR_3rd			((uint8_t) 0x11) /*!< Write third Status Register instruction */
#endif
#define qFLASH_CMD_WREN  			((uint8_t) 0x06) /*!< Write enable instruction */
#define qFLASH_CMD_READ  			((uint8_t) 0x03) /*!< Read from flash instruction */
#define qFLASH_CMD_D_READ			((uint8_t) 0x3B) /*!< Read from flash in dual mode instruction */
#define qFLASH_CMD_Q_READ			((uint8_t) 0x6B) /*!< Read from flash in quad mode instruction */
#define qFLASH_CMD_RDSR_1st			((uint8_t) 0x05) /*!< Read first Status Register instruction  */
#define qFLASH_CMD_RDSR_2nd			((uint8_t) 0x35) /*!< Read second Status Register instruction  */
#if qFLASH_DEV == GD25Q32C
#define qFLASH_CMD_RDSR_3rd			((uint8_t) 0x15) /*!< Read third Status Register instruction  */
#endif
#define qFLASH_CMD_RDID  			((uint8_t) 0x9F) /*!< Read identification */
#define qFLASH_CMD_SE    			((uint8_t) 0x20) /*!< Sector Erase instruction */
#define qFLASH_CMD_BE    			((uint8_t) 0xD8) /*!< Block Erase instruction */
#define qFLASH_CMD_CE				((uint8_t) 0xC7) /*!< Chip Erase instruction */

/**
 * @brief  QSPI Flash status flags
 */
#define qFLASH_WIP_FLAG				((uint8_t) 0x01) /*!< Write In Progress (WIP) flag */
#define qFLASH_WEL_FLAG				((uint8_t) 0x02) /*!< Write Enable Latch flag */
#define qFLASH_QE_FLAG				((uint8_t) 0x02) /*!< QE(Quad Enable) flag */

/**
 * @brief  QSPI Flash memory organization
 */
#if qFLASH_DEV == GD25Q32C
#define qFLASH_PAGES				((uint32_t) 16384)			/* Total flash pages */
#define qFLASH_SECTORPAGES			((uint32_t) 16)				/* One sector pages */
#define qFLASH_BLOCKPAGES			((uint32_t) 256)			/* One block pages */
#define qFLASH_PAGESIZE				((uint32_t) 0x100)						/* 256 bytes per page */
#define qFLASH_SECTORSIZE			((uint32_t) (16 * qFLASH_PAGESIZE))		/* 16 pages per sector(4KB) */
#define qFLASH_BLOCKSIZE			((uint32_t) (16 * qFLASH_SECTORSIZE))	/* 16 sectors per block(64KB) */
#define qFLASH_SIZE					((uint32_t) (64 * qFLASH_BLOCKSIZE))	/* 64 blocks per chip(4MB) */
#elif qFLASH_DEV == GD25Q40C
#define qFLASH_PAGES				((uint32_t) 2048)			/* Total flash pages */
#define qFLASH_SECTORPAGES			((uint32_t) 16)				/* One sector pages */
#define qFLASH_BLOCKPAGES			((uint32_t) 256)			/* One block pages */
#define qFLASH_PAGESIZE				((uint32_t) 0x100)						/* 256 bytes per page */
#define qFLASH_SECTORSIZE			((uint32_t) (16 * qFLASH_PAGESIZE))		/* 16 pages per sector(4KB) */
#define qFLASH_BLOCKSIZE			((uint32_t) (16 * qFLASH_SECTORSIZE))	/* 16 sectors per block(64KB) */
#define qFLASH_SIZE					((uint32_t) (8 * qFLASH_BLOCKSIZE))	/* 64 blocks per chip(4MB) */
#endif

/**
 * @brief  QSPI Flash Identification
 */
#define qFLASH_GD25Q32C_ID			(0x00C84016)
#define qFLASH_GD25Q40C_ID			(0x00C84013)
#if qFLASH_DEV == GD25Q32C
#define qFLASH_ID					qFLASH_GD25Q32C_ID
#elif qFLASH_DEV == GD25Q40C
#define qFLASH_ID					qFLASH_GD25Q40C_ID
#endif

/**
 * @}
 */

/** @addtogroup QSPI_FLASH_Exported_Macros
 * @{
 */



/**
 * @}
 */

/** @addtogroup QSPI_FLASH_Exported_Functions
 * @{
 */
/**
 * @brief  High layer functions
 */
void		qFLASH_DeInit (void);
void		qFLASH_Init (uint32_t LineMode, uint32_t TransMode, uint16_t ReadNr);
void 		qFLASH_EraseSector (uint32_t SectorAddr);
void 		qFLASH_EraseBlock (uint32_t BlockAddr);
void		qFLASH_EraseChip (void);
void 		qFLASH_WritePage (uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void 		qFLASH_WritePageQ (uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void 		qFLASH_WriteBuffer (uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void 		qFLASH_WriteBufferQ (uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void		qFLASH_WritePageQ_DMA (uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void 		qFLASH_ReadBuffer (uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);
void 		qFLASH_ReadBufferD (uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);
void 		qFLASH_ReadBufferQ (uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);
void		qFLASH_ReadBufferD_DMA (uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);
void		qFLASH_ReadBufferQ_DMA (uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);
void		qFLASH_Command (uint8_t* pCmd, uint8_t Len);
void		qFLASH_Response (uint8_t* pRsp, uint8_t Len);

/**
 * @brief  Low layer functions
 */
uint8_t 	qFLASH_ReadStatus (void);
uint32_t	qFLASH_ReadID (void);
void		qFLASH_QuadEnable (void);
void		qFLASH_QuadDisable (void);
void		qFLASH_WriteEnable (void);
void		qFLASH_WaitForWriteEnd (uint32_t timeout);

#ifdef __cplusplus
}
#endif

#endif

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
