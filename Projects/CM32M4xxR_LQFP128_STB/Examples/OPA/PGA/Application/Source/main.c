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
 * @file main.c
 * @author CMIOT
 * @version v1.0.0
 *
 * @COPYRIGHT(c) 2020, China Mobile IOT. All rights reserved.
 */
#include "main.h"

/** @addtogroup OPAMP_PGA
 * @{
 */

ADC_InitType ADC_InitStructure;
DMA_InitType DMA_InitStructure;

void RCC_Configuration(void);
void GPIO_Configuration(void);
void OPAMP_Configuration(void);

/**
 * @brief   Main program,Test PGA is work ok? Opa out Pin can view by scope
 */
int main(void)
{
    /* System clocks configuration ---------------------------------------------*/
    RCC_Configuration();

    /* GPIO configuration ------------------------------------------------------*/
    GPIO_Configuration();

    /* OPAMP configuration ------------------------------------------------------*/
    OPAMP_Configuration();
    while (1)
    {
        ;
    }
}

/**
 * @brief  Configures the Opa.
 */
void OPAMP_Configuration(void)
{
    OPAMP_InitType OPAMP_Initial;
    OPAMP_StructInit(&OPAMP_Initial);
    OPAMP_Initial.Gain = OPAMP_CS_PGA_GAIN_2;
    /*configure opamp1*/
    OPAMP_Init(OPAMP1, &OPAMP_Initial);
    OPAMP_SetVpSel(OPAMP1, OPAMP1_CS_VPSEL_PA1);
    OPAMP_SetVmSel(OPAMP1, OPAMPx_CS_VMSEL_FLOAT);
    OPAMP_Enable(OPAMP1, ENABLE);
    /*configure opamp2*/
    OPAMP_Init(OPAMP2, &OPAMP_Initial);
    OPAMP_SetVpSel(OPAMP2, OPAMP2_CS_VPSEL_PA7);
    OPAMP_SetVmSel(OPAMP2, OPAMPx_CS_VMSEL_FLOAT);
    OPAMP_Enable(OPAMP2, ENABLE);
    /*configure opamp3*/
    OPAMP_Init(OPAMP3, &OPAMP_Initial);
    OPAMP_SetVpSel(OPAMP3, OPAMP3_CS_VPSEL_PC9);
    OPAMP_SetVmSel(OPAMP3, OPAMPx_CS_VMSEL_FLOAT);
    OPAMP_Enable(OPAMP3, ENABLE);
    /*configure opamp4*/
    OPAMP_Init(OPAMP4, &OPAMP_Initial);
    OPAMP_SetVpSel(OPAMP4, OPAMP4_CS_VPSEL_PC3);
    OPAMP_SetVmSel(OPAMP4, OPAMPx_CS_VMSEL_FLOAT);
    OPAMP_Enable(OPAMP4, ENABLE);
    // OPAMP output pin enable pix pin when OPAMPx En.not to remap or select output pin
}

/**
 * @brief  Configures the different system clocks.
 */
void RCC_Configuration(void)
{
    /* Enable COMPE clocks */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_COMP | RCC_APB1_PERIPH_OPAMP | RCC_APB1_PERIPH_COMP_FILT, ENABLE);
    /* Enable GPIOA, GPIOB, GPIOC and GPIOD clocks */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO | RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_GPIOC
                                | RCC_APB2_PERIPH_GPIOD | RCC_APB2_PERIPH_GPIOE | RCC_APB2_PERIPH_GPIOF,
                            ENABLE);
}

/**
 * @brief  Configures the different GPIO ports.
 */
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    /* Configure OPAMP1_VP, OPAMP2_Vp, OPAMP3_Vp, OPAMP4_Vp
                 PA1       PA7      PC9       PC3   as analog inputs */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.Pin       = GPIO_PIN_1 | GPIO_PIN_7;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.Pin = GPIO_PIN_9 | GPIO_PIN_3;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    // OPAMP output pin enable pix pin when OPAMPx En.not to remap or select output pin
    /* configure OP1_out,  OP2_out,  OP1_out,  OP1_out,
                   PA6        PB1       PB11      PB12       as analog output */
    GPIO_InitStructure.Pin = GPIO_PIN_6;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.Pin = GPIO_PIN_1 | GPIO_PIN_11 | GPIO_PIN_12;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

#ifdef USE_FULL_ASSERT

/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param file pointer to the source file name
 * @param line assert_param error line source number
 */
void assert_failed(const uint8_t* expr, const uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {
    }
}

#endif

/**
 * @}
 */

/**
 * @}
 */
