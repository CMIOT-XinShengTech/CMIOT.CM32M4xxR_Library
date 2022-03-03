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
 * @file        os_waitqueue.c
 *
 * @brief       This file implements the waitqueue functions.
 *
 * @revision
 * Date         Author          Notes
 * 2020-03-19   OneOS Team      First Version
 ***********************************************************************************************************************
 */
#include <os_assert.h>
#include <os_ipc.h>

#include <extend/os_waitqueue.h>

#include "./../os_kernel_internal.h"

#ifdef OS_USING_WAITQUEUE

/**
 ***********************************************************************************************************************
 * @brief           Initlialize a waitqueue
 *
 * @details         This function will initlialize a waitqueue flag and list.
 *
 * @param[in]       queue           The descriptor of waitqueue.
 *
 * @return          No return value.
 ***********************************************************************************************************************
 */
void os_waitqueue_init(os_waitqueue_t *queue)
{
    OS_ASSERT(queue != OS_NULL);

    queue->flag = OS_WQ_FLAG_CLEAN;
    os_list_init(&queue->waiting_list);
}

/**
 ***********************************************************************************************************************
 * @brief           Add a waitqueue_node to waitqueue
 *
 * @details         This function will add a waitqueue_node at the end of waitqueue.
 *
 * @param[in]       queue           The descriptor of waitqueue.
 *
 * @return          No return value.
 ***********************************************************************************************************************
 */
void os_waitqueue_add(os_waitqueue_t *queue, os_waitqueue_node_t *node)
{
    os_base_t level;

    level = os_hw_interrupt_disable();

    os_list_add_tail(&queue->waiting_list, &node->list);

    os_hw_interrupt_enable(level);
}

/**
 ***********************************************************************************************************************
 * @brief           Remove a waitqueue_node from waitqueue
 *
 * @details         This function will remove a waitqueue_node from waitqueue.
 *
 * @param[in]       queue           The descriptor of waitqueue.
 *
 * @return          No return value.
 ***********************************************************************************************************************
 */
void os_waitqueue_remove(os_waitqueue_node_t *node)
{
    os_base_t level;

    level = os_hw_interrupt_disable();

    os_list_del(&node->list);

    os_hw_interrupt_enable(level);
}

/**
 ***********************************************************************************************************************
 * @brief           A default funtion for a waitqueue_node.
 *
 * @details         This function is a default funtion for a waitqueue_node.
 *
 * @param[in]       wait            a wait node.
 * @param[in]       key             a key for weak up.
 *
 * @return          No return value.
 ***********************************************************************************************************************
 */
os_err_t os_waitqueue_default_do_wake(os_waitqueue_node_t *wait, void *key)
{
    return OS_EOK;
}

/**
 ***********************************************************************************************************************
 * @brief           Wake up all tasks waiting for "key"
 *
 * @details         This function wake up all tasks waiting for "key".
 *
 * @param[in]       queue           The descriptor of waitqueue.
 * @param[in]       key             a key used by function wakeup() of waitqueue_node.
 * @return          None.
 ***********************************************************************************************************************
 */
void os_waitqueue_wakeup(os_waitqueue_t *queue, void *key)
{
    os_base_t               level;
    os_list_node_t         *queue_list;
    os_list_node_t         *node;
    os_waitqueue_node_t    *entry;

    queue_list = &queue->waiting_list;

    level = os_hw_interrupt_disable();
    
    /* Set wakeup flag in the queue. */
    queue->flag = OS_WQ_FLAG_WAKEUP;

    if (!(os_list_empty(queue_list)))
    {
        for (node = queue_list->next; node != queue_list; node = node->next)
        {
            entry = os_list_entry(node, os_waitqueue_node_t, list);
            if (entry->wakeup(entry, key) == 0)
            {
                os_task_resume(entry->polling_task);
                os_waitqueue_remove(entry);

                os_schedule();
                break;
            }
        }
    }

    os_hw_interrupt_enable(level);
}

/**
 ***********************************************************************************************************************
 * @brief           This function will suspend uitl a event occur.
 *
 * @param[in]       queue           The waitqueue to wait on.
 * @param[in]       condition       a condition for the event to wait for.
 * @param[out]      timeout         Waitting time (in clock ticks).
 *
 * @return          On success, return OS_EOK; on error, return a error code.
 * @retval          OS_EOK          Successfully wait weakup event.
 * @retval          OS_ETIMEOUT     The call timed out before weakup function return ok.
 ***********************************************************************************************************************
 */
os_err_t os_waitqueue_wait(os_waitqueue_t *queue, os_int32_t condition, os_tick_t timeout)
{
    os_task_t              *task;
    os_waitqueue_node_t     wait_node;
    os_base_t               level;

    OS_ASSERT(queue != OS_NULL);
    OS_ASSERT((timeout < (OS_TICK_MAX / 2)) || (OS_IPC_WAITING_FOREVER == timeout));

    /* The following program will suspend the current task and can only be executed in the task context. */
    OS_DEBUG_IN_TASK_CONTEXT;

    if ((condition) || (OS_IPC_WAITING_NO == timeout))
    {
        return OS_EOK;
    }

    task = os_task_self();

    os_waitqueue_node_init(&wait_node,
                           os_waitqueue_default_do_wake,
                           task,
                           0);

    level = os_hw_interrupt_disable();

    if (OS_WQ_FLAG_WAKEUP == queue->flag)
    {
        /* Already wakeup. */
        goto __exit_wakeup;
    }

    os_waitqueue_add(queue, &wait_node);

    task->error = OS_EOK;
    os_task_suspend(task);

    /* Has waiting time, start task timer. */
    if (timeout != OS_IPC_WAITING_FOREVER)
    {
        os_timer_control(&task->task_timer,
                         OS_TIMER_CTRL_SET_TIME,
                         &timeout);

        os_timer_start(&task->task_timer);
    }
    os_hw_interrupt_enable(level);

    os_schedule();

    level = os_hw_interrupt_disable();

__exit_wakeup:
    queue->flag = OS_WQ_FLAG_CLEAN;
    os_hw_interrupt_enable(level);

    os_waitqueue_remove(&wait_node);

    return task->error;
}

#endif /* End of OS_USING_WAITQUEUE */

