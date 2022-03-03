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

#include <main.h>
#include <stdio.h>
#include "log.h"
#include "led.h"

/** @addtogroup CM32M4xxR_StdPeriph_Examples
 * @{
 */


/** @addtogroup TamperTest
 * @{
 */

#define BKP_DR_NUMBER	(42)

uint16_t BKPDataReg[BKP_DR_NUMBER] = {BKP_DAT1,  BKP_DAT2,  BKP_DAT3,  BKP_DAT4,  BKP_DAT5,  BKP_DAT6,  BKP_DAT7,
                                      BKP_DAT8,  BKP_DAT9,  BKP_DAT10, BKP_DAT11, BKP_DAT12, BKP_DAT13, BKP_DAT14,
                                      BKP_DAT15, BKP_DAT16, BKP_DAT17, BKP_DAT18, BKP_DAT19, BKP_DAT20, BKP_DAT21,
                                      BKP_DAT22, BKP_DAT23, BKP_DAT24, BKP_DAT25, BKP_DAT26, BKP_DAT27, BKP_DAT28,
                                      BKP_DAT29, BKP_DAT30, BKP_DAT31, BKP_DAT32, BKP_DAT33, BKP_DAT34, BKP_DAT35,
                                      BKP_DAT36, BKP_DAT37, BKP_DAT38, BKP_DAT39, BKP_DAT40, BKP_DAT41, BKP_DAT42};

void ECLIC_Configuration(void);
void WriteToBackupReg(uint16_t FirstBackupData);
uint32_t CheckBackupReg(uint16_t FirstBackupData);

void TamperPinInit(void)
{
    GPIO_InitType GPIO_InitStructure;

    /* Check the parameters */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);

    /* Configure the GPIO pin as IPD*/
    GPIO_InitStructure.Pin        = GPIO_PIN_13;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/**
 * @brief  Main program.
 */
int main(void)
{
    /*!< At this stage the microcontroller clock setting is already configured,
         this is done through SystemInit() function which is called from startup
         file (startup_cm32m4xxr.s) before to branch to application main.
         To reconfigure the default setting of SystemInit() function, refer to
         system_cm32m4xxr.c file
       */

	/* Disable global interrupt */
	__disable_irq();

    /* ECLIC configuration */
    ECLIC_Configuration();

    LedInit(LED1_PORT, LED1_PIN);
    LedInit(LED2_PORT, LED2_PIN);
    LedInit(LED3_PORT, LED3_PIN);
    LedOff(LED1_PORT, LED1_PIN);
    LedOff(LED2_PORT, LED2_PIN);
    LedOff(LED3_PORT, LED3_PIN);
    TamperPinInit();

    /* Enable PWR and BKP clock */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_PWR | RCC_APB1_PERIPH_BKP, ENABLE);

    /* Enable write access to Backup domain */
    PWR_BackupAccessEnable(ENABLE);

    /* Disable Tamper pin */
    BKP_TPEnable(DISABLE);

    /* Disable Tamper interrupt */
    BKP_TPIntEnable(DISABLE);

    /* Tamper pin active on low level */
    BKP_ConfigTPLevel(BKP_TP_LOW);
    //BKP_ConfigTPLevel(BKP_TP_HIGH);

    /* Clear Tamper pin Event(TE) pending flag */
    BKP_ClrTEFlag();

    /* Enable Tamper interrupt */
    BKP_TPIntEnable(ENABLE);

    /* Enable Tamper pin */
    BKP_TPEnable(ENABLE);

	/* Enable global interrupt */
	__enable_irq();

    /* Write data to Backup DRx registers */
    WriteToBackupReg(0xA53C);

    /* Check if the written data are correct */
    if (CheckBackupReg(0xA53C) == 0x00)
    {
        /* Turn off LED1 */
        LedOff(LED1_PORT, LED1_PIN);
    }
    else
    {
        /* Turn on LED1 */
        LedOn(LED1_PORT, LED1_PIN);
    }

    while (1)
    {
    }
}

/**
 * @brief  ECLIC configuration.
 */
void ECLIC_Configuration(void)
{
    /* Enable the TAMPER Interrupt */
	ECLIC_SetLevelIRQ(TAMPER_IRQn, 1);
	ECLIC_SetPriorityIRQ(TAMPER_IRQn, 1);
	ECLIC_SetTrigIRQ(TAMPER_IRQn, ECLIC_NEGTIVE_EDGE_TRIGGER);
	ECLIC_EnableIRQ(TAMPER_IRQn);
}

/**
 * @brief  Writes data Backup DRx registers.
 * @param FirstBackupData data to be written to Backup data registers.
 */
void WriteToBackupReg(uint16_t FirstBackupData)
{
    uint32_t index = 0;

    for (index = 0; index < BKP_DR_NUMBER; index++)
    {
        BKP_WriteBkpData(BKPDataReg[index], FirstBackupData + (index * 0x5A));
    }
}

/**
 * @brief  Checks if the Backup DRx registers values are correct or not.
 * @param FirstBackupData data to be compared with Backup data registers.
 * @return
 *         - 0: All Backup DRx registers values are correct
 *         - Value different from 0: Number of the first Backup register
 *           which value is not correct
 */
uint32_t CheckBackupReg(uint16_t FirstBackupData)
{
    uint32_t index = 0;

    for (index = 0; index < BKP_DR_NUMBER; index++)
    {
        if (BKP_ReadBkpData(BKPDataReg[index]) != (FirstBackupData + (index * 0x5A)))
        {
            return (index + 1);
        }
    }

    return 0;
}

/**
 * @brief  Checks if the Backup DRx registers are reset or not.
 * @return
 *          - 0: All Backup DRx registers are reset
 *          - Value different from 0: Number of the first Backup register
 *            not reset
 */
uint32_t IsBackupRegReset(void)
{
    uint32_t index = 0;

    for (index = 0; index < BKP_DR_NUMBER; index++)
    {
        if (BKP_ReadBkpData(BKPDataReg[index]) != 0x0000)
        {
            return (index + 1);
        }
    }

    return 0;
}

/**
 * @}
 */

/**
 * @}
 */
