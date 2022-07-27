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
 * @file misc.h
 * @author CMIOT
 * @version v1.0.0
 *
 * @copyright COPYRIGHT(c) 2020, China Mobile IOT. All rights reserved.
 */
#ifndef __MISC_H__
#define __MISC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "nuclei_sdk_soc.h"


/** @addtogroup CM32M4xxR_StdPeriph_Driver
 * @{
 */

/** @addtogroup MISC
 * @{
 */

/** @defgroup MISC_Exported_Macros MISC Exported Macros
  * @{
  */
#if (__PMP_PRESENT == 1)

#define PMP_ACCESS_BITS_OFFSET 0
#define PMP_MATCHING_BITS_OFFSET 3
#define PMP_LOCK_BITS_OFFSET 7

/** @defgroup RISCV_PMP_Region_Enable RISC-V PMP Region Enable
  * @{
  */
#define PMP_REGION_ENABLE ((uint8_t)0x01)
#define PMP_REGION_DISABLE ((uint8_t)0x00)
/**
  * @}
  */
/** @defgroup RISCV_PMP_Region_Number RISC-V PMP Region Number
  * @{
  */
#define PMP_REGION_NUMBER0 ((uint8_t)0x00)
#define PMP_REGION_NUMBER1 ((uint8_t)0x01)
#define PMP_REGION_NUMBER2 ((uint8_t)0x02)
#define PMP_REGION_NUMBER3 ((uint8_t)0x03)
#define PMP_REGION_NUMBER4 ((uint8_t)0x04)
#define PMP_REGION_NUMBER5 ((uint8_t)0x05)
#define PMP_REGION_NUMBER6 ((uint8_t)0x06)
#define PMP_REGION_NUMBER7 ((uint8_t)0x07)
/**
  * @}
  */
  
/** @defgroup RISCV_PMP_Region_Size RISC-V PMP Region Size
  * @{
  */
#define PMP_REGION_SIZE_8B ((uint8_t)0x00)
#define PMP_REGION_SIZE_16B ((uint8_t)0x01)
#define PMP_REGION_SIZE_32B ((uint8_t)0x02)
#define PMP_REGION_SIZE_64B ((uint8_t)0x03)
#define PMP_REGION_SIZE_128B ((uint8_t)0x04)
#define PMP_REGION_SIZE_256B ((uint8_t)0x05)
#define PMP_REGION_SIZE_512B ((uint8_t)0x06)
#define PMP_REGION_SIZE_1KB ((uint8_t)0x07)
#define PMP_REGION_SIZE_2KB ((uint8_t)0x08)
#define PMP_REGION_SIZE_4KB ((uint8_t)0x09)
#define PMP_REGION_SIZE_8KB ((uint8_t)0x0A)
#define PMP_REGION_SIZE_16KB ((uint8_t)0x0B)
#define PMP_REGION_SIZE_32KB ((uint8_t)0x0C)
#define PMP_REGION_SIZE_64KB ((uint8_t)0x0D)
#define PMP_REGION_SIZE_128KB ((uint8_t)0x0E)
#define PMP_REGION_SIZE_256KB ((uint8_t)0x0F)
#define PMP_REGION_SIZE_512KB ((uint8_t)0x10)
#define PMP_REGION_SIZE_1MB ((uint8_t)0x11)
#define PMP_REGION_SIZE_2MB ((uint8_t)0x12)
#define PMP_REGION_SIZE_4MB ((uint8_t)0x13)
#define PMP_REGION_SIZE_8MB ((uint8_t)0x14)
#define PMP_REGION_SIZE_16MB ((uint8_t)0x15)
#define PMP_REGION_SIZE_32MB ((uint8_t)0x16)
#define PMP_REGION_SIZE_64MB ((uint8_t)0x17)
#define PMP_REGION_SIZE_128MB ((uint8_t)0x18)
#define PMP_REGION_SIZE_256MB ((uint8_t)0x19)
#define PMP_REGION_SIZE_512MB ((uint8_t)0x1A)
#define PMP_REGION_SIZE_1GB ((uint8_t)0x1B)
#define PMP_REGION_SIZE_2GB ((uint8_t)0x1C)
#define PMP_REGION_SIZE_4GB ((uint8_t)0x1D)
/**
  * @}
  */
/** @defgroup RISCV_PMP_Region_Lock RISC-V PMP Region Lock configure
  * @{
  */
#define PMP_REGION_LOCK ((uint8_t)0x01)
#define PMP_REGION_UNLOCK ((uint8_t)0x00)
/**
  * @}
  */
/** @defgroup RISCV_PMP_Region_Access RISC-V PMP Region Access Permission
  * @{
  */
#define PMP_ACCESS_NONE ((uint8_t)0)
#define PMP_ACCESS_R ((uint8_t)(1 << 0))
#define PMP_ACCESS_W ((uint8_t)(1 << 1))
#define PMP_ACCESS_X ((uint8_t)(1 << 2))
#define PMP_ACCESS_RW (PMP_ACCESS_R | PMP_ACCESS_W)
#define PMP_ACCESS_RX (PMP_ACCESS_R | PMP_ACCESS_X)
#define PMP_ACCESS_RWX (PMP_ACCESS_RW | PMP_ACCESS_X)
#define PMP_ACCESS_WX (PMP_ACCESS_W | PMP_ACCESS_X)
/**
  * @}
  */
/** @defgroup RISCV_PMP_Region_Address_Matching RISC-V PMP Region Address Matching Mode
  * @{
  */
#define PMP_ADDRESS_MATCHING_NONE ((uint8_t)0)
#define PMP_ADDRESS_MATCHING_TOR ((uint8_t)1)
#define PMP_ADDRESS_MATCHING_NA4 ((uint8_t)2)
#define PMP_ADDRESS_MATCHING_NAPOT ((uint8_t)3)
/**
  * @}
  */

/**
  * @}
  */
/** @defgroup MISC_Private_Macros MISC Private Macros
 * @{
 */
#define IS_PMP_REGION_ENABLE(STATE) (((STATE) == PMP_REGION_ENABLE) || \
                                     ((STATE) == PMP_REGION_DISABLE))

#define IS_PMP_REGION_PERMISSION_ATTRIBUTE(TYPE) (((TYPE) == PMP_ACCESS_NONE) || \
                                                  ((TYPE) == PMP_ACCESS_R) ||    \
                                                  ((TYPE) == PMP_ACCESS_W) ||    \
                                                  ((TYPE) == PMP_ACCESS_X) ||    \
                                                  ((TYPE) == PMP_ACCESS_RW) ||   \
                                                  ((TYPE) == PMP_ACCESS_RWX) ||  \
                                                  ((TYPE) == PMP_ACCESS_WX) ||   \
                                                  ((TYPE) == PMP_ACCESS_RX))

#define IS_PMP_REGION_NUMBER(NUMBER) (((NUMBER) == PMP_REGION_NUMBER0) || \
                                      ((NUMBER) == PMP_REGION_NUMBER1) || \
                                      ((NUMBER) == PMP_REGION_NUMBER2) || \
                                      ((NUMBER) == PMP_REGION_NUMBER3) || \
                                      ((NUMBER) == PMP_REGION_NUMBER4) || \
                                      ((NUMBER) == PMP_REGION_NUMBER5) || \
                                      ((NUMBER) == PMP_REGION_NUMBER6) || \
                                      ((NUMBER) == PMP_REGION_NUMBER7))

#define IS_PMP_ADDRESS_MATCHING(MODE) (((MODE) == PMP_ADDRESS_MATCHING_NONE) || \
                                       ((MODE) == PMP_ADDRESS_MATCHING_TOR) ||  \
                                       ((MODE) == PMP_ADDRESS_MATCHING_NA4) ||  \
                                       ((MODE) == PMP_ADDRESS_MATCHING_NAPOT))

#define IS_PMP_REGION_SIZE(SIZE) (((SIZE) == PMP_REGION_SIZE_8B) ||   \
                                  ((SIZE) == PMP_REGION_SIZE_16B) ||   \
                                  ((SIZE) == PMP_REGION_SIZE_32B) ||   \
                                  ((SIZE) == PMP_REGION_SIZE_64B) ||   \
                                  ((SIZE) == PMP_REGION_SIZE_128B) ||  \
                                  ((SIZE) == PMP_REGION_SIZE_256B) ||  \
                                  ((SIZE) == PMP_REGION_SIZE_512B) ||  \
                                  ((SIZE) == PMP_REGION_SIZE_1KB) ||   \
                                  ((SIZE) == PMP_REGION_SIZE_2KB) ||   \
                                  ((SIZE) == PMP_REGION_SIZE_4KB) ||   \
                                  ((SIZE) == PMP_REGION_SIZE_8KB) ||   \
                                  ((SIZE) == PMP_REGION_SIZE_16KB) ||  \
                                  ((SIZE) == PMP_REGION_SIZE_32KB) ||  \
                                  ((SIZE) == PMP_REGION_SIZE_64KB) ||  \
                                  ((SIZE) == PMP_REGION_SIZE_128KB) || \
                                  ((SIZE) == PMP_REGION_SIZE_256KB) || \
                                  ((SIZE) == PMP_REGION_SIZE_512KB) || \
                                  ((SIZE) == PMP_REGION_SIZE_1MB) ||   \
                                  ((SIZE) == PMP_REGION_SIZE_2MB) ||   \
                                  ((SIZE) == PMP_REGION_SIZE_4MB) ||   \
                                  ((SIZE) == PMP_REGION_SIZE_8MB) ||   \
                                  ((SIZE) == PMP_REGION_SIZE_16MB) ||  \
                                  ((SIZE) == PMP_REGION_SIZE_32MB) ||  \
                                  ((SIZE) == PMP_REGION_SIZE_64MB) ||  \
                                  ((SIZE) == PMP_REGION_SIZE_128MB) || \
                                  ((SIZE) == PMP_REGION_SIZE_256MB) || \
                                  ((SIZE) == PMP_REGION_SIZE_512MB) || \
                                  ((SIZE) == PMP_REGION_SIZE_1GB) ||   \
                                  ((SIZE) == PMP_REGION_SIZE_2GB) ||   \
                                  ((SIZE) == PMP_REGION_SIZE_4GB))
/**
  * @}
  */
/** @defgroup MISC_Exported_Types MISC Exported Types
 * @{
 */
typedef struct
{
  uint8_t Enable;           /*!< Specifies the status of the region.
                                                     This parameter can be a value of @ref RISCV_PMP_Region_Enable                 */
  uint8_t Number;           /*!< Specifies the number of the region to protect.
                                                     This parameter can be a value of @ref RISCV_PMP_Region_Number                 */
  uint8_t AddressMatching;  /*!< Specifies address matching of the region to protect.
                                                     This parameter can be a value of @ref RISCV_PMP_Region_Address_Matching     */
  uint32_t BaseAddress;     /*!< Specifies the base address of the region to protect.                           */
  uint8_t Size;             /*!< Specifies the size of the region to protect.
                                                     This parameter can be a value of @ref RISCV_PMP_Region_Size           */
  uint8_t AccessPermission; /*!< Specifies the region access permission type.
                                                     This parameter can be a value of @ref RISCV_PMP_Region_Access */

  uint8_t Lock; /*!< Specifies the region lock type.
                                                     This parameter can be a value of @ref RISCV_PMP_Region_Lock */

} PMP_Region_InitTypeDef;

/**
  * @}
  */
/** @defgroup MISC_Exported_Functions MISC Exported Functions
 * @{
 */
void PMP_ConfigRegion(PMP_Region_InitTypeDef *PMP_Init);

void PMP_ClearRegion(uint8_t id);
/**
  * @}
  */
#endif

/** @addtogroup MISC_Private_Macros
 * @{
 */
#if (__sPMP_PRESENT == 1)



#define SPMP_ACCESS_BITS_OFFSET 0
#define SPMP_MATCHING_BITS_OFFSET 3
#define SPMP_USER_BITS_OFFSET 6
#define SPMP_LOCK_BITS_OFFSET 7

/** @defgroup RISCV_sPMP_Region_Enable RISC-V SPMP Region Enable
  * @{
  */
#define SPMP_REGION_ENABLE ((uint8_t)0x01)
#define SPMP_REGION_DISABLE ((uint8_t)0x00)
/**
  * @}
  */
/** @defgroup RISCV_sPMP_Region_Number RISC-V SPMP Region Number
  * @{
  */
#define SPMP_REGION_NUMBER0 ((uint8_t)0x00)
#define SPMP_REGION_NUMBER1 ((uint8_t)0x01)
#define SPMP_REGION_NUMBER2 ((uint8_t)0x02)
#define SPMP_REGION_NUMBER3 ((uint8_t)0x03)
#define SPMP_REGION_NUMBER4 ((uint8_t)0x04)
#define SPMP_REGION_NUMBER5 ((uint8_t)0x05)
#define SPMP_REGION_NUMBER6 ((uint8_t)0x06)
#define SPMP_REGION_NUMBER7 ((uint8_t)0x07)
/**
  * @}
  */
/** @defgroup RISCV_sPMP_Region_Size RISC-V SPMP Region Size
  * @{
  */  
#define SPMP_REGION_SIZE_8B ((uint8_t)0x00)
#define SPMP_REGION_SIZE_16B ((uint8_t)0x01)
#define SPMP_REGION_SIZE_32B ((uint8_t)0x02)
#define SPMP_REGION_SIZE_64B ((uint8_t)0x03)
#define SPMP_REGION_SIZE_128B ((uint8_t)0x04)
#define SPMP_REGION_SIZE_256B ((uint8_t)0x05)
#define SPMP_REGION_SIZE_512B ((uint8_t)0x06)
#define SPMP_REGION_SIZE_1KB ((uint8_t)0x07)
#define SPMP_REGION_SIZE_2KB ((uint8_t)0x08)
#define SPMP_REGION_SIZE_4KB ((uint8_t)0x09)
#define SPMP_REGION_SIZE_8KB ((uint8_t)0x0A)
#define SPMP_REGION_SIZE_16KB ((uint8_t)0x0B)
#define SPMP_REGION_SIZE_32KB ((uint8_t)0x0C)
#define SPMP_REGION_SIZE_64KB ((uint8_t)0x0D)
#define SPMP_REGION_SIZE_128KB ((uint8_t)0x0E)
#define SPMP_REGION_SIZE_256KB ((uint8_t)0x0F)
#define SPMP_REGION_SIZE_512KB ((uint8_t)0x10)
#define SPMP_REGION_SIZE_1MB ((uint8_t)0x11)
#define SPMP_REGION_SIZE_2MB ((uint8_t)0x12)
#define SPMP_REGION_SIZE_4MB ((uint8_t)0x13)
#define SPMP_REGION_SIZE_8MB ((uint8_t)0x14)
#define SPMP_REGION_SIZE_16MB ((uint8_t)0x15)
#define SPMP_REGION_SIZE_32MB ((uint8_t)0x16)
#define SPMP_REGION_SIZE_64MB ((uint8_t)0x17)
#define SPMP_REGION_SIZE_128MB ((uint8_t)0x18)
#define SPMP_REGION_SIZE_256MB ((uint8_t)0x19)
#define SPMP_REGION_SIZE_512MB ((uint8_t)0x1A)
#define SPMP_REGION_SIZE_1GB ((uint8_t)0x1B)
#define SPMP_REGION_SIZE_2GB ((uint8_t)0x1C)
#define SPMP_REGION_SIZE_4GB ((uint8_t)0x1D)
/**
  * @}
  */
/** @defgroup RISCV_sPMP_Region_Lock RISC-V sPMP Region Lock configure
  * @{
  */
#define SPMP_REGION_LOCK ((uint8_t)0x01)
#define SPMP_REGION_UNLOCK ((uint8_t)0x00)
/**
  * @}
  */
/** @defgroup RISCV_sPMP_Region_Access RISC-V sPMP Region Access Permission
  * @{
  */
#define SPMP_ACCESS_NONE ((uint8_t)0)
#define SPMP_ACCESS_R ((uint8_t)(1 << 0))
#define SPMP_ACCESS_W ((uint8_t)(1 << 1))
#define SPMP_ACCESS_X ((uint8_t)(1 << 2))
#define SPMP_ACCESS_RW (SPMP_ACCESS_R | SPMP_ACCESS_W)
#define SPMP_ACCESS_RX (SPMP_ACCESS_R | SPMP_ACCESS_X)
#define SPMP_ACCESS_RWX (SPMP_ACCESS_RW | SPMP_ACCESS_X)
#define SPMP_ACCESS_WX (SPMP_ACCESS_W | SPMP_ACCESS_X)
/**
  * @}
  */
/** @defgroup RISCV_sPMP_Region_Usermode RISC-V sPMP Region Whether used in user mode
  * @{
  */
#define SPMP_USERMODE_SET ((uint8_t)1)
#define SPMP_USERMODE_RESET ((uint8_t)0)
/**
  * @}
  */
/** @defgroup RISCV_sPMP_Region_Address_Matching RISC-V PMP Region Address Matching Mode
  * @{
  */
#define SPMP_ADDRESS_MATCHING_NONE ((uint8_t)0)
#define SPMP_ADDRESS_MATCHING_TOR ((uint8_t)1)
#define SPMP_ADDRESS_MATCHING_NA4 ((uint8_t)2)
#define SPMP_ADDRESS_MATCHING_NAPOT ((uint8_t)3)
/**
  * @}
  */
/**
  * @}
  */
/** @addtogroup MISC_Private_Macros
 * @{
 */
#define IS_SPMP_REGION_ENABLE(STATE) (((STATE) == SPMP_REGION_ENABLE) || \
                                     ((STATE) == SPMP_REGION_DISABLE))
                                    
#define IS_SPMP_REGION_USERMODE(STATE) (((STATE) == SPMP_USERMODE_SET) || \
                                     ((STATE) == SPMP_USERMODE_RESET))

#define IS_SPMP_REGION_PERMISSION_ATTRIBUTE(TYPE) (((TYPE) == SPMP_ACCESS_NONE) || \
                                                  ((TYPE) == SPMP_ACCESS_R) ||    \
                                                  ((TYPE) == SPMP_ACCESS_W) ||    \
                                                  ((TYPE) == SPMP_ACCESS_X) ||    \
                                                  ((TYPE) == SPMP_ACCESS_RW) ||   \
                                                  ((TYPE) == SPMP_ACCESS_RWX) ||  \
                                                  ((TYPE) == SPMP_ACCESS_WX) ||   \
                                                  ((TYPE) == SPMP_ACCESS_RX))

#define IS_SPMP_REGION_NUMBER(NUMBER) (((NUMBER) == SPMP_REGION_NUMBER0) || \
                                      ((NUMBER) == SPMP_REGION_NUMBER1) || \
                                      ((NUMBER) == SPMP_REGION_NUMBER2) || \
                                      ((NUMBER) == SPMP_REGION_NUMBER3) || \
                                      ((NUMBER) == SPMP_REGION_NUMBER4) || \
                                      ((NUMBER) == SPMP_REGION_NUMBER5) || \
                                      ((NUMBER) == SPMP_REGION_NUMBER6) || \
                                      ((NUMBER) == SPMP_REGION_NUMBER7))

#define IS_SPMP_ADDRESS_MATCHING(MODE) (((MODE) == SPMP_ADDRESS_MATCHING_NONE) || \
                                       ((MODE) == SPMP_ADDRESS_MATCHING_TOR) ||  \
                                       ((MODE) == SPMP_ADDRESS_MATCHING_NA4) ||  \
                                       ((MODE) == SPMP_ADDRESS_MATCHING_NAPOT))

#define IS_SPMP_REGION_SIZE(SIZE) (((SIZE) == SPMP_REGION_SIZE_8B) ||   \
                                  ((SIZE) == SPMP_REGION_SIZE_16B) ||   \
                                  ((SIZE) == SPMP_REGION_SIZE_32B) ||   \
                                  ((SIZE) == SPMP_REGION_SIZE_64B) ||   \
                                  ((SIZE) == SPMP_REGION_SIZE_128B) ||  \
                                  ((SIZE) == SPMP_REGION_SIZE_256B) ||  \
                                  ((SIZE) == SPMP_REGION_SIZE_512B) ||  \
                                  ((SIZE) == SPMP_REGION_SIZE_1KB) ||   \
                                  ((SIZE) == SPMP_REGION_SIZE_2KB) ||   \
                                  ((SIZE) == SPMP_REGION_SIZE_4KB) ||   \
                                  ((SIZE) == SPMP_REGION_SIZE_8KB) ||   \
                                  ((SIZE) == SPMP_REGION_SIZE_16KB) ||  \
                                  ((SIZE) == SPMP_REGION_SIZE_32KB) ||  \
                                  ((SIZE) == SPMP_REGION_SIZE_64KB) ||  \
                                  ((SIZE) == SPMP_REGION_SIZE_128KB) || \
                                  ((SIZE) == SPMP_REGION_SIZE_256KB) || \
                                  ((SIZE) == SPMP_REGION_SIZE_512KB) || \
                                  ((SIZE) == SPMP_REGION_SIZE_1MB) ||   \
                                  ((SIZE) == SPMP_REGION_SIZE_2MB) ||   \
                                  ((SIZE) == SPMP_REGION_SIZE_4MB) ||   \
                                  ((SIZE) == SPMP_REGION_SIZE_8MB) ||   \
                                  ((SIZE) == SPMP_REGION_SIZE_16MB) ||  \
                                  ((SIZE) == SPMP_REGION_SIZE_32MB) ||  \
                                  ((SIZE) == SPMP_REGION_SIZE_64MB) ||  \
                                  ((SIZE) == SPMP_REGION_SIZE_128MB) || \
                                  ((SIZE) == SPMP_REGION_SIZE_256MB) || \
                                  ((SIZE) == SPMP_REGION_SIZE_512MB) || \
                                  ((SIZE) == SPMP_REGION_SIZE_1GB) ||   \
                                  ((SIZE) == SPMP_REGION_SIZE_2GB) ||   \
                                  ((SIZE) == SPMP_REGION_SIZE_4GB))
/**
  * @}
  */

/** @defgroup MISC_Exported_Types MISC Exported Types
 * @{
 */
typedef struct
{
  uint8_t Enable;           /*!< Specifies the status of the region.
                                                     This parameter can be a value of @ref RISCV_sPMP_Region_Enable                 */
  uint8_t Number;           /*!< Specifies the number of the region to protect.
                                                     This parameter can be a value of @ref RISCV_sPMP_Region_Number                 */
  uint8_t AddressMatching;  /*!< Specifies address matching of the region to protect.
                                                     This parameter can be a value of @ref RISCV_sPMP_Region_Address_Matching     */
  uint32_t BaseAddress;     /*!< Specifies the base address of the region to protect.                           */
  uint8_t Size;             /*!< Specifies the size of the region to protect.
                                                     This parameter can be a value of @ref RISCV_sPMP_Region_Size                    */
  uint8_t AccessPermission; /*!< Specifies the region access permission type.
                                                     This parameter can be a value of @ref RISCV_sPMP_Region_Access */
  uint8_t UserMode;  /*!< Specifies the region Indicates the sPMP entry is for user mode. 
                                                     This parameter can be a value of @ref RISCV_sPMP_Region_Usermode */
  uint8_t Lock; /*!< Specifies the region lock type.
                                                     This parameter can be a value of @ref RISCV_sPMP_Region_Lock */

} sPMP_Region_InitTypeDef;
/**
  * @}
  */

/** @addtogroup MISC_Exported_Functions
 * @{
 */
void sPMP_ConfigRegion(sPMP_Region_InitTypeDef *sPMP_Init);

void sPMP_ClearRegion(uint8_t id);
/**
  * @}
  */
#endif

/** @addtogroup MISC_Exported_Functions
 * @{
 */

void delay_us(uint32_t nus);
void delay_ms(uint32_t nms);

__WEAK void assert_failed(const uint8_t* expr, const uint8_t* file, uint32_t line);

void GetUCID (uint8_t *UCIDbuf);
void GetUID (uint8_t *UIDbuf);

/**
  * @}
  */

#ifdef __cplusplus
}
#endif


/**
  * @}
  */

/**
  * @}
  */

#endif /* __MISC_H__ */
