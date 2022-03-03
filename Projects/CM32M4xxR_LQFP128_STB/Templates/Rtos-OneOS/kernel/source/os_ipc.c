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
 * @file        os_ipc.c
 *
 * @brief       This file implements the ipc public interface.
 *
 * @revision
 * Date         Author          Notes
 * 2020-02-11   OneOS Team      First Version
 ***********************************************************************************************************************
 */

#include <os_errno.h>
#include <os_ipc.h>

#include "os_kernel_internal.h"

/**
 ***********************************************************************************************************************
 * @brief           This function will initlialize the list of sender suspend task 
 *
 * @param[in]       ipc             the object descriptor of ipc
 *
 * @return          Will only return OS_EOK
 ***********************************************************************************************************************
 */
os_err_t os_ipc_object_init(os_ipc_object_t *ipc)
{
    /* Initlialize the list of sender suspend task to empty. */
    os_list_init(&(ipc->suspend_task));

    return OS_EOK;
}

/**
 ***********************************************************************************************************************
 * @brief           This function will suspend task based on object flag. 
 *
 * @param[in]       list            The list head of ipc object.
 * @param[in]       task            The taks descriptor.
 * @param[in]       flag            The ways to wake up blocked tasks
 *                                  OS_IPC_FLAG_FIFO:Wake up blocked tasks in a first-in, first-out order
 *                                  OS_IPC_FLAG_PRIO:Wake up blocked tasks in order of priority
 *
 * @return          Will only return OS_EOK
 ***********************************************************************************************************************
 */
os_err_t os_ipc_list_suspend(os_list_node_t     *list,
                             os_task_t          *task,
                             os_uint8_t          flag)
{
    os_task_suspend(task);

    switch (flag)
    {
    case OS_IPC_FLAG_FIFO:
        os_list_add_tail(list, &(task->task_list));
        break;

    case OS_IPC_FLAG_PRIO:
    default:
        {
            os_list_node_t *n;
            os_task_t      *stask;

            /* Find a suitable position. */
            for (n = list->next; n != list; n = n->next)
            {
                stask = os_list_entry(n, os_task_t, task_list);

                /* Find out. */
                if (task->current_priority < stask->current_priority)
                {
                    /* Insert this task before the stask. */
                    os_list_add_tail(&(stask->task_list), &(task->task_list));
                    break;
                }
            }

            /*
             * IF not found a suitable position,
             * append to the end of suspend_task list.
             */
            if (n == list)
                os_list_add_tail(list, &(task->task_list));
        }
        break;
    }

    return OS_EOK;
}

/**
 ***********************************************************************************************************************
 * @brief           This function will resume the first task on the list. 
 *
 * @param[in]       list            The list head of ipc object.
 *
 * @return          Will only return OS_EOK
 ***********************************************************************************************************************
 */
os_err_t os_ipc_list_resume(os_list_node_t *list)
{
    os_task_t *task;

    task = os_list_entry(list->next, os_task_t, task_list);
    
    os_task_resume(task);

    return OS_EOK;
}

/**
 ***********************************************************************************************************************
 * @brief           This function will resume all the task on the list. 
 *
 * @param[in]       list            The list head of ipc object.
 *
 * @attention       The error code of all the awakened tasks is set to OS_ERROR. 
 *
 * @return          Will only return OS_EOK
 ***********************************************************************************************************************
 */
 
os_err_t os_ipc_list_resume_all(os_list_node_t *list)
{
    os_task_t              *task;
    register os_ubase_t     temp;

    /* Wakeup all suspend tasks. */
    while (!os_list_empty(list))
    {
        temp = os_hw_interrupt_disable();

        /* Get next suspend task. */
        task = os_list_entry(list->next, os_task_t, task_list);
        /* Set error code to OS_ERROR. */
        task->error = OS_ERROR;

        os_task_resume(task);

        os_hw_interrupt_enable(temp);
    }

    return OS_EOK;
}

#ifdef OS_USING_SHELL

/**
 ***********************************************************************************************************************
 * @brief           This function will show all the task on the list. 
 *
 * @param[in]       list            The list head of ipc object.
 *
 *
 * @return          None
 ***********************************************************************************************************************
 */
void os_ipc_show_waiting_task(os_list_node_t *list)
{
    os_task_t *task;
    os_list_node_t *node;

    for (node = list->next; node != list; node = node->next)
    {
        task = os_list_entry(node, os_task_t, task_list);
        os_kprintf("%s", task->parent.name);

        if (node->next != list)
        {
            os_kprintf("/");
        }
    }
}

#endif


