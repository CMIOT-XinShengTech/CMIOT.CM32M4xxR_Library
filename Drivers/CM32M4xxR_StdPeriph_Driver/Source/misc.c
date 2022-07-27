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
 * @file misc.c
 * @author CMIOT Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */

#include <stdio.h>
#include "misc.h"


/** @addtogroup CM32M4xxR_StdPeriph_Driver
 * @{
 */

/** @defgroup MISC MISC
 * @brief MISC driver modules
 * @{
 */

#ifdef	DRIVER_MODULE_ENABLED_MISC

/** @defgroup MISC_Exported_Functions MISC Exported Functions
 * @{
 */

#if (__PMP_PRESENT == 1)

void PMP_ConfigRegion(PMP_Region_InitTypeDef *PMP_Init)
{
  uint8_t pmpcfg = 0;
  uint32_t addr = PMP_Init->BaseAddress >> 2;
  /* Check the parameters */
  assert_param(IS_PMP_REGION_NUMBER(PMP_Init->Number));
  assert_param(IS_PMP_REGION_ENABLE(PMP_Init->Enable));
  
  if((PMP_Init->Enable) == PMP_REGION_ENABLE)
  {
  
    assert_param(IS_PMP_REGION_PERMISSION_ATTRIBUTE(PMP_Init->AccessPermission));
    assert_param(IS_PMP_REGION_SIZE(PMP_Init->Size));
    
    pmpcfg = (PMP_Init->Lock << PMP_LOCK_BITS_OFFSET) |
             (PMP_Init->AddressMatching << PMP_MATCHING_BITS_OFFSET) |
             (PMP_Init->AccessPermission << PMP_ACCESS_BITS_OFFSET);
             
    if(PMP_Init->AddressMatching == PMP_ADDRESS_MATCHING_NAPOT)
    {
      uint32_t bits = 1 << PMP_Init->Size;
      addr = (addr & (~bits)) | (bits - 1);
    }
    
  }
  else
  {
    pmpcfg = PMP_ADDRESS_MATCHING_NONE << PMP_MATCHING_BITS_OFFSET;
  }
  
  __set_PMPADDRx(PMP_Init->Number, addr);
  __set_PMPxCFG(PMP_Init->Number, pmpcfg);
  
}

void PMP_ClearRegion(uint8_t id)
{
  PMP_Region_InitTypeDef init;
  init.Enable = PMP_REGION_DISABLE;
  init.BaseAddress = 0;
  init.Number = id;
  PMP_ConfigRegion(&init);
}

#endif

#if (__sPMP_PRESENT == 1)

void sPMP_ConfigRegion(sPMP_Region_InitTypeDef *sPMP_Init)
{
  uint8_t pmpcfg = 0;
  uint32_t addr = sPMP_Init->BaseAddress >> 2;
  /* Check the parameters */
  assert_param(IS_SPMP_REGION_NUMBER(sPMP_Init->Number));
  assert_param(IS_SPMP_REGION_ENABLE(sPMP_Init->Enable));
  assert_param(IS_SPMP_REGION_USERMODE(sPMP_Init->UserMode));
	
  if((sPMP_Init->Enable) == SPMP_REGION_ENABLE)
  {
  
    assert_param(IS_SPMP_REGION_PERMISSION_ATTRIBUTE(sPMP_Init->AccessPermission));
    assert_param(IS_SPMP_REGION_SIZE(sPMP_Init->Size));
    
    pmpcfg = (sPMP_Init->Lock << SPMP_LOCK_BITS_OFFSET) |
             (sPMP_Init->AddressMatching << SPMP_MATCHING_BITS_OFFSET) |
             (sPMP_Init->UserMode << SPMP_USER_BITS_OFFSET) |
             (sPMP_Init->AccessPermission << SPMP_ACCESS_BITS_OFFSET);
             
    if(sPMP_Init->AddressMatching == SPMP_ADDRESS_MATCHING_NAPOT)
    {
      uint32_t bits = 1 << sPMP_Init->Size;
      addr = (addr & (~bits)) | (bits - 1);
    }
    
  }
  else
  {
    pmpcfg = SPMP_ADDRESS_MATCHING_NONE << SPMP_MATCHING_BITS_OFFSET;
  }
  
  __set_sPMPADDRx(sPMP_Init->Number, addr);
  __set_sPMPxCFG(sPMP_Init->Number, pmpcfg);
  
}

void sPMP_ClearRegion(uint8_t id)
{
  sPMP_Region_InitTypeDef init;
  init.Enable = SPMP_REGION_DISABLE;
  init.BaseAddress = 0;
  init.Number = id;
  init.UserMode = SPMP_USERMODE_RESET;
  sPMP_ConfigRegion(&init);
}

#endif

/**
 * @brief  Delay function based on system timer.
 */

/**
 * @brief  Function of delay nus.
 * @param  nus specifies Delay number of us.
 */
void delay_us(uint32_t nus)
{
    uint64_t temp;
    uint64_t cmpvalue;

    cmpvalue = SysTimer_GetLoadValue() + nus*(SystemCoreClock / 1000000);

    do
    {
        temp = SysTimer_GetLoadValue();
    } while (temp < cmpvalue); // waiting time arrives
}

/**
 * @brief  Function of delay nms.
 * @param  nms specifies Delay number of ms.
 */
void delay_ms(uint32_t nms)
{
    uint64_t temp;
    uint64_t cmpvalue;

    cmpvalue = SysTimer_GetLoadValue() + nms*(SystemCoreClock / 1000);

    do
    {
        temp = SysTimer_GetLoadValue();
    } while (temp < cmpvalue); 						// waiting time arrives
}

/**
 * @brief  when driver Interface parameter check failed, it will call assert_failed .
 * @param  expr specifies The expression of parameter check.
 * @param  file specifies source file name of the expression.
 * @param  line specifies source line number of the expression.
 */
__WEAK void assert_failed(const uint8_t* expr, const uint8_t* file, uint32_t line)
{
	printf("assertion failed: `%s` at %s:%d\r\n", expr, file, line);
	while(1)
	{

	}
}


/**
 * @brief  Returns the UCID.
 * @param UCIDbuf used to get and store the UCID info
 */

void GetUCID(uint8_t *UCIDbuf)
{
    assert_param(UCIDbuf != 0);

    UCIDbuf[0] = *((uint8_t*)0x1FFFF7C0);
    UCIDbuf[1] = *((uint8_t*)0x1FFFF7F4);
    UCIDbuf[2] = *((uint8_t*)0x1FFFF7C4);
    UCIDbuf[3] = *((uint8_t*)0x1FFFF7C5);
    UCIDbuf[4] = *((uint8_t*)0x1FFFF7C6);
    UCIDbuf[5] = *((uint8_t*)0x1FFFF7C7);
    UCIDbuf[6] = *((uint8_t*)0x1FFFF7C8);
    UCIDbuf[7] = *((uint8_t*)0x1FFFF7C9);
    UCIDbuf[8] = *((uint8_t*)0x1FFFF7CA);
    UCIDbuf[9] = *((uint8_t*)0x1FFFF7CB);
    UCIDbuf[10] = *((uint8_t*)0x1FFFF7CC);
    UCIDbuf[11] = *((uint8_t*)0x1FFFF7CD);
    UCIDbuf[12] = *((uint8_t*)0x1FFFF7CE);
    UCIDbuf[13] = *((uint8_t*)0x1FFFF7F0);
    UCIDbuf[14] = *((uint8_t*)0x1FFFF7F1);
    UCIDbuf[15] = *((uint8_t*)0x1FFFF7F2);

}

/**
 * @brief  Returns the UID.
 * @param UIDbuf used to get and store the UID info
 */

void GetUID(uint8_t *UIDbuf)
{
    assert_param(UIDbuf != 0);

    UIDbuf[0] = *((uint8_t*)0x1FFFF7C0);
    UIDbuf[1] = *((uint8_t*)0x1FFFF7F4);
    UIDbuf[2] = *((uint8_t*)0x1FFFF7C7);
    UIDbuf[3] = *((uint8_t*)0x1FFFF7C8);
    UIDbuf[4] = *((uint8_t*)0x1FFFF7C9);
    UIDbuf[5] = *((uint8_t*)0x1FFFF7CA);
    UIDbuf[6] = *((uint8_t*)0x1FFFF7CB);
    UIDbuf[7] = *((uint8_t*)0x1FFFF7CC);
    UIDbuf[8] = *((uint8_t*)0x1FFFF7CD);
    UIDbuf[9] = *((uint8_t*)0x1FFFF7CE);
    UIDbuf[10] = *((uint8_t*)0x1FFFF7F1);
    UIDbuf[11] = *((uint8_t*)0x1FFFF7F2);
}


/**
 * @}
 */

#endif

/**
 * @}
 */


/**
 * @}
 */

