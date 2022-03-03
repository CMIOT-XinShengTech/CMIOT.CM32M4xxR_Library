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
 * @file        os_completion.c
 *
 * @brief       This file implements the completion functions.
 *
 * @revision
 * Date         Author          Notes
 * 2020-03-20   OneOS Team      First Version
 ***********************************************************************************************************************
 */
#include <os_task.h>
#include <os_errno.h>
#include <os_hw.h>
#include <os_dbg.h>
#include <os_module.h>
#include <os_ipc.h>
#include <extend/os_completion.h>

#include "../os_kernel_internal.h"

#ifdef OS_USING_COMPLETION

#define OS_COMPLETED    1
#define OS_UNCOMPLETED  0

/**
 ***********************************************************************************************************************
 * @brief           This function initializes a completion.
 *
 * @details         This function will initializate the specified completion by completion descriptor.
 *                  It will initializate the  suspend list to empty,and set the flag to OS_UNCOMPLETED.
 *
 * @param[in]       completion            The descriptor of completion.
 *
 * @return          None
 ***********************************************************************************************************************
 */
void os_completion_init(os_completion_t *completion)
{
    os_base_t level;
    
    OS_ASSERT(OS_NULL != completion);

    level = os_hw_interrupt_disable();
    
    completion->flag = OS_UNCOMPLETED;
    
    os_list_init(&completion->suspended_list);
    
    os_hw_interrupt_enable(level);
}
EXPORT_SYMBOL(os_completion_init);

/**
 ***********************************************************************************************************************
 * @brief           This function deinitializes a completion.
 *
 * @details         This function will deinitializate the specified completion by completion descriptor.
 *                  It will set the flag to OS_COMPLETED. If the block list have task, it will weak up the task and
 *                  set the error code of task to OS_ERROR.
 *
 * @param[in]       completion            The descriptor of completion.
 *
 * @return          None
 ***********************************************************************************************************************
 */
void os_completion_deinit(os_completion_t *completion)
{
    os_base_t level;
    os_task_t *task;

    OS_ASSERT(OS_NULL != completion);

    level = os_hw_interrupt_disable();
    
    completion->flag = OS_COMPLETED;

    if (!os_list_empty(&completion->suspended_list))
    {
        /* get task entry */
        task = os_list_entry(completion->suspended_list.next, os_task_t, task_list);

        task->error = OS_ERROR;

        os_task_resume(task);
        
        os_hw_interrupt_enable(level);

        os_schedule();
    }
    else
    {
        os_hw_interrupt_enable(level);
    }  
}
EXPORT_SYMBOL(os_completion_deinit);

/**
 ***********************************************************************************************************************
 * @brief           This function will suspend uitl a completion occur.
 *
 *
 * @attention       If some task on the block list,the system will assert.
 *
 * @param[in]       completion      The descriptor of completion.
 * @param[in]       timeout         Waitting time (in clock ticks).
 *
 * @return          On success, return OS_EOK; on error, return a error code.
 * @retval          OS_EOK          Successfully wait a completion.
 * @retval          OS_ETIMEOUT     The call timed out before weakup function return ok.
 ***********************************************************************************************************************
*/
os_err_t os_completion_wait(os_completion_t *completion, os_tick_t timeout)
{
    os_err_t  result;
    os_base_t level;
    os_task_t *task;
    
    OS_ASSERT(OS_NULL != completion);
    OS_ASSERT((timeout < (OS_TICK_MAX / 2)) || (OS_IPC_WAITING_FOREVER == timeout));

    result = OS_EOK;

    level = os_hw_interrupt_disable();
    
    if (OS_COMPLETED != completion->flag)
    {
        /* Only one task can suspend on complete. */
        OS_ASSERT(os_list_empty(&completion->suspended_list));

        if (OS_IPC_WAITING_NO == timeout)
        {
            result = OS_ETIMEOUT;
            goto __exit;
        }
        else
        {
            /* The following program will suspend the current task and can only be executed in the task context. */
            OS_DEBUG_IN_TASK_CONTEXT;
    
            task = os_task_self();
    
            task->error = OS_EOK;

            os_task_suspend(task);
            os_list_add_tail(&completion->suspended_list, &task->task_list);

            if (OS_IPC_WAITING_FOREVER != timeout)
            {
                os_timer_control(&task->task_timer, OS_TIMER_CTRL_SET_TIME, &timeout);
                os_timer_start(&task->task_timer);
            }
            
            os_hw_interrupt_enable(level);

            os_schedule();

            /* Task is waked up */
            result = task->error;

            level = os_hw_interrupt_disable();
        }
    }
    
    /* Clean completed flag */
    completion->flag = OS_UNCOMPLETED;

__exit:
    os_hw_interrupt_enable(level);

    return result;
}
EXPORT_SYMBOL(os_completion_wait);

/**
 ***********************************************************************************************************************
 * @brief           This function will release a completion.
 *
 * @attention       If completion flag is OS_COMPLETED it will nothing to do.
 *
 * @param[in]       completion      The descriptor of completion.
 *
 * @return          None.
 ***********************************************************************************************************************
*/
void os_completion_done(os_completion_t *completion)
{
    os_base_t level;
    os_task_t *task;
    OS_ASSERT(OS_NULL != completion);
  
    level = os_hw_interrupt_disable();

    if (OS_COMPLETED == completion->flag)
    {
        os_hw_interrupt_enable(level);
        return;
    }
     
    completion->flag = OS_COMPLETED;

    if (!os_list_empty(&completion->suspended_list))
    {
        task = os_list_entry(completion->suspended_list.next, os_task_t, task_list);

        os_task_resume(task);
        
        os_hw_interrupt_enable(level);

        os_schedule();
    }
    else
    {
        os_hw_interrupt_enable(level);
    }
}
EXPORT_SYMBOL(os_completion_done);

#endif /* OS_USING_COMPLETION */

