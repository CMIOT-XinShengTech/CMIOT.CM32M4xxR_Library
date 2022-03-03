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
 * @file        os_stddef.h
 *
 * @brief       OneOS standard macro definitions.
 *
 * @revision
 * Date         Author          Notes
 * 2020-02-13   OneOS Team      First version
 ***********************************************************************************************************************
 */

#ifndef __OS_STDDEF_H__
#define __OS_STDDEF_H__

#include <os_types.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
#define __CLANG_ARM
#endif

/* Compiler related definitions */
#if defined(__CC_ARM) || defined(__CLANG_ARM)   /* For ARM compiler */
    #include <stdarg.h>
    
    #define OS_SECTION(x)               __attribute__((section(x)))
    #define OS_ALIGN(n)                 __attribute__((aligned(n)))
    #define OS_UNUSED                   __attribute__((unused))
    #define OS_USED                     __attribute__((used))
    #define OS_WEAK                     __attribute__((weak))
    #define OS_INLINE                   static __inline
#elif defined (__IAR_SYSTEMS_ICC__)             /* For IAR compiler */
    #include <stdarg.h>
    
    #define OS_SECTION(x)               @ x
    #define OS_PRAGMA(x)                _Pragma(#x)
    #define OS_ALIGN(n)                 OS_PRAGMA(data_alignment=n)
    #define OS_UNUSED
    #define OS_USED                     __root
    #define OS_WEAK                     __weak
    #define OS_INLINE                   static inline
#elif defined (__GNUC__)                        /* For GNU GCC compiler */
    #ifdef OS_USING_NEWLIB
        #include <stdarg.h>
    #else
        /* The version of GNU GCC must be greater than 4.x */
        typedef __builtin_va_list       __gnuc_va_list;
        typedef __gnuc_va_list          va_list;
        #define va_start(v,l)           __builtin_va_start(v,l)
        #define va_end(v)               __builtin_va_end(v)
        #define va_arg(v,l)             __builtin_va_arg(v,l)
    #endif

    #define OS_SECTION(x)               __attribute__((section(x)))
    #define OS_ALIGN(n)                 __attribute__((aligned(n)))
    #define OS_UNUSED                   __attribute__((unused))
    #define OS_USED                     __attribute__((used))
    
    #define OS_WEAK                     __attribute__((weak))
    #define OS_INLINE                   static __inline
#elif defined (__ADSPBLACKFIN__)                /* For VisualDSP++ compiler */
    #include <stdarg.h>
    
    #define OS_SECTION(x)               __attribute__((section(x)))
    #define OS_ALIGN(n)                 __attribute__((aligned(n)))
    
    #define OS_UNUSED                   __attribute__((unused))
    #define OS_USED                     __attribute__((used))
    
    #define OS_WEAK                     __attribute__((weak))
    #define OS_INLINE                   static inline
#elif defined (_MSC_VER)                        /* For Microsoft C compiler */
    #include <stdarg.h>
    
    #define OS_SECTION(x)
    #define OS_ALIGN(n)                 __declspec(align(n))
    #define OS_UNUSED
    #define OS_USED
    
    #define OS_WEAK
    #define OS_INLINE                   static __inline
#elif defined (__TI_COMPILER_VERSION__)         /* For TI compiler */
    #include <stdarg.h>

    /* 
     * The way that TI compiler set section is different from other(at least
     * GCC and MDK) compilers. See ARM Optimizing C/C++ Compiler 5.9.3 for more
     * details. 
     */
    #define OS_SECTION(x)
    #define OS_PRAGMA(x)                _Pragma(#x)
    #define OS_ALIGN(n)
    #define OS_UNUSED
    #define OS_USED
    #define OS_WEAK
    #define OS_INLINE                   static inline
#else
    #error Not supported tool chain
#endif


/* Auto initialization function type */
typedef os_err_t (*os_init_fn_t)(void);

#define OS_INIT_EXPORT(fn, level)                                                           \
    OS_USED const os_init_fn_t __os_call_##fn OS_SECTION(".init_call."level) = fn

/* Board init routines will be called in os_hw_board_init() function */
#define OS_BOARD_INIT(fn)       OS_INIT_EXPORT(fn, "1")

/* pre/device/component/env/app init routines will be called before main() function */
#define OS_PREV_INIT(fn)        OS_INIT_EXPORT(fn, "2")     /* Pre-initialization except board(pure software
                                                               initilization) */
#define OS_DEVICE_INIT(fn)      OS_INIT_EXPORT(fn, "3")     /* Device initialization */
#define OS_CMPOENT_INIT(fn)     OS_INIT_EXPORT(fn, "4")     /* Components initialization (dfs, lwip, ...) */
#define OS_ENV_INIT(fn)         OS_INIT_EXPORT(fn, "5")     /* Environment initialization (mount disk, ...) */
#define OS_APP_INIT(fn)         OS_INIT_EXPORT(fn, "6")     /* Appliation initialization */


/* Similar as the NULL in C library */
#ifdef __cplusplus
#define OS_NULL                         0
#else
#define OS_NULL                         ((void *)0)
#endif

/* Boolean value definitions */
#define OS_FALSE                        0
#define OS_TRUE                         1


/* Return the most contiguous size aligned at specified width. OS_ALIGN_UP(13, 4) would return 16. */
#define OS_ALIGN_UP(size, align)        (((size) + (align) - 1) & ~((align) - 1))

/* Return the down number of aligned at specified width. OS_ALIGN_DOWN(13, 4) would return 12. */
#define OS_ALIGN_DOWN(size, align)      ((size) & ~((align) - 1))

/* Calculate array size */
#define OS_ARRAY_SIZE(x)                (sizeof(x) / sizeof(x[0]))

/**
 ***********************************************************************************************************************
 * @def         os_container_of
 *
 * @brief       Cast a member of a structure out to the containing structure.
 *
 * @param       ptr             The pointer to the member.
 * @param       type            The type of the container struct this is embedded in.
 * @param       member          The name of the member within the struct. 
 ***********************************************************************************************************************
 */
#define os_container_of(ptr, type, member)      \
    ((type *)((char *)(ptr) - (unsigned long)(&((type *)0)->member)))

/**
 ***********************************************************************************************************************
 * @def         os_offsetof
 *
 * @brief       This macro will return a byte offset of a member to the beginning of the struct.
 *
 * @param       type            The type of the struct
 * @param       member          The name of the member within the struct.
 ***********************************************************************************************************************
 */
#define os_offsetof(type, member)       ((os_size_t) &((type *)0)->member)

#ifdef __cplusplus
}
#endif

#endif /* __OS_STDDEF_H__ */

