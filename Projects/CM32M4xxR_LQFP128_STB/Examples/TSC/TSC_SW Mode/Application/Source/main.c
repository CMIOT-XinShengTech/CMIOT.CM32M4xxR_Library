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
 * @version v1.0.1
 *
 * @COPYRIGHT(c) 2020, China Mobile IOT. All rights reserved.
 */
#include "main.h"
#include "bsp.h"
#include "cm32m4xxr_it.h"

static void SetSysClock_HSE_PLL(uint32_t pllmul);

void tim3_init(uint16_t Period, uint16_t Prescaler);
/**
* @brief  Main program.
*/
int main(void)
{
    static uint32_t Cnt1s = 0;

    // HSE,SYSCLK = 8M * RCC_PLLMul_x,
    SetSysClock_HSE_PLL(RCC_PLL_MUL_2);

    /*Initialize USART as 115200 bps, 8 bit length,1 stop bit,no check bit,enable receive by interrupt */
    log_init();
    LedInit(LED1_PORT, LED1_PIN);

    printf("System Startup ...\n");
    printf("Enter Normal Mode!\r\n");

    BSP_TSC_SW_Init();

    tim3_init(199, 15); // 16MHz/(15+1)=1MHz;(199+1)/1MHz=200us,with irq

    while (1)       
    {
        while(0==b_10ms_flag);

        b_10ms_flag = 0;

        BSP_TSC_KeyCheck();	  //check key every 10ms

        if (Cnt1s<40)   //about 400ms
            Cnt1s++;
        else
        {
            Cnt1s = 0;

            if(led_blink)
            {
                led_blink--;

                if(led_blink & 0x01UL)
                	LedOn(LED1_PORT, LED1_PIN);
                else
                	LedOff(LED1_PORT, LED1_PIN);
            }
        }
    }
}


/**
* @brief  Set system clock again.
*/
void SetSysClock_HSE_PLL(uint32_t pllmul)
{
    __IO uint32_t StartUpCounter = 0, HSEStartUpStatus = 0;

    // It is necessary to initialize the RCC peripheral to the reset state.
    RCC_DeInit();

    // Enable HSE, open external crystal oscillator.
    RCC_ConfigHse(RCC_HSE_ENABLE);

    // Wait for HSE to be stable.
    HSEStartUpStatus = RCC_WaitHseStable();

    // Go on until the HSE is stable.
    if (HSEStartUpStatus == SUCCESS)
    {
        //----------------------------------------------------------------------//
        // Enable flash Prefetch buffer
        FLASH_PrefetchBufSet(FLASH_PrefetchBuf_EN);

        FLASH_SetLatency(FLASH_LATENCY_3);
        //----------------------------------------------------------------------//

        // AHB prescaler factor set to 1,HCLK = SYSCLK = 16M
        RCC_ConfigHclk(RCC_SYSCLK_DIV1);
        // AHB prescaler factor set to 1,PCLK2 = HCLK/1 = 16M
        RCC_ConfigPclk2(RCC_HCLK_DIV1);
        // AHB prescaler factor set to 1,PCLK1 = HCLK/1 = 16M
        RCC_ConfigPclk1(RCC_HCLK_DIV1);

        ////-----------------Set PLL clock source as HSE, set PLL frequency multiplication factor.-------------------//
        // PLLCLK = 8MHz * pllmul
        RCC_ConfigPll(RCC_PLL_SRC_HSE_DIV1, pllmul);
        ////------------------------------------------------------------------//

        // Enable PLL
        RCC_EnablePll(ENABLE);
        // Wait for PLL to be stable.
        while (RCC_GetFlagStatus(RCC_FLAG_PLLRD) == RESET)
        {
        }

        // Switch PLL clock to SYSCLK.
        RCC_ConfigSysclk(RCC_SYSCLK_SRC_PLLCLK);

        // Read the clock switch status bit and make sure pllclk is selected as the system clock.
        while (RCC_GetSysclkSrc() != RCC_CFG_SCLKSTS_PLL)
        {
        }
    }
    else
    {   // If HSE fails to open, the program will come here, where the user can add the error code to handle.
        // When HSE fails or breaks down,mcu will automatically set HSI as the system clock.HSI is an internal high speed
        // clock of 8MHz.
        while (1)
        {
        }
    }

    SystemCoreClockUpdate();
}

/**
 * @brief  Timer3 initialization configuration.
 */
void tim3_init(uint16_t Period, uint16_t Prescaler)
{
    TIM_TimeBaseInitType timInitStruct;

    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM3, ENABLE);

    timInitStruct.Period    = Period;
    timInitStruct.Prescaler = Prescaler;
    timInitStruct.ClkDiv    = 0;
    timInitStruct.CntMode   = TIM_CNT_MODE_UP;
    TIM_InitTimeBase(TIM3, &timInitStruct);

    TIM_ConfigInt(TIM3, TIM_INT_UPDATE, ENABLE);

    /* Configure the ECLIC level and priority Bits */
    ECLIC_SetCfgNlbits(0); /* 0 bits for level, 4 bits for priority */

    /* Enable the USARTy Interrupt */
    ECLIC_SetPriorityIRQ(TIM3_IRQn, 1);
    ECLIC_SetTrigIRQ(TIM3_IRQn, ECLIC_LEVEL_TRIGGER);
    ECLIC_EnableIRQ(TIM3_IRQn);

    /* Enable global interrupt */
    __enable_irq();

    TIM_Enable(TIM3, ENABLE);
}






