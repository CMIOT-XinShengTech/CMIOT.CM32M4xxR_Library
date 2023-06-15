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
 * @file main.h
 * @author CMIOT
 * @version v1.0.0
 *
 * @COPYRIGHT(c) 2020, China Mobile IOT. All rights reserved.
 */
#ifndef __MAIN_H__
#define __MAIN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "nuclei_sdk_soc.h"

typedef enum
{
    FAILED = 0,
    PASSED = !FAILED
} Status;

typedef enum
{
    NONE = 0,
    TRANSMIT,
    RECEIVE
} TR_STA;

typedef enum
{
    C_READY = 0,
    C_START_BIT,
    C_STOP_BIT
}CommCtrl_t;

typedef enum
{
    MASTER_OK = 0,
    MASTER_BUSY,
    MASTER_MODE,
    MASTER_TXMODE,
    MASTER_RXMODE,
    MASTER_SENDING,
    MASTER_SENDED,
    MASTER_RECVD,
    MASTER_BYTEF,
    MASTER_BUSERR,
    MASTER_UNKNOW,
    SLAVE_OK = 20,
    SLAVE_BUSY,
    SLAVE_MODE,
    SLAVE_BUSERR,
    SLAVE_UNKNOW,

}ErrCode_t;

#define MODULE_SELF_RESET       1
#define MODULE_RCC_RESET        2
#define SYSTEM_NVIC_RESET       3
#define COMM_RECOVER_MODE       0

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
