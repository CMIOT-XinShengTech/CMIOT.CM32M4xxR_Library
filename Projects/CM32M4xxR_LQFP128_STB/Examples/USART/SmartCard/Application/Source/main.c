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
 * @author CMIOT
 * @version v1.0.0
 *
 * @COPYRIGHT(c) 2020, China Mobile IOT. All rights reserved.
 */
#include <stdio.h>
#include "main.h"
#include "bsp.h"
#include "smartcard.h"

static void System_Init(void)
{
    log_init();
    log_info("System Init Finish!\r\n");
}


void Test_PSAM(void)
{
    int i = 0;
    SC_InitStructure SC_InitCfg;
    SC_State SCState = SC_POWER_OFF;
    SC_ADPU_Commands SC_ADPU;
    SC_ADPU_Responce SC_Responce;
    log_info("USARTx Smart_Card Test Start\r\n");
    SC_InitCfg.Clk_Div   = 10;//6;//14;    //SC_USART Clock set to (PCLK1 = SC_USART MHZ / Clk_Div) MHz
    SC_InitCfg.GT        = 16;
    SC_InitCfg.StopBits  = 3;
    SC_InitCfg.Parity    = 1;
    SC_InitCfg.NackEn    = 0;    // 0 - Disable NACK, 1 - Enable NACK
    SCState = SC_POWER_ON;
    SC_APDU_Init(&SC_ADPU, 0x00, SC_GET_A2R, 0x00, 0x00, 0x00, NULL, 0);
    while(SCState != SC_ACTIVE_ON_T0)
    {
        SC_Handler(&SCState, &SC_ADPU, &SC_Responce, &SC_InitCfg);
    }
    /* Apply the Procedure Type Selection (PTS) */
    SC_PTSConfig();
    delay_ms(10);
    SC_APDU_Init(&SC_ADPU, 0x00, 0x84, 0x00, 0x00, 0x00, NULL, 8);
    SC_Handler(&SCState, &SC_ADPU, &SC_Responce, &SC_InitCfg);
    delay_ms(10);
    for(i = 0; i < SC_ADPU.Body.LE; i++)
    {
        log_info("\r\n SC_Responce.Data[%d] = 0x%02x \r\n", i, SC_Responce.Data[i]);
    }
    log_info("\r\n SC_Responce.SW1 = 0x%02x \r\n", SC_Responce.SW1);
    log_info("\r\n SC_Responce.SW2 = 0x%02x \r\n", SC_Responce.SW2);
    if((SC_Responce.SW1 == 0x90) && (SC_Responce.SW2 == 0x00))
    {
        log_info("\r\n SmartCard command normally completed \r\n");
        log_info("get rand success!\r\n");
        for(i = 0; i < SC_ADPU.Body.LE; i++)
        {
            log_info("%02x ", SC_Responce.Data[i]);
        }
        log_info("\r\n");
    }
    else if((SC_Responce.SW1 == 0x6E) && (SC_Responce.SW2 == 0x00))
    {
        log_info("\r\n SmartCard CLA not supported \r\n");
    }
    else if((SC_Responce.SW1 == 0x6D) && (SC_Responce.SW2 == 0x00))
    {
        log_info("\r\n SmartCard CLA supported, but INS not programmed or invalid \r\n");
    }
    else if((SC_Responce.SW1 == 0x6B) && (SC_Responce.SW2 == 0x00))
    {
        log_info("\r\n SmartCard CLA INS supported, but P1 P2 incorrect \r\n");
    }
    else if((SC_Responce.SW1 == 0x67) && (SC_Responce.SW2 == 0x00))
    {
        log_info("\r\n SmartCard CLA INS P1 P2 supported, but P3 incorrect \r\n");
    }
    else if((SC_Responce.SW1 == 0x6F) && (SC_Responce.SW2 == 0x00))
    {
        log_info("\r\n SmartCard command not supported and no precise diagnosis given \r\n");
    }
//---------------------------------------------------------------------------//ÈÈ¸´Î»
    SC_HotReset_handle();
    SC_DeInit();
}


/** @addtogroup CM32M4xxR_StdPeriph_Examples
 * @{
 */

/**
 * @brief  Main program
 */
int main(void)
{
    System_Init();
    //while(1)
    {
        Test_PSAM();
        // SC_DeInit();
        log_info("PSAM test finish\r\n");
        delay_ms(1000);
    }
    while (1)
    {
    }
}

/**
 * @}
 */

/**
 * @}
 */
