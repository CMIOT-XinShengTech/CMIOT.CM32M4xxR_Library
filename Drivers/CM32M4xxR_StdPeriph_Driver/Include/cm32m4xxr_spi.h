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
 * @file cm32m4xxr_spi.h
 * @author CMIOT Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */
#ifndef __CM32M4xxR_SPI_H__
#define __CM32M4xxR_SPI_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup CM32M4xxR_StdPeriph_Driver
 * @{
 */

/** @addtogroup SPI
 * @{
 */

/** @defgroup SPI_Exported_Types SPI Exported Types
 * @{
 */

/**
 * @brief  SPI Init structure definition
 */

typedef struct
{
    uint16_t DataDirection;	/*!< Specifies the SPI unidirectional or bidirectional data mode.
								 This parameter can be a value of @ref SPI_data_direction */

    uint16_t SpiMode;		/*!< Specifies the SPI operating mode.
								 This parameter can be a value of @ref SPI_mode */

    uint16_t DataLen;		/*!< Specifies the SPI data size.
								 This parameter can be a value of @ref SPI_data_size */

    uint16_t CLKPOL;		/*!< Specifies the serial clock steady state.
								 This parameter can be a value of @ref SPI_Clock_Polarity */

    uint16_t CLKPHA;		/*!< Specifies the clock active edge for the bit capture.
								 This parameter can be a value of @ref SPI_Clock_Phase */

    uint16_t NSS;			/*!< Specifies whether the NSS signal is managed by
								 hardware (NSS pin) or by software using the SSI bit.
								 This parameter can be a value of @ref SPI_Slave_Select_management */

    uint16_t BaudRatePres;	/*!< Specifies the Baud Rate prescaler value which will be
								 used to configure the transmit and receive SCK clock.
								 This parameter can be a value of @ref SPI_BaudRate_Prescaler.
								 @note The communication clock is derived from the master
								 clock. The slave clock does not need to be set. */

    uint16_t FirstBit;		/*!< Specifies whether data transfers start from MSB or LSB bit.
								 This parameter can be a value of @ref SPI_MSB_LSB_transmission */

    uint16_t CRCPoly;		/*!< Specifies the polynomial used for the CRC calculation. */
} SPI_InitType;

/**
 * @brief  I2S Init structure definition
 */

typedef struct
{
    uint16_t I2sMode;			/*!< Specifies the I2S operating mode.
									 This parameter can be a value of @ref I2sMode */

    uint16_t Standard;			/*!< Specifies the standard used for the I2S communication.
									 This parameter can be a value of @ref Standard */

    uint16_t DataFormat;		/*!< Specifies the data format for the I2S communication.
									 This parameter can be a value of @ref I2S_Data_Format */

    uint16_t MCLKEnable;		/*!< Specifies whether the I2S MCLK output is enabled or not.
									 This parameter can be a value of @ref I2S_MCLK_Output */

    uint32_t AudioFrequency;	/*!< Specifies the frequency selected for the I2S communication.
									 This parameter can be a value of @ref I2S_Audio_Frequency */

    uint16_t CLKPOL;			/*!< Specifies the idle state of the I2S clock.
									 This parameter can be a value of @ref I2S_Clock_Polarity */
} I2S_InitType;

/**
 * @}
 */

/** @defgroup SPI_Exported_Constants SPI Exported Constants
 * @{
 */

#define IS_SPI_PERIPH(PERIPH)		(((PERIPH) == SPI1) || ((PERIPH) == SPI2) || ((PERIPH) == SPI3))

#define IS_SPI_2OR3_PERIPH(PERIPH)	(((PERIPH) == SPI2) || ((PERIPH) == SPI3))

/** @defgroup SPI_data_direction SPI data direction
 * @{
 */

#define SPI_DIR_DOUBLELINE_FULLDUPLEX	((uint16_t) 0x0000)
#define SPI_DIR_DOUBLELINE_RONLY		((uint16_t) 0x0400)
#define SPI_DIR_SINGLELINE_RX			((uint16_t) 0x8000)
#define SPI_DIR_SINGLELINE_TX			((uint16_t) 0xC000)
#define IS_SPI_DIR_MODE(MODE)			(((MODE) == SPI_DIR_DOUBLELINE_FULLDUPLEX) || ((MODE) == SPI_DIR_DOUBLELINE_RONLY) || \
										 ((MODE) == SPI_DIR_SINGLELINE_RX)         || ((MODE) == SPI_DIR_SINGLELINE_TX))
/**
 * @}
 */

/** @defgroup SPI_mode SPI mode
 * @{
 */

#define SPI_MODE_MASTER		((uint16_t) 0x0104)
#define SPI_MODE_SLAVE		((uint16_t) 0x0000)
#define IS_SPI_MODE(MODE)	(((MODE) == SPI_MODE_MASTER) || ((MODE) == SPI_MODE_SLAVE))
/**
 * @}
 */

/** @defgroup SPI_data_size SPI data size
 * @{
 */

#define SPI_DATA_SIZE_16BITS		((uint16_t) 0x0800)
#define SPI_DATA_SIZE_8BITS			((uint16_t) 0x0000)
#define IS_SPI_DATASIZE(DATASIZE)	(((DATASIZE) == SPI_DATA_SIZE_16BITS) || ((DATASIZE) == SPI_DATA_SIZE_8BITS))
/**
 * @}
 */

/** @defgroup SPI_Clock_Polarity SPI Clock Polarity
 * @{
 */

#define SPI_CLKPOL_LOW		((uint16_t) 0x0000)
#define SPI_CLKPOL_HIGH		((uint16_t) 0x0002)
#define IS_SPI_CLKPOL(CPOL)	(((CPOL) == SPI_CLKPOL_LOW) || ((CPOL) == SPI_CLKPOL_HIGH))
/**
 * @}
 */

/** @defgroup SPI_Clock_Phase SPI Clock Phase
 * @{
 */

#define SPI_CLKPHA_FIRST_EDGE	((uint16_t) 0x0000)
#define SPI_CLKPHA_SECOND_EDGE	((uint16_t) 0x0001)
#define IS_SPI_CLKPHA(CPHA)		(((CPHA) == SPI_CLKPHA_FIRST_EDGE) || ((CPHA) == SPI_CLKPHA_SECOND_EDGE))
/**
 * @}
 */

/** @defgroup SPI_Slave_Select_management SPI Slave Select management
 * @{
 */

#define SPI_NSS_SOFT	((uint16_t) 0x0200)
#define SPI_NSS_HARD	((uint16_t) 0x0000)
#define IS_SPI_NSS(NSS)	(((NSS) == SPI_NSS_SOFT) || ((NSS) == SPI_NSS_HARD))
/**
 * @}
 */

/** @defgroup SPI_BaudRate_Prescaler SPI BaudRate Prescaler
 * @{
 */

#define SPI_BR_PRESCALER_2				((uint16_t) 0x0000)
#define SPI_BR_PRESCALER_4				((uint16_t) 0x0008)
#define SPI_BR_PRESCALER_8				((uint16_t) 0x0010)
#define SPI_BR_PRESCALER_16				((uint16_t) 0x0018)
#define SPI_BR_PRESCALER_32				((uint16_t) 0x0020)
#define SPI_BR_PRESCALER_64				((uint16_t) 0x0028)
#define SPI_BR_PRESCALER_128			((uint16_t) 0x0030)
#define SPI_BR_PRESCALER_256			((uint16_t) 0x0038)
#define IS_SPI_BR_PRESCALER(PRESCALER)	(((PRESCALER) == SPI_BR_PRESCALER_2)   || ((PRESCALER) == SPI_BR_PRESCALER_4)  || \
										 ((PRESCALER) == SPI_BR_PRESCALER_8)   || ((PRESCALER) == SPI_BR_PRESCALER_16) || \
										 ((PRESCALER) == SPI_BR_PRESCALER_32)  || ((PRESCALER) == SPI_BR_PRESCALER_64) || \
										 ((PRESCALER) == SPI_BR_PRESCALER_128) || ((PRESCALER) == SPI_BR_PRESCALER_256))
/**
 * @}
 */

/** @defgroup SPI_MSB_LSB_transmission SPI MSB LSB transmission
 * @{
 */

#define SPI_FB_MSB				((uint16_t) 0x0000)
#define SPI_FB_LSB				((uint16_t) 0x0080)
#define IS_SPI_FIRST_BIT(BIT)	(((BIT) == SPI_FB_MSB) || ((BIT) == SPI_FB_LSB))
/**
 * @}
 */

/** @defgroup I2sMode I2sMode
 * @{
 */

#define I2S_MODE_SlAVE_TX 	((uint16_t) 0x0000)
#define I2S_MODE_SlAVE_RX 	((uint16_t) 0x0100)
#define I2S_MODE_MASTER_TX	((uint16_t) 0x0200)
#define I2S_MODE_MASTER_RX	((uint16_t) 0x0300)
#define IS_I2S_MODE(MODE)	(((MODE) == I2S_MODE_SlAVE_TX)  || ((MODE) == I2S_MODE_SlAVE_RX) || \
							 ((MODE) == I2S_MODE_MASTER_TX) || ((MODE) == I2S_MODE_MASTER_RX))
/**
 * @}
 */

/** @defgroup Standard Standard
 * @{
 */

#define I2S_STD_PHILLIPS      		((uint16_t) 0x0000)
#define I2S_STD_MSB_ALIGN     		((uint16_t) 0x0010)
#define I2S_STD_LSB_ALIGN     		((uint16_t) 0x0020)
#define I2S_STD_PCM_SHORTFRAME		((uint16_t) 0x0030)
#define I2S_STD_PCM_LONGFRAME 		((uint16_t) 0x00B0)
#define IS_I2S_STANDARD(STANDARD)	(((STANDARD) == I2S_STD_PHILLIPS)  || ((STANDARD) == I2S_STD_MSB_ALIGN)      || \
									 ((STANDARD) == I2S_STD_LSB_ALIGN) || ((STANDARD) == I2S_STD_PCM_SHORTFRAME) || \
									 ((STANDARD) == I2S_STD_PCM_LONGFRAME))
/**
 * @}
 */

/** @defgroup I2S_Data_Format I2S Data Format
 * @{
 */

#define I2S_DATA_FMT_16BITS         	((uint16_t) 0x0000)
#define I2S_DATA_FMT_16BITS_EXTENDED	((uint16_t) 0x0001)
#define I2S_DATA_FMT_24BITS         	((uint16_t) 0x0003)
#define I2S_DATA_FMT_32BITS         	((uint16_t) 0x0005)
#define IS_I2S_DATA_FMT(FORMAT)			(((FORMAT) == I2S_DATA_FMT_16BITS) || ((FORMAT) == I2S_DATA_FMT_16BITS_EXTENDED) || \
										 ((FORMAT) == I2S_DATA_FMT_24BITS) || ((FORMAT) == I2S_DATA_FMT_32BITS))
/**
 * @}
 */

/** @defgroup I2S_MCLK_Output I2S MCLK Output
 * @{
 */

#define I2S_MCLK_ENABLE				((uint16_t) 0x0200)
#define I2S_MCLK_DISABLE			((uint16_t) 0x0000)
#define IS_I2S_MCLK_ENABLE(OUTPUT)	(((OUTPUT) == I2S_MCLK_ENABLE) || ((OUTPUT) == I2S_MCLK_DISABLE))
/**
 * @}
 */

/** @defgroup I2S_Audio_Frequency I2S Audio Frequency
 * @{
 */

#define I2S_AUDIO_FREQ_96K    	((uint32_t) 96000)
#define I2S_AUDIO_FREQ_48K    	((uint32_t) 48000)
#define I2S_AUDIO_FREQ_44K    	((uint32_t) 44100)
#define I2S_AUDIO_FREQ_32K    	((uint32_t) 32000)
#define I2S_AUDIO_FREQ_22K    	((uint32_t) 22050)
#define I2S_AUDIO_FREQ_16K    	((uint32_t) 16000)
#define I2S_AUDIO_FREQ_11K    	((uint32_t) 11025)
#define I2S_AUDIO_FREQ_8K     	((uint32_t) 8000)
#define I2S_AUDIO_FREQ_DEFAULT	((uint32_t) 2)

#define IS_I2S_AUDIO_FREQ(FREQ)	((((FREQ) >= I2S_AUDIO_FREQ_8K) && ((FREQ) <= I2S_AUDIO_FREQ_96K)) || ((FREQ) == I2S_AUDIO_FREQ_DEFAULT))
/**
 * @}
 */

/** @defgroup I2S_Clock_Polarity I2S Clock Polarity
 * @{
 */

#define I2S_CLKPOL_LOW		((uint16_t) 0x0000)
#define I2S_CLKPOL_HIGH		((uint16_t) 0x0008)
#define IS_I2S_CLKPOL(CPOL)	(((CPOL) == I2S_CLKPOL_LOW) || ((CPOL) == I2S_CLKPOL_HIGH))
/**
 * @}
 */

/** @defgroup SPI_I2S_DMA_transfer_requests SPI I2S DMA transfer requests
 * @{
 */

#define SPI_I2S_DMA_TX			((uint16_t) 0x0002)
#define SPI_I2S_DMA_RX			((uint16_t) 0x0001)
#define IS_SPI_I2S_DMA(DMAREQ)	((((DMAREQ) & (uint16_t)0xFFFC) == 0x00) && ((DMAREQ) != 0x00))
/**
 * @}
 */

/** @defgroup SPI_NSS_internal_software_management SPI NSS internal software management
 * @{
 */

#define SPI_NSS_HIGH				((uint16_t) 0x0100)
#define SPI_NSS_LOW					((uint16_t) 0xFEFF)
#define IS_SPI_NSS_LEVEL(INTERNAL)	(((INTERNAL) == SPI_NSS_HIGH) || ((INTERNAL) == SPI_NSS_LOW))
/**
 * @}
 */

/** @defgroup SPI_CRC_Transmit_Receive SPI CRC Transmit Receive
 * @{
 */

#define SPI_CRC_TX      ((uint8_t) 0x00)
#define SPI_CRC_RX      ((uint8_t) 0x01)
#define IS_SPI_CRC(CRC)	(((CRC) == SPI_CRC_TX) || ((CRC) == SPI_CRC_RX))
/**
 * @}
 */

/** @defgroup SPI_direction_transmit_receive SPI direction transmit receive
 * @{
 */

#define SPI_BIDIRECTION_RX				((uint16_t) 0xBFFF)
#define SPI_BIDIRECTION_TX				((uint16_t) 0x4000)
#define IS_SPI_BIDIRECTION(DIRECTION)	(((DIRECTION) == SPI_BIDIRECTION_RX) || ((DIRECTION) == SPI_BIDIRECTION_TX))
/**
 * @}
 */

/** @defgroup SPI_I2S_interrupts_definition SPI I2S interrupts definition
 * @{
 */
/* higher 4bit uesd to set CTRL2 register, lower 4bit used to get the status in STS register */
#define SPI_I2S_INT_TE				((uint8_t) 0x71)
#define SPI_I2S_INT_RNE				((uint8_t) 0x60)
#define SPI_I2S_INT_ERR				((uint8_t) 0x50)
#define IS_SPI_I2S_CONFIG_INT(IT)	(((IT) == SPI_I2S_INT_TE) || ((IT) == SPI_I2S_INT_RNE) || ((IT) == SPI_I2S_INT_ERR))
#define SPI_I2S_INT_OVER			((uint8_t) 0x56)
#define SPI_INT_MODERR				((uint8_t) 0x55)
#define SPI_INT_CRCERR				((uint8_t) 0x54)
#define I2S_INT_UNDER				((uint8_t) 0x53)
#define IS_SPI_I2S_CLR_INT(IT)		(((IT) == SPI_INT_CRCERR))
#define IS_SPI_I2S_GET_INT(IT)		(((IT) == SPI_I2S_INT_RNE) || ((IT) == SPI_I2S_INT_TE) || ((IT) == I2S_INT_UNDER) || \
									 ((IT) == SPI_INT_CRCERR)  || ((IT) == SPI_INT_MODERR) || ((IT) == SPI_I2S_INT_OVER))
/**
 * @}
 */

/** @defgroup SPI_I2S_flags_definition SPI I2S flags definition
 * @{
 */

#define SPI_I2S_RNE_FLAG 			((uint16_t) 0x0001)
#define SPI_I2S_TE_FLAG  			((uint16_t) 0x0002)
#define I2S_CHSIDE_FLAG  			((uint16_t) 0x0004)
#define I2S_UNDER_FLAG   			((uint16_t) 0x0008)
#define SPI_CRCERR_FLAG  			((uint16_t) 0x0010)
#define SPI_MODERR_FLAG  			((uint16_t) 0x0020)
#define SPI_I2S_OVER_FLAG			((uint16_t) 0x0040)
#define SPI_I2S_BUSY_FLAG			((uint16_t) 0x0080)
#define IS_SPI_I2S_CLR_FLAG(FLAG)	(((FLAG) == SPI_CRCERR_FLAG))
#define IS_SPI_I2S_GET_FLAG(FLAG)	(((FLAG) == SPI_I2S_BUSY_FLAG) || ((FLAG) == SPI_I2S_OVER_FLAG) || ((FLAG) == SPI_MODERR_FLAG) || \
									 ((FLAG) == SPI_CRCERR_FLAG)   || ((FLAG) == I2S_UNDER_FLAG)    || ((FLAG) == I2S_CHSIDE_FLAG) || \
									 ((FLAG) == SPI_I2S_TE_FLAG)   || ((FLAG) == SPI_I2S_RNE_FLAG))
/**
 * @}
 */

/** @defgroup SPI_CRC_polynomial SPI CRC polynomial
 * @{
 */

#define IS_SPI_CRC_POLYNOMIAL(POLYNOMIAL)	((POLYNOMIAL) >= 0x1)
/**
 * @}
 */

/**
 * @}
 */

/** @addtogroup SPI_Exported_Functions
 * @{
 */

void		SPI_I2S_DeInit (SPI_Module* SPIx);
void		SPI_Init (SPI_Module* SPIx, SPI_InitType* SPI_InitStruct);
void		I2S_Init (SPI_Module* SPIx, I2S_InitType* I2S_InitStruct);
void		SPI_InitStruct (SPI_InitType* SPI_InitStruct);
void		I2S_InitStruct (I2S_InitType* I2S_InitStruct);
void		SPI_Enable (SPI_Module* SPIx, FunctionalState Cmd);
void		I2S_Enable (SPI_Module* SPIx, FunctionalState Cmd);
void		SPI_I2S_EnableInt (SPI_Module* SPIx, uint8_t SPI_I2S_IT, FunctionalState Cmd);
void		SPI_I2S_EnableDma (SPI_Module* SPIx, uint16_t SPI_I2S_DMAReq, FunctionalState Cmd);
void		SPI_I2S_TransmitData (SPI_Module* SPIx, uint16_t Data);
uint16_t	SPI_I2S_ReceiveData (SPI_Module* SPIx);
void		SPI_SetNssLevel (SPI_Module* SPIx, uint16_t SPI_NSSInternalSoft);
void		SPI_SSOutputEnable (SPI_Module* SPIx, FunctionalState Cmd);
void		SPI_ConfigDataLen (SPI_Module* SPIx, uint16_t DataLen);
void		SPI_TransmitCrcNext (SPI_Module* SPIx);
void		SPI_EnableCalculateCrc (SPI_Module* SPIx, FunctionalState Cmd);
uint16_t	SPI_GetCRCDat (SPI_Module* SPIx, uint8_t SPI_CRC);
uint16_t	SPI_GetCRCPoly (SPI_Module* SPIx);
void		SPI_ConfigBidirectionalMode (SPI_Module* SPIx, uint16_t DataDirection);
FlagStatus	SPI_I2S_GetStatus (SPI_Module* SPIx, uint16_t SPI_I2S_FLAG);
void		SPI_I2S_ClrCRCErrFlag (SPI_Module* SPIx, uint16_t SPI_I2S_FLAG);
INTStatus	SPI_I2S_GetIntStatus (SPI_Module* SPIx, uint8_t SPI_I2S_IT);
/**
 * @}
 */

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

/**
 * @}
 */
#endif /*__CM32M4xxR_SPI_H__ */
