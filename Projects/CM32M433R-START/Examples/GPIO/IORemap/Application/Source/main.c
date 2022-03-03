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
#include "bsp.h"

/** @addtogroup CM32M4xxR_StdPeriph_Examples
 * @{
 */

/** @addtogroup IORemap
 * @{
 */

/**
 * @brief Configures JTAG GPIO.
 */

void JTAGPortDisable(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);

    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_AFIO, ENABLE);

    /* Configure PA.13 (JTMS) PA.14(JTCK) and PA.15 (JTDI) as gpio */
    GPIO_InitStructure.Pin        = GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure PB.03 (JTDO) as gpio */
    GPIO_InitStructure.Pin        = GPIO_PIN_3;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* Disable the Serial Wire and JTAG Debug Port SWJ-DP */
    GPIO_ConfigPinRemap(GPIO_RMP_SW_JTAG_DISABLE, ENABLE);
}

void JTAGPortEnable(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);

    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO | RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_GPIOB, ENABLE);

    /* Configure PA.13 (JTMS) and PA.15 (JTDI) as gpio*/
    GPIO_InitStructure.Pin        = GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure PA.14(JTCK) as gpio*/
	GPIO_InitStructure.Pin        = GPIO_PIN_14;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPD;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure PB.03 (JTDO)  */
    GPIO_InitStructure.Pin        = GPIO_PIN_3;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* Enable the Serial Wire and JTAG Debug Port SWJ-DP */
    GPIO_ConfigPinRemap(GPIO_RMP_SW_JTAG_DISABLE, DISABLE);

}
/**
 * @brief  Main function.
 */
int main(void)
{
	/*SystemInit() function has been called by startup file startup_cm32m4xxr.s*/

    /* Initialize Led1~Led2 as output pushpull mode */
    LedInit(LED1_PORT, LED1_PIN);
    LedInit(LED2_PORT, LED2_PIN);

    KeyInputInit(KEY_INPUT_PORT1, KEY_INPUT_PIN1);

    while (1)
    {
        if (GPIO_ReadInputDataBit(KEY_INPUT_PORT1, KEY_INPUT_PIN1) == Bit_RESET)
        {
            /*Turn on Led1 */
            LedOn(LED1_PORT, LED1_PIN);

            /*Turn off Led2 */
            LedOff(LED2_PORT, LED2_PIN);

            JTAGPortDisable();

            while (1)
            {
                /*Toggle JTMS/SWDAT pin */
                GPIO_WriteBit(GPIOA, GPIO_PIN_13, (Bit_OperateType)(1 - GPIO_ReadOutputDataBit(GPIOA, GPIO_PIN_13)));

                /*Toggle JTCK/SWCLK pin */
                GPIO_WriteBit(GPIOA, GPIO_PIN_14, (Bit_OperateType)(1 - GPIO_ReadOutputDataBit(GPIOA, GPIO_PIN_14)));

                /* Toggle JTDI pin */
                GPIO_WriteBit(GPIOA, GPIO_PIN_15, (Bit_OperateType)(1 - GPIO_ReadOutputDataBit(GPIOA, GPIO_PIN_15)));

                /* Toggle JTDO pin */
                GPIO_WriteBit(GPIOB, GPIO_PIN_3, (Bit_OperateType)(1 - GPIO_ReadOutputDataBit(GPIOB, GPIO_PIN_3)));

                /* Insert delay */
                delay_ms(1000);

                if (GPIO_ReadInputDataBit(KEY_INPUT_PORT1, KEY_INPUT_PIN1) == Bit_SET)
                {
                    break;
                }
            }
        }
        else
        {

        	JTAGPortEnable();

        	/*Turn off Led1 */
        	LedOff(LED1_PORT, LED1_PIN);
            /*Turn on Led2 */
            LedOn(LED2_PORT, LED2_PIN);
        }
    }
}

/**
 * @}
 */

/**
 * @}
 */
