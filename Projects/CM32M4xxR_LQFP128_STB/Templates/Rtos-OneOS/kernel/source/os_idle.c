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
 * @file        os_idle.c
 *
 * @brief       This file implements the idle task.
 *
 * @revision
 * Date         Author          Notes
 * 2020-02-19   OneOS Team      First Version
 ***********************************************************************************************************************
 */
 
#include <os_errno.h>
#include <os_idle.h>
#include <os_dbg.h>
#include <os_hw.h>
#include <os_irq.h>
#include "os_kernel_internal.h"

#ifdef OS_USING_MODULE
#include <os_module.h>
#endif

#define IDLE_TAG        "IDLE"

#if defined (OS_USING_HOOK)
#ifndef OS_USING_IDLE_HOOK
#define OS_USING_IDLE_HOOK
#endif
#endif

#ifndef OS_IDLE_TASK_STACK_SIZE
#if defined (OS_USING_IDLE_HOOK) || defined(OS_USING_HEAP)
#define OS_IDLE_TASK_STACK_SIZE  512
#else
#define OS_IDLE_TASK_STACK_SIZE  256
#endif
#endif

static os_task_t gs_idle_task;

OS_ALIGN(OS_ALIGN_SIZE)
static os_uint8_t gs_idle_task_stack[OS_IDLE_TASK_STACK_SIZE];

extern os_list_node_t g_os_task_defunct;

#if defined(OS_USING_CPU_USAGE) && defined(OS_USING_SHELL)
    extern void cpu_usage_calc(void);
#endif

#ifdef OS_USING_IDLE_HOOK

#ifndef OS_IDLE_HOOK_LIST_SIZE
#define OS_IDLE_HOOK_LIST_SIZE          4
#endif

static void (*idle_hook_list[OS_IDLE_HOOK_LIST_SIZE])(void);

/**
 ***********************************************************************************************************************
 * @brief           Add specified hook function into the idle task hook list, fail if the list is already full.
 *
 * @param[in]       hook       The hook function to be added.
 *
 * @return          Return OS_EOK on success, OS_EFULL if the hook list is already full.
 ***********************************************************************************************************************
 */
os_err_t os_idle_task_set_hook(void (*hook)(void))
{
    os_size_t i;
    os_base_t level;
    os_err_t ret;

    ret = OS_EFULL;

    level = os_hw_interrupt_disable();

    for (i = 0; i < OS_IDLE_HOOK_LIST_SIZE; i++)
    {
        if (OS_NULL == idle_hook_list[i])
        {
            idle_hook_list[i] = hook;

            ret = OS_EOK;

            break;
        }
    }

    os_hw_interrupt_enable(level);

    return ret;
}

/**
 ***********************************************************************************************************************
 * @brief           Remove specified hook function from the idle task hook list.
 *
 * @param[in]       hook       The hook function to be removed.
 *
 * @return          Return OS_EOK on success, OS_ENOSYS if failed.
 ***********************************************************************************************************************
 */
os_err_t os_idle_task_del_hook(void (*hook)(void))
{
    os_size_t i;
    os_base_t level;
    os_err_t ret;

    ret = OS_ENOSYS;

    level = os_hw_interrupt_disable();

    for (i = 0; i < OS_IDLE_HOOK_LIST_SIZE; i++)
    {
        if (hook == idle_hook_list[i])
        {
            idle_hook_list[i] = OS_NULL;

            ret = OS_EOK;

            break;
        }
    }

    os_hw_interrupt_enable(level);

    return ret;
}

#endif

OS_INLINE int has_defunct_task(void)
{
    /* The os_list_empty has prototype of "int os_list_empty(const cm_list_t *l)".
     * So the compiler has a good reason that the g_os_task_defunct list does
     * not change within os_idle_task_excute thus optimize the "while" loop
     * into a "if".
     *
     * So add the volatile qualifier here. */
    const volatile os_list_node_t *l = (const volatile os_list_node_t *)&g_os_task_defunct;

    return l->next != l;
}

/**
 ***********************************************************************************************************************
 * @brief           This function do the main work of idle task, which is cleanup dead task.
 *
 * @param           None
 *
 * @return          None
 ***********************************************************************************************************************
 */
void os_idle_task_excute(void)
{
    os_base_t lock;
    os_task_t *task;
#ifdef OS_USING_MODULE
    struct os_module *module = OS_NULL;
#endif

    /* Loop until there is no dead task. So one call to os_idle_task_excute will do all the cleanups. */
    while (has_defunct_task())
    {
        OS_DEBUG_NOT_IN_INTERRUPT;

        lock = os_hw_interrupt_disable();

        /* Re-check whether list is empty */
        if (has_defunct_task())
        {
            /* Get defunct task */
            task = os_list_entry(g_os_task_defunct.next, os_task_t, task_list);
#ifdef OS_USING_MODULE
            module = (struct os_module*)task->module_id;
            if (module)
            {
                os_module_destroy(module);
            }
#endif
            OS_KERN_LOG(KERN_DEBUG, IDLE_TAG, "remove task:%s ",task->parent.name);

            /* Remove defunct task */
            os_list_del(&task->task_list);

            /* Lock scheduler to prevent scheduling in cleanup function. */
            os_enter_critical();

            /* Invoke task cleanup */
            if (OS_NULL != task->cleanup)
            {
                task->cleanup(task);
            }

#ifdef OS_USING_SIGNALS
            os_task_free_sig(task);
#endif
            os_object_deinit((os_object_t *)task);

            /* If it's a system object, not delete it */
            if (OS_TRUE == os_object_is_static((os_object_t *)task))
            {
                os_exit_critical();

                os_hw_interrupt_enable(lock);

                continue;
            }

            os_exit_critical();
        }
        else
        {
            os_hw_interrupt_enable(lock);

            /* May the defunct task list is removed by others, just return */
            return;
        }

        os_hw_interrupt_enable(lock);

#ifdef OS_USING_HEAP
        /* Release task's stack */
        OS_KERNEL_FREE(task->stack_addr);

        /* Release task's object */
        OS_KERNEL_FREE(task);
#endif
    }
}

/**
 ***********************************************************************************************************************
 * @brief           This function executes the idle hook functions.
 *
 * @param           None
 *
 * @return          None
 ***********************************************************************************************************************
 */
#ifdef OS_USING_IDLE_HOOK
void os_idle_hook_excute(void)
{
    os_size_t i;
    void (*idle_hook)();
    register os_base_t level;
    
    for (i = 0; i < OS_IDLE_HOOK_LIST_SIZE; i++)
    {
        level = os_hw_interrupt_disable();
    
        if (OS_NULL != idle_hook_list[i])
        {
            idle_hook = idle_hook_list[i];
            os_hw_interrupt_enable(level);

            idle_hook(); 
        }
        else
        {
            os_hw_interrupt_enable(level);
        }
    }
}
#endif

/**
 ***********************************************************************************************************************
 * @brief           This function is the idle task entry function. 
 *
 * @param[in]       parameter    The parameter passed in when create the task.
 *
 * @return          None
 ***********************************************************************************************************************
 */
extern void os_low_power_manager(void);
static void os_idle_task_entry(void *parameter)
{
    while (1)
    {
        os_idle_task_excute();

#if defined(OS_USING_CPU_USAGE) && defined(OS_USING_SHELL)
        cpu_usage_calc();
#endif

#ifdef OS_USING_IDLE_HOOK
        os_idle_hook_excute();
#endif

#ifdef OS_USING_LPMGR
        os_low_power_manager();
#endif
    }
}

/**
 ***********************************************************************************************************************
 * @brief           This function return the idle task handler. 
 *
 * @param           None
 *
 * @return          Return idle task handler
 ***********************************************************************************************************************
 */
os_task_t *os_idle_task_get_handler(void)
{
    return &gs_idle_task;
}

/**
 ***********************************************************************************************************************
 * @brief           This function initialize and start the idle task. 
 *
 * @param           None
 *
 * @return          None
 ***********************************************************************************************************************
 */
void os_idle_task_init(void)
{
    os_err_t ret;
    
    /* Initialize task */
    ret = os_task_init(&gs_idle_task,
                       "tidle",
                       os_idle_task_entry,
                       OS_NULL,
                       &gs_idle_task_stack[0],
                       sizeof(gs_idle_task_stack),
                       OS_TASK_PRIORITY_MAX - 1,
                       32);

    OS_ASSERT(OS_EOK == ret);
    (void)ret;

    /* Startup */
    os_task_startup(&gs_idle_task);
}

