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

/******************************************************************************
 * @file     cm32m4xxr_def.h
 * @brief    CM32M4xxR generic types definition header file
 * @version  V1.00
 * @date     28. Jun 2020
 ******************************************************************************/
 
#ifndef __CM32M4xxR_DEF_H__
#define __CM32M4xxR_DEF_H__

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup Exported_types
  * @{
  */ 

typedef			int32_t		s32;
typedef			int16_t		s16;
typedef			int8_t		s8;

typedef const	int32_t		sc32;	/*!< Read Only */
typedef const	int16_t		sc16;	/*!< Read Only */
typedef const	int8_t		sc8;	/*!< Read Only */

typedef __IO	int32_t		vs32;
typedef __IO	int16_t		vs16;
typedef __IO	int8_t		vs8;

typedef __I		int32_t		vsc32;	/*!< Read Only */
typedef __I		int16_t		vsc16;	/*!< Read Only */
typedef __I		int8_t		vsc8;	/*!< Read Only */

typedef			uint32_t	u32;
typedef			uint16_t	u16;
typedef			uint8_t		u8;

typedef const	uint32_t	uc32;	/*!< Read Only */
typedef const	uint16_t	uc16;	/*!< Read Only */
typedef const	uint8_t		uc8;	/*!< Read Only */

typedef __IO	uint32_t	vu32;
typedef __IO	uint16_t	vu16;
typedef __IO	uint8_t		vu8;

typedef __I		uint32_t	vuc32;	/*!< Read Only */
typedef __I		uint16_t	vuc16;	/*!< Read Only */
typedef __I		uint8_t		vuc8;	/*!< Read Only */

typedef enum
{
	RESET = 0,
	SET   = !RESET
} FlagStatus, INTStatus;

typedef enum
{
    DISABLE = 0,
    ENABLE  = !DISABLE	/* !0 is '1' */
} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum
{
	ERROR   = 0,
	SUCCESS = !ERROR
} ErrorStatus;
  
/**
  * @}
  */


/** @addtogroup Exported_macro
  * @{
  */
#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

#define POSITION_VAL(VAL)     (__CLZ(__RBIT(VAL))) 

/**
  * @}
  */


#ifdef __cplusplus
}
#endif
#endif	/* __CM32M4xxR_DEF_H__ */
