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
 * @file cm32m4xxr_qspi.h
 * @author CMIOT Firmware Team
 * @brief Header file containing functions prototypes of QSPI StdPeriph Library.
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CM32M4xxR_QSPI_H__
#define __CM32M4xxR_QSPI_H__

/* Includes ------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup CM32M4xxR_StdPeriph_Driver
  * @{
  */

/** @addtogroup QSPI
  * @{
  */


/* Exported types ------------------------------------------------------------*/
/** @defgroup QSPI_Exported_Types QSPI Exported Types
  * @{
  */

/**
  * @brief  QSPI Enhanced Initialization Structure definition
  */
typedef struct
{
	uint32_t		InstLen;		/*!< Specifies instruction length in Dual/Quad mode in bits.
	 	 	 	 	 	 	 	 	 	 This parameter can be a value of @ref QSPI_InstLen						*/
	uint32_t		AddrLen;		/*!< Specifies the length of address to transmit.
	 	 	 	 	 	 	 	 	 	 This parameter can be a value of @ref QSPI_AddrLen						*/
	uint32_t		WaitCycles;		/*!< Specifies wait cycles in Dual/Quad mode between control frames
	 	 	 	 	 	 	 	 	 	 transmit and data reception.
	 	 	 	 	 	 	 	 	 	 This parameter can be a value of @ref QSPI_WaitCycles					*/
	uint32_t		TransferType;	/*!< Specifies address and instruction transfer format.
	 	 	 	 	 	 	 	 	 	 This parameter can be a value of @ref QSPI_TransferType				*/
	FunctionalState	ClkStretch;		/*!< Enable or disable clock stretch in SPI transfer.
	 	 	 	 	 	 	 	 	 	 This parameter can be ENABLE or DISABLE								*/
	/* XIP configuration */
	FunctionalState	XIP_CT_EN;		/*!< Enable or disable continuous transfer in XIP mode.
	 	 	 	 	 	 	 	 	 	 This parameter can be ENABLE or DISABLE								*/
	FunctionalState XIP_INST_EN;	/*!< Enable or disable instruction in XIP mode.
	 	 	 	 	 	 	 	 	 	 This parameter can be ENABLE or DISABLE								*/
	FunctionalState XIP_DFS_HC;		/*!< Enable or disable fixed data frame size for XIP transfer.
	 	 	 	 	 	 	 	 	 	 This parameter can be ENABLE or DISABLE								*/
	FunctionalState INST_DDR_EN;	/*!< Enable or disable instruction DDR.
	 	 	 	 	 	 	 	 	 	 This parameter can be ENABLE or DISABLE								*/
	FunctionalState SPI_DDR_EN;		/*!< Enable or disable SPI DDR.
	 	 	 	 	 	 	 	 	 	 This parameter can be ENABLE or DISABLE								*/
	FunctionalState MD_BIT_EN;		/*!< Enable or disable mode bit in XIP mode.
	 	 	 	 	 	 	 	 	 	 This parameter can be ENABLE or DISABLE								*/
	uint32_t		XIP_MBL;		/*!< Specifies the XIP mode bits length.
										 @note This parameter only works when MD_BIT_EN is ENABLE.
	 	 	 	 	 	 	 	 	 	 This parameter can be a value of @ref QSPI_XIP_MBL						*/
	uint16_t		XIP_MODE_BITS;	/*!< Specifies XIP mode bits to be sent after address phase of XIP transfer.
										 @note This parameter only works when MD_BIT_EN is ENABLE.
	 	 	 	 	 	 	 	 	 	 This parameter can be a value between 0x0 and 0xFFFF					*/
	uint16_t		ITOC;			/*!< Specifies XIP INCR transfer operation code.
	 	 	 	 	 	 	 	 	 	 @note This parameter only works when XIP_INS_EN is ENABLE.
	 	 	 	 	 	 	 	 	 	 This parameter can be a value between 0x0 and 0xFFFF					*/
	uint16_t		WTOC;			/*!< Specifies XIP WRAP transfer operation code.
	 	 	 	 	 	 	 	 	 	 @note This parameter only works when XIP_INS_EN is ENABLE.
	 	 	 	 	 	 	 	 	 	 This parameter can be a value between 0x0 and 0xFFFF					*/

}QSPI_ENHInitType;

/**
  * @brief  QSPI Initialization Structure definition
  */
typedef struct
{
	uint32_t			LineMode;		/*!< Specifies the line mode.
	 	 	 	 	 	 	 	 	 	 	 This parameter can be a value of @ref QSPI_LineMode						*/
	uint32_t			TransferMode;	/*!< Specifies the transfer mode.
								 	 	 	 This parameter can be a value of @ref QSPI_TransferMode					*/
	uint32_t			CLKPOL;			/*!< Specifies the serial clock steady state.
								 	 	 	 This parameter can be a value of @ref QSPI_ClockPolarity					*/
	uint32_t			CLKPHA;			/*!< Specifies the clock active edge for the bit capture.
								 	 	 	 This parameter can be a value of @ref QSPI_ClockPhase						*/
	uint32_t			FrameFormat;	/*!< Specifies the frame format.
	 	 	 	 	 	 	 	 	 	 	 This parameter can be a value of @ref QSPI_FrameFormat						*/
	uint32_t			CFS;			/*!< Specifies the control frame size.
	 	 	 	 	 	 	 	 	 	 	 This parameter can be a value of @ref QSPI_ControlFrameSize.
	 	 	 	 	 	 	 	 	 	 	 @note This parameter only works when FrameFormat is QSPI_FRF_MICROWIRE		*/
	uint32_t			DFS;			/*!< Specifies data frame size.
	 	 	 	 	 	 	 	 	 	 	 This parameter can be a value of @ref QSPI_DataFrameSize					*/
	FunctionalState 	SSTE;			/*!< Enable or disable slave select toggle enable.
	 	 	 	 	 	 	 	 	 	 	 This parameter can be ENABLE or DISABLE									*/
    uint16_t			ClkDiv;			/*!< Specifies the clock divider value which will be
								 	 	 	 used to configure the transmit and receive SCK clock.
								 	 	 	 This parameter can be a value of even number between 0 and 65535, if chose 0,
								 	 	 	 the serial clock output is disabled.
								 	 	 	 	 - sck = hclk / ClkDiv.													*/
	uint16_t			RxDataNr;		/*!< Specifies the number of consecutively received data frames.
	 	 	 	 	 	 	 	 	 	 	 @note This parameter only works in QSPI_TRANSFER_RX_ONLY and
	 	 	 	 	 	 	 	 	 	 	 QSPI_TRANSFER_EEPROM_READ mode.
	 	 	 	 	 	 	 	 	 	 	 This parameter can be a value from 0 to 65535 								*/
    QSPI_ENHInitType	Enhance;		/*!< Specifies enhanced QSPI configuration.										*/
}QSPI_InitType;

/**
  * @brief  QSPI Command structure definition
  */
typedef struct
{
	uint32_t Instruction;	/*!< Specifies the Instruction to be sent(Size form 0 to 16 bits according InstLen or CFS).
                                 This parameter can be a value between 0x0000 and 0xFFFF(align right)						*/
	uint32_t AddressLow;	/*!< Specifies the Low Word of Address to be sent (Size from 0 to 32 bits according AddrLen).
                                 This parameter can be a value between 0x0 and 0xFFFFFFFF(align right)						*/
	uint32_t AddressHigh;	/*!< Specifies the High Word of Address to be sent (Size from 0 to 28 bits according AddrLen).
                                 This parameter can be a value between 0x0 and 0x0FFFFFFF(align right)						*/
}QSPI_CommandType;

/**
  * @brief  QSPI DMA configuration structure definition
  */
typedef struct
{
	uint8_t	TX_DMA_EN;	/*!< Enable or Disable DMA Transmit.
	 	 	 	 	 	 	 This parameter can be a value of @ref QSPI_DMATxEnable */
	uint8_t	RX_DMA_EN;	/*!< Enable or Disable DMA Receive.
	 	 	 	 	 	 	 This parameter can be a value of @ref QSPI_DMARxEnable */
	uint8_t	TDL;		/*!< DMA Transmit Data Level.
	 	 	 	 	 	 	 This parameter can be a value between 1 and 32			*/
	uint8_t	RDL;		/*!< DMA Receive Data Level.
	 	 	 	 	 	 	 This parameter can be a value between 1 and 32			*/
}QSPI_DMAType;

/**
  * @brief  QSPI Microwire configuration structure definition
  */
typedef struct
{
	uint8_t MHS_EN;		/*!< Enable or Disable Micro handshaking.
	 	 	 	 	 	 	 This parameter can be a value of @ref QSPI_MicrowireHs		*/
	uint8_t MC_DIR;		/*!< Specifies the direction of data when microwire control.
	 	 	 	 	 	 	 This parameter can be a value of @ref QSPI_MicrowireDir	*/
	uint8_t MWMOD;		/*!< Specifies microwire transfer mode.
	 	 	 	 	 	 	 This parameter can be a value of @ref QSPI_MicrowireMode	*/
}QSPI_MicrowireType;

/**
  * @brief  QSPI port selection enumeration definition. Using NSS port to indicate the I/Os group.
  */
typedef enum
{
    QSPI_NSS_PORTA = 0,	/*!< NSS->PA4, CLK->PA5, IO0->PA6, IO1->PA7, IO2->PC4, IO3->PC5 	*/
    QSPI_NSS_PORTC = 1,	/*!< NSS->PC10, CLK->PC11, IO0->PC12, IO1->PD0, IO2->PD1, IO3->PD2	*/
    QSPI_NSS_PORTF = 2	/*!< NSS->PF0, CLK->PF1, IO0->PF2, IO1->PF3, IO2->PF4, IO3->PF5 	*/
} QSPI_PortSelType;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup QSPI_Exported_Constants QSPI Exported Constants
  * @{
  */

/** @defgroup QSPI_LineMode QSPI Line Mode
  * @{
  */
/* Note: These macros are used to set register QSPI_CTRL0 and QSPI_XIP_CTRL
 *       and need to be shifted left before setting */
/* Standard mode */
#define QSPI_LINE_STANDARD			((uint32_t) 0x00000000)	/*!< Standard SPI 			*/
/* Enhanced mode */
#define QSPI_LINE_2_LINES			((uint32_t) 0x00000001)	/*!< Dual SPI 				*/
#define QSPI_LINE_4_LINES			((uint32_t) 0x00000002)	/*!< Quad SPI 				*/
/* XIP mode */
#define QSPI_LINE_2_LINES_XIP		((uint32_t) 0x00000004)	/*!< Dual SPI in XIP mode	*/
#define QSPI_LINE_4_LINES_XIP		((uint32_t) 0x00000008)	/*!< Quad SPI in XIP mode 	*/

/**
 * @}
 */

/** @defgroup QSPI_TransferMode QSPI Transfer Mode
  * @{
  */
#define QSPI_TRANSFER_TX_AND_RX			((uint32_t) 0x00000000)	/*!< Transmit and receive	*/
#define QSPI_TRANSFER_TX_ONLY			((uint32_t) 0x00000400)	/*!< Transmit only			*/
#define QSPI_TRANSFER_RX_ONLY			((uint32_t) 0x00000800)	/*!< Receive only			*/
#define QSPI_TRANSFER_EEPROM_READ		((uint32_t) 0x00000C00)	/*!< EEPROM read			*/
/**
  * @}
  */

/** @defgroup QSPI_ClockPolarity QSPI Clock Polarity
  * @{
  */
#define QSPI_CLKPOL_LOW				((uint32_t) 0x00000000)	/*!< Serial clock steady state low	*/
#define QSPI_CLKPOL_HIGH			((uint32_t) 0x00000200)	/*!< Serial clock steady state high	*/
/**
  * @}
  */

/** @defgroup QSPI_ClockPhase QSPI Clock Phase
  * @{
  */
#define QSPI_CLKPHA_FIRST_EDGE		((uint32_t) 0x00000000)	/*!< Capture bit at first serial clock edge		*/
#define QSPI_CLKPHA_SECOND_EDGE		((uint32_t) 0x00000100)	/*!< Capture bit at second serial clock edge	*/
/**
  * @}
  */

/** @defgroup QSPI_FrameFormat QSPI Frame Format
  * @{
  */
#define QSPI_FRF_SPI				((uint32_t) 0x00000000)	/*!< Motorola SPI frame format						*/
#define QSPI_FRF_SSP				((uint32_t) 0x00000040)	/*!< TI SSP frame format							*/
#define QSPI_FRF_MICROWIRE			((uint32_t) 0x00000080) /*!< NS Microwire frame format						*/
/**
  * @}
  */

/** @defgroup QSPI_ControlFrameSize QSPI Control Frame Size
  * @{
  */
#define QSPI_CFS_1_BIT				((uint32_t) 0x00000000)	/*!< 1 bit control frame for Microwire frame format */
#define QSPI_CFS_2_BITS				((uint32_t) 0x00010000)
#define QSPI_CFS_3_BITS				((uint32_t) 0x00020000)
#define QSPI_CFS_4_BITS				((uint32_t) 0x00030000)
#define QSPI_CFS_5_BITS				((uint32_t) 0x00040000)
#define QSPI_CFS_6_BITS				((uint32_t) 0x00050000)
#define QSPI_CFS_7_BITS				((uint32_t) 0x00060000)
#define QSPI_CFS_8_BITS				((uint32_t) 0x00070000)
#define QSPI_CFS_9_BITS				((uint32_t) 0x00080000)
#define QSPI_CFS_10_BITS			((uint32_t) 0x00090000)
#define QSPI_CFS_11_BITS			((uint32_t) 0x000A0000)
#define QSPI_CFS_12_BITS			((uint32_t) 0x000B0000)
#define QSPI_CFS_13_BITS			((uint32_t) 0x000C0000)
#define QSPI_CFS_14_BITS			((uint32_t) 0x000D0000)
#define QSPI_CFS_15_BITS			((uint32_t) 0x000E0000)
#define QSPI_CFS_16_BITS			((uint32_t) 0x000F0000)
/**
  * @}
  */

/** @defgroup QSPI_DataFrameSize QSPI Data Frame Size
  * @{
  */
#define QSPI_DFS_4_BITS				((uint32_t) 0x00000003)	/*!< 4 bits data frame */
#define QSPI_DFS_5_BITS				((uint32_t) 0x00000004)
#define QSPI_DFS_6_BITS				((uint32_t) 0x00000005)
#define QSPI_DFS_7_BITS				((uint32_t) 0x00000006)
#define QSPI_DFS_8_BITS				((uint32_t) 0x00000007)
#define QSPI_DFS_9_BITS				((uint32_t) 0x00000008)
#define QSPI_DFS_10_BITS			((uint32_t) 0x00000009)
#define QSPI_DFS_11_BITS			((uint32_t) 0x0000000A)
#define QSPI_DFS_12_BITS			((uint32_t) 0x0000000B)
#define QSPI_DFS_13_BITS			((uint32_t) 0x0000000C)
#define QSPI_DFS_14_BITS			((uint32_t) 0x0000000D)
#define QSPI_DFS_15_BITS			((uint32_t) 0x0000000E)
#define QSPI_DFS_16_BITS			((uint32_t) 0x0000000F)
#define QSPI_DFS_17_BITS			((uint32_t) 0x00000010)
#define QSPI_DFS_18_BITS			((uint32_t) 0x00000011)
#define QSPI_DFS_19_BITS			((uint32_t) 0x00000012)
#define QSPI_DFS_20_BITS			((uint32_t) 0x00000013)
#define QSPI_DFS_21_BITS			((uint32_t) 0x00000014)
#define QSPI_DFS_22_BITS			((uint32_t) 0x00000015)
#define QSPI_DFS_23_BITS			((uint32_t) 0x00000016)
#define QSPI_DFS_24_BITS			((uint32_t) 0x00000017)
#define QSPI_DFS_25_BITS			((uint32_t) 0x00000018)
#define QSPI_DFS_26_BITS			((uint32_t) 0x00000019)
#define QSPI_DFS_27_BITS			((uint32_t) 0x0000001A)
#define QSPI_DFS_28_BITS			((uint32_t) 0x0000001B)
#define QSPI_DFS_29_BITS			((uint32_t) 0x0000001C)
#define QSPI_DFS_30_BITS			((uint32_t) 0x0000001D)
#define QSPI_DFS_31_BITS			((uint32_t) 0x0000001E)
#define QSPI_DFS_32_BITS			((uint32_t) 0x0000001F)
/**
  * @}
  */

/** @defgroup QSPI_XIP_MBL QSPI XIP Mode Bits Length
  * @{
  */
/* Note: These macros are used to set register QSPI_ENH_CTRL0 and QSPI_XIP_CTRL */
#define QSPI_XIP_MBL_2_BITS			((uint32_t) 0x00000000)	/*!< 2 bits XIP Mode */
#define QSPI_XIP_MBL_4_BITS			((uint32_t) 0x04000000)
#define QSPI_XIP_MBL_8_BITS			((uint32_t) 0x08000000)
#define QSPI_XIP_MBL_16_BITS		((uint32_t) 0x0C000000)
/**
  * @}
  */

/** @defgroup QSPI_WaitCycles QSPI Wait Cycles
  * @{
  */
/* Note: These macros are used to set register QSPI_ENH_CTRL0 and QSPI_XIP_CTRL
 *       and need to be shifted left before setting */
#define QSPI_WAIT_NONE				((uint32_t) 0x00)	/*!< No wait cycle between control frames transmit and data reception in Dual/Quad mode 	*/
#define QSPI_WAIT_1_CYCLE			((uint32_t) 0x01)	/*!< One wait cycle between control frames transmit and data reception in Dual/Quad mode	*/
#define QSPI_WAIT_2_CYCLES			((uint32_t) 0x02)
#define QSPI_WAIT_3_CYCLES			((uint32_t) 0x03)
#define QSPI_WAIT_4_CYCLES			((uint32_t) 0x04)
#define QSPI_WAIT_5_CYCLES			((uint32_t) 0x05)
#define QSPI_WAIT_6_CYCLES			((uint32_t) 0x06)
#define QSPI_WAIT_7_CYCLES			((uint32_t) 0x07)
#define QSPI_WAIT_8_CYCLES			((uint32_t) 0x08)
#define QSPI_WAIT_9_CYCLES			((uint32_t) 0x09)
#define QSPI_WAIT_10_CYCLES			((uint32_t) 0x0A)
#define QSPI_WAIT_11_CYCLES			((uint32_t) 0x0B)
#define QSPI_WAIT_12_CYCLES			((uint32_t) 0x0C)
#define QSPI_WAIT_13_CYCLES			((uint32_t) 0x0D)
#define QSPI_WAIT_14_CYCLES			((uint32_t) 0x0E)
#define QSPI_WAIT_15_CYCLES			((uint32_t) 0x0F)
#define QSPI_WAIT_16_CYCLES			((uint32_t) 0x10)
#define QSPI_WAIT_17_CYCLES			((uint32_t) 0x11)
#define QSPI_WAIT_18_CYCLES			((uint32_t) 0x12)
#define QSPI_WAIT_19_CYCLES			((uint32_t) 0x13)
#define QSPI_WAIT_20_CYCLES			((uint32_t) 0x14)
#define QSPI_WAIT_21_CYCLES			((uint32_t) 0x15)
#define QSPI_WAIT_22_CYCLES			((uint32_t) 0x16)
#define QSPI_WAIT_23_CYCLES			((uint32_t) 0x17)
#define QSPI_WAIT_24_CYCLES			((uint32_t) 0x18)
#define QSPI_WAIT_25_CYCLES			((uint32_t) 0x19)
#define QSPI_WAIT_26_CYCLES			((uint32_t) 0x1A)
#define QSPI_WAIT_27_CYCLES			((uint32_t) 0x1B)
#define QSPI_WAIT_28_CYCLES			((uint32_t) 0x1C)
#define QSPI_WAIT_29_CYCLES			((uint32_t) 0x1D)
#define QSPI_WAIT_30_CYCLES			((uint32_t) 0x1E)
#define QSPI_WAIT_31_CYCLES			((uint32_t) 0x1F)
/**
  * @}
  */

/** @defgroup QSPI_InstLen QSPI Instruction Length
  * @{
  */
/* Note: These macros are used to set register QSPI_ENH_CTRL0 and QSPI_XIP_CTRL
 *       and need to be shifted left before setting */
#define QSPI_INST_NONE				((uint32_t) 0x00)	/*!< No instruction in Dual/Quad mode		*/
#define QSPI_INST_4_BITS			((uint32_t) 0x01)	/*!< 4 bits instruction in Dual/Quad mode	*/
#define QSPI_INST_8_BITS			((uint32_t) 0x02)
#define QSPI_INST_16_BITS			((uint32_t) 0x03)
/**
  * @}
  */

/** @defgroup QSPI_AddrLen QSPI Address Length
  * @{
  */
/* Note: These macros are used to set register QSPI_ENH_CTRL0 and QSPI_XIP_CTRL
 *       and need to be shifted left before setting */
#define QSPI_ADDR_NONE				((uint32_t) 0x00)	/*!< No address in Dual/Quad mode		*/
#define QSPI_ADDR_4_BITS			((uint32_t) 0x01)	/*!< 4 bit address in Dual/Quad mode	*/
#define QSPI_ADDR_8_BITS			((uint32_t) 0x02)
#define QSPI_ADDR_12_BITS			((uint32_t) 0x03)
#define QSPI_ADDR_16_BITS			((uint32_t) 0x04)
#define QSPI_ADDR_20_BITS			((uint32_t) 0x05)
#define QSPI_ADDR_24_BITS			((uint32_t) 0x06)
#define QSPI_ADDR_28_BITS			((uint32_t) 0x07)
#define QSPI_ADDR_32_BITS			((uint32_t) 0x08)
#define QSPI_ADDR_36_BITS			((uint32_t) 0x09)
#define QSPI_ADDR_40_BITS			((uint32_t) 0x0A)
#define QSPI_ADDR_44_BITS			((uint32_t) 0x0B)
#define QSPI_ADDR_48_BITS			((uint32_t) 0x0C)
#define QSPI_ADDR_52_BITS			((uint32_t) 0x0D)
#define QSPI_ADDR_56_BITS			((uint32_t) 0x0E)
#define QSPI_ADDR_60_BITS			((uint32_t) 0x0F)
/**
  * @}
  */

/** @defgroup QSPI_TransferType QSPI Transfer Type
 * @{
 */
/* Note: These macros are used to set register QSPI_ENH_CTRL0 and QSPI_XIP_CTRL
 *       and need to be shifted left before setting */
#define QSPI_TRANS_BOTH_STANDARD					((uint32_t) 0x00)	/*!< Instruction and address both in standard SPI mode					*/
#define QSPI_TRANS_INST_STANDARD_ADDR_CUSTOMIZE		((uint32_t) 0x01)	/*!< Instruction in standard SPI mode, address in customized SPI mode
																			 specified by QSPI_CTRL0.SPI_FRF or QSPI_XIP_CTRL.FRF				*/
#define QSPI_TRANS_BOTH_CUSTOMIZED					((uint32_t) 0x02)	/*!< Instruction and address both in customized SPI mode
																			 specified by QSPI_CTRL0.SPI_FRF or QSPI_XIP_CTRL.FRF				*/
/**
  * @}
  */

/** @defgroup QSPI_DMATxEnable QSPI DMA Transmit Enable
  * @{
  */
#define QSPI_DMA_TX_ENABLE			((uint8_t) 0x02)	/*!< Transmit DMA enable 	*/
#define QSPI_DMA_TX_DISABLE			((uint8_t) 0x00)	/*!< Transmit DMA disable	*/
/**
  * @}
  */

/** @defgroup QSPI_DMARxEnable QSPI DMA Receive Enable
  * @{
  */
#define QSPI_DMA_RX_ENABLE			((uint8_t) 0x01)	/*!< Receive DMA enable		*/
#define QSPI_DMA_RX_DISABLE			((uint8_t) 0x00)	/*!< Receive DMA disable	*/
/**
  * @}
  */

/** @defgroup QSPI_MicrowireHs QSPI Microwire Handshaking
  * @{
  */
#define QSPI_MW_HS_ENABLE			((uint8_t) 0x04)	/*!< Microwire Handshaking enable	*/
#define QSPI_MW_HS_DISABLE			((uint8_t) 0x00)	/*!< Microwire Handshaking disable	*/
/**
  * @}
  */

/** @defgroup QSPI_MicrowireDir QSPI Microwire Direction of data
  * @{
  */
#define QSPI_MW_DIR_TX				((uint8_t) 0x02)	/*!< Transmit 	*/
#define QSPI_MW_DIR_RX				((uint8_t) 0x00)	/*!< Receive	*/
/**
  * @}
  */

/** @defgroup QSPI_MicrowireMode QSPI Microwire Transfer mode
  * @{
  */
#define QSPI_MW_MODE_SEQ			((uint8_t) 0x01)	/*!< Sequentially transfer		*/
#define QSPI_MW_MODE_NONSEQ			((uint8_t) 0x00)	/*!< Non-Sequentially transfer	*/
/**
  * @}
  */

/** @defgroup QSPI_TFIFOTransThr QSPI Transmit FIFO Transfer Threshold
  * @{
  */
#define QSPI_TXFIFO_TTHR_1			((uint32_t) 0x00000000)	/*!< Start to transfer when data in transmit FIFO reach 1 */
#define QSPI_TXFIFO_TTHR_2			((uint32_t) 0x00010000)
#define QSPI_TXFIFO_TTHR_3			((uint32_t) 0x00020000)
#define QSPI_TXFIFO_TTHR_4			((uint32_t) 0x00030000)
#define QSPI_TXFIFO_TTHR_5			((uint32_t) 0x00040000)
#define QSPI_TXFIFO_TTHR_6			((uint32_t) 0x00050000)
#define QSPI_TXFIFO_TTHR_7			((uint32_t) 0x00060000)
#define QSPI_TXFIFO_TTHR_8			((uint32_t) 0x00070000)
#define QSPI_TXFIFO_TTHR_9			((uint32_t) 0x00080000)
#define QSPI_TXFIFO_TTHR_10			((uint32_t) 0x00090000)
#define QSPI_TXFIFO_TTHR_11			((uint32_t) 0x000A0000)
#define QSPI_TXFIFO_TTHR_12			((uint32_t) 0x000B0000)
#define QSPI_TXFIFO_TTHR_13			((uint32_t) 0x000C0000)
#define QSPI_TXFIFO_TTHR_14			((uint32_t) 0x000D0000)
#define QSPI_TXFIFO_TTHR_15			((uint32_t) 0x000E0000)
#define QSPI_TXFIFO_TTHR_16			((uint32_t) 0x000F0000)
#define QSPI_TXFIFO_TTHR_17			((uint32_t) 0x00100000)
#define QSPI_TXFIFO_TTHR_18			((uint32_t) 0x00110000)
#define QSPI_TXFIFO_TTHR_19			((uint32_t) 0x00120000)
#define QSPI_TXFIFO_TTHR_20			((uint32_t) 0x00130000)
#define QSPI_TXFIFO_TTHR_21			((uint32_t) 0x00140000)
#define QSPI_TXFIFO_TTHR_22			((uint32_t) 0x00150000)
#define QSPI_TXFIFO_TTHR_23			((uint32_t) 0x00160000)
#define QSPI_TXFIFO_TTHR_24			((uint32_t) 0x00170000)
#define QSPI_TXFIFO_TTHR_25			((uint32_t) 0x00180000)
#define QSPI_TXFIFO_TTHR_26			((uint32_t) 0x00190000)
#define QSPI_TXFIFO_TTHR_27			((uint32_t) 0x001A0000)
#define QSPI_TXFIFO_TTHR_28			((uint32_t) 0x001B0000)
#define QSPI_TXFIFO_TTHR_29			((uint32_t) 0x001C0000)
#define QSPI_TXFIFO_TTHR_30			((uint32_t) 0x001D0000)
#define QSPI_TXFIFO_TTHR_31			((uint32_t) 0x001E0000)
#define QSPI_TXFIFO_TTHR_32			((uint32_t) 0x001F0000)
/**
  * @}
  */

/** @defgroup QSPI_TFIFOIntThr QSPI Transmit FIFO Empty Interrupt Threshold
  * @{
  */
#define QSPI_TXFIFO_ITHR_1			((uint32_t) 0x00000000)	/*!< Trigger empty interrupt when data in transmit FIFO is less than 1 */
#define QSPI_TXFIFO_ITHR_2			((uint32_t) 0x00000001)
#define QSPI_TXFIFO_ITHR_3			((uint32_t) 0x00000002)
#define QSPI_TXFIFO_ITHR_4			((uint32_t) 0x00000003)
#define QSPI_TXFIFO_ITHR_5			((uint32_t) 0x00000004)
#define QSPI_TXFIFO_ITHR_6			((uint32_t) 0x00000005)
#define QSPI_TXFIFO_ITHR_7			((uint32_t) 0x00000006)
#define QSPI_TXFIFO_ITHR_8			((uint32_t) 0x00000007)
#define QSPI_TXFIFO_ITHR_9			((uint32_t) 0x00000008)
#define QSPI_TXFIFO_ITHR_10			((uint32_t) 0x00000009)
#define QSPI_TXFIFO_ITHR_11			((uint32_t) 0x0000000A)
#define QSPI_TXFIFO_ITHR_12			((uint32_t) 0x0000000B)
#define QSPI_TXFIFO_ITHR_13			((uint32_t) 0x0000000C)
#define QSPI_TXFIFO_ITHR_14			((uint32_t) 0x0000000D)
#define QSPI_TXFIFO_ITHR_15			((uint32_t) 0x0000000E)
#define QSPI_TXFIFO_ITHR_16			((uint32_t) 0x0000000F)
#define QSPI_TXFIFO_ITHR_17			((uint32_t) 0x00000010)
#define QSPI_TXFIFO_ITHR_18			((uint32_t) 0x00000011)
#define QSPI_TXFIFO_ITHR_19			((uint32_t) 0x00000012)
#define QSPI_TXFIFO_ITHR_20			((uint32_t) 0x00000013)
#define QSPI_TXFIFO_ITHR_21			((uint32_t) 0x00000014)
#define QSPI_TXFIFO_ITHR_22			((uint32_t) 0x00000015)
#define QSPI_TXFIFO_ITHR_23			((uint32_t) 0x00000016)
#define QSPI_TXFIFO_ITHR_24			((uint32_t) 0x00000017)
#define QSPI_TXFIFO_ITHR_25			((uint32_t) 0x00000018)
#define QSPI_TXFIFO_ITHR_26			((uint32_t) 0x00000019)
#define QSPI_TXFIFO_ITHR_27			((uint32_t) 0x0000001A)
#define QSPI_TXFIFO_ITHR_28			((uint32_t) 0x0000001B)
#define QSPI_TXFIFO_ITHR_29			((uint32_t) 0x0000001C)
#define QSPI_TXFIFO_ITHR_30			((uint32_t) 0x0000001D)
#define QSPI_TXFIFO_ITHR_31			((uint32_t) 0x0000001E)
#define QSPI_TXFIFO_ITHR_32			((uint32_t) 0x0000001F)
/**
  * @}
  */

/** @defgroup QSPI_RFIFOIntThr QSPI Receive FIFO Full Interrupt Threshold
  * @{
  */
#define QSPI_RXFIFO_ITHR_1			((uint32_t) 0x00000000)	/*!< Trigger full interrupt when data in receive FIFO is more or equal to 1 */
#define QSPI_RXFIFO_ITHR_2			((uint32_t) 0x00000001)
#define QSPI_RXFIFO_ITHR_3			((uint32_t) 0x00000002)
#define QSPI_RXFIFO_ITHR_4			((uint32_t) 0x00000003)
#define QSPI_RXFIFO_ITHR_5			((uint32_t) 0x00000004)
#define QSPI_RXFIFO_ITHR_6			((uint32_t) 0x00000005)
#define QSPI_RXFIFO_ITHR_7			((uint32_t) 0x00000006)
#define QSPI_RXFIFO_ITHR_8			((uint32_t) 0x00000007)
#define QSPI_RXFIFO_ITHR_9			((uint32_t) 0x00000008)
#define QSPI_RXFIFO_ITHR_10			((uint32_t) 0x00000009)
#define QSPI_RXFIFO_ITHR_11			((uint32_t) 0x0000000A)
#define QSPI_RXFIFO_ITHR_12			((uint32_t) 0x0000000B)
#define QSPI_RXFIFO_ITHR_13			((uint32_t) 0x0000000C)
#define QSPI_RXFIFO_ITHR_14			((uint32_t) 0x0000000D)
#define QSPI_RXFIFO_ITHR_15			((uint32_t) 0x0000000E)
#define QSPI_RXFIFO_ITHR_16			((uint32_t) 0x0000000F)
#define QSPI_RXFIFO_ITHR_17			((uint32_t) 0x00000010)
#define QSPI_RXFIFO_ITHR_18			((uint32_t) 0x00000011)
#define QSPI_RXFIFO_ITHR_19			((uint32_t) 0x00000012)
#define QSPI_RXFIFO_ITHR_20			((uint32_t) 0x00000013)
#define QSPI_RXFIFO_ITHR_21			((uint32_t) 0x00000014)
#define QSPI_RXFIFO_ITHR_22			((uint32_t) 0x00000015)
#define QSPI_RXFIFO_ITHR_23			((uint32_t) 0x00000016)
#define QSPI_RXFIFO_ITHR_24			((uint32_t) 0x00000017)
#define QSPI_RXFIFO_ITHR_25			((uint32_t) 0x00000018)
#define QSPI_RXFIFO_ITHR_26			((uint32_t) 0x00000019)
#define QSPI_RXFIFO_ITHR_27			((uint32_t) 0x0000001A)
#define QSPI_RXFIFO_ITHR_28			((uint32_t) 0x0000001B)
#define QSPI_RXFIFO_ITHR_29			((uint32_t) 0x0000001C)
#define QSPI_RXFIFO_ITHR_30			((uint32_t) 0x0000001D)
#define QSPI_RXFIFO_ITHR_31			((uint32_t) 0x0000001E)
#define QSPI_RXFIFO_ITHR_32			((uint32_t) 0x0000001F)
/**
  * @}
  */

/** @defgroup QSPI_Status_Type QSPI Status Type
  * @{
  */
#define QSPI_STATUS_BUSY				((uint8_t) 0x01)	/*!< Transfer busy			*/
#define QSPI_STATUS_TXFNF				((uint8_t) 0x02)	/*!< Transmit FIFO not full */
#define QSPI_STATUS_TXFE				((uint8_t) 0x04)	/*!< Transmit FIFO empty	*/
#define QSPI_STATUS_RXFNE				((uint8_t) 0x08)	/*!< Receive FIFO not empty */
#define QSPI_STATUS_RXFF				((uint8_t) 0x10)	/*!< Receive FIFO full		*/
#define QSPI_STATUS_TX_ERR				((uint8_t) 0x20)	/*!< Transmit error			*/
#define QSPI_STATUS_DC_ERR				((uint8_t) 0x40)	/*!< Data conflict error	*/
/**
  * @}
  */

/** @defgroup QSPI_Int_Type QSPI Int Type
  * @{
  */
#define QSPI_INT_TXFEI					((uint8_t) 0x01)	/*!< Transmit FIFO Empty Interrupt			*/
#define QSPI_INT_TXFOI					((uint8_t) 0x02)	/*!< Transmit FIFO Overflow Interrupt		*/
#define QSPI_INT_RXFUI					((uint8_t) 0x04)	/*!< Receive FIFO Underflow Interrupt		*/
#define QSPI_INT_RXFOI					((uint8_t) 0x08)	/*!< Receive FIFO Overflow Interrupt		*/
#define QSPI_INT_RXFFI					((uint8_t) 0x10)	/*!< Receive FIFO Full Interrupt			*/
#define QSPI_INT_MMCI					((uint8_t) 0x20)	/*!< Multi-Master Contention Interrupt		*/
#define QSPI_INT_XRXOI					((uint8_t) 0x40)	/*!< XIP Receive FIFO Overflow Interrupt	*/
#define QSPI_INT_ALL_CLR				((uint8_t) (QSPI_INT_TXFOI | QSPI_INT_RXFUI | QSPI_INT_RXFOI | QSPI_INT_MMCI))
/**
  * @}
  */

/** @defgroup QSPI_IO_State QSPI IO State
  * @{
  */
#define QSPI_IO_OUT_HIGH			((uint8_t) 1)	/*!< IO2 or IO3 output high in standard or 2-line mode	*/
#define QSPI_IO_OUT_LOW				((uint8_t) 0)	/*!< IO2 or IO3 output low in standard or 2-line mode 	*/
/**
  * @}
  */

/** @defgroup QSPI_FIFO_DEPTH QSPI FIFO DEPTH
  * @{
  */
#define QSPI_TFIFO_DEPTH			((uint8_t) 32) 		/*!< Transmit FIFO depth */
#define QSPI_RFIFO_DEPTH			QSPI_TFIFO_DEPTH 	/*!< Receive FIFO depth */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup QSPI_Exported_Macros QSPI Export Macros
  * @{
  */

/** @brief  Enable the QSPI peripheral.
  * @return None
  */
#define __QSPI_ENABLE()				SET_BIT(QSPI->EN, QSPI_EN_QEN)

/** @brief  Disable the QSPI peripheral.
  * @return None
  */
#define __QSPI_DISABLE()			CLEAR_BIT(QSPI->EN, QSPI_EN_QEN)

/** @brief  Enable the QSPI slave device.
  * @return None
  */
#define __QSPI_SLAVE_ENABLE()		SET_BIT(QSPI->SLAVE_EN, QSPI_SLAVE_EN_SEN)

/** @brief  Disable the QSPI slave device.
  * @return None
  */
#define __QSPI_SLAVE_DISABLE()		CLEAR_BIT(QSPI->SLAVE_EN, QSPI_SLAVE_EN_SEN)

/** @brief  Enable XIP mode.
  * @return None
  */
#define __QSPI_XIP_ENABLE()			SET_BIT(AFIO->RMP_CFG4, AFIO_RMP_CFG4_QSPI_XIP_EN_RMP)

/** @brief  Disable XIP mode.
  * @return None
  */
#define __QSPI_XIP_DISABLE()		CLEAR_BIT(AFIO->RMP_CFG4, AFIO_RMP_CFG4_QSPI_XIP_EN_RMP)

/** @brief  Enable the QSPI XIP slave device.
  * @return None
  */
#define __QSPI_XIP_SLAVE_ENABLE()	SET_BIT(QSPI->XIP_SLAVE_EN, QSPI_XIP_SLAVE_EN_SEN)

/** @brief  Disable the QSPI XIP slave device.
  * @return None
  */
#define __QSPI_XIP_SLAVE_DISABLE()	CLEAR_BIT(QSPI->XIP_SLAVE_EN, QSPI_XIP_SLAVE_EN_SEN)

/** @brief  Set QSPI Transmit FIFO Transfer Threshold.
  * @param  \__THR__ refer to @ref QSPI_TFIFOTransThr
  */
#define __QSPI_SET_TXFIFO_TTHR(__THR__)		MODIFY_REG(QSPI->TXFT, QSPI_TXFT_ST, (__THR__))

/** @brief  Set QSPI Receive FIFO Full Threshold.
  * @param  \__THR__ refer to @ref QSPI_RFIFOIntThr
  */
#define __QSPI_SET_RXFIFO_ITHR(__THR__)		MODIFY_REG(QSPI->RXFT, QSPI_RXFT_TFI, (__THR__))

/** @brief  XIP continuous transfer enable status.
  * @return None
  */
#define __QSPI_IS_XIP_CT_ENABLED()	((QSPI->ENH_CTRL0 & QSPI_ENH_CTRL0_XIP_CT_EN) != RESET)

/** @brief  XIP mode enable status.
  * @return None
  */
#define __QSPI_IS_XIP_ENABLED()		((AFIO->RMP_CFG4 & AFIO_RMP_CFG4_QSPI_XIP_EN_RMP) != RESET)

/** @brief  Get QSPI status.
  * @param  \__STS__ Refer to @ref QSPI_Status_Type
  * @return RESET or !RESET
  */
#define __QSPI_GET_STS(__STS__)		((uint8_t)((QSPI->STS) & (uint32_t)(__STS__)))

/** @brief  Clear QSPI status.
  * @param \__STS__  can be one of the following values:
  * 	   QSPI_STATUS_TX_ERR
  * 	   QSPI_STATUS_DC_ERR
  */
#define __QSPI_CLR_STS(__STS__)		\
	do{								\
		__IO uint32_t reg = 0;		\
		/* Clear error status by reading QSPI_STS register */	\
		reg = READ_REG(QSPI->STS);	\
		(void)reg;					\
	}while(0)

/** @brief  Get QSPI interrupt status.
  * @param  \__INT__ Refer to @ref QSPI_Int_Type
  * @return RESET or !RESET
  */
#define __QSPI_GET_INT_STS(__INT__)		((uint8_t)((QSPI->ISTS) & (uint32_t)(__INT__)))

/** @brief  Get QSPI interrupt status.
  * @param  \__INT__ Refer to @ref QSPI_Int_Type
  * @return RESET or !RESET
  */
#define __QSPI_GET_INT_RAW_STS(__INT__)	((uint8_t)((QSPI->RISTS) & (uint32_t)(__INT__)))

/** @brief  Get QSPI line mode.
  * @return QSPI_LINE_STANDARD, QSPI_LINE_2_LINES or QSPI_LINE_4_LINES
  */
#define __QSPI_GET_LINE_MODE()		((uint32_t)(QSPI->CTRL0 & QSPI_CTRL0_SPI_FRF) >> QSPI_CTRL0_SPI_FRF_Pos)

/** @brief  Get QSPI transfer mode.
  * @return QSPI_TRANSFER_TX_AND_RX, QSPI_TRANSFER_TX_ONLY, QSPI_TRANSFER_RX_ONLY
  * 		or QSPI_TRANSFER_EEPROM_READ
  */
#define __QSPI_GET_TRANS_MODE()		((uint32_t)(QSPI->CTRL0 & QSPI_CTRL0_TMOD))

/** @brief  Get QSPI frame format.
  * @return QSPI_FRF_SPI, QSPI_FRF_SSP or QSPI_FRF_MICROWIRE
  */
#define __QSPI_GET_FRF()			((uint32_t)(QSPI->CTRL0 & QSPI_CTRL0_FRF))

/** @brief  Get QSPI instruction length.
  * @return Refer to @ref QSPI_InstLen
  */
#define __QSPI_GET_INST_LEN()		((uint32_t)(QSPI->ENH_CTRL0 & QSPI_ENH_CTRL0_INST_L) >> QSPI_ENH_CTRL0_INST_L_Pos)

/** @brief  Get QSPI address length.
  * @return Refer to @ref QSPI_AddrLen
  */
#define __QSPI_GET_ADDR_LEN()		((uint32_t)(QSPI->ENH_CTRL0 & QSPI_ENH_CTRL0_ADDR_LEN) >> QSPI_ENH_CTRL0_ADDR_LEN_Pos)

/** @brief  Get QSPI control frame size.
  * @return Refer to @ref QSPI_ControlFrameSize
  */
#define __QSPI_GET_CFS()			((uint32_t)(QSPI->CTRL0 & QSPI_CTRL0_CFS))

/** @brief  Get QSPI data length.
  * @return Refer to @ref QSPI_DataFrameSize
  */
#define __QSPI_GET_DATA_LEN()		((uint32_t)(QSPI->CTRL0 & QSPI_CTRL0_DFS))

/** @brief  Get number of filled items in transmit FIFO.
  * @return Number from 0 ~ 32
  */
#define __QSPI_GET_TFIFO_NR_FILLED()		((uint8_t)(QSPI->TXFN & QSPI_TXFN_TXFN))

/** @brief  Get number of filled items in receive FIFO.
  * @return Number from 0 ~ 32
  */
#define __QSPI_GET_RFIFO_NR_FILLED()		((uint8_t)(QSPI->RXFN & QSPI_RXFN_RXFN))

/** @brief  Get number of free items in transmit FIFO.
  * @return Number from 0 ~ 32
  */
#define __QSPI_GET_TFIFO_NR_FREE()			((uint8_t)(QSPI_TFIFO_DEPTH - (uint8_t)(QSPI->TXFN & QSPI_TXFN_TXFN)))
/** @brief  Get number of free items in receive FIFO.
  * @return Number from 0 ~ 32
  */
#define __QSPI_GET_RFIFO_NR_FREE()			((uint8_t)(QSPI_RFIFO_DEPTH - (uint8_t)(QSPI->RXFN & QSPI_RXFN_RXFN)))

/**
 * @}
 */


/* Exported functions --------------------------------------------------------*/
/** @addtogroup QSPI_Exported_Functions
 * @{
 */

/** @addtogroup QSPI_Exported_Functions_Group1
  * @{
  */
/* Initialization/de-initialization functions *********************************/
void		QSPI_DeInit (void);
void		QSPI_Init (QSPI_InitType* QSPI_InitStruct);
void		QSPI_InitStruct (QSPI_InitType* QSPI_InitStruct);
/**
  * @}
  */

/** @addtogroup QSPI_Exported_Functions_Group2
  * @{
  */
/* I/O operation functions ****************************************************/
/* QSPI indirect mode */
void		QSPI_Command (QSPI_CommandType* Cmd);
void 		QSPI_Transmit (void* pData, uint32_t Nr);
void		QSPI_Receive (void* pData, uint32_t Nr);
void		QSPI_ClrRxFIFO (void);
/**
  * @}
  */

/** @addtogroup QSPI_Exported_Functions_Group3
  * @{
  */
/* Peripheral Control functions ***********************************************/
void		QSPI_DMAConfig (QSPI_DMAType* Cfg);
void		QSPI_MicrowireConfig (QSPI_MicrowireType* Cfg);
void		QSPI_GPIOConfig (uint32_t LineMode, uint32_t Port, uint8_t IO2State, uint8_t IO3State);
void		QSPI_INTConfig (uint8_t Int, FunctionalState Cmd);

/* QSPI enhanced(including XIP) mode */
void		QSPI_SetWaitCycles (uint32_t WaitCycles);

void		QSPI_Enable (FunctionalState Cmd);
void		QSPI_XIP_Enable (FunctionalState Cmd);
/**
  * @}
  */

/** @addtogroup QSPI_Exported_Functions_Group4
  * @{
  */
/* Peripheral State functions *************************************************/
FlagStatus	QSPI_GetStatus (uint8_t Status);
void		QSPI_ClrErrStatus (uint8_t ErrStatus);
INTStatus	QSPI_GetIntStatus (uint8_t IntStatus);
INTStatus	QSPI_GetRawIntStatus (uint8_t RawIntStatus);
void		QSPI_ClrIntStatus (uint8_t IntStatus);
/**
  * @}
  */

/**
  * @}
  */

 
/* Private macro ------------------------------------------------------------*/
/** @defgroup QSPI_Private_Macros QSPI Private Macros
  * @{
  */
/* Macro reserved for internal standard driver usage, not intended to be used in
   code of final user */ 
#define IS_QSPI_PORT(PORT)			(((PORT) == QSPI_NSS_PORTA) || ((PORT) == QSPI_NSS_PORTC) || ((PORT) == QSPI_NSS_PORTF))
#define IS_QSPI_LINE_MODE(MODE)		(((MODE) == QSPI_LINE_STANDARD)    || ((MODE) == QSPI_LINE_2_LINES) || ((MODE) == QSPI_LINE_4_LINES) || \
									 ((MODE) == QSPI_LINE_2_LINES_XIP) || ((MODE) == QSPI_LINE_4_LINES_XIP))
#define IS_QSPI_TRANSFER_MODE(MODE)	(((MODE) == QSPI_TRANSFER_TX_AND_RX) || ((MODE) == QSPI_TRANSFER_TX_ONLY) || \
									 ((MODE) == QSPI_TRANSFER_RX_ONLY)   || ((MODE) == QSPI_TRANSFER_EEPROM_READ))
#define IS_QSPI_CLKPOL(POL)			(((POL) == QSPI_CLKPOL_LOW) || ((POL) == QSPI_CLKPOL_HIGH))
#define IS_QSPI_CLKPHA(PHA)			(((PHA) == QSPI_CLKPHA_FIRST_EDGE) || ((PHA) == QSPI_CLKPHA_SECOND_EDGE))
#define IS_QSPI_FRF(FORMAT)			(((FORMAT) == QSPI_FRF_SPI) || ((FORMAT) == QSPI_FRF_SSP) || ((FORMAT) == QSPI_FRF_MICROWIRE))
#define IS_QSPI_CFS(SIZE)			(((SIZE) == QSPI_CFS_1_BIT)   || ((SIZE) == QSPI_CFS_2_BITS)  || ((SIZE) == QSPI_CFS_3_BITS)  || ((SIZE) == QSPI_CFS_4_BITS)  || \
									 ((SIZE) == QSPI_CFS_5_BITS)  || ((SIZE) == QSPI_CFS_6_BITS)  || ((SIZE) == QSPI_CFS_7_BITS)  || ((SIZE) == QSPI_CFS_8_BITS)  || \
									 ((SIZE) == QSPI_CFS_9_BITS)  || ((SIZE) == QSPI_CFS_10_BITS) || ((SIZE) == QSPI_CFS_11_BITS) || ((SIZE) == QSPI_CFS_12_BITS) || \
									 ((SIZE) == QSPI_CFS_13_BITS) || ((SIZE) == QSPI_CFS_14_BITS) || ((SIZE) == QSPI_CFS_15_BITS) || ((SIZE) == QSPI_CFS_16_BITS))
#define IS_QSPI_DFS(SIZE)			(((SIZE) == QSPI_DFS_4_BITS)  || ((SIZE) == QSPI_DFS_5_BITS)  || ((SIZE) == QSPI_DFS_6_BITS)  || ((SIZE) == QSPI_DFS_7_BITS)  || \
									 ((SIZE) == QSPI_DFS_8_BITS)  || ((SIZE) == QSPI_DFS_9_BITS)  || ((SIZE) == QSPI_DFS_10_BITS) || ((SIZE) == QSPI_DFS_11_BITS) || \
									 ((SIZE) == QSPI_DFS_12_BITS) || ((SIZE) == QSPI_DFS_13_BITS) || ((SIZE) == QSPI_DFS_14_BITS) || ((SIZE) == QSPI_DFS_15_BITS) || \
									 ((SIZE) == QSPI_DFS_16_BITS) || ((SIZE) == QSPI_DFS_17_BITS) || ((SIZE) == QSPI_DFS_18_BITS) || ((SIZE) == QSPI_DFS_19_BITS) || \
									 ((SIZE) == QSPI_DFS_20_BITS) || ((SIZE) == QSPI_DFS_21_BITS) || ((SIZE) == QSPI_DFS_22_BITS) || ((SIZE) == QSPI_DFS_23_BITS) || \
									 ((SIZE) == QSPI_DFS_24_BITS) || ((SIZE) == QSPI_DFS_25_BITS) || ((SIZE) == QSPI_DFS_26_BITS) || ((SIZE) == QSPI_DFS_27_BITS) || \
									 ((SIZE) == QSPI_DFS_28_BITS) || ((SIZE) == QSPI_DFS_29_BITS) || ((SIZE) == QSPI_DFS_30_BITS) || ((SIZE) == QSPI_DFS_31_BITS) || \
									 ((SIZE) == QSPI_DFS_32_BITS))
#define IS_QSPI_XIP_MBL(LENGTH)		(((LENGTH) == QSPI_XIP_MBL_2_BITS) || ((LENGTH) == QSPI_XIP_MBL_4_BITS) || ((LENGTH) == QSPI_XIP_MBL_8_BITS) || \
									 ((LENGTH) == QSPI_XIP_MBL_16_BITS))
#define IS_QSPI_WAIT_CYCLES(CYCLES)	(((CYCLES) == QSPI_WAIT_NONE)      || ((CYCLES) == QSPI_WAIT_1_CYCLE)   || ((CYCLES) == QSPI_WAIT_2_CYCLES)  || \
									 ((CYCLES) == QSPI_WAIT_3_CYCLES)  || ((CYCLES) == QSPI_WAIT_4_CYCLES)  || ((CYCLES) == QSPI_WAIT_5_CYCLES)  || \
									 ((CYCLES) == QSPI_WAIT_6_CYCLES)  || ((CYCLES) == QSPI_WAIT_7_CYCLES)  || ((CYCLES) == QSPI_WAIT_8_CYCLES)  || \
									 ((CYCLES) == QSPI_WAIT_9_CYCLES)  || ((CYCLES) == QSPI_WAIT_10_CYCLES) || ((CYCLES) == QSPI_WAIT_11_CYCLES) || \
									 ((CYCLES) == QSPI_WAIT_12_CYCLES) || ((CYCLES) == QSPI_WAIT_13_CYCLES) || ((CYCLES) == QSPI_WAIT_14_CYCLES) || \
									 ((CYCLES) == QSPI_WAIT_15_CYCLES) || ((CYCLES) == QSPI_WAIT_16_CYCLES) || ((CYCLES) == QSPI_WAIT_17_CYCLES) || \
									 ((CYCLES) == QSPI_WAIT_18_CYCLES) || ((CYCLES) == QSPI_WAIT_19_CYCLES) || ((CYCLES) == QSPI_WAIT_20_CYCLES) || \
									 ((CYCLES) == QSPI_WAIT_21_CYCLES) || ((CYCLES) == QSPI_WAIT_22_CYCLES) || ((CYCLES) == QSPI_WAIT_23_CYCLES) || \
									 ((CYCLES) == QSPI_WAIT_24_CYCLES) || ((CYCLES) == QSPI_WAIT_25_CYCLES) || ((CYCLES) == QSPI_WAIT_26_CYCLES) || \
									 ((CYCLES) == QSPI_WAIT_27_CYCLES) || ((CYCLES) == QSPI_WAIT_28_CYCLES) || ((CYCLES) == QSPI_WAIT_29_CYCLES) || \
									 ((CYCLES) == QSPI_WAIT_30_CYCLES) || ((CYCLES) == QSPI_WAIT_31_CYCLES))
#define IS_QSPI_INST_LENGTH(LENGTH)	(((LENGTH) == QSPI_INST_NONE) || ((LENGTH) == QSPI_INST_4_BITS) || ((LENGTH) == QSPI_INST_8_BITS) || ((LENGTH) == QSPI_INST_16_BITS))
#define IS_QSPI_ADDR_LENGTH(LENGTH)	(((LENGTH) == QSPI_ADDR_NONE)    || ((LENGTH) == QSPI_ADDR_4_BITS)  || ((LENGTH) == QSPI_ADDR_8_BITS)  || \
									 ((LENGTH) == QSPI_ADDR_12_BITS) || ((LENGTH) == QSPI_ADDR_16_BITS) || ((LENGTH) == QSPI_ADDR_20_BITS) || \
									 ((LENGTH) == QSPI_ADDR_24_BITS) || ((LENGTH) == QSPI_ADDR_28_BITS) || ((LENGTH) == QSPI_ADDR_32_BITS) || \
									 ((LENGTH) == QSPI_ADDR_36_BITS) || ((LENGTH) == QSPI_ADDR_40_BITS) || ((LENGTH) == QSPI_ADDR_44_BITS) || \
									 ((LENGTH) == QSPI_ADDR_48_BITS) || ((LENGTH) == QSPI_ADDR_52_BITS) || ((LENGTH) == QSPI_ADDR_56_BITS) || \
									 ((LENGTH) == QSPI_ADDR_60_BITS))
#define IS_QSPI_TRANS_TYPE(TYPE)	(((TYPE) == QSPI_TRANS_BOTH_STANDARD) || ((TYPE) == QSPI_TRANS_INST_STANDARD_ADDR_CUSTOMIZE) || ((TYPE) == QSPI_TRANS_BOTH_CUSTOMIZED))
#define IS_QSPI_DMA_TX_MODE(MODE)	(((MODE) == QSPI_DMA_TX_ENABLE) || ((MODE) == QSPI_DMA_TX_DISABLE))
#define IS_QSPI_DMA_TDL(LEVEL)		((uint8_t)(LEVEL) > 0 && (uint8_t)(LEVEL) <= 32) /*!< Check transmit data level */
#define IS_QSPI_DMA_RX_MODE(MODE)	(((MODE) == QSPI_DMA_RX_ENABLE) || ((MODE) == QSPI_DMA_RX_DISABLE))
#define IS_QSPI_DMA_RDL(LEVEL)		((uint8_t)(LEVEL) > 0 && (uint8_t)(LEVEL) <= 32) /*!< Check receive data level */
#define IS_QSPI_MW_HS_MODE(MODE)	(((MODE) == QSPI_MW_HS_ENABLE) || ((MODE) == QSPI_MW_HS_DISABLE))
#define IS_QSPI_MW_DIR(DIR)			(((DIR) == QSPI_MW_DIR_RX) || ((DIR) == QSPI_MW_DIR_TX))
#define IS_QSPI_MW_MODE(MODE)		(((MODE) == QSPI_MW_MODE_SEQ) || ((MODE) == QSPI_MW_MODE_NONSEQ))
#define IS_QSPI_TXFIFO_TTHR(THR)	(((THR) == QSPI_TXFIFO_TTHR_1)  || ((THR) == QSPI_TXFIFO_TTHR_2)  || ((THR) == QSPI_TXFIFO_TTHR_3)  || \
									 ((THR) == QSPI_TXFIFO_TTHR_4)  || ((THR) == QSPI_TXFIFO_TTHR_5)  || ((THR) == QSPI_TXFIFO_TTHR_6)  || \
									 ((THR) == QSPI_TXFIFO_TTHR_7)  || ((THR) == QSPI_TXFIFO_TTHR_8)  || ((THR) == QSPI_TXFIFO_TTHR_9)  || \
									 ((THR) == QSPI_TXFIFO_TTHR_10) || ((THR) == QSPI_TXFIFO_TTHR_11) || ((THR) == QSPI_TXFIFO_TTHR_12) || \
									 ((THR) == QSPI_TXFIFO_TTHR_13) || ((THR) == QSPI_TXFIFO_TTHR_14) || ((THR) == QSPI_TXFIFO_TTHR_15) || \
									 ((THR) == QSPI_TXFIFO_TTHR_16) || ((THR) == QSPI_TXFIFO_TTHR_17) || ((THR) == QSPI_TXFIFO_TTHR_18) || \
									 ((THR) == QSPI_TXFIFO_TTHR_19) || ((THR) == QSPI_TXFIFO_TTHR_20) || ((THR) == QSPI_TXFIFO_TTHR_21) || \
									 ((THR) == QSPI_TXFIFO_TTHR_22) || ((THR) == QSPI_TXFIFO_TTHR_23) || ((THR) == QSPI_TXFIFO_TTHR_24) || \
									 ((THR) == QSPI_TXFIFO_TTHR_25) || ((THR) == QSPI_TXFIFO_TTHR_26) || ((THR) == QSPI_TXFIFO_TTHR_27) || \
									 ((THR) == QSPI_TXFIFO_TTHR_28) || ((THR) == QSPI_TXFIFO_TTHR_29) || ((THR) == QSPI_TXFIFO_TTHR_30) || \
									 ((THR) == QSPI_TXFIFO_TTHR_31) || ((THR) == QSPI_TXFIFO_TTHR_32))
#define IS_QSPI_TXFIFO_ITHR(THR)	(((THR) == QSPI_TXFIFO_ITHR_1)  || ((THR) == QSPI_TXFIFO_ITHR_2)  || ((THR) == QSPI_TXFIFO_ITHR_3)  || \
									 ((THR) == QSPI_TXFIFO_ITHR_4)  || ((THR) == QSPI_TXFIFO_ITHR_5)  || ((THR) == QSPI_TXFIFO_ITHR_6)  || \
									 ((THR) == QSPI_TXFIFO_ITHR_7)  || ((THR) == QSPI_TXFIFO_ITHR_8)  || ((THR) == QSPI_TXFIFO_ITHR_9)  || \
									 ((THR) == QSPI_TXFIFO_ITHR_10) || ((THR) == QSPI_TXFIFO_ITHR_11) || ((THR) == QSPI_TXFIFO_ITHR_12) || \
									 ((THR) == QSPI_TXFIFO_ITHR_13) || ((THR) == QSPI_TXFIFO_ITHR_14) || ((THR) == QSPI_TXFIFO_ITHR_15) || \
									 ((THR) == QSPI_TXFIFO_ITHR_16) || ((THR) == QSPI_TXFIFO_ITHR_17) || ((THR) == QSPI_TXFIFO_ITHR_18) || \
									 ((THR) == QSPI_TXFIFO_ITHR_19) || ((THR) == QSPI_TXFIFO_ITHR_20) || ((THR) == QSPI_TXFIFO_ITHR_21) || \
									 ((THR) == QSPI_TXFIFO_ITHR_22) || ((THR) == QSPI_TXFIFO_ITHR_23) || ((THR) == QSPI_TXFIFO_ITHR_24) || \
									 ((THR) == QSPI_TXFIFO_ITHR_25) || ((THR) == QSPI_TXFIFO_ITHR_26) || ((THR) == QSPI_TXFIFO_ITHR_27) || \
									 ((THR) == QSPI_TXFIFO_ITHR_28) || ((THR) == QSPI_TXFIFO_ITHR_29) || ((THR) == QSPI_TXFIFO_ITHR_30) || \
									 ((THR) == QSPI_TXFIFO_ITHR_31) || ((THR) == QSPI_TXFIFO_ITHR_32))
#define IS_QSPI_RXFIFO_ITHR(THR)	(((THR) == QSPI_RXFIFO_ITHR_1)  || ((THR) == QSPI_RXFIFO_ITHR_2)  || ((THR) == QSPI_RXFIFO_ITHR_3)  || \
								 	 ((THR) == QSPI_RXFIFO_ITHR_4)  || ((THR) == QSPI_RXFIFO_ITHR_5)  || ((THR) == QSPI_RXFIFO_ITHR_6)  || \
									 ((THR) == QSPI_RXFIFO_ITHR_7)  || ((THR) == QSPI_RXFIFO_ITHR_8)  || ((THR) == QSPI_RXFIFO_ITHR_9)  || \
									 ((THR) == QSPI_RXFIFO_ITHR_10) || ((THR) == QSPI_RXFIFO_ITHR_11) || ((THR) == QSPI_RXFIFO_ITHR_12) || \
									 ((THR) == QSPI_RXFIFO_ITHR_13) || ((THR) == QSPI_RXFIFO_ITHR_14) || ((THR) == QSPI_RXFIFO_ITHR_15) || \
									 ((THR) == QSPI_RXFIFO_ITHR_16) || ((THR) == QSPI_RXFIFO_ITHR_17) || ((THR) == QSPI_RXFIFO_ITHR_18) || \
									 ((THR) == QSPI_RXFIFO_ITHR_19) || ((THR) == QSPI_RXFIFO_ITHR_20) || ((THR) == QSPI_RXFIFO_ITHR_21) || \
									 ((THR) == QSPI_RXFIFO_ITHR_22) || ((THR) == QSPI_RXFIFO_ITHR_23) || ((THR) == QSPI_RXFIFO_ITHR_24) || \
									 ((THR) == QSPI_RXFIFO_ITHR_25) || ((THR) == QSPI_RXFIFO_ITHR_26) || ((THR) == QSPI_RXFIFO_ITHR_27) || \
									 ((THR) == QSPI_RXFIFO_ITHR_28) || ((THR) == QSPI_RXFIFO_ITHR_29) || ((THR) == QSPI_RXFIFO_ITHR_30) || \
									 ((THR) == QSPI_RXFIFO_ITHR_31) || ((THR) == QSPI_RXFIFO_ITHR_32))
#define IS_QSPI_STATUS(STS)			(((STS) == QSPI_STATUS_BUSY)  || ((STS) == QSPI_STATUS_TXFNF) || ((STS) == QSPI_STATUS_TXFE)   || \
									 ((STS) == QSPI_STATUS_RXFNE) || ((STS) == QSPI_STATUS_RXFF)  || ((STS) == QSPI_STATUS_TX_ERR) || \
									 ((STS) == QSPI_STATUS_DC_ERR))
#define IS_QSPI_ERR_STATUS(STS)		(((STS) == QSPI_STATUS_TX_ERR) || ((STS) == QSPI_STATUS_DC_ERR))
#define IS_QSPI_INT(INT)			(((INT) == QSPI_INT_TXFEI) || ((INT) == QSPI_INT_TXFOI) || ((INT) == QSPI_INT_RXFUI) || \
									 ((INT) == QSPI_INT_RXFOI) || ((INT) == QSPI_INT_RXFFI) || ((INT) == QSPI_INT_MMCI)  || \
									 ((INT) == QSPI_INT_XRXOI))
#define IS_QSPI_INT_STATUS(STS)		(((STS) == QSPI_INT_TXFEI) || ((STS) == QSPI_INT_TXFOI) || ((STS) == QSPI_INT_RXFUI) || \
		 	 	 	 	 	 	 	 ((STS) == QSPI_INT_RXFOI) || ((STS) == QSPI_INT_RXFFI) || ((STS) == QSPI_INT_MMCI)  || \
									 ((STS) == QSPI_INT_XRXOI))
#define IS_QSPI_INT_RAW_STATUS(STS)	(((STS) == QSPI_INT_TXFEI) || ((STS) == QSPI_INT_TXFOI) || ((STS) == QSPI_INT_RXFUI) || \
 	 	 	 	 	 	 	 	 	 ((STS) == QSPI_INT_RXFOI) || ((STS) == QSPI_INT_RXFFI) || ((STS) == QSPI_INT_MMCI)  || \
									 ((STS) == QSPI_INT_XRXOI))
#define IS_QSPI_INT_CLR_STATUS(STS)	(((STS) == QSPI_INT_TXFOI) || ((STS) == QSPI_INT_RXFUI) || ((STS) == QSPI_INT_RXFOI) || \
									 ((STS) == QSPI_INT_MMCI)  || ((STS) == QSPI_INT_XRXOI) || ((STS) == QSPI_INT_ALL_CLR))
#define IS_QSPI_IO_OUT_STATE(STATE)	(((STATE) == QSPI_IO_OUT_HIGH) || ((STATE) == QSPI_IO_OUT_LOW))

/**
  * @}
  */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /*__CM32M4xxR_QSPI_H__ */