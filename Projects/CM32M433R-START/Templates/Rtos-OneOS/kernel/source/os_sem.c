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
 * @file        os_sem.c
 *
 * @brief       This file implements the semaphore functions.
 *
 * @revision
 * Date         Author          Notes
 * 2020-02-11   OneOS team      First Version
 ***********************************************************************************************************************
 */

#include <os_sem.h>
#include <os_errno.h>
#include <os_dbg.h>
#include <os_module.h>
#include <os_hw.h>
#include <os_irq.h>

#include "os_kernel_internal.h"

#ifdef OS_USING_SEMAPHORE

#define SEM_TAG             "SEM"

#ifdef OS_USING_HOOK

static void (*gs_os_sem_try_wait_hook)(os_sem_t *sem) = OS_NULL;

static void (*gs_os_sem_wait_hook)(os_sem_t *sem) = OS_NULL;

static void (*gs_os_sem_post_hook)(os_sem_t *sem) = OS_NULL;

/**
 ***********************************************************************************************************************
 * @brief           This function sets a hook called at the beginning of os_sem_wait().
 *
 * @param[in]       hook             The hook function is complemented by user.
 *
 * @return          None.
 ***********************************************************************************************************************
 */
void os_sem_try_wait_set_hook(void (*hook)(os_sem_t *sem))
{
    gs_os_sem_try_wait_hook = hook;
}

/**
 ***********************************************************************************************************************
 * @brief           This function sets a hook called at the end of os_sem_wait().
 *
 * @param[in]       hook             The hook function is complemented by user.
 *
 * @return          None.
 ***********************************************************************************************************************
 */
void os_sem_wait_set_hook(void (*hook)(os_sem_t *sem))
{
    gs_os_sem_wait_hook = hook;
}

/**
 ***********************************************************************************************************************
 * @brief           This function sets a hook called in os_sem_pos().
 *
 * @param[in]       hook             The hook function is complemented by user.
 *
 * @return          None.
 ***********************************************************************************************************************
 */
void os_sem_post_set_hook(void (*hook)(os_sem_t *sem))
{
    gs_os_sem_post_hook = hook;
}

#endif /* end OS_USING_HOOK */

/**
 ***********************************************************************************************************************
 * @brief           This function will initlialize a semaphore object and put it on object list.
 *
 * @param[in]       sem             The semaphore to initialize.
 * @param[in]       name            The name of semaphore.
 * @param[in]       value           The init value of semaphore.
 * @param[in]       flag            The ipc flag of semaphore.
 *
 * @return          The operation result.
 * @retval          OS_EOK          If the operation successful.
 * @retval          else            Error code.
 ***********************************************************************************************************************
 */
os_err_t os_sem_init(os_sem_t *sem, const char *name, os_uint16_t value, os_ipc_flag_t flag)
{
    OS_ASSERT(sem);

    /* Init base object */
    os_object_init(&sem->parent.parent, OS_OBJECT_SEMAPHORE, name, OS_TRUE);

    /* Init ipc object */
    os_ipc_object_init(&(sem->parent));

    /* Set init count */
    sem->count = value;

    /* Set parent */
    sem->parent.parent.flag = flag;

    return OS_EOK;
}
EXPORT_SYMBOL(os_sem_init);

/**
 ***********************************************************************************************************************
 * @brief           Deinitialize a semaphore object.
 *
 * @param[in]       sem             The semaphore to deinitialize.
 *
 * @return          The operation result.
 * @retval          OS_EOK          If the operation successful.
 * @retval          else            Error code.
 ***********************************************************************************************************************
 */
os_err_t os_sem_deinit(os_sem_t *sem)
{
    OS_ASSERT(OS_NULL != sem);
    OS_ASSERT(OS_OBJECT_SEMAPHORE == os_object_get_type(&sem->parent.parent));
    OS_ASSERT(OS_TRUE == os_object_is_static(&sem->parent.parent));

    os_enter_critical();
    
    /* Wakeup all suspend tasks */
    os_ipc_list_resume_all(&(sem->parent.suspend_task));
    
    /* Deinit base object */
    os_object_deinit(&(sem->parent.parent));

    os_exit_critical();
    
    os_schedule();

    return OS_EOK;
}
EXPORT_SYMBOL(os_sem_deinit);

#ifdef OS_USING_HEAP
/**
 ***********************************************************************************************************************
 * @brief           This function will create a semaphore object from heap and put it on object list.
 *
 * @param[in]       name            The name of semaphore.
 * @param[in]       value           The init value of semaphore.
 * @param[in]       flag            The ipc flag of semaphore.
 *
 * @return          The pointer to the created semaphore.
 * @retval          pointer         If operation successful.
 * @retval          OS_NULL         Error occurred.
 ***********************************************************************************************************************
 */
os_sem_t *os_sem_create(const char *name, os_uint16_t value, os_ipc_flag_t flag)
{
    os_sem_t *sem;

    OS_DEBUG_NOT_IN_INTERRUPT;

    /* Allocate object */
    sem = (os_sem_t *)OS_KERNEL_MALLOC(sizeof(os_sem_t));
    if (OS_NULL == sem)
    {
        OS_KERN_LOG(KERN_ERROR, SEM_TAG, "Malloc sem memory failed");
        return OS_NULL;
    }

    /* Init base object */
    os_object_init(&sem->parent.parent, OS_OBJECT_SEMAPHORE, name, OS_FALSE);

    /* Init ipc object */
    os_ipc_object_init(&sem->parent);

    /* Set init count */
    sem->count = value;

    /* Set parent */
    sem->parent.parent.flag = flag;

    return sem;
}
EXPORT_SYMBOL(os_sem_create);

/**
 ***********************************************************************************************************************
 * @brief           Destory a semaphore object created from heap.
 *
 * @param[in]       sem             The semaphore to destroy.
 *
 * @return          The operation result.
 * @retval          OS_EOK          If the operation successful.
 * @retval          else            Error code.
 ***********************************************************************************************************************
 */
os_err_t os_sem_destroy(os_sem_t *sem)
{
    OS_ASSERT(OS_NULL != sem);
    OS_ASSERT(OS_OBJECT_SEMAPHORE == os_object_get_type(&sem->parent.parent));
    OS_ASSERT(OS_FALSE == os_object_is_static(&sem->parent.parent));

    os_enter_critical();

    /* Wakeup all suspend tasks */
    os_ipc_list_resume_all(&sem->parent.suspend_task);

    /* Deinit base object */
    os_object_deinit(&sem->parent.parent);

    OS_DEBUG_NOT_IN_INTERRUPT;

    /* Free semaphore object */
    OS_KERNEL_FREE(sem);
    sem = OS_NULL;

    os_exit_critical();

    os_schedule();

    return OS_EOK;
}
EXPORT_SYMBOL(os_sem_destroy);
#endif

/**
 ***********************************************************************************************************************
 * @brief           This function decrements the semaphore's count. If the semaphore's count greater than 0, the function
 *                  decrements semaphore's count and returns immediately. Otherwise, the calling task blocks until either
 *                  the semaphore's count greater than 0 or waiting time expires.
 *
 * @param[in]       sem             The pointer to a semaphore.
 * @param[in]       timeout         Waitting time (in clock ticks).
 *
 * @return          The operation result.
 * @retval          OS_EOK          If the operation successful.
 * @retval          else            Error code.
 ***********************************************************************************************************************
 */
os_err_t os_sem_wait(os_sem_t *sem, os_tick_t timeout)
{
    register os_base_t temp;
    struct os_task     *task;

    OS_ASSERT(OS_NULL != sem);
    OS_ASSERT(OS_OBJECT_SEMAPHORE == os_object_get_type(&sem->parent.parent));
    OS_ASSERT((timeout < (OS_TICK_MAX / 2)) || (OS_IPC_WAITING_FOREVER == timeout));

    OS_OBJECT_HOOK_CALL(gs_os_sem_try_wait_hook, (sem));

    temp = os_hw_interrupt_disable();

    OS_KERN_LOG(KERN_DEBUG, SEM_TAG, "task %s take sem:%s, which count is: %d",
                ((os_object_t *)os_task_self())->name,
                ((os_object_t *)sem)->name,
                sem->count);

    if (sem->count> 0)
    {
        /* Semaphore is available, decrement count.*/
        sem->count--;

        os_hw_interrupt_enable(temp);
    }
    else
    {
        /* Return OS_EBUSY imediately when waitting time is 0 */
        if (timeout == OS_IPC_WAITING_NO)
        {
            os_hw_interrupt_enable(temp);

            return OS_EBUSY;
        }
        else
        {
            /* Program shall run in task context. */
            OS_DEBUG_IN_TASK_CONTEXT;

            /* Semaphore is unavailable, put current task on suspend list. */
            task = os_task_self();

            /* Reset task error number. */
            task->error = OS_EOK;

            OS_KERN_LOG(KERN_DEBUG, SEM_TAG, "sem take: suspend task - %s",
                        ((os_object_t *)task)->name);

            /* Suspend task */
            os_ipc_list_suspend(&(sem->parent.suspend_task),
                                task,
                                sem->parent.parent.flag);

            /* Start task timer. */
            if (OS_IPC_WAITING_FOREVER != timeout)
            {
                OS_KERN_LOG(KERN_DEBUG, SEM_TAG, "set task:%s to timer list",
                            ((os_object_t *)task)->name);

                /* reset the timeout of task timer and start it */
                os_timer_control(&(task->task_timer),
                                 OS_TIMER_CTRL_SET_TIME,
                                 &timeout);
                os_timer_start(&(task->task_timer));
            }

            os_hw_interrupt_enable(temp);

            os_schedule();

            if (OS_EOK != task->error)
            {
                return task->error;
            }
        }
    }

    OS_OBJECT_HOOK_CALL(gs_os_sem_wait_hook, (sem));

    return OS_EOK;
}
EXPORT_SYMBOL(os_sem_wait);

/**
 ***********************************************************************************************************************
 * @brief           This function increments the semaphore's count. If the semaphore's count becomes greater than 0. A
 *                  task blocked on it will be woken up.
 *
 * @param[in]       sem             The pointer to a semaphore.
 *
 * @return          The operation result.
 * @retval          OS_EOK          If the operation successful.
 * @retval          else            Error code.
 ***********************************************************************************************************************
 */
os_err_t os_sem_post(os_sem_t *sem)
{
    register os_base_t temp;
    register os_bool_t need_schedule;

    OS_ASSERT(OS_NULL != sem);
    OS_ASSERT(OS_OBJECT_SEMAPHORE == os_object_get_type(&sem->parent.parent));

    OS_OBJECT_HOOK_CALL(gs_os_sem_post_hook, (sem));

    need_schedule = OS_FALSE;

    temp = os_hw_interrupt_disable();

    OS_KERN_LOG(KERN_DEBUG, SEM_TAG, "task %s post sem:%s, which count is: %d",
                ((os_object_t *)os_task_self())->name,
                ((os_object_t *)sem)->name,
                sem->count);

    /* Resume the suspended task */
    if (!os_list_empty(&sem->parent.suspend_task))
    {
        os_ipc_list_resume(&(sem->parent.suspend_task));
        need_schedule = OS_TRUE;
    }
    else
    {
        /* Increment count */
        sem->count++;
    }

    os_hw_interrupt_enable(temp);

    if (OS_TRUE == need_schedule)
    {
        os_schedule();
    }

    return OS_EOK;
}
EXPORT_SYMBOL(os_sem_post);

/**
 ***********************************************************************************************************************
 * @brief           This function set and get semaphore's attribute.
 *
 * @param[in]       sem             The pointer to a semaphore.
 * @param[in]       cmd             The execution command.
 * @param[in]       arg             The execution argument.
 *
 * @return          The operation result.
 * @retval          OS_EOK          If the operation successful.
 * @retval          else            Error code.
 ***********************************************************************************************************************
 */
os_err_t os_sem_control(os_sem_t *sem, os_ipc_cmd_t cmd, void *arg)
{
    os_ubase_t level;

    OS_ASSERT(OS_NULL != sem);
    OS_ASSERT(OS_OBJECT_SEMAPHORE == os_object_get_type(&sem->parent.parent));

    if (OS_IPC_CMD_RESET == cmd)
    {
        level = os_hw_interrupt_disable();

        /* Resume all waiting task. */
        os_ipc_list_resume_all(&sem->parent.suspend_task);

        /* Set new count */
        sem->count= *(os_uint16_t *)arg;

        os_hw_interrupt_enable(level);

        os_schedule();

        return OS_EOK;
    }

    return OS_ERROR;
}
EXPORT_SYMBOL(os_sem_control);

#ifdef OS_USING_SHELL

#include <shell.h>

static os_err_t list_sem_info(struct os_list_node *list)
{
    int maxlen;
    os_sem_t *sem;
    os_list_node_t *node;
    const char *item_title = "semaphore";

    maxlen = os_object_name_maxlen(item_title, list);

    os_kprintf("%-*.s value suspend task\r\n", maxlen, item_title);
    os_object_split(maxlen);
    os_kprintf(     " ----- ------------\r\n");

    for (node = list->next; node != list; node = node->next)
    {
        sem = (os_sem_t *)(os_list_entry(node, os_object_t, list));
        if (!os_list_empty(&sem->parent.suspend_task))
        {
            os_kprintf("%-*.*s %05d %d:",
                       maxlen,
                       OS_NAME_MAX,
                       sem->parent.parent.name,
                       sem->count,
                       os_list_len(&sem->parent.suspend_task));
            os_ipc_show_waiting_task(&sem->parent.suspend_task);
            os_kprintf("\r\n");
        }
        else
        {
            os_kprintf("%-*.*s %05d %d\r\n",
                       maxlen, 
                       OS_NAME_MAX,
                       sem->parent.parent.name,
                       sem->count,
                       os_list_len(&sem->parent.suspend_task));
        }
    }

    return OS_EOK;
}

static os_err_t sh_list_sem(os_int32_t argc, char **argv)
{
    os_object_info_t *info;

    info = os_object_get_info(OS_OBJECT_SEMAPHORE);

    return list_sem_info(&info->object_list);
}

SH_CMD_EXPORT(sem, sh_list_sem, "show semaphore information");
#endif /* OS_USING_SHELL */

#endif /* OS_USING_SEMAPHORE */
