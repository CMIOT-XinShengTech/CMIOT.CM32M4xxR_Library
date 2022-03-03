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
 * @file bsp_Tim_38K.c
 * @author CMIOT Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */

#include "bsp_Tim_38K.h"

/**
 * @brief  Configures the different system clocks.
 */
void ADVANCE_TIM_RCC_Configuration(void)
{
    /* Enable DMA clocks */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_DMA1, ENABLE);
    /* TIM1 clock enable */
    ADVANCE_TIM_APBxClock_FUN(ADVANCE_TIM_CLK, ENABLE);
    /* GPIO clock enable */
    RCC_EnableAPB2PeriphClk(ADVANCE_TIM_CH1_GPIO_CLK, ENABLE);
}

/**
 * @brief  Configure the GPIO Pins.
 */
void ADVANCE_TIM_GPIO_Config(void)
{
    GPIO_InitType GPIO_InitStructure;

    /* Configure PE9 as Out_PP */
    GPIO_InitStructure.Pin        = ADVANCE_TIM_CH1_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(ADVANCE_TIM_CH1_PORT, &GPIO_InitStructure);

    GPIO_ConfigPinRemap(ADVANCE_TIM_CH1_GPIO_RMP, ENABLE);
}

static void ADVANCE_TIM_Mode_Config(void)
{
    TIM_TimeBaseInitType TIM_TimeBaseStructure;

    /* Time base configuration */
    TIM_TimeBaseStructure.Period    = ADVANCE_TIM_Period;
    TIM_TimeBaseStructure.Prescaler = ADVANCE_TIM_Prescaler;
    TIM_TimeBaseStructure.ClkDiv    = TIM_CLK_DIV1;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
    TIM_TimeBaseStructure.RepetCnt  = 0;
    TIM_InitTimeBase(ADVANCE_TIM, &TIM_TimeBaseStructure);

    TIM_EnableDma(ADVANCE_TIM, TIM_DMA_UPDATE, ENABLE);

    /* TIM counter enable */
    TIM_Enable(ADVANCE_TIM, ENABLE);
}

volatile uint32_t PinOutputValue_Px3[2]={(1<<3),(1<<19)};
void ADVANCE_TIM_DMA_Configuration(void)
{
    DMA_InitType DMA_InitStructure;

    /* DMA1 Channel1 Config */
    DMA_DeInit(DMA1_CH1);

    DMA_InitStructure.PeriphAddr     = (uint32_t)&ADVANCE_TIM_CH1_PORT->PBSC;
    DMA_InitStructure.MemAddr        = (uint32_t)&PinOutputValue_Px3;
    DMA_InitStructure.Direction      = DMA_DIR_PERIPH_DST;
    DMA_InitStructure.BufSize        = 2;
    DMA_InitStructure.PeriphInc      = DMA_PERIPH_INC_DISABLE;
    DMA_InitStructure.DMA_MemoryInc  = DMA_MEM_INC_ENABLE;
    DMA_InitStructure.PeriphDataSize = DMA_PERIPH_DATA_SIZE_WORD;
    DMA_InitStructure.MemDataSize    = DMA_MEMORY_DATA_SIZE_WORD;
    DMA_InitStructure.CircularMode   = DMA_MODE_CIRCULAR;
    DMA_InitStructure.Priority       = DMA_PRIORITY_VERY_HIGH;
    DMA_InitStructure.Mem2Mem        = DMA_M2M_DISABLE;

    DMA_Init(DMA1_CH1, &DMA_InitStructure);
    DMA_RequestRemap(DMA1_REMAP_TIM1_UP, DMA1, DMA1_CH1, ENABLE);

    /* DMA1 Channel1 enable */
    DMA_EnableChannel(DMA1_CH1, ENABLE);
}

void ADVANCE_TIM_Init(void)
{
    ADVANCE_TIM_RCC_Configuration();
    ADVANCE_TIM_GPIO_Config();
    ADVANCE_TIM_DMA_Configuration();
    ADVANCE_TIM_Mode_Config();
}

