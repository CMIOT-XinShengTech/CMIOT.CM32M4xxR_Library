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
 * @file        os_timer.c
 *
 * @brief       This file implements the timer functions.
 *
 * @revision
 * Date         Author          Notes
 * 2020-02-12   OneOS Team      First Version
 ***********************************************************************************************************************
 */
#include <os_errno.h>
#include <os_task.h>
#include <os_timer.h>
#include <os_dbg.h>
#include <os_module.h>
#include <os_hw.h>
#include <os_irq.h>
#include <os_clock.h>
#include "os_kernel_internal.h"

#define TIMER_TAG           "TIMER"

/* Hard timer list. */
static os_list_node_t gs_os_timer_list[OS_TIMER_SKIP_LIST_LEVEL];

#ifdef OS_USING_TIMER_SOFT

/* Soft timer task default stack size. */
#ifndef OS_TIMER_TASK_STACK_SIZE
#define OS_TIMER_TASK_STACK_SIZE     512
#endif

/* Soft timer task default priority. */
#ifndef OS_TIMER_TASK_PRIO
#define OS_TIMER_TASK_PRIO           0
#endif

/* Soft timer list. */
static os_list_node_t   gs_os_soft_timer_list[OS_TIMER_SKIP_LIST_LEVEL];

/* Soft timer task handle. */
static os_task_t        gs_timer_task;

/* Soft timer task stack. */
OS_ALIGN(OS_ALIGN_SIZE)
static os_uint8_t       gs_timer_task_stack[OS_TIMER_TASK_STACK_SIZE];

#endif /* OS_USING_TIMER_SOFT */

#ifdef OS_USING_HOOK
static void (*gs_os_timer_start_hook)(os_timer_t *timer) = OS_NULL;
static void (*gs_os_timer_stop_hook)(os_timer_t *timer)  = OS_NULL;;
static void (*gs_os_timer_enter_hook)(os_timer_t *timer) = OS_NULL;;
static void (*gs_os_timer_exit_hook)(os_timer_t *timer)  = OS_NULL;;

/**
 ***********************************************************************************************************************
 * @brief           This function sets a hook function called at the beginning of os_timer_start.
 *
 * @param[in]       hook            The hook function is complemented by user.
 *
 * @return          None
 ***********************************************************************************************************************
 */
void os_timer_start_set_hook(void (*hook)(os_timer_t *timer))
{
    gs_os_timer_start_hook = hook;
}

/**
 ***********************************************************************************************************************
 * @brief           This function sets a hook function called at the beginning of os_timer_stop.
 *
 * @param[in]       hook            The hook function is complemented by user.
 *
 * @return          None
 ***********************************************************************************************************************
 */
void os_timer_stop_set_hook(void (*hook)(os_timer_t *timer))
{
    gs_os_timer_stop_hook = hook;
}

/**
 ***********************************************************************************************************************
 * @brief           This function sets a hook function called befor user's timeout func.
 *
 * @param[in]       hook            The hook function is complemented by user.
 *
 * @return          None
 ***********************************************************************************************************************
 */
void os_timer_enter_set_hook(void (*hook)(os_timer_t *timer))
{
    gs_os_timer_enter_hook = hook;
}

/**
 ***********************************************************************************************************************
 * @brief           This function sets a hook function called after user's timeout func.
 *
 * @param[in]       hook            The hook function is complemented by user.
 *
 * @return          None
 ***********************************************************************************************************************
 */
void os_timer_exit_set_hook(void (*hook)(os_timer_t *timer))
{
    gs_os_timer_exit_hook = hook;
}

#endif /* OS_USING_HOOK */

static void os_timer_do_init(os_timer_t    *timer,
                             void         (*timeout)(void *parameter),
                             void          *parameter,
                             os_tick_t      time,
                             os_uint8_t     flag)
{
    os_int32_t i;

    /* Set flag. */
    timer->parent.flag  = flag;

    /* Set deactivated. */
    timer->parent.flag &= ~OS_TIMER_FLAG_ACTIVATED;

    timer->timeout_func = timeout;
    timer->parameter    = parameter;

    timer->timeout_tick = 0;
    timer->init_tick    = time;

    /* Initialize timer list */
    for (i = 0; i < OS_TIMER_SKIP_LIST_LEVEL; i++)
    {
        os_list_init(&(timer->row[i]));
    }
}


static os_tick_t os_timer_list_next_timeout(os_list_node_t timer_list[])
{
    os_timer_t *timer;

    if (os_list_empty(&timer_list[OS_TIMER_SKIP_LIST_LEVEL - 1]))
    {
        return OS_TICK_MAX;
    }

    timer = os_list_entry(timer_list[OS_TIMER_SKIP_LIST_LEVEL - 1].next, os_timer_t, row[OS_TIMER_SKIP_LIST_LEVEL - 1]);

    return timer->timeout_tick;
}

OS_INLINE void os_timer_remove(os_timer_t *timer)
{
    os_int32_t i;

    for (i = 0; i < OS_TIMER_SKIP_LIST_LEVEL; i++)
    {
        os_list_del(&timer->row[i]);
    }
}

#if OS_DEBUG_TIMER
static os_int32_t os_timer_count_height(os_timer_t *timer)
{
    os_int32_t i, cnt = 0;

    for (i = 0; i < OS_TIMER_SKIP_LIST_LEVEL; i++)
    {
        if (!os_list_empty(&timer->row[i]))
        {
            cnt++;
        }
    }

    return cnt;
}

void os_timer_dump(os_list_node_t timer_heads[])
{
    os_list_node_t *list;
    os_timer_t     *timer;

    for (list = timer_heads[OS_TIMER_SKIP_LIST_LEVEL - 1].next; list != &timer_heads[OS_TIMER_SKIP_LIST_LEVEL - 1]; list = list->next)
    {
        timer = os_list_entry(list, os_timer_t, row[OS_TIMER_SKIP_LIST_LEVEL - 1]);
        os_kprintf("%d", os_timer_count_height(timer));
    }
    os_kprintf("\r\n");
}
#endif

/**
 ***********************************************************************************************************************
 * @brief           This function initialize a timer and places it on the list of timer object.
 *
 * @param[in]       timer           The descriptor of timer control block.
 * @param[in]       name            Pointer to timer name string.
 * @param[in]       timeout         Entry function of timeout.
 * @param[in]       parameter       Parameter of entry function.
 * @param[in]       time            Number of ticks that need to be delayed.
 * @param[in]       flag            Flag of timer.
 *
 * @return          None
 ***********************************************************************************************************************
 */
void os_timer_init(os_timer_t    *timer,
                   const char    *name, 
                   void         (*timeout)(void *parameter), 
                   void          *parameter, 
                   os_tick_t      time, 
                   os_uint8_t     flag)
{
    OS_ASSERT(time < (OS_TICK_MAX / 2));
    OS_ASSERT(OS_NULL != timer);

    os_object_init((os_object_t *)timer, OS_OBJECT_TIMER, name, OS_TRUE);

    os_timer_do_init(timer, timeout, parameter, time, flag);
}
EXPORT_SYMBOL(os_timer_init);

/**
 ***********************************************************************************************************************
 * @brief           This function will deinitializate the specified timer by timer descriptor.
 *
 * @attention       It corresponds to os_timer_init.
 *
 * @param[in]       timer            The descriptor of timer control block
 *
 * @return          Will only return OS_EOK
 ***********************************************************************************************************************
 */
void os_timer_deinit(os_timer_t *timer)
{
    register os_base_t level;

    OS_ASSERT(OS_NULL != timer);
    OS_ASSERT(OS_OBJECT_TIMER == os_object_get_type(&timer->parent));
    OS_ASSERT(OS_TRUE == os_object_is_static(&timer->parent));

    level = os_hw_interrupt_disable();

    os_timer_remove(timer);

    os_hw_interrupt_enable(level);

    os_object_deinit((os_object_t *)timer);
}
EXPORT_SYMBOL(os_timer_deinit);

#ifdef OS_USING_HEAP
/**
 ***********************************************************************************************************************
 * @brief           This function create a timer and places it on the list of timer object.
 *
 * @details         This function create a timer and places it on the list of timer object.The memory space of the 
 *                  timer control block descriptor is applied from the heap.
 *
 * @param[in]       name            Pointer to timer name string.
 * @param[in]       timeout         Entry function of timeout.
 * @param[in]       parameter       Parameter of entry function.
 * @param[in]       time            Number of ticks that need to be delayed.
 * @param[in]       flag            Flag of timer.
 * 
 * @return          On success, return a timer control block descriptor; on error, OS_NULL is returned.
 * @retval          not OS_NULL     Return a timer control block descriptor.
 * @retval          OS_NULL         Call os_timer_create failed.
 ***********************************************************************************************************************
 */
os_timer_t *os_timer_create(const char    *name, 
                            void         (*timeout)(void *parameter), 
                            void          *parameter, 
                            os_tick_t      time, 
                            os_uint8_t     flag)
{
    OS_ASSERT(time < (OS_TICK_MAX / 2));

    os_timer_t *timer;

    OS_DEBUG_NOT_IN_INTERRUPT;

    timer = (os_timer_t *)OS_KERNEL_MALLOC(sizeof(os_timer_t));
    if (OS_NULL == timer)
    {
        OS_KERN_LOG(KERN_ERROR, TIMER_TAG, "malloc timer tcb fail");
        return OS_NULL;
    }

    os_object_init((os_object_t *)timer, OS_OBJECT_TIMER, name, OS_FALSE);

    os_timer_do_init(timer, timeout, parameter, time, flag);

    return timer;
}
EXPORT_SYMBOL(os_timer_create);

/**
 ***********************************************************************************************************************
 * @brief           This function will destroy the specified timer by timer descriptor.
 *
 * @attention       It corresponds to os_timer_create.
 *
 * @param[in]       timer           The descriptor of timer control block
 *
 * @return          Will only return OS_EOK
 ***********************************************************************************************************************
 */
os_err_t os_timer_destroy(os_timer_t *timer)
{
    register os_base_t level;

    OS_ASSERT(OS_NULL != timer);
    OS_ASSERT(OS_OBJECT_TIMER == os_object_get_type(&timer->parent));
    OS_ASSERT(OS_FALSE == os_object_is_static(&timer->parent));

    OS_DEBUG_NOT_IN_INTERRUPT;

    level = os_hw_interrupt_disable();

    os_timer_remove(timer);

    os_hw_interrupt_enable(level);

    os_object_deinit((os_object_t *)timer);

    OS_KERNEL_FREE(timer);

    return OS_EOK;
}
EXPORT_SYMBOL(os_timer_destroy);
#endif

/**
 ***********************************************************************************************************************
 * @brief           This function will starup the specified timer by timer descriptor.
 *
 * @param[in]       timer           The descriptor of timer control block
 *
 * @return          Will only return OS_EOK
 ***********************************************************************************************************************
 */
os_err_t os_timer_start(os_timer_t *timer)
{
    os_uint32_t         row_lvl;
    os_uint32_t         tst_nr;
    os_list_node_t     *timer_list;
    os_list_node_t     *row_head[OS_TIMER_SKIP_LIST_LEVEL];
    static os_uint32_t  random_nr;
    register os_base_t  level;

    OS_ASSERT(OS_NULL != timer);
    OS_ASSERT(OS_OBJECT_TIMER == os_object_get_type(&timer->parent));

    /* Stop timer firstly. */
    level = os_hw_interrupt_disable();

    /* Remove timer from list. */
    os_timer_remove(timer);

    /* Change status of timer. */
    timer->parent.flag &= ~OS_TIMER_FLAG_ACTIVATED;

    os_hw_interrupt_enable(level);

    OS_OBJECT_HOOK_CALL(gs_os_timer_start_hook, (timer));

    /* Get timeout tick,the max timeout tick shall not great than OS_TICK_MAX/2 */
    OS_ASSERT(timer->init_tick < OS_TICK_MAX / 2);
    timer->timeout_tick = os_tick_get() + timer->init_tick;

    level = os_hw_interrupt_disable();

#ifdef OS_USING_TIMER_SOFT
    if (timer->parent.flag & OS_TIMER_FLAG_SOFT_TIMER)
    {
        /* Insert timer to soft timer list. */
        timer_list = gs_os_soft_timer_list;
    }
    else
#endif
    {
        /* Insert timer to system timer list. */
        timer_list = gs_os_timer_list;
    }

    row_head[0]  = &timer_list[0];
    for (row_lvl = 0; row_lvl < OS_TIMER_SKIP_LIST_LEVEL; row_lvl++)
    {
        for (; row_head[row_lvl] != timer_list[row_lvl].prev; row_head[row_lvl] = row_head[row_lvl]->next)
        {
            os_timer_t *t;
            os_list_node_t *p = row_head[row_lvl]->next;

            /* Fix up the entry pointer. */
            t = os_list_entry(p, os_timer_t, row[row_lvl]);

            /* If we have two timers that timeout at the same time, it's preferred that the timer inserted early get called early.
             * So insert the new timer to the end the the some-timeout timer list.
             */
            if ((t->timeout_tick - timer->timeout_tick) == 0)
            {
                continue;
            }
            else if ((t->timeout_tick - timer->timeout_tick) < OS_TICK_MAX / 2)
            {
                break;
            }
        }

        if (row_lvl != OS_TIMER_SKIP_LIST_LEVEL - 1)
        {
            row_head[row_lvl + 1] = row_head[row_lvl] + 1;
        }
    }

    /* Interestingly, this super simple timer insert counter works very very
     * well on distributing the list height uniformly. By means of "very very
     * well", I mean it beats the randomness of timer->timeout_tick very easily
     * (actually, the timeout_tick is not random and easy to be attacked). 
     */
    random_nr++;
    tst_nr = random_nr;

    os_list_add(row_head[OS_TIMER_SKIP_LIST_LEVEL - 1], &(timer->row[OS_TIMER_SKIP_LIST_LEVEL - 1]));
    for (row_lvl = 2; row_lvl <= OS_TIMER_SKIP_LIST_LEVEL; row_lvl++)
    {
        if (!(tst_nr & OS_TIMER_SKIP_LIST_MASK))
        {
            os_list_add(row_head[OS_TIMER_SKIP_LIST_LEVEL - row_lvl], &(timer->row[OS_TIMER_SKIP_LIST_LEVEL - row_lvl]));
        }
        else
        {
            break;
        }

        /* Shift over the bits, Works well with 1 bit and 2 bits. */
        tst_nr >>= (OS_TIMER_SKIP_LIST_MASK + 1) >> 1;
    }

    timer->parent.flag |= OS_TIMER_FLAG_ACTIVATED;

    os_hw_interrupt_enable(level);

#ifdef OS_USING_TIMER_SOFT
    if (timer->parent.flag & OS_TIMER_FLAG_SOFT_TIMER)
    {
        level = os_hw_interrupt_disable();
        
        /* Check whether timer task is ready. */
        if ((gs_timer_task.stat & OS_TASK_STAT_MASK) != OS_TASK_READY)
        {
            /* Resume timer task to check soft timer */
            (void)os_task_resume(&gs_timer_task);
            
            os_hw_interrupt_enable(level);
            
            os_schedule();
        }
        else
        {
            os_hw_interrupt_enable(level);
        }
    }
#endif

    return OS_EOK;
}
EXPORT_SYMBOL(os_timer_start);

/**
 ***********************************************************************************************************************
 * @brief           This function will stop the specified timer by timer descriptor.
 *
 * @param[in]       timer           The descriptor of timer control block
 *
 * @return          Will only return OS_EOK
 ***********************************************************************************************************************
 */
os_err_t os_timer_stop(os_timer_t *timer)
{
    register os_base_t level;

    OS_ASSERT(OS_NULL != timer);
    OS_ASSERT(OS_OBJECT_TIMER == os_object_get_type(&timer->parent));

    if (!(timer->parent.flag & OS_TIMER_FLAG_ACTIVATED))
    {
        return OS_ERROR;
    }

    OS_OBJECT_HOOK_CALL(gs_os_timer_stop_hook, (timer));

    level = os_hw_interrupt_disable();

    os_timer_remove(timer);

    os_hw_interrupt_enable(level);

    /* Change stat */
    timer->parent.flag &= ~OS_TIMER_FLAG_ACTIVATED;

    return OS_EOK;
}
EXPORT_SYMBOL(os_timer_stop);

/**
 ***********************************************************************************************************************
 * @brief           Control timer
 *
 * @details         This function control or change the properties of the timer.
 *
 * @param[in]       timer           The descriptor of timer control block.
 * @param[in]       cmd             Control commands.
 *                                  OS_TIMER_CTRL_SET_TIME:It will set timer timeout time.
 *                                  OS_TIMER_CTRL_GET_TIME:It will get timer timeout time.
 *                                  OS_TIMER_CTRL_SET_ONESHOT:It will change the timer to a one-shot timer.
 *                                  OS_TIMER_CTRL_SET_PERIODIC:It will change the timer to a periodic timer.
 * 
 * @param[in]       arg             Control argments.
 *
 *
 * @return          On success, return OS_EOK; on error, return a error code.
 * @retval          OS_EOK          Successfully control timer.
 * @retval          OS_ERROR        This command is currently not supported.
 ***********************************************************************************************************************
 */
os_err_t os_timer_control(os_timer_t *timer, enum os_timer_ctrl_cmd cmd, void *arg)
{
    OS_ASSERT(OS_NULL != timer);
    OS_ASSERT(OS_OBJECT_TIMER == os_object_get_type(&timer->parent));

    switch (cmd)
    {
    case OS_TIMER_CTRL_GET_TIME:
        *(os_tick_t *)arg = timer->init_tick;
        break;

    case OS_TIMER_CTRL_SET_TIME:
        timer->init_tick = *(os_tick_t *)arg;
        break;

    case OS_TIMER_CTRL_SET_ONESHOT:
        timer->parent.flag &= ~OS_TIMER_FLAG_PERIODIC;
        break;

    case OS_TIMER_CTRL_SET_PERIODIC:
        timer->parent.flag |= OS_TIMER_FLAG_PERIODIC;
        break;
        
    default:
        return OS_ERROR;
    }

    return OS_EOK;
}
EXPORT_SYMBOL(os_timer_control);

/**
 ***********************************************************************************************************************
 * @brief           This function checks whether the hard timer expires, and if it expires, executes the timeout 
 *                  processing function.
 *
 * @param           None
 *
 * @return          None
 ***********************************************************************************************************************
 */
void os_timer_check(void)
{
    os_timer_t         *t;
    os_tick_t           current_tick;
    register os_base_t  level;

    current_tick = os_tick_get();

    level = os_hw_interrupt_disable();

    while (!os_list_empty(&gs_os_timer_list[OS_TIMER_SKIP_LIST_LEVEL - 1]))
    {
        t = os_list_entry(gs_os_timer_list[OS_TIMER_SKIP_LIST_LEVEL - 1].next, os_timer_t, row[OS_TIMER_SKIP_LIST_LEVEL - 1]);
        
        /* It supposes that the new tick shall less than the half duration of tick max. */
        if ((current_tick - t->timeout_tick) < OS_TICK_MAX / 2)
        {
            OS_OBJECT_HOOK_CALL(gs_os_timer_enter_hook, (t));

            /* Remove timer from timer list firstly. */
            os_timer_remove(t);

            /* Call timeout function. */
            t->timeout_func(t->parameter);

            /* Re-get tick */
            current_tick = os_tick_get();

            OS_OBJECT_HOOK_CALL(gs_os_timer_exit_hook, (t));
            OS_KERN_LOG(KERN_DEBUG, TIMER_TAG, "current tick: %d", current_tick);

            if ((t->parent.flag & OS_TIMER_FLAG_PERIODIC) && (t->parent.flag & OS_TIMER_FLAG_ACTIVATED))
            {
                /* Start it */
                t->parent.flag &= ~OS_TIMER_FLAG_ACTIVATED;
                os_timer_start(t);
            }
            else
            {
                /* Stop timer */
                t->parent.flag &= ~OS_TIMER_FLAG_ACTIVATED;
            }
        }
        else
        {
            break;
        }
    }

    os_hw_interrupt_enable(level);
}

/**
 ***********************************************************************************************************************
 * @brief           This function gets the number of ticks for the next timeout.
 *
 * @param           None
 *
 * @return          Number of ticks.
 ***********************************************************************************************************************
 */
os_tick_t os_timer_next_timeout_tick(void)
{
    return os_timer_list_next_timeout(gs_os_timer_list);
}

#ifdef OS_USING_TIMER_SOFT

/**
 ***********************************************************************************************************************
 * @brief           This function gets the number of ticks for the soft timer next timeout.
 *
 * @param           None
 *
 * @return          Number of ticks.
 ***********************************************************************************************************************
 */
os_tick_t os_soft_timer_next_timeout_tick(void)
{
    return os_timer_list_next_timeout(gs_os_soft_timer_list);
}

/**
 ***********************************************************************************************************************
 * @brief           This function checks whether the soft timer expires, and if it expires, executes the timeout 
 *                  processing function
 *
 * @param[in]       None
 *
 * @return          None
 ***********************************************************************************************************************
 */
void os_soft_timer_check(void)
{
    os_timer_t     *t;
    os_list_node_t *n;
    os_list_node_t *pos;
    os_tick_t       current_tick;

    OS_KERN_LOG(KERN_DEBUG, TIMER_TAG, "software timer check enter");

    current_tick = os_tick_get();

    os_enter_critical();

    os_list_for_each_safe(pos, n, &gs_os_soft_timer_list[OS_TIMER_SKIP_LIST_LEVEL - 1])
    {
        t = os_list_entry(pos, os_timer_t, row[OS_TIMER_SKIP_LIST_LEVEL - 1]);

        /* It supposes that the new tick shall less than the half duration of tick max. */
        if ((current_tick - t->timeout_tick) < OS_TICK_MAX / 2)
        {
            OS_OBJECT_HOOK_CALL(gs_os_timer_enter_hook, (t));
            
            /* Remove timer from timer list firstly. */
            os_timer_remove(t);

            /* Not lock scheduler when performing timeout function. */
            os_exit_critical();
            
            /* Call timeout function. */
            t->timeout_func(t->parameter);

            /* Re-get tick. */
            current_tick = os_tick_get();

            OS_OBJECT_HOOK_CALL(gs_os_timer_exit_hook, (t));
            OS_KERN_LOG(KERN_DEBUG, TIMER_TAG, "current tick: %d", current_tick);

            os_enter_critical();

            if ((t->parent.flag & OS_TIMER_FLAG_PERIODIC) && (t->parent.flag & OS_TIMER_FLAG_ACTIVATED))
            {
                /* Start it. */
                t->parent.flag &= ~OS_TIMER_FLAG_ACTIVATED;
                (void)os_timer_start(t);
            }
            else
            {
                /* Stop timer. */
                t->parent.flag &= ~OS_TIMER_FLAG_ACTIVATED;
            }
        }
        else 
        {
            break;
        }
    }

    os_exit_critical();

    OS_KERN_LOG(KERN_DEBUG, TIMER_TAG, "software timer check leave");
}


static void os_task_timer_entry(void *parameter)
{
    os_tick_t          next_timeout;
    register os_base_t level;

    while (1)
    {
        level = os_hw_interrupt_disable();
        
        /* Get the next timeout tick. */
        next_timeout = os_timer_list_next_timeout(gs_os_soft_timer_list);
        
        if (OS_TICK_MAX == next_timeout)
        {
            /* No software timer exist, suspend self. */
            (void)os_task_suspend(os_task_self());

            os_hw_interrupt_enable(level);
            
            os_schedule();
        }
        else
        {
            os_hw_interrupt_enable(level);
            
            os_tick_t current_tick;

            /* Get current tick */
            current_tick = os_tick_get();

            if ((next_timeout - current_tick) < OS_TICK_MAX / 2)
            {
                /* Get the delta timeout tick, next_timeout is must be positive. */
                next_timeout = next_timeout - current_tick;
                os_task_delay(next_timeout);
            }
        }

        /* Check software timer */
        os_soft_timer_check();
    }
}
#endif

/**
 ***********************************************************************************************************************
 * @brief           This function will initialize the hard timer list.
 *
 * @param[in]       None
 *
 * @return          None
 ***********************************************************************************************************************
 */
void os_system_timer_init(void)
{
    os_int32_t i;

    for (i = 0; i < sizeof(gs_os_timer_list) / sizeof(gs_os_timer_list[0]); i++)
    {
        os_list_init(gs_os_timer_list + i);
    }
}

/**
 ***********************************************************************************************************************
 * @brief           This function will initialize the soft timer list and startup soft timer task.
 *
 * @param[in]       None
 *
 * @return          None
 ***********************************************************************************************************************
 */
void os_system_timer_task_init(void)
{
#ifdef OS_USING_TIMER_SOFT
    os_int32_t i;
    os_err_t   ret;

    for (i = 0; i < sizeof(gs_os_soft_timer_list) / sizeof(gs_os_soft_timer_list[0]); i++)
    {
        os_list_init(gs_os_soft_timer_list + i);
    }

    /* Start software timer task. */
    ret = os_task_init(&gs_timer_task,
                       "timer", 
                       os_task_timer_entry, 
                       OS_NULL,
                       &gs_timer_task_stack[0],
                       sizeof(gs_timer_task_stack),
                       OS_TIMER_TASK_PRIO, 
                       10);
    OS_ASSERT(OS_EOK == ret);

    os_task_startup(&gs_timer_task);
    
#endif
}

#ifdef OS_USING_SHELL

#include <shell.h>

static os_err_t sh_list_timer_info(os_list_node_t *list)
{
    os_int32_t     maxlen;
    os_timer_t     *timer;
    os_list_node_t *node;
    
    const char *item_title = "timer";

    maxlen = os_object_name_maxlen(item_title, list);

    os_kprintf("%-*.s  periodic   timeout       flag\r\n", maxlen, item_title);
    os_object_split(maxlen);
    os_kprintf(     " ---------- ---------- -----------\r\n");
    
    for(node = list->next; node != list; node = node->next)
    {
        timer = (os_timer_t *)(os_list_entry(node, os_object_t, list));
        os_kprintf("%-*.*s 0x%08x 0x%08x ",
                   maxlen, OS_NAME_MAX,
                   timer->parent.name,
                   timer->init_tick,
                   timer->timeout_tick);
        if(timer->parent.flag & OS_TIMER_FLAG_ACTIVATED)
        {
            os_kprintf("activated\r\n");
        }
        else
        {
            os_kprintf("deactivated\r\n");
        }
    }

    os_kprintf("current tick:0x%08x\r\n", os_tick_get());

    return OS_EOK;
}

/**
***********************************************************************************************************************
* @brief           Show all timer on the list of timer object
*
* @param[in]       argc                argment count
* @param[in]       argv                argment list
*
* @return          Will only return OS_EOK     
***********************************************************************************************************************
*/
os_err_t sh_list_timer(os_int32_t argc, char **argv)
{
    os_object_info_t *info;

    info = os_object_get_info(OS_OBJECT_TIMER);
    return sh_list_timer_info(&info->object_list);
}

SH_CMD_EXPORT(timer, sh_list_timer, "show timer information");

#endif

