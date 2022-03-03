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
#include <string.h>
#include <stdio.h>
#include "nuclei_sdk_soc.h"
#include "log.h"
#include "qspi_flash.h"
#include "main.h"

/** @addtogroup CM32M4xxR_StdPeriph_Examples
 * @{
 */
__IO uint32_t	gTick = 0;	/* Systick counter in ms */

#define TX_DATA_NR		qFLASH_PAGESIZE
#define RX_DATA_NR		TX_DATA_NR

/** @addtogroup QSPI_QUAD
 * @{
 */

/**
 * @brief  Main function.
 */
int main(void)
{
	__IO uint32_t i = 0;
	uint8_t TxData[TX_DATA_NR] = {0};
	uint8_t RxData[RX_DATA_NR] = {0};

    /*SystemInit() function has been called by startup file startup_cm32m4xxr.s*/
	/* Initialize log port */
    log_init();
	log_info("This is a QSPI_QUAD demo-----------------------------------\n");
	/* Configure system tick */
	Systick_Configuration();

	/* QSPI 2/4 mode ---------------------------------------------------------*/
	/* Initialize QSPI to standard mode */
	qFLASH_Init(QSPI_LINE_STANDARD, QSPI_TRANSFER_TX_AND_RX, 0);
	/* Read Flash ID */
	if(qFLASH_ReadID() != qFLASH_ID){
		log_info("Wrong device ID!\n");
	}
	/* Erase one sector */
	qFLASH_EraseSector(0);
	/* Read Flash in dual mode */
	qFLASH_ReadBufferD(RxData, 0, RX_DATA_NR);
	log_info("Data read in 2-line mode...\n");
	for(i = 0; i < TX_DATA_NR / 4; i++){
		log_info("0x%08x\n", ((uint32_t *)RxData)[i]);
	}
	/* Write flash in quad mode */
	for(i = 0; i < TX_DATA_NR; i++){
		TxData[i] = (uint8_t)i;
	}
	/* Program flash in quad mode */
	qFLASH_QuadEnable();
	qFLASH_WritePageQ(TxData, 0, TX_DATA_NR);
	/* Read Flash in quad mode */
	memset(RxData, 0x00, RX_DATA_NR);
	qFLASH_ReadBufferQ(RxData, 0, RX_DATA_NR);
	log_info("Data read in 4-line mode...\n");
	for(i = 0; i < TX_DATA_NR / 4; i++){
		log_info("0x%08x\n", ((uint32_t *)RxData)[i]);
	}
	/* Check the operation result */
	if(memcmp(TxData, RxData, RX_DATA_NR) == 0){
		log_info("Pass!\n");
	}else{
		log_info("Fail!\n");
	}

    while (1)
    {
    }
}

/**
 * @brief  Configures system tick.
 */
void Systick_Configuration(void)
{
	/* Use core_aon_clk as systick clock */
	SysTimer_SetControlValue(SysTimer_GetControlValue() | SysTimer_MTIMECTL_CLKSRC_Msk);
	/* Set 1ms periodic interrupt */
	SysTick_Config(SYSTICK_1MS);
	/* Enable global interrupt */
	__enable_irq();
}

/**
  * @brief Get system tick value.
  */
uint32_t GetSystick(void)
{
	return gTick;
}

/**
 * @}
 */

/**
 * @}
 */
