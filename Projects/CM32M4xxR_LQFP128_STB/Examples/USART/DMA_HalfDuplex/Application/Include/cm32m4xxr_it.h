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
 * @file cm32m4xxr_it.h
 * @author CMIOT Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */
#ifndef __CM32M4xxR_IT_H__
#define __CM32M4xxR_IT_H__

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************/
/*                 N308 Processor Exceptions Handlers                         */
/*    Please uncommont the function declaration if used corresponding         */
/*                     peripheral interrupt.                                  */
/******************************************************************************/
void InsUnalign_EXCHandler(void); //TODO:..Need to change core_exception_handler() function's implementation if the exception and NMI functions have no argument.
//void InsAccFault_EXCHandler(void);
//void IlleIns_EXCHandler(void);
//void Break_EXCHandler(void);
//void LdAddrUnalign_EXCHandler(void);
//void LdFault_EXCHandler(void);
//void StAddrUnalign_EXCHandler(void);
//void StAccessFault_EXCHandler(void);
//void UmodeEcall_EXCHandler(void);
//void MmodeEcall_EXCHandler(void);

//void NMI_EXCHandler(void);

/******************************************************************************/
/*                  N308 Processor Interrupt Handlers                         */
/******************************************************************************/
void eclic_msip_handler(void);
void eclic_mtip_handler(void);

/******************************************************************************/
/*              CM32M4xxR Peripheral Interrupt Handlers                       */
/*    Please uncommont the function declaration if used corresponding         */
/*                     peripheral interrupt.                                  */
/******************************************************************************/

void USARTy_Tx_DMA_IRQHandler(void);
void USARTz_Rx_DMA_IRQHandler(void);


#ifdef __cplusplus
}
#endif

#endif /* __CM32M4xxR_IT_H__ */
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
