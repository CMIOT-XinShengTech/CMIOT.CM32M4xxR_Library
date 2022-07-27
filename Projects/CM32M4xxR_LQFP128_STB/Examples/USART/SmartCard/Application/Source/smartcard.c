/*
  ******************************************************************************
  *
  * COPYRIGHT(c) 2020, China Mobile IOT
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of China Mobile IOT nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
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
  ******************************************************************************
  */ 

/**
 * @file smartcard.c
 * @author CMIOT
 * @version v1.0.0
 *
 * @COPYRIGHT(c) 2020, China Mobile IOT. All rights reserved.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "smartcard.h"
#include "bsp.h"
#include "main.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Global variables definition and initialization ----------------------------*/
SC_ATR SC_A2R;
uint8_t SC_ATR_Table[40];
static __IO uint8_t SCData = 0;
static uint32_t F_Table[16] = {0, 372, 558, 744, 1116, 1488, 1860, 0,
                               0, 512, 768, 1024, 1536, 2048, 0, 0
                              };
static uint32_t D_Table[16] = {0, 1, 2, 4, 8, 16, 32, 64,
                               12, 20, 0, 0, 0, 0, 0, 0
                              };

uint8_t F_HotReset = 0;


/* Private function prototypes -----------------------------------------------*/
/* Transport Layer -----------------------------------------------------------*/
/*--------------APDU-----------*/
// static void SC_SendData(SC_ADPU_Commands *SC_ADPU, SC_ADPU_Responce *SC_ResponceStatus);

/*------------ ATR ------------*/
// static void SC_AnswerReq(SC_State *SCState, uint8_t *card, uint8_t length);  /* Ask ATR */
// static uint8_t SC_decode_Answer2reset(uint8_t *card);  /* Decode ATR */

/* Physical Port Layer -------------------------------------------------------*/
// static void SC1_Init(SC_InitStructure *SC_InitCfg);
// void SC1_DeInit(void);

static ErrorStatus USART_ByteReceive(uint8_t *Data, uint32_t TimeOut);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes all peripheral used for Smartcard interface.
  * @param  None
  * @retval None
  */
static void SC_Init(SC_InitStructure *SC_InitCfg)
{
    GPIO_InitType GPIO_InitStructure;
    USART_InitType USART_InitStructure;
    USART_ClockInitType USART_ClockInitStructure;
    RCC_ClocksType RCC_ClocksStatus;
    /* Enable GPIO clocks */
    RCC_EnableAPB2PeriphClk(SC_PIN_RESET_GPIO_CLK | SC_USART_GPIO_CLK, ENABLE);
    /* Enable USART clock */
    SC_USART_APBxClkCmd(SC_USART_CLK, ENABLE);
    /* Initialize GPIO_InitStructure */
    GPIO_InitStruct(&GPIO_InitStructure);
    /* Configure USART CK pin as alternate function push-pull */
    GPIO_InitStructure.Pin        		= SC_USART_PIN_CK;
    GPIO_InitStructure.GPIO_Mode        = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed       = GPIO_Speed_50MHz;
    GPIO_Init(SC_USART_GPIO, &GPIO_InitStructure);
    /* Configure USART Tx pin as alternate function open-drain */
	GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin         		= SC_USART_PIN_TX;
    GPIO_InitStructure.GPIO_Mode      = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed       = GPIO_Speed_50MHz;
    GPIO_Init(SC_USART_GPIO, &GPIO_InitStructure);
    /* Configure Smartcard Reset pin */
	GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin = SC_PIN_RESET;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SC_PIN_RESET_GPIO, &GPIO_InitStructure);
	/* Configure SmartCard VCC Pin */
	GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin = SC_PIN_VCC;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SC_PIN_VCC_GPIO, &GPIO_InitStructure);
		
	/* Set RSTIN HIGH 复位管脚初始值*/
	SC_Reset(Bit_SET);
	/* Set VCC LOW 关闭智能卡供电*/
	SC_Power(Bit_RESET);
		
	USART_DeInit(SC_USART);
    /* SC_USART configuration ----------------------------------------------------*/
    /* SC_USART configured as follow:
        - Word Length = 9 Bits
        - 0.5 Stop Bit
        - Even parity
        - BaudRate = 9677 baud
        - Hardware flow control disabled (RTS and CTS signals)
        - Tx and Rx enabled
        - USART Clock enabled
    */
    /* SC_USART Clock set to 2.7MHz (PCLK1 = 27 MHZ / 10) */
    USART_SetPrescaler(SC_USART, SC_InitCfg->Clk_Div >> 1);
    /* USART Guard Time set to 16 Bit */
    USART_SetGuardTime(SC_USART, SC_InitCfg->GT);
    USART_ClockInitStructure.Clock 		= USART_CLK_ENABLE;
    USART_ClockInitStructure.Polarity 	= USART_CLKPOL_LOW;
    USART_ClockInitStructure.Phase 		= USART_CLKPHA_1EDGE;
    USART_ClockInitStructure.LastBit 	= USART_CLKLB_ENABLE;
    USART_ClockInit(SC_USART, &USART_ClockInitStructure);
    RCC_GetClocksFreqValue(&RCC_ClocksStatus);
    //USART_InitStructure.BaudRate = RCC_ClocksStatus.Pclk2Freq / (372 * ((SC_USART->GTP & (uint16_t)0x00FF) * 2));
    USART_InitStructure.BaudRate = RCC_ClocksStatus.Pclk1Freq / (372 * ((SC_USART->GTP & (uint16_t)0x00FF) * 2));	// PCLK1/372/LCK_DIV
    USART_InitStructure.WordLength = USART_WL_9B;
    if(SC_InitCfg->StopBits == 1)
    {
        USART_InitStructure.StopBits = USART_STPB_0_5;
    }
    else if(SC_InitCfg->StopBits == 3)
    {
        USART_InitStructure.StopBits = USART_STPB_1_5;
    }
    else
    {
        log_info("\r\n StopBits value is error !!! \r\n");
    }
    if(SC_InitCfg->Parity == 1)
    {
        USART_InitStructure.Parity = USART_PE_EVEN;
    }
    else if(SC_InitCfg->Parity == 2)
    {
        USART_InitStructure.Parity = USART_PE_ODD;
    }
    else
    {
        log_info("\r\n Parity value is error !!! \r\n");
    }
    USART_InitStructure.Mode                  = USART_MODE_RX | USART_MODE_TX;
    USART_InitStructure.HardwareFlowControl   = USART_HFCTRL_NONE;
    USART_Init(SC_USART, &USART_InitStructure);
    /* Enable the SC_USART Parity Error Interrupt */
    USART_ConfigInt(SC_USART, USART_INT_PEF, ENABLE);
    /* Enable the SC_USART Framing Error Interrupt */
    USART_ConfigInt(SC_USART, USART_INT_ERRF, ENABLE);
    /* Enable SC_USART */
    USART_Enable(SC_USART, ENABLE);
    /* Enable the NACK Transmission */
    if(SC_InitCfg->NackEn == 0)
    {
        USART_SetSmartCardNACK(SC_USART, DISABLE);
    }
    else if(SC_InitCfg->NackEn == 1)
    {
        USART_SetSmartCardNACK(SC_USART, ENABLE);
    }
    else
    {
        log_info("\r\n NACK Enable value is error !!! \r\n");
    }
    /* Enable the Smartcard Interface */
    USART_EnableSmartCard(SC_USART, ENABLE);
		
	/* Set VCC HIGH 开启智能卡供电*/
	SC_Power(Bit_SET);
    /* Set RSTIN LOW 卡开始复位*/
    SC_Reset(Bit_RESET);
	delay_ms(1);
	/* Set RSTIN HIGH 复位结束*/
    SC_Reset(Bit_SET);
}

/**
  * @brief  Deinitializes all ressources used by the Smartcard interface.
  * @param  None
  * @retval None
  */
void SC_DeInit(void)
{
    /* Deinitializes the SC_USART */
    USART_DeInit(SC_USART);
    GPIO_DeInit(SC_PIN_RESET_GPIO);
	GPIO_DeInit(SC_PIN_VCC_GPIO);
	GPIO_DeInit(SC_PIN_VPP_GPIO);
    /* Disable GPIO clocks */
    RCC_EnableAPB2PeriphClk(SC_PIN_RESET_GPIO_CLK | SC_PIN_VCC_GPIO_CLK | SC_PIN_VPP_GPIO_CLK| SC_USART_GPIO_CLK, DISABLE);
    /* Disable SC_USART clock */
    SC_USART_APBxClkCmd(SC_USART_CLK, DISABLE);
}

/**
  * @brief  Sets or clears the Smartcard reset pin.
  * @param  ResetState: this parameter specifies the state of the Smartcard
  *   reset pin. BitVal must be one of the BitAction enum values:
  *     @arg Bit_RESET: to clear the port pin.
  *     @arg Bit_SET: to set the port pin.
  * @retval None
  */
void SC_Reset(Bit_OperateType ResetState)
{
    GPIO_WriteBit(SC_PIN_RESET_GPIO, SC_PIN_RESET, ResetState);
}

/**
  * @brief  Enables or disables the power to the Smartcard.
  * @param  VccState: new state of the Smartcard power supply.
  *         This parameter can be: Bit_SET or Bit_RESET.
  * @retval None
  */
void SC_Power(Bit_OperateType VccState)
{
	GPIO_WriteBit(SC_PIN_VCC_GPIO, SC_PIN_VCC, VccState);
}

/**
  * @brief  Resends the byte that failed to be received (by the Smartcard) correctly.
  * @param  None
  * @retval None
  */
void SC_ParityErrorHandler(void)
{
    USART_SendData(SC_USART, SCData);
    while(USART_GetFlagStatus(SC_USART, USART_FLAG_TXC) == RESET)
    {
    }
}

/**
  * @brief  Configures the IO speed (BaudRate) communication.
  * @param  None
  * @retval None
  */
void SC_PTSConfig(void)
{
    RCC_ClocksType RCC_ClocksStatus;
    uint32_t workingbaudrate = 0, apbclock = 0;
    uint8_t locData = 0, PTSConfirmStatus = 1;
    uint8_t locData2 = 0;
    uint8_t locData3 = 0;
    uint8_t locData4 = 0;
    USART_InitType USART_InitStructure;
    USART_ClockInitType USART_ClockInitStructure;
    /* Reconfigure the USART Baud Rate -------------------------------------------*/
    //RCC_GetClocksFreq(&RCC_ClocksStatus);
    RCC_GetClocksFreqValue(&RCC_ClocksStatus);
    //apbclock = RCC_ClocksStatus.Pclk2Freq;
    apbclock = RCC_ClocksStatus.Pclk1Freq;
    apbclock /= ((SC_USART->GTP & (uint16_t)0x00FF) * 2);
    /* Enable the DMA Receive (Set DMAR bit only) to enable interrupt generation
    in case of a framing error FE */
    USART_EnableDMA(SC_USART, USART_DMAREQ_RX, ENABLE);
    if((SC_A2R.T0 & (uint8_t)0x10) == 0x10)
    {
        if(SC_A2R.T[0] != 0x11)
        {
            /* Send PTSS */
            SCData = 0xFF;
            USART_SendData(SC_USART, SCData);
            while(USART_GetFlagStatus(SC_USART, USART_FLAG_TXC) == RESET)
            {
            }
            /* Send PTS0 */
            SCData = 0x10;
            USART_SendData(SC_USART, SCData);
            while(USART_GetFlagStatus(SC_USART, USART_FLAG_TXC) == RESET)
            {
            }
            /* Send PTS1 */
            SCData = SC_A2R.T[0];
            USART_SendData(SC_USART, SCData);
            while(USART_GetFlagStatus(SC_USART, USART_FLAG_TXC) == RESET)
            {
            }
            /* Send PCK */
            SCData = (uint8_t)0xFF ^ (uint8_t)0x10 ^ (uint8_t)SC_A2R.T[0];
            USART_SendData(SC_USART, SCData);
            while(USART_GetFlagStatus(SC_USART, USART_FLAG_TXC) == RESET)
            {
            }
            /* Disable the DMA Receive (Reset DMAR bit only) */
            USART_EnableDMA(SC_USART, USART_DMAREQ_RX, DISABLE);
            if((USART_ByteReceive(&locData, SC_RECEIVE_TIMEOUT)) == SUCCESS)
            {
                if(locData != 0xFF)
                {
                    PTSConfirmStatus = 0x00;
                }
            }
            if((USART_ByteReceive(&locData2, SC_RECEIVE_TIMEOUT)) == SUCCESS)
            {
                if(locData2 != 0x10)
                {
                    PTSConfirmStatus = 0x00;
                }
            }
            if((USART_ByteReceive(&locData3, SC_RECEIVE_TIMEOUT)) == SUCCESS)
            {
                if(locData3 != SC_A2R.T[0])
                {
                    PTSConfirmStatus = 0x00;
                }
            }
            if((USART_ByteReceive(&locData4, SC_RECEIVE_TIMEOUT)) == SUCCESS)
            {
                if(locData4 != ((uint8_t)0xFF ^ (uint8_t)0x10 ^ (uint8_t)SC_A2R.T[0]))
                {
                    PTSConfirmStatus = 0x00;
                }
            }
            else
            {
                PTSConfirmStatus = 0x00;
            }
            log_info(" locData =%02x\r\n", locData);
            log_info(" locData2 =%02x\r\n", locData2);
            log_info(" locData3 =%02x\r\n", locData3);
            log_info(" locData4 =%02x\r\n", locData4);
            log_info(" PTSConfirmStatus =%d\r\n", PTSConfirmStatus);
            /* PTS Confirm */
            if(PTSConfirmStatus == 0x01)
            {
                workingbaudrate = apbclock * D_Table[(SC_A2R.T[0] & (uint8_t)0x0F)];
                workingbaudrate /= F_Table[((SC_A2R.T[0] >> 4) & (uint8_t)0x0F)];
                USART_ClockInitStructure.Clock          = USART_CLK_ENABLE;
                USART_ClockInitStructure.Polarity       = USART_CLKPOL_LOW;
                USART_ClockInitStructure.Phase          = USART_CLKPHA_1EDGE;
                USART_ClockInitStructure.LastBit        = USART_CLKLB_ENABLE;
                USART_ClockInit(SC_USART, &USART_ClockInitStructure);
                log_info(" bps =%d\r\n", workingbaudrate);
                USART_InitStructure.BaudRate            = workingbaudrate;
                USART_InitStructure.WordLength          = USART_WL_9B;
                USART_InitStructure.StopBits            = USART_STPB_1_5;
                USART_InitStructure.Parity              = USART_PE_EVEN;
                USART_InitStructure.Mode                = USART_MODE_RX | USART_MODE_TX;
                USART_InitStructure.HardwareFlowControl = USART_HFCTRL_NONE;
                USART_Init(SC_USART, &USART_InitStructure);
            }
            else
            {
                //pps fail，HotReset
                SC_HotReset_handle();
            }
        }
    }
}

/**
  * @brief  Manages the Smartcard transport layer: send APDU commands and receives
  *   the APDU responce.
  * @param  SC_ADPU: pointer to a SC_ADPU_Commands structure which will be initialized.
  * @param  SC_Response: pointer to a SC_ADPU_Responce structure which will be initialized.
  * @retval None
  */
static void SC_SendData(SC_ADPU_Commands *SC_ADPU, SC_ADPU_Responce *SC_ResponceStatus)
#if 1
{
    uint32_t i = 0;
    uint32_t number = 0;
    uint8_t locData = 0;
    /* Reset responce buffer ---------------------------------------------------*/
    for(i = 0; i < LC_MAX; i++)
    {
        SC_ResponceStatus->Data[i] = 0;
    }
    log_info("\r\nSC_ADPU:0x%x", SC_ADPU->Header.CLA);
    log_info(" 0x%x", SC_ADPU->Header.INS);
    log_info(" 0x%x", SC_ADPU->Header.P1);
    log_info(" 0x%x", SC_ADPU->Header.P2);
    log_info(" 0x%x\r\n", SC_ADPU->Body.LC);
    SC_ResponceStatus->SW1 = 0;
    SC_ResponceStatus->SW2 = 0;
    /* Enable the DMA Receive (Set DMAR bit only) to enable interrupt generation
    in case of a framing error FE */
    // USART_DMACmd(SC_USART, USART_DMAReq_Rx, ENABLE);
    /* Send header -------------------------------------------------------------*/
    SCData = SC_ADPU->Header.CLA;
    USART_SendData(SC_USART, SCData);
    while(USART_GetFlagStatus(SC_USART, USART_FLAG_TXC) == RESET)
    {
    }
    SCData = SC_ADPU->Header.INS;
    USART_SendData(SC_USART, SCData);
    while(USART_GetFlagStatus(SC_USART, USART_FLAG_TXC) == RESET)
    {
    }
    SCData = SC_ADPU->Header.P1;
    USART_SendData(SC_USART, SCData);
    while(USART_GetFlagStatus(SC_USART, USART_FLAG_TXC) == RESET)
    {
    }
    SCData = SC_ADPU->Header.P2;
    USART_SendData(SC_USART, SCData);
    while(USART_GetFlagStatus(SC_USART, USART_FLAG_TXC) == RESET)
    {
    }
    /* Send body length to/from SC ---------------------------------------------*/
    if(SC_ADPU->Body.LC)
    {
        SCData = SC_ADPU->Body.LC;
        USART_SendData(SC_USART, SCData);
        while(USART_GetFlagStatus(SC_USART, USART_FLAG_TXC) == RESET)
        {
        }
    }
    else if(SC_ADPU->Body.LE)
    {
        SCData = SC_ADPU->Body.LE;
        USART_SendData(SC_USART, SCData);
        while(USART_GetFlagStatus(SC_USART, USART_FLAG_TXC) == RESET)
        {
        }
    }
    /* Flush the SC_USART DAT */
    (void)USART_ReceiveData(SC_USART);
    /* --------------------------------------------------------
    Wait Procedure byte from card:
    1 - ACK
    2 - NULL
    3 - SW1; SW2
    -------------------------------------------------------- */
    while(1)
    {
        if((USART_ByteReceive(&locData, SC_RECEIVE_TIMEOUT)) == SUCCESS)
        {
            if(locData != 0x60) //空操作的过程字节NULL(0x60),不进行超时处理，继续等待
            {
                if(((locData & (uint8_t)0xFE) == (((uint8_t)~(SC_ADPU->Header.INS)) & \
                                                  (uint8_t)0xFE)) || ((locData & (uint8_t)0xFE) == (SC_ADPU->Header.INS & (uint8_t)0xFE)))
                {
                    SC_ResponceStatus->Data[0] = locData;/* ACK received */
                    break;
                }
                else if(((locData & (uint8_t)0xF0) == 0x60) || ((locData & (uint8_t)0xF0) == 0x90))//状态字第一个字节SW1，no ation
                {
                    SC_ResponceStatus->SW1 = locData;
                    if((USART_ByteReceive(&locData, SC_RECEIVE_TIMEOUT)) == SUCCESS)
                    {
                        /* SW2 received */
                        if(((locData & (uint8_t)0xF0) == 0x60) || ((locData & (uint8_t)0xF0) == 0x90))
                        {
                            SC_ResponceStatus->SW2 = locData;
                        }
                    }
                    break;
                }
                else //NULL
                {
                    SC_ResponceStatus->Data[number] = locData;
                    number++;
                    for(; number < (SC_ADPU->Body.LC); number++)
                    {
                        if((USART_ByteReceive(&locData, SC_RECEIVE_TIMEOUT)) == SUCCESS)
                        {
                            if(((locData & (uint8_t)0xF0) == 0x60) || ((locData & (uint8_t)0xF0) == 0x90))
                            {
                                SC_ResponceStatus->Data[number] = locData;
                            }
                            //log_info("%x , %d\r\n", locData, number);
                        }
                    }
                    /* SW1 received */
                    if((USART_ByteReceive(&locData, SC_RECEIVE_TIMEOUT)) == SUCCESS)
                    {
                        if(((locData & (uint8_t)0xF0) == 0x60) || ((locData & (uint8_t)0xF0) == 0x90))
                        {
                            SC_ResponceStatus->SW1 = locData;
                        }
                    }
                    if((USART_ByteReceive(&locData, SC_RECEIVE_TIMEOUT)) == SUCCESS)
                    {
                        /* SW2 received */
                        if(((locData & (uint8_t)0xF0) == 0x60) || ((locData & (uint8_t)0xF0) == 0x90))
                        {
                            SC_ResponceStatus->SW2 = locData;
                        }
                    }
                    break;
                }
            }
        }
    }
    /* If no status bytes received ---------------------------------------------*/
    if(SC_ResponceStatus->SW1 == 0x00)
    {
        /* Send body data to SC--------------------------------------------------*/
        if (SC_ADPU->Body.LC)
        {
            for(i = 0; i < SC_ADPU->Body.LC; i++)
            {
                SCData = SC_ADPU->Body.Data[i];
                USART_SendData(SC_USART, SCData);
                while(USART_GetFlagStatus(SC_USART, USART_FLAG_TXC) == RESET)
                {
                }
            }
            /* Flush the SC_USART DR */
            (void)USART_ReceiveData(SC_USART);
            /* Disable the DMA Receive (Reset DMAR bit only) */
            USART_EnableDMA(SC_USART, USART_DMAREQ_RX, DISABLE);
        }
        /* Or receive body data from SC ------------------------------------------*/
        else if (SC_ADPU->Body.LE)
        {
            for(i = 0; i < SC_ADPU->Body.LE; i++)
            {
                if(USART_ByteReceive(&locData, SC_RECEIVE_TIMEOUT) == SUCCESS)
                {
                    SC_ResponceStatus->Data[i] = locData;
                }
            }
        }
        /* Wait SW1 --------------------------------------------------------------*/
        i = 0;
        while(i < 10)
        {
            if(USART_ByteReceive(&locData, SC_RECEIVE_TIMEOUT) == SUCCESS)
            {
                SC_ResponceStatus->SW1 = locData;
                i = 11;
            }
            else
            {
                i++;
            }
        }
        /* Wait SW2 ------------------------------------------------------------*/
        i = 0;
        while(i < 10)
        {
            if(USART_ByteReceive(&locData, SC_RECEIVE_TIMEOUT) == SUCCESS)
            {
                SC_ResponceStatus->SW2 = locData;
                i = 11;
            }
            else
            {
                i++;
            }
        }
    }
}


#endif

/**
  * @brief  Requests the reset answer from card.
  * @param  SCState: pointer to an SC_State enumeration that will contain the Smartcard state.
  * @param  card: pointer to a buffer which will contain the card ATR.
  * @param  length: maximum ATR length
  * @retval None
  */
static void SC_AnswerReq(SC_State *SCState, uint8_t *card, uint8_t length)
{
    uint8_t Data = 0;
    uint32_t i = 0;
    uint32_t number = 0;
    //log_info("SC_AnswerReq *SCState = %d \r\n", *SCState);
    switch(*SCState)
    {
    case SC_RESET_LOW:
        //log_info(" SC_RESET_LOW\r\n");
        /* Check responce with reset low ---------------------------------------
        */
        while(i < (length))
        {
            i++;
						GPIO_WriteBit(GPIOC, GPIO_PIN_8, (Bit_OperateType)(1 - GPIO_ReadOutputDataBit(GPIOC, GPIO_PIN_8)));
            if((USART_ByteReceive(&Data, SC_RECEIVE_TIMEOUT)) == SUCCESS)
            {
                card[number] = Data;
                number++;
                //log_info(" SC_AnswerReq SC_RESET_LOW Rece success card[%d] = %02x\r\n",i,card[i]);
            }
        }
        /*
        for (i = 0; i < length; i++)
        {
        if((USART_ByteReceive(&Data, SC_RECEIVE_TIMEOUT)) == SUCCESS)
        {
            card[i] = Data;
            //log_info(" SC_AnswerReq SC_RESET_LOW Rece success card[%d] = %02x\r\n",i,card[i]);
        }
        }

        */
        if(card[0])
        {
            (*SCState) = SC_ACTIVE;
            //
            SC_Reset(Bit_SET);/* Reset High */
        }
        else
        {
            (*SCState) = SC_RESET_HIGH;
        }
        break;
    case SC_RESET_HIGH:
        //log_info(" SC_RESET_HIGH\r\n");
        /* Check responce with reset high --------------------------------------*/
        SC_Reset(Bit_SET); /* Reset High */
        while(i < length )
        {
            i++;
            if((USART_ByteReceive(&Data, SC_RECEIVE_TIMEOUT)) == SUCCESS)
            {
                card[number] = Data;
                number++;
                //log_info(" SC_AnswerReq SC_RESET_LOW Rece success card[%d] = %02x\r\n",i,card[i]);
            }
        }
        /*
        for (i = 0; i < length; i++)
        {
            if((USART_ByteReceive(&Data, SC_RECEIVE_TIMEOUT)) == SUCCESS)
            {
                card[i] = Data;
                //log_info(" SC_AnswerReq SC_RESET_LOW Rece success card[%d] = %02x\r\n",i,card[i]);
            }
        }
        */
        if(card[0])
        {
            (*SCState) = SC_ACTIVE;
        }
        else
        {
            (*SCState) = SC_POWER_OFF;
        }
        break;
    case SC_ACTIVE:
        log_info(" SC_ACTIVE\r\n");
        break;
    case SC_POWER_OFF:
        log_info(" SC_POWER_OFF\r\n");
        /* Close Connection if no answer received ------------------------------*/
        SC_Reset(Bit_SET); /* Reset high - a bit is used as level shifter from 3.3 to 5 V */
        break;
    default:
        (*SCState) = SC_RESET_LOW;
    }
}

/**
  * @brief  Decodes the Answer to reset received from card.
  * @param  card: pointer to the buffer containing the card ATR.
  * @retval None
  */
static uint8_t SC_decode_Answer2reset(uint8_t *card)
{
    uint32_t i = 0, flag = 0, buf = 0, protocol = 0;
    SC_A2R.TS = card[0];  /* Initial character */
    SC_A2R.T0 = card[1];  /* Format character */
    SC_A2R.Hlength = SC_A2R.T0 & (uint8_t)0x0F;
    if ((SC_A2R.T0 & (uint8_t)0x80) == 0x80)
    {
        flag = 1;
    }
    for (i = 0; i < 4; i++)
    {
        SC_A2R.Tlength = SC_A2R.Tlength + (((SC_A2R.T0 & (uint8_t)0xF0) >> (4 + i)) & (uint8_t)0x1);
    }
    for (i = 0; i < SC_A2R.Tlength; i++)
    {
        SC_A2R.T[i] = card[i + 2];
    }
    protocol = SC_A2R.T[SC_A2R.Tlength - 1] & (uint8_t)0x0F;
    while (flag)
    {
        if ((SC_A2R.T[SC_A2R.Tlength - 1] & (uint8_t)0x80) == 0x80)
        {
            flag = 1;
        }
        else
        {
            flag = 0;
        }
        buf = SC_A2R.Tlength;
        SC_A2R.Tlength = 0;
        for (i = 0; i < 4; i++)
        {
            SC_A2R.Tlength = SC_A2R.Tlength + (((SC_A2R.T[buf - 1] & (uint8_t)0xF0) >> (4 + i)) & (uint8_t)0x1);
        }
        for (i = 0; i < SC_A2R.Tlength; i++)
        {
            SC_A2R.T[buf + i] = card[i + 2 + buf];
        }
        SC_A2R.Tlength += (uint8_t)buf;
    }
    for (i = 0; i < SC_A2R.Hlength; i++)
    {
        SC_A2R.H[i] = card[i + 2 + SC_A2R.Tlength];
    }
    return (uint8_t)protocol;
}

/**
  * @brief  Receives a new data while the time out not elapsed.
  * @param  None
  * @retval An ErrorStatus enumuration value:
  *          - SUCCESS: New data has been received
  *          - ERROR: time out was elapsed and no further data is received
  */
static ErrorStatus USART_ByteReceive(uint8_t *Data, uint32_t TimeOut)
{
    uint32_t Counter = 0;
    while((USART_GetFlagStatus(SC_USART, USART_FLAG_RXDNE) == RESET) && (Counter != TimeOut))
    {
        Counter++;
    }
    if(Counter != TimeOut)
    {
        *Data = (uint8_t)USART_ReceiveData(SC_USART);
				//log_info("Counter = %x \r\n", Counter);
        return SUCCESS;
    }
    else
    {
				//log_info("Counter = %x \r\n", Counter);
        return ERROR;
    }
}

void SC_APDU_Init(SC_ADPU_Commands *SC_ADPU, uint8_t SC_APDU_CLA, uint8_t SC_APDU_INS, uint8_t SC_APDU_P1, uint8_t SC_APDU_P2,
                  uint8_t SC_APDU_LC, uint8_t *SC_APDU_Data, uint8_t SC_APDU_LE)
{
    SC_ADPU->Header.CLA  = SC_APDU_CLA;
    SC_ADPU->Header.INS  = SC_APDU_INS;
    SC_ADPU->Header.P1   = SC_APDU_P1;
    SC_ADPU->Header.P2   = SC_APDU_P2;
    SC_ADPU->Body.LC     = SC_APDU_LC;
    if(SC_ADPU->Body.LC)
    {
        memcpy(SC_ADPU->Body.Data, SC_APDU_Data, SC_ADPU->Body.LC);
    }
    if(SC_ADPU->Body.LC < LC_MAX)
    {
        memset(SC_ADPU->Body.Data + SC_ADPU->Body.LC, 0, LC_MAX - SC_ADPU->Body.LC);
        // SC_ADPU.Body.Data[i++] = 0;
    }
    if(SC_APDU_LE != 0x00)
    {
        SC_ADPU->Body.LE = SC_APDU_LE;
    }
}

/**
  * @brief  Handles all Smartcard states and serves to send and receive all
  *   communication data between Smartcard and reader.
  * @param  SCState: pointer to an SC_State enumeration that will contain the Smartcard state.
  * @param  SC_ADPU: pointer to an SC_ADPU_Commands structure that will be initialized.
  * @param  SC_Response: pointer to a SC_ADPU_Responce structure which will be initialized.
  * @retval None
  */
void SC_Handler(SC_State *SCState, SC_ADPU_Commands *SC_ADPU, SC_ADPU_Responce *SC_Response, SC_InitStructure *SC_InitCfg)
{
    uint32_t i = 0;
    log_info("*SCState = %d \r\n", *SCState);
    switch(*SCState)
    {
    case SC_POWER_ON:
        if (SC_ADPU->Header.INS == SC_GET_A2R)
        {
            if(F_HotReset == 0)
            {
                /* Smartcard intialization ------------------------------------------*/
                SC_Init(SC_InitCfg);
            }
			else
			{
				SC_Reset(Bit_RESET);
				delay_ms(10);
				SC_Reset(Bit_SET);
			}
            /* Reset Data from SC buffer -----------------------------------------*/
            for (i = 0; i < 40; i++)
            {
                SC_ATR_Table[i] = 0;
            }
            /* Reset SC_A2R Structure --------------------------------------------*/
            SC_A2R.TS = 0;
            SC_A2R.T0 = 0;
            for (i = 0; i < SETUP_LENGTH; i++)
            {
                SC_A2R.T[i] = 0;
            }
            for (i = 0; i < HIST_LENGTH; i++)
            {
                SC_A2R.H[i] = 0;
            }
            SC_A2R.Tlength = 0;
            SC_A2R.Hlength = 0;
            /* Next State --------------------------------------------------------*/
            *SCState = SC_RESET_LOW;
        }
        break;
    case SC_RESET_LOW:
        if(SC_ADPU->Header.INS == SC_GET_A2R)
        {
            /* If card is detected then Power ON, Card Reset and wait for an answer) */
            if (1)
            {
                while(((*SCState) != SC_POWER_OFF) && ((*SCState) != SC_ACTIVE))
                {
                    SC_AnswerReq(SCState, &SC_ATR_Table[0], 40); /* Check for answer to reset */
                    log_info("SC_ATR_Table:");
                    for(i = 0; i < 32; i++)
                    {
                        log_info("0x%x\r\n", SC_ATR_Table[i]);
                    }
                }
            }
            else
            {
                (*SCState) = SC_POWER_OFF;
            }
        }
        break;
    case SC_ACTIVE:
        if (SC_ADPU->Header.INS == SC_GET_A2R)
        {
            if(SC_decode_Answer2reset(&SC_ATR_Table[0]) == T0_PROTOCOL)
            {
                (*SCState) = SC_ACTIVE_ON_T0;
            }
            else
            {
                (*SCState) = SC_POWER_OFF;
            }
        }
        break;
    case SC_ACTIVE_ON_T0:
        SC_SendData(SC_ADPU, SC_Response);
        break;
    case SC_POWER_OFF:
        SC_DeInit(); /* Disable Smartcard interface */
        break;
    default:
        (*SCState) = SC_POWER_OFF;
    }
}

void SC_HotReset_handle(void)
{
    SC_InitStructure SC_InitCfg;
    SC_State SCState = SC_POWER_OFF;
    SC_ADPU_Commands SC_ADPU;
    SC_ADPU_Responce SC_Responce;
    USART_InitType USART_InitStructure;
    RCC_ClocksType RCC_ClocksStatus;
    F_HotReset = 1;
    SC_InitCfg.Clk_Div   = 10;//6;    //SC_USART Clock set to (PCLK1 = SC_USART MHZ / Clk_Div)MHz
    SC_InitCfg.GT        = 16;
    SC_InitCfg.StopBits  = 3;
    SC_InitCfg.Parity    = 1;
    SC_InitCfg.NackEn    = 0;    // 0 - Disable NACK, 1 - Enable NACK
    SCState = SC_POWER_ON;
    SC_APDU_Init(&SC_ADPU, 0x00, SC_GET_A2R, 0x00, 0x00, 0x00, NULL, 0x00);
    RCC_GetClocksFreqValue(&RCC_ClocksStatus);
		/*reset BaudRate*/
    USART_InitStructure.BaudRate            = RCC_ClocksStatus.Pclk1Freq / (372 * ((SC_USART->GTP & (uint16_t)0x00FF) * 2));
    USART_InitStructure.WordLength          = USART_WL_9B;
    USART_InitStructure.StopBits            = USART_STPB_1_5;
    USART_InitStructure.Parity              = USART_PE_EVEN;
    USART_InitStructure.Mode                = USART_MODE_RX | USART_MODE_TX;
    USART_InitStructure.HardwareFlowControl = USART_HFCTRL_NONE;
    USART_Init(SC_USART, &USART_InitStructure);
		log_info("USARTx Smart_Card Hot_Reset\r\n");
		/* Flush the SC_USART DAT */
	  (void)USART_ReceiveData(SC_USART);

    while(SCState != SC_ACTIVE_ON_T0)
    {
        SC_Handler(&SCState, &SC_ADPU, &SC_Responce, &SC_InitCfg);
    }
    log_info("USARTx Smart_Card Hot_Reset Finish\r\n");
    F_HotReset = 0;
}
