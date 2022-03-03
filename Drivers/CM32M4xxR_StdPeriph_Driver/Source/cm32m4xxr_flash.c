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
 * @file cm32m4xxr_flash.c
 * @author CMIOT Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */
#include "nuclei_sdk_soc.h"

/** @addtogroup CM32M4xxR_StdPeriph_Driver
 * @{
 */

/** @addtogroup FLASH
 * @brief FLASH driver modules
 * @{
 */

#ifdef	DRIVER_MODULE_ENABLED_FLASH


/** @defgroup FLASH_Private_Constants FLASH Private Constants
 * @{
 */

/* Flash Control Register bits */
#define CR_Set_PG       	FLASH_CTRL_PG
#define CR_Reset_PG     	(~FLASH_CTRL_PG)
#define CR_Set_PER      	FLASH_CTRL_PER
#define CR_Reset_PER   		(~FLASH_CTRL_PER)
#define CR_Set_MER      	FLASH_CTRL_MER
#define CR_Reset_MER    	(~FLASH_CTRL_MER)
#define CR_Set_OPTPG    	FLASH_CTRL_OPTPG
#define CR_Reset_OPTPG  	(~FLASH_CTRL_OPTPG)
#define CR_Set_OPTER    	FLASH_CTRL_OPTER
#define CR_Reset_OPTER  	(~FLASH_CTRL_OPTER)
#define CR_Set_START    	FLASH_CTRL_START
#define CR_Set_LOCK     	FLASH_CTRL_LOCK
#define CR_Reset_OPTWE     	(~FLASH_CTRL_OPTWE)


/* FLASH Keys */
#define L1_RDP_Key   		((uint32_t) 0xFFFF00A5)
#define RDP_USER_Key 		((uint32_t) 0xFFF800A5)
#define L2_RDP_Key   		((uint32_t) 0xFFFF33CC)
#define FLASH_KEY1   		((uint32_t) 0x45670123)
#define FLASH_KEY2   		((uint32_t) 0xCDEF89AB)


/* Delay definition */
#define EraseTimeout   		((uint32_t) 0x000B0000)
#define ProgramTimeout 		((uint32_t) 0x00002000)

/**
 * @}
 */


/** @addtogroup FLASH_Exported_Functions
 * @{
 */

/**
 * @brief  Sets the code latency value.
 * @note   This function can be used for CM32M4xxR devices.
 * @param FLASH_Latency specifies the FLASH Latency value.
 *   This parameter can be one of the following values:
 *     @arg FLASH_LATENCY_0 FLASH Zero Latency cycle
 *     @arg FLASH_LATENCY_1 FLASH One Latency cycle
 *     @arg FLASH_LATENCY_2 FLASH Two Latency cycles
 *     @arg FLASH_LATENCY_3 FLASH Three Latency cycles
 *     @arg FLASH_LATENCY_4 FLASH Four Latency cycles
 */
void FLASH_SetLatency(uint32_t FLASH_Latency)
{
    uint32_t tmpregister = 0;

    /* Check the parameters */
    assert_param(IS_FLASH_LATENCY(FLASH_Latency));

    /* Read the AC register */
    tmpregister = FLASH->AC;

    /* Sets the Latency value */
    tmpregister &= (~FLASH_AC_LATENCY);
    tmpregister |= FLASH_Latency;

    /* Write the AC register */
    FLASH->AC = tmpregister;
}

/**
 * @brief  Enables or disables the Prefetch Buffer.
 * @note   This function can be used for CM32M4xxR devices.
 * @param FLASH_PrefetchBuf specifies the Prefetch buffer status.
 *   This parameter can be one of the following values:
 *     @arg FLASH_PrefetchBuf_EN FLASH Prefetch Buffer Enable
 *     @arg FLASH_PrefetchBuf_DIS FLASH Prefetch Buffer Disable
 */
void FLASH_PrefetchBufSet(uint32_t FLASH_PrefetchBuf)
{
    /* Check the parameters */
    assert_param(IS_FLASH_PREFETCHBUF_STATE(FLASH_PrefetchBuf));

    /* Enable or disable the Prefetch Buffer */
    FLASH->AC &= (~FLASH_AC_PRFTBFE);
    FLASH->AC |= FLASH_PrefetchBuf;
}

/**
 * @brief  ICache Reset.
 * @note   This function can be used for CM32M4xxR devices.
 */
void FLASH_iCacheRST(void)
{
    /* ICache Reset */
    FLASH->AC |= FLASH_AC_ICAHRST;
}

/**
 * @brief  Enables or disables the iCache.
 * @note   This function can be used for CM32M4xxR devices.
 * @param FLASH_iCache specifies the iCache status.
 *   This parameter can be one of the following values:
 *     @arg FLASH_iCache_EN FLASH iCache Enable
 *     @arg FLASH_iCache_DIS FLASH iCache Disable
 */
void FLASH_iCacheCmd(uint32_t FLASH_iCache)
{
    /* Check the parameters */
    assert_param(IS_FLASH_ICACHE_STATE(FLASH_iCache));

    /* Enable or disable the iCache */
    FLASH->AC &= (~FLASH_AC_ICAHEN);
    FLASH->AC |= FLASH_iCache;
}

/**
 * @brief  Checks whether the FLASH SMPSEL is SMP1 or SMP2.
 * @note   This function can be used for CM32M4xxR devices.
 * @param FLASH_smpsel specifies the SMPSEL status.
 *   This parameter can be one of the following values:
 *     @arg FLASH_SMPSEL_SMP1 FLASH SMPSEL SMP1
 *     @arg FLASH_SMPSEL_SMP2 FLASH SMPSEL SMP2
 */
void FLASH_SetSMPSELStatus(uint32_t FLASH_smpsel)
{
    /* Check the parameters */
    assert_param(IS_FLASH_SMPSEL_STATE(FLASH_smpsel));

    /* SMP1 or SMP2 */
    FLASH->CTRL &= (~FLASH_CTRL_SMPSEL);
    FLASH->CTRL |= FLASH_smpsel;
}

/**
 * @brief  Unlocks the FLASH Program Erase Controller.
 * @note   This function can be used for CM32M4xxR devices.
 *         - For CM32M4xxR devices this function unlocks flash.
 */
void FLASH_Unlock(void)
{
    /* Authorize the FKEY of flash Access */
    FLASH->KEY = FLASH_KEY1;
    FLASH->KEY = FLASH_KEY2;
}

/**
 * @brief  Locks the FLASH Program Erase Controller.
 * @note   This function can be used for CM32M4xxR devices.
 *         - For CM32M4xxR devices this function Locks flash.
 */
void FLASH_Lock(void)
{
    /* Set the Lock Bit to lock the FKEY and the CTRL of flash */
    FLASH->CTRL |= CR_Set_LOCK;
}

/**
 * @brief  Erases a specified FLASH page.
 * @note   This function can be used for CM32M4xxR devices.
 * @param Page_Address The page address to be erased.
 * @retval FLASH Status: The returned value can be: FLASH_BUSY,
 *         FLASH_ERR_PG, FLASH_ERR_PV, FLASH_ERR_WRP, FLASH_COMPL,
 *         FLASH_ERR_EV or FLASH_TIMEOUT.
 */
FLASH_STS FLASH_EraseOnePage(uint32_t Page_Address)
{
    FLASH_STS status = FLASH_COMPL;
	
    /* Check the parameters */
    assert_param(IS_FLASH_ADDRESS(Page_Address));

    /* Clears the FLASH's pending flags */
    FLASH_ClearFlag(FLASH_STS_CLRFLAG);
	
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOpt(EraseTimeout);

    if (status == FLASH_COMPL)
    {
        /* if the previous operation is completed, proceed to erase the page */
        FLASH->CTRL |= CR_Set_PER;
        FLASH->ADD = Page_Address;
        FLASH->CTRL |= CR_Set_START;

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOpt(EraseTimeout);

        /* Disable the PER Bit */
        FLASH->CTRL &= CR_Reset_PER;
    }

    /* Return the Erase Status */
    return status;
}

/**
 * @brief  Erases all FLASH pages.
 * @note   This function can be used for all CM32M4xxR devices.
 * @retval FLASH Status: The returned value can be: FLASH_BUSY,
 *         FLASH_ERR_PG, FLASH_ERR_PV, FLASH_ERR_WRP, FLASH_COMPL,
 *         FLASH_ERR_EV or FLASH_TIMEOUT.
 */
FLASH_STS FLASH_MassErase(void)
{
    FLASH_STS status = FLASH_COMPL;

    /* Clears the FLASH's pending flags */
    FLASH_ClearFlag(FLASH_STS_CLRFLAG);
	
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOpt(EraseTimeout);
    if (status == FLASH_COMPL)
    {
        /* if the previous operation is completed, proceed to erase all pages */
        FLASH->CTRL |= CR_Set_MER;
        FLASH->CTRL |= CR_Set_START;

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOpt(EraseTimeout);

        /* Disable the MER Bit */
        FLASH->CTRL &= CR_Reset_MER;
    }

    /* Return the Erase Status */
    return status;
}

/**
 * @brief  Erases the FLASH option bytes.
 * @note   This functions erases all option bytes except the Read protection (RDP).
 * @note   This function can be used for CM32M4xxR devices.
 * @retval FLASH Status: The returned value can be: FLASH_BUSY,
 *         FLASH_ERR_PG, FLASH_ERR_PV, FLASH_ERR_WRP, FLASH_COMPL,
 *         FLASH_ERR_EV, FLASH_ERR_RDP2 or FLASH_TIMEOUT.
 */
FLASH_STS FLASH_EraseOB(void)
{
    uint32_t rdptmp = L1_RDP_Key;

    FLASH_STS status = FLASH_COMPL;

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status = FLASH_ERR_RDP2;
        return status;
    }

    /* Get the actual read protection Option Byte value */
    if (FLASH_GetReadOutProtectionSTS() != RESET)
    {
        rdptmp = (L1_RDP_Key & OB_RDP1_USER_USER_Msk);
    }

    /* Clears the FLASH's pending flags */
    FLASH_ClearFlag(FLASH_STS_CLRFLAG);
	
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOpt(EraseTimeout);
    if (status == FLASH_COMPL)
    {
        /* Authorize the small information block programming */
        FLASH->OPTKEY = FLASH_KEY1;
        FLASH->OPTKEY = FLASH_KEY2;

        /* if the previous operation is completed, proceed to erase the option bytes */
        FLASH->CTRL |= CR_Set_OPTER;
        FLASH->CTRL |= CR_Set_START;
		
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOpt(EraseTimeout);

        if (status == FLASH_COMPL)
        {
            /* Clears the FLASH's pending flags */
            FLASH_ClearFlag(FLASH_STS_CLRFLAG);

            /* if the erase operation is completed, disable the OPTER Bit */
            FLASH->CTRL &= CR_Reset_OPTER;

            /* Enable the Option Bytes Programming operation */
            FLASH->CTRL |= CR_Set_OPTPG;
			
            /* Restore the last read protection Option Byte value */
            OPB->USER_RDP = (uint32_t)rdptmp;
			
            /* Wait for last operation to be completed */
            status = FLASH_WaitForLastOpt(ProgramTimeout);
            if (status != FLASH_TIMEOUT)
            {
                /* if the program operation is completed, disable the OPTPG Bit */
                FLASH->CTRL &= CR_Reset_OPTPG;
            }
        }
        else
        {
            if (status != FLASH_TIMEOUT)
            {
                /* Disable the OPTER Bit */
                FLASH->CTRL &= CR_Reset_OPTER;
            }
        }
		FLASH->CTRL &= CR_Reset_OPTWE;
    }
	
    /* Return the erase status */
    return status;
}

/**
 * @brief  Programs a word at a specified address.
 * @note   This function can be used for CM32M4xxR devices.
 * @param Address specifies the address to be programmed.
 * @param Data specifies the data to be programmed.
 * @retval FLASH Status: The returned value can be: FLASH_BUSY,
 *         FLASH_ERR_PG, FLASH_ERR_PV, FLASH_ERR_WRP, FLASH_COMPL,
 *         FLASH_ERR_EV, FLASH_ERR_ADD or FLASH_TIMEOUT.
 */
FLASH_STS FLASH_ProgramWord(uint32_t Address, uint32_t Data)
{
    FLASH_STS status  = FLASH_COMPL;
    __IO uint32_t tmp = 0;

    /* Check the parameters */
    assert_param(IS_FLASH_ADDRESS(Address));

    if((Address & (uint32_t)0x3) != 0)
    {
        /* The programming address is not a multiple of 4 */
        status = FLASH_ERR_ADD;
        return status;
    }

    /* Clears the FLASH's pending flags */
    FLASH_ClearFlag(FLASH_STS_CLRFLAG);
	
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOpt(ProgramTimeout);

    if (status == FLASH_COMPL)
    {
        /* if the previous operation is completed, proceed to program the new word */
        FLASH->CTRL |= CR_Set_PG;

        *(__IO uint32_t*)Address = (uint32_t)Data;
		
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOpt(ProgramTimeout);

        /* Disable the PG Bit */
        FLASH->CTRL &= CR_Reset_PG;
    }

    /* Return the Program Status */
    return status;
}

/**
 * @brief  Programs a half word at a specified Option Byte Data address.
 * @note   This function can be used for CM32M4xxR devices.
 * @param Data specifies the data to be programmed(Data0 and Data1).
 * @retval FLASH Status: The returned value can be: FLASH_BUSY,
 *         FLASH_ERR_PG, FLASH_ERR_PV, FLASH_ERR_WRP, FLASH_COMPL,
 *         FLASH_ERR_EV, FLASH_ERR_RDP2 or FLASH_TIMEOUT.
 */
FLASH_STS FLASH_ProgramOBData(uint32_t Data)
{
    FLASH_STS status = FLASH_COMPL;
	
	uint32_t Address = 0x1FFFF804;
	/* Clears the FLASH's pending flags */
	FLASH_ClearFlag(FLASH_STS_CLRFLAG);
	
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOpt(ProgramTimeout);

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status = FLASH_ERR_RDP2;
        return status;
    }
	
    if (status == FLASH_COMPL)
    {
        /* Authorize the small information block programming */
        FLASH->OPTKEY = FLASH_KEY1;
        FLASH->OPTKEY = FLASH_KEY2;
		
        /* Enables the Option Bytes Programming operation */
        FLASH->CTRL |= CR_Set_OPTPG;
		
        *(__IO uint32_t*)Address = (uint32_t)Data;

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOpt(ProgramTimeout);
        if (status != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CR_Reset_OPTPG;
        }
		FLASH->CTRL &= CR_Reset_OPTWE;
    }
	
    /* Return the Option Byte Data Program Status */
    return status;
}

/**
 * @brief  Write protects the desired pages
 * @note   This function can be used for CM32M4xxR devices.
 * @param FLASH_Pages specifies the address of the pages to be write protected.
 *   This parameter can be:
 *     value between FLASH_WRPR_Pages0to1 and FLASH_WRPR_Pages60to61
 *       or FLASH_WRPR_Pages62to255
 *       or FLASH_WRPR_AllPages
 * @retval FLASH Status: The returned value can be: FLASH_BUSY,
 *         FLASH_ERR_PG, FLASH_ERR_PV, FLASH_ERR_WRP, FLASH_COMPL,
 *         FLASH_ERR_EV, FLASH_ERR_RDP2 or FLASH_TIMEOUT.
 */
FLASH_STS FLASH_EnWriteProtection(uint32_t FLASH_Pages)
{
    uint16_t WRP0_Data = 0xFFFF;
	uint16_t WRP1_Data = 0xFFFF;
	uint16_t WRP2_Data = 0xFFFF;
	uint16_t WRP3_Data = 0xFFFF;

    FLASH_STS status = FLASH_COMPL;

    /* Check the parameters */
    assert_param(IS_FLASH_WRP_PAGE(FLASH_Pages));

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status = FLASH_ERR_RDP2;
        return status;
    }
	
    FLASH_Pages = (uint32_t)(~FLASH_Pages);
    WRP0_Data   = (uint16_t)(FLASH_Pages  & FLASH_WRP_WRPT_0_7);
    WRP1_Data   = (uint16_t)((FLASH_Pages & FLASH_WRP_WRPT_8_15) >> 8);
    WRP2_Data   = (uint16_t)((FLASH_Pages & FLASH_WRP_WRPT_16_23) >> 16);
    WRP3_Data   = (uint16_t)((FLASH_Pages & FLASH_WRP_WRPT_24_31) >> 24);

    /* Clears the FLASH's pending flags */
    FLASH_ClearFlag(FLASH_STS_CLRFLAG);
	
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOpt(ProgramTimeout);
    if (status == FLASH_COMPL)
    {
        /* Authorizes the small information block programming */
        FLASH->OPTKEY = FLASH_KEY1;
        FLASH->OPTKEY = FLASH_KEY2;
        FLASH->CTRL |= CR_Set_OPTPG;

        if ((WRP0_Data != 0xFF) || (WRP1_Data != 0xFF))
        {
            OPB->WRP1_WRP0 = (((uint32_t) WRP0_Data) | (((uint32_t) WRP1_Data) << OB_WRP1_WRP0_WRP1_Pos));

            /* Wait for last operation to be completed */
            status = FLASH_WaitForLastOpt(ProgramTimeout);
        }

        if (((WRP2_Data != 0xFF) || (WRP3_Data != 0xFF)) && (status == FLASH_COMPL))
        {
            /* Clears the FLASH's pending flags */
            FLASH_ClearFlag(FLASH_STS_CLRFLAG);
			
            OPB->WRP3_WRP2 = (((uint32_t) WRP2_Data) | (((uint32_t) WRP3_Data) << OB_WRP3_WRP2_WRP3_Pos));

            /* Wait for last operation to be completed */
            status = FLASH_WaitForLastOpt(ProgramTimeout);
        }

        if (status != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CR_Reset_OPTPG;
        }
		FLASH->CTRL &= CR_Reset_OPTWE;
    }
	
    /* Return the write protection operation Status */
    return status;
}

/**
 * @brief  Enables or disables the read out protection.
 * @note   If the user has already programmed the other option bytes before calling
 *   this function, he must re-program them since this function erases all option bytes.
 * @note   This function can be used for CM32M4xxR devices.
 * @param Cmd new state of the ReadOut Protection.
 *   This parameter can be: ENABLE or DISABLE.
 * @retval FLASH Status: The returned value can be: FLASH_BUSY,
 *         FLASH_ERR_PG, FLASH_ERR_PV, FLASH_ERR_WRP, FLASH_COMPL,
 *         FLASH_ERR_EV, FLASH_ERR_RDP2 or FLASH_TIMEOUT.
 */
FLASH_STS FLASH_ReadOutProtectionL1(FunctionalState Cmd)
{
    uint32_t usertmp;
    FLASH_STS status = FLASH_COMPL;

    usertmp = ((FLASH->OB & FLASH_OB_USER_Msk) << 0x0E);
	
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status = FLASH_ERR_RDP2;
        return status;
    }

    /* Clears the FLASH's pending flags */
    FLASH_ClearFlag(FLASH_STS_CLRFLAG);
	
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOpt(EraseTimeout);
	
    if (status == FLASH_COMPL)
    {
        /* Authorizes the small information block programming */
        FLASH->OPTKEY = FLASH_KEY1;
        FLASH->OPTKEY = FLASH_KEY2;
        FLASH->CTRL |= CR_Set_OPTER;
        FLASH->CTRL |= CR_Set_START;
		
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOpt(EraseTimeout);
        if (status == FLASH_COMPL)
        {
            /* Clears the FLASH's pending flags */
            FLASH_ClearFlag(FLASH_STS_CLRFLAG);
			
            /* If the erase operation is completed, disable the OPTER Bit */
            FLASH->CTRL &= CR_Reset_OPTER;
			
            /* Enable the Option Bytes Programming operation */
            FLASH->CTRL |= CR_Set_OPTPG;
			
            if (Cmd != DISABLE)
            {
                OPB->USER_RDP = (OB_RDP1_USER_USER_Msk & usertmp);
            }
            else
            {
                OPB->USER_RDP = (L1_RDP_Key & OB_RDP1_USER_RDP1_Msk) | usertmp;
            }
			
            /* Wait for last operation to be completed */
            status = FLASH_WaitForLastOpt(EraseTimeout);

            if (status != FLASH_TIMEOUT)
            {
                /* if the program operation is completed, disable the OPTPG Bit */
                FLASH->CTRL &= CR_Reset_OPTPG;
            }
        }
        else
        {
            if (status != FLASH_TIMEOUT)
            {
                /* Disable the OPTER Bit */
                FLASH->CTRL &= CR_Reset_OPTER;
            }
        }
		FLASH->CTRL &= CR_Reset_OPTWE;
    }
	
    /* Return the protection operation Status */
    return status;
}

/**
 * @brief  Enables the read out protection L2.
 * @note   If the user has already programmed the other option bytes before calling
 *   this function, he must re-program them since this function erases all option bytes.
 * @note   This function can be used for CM32M4xxR devices.
 * @retval FLASH Status: The returned value can be: FLASH_BUSY,
 *         FLASH_ERR_PG, FLASH_ERR_PV, FLASH_ERR_WRP, FLASH_COMPL,
 *         FLASH_ERR_EV, FLASH_ERR_RDP2 or FLASH_TIMEOUT.
 */
FLASH_STS FLASH_ReadOutProtectionL2_ENABLE(void)
{
    uint32_t usertmp;
    FLASH_STS status = FLASH_COMPL;

    usertmp = ((FLASH->OB & FLASH_OB_USER_Msk) << 0x0E);
  
    /* Get the actual read protection L1 Option Byte value */
    if (FLASH_GetReadOutProtectionSTS() == RESET)
    {
        usertmp |= (L1_RDP_Key & OB_RDP1_USER_USER_Msk);
    }
	
    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status = FLASH_ERR_RDP2;
        return status;
    }

    /* Clears the FLASH's pending flags */
    FLASH_ClearFlag(FLASH_STS_CLRFLAG);
	
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOpt(EraseTimeout);
    if (status == FLASH_COMPL)
    {
        /* Authorizes the small information block programming */
        FLASH->OPTKEY = FLASH_KEY1;
        FLASH->OPTKEY = FLASH_KEY2;
        FLASH->CTRL |= CR_Set_OPTER;
        FLASH->CTRL |= CR_Set_START;
		
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOpt(EraseTimeout);
        if (status == FLASH_COMPL)
        {
            /* Clears the FLASH's pending flags */
            FLASH_ClearFlag(FLASH_STS_CLRFLAG);
			
            /* if the erase operation is completed, disable the OPTER Bit */
            FLASH->CTRL &= CR_Reset_OPTER;
			
            /* Enable the Option Bytes Programming operation */
            FLASH->CTRL |= CR_Set_OPTPG;

            OPB->USER_RDP = usertmp;
			
            /* Wait for last operation to be completed */
            status = FLASH_WaitForLastOpt(EraseTimeout);

            if (status == FLASH_COMPL)
            {
                /* Clears the FLASH's pending flags */
                FLASH_ClearFlag(FLASH_STS_CLRFLAG);
				
                /* Enables the read out protection L2 */
                OPB->RDP2 = L2_RDP_Key;

                /* Wait for last operation to be completed */
                status = FLASH_WaitForLastOpt(EraseTimeout);
            }

            if (status != FLASH_TIMEOUT)
            {
                /* if the program operation is completed, disable the OPTPG Bit */
                FLASH->CTRL &= CR_Reset_OPTPG;
            }
        }
        else
        {
            if (status != FLASH_TIMEOUT)
            {
                /* Disable the OPTER Bit */
                FLASH->CTRL &= CR_Reset_OPTER;
            }
        }
		FLASH->CTRL &= CR_Reset_OPTWE;
    }
	
    /* Return the protection operation Status */
    return status;
}

/**
 * @brief  Programs the FLASH User Option Byte: IWDG_SW / RST_STOP / RST_STDBY.
 * @note   This function can be used for CM32M4xxR devices.
 * @param OB_IWDG Selects the IWDG mode
 *   This parameter can be one of the following values:
 *     @arg OB_IWDG_SW Software IWDG selected
 *     @arg OB_IWDG_HW Hardware IWDG selected
 * @param OB_STOP Reset event when entering STOP mode.
 *   This parameter can be one of the following values:
 *     @arg OB_STOP0_NORST No reset generated when entering in STOP
 *     @arg OB_STOP0_RST Reset generated when entering in STOP
 * @param OB_STDBY Reset event when entering Standby mode.
 *   This parameter can be one of the following values:
 *     @arg OB_STDBY_NORST No reset generated when entering in STANDBY
 *     @arg OB_STDBY_RST Reset generated when entering in STANDBY
 * @retval FLASH Status: The returned value can be: FLASH_BUSY,
 *         FLASH_ERR_PG, FLASH_ERR_PV, FLASH_ERR_WRP, FLASH_COMPL,
 *         FLASH_ERR_EV, FLASH_ERR_RDP2 or FLASH_TIMEOUT.
 */
FLASH_STS FLASH_ConfigUserOB(uint16_t OB_IWDG, uint16_t OB_STOP, uint16_t OB_STDBY)
{
    uint32_t rdptmp = RDP_USER_Key;

    FLASH_STS status = FLASH_COMPL;

    /* Check the parameters */
    assert_param(IS_OB_IWDG_SOURCE(OB_IWDG));
    assert_param(IS_OB_STOP0_SOURCE(OB_STOP));
    assert_param(IS_OB_STDBY_SOURCE(OB_STDBY));

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status = FLASH_ERR_RDP2;
        return status;
    }

    /* Get the actual read protection Option Byte value */
    if (FLASH_GetReadOutProtectionSTS() != RESET)
    {
        rdptmp = 0xFFF80000;
    }


    /* Clears the FLASH's pending flags */
    FLASH_ClearFlag(FLASH_STS_CLRFLAG);
	
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOpt(EraseTimeout);
    if (status == FLASH_COMPL)
    {
		/* Authorize the small information block programming */
		FLASH->OPTKEY = FLASH_KEY1;
		FLASH->OPTKEY = FLASH_KEY2;
        /* if the previous operation is completed, proceed to erase the option bytes */
        FLASH->CTRL |= CR_Set_OPTER;
        FLASH->CTRL |= CR_Set_START;
		
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOpt(EraseTimeout);

        if (status == FLASH_COMPL)
        {
            /* Clears the FLASH's pending flags */
            FLASH_ClearFlag(FLASH_STS_CLRFLAG);

            /* if the erase operation is completed, disable the OPTER Bit */
            FLASH->CTRL &= CR_Reset_OPTER;

            /* Enable the Option Bytes Programming operation */
            FLASH->CTRL |= CR_Set_OPTPG;
			
            /* Restore the last read protection Option Byte value */
			OPB->USER_RDP = (uint32_t)rdptmp | ((uint32_t)(OB_IWDG | OB_STOP | OB_STDBY | 0x00F8) << 16);
				
            /* Wait for last operation to be completed */
            status = FLASH_WaitForLastOpt(ProgramTimeout);

            if (status != FLASH_TIMEOUT)
            {
                /* if the program operation is completed, disable the OPTPG Bit */
                FLASH->CTRL &= CR_Reset_OPTPG;
            }
        }
        else
        {
            if (status != FLASH_TIMEOUT)
            {
                /* Disable the OPTER Bit */
                FLASH->CTRL &= CR_Reset_OPTER;
            }
        }
		FLASH->CTRL &= CR_Reset_OPTWE;
    }

    /* Return the Option Byte program Status */
    return status;
}

/**
 * @brief  Returns the FLASH User Option Bytes values.
 * @note   This function can be used for CM32M4xxR devices.
 * @retval The FLASH User Option Bytes values:IWDG_SW(Bit0), RST_STOP(Bit1)
 *         and RST_STDBY(Bit2).
 */
uint32_t FLASH_GetUserOB(void)
{
    /* Return the User Option Byte */
    return (uint32_t)((FLASH->OB << 27) >> 29);
}

/**
 * @brief  Returns the FLASH Write Protection Option Bytes Register value.
 * @note   This function can be used for CM32M4xxR devices.
 * @retval The FLASH Write Protection  Option Bytes Register value
 */
uint32_t FLASH_GetWriteProtectionOB(void)
{
    /* Return the Flash write protection Register value */
    return (uint32_t)(FLASH->WRP);
}

/**
 * @brief  Checks whether the FLASH Read Out Protection Status is set or not.
 * @note   This function can be used for CM32M4xxR devices.
 * @retval FLASH ReadOut Protection Status(SET or RESET)
 */
FlagStatus FLASH_GetReadOutProtectionSTS(void)
{
    FlagStatus readoutstatus = RESET;
	
    if ((FLASH->OB & FLASH_OB_RDPRT1_Msk) != (uint32_t)RESET)
    {
        readoutstatus = SET;
    }
    else
    {
        readoutstatus = RESET;
    }
	
    return readoutstatus;
}

/**
 * @brief  Checks whether the FLASH Read Out Protection L2 Status is set or not.
 * @note   This function can be used for CM32M4xxR devices.
 * @retval FLASH ReadOut Protection L2 Status(SET or RESET)
 */
FlagStatus FLASH_GetReadOutProtectionL2STS(void)
{
    FlagStatus readoutstatus = RESET;
	
    if ((FLASH->OB & FLASH_OB_RDPRT2_Msk) != (uint32_t)RESET)
    {
        readoutstatus = SET;
    }
    else
    {
        readoutstatus = RESET;
    }
	
    return readoutstatus;
}

/**
 * @brief  Checks whether the FLASH Prefetch Buffer status is set or not.
 * @note   This function can be used for CM32M4xxR devices.
 * @retval FLASH Prefetch Buffer Status (SET or RESET).
 */
FlagStatus FLASH_GetPrefetchBufSTS(void)
{
    FlagStatus bitstatus = RESET;

    if ((FLASH->AC & FLASH_AC_PRFTBFS_Msk) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
	
    /* Return the new state of FLASH Prefetch Buffer Status (SET or RESET) */
    return bitstatus;
}

/**
 * @brief  Checks whether the FLASH SMPSEL is SMP1 or SMP2.
 * @note   This function can be used for CM32M4xxR devices.
 * @retval FLASH SMPSEL (@arg FLASH_SMP1 or @arg FLASH_SMP2).
 */
FLASH_SMPSEL FLASH_GetSMPSELStatus(void)
{
    FLASH_SMPSEL bitstatus = FLASH_SMP1;

    if ((FLASH->CTRL & FLASH_CTRL_SMPSEL_Msk) != (uint32_t)FLASH_SMP1)
    {
        bitstatus = FLASH_SMP2;
    }
    else
    {
        bitstatus = FLASH_SMP1;
    }
	
    /* Return the new state of FLASH SMPSEL (FLASH_SMP1 or FLASH_SMP2) */
    return bitstatus;
}

/**
 * @brief  Enables or disables the specified FLASH interrupts.
 * @note   This function can be used for CM32M4xxR devices.
 * @param FLASH_INT specifies the FLASH interrupt sources to be enabled or disabled.
 *   This parameter can be any combination of the following values:
 *     @arg FLASH_IT_ERROR FLASH Error Interrupt
 *     @arg FLASH_INT_FERR EVERR PVERR Interrupt
 *     @arg FLASH_INT_EOP FLASH end of operation Interrupt
 * @param Cmd new state of the specified Flash interrupts.
 *   This parameter can be: ENABLE or DISABLE.
 */
void FLASH_INTConfig(uint32_t FLASH_INT, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FLASH_INT(FLASH_INT));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if (Cmd != DISABLE)
    {
        /* Enable the interrupt sources */
        FLASH->CTRL |= FLASH_INT;
    }
    else
    {
        /* Disable the interrupt sources */
        FLASH->CTRL &= ~(uint32_t)FLASH_INT;
    }
}

/**
 * @brief  Checks whether the specified FLASH flag is set or not.
 * @note   This function can be used for CM32M4xxR devices.
 * @param FLASH_FLAG specifies the FLASH flag to check.
 *   This parameter can be one of the following values:
 *     @arg FLASH_FLAG_BUSY FLASH Busy flag
 *     @arg FLASH_FLAG_PGERR FLASH Program error flag
 *     @arg FLASH_FLAG_PVERR FLASH Program Verify ERROR flag
 *     @arg FLASH_FLAG_WRPERR FLASH Write protected error flag
 *     @arg FLASH_FLAG_EOP FLASH End of Operation flag
 *     @arg FLASH_FLAG_EVERR FLASH Erase Verify ERROR flag
 *     @arg FLASH_FLAG_OBERR FLASH Option Byte error flag
 * @retval The new state of FLASH_FLAG (SET or RESET).
 */
FlagStatus FLASH_GetFlagSTS(uint32_t FLASH_FLAG)
{
    FlagStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_FLASH_GET_FLAG(FLASH_FLAG));
	
    if (FLASH_FLAG == FLASH_FLAG_OBERR)
    {
        if ((FLASH->OB & FLASH_FLAG_OBERR) != (uint32_t)RESET)
        {
            bitstatus = SET;
        }
        else
        {
            bitstatus = RESET;
        }
    }
    else
    {
        if ((FLASH->STS & FLASH_FLAG) != (uint32_t)RESET)
        {
            bitstatus = SET;
        }
        else
        {
            bitstatus = RESET;
        }
    }

    /* Return the new state of FLASH_FLAG (SET or RESET) */
    return bitstatus;
}

/**
 * @brief  Clears the FLASH's pending flags.
 * @note   This function can be used for CM32M4xxR devices.
 * @param FLASH_FLAG specifies the FLASH flags to clear.
 *   This parameter can be any combination of the following values:
 *     @arg FLASH_FLAG_PGERR FLASH Program error flag
 *     @arg FLASH_FLAG_PVERR FLASH Program Verify ERROR flag
 *     @arg FLASH_FLAG_WRPERR FLASH Write protected error flag
 *     @arg FLASH_FLAG_EOP FLASH End of Operation flag
 *     @arg FLASH_FLAG_EVERR FLASH Erase Verify ERROR flag
 */
void FLASH_ClearFlag(uint32_t FLASH_FLAG)
{
    /* Check the parameters */
    assert_param(IS_FLASH_CLEAR_FLAG(FLASH_FLAG));

    /* Clear the flags */
    FLASH->STS |= FLASH_FLAG;
}

/**
 * @brief  Returns the FLASH Status.
 * @note   This function can be used for CM32M4xxR devices.
 * @retval FLASH Status: The returned value can be: FLASH_BUSY,
 *         FLASH_ERR_PG, FLASH_ERR_PV, FLASH_ERR_WRP, FLASH_COMPL,
 *         FLASH_ERR_EV.
 */
FLASH_STS FLASH_GetSTS(void)
{
    FLASH_STS flashstatus = FLASH_COMPL;

    if ((FLASH->STS & FLASH_FLAG_BUSY) == FLASH_FLAG_BUSY)
    {
        flashstatus = FLASH_BUSY;
    }
    else
    {
        if ((FLASH->STS & FLASH_FLAG_PGERR) != 0)
        {
            flashstatus = FLASH_ERR_PG;
        }
        else
        {
            if ((FLASH->STS & FLASH_FLAG_PVERR) != 0)
            {
                flashstatus = FLASH_ERR_PV;
            }
            else
            {
                if ((FLASH->STS & FLASH_FLAG_WRPERR) != 0)
                {
                    flashstatus = FLASH_ERR_WRP;
                }
                else
                {
                    if ((FLASH->STS & FLASH_FLAG_EVERR) != 0)
                    {
                        flashstatus = FLASH_ERR_EV;
                    }
                    else
                    {
                        flashstatus = FLASH_COMPL;
                    }
                }
            }
        }
    }

    /* Return the Flash Status */
    return flashstatus;
}

/**
 * @brief  Waits for a Flash operation to complete or a TIMEOUT to occur.
 * @note   This function can be used for CM32M4xxR devices.
 * @param Timeout FLASH programming Timeout
 * @retval FLASH Status: The returned value can be: FLASH_BUSY,
 *         FLASH_ERR_PG, FLASH_ERR_PV, FLASH_ERR_WRP, FLASH_COMPL,
 *         FLASH_ERR_EV or FLASH_TIMEOUT.
 */
FLASH_STS FLASH_WaitForLastOpt(uint32_t Timeout)
{
    FLASH_STS status = FLASH_COMPL;

    /* Check for the Flash Status */
    status = FLASH_GetSTS();
	
    /* Wait for a Flash operation to complete or a TIMEOUT to occur */
    while ((status == FLASH_BUSY) && (Timeout != 0x00))
    {
        status = FLASH_GetSTS();
        Timeout--;
    }
	
    if (Timeout == 0x00)
    {
        status = FLASH_TIMEOUT;
    }
	
    /* Return the operation status */
    return status;
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
