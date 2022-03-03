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


/** @addtogroup PWR_PVD
 * @{
 */

void EXTI_Configuration(void);
void ECLIC_Configuration(void);

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

	/* Initialize log output port */
	log_init();
	log_info("This is a PWR_PVD demo\r\n");

    /* Initialize LEDs on CM32M4xxR-EVAL board */
    LedInit(LED1_PORT, LED1_PIN);
    LedOff(LED1_PORT, LED1_PIN);

    /* Enable PWR and BKP clock */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_PWR | RCC_APB1_PERIPH_BKP, ENABLE);

    /* Configure EXTI Line to generate an interrupt on falling edge */
    EXTI_Configuration();

    /* ECLIC configuration */
    ECLIC_Configuration();

    /* Configure the PVD Level to 2.9V */
    PWR_PvdRangeConfig(PWR_PVDRANGRE_2V9);

    /* Enable global interrupt */
    __enable_irq();

    /* Enable the PVD Output */
    PWR_PvdEnable(ENABLE);

    while (1)
    {
    }
}

/**
 * @brief  Configures EXTI Lines.
 */
void EXTI_Configuration(void)
{
    EXTI_InitType EXTI_InitStructure;

    /* Configure EXTI Line16(PVD Output) to generate an interrupt on rising and
       falling edges */
    EXTI_ClrITPendBit(EXTI_LINE16);
    EXTI_InitStructure.EXTI_Line    = EXTI_LINE16;
    EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
}

/**
 * @brief  Configures ECLIC.
 */
void ECLIC_Configuration(void)
{
    /* Enable the PVD Interrupt */
	ECLIC_SetLevelIRQ(PVD_IRQn, 1);
	ECLIC_SetPriorityIRQ(PVD_IRQn, 1);
	ECLIC_SetTrigIRQ(PVD_IRQn, ECLIC_LEVEL_TRIGGER);
	ECLIC_EnableIRQ(PVD_IRQn);
}

/**
 * @}
 */

/**
 * @}
 */
