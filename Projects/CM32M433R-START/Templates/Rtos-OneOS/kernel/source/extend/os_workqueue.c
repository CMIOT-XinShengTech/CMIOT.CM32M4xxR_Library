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
 * @file        os_workqueue.c
 *
 * @brief       This function implements workqueue mechanism.
 *
 * @revision
 * Date         Author          Notes
 * 2020-04-06   OneOS Team      First version.
 ***********************************************************************************************************************
 */
#include <oneos_config.h>
#include <os_errno.h>
#include <os_assert.h>
#include <os_stddef.h>
#include <os_timer.h>
#include <os_ipc.h>
#include <os_object.h>
#include <extend/os_workqueue.h>

#include "./../os_kernel_internal.h"

#ifdef OS_USING_WORKQUEUE

/* Workqueue depends on memory heap. */
#ifndef OS_USING_HEAP
#error "Make sure memory heap is enable"
#endif

/* Workqueue depends on semaphore. */
#ifndef OS_USING_SEMAPHORE
#error "Make sure semaphore is enable"
#endif

/* Log tag of workqueue */
#define WORKQ_TAG       "WORKQ"

static void os_work_ref_get(os_work_t *work)
{
    work->ref_count++;
    return;
}

static void os_work_ref_put(os_work_t *work)
{
    if (work->ref_count > 0)
    {
        work->ref_count--;
    }

    if (0 == work->ref_count)
    {
        if (OS_NULL != work->cleanup)
        {
            work->cleanup(work);
        }
    }

    return;
}

static void os_workqueue_task_entry(void *parameter)
{
    os_base_t       level;
    os_work_t       *work;
    os_workqueue_t  *queue;

    OS_ASSERT(OS_NULL != parameter);

    queue = (os_workqueue_t *)parameter;
    
    while (1)
    {
        os_sem_wait(&queue->process_sem, OS_IPC_WAITING_FOREVER);

        while (1)
        {
            if (OS_TRUE == queue->destroy)
            {
                break;
            }
        
            level = os_hw_interrupt_disable();
            
            if (!os_list_empty(&queue->pending_list_head))
            {
                work = os_list_first_entry(&queue->pending_list_head, os_work_t, list);
                os_list_del(&work->list);

                os_work_ref_get(work);

                queue->work_current = work;
                work->stage         = OS_WORK_STAGE_PROCESSING;
                os_hw_interrupt_enable(level);

                /* Execute callback function */
                work->func(work, work->data);

                level = os_hw_interrupt_disable();
                
                queue->work_current = OS_NULL;
                work->workqueue     = OS_NULL; 
                work->stage         = OS_WORK_STAGE_INIT;

                /* Using for synchronization cancellation */
                (void)os_sem_post(&work->sem);
                
                os_hw_interrupt_enable(level);

                os_work_ref_put(work);
            }
            else
            {
                os_hw_interrupt_enable(level);
                break;
            }
        }
    }
}

/**
 ***********************************************************************************************************************
 * @brief           This function creates a workqueue.
 *
 * @param[in]       name            The name of task in workqueue.
 * @param[in]       stack_size      The stack size of task in workqueue.
 * @param[in]       priority        The priority of task in workqueue.
 *
 * @return          The created workqueue pointer.
 * @retval          OS_NULL         Create workqueue failed.
 * @retval          else            Create workqueue success.
 ***********************************************************************************************************************
 */
os_workqueue_t *os_workqueue_create(const char *name, os_uint32_t stack_size, os_uint8_t priority)
{
    os_workqueue_t *queue;

    OS_ASSERT(stack_size > 0);
    OS_ASSERT(priority < OS_TASK_PRIORITY_MAX);

    queue = (os_workqueue_t *)OS_KERNEL_MALLOC(sizeof(os_workqueue_t));
    if (!queue)
    {
        OS_KERN_LOG(KERN_ERROR, WORKQ_TAG, "Malloc workqueue(%s) failed", name);
        return OS_NULL;
    }

    os_list_init(&queue->pending_list_head);
    os_list_init(&queue->delaying_list_head);
    
    (void)os_sem_init(&queue->process_sem, OS_NULL, 0, OS_IPC_FLAG_FIFO);
    
    queue->work_current = OS_NULL;
    queue->destroy      = OS_FALSE;

    queue->process_task = os_task_create(name, os_workqueue_task_entry, (void *)queue, stack_size, priority, 10);
    if (OS_NULL == queue->process_task)
    {
        OS_KERN_LOG(KERN_ERROR, WORKQ_TAG, "Create workqueue(%s) task failed", name);

        os_sem_deinit(&queue->process_sem);
        OS_KERNEL_FREE(queue);
        
        return OS_NULL;
    }

    (void)os_task_startup(queue->process_task);

    return queue;
}

/**
 ***********************************************************************************************************************
 * @brief           Destroy a workqueue.
 *
 * @details         Before destroying the workqueue, all work is cancelled.
 *
 * @param[in]       queue           Workqueue to be destroyed.
 *
 * @return          Workqueue destroy result.
 * @retval          OS_EOK          Destroy workqueue success.
 * @retval          else            Destroy workqueue failed.
 ***********************************************************************************************************************
 */
os_err_t os_workqueue_destroy(os_workqueue_t *queue)
{
    os_work_t  *work_current;
    os_base_t   level;
    
    OS_ASSERT(queue != OS_NULL);

    queue->destroy = OS_TRUE;

    os_workqueue_cancel_all_work(queue);

    level = os_hw_interrupt_disable();
    if (OS_NULL != queue->work_current)
    {
        work_current = queue->work_current;
        os_hw_interrupt_enable(level);

        os_workqueue_cancel_work_sync(queue, work_current); 
    }
    else
    {
        os_hw_interrupt_enable(level); 
    }

    (void)os_task_destroy(queue->process_task);
    (void)os_sem_deinit(&queue->process_sem);
    
    OS_KERNEL_FREE(queue);
    
    return OS_EOK;
}

/**
 ***********************************************************************************************************************
 * @brief           Initialize work.
 *
 * @attention       Before using work, must initialize work.
 *
 * @param[in]       work            The work.
 * @param[in]       func            Callback function for work.
 * @param[in]       data            Private data of work.
 *
 * @return          None.
 ***********************************************************************************************************************
 */
void os_work_init(os_work_t *work, void (*func)(os_work_t *work, void *data), void *data)
{
    OS_ASSERT(work);
    OS_ASSERT(func);

    work->ref_count = 0;
    os_work_ref_get(work);

    os_list_init(&work->list);

    (void)os_sem_init(&work->sem, OS_NULL, 0, OS_IPC_FLAG_FIFO);

    /* Detach the object from system object container, so semaphore is initialized repeatly */
    os_object_deinit(&work->sem.parent.parent);
    work->sem.parent.parent.type = OS_OBJECT_SEMAPHORE;
    
    work->func      = func;
    work->data      = data;
    work->stage     = OS_WORK_STAGE_INIT;
    work->workqueue = OS_NULL;

    return;
}

/**
 ***********************************************************************************************************************
 * @brief           Deinitialize work.
 *
 * @attention       If there is no relevant resource to cleanup, it is not necessary to deinitialize the work.
 *
 * @param[in]       work            The work.
 * @param[in]       cleanup         Callback function for cleanuping asynchronously.
 *
 * @return          None.
 ***********************************************************************************************************************
 */
void os_work_deinit(os_work_t *work, void (*cleanup)(os_work_t *work))
{
    OS_ASSERT(work);

    work->cleanup = cleanup;
    os_work_ref_put(work);

    return;
}

static os_err_t os_workqueue_do_submit_work(os_workqueue_t *queue, os_work_t *work)
{
    os_base_t   level;
    os_uint16_t count;

    level = os_hw_interrupt_disable();

    if (work->workqueue)
    {
        os_hw_interrupt_enable(level);

        OS_KERN_LOG(KERN_WARNING, WORKQ_TAG, "Work has been submitted");
        
        return OS_EBUSY;
    }

    work->workqueue = queue;

    count = 0;
    os_sem_control(&work->sem, OS_IPC_CMD_RESET, (void *)&count);

    os_list_add_tail(&queue->pending_list_head, &work->list);
    work->stage = OS_WORK_STAGE_PENDING;

    os_sem_post(&queue->process_sem);

    os_hw_interrupt_enable(level);

    return OS_EOK;
}

static void os_delayed_work_timeout_handler(void *parameter)
{
    os_work_t      *delayed_work;
    os_base_t      level;
    os_uint16_t    count;

    delayed_work = (os_work_t *)parameter;

    os_work_ref_get(delayed_work);
    
    level = os_hw_interrupt_disable();

    if (OS_WORK_STAGE_SUBMITTING != delayed_work->stage)
    {
        os_hw_interrupt_enable(level);
        
        os_work_ref_put(delayed_work);
        
        OS_KERN_LOG(KERN_WARNING, WORKQ_TAG, "Work has been canceled"); 
        return;
    }

    if (OS_TRUE == delayed_work->workqueue->destroy)
    {
        os_hw_interrupt_enable(level);

        os_work_ref_put(delayed_work);

        OS_KERN_LOG(KERN_WARNING, WORKQ_TAG, "Workqueu is destroying, not continue process"); 
        return;
    }

    os_list_del(&delayed_work->list);
    os_timer_stop(&delayed_work->timer);
    os_timer_deinit(&delayed_work->timer);

    count = 0;
    os_list_add_tail(&delayed_work->workqueue->pending_list_head, &delayed_work->list);
    os_sem_control(&delayed_work->sem, OS_IPC_CMD_RESET, (void *)&count);
    delayed_work->stage = OS_WORK_STAGE_PENDING;

    os_sem_post(&delayed_work->workqueue->process_sem);

    os_hw_interrupt_enable(level);

    os_work_ref_put(delayed_work);

    return;
}

static os_err_t os_workqueue_do_submit_delayed_work(os_workqueue_t *queue, os_work_t *work, os_tick_t ticks)
{
    os_base_t   level;

    level = os_hw_interrupt_disable();

    if (work->workqueue)
    {
        os_hw_interrupt_enable(level);

        OS_KERN_LOG(KERN_WARNING, WORKQ_TAG, "Work has been submitted");
        return OS_EBUSY;
    }

    work->workqueue = queue;
    work->stage     = OS_WORK_STAGE_SUBMITTING;
    
    os_list_add_tail(&queue->delaying_list_head, &work->list);

    os_timer_init(&work->timer,
                  OS_NULL,
                  os_delayed_work_timeout_handler,
                  work,
                  ticks,
                  OS_TIMER_FLAG_ONE_SHOT | OS_TIMER_FLAG_SOFT_TIMER);
        
    os_hw_interrupt_enable(level);
    
    (void)os_timer_start(&work->timer);

    return OS_EOK;
}


/**
 ***********************************************************************************************************************
 * @brief           Submit a work to the specified workqueue.
 *
 * @details         When the delay_time is greater than 0, the work will be delayed.
 *
 * @param[in]       queue           The workqueue.
 * @param[in]       work            The work.
 * @param[in]       delay_time      Delay time. If it is greater than 0, the work will be delayed.
 *
 * @return          Submit work result.
 * @retval          OS_EOK          Submit work success.
 * @retval          OS_EBUSY        The work has been submitted.
 ***********************************************************************************************************************
 */
os_err_t os_workqueue_submit_work(os_workqueue_t *queue, os_work_t *work, os_tick_t delay_time)
{
    os_err_t ret;

    OS_ASSERT(OS_NULL != queue);
    OS_ASSERT(OS_NULL != work);
    OS_ASSERT(delay_time < (OS_TICK_MAX / 2));

    os_work_ref_get(work);

    ret = OS_EOK;
    if (0 == delay_time)
    {
        ret = os_workqueue_do_submit_work(queue, work);  
    }
    else
    {
        ret = os_workqueue_do_submit_delayed_work(queue, work, delay_time); 
    }

    os_work_ref_put(work);

    return ret;
}

static os_err_t os_workqueue_do_cancel_delayed_work(os_workqueue_t *queue, os_work_t *work)
{
    os_base_t   level;

    level = os_hw_interrupt_disable();

    /* Enter this function, judge again, avoid stage has been changed */
    if (work->stage != OS_WORK_STAGE_SUBMITTING)
    {
        os_hw_interrupt_enable(level);

        OS_KERN_LOG(KERN_WARNING, WORKQ_TAG, "Delay timer timeout, cancel failed");
        return OS_EBUSY;
    }

    if (work->workqueue != queue)
    {
        os_hw_interrupt_enable(level);
    
        OS_KERN_LOG(KERN_WARNING, WORKQ_TAG, "Workqueue is not match, cancel failed");
        return OS_ERROR;
    }

    os_list_del(&work->list);
    os_timer_stop(&work->timer);
    os_timer_deinit(&work->timer);
    
    work->stage     = OS_WORK_STAGE_CANCELED;
    work->workqueue = OS_NULL;
    
    os_hw_interrupt_enable(level);

    OS_KERN_LOG(KERN_INFO, WORKQ_TAG, "Cancel delayed work success");

    return OS_EOK;
}

static os_err_t os_workqueue_do_cancel_work(os_workqueue_t *queue, os_work_t *work)
{
    os_base_t level;

    level = os_hw_interrupt_disable();

    if ((OS_WORK_STAGE_INIT == work->stage) || (OS_WORK_STAGE_CANCELED == work->stage))
    {
        os_hw_interrupt_enable(level);

        OS_KERN_LOG(KERN_WARNING, WORKQ_TAG, "Work is not submitted, do nothing");
        return OS_EOK;    
    }

    if (OS_WORK_STAGE_SUBMITTING == work->stage)
    {
        os_hw_interrupt_enable(level);

        OS_KERN_LOG(KERN_WARNING, WORKQ_TAG, "Why enter this branch?");
        return OS_ERROR;    
    }

    if (work->workqueue != queue)
    {
        os_hw_interrupt_enable(level);
        
        OS_KERN_LOG(KERN_WARNING, WORKQ_TAG, "Workqueue is not match, cancel failed");
        return OS_ERROR;
    }
    
    if (queue->work_current == work)
    {
        os_hw_interrupt_enable(level);

        OS_KERN_LOG(KERN_WARNING, WORKQ_TAG, "Work is executing, not allow to canced");
        return OS_EBUSY;
    }
    
    os_list_del(&work->list);
    work->stage = OS_WORK_STAGE_CANCELED;
    work->workqueue = OS_NULL;
    
    os_hw_interrupt_enable(level);

    return OS_EOK;
}

/**
 ***********************************************************************************************************************
 * @brief           Cancel a work from the specified workqueue.
 *
 * @attention       Work cannot be cancelled while it is in progress, and return OS_EBUSY.
 *
 * @param[in]       queue           The workqueue.
 * @param[in]       work            The work.
 *
 * @return          Cancel work result.
 * @retval          OS_EOK          Cancel work success.
 * @retval          OS_EBUSY        The work is in progress.
 * @retval          OS_ERROR        Else error.
 ***********************************************************************************************************************
 */
os_err_t os_workqueue_cancel_work(os_workqueue_t *queue, os_work_t *work)
{
    os_err_t ret;

    OS_ASSERT(queue != OS_NULL);
    OS_ASSERT(work != OS_NULL);

    os_work_ref_get(work);

    ret = OS_EOK;
    if (OS_WORK_STAGE_SUBMITTING == work->stage)
    {
        ret = os_workqueue_do_cancel_delayed_work(queue, work);
        if (OS_EBUSY == ret)
        {
            ret = os_workqueue_do_cancel_work(queue, work);
        }
    }
    else
    {
        ret = os_workqueue_do_cancel_work(queue, work);
    }

    os_work_ref_put(work);
    
    return ret;
}

/**
 ***********************************************************************************************************************
 * @brief           To cancel work from specified workqueue synchronously.
 *
 * @attention       When the work in progress, wait for it to complete before returning, and return OS_EOK.
 *
 * @param[in]       queue           The workqueue.
 * @param[in]       work            The work.
 *
 * @return          Cancel work result.
 * @retval          OS_EOK          Cancel work success.
 * @retval          OS_ERROR        Else error.
 ***********************************************************************************************************************
 */
os_err_t os_workqueue_cancel_work_sync(os_workqueue_t *queue, os_work_t *work)
{
    os_err_t  ret;

    OS_ASSERT(queue != OS_NULL);
    OS_ASSERT(work != OS_NULL);

    os_work_ref_get(work);

    ret = os_workqueue_cancel_work(queue, work);
    if (OS_EBUSY != ret)
    {
        os_work_ref_put(work);
        return ret;
    }

    OS_KERN_LOG(KERN_INFO, WORKQ_TAG, "Waiting work to finish");

    os_sem_wait(&work->sem, OS_IPC_WAITING_FOREVER);

    os_work_ref_put(work);

    return OS_EOK;
}

/**
 ***********************************************************************************************************************
 * @brief           To cancel all work from specified workqueue
 *
 * @attention       If one work in progress, it will not be cancelled, nor will it wait for completion.
 *
 * @param[in]       queue           The workqueue.
 *
 * @return          None.
 ***********************************************************************************************************************
 */
void os_workqueue_cancel_all_work(os_workqueue_t *queue)
{
    os_base_t      level;
    os_list_node_t *pos;
    os_list_node_t *next;
    os_work_t      *work;

    OS_ASSERT(queue != OS_NULL);

    level = os_hw_interrupt_disable();
    os_list_for_each_safe(pos, next, &queue->delaying_list_head)
    {
        work = os_list_entry(pos, os_work_t, list);
        os_list_del(&work->list);

        os_work_ref_get(work);
        
        os_timer_stop(&work->timer);
        os_timer_deinit(&work->timer);
        
        work->stage     = OS_WORK_STAGE_CANCELED;
        work->workqueue = OS_NULL;

        os_work_ref_put(work);
    }
    os_hw_interrupt_enable(level);

    level = os_hw_interrupt_disable();
    os_list_for_each_safe(pos, next, &queue->pending_list_head)
    {
        work = os_list_entry(pos, os_work_t, list);
        os_list_del(&work->list);

        os_work_ref_get(work);
        
        work->stage     = OS_WORK_STAGE_CANCELED;
        work->workqueue = OS_NULL;

        os_work_ref_put(work);
    }
    os_hw_interrupt_enable(level);

    return;
}

#ifdef OS_USING_SYSTEM_WORKQUEUE

#if (OS_SYSTEM_WORKQUEUE_PRIORITY > OS_TASK_PRIORITY_MAX - 1)
#error "System workqueue task priority is greater than or equal to OS_TASK_PRIORITY_MAX"
#endif

static os_workqueue_t *gs_sys_workq = OS_NULL;

/**
 ***********************************************************************************************************************
 * @brief           Submit a work to the system workqueue.
 *
 * @details         When the delay_time is greater than 0, the work will be delayed.
 *
 * @param[in]       work            The work.
 * @param[in]       delay_time      Delay time. If it is greater than 0, the work will be delayed.
 *
 * @return          Submit work result.
 * @retval          OS_EOK          Submit work success.
 * @retval          OS_EBUSY        The work has been submitted.
 ***********************************************************************************************************************
 */
os_err_t os_submit_work(os_work_t *work, os_tick_t delay_time)
{
    return os_workqueue_submit_work(gs_sys_workq, work, delay_time);
}

/**
 ***********************************************************************************************************************
 * @brief           Cancel a work from the system workqueue.
 *
 * @attention       Work cannot be cancelled while it is in progress, and return OS_EBUSY.
 *
 * @param[in]       work            The work.
 *
 * @return          Cancel work result.
 * @retval          OS_EOK          Cancel work success.
 * @retval          OS_EBUSY        The work is in progress.
 * @retval          OS_ERROR        Else error.
 ***********************************************************************************************************************
 */
os_err_t os_cancel_work(os_work_t *work)
{
    return os_workqueue_cancel_work(gs_sys_workq, work);
}

/**
 ***********************************************************************************************************************
 * @brief           To cancel work from system workqueue synchronously.
 *
 * @attention       When the work in progress, wait for it to complete before returning, and return OS_EOK.
 *
 * @param[in]       work            The work.
 *
 * @return          Cancel work result.
 * @retval          OS_EOK          Cancel work success.
 * @retval          OS_ERROR        Else error.
 ***********************************************************************************************************************
 */
os_err_t os_cancel_work_sync(os_work_t *work)
{
    return os_workqueue_cancel_work_sync(gs_sys_workq, work);
}

/**
 ***********************************************************************************************************************
 * @brief           To cancel all work from system workqueue
 *
 * @attention       If one work in progress, it will not be cancelled, nor will it wait for completion.
 *
 * @param           None.
 *
 * @return          None.
 ***********************************************************************************************************************
 */
void os_cancel_all_work(void)
{
    os_workqueue_cancel_all_work(gs_sys_workq);
    return;
}

/**
 ***********************************************************************************************************************
 * @brief           Initialize system workqueue.
 *
 * @param           None.
 *
 * @return          Initialize system workqueue result.
 * @retval          OS_EOK          Initialize system workqueue success.
 * @retval          OS_ERROR        Initialize system workqueue failed.
 ***********************************************************************************************************************
 */
os_err_t os_work_sys_workqueue_init(void)
{
    /* prevent repeat create */
    if (gs_sys_workq != OS_NULL)
    {
        return OS_EOK;
    }

    gs_sys_workq = os_workqueue_create("sys_work", 
                                       OS_SYSTEM_WORKQUEUE_STACK_SIZE,
                                       OS_SYSTEM_WORKQUEUE_PRIORITY);

    if (gs_sys_workq != OS_NULL)
    {
        return OS_EOK;
    }
    else
    {
        OS_KERN_LOG(KERN_ERROR, WORKQ_TAG, "Create system workqueue failed");
        return OS_ERROR;   
    }    
}
OS_DEVICE_INIT(os_work_sys_workqueue_init);

#endif  /* OS_USING_SYSTEM_WORKQUEUE */

#endif /* END OS_USING_WORKQUEUE */

