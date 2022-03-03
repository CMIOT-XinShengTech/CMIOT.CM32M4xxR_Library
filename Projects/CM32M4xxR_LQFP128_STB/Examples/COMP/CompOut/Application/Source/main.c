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
#define BIT0                     ((uint32_t)1 << 0)
#define BIT1                     ((uint32_t)1 << 1)
#define BIT2                     ((uint32_t)1 << 2)
#define BIT3                     ((uint32_t)1 << 3)
#define BIT4                     ((uint32_t)1 << 4)
#define BIT5                     ((uint32_t)1 << 5)
#define BIT6                     ((uint32_t)1 << 6)
#define BIT7                     ((uint32_t)1 << 7)
#define BIT8                     ((uint32_t)1 << 8)
#define BIT9                     ((uint32_t)1 << 9)
#define BIT10                    ((uint32_t)1 << 10)
#define BIT11                    ((uint32_t)1 << 11)
#define BIT12                    ((uint32_t)1 << 12)
#define BIT13                    ((uint32_t)1 << 13)
#define BIT14                    ((uint32_t)1 << 14)
#define BIT15                    ((uint32_t)1 << 15)
#define BIT16                    ((uint32_t)1 << 16)
#define BIT17                    ((uint32_t)1 << 17)
#define BIT18                    ((uint32_t)1 << 18)
#define BIT19                    ((uint32_t)1 << 19)
#define BIT20                    ((uint32_t)1 << 20)
#define BIT21                    ((uint32_t)1 << 21)
#define BIT22                    ((uint32_t)1 << 22)
#define BIT23                    ((uint32_t)1 << 23)
#define BIT24                    ((uint32_t)1 << 24)
#define BIT25                    ((uint32_t)1 << 25)
#define BIT26                    ((uint32_t)1 << 26)
#define BIT27                    ((uint32_t)1 << 27)
#define BIT28                    ((uint32_t)1 << 28)
#define BIT29                    ((uint32_t)1 << 29)
#define BIT30                    ((uint32_t)1 << 30)
#define BIT31                    ((uint32_t)1 << 31)
#define SetBitMsk(reg, bit, msk) ((reg) = ((reg) & ~(msk) | (bit)))
#define ClrBit(reg, bit)         ((reg) &= ~(bit))
#define SetBit(reg, bit)         ((reg) |= (bit))
#define GetBit(reg, bit)         ((reg) & (bit))

#include "main.h"

/** @addtogroup ADC_3ADCs_DMA
 * @{
 */

void RCC_Configuration(void);
void GPIO_Configuration(void);
void COMP_Configuratoin(void);
//void NVIC_Configuration(void);
void ECLIC_Configuration(void);
void ChangeVmVp(void);

/**
 * @brief   Main program
 */
int main(void)
{
    /* System clocks configuration ---------------------------------------------*/
    RCC_Configuration();

    /* NVIC configuration ------------------------------------------------------*/
    //NVIC_Configuration();

    /* ECLIC configuration ------------------------------------------------------*/
    ECLIC_Configuration();

    /* GPIO configuration ------------------------------------------------------*/
    GPIO_Configuration();

    /* COMP configuration ------------------------------------------------------*/
    COMP_Configuratoin();
    while (1)
    {
        ChangeVmVp();
    }
}

/**
 * @brief  Self Generate Puls ,by skip line connect to vp and vm if need.
 */
void ChangeVmVp(void)
{
    GPIO_SetBits(GPIOE, GPIO_PIN_2);
    GPIO_ResetBits(GPIOE, GPIO_PIN_3);
    {
        volatile uint32_t i = 0;
        while (i++ < 1000)
            ;
    }
    GPIO_ResetBits(GPIOE, GPIO_PIN_2);
    GPIO_SetBits(GPIOE, GPIO_PIN_3);
    {
        volatile uint32_t i = 0;
        while (i++ < 1000)
            ;
    }
}
/**
 * @brief  Configures the comp module.
 */
void COMP_Configuratoin(void)
{
    COMP_InitType COMP_Initial;

    /*Set dac2,dac1. because dac1/PA4 is share pin line,so only PB0 puls 0/1, can find out puls*/
    COMP_SetRefScl(16, true, 32, true);
    /*Initial comp*/
    COMP_StructInit(&COMP_Initial);
    COMP_Initial.InpSel     = COMP1_CTRL_INPSEL_PB10;
    COMP_Initial.InmSel     = COMP1_CTRL_INMSEL_DAC1_PA4;
    COMP_Initial.SampWindow = 18;       //(0~31)
    COMP_Initial.Thresh     = 30;       //(0~31)
    COMP_Init(COMP1, &COMP_Initial);
    COMP_Enable(COMP1, ENABLE);
}

/**
 * @brief  Configures the different system clocks.
 */
void RCC_Configuration(void)
{
    /* Enable COMPE clocks */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_COMP | RCC_APB1_PERIPH_COMP_FILT, ENABLE);
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
    // INP
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.Pin        = GPIO_PIN_10;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    // INM
    GPIO_InitStructure.Pin = GPIO_PIN_4;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // PE2,PE3
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.Pin       = GPIO_PIN_2 | GPIO_PIN_3;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    // OutSel
    // PB1 if remap [1:0] == 01 with comp1
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.Pin       = GPIO_PIN_1;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    SetBit(AFIO->RMP_CFG4, BIT0);
    ClrBit(AFIO->RMP_CFG4, BIT1);
}
#if 0
/**
 * @brief  Configures Vector Table base location.
 */
void NVIC_Configuration(void)
{
    NVIC_InitType NVIC_InitStructure;

    /* Configure and enable ADC interrupt */
    NVIC_InitStructure.NVIC_IRQChannel                   = COMP_1_2_3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
#endif
/**
 * @brief  Configures the enhanced core local interrupt controller.
 */
void ECLIC_Configuration(void)
{
    /* Configure the ECLIC level and priority Bits */
	ECLIC_SetCfgNlbits(0); /* 0 bits for level, 4 bits for priority */

    /* Enable the USARTy Interrupt */
	ECLIC_SetPriorityIRQ(COMP_1_2_3_IRQn, 1);
	ECLIC_SetTrigIRQ(COMP_1_2_3_IRQn, ECLIC_LEVEL_TRIGGER);
	ECLIC_EnableIRQ(COMP_1_2_3_IRQn);

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
