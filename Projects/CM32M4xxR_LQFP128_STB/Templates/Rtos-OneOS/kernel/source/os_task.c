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
 * @file        os_task.c
 *
 * @brief       This file implements the task functions.
 *
 * @revision
 * Date         Author          Notes
 * 2020-02-18   OneOS Team      First Version
 ***********************************************************************************************************************
 */
#include <os_task.h>
#include <os_clock.h>
#include <os_errno.h>
#include <os_module.h>
#include <os_hw.h>
#include <os_task.h>
#include "os_kernel_internal.h"
#include "os_util_internal.h"

#define TASK_TAG            "TASK"

/* It is used to interrupt context or scheduler is not start record error code.*/
static volatile os_int32_t gs_os_errno;

/* Define the global lock scheduler variable. If this is non-zero, scheduler is
   locked. It is used to prevent task schedule. */
static os_int16_t gs_os_scheduler_lock_nest = 0;

/* Define the global task priority ready table variable.It is used to record all ready task.*/
static os_list_node_t gs_os_task_priority_table[OS_TASK_PRIORITY_MAX];

/* Current running task. */
static os_task_t      *gs_os_current_task;

/* Define global variables related to bitmaps.*/
#if OS_TASK_PRIORITY_MAX > 32
/* Maximum priority level, 256 */
static os_uint32_t gs_os_task_ready_priority_group;
static os_uint8_t  gs_os_task_ready_table[32];
#else
/* Maximum priority level, 32 */
static os_uint32_t gs_os_task_ready_priority_group;
#endif

/* Define the global defunct task list variables. */
os_list_node_t g_os_task_defunct;

extern volatile os_uint8_t g_os_interrupt_nest;


void os_task_timeout(void *parameter);
void os_schedule_insert_task(os_task_t *task);
void os_schedule_remove_task(os_task_t *task);

#ifdef OS_USING_HOOK

static void (*gs_os_task_suspend_hook) (os_task_t *task) = OS_NULL;
static void (*gs_os_task_resume_hook) (os_task_t *task) = OS_NULL;
static void (*gs_os_task_inited_hook) (os_task_t *task) = OS_NULL;
static void (*gs_os_scheduler_hook)(os_task_t *from, os_task_t *to) = OS_NULL;

/**
 ***********************************************************************************************************************
 * @brief           This function sets a hook function called at the end of os_task_suspend.
 *
 * @param[in]       hook            The hook function is complemented by user.
 *
 * @return          None
 ***********************************************************************************************************************
 */
void os_task_suspend_set_hook(void (*hook)(os_task_t *task))
{
    gs_os_task_suspend_hook = hook;
}

/**
 ***********************************************************************************************************************
 * @brief           This function sets a hook function called at the end of os_task_resume.
 *
 * @param[in]       hook            The hook function is complemented by user.
 *
 * @return          None
 ***********************************************************************************************************************
 */
void os_task_resume_set_hook(void (*hook)(os_task_t *task))
{
    gs_os_task_resume_hook = hook;
}

/**
 ***********************************************************************************************************************
 * @brief           This function sets a hook function called at the beginning of os_task_init.
 *
 * @param[in]       hook            The hook function is complemented by user.
 *
 * @return          None
 ***********************************************************************************************************************
 */
void os_task_inited_set_hook(void (*hook)(os_task_t *task))
{
    gs_os_task_inited_hook = hook;
}

/**
 ***********************************************************************************************************************
 * @brief           This function sets a hook function called at the before task switch.
 *
 * @param[in]       hook            The hook function is complemented by user.
 *
 * @return          None
 ***********************************************************************************************************************
 */
void os_scheduler_set_hook(void (*hook)(os_task_t *from, os_task_t *to))
{
    gs_os_scheduler_hook = hook;
}

#endif

/**
 ***********************************************************************************************************************
 * @brief           This function return number of last error.
 *
 * @details         When in the task context return the error of current task,otherwise return "gs_os_errno"
 
 * @param           None.
 *
 * @return          Return system error number.
 ***********************************************************************************************************************
 */
os_err_t os_get_errno(void)
{
    os_task_t *task;

    /* It's in interrupt context. */
    if (0 != os_interrupt_get_nest())
    {
        
        return gs_os_errno;
    }

    /* The schduler is not start. */
    task = gs_os_current_task;
    if (OS_NULL == task)
    {
        return gs_os_errno;
    }

    /* It's in task context. */
    return task->error;
}
EXPORT_SYMBOL(os_get_errno);

/**
 ***********************************************************************************************************************
 * @brief           This function will set number of last error.
 *
 * @details         When in the task context set the error of current task,otherwise set "gs_os_errno".
 
 * @param[in]       error           The value of error code.
 *
 * @return          None.
 ***********************************************************************************************************************
 */
void os_set_errno(os_err_t error)
{
    os_task_t *task;

    /* It's in interrupt context. */
    if (0 != os_interrupt_get_nest())
    {
        gs_os_errno = error;

        return;
    }

    /* The schduler is not start. */
    task = gs_os_current_task;
    if (OS_NULL == task)
    {
        gs_os_errno = error;

        return;
    }

    /* It's in task context. */
    task->error = error;
}
EXPORT_SYMBOL(os_set_errno);

/**
 ***********************************************************************************************************************
 * @brief           This function will return the pointer of the last error number.
 *
 * @details         When in the task context use the error of current task,otherwise use "gs_os_errno".
 
 * @param           None.
 *
 * @return          The pointer of the last error number.
 ***********************************************************************************************************************
 */
os_int32_t *os_errno(void)
{
    os_task_t *task;

    /* It's in task context. */
    if (0 != os_interrupt_get_nest())
    {
        return (os_int32_t *)&gs_os_errno;
    }

    /* It's in task context. */
    task = gs_os_current_task;
    if (OS_NULL != task)
    {
        return (os_int32_t *)&task->error;
    }

    /* The schduler is not start. */
    return (os_int32_t *)&gs_os_errno;
}
EXPORT_SYMBOL(os_errno);

/**
 ***********************************************************************************************************************
 * @brief           This function return the currently running task descriptor.
 *
 * @param           None.
 *
 * @return          The currently running task descriptor.
 ***********************************************************************************************************************
 */
os_task_t *os_task_self(void)
{
    return gs_os_current_task;
}
EXPORT_SYMBOL(os_task_self);

/**
 ***********************************************************************************************************************
 * @brief           This function will return the task name.
 *
 * @param[in]       The task descriptor.
 *
 * @return          The task name.
 ***********************************************************************************************************************
 */
char *os_task_name(os_task_t *task)
{
    OS_ASSERT(task);

    return task->parent.name;
}
EXPORT_SYMBOL(os_task_name);

/**
 ***********************************************************************************************************************
 * @brief           This function handles application task exit.
 *
 * @param           None.
 *
 * @return          None.
 ***********************************************************************************************************************
 */
void os_task_exit(void)
{
    os_task_t *task;
    register os_base_t level;

    /* Get current task. */
    task = gs_os_current_task;

    level = os_hw_interrupt_disable();

    /* Remove from schedule. */
    os_schedule_remove_task(task);

    /* Change stat. */
    task->stat = OS_TASK_CLOSE;

    /* Remove it from timer list. */
    (void)os_timer_deinit(&task->task_timer);

    if (OS_TRUE == (os_object_is_static((os_object_t *)task)) && (OS_NULL == task->cleanup))
    {
        os_object_deinit((os_object_t *)task);
    }
    else
    {
        /* Place it on defunct task list. */
        os_list_add(&g_os_task_defunct, &task->task_list);
    }

    os_hw_interrupt_enable(level);

    /* Switch to next task. */
    os_schedule();
}

static os_err_t os_task_do_init(os_task_t    *task,
                                const char   *name,
                                void        (*entry)(void *parameter),
                                void         *parameter,
                                void         *stack_start,
                                os_uint32_t   stack_size,
                                os_uint8_t    priority,
                                os_uint32_t   tick)
{
    /* Initialize task list. */
    os_list_init(&task->task_list);

    task->entry = (void *)entry;
    task->parameter = parameter;

    /* Initialize stack. */
    task->stack_addr = stack_start;
    task->stack_size = stack_size;

    /* Initialize stack data to '#' */
    os_memset(task->stack_addr, '#', task->stack_size);
    
#ifdef ARCH_CPU_STACK_GROWS_UPWARD
    task->sp = (void *)os_hw_stack_init(task->entry,
                                        task->parameter,
                                        (void *)((char *)task->stack_addr),
                                        (void *)os_task_exit);
#else
    task->sp = (void *)os_hw_stack_init(task->entry,
                                        task->parameter,
                                        (void *)((char *)task->stack_addr + task->stack_size - 4),
                                        (void *)os_task_exit);
#endif

    /* Initialize task priority. */
    OS_ASSERT(priority < OS_TASK_PRIORITY_MAX);
    task->init_priority    = priority;
    task->current_priority = priority;

    task->number_mask = 0;
#if OS_TASK_PRIORITY_MAX > 32
    task->number    = 0;
    task->high_mask = 0;
#endif

    /* Initialize task time-slice value. */
    task->init_tick      = tick;
    task->remaining_tick = tick;

    /* Initialize task error code and state to OS_TASK_INIT. */
    task->error = OS_EOK;
    task->stat  = OS_TASK_INIT;

    /* Initialize cleanup function and user data. */
    task->cleanup   = OS_NULL;
    task->user_data = 0;

    /* Initialize task timer. */
    (void)os_timer_init(&task->task_timer, task->parent.name, os_task_timeout, (void *)task, 0, OS_TIMER_FLAG_ONE_SHOT);

    /* Initialize signal. */
#ifdef OS_USING_SIGNALS
    task->sig_mask    = 0x00;
    task->sig_pending = 0x00;

    task->sig_ret     = OS_NULL;
    task->sig_vectors = OS_NULL;
    task->si_list     = OS_NULL;
#endif

#ifdef OS_USING_MODULE
    task->module_id = OS_NULL;
#endif

#ifdef OS_USING_LWP
    task->lwp = OS_NULL;
#endif

    OS_OBJECT_HOOK_CALL(gs_os_task_inited_hook, (task));

    return OS_EOK;
}

/**
 ***********************************************************************************************************************
 * @brief           This function initializes a task and places it on the list of task object.
 *
 * @param[in]       task            The descriptor of task control block
 * @param[in]       name            Pointer to task name string
 * @param[in]       entry           Entry function of the task
 * @param[in]       parameter       Parameter of entry function
 * @param[in]       stack_start     Pointer to start of stack
 * @param[in]       stack_size      Stack size in bytes
 * @param[in]       priority        Priority of task
 * @param[in]       tick            task time-slice value
 *
 * @return          On success, return OS_EOK; on error, return a error code.
 * @retval          OS_EOK          Successfully initialized a task.
 * @retval          OS_EINVAL       Parameter "name" is null or used by other task.
 * @retval          OS_ERROR        Actual task initialize function return failed.
 ***********************************************************************************************************************
 */
os_err_t os_task_init(os_task_t    *task,
                      const char   *name, 
                      void        (*entry)(void *parameter),
                      void         *parameter,
                      void         *stack_start,
                      os_uint32_t   stack_size,
                      os_uint8_t    priority,
                      os_uint32_t   tick)
{
    os_err_t ret;
    
    OS_ASSERT(OS_NULL != task);
    OS_ASSERT(OS_NULL != stack_start);

    /* Check for name is null or duplicated names. */
    if ((OS_NULL == name) || (OS_NULL != os_task_find((char *)name)))
    {
        OS_KERN_LOG(KERN_ERROR, TASK_TAG, "init task name err");
        return OS_EINVAL;
    }

    /* Initialize task object.If the task is reinitialized there will be assert. */
    os_object_init((os_object_t *)task, OS_OBJECT_TASK, name, OS_TRUE);

    /* Call actual task initialize function. */
    ret = os_task_do_init(task, name, entry, parameter, stack_start, stack_size, priority, tick);
    if (OS_EOK != ret)
    {
        os_object_deinit((os_object_t *)task);

        OS_KERN_LOG(KERN_ERROR, TASK_TAG, "init task tcb doinit fail");

        return OS_ERROR;
    }

    return ret;
}
EXPORT_SYMBOL(os_task_init);

/**
 ***********************************************************************************************************************
 * @brief           Deinitialize a task
  *
 * @details         This function will deinitializate the specified task by task descriptor.
 *                  It will remove form task_list if the task state isn't OS_TASK_INIT,deinitializate the time of task,
 *                  set the task state to OS_TASK_CLOSE.If the cleanup callback function is null remove task from task
 *                  object list,otherwise places the task on the list of defunct task.
 *
 * @attention       It corresponds to os_task_init.
 *
 * @param[in]       task            The descriptor of task control block
 *
 * @return          Will only return OS_EOK
 ***********************************************************************************************************************
 */
os_err_t os_task_deinit(os_task_t *task)
{
    os_base_t lock;

    OS_ASSERT(OS_NULL != task);
    OS_ASSERT(OS_OBJECT_TASK == task->parent.type);
    OS_ASSERT(OS_TRUE == os_object_is_static(&task->parent));

    if (OS_TASK_INIT != (task->stat & OS_TASK_STAT_MASK))
    {
        /* Remove the task from ready table */
        os_schedule_remove_task(task);
    }

    /* Release task timer. */
    (void)os_timer_deinit(&task->task_timer);

    task->stat = OS_TASK_CLOSE;
    
    if (OS_NULL == task->cleanup)
    {
        os_object_deinit((os_object_t *)task);
    }
    else
    {
        lock = os_hw_interrupt_disable();

        /* Insert it to defunct task list. */
        os_list_add(&g_os_task_defunct, &task->task_list);

        os_hw_interrupt_enable(lock);
    }

    return OS_EOK;
}
EXPORT_SYMBOL(os_task_deinit);

#ifdef OS_USING_HEAP
/**
 ***********************************************************************************************************************
 * @brief           This function create a task and places it on the list of task object.
 *
 * @details         This function create a task and places it on the list of task object.The memory space of the 
 *                  stack and task control block descriptor is applied from the heap.
 *
 * @param[in]       name            Pointer to task name string
 * @param[in]       entry           Entry function of the task
 * @param[in]       parameter       Parameter of entry function
 * @param[in]       stack_size      Stack size in bytes
 * @param[in]       priority        Priority of task
 * @param[in]       tick            task time-slice value
 * 
 * @return          On success, return a task control block descriptor; on error, OS_NULL is returned.
 * @retval          not OS_NULL     Return a task control block descriptor.
 * @retval          OS_NULL         Call os_task_create failed.
 ***********************************************************************************************************************
 */
os_task_t *os_task_create(const char   *name, 
                          void        (*entry)(void *parameter),
                          void         *parameter,
                          os_uint32_t   stack_size,
                          os_uint8_t    priority,
                          os_uint32_t   tick)
{
    os_task_t  *task;
    void       *stack_start;
    os_err_t    ret;

    OS_DEBUG_NOT_IN_INTERRUPT;

    /* Check for name is null or duplicated names */
    if ((OS_NULL == name) || (OS_NULL != os_task_find((char *)name)))
    {
        OS_KERN_LOG(KERN_ERROR, TASK_TAG, "create task name err");
        return OS_NULL;
    }

    task = (os_task_t *)OS_KERNEL_MALLOC(sizeof(os_task_t));
    if (OS_NULL == task)
    {
        OS_KERN_LOG(KERN_ERROR, TASK_TAG, "create malloc task tcb fail");
        return OS_NULL;
    }

    stack_start = OS_KERNEL_MALLOC(stack_size);
    if (OS_NULL == stack_start)
    {
        OS_KERN_LOG(KERN_ERROR, TASK_TAG, "malloc task stack fail");
        
        OS_KERNEL_FREE(task);
        return OS_NULL;
    }

    /* Initialize task object */
    os_object_init((os_object_t *)task, OS_OBJECT_TASK, name, OS_FALSE);

    /* Call actual task initialize function. */
    ret = os_task_do_init(task, name, entry, parameter, stack_start, stack_size, priority, tick);
    if (OS_EOK != ret)
    {
        os_object_deinit((os_object_t *)task);

        OS_KERNEL_FREE(task);
        OS_KERNEL_FREE(stack_start);

        OS_KERN_LOG(KERN_ERROR, TASK_TAG, "create task doinit fail");

        return OS_NULL;
    }

    return task;
}
EXPORT_SYMBOL(os_task_create);

/**
 ***********************************************************************************************************************
 * @brief           Destroy a task
  *
 * @details         This function will destroy the specified task by task descriptor.
 *                  It will remove form task_list if the task state isn't OS_TASK_INIT,deinitializate the time of task,
 *                  set the task state to OS_TASK_CLOSE,places the task on the list of defunct task.
 *
 * @attention       It corresponds to os_task_create.
 *
 * @param[in]       task            The descriptor of task control block
 *
 * @return          Will only return OS_EOK
 ***********************************************************************************************************************
 */
os_err_t os_task_destroy(os_task_t *task)
{
    os_base_t lock;

    OS_ASSERT(OS_NULL != task);
    OS_ASSERT(OS_OBJECT_TASK == task->parent.type);
    OS_ASSERT(OS_FALSE == os_object_is_static(&task->parent));

    if (OS_TASK_INIT != (task->stat & OS_TASK_STAT_MASK))
    {
        /* Remove the task from ready table */
        os_schedule_remove_task(task);
    }

    /* Release task timer. */
    os_timer_deinit(&task->task_timer);

    task->stat = OS_TASK_CLOSE;
    
    lock = os_hw_interrupt_disable();

    /* Insert it to defunct task list. */
    os_list_add(&g_os_task_defunct, &task->task_list);

    os_hw_interrupt_enable(lock);

    return OS_EOK;
}
EXPORT_SYMBOL(os_task_destroy);
#endif

/**
 ***********************************************************************************************************************
 * @brief           Startup a task.
 *
 * @details         This function will starup the specified task by task descriptor.
 *
 * @attention       The task state must be OS_TASK_INIT.
 *
 * @param[in]       task            The descriptor of task control block
 *
 * @return          Will only return OS_EOK
 ***********************************************************************************************************************
 */
os_err_t os_task_startup(os_task_t *task)
{
    OS_ASSERT(OS_NULL != task);
    OS_ASSERT(OS_TASK_INIT == (task->stat & OS_TASK_STAT_MASK));
    OS_ASSERT(OS_OBJECT_TASK == os_object_get_type((os_object_t *)task));

    /* Set current priority to init priority. */
    task->current_priority = task->init_priority;

    /* Calculate priority attribute. */
#if OS_TASK_PRIORITY_MAX > 32
    task->number      = task->current_priority >> 3;            /* 5bit */
    task->number_mask = 1L << task->number;
    task->high_mask   = 1L << (task->current_priority & 0x07);  /* 3bit */
#else
    task->number_mask = 1L << task->current_priority;
#endif

    OS_KERN_LOG(KERN_DEBUG, TASK_TAG, "startup a task:%s with priority:%d", task->parent.name, task->init_priority);

    task->stat = OS_TASK_SUSPEND;

    (void)os_task_resume(task);

    if (OS_NULL != gs_os_current_task)
    {
        os_schedule();
    }

    return OS_EOK;
}
EXPORT_SYMBOL(os_task_startup);

/**
 ***********************************************************************************************************************
 * @brief           Task actively give up cpu to tasks of equal priority. 
 *
 * @details         This function moves the currently executing task to the end of the list of task ready 
 *                  at the same priority. If no other task of the same or higher priority are ready, 
 *                  this function simply returns. 
 *
 * @param           None
 *
 * @return          Will only return OS_EOK
 ***********************************************************************************************************************
 */
os_err_t os_task_yield(void)
{
    os_task_t *task;
    register os_base_t level;

    level = os_hw_interrupt_disable();

    task = gs_os_current_task;

    /* If the task stat is READY and the task priority ready list have other task. */
    if ((OS_TASK_READY == (task->stat & OS_TASK_STAT_MASK)) && (task->task_list.next != task->task_list.prev))
    {
        /* Remove task from task list. */
        os_list_del(&task->task_list);

        /* put task to the end of ready list. */
        os_list_add_tail(&(gs_os_task_priority_table[task->current_priority]), &task->task_list);

        os_hw_interrupt_enable(level);

        os_schedule();

        return OS_EOK;
    }

    os_hw_interrupt_enable(level);

    return OS_EOK;
}
EXPORT_SYMBOL(os_task_yield);

/**
 ***********************************************************************************************************************
 * @brief           Suspend a task.
 *
 * @details         This function will suspend the specified task by task descriptor.
 *
 * @param[in]       task            The descriptor of task control block
 *
 * @return          On success, return OS_EOK; on error, return a error code.
 * @retval          OS_EOK          Successfully suspended a task.
 * @retval          OS_ERROR        The task state is not OS_TASK_READY.
 ***********************************************************************************************************************
 */
os_err_t os_task_suspend(os_task_t *task)
{
    register os_base_t temp;

    OS_ASSERT(OS_NULL != task);
    OS_ASSERT(OS_OBJECT_TASK == os_object_get_type((os_object_t*)task));

    OS_KERN_LOG(KERN_DEBUG, TASK_TAG, "task suspend:  %s", task->parent.name);

    if (OS_TASK_READY != (task->stat & OS_TASK_STAT_MASK))
    {
        OS_KERN_LOG(KERN_DEBUG, TASK_TAG, "task suspend: task disorder, 0x%2x",task->stat);

        return OS_ERROR;
    }

    temp = os_hw_interrupt_disable();

    /* Change task stat. */
    task->stat = OS_TASK_SUSPEND | (task->stat & ~OS_TASK_STAT_MASK);
    os_schedule_remove_task(task);

    /* Stop task timer anyway. */
    (void)os_timer_stop(&task->task_timer);

    os_hw_interrupt_enable(temp);

    OS_OBJECT_HOOK_CALL(gs_os_task_suspend_hook, (task));

    return OS_EOK;
}
EXPORT_SYMBOL(os_task_suspend);

/**
 ***********************************************************************************************************************
 * @brief           Resume a task.
 *
 * @details         This function will resume the specified task by task descriptor.
 *
 * @param[in]       task            The descriptor of task control block
 *
 * @return          On success, return OS_EOK; on error, return a error code.
 * @retval          OS_EOK          Successfully resumed a task.
 * @retval          OS_ERROR        The task state is not OS_TASK_SUSPEND.
 ***********************************************************************************************************************
 */
os_err_t os_task_resume(os_task_t *task)
{
    register os_base_t temp;

    OS_ASSERT(OS_NULL != task);
    OS_ASSERT(OS_OBJECT_TASK == os_object_get_type((os_object_t*)task));

    OS_KERN_LOG(KERN_DEBUG, TASK_TAG, "task resume:  %s", task->parent.name);

    if (OS_TASK_SUSPEND != (task->stat & OS_TASK_STAT_MASK))
    {
        OS_KERN_LOG(KERN_DEBUG, TASK_TAG, "task resume: task disorder, %d",task->stat);

        return OS_ERROR;
    }

    temp = os_hw_interrupt_disable();

    /* Remove from suspend list. */
    os_list_del(&task->task_list);

    /* Stop task timer anyway. */
    (void)os_timer_stop(&task->task_timer);

    os_hw_interrupt_enable(temp);

    /* palce the task on ready list. */
    os_schedule_insert_task(task);

    OS_OBJECT_HOOK_CALL(gs_os_task_resume_hook, (task));

    return OS_EOK;
}
EXPORT_SYMBOL(os_task_resume);

/**
 ***********************************************************************************************************************
 * @brief           This function is the callback function of the task timer
 *
 * @param[in]       parameter       The descriptor of task control block
 *
 * @return          None
 ***********************************************************************************************************************
 */
void os_task_timeout(void *parameter)
{
    os_task_t *task;

    task = (os_task_t *)parameter;

    OS_ASSERT(OS_NULL != task);
    OS_ASSERT(OS_TASK_SUSPEND == (task->stat & OS_TASK_STAT_MASK));
    OS_ASSERT(OS_OBJECT_TASK == os_object_get_type((os_object_t *)task));

    /* Set error number. */
    task->error = OS_ETIMEOUT;

    /* Remove from suspend list. */
    os_list_del(&task->task_list);

    /* palce the task on ready list. */
    os_schedule_insert_task(task);

    os_schedule();
}
EXPORT_SYMBOL(os_task_timeout);

/**
 ***********************************************************************************************************************
 * @brief           Control task
 *
 * @details         This function control or change the properties of the task.
 *
 * @param[in]       task            The descriptor of task control block.
 * @param[in]       cmd             Control commands.
 *                                  OS_TASK_CTRL_CHANGE_PRIORITY:It will change priority of the task.
 *                                  OS_TASK_CTRL_STARTUP:It will startup the task.
 *                                  OS_TASK_CTRL_CLOSE:It will close the task.
 * 
 * @param[in]       arg             Control argments.
 *
 *
 * @return          On success, return OS_EOK; on error, return a error code.
 * @retval          OS_EOK          Successfully control task.
 * @retval          OS_ERROR        This command is currently not supported or execute error.
 ***********************************************************************************************************************
 */
os_err_t os_task_control(os_task_t *task, enum os_task_ctrl_cmd cmd, void *arg)
{
    register os_base_t temp;

    OS_ASSERT(OS_NULL != task);
    OS_ASSERT(OS_OBJECT_TASK == os_object_get_type((os_object_t *)task));

    switch (cmd)
    {
    case OS_TASK_CTRL_CHANGE_PRIORITY:
        
        temp = os_hw_interrupt_disable();

        /* For ready task, change list. */
        if (OS_TASK_READY == (task->stat & OS_TASK_STAT_MASK))
        {
            /* Remove task from ready list first */
            os_schedule_remove_task(task);

            /* change task priority */
            task->current_priority = *(os_uint8_t *)arg;

            /* recalculate priority attribute */
#if OS_TASK_PRIORITY_MAX > 32
            task->number      = task->current_priority >> 3;            /* 5bit */
            task->number_mask = 1 << task->number;
            task->high_mask   = 1 << (task->current_priority & 0x07);   /* 3bit */
#else
            task->number_mask = 1 << task->current_priority;
#endif

            /* Palce it on ready list again. */
            os_schedule_insert_task(task);
        }
        else
        {
            task->current_priority = *(os_uint8_t *)arg;

            /* recalculate priority attribute */
#if OS_TASK_PRIORITY_MAX > 32
            task->number      = task->current_priority >> 3;            /* 5bit */
            task->number_mask = 1 << task->number;
            task->high_mask   = 1 << (task->current_priority & 0x07);   /* 3bit */
#else
            task->number_mask = 1 << task->current_priority;
#endif
        }

        os_hw_interrupt_enable(temp);
        return OS_EOK;

    case OS_TASK_CTRL_STARTUP:
        return os_task_startup(task);

    case OS_TASK_CTRL_CLOSE:
        if (OS_TRUE == os_object_is_static(&task->parent))
        {
            return os_task_deinit(task);
        }
#ifdef OS_USING_HEAP
        else
        {
            return os_task_destroy(task);
        }
#endif

    default:
        break;
    }

    return OS_ERROR;
}
EXPORT_SYMBOL(os_task_control);

/**
 ***********************************************************************************************************************
 * @brief           Find task by name on the task object list 
 *
 * @details         This function will find task by name on the task object list.
 *
 * @param[in]       name            Pointer to task name string
 * 
 * @return          On success, return a task control block descriptor; on error, OS_NULL is returned.
 * @retval          not OS_NULL     Return a task control block descriptor.
 * @retval          OS_NULL         No task to be found.
 ***********************************************************************************************************************
 */
os_task_t *os_task_find(char *name)
{
    os_object_info_t *info;
    os_object_t      *object;
    os_list_node_t   *node;

    os_enter_critical();

    /* Try to find device object. */
    info = os_object_get_info(OS_OBJECT_TASK);
    OS_ASSERT(OS_NULL != info);

    /* Traverse task object list. */
    os_list_for_each(node, &info->object_list)
    {
        object = os_list_entry(node, os_object_t, list);
        if (0 == os_strncmp(object->name, name, OS_NAME_MAX))
        {
            os_exit_critical();

            return (os_task_t *)object;
        }
    }

    os_exit_critical();

    /* There is no task with this name on the list. */
    return OS_NULL;
}
EXPORT_SYMBOL(os_task_find);

/**
 ***********************************************************************************************************************
 * @brief           Verify task by id on the task object list 
 *
 * @details         This function will verify task by id on the task object list.
 *
 * @param[in]       id          a task control block descriptor
 * 
 * @return          On success, return OS_EOK; on error, OS_ERROR is returned.
 * @retval          OS_EOK      Find the task with the same task id.
 * @retval          OS_ERROR    No task found with the same task id.
 ***********************************************************************************************************************
 */
os_err_t os_task_id_verify(os_task_t *id)
{
    os_object_info_t *info;
    os_task_t        *task;
    os_list_node_t   *node;

    os_enter_critical();

    /* Try to find device object. */
    info = os_object_get_info(OS_OBJECT_TASK);
    OS_ASSERT(OS_NULL != info);

    /* Traverse task object list. */
    os_list_for_each(node, &info->object_list)
    {
        task = os_list_entry(node, os_task_t, parent.list);
        if (task == id)
        {
            os_exit_critical();

            return OS_EOK;
        }
    }

    os_exit_critical();

    /* There is no task with this id on the list. */
    return OS_ERROR;
}
EXPORT_SYMBOL(os_task_id_verify);


/**
 ***********************************************************************************************************************
 * @brief           Task sleep in tick 
 *
 * @details         This function will cause task to sleep.
 *
 * @attention       If the tick of input parameter equal zero,the current task will give up cpu to tasks 
 *                  of equal priority.
 *
 * @param[in]       tick            The value of task sleep in tick.
 * 
 * @return          Will only return OS_EOK.
 ***********************************************************************************************************************
 */
os_err_t os_task_sleep(os_tick_t tick)
{
    os_task_t *task;
    register os_base_t temp;

    /* give up cpu to tasks of equal priority  */
    if (0 == tick)
    {
        return os_task_yield();
    }
    else
    {
        temp = os_hw_interrupt_disable();
        
        task = gs_os_current_task;

        OS_ASSERT(OS_NULL != task);
        OS_ASSERT(OS_OBJECT_TASK == os_object_get_type((os_object_t *)task));
        
        /* Suspend task */
        (void)os_task_suspend(task);

        /* Reset the timeout of task timer and start it. */
        (void)os_timer_control(&task->task_timer, OS_TIMER_CTRL_SET_TIME, &tick);
        (void)os_timer_start(&task->task_timer);

        os_hw_interrupt_enable(temp);

        os_schedule();

        /* Clear error number of this task to OS_EOK. */
        if (OS_ETIMEOUT == task->error)
        {
            task->error = OS_EOK;
        }

        return OS_EOK;
    }
}
EXPORT_SYMBOL(os_task_sleep);

/**
 ***********************************************************************************************************************
 * @brief           Task sleep in millisecond 
 *
 * @details         This function will cause task to sleep.
 *
 * @attention       This function actually calls os_task_sleep, so the minimum precision is tick.
 *
 * @param[in]       ms              The value of task sleep in millisecond.
 * 
 * @return          Will only return OS_EOK.
 ***********************************************************************************************************************
 */
os_err_t os_task_msleep(os_uint32_t ms)
{
    os_tick_t tick;

    tick = os_tick_from_ms(ms);
    OS_ASSERT(tick < OS_TICK_MAX / 2);

    return os_task_sleep(tick);
}
EXPORT_SYMBOL(os_task_msleep);

/**
 ***********************************************************************************************************************
 * @brief           Task delay in tick
  *
 * @details         This function will cause task to sleep.
 *
 * @attention       This function is the same as os_task_sleep.
 *
 * @param[in]       tick            The value of task sleep in tick.
 * 
 * @return          Will only return OS_EOK.
 ***********************************************************************************************************************
 */
os_err_t os_task_delay(os_tick_t tick)
{
    OS_ASSERT(tick < OS_TICK_MAX / 2);

    return os_task_sleep(tick);
}
EXPORT_SYMBOL(os_task_delay);

/**
 ***********************************************************************************************************************
 * @brief           Task sleep in millisecond 
 *
 * @details         This function will cause task to sleep.
 *
 * @attention       This function is the same as os_task_msleep.
 *
 * @param[in]       ms              The value of task sleep in millisecond.
 * 
 * @return          Will only return OS_EOK.
 ***********************************************************************************************************************
 */
os_err_t os_task_mdelay(os_uint32_t ms)
{
    return os_task_msleep(ms);
}
EXPORT_SYMBOL(os_task_mdelay);

/**
 ***********************************************************************************************************************
 * @brief           This function initializes the system's scheduler.
 *
 * @details         This function initialize the global variable of system scheduler.
 *
 *
 * @param           None       
 *
 * @return          None
 ***********************************************************************************************************************
 */
void os_system_scheduler_init(void)
{
    register os_base_t offset;

    gs_os_scheduler_lock_nest = 0;

    OS_KERN_LOG(KERN_DEBUG, TASK_TAG, "start scheduler: max priority 0x%02x", OS_TASK_PRIORITY_MAX);

    for (offset = 0; offset < OS_TASK_PRIORITY_MAX; offset++)
    {
        os_list_init(&gs_os_task_priority_table[offset]);
    }

    gs_os_current_task = OS_NULL;

    /* Initialize ready priority group. */
    gs_os_task_ready_priority_group = 0;

#if OS_TASK_PRIORITY_MAX > 32
    /* Initialize ready table. */
    os_memset(gs_os_task_ready_table, 0, sizeof(gs_os_task_ready_table));
#endif

    /* Initialize task defunct. */
    os_list_init(&g_os_task_defunct);
}

/**
 ***********************************************************************************************************************
 * @brief           This function will start the system's scheduler.
 *
 * @details         This function will find the highest priority task first, then switch to it.
 *
 *
 * @param           None       
 *
 * @return          None
 ***********************************************************************************************************************
 */
void os_system_scheduler_start(void)
{
    register os_task_t *to_task;
    register os_ubase_t highest_ready_priority;

#if OS_TASK_PRIORITY_MAX > 32
    register os_ubase_t number;

    number = os_find_first_bit_set(gs_os_task_ready_priority_group) - 1;
    highest_ready_priority = (number << 3) + os_find_first_bit_set(gs_os_task_ready_table[number]) - 1;
#else
    highest_ready_priority = os_find_first_bit_set(gs_os_task_ready_priority_group) - 1;
#endif

    /* Get switch to task. */
    to_task = os_list_entry(gs_os_task_priority_table[highest_ready_priority].next, os_task_t, task_list);

    gs_os_current_task = to_task;

    /* Switch to new task. */
    os_hw_context_switch_to((os_uint32_t)&to_task->sp);

    /* Never come back. */
}

/**
 ***********************************************************************************************************************
 * @brief           This function implement system scheduling
 *
 * @details         This function will find the highest priority task first,if it not same with 
 *                  current task,then switch to it.
 *
 * @param           None       
 *
 * @return          None
 ***********************************************************************************************************************
 */
void os_schedule(void)
{
    os_base_t level;
    os_task_t *to_task;
    os_task_t *from_task;

    level = os_hw_interrupt_disable();

    /* Check the scheduler is enabled or not. */
    if (gs_os_scheduler_lock_nest == 0)
    {
        register os_ubase_t highest_ready_priority;

#if OS_TASK_PRIORITY_MAX <= 32
        highest_ready_priority = os_find_first_bit_set(gs_os_task_ready_priority_group) - 1;
#else
        register os_ubase_t number;

        number = os_find_first_bit_set(gs_os_task_ready_priority_group) - 1;
        highest_ready_priority = (number << 3) + os_find_first_bit_set(gs_os_task_ready_table[number]) - 1;
#endif

        /* Get highest ready priority task. */
        to_task = os_list_entry(gs_os_task_priority_table[highest_ready_priority].next, os_task_t, task_list);

        /* If the destination task is not the same as current task. */
        if (to_task != gs_os_current_task)
        {

#ifdef OS_USING_OVERFLOW_CHECK
            extern void schedule_from_task_stack_check(os_task_t *task);
            extern void schedule_to_task_stack_check(os_task_t *task);
            schedule_from_task_stack_check(gs_os_current_task);
            schedule_to_task_stack_check(to_task);          
#endif

            from_task              = gs_os_current_task;
            gs_os_current_task     = to_task;

            OS_OBJECT_HOOK_CALL(gs_os_scheduler_hook, (from_task, to_task));

            OS_KERN_LOG(KERN_DEBUG, TASK_TAG, "[%d]switch to priority#%d task:%.*s(sp:0x%p),from task:%.*s(sp: 0x%p)",
                        g_os_interrupt_nest, 
                        highest_ready_priority,
                        OS_NAME_MAX, 
                        to_task->parent.name, 
                        to_task->sp,
                        OS_NAME_MAX, 
                        from_task->parent.name, 
                        from_task->sp);

            /* Switch to new task. */
            if (0 == g_os_interrupt_nest)
            {
                os_hw_context_switch((os_uint32_t)&from_task->sp, (os_uint32_t)&to_task->sp);

#ifdef OS_USING_SIGNALS
                if (gs_os_current_task->stat & OS_TASK_STAT_SIGNAL_PENDING)
                {
                    extern void os_task_handle_signal(os_bool_t clean_state);

                    gs_os_current_task->stat &= ~OS_TASK_STAT_SIGNAL_PENDING;

                    os_hw_interrupt_enable(level);

                    /* check signal status */
                    os_task_handle_signal(OS_TRUE);
                }
                else
#endif
                {
                    os_hw_interrupt_enable(level);
                }

                return ;
            }
            else
            {
                OS_KERN_LOG(KERN_DEBUG, TASK_TAG, "switch in interrupt");

                os_hw_context_switch_interrupt((os_uint32_t)&from_task->sp, (os_uint32_t)&to_task->sp);
            }
        }
    }

    os_hw_interrupt_enable(level);
}

/**
 ***********************************************************************************************************************
 * @brief           This function will place the task on priority ready list.
 *
 * @details         This function will set the task state to OS_TASK_READY, and then place the task on ready priority 
 *                  ready list and update bitmap.
 *
 * @param[in]       task            The descriptor of task control block.                
 *
 * @return          None
 ***********************************************************************************************************************
 */
void os_schedule_insert_task(os_task_t *task)
{
    register os_base_t temp;

    OS_ASSERT(OS_NULL != task);

    temp = os_hw_interrupt_disable();

    task->stat = OS_TASK_READY | (task->stat & ~OS_TASK_STAT_MASK);

    /* Insert task to ready list. */
    os_list_add_tail(&(gs_os_task_priority_table[task->current_priority]), &task->task_list);

    /* Set priority mask. */
#if OS_TASK_PRIORITY_MAX <= 32
    OS_KERN_LOG(KERN_DEBUG, TASK_TAG, "insert task[%.*s], the priority: %d",
                OS_NAME_MAX,
                task->parent.name,
                task->current_priority);
#else
    OS_KERN_LOG(KERN_DEBUG, TASK_TAG, "insert task[%.*s], the priority: %d 0x%x %d",
                OS_NAME_MAX,
                task->parent.name,
                task->number,
                task->number_mask,
                task->high_mask);
#endif

#if OS_TASK_PRIORITY_MAX > 32
    gs_os_task_ready_table[task->number] |= task->high_mask;
#endif
    gs_os_task_ready_priority_group |= task->number_mask;

    os_hw_interrupt_enable(temp);
}

/**
 ***********************************************************************************************************************
 * @brief           This function will remove the task from ready table.
 *
 * @details         This function will remove the task from ready table.If only this task is on the priority ready list
 *                  need to update the bitmap.
 *
 * @param[in]       task            The descriptor of task control block.       
 *
 * @return          None
 ***********************************************************************************************************************
 */
void os_schedule_remove_task(os_task_t *task)
{
    register os_base_t temp;

    OS_ASSERT(OS_NULL != task);

    temp = os_hw_interrupt_disable();

#if OS_TASK_PRIORITY_MAX <= 32

    OS_KERN_LOG(KERN_DEBUG, TASK_TAG, "remove task[%.*s], the priority: %d",
                OS_NAME_MAX, 
                task->parent.name,
                task->current_priority);
#else
    OS_KERN_LOG(KERN_DEBUG, TASK_TAG, "remove task[%.*s], the priority: %d 0x%x %d",
                OS_NAME_MAX,
                task->parent.name,
                task->number,
                task->number_mask,
                task->high_mask);
#endif

    /* Remove task from ready list. */
    os_list_del(&task->task_list);

    if (os_list_empty(&(gs_os_task_priority_table[task->current_priority])))
    {
#if OS_TASK_PRIORITY_MAX > 32
        gs_os_task_ready_table[task->number] &= ~task->high_mask;
        if (gs_os_task_ready_table[task->number] == 0)
        {
            gs_os_task_ready_priority_group &= ~task->number_mask;
        }
#else
        gs_os_task_ready_priority_group &= ~task->number_mask;
#endif
    }

    os_hw_interrupt_enable(temp);
}

/**
 ***********************************************************************************************************************
 * @brief           This function will lock the system scheduler.
 *
 * @param           None
 *
 * @return          None
 ***********************************************************************************************************************
 */
void os_enter_critical(void)
{
    register os_base_t level;

    level = os_hw_interrupt_disable();

    gs_os_scheduler_lock_nest++;

    os_hw_interrupt_enable(level);
}
EXPORT_SYMBOL(os_enter_critical);

/**
 ***********************************************************************************************************************
 * @brief           This function will unlock the system scheduler.
 *
 * @details         This function will decrement "gs_os_scheduler_lock_nest".
 *                  If gs_os_scheduler_lock_nest is equal zero unlock the system scheduler.
 *
 * @param           None
 *
 * @return          None
 ***********************************************************************************************************************
 */
void os_exit_critical(void)
{
    register os_base_t level;

    level = os_hw_interrupt_disable();

    gs_os_scheduler_lock_nest--;

    if (gs_os_scheduler_lock_nest <= 0)
    {
        gs_os_scheduler_lock_nest = 0;

        os_hw_interrupt_enable(level);

        if (gs_os_current_task)
        {
            /* If scheduler is started, do a schedule. */
            os_schedule();
        }
    }
    else
    {
        os_hw_interrupt_enable(level);
    }
}
EXPORT_SYMBOL(os_exit_critical);

/**
 ***********************************************************************************************************************
 * @brief           This function will return nesting level of lock the system scheduler.
 *
 * @param           None
 *
 * @return          None
 ***********************************************************************************************************************
 */
os_uint16_t os_critical_level(void)
{
    return gs_os_scheduler_lock_nest;
}
EXPORT_SYMBOL(os_critical_level);


#ifdef OS_USING_SHELL

#include <shell.h>

static os_err_t sh_list_task_info(os_list_node_t *list)
{
    os_int32_t      maxlen;
    os_uint8_t     *ptr;
    os_task_t      *task;
    os_list_node_t *node;
    os_uint32_t     task_sp;
    
    const char *item_title = "task";

    maxlen = os_object_name_maxlen(item_title, list);

    os_kprintf("%-*.s pri  status      sp     stack addr stack size max used left tick  err\r\n", maxlen, item_title); 
    os_object_split(maxlen);
    os_kprintf(     " ---  ------- ---------- ---------- ----------  ------  ---------- ---\r\n");
    
    for(node = list->next; node != list; node = node->next)
    {
        os_uint8_t stat;
        task = os_list_entry(node, os_task_t, parent.list);
        os_kprintf("%-*.*s %3d ", maxlen, OS_NAME_MAX, task->parent.name, task->current_priority);

        stat = (task->stat & OS_TASK_STAT_MASK);
        if (stat == OS_TASK_READY)
        {
            os_kprintf(" ready  ");
        }
        else if (stat == OS_TASK_SUSPEND)
        {
            os_kprintf(" suspend");
        }
        else if (stat == OS_TASK_INIT)
        {
            os_kprintf(" init   ");
        }
        else if (stat == OS_TASK_CLOSE)
        {
            os_kprintf(" close  ");
        }

        if (os_interrupt_get_nest() > 0)
        {
            task_sp = (os_uint32_t)task->sp;
        }
        else
        {
            if (task == gs_os_current_task)
            {
                extern os_size_t *get_current_task_sp(void);
                
                task_sp = (os_uint32_t)get_current_task_sp();
            }
            else
            {
                task_sp = (os_uint32_t)task->sp;
            }
        }

#if defined(ARCH_CPU_STACK_GROWS_UPWARD)
        ptr = (os_uint8_t *)task->stack_addr + task->stack_size;
        while(*ptr == '#')
        {
            ptr--;
        }

        os_kprintf(" 0x%08x 0x%08x 0x%08x    %02d%%   0x%08x %03d\r\n",
                   task_sp,
                   task->stack_addr,
                   task->stack_size,
                   ((os_uint32_t)ptr - (os_uint32_t)task->stack_addr) * 100 / task->stack_size,
                   task->remaining_tick,
                   task->error);
#else
        ptr = (os_uint8_t *)task->stack_addr;
        while(*ptr == '#')
        {
            ptr++;
        }

        os_kprintf(" 0x%08x 0x%08x 0x%08x    %02d%%   0x%08x %03d\r\n",
                   task_sp,
                   task->stack_addr,
                   task->stack_size,
                   (task->stack_size + (os_uint32_t)task->stack_addr - (os_uint32_t) ptr) * 100 / task->stack_size,
                   task->remaining_tick,
                   task->error);
#endif
    }

    return OS_EOK;
}

/**
***********************************************************************************************************************
* @brief           Show all task on the list of task object
*
* @param[in]       argc                argment count
* @param[in]       argv                argment list
*
* @return          Will only return OS_EOK     
***********************************************************************************************************************
*/
os_err_t sh_list_task(os_int32_t argc, char **argv)
{
    os_object_info_t *info;

    info = os_object_get_info(OS_OBJECT_TASK);
    return sh_list_task_info(&info->object_list);
}

SH_CMD_EXPORT(task, sh_list_task, "show task information");

#ifdef OS_USING_TASK_MONITOR

/**
 ***********************************************************************************************************************
 * @brief           Get tasks that are in the ready list by priority order.
 *
 * @param[out]      taks_out     Pointer to array of task pointer.
 * @param[in]       size         The number of task_out array's element. 
 *
 * @return          The number of tasks which are set to parameter task_out.
 ***********************************************************************************************************************
 */
os_uint8_t os_task_get_by_priority_order(os_task_t* task_out[], os_uint8_t size)
{
    register os_ubase_t highest_ready_priority;
    os_uint32_t         ready_priority_group;
    os_list_node_t     *node;
    os_task_t          *task;
    os_uint8_t          i;

    OS_ASSERT(OS_NULL != task_out);
    OS_ASSERT(size > 0);

    ready_priority_group = gs_os_task_ready_priority_group;

#if OS_TASK_PRIORITY_MAX > 32
    os_uint8_t ready_table[32];
    for (i = 0; i < 32; i++)
    {
        ready_table[i] = gs_os_task_ready_table[i];
    }
#endif

    i = 0;
    while (i < size)
    {
#if OS_TASK_PRIORITY_MAX <= 32
        highest_ready_priority = os_find_first_bit_set(ready_priority_group) - 1;
        ready_priority_group &= ~(1 << highest_ready_priority);
#else
        register os_ubase_t number;
        os_uint8_t          tmp;

        number = os_find_first_bit_set(ready_priority_group) - 1;
        tmp = os_find_first_bit_set(ready_table[number]) - 1;
        highest_ready_priority = (number << 3) + tmp;

        ready_table[number] &= ~(1 << tmp);
        if (0 == ready_table[number])
        {
            ready_priority_group &= ~(1 << number);
        }
#endif

        os_list_for_each(node, &gs_os_task_priority_table[highest_ready_priority])
        {
            task = os_list_entry(node, os_task_t, task_list);
            task_out[i++] = task;

            if (i >= size)
            {
                break;
            }
        }

        if (0 == ready_priority_group)
        {
            break;
        }
    }

    return i;
}

EXPORT_SYMBOL(os_task_get_by_priority);

#endif

#endif 


