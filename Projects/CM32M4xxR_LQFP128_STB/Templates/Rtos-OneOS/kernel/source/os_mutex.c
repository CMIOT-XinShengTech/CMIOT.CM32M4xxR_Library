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
 * @file        os_mutex.c
 *
 * @brief       This file implements the mutex functions.
 *
 * @revision
 * Date         Author          Notes
 * 2020-02-21   OneOS team      First Version
 ***********************************************************************************************************************
 */

#include <os_errno.h>
#include <os_mutex.h>
#include <os_dbg.h>
#include <os_module.h>
#include <os_hw.h>
#include <os_irq.h>

#include "os_kernel_internal.h"

#ifdef OS_USING_MUTEX

#define MUTEX_TAG   "MUTEX"

#ifdef OS_USING_HOOK

static void (*gs_os_mutex_try_lock_hook)(os_mutex_t *mutex) = OS_NULL;

static void (*gs_os_mutex_lock_hook)(os_mutex_t *mutex) = OS_NULL;

static void (*gs_os_mutex_unlock_hook)(os_mutex_t *mutex) = OS_NULL;

/**
 ***********************************************************************************************************************
 * @brief           This function sets a hook called at the beginning of os_mutex_lock() and os_mutex_recursive_lock().
 *
 * @param[in]       hook             The hook function is complemented by user.
 *
 * @return          None.
 ***********************************************************************************************************************
 */
void os_mutex_try_lock_set_hook(void (*hook)(os_mutex_t *mutex))
{
    gs_os_mutex_try_lock_hook = hook;
}

/**
 ***********************************************************************************************************************
 * @brief           This function sets a hook called at the end of os_mutex_lock() and os_mutex_recursive_lock().
 *
 * @param[in]       hook             The hook function is complemented by user.
 *
 * @return          None.
 ***********************************************************************************************************************
 */
void os_mutex_lock_set_hook(void (*hook)(os_mutex_t *mutex))
{
    gs_os_mutex_lock_hook = hook;
}

/**
 ***********************************************************************************************************************
 * @brief           This function sets a hook called at the beginning of os_mutex_unlock() and os_mutex_recursive_unlock().
 *
 * @param[in]       hook             The hook function is complemented by user.
 *
 * @return          None.
 ***********************************************************************************************************************
 */
void os_mutex_unlock_set_hook(void (*hook)(os_mutex_t *mutex))
{
    gs_os_mutex_unlock_hook = hook;
}

#endif /* end OS_USING_HOOK */

/**
 ***********************************************************************************************************************
 * @brief           This function will initlialize a mutex object and put it on object list.
 *
 * @param[in]       mutex           The mutex to initialize.
 * @param[in]       name            The name of mutex.
 * @param[in]       flag            The ipc flag of mutex.
 * @param[in]       recursive       A recursive mutex or not.
 *
 * @return          The operation result.
 * @retval          OS_EOK          If the operation successful.
 * @retval          else            Error code.
 ***********************************************************************************************************************
 */
os_err_t os_mutex_init(os_mutex_t *mutex, const char *name, os_ipc_flag_t flag, os_bool_t recursive)
{
    OS_ASSERT(mutex);

    /* Init base object */
    os_object_init(&mutex->parent.parent, OS_OBJECT_MUTEX, name, OS_TRUE);

    /* Init ipc object */
    os_ipc_object_init(&(mutex->parent));

    mutex->owner              = OS_NULL;
    mutex->original_priority  = 0xFF;
    mutex->nested             = 0;
    mutex->recursive          = recursive;

    /* Set flag */
    mutex->parent.parent.flag = flag;

    return OS_EOK;
}
EXPORT_SYMBOL(os_mutex_init);

/**
 ***********************************************************************************************************************
 * @brief           Deinitialize a mutex object.
 *
 * @param[in]       mutex           The mutex to deinitialize.
 *
 * @return          The operation result.
 * @retval          OS_EOK          If the operation successful.
 * @retval          else            Error code.
 ***********************************************************************************************************************
 */
os_err_t os_mutex_deinit(os_mutex_t *mutex)
{
    OS_ASSERT(OS_NULL != mutex);
    OS_ASSERT(OS_OBJECT_MUTEX == os_object_get_type(&mutex->parent.parent));
    OS_ASSERT(OS_TRUE == os_object_is_static(&mutex->parent.parent));

    os_enter_critical();

    /* Wakeup all suspend tasks */
    os_ipc_list_resume_all(&(mutex->parent.suspend_task));

    /* Deinit base object */
    os_object_deinit(&(mutex->parent.parent));

    os_exit_critical();

    os_schedule();

    return OS_EOK;
}
EXPORT_SYMBOL(os_mutex_deinit);

#ifdef OS_USING_HEAP
/**
 ***********************************************************************************************************************
 * @brief           This function will create a mutex object from heap and put it on object list.
 *
 * @param[in]       name            The name of mutex.
 * @param[in]       value           The init value of mutex.
 * @param[in]       flag            The ipc flag of mutex.
 *
 * @return          The pointer to the created mutex.
 * @retval          pointer         If operation successful.
 * @retval          OS_NULL         Error occurred.
 ***********************************************************************************************************************
 */
os_mutex_t *os_mutex_create(const char *name, os_ipc_flag_t flag, os_bool_t recursive)
{
    os_mutex_t *mutex;

    /* Check context. */
    OS_DEBUG_NOT_IN_INTERRUPT;

    mutex = (os_mutex_t *)OS_KERNEL_MALLOC(sizeof(os_mutex_t));
    if (OS_NULL == mutex)
    {
        OS_KERN_LOG(KERN_ERROR, MUTEX_TAG, "Malloc mutex memory failed");
        return OS_NULL;
    }

    /* Init base object */
    os_object_init(&mutex->parent.parent, OS_OBJECT_MUTEX, name, OS_FALSE);

    /* Init ipc object */
    os_ipc_object_init(&mutex->parent);

    mutex->owner              = OS_NULL;
    mutex->original_priority  = 0xFF;
    mutex->nested             = 0;
    mutex->recursive          = recursive;

    /* Set flag */
    mutex->parent.parent.flag = flag;

    return mutex;
}
EXPORT_SYMBOL(os_mutex_create);

/**
 ***********************************************************************************************************************
 * @brief           Destory a mutex object created from heap.
 *
 * @param[in]       mutex           The mutex to destroy.
 *
 * @return          The operation result.
 * @retval          OS_EOK          If the operation successful.
 * @retval          else            Error code.
 ***********************************************************************************************************************
 */
os_err_t os_mutex_destroy(os_mutex_t *mutex)
{
    OS_ASSERT(OS_NULL != mutex);
    OS_ASSERT(OS_OBJECT_MUTEX == os_object_get_type(&mutex->parent.parent));
    OS_ASSERT(OS_FALSE == os_object_is_static(&mutex->parent.parent));

    os_enter_critical();

    /* Wakeup all suspend tasks */
    os_ipc_list_resume_all(&mutex->parent.suspend_task);

    /* Deinit base object */
    os_object_deinit(&mutex->parent.parent);

    OS_DEBUG_NOT_IN_INTERRUPT;

    /* Delete mutex object */
    OS_KERNEL_FREE(mutex);
    mutex = OS_NULL;

    os_exit_critical();

    os_schedule();

    return OS_EOK;
}
EXPORT_SYMBOL(os_mutex_destroy);
#endif /* OS_USING_HEAP */

/**
 ***********************************************************************************************************************
 * @brief           This function locks a mutex. If the mutex is already locked by other task, the calling task will be blocked
 *                  until either the mutex becomes available or waiting time expires. When mutex is locked multiple times
 *                  by the same task, OS_ASSERT() will detect it.
 *
 * @param[in]       mutex           The pointer to a mutex.
 * @param[in]       timeout         Waitting time (in clock ticks).
 *
 * @return          The operation result.
 * @retval          OS_EOK          If the operation successful.
 * @retval          else            Error code.
 ***********************************************************************************************************************
 */
os_err_t os_mutex_lock(os_mutex_t *mutex, os_tick_t timeout)
{
    register os_base_t temp;
    os_task_t          *task;

    OS_ASSERT(OS_NULL != mutex);
    OS_ASSERT(OS_OBJECT_MUTEX == os_object_get_type(&mutex->parent.parent));
    OS_ASSERT((timeout < (OS_TICK_MAX / 2)) || (OS_IPC_WAITING_FOREVER == timeout));
    OS_ASSERT(OS_FALSE == mutex->recursive );

    /* Program shall run in task context. */
    OS_DEBUG_IN_TASK_CONTEXT;

    /* Get current task */
    task = os_task_self();

    /* Disable interrupt */
    temp = os_hw_interrupt_disable();

    OS_OBJECT_HOOK_CALL(gs_os_mutex_try_lock_hook, (mutex));

    OS_KERN_LOG(KERN_DEBUG, MUTEX_TAG, "mutex_lock: current task %s, nested: %d",
                ((os_object_t *)task)->name,
                mutex->nested);

    /* Reset task error */
    task->error = OS_EOK;

    OS_ASSERT(mutex->owner != task);

__again:
    if (OS_NULL == mutex->owner)
    {
        /* Set mutex owner and original priority */
        mutex->owner             = task;
        mutex->original_priority = task->current_priority;

        os_hw_interrupt_enable(temp);
    }
    else
    {
        /* Return OS_EBUSY imediately when waitting time is 0 */
        if (OS_IPC_WAITING_NO == timeout)
        {
            /* Set error as OS_EBUSY */
            task->error = OS_EBUSY;

            os_hw_interrupt_enable(temp);

            return OS_EBUSY;
        }
        else
        {
            /* Mutex is unavailable, put current task on suspend list */
            OS_KERN_LOG(KERN_DEBUG, MUTEX_TAG, "mutex_lock: suspend task: %s",
                        ((os_object_t *)task)->name);

            /* Change the owner task priority of mutex */
            if (task->current_priority < mutex->owner->current_priority)
            {
                /* Change the owner task priority */
                os_task_control(mutex->owner,
                                OS_TASK_CTRL_CHANGE_PRIORITY,
                                &task->current_priority);
            }

            /* Suspend current task */
            os_ipc_list_suspend(&(mutex->parent.suspend_task),
                                task,
                                mutex->parent.parent.flag);

            /* Start task timer */
            if (OS_IPC_WAITING_FOREVER != timeout)
            {
                OS_KERN_LOG(KERN_DEBUG, MUTEX_TAG, "mutex_lock: start the timer of task:%s",
                            ((os_object_t *)task)->name);

                /* Reset the timeout of task timer and start it */
                os_timer_control(&(task->task_timer),
                                 OS_TIMER_CTRL_SET_TIME,
                                 &timeout);
                os_timer_start(&(task->task_timer));
            }

            os_hw_interrupt_enable(temp);

            os_schedule();

            if (OS_EOK != task->error)
            {
                /* Interrupt by signal, try it again */
                if (OS_EINTR == task->error) 
                {
                    temp = os_hw_interrupt_disable();
                    goto __again;
                }

                /* Return error */
                return task->error;
            }
        }
    }

    OS_OBJECT_HOOK_CALL(gs_os_mutex_lock_hook, (mutex));

    return OS_EOK;
}
EXPORT_SYMBOL(os_mutex_lock);

/**
 ***********************************************************************************************************************
 * @brief           This function unlocks a mutex. If there are tasks blocked on the mutex, one of them, decided by os_ipc_flag,
 *                  will be woken up and aqcuire the mutex. When mutex is unlocked multiple times by the same task, OS_ASSERT()
 *                  will detect it.
 *
 * @param[in]       mutex           The pointer to a mutex.
 *
 * @return          The operation result.
 * @retval          OS_EOK          If the operation successful.
 * @retval          else            Error code.
 ***********************************************************************************************************************
 */
os_err_t os_mutex_unlock(os_mutex_t *mutex)
{
    register os_base_t temp;
    struct os_task     *task;
    os_bool_t          need_schedule;

    OS_ASSERT(OS_NULL != mutex);
    OS_ASSERT(OS_OBJECT_MUTEX == os_object_get_type(&mutex->parent.parent));
    OS_ASSERT(OS_FALSE == mutex->recursive);

    need_schedule = OS_FALSE;

    /* Program shall run in task context, otherwise we cannot get right current task. */
    OS_DEBUG_IN_TASK_CONTEXT;

    task = os_task_self();

    temp = os_hw_interrupt_disable();

    OS_KERN_LOG(KERN_DEBUG, MUTEX_TAG, "mutex_unlock:current task %s, nested: %d",
                ((os_object_t *)task)->name, mutex->nested);

    OS_OBJECT_HOOK_CALL(gs_os_mutex_unlock_hook, (mutex));

    /* Mutex only can be unlocked by owner */
    OS_ASSERT(task == mutex->owner);

    /* Set the ower's priority back */
    if (mutex->original_priority != mutex->owner->current_priority)
    {
        os_task_control(mutex->owner,
                        OS_TASK_CTRL_CHANGE_PRIORITY,
                        &(mutex->original_priority));
    }

    /* Wakeup suspended task */
    if (!os_list_empty(&mutex->parent.suspend_task))
    {
        task = os_list_entry(mutex->parent.suspend_task.next, struct os_task, task_list);

        OS_KERN_LOG(KERN_DEBUG, MUTEX_TAG, "mutex_unlock: resume task: %s",
                    ((os_object_t *)task)->name);

        /* Set new owner and priority */
        mutex->owner             = task;
        mutex->original_priority = task->current_priority;

        /* Resume task */
        os_ipc_list_resume(&(mutex->parent.suspend_task));

        need_schedule = OS_TRUE;
    }
    else
    {
        /* Clear owner */
        mutex->owner             = OS_NULL;
        mutex->original_priority = 0xff;
    }

    os_hw_interrupt_enable(temp);

    if (OS_TRUE == need_schedule)
    {
        os_schedule();
    }

    return OS_EOK;
}
EXPORT_SYMBOL(os_mutex_unlock);

/**
 ***********************************************************************************************************************
 * @brief           This function recursively locks a mutex and the increments it's nested count. If the mutex is already
 *                  locked by other task, the calling task will block until either the mutex becomes available or waiting
 *                  time expires. In contrast to os_mutex_lock(), it's ok to lock a mutex multiple times.
 *
 * @param[in]       mutex           The pointer to a mutex.
 * @param[in]       timeout         Waitting time (in clock ticks).
 *
 * @return          The operation result.
 * @retval          OS_EOK          If the operation successful.
 * @retval          else            Error code.
 ***********************************************************************************************************************
 */
os_err_t os_mutex_recursive_lock(os_mutex_t *mutex, os_tick_t timeout)
{
    register os_base_t temp;
    os_task_t          *task;

    OS_ASSERT(OS_NULL != mutex);
    OS_ASSERT(OS_OBJECT_MUTEX == os_object_get_type(&mutex->parent.parent));
    OS_ASSERT((timeout < (OS_TICK_MAX / 2)) || (OS_IPC_WAITING_FOREVER == timeout));
    OS_ASSERT(OS_TRUE == mutex->recursive);

    /* Program shall run in task context */
    OS_DEBUG_IN_TASK_CONTEXT;

    task = os_task_self();

    temp = os_hw_interrupt_disable();

    OS_OBJECT_HOOK_CALL(gs_os_mutex_try_lock_hook, (mutex));

    OS_KERN_LOG(KERN_DEBUG, MUTEX_TAG, "mutex_recursive_lock: current task %s, nested: %d",
                ((os_object_t *)task)->name, mutex->nested);

    /* Reset task error */
    task->error = OS_EOK;

    if (mutex->owner == task)
    {
        /* The same task, increment the nested count */
        mutex->nested ++;

        os_hw_interrupt_enable(temp);
    }
    else
    {
__again:
        if (OS_NULL == mutex->owner)
        {
            /* Set mutex owner and original priority */
            mutex->owner             = task;
            mutex->original_priority = task->current_priority;
            mutex->nested ++;

            os_hw_interrupt_enable(temp);
        }
        else
        {
            /* Return OS_EBUSY imediately when waitting time is 0 */
            if (OS_IPC_WAITING_NO == timeout)
            {
                /* Set error as OS_EBUSY */
                task->error = OS_EBUSY;

                os_hw_interrupt_enable(temp);

                return OS_EBUSY;
            }
            else
            {
                /* Mutex is unavailable, put current task on suspend list */
                OS_KERN_LOG(KERN_DEBUG, MUTEX_TAG, "mutex_recursive_lock: suspend task: %s",
                            ((os_object_t *)task)->name);

                if (task->current_priority < mutex->owner->current_priority)
                {
                    /* Change the owner task priority */
                    os_task_control(mutex->owner,
                                    OS_TASK_CTRL_CHANGE_PRIORITY,
                                    &task->current_priority);
                }

                /* Suspend current task */
                os_ipc_list_suspend(&(mutex->parent.suspend_task),
                                    task,
                                    mutex->parent.parent.flag);

                /* Start task timer */
                if (OS_IPC_WAITING_FOREVER != timeout)
                {
                    OS_KERN_LOG(KERN_DEBUG, MUTEX_TAG, "mutex_recursive_lock: start the timer of task:%s",
                                ((os_object_t *)task)->name);

                    /* Reset the timeout of task timer and start it */
                    os_timer_control(&(task->task_timer),
                                     OS_TIMER_CTRL_SET_TIME,
                                     &timeout);
                    os_timer_start(&(task->task_timer));
                }

                os_hw_interrupt_enable(temp);

                os_schedule();

                if (OS_EOK != task->error)
                {
                    /* interrupt by signal, try it again */
                    if (OS_EINTR == task->error)
                    {
                        temp = os_hw_interrupt_disable();
                        goto __again;
                    }

                    return task->error;
                }
            }
        }
    }

    OS_OBJECT_HOOK_CALL(gs_os_mutex_lock_hook, (mutex));

    return OS_EOK;
}
EXPORT_SYMBOL(os_mutex_recursive_lock);

/**
 ***********************************************************************************************************************
 * @brief           This function recursively unlocks a mutex and decrements it's nested count. If the nested count is 0
 *                  and there are tasks blocked on the mutex, one of them, decided by os_ipc_flag, will be woken up and
 *                  aqcuire the mutex. In contrast to os_mutex_unlock(), it's ok to unlock a mutex multiple times.
 *
 * @param[in]       mutex           The pointer to a mutex.
 *
 * @return          The operation result.
 * @retval          OS_EOK          If the operation successful.
 * @retval          else            Error code.
 ***********************************************************************************************************************
 */
os_err_t os_mutex_recursive_unlock(os_mutex_t *mutex)
{
    register os_base_t temp;
    struct os_task   *task;
    os_bool_t          need_schedule;

    /* parameter check */
    OS_ASSERT(OS_NULL != mutex);
    OS_ASSERT(OS_OBJECT_MUTEX == os_object_get_type(&mutex->parent.parent));
    OS_ASSERT(OS_TRUE == mutex->recursive);

    need_schedule = OS_FALSE;

    /* Program shall run in task context, otherwise we cannot get right current task. */
    OS_DEBUG_IN_TASK_CONTEXT;

    task = os_task_self();

    temp = os_hw_interrupt_disable();

    OS_KERN_LOG(KERN_DEBUG, MUTEX_TAG, "mutex_recursive_unlock:current task %s, nested: %d",
                ((os_object_t *)task)->name, mutex->nested);

    OS_OBJECT_HOOK_CALL(gs_os_mutex_unlock_hook, (mutex));

    /* Mutex only can be unlocked by owner */
    if (task != mutex->owner)
    {
        task->error = OS_ERROR;

        os_hw_interrupt_enable(temp);

        return OS_ERROR;
    }

    /* Decrement nested count */
    mutex->nested --;
    /* If no owner */
    if (0 == mutex->nested)
    {
        /* Change the owner task to original priority */
        if (mutex->original_priority != mutex->owner->current_priority)
        {
            os_task_control(mutex->owner,
                            OS_TASK_CTRL_CHANGE_PRIORITY,
                            &(mutex->original_priority));
        }

        /* Wakeup suspended task */
        if (!os_list_empty(&mutex->parent.suspend_task))
        {
            /* get suspended task */
            task = os_list_entry(mutex->parent.suspend_task.next,
                                   struct os_task,
                                   task_list);

            OS_KERN_LOG(KERN_DEBUG, MUTEX_TAG, "mutex_recursive_unlock: resume task: %s",
                        ((os_object_t *)task)->name);

            /* Set new owner and priority */
            mutex->owner             = task;
            mutex->original_priority = task->current_priority;
            mutex->nested ++;

            /* Resume task */
            os_ipc_list_resume(&(mutex->parent.suspend_task));

            need_schedule = OS_TRUE;
        }
        else
        {
            /* Clear owner */
            mutex->owner             = OS_NULL;
            mutex->original_priority = 0xff;
        }
    }

    os_hw_interrupt_enable(temp);

    if (OS_TRUE == need_schedule)
    {
        os_schedule();
    }

    return OS_EOK;
}
EXPORT_SYMBOL(os_mutex_recursive_unlock);

/**
 ***********************************************************************************************************************
 * @brief           This function set and get mutex's attribute.
 *
 * @param[in]       mutex           The pointer to a mutex.
 * @param[in]       cmd             The execution command.
 * @param[in]       arg             The execution argument.
 *
 * @return          The operation result.
 * @retval          OS_EOK          If the operation successful.
 * @retval          else            Error code.
 ***********************************************************************************************************************
 */
os_err_t os_mutex_control(os_mutex_t *mutex, os_ipc_cmd_t cmd, void *arg)
{
    /* parameter check */
    OS_ASSERT(OS_NULL != mutex);
    OS_ASSERT(OS_OBJECT_MUTEX == os_object_get_type(&mutex->parent.parent));

    return OS_ERROR;
}
EXPORT_SYMBOL(os_mutex_control);

#ifdef OS_USING_SHELL

#include <shell.h>

static os_err_t list_mutex_info(struct os_list_node *list)
{
    int maxlen;
    os_mutex_t *mutex;
    os_list_node_t *node;
    const char *item_title = "mutex";

    maxlen = os_object_name_maxlen(item_title, list);

    os_kprintf("%-*.s  owner   hold suspend task\r\n", maxlen, item_title);
    os_object_split(maxlen);
    os_kprintf(     " -------- ---- --------------\r\n");

    for (node = list->next; node != list; node = node->next)
    {
        mutex = (os_mutex_t *)(os_list_entry(node, os_object_t, list));
        os_kprintf("%-*.*s %-8.*s %04d %d\r\n",
                   maxlen,
                   OS_NAME_MAX,
                   mutex->parent.parent.name,
                   OS_NAME_MAX,
                   mutex->owner->parent.name,
                   mutex->nested,
                   os_list_len(&mutex->parent.suspend_task));
    }

    return OS_EOK;
}

static os_err_t sh_list_mutex(os_int32_t argc, char **argv)
{
    os_object_info_t *info;

    info = os_object_get_info(OS_OBJECT_MUTEX);

    return list_mutex_info(&info->object_list);
}

SH_CMD_EXPORT(mutex, sh_list_mutex, "show mutex information");
#endif /* OS_USING_SHELL */

#endif /* OS_USING_MUTEX */

