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
 * @file        os_dataqueue.c
 *
 * @brief       This file implements the data queue functions.
 *
 * @revision
 * Date         Author          Notes
 * 2020-03-20   OneOS Team      First Version
 ***********************************************************************************************************************
 */
#include <os_errno.h>
#include <os_hw.h>
#include <os_timer.h>
#include <os_clock.h>
#include <os_task.h>
#include <os_ipc.h>
#include <os_module.h>
#include <extend/os_dataqueue.h>
#include <os_dbg.h>

#include "../os_kernel_internal.h"

#define DATA_QUEUE_TAG      "DATAQ"

#ifdef OS_USING_DATAQUEUE

#ifndef OS_USING_HEAP
#error "Make sure memory heap is enable"
#endif

/**
 ***********************************************************************************************************************
 * @brief           This function initializes a data queue.
 *
 * @param[in]       queue           The descriptor of data queue.
 * @param[in]       size            Data queue holds the maximum number of data item.
 * @param[in]       threshold       When the number of data item less than this,resume the push task. 
 * @param[in]       evt_notify      The callback function of data queue.
 *
 * @return          On success, return OS_EOK; on error, return a error code.
 * @retval          OS_EOK          Successfully initialized a data queue.
 * @retval          OS_ENOMEM       The space of heap is not enough.
 ***********************************************************************************************************************
 */
os_err_t os_data_queue_init(os_data_queue_t    *queue,
                            os_uint16_t         size,
                            os_uint16_t         threshold,
                            void              (*evt_notify)(os_data_queue_t *queue, os_uint32_t event))
{
    OS_ASSERT(OS_NULL != queue);

    queue->evt_notify = evt_notify;

    queue->size      = size;
    queue->threshold = threshold;

    queue->get_index = 0x00;
    queue->put_index = 0x00;

    os_list_init(&queue->suspended_push_list);
    os_list_init(&queue->suspended_pop_list);

    queue->queue = (os_data_item_t *)OS_KERNEL_MALLOC(sizeof(os_data_item_t) * size);
    if (OS_NULL == queue->queue)
    {
        OS_KERN_LOG(KERN_ERROR, DATA_QUEUE_TAG, "data queue init fail,no mem");
        return OS_ENOMEM;
    }

    return OS_EOK;
}
EXPORT_SYMBOL(os_data_queue_init);

/**
 ***********************************************************************************************************************
 * @brief           Deinitialization a data queue
 *
 * @details         This function will deinitialization the specified data queue by data queue descriptor.
 *                  It will be wake up the tasks that are blocking waiting for this data queue.
 *
 * @attention       It corresponds to os_data_queue_init.
 *
 * @param[in]       queue           The data queue descriptor
 *
 * @return          Will only return OS_EOK
 ***********************************************************************************************************************
 */
os_err_t os_data_queue_deinit(os_data_queue_t *queue)
{
    OS_ASSERT(OS_NULL != queue);
    OS_ASSERT(OS_NULL != queue->queue);

    os_enter_critical();

    queue->evt_notify = OS_NULL;

    queue->size      = 0;
    queue->threshold = 0;

    queue->get_index = 0;
    queue->put_index = 0;

    os_ipc_list_resume_all(&queue->suspended_push_list);
    os_ipc_list_resume_all(&queue->suspended_pop_list);

    OS_KERNEL_FREE(queue->queue);
    queue->queue = OS_NULL;

    os_exit_critical();

    os_schedule();

    return OS_EOK;
}
EXPORT_SYMBOL(os_data_queue_deinit);

/**
 ***********************************************************************************************************************
 * @brief           Push a data item to data queue.
 *
 * @details         This function will push a data item to specified data queue by data queue descriptor.
 *
 * @attention       It corresponds to os_data_queue_init.
 *
 * @param[in]       queue           The data queue descriptor.
 * @param[in]       data_ptr        Pointer to data item to be pushed.
 * @param[in]       data_size       The size of data item to be pushed.
 * @param[in]       timeout         Waiting time in ticks.
 *
 * @return          On success, return OS_EOK; on error, return a error code.
 * @retval          OS_EOK          Successfully push a data item to data queue.
 * @retval          OS_ETIMEOUT     The call timed out before a data item could be pushed and data queue is full.
 ***********************************************************************************************************************
 */
os_err_t os_data_queue_push(os_data_queue_t *queue, const void *data_ptr, os_size_t data_size, os_tick_t timeout)
{
    os_ubase_t  level;
    os_task_t  *task;
    os_err_t    result;
    os_tick_t   tick_delta;
    
    OS_ASSERT(OS_NULL != queue);
    OS_ASSERT(OS_NULL != queue->queue);
    OS_ASSERT((timeout < (OS_TICK_MAX / 2)) || (OS_IPC_WAITING_FOREVER == timeout));

    result = OS_EOK;
   
    level = os_hw_interrupt_disable();

    while (queue->size == (queue->put_index - queue->get_index))
    {
        /* Data queue is full. */
        if (OS_IPC_WAITING_NO == timeout)
        {            
            result = OS_ETIMEOUT;

            goto __exit;
        }

        /* The following program will suspend the current task and can only be executed in the task context. */
        OS_DEBUG_IN_TASK_CONTEXT;
        
        task = os_task_self();

        task->error = OS_EOK;
        
        /* Suspend task on the push list */
        os_task_suspend(task);
        os_list_add_tail(&queue->suspended_push_list, &task->task_list);

        if (OS_IPC_WAITING_FOREVER != timeout)
        {
            tick_delta = os_tick_get();
            os_timer_control(&task->task_timer, OS_TIMER_CTRL_SET_TIME, &timeout);
            os_timer_start(&task->task_timer);
        }

        os_hw_interrupt_enable(level);

        os_schedule();

        /* Task is waked up. */
        result = task->error;

        level = os_hw_interrupt_disable();

        if (OS_EOK != result)
        {
            goto __exit;
        }

        if (OS_IPC_WAITING_FOREVER != timeout)
        {
            tick_delta = os_tick_get() - tick_delta;
            if (timeout > tick_delta)
            {
                 timeout -= tick_delta;
            }
            else
            {
                 timeout = 0;
            }
        }
    }

    queue->queue[queue->put_index % queue->size].data_ptr  = data_ptr;
    queue->queue[queue->put_index % queue->size].data_size = data_size;
    queue->put_index += 1;

    /* There is at least one task in blocked list. */
    if (!os_list_empty(&queue->suspended_pop_list))
    {
        /* Get task entry. */
        task = os_list_entry(queue->suspended_pop_list.next, os_task_t, task_list);

        os_task_resume(task);

        os_hw_interrupt_enable(level);

        os_schedule();

        return result;
    }

__exit:
    os_hw_interrupt_enable(level);
    if ((OS_NULL != queue->evt_notify) && (OS_EOK == result))
    {
        queue->evt_notify(queue, OS_DATAQUEUE_EVENT_PUSH);
    }

    return result;
}
EXPORT_SYMBOL(os_data_queue_push);

/**
 ***********************************************************************************************************************
 * @brief           Pop a data item from data queue.
 *
 * @details         This function will pop a data item from specified data queue by data queue descriptor.
 *
 * @attention       When the number of data item less than threshold,resume the push task.
 *
 * @param[in]       queue           The data queue descriptor.
 * @param[out]      data_ptr        Secondary pointer to data item to be poped.
 * @param[out]      size            The size of data item to be poped.
 * @param[in]       timeout         Waiting time in ticks.
 *
 * @return          On success, return OS_EOK; on error, return a error code.
 * @retval          OS_EOK          Successfully pop a data item from data queue.
 * @retval          OS_ETIMEOUT     The call timed out before a data item could be poped and data queue is empty.
 ***********************************************************************************************************************
 */
os_err_t os_data_queue_pop(os_data_queue_t *queue, const void** data_ptr, os_size_t *size, os_tick_t timeout)
{
    os_ubase_t  level;
    os_task_t  *task;
    os_err_t    result;
    os_tick_t   tick_delta;

    OS_ASSERT(OS_NULL != queue);
    OS_ASSERT(OS_NULL != queue->queue);
    OS_ASSERT(OS_NULL != data_ptr);
    OS_ASSERT(OS_NULL != size);
    OS_ASSERT((timeout < (OS_TICK_MAX / 2)) || (OS_IPC_WAITING_FOREVER == timeout));

    result = OS_EOK;

    level = os_hw_interrupt_disable();

    while (queue->get_index == queue->put_index)
    {
        /* queue is empty */
        if (OS_IPC_WAITING_NO == timeout)
        {
            result = OS_ETIMEOUT;
            goto __exit;
        }

        /* The following program will suspend the current task and can only be executed in the task context. */
        OS_DEBUG_IN_TASK_CONTEXT;

        task = os_task_self();
                
        task->error = OS_EOK;
        
        /* Suspend task on the pop list. */
        os_task_suspend(task);
        os_list_add_tail(&queue->suspended_pop_list, &task->task_list);

        if (OS_IPC_WAITING_FOREVER != timeout)
        {
            tick_delta = os_tick_get();
            os_timer_control(&task->task_timer, OS_TIMER_CTRL_SET_TIME, &timeout);
            os_timer_start(&task->task_timer);
        }

        os_hw_interrupt_enable(level);

        os_schedule();

        /* Task is waked up. */
        result = task->error;
        
        level  = os_hw_interrupt_disable();

        if (result != OS_EOK)
        {
            goto __exit;
        }

        if (OS_IPC_WAITING_FOREVER != timeout)
        {
            tick_delta = os_tick_get() - tick_delta;
            if (timeout > tick_delta)
            {
                 timeout -= tick_delta;
            }
            else
            {
                 timeout = 0;
            }
        }
    }

    *data_ptr = queue->queue[queue->get_index % queue->size].data_ptr;
    *size     = queue->queue[queue->get_index % queue->size].data_size;

    queue->get_index += 1;

    if ((queue->put_index - queue->get_index) <= queue->threshold)
    {
        /* There is at least one task in blocked list. */
        if (!os_list_empty(&queue->suspended_push_list))
        {
            /* Get task entry. */
            task = os_list_entry(queue->suspended_push_list.next, os_task_t, task_list);
            
            os_task_resume(task);
            
            os_hw_interrupt_enable(level);

            os_schedule();
        }
        else
        {
            os_hw_interrupt_enable(level);
        }

        if (OS_NULL != queue->evt_notify)
        {
            queue->evt_notify(queue, OS_DATAQUEUE_EVENT_THRESHOLD);
        }

        return result;
    }

__exit:
    os_hw_interrupt_enable(level);
    
    if ((OS_NULL != queue->evt_notify) && (OS_EOK == result))
    {
        queue->evt_notify(queue, OS_DATAQUEUE_EVENT_POP);
    }

    return result;
}
EXPORT_SYMBOL(os_data_queue_pop);

/**
 ***********************************************************************************************************************
 * @brief           peak a data item from data queue.
 *
 * @details         This function will peak a data item from specified data queue by data queue descriptor.
 *
 * @attention       os_data_queue_peak not modify the data queue descriptor.
 *
 * @param[in]       queue           The data queue descriptor.
 * @param[out]      data_ptr        Secondary pointer to data item to be peaked.
 * @param[out]      size            The size of data item to be poped.
 *
 * @return          On success, return OS_EOK; on error, return a error code.
 * @retval          OS_EOK          Successfully peak a data item from data queue.
 * @retval          OS_EEMPTY       Data queue is empty.
 ***********************************************************************************************************************
 */
os_err_t os_data_queue_peak(os_data_queue_t *queue, const void** data_ptr, os_size_t *size)
{
    os_ubase_t  level;

    OS_ASSERT(OS_NULL != queue);
    OS_ASSERT(OS_NULL != queue->queue);

    level = os_hw_interrupt_disable();

    if (queue->get_index == queue->put_index) 
    {
        os_hw_interrupt_enable(level);
        
        return OS_EEMPTY;
    }

    *data_ptr = queue->queue[queue->get_index % queue->size].data_ptr;
    *size     = queue->queue[queue->get_index % queue->size].data_size;

    os_hw_interrupt_enable(level);

    return OS_EOK;
}
EXPORT_SYMBOL(os_data_queue_peak);

/**
 ***********************************************************************************************************************
 * @brief           Reset a data queue
 *
 * @details         This function will reset the specified data queue by data queue descriptor.
 *                  It will be wake up the tasks that are blocking waiting for this data queue.
 *
 * @param[in]       queue           The data queue descriptor.
 *
 * @return          None
 ***********************************************************************************************************************
 */
void os_data_queue_reset(os_data_queue_t *queue)
{
    OS_ASSERT(OS_NULL != queue);
    OS_ASSERT(OS_NULL != queue->queue);

    os_enter_critical();

    os_ipc_list_resume_all(&queue->suspended_push_list);
    os_ipc_list_resume_all(&queue->suspended_pop_list);

    os_exit_critical();

    os_schedule();
}
EXPORT_SYMBOL(os_data_queue_reset);

#endif /* OS_USING_DATAQUEUE */

