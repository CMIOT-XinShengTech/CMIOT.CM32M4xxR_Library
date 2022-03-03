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
 * @file cm32m4xxr_qspi.c
 * @author CMIOT Firmware Team
 * @brief Source file containing functions prototypes of QSPI StdPeriph Library.
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */
 
/* Includes ------------------------------------------------------------------*/
#include "nuclei_sdk_soc.h"


/** @addtogroup CM32M4xxR_StdPeriph_Driver
  * @{
  */

/** @defgroup QSPI QSPI
  * @brief QSPI driver modules
  * @{
  */

#ifdef	DRIVER_MODULE_ENABLED_QSPI


/* Private definition --------------------------------------------------------*/
/** @defgroup QSPI_Private_Constants QSPI Private Constants 
  * @{
  */
#define QSPI_TIMEOUT_VALUE	((uint32_t) 0xFFFF)

/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup QSPI_Private_Functions QSPI Private Functions
  * @{
  */

/**
  * @brief  Configure single GPIO.
  * @param  GPIOx GPIOx where x can be A, C or F to select the GPIO peripheral used by QSPI.
  * @param  Pin   Pin Specifies the port bit used by QSPI.
  * @param  Mode  The operating mode for the selected pins
  * 		This parameter can be one of the following value according to the QSPI configuration:
  * 		    @arg GPIO_Mode_IN_FLOATING
  * 		    @arg GPIO_Mode_IPD
  * 		    @arg GPIO_Mode_IPU
  * 		    @arg GPIO_Mode_Out_PP
  * 		    @arg GPIO_Mode_AF_PP
  * @return None
  */
static void GPIO_Config(GPIO_Module* GPIOx, uint16_t Pin, GPIO_ModeType Mode)
{
	GPIO_InitType GPIO_InitStructure;

	GPIO_InitStructure.Pin = Pin;
	GPIO_InitStructure.GPIO_Mode = Mode;
	/* Input */
	if(Mode == GPIO_Mode_IN_FLOATING || Mode == GPIO_Mode_IPD || Mode == GPIO_Mode_IPU){
		GPIO_InitStructure.GPIO_Speed = GPIO_INPUT;
	}
	/* Output */
	else{
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	}
	GPIO_Init(GPIOx, &GPIO_InitStructure);
}
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup QSPI_Exported_Functions QSPI Exported Functions
  * @{
  */

/** @defgroup QSPI_Exported_Functions_Group1 Initialization and de-initialization functions 
  * @brief    Initialization and Configuration functions 
  * @{
  */

/**
  * @brief  Deinitializes the QSPI peripheral registers to its default reset values.
  * @return None
  */
void QSPI_DeInit(void)
{
	/* Force reset QSPI */
    RCC_EnableAHBPeriphReset(RCC_AHB_PERIPH_QSPI, ENABLE);
    /* Release reset */
    RCC_EnableAHBPeriphReset(RCC_AHB_PERIPH_QSPI, DISABLE);
}

/**
  * @brief  Initializes the QSPI peripheral according to the specified
  *         parameters in the QSPI_InitStruct.
  * @param QSPI_InitStruct Pointer to a QSPI_InitType structure that
  *        contains the configuration information for the QSPI peripheral.
  * @note  QSPI_TRANSFER_TX_AND_RX transfer mode can only be used in QSPI_LINE_STANDARD
  * 	   line mode.
  * @return None
  */
void QSPI_Init(QSPI_InitType* QSPI_InitStruct)
{
	__IO uint32_t tmpreg = 0;

	/* Check NULL pointer */
	if(!QSPI_InitStruct) { return; }
	/* Check the parameters --------------------------------------------------*/
	assert_param(IS_QSPI_LINE_MODE(QSPI_InitStruct->LineMode));
	assert_param(IS_QSPI_TRANSFER_MODE(QSPI_InitStruct->TransferMode));
	assert_param(IS_QSPI_CLKPOL(QSPI_InitStruct->CLKPOL));
	assert_param(IS_QSPI_CLKPHA(QSPI_InitStruct->CLKPHA));
	assert_param(IS_QSPI_FRF(QSPI_InitStruct->FrameFormat));
	assert_param(IS_QSPI_DFS(QSPI_InitStruct->DFS));
	assert_param(IS_FUNCTIONAL_STATE(QSPI_InitStruct->SSTE));
	/* Check Control Frame Size if Frame Format is Microwire */
	if(QSPI_InitStruct->FrameFormat == QSPI_FRF_MICROWIRE){
		assert_param(IS_QSPI_CFS(QSPI_InitStruct->CFS));
	}
	/* Check enhanced parameters if Line Mode is in enhanced mode */
	if(QSPI_InitStruct->LineMode != QSPI_LINE_STANDARD){
		assert_param(IS_QSPI_ADDR_LENGTH(QSPI_InitStruct->Enhance.AddrLen));
		assert_param(IS_QSPI_INST_LENGTH(QSPI_InitStruct->Enhance.InstLen));
		assert_param(IS_QSPI_WAIT_CYCLES(QSPI_InitStruct->Enhance.WaitCycles));
		assert_param(IS_QSPI_TRANS_TYPE(QSPI_InitStruct->Enhance.TransferType));
		assert_param(IS_FUNCTIONAL_STATE(QSPI_InitStruct->Enhance.ClkStretch));
	}
	/* Check XIP parameters if Line Mode is in XIP mode */
	if(QSPI_InitStruct->LineMode == QSPI_LINE_2_LINES_XIP || QSPI_InitStruct->LineMode == QSPI_LINE_4_LINES_XIP){
		assert_param(IS_QSPI_XIP_MBL(QSPI_InitStruct->Enhance.XIP_MBL));
		assert_param(IS_FUNCTIONAL_STATE(QSPI_InitStruct->Enhance.MD_BIT_EN));
		assert_param(IS_FUNCTIONAL_STATE(QSPI_InitStruct->Enhance.XIP_CT_EN));
		assert_param(IS_FUNCTIONAL_STATE(QSPI_InitStruct->Enhance.XIP_INST_EN));
		assert_param(IS_FUNCTIONAL_STATE(QSPI_InitStruct->Enhance.XIP_DFS_HC));
		assert_param(IS_FUNCTIONAL_STATE(QSPI_InitStruct->Enhance.INST_DDR_EN));
		assert_param(IS_FUNCTIONAL_STATE(QSPI_InitStruct->Enhance.SPI_DDR_EN));
	}

	/* Disable memory-remap(XIP) mode before configuring QSPI.
	 * In memory-remap mode, QSPI registers cannot be configured */
	__QSPI_XIP_DISABLE();
	/* Configure QSPI_CTRL0 register -----------------------------------------*/
	tmpreg = QSPI->CTRL0;
	/* Clear SPI_FRF[1:0], CFS[3:0], SSTE, SRL, TMODE[1:0], SCPOL, SCPH,
	 * FRF[1:0] and DFS[4:0] bits */
	tmpreg &= (uint32_t)~(QSPI_CTRL0_SPI_FRF | QSPI_CTRL0_CFS   | QSPI_CTRL0_SSTE | QSPI_CTRL0_SRL |
						  QSPI_CTRL0_TMOD    | QSPI_CTRL0_SCPOL | QSPI_CTRL0_SCPH | QSPI_CTRL0_FRF |
						  QSPI_CTRL0_DFS);
	/* Configure SPI_FRF[1:0] bits */
	if(QSPI_InitStruct->LineMode == QSPI_LINE_STANDARD || QSPI_InitStruct->LineMode == QSPI_LINE_2_LINES || QSPI_InitStruct->LineMode == QSPI_LINE_4_LINES){
		tmpreg |= QSPI_InitStruct->LineMode << QSPI_CTRL0_SPI_FRF_Pos;
	}else{
		tmpreg |= QSPI_InitStruct->LineMode << (QSPI_CTRL0_SPI_FRF_Pos - 2);
	}
	/* Configure CFS[3:0] bits */
	if(QSPI_InitStruct->FrameFormat == QSPI_FRF_MICROWIRE){
		tmpreg |= QSPI_InitStruct->CFS;
	}
	/* Configure SSTE bit */
	if(QSPI_InitStruct->SSTE == ENABLE){
		tmpreg |= QSPI_CTRL0_SSTE;
	}
	/* Configure TMODE[1:0], SCPOL, SCPH, FRF[1:0] and DFS[4:0] bits */
	tmpreg |= (uint32_t)(QSPI_InitStruct->TransferMode | QSPI_InitStruct->CLKPOL      |
						 QSPI_InitStruct->CLKPHA       | QSPI_InitStruct->FrameFormat |
						 QSPI_InitStruct->DFS);
	QSPI->CTRL0 = tmpreg;

	/* Configure the number of data frames to receive(QSPI_CTRL1 register) ---*/
	if(QSPI_InitStruct->TransferMode == QSPI_TRANSFER_RX_ONLY || QSPI_InitStruct->TransferMode == QSPI_TRANSFER_EEPROM_READ){
		QSPI->CTRL1 = (uint32_t)QSPI_InitStruct->RxDataNr;
	}else{
		QSPI->CTRL1 = 0;
	}

	/* Configure baud rate(QSPI_BAUD register) -------------------------------*/
	QSPI->BAUD = (uint32_t)QSPI_InitStruct->ClkDiv;

	/* Configure QSPI_ENH_CTRL0 register if in enhanced mode -----------------*/
	if(QSPI_InitStruct->LineMode != QSPI_LINE_STANDARD){
		tmpreg = QSPI->ENH_CTRL0;
		/* Clear CLK_STRETCH_EN, XIP_MBL[1:0], XIP_CT_EN, XIP_INST_EN,
		 * XIP_DFS_HC, INST_DDR_EN, SPI_DDR_EN, WATI_CYCLES[4:0], INST_L[1:0],
		 * MD_BIT_EN, ADDR_LEN[3:0] and TRANS_TYPE[1:0] */
		tmpreg &= (uint32_t)~(QSPI_ENH_CTRL0_CLK_STRETCH_EN | QSPI_ENH_CTRL0_XIP_MBL 	 | QSPI_ENH_CTRL0_XIP_CT_EN   |
							  QSPI_ENH_CTRL0_XIP_INST_EN 	| QSPI_ENH_CTRL0_XIP_DFS_HC  | QSPI_ENH_CTRL0_INST_DDR_EN |
							  QSPI_ENH_CTRL0_SPI_DDR_EN 	| QSPI_ENH_CTRL0_WAIT_CYCLES | QSPI_ENH_CTRL0_INST_L      |
							  QSPI_ENH_CTRL0_MD_BIT_EN 		| QSPI_ENH_CTRL0_ADDR_LEN    | QSPI_ENH_CTRL0_TRANS_TYPE);
		/* Configure CLK_STRETCH_EN bit */
		if(QSPI_InitStruct->Enhance.ClkStretch == ENABLE){
			tmpreg |= QSPI_ENH_CTRL0_CLK_STRETCH_EN;
		}
		/* Configure WAIT_CYCLES[4:0], INST_L[1:0], ADDR_LEN[3:0]
		 * and TRANS_TYPE[1:0] bits */
		tmpreg |= (uint32_t)(QSPI_InitStruct->Enhance.WaitCycles   << QSPI_ENH_CTRL0_WAIT_CYCLES_Pos |
							 QSPI_InitStruct->Enhance.InstLen      << QSPI_ENH_CTRL0_INST_L_Pos      |
							 QSPI_InitStruct->Enhance.AddrLen      << QSPI_ENH_CTRL0_ADDR_LEN_Pos    |
							 QSPI_InitStruct->Enhance.TransferType << QSPI_ENH_CTRL0_TRANS_TYPE_Pos);
		/* Configure XIP_MBL[1:0], XIP_CT_EN, XIP_INST_EN, XIP_DFS_HC,
		 * INST_DDR_EN, SPI_DDR_EN and MD_BIT_EN bits */
		if(QSPI_InitStruct->LineMode == QSPI_LINE_2_LINES_XIP || QSPI_InitStruct->LineMode == QSPI_LINE_4_LINES_XIP){
			if(QSPI_InitStruct->Enhance.MD_BIT_EN == ENABLE){
				tmpreg |= (uint32_t)(QSPI_InitStruct->Enhance.XIP_MBL | QSPI_ENH_CTRL0_MD_BIT_EN);
			}
			if(QSPI_InitStruct->Enhance.XIP_CT_EN == ENABLE){
				tmpreg |= QSPI_ENH_CTRL0_XIP_CT_EN;
			}
			if(QSPI_InitStruct->Enhance.XIP_INST_EN == ENABLE){
				tmpreg |= QSPI_ENH_CTRL0_XIP_INST_EN;
			}
			if(QSPI_InitStruct->Enhance.XIP_DFS_HC == ENABLE){
				tmpreg |= QSPI_ENH_CTRL0_XIP_DFS_HC;
			}
			if(QSPI_InitStruct->Enhance.INST_DDR_EN == ENABLE){
				tmpreg |= QSPI_ENH_CTRL0_INST_DDR_EN;
			}
			if(QSPI_InitStruct->Enhance.SPI_DDR_EN == ENABLE){
				tmpreg |= QSPI_ENH_CTRL0_SPI_DDR_EN;
			}
		}
		QSPI->ENH_CTRL0 = tmpreg;
	}

	/* Configure QSPI_XIP_CTRL register if in XIP mode -----------------------*/
	if(QSPI_InitStruct->LineMode == QSPI_LINE_2_LINES_XIP || QSPI_InitStruct->LineMode == QSPI_LINE_4_LINES_XIP){
		tmpreg = QSPI->XIP_CTRL;
		/* Clear XIP_MBL[1:0], XIP_CT_EN, XIP_INST_EN, INST_DDR_EN, DDR_EN,
		 * DFS_HC, WAIT_CYCLES[4:0], MD_BITS_EN, INST_L[1:0], ADDR_LEN[3:0],
		 * TRANS_TYPE[1:0] and FRF[1:0] bits */
		tmpreg &= (uint32_t)~(QSPI_XIP_CTRL_XIP_MBL     | QSPI_XIP_CTRL_XIP_CT_EN  | QSPI_XIP_CTRL_XIP_INST_EN |
							  QSPI_XIP_CTRL_INST_DDR_EN | QSPI_XIP_CTRL_DDR_EN     | QSPI_XIP_CTRL_DFS_HC      |
							  QSPI_XIP_CTRL_WAIT_CYCLES | QSPI_XIP_CTRL_MD_BITS_EN | QSPI_XIP_CTRL_INST_L      |
							  QSPI_XIP_CTRL_ADDR_LEN    | QSPI_XIP_CTRL_TRANS_TYPE | QSPI_XIP_CTRL_FRF);
		/* Configure WAIT_CYCLES[4:0], INST_L[1:0], ADDR_LEN[3:0] and
		 * TRANS_TYPE[1:0] bits */
		tmpreg |= (uint32_t)(QSPI_InitStruct->Enhance.WaitCycles   << QSPI_XIP_CTRL_WAIT_CYCLES_Pos |
							 QSPI_InitStruct->Enhance.InstLen      << QSPI_XIP_CTRL_INST_L_Pos      |
							 QSPI_InitStruct->Enhance.AddrLen      << QSPI_XIP_CTRL_ADDR_LEN_Pos    |
							 QSPI_InitStruct->Enhance.TransferType << QSPI_XIP_CTRL_TRANS_TYPE_Pos);
		/* Configure XIP_MBL[1:0], XIP_CT_EN, XIP_INST_EN, INST_DDR_EN,
		 * DDR_EN, DFS_HC, MD_BITS_EN and FRF[1:0] bits */
		if(QSPI_InitStruct->Enhance.MD_BIT_EN == ENABLE){
			tmpreg |= (uint32_t)(QSPI_InitStruct->Enhance.XIP_MBL | QSPI_XIP_CTRL_MD_BITS_EN);
			/* Configure QSPI_XIP_MODE register */
			QSPI->XIP_MODE = (uint32_t)QSPI_InitStruct->Enhance.XIP_MODE_BITS;
		}
		if(QSPI_InitStruct->Enhance.XIP_CT_EN == ENABLE){
			tmpreg |= QSPI_XIP_CTRL_XIP_CT_EN;
		}
		if(QSPI_InitStruct->Enhance.XIP_INST_EN == ENABLE){
			tmpreg |= QSPI_XIP_CTRL_XIP_INST_EN;
			/* Configure QSPI_XIP_INCR_TOC and QSPI_XIP_WRAP_TOC registers */
			QSPI->XIP_INCR_TOC = (uint32_t)QSPI_InitStruct->Enhance.ITOC;
			QSPI->XIP_WRAP_TOC = (uint32_t)QSPI_InitStruct->Enhance.WTOC;
		}
		if(QSPI_InitStruct->Enhance.XIP_DFS_HC == ENABLE){
			tmpreg |= QSPI_XIP_CTRL_DFS_HC;
		}
		if(QSPI_InitStruct->Enhance.INST_DDR_EN == ENABLE){
			tmpreg |= QSPI_XIP_CTRL_INST_DDR_EN;
		}
		if(QSPI_InitStruct->Enhance.SPI_DDR_EN == ENABLE){
			tmpreg |= QSPI_XIP_CTRL_DDR_EN;
		}
		tmpreg |= (uint32_t)(QSPI_InitStruct->LineMode >> 2u);
		QSPI->XIP_CTRL = tmpreg;
	}
}

/**
  * @brief Fills each QSPI_InitStruct member with its default value.
  * @param QSPI_InitStruct Pointer to an QSPI_InitType structure which will be initialized.
  * @return None.
  */
void QSPI_InitStruct(QSPI_InitType *QSPI_InitStruct)
{
	/* Check NULL pointer */
	if(!QSPI_InitStruct) { return; }

	/* Initialize normal mode parameters value -------------------------------*/
	/* Initialize the LineMode member */
	QSPI_InitStruct->LineMode 				= QSPI_LINE_4_LINES;
	/* Initialize the FrameFormat member */
	QSPI_InitStruct->FrameFormat			= QSPI_FRF_SPI;
	/* Initialize the TransferMode member */
	QSPI_InitStruct->TransferMode 			= QSPI_TRANSFER_TX_ONLY;
	/* Initialize the CLKPOL member */
	QSPI_InitStruct->CLKPOL 				= QSPI_CLKPOL_HIGH;
	/* Initialize the CLKPHA member */
	QSPI_InitStruct->CLKPHA 				= QSPI_CLKPHA_SECOND_EDGE;
	/* Initialize the SSTE member */
	QSPI_InitStruct->SSTE 					= ENABLE;
	/* Initialize the DFS member */
	QSPI_InitStruct->DFS 					= QSPI_DFS_8_BITS;
	/* Initialize the CFS member */
	QSPI_InitStruct->CFS 					= QSPI_CFS_1_BIT;
	/* Initialize the ClkDiv member */
	QSPI_InitStruct->ClkDiv 				= 12;
	/* Initialize the member */
	QSPI_InitStruct->RxDataNr				= 0;

	/* Initialize enhanced mode parameters value -----------------------------*/
	/* Initialize the ClkStretch member */
	QSPI_InitStruct->Enhance.ClkStretch 	= ENABLE;
	/* Initialize the AddrLen member */
	QSPI_InitStruct->Enhance.AddrLen 		= QSPI_ADDR_NONE;
	/* Initialize the InstLen member */
	QSPI_InitStruct->Enhance.InstLen 		= QSPI_INST_8_BITS;
	/* Initialize the WaitCycles member */
	QSPI_InitStruct->Enhance.WaitCycles 	= QSPI_WAIT_NONE;
	/* Initialize the TransferType member */
	QSPI_InitStruct->Enhance.TransferType 	= QSPI_TRANS_BOTH_STANDARD;

	/* Initialize XIP mode parameters value ----------------------------------*/
	/* Initialize the MD_BIT_EN member */
	QSPI_InitStruct->Enhance.MD_BIT_EN 		= DISABLE;
	/* Initialize the XIP_MBL member */
	QSPI_InitStruct->Enhance.XIP_MBL 		= QSPI_XIP_MBL_2_BITS;
	/* Initialize the XIP_CT_EN member */
	QSPI_InitStruct->Enhance.XIP_CT_EN 		= DISABLE;
	/* Initialize the XIP_INST_EN member */
	QSPI_InitStruct->Enhance.XIP_INST_EN 	= DISABLE;
	/* Initialize the XIP_DFS_HC member */
	QSPI_InitStruct->Enhance.XIP_DFS_HC 	= DISABLE;
	/* Initialize the INST_DDR_EN member */
	QSPI_InitStruct->Enhance.INST_DDR_EN 	= DISABLE;
	/* Initialize the SPI_DDR_EN member */
	QSPI_InitStruct->Enhance.SPI_DDR_EN 	= DISABLE;
	/* Initialize the XIP_MODE_BITS member */
	QSPI_InitStruct->Enhance.XIP_MODE_BITS	= 0x0000;
	/* Initialize the ITOC member */
	QSPI_InitStruct->Enhance.ITOC 			= 0x0000;
	/* Initialize the WTOC member */
	QSPI_InitStruct->Enhance.WTOC 			= 0x0000;
}
/**
  * @}
  */

/** @defgroup QSPI_Exported_Functions_Group2 IO operation functions
  * @brief    IO operation functions 
  * @{
  */
  
/**
  * @brief  Transmit the commands in indirect mode.
  * @param  Cmd Pointer to a QSPI_CommandType structure that contains
  *		    instruction and address.
  * @note   For Motorola format, this interface is only applicable to enhanced mode but not XIP mode.
  * 		In standard mode, there is no difference among instruction, address
  * 		and data, all transmitted are treated as data. In XIP mode, instruction is
  * 		stored in QSPI_XIP_INCR_TOC/SPI_XIP_WRP_TOC registers and address is specified
  * 		at execution time, such as "Data = *((uint32_t *)0x90000000);".
  * 		For Microwire format, this interface is only applicable when there is data to be transferred.
  * 		If only control frame need to be transmitted, use QSPI_Transmit().
  * @return None
  */
void QSPI_Command(QSPI_CommandType* Cmd)
{
	/* Check NULL pointer */
	if(!Cmd) { return; }
	/* Check busy status */
	if(__QSPI_GET_STS(QSPI_STATUS_BUSY) != RESET) { return; }

	/* Motorola SPI frame format */
	if(__QSPI_GET_FRF() == QSPI_FRF_SPI){
		/* Check line mode */
		if((__QSPI_GET_LINE_MODE() != QSPI_LINE_2_LINES && __QSPI_GET_LINE_MODE() != QSPI_LINE_4_LINES)
			|| (__QSPI_IS_XIP_ENABLED())) { return; }

		/* Set Transmit FIFO threshold the biggest value to avoid ending transmission early */
		__QSPI_SET_TXFIFO_TTHR(QSPI_TXFIFO_TTHR_32);
		/* Transmit instruction according to the configured length */
		if(__QSPI_GET_INST_LEN() != QSPI_INST_NONE){
			QSPI->DAT0 = Cmd->Instruction;
		}
		/* Transmit address according to the configured length */
		if(__QSPI_GET_ADDR_LEN() != QSPI_ADDR_NONE){
			QSPI->DAT0 = Cmd->AddressLow;
			/* Transmit high 32-bit address if address length is greater than 32 bits */
			if(__QSPI_GET_ADDR_LEN() > QSPI_ADDR_32_BITS){
				QSPI->DAT0 = Cmd->AddressHigh;
			}
		}
	}
	
	else if(__QSPI_GET_FRF() == QSPI_FRF_MICROWIRE){
		/* Set Transmit FIFO threshold the biggest value to avoid ending transmission early */
		__QSPI_SET_TXFIFO_TTHR(QSPI_TXFIFO_TTHR_32);
		/* Transmit control frame */
		QSPI->DAT0 = Cmd->Instruction;
	}

}

/**
  * @brief  Transmit data in indirect mode.
  * @param  pData Pointer to data buffer.
  * @param  Nr    Number of data frames to transmit.
  * @note   This interface is only applicable to standard mode and enhanced mode but not
  * 		XIP mode. Read only in XIP mode.
  * @note   The data to be transmitted should meet the following alignment requirements in buffer:
  *          - DFS <= 8 bits, 		   byte alignment;
  *          - 8 bits < DFS <= 16 bits, halfword alignment;
  *          - 16 bits < DFS <= 32bits, word alignment.
  * @return None
  */
void QSPI_Transmit(void* pData, uint32_t Nr)
{
	uint32_t timeout = 0;
	__IO uint32_t dfs = __QSPI_GET_DATA_LEN(); 		/* Get data frame length */
	__IO uint8_t fnr = 0;	/* Free items number in transmit FIFO */
	uint8_t *p = (uint8_t *)pData;
	uint32_t i = 0;

	/* Check parameter, line mode and status ---------------------------------*/
	if(!pData || !Nr) { return; }

	/* Set Transmit FIFO threshold according to current data number
	 * in FIFO and make sure to start transmitting after one more
	 * data is put in FIFO */
	__QSPI_SET_TXFIFO_TTHR((uint32_t)__QSPI_GET_TFIFO_NR_FILLED() << 16);
	/* Transmit data ---------------------------------------------------------*/
	while(i < Nr){
		/* Wait transmit FIFO not full */
		do{
			fnr = __QSPI_GET_TFIFO_NR_FREE();
		}while(!fnr && timeout++ < QSPI_TIMEOUT_VALUE);
		/* Abort if timeout */
		if(!fnr) {
			timeout = 0;
			break;
		}
		timeout = 0;
		/* Data frame size less than or equal to 8 bits, no need to pack */
		if(dfs <= QSPI_DFS_8_BITS){
			do{
				QSPI->DAT0 = (uint32_t)p[i];
				i++;
			}while(--fnr && i < Nr);
		}
		/* Data frame size greater than 8 bits but less than or equal to 16 bits,
		 * pack two 8-bit data into one 16-bit data */
		else if(dfs <= QSPI_DFS_16_BITS){
			do{
				QSPI->DAT0 = (uint32_t)((uint16_t *) p)[i];
				i++;
			}while(--fnr && i < Nr);
		}
		/* Data frame size greater than 16 bits, pack four 8-bit data into one 32-bit data */
		else{
			do{
				QSPI->DAT0 = (uint32_t)((uint32_t *) p)[i];
				i++;
			}while(--fnr && i < Nr);
		}
	}
	/* Wait for transmitting done --------------------------------------------*/
	while(__QSPI_GET_STS(QSPI_STATUS_BUSY) != RESET && timeout++ < QSPI_TIMEOUT_VALUE);
}

/**
  * @brief  Receive data in indirect mode.
  * @param  pData Pointer to data buffer.
  * @param  Nr    Number of data frames to receive.
  * @note   This interface is only applicable to standard mode and enhanced mode but not
  * 		XIP mode. In XIP mode, instruction is stored in QSPI_XIP_INCR_TOC/SPI_XIP_WRP_TOC
  * 		registers and address is specified at execution time, such as
  * 		"Data = *((uint32_t *)0x90000000);".
  * @note   The data to be received will be stored in the following alignment in buffer:
  *          - DFS <= 8 bits, 		   byte alignment;
  *          - 8 bits < DFS <= 16 bits, halfword alignment;
  *          - 16 bits < DFS <= 32bits, word alignment.
  * @return None
  */
void QSPI_Receive(void* pData, uint32_t Nr)
{
	uint32_t timeout = 0;
	__IO uint32_t dfs = __QSPI_GET_DATA_LEN(); /* Get data frame length */
	__IO uint32_t tmode = __QSPI_GET_TRANS_MODE(); /* Get transfer mode */
	uint8_t *p = (uint8_t *)pData;
	uint32_t i = 0;

	/* Check parameter, line mode and status ---------------------------------*/
	if(!pData || !Nr) { return; }

	/* Receive data ----------------------------------------------------------*/
	for(i = 0; i < Nr; i++){
		/* Wait receive FIFO not empty */
		while(__QSPI_GET_STS(QSPI_STATUS_RXFNE) == RESET && timeout++ < QSPI_TIMEOUT_VALUE);
		/* Abort if timeout */
		if(__QSPI_GET_STS(QSPI_STATUS_RXFNE) == RESET) {
			timeout = 0;
			break;
		}
		timeout = 0;
		/* Data frame size less than or equal to 8 bits, no need to unpack */
		if(dfs <= QSPI_DFS_8_BITS){
			p[i] = (uint8_t)QSPI->DAT0;
		}
		/* Data frame size greater than 8 bits but less than or equal to 16 bits,
		 * unpack 16-bit data into two 8-bit data */
		else if(dfs <= QSPI_DFS_16_BITS){
			((uint16_t *) p)[i] = (uint16_t)QSPI->DAT0;
		}
		/* Data frame size greater than 16 bits, unpack 32-bit data into four 8-bit data  */
		else{
			((uint32_t *) p)[i] = (uint32_t)QSPI->DAT0;
		}
	}
	/* Wait for receiving done -----------------------------------------------*/
	while(__QSPI_GET_STS(QSPI_STATUS_BUSY) != RESET && timeout++ < QSPI_TIMEOUT_VALUE);
}

/**
  * @brief  Clear receive FIFO.
  * @return None
  */
void QSPI_ClrRxFIFO(void)
{
	uint32_t timeout = 0;
	__IO uint32_t data;

	/* Read receive FIFO to empty */
	while(__QSPI_GET_STS(QSPI_STATUS_RXFNE) != RESET && ++timeout < QSPI_TIMEOUT_VALUE){
		data = QSPI->DAT0;
	}
}
/**
  * @}
  */
  
/** @defgroup QSPI_Exported_Functions_Group3 Peripheral Control functions
  * @brief    Peripheral Control functions 
  * @{
  */

/**
  * @brief  Enable or disable QSPI and slave.
  * @param  Cmd Select enable or disable QSPI and slave.
  * @return None
  */
void QSPI_Enable(FunctionalState Cmd)
{
	/* Check parameter */
	assert_param(IS_FUNCTIONAL_STATE(Cmd));

	if(Cmd == ENABLE){
		/* Enable slave */
		__QSPI_SLAVE_ENABLE();
		/* Enable QSPI */
		__QSPI_ENABLE();
	}else{
		__QSPI_SLAVE_DISABLE();
		__QSPI_DISABLE();
	}
}

/**
  * @brief  Enable or disable XIP slave.
  * @param  Cmd Select enable or disable QSPI and XIP slave.
  * @return None
  */
void QSPI_XIP_Enable(FunctionalState Cmd)
{
	/* Check parameter */
	assert_param(IS_FUNCTIONAL_STATE(Cmd));

	if(Cmd == ENABLE){
		/* Enable XIP slave */
		__QSPI_XIP_SLAVE_ENABLE();
	}else{
		__QSPI_XIP_SLAVE_DISABLE();
	}
}

/**
  * @brief  Configure QSPI DMA transfer.
  * @param  Cfg Pointer to a QSPI_DMAType structure that contains the configuration
  * 		information for QSPI DMA.
  * @return None
  */
void QSPI_DMAConfig(QSPI_DMAType* Cfg)
{
	__IO uint32_t tmpreg = 0;

	/* Check NULL pointer ----------------------------------------------------*/
	if(!Cfg) { return; }
	/* Check parameters ------------------------------------------------------*/
	assert_param(IS_QSPI_DMA_RX_MODE(Cfg->RX_DMA_EN));
	assert_param(IS_QSPI_DMA_TX_MODE(Cfg->TX_DMA_EN));
	if(Cfg->RX_DMA_EN == QSPI_DMA_RX_ENABLE){
		assert_param(IS_QSPI_DMA_RDL(Cfg->RDL));
	}
	if(Cfg->TX_DMA_EN == QSPI_DMA_TX_ENABLE){
		assert_param(IS_QSPI_DMA_TDL(Cfg->TDL));
	}

	/* Configure DMA_CTRL and QSPI_DMARDL/TDL_CTRL register ------------------*/
	tmpreg = QSPI->DMA_CTRL;
	/* Clear RX_DMA_EN and TX_DMA_EN bits */
	tmpreg &= (uint32_t)~(QSPI_DMA_CTRL_RX_DMA_EN | QSPI_DMA_CTRL_TX_DMA_EN);
	/* Set RX_DMA_EN and TX_DMA_EN bits according to Cfg.RX_DMA_EN and
	 * Cfg.TX_DMA_EN value */
	tmpreg |= (uint32_t)Cfg->RX_DMA_EN | (uint32_t)Cfg->TX_DMA_EN;
	/* Configure QSPI_DMARDL_CTRL and QSPI_DMATDL_CTRL registers */
	if(Cfg->RX_DMA_EN == QSPI_DMA_RX_ENABLE){
		QSPI->DMARDL_CTRL = (uint32_t)Cfg->RDL;
	}
	if(Cfg->TX_DMA_EN == QSPI_DMA_TX_ENABLE){
		QSPI->DMATDL_CTRL = (uint32_t)Cfg->TDL;
	}
	QSPI->DMA_CTRL = tmpreg;
}

/**
  * @brief  Configure microwire.
  * @param  Cfg Pointer to a QSPI_MicrowireType structure that contains the configuration
  * 		information for microwire.
  * @return None
  */
void QSPI_MicrowireConfig(QSPI_MicrowireType* Cfg)
{
	__IO uint32_t tmpreg = 0;

	/* Check NULL pointer ----------------------------------------------------*/
	if(!Cfg) { return; }
	/* Check parameters ------------------------------------------------------*/
	assert_param(IS_QSPI_MW_HS_MODE(Cfg->MHS_EN));
	assert_param(IS_QSPI_MW_DIR(Cfg->MC_DIR));
	assert_param(IS_QSPI_MW_MODE(Cfg->MWMOD));

	/* Configure QSPI_MW_CTRL register ---------------------------------------*/
	tmpreg = QSPI->MW_CTRL;
	/* Clear MHS_EN, MC_DIR and MWMOD bits */
	tmpreg &= (uint32_t)~(QSPI_MW_CTRL_MHS_EN | QSPI_MW_CTRL_MC_DIR | QSPI_MW_CTRL_MWMOD);
	/* Set MHS_EN, MC_DIR and MWMOD bits according to Cfg.MHS_EN,
	 * Cfg.MC_DIR and Cfg.MWMOD value */
	tmpreg |= (uint32_t)Cfg->MHS_EN | (uint32_t)Cfg->MC_DIR | (uint32_t)Cfg->MWMOD;
	QSPI->MW_CTRL = tmpreg;
}

/**
  * @brief  Configure GPIO used by QSPI.
  * @param  LineMode  The line mode that will be used to configure QSPI
  * 		This parameter can be one of the following values:
  *		        @arg QSPI_LINE_STANDARD		Standard SPI
  *		        @arg QSPI_LINE_2_LINES		Dual SPI
  *		        @arg QSPI_LINE_4_LINES		Quad SPI
  *		        @arg QSPI_LINE_2_LINES_XIP	Dual SPI in XIP mode
  *		        @arg QSPI_LINE_4_LINES_XIP	Quad SPI in XIP mode
  * @param  Port The I/Os group that will be used during data transmission
  * 		This parameter can be one of the following values:
  * 		    @arg QSPI_NSS_PORTA	NSS->PA4, CLK->PA5, IO0->PA6, IO1->PA7,
  * 		     	 IO2->PC4, IO3->PC5
  * 		    @arg QSPI_NSS_PORTC	NSS->PC10, CLK->PC11, IO0->PC12, IO1->PD0,
  * 		     	 IO2->PD1, IO3->PD2
  * 		    @arg QSPI_NSS_PORTF	NSS->PF0, CLK->PF1, IO0->PF2, IO1->PF3,
  * 		     	 IO2->PF4, IO3->PF5
  * @param IO2State	 IO2 high or low output state in standard and 2-line mode
  * 	   according to the connection with external flash.
  * 	   This parameter can be one of the following values:
  * 		  	@arg QSPI_IO_OUT_HIGH	Output high level
  * 		  	@arg QSPI_IO_OUT_LOW	Output lov level
  * @param IO3State	 IO3 high or low output state in standard and 2-line mode
  * 	   according to the connection with external flash.
  * 	   This parameter can be one of the following values:
  * 		  	@arg QSPI_IO_OUT_HIGH	Output high level
  * 		  	@arg QSPI_IO_OUT_LOW	Output lov level
  * @return None
  */
void QSPI_GPIOConfig(uint32_t LineMode, uint32_t Port, uint8_t IO2State, uint8_t IO3State)
{
	/* Check parameters ------------------------------------------------------*/
	assert_param(IS_QSPI_LINE_MODE(LineMode));
	assert_param(IS_QSPI_PORT(Port));
	/* Ignore IO2State and IO3State in 4-line mode  */
	if(LineMode == QSPI_LINE_STANDARD || LineMode == QSPI_LINE_2_LINES || LineMode == QSPI_LINE_2_LINES_XIP){
		assert_param(IS_QSPI_IO_OUT_STATE(IO2State));
		assert_param(IS_QSPI_IO_OUT_STATE(IO3State));
	}

	/* Configure GPIO according to port selection and QSPI line mode */
	switch(Port)
	{
	case QSPI_NSS_PORTA:
		/* Enable GPIO and AFIO clock */
		RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_GPIOC | RCC_APB2_PERIPH_AFIO, ENABLE);
		/* Disable I/O remap */
		GPIO_ConfigPinRemap(GPIO_RMP3_QSPI, DISABLE);

		/* Configure NSS, SCK, IO0, IO1, IO2 and IO3 pin */
		GPIO_Config(GPIOA, GPIO_PIN_4, GPIO_Mode_AF_PP);		/* NSS */
		GPIO_Config(GPIOA, GPIO_PIN_5, GPIO_Mode_AF_PP);		/* SCK */
		GPIO_Config(GPIOA, GPIO_PIN_6, GPIO_Mode_AF_PP);		/* IO0 */
		/* Set IO1 floating input mode in standard QSPI mode, set it alternate
		 * function push-pull output mode in other QSPI mode */
		if(LineMode == QSPI_LINE_STANDARD){
			GPIO_Config(GPIOA, GPIO_PIN_7, GPIO_Mode_IN_FLOATING);
		}else{
			GPIO_Config(GPIOA, GPIO_PIN_7, GPIO_Mode_AF_PP);
		}
		/* Set IO2 and IO3 push-pull output mode in standard or 2-line QSPI mode,
		 * set them alternate function push-pull output mode in 4-line QSPI mode */
		if(LineMode == QSPI_LINE_STANDARD || LineMode == QSPI_LINE_2_LINES || LineMode == QSPI_LINE_2_LINES_XIP){
			GPIO_Config(GPIOC, GPIO_PIN_4, GPIO_Mode_Out_PP);
			GPIO_Config(GPIOC, GPIO_PIN_5, GPIO_Mode_Out_PP);
			/* Set IO2 output state */
			if(IO2State == QSPI_IO_OUT_HIGH){
				GPIOC->PBSC |= GPIO_PIN_4;
			}else{
				GPIOC->PBC |= GPIO_PIN_4;
			}
			/* Set IO3 output state */
			if(IO3State == QSPI_IO_OUT_HIGH){
				GPIOC->PBSC |= GPIO_PIN_5;
			}else{
				GPIOC->PBC |= GPIO_PIN_5;
			}
		}else{
			GPIO_Config(GPIOC, GPIO_PIN_4, GPIO_Mode_AF_PP);
			GPIO_Config(GPIOC, GPIO_PIN_5, GPIO_Mode_AF_PP);
		}
		break;
	case QSPI_NSS_PORTC:
		RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC | RCC_APB2_PERIPH_GPIOD | RCC_APB2_PERIPH_AFIO, ENABLE);
		/* Enable I/O remap 3 */
		GPIO_ConfigPinRemap(GPIO_RMP3_QSPI, ENABLE);

		GPIO_Config(GPIOC, GPIO_PIN_10, GPIO_Mode_AF_PP);		/* NSS */
		GPIO_Config(GPIOC, GPIO_PIN_11, GPIO_Mode_AF_PP);		/* SCK */
		GPIO_Config(GPIOC, GPIO_PIN_12, GPIO_Mode_AF_PP);		/* IO0 */
		if(LineMode == QSPI_LINE_STANDARD){
			GPIO_Config(GPIOD, GPIO_PIN_0, GPIO_Mode_IN_FLOATING);	/* IO1 */
		}else{
			GPIO_Config(GPIOD, GPIO_PIN_0, GPIO_Mode_AF_PP);
		}
		if(LineMode == QSPI_LINE_STANDARD || LineMode == QSPI_LINE_2_LINES || LineMode == QSPI_LINE_2_LINES_XIP){
			GPIO_Config(GPIOD, GPIO_PIN_1, GPIO_Mode_Out_PP);	/* IO2 */
			GPIO_Config(GPIOD, GPIO_PIN_2, GPIO_Mode_Out_PP);	/* IO3 */
			if(IO2State == QSPI_IO_OUT_HIGH){
				GPIOD->PBSC |= GPIO_PIN_1;
			}else{
				GPIOD->PBC |= GPIO_PIN_1;
			}
			if(IO3State == QSPI_IO_OUT_HIGH){
				GPIOD->PBSC |= GPIO_PIN_2;
			}else{
				GPIOD->PBC |= GPIO_PIN_2;
			}
		}else{
			GPIO_Config(GPIOD, GPIO_PIN_1, GPIO_Mode_AF_PP);
			GPIO_Config(GPIOD, GPIO_PIN_2, GPIO_Mode_AF_PP);
		}
		break;;
	case QSPI_NSS_PORTF:
		RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOF | RCC_APB2_PERIPH_AFIO, ENABLE);
		/* Enable I/O remap 1 */
		GPIO_ConfigPinRemap(GPIO_RMP2_QSPI, ENABLE);

		GPIO_Config(GPIOF, GPIO_PIN_0, GPIO_Mode_AF_PP);		/* NSS */
		GPIO_Config(GPIOF, GPIO_PIN_1, GPIO_Mode_AF_PP);		/* SCK */
		GPIO_Config(GPIOF, GPIO_PIN_2, GPIO_Mode_AF_PP);		/* IO0 */
		if(LineMode == QSPI_LINE_STANDARD){
			GPIO_Config(GPIOF, GPIO_PIN_3, GPIO_Mode_IN_FLOATING);	/* IO1 */
		}else{
			GPIO_Config(GPIOF, GPIO_PIN_3, GPIO_Mode_AF_PP);
		}
		if(LineMode == QSPI_LINE_STANDARD || LineMode == QSPI_LINE_2_LINES || LineMode == QSPI_LINE_2_LINES_XIP){
			GPIO_Config(GPIOF, GPIO_PIN_4, GPIO_Mode_Out_PP);	/* IO2 */
			GPIO_Config(GPIOF, GPIO_PIN_5, GPIO_Mode_Out_PP);	/* IO3 */
			if(IO2State == QSPI_IO_OUT_HIGH){
				GPIOF->PBSC |= GPIO_PIN_4;
			}else{
				GPIOF->PBC |= GPIO_PIN_4;
			}
			if(IO3State == QSPI_IO_OUT_HIGH){
				GPIOF->PBSC |= GPIO_PIN_5;
			}else{
				GPIOF->PBC |= GPIO_PIN_5;
			}
		}else{
			GPIO_Config(GPIOF, GPIO_PIN_4, GPIO_Mode_AF_PP);
			GPIO_Config(GPIOF, GPIO_PIN_5, GPIO_Mode_AF_PP);
		}
		break;
	default:
		break;
	}
}

/**
  * @brief Enable or disable QSPI interrupt.
  * @param Int Specifies the QSPI interrupt type.
  *   	   This parameter can be one of the following values:
  *            @arg QSPI_INT_TXFEI	Transmit FIFO Empty
  *            @arg QSPI_INT_TXFOI	Transmit FIFO Overflow
  *            @arg QSPI_INT_RXFUI	Transmit FIFO Underflow
  *            @arg QSPI_INT_RXFOI	Receive FIFO Overflow
  *            @arg QSPI_INT_RXFFI	Receive FIFO Full
  *            @arg QSPI_INT_MMCI	Multi-Master Contention
  *            @arg QSPI_INT_XRXOI	XIP Receive FIFO Overflow
  * @param Cmd ENABLE or DISABLE command
  * @return None.
  */
void QSPI_INTConfig(uint8_t Int, FunctionalState Cmd)
{
	/* Check parameters */
	assert_param(IS_QSPI_INT(Int));
	assert_param(IS_FUNCTIONAL_STATE(Cmd));

	if(Cmd == ENABLE){
		/* Set transmit FIFO empty interrupt threshold */
		if(Int == QSPI_INT_TXFEI){
			MODIFY_REG(QSPI->TXFT, QSPI_TXFT_TEI, QSPI_TXFIFO_ITHR_1);
		}
		/* Set Receive FIFO full interrupt threshold */
		if(Int == QSPI_INT_RXFFI){
			MODIFY_REG(QSPI->RXFT, QSPI_RXFT_TFI, QSPI_RXFIFO_ITHR_32);
		}
		/* Unmask interrupt */
		SET_BIT(QSPI->IMASK, (uint32_t)Int);
	}else{
		/* Mask interrupt */
		CLEAR_BIT(QSPI->IMASK, (uint32_t)Int);
	}
}

/**
  * @brief Set wait cycles in enhanced(including XIP) mode.
  * @param WaitCycles Wait cycles value to set.
  *   	   This parameter can be a value of @ref QSPI_WaitCycles
  * @return None.
  */
void QSPI_SetWaitCycles(uint32_t WaitCycles)
{
	return;
}  
/**
  * @}
  */


/** @defgroup QSPI_Exported_Functions_Group4 QSPI Peripheral State functions
  * @brief   QSPI Peripheral State functions 
  * @{
  */
 
/**
  * @brief Checks whether the specified QSPI flag is set or not.
  * @param Status Specifies the QSPI flag to check.
  *   	   This parameter can be one of the following values:
  *            @arg QSPI_STATUS_BUSY	Transfer busy
  *            @arg QSPI_STATUS_TXFNF	Transmit FIFO not full
  *            @arg QSPI_STATUS_TXFE	Transmit FIFO empty
  *            @arg QSPI_STATUS_RXFNE	Receive FIFO not empty
  *            @arg QSPI_STATUS_RXFF	Receive FIFO full
  *            @arg QSPI_STATUS_TX_ERR	Transmit error
  *            @arg QSPI_STATUS_DC_ERR	Data conflict error
  * @note   TX_ERR and DC_ERR bits in QSPI_STS register are read clear.
  * @return The new QSPI status(SET or RESET).
  */
FlagStatus QSPI_GetStatus(uint8_t Status)
{
    FlagStatus bitstatus = RESET;

    /* Check parameter */
    assert_param(IS_QSPI_STATUS(Status));

    /* Get status */
    if(__QSPI_GET_STS(Status) != (uint8_t)RESET){
    	bitstatus = SET;
    }

    return bitstatus;
}

/**
  * @brief Clear QSPI error flag(other flags in QSPI_STS register are cleared
  * 	   by hardware).
  * @param ErrStatus Specifies the QSPI error flag to clear.
  *   	   This parameter can be one of the following values:
  *            @arg QSPI_STATUS_TX_ERR	Transmit error
  *            @arg QSPI_STATUS_DC_ERR	Data conflict error
  * @return None.
  */
void QSPI_ClrErrStatus(uint8_t ErrStatus)
{
	/* Check parameter */
	assert_param(IS_QSPI_ERR_STATUS(ErrStatus));

	/* Clear error status */
	__QSPI_CLR_STS(ErrStatus);
}

/**
  * @brief Checks whether the specified QSPI interrupt flag is set or not.
  * @param IntStatus Specifies the QSPI interrupt flag to check.
  *   	   This parameter can be one of the following values:
  *           @arg QSPI_INT_TXFEI	Transmit FIFO Empty
  *           @arg QSPI_INT_TXFOI	Transmit FIFO Overflow
  *           @arg QSPI_INT_RXFUI	Transmit FIFO Underflow
  *           @arg QSPI_INT_RXFOI	Receive FIFO Overflow
  *           @arg QSPI_INT_RXFFI	Receive FIFO Full
  *           @arg QSPI_INT_MMCI	Multi-Master Contention
  *           @arg QSPI_INT_XRXOI	XIP Receive FIFO Overflow
  * @return The new QSPI interrupt status(SET or RESET).
  */
INTStatus QSPI_GetIntStatus(uint8_t IntStatus)
{
	INTStatus bitstatus = RESET;

	/* Check parameter */
	assert_param(IS_QSPI_INT_STATUS(IntStatus));

	/* Get interrupt status */
	if(__QSPI_GET_INT_STS(IntStatus) != (uint8_t)RESET){
		bitstatus = SET;
	}

	return bitstatus;
}

/**
  * @brief Checks whether the specified QSPI raw interrupt flag is set or not.
  * @param RawIntStatus Specifies the QSPI raw interrupt flag to check.
  *   	  This parameter can be one of the following values:
  *           @arg QSPI_INT_TXFEI	Transmit FIFO Empty
  *           @arg QSPI_INT_TXFOI	Transmit FIFO Overflow
  *           @arg QSPI_INT_RXFUI	Transmit FIFO Underflow
  *           @arg QSPI_INT_RXFOI	Receive FIFO Overflow
  *           @arg QSPI_INT_RXFFI	Receive FIFO Full
  *           @arg QSPI_INT_MMCI	Multi-Master Contention
  *           @arg QSPI_INT_XRXOI	XIP Receive FIFO Overflow
  * @return The new QSPI raw interrupt status(SET or RESET).
  */
INTStatus QSPI_GetRawIntStatus(uint8_t RawIntStatus)
{
	INTStatus bitstatus = RESET;

	/* Check parameter */
	assert_param(IS_QSPI_INT_RAW_STATUS(RawIntStatus));

	/* Get raw interrupt status */
	if(__QSPI_GET_INT_RAW_STS(RawIntStatus) != (uint8_t)RESET){
		bitstatus = SET;
	}

	return bitstatus;
}

/**
  * @brief Clear QSPI interrupt flag.
  * @param IntStatus Specifies the QSPI interrupt flag to clear.
  *   	   This parameter can be one of the following values:
  *            @arg QSPI_INT_TXFOI	Transmit FIFO Overflow
  *            @arg QSPI_INT_RXFUI	Transmit FIFO Underflow
  *            @arg QSPI_INT_RXFOI	Receive FIFO Overflow
  *            @arg QSPI_INT_MMCI	Multi-Master Contention
  *            @arg QSPI_INT_XRXOI	XIP Receive FIFO Overflow
  * @return None.
  */
void QSPI_ClrIntStatus(uint8_t IntStatus)
{
	__IO uint32_t tmpreg = 0;

	/* Check parameter */
	assert_param(IS_QSPI_INT_CLR_STATUS(IntStatus));

	/* Clear interrupt status by reading the corresponding register */
	/* Transmit FIFO overflow interrupt */
	if(IntStatus == QSPI_INT_TXFOI){
		tmpreg = QSPI->TXFOI_CLR;
	}
	/* Receive FIFO overflow interrupt */
	else if(IntStatus == QSPI_INT_RXFUI){
		tmpreg = QSPI->RXFUI_CLR;
	}
	/* Receive FIFO underflow */
	else if(IntStatus == QSPI_INT_RXFOI){
		tmpreg = QSPI->RXFOI_CLR;
	}
	/* Multi-Master contention interrupt */
	else if(IntStatus == QSPI_INT_MMCI){
		tmpreg = QSPI->MMCI_CLR;
	}
	/* XIP receive FIFO overflow interrupt */
	else if(IntStatus == QSPI_INT_XRXOI){
		tmpreg = QSPI->XIP_RXFOI_CLR;
	}
	/* Transmit FIFO overflow interrupt, Receive FIFO overflow interrupt,
	 * Receive FIFO underflow and Multi-Master contention interrupt */
	else{
		tmpreg = QSPI->ICLR;
	}
	/* Avoid warning */
	(void)tmpreg;
}  
/**
  * @}
  */

/**
  * @}
  */
#endif /* DRIVER_MODULE_ENABLED_QSPI */

/**
  * @}
  */

/**
  * @}
  */
