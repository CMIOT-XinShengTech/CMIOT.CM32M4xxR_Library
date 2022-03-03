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
 * @file        os_kernel_internal.h
 *
 * @brief       Provides some macro definitions and function declarations, only use for kernel.
 *
 * @revision
 * Date         Author          Notes
 * 2020-03-03   OneOS Team      First version.
 ***********************************************************************************************************************
 */
#ifndef __OS_KERNEL_INTERNAL_H__
#define __OS_KERNEL_INTERNAL_H__

#include <oneos_config.h>
#include <os_types.h>
#include <os_stddef.h>
#include <os_irq.h>
#include <os_assert.h>
#include <os_hw.h>
#include <os_util.h>
#include <os_memory.h>
#include <os_task.h>

#ifdef __cplusplus
extern "C" {
#endif

#define OS_KERNEL_VERSION               "Kernel-V1.1.0-20200812"

#ifndef OS_KERNEL_MALLOC
#define OS_KERNEL_MALLOC(sz)            os_malloc(sz)
#endif

#ifndef OS_KERNEL_FREE
#define OS_KERNEL_FREE(ptr)             os_free(ptr)
#endif

#ifndef OS_KERNEL_REALLOC
#define OS_KERNEL_REALLOC(ptr, size)    os_realloc(ptr, size)
#endif

#ifdef OS_DEBUG

/* Kernel log level */
#define KERN_ERROR                      0       /* Error conditions */
#define KERN_WARNING                    1       /* Warning conditions */
#define KERN_INFO                       2       /* Informational */
#define KERN_DEBUG                      3       /* Debug-level messages */

#ifndef KLOG_GLOBAL_LEVEL
#define KLOG_GLOBAL_LEVEL               KERN_WARNING
#endif

#define KLOG_FILTER_TAG_MAX_LEN         15

#ifdef OS_USING_KERNEL_DEBUG

#ifdef OS_DEBUG_LOG_WITH_FUNC_LINE


/**
 ***********************************************************************************************************************
 * @def         OS_KERN_LOG
 *
 * @brief       Print kernel log with function name and file line number.
 *
 * @param       level           The log level.
 * @param       tag             The log tag.
 * @param       fmt             The format.
 ***********************************************************************************************************************
 */
#define OS_KERN_LOG(level, tag, fmt, ...)                                                       \
do                                                                                              \
{                                                                                               \
    if ((level <= *g_klog_global_lvl) || (g_klog_tag_lvl_list->next != g_klog_tag_lvl_list))    \
    {                                                                                           \
        os_kernel_print(level, tag, OS_TRUE, fmt " [%s][%d]",                                   \
                        ##__VA_ARGS__, __FUNCTION__, __LINE__);                                 \
    }                                                                                           \
} while (0)

#else

/**
 ***********************************************************************************************************************
 * @def         OS_KERN_LOG
 *
 * @brief       Print kernel log without function name and file line number.
 *
 * @param       level           The log level.
 * @param       tag             The log tag.
 * @param       fmt             The format.
 ***********************************************************************************************************************
 */
#define OS_KERN_LOG(level, tag, fmt, ...)                                                       \
do                                                                                              \
{                                                                                               \
    if ((level <= *g_klog_global_lvl) || (g_klog_tag_lvl_list->next != g_klog_tag_lvl_list))    \
    {                                                                                           \
        os_kernel_print(level, tag, OS_TRUE, fmt, ##__VA_ARGS__);                               \
    }                                                                                           \
} while (0)

#endif /* OS_DEBUG_LOG_WITH_FUNC_LINE */

/* Macro to check current context */
#ifdef OS_USING_CONTEXT_CHECK
#define OS_DEBUG_NOT_IN_INTERRUPT                                               \
do                                                                              \
{                                                                               \
    os_base_t level;                                                            \
    level = os_hw_interrupt_disable();                                          \
    if (os_interrupt_get_nest() != 0)                                           \
    {                                                                           \
        os_kprintf("Function[%s] shall not be used in ISR\n", __FUNCTION__);    \
        OS_ASSERT(0);                                                           \
    }                                                                           \
    os_hw_interrupt_enable(level);                                              \
} while (0)

/* 
 * "In task context" means:
 *     1) The scheduler has been started
 *     2) Not in interrupt context.
 */
#define OS_DEBUG_IN_TASK_CONTEXT                                                \
do                                                                              \
{                                                                               \
    os_base_t level;                                                            \
    level = os_hw_interrupt_disable();                                          \
    if (OS_NULL == os_task_self())                                              \
    {                                                                           \
        os_kprintf("Function[%s] shall not be used before scheduler start\n",   \
                   __FUNCTION__);                                               \
        OS_ASSERT(0);                                                           \
    }                                                                           \
    OS_DEBUG_NOT_IN_INTERRUPT;                                                  \
    os_hw_interrupt_enable(level);                                              \
} while (0)
#else
#define OS_DEBUG_NOT_IN_INTERRUPT
#define OS_DEBUG_IN_TASK_CONTEXT
#endif /* OS_USING_CONTEXT_CHECK */

extern const os_int16_t     *g_klog_global_lvl;
extern const os_list_node_t *g_klog_tag_lvl_list;

#else
#define OS_KERN_LOG(level, tag, fmt, ...)
#define OS_DEBUG_NOT_IN_INTERRUPT
#define OS_DEBUG_IN_TASK_CONTEXT

#endif /* OS_USING_KERNEL_DEBUG */

extern void os_kernel_print(os_uint16_t level, const char *tag, os_bool_t newline, const char *fmt, ...);
#else
#define OS_KERN_LOG(level, tag, fmt, ...)

#define OS_DEBUG_NOT_IN_INTERRUPT
#define OS_DEBUG_IN_TASK_CONTEXT
#endif /* OS_DEBUG */

/* Timer */
extern void     os_timer_check(void);

/* Task and schedule */
extern os_err_t os_task_suspend(os_task_t *task);
extern os_err_t os_task_resume(os_task_t *task);
extern void     os_schedule(void);
extern void     os_system_scheduler_init(void);
extern void     os_system_scheduler_start(void);

/* Idle task */
extern void     os_idle_task_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __OS_KERNEL_INTERNAL_H__ */

