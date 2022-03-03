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
 * @file        os_hw.h
 *
 * @brief       Header file for cpu hw interface.
 *
 * @revision
 * Date         Author          Notes
 * 2020-02-25   OneOS Team      First version.
 * 2020-07-31   OneOS Team      Add os_hw_exception_install declaration.
 ***********************************************************************************************************************
 */
#ifndef __OS_HW_H__
#define __OS_HW_H__

#include <oneos_config.h>
#include <os_types.h>
#include <os_task.h>


#ifdef __cplusplus
extern "C" {
#endif

#ifndef OS_CPU_CACHE_LINE_SZ
#define OS_CPU_CACHE_LINE_SZ    32
#endif

enum OS_HW_CACHE_OPS
{
    OS_HW_CACHE_FLUSH      = 0x01,
    OS_HW_CACHE_INVALIDATE = 0x02,
};

/* CPU interfaces */
extern void        os_hw_cpu_icache_enable(void);
extern void        os_hw_cpu_icache_disable(void);
extern os_base_t   os_hw_cpu_icache_status(void);
extern void        os_hw_cpu_icache_ops(os_int32_t ops, void* addr, os_int32_t size);

extern void        os_hw_cpu_dcache_enable(void);
extern void        os_hw_cpu_dcache_disable(void);
extern os_base_t   os_hw_cpu_dcache_status(void);
extern void        os_hw_cpu_dcache_ops(os_int32_t ops, void* addr, os_int32_t size);

extern void        os_hw_cpu_reset(void);
extern void        os_hw_cpu_shutdown(void);
extern os_uint8_t *os_hw_stack_init(void *task_entry, void *parameter, os_uint8_t *stack_addr, void *task_exit);

/* Interrupt interfaces. */
extern os_base_t   os_hw_interrupt_disable(void);
extern void        os_hw_interrupt_enable(os_base_t level);

/* Context interfaces. */
extern void        os_hw_context_switch(os_uint32_t from, os_uint32_t to);
extern void        os_hw_context_switch_to(os_uint32_t to);
extern void        os_hw_context_switch_interrupt(os_uint32_t from, os_uint32_t to);

extern os_int32_t  os_find_first_bit_set(os_int32_t value);

/* Exception interfaces */
extern void os_hw_exception_install(os_err_t (*exception_handle)(void *context));

/* Board interfaces. */
extern void        os_board_auto_init(void);
extern void        os_hw_board_init(void);
extern void        os_hw_console_output(const char *str);

/* Delay interfaces. */
extern void        os_hw_us_delay(os_uint32_t us);


#define OS_DEFINE_SPINLOCK(x)  
#define OS_DECLARE_SPINLOCK(x)    os_ubase_t x

#define os_hw_spin_lock(lock)     *(lock) = os_hw_interrupt_disable()
#define os_hw_spin_unlock(lock)   os_hw_interrupt_enable(*(lock))

#ifdef __cplusplus
}
#endif

#endif /* __OS_HW_H__ */

