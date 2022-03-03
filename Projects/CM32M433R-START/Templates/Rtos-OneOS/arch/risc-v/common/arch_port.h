/**
 ***********************************************************************************************************************
 * Copyright (c) 2020, China Mobile Communications Group Co.,Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with 
 * the License. You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on 
 * an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the 
 * specific language governing permissions and limitations under the License.
 *
 * @file        arch_port.h
 *
 * @brief       This file provides functions related to the RISC-V architecture.
 *
 * @revision
 * Date         Author          Notes
 * 2020-09-25   OneOS Team      First version.
 ***********************************************************************************************************************
 */
#ifndef ARCH_PORT_H
#define ARCH_PORT_H
#ifdef __cplusplus
    extern "C" {
#endif
//#include "riscv_encoding.h"
#include "riscv-ops.h"
#include "oneos_config.h"
#include "os_stddef.h"
#include "cpuport.h"

/**
 ***********************************************************************************************************************
 * @def         read_clear_csr
 *
 * @brief       Read and clear csr register.
 ***********************************************************************************************************************
 */
#define read_clear_csr(reg, val)                                                \
    ({                                                                          \
        unsigned long __tmp;                                                    \
        if (__builtin_constant_p(val) && (unsigned long)(val) < 32)             \
            asm volatile("csrrci %0, " "%1" ", %2" : "=r"(__tmp) :"i"(reg), "i"(val));   \
        else                                                                    \
            asm volatile("csrrci %0, " "%1" ", %2" : "=r"(__tmp) :"i"(reg), "r"(val));   \
        __tmp;                                                                  \
    })

/**
 ***********************************************************************************************************************
 * @def         _k_get_interrupt_mask
 *
 * @brief       This function returns the current state of the priority mask bit from the Priority Mask Register.
 ***********************************************************************************************************************
 */
#define _k_get_interrupt_mask()       read_csr(CSR_MSTATUS)

/**
 ***********************************************************************************************************************
 * @def         os_hw_context_state
 *
 * @brief       Get the current context state, Not 0: interrupt context  0: task context.
 ***********************************************************************************************************************
 */
#define os_hw_context_state()                  \
    ({                                         \
        unsigned long __tmp;                   \
        asm volatile("csrr %0, 0x7c4 \n"       \
                     "andi %0, %0, 0x000000c0" \
                      : "=r"(__tmp));          \
        __tmp;                                 \
    })

/**
 ***********************************************************************************************************************
 * @def         INT_DISABLE_SAVE
 *
 * @brief       Get interrupt enable status and disable interrupt
 ***********************************************************************************************************************
 */
#define INT_DISABLE_SAVE(old_state)                         \
do  {                                                       \
        old_state = read_clear_csr(CSR_MSTATUS, 0x00000008);    \
} while (0);

/**
 ***********************************************************************************************************************
 * @def         INT_RESTORE
 *
 * @brief       Restore interrupt enable state
 ***********************************************************************************************************************
 */
#define INT_RESTORE(old_state)         \
do  {                                  \
	    write_csr(CSR_MSTATUS, old_state); \
} while (0);

/**
 ***********************************************************************************************************************
 * @def         INT_DISABLE
 *
 * @brief       Disable interrupt
 ***********************************************************************************************************************
 */
#define INT_DISABLE(level)    clear_csr(CSR_MSTATUS, 0x00000008)

/**
 ***********************************************************************************************************************
 * @def         os_hw_irq_nesting
 *
 * @brief       Get the current irq nesting state, Not 0: nesting  0: not nesting.
 ***********************************************************************************************************************
 */
#define os_hw_irq_nesting()                   \
    ({                                         \
        unsigned long __tmp;                   \
        asm volatile("csrr %0, 0x7c4 \n"       \
                     "andi %0, %0, 0x00000300" \
                      : "=r"(__tmp));          \
        __tmp;                                 \
    })
    
#ifdef OS_USING_CPU_FFS
/**
 ***********************************************************************************************************************
 * @def         os_clz
 *
 * @brief       Get the number of 0s between the highest sign bit of the operand and the first 1
 * 
 * @param       mask:     Operand.
 * @param       val:      The number of 0s between the highest sign bit of the operand and the first 1.
 ***********************************************************************************************************************
 */
#error "not support OS_USING_CPU_FFS"
    
#else
    
#define os_clz(value)       (__builtin_clz(value))
    
#endif /* OS_USING_CPU_FFS */

#ifdef __cplusplus
    }
#endif
#endif /* ARCH_PORT_H */
