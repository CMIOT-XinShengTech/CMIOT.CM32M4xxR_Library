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
 * @file cm32m4xxr_it.c
 * @author CMIOT Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */
#include "cm32m4xxr_it.h"
#include "main.h"

/** @addtogroup CM32M4xxR_StdPeriph_Template
 * @{
 */

extern const uint16_t I2S3_Buffer_Tx[32];
extern uint16_t I2S2_Buffer_Rx[32];
extern __IO uint32_t TxIdx;
extern __IO uint32_t RxIdx;

/******************************************************************************/
/*                 N308 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
 * @brief  This function handles NMI exception.
 */
void InsUnalign_EXCHandler(void)
{
	while(1)
	{
	
	}
}

/******************************************************************************/
/*                 N308 Processor Interrupt Handlers                          */
/******************************************************************************/

/**
 * @brief  This function handles software interrupt request.
 */
void eclic_msip_handler(void)
{

}

/**
 * @brief  This function handles TIMER interrupt request.
 */
void eclic_mtip_handler(void)
{

}


/******************************************************************************/
/* CM32M4xxR Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_cm32m4xxr.S).                    */
/******************************************************************************/

/**
 * @brief  This function handles SPI3_I2S3 global interrupt request.
 */
void SPI3_I2S3_IRQHandler(void)
{
    /* Check the interrupt source */
    if (SPI_I2S_GetIntStatus(SPI3, SPI_I2S_INT_TE) == SET)
    {
        /* Send a data from I2S3 */
        SPI_I2S_TransmitData(SPI3, I2S3_Buffer_Tx[TxIdx++]);
    }

    /* Check the end of buffer transfer */
    if (RxIdx == 32)
    {
        /* Disable the I2S3 TXE interrupt to end the communication */
        SPI_I2S_EnableInt(SPI3, SPI_I2S_INT_TE, DISABLE);
    }
}

/**
 * @brief  This function handles SPI2_I2S2 global interrupt request.
 */
void SPI2_I2S2_IRQHandler(void)
{
    /* Check the interrupt source */
    if (SPI_I2S_GetIntStatus(SPI2, SPI_I2S_INT_RNE) == SET)
    {
        /* Store the I2S2 received data in the relative data table */
        I2S2_Buffer_Rx[RxIdx++] = SPI_I2S_ReceiveData(SPI2);
    }
}


/**
 * @}
 */
