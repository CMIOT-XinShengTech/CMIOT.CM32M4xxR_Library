/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-10-03     Bernard      The first version
 */

#ifndef RISCV_OPS_H__
#define RISCV_OPS_H__

#if defined(__GNUC__) && !defined(__ASSEMBLER__)

#define read_csr(reg) ({ unsigned long __tmp;                               \
    asm volatile ("csrr %0, " "%1" : "=r"(__tmp):"i"(reg));                          \
        __tmp; })

#define write_csr(reg, val) ({                                              \
    if (__builtin_constant_p(val) && (unsigned long)(val) < 32)             \
        asm volatile ("csrw " "%0"", %1"  ::"i"(reg), "i"(val));                     \
    else                                                                    \
        asm volatile ("csrw " "%0" ", %1" ::"i"(reg), "r"(val)); })

#define set_csr(reg, bit) ({ unsigned long __tmp;                           \
    if (__builtin_constant_p(bit) && (unsigned long)(bit) < 32)             \
        asm volatile ("csrrs %0, " "%1" ", %2" : "=r"(__tmp):"i"(reg) , "i"(bit));   \
    else                                                                    \
        asm volatile ("csrrs %0, " "%1" ", %2" : "=r"(__tmp):"i"(reg) , "r"(bit));   \
            __tmp; })

#define clear_csr(reg, bit) ({ unsigned long __tmp;                         \
    if (__builtin_constant_p(bit) && (unsigned long)(bit) < 32)             \
        asm volatile ("csrrc %0, " "%1" ", %2" : "=r"(__tmp):"i"(reg) , "i"(bit));   \
    else                                                                    \
        asm volatile ("csrrc %0, " "%1" ", %2" : "=r"(__tmp):"i"(reg) , "r"(bit));   \
            __tmp; })
#endif /* end of __GNUC__ */

#endif
