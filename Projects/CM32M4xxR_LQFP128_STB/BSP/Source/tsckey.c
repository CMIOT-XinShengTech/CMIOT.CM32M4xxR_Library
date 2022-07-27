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
 * @file tsckey.c
 * @author CMIOT
 * @version v1.0.1
 *
 * @COPYRIGHT(c) 2020, China Mobile IOT. All rights reserved.
 */
#include "nuclei_sdk_soc.h"
#include "tsckey.h"
#include "log.h"
#include "string.h"
#include "stdbool.h"
#include "stdio.h"

// The following is the corresponding relationship of port, TSC channel, pulse data and key of this demo.
/*  port <-------->  TSC channel    <-------->  key on board

        PA4  <--------> TSC channel 0   <-------->  Key "SW4"
        PA5  <--------> TSC channel 1   <-------->  Key "SW5"
        PB14 <--------> TSC channel 2   <-------->  NC
        PB15 <--------> TSC channel 3   <-------->  NC
    
        PD8  <--------> TSC channel 4   <-------->  NC
        PD9  <--------> TSC channel 5   <-------->  NC
        PD11 <--------> TSC channel 6   <-------->  NC
        PD12 <--------> TSC channel 7   <-------->  NC
    
        PC6  <--------> TSC channel 8   <-------->  NC
        PC7  <--------> TSC channel 9   <-------->  NC
        PC8  <--------> TSC channel 10  <-------->  NC
        PC9  <--------> TSC channel 11  <-------->  NC
    
        PC10 <--------> TSC channel 12  <-------->  NC
        PC11 <--------> TSC channel 13  <-------->  NC
        PC12 <--------> TSC channel 14  <-------->  NC
        PD2  <--------> TSC channel 15  <-------->  NC
    
        PD4  <--------> TSC channel 16  <-------->  NC
        PD5  <--------> TSC channel 17  <-------->  NC
        PD6  <--------> TSC channel 18  <-------->  NC
        PD7  <--------> TSC channel 19  <-------->  NC
    
        PB6  <--------> TSC channel 20  <-------->  NC
        PB7  <--------> TSC channel 21  <-------->  NC
        PB8  <--------> TSC channel 22  <-------->  NC
        PB9  <--------> TSC channel 23  <-------->  NC
    */
    
    //PA9  <------->  TSC_OUT

#define THRESHOLD_MIN  400
#define KEEP_IN_RRAM	__attribute__ ((section (".rram_data")))
static TSC_ETR_KEY_PARA tsc_etr_key;         // The struct is the about the process of key recognition by ETR.
static bool b_one_cycle_sample_flag = false; // Calculate after completing 10 samples for each channel.
static bool b_channel_switch_delay = false;
static uint16_t *pEtrTimCnt;

KEEP_IN_RRAM static uint8_t TSC_Key_ch[KEY_NUM]={0,1};
KEEP_IN_RRAM static uint8_t TSC_Key_Num[KEY_NUM]={4,5};
uint32_t led_blink = 0;

/******************************************************************/
/***
 * @brief   Init tsc by hardware mode,all channels used.
 * @param:  None
 * @retval: None
 */
void BSP_TSC_HwInit(void)
{
    TSC_InitType Init = {0};

    /* Select LSI as TSC clock source and enable */
    TSC_ConfigClock(TSC_CLK_SRC_LSI);

    /* Init gpio port used for TSC */
    BSP_TSC_GpioInit();

    /* Init TSC model */
    Init.Period = TSC_DET_PERIOD_8;     /* Detect priod= 8/TSC_CLK */
    Init.Filter = TSC_DET_FILTER_1;     /* Detect filter= 1 sample */
    Init.Type   = TSC_DET_TYPE_LESS;    /* Enable less detect */
    Init.Int    = TSC_IT_DET_ENABLE;    /* Enable interrupt */
    Init.PadOpt = TSC_PAD_INTERNAL_RES; /* Use internal resistor */
    Init.Speed  = TSC_PAD_SPEED_0;      /* Low speed */
    TSC_Init(&Init);

    /*Select the internal resistance of each channel as 125K*/
    TSC_ConfigInternalResistor(TSC_CHN_SEL_ALL, TSC_RESR0_CHN_RESIST0_125K);
}

/***
 * @brief   Get TSC cnt value of each channel after poweron,and set as threshold
 * @param:  None
 * @retval: None
 */
void BSP_TSC_AutoAdjust(void)
{
    uint32_t i,tCnt;

    /* Config TSC wakeup time,it is controlled by RTC module*/
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_PWR,ENABLE);    /*Enable PWR  peripheral Clock*/
    PWR_BackupAccessEnable(ENABLE);     					/* Set bit 8 of PWR_CTRL1.Open PWR DBP.*/
    RCC_ConfigRtcClk(RCC_RTCCLK_SRC_LSI);   				/* Set LSI as RTC clock*/
    RCC_EnableRtcClk(ENABLE);           					/* Enable RTC clock*/
    RTC_EnableWakeUpTsc(0x2fe);     						/* Set TSC wakeup time as 0x2FE*LSI */

    /* Get cnt value of each channel */
    for(i=0;i<KEY_NUM;i++)
    {
        TSC_ConfigHWMode(0x1UL << TSC_Key_ch[i], ENABLE);
        delay_ms(300);	//wait for a TSC HW det interval to refresh the cnt value
        while(TSC_GetStatus(TSC_STS_TYP_CHN_NUM) != TSC_Key_ch[i]); /* make sure current detect channel is correct */
        while((tCnt=TSC_GetStatus(TSC_STS_TYP_CNTVALUE))==0);   /* wait until detect done */
        TSC_ConfigHWMode(0x1UL << TSC_Key_ch[i], DISABLE);     /* disable hw detect */

        TSC_ConfigThreshold(0x1UL << TSC_Key_ch[i], tCnt, tCnt/3);  /* set the cnt value as threshold */

        printf("Channel%d base value:%d delta value:%d \r\n",i,tCnt,tCnt/3);
    }

    RTC_EnableWakeUpTsc(0x2fe);    /* Set wakeup time as the longest in normal work */
}

void BSP_TSC_HwEnable(void)
{
	uint32_t i,channel;

	channel = 0;
	for(i=0;i<KEY_NUM;i++)
	{
		channel |= 0x1UL << TSC_Key_ch[i];
	}
	TSC_ConfigHWMode(channel, ENABLE);
}

/***
 * @brief   Config the interrupt of TSC
 * @param:  None
 * @retval: None
 */
void BSP_TSC_ConfigInt(void)
{
    EXTI_InitType EXTI_InitStruct;

    EXTI_InitStruct.EXTI_Line    = EXTI_LINE21;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_InitStruct.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;

    EXTI_Init(&EXTI_InitStruct);

    /* Configure the ECLIC level and priority Bits */
	ECLIC_SetCfgNlbits(0); /* 0 bits for level, 4 bits for priority */

    /* Enable the TSC Interrupt */
	ECLIC_SetPriorityIRQ(TSC_IRQn, 1);
	ECLIC_SetTrigIRQ(TSC_IRQn, ECLIC_LEVEL_TRIGGER);
	ECLIC_EnableIRQ(TSC_IRQn);

    /* Enable global interrupt */
    __enable_irq();
}

/***
 * @brief   Get the key number as show on board.
 * @param:  None
 * @retval: Key number on board,5,6 or 7
 */
uint32_t BSP_TSC_GetKeyNum(void)
{
    uint32_t i,ch;

    ch = TSC_GetStatus(TSC_STS_TYP_CHN_NUM);

    for(i=0;i<KEY_NUM;i++)
    {
        if(ch == TSC_Key_ch[i])
            return (TSC_Key_Num[i]);
    }

    return 0;
}

/***
 * @brief   init the GPIO configuration for TSC
 * @param:  None
 * @retval: None
 */
void BSP_TSC_GpioInit(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Speed   = GPIO_INPUT;

    RCC_EnableAPB2PeriphClk( RCC_APB2_PERIPH_GPIOA
                            |RCC_APB2_PERIPH_GPIOC, ENABLE);

    /*  tsc GPIOA port*/
    /*  PA4: TSC_CH0   */
    GPIO_InitStructure.Pin          = GPIO_PIN_4;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    /*  PA5: TSC_CH1   */
    GPIO_InitStructure.Pin          = GPIO_PIN_5;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /*PA9: TSC OUT*/
    GPIO_InitStructure.Pin              = GPIO_PIN_9;
    GPIO_InitStructure.GPIO_Mode        = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed       = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    RCC_EnableAPB2PeriphClk( RCC_APB2_PERIPH_AFIO, ENABLE);
    GPIO_ConfigPinRemap(GPIO_RMP_TSC_OUT_CTRL, ENABLE);
}

/***
 * @brief    Get ETR counts by counters of timer2.
 */
void TSC_EtrTimInit(TIM_Module *TIMx)
{
    TIM_TimeBaseInitType timInitStruct;

    if(TIM2 == TIMx)
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM2, ENABLE);
    else if(TIM4 == TIMx)
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM4, ENABLE);
    else
        return;

    // Reset timer to default.
    TIM_DeInit(TIMx);

    TIM_InitTimBaseStruct(&timInitStruct);
    timInitStruct.CapEtrSelFromTscEn = true;
    TIM_InitTimeBase(TIMx, &timInitStruct);

    TIM_ConfigArPreload(TIMx,ENABLE);

    TIM_ConfigExtClkMode2(  TIMx,
                            TIM_EXT_TRG_PSC_OFF,
                            TIM_EXT_TRIG_POLARITY_NONINVERTED,
                            0 );
    TIMx->CNT = 0;
    TIMx->STS = 0;
    TIM_Enable(TIMx, ENABLE);
}

void BSP_TSC_SW_Init(void)
{
    TSC_InitType Init = {0};

    /*Initialize the variables of TSC.*/
    memset((void*)&tsc_etr_key, 0, sizeof(TSC_ETR_KEY_PARA));

    /*------------------for test--------------------*/
    uint32_t i;
    for(i=0;i<KEY_NUM;i++)
    {
        tsc_etr_key.MaxPressSum[i]      = 0;
        tsc_etr_key.MaxReleaseSum[i]    = 0;
        tsc_etr_key.MinPressSum[i]      = 0xFFFFFFFF;
        tsc_etr_key.MinReleaseSum[i]    = 0xFFFFFFFF;
    }
    /*-----------------------------------------------*/

    TSC_ConfigClock(TSC_CLK_SRC_LSI);

    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TSC, ENABLE);
    BSP_TSC_GpioInit();

    Init.Out    = TSC_OUT_TIM2_ETR;
    Init.PadOpt = TSC_PAD_INTERNAL_RES;
    Init.Speed  = TSC_PAD_SPEED_0;
    TSC_Init(&Init);
    /*Select the internal resistance of each channel as 125K*/
    TSC_ConfigInternalResistor(TSC_CHN_SEL_ALL, TSC_RESR0_CHN_RESIST0_125K);

    if(Init.Out != TSC_OUT_TIM2_ETR)
    {
        TSC_EtrTimInit(TIM4);
        pEtrTimCnt = (uint16_t *)(&(TIM4->CNT));
    }
    else
    {
        TSC_EtrTimInit(TIM2);
        pEtrTimCnt = (uint16_t *)(&(TIM2->CNT));
    }

    TSC_ConfigSWMode(TSC_Key_ch[0], Init.Out, ENABLE);

    b_channel_switch_delay = true;
}




/**
* @brief  Check if all samples are done every 10ms
*         If they are done,check if there is any change of key status.
*         If key status changed,print out.
* @param: none
* @return: none
*/
void BSP_TSC_KeyCheck(void)
{
    uint32_t i = 0, j = 0, tempSum;

    if (!b_one_cycle_sample_flag)
        return;

    for (i = 0; i < KEY_NUM; i++)
    {
        tempSum = 0;
        /* sum the 10 times pulse sample */
        for (j = 0; j < SUM_NUM; j++)
        {
            tempSum += tsc_etr_key.PulseSample[i][j];
        }

        if(tsc_etr_key.EtrSumThreshold[i] == 0) 		/*init the threshold for each channel in the first 10ms*/
        {
            if(tempSum < THRESHOLD_MIN)
                tsc_etr_key.EtrSumThreshold[i] = THRESHOLD_MIN;
            else
                tsc_etr_key.EtrSumThreshold[i] = tempSum;
        }

        if ((tempSum <= THRESHOLD_MIN)||((tempSum+200) < tsc_etr_key.EtrSumThreshold[i]))
        {
            tsc_etr_key.key_status |= 1 << i;

            /*------------------for test--------------------*/
            if(tsc_etr_key.MaxPressSum[i] < tempSum)
            tsc_etr_key.MaxPressSum[i] = tempSum;

            if(tsc_etr_key.MinPressSum[i] > tempSum)
            tsc_etr_key.MinPressSum[i] = tempSum;
            /*-----------------------------------------------*/
        }
        else
        {
            tsc_etr_key.key_status &= ~(1 << i);

            /*------------------for test--------------------*/
            if(tsc_etr_key.MaxReleaseSum[i] < tempSum)
            tsc_etr_key.MaxReleaseSum[i] = tempSum;

            if(tsc_etr_key.MinReleaseSum[i] > tempSum)
            tsc_etr_key.MinReleaseSum[i] = tempSum;
            /*-----------------------------------------------*/
        }
    }


    if (tsc_etr_key.key_status != tsc_etr_key.key_status_pre)
    {
        BSP_TSC_KeyPrint(tsc_etr_key.key_status,tsc_etr_key.key_status_pre);
        tsc_etr_key.key_status_pre = tsc_etr_key.key_status;
    }

    b_one_cycle_sample_flag = false;
}
/******************************************************************/

/******************************************************************/
/**
* @brief Print the key press and release infomation.
* @param current_key: key status deteced now
* @param last_key:    key status deteced last time
* @return : none
*/
void BSP_TSC_KeyPrint(uint32_t current_key, uint32_t last_key)
{
    uint32_t i = 0, key_change;

    key_change = current_key^last_key;

    for (i = 0; i < KEY_NUM; i++)
    {
        if (key_change & (1 << i))
        {
            if(current_key & (1<<i))
            {
                printf("K%d pressed,key=0x%03x!\r\n",TSC_Key_Num[i],current_key);
                led_blink = i*2+2;
            }
            else
                printf("K%d released,key=0x%03x!\r\n",TSC_Key_Num[i],current_key);
        }
    }

}

/**
* @brief  Do it in TIM3 interrupt process.
*         Calculate the number of pulses for each channel one by one during TIM3 period.
*         The pulses are counted by TIM2
* @param: None
* @return: None
*/
void BSP_TSC_TimIrqCheck(void)
{
    static uint32_t Channel = 0;
    static uint32_t num     = 0;
    uint32_t tempDelta;

    if(b_one_cycle_sample_flag)     /*if the data of last loop is not dealed with user, wait*/
        return;

    /*Keep last value of TIMx->CNT*/
    tsc_etr_key.EtrCntPre = tsc_etr_key.EtrCnt;

    /* Get current value of TIMx->CNT*/
    tsc_etr_key.EtrCnt = *pEtrTimCnt;

    if (b_channel_switch_delay==true)
    {
        b_channel_switch_delay = false;
        return;
    }

    /* Calculate the number of pulses in 100us(between two TIM3 IRQS)*/
    if (tsc_etr_key.EtrCnt >= tsc_etr_key.EtrCntPre)
        tempDelta = tsc_etr_key.EtrCnt - tsc_etr_key.EtrCntPre;
    else
        tempDelta = tsc_etr_key.EtrCnt+0xFFFF-tsc_etr_key.EtrCntPre;

    /*save the pulse for each sample in every Channel*/
    tsc_etr_key.PulseSample[Channel][num] = tempDelta;

    if(Channel<(KEY_NUM-1)) /* switch to next channel */
        Channel++;
    else            /* Get sample of last channel */
    {
        Channel = 0;    /* switch to the first channel */
        num++;          /* loop count */
        if(num >= SUM_NUM)       /*Get enough samples for each channel*/
        {
            num = 0;        /* reset the loop count */
            b_one_cycle_sample_flag = true; /*set mark for sample finished*/
        }
    }

    TSC_SwitchChannel(TSC_Key_ch[Channel]);

    b_channel_switch_delay = true;

}

