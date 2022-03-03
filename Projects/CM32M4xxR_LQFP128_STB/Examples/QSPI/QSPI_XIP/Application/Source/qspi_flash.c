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
 * @file qspi_flash.c
 * @author CMIOT Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "nuclei_sdk_soc.h"
#include "main.h"
#include "qspi_flash.h"

/** @addtogroup Utilities
 * @{
 */

/** @addtogroup
 * @{
 */

/** @addtogroup Common
 * @{
 */

/** @addtogroup SPI_FLASH
 * @brief
 * @{
 */

/** @addtogroup SPI_FLASH_Private_Types
 * @{
 */
/**
 * @}
 */

/** @addtogroup SPI_FLASH_Private_Defines
 * @{
 */
/* QSPI operation timeout value */
#define __MULTIPLIER				(1.5)	/* Coefficient to multiply with original timeout value  */
#define __CALC_TIMEOUT(__TIMEOUT__, __MULTIPLIER__)	\
		/* Get final timeout value by multiplying original
		 * timeout value with __MULTIPLIER_ */ \
		((uint32_t)ceil((__TIMEOUT__) * (__MULTIPLIER__)) < 2 ? 2 + 1 : (uint32_t)ceil((__TIMEOUT__) * (__MULTIPLIER__)) + 1)
#define QFLASH_CE_TIMEOUT_MS		__CALC_TIMEOUT(30000, __MULTIPLIER)	/* Chip Erase timeout value */
#define QFLASH_BE_TIMEOUT_MS		__CALC_TIMEOUT(2000, __MULTIPLIER)	/* Block Erase timeout value */
#define QFLASH_SE_TIMEOUT_MS		__CALC_TIMEOUT(300, __MULTIPLIER)	/* Sector Erase timeout value */
#define QFLASH_PP_TIMEOUT_MS		__CALC_TIMEOUT(2.4, __MULTIPLIER)	/* Page Program timeout value */
#define QFLASH_WSR_TIMEOUT_MS		__CALC_TIMEOUT(30, __MULTIPLIER)	/* Write Status Register timeout value */
/* DMA channels for QSPI transmit and receive data */
#define QSPI_RX_DMA_CH				(DMA2_CH6)
#define QSPI_TX_DMA_CH				(DMA2_CH7)
#define QSPI_DMA_TIMEOUT_MS			(2)
/* If defined, use the maximum sclk frequency(36M) */
//#define QSPI_USE_36M

/**
 * @}
 */

/** @addtogroup SPI_FLASH_Private_Macros
 * @{
 */
/* Reverse the byte order of 32-bit data */
#define REV_BYTE_ORDER_32(DAT)		((uint32_t)(((uint32_t)(DAT) & 0x000000FF) << 24 | \
								 	 	 		((uint32_t)(DAT) & 0x0000FF00) << 8  | \
												((uint32_t)(DAT) & 0x00FF0000) >> 8  | \
												((uint32_t)(DAT) & 0xFF000000) >> 24))
/**
 * @}
 */

/** @addtogroup SPI_FLASH_Private_Variables
 * @{
 */
/**
 * @}
 */

/** @addtogroup SPI_FLASH_Private_Function_Prototypes
 * @{
 */
/**
 * @}
 */

/** @addtogroup SPI_FLASH_Private_Functions
 * @{
 */
/**
 * @brief  DeInitializes the peripherals used by the SPI FLASH driver.
 */
void qFLASH_DeInit(void)
{

}

/**
 * @brief  Initializes the peripherals used by the SPI FLASH driver.
 * @param  LineMode	The QSPI line mode.
 * 		   This parameter can be one of the following values:
 * 		     - QSPI_LINE_STANDARD
 * 		     - QSPI_LINE_2_LINES
 * 		     - QSPI_LINE_4_LINES
 * 		     - QSPI_LINE_2_LINES_XIP
 * 		     - QSPI_LINE_4_LINES_XIP
 * @param  TransMode The QSPI transfer mode.
 * 		   This parameter can be one of the following values:
 * 		     - QSPI_TRANSFER_TX_AND_RX
 * 		     - QSPI_TRANSFER_RX_ONLY
 * 		     - QSPI_TRANSFER_TX_ONLY
 * @param  ReadNr The number of data frames to read in Rx only mode. In other mode
 * 	       this parameter will be ignored.
 */
void qFLASH_Init(uint32_t LineMode, uint32_t TransMode, uint16_t ReadNr)
{
	QSPI_InitType QSPI_InitStructure;

	/* Configure QSPI GPIOs */
	QSPI_GPIOConfig(LineMode, QSPI_NSS_PORTA, QSPI_IO_OUT_HIGH, QSPI_IO_OUT_HIGH);
	/* Reset QSPI */
	QSPI_DeInit();
	/* QSPI clock enable */
	RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_QSPI, ENABLE);
	/* Set QSPI configuration parameters value to default value */
	QSPI_InitStruct(&QSPI_InitStructure);
	/* Set specific parameters according to line mode */
	if(LineMode == QSPI_LINE_STANDARD){
		QSPI_InitStructure.SSTE 		= DISABLE;
	}else if(LineMode == QSPI_LINE_2_LINES || LineMode == QSPI_LINE_4_LINES){
		QSPI_InitStructure.Enhance.AddrLen = QSPI_ADDR_24_BITS;
		if(TransMode == QSPI_TRANSFER_RX_ONLY){
			QSPI_InitStructure.Enhance.WaitCycles = QSPI_WAIT_8_CYCLES;
			QSPI_InitStructure.RxDataNr   = (ReadNr > 0) ? ReadNr - 1 : ReadNr;
			/* Set receive FIFO full threshold to the maximum to avoid FIFO
			 * full before read */
			__QSPI_SET_RXFIFO_ITHR(QSPI_RXFIFO_ITHR_32);
		}
	}else if(LineMode == QSPI_LINE_2_LINES_XIP || LineMode == QSPI_LINE_4_LINES_XIP){
		QSPI_InitStructure.Enhance.AddrLen 			= QSPI_ADDR_24_BITS;
		QSPI_InitStructure.Enhance.WaitCycles 		= QSPI_WAIT_8_CYCLES;
		QSPI_InitStructure.Enhance.XIP_CT_EN 		= ENABLE;
		QSPI_InitStructure.Enhance.XIP_INST_EN 		= ENABLE;
		QSPI_InitStructure.Enhance.XIP_DFS_HC 		= DISABLE;
		QSPI_InitStructure.Enhance.TransferType 	= QSPI_TRANS_BOTH_STANDARD;
		QSPI_InitStructure.Enhance.ITOC 			= 0x6B;
		QSPI_InitStructure.Enhance.WTOC 			= 0x6B;
		QSPI_InitStructure.Enhance.MD_BIT_EN		= DISABLE;
		QSPI_InitStructure.Enhance.XIP_MBL 			= QSPI_XIP_MBL_8_BITS;
	}
	QSPI_InitStructure.LineMode 	= LineMode;
	QSPI_InitStructure.TransferMode = TransMode;
#ifdef QSPI_USE_36M
	QSPI_InitStructure.ClkDiv = 4;
#else
	QSPI_InitStructure.ClkDiv = 8;
#endif
	/* Initialize QSPI */
	QSPI_Init(&QSPI_InitStructure);
	/* Enable QSPI XIP */
	if(LineMode == QSPI_LINE_2_LINES_XIP || LineMode == QSPI_LINE_4_LINES_XIP){
		QSPI_XIP_Enable(ENABLE);
	}else{
		QSPI_XIP_Enable(DISABLE);
	}
	/* Enable QSPI */
	QSPI_Enable(ENABLE);
	/* Enable memory-remap. Should note that if XIP mode is used,
	 * this step must be done after other QSPI configuration */
	if(LineMode == QSPI_LINE_2_LINES_XIP || LineMode == QSPI_LINE_4_LINES_XIP){
		__QSPI_XIP_ENABLE();
	}else{
		__QSPI_XIP_DISABLE();
	}
}

/**
 * @brief  Transmit command to flash.
 * @param  pCmd Pointer to command buffer.
 * @param  Len  Command length.
 * @note   Len must be equal to or less than the actual length of
 * 		   command buffer.
 */
void qFLASH_Command(uint8_t* pCmd, uint8_t Len)
{
#ifdef QSPI_USE_36M
	DMA_InitType DMA_InitStructure;
	QSPI_DMAType QSPI_DMAInitStructure = {0};
	uint32_t *pCmdSeq = NULL;
	uint32_t sTick = 0;
#endif
	/* Check parameters */
	if(!pCmd || !Len) { return; }
	/* Use DMA if the QSPI sclk is 36M */
#ifdef QSPI_USE_36M
	/* Copy data and extend 8-bit data to 32 bit */
	pCmdSeq = (uint32_t *)malloc(Len * sizeof(uint32_t));
	if(!pCmdSeq) { return; }
	for(uint32_t i = 0; i < Len; i++){
		pCmdSeq[i] = (uint32_t)pCmd[i];
	}
	/* Configure DMA channel */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_DMA2, ENABLE);
	DMA_DeInit(QSPI_TX_DMA_CH);
	DMA_InitStructure.PeriphAddr		= (uint32_t)&QSPI->DAT0;
	DMA_InitStructure.MemAddr			= (uint32_t)pCmdSeq;
	DMA_InitStructure.Direction			= DMA_DIR_PERIPH_DST;
	DMA_InitStructure.BufSize			= Len;
	DMA_InitStructure.PeriphInc			= DMA_PERIPH_INC_DISABLE;
	DMA_InitStructure.DMA_MemoryInc		= DMA_MEM_INC_ENABLE;
	DMA_InitStructure.PeriphDataSize	= DMA_PERIPH_DATA_SIZE_WORD;
	DMA_InitStructure.MemDataSize		= DMA_MEMORY_DATA_SIZE_WORD;
	DMA_InitStructure.CircularMode		= DMA_MODE_NORMAL;
	DMA_InitStructure.Priority			= DMA_PRIORITY_HIGH;
	DMA_InitStructure.Mem2Mem			= DMA_M2M_DISABLE;
    DMA_Init(QSPI_TX_DMA_CH, &DMA_InitStructure);
    /* Configure QSPI DMA transmit data level and enable DMA transmit */
    QSPI_DMAInitStructure.TDL = 1;
    QSPI_DMAInitStructure.TX_DMA_EN = QSPI_DMA_TX_ENABLE;
    QSPI_DMAConfig(&QSPI_DMAInitStructure);
    /* Enable DMA and start transmitting */
    DMA_EnableChannel(QSPI_TX_DMA_CH, ENABLE);
    /* Waiting for DMA transmission to complete */
    sTick = GetSystick();
    while (!DMA_GetFlagStatus(DMA2_FLAG_TC7, DMA2) && (GetSystick() - sTick) < QSPI_DMA_TIMEOUT_MS);
    /* When the DMA transfer is over, there may still be
     * unsent data in the FIFO */
    while(__QSPI_GET_STS(QSPI_STATUS_TXFE) == RESET && (GetSystick() - sTick) < QSPI_DMA_TIMEOUT_MS);
    /* Disable DMA */
    DMA_EnableChannel(QSPI_TX_DMA_CH, DISABLE);
    /* Free memory */
    free(pCmdSeq);
#else
	QSPI_Transmit(pCmd, Len);
#endif
}

/**
 * @brief  Receive response from flash.
 * @param  pRsp Pointer to response buffer.
 * @param  Len  Response length.
 * @note   Len must be equal to or less than the maximum length of
 * 		   response buffer.
 */
void qFLASH_Response(uint8_t* pRsp, uint8_t Len)
{
	/* Check parameters */
	if(!pRsp || !Len) { return; }
	/* Read response from QSPI FIFO */
	QSPI_Receive(pRsp, Len);
}

/**
 * @brief  Erases the specified FLASH sector.
 * @param  SectorAddr address of the sector to erase.
 * @note   This interface should be called in QSPI standard mode.
 */
void qFLASH_EraseSector(uint32_t SectorAddr)
{
	uint8_t cmdSeq[] = {qFLASH_CMD_SE, 0x00, 0x00, 0x00};	/* Sector erase command and three address bytes */

	/* Check secotr address */
	if(SectorAddr >= qFLASH_SIZE) { return; }

	/* Set sector address */
	cmdSeq[1] = (uint8_t)((SectorAddr & 0x00FF0000) >> 16);
	cmdSeq[2] = (uint8_t)((SectorAddr & 0x0000FF00) >> 8);
	cmdSeq[3] = (uint8_t)(SectorAddr & 0x000000FF);
	/* Enable write */
	qFLASH_WriteEnable();
	/* Transmit sector erase command */
	qFLASH_Command(cmdSeq, 4);
    /* Wait the end of flash erasing */
    qFLASH_WaitForWriteEnd(QFLASH_SE_TIMEOUT_MS);
}

/**
 * @brief  Erases the entire FLASH.
 * @note   This interface should be called in QSPI standard mode.
 */
void qFLASH_EraseBlock(uint32_t BlockAddr)
{
	uint8_t cmdSeq[] = {qFLASH_CMD_BE, 0x00, 0x00, 0x00};	/* Sector erase command and three address bytes */

	/* Check block address */
	if(BlockAddr >= qFLASH_SIZE) { return; }

	/* Set block address */
	cmdSeq[1] = (uint8_t)((BlockAddr & 0x00FF0000) >> 16);
	cmdSeq[2] = (uint8_t)((BlockAddr & 0x0000FF00) >> 8);
	cmdSeq[3] = (uint8_t)(BlockAddr & 0x000000FF);
	/* Enable write */
	qFLASH_WriteEnable();
	/* Transmit block erase command */
	qFLASH_Command(cmdSeq, 4);
    /* Wait the end of flash erasing */
    qFLASH_WaitForWriteEnd(QFLASH_BE_TIMEOUT_MS);
}

/**
 * @brief  Erases the entire FLASH.
 * @note   This interface should be called in QSPI standard mode.
 */
void qFLASH_EraseChip(void)
{
	uint8_t cmd = qFLASH_CMD_CE; /* Chip erase command */

	/* Enable write */
	qFLASH_WriteEnable();
	/* Transmit chip erase command */
	qFLASH_Command(&cmd, 1);
    /* Wait the end of flash writing */
    qFLASH_WaitForWriteEnd(QFLASH_CE_TIMEOUT_MS);
}

/**
 * @brief  Writes data to the FLASH in QSPI standard mode.
 * @note   The number of byte can't exceed the FLASH page size.
 * @param  pBuffer pointer to the buffer containing the data to be written
 *         to the FLASH.
 * @param  WriteAddr FLASH's internal address to write to.
 * @param  NumByteToWrite number of bytes to write to the FLASH, must be equal
 *         or less than "qFLASH_PAGESIZE" value.
 * @note   This interface should be called in QSPI standard mode.
 */
void qFLASH_WritePage(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
	uint8_t cmdSeq[qFLASH_PAGESIZE + 4] = {qFLASH_CMD_WRITE}; /* Page program command, three address bytes and specified number of data */

	/* Check parameters */
	if(!pBuffer || WriteAddr >= qFLASH_SIZE || !NumByteToWrite || NumByteToWrite > qFLASH_PAGESIZE){
		return;
	}

	/* Set page address */
	cmdSeq[1] = (uint8_t)((WriteAddr & 0x00FF0000) >> 16);
	cmdSeq[2] = (uint8_t)((WriteAddr & 0x0000FF00) >> 8);
	cmdSeq[3] = (uint8_t)(WriteAddr & 0x000000FF);
	/* Copy data */
	memcpy(&cmdSeq[4], pBuffer, NumByteToWrite);
	/* Enable write */
	qFLASH_WriteEnable();
	/* Transmit page program command, address and data to flash */
	QSPI_Transmit(cmdSeq, NumByteToWrite + 4);
    /* Wait the end of flash writing */
    qFLASH_WaitForWriteEnd(QFLASH_PP_TIMEOUT_MS);
}

/**
 * @brief  Writes data to the FLASH in QSPI quad mode.
 * @note   The number of byte can't exceed the FLASH page size.
 * @param  pBuffer pointer to the buffer containing the data to be written
 *         to the FLASH.
 * @param  WriteAddr FLASH's internal address to write to.
 * @param  NumByteToWrite number of bytes to write to the FLASH, must be equal
 *         or less than "qFLASH_PAGESIZE" value.
 * @note   qFLASH_QuadEnable() should be called before calling this function.
 */
void qFLASH_WritePageQ(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
	QSPI_CommandType QSPI_CmdStructure;

	/* Check parameters */
	if(!pBuffer || WriteAddr >= qFLASH_SIZE || !NumByteToWrite || NumByteToWrite > qFLASH_PAGESIZE){
		return;
	}

	/* Set command and address */
	QSPI_CmdStructure.Instruction = (uint32_t)qFLASH_CMD_Q_WRITE;
	QSPI_CmdStructure.AddressLow = WriteAddr;
	/* Enable write */
	qFLASH_WriteEnable();
	/* Switch QSPI to quad mode */
	qFLASH_Init(QSPI_LINE_4_LINES, QSPI_TRANSFER_TX_ONLY, 0);
	/* Transmit page program command and address to flash */
	QSPI_Command(&QSPI_CmdStructure);
	/* Transmit data to flash */
	QSPI_Transmit(pBuffer, NumByteToWrite);
	/* Restore standard mode */
	qFLASH_Init(QSPI_LINE_STANDARD, QSPI_TRANSFER_TX_AND_RX, 0);
    /* Wait the end of flash writing */
    qFLASH_WaitForWriteEnd(QFLASH_PP_TIMEOUT_MS);
}

/**
 * @brief  Writes data to the FLASH in QSPI quad mode via DMA.
 * @note   The number of byte can't exceed the FLASH page size.
 * @param  pBuffer pointer to the buffer containing the data to be written
 *         to the FLASH.
 * @param  WriteAddr FLASH's internal address to write to.
 * @param  NumByteToWrite number of bytes to write to the FLASH, must be equal
 *         or less than "qFLASH_PAGESIZE" value.
 * @note   qFLASH_QuadEnable() should be called before calling this function.
 */
void qFLASH_WritePageQ_DMA(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
	DMA_InitType DMA_InitStructure;
	QSPI_DMAType QSPI_DMAInitStructure = {0};
	uint32_t cmdSeq[qFLASH_PAGESIZE + 2] = {qFLASH_CMD_Q_WRITE}; /* Page program command, three address bytes and specified number of data */
	uint32_t sTick = 0;

	/* Check parameters */
	if(!pBuffer || WriteAddr >= qFLASH_SIZE || !NumByteToWrite || NumByteToWrite > qFLASH_PAGESIZE){
		return;
	}

	/* Set page address */
	cmdSeq[1] = WriteAddr;
	/* Copy data and extend 8-bit data to 32 bit */
	for(uint32_t i = 0; i < NumByteToWrite; i++){
		(&cmdSeq[2])[i] = (uint32_t)pBuffer[i];
	}
	/* Enable write */
	qFLASH_WriteEnable();
	/* Switch QSPI to quad mode */
	qFLASH_Init(QSPI_LINE_4_LINES, QSPI_TRANSFER_TX_ONLY, 0);

	/* Configure DMA channel */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_DMA2, ENABLE);
	DMA_DeInit(QSPI_TX_DMA_CH);
	DMA_InitStructure.PeriphAddr		= (uint32_t)&QSPI->DAT0;
	DMA_InitStructure.MemAddr			= (uint32_t)cmdSeq;
	DMA_InitStructure.Direction			= DMA_DIR_PERIPH_DST;
	DMA_InitStructure.BufSize			= NumByteToWrite + 2;
	DMA_InitStructure.PeriphInc			= DMA_PERIPH_INC_DISABLE;
	DMA_InitStructure.DMA_MemoryInc		= DMA_MEM_INC_ENABLE;
	DMA_InitStructure.PeriphDataSize	= DMA_PERIPH_DATA_SIZE_WORD;
	DMA_InitStructure.MemDataSize		= DMA_MEMORY_DATA_SIZE_WORD;
	DMA_InitStructure.CircularMode		= DMA_MODE_NORMAL;
	DMA_InitStructure.Priority			= DMA_PRIORITY_HIGH;
	DMA_InitStructure.Mem2Mem			= DMA_M2M_DISABLE;
    DMA_Init(QSPI_TX_DMA_CH, &DMA_InitStructure);
    /* Configure QSPI DMA transmit data level and enable DMA transmit */
    QSPI_DMAInitStructure.TDL = 1;
    QSPI_DMAInitStructure.TX_DMA_EN = QSPI_DMA_TX_ENABLE;
    QSPI_DMAConfig(&QSPI_DMAInitStructure);
    /* Enable DMA and start transmitting */
    DMA_EnableChannel(QSPI_TX_DMA_CH, ENABLE);
    /* Waiting for DMA transmission to complete */
    sTick = GetSystick();
    while (!DMA_GetFlagStatus(DMA2_FLAG_TC7, DMA2) && (GetSystick() - sTick) < QSPI_DMA_TIMEOUT_MS);
    /* When the DMA transfer is over, there may still be
     * unsent data in the FIFO */
    while(__QSPI_GET_STS(QSPI_STATUS_TXFE) == RESET && (GetSystick() - sTick) < QSPI_DMA_TIMEOUT_MS);
	/* Restore standard mode */
	qFLASH_Init(QSPI_LINE_STANDARD, QSPI_TRANSFER_TX_AND_RX, 0);
    /* Wait the end of flash writing */
    qFLASH_WaitForWriteEnd(QFLASH_PP_TIMEOUT_MS);
    /* Disable DMA */
    DMA_EnableChannel(QSPI_TX_DMA_CH, DISABLE);
}

/**
 * @brief  Reads a block of data from the FLASH.
 * @param  pBuffer pointer to the buffer that receives the data read from the FLASH.
 * @param  ReadAddr FLASH's internal address to read from.
 * @param  NumByteToRead number of bytes to read from the FLASH.
 */
void qFLASH_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
	return;
}

/**
 * @brief  Reads a block of data from the FLASH in dual mode.
 * @param  pBuffer pointer to the buffer that receives the data read from the FLASH.
 * @param  ReadAddr FLASH's internal address to read from.
 * @param  NumByteToRead number of bytes to read from the FLASH.
 */
void qFLASH_ReadBufferD(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
	QSPI_CommandType QSPI_CmdStructure;

	/* Check parameters */
	if(!pBuffer || ReadAddr >= qFLASH_SIZE || !NumByteToRead) { return; }

	/* Set command and address */
	QSPI_CmdStructure.Instruction = (uint32_t)qFLASH_CMD_D_READ;
	QSPI_CmdStructure.AddressLow = ReadAddr;
	/* Switch to dual mode */
	qFLASH_Init(QSPI_LINE_2_LINES, QSPI_TRANSFER_RX_ONLY, NumByteToRead);
	/* Transmit qual read command and address */
	QSPI_Command(&QSPI_CmdStructure);
	/* Receive data */
	QSPI_Receive(pBuffer, NumByteToRead);
	/* Restore standard mode */
	qFLASH_Init(QSPI_LINE_STANDARD, QSPI_TRANSFER_TX_AND_RX, 0);
}

/**
 * @brief  Reads a block of data from the FLASH in quad mode.
 * @param  pBuffer pointer to the buffer that receives the data read from the FLASH.
 * @param  ReadAddr FLASH's internal address to read from.
 * @param  NumByteToRead number of bytes to read from the FLASH.
 * @note   This interface should be called in QSPI quad mode.
 * @note   qFLASH_QuadEnable() should be called before calling this function.
 */
void qFLASH_ReadBufferQ(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
	QSPI_CommandType QSPI_CmdStructure;

	/* Check parameters */
	if(!pBuffer || ReadAddr >= qFLASH_SIZE || !NumByteToRead) { return; }

	/* Set command and address */
	QSPI_CmdStructure.Instruction = (uint32_t)qFLASH_CMD_Q_READ;
	QSPI_CmdStructure.AddressLow = ReadAddr;
	/* Switch to quad mode */
	qFLASH_Init(QSPI_LINE_4_LINES, QSPI_TRANSFER_RX_ONLY, NumByteToRead);
	/* Transmit quad read command and address */
	QSPI_Command(&QSPI_CmdStructure);
	/* Receive data */
	QSPI_Receive(pBuffer, NumByteToRead);
	/* Restore standard mode */
	qFLASH_Init(QSPI_LINE_STANDARD, QSPI_TRANSFER_TX_AND_RX, 0);
}

/**
 * @brief  Reads a block of data from the FLASH in dual mode via DMA.
 * @param  pBuffer pointer to the buffer that receives the data read from the FLASH.
 * @param  ReadAddr FLASH's internal address to read from.
 * @param  NumByteToRead number of bytes to read from the FLASH.
 */
void qFLASH_ReadBufferD_DMA(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
	QSPI_CommandType QSPI_CmdStructure;
	QSPI_DMAType QSPI_DMAInitStructure = {0};
	DMA_InitType DMA_InitStructure;
	uint32_t sTick = 0;

	/* Check parameters */
	if(!pBuffer || ReadAddr >= qFLASH_SIZE || !NumByteToRead) { return; }

	/* Set command and address */
	QSPI_CmdStructure.Instruction = (uint32_t)qFLASH_CMD_D_READ;
	QSPI_CmdStructure.AddressLow = ReadAddr;
	/* Configure DMA channel */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_DMA2, ENABLE);
	DMA_DeInit(QSPI_RX_DMA_CH);
	DMA_InitStructure.PeriphAddr		= (uint32_t)&QSPI->DAT0;
	DMA_InitStructure.MemAddr			= (uint32_t)pBuffer;
	DMA_InitStructure.Direction			= DMA_DIR_PERIPH_SRC;
	DMA_InitStructure.BufSize			= NumByteToRead;
	DMA_InitStructure.PeriphInc			= DMA_PERIPH_INC_DISABLE;
	DMA_InitStructure.DMA_MemoryInc		= DMA_MEM_INC_ENABLE;
	DMA_InitStructure.PeriphDataSize	= DMA_PERIPH_DATA_SIZE_BYTE;
	DMA_InitStructure.MemDataSize		= DMA_MEMORY_DATA_SIZE_BYTE;
	DMA_InitStructure.CircularMode		= DMA_MODE_NORMAL;
	DMA_InitStructure.Priority			= DMA_PRIORITY_HIGH;
	DMA_InitStructure.Mem2Mem			= DMA_M2M_DISABLE;
    DMA_Init(QSPI_RX_DMA_CH, &DMA_InitStructure);
    /* Configure QSPI DMA Receive data level */
    QSPI_DMAInitStructure.RDL = 1;
    QSPI_DMAInitStructure.RX_DMA_EN = QSPI_DMA_RX_ENABLE;
	/* Switch to dual mode */
	qFLASH_Init(QSPI_LINE_2_LINES, QSPI_TRANSFER_RX_ONLY, NumByteToRead);
	/* Transmit qual read command and address */
	QSPI_Command(&QSPI_CmdStructure);
	/* Enable DMA transmit */
    QSPI_DMAConfig(&QSPI_DMAInitStructure);
    /* Enable DMA and start transmitting */
    DMA_EnableChannel(QSPI_RX_DMA_CH, ENABLE);
    /* Waiting for QSPI ready */
    sTick = GetSystick();
	while(__QSPI_GET_STS(QSPI_STATUS_BUSY) != RESET && (GetSystick() - sTick) < QSPI_DMA_TIMEOUT_MS);
	/* Restore standard mode */
	qFLASH_Init(QSPI_LINE_STANDARD, QSPI_TRANSFER_TX_AND_RX, 0);
	/* Disable DMA */
    DMA_EnableChannel(QSPI_RX_DMA_CH, DISABLE);
}

/**
 * @brief  Reads a block of data from the FLASH in quad mode via DMA.
 * @param  pBuffer pointer to the buffer that receives the data read from the FLASH.
 * @param  ReadAddr FLASH's internal address to read from.
 * @param  NumByteToRead number of bytes to read from the FLASH.
 * @note   This interface should be called in QSPI quad mode.
 */
void qFLASH_ReadBufferQ_DMA(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
	QSPI_CommandType QSPI_CmdStructure;
	QSPI_DMAType QSPI_DMAInitStructure = {0};
	DMA_InitType DMA_InitStructure;
	uint32_t sTick = 0;

	/* Check parameters */
	if(!pBuffer || ReadAddr >= qFLASH_SIZE || !NumByteToRead) { return; }

	/* Set command and address */
	QSPI_CmdStructure.Instruction = (uint32_t)qFLASH_CMD_Q_READ;
	QSPI_CmdStructure.AddressLow = ReadAddr;
	/* Configure DMA channel */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_DMA2, ENABLE);
	DMA_DeInit(QSPI_RX_DMA_CH);
	DMA_InitStructure.PeriphAddr		= (uint32_t)&QSPI->DAT0;
	DMA_InitStructure.MemAddr			= (uint32_t)pBuffer;
	DMA_InitStructure.Direction			= DMA_DIR_PERIPH_SRC;
	DMA_InitStructure.BufSize			= NumByteToRead;
	DMA_InitStructure.PeriphInc			= DMA_PERIPH_INC_DISABLE;
	DMA_InitStructure.DMA_MemoryInc		= DMA_MEM_INC_ENABLE;
	DMA_InitStructure.PeriphDataSize	= DMA_PERIPH_DATA_SIZE_BYTE;
	DMA_InitStructure.MemDataSize		= DMA_MEMORY_DATA_SIZE_BYTE;
	DMA_InitStructure.CircularMode		= DMA_MODE_NORMAL;
	DMA_InitStructure.Priority			= DMA_PRIORITY_HIGH;
	DMA_InitStructure.Mem2Mem			= DMA_M2M_DISABLE;
    DMA_Init(QSPI_RX_DMA_CH, &DMA_InitStructure);
    /* Configure QSPI DMA transmit data level */
    QSPI_DMAInitStructure.RDL = 1;
    QSPI_DMAInitStructure.RX_DMA_EN = QSPI_DMA_RX_ENABLE;
	/* Switch to dual mode */
	qFLASH_Init(QSPI_LINE_4_LINES, QSPI_TRANSFER_RX_ONLY, NumByteToRead);
	/* Transmit qual read command and address */
	QSPI_Command(&QSPI_CmdStructure);
	/* Enable DMA transmit */
    QSPI_DMAConfig(&QSPI_DMAInitStructure);
    /* Enable DMA and start transmitting */
    DMA_EnableChannel(QSPI_RX_DMA_CH, ENABLE);
    /* Waiting for QSPI ready */
    sTick = GetSystick();
	while(__QSPI_GET_STS(QSPI_STATUS_BUSY) != RESET && (GetSystick() - sTick) < QSPI_DMA_TIMEOUT_MS);
	/* Restore standard mode */
	qFLASH_Init(QSPI_LINE_STANDARD, QSPI_TRANSFER_TX_AND_RX, 0);
	/* Disable DMA */
    DMA_EnableChannel(QSPI_RX_DMA_CH, DISABLE);
}

/**
 * @brief  Reads FLASH identification.
 * @return FLASH identification
 * @note   This interface should be called in QSPI standard mode.
 */
uint32_t qFLASH_ReadID(void)
{
	uint32_t id = 0;
	uint8_t cmdSeq[] = {qFLASH_CMD_RDID, 0x00, 0x00, 0x00}; /* Read ID command and three dummy bytes */

	/* Clear dirty data in FIFO before read ID bytes */
	QSPI_ClrRxFIFO();
	/* Transmit command sequence. After transmitting, the ID bytes
	 * will be stored in receive FIFO  */
	qFLASH_Command(cmdSeq, 4);
	/* Read ID from receive FIFO */
	qFLASH_Response((uint8_t *)&id, 4);

	return (uint32_t)(REV_BYTE_ORDER_32(id) & 0x00FFFFFF);
}

/**
 * @brief  Reads FLASH status register[S15:S8].
 * @return Contents of status register[S15:S8]
 * @note   This interface should be called in QSPI standard mode.
 */
uint8_t qFLASH_ReadStatus(void)
{
	uint8_t status[] = {0x00, 0x00};
	uint8_t cmdSeq[] = {qFLASH_CMD_RDSR_2nd, 0x00}; /* Read status command and three dummy bytes */

	/* Clear dirty data in FIFO before read status bytes */
	QSPI_ClrRxFIFO();
	/* Read status register */
	qFLASH_Command(cmdSeq, 2);
	qFLASH_Response(status, 2);

	return status[1];
}

/**
 * @brief  Enables the write access to the FLASH.
 * @note   This interface should be called in QSPI standard mode.
 */
void qFLASH_WriteEnable(void)
{
	uint8_t cmd = qFLASH_CMD_WREN;	/* Write enable command */

    /* Transmit "Write Enable" instruction */
	qFLASH_Command(&cmd, 1);
}

/**
 * @brief  Enables the Quad operation to the FLASH.
 * @note   This interface should be called in QSPI standard mode.
 */
void qFLASH_QuadEnable(void)
{
#if qFLASH_DEV == GD25Q32C
	uint8_t cmdSeq[] = {qFLASH_CMD_RDSR_2nd, 0x00};
	uint8_t status[] = {0x00, 0x00};

	/* Clear dirty data in FIFO before read status bytes */
	QSPI_ClrRxFIFO();
	/* Read status register */
	qFLASH_Command(cmdSeq, 2);
	qFLASH_Response(status, 2);
	/* Check QE bit value and enable it if disabled */
	if(!(status[1] & qFLASH_QE_FLAG)){
		cmdSeq[0] = qFLASH_CMD_WRSR_2nd;
		/* Note: The read-modify-write operation may
		 * cause unexpected data to be written into the
		 * register and set Block Protect inadvertently
		 * because the wrong result from the read operation.
		 * This may happen in the case of high frequency. */
		cmdSeq[1] = (status[1] | qFLASH_QE_FLAG);
		/* Enable write */
		qFLASH_WriteEnable();
		/* Enable QE */
		qFLASH_Command(cmdSeq, 2);
		/* Wait for write end */
		qFLASH_WaitForWriteEnd(QFLASH_WSR_TIMEOUT_MS);
	}
#elif qFLASH_DEV == GD25Q40C
	uint8_t cmdSeq[] = {qFLASH_CMD_RDSR_1st, 0x00, 0x00};
	uint8_t status[] = {0x00, 0x00, 0x00};

	/* Clear dirty data in FIFO before read status bytes */
	QSPI_ClrRxFIFO();
	/* Read status register */
	qFLASH_Command(cmdSeq, 3);
	qFLASH_Response(status, 3);
	/* Check QE bit value and enable it if disabled */
	if(!(status[2] & qFLASH_QE_FLAG)){
		cmdSeq[0] = qFLASH_CMD_WRSR_1st;
		cmdSeq[1] = status[1];
		cmdSeq[2] = (status[2] | qFLASH_QE_FLAG);
		/* Enable write */
		qFLASH_WriteEnable();
		/* Enable QE */
		qFLASH_Command(cmdSeq, 3);
		/* Wait for write end */
		qFLASH_WaitForWriteEnd(QFLASH_WSR_TIMEOUT_MS);
	}
#endif
}

/**
 * @brief  Disable the Quad operation to the FLASH.
 */
void qFLASH_QuadDisable(void)
{
#if qFLASH_DEV == GD25Q32C
	uint8_t cmdSeq[] = {qFLASH_CMD_RDSR_2nd, 0x00};
	uint8_t status[] = {0x00, 0x00};

	/* Clear dirty data in FIFO before read status bytes */
	QSPI_ClrRxFIFO();
	/* Read status register */
	qFLASH_Command(cmdSeq, 2);
	qFLASH_Response(status, 2);
	/* Check QE bit value and disable it if enabled */
	if(status[1] & qFLASH_QE_FLAG){
		cmdSeq[0] = qFLASH_CMD_WRSR_2nd;
		cmdSeq[1] = (status[1] & (~qFLASH_QE_FLAG));
		/* Enable write */
		qFLASH_WriteEnable();
		/* Enable QE */
		qFLASH_Command(cmdSeq, 2);
		/* Wait for write end */
		qFLASH_WaitForWriteEnd(QFLASH_WSR_TIMEOUT_MS);
	}
#elif qFLASH_DEV == GD25Q40C
	uint8_t cmdSeq[] = {qFLASH_CMD_RDSR_1st, 0x00, 0x00};
	uint8_t status[] = {0x00, 0x00, 0x00};

	/* Clear dirty data in FIFO before read status bytes */
	QSPI_ClrRxFIFO();
	/* Read status register */
	qFLASH_Command(cmdSeq, 3);
	qFLASH_Response(status, 3);
	/* Check QE bit value and disable it if enabled */
	if(status[2] & qFLASH_QE_FLAG){
		cmdSeq[0] = qFLASH_CMD_WRSR_1st;
		cmdSeq[1] = status[1];
		cmdSeq[2] = (status[2] & (~qFLASH_QE_FLAG));
		/* Enable write */
		qFLASH_WriteEnable();
		/* Enable QE */
		qFLASH_Command(cmdSeq, 3);
		/* Wait for write end */
		qFLASH_WaitForWriteEnd(QFLASH_WSR_TIMEOUT_MS);
	}
#endif
}

/**
 * @brief  Polls the status of the Write In Progress (WIP) flag in the FLASH's
 *         status register and loop until write operation has completed.
 * @note   This interface should be called in QSPI standard mode.
 */
void qFLASH_WaitForWriteEnd(uint32_t timeout)
{
    uint8_t status[] = {0x00, 0x00};
    uint8_t cmdSeq[] = {qFLASH_CMD_RDSR_1st, 0x00}; /* Read status register command and one dummy byte */
    uint32_t sTick = 0;

	/* Clear dirty data in FIFO before read status bytes */
	QSPI_ClrRxFIFO();
    /* Loop as long as the memory is busy with a write cycle */
	sTick = GetSystick();
    do
    {
    	/* Transmit command sequence. After transmitting, the status(S7-S0)
    	 * will be stored in receive FIFO  */
    	qFLASH_Command(cmdSeq, 2);
    	/* Read ID from receive FIFO */
    	qFLASH_Response(status, 2);
    } while ((status[1] & qFLASH_WIP_FLAG) == SET && (GetSystick() - sTick) < timeout); /* Write in progress */
}

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
