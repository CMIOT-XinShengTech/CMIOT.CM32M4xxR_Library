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

/** @addtogroup TIM_DMABurst
 * @{
 */

#define TIM1_DMAR_ADDRESS	(TIM1_BASE + 0x4C) /* TIM1_DADDR register address */

GPIO_InitType GPIO_InitStructure;
DMA_InitType DMA_InitStructure;
TIM_TimeBaseInitType TIM_TimeBaseStructure;
TIM_OCInitType TIM_OCInitStructure;
uint16_t SRC_Buffer[6] = {0x0FFF, 0x0000, 0x0555};
uint16_t DmaAgain      = 1;

/**
 * @brief  Main function
 */
int main(void)
{
    /* TIM1 and GPIOA clock enable */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_TIM1 | RCC_APB2_PERIPH_GPIOA, ENABLE);

    /* DMA clock enable */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_DMA1, ENABLE);

    /* GPIOA Configuration: Channel 1 as alternate function push-pull */
    GPIO_InitStructure.Pin        = GPIO_PIN_8;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* TIM1 DeInit */
    TIM_DeInit(TIM1);

    /* DMA1 Channel5 Configuration */
    DMA_DeInit(DMA1_CH5);

    DMA_InitStructure.PeriphAddr     = (uint32_t)TIM1_DMAR_ADDRESS;
    DMA_InitStructure.MemAddr        = (uint32_t)SRC_Buffer;
    DMA_InitStructure.Direction      = DMA_DIR_PERIPH_DST;
    DMA_InitStructure.BufSize        = 3;
    DMA_InitStructure.PeriphInc      = DMA_PERIPH_INC_DISABLE;
    DMA_InitStructure.DMA_MemoryInc  = DMA_MEM_INC_ENABLE;
    DMA_InitStructure.PeriphDataSize = DMA_PERIPH_DATA_SIZE_HALFWORD;
    DMA_InitStructure.MemDataSize    = DMA_MEMORY_DATA_SIZE_HALFWORD;
    DMA_InitStructure.CircularMode   = DMA_MODE_NORMAL;
    DMA_InitStructure.Priority       = DMA_PRIORITY_HIGH;
    DMA_InitStructure.Mem2Mem        = DMA_M2M_DISABLE;
    DMA_Init(DMA1_CH5, &DMA_InitStructure);

    /* Time base configuration */
    /* -----------------------------------------------------------------------
    TIM1 Configuration: generate 1 PWM signal using the DMA burst mode:
    The TIM1CLK frequency is set to SystemCoreClock (Hz), to get TIM1 counter
    clock at 8 MHz, the Prescaler is computed as following:
     - Prescaler = (TIM1CLK / TIM1 counter clock) - 1
    SystemCoreClock is set to 8 MHz.

    The TIM1 period is TIM1_AR + 1: TIM1 Frequency = TIM1 counter clock / (TIM1_AR + 1)
                                               = 8 MHz / 4096 = 1953 Hz
    TIM1 Channel1 duty cycle = (TIM1_CCR1 / (TIM1_ARR + 1)) * 100 = 33.33%
    ----------------------------------------------------------------------- */

    TIM_TimeBaseStructure.Period    = 0xFFFF;
    TIM_TimeBaseStructure.Prescaler = (uint16_t)(SystemCoreClock / 8000000) - 1;
    TIM_TimeBaseStructure.ClkDiv    = 0x0;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
    TIM_InitTimeBase(TIM1, &TIM_TimeBaseStructure);

    /* TIM Configuration in PWM Mode */
    TIM_OCInitStructure.OcMode      = TIM_OCMODE_PWM1;
    TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.Pulse       = 0xFFF;
    TIM_InitOc1(TIM1, &TIM_OCInitStructure);

    /* TIM1 DADDR Base register and DMA Burst Length Configuration */
    TIM_ConfigDma(TIM1, TIM_DMABASE_AR, TIM_DMABURST_LENGTH_3TRANSFERS);

    /* TIM1 DMA Update enable */
    TIM_EnableDma(TIM1, TIM_DMA_UPDATE, ENABLE);

    /* TIM1 enable */
    TIM_Enable(TIM1, ENABLE);

    /* TIM1 PWM Outputs Enable */
    TIM_EnableCtrlPwmOutputs(TIM1, ENABLE);

    /* DMA1 Channel5 enable */
    DMA_EnableChannel(DMA1_CH5, ENABLE);

    /* Wait until DMA1 Channel5 end of Transfer */
    while (!DMA_GetFlagStatus(DMA1_FLAG_TC5, DMA1))
    {
    }

    DMA_ClearFlag(DMA1_FLAG_GL5 | DMA1_FLAG_TC5 | DMA1_FLAG_HT5 | DMA1_FLAG_TE5, DMA1);

    /* Infinite loop */
    while (1)
    {
    	;
    }
}

/**
 * @}
 */

/**
 * @}
 */
