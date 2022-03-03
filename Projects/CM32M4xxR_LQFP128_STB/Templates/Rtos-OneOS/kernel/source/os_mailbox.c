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
 * @file        os_mailbox.c
 *
 * @brief       This file implements the mailbox functions.
 *
 * @revision
 * Date         Author          Notes
 * 2020-02-13   OneOS Team      First Version
 ***********************************************************************************************************************
 */
#include <oneos_config.h>
#include <os_errno.h>
#include <os_clock.h>
#include <os_timer.h>
#include <os_task.h>
#include <os_dbg.h>
#include <os_module.h>
#include <os_irq.h>
#include <os_stddef.h>
#include <os_mailbox.h>

#include "os_kernel_internal.h"

#ifdef OS_USING_MAILBOX

#define MAILBOX_TAG     "MB"

#ifdef OS_USING_HOOK

static void (*gs_os_mb_try_send_hook)(os_mailbox_t *mb) = OS_NULL;

static void (*gs_os_mb_send_hook)(os_mailbox_t *mb) = OS_NULL;

static void (*gs_os_mb_try_recv_hook)(os_mailbox_t *mb) = OS_NULL;

static void (*gs_os_mb_recv_hook)(os_mailbox_t *mb) = OS_NULL;

/**
 ***********************************************************************************************************************
 * @brief           This function sets a hook function called at the beginning of os_mb_send.
 *
 * @param[in]       hook            The hook function is complemented by user.
 *
 * @return          None
 ***********************************************************************************************************************
 */
void os_mb_try_send_set_hook(void (*hook)(os_mailbox_t *mb))
{
    gs_os_mb_try_send_hook = hook;
}
/**
 ***********************************************************************************************************************
 * @brief           This function sets a hook function called at the end of os_mq_send.
 *
 * @param[in]       hook            The hook function is complemented by user.
 *
 * @return          None
 ***********************************************************************************************************************
 */
void os_mb_send_set_hook(void (*hook)(os_mailbox_t *mb))
{
    gs_os_mb_send_hook = hook;
}

/**
 ***********************************************************************************************************************
 * @brief           This function sets a hook function called at the beginning of os_mb_recv.
 *
 * @param[in]       hook            The hook function is complemented by user.
 *
 * @return          None
 ***********************************************************************************************************************
 */
void os_mb_try_recv_set_hook(void (*hook)(os_mailbox_t *mb))
{
    gs_os_mb_try_recv_hook = hook;
}

/**
 ***********************************************************************************************************************
 * @brief           This function sets a hook function called at the end of os_mb_recv.
 *
 * @param[in]       hook            The hook function is complemented by user.
 *
 * @return          None
 ***********************************************************************************************************************
 */
void os_mb_recv_set_hook(void (*hook)(os_mailbox_t *mb))
{
    gs_os_mb_recv_hook = hook;
}

#endif /* end OS_USING_HOOK */


#ifdef OS_USING_HEAP
/**
 ***********************************************************************************************************************
 * @brief           Creates a mailbox
 *
 * @details         This function will creates a mailbox.The memory space of the mail buffer pointer and 
 *                  mailbox descriptor is applied from the heap
 *
 * @attention       This function cannot be called in interrupt.
 *
 * @param[in]       name            The name of mailbox
 * @param[in]       max_mails       Mailbox holds the maximum number of mail
 * @param[in]       flag            The ways to wake up blocked tasks
 *                                  OS_IPC_FLAG_FIFO:Wake up blocked tasks in a first-in, first-out order
 *                                  OS_IPC_FLAG_PRIO:Wake up blocked tasks in order of priority
 *
 * @return          On success, return a mailbox descriptor; on error, OS_NULL is returned.
 * @retval          not OS_NULL     Return a mailbox descriptor for use by other mailbox functions.
 * @retval          OS_NULL         Call os_mb_create failed.
 ***********************************************************************************************************************
 */
os_mailbox_t *os_mb_create(const char *name, os_size_t max_mails, os_ipc_flag_t flag)
{
    os_mailbox_t    *mb;

    OS_ASSERT(max_mails > 0);  

    /* Dynamically creating a mailbox will allocate memory and cannot be called in interrupt. */
    OS_DEBUG_NOT_IN_INTERRUPT;

    mb = (os_mailbox_t *)OS_KERNEL_MALLOC(sizeof(os_mailbox_t));
    if (OS_NULL == mb)
    {
        return OS_NULL;
    }

    mb->msg_pool = (os_uint32_t *)OS_KERNEL_MALLOC(max_mails * sizeof(os_uint32_t));
    if (OS_NULL == mb->msg_pool)
    {
        OS_KERNEL_FREE(mb);
        return OS_NULL;	
    }

    os_object_init(&mb->parent.parent, OS_OBJECT_MAILBOX, name, OS_FALSE);

    /* Set parent. */
    mb->parent.parent.flag = flag;

    /* Initialize ipc object */
    (void)os_ipc_object_init(&mb->parent);

    /* Initialize mailbox */
    mb->size        = max_mails;
    mb->entry       = 0;
    mb->in_offset   = 0;
    mb->out_offset  = 0;

    /* Initialize an additional list of sender suspend task */
    os_list_init(&mb->suspend_sender_task);

    return mb;
}
EXPORT_SYMBOL(os_mb_create);

/**
 ***********************************************************************************************************************
 * @brief           Destroy a mailbox
 *
 * @details         This function will destroy the specified mailbox by mailbox descriptor.It will be wake up 
                    the tasks that are blocking waiting for this mailbox and removed from the object list,
 *                  and also free the memory space of the mail buffer and mailbox descriptor.
 *
 * @attention       It corresponds to os_mb_create.This function cannot be used in interrupt.
 *
 * @param[in]       mb              The mailbox descriptor
 *
 * @return          Will only return OS_EOK
 * @retval          OS_EOK          Successfully destroyed a mailbox.
 ***********************************************************************************************************************
 */
os_err_t os_mb_destroy(os_mailbox_t *mb)
{
    OS_ASSERT(mb != OS_NULL);
    OS_ASSERT(OS_OBJECT_MAILBOX == os_object_get_type(&mb->parent.parent));
    OS_ASSERT(OS_FALSE == mb->parent.parent.is_static);

    os_enter_critical();

    /* Resume all suspended task. */
    os_ipc_list_resume_all(&mb->parent.suspend_task);

    /* Also resume all mailbox private suspended task. */
    os_ipc_list_resume_all(&mb->suspend_sender_task);

    /* Deinitialize mailbox object. */
    os_object_deinit(&mb->parent.parent);

    /* Destroy a mailbox will free memory and cannot be called in interrupt. */
    OS_DEBUG_NOT_IN_INTERRUPT;
    
    OS_KERNEL_FREE(mb->msg_pool);
    OS_KERNEL_FREE(mb);
        
    os_exit_critical();

    os_schedule();
    
    return OS_EOK;
}
EXPORT_SYMBOL(os_mb_destroy);


#endif

/**
 ***********************************************************************************************************************
 * @brief           Initlialize a mailbox
 *
 * @details         This function will initlialize a mailbox object and put it on object list.
 *
 * @attention       The base address of msg_pool is preferably aligned according to 4 bytes. 
 *                  The msg_pool_size is preferably an integer multiple of 4.
 *                  If both msg_pool and msg_pool_size are aligned, the calculation formula for the number of 
 *                  mail is:msg_pool_size/sizeof(os_uint32_t).
 *
 * @param[in]       mb              The descriptor of mailbox
 * @param[in]       name            The name of mailbox
 * @param[in]       msg_pool        The base address of message pool
 * @param[in]       msg_pool_size   The size of a message pool
 * @param[in]       flag            The ways to wake up blocked tasks
 *                                  OS_IPC_FLAG_FIFO:wake up blocked tasks in a first-in, first-out order
 *                                  OS_IPC_FLAG_PRIO:wake up blocked tasks in order of priority
 *
 * @return          On success, return OS_EOK; on error, OS_ERROR is returned.
 * @retval          OS_EOK          Successfully initialized a mailbox.
 * @retval          OS_ERROR        When calculated number of mail is 0 ,initialized a mailbox failed.
 ***********************************************************************************************************************
 */
os_err_t os_mb_init(os_mailbox_t *mb,
                    const char   *name,                              
                    void         *msg_pool,
                    os_size_t     msg_pool_size,
                    os_ipc_flag_t flag)
{
    os_size_t  max_mails;
    os_ubase_t start;
    os_ubase_t end;

    OS_ASSERT(mb != OS_NULL);
    OS_ASSERT(msg_pool != OS_NULL);
    OS_ASSERT(msg_pool_size >= sizeof(os_uint32_t));  

    /* Align the base address. */
    if (((os_ubase_t)msg_pool & (sizeof(os_uint32_t) - 1)) != 0)
    {    
        start           = OS_ALIGN_UP((os_ubase_t)msg_pool, sizeof(os_uint32_t));
        end             = OS_ALIGN_DOWN((os_ubase_t)msg_pool + msg_pool_size, sizeof(os_uint32_t));
        mb->msg_pool    = (os_uint32_t *)start; 
        max_mails       = (end - start) / sizeof(os_uint32_t);

        if(0 == max_mails)
        {
            return OS_ERROR;
        }
    }
    else
    {
        mb->msg_pool    = msg_pool;
        max_mails       = msg_pool_size / sizeof(os_uint32_t);
    }

    os_object_init(&mb->parent.parent, OS_OBJECT_MAILBOX, name, OS_TRUE);

    /* Set parent. */
    mb->parent.parent.flag = flag;

    /* Initlialize ipc object. */
    (void)os_ipc_object_init(&mb->parent);

    /* Initlialize mailbox. */
    mb->size        = max_mails;
    mb->entry       = 0;
    mb->in_offset   = 0;
    mb->out_offset  = 0;

    /* Initlialize an additional list of sender suspend task. */
    os_list_init(&mb->suspend_sender_task);

    return OS_EOK;
}
EXPORT_SYMBOL(os_mb_init);

/**
 ***********************************************************************************************************************
 * @brief           Deinitialization a mailbox
 *
 * @details         This function will deinitialization the specified mailbox by mailbox descriptor.
 *                  It will be wake up the tasks that are blocking waiting for this mailbox
 *                  and removed from the object list 
 *
 * @attention       It corresponds to os_mb_init.
 *
 * @param[in]       mb              The mailbox descriptor
 *
 * @return          Will only return OS_EOK
 * @retval          OS_EOK          Successfully deinitialized a mailbox.
 ***********************************************************************************************************************
 */
os_err_t os_mb_deinit(os_mailbox_t *mb)
{
    OS_ASSERT(mb != OS_NULL);
    OS_ASSERT(OS_OBJECT_MAILBOX == os_object_get_type(&mb->parent.parent));
    OS_ASSERT(OS_TRUE == mb->parent.parent.is_static);

    os_enter_critical();
    
    /* Resume all suspended task. */
    os_ipc_list_resume_all(&mb->parent.suspend_task);

    /* Also resume all mailbox private suspended task. */
    os_ipc_list_resume_all(&mb->suspend_sender_task);

    /* Deinitialized mailbox object. */
    os_object_deinit(&mb->parent.parent);

    os_exit_critical();

    os_schedule();

    return OS_EOK;
}
EXPORT_SYMBOL(os_mb_deinit);

/**
 ***********************************************************************************************************************
 * @brief           Send a mail to mailbox
 *
 * @details         This function copys the value to the mailbox referenced by the descriptor mb.
 *
 * @param[in]       mb              The mailbox descriptor.
 * @param[in]       value           Content of mail.
 * @param[in]       timeout         Waitting time (in clock ticks).
 *
 * @return          On success, return OS_EOK; on error, return a error code.
 * @retval          OS_EOK          Successfully send a mail to mailbox.
 * @retval          OS_EFULL        When the timeout is 0 and the mailbox is already full.
 * @retval          OS_ETIMEOUT     The call timed out before a mail could be transferred.
 ***********************************************************************************************************************
 */
os_err_t os_mb_send(os_mailbox_t *mb, os_uint32_t value, os_tick_t timeout)
{
    os_task_t           *task;
    os_tick_t           tick_delta;

    register os_ubase_t level;
    
    OS_ASSERT(mb != OS_NULL);
    OS_ASSERT(OS_OBJECT_MAILBOX == os_object_get_type(&mb->parent.parent));
    OS_ASSERT((timeout < (OS_TICK_MAX / 2)) || (OS_IPC_WAITING_FOREVER == timeout));

    
    task = os_task_self();

    OS_OBJECT_HOOK_CALL(gs_os_mb_try_send_hook, (mb));

    level = os_hw_interrupt_disable();

    /* When the mailbox is already full and the timeout is 0 return full */
    if ((mb->entry == mb->size) && (OS_IPC_WAITING_NO == timeout))
    {
        os_hw_interrupt_enable(level);

        return OS_EFULL;
    }

    while (mb->entry == mb->size)
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
        os_ipc_list_suspend(&mb->suspend_sender_task,
                            task,
                            mb->parent.parent.flag);

        /* Has waiting time, start task timer. */
        if (timeout != OS_IPC_WAITING_FOREVER)
        {
            /* Get the start tick of timer. */
            tick_delta = os_tick_get();

            OS_KERN_LOG(KERN_DEBUG, MAILBOX_TAG, "mb_send_wait: start timer of task:%s",
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
         *   4.other task or interrpt recv a mail  task->error = OK
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
    }

    /* Add mail. */
    mb->msg_pool[mb->in_offset] = value;
    mb->in_offset++;
    if (mb->in_offset >= mb->size)
    {
        mb->in_offset = 0;
    }
    mb->entry++;

    /* Resume suspended task. */
    if (!os_list_empty(&mb->parent.suspend_task))
    {
        os_ipc_list_resume(&mb->parent.suspend_task);

        os_hw_interrupt_enable(level);

        OS_OBJECT_HOOK_CALL(gs_os_mb_send_hook, (mb));
        
        os_schedule();

        return OS_EOK;
    }

    os_hw_interrupt_enable(level);

    OS_OBJECT_HOOK_CALL(gs_os_mb_send_hook, (mb));

    return OS_EOK;
}
EXPORT_SYMBOL(os_mb_send);

/**
 ***********************************************************************************************************************
 * @brief           Receive a mail from mailbox
 *
 * @details         This function gets a mail from the mailbox referenced by the descriptor mb.
 *
 * @param[in]       mb              The mailbox descriptor.
 * @param[in]       value           Pointer to mail to be receive.
 * @param[in]       timeout         Waitting time (in clock ticks).
 *
 * @return          On success, return OS_EOK; on error, return a error code.
 * @retval          OS_EOK          Successfully receive a mail from mailbox.
 * @retval          OS_ERROR        
 * @retval          OS_EEMPTY       When the timeout is 0 and the mailbox is empty.
 * @retval          OS_ETIMEOUT     The call timed out before a mail could be receiveed.
 ***********************************************************************************************************************
 */
os_err_t os_mb_recv(os_mailbox_t *mb, os_uint32_t *value, os_tick_t timeout)
{
    os_task_t          *task;
    os_tick_t           tick_delta;

    register os_ubase_t level;

    OS_ASSERT(mb != OS_NULL);
    OS_ASSERT(value != OS_NULL);
    OS_ASSERT(OS_OBJECT_MAILBOX == os_object_get_type(&mb->parent.parent));
    OS_ASSERT((timeout < (OS_TICK_MAX / 2)) || (OS_IPC_WAITING_FOREVER == timeout));

    task = os_task_self();

    OS_OBJECT_HOOK_CALL(gs_os_mb_try_recv_hook, (mb));

    level = os_hw_interrupt_disable();

    /* When the mailbox is empty and the timeout is 0 return empty. */
    if ((0 == mb->entry) && (OS_IPC_WAITING_NO == timeout))
    {
        os_hw_interrupt_enable(level);

        return OS_EEMPTY;
    }

    while (0 == mb->entry)
    {
        /* Reset error number in task */
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
        os_ipc_list_suspend(&mb->parent.suspend_task,
                            task,
                            mb->parent.parent.flag);

        /* Has waiting time, start task timer. */
        if (timeout != OS_IPC_WAITING_FOREVER)
        {
            /* Get the start tick of timer. */
            tick_delta = os_tick_get();

            OS_KERN_LOG(KERN_DEBUG, MAILBOX_TAG, "mb_recv: start timer of task:%s",
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
         *   4.other task or interrpt send a mail  task->error = OK
         */
        if (task->error != OS_EOK)
        {
            return task->error;
        }

        level = os_hw_interrupt_disable();

        /* If it's not waiting forever and then re-calculate timeout tick */
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

    /* Take out mail */
    *value = mb->msg_pool[mb->out_offset];
    mb->out_offset++;
    if (mb->out_offset >= mb->size)
    {
        mb->out_offset = 0;
    }
    mb->entry--;

    /* Resume suspended task */
    if (!os_list_empty(&mb->suspend_sender_task))
    {
        os_ipc_list_resume(&mb->suspend_sender_task);

        os_hw_interrupt_enable(level);

        OS_OBJECT_HOOK_CALL(gs_os_mb_recv_hook, (mb));

        os_schedule();

        return OS_EOK;
    }

    os_hw_interrupt_enable(level);

    OS_OBJECT_HOOK_CALL(gs_os_mb_recv_hook, (mb));

    return OS_EOK;
}
EXPORT_SYMBOL(os_mb_recv);

/**
 ***********************************************************************************************************************
 * @brief           Control mailbox
 *
 * @details         This function control or change the properties of the mailbox.
 *
 * @param[in]       mb              The message queue descriptor.
 * @param[in]       cmd             Control commands.
 *                                  OS_IPC_CMD_RESET:It will be wake up the tasks that are blocking waiting for this 
 *                                                   mailbox and set the number of mail to 0.
 * 
 * @param[in]       arg             Control argments.
 *
 * @return          On success, return OS_EOK; on error, return a error code.
 * @retval          OS_EOK          Successfully control mailbox.
 * @retval          OS_ERROR        This command is currently not supported.
 ***********************************************************************************************************************
 */
os_err_t os_mb_control(os_mailbox_t *mb, os_ipc_cmd_t cmd, void *arg)
{
    os_ubase_t      level;
    
    OS_ASSERT(mb != OS_NULL);
    OS_ASSERT(OS_OBJECT_MAILBOX == os_object_get_type(&mb->parent.parent));

    if (OS_IPC_CMD_RESET == cmd)
    {
        level = os_hw_interrupt_disable();

        /* Resume all waiting task and sender task. */
        os_ipc_list_resume_all(&mb->parent.suspend_task);
        os_ipc_list_resume_all(&mb->suspend_sender_task);

        /* Re-init mailbox. */
        mb->entry      = 0;
        mb->in_offset  = 0;
        mb->out_offset = 0;

        os_hw_interrupt_enable(level);

        os_schedule();

        return OS_EOK;
    }

    return OS_ERROR;
}
EXPORT_SYMBOL(os_mb_control);

#ifdef OS_USING_SHELL

#include <shell.h>

static os_err_t list_mailbox_info(os_list_node_t *list)
{
    int             maxlen;
    os_mailbox_t    *mb;
    os_list_node_t  *node;
    
    const char *item_title = "mailbox";

    maxlen = os_object_name_maxlen(item_title, list);

    os_kprintf("\r\n");
    os_kprintf("%-*.s entry size suspend task\r\n", maxlen, item_title); 
    os_object_split(maxlen);
    os_kprintf(     " ----  ---- ------------\r\n");
    
    for (node = list->next; node != list; node = node->next)
    {
        mb = (os_mailbox_t *)(os_list_entry(node, os_object_t, list));
        if (!os_list_empty(&mb->parent.suspend_task))
        {
            os_kprintf( "%-*.*s %04d  %04d %d:",
                        maxlen,
                        OS_NAME_MAX,
                        mb->parent.parent.name,
                        mb->entry,
                        mb->size,
                        os_list_len(&mb->parent.suspend_task));
            os_ipc_show_waiting_task(&mb->parent.suspend_task);
        }

        else if (!os_list_empty(&mb->suspend_sender_task))
        {
            os_kprintf( "%-*.*s %04d  %04d %d:",
                        maxlen,
                        OS_NAME_MAX,
                        mb->parent.parent.name,
                        mb->entry,
                        mb->size,
                        os_list_len(&mb->suspend_sender_task));
            
            os_ipc_show_waiting_task(&mb->suspend_sender_task);   
        }
        else
        {
            os_kprintf( "%-*.*s %04d  %04d %d",
                        maxlen,
                        OS_NAME_MAX,
                        mb->parent.parent.name,
                        mb->entry,
                        mb->size,
                        0);
        }
        os_kprintf("\r\n");
    }

    return OS_EOK;
}

/**
 ***********************************************************************************************************************
 * @brief           Show all mailbox on the linked list of objects
 *
 * @param[in]       argc                argment count
 * @param[in]       argv                argment list
 *
 * @return          Will only return OS_EOK     
 ***********************************************************************************************************************
 */
os_err_t sh_list_mailbox(os_int32_t argc, char **argv)
{
    os_object_info_t *info;

    info = os_object_get_info(OS_OBJECT_MAILBOX);
    return list_mailbox_info(&info->object_list);
}

SH_CMD_EXPORT(mb, sh_list_mailbox, "show mailbox information");


#endif /* end of OS_USING_SHELL */


#endif /* end of OS_USING_MAILBOX */


