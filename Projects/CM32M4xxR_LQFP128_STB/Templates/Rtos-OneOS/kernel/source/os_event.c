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
 * @file        os_event.c
 *
 * @brief       This file implements the event functions.
 *
 * @revision
 * Date         Author          Notes
 * 2020-02-13   OneOS team      First Version
 ***********************************************************************************************************************
 */

#include <os_errno.h>
#include <os_event.h>
#include <os_module.h>
#include <os_dbg.h>
#include <os_irq.h>

#include "os_kernel_internal.h"

#ifdef OS_USING_EVENT

#define EVENT_TAG       "EVENT"

#ifdef OS_USING_HOOK

static void (*gs_os_event_send_hook)(os_event_t *event) = OS_NULL;

static void (*gs_os_event_try_recv_hook)(os_event_t *event) = OS_NULL;

static void (*gs_os_event_recv_hook)(os_event_t *event) = OS_NULL;

/**
 ***********************************************************************************************************************
 * @brief           This function sets a hook called at the beginning of os_event_send().
 *
 * @param[in]       hook             The hook function is complemented by user.
 *
 * @return          None.
 ***********************************************************************************************************************
 */
void os_event_send_set_hook(void (*hook)(os_event_t *event))
{
    gs_os_event_send_hook = hook;
}

/**
 ***********************************************************************************************************************
 * @brief           This function sets a hook called at the beging of os_event_recv().
 *
 * @param[in]       hook             The hook function is complemented by user.
 *
 * @return          None.
 ***********************************************************************************************************************
 */
void os_event_try_recv_set_hook(void (*hook)(os_event_t *event))
{
    gs_os_event_try_recv_hook = hook;
}

/**
 ***********************************************************************************************************************
 * @brief           This function sets a hook called at the end of os_event_recv().
 *
 * @param[in]       hook             The hook function is complemented by user.
 *
 * @return          None.
 ***********************************************************************************************************************
 */
void os_event_recv_set_hook(void (*hook)(os_event_t *event))
{
    gs_os_event_recv_hook = hook;
}

#endif /* end of OS_USING_HOOK */

/**
 ***********************************************************************************************************************
 * @brief           This function initlializes a event object and put it on object list.
 *
 * @param[in]       event           The pointer to event object.
 * @param[in]       name            The name of event object.
 * @param[in]       flag            The ipc flag of event object.
 *
 * @return          The operation result.
 * @retval          OS_EOK          If the operation successful.
 * @retval          else            Error code.
 ***********************************************************************************************************************
 */
os_err_t os_event_init(os_event_t *event, const char *name, os_ipc_flag_t flag)
{
    OS_ASSERT(event);

    /* Init base object */
    os_object_init(&event->parent.parent, OS_OBJECT_EVENT, name, OS_TRUE);

    /* Set parent */
    event->parent.parent.flag = flag;

    /* Init ipc object */
    os_ipc_object_init(&event->parent);

    /* Init event */
    event->set = 0;

    return OS_EOK;
}
EXPORT_SYMBOL(os_event_init);

/**
 ***********************************************************************************************************************
 * @brief           This function deinitializes an event object.
 *
 * @param[in]       event           The pointer to event object.
 *
 * @return          The operation result.
 * @retval          OS_EOK          If the operation successful.
 * @retval          else            Error code.
 ***********************************************************************************************************************
 */
os_err_t os_event_deinit(os_event_t *event)
{
    OS_ASSERT(OS_NULL != event);
    OS_ASSERT(OS_OBJECT_EVENT == os_object_get_type(&event->parent.parent));
    OS_ASSERT(OS_TRUE == os_object_is_static(&event->parent.parent));

    os_enter_critical();

    /* Resume all suspended task */
    os_ipc_list_resume_all(&event->parent.suspend_task);

    /* Deinit base object */
    os_object_deinit(&event->parent.parent);

    os_exit_critical();

    os_schedule();

    return OS_EOK;
}
EXPORT_SYMBOL(os_event_deinit);

#ifdef OS_USING_HEAP
/**
 ***********************************************************************************************************************
 * @brief           This function will create an event object from heap and put it on object list.
 *
 * @param[in]       name            The name of event.
 * @param[in]       value           The init value of event.
 * @param[in]       flag            The ipc flag of event.
 *
 * @return          The pointer to the created event object.
 * @retval          pointer         If operation successful.
 * @retval          OS_NULL         Error occurred.
 ***********************************************************************************************************************
 */
os_event_t *os_event_create(const char *name, os_ipc_flag_t flag)
{
    os_event_t *event;

    OS_DEBUG_NOT_IN_INTERRUPT;

    event = (os_event_t *)OS_KERNEL_MALLOC(sizeof(os_event_t));
    if (OS_NULL == event)
    {
        OS_KERN_LOG(KERN_ERROR, EVENT_TAG, "Malloc event memory failed");
        return OS_NULL;
    }

    /* Init base object */
    os_object_init(&event->parent.parent, OS_OBJECT_EVENT, name, OS_FALSE);

    /* Set parent */
    event->parent.parent.flag = flag;

    /* Init ipc object */
    os_ipc_object_init(&event->parent);

    /* Init event */
    event->set = 0;

    return event;
}
EXPORT_SYMBOL(os_event_create);

/**
 ***********************************************************************************************************************
 * @brief           Destory an event object created from heap.
 *
 * @param[in]       event           The event to destroy.
 *
 * @return          The operation result.
 * @retval          OS_EOK          If the operation successful.
 * @retval          else            Error code.
 ***********************************************************************************************************************
 */
os_err_t os_event_destroy(os_event_t *event)
{
    /* Parameter check */
    OS_ASSERT(OS_NULL != event);
    OS_ASSERT(OS_OBJECT_EVENT == os_object_get_type(&event->parent.parent));
    OS_ASSERT(OS_FALSE == os_object_is_static(&event->parent.parent));

    os_enter_critical();

    /* Resume all suspended task */
    os_ipc_list_resume_all(&event->parent.suspend_task);

    /* Deinit base object */
    os_object_deinit(&event->parent.parent);

    OS_DEBUG_NOT_IN_INTERRUPT;

    /* Free event object */
    OS_KERNEL_FREE(event);
    event = OS_NULL;

    os_exit_critical();

    os_schedule();

    return OS_EOK;
}
EXPORT_SYMBOL(os_event_destroy);
#endif /* OS_USING_HEAP */

/**
 ***********************************************************************************************************************
 * @brief           This function sends an event to event object. If there are tasks blocked on the event object, all tasks
 *                  interested this specific event will be woken up.
 *
 * @param[in]       event           The pointer to a event object.
 * @param[in]       set             The specific event set.
 *
 * @return          The operation result.
 * @retval          OS_EOK          If the operation successful.
 * @retval          else            Error code.
 ***********************************************************************************************************************
 */
os_err_t os_event_send(os_event_t *event, os_uint32_t set)
{
    os_list_node_t      *node;
    os_task_t           *task;
    register os_ubase_t level;
    register os_base_t  status;
    os_bool_t           need_schedule;

    OS_ASSERT(OS_NULL != event);
    OS_ASSERT(OS_OBJECT_EVENT == os_object_get_type(&event->parent.parent));

    if (0 == set)
    {
        return OS_ERROR;
    }

    need_schedule = OS_FALSE;

    level = os_hw_interrupt_disable();

    /* Set event. */
    event->set |= set;

    OS_OBJECT_HOOK_CALL(gs_os_event_send_hook, (event));

    /* Search suspend task list and resume suitable tasks. */
    if (!os_list_empty(&event->parent.suspend_task))
    {
        node = event->parent.suspend_task.next;
        while (node != &(event->parent.suspend_task))
        {
            task = os_list_entry(node, struct os_task, task_list);

            status = OS_ERROR;
            if (task->event_info & OS_EVENT_OPTION_AND)
            {
                if ((task->event_set & event->set) == task->event_set)
                {
                    /* Received an AND event. */
                    status = OS_EOK;
                }
            }
            else if (task->event_info & OS_EVENT_OPTION_OR)
            {
                if (task->event_set & event->set)
                {
                    /* Save recieved event set. */
                    task->event_set = task->event_set & event->set;

                    /* Received an OR event. */
                    status = OS_EOK;
                }
            }

            /* Move node to the next. */
            node = node->next;

            /* Condition is satisfied, resume task. */
            if (OS_EOK == status)
            {
                /* Clear event */
                if (task->event_info & OS_EVENT_OPTION_CLEAR)
                {
                    event->set &= ~task->event_set;
                }

                os_task_resume(task);

                need_schedule = OS_TRUE;
            }
        }
    }

    os_hw_interrupt_enable(level);

    if (OS_TRUE == need_schedule)
    {
        os_schedule();
    }

    return OS_EOK;
}
EXPORT_SYMBOL(os_event_send);

/**
 ***********************************************************************************************************************
 * @brief           This function recieves an event from event object. If there is no interested event has been sent, the
 *                  calling task will be blocked until either interested event is sent by other task or waiting time expires.
 *
 * @param[in]       event           The pointer to a event object.
 * @param[in]       interested_set  The intereseted event set.
 * @param[in]       option          The option of OS_EVENT_OPTION_AND, OS_EVENT_OPTION_OR and OS_EVENT_OPTION_CLEAR.
 * @param[in]       timeout         Waiting time (in clock ticks).
 * @param[out]      recved_set      The actual recieved event set.
 *
 * @return          The operation result.
 * @retval          OS_EOK          If the operation successful.
 * @retval          else            Error code.
 ***********************************************************************************************************************
 */
os_err_t os_event_recv(os_event_t   *event,
                       os_uint32_t  interested_set,
                       os_uint8_t   option,
                       os_tick_t    timeout,
                       os_uint32_t  *recved_set)
{
    os_task_t           *task;
    register os_ubase_t level;
    register os_base_t  status;

    OS_DEBUG_IN_TASK_CONTEXT;

    OS_ASSERT(OS_NULL != event);
    OS_ASSERT(OS_OBJECT_EVENT == os_object_get_type(&event->parent.parent));
    OS_ASSERT((timeout < (OS_TICK_MAX / 2)) || (OS_IPC_WAITING_FOREVER == timeout));

    if (0 == interested_set)
    {
        return OS_ERROR;
    }

    status = OS_ERROR;
    task = os_task_self();
    task->error = OS_EOK;

    OS_OBJECT_HOOK_CALL(gs_os_event_try_recv_hook, (event));

    level = os_hw_interrupt_disable();

    /* Check event set. */
    if (option & OS_EVENT_OPTION_AND)
    {
        if ((event->set & interested_set) == interested_set)
        {
            status = OS_EOK;
        }
    }
    else if (option & OS_EVENT_OPTION_OR)
    {
        if (event->set & interested_set)
        {
            status = OS_EOK;
        }
    }
    else
    {
        /* Either OS_EVENT_FLAG_AND or OS_EVENT_FLAG_OR should be set. */
        OS_ASSERT(0);
    }

    if (OS_EOK == status)
    {
        /* Set received event. */
        if (recved_set)
        {
            *recved_set = (event->set & interested_set);
        }

        /* Received event. */
        if (option & OS_EVENT_OPTION_CLEAR)
        {
            event->set &= ~interested_set;
        }
    }
    else if (OS_IPC_WAITING_NO == timeout)
    {
        task->error = OS_ETIMEOUT;
    }
    else
    {
        /* Fill task event info */
        task->event_set  = interested_set;
        task->event_info = option;

        /* Put task to suspended task list. */
        os_ipc_list_suspend(&(event->parent.suspend_task),
                            task,
                            event->parent.parent.flag);

        /* If there is a waiting timeout, active task timer. */
        if (OS_IPC_WAITING_FOREVER != timeout)
        {
            /* reset the timeout of task timer and start it. */
            os_timer_control(&(task->task_timer),
                             OS_TIMER_CTRL_SET_TIME,
                             &timeout);
            os_timer_start(&(task->task_timer));
        }

        os_hw_interrupt_enable(level);

        os_schedule();

        if (OS_EOK != task->error)
        {
            return task->error;
        }

        level = os_hw_interrupt_disable();

        /* Set received event. */
        if (recved_set)
        {
            *recved_set = task->event_set;
        }
    }

    os_hw_interrupt_enable(level);

    OS_OBJECT_HOOK_CALL(gs_os_event_recv_hook, (event));

    return task->error;
}
EXPORT_SYMBOL(os_event_recv);

/**
 ***********************************************************************************************************************
 * @brief           This function set and get event's attribute.
 *
 * @param[in]       event           The pointer to a event object.
 * @param[in]       cmd             The execution command.
 * @param[in]       arg             The execution argument.
 *
 * @return          The operation result.
 * @retval          OS_EOK          If the operation successful.
 * @retval          else            Error code.
 ***********************************************************************************************************************
 */
os_err_t os_event_control(os_event_t *event, os_ipc_cmd_t cmd, void *arg)
{
    os_ubase_t level;

    OS_ASSERT(OS_NULL != event);
    OS_ASSERT(OS_OBJECT_EVENT == os_object_get_type(&event->parent.parent));

    if (OS_IPC_CMD_RESET == cmd)
    {
        level = os_hw_interrupt_disable();

        /* Resume all waiting task */
        os_ipc_list_resume_all(&event->parent.suspend_task);

        /* Init event set */
        event->set = 0;

        os_hw_interrupt_enable(level);

        os_schedule();

        return OS_EOK;
    }

    return OS_ERROR;
}
EXPORT_SYMBOL(os_event_control);

#ifdef OS_USING_SHELL

#include <shell.h>

static os_err_t list_event_info(struct os_list_node *list)
{
    int maxlen;
    os_event_t *event;
    os_list_node_t *node;
    const char *item_title = "event";

    maxlen = os_object_name_maxlen(item_title, list);

    os_kprintf("%-*.s      set    suspend task\r\n", maxlen, item_title); 
    os_object_split(maxlen);
    os_kprintf(     "  ---------- --------------\r\n");
    for (node = list->next; node != list; node = node->next)
    {
        event = (os_event_t *)(os_list_entry(node, struct os_object, list));
        if (!os_list_empty(&event->parent.suspend_task))
        {
            os_kprintf("%-*.*s  0x%08x %03d:",
                       maxlen,
                       OS_NAME_MAX,
                       event->parent.parent.name,
                       event->set,
                       os_list_len(&event->parent.suspend_task));
            os_ipc_show_waiting_task(&event->parent.suspend_task);
            os_kprintf("\r\n");
        }
        else
        {
            os_kprintf("%-*.*s  0x%08x 0\r\n",
                       maxlen,
                       OS_NAME_MAX,
                       event->parent.parent.name,
                       event->set);
        }
    }

    return OS_EOK;
}

static os_err_t sh_list_event(os_int32_t argc, char **argv)
{
    os_object_info_t *info;

    info = os_object_get_info(OS_OBJECT_EVENT);

    return list_event_info(&info->object_list);
}

SH_CMD_EXPORT(event, sh_list_event, "show event information");
#endif /* OS_USING_SHELL */

#endif /* OS_USING_EVENT */

