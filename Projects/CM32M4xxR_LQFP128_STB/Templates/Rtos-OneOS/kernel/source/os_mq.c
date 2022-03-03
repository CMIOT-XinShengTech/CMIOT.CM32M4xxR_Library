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
 * @file        os_mq.c
 *
 * @brief       This file implements the message queue functions.
 *
 * @revision
 * Date         Author          Notes
 * 2020-02-14   OneOS Team      First Version
 ***********************************************************************************************************************
 */

#include <oneos_config.h>
#include <os_stddef.h>
#include <os_errno.h>
#include <os_clock.h>
#include <os_dbg.h>
#include <os_irq.h>
#include <os_module.h>
#include <os_hw.h>
#include <os_mq.h>

#include "os_kernel_internal.h"
#include "os_util_internal.h"

#ifdef OS_USING_MESSAGEQUEUE

#define MSG_QUEUE_TAG       "MSGQ"

#ifdef OS_USING_HOOK

static void (*gs_os_mq_try_send_hook)(os_mq_t *mq) = OS_NULL;

static void (*gs_os_mq_send_hook)(os_mq_t *mq) = OS_NULL;

static void (*gs_os_mq_try_recv_hook)(os_mq_t *mq) = OS_NULL;

static void (*gs_os_mq_recv_hook)(os_mq_t *mq) = OS_NULL;

/**
 ***********************************************************************************************************************
 * @brief           This function sets a hook function called at the beginning of os_mq_send and os_mq_send_urgent.
 *
 * @param[in]       hook            The hook function is complemented by user.
 *
 * @return          None
 ***********************************************************************************************************************
 */
void os_mq_try_send_set_hook(void (*hook)(os_mq_t *mq))
{
    gs_os_mq_try_send_hook = hook;
}

/**
 ***********************************************************************************************************************
 * @brief           This function sets a hook function called at the end of os_mq_send and os_mq_send_urgent.
 *
 * @param[in]       hook            The hook function is complemented by user.
 *
 * @return          None
 ***********************************************************************************************************************
 */
void os_mq_send_set_hook(void (*hook)(os_mq_t *mq))
{
    gs_os_mq_send_hook = hook;
}

/**
 ***********************************************************************************************************************
 * @brief           This function sets a hook function called at the end of os_mq_recv.
 *
 * @param[in]       hook            The hook function is complemented by user.
 *
 * @return          None
 ***********************************************************************************************************************
 */
void os_mq_try_recv_set_hook(void (*hook)(os_mq_t *mq))
{
    gs_os_mq_try_recv_hook = hook;
}
/**
 ***********************************************************************************************************************
 * @brief           This function sets a hook function called at the end of os_mq_recv.
 *
 * @param[in]       hook        The hook function is complemented by user.
 *
 * @return          None
 ***********************************************************************************************************************
 */
void os_mq_recv_set_hook(void (*hook)(os_mq_t *mq))
{
    gs_os_mq_recv_hook = hook;
}

#endif /* end OS_USING_HOOK */


#ifdef OS_USING_HEAP
/**
 ***********************************************************************************************************************
 * @brief           Create a message queue
 *
 * @details         This function will creates a message queue.The memory space of the message queue buffer and 
 *                  message queue descriptor is applied from the heap.
 *
 * @attention       This function cannot be called in interrupt.
 *
 * @param[in]       name            The name of message queue
 * @param[in]       msg_size        The size of a message
 * @param[in]       max_msgs        Message queue holds the maximum number of messages
 * @param[in]       flag            The ways to wake up blocked tasks
 *                                  OS_IPC_FLAG_FIFO:Wake up blocked tasks in a first-in, first-out order
 *                                  OS_IPC_FLAG_PRIO:Wake up blocked tasks in order of priority
 *
 * @return          On success, return a message queue descriptor; on error, OS_NULL is returned.
 * @retval          not OS_NULL     Return a message queue descriptor for use by other message queue functions.
 * @retval          OS_NULL         Call os_mq_create failed.
 ***********************************************************************************************************************
 */
os_mq_t  *os_mq_create(const char     *name,
                       os_size_t       msg_size,
                       os_size_t       max_msgs,
                       os_ipc_flag_t   flag)
{
    os_mq_t            *mq;
    os_mq_msg_t        *head;
    os_size_t           align_msg_size;

    register os_base_t  index;

    OS_ASSERT(msg_size > 0);
    OS_ASSERT(max_msgs > 0);

    align_msg_size  = OS_ALIGN_UP(msg_size, OS_ALIGN_SIZE);

    /* Dynamically creating a message queue will allocate memory and cannot be called in interrupt. */
    OS_DEBUG_NOT_IN_INTERRUPT;

    mq = (os_mq_t *)OS_KERNEL_MALLOC(sizeof(os_mq_t));
    if (OS_NULL == mq)
    {
        return OS_NULL;
    }

    /* Use "os_mq_msg_t" to organize every messages,so need to allocate sizeof(os_mq_msg_t)  size additional spaces */
    mq->msg_pool = (void *)OS_KERNEL_MALLOC(max_msgs * (align_msg_size + sizeof(os_mq_msg_t)));
    if (OS_NULL == mq->msg_pool)
    {
        OS_KERNEL_FREE(mq);
        return OS_NULL;
    }

    os_object_init(&mq->parent.parent, OS_OBJECT_MESSAGEQUEUE, name, OS_FALSE); 

    /* Set parent. */
    mq->parent.parent.flag = flag;

    /* Initialize ipc object. */
    (void)os_ipc_object_init(&mq->parent);


    /* Get correct message size. */
    mq->msg_size = align_msg_size;
    mq->max_msgs = max_msgs;

    /* Initialize message list. */
    mq->msg_queue_head = OS_NULL;
    mq->msg_queue_tail = OS_NULL;

    /* Initialize message free list.Note:the last is head. */
    mq->msg_queue_free = OS_NULL;
    for (index = 0; index < mq->max_msgs; index++)
    {
        head = (os_mq_msg_t *)((os_uint8_t *)mq->msg_pool +
                        index * (mq->msg_size + sizeof(os_mq_msg_t)));
        head->next = mq->msg_queue_free;
        head->msg_len = 0;
        mq->msg_queue_free = head;
    }

    /* Initialize entry is zero */
    mq->entry = 0;
    
    /* Initialize an additional list of sender suspend task */
    os_list_init(&mq->suspend_sender_task);
    
    return mq;
}
EXPORT_SYMBOL(os_mq_create);

/**
 ***********************************************************************************************************************
 * @brief           Destroy a message queue
 *
 * @details         This function will destroy the specified message queue by message queue descriptor.It will be wake up 
                    the tasks that are blocking waiting for this message queue and removed from the object list,
 *                  and also free the memory space of the message queue buffer and message queue descriptor.
 *
 * @attention       It corresponds to os_mq_create.This function cannot be used in interrupt.
 *
 * @param[in]       mq              The message queue descriptor
 *
 * @return          Will only return OS_EOK
 * @retval          OS_EOK          Successfully destroyed a message queue.
 ***********************************************************************************************************************
 */
os_err_t os_mq_destroy(os_mq_t *mq)
{  
    OS_ASSERT(mq != OS_NULL);
    OS_ASSERT(OS_OBJECT_MESSAGEQUEUE == os_object_get_type(&mq->parent.parent));
    OS_ASSERT(OS_FALSE == mq->parent.parent.is_static);

    os_enter_critical();
    
    /*Resume all waiting task and sender task. */
    os_ipc_list_resume_all(&mq->parent.suspend_task);
    os_ipc_list_resume_all(&mq->suspend_sender_task);

    /* Deinit message queue object. */
    os_object_deinit(&mq->parent.parent);

    /* Destroy a message queue will free memory and cannot be called in interrupt. */
    OS_DEBUG_NOT_IN_INTERRUPT;
    
    OS_KERNEL_FREE(mq->msg_pool);
    OS_KERNEL_FREE(mq);

    os_exit_critical();
    
    os_schedule();


    return OS_EOK;
}

EXPORT_SYMBOL(os_mq_destroy);

#endif

/**
 ***********************************************************************************************************************
 * @brief           Initlialize a message queue
 *
 * @details         This function will initlialize a message queue object and put it on object list.
 *
 * @attention       The base address of msg_pool is preferably aligned according to 4 bytes. 
 *                  The msg_size is preferably an integer multiple of 4.
 *                  This msg_pool contains not only the message space, but also the message header space.
 *                  If both msg_pool_size and msg_size are aligned, the calculation formula for the number of 
 *                  messages is:msg_pool_size/(msg_size + sizeof(os_mq_msg_t))
 *
 * @param[in]       mq              The descriptor of message queue
 * @param[in]       name            The name of message queue
 * @param[in]       msg_pool        The base address of message pool
 * @param[in]       msg_pool_size   The size of a message pool
 * @param[in]       msg_size        The size of a message
 * @param[in]       flag            The ways to wake up blocked tasks
 *                                  OS_IPC_FLAG_FIFO:wake up blocked tasks in a first-in, first-out order
 *                                  OS_IPC_FLAG_PRIO:wake up blocked tasks in order of priority
 *
 * @return          Will only return OS_EOK
 * @retval          OS_EOK          Successfully initialized a message queue.
 ***********************************************************************************************************************
 */
os_err_t os_mq_init(os_mq_t        *mq,
                    const char     *name,
                    void           *msg_pool,
                    os_size_t       msg_pool_size,
                    os_size_t       msg_size,
                    os_ipc_flag_t   flag)
{
    os_mq_msg_t        *head;
    os_size_t           align_msg_size;
    os_size_t           max_msgs;
    os_size_t           start;
    os_size_t           end;

    register os_base_t  index;

    OS_ASSERT(mq != OS_NULL);
    OS_ASSERT(msg_pool != OS_NULL);
    OS_ASSERT(msg_size > 0);
    OS_ASSERT(msg_pool_size >= (OS_ALIGN_SIZE + sizeof(os_mq_msg_t)));

    
    align_msg_size  = OS_ALIGN_UP(msg_size, OS_ALIGN_SIZE);
    
    /* Align the base address. */
    if (((os_size_t)msg_pool & (OS_ALIGN_SIZE - 1)) != 0)
    {
        start           = OS_ALIGN_UP((os_uint32_t)msg_pool, OS_ALIGN_SIZE);
        end             = OS_ALIGN_DOWN((os_uint32_t)msg_pool + msg_pool_size,OS_ALIGN_SIZE);
        
        mq->msg_pool    = (os_uint32_t*)start; 
        max_msgs        = (end - start) / (align_msg_size + sizeof(os_mq_msg_t));
    }
    else
    {
        mq->msg_pool = msg_pool; 
        max_msgs     = msg_pool_size / (align_msg_size + sizeof(os_mq_msg_t));
    }
    
    os_object_init(&mq->parent.parent, OS_OBJECT_MESSAGEQUEUE, name, OS_TRUE); 

    /* Set parent. */
    mq->parent.parent.flag = flag;

    /* Initialize ipc object. */
    (void)os_ipc_object_init(&mq->parent);

    /* Get correct message size. */
    mq->msg_size = align_msg_size;
    mq->max_msgs = max_msgs;

    /* Initialize message list. */
    mq->msg_queue_head = OS_NULL;
    mq->msg_queue_tail = OS_NULL;

    /* Initialize message empty list Note:the last is head. */
    mq->msg_queue_free = OS_NULL;
    for (index = 0; index < mq->max_msgs; index++)
    {
        head = (os_mq_msg_t *)((os_uint8_t *)mq->msg_pool +
                        index * (mq->msg_size + sizeof(os_mq_msg_t)));
        head->next = mq->msg_queue_free;
        head->msg_len = 0;
        mq->msg_queue_free = head;
    }

    /* Initialize entry is zero. */
    mq->entry = 0;
    
    /* Initialize an additional list of sender suspend task. */
    os_list_init(&mq->suspend_sender_task);
    
    return OS_EOK;
}
EXPORT_SYMBOL(os_mq_init);


/**
 ***********************************************************************************************************************
 * @brief           Deinitialization a message queue
 *
 * @details         This function will deinitialization the specified message queue by message queue descriptor.
 *                  It will be wake up the tasks that are blocking waiting for this message queue
 *                  and removed from the object list 
 *
 * @attention       It corresponds to os_mq_init.
 *
 * @param[in]       mq              The message queue descriptor
 *
 * @return          Will only return OS_EOK
 * @retval          OS_EOK          Successfully deinitialized a message queue.
 ***********************************************************************************************************************
 */
os_err_t os_mq_deinit(os_mq_t *mq)
{
    OS_ASSERT(mq != OS_NULL);
    OS_ASSERT(OS_OBJECT_MESSAGEQUEUE == os_object_get_type(&mq->parent.parent));
    OS_ASSERT(OS_TRUE == mq->parent.parent.is_static);

    os_enter_critical();
    
    /* Resume all waiting task and sender task. */
    os_ipc_list_resume_all(&mq->parent.suspend_task);
    os_ipc_list_resume_all(&mq->suspend_sender_task);

    /* Deinitialize message queue object. */
    os_object_deinit(&mq->parent.parent);

    os_exit_critical();
    
    os_schedule();
    
    return OS_EOK;
}
EXPORT_SYMBOL(os_mq_deinit);

/**
 ***********************************************************************************************************************
 * @brief           Send a message to message queue
 *
 * @details         This function copies the buffer data to the message queue referenced by the descriptor mq.
 *
 * @param[in]       mq              The message queue descriptor.
 * @param[in]       buffer          Pointer to message to be sent.
 * @param[in]       buff_size       The size of the message pointed to by buffer.
 * @param[in]       timeout         Waitting time (in clock ticks).
 *
 * @return          On success, return OS_EOK; on error, return a error code.
 * @retval          OS_EOK          Successfully send a message to message queue.
 * @retval          OS_ERROR        When buff_size is greater than the msg_size attribute of the message queue.
 * @retval          OS_EFULL        When the timeout is 0 and the message queue is already full.
 * @retval          OS_ETIMEOUT     The call timed out before a message could be transferred.
 ***********************************************************************************************************************
 */
os_err_t os_mq_send(os_mq_t *mq, void *buffer, os_size_t buff_size, os_tick_t timeout)
{
    os_task_t          *task;
    os_mq_msg_t        *msg;
    os_tick_t           tick_delta;

    register os_ubase_t level;

    OS_ASSERT(mq != OS_NULL);
    OS_ASSERT(OS_OBJECT_MESSAGEQUEUE == os_object_get_type(&mq->parent.parent));
    OS_ASSERT(buffer != OS_NULL);
    OS_ASSERT(buff_size != 0);
    OS_ASSERT((timeout < (OS_TICK_MAX / 2)) || (OS_IPC_WAITING_FOREVER == timeout));

    if (buff_size > mq->msg_size)
    {
        return OS_ERROR;
    }

    task = os_task_self();
   
    OS_OBJECT_HOOK_CALL(gs_os_mq_try_send_hook, (mq));

    level = os_hw_interrupt_disable();

    /* Get a free list, there must be an empty item. */
    msg = (os_mq_msg_t *)mq->msg_queue_free;
    
    /* When the message queue is already full and non-blocking call return full. */
    if ((OS_NULL == msg) && (OS_IPC_WAITING_NO == timeout))
    {
        os_hw_interrupt_enable(level);

        return OS_EFULL;
    }

    while (OS_NULL == msg)
    {
        /* Reset error number in task. */
        task->error = OS_EOK;

        /* When the timeout is reduced to 0,return timeout. */
        if (0 == timeout)
        {
             task->error = OS_ETIMEOUT;

            os_hw_interrupt_enable(level);

            return OS_ETIMEOUT;
        }

        /* The following program will suspend the current task and can only be executed in the task context. */
        OS_DEBUG_IN_TASK_CONTEXT;
        
        /* Suspend current task. */
        os_ipc_list_suspend(&mq->suspend_sender_task,
                            task,
                            mq->parent.parent.flag);

        /* Has waiting time, start task timer */
        if (timeout != OS_IPC_WAITING_FOREVER)
        {
            /* Get the start tick of timer */
            tick_delta = os_tick_get();

            OS_KERN_LOG(KERN_DEBUG, MSG_QUEUE_TAG, "set task:%s to timer list",
                         task->parent.name);

            /* Reset the timeout of task timer and start it */
            os_timer_control(&task->task_timer,
                             OS_TIMER_CTRL_SET_TIME,
                             &timeout);
            os_timer_start(&task->task_timer);
        }

        os_hw_interrupt_enable(level);

        os_schedule();
        
        /* 
         *   The task is weaked up when the following event occurs:
         *   1.timeout                  task->error = OS_ETIMEOUT 
         *   2.os_mq_control reset      task->error = OS_ERROR
         *   3.signal                   task->error = EINTER
         *   4.other task or interrpt recv a message  task->error = OK
         */    
        if (task->error != OS_EOK)
        {
            /* Return error. */
            return task->error;
        }

        level = os_hw_interrupt_disable();

        /* If it's not waiting forever and then re-calculate timeout tick. */
        if (timeout != OS_IPC_WAITING_FOREVER)
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
        
        /* msg_queue_free may be changed */
        msg = (os_mq_msg_t *)mq->msg_queue_free;
    }
 
    /* Move free list pointer. */
    mq->msg_queue_free = msg->next;

    os_hw_interrupt_enable(level);

    /* The msg is the new tailer of list, the next shall be NULL */
    msg->next = OS_NULL;
    os_memcpy((char *)msg + sizeof(os_mq_msg_t), buffer, buff_size);
    msg->msg_len = buff_size;

    level = os_hw_interrupt_disable();
    /* Link msg to message queue. */
    if (mq->msg_queue_tail != OS_NULL)
    {
        /* if the tail exists, */
        ((os_mq_msg_t *)mq->msg_queue_tail)->next = msg;
    }

    /* Set new tail */
    mq->msg_queue_tail = msg;
    /* If the head is empty, set head. */
    if (OS_NULL == mq->msg_queue_head)
    {
        mq->msg_queue_head = msg;
    }

    mq->entry++;

    /* Resume suspended task. */
    if (!os_list_empty(&mq->parent.suspend_task))
    {
        os_ipc_list_resume(&mq->parent.suspend_task);

        os_hw_interrupt_enable(level);

        OS_OBJECT_HOOK_CALL(gs_os_mq_send_hook, (mq));
        
        os_schedule();

        return OS_EOK;
    }

    os_hw_interrupt_enable(level);

    OS_OBJECT_HOOK_CALL(gs_os_mq_send_hook, (mq));
    
    return OS_EOK;
}
EXPORT_SYMBOL(os_mq_send);

/**
 ***********************************************************************************************************************
 * @brief           Send  a urgent message to message queue
 *
 * @details         This function copies the buffer data to the message queue referenced by the descriptor mq.
 *                  os_mq_send_urgent() behaves just like os_mq_send(), except that it will add the current message 
 *                  to the head of the message queue for processing as soon as possible.
 *
 * @param[in]       mq              The message queue descriptor.
 * @param[in]       buffer          Pointer to message to be sent.
 * @param[in]       buff_size       The size of the message pointed to by buffer.
 * @param[in]       timeout         Waitting time (in clock ticks).
 *
 * @return          On success, return OS_EOK; on error, return a error code.
 * @retval          OS_EOK          Successfully send a urgent message to message queue.
 * @retval          OS_ERROR        When buff_size is greater than the msg_size attribute of the message queue.
 * @retval          OS_EFULL        When the timeout is 0 and the message queue is already full.
 * @retval          OS_ETIMEOUT     The call timed out before a message could be transferred.
 ***********************************************************************************************************************
 */                        
os_err_t os_mq_send_urgent(os_mq_t *mq, void *buffer, os_size_t buff_size, os_tick_t timeout)
{
    os_task_t          *task;
    os_mq_msg_t        *msg;
    os_tick_t           tick_delta;

    register os_ubase_t level;

    OS_ASSERT(mq != OS_NULL);
    OS_ASSERT(OS_OBJECT_MESSAGEQUEUE == os_object_get_type(&mq->parent.parent));
    OS_ASSERT(buffer != OS_NULL);
    OS_ASSERT(buff_size != 0);
    OS_ASSERT((timeout < (OS_TICK_MAX / 2)) || (OS_IPC_WAITING_FOREVER == timeout));

    if (buff_size > mq->msg_size)
    {
        return OS_ERROR;
    }

    task = os_task_self();

    OS_OBJECT_HOOK_CALL(gs_os_mq_try_send_hook, (mq));

    level = os_hw_interrupt_disable();

    /* Get a free list, there must be an empty item. */
    msg = (os_mq_msg_t *)mq->msg_queue_free;
    
    /* When the message queue is already full and non-blocking call return OS_EFULL */
    if ((OS_NULL == msg) && (OS_IPC_WAITING_NO == timeout))
    {
        os_hw_interrupt_enable(level);

        return OS_EFULL;
    }

    while (OS_NULL == msg)
    {
        /* Reset error number in task. */
        task->error = OS_EOK;

        /* When the timeout is reduced to 0,return timeout. */
        if (0 == timeout)
        {
            task->error = OS_ETIMEOUT;
           
            os_hw_interrupt_enable(level);

            return OS_ETIMEOUT;
        }

        /* The following program will suspend the current task and can only be executed in the task context. */
        OS_DEBUG_IN_TASK_CONTEXT;

        /* Suspend current task. */
        os_ipc_list_suspend(&mq->suspend_sender_task,
                            task,
                            mq->parent.parent.flag);

        /* Has waiting time, start task timer */
        if (timeout != OS_IPC_WAITING_FOREVER)
        {
            /* Get the start tick of timer. */
            tick_delta = os_tick_get();

            OS_KERN_LOG(KERN_DEBUG, MSG_QUEUE_TAG, "set task:%s to timer list",
                        task->parent.name);

            /* Reset the timeout of task timer and start it. */
            os_timer_control(&task->task_timer,
                             OS_TIMER_CTRL_SET_TIME,
                             &timeout);
            os_timer_start(&task->task_timer);
        }

        os_hw_interrupt_enable(level);

        os_schedule();

        /* 
         *   The task is weaked up when the following event occurs:
         *   1.timeout                  task->error = OS_ETIMEOUT 
         *   2.os_mq_control reset      task->error = OS_ERROR
         *   3.signal                   task->error = EINTER
         *   4.other task or interrpt recv a message  task->error = OK
         */ 
        if (task->error != OS_EOK)
        {
            return task->error;
        }

        level = os_hw_interrupt_disable();

        /* If it's not waiting forever and then re-calculate timeout tick. */
        if (timeout != OS_IPC_WAITING_FOREVER)
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
                
        /* msg_queue_free may be changed */
        msg = (os_mq_msg_t *)mq->msg_queue_free;
    }
    
    /* Move free list pointer. */
    mq->msg_queue_free = msg->next;

    os_hw_interrupt_enable(level);

    os_memcpy((char *)msg + sizeof(os_mq_msg_t), buffer, buff_size);
    msg->msg_len = buff_size;

    level = os_hw_interrupt_disable();

    /* Link msg to the beginning of message queue. */
    msg->next = mq->msg_queue_head;
    mq->msg_queue_head = msg;

    /* If there is no tail. */
    if (OS_NULL == mq->msg_queue_tail)
    {
        mq->msg_queue_tail = msg;
    }
       

    mq->entry++;

    /* Resume suspended task. */
    if (!os_list_empty(&mq->parent.suspend_task))
    {
        os_ipc_list_resume(&mq->parent.suspend_task);

        os_hw_interrupt_enable(level);
        
        OS_OBJECT_HOOK_CALL(gs_os_mq_send_hook, (mq));
        
        os_schedule();

        return OS_EOK;
    }

    os_hw_interrupt_enable(level);

    OS_OBJECT_HOOK_CALL(gs_os_mq_send_hook, (mq));
    
    return OS_EOK;
}
EXPORT_SYMBOL(os_mq_send_urgent);

/**
 ***********************************************************************************************************************
 * @brief           Receive a message from message queue
 *
 * @details         This function get a message from the message queue referenced by the descriptor mq
 *                  and then copyies it the buffer.
 *
 * @param[in]       mq              The message queue descriptor.
 * @param[in]       buffer          Pointer to message to be receive.
 * @param[in]       buff_size       The size of the message pointed to by buffer.
 * @param[in]       timeout         Waitting time (in clock ticks).
 * @param[out]      recv_size       Record the size of the received message.
 *
 * @return          On success, return OS_EOK; on error, return a error code.
 * @retval          OS_EOK          Successfully receive a message from message queue.
 * @retval          OS_ERROR        When buff_size is less than the msg_size attribute of the message queue.
 * @retval          OS_EEMPTY       When the timeout is 0 and the message queue is empty.
 * @retval          OS_ETIMEOUT     The call timed out before a message could be receiveed.
 ***********************************************************************************************************************
 */
os_err_t os_mq_recv(os_mq_t    *mq,
                    void       *buffer,
                    os_size_t   buff_size,
                    os_tick_t   timeout,
                    os_size_t   *recv_size)
{
    os_task_t          *task;
    os_mq_msg_t        *msg;
    os_tick_t           tick_delta;

    register os_ubase_t level;
    
    OS_ASSERT(mq != OS_NULL);
    OS_ASSERT(OS_OBJECT_MESSAGEQUEUE == os_object_get_type(&mq->parent.parent));
    OS_ASSERT(buffer != OS_NULL);
    OS_ASSERT(buff_size != 0);
    OS_ASSERT((timeout < (OS_TICK_MAX / 2)) || (OS_IPC_WAITING_FOREVER == timeout));
    OS_ASSERT(recv_size != OS_NULL);

    task = os_task_self();
    
    OS_OBJECT_HOOK_CALL(gs_os_mq_try_recv_hook, (mq));

    level = os_hw_interrupt_disable();

    /* When the message queue is empty and the timeout is 0 return empty. */
    if ((0 == mq->entry) && (OS_IPC_WAITING_NO == timeout))
    {
        os_hw_interrupt_enable(level);

        return OS_EEMPTY;
    }
    
    while (0 == mq->entry)
    {
        /* Reset error number in task. */
        task->error = OS_EOK;

        /* When the timeout is reduced to 0,return timeout */
        if (0 == timeout)
        {
            task->error = OS_ETIMEOUT;
            
            os_hw_interrupt_enable(level);

            return OS_ETIMEOUT;
        }

        /* The following program will suspend the current task and can only be executed in the task context. */
        OS_DEBUG_IN_TASK_CONTEXT;
        
        /* Suspend current task. */
        os_ipc_list_suspend(&mq->parent.suspend_task,
                            task,
                            mq->parent.parent.flag);

        /* Has waiting time, start task timer. */
        if (timeout != OS_IPC_WAITING_FOREVER)
        {
            /* Get the start tick of timer. */
            tick_delta = os_tick_get();

            OS_KERN_LOG(KERN_DEBUG, MSG_QUEUE_TAG, "set task:%s to timer list",
                        task->parent.name);

            /* Reset the timeout of task timer and start it. */
            os_timer_control(&task->task_timer,
                             OS_TIMER_CTRL_SET_TIME,
                             &timeout);
            os_timer_start(&task->task_timer);
        }

        os_hw_interrupt_enable(level);

        os_schedule();

        /* 
         *   The task is weaked up when the following event occurs:
         *   1.timeout                  task->error = OS_ETIMEOUT 
         *   2.os_mb_control reset      task->error = OS_ERROR
         *   3.signal                   task->error = EINTER
         *   4.other task or interrpt send a message  task->error = OK
         */
        if (task->error != OS_EOK)
        {
            /* return error */
            return task->error;
        }

        level = os_hw_interrupt_disable();

        /* If it's not waiting forever and then re-calculate timeout tick. */
        if (timeout != OS_IPC_WAITING_FOREVER)
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

    
    /* Get message from queue. */
    msg = (os_mq_msg_t *)mq->msg_queue_head;
    
    /* If user buff size is not enough. */
    if (buff_size < msg->msg_len)
    {
        OS_KERN_LOG(KERN_DEBUG, MSG_QUEUE_TAG, "task:%s get mq space not enough,buff_size %d less msg_len %d",
                    task->parent.name,buff_size,msg->msg_len);
        
        *recv_size = 0;
        
        os_hw_interrupt_enable(level);
        
        return OS_ERROR;
    }
    
    /* Move message queue head. */
    mq->msg_queue_head = msg->next;
    
    /* Reach queue tail, set to NULL. */
    if (mq->msg_queue_tail == msg)
    {
        mq->msg_queue_tail = OS_NULL;
    }

    mq->entry--;

    os_hw_interrupt_enable(level);

    /* Copy message to user buffer. */
    os_memcpy(buffer, (char *)msg + sizeof(os_mq_msg_t), msg->msg_len);
    *recv_size = msg->msg_len;
    
    level = os_hw_interrupt_disable();
    
    /* Put message to free list. */
    msg->next = (os_mq_msg_t *)mq->msg_queue_free;
    mq->msg_queue_free = msg;

    /* Resume suspended task */
    if (!os_list_empty(&mq->suspend_sender_task))
    {
        os_ipc_list_resume(&mq->suspend_sender_task);

        os_hw_interrupt_enable(level);

        OS_OBJECT_HOOK_CALL(gs_os_mq_recv_hook, (mq));

        os_schedule();

        return OS_EOK;
    }
    
    os_hw_interrupt_enable(level);

    OS_OBJECT_HOOK_CALL(gs_os_mq_recv_hook, (mq));
    
    return OS_EOK;
}
EXPORT_SYMBOL(os_mq_recv);

/**
 ***********************************************************************************************************************
 * @brief           Control message queue
 *
 * @details         This function control or change the properties of the message queue.
 *
 * @param[in]       mq              The message queue descriptor.
 * @param[in]       cmd             Control commands.
 *                                  OS_IPC_CMD_RESET:It will be wake up the tasks that are blocking waiting for this 
 *                                                   message queue and set the number of messages to 0.
 * 
 * @param[in]       arg             Control argments.
 *                                  
 *
 * @return          On success, return OS_EOK; on error, return a error code.
 * @retval          OS_EOK          Successfully control message queue.
 * @retval          OS_ERROR        This command is currently not supported.
 ***********************************************************************************************************************
 */
os_err_t os_mq_control(os_mq_t *mq, os_ipc_cmd_t cmd, void *arg)
{
    os_ubase_t  level;
    os_mq_msg_t *msg;

    OS_ASSERT(mq != OS_NULL);
    OS_ASSERT(OS_OBJECT_MESSAGEQUEUE == os_object_get_type(&mq->parent.parent));

    if (OS_IPC_CMD_RESET == cmd)
    {
        level = os_hw_interrupt_disable();

        /* Resume all waiting task and sender task. */
        os_ipc_list_resume_all(&mq->parent.suspend_task);
        os_ipc_list_resume_all(&mq->suspend_sender_task);

        /* Release all message in the queue. */
        while (mq->msg_queue_head != OS_NULL)
        {
            /* Get message from queue. */
            msg = (os_mq_msg_t *)mq->msg_queue_head;

            /* Move message queue head. */
            mq->msg_queue_head = msg->next;
            /* Reach queue tail, set to NULL. */
            if (mq->msg_queue_tail == msg)
            {
                mq->msg_queue_tail = OS_NULL;
            }
                
            /* Put message to free list */
            msg->next = (os_mq_msg_t *)mq->msg_queue_free;
            mq->msg_queue_free = msg;
        }

        mq->entry = 0;

        os_hw_interrupt_enable(level);

        os_schedule();

        return OS_EOK;
    }

    return OS_ERROR;
}
EXPORT_SYMBOL(os_mq_control);

#ifdef OS_USING_SHELL

#include <shell.h>

static os_err_t list_msgqueue_info(os_list_node_t *list)
{
    int             maxlen;
    os_mq_t         *mq;
    os_list_node_t  *node;
    
    const char *item_title = "msgqueue";

    maxlen = os_object_name_maxlen(item_title, list);

    os_kprintf("\r\n");
    os_kprintf("%-*.s entry size suspend task\r\n", maxlen, item_title); 
    os_object_split(maxlen);
    os_kprintf(     " ----  ---- ------------\r\n");
    for (node = list->next; node != list; node = node->next)
    {
        mq = (os_mq_t *)(os_list_entry(node, os_object_t, list));
        if (!os_list_empty(&mq->parent.suspend_task))
        {
            os_kprintf("%-*.*s %04d  %d:",
                        maxlen, 
                        OS_NAME_MAX,
                        mq->parent.parent.name,
                        mq->entry,
                        os_list_len(&mq->parent.suspend_task));
            
            os_ipc_show_waiting_task(&mq->parent.suspend_task);
        }
        else if (!os_list_empty(&mq->suspend_sender_task))
        {
            os_kprintf( "%-*.*s %04d  %d:",
                        maxlen,
                        OS_NAME_MAX,
                        mq->parent.parent.name,
                        mq->entry,
                        os_list_len(&mq->suspend_sender_task));
            
            os_ipc_show_waiting_task(&mq->suspend_sender_task);
        }
        else
        {
            os_kprintf( "%-*.*s %04d  %d",
                        maxlen,
                        OS_NAME_MAX,
                        mq->parent.parent.name,
                        mq->entry,
                        0);
        }
        
        os_kprintf("\r\n");
    }

    return OS_EOK;
}

 /**
 ***********************************************************************************************************************
 * @brief           Show all message queues on the linked list of objects
 *
 * @param[in]       argc                argment count
 * @param[in]       argv                argment list
 *
 * @return          Will only return OS_EOK     
 ***********************************************************************************************************************
 */
os_err_t sh_list_msgqueue(os_int32_t argc, char **argv)
{
    os_object_info_t *info;

    info = os_object_get_info(OS_OBJECT_MESSAGEQUEUE);
    return list_msgqueue_info(&info->object_list);
}

SH_CMD_EXPORT(mq, sh_list_msgqueue, "show message queue information");

#endif /* end of OS_USING_SHELL*/

#endif /* end of OS_USING_MESSAGEQUEUE */

