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

#include "main.h"
#include "bsp.h"

/** @addtogroup CM32M4xxR_StdPeriph_Examples
 * @{
 */

/** @addtogroup LoopBack_CAN1
 * @{
 */

#define CAN_BAUDRATE_1M  	((uint32_t) 1000)
#define CAN_BAUDRATE_500K	((uint32_t) 500)
#define CAN_BAUDRATE_250K	((uint32_t) 250)
#define CAN_BAUDRATE_125K	((uint32_t) 125)
#define CAN_BAUDRATE_100K	((uint32_t) 100)
#define CAN_BAUDRATE_50K 	((uint32_t) 50)
#define CAN_BAUDRATE_20K 	((uint32_t) 20)
#define CAN_BAUDRATE_10K 	((uint32_t) 10)
#define CAN_BTR_CALCULATE	((uint32_t) 6000)

#define CAN_TXDLC_8    		((uint8_t) 8)
#define CAN_FILTERNUM0 		((uint8_t) 0)

CanTxMessage	CAN1_TxMessage;
CanRxMessage	CAN1_RxMessage;

/**
 * @brief  Main program.
 */
int main(void)
{
    uint8_t TransmitMailbox = 0;
    uint16_t Time_out       = 0xFFFF;

    /* USART Init */
    log_init();
    log_info("This is a LoopBack_CAN1 demo\r\n");

    /* Configures the ECLIC for CAN1_RX0 */
    ECLIC_Config();

    /* Enable global interrupt */
    __enable_irq();

    /* Configures CAN1 IOs */
    CAN_GPIO_Config();

    /* Configures CAN1 - LoopBack Mode */
    CAN_Config(CAN_BAUDRATE_500K);

    /* CAN1 transmit message */
    TransmitMailbox = CANTxMessage(CAN1,
                                   &CAN1_TxMessage,
                                   0x0400,
                                   0x00,
                                   CAN_ID_STD,
                                   CAN_RTRQ_DATA,
                                   CAN_TXDLC_8,
                                   0x01,
                                   0x02,
                                   0x03,
                                   0x04,
                                   0x05,
                                   0x06,
                                   0x07,
                                   0x08);

    while ((CAN_TransmitSTS(CAN1, TransmitMailbox) != CANTXSTSOK) && (Time_out != 0))
    {
        Time_out--;
    }

    Time_out = 0xFFFF;
    while ((CAN_PendingMessage(CAN1, CAN_FIFO0) < 1) && (Time_out != 0))
    {
        Time_out--;
    }

    /* Receive Message */
    if (FAILED == Check_CANRxMessage(&CAN1_RxMessage,
                              	  	 0x0400,
									 0x00,
									 CAN_ID_STD,
									 CAN_RTRQ_DATA,
									 CAN_TXDLC_8,
									 0x01,
									 0x02,
									 0x03,
									 0x04,
									 0x05,
									 0x06,
									 0x07,
									 0x08,
									 CAN_FILTERNUM0))
    {
        log_info("Check RX Message Failed \r\n");
    }
    else
    {
        log_info("Check RX Message Passed \r\n");
    }

    while (1)
    {
    }
}

/**
 * @brief  Configures the ECLIC for CAN.
 */
void ECLIC_Config(void)
{
    /* Enable the CAN1 Interrupt */
	ECLIC_SetLevelIRQ(CAN1_RX0_IRQn, 0);
	ECLIC_SetPriorityIRQ(CAN1_RX0_IRQn, 0);
	ECLIC_SetTrigIRQ(CAN1_RX0_IRQn, ECLIC_LEVEL_TRIGGER);
	ECLIC_EnableIRQ(CAN1_RX0_IRQn);
}

/**
 * @brief  Configures CAN1 GPIOs
 */
void CAN_GPIO_Config(void)
{
    GPIO_InitType GPIO_InitStructure;

    /* Configures CAN1 and CAN2 IOs */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO | RCC_APB2_PERIPH_GPIOD, ENABLE);

    /* Configure CAN1 RX pin */
    GPIO_InitStructure.Pin       = GPIO_PIN_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    /* Configure CAN1 TX pin */
    GPIO_InitStructure.Pin        = GPIO_PIN_1;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    /* Remap CAN1 GPIOs */
    GPIO_ConfigPinRemap(GPIO_RMP3_CAN1, ENABLE);
}

/**
 * @brief  Configures CAN1.
 * @param CAN_BaudRate 10Kbit/s ~ 1Mbit/s
 */
void CAN_Config(uint32_t CAN_BaudRate)
{
    CAN_InitType CAN_InitStructure;
    CAN_FilterInitType CAN_FilterInitStructure;

    /* Configure CAN1 */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_CAN1, ENABLE);

    /* CAN1 register init */
    CAN_DeInit(CAN1);

    /* Struct init*/
    CAN_InitStruct(&CAN_InitStructure);

    /* CAN1 cell init */
    CAN_InitStructure.TTCM          = DISABLE;
    CAN_InitStructure.ABOM          = DISABLE;
    CAN_InitStructure.AWKUM         = DISABLE;
    CAN_InitStructure.NART          = DISABLE;
    CAN_InitStructure.RFLM          = DISABLE;
    CAN_InitStructure.TXFP          = ENABLE;
    CAN_InitStructure.OperatingMode = CAN_LoopBack_Mode;
    CAN_InitStructure.RSJW          = CAN_RSJW_1tq;
    CAN_InitStructure.TBS1          = CAN_TBS1_3tq;
    CAN_InitStructure.TBS2          = CAN_TBS2_2tq;

    if ((CAN_BaudRate > CAN_BAUDRATE_1M) || (CAN_BaudRate < CAN_BAUDRATE_10K))
    {
        log_info("Please select the CAN Baudrate between 10Kbit/s to 1Mbit/s.\r\n");
    }
    else
    {
        CAN_InitStructure.BaudRatePrescaler = (uint32_t)(CAN_BTR_CALCULATE / CAN_BaudRate);
    }

    /*Initializes the CAN1 */
    CAN_Init(CAN1, &CAN_InitStructure);

    /* CAN1 filter init */
    CAN_FilterInitStructure.Filter_Num            = CAN_FILTERNUM0;
    CAN_FilterInitStructure.Filter_Mode           = CAN_Filter_IdMaskMode;
    CAN_FilterInitStructure.Filter_Scale          = CAN_Filter_32bitScale;
    CAN_FilterInitStructure.Filter_HighId         = 0x8000;
    CAN_FilterInitStructure.Filter_LowId          = 0x0000;
    CAN_FilterInitStructure.FilterMask_HighId     = 0x4000;
    CAN_FilterInitStructure.FilterMask_LowId      = 0x0000;
    CAN_FilterInitStructure.Filter_FIFOAssignment = CAN_FIFO0;
    CAN_FilterInitStructure.Filter_Act            = ENABLE;
    CAN_InitFilter(CAN1, &CAN_FilterInitStructure);

    CAN_INTConfig(CAN1, CAN_INT_FMP0, ENABLE);
}

/**
 * @brief  CAN1/2 Transmit Message.
 * @param CANx CAN1/2
 * @param TxMessage CAN1/2_TxMessage
 * @param  StdId
 * @param  ExtId
 * @param  IDE
 * @param  RTR
 * @param  DLC
 * @param  Data0~7
 * @return The number of the mailbox that is used for transmission or CAN_TxSTS_NoMailBox if there is no empty mailbox.
 */
uint8_t CANTxMessage(CAN_Module* CANx,
                     CanTxMessage* TxMessage,
                     uint32_t StdId,
                     uint32_t ExtId,
                     uint8_t IDE,
                     uint8_t RTR,
                     uint8_t DLC,
                     uint8_t Data0,
                     uint8_t Data1,
                     uint8_t Data2,
                     uint8_t Data3,
                     uint8_t Data4,
                     uint8_t Data5,
                     uint8_t Data6,
                     uint8_t Data7)
{
    /* Transmit */
    TxMessage->StdId   = StdId; /* Standard ID or Extended ID(MSBs) */
    TxMessage->ExtId   = ExtId; /* Extended ID(LSBs) */
    TxMessage->IDE     = IDE;   /* CAN_ID_STD / CAN_ID_EXT */
    TxMessage->RTR     = RTR;   /* CAN_RTRQ_DATA / CAN_RTRQ_REMOTE */
    TxMessage->DLC     = DLC;   /* 0 to 8 */
    TxMessage->Data[0] = Data0;
    TxMessage->Data[1] = Data1;
    TxMessage->Data[2] = Data2;
    TxMessage->Data[3] = Data3;
    TxMessage->Data[4] = Data4;
    TxMessage->Data[5] = Data5;
    TxMessage->Data[6] = Data6;
    TxMessage->Data[7] = Data7;

    return CAN_TransmitMessage(CANx, TxMessage);
}

/**
 * @brief  Check Can Receive Message.
 * @param RxMessage CAN1/2_TxMessage
 * @param  StdId
 * @param  ExtId
 * @param  IDE
 * @param  RTR
 * @param  DLC
 * @param  Data0~7
 * @param FMI Filter match index
 * @return FAILED/PASSED
 */
uint8_t Check_CANRxMessage(CanRxMessage* RxMessage,
                           uint32_t StdId,
                           uint32_t ExtId,
                           uint8_t IDE,
                           uint8_t RTR,
                           uint8_t DLC,
                           uint8_t Data0,
                           uint8_t Data1,
                           uint8_t Data2,
                           uint8_t Data3,
                           uint8_t Data4,
                           uint8_t Data5,
                           uint8_t Data6,
                           uint8_t Data7,
                           uint8_t FMI)
{
    /* ID */
    if (IDE == CAN_ID_EXT)
    {
        if (RxMessage->ExtId != ExtId)
        {
            return FAILED;
        }
    }
    else if (IDE == CAN_ID_STD)
    {
        if (RxMessage->StdId != StdId)
        {
            return FAILED;
        }
    }

    /* IDE/RTR/DLC */
    if ((RxMessage->IDE != IDE) || /* CAN_ID_STD / CAN_ID_EXT */
        (RxMessage->RTR != RTR) || /* CAN_RTRQ_DATA / CAN_RTRQ_REMOTE */
        (RxMessage->DLC != DLC)    /* 0 to 8 */
    )
    {
        return FAILED;
    }

    /* DATA */
    if (RTR == CAN_RTRQ_DATA)
    {
        if (DLC >= 1)
        {
            if (RxMessage->Data[0] != Data0)
            {
                return FAILED;
            }
        }

        if (DLC >= 2)
        {
            if (RxMessage->Data[1] != Data1)
            {
                return FAILED;
            }
        }

        if (DLC >= 3)
        {
            if (RxMessage->Data[2] != Data2)
            {
                return FAILED;
            }
        }

        if (DLC >= 4)
        {
            if (RxMessage->Data[3] != Data3)
            {
                return FAILED;
            }
        }

        if (DLC >= 5)
        {
            if (RxMessage->Data[4] != Data4)
            {
                return FAILED;
            }
        }

        if (DLC >= 6)
        {
            if (RxMessage->Data[5] != Data5)
            {
                return FAILED;
            }
        }

        if (DLC >= 7)
        {
            if (RxMessage->Data[6] != Data6)
            {
                return FAILED;
            }
        }

        if (DLC == 8)
        {
            if (RxMessage->Data[7] != Data7)
            {
                return FAILED;
            }
        }

        if (DLC > 8)
        {
            return FAILED;
        }
    }
    else if (RTR == CAN_RTRQ_REMOTE)
    {
    }

    /* RTR/DLC */
    if (RxMessage->FMI != FMI)
    {
        return FAILED;
    }

    return PASSED;
}

/**
 * @}
 */

/**
 * @}
 */
