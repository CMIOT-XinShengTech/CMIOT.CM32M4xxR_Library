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

#include <stdio.h>
#include "main.h"

#include "log.h"
#include "led.h"

/** @addtogroup CM32M4xxR_StdPeriph_Examples
 * @{
 */


/** @addtogroup IWDG_Reset
 * @{
 */

__IO uint32_t TimingDelay = 0;
__IO uint32_t LsiFreq     = 40000; /* 40KHz */

/**
 * @brief  Inserts a delay time.
 * @param nTime specifies the delay time length, in milliseconds.
 */
void Delay(__IO uint32_t nTime)
{
    TimingDelay = nTime;

    while (TimingDelay != 0)
        ;
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

    log_init();
    log_info("--- IWDG demo reset ---\n");

    LedInit(LED1_PORT, LED1_PIN);
    LedInit(LED2_PORT, LED2_PIN);
    LedOff(LED1_PORT, LED1_PIN);
    LedOff(LED2_PORT, LED2_PIN);

    /* Enable global interrupt */
    __enable_irq();

    /* Use core_aon_clk as systimer clock */
    SysTimer_SetControlValue(SysTimer_GetControlValue() | SysTimer_MTIMECTL_CLKSRC_Msk);

    /* Setup SysTick Timer for 1 msec interrupts  */
    if (SysTick_Config(SystemCoreClock / 1000))
    {
        /* Capture error */
        while (1)
            ;
    }

    /* Check if the system has resumed from IWDG reset */
    if (RCC_GetFlagStatus(RCC_FLAG_IWDGRST) != RESET)
    {
        /* IWDGRST flag set */
        /* Turn on LED1 */
        LedOn(LED1_PORT, LED1_PIN);

        log_info("reset by IWDG\n");

        /* Clear reset flags */
        RCC_ClrFlag();
    }
    else
    {
        /* IWDGRST flag is not set */
        /* Turn off LED1 */
        LedOff(LED1_PORT, LED1_PIN);
    }

#ifdef LSI_TIM_MEASURE

    /* Enable the LSI OSC */
    RCC_EnableLsi(ENABLE);

    /* Wait till LSI is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_LSIRD) == RESET)
    {
    }

    /* TIM Configuration -------------------------------------------------------*/
    TIM5_ConfigForLSI();

    /* Wait until the TIM5 get 3 LSI edges */
    while (CaptureNumber < 3)
    {
    }

    /* Disable TIM5 CC4 Interrupt Request */
    TIM_ConfigInt(TIM5, TIM_INT_CC4, DISABLE);

#endif

    /* IWDG timeout equal to 250 ms (the timeout may varies due to LSI frequency
       dispersion) */
    /* Enable write access to IWDG_PR and IWDG_RLR registers */
    IWDG_WriteConfig(IWDG_WRITE_ENABLE);

    /* IWDG counter clock: LSI/32 */
    IWDG_SetPrescalerDiv(IWDG_PRESCALER_DIV32);

    /* Set counter reload value to obtain 250ms IWDG TimeOut.
       Counter Reload Value = 250ms / IWDG counter clock period
                            = 250ms / (32 / LSI)
                            = 0.25s / (32 / LsiFreq)
                            = LsiFreq / (32 * 4)
                            = LsiFreq / 128
     */
    log_debug("LsiFreq is: %d\n", LsiFreq);
    IWDG_CntReload(LsiFreq / 128);

    /* Reload IWDG counter */
    IWDG_ReloadKey();

    /* Enable IWDG (the LSI oscillator will be enabled by hardware) */
    IWDG_Enable();

    while (1)
    {
        /* Toggle LED2 */
        LedBlink(LED2_PORT, LED2_PIN);

        /* Insert 245 ms delay */
        Delay(245);

        /* Reload IWDG counter */
        IWDG_ReloadKey();
    }
}

#ifdef LSI_TIM_MEASURE
/**
 * @brief  Configures TIM5 to measure the LSI oscillator frequency.
 */
void TIM5_ConfigForLSI(void)
{
    TIM_ICInitType TIM_ICInitStructure;

    /* Enable TIM5 clocks */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM5, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);

    /* Enable the TIM5 Interrupt */
    ECLIC_SetLevelIRQ(TIM5_IRQn, 2);
	ECLIC_SetPriorityIRQ(TIM5_IRQn, 1);
	ECLIC_SetTrigIRQ(TIM5_IRQn, ECLIC_LEVEL_TRIGGER);
	ECLIC_EnableIRQ(TIM5_IRQn);

    /* Configure TIM5 prescaler */
    TIM_ConfigPrescaler(TIM5, 0, TIM_PSC_RELOAD_MODE_IMMEDIATE);

    /* Connect internally the TM5_CH4 Input Capture to the LSI clock output */
    GPIO_ConfigPinRemap(GPIO_RMP_TIM5CH4, ENABLE);

    /* TIM5 configuration: Input Capture mode ---------------------
       The LSI oscillator is connected to TIM5 CH4
       The Rising edge is used as active edge,
       The TIM5 CCDAT4 is used to compute the frequency value
    ------------------------------------------------------------ */
    TIM_ICInitStructure.Channel     = TIM_CH_4;
    TIM_ICInitStructure.IcPolarity  = TIM_IC_POLARITY_RISING;
    TIM_ICInitStructure.IcSelection = TIM_IC_SELECTION_DIRECTTI;
    TIM_ICInitStructure.IcPrescaler = TIM_IC_PSC_DIV8;
    TIM_ICInitStructure.IcFilter    = 0;
    TIM_ICInit(TIM5, &TIM_ICInitStructure);

    /* TIM10 Counter Enable */
    TIM_Enable(TIM5, ENABLE);

    /* Reset the flags */
    TIM5->STS = 0;

    /* Enable the CC4 Interrupt Request */
    TIM_ConfigInt(TIM5, TIM_INT_CC4, ENABLE);
}
#endif

/**
 * @}
 */

/**
 * @}
 */
