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
 * @file        os_task.h
 *
 * @brief       Header file for task interface.
 *
 * @revision
 * Date         Author          Notes
 * 2020-02-18   OneOS Team      First Version
 ***********************************************************************************************************************
 */

#ifndef __OS_TASK_H__
#define __OS_TASK_H__

#include <oneos_config.h>
#include <os_types.h>
#include <os_stddef.h>
#include <os_object.h>
#include <os_timer.h>

#ifdef __cplusplus
extern "C" {
#endif

#define OS_TASK_INIT                  0x00                /* Initialized status. */
#define OS_TASK_READY                 0x01                /* Ready status. */
#define OS_TASK_SUSPEND               0x02                /* Suspend status. */
#define OS_TASK_RUNNING               0x03                /* Running status. */
#define OS_TASK_BLOCK                 OS_TASK_SUSPEND     /* Blocked status. */
#define OS_TASK_CLOSE                 0x04                /* Closed status. */
#define OS_TASK_STAT_MASK             0x0f

#define OS_TASK_STAT_SIGNAL           0x10                /* Task hold signals. */
#define OS_TASK_STAT_SIGNAL_READY     (OS_TASK_STAT_SIGNAL | OS_TASK_READY)
#define OS_TASK_STAT_SIGNAL_WAIT      0x20                /* Task is waiting for signals. */
#define OS_TASK_STAT_SIGNAL_PENDING   0x40                /* Signals is held and it has not been procressed. */
#define OS_TASK_STAT_SIGNAL_MASK      0xf0

/**
 ***********************************************************************************************************************
 * @enum        enum os_task_ctrl_cmd
 *
 * @brief       os_task_ctrl_cmd is used to os_task_control function.
 ***********************************************************************************************************************
 */
enum os_task_ctrl_cmd
{
    OS_TASK_CTRL_STARTUP = 0x0,
    OS_TASK_CTRL_CLOSE,
    OS_TASK_CTRL_CHANGE_PRIORITY
};

/**
 ***********************************************************************************************************************
 * @struct      struct os_task
 *
 * @brief       Define task control block descriptor.
 ***********************************************************************************************************************
 */
struct os_task
{
    os_object_t parent;                                 /* Inherit from os_object. */        

    os_list_node_t   task_list;                         /* The task list. */

    /* Stack point and entry. */
    void       *sp;                                     /* Stack point. */
    void       *entry;                                  /* Entry. */
    void       *parameter;                              /* Parameter. */
    void       *stack_addr;                             /* Stack address. */
    os_uint32_t stack_size;                             /* Stack size. */

    /* Error code. */
    os_err_t    error;                                  /* Error code. */

    os_uint8_t  stat;                                   /* Task status. */

    /* Priority. */
    os_uint8_t  current_priority;                       /* Current priority. */
    os_uint8_t  init_priority;                          /* Initialized priority. */
#if OS_TASK_PRIORITY_MAX > 32
    os_uint8_t  number;
    os_uint8_t  high_mask;
#endif
    os_uint32_t number_mask;

#if defined(OS_USING_EVENT)
    /* Task event. */
    os_uint32_t event_set;
    os_uint8_t  event_info;
#endif

#if defined(OS_USING_SIGNALS)
    os_sigset_t     sig_pending;                        /* The pending signals. */
    os_sigset_t     sig_mask;                           /* The mask bits of signal. */

    void            *sig_ret;                           /* The return stack pointer from signal. */
    os_sighandler_t *sig_vectors;                       /* Vectors of signal handler. */
    void            *si_list;                           /* The signal infor list. */
#endif

    os_ubase_t  init_tick;                              /* Task's initialized tick. */
    os_ubase_t  remaining_tick;                         /* Remaining tick. */

    os_timer_t  task_timer;                             /* Built-in task timer. */

    void (*cleanup)(struct os_task *task);              /* Cleanup function when task exit. */

    /* Light weight process if present. */
#ifdef OS_USING_LWP
    void        *lwp;
#endif

#ifdef OS_USING_MODULE
    void       *module_id;                              /* Id of application module */
#endif
    os_uint32_t user_data;                              /* Private user data beyond this task. */
};
typedef struct os_task os_task_t;


extern os_err_t    os_get_errno(void);
extern void        os_set_errno(os_err_t error);
extern os_int32_t *os_errno(void);

#if !defined(OS_USING_NEWLIB) && !defined(_WIN32)
#ifndef errno
#define errno    *os_errno()
#endif
#endif

#ifdef OS_USING_HOOK

void os_task_suspend_set_hook(void (*hook)(os_task_t *task));

void os_task_resume_set_hook(void (*hook)(os_task_t *task));

void os_task_inited_set_hook(void (*hook)(os_task_t *task));

void os_scheduler_set_hook(void (*hook)(os_task_t *from, os_task_t *to));

#endif /* end OS_USING_HOOK */


#ifdef OS_USING_HEAP
extern os_task_t *os_task_create(const char   *name, 
                                 void        (*entry)(void *parameter),
                                 void         *parameter,
                                 os_uint32_t   stack_size,
                                 os_uint8_t    priority,
                                 os_uint32_t   tick);

extern os_err_t   os_task_destroy(os_task_t *task);
#endif

extern os_err_t   os_task_init(os_task_t    *task,
                               const char   *name, 
                               void        (*entry)(void *parameter),
                               void         *parameter,
                               void         *stack_start,
                               os_uint32_t   stack_size,
                               os_uint8_t    priority,
                               os_uint32_t   tick);

extern os_err_t   os_task_deinit(os_task_t *task);

extern os_err_t         os_task_startup(os_task_t *task);
extern os_task_t       *os_task_self(void);
extern char            *os_task_name(os_task_t *task);
extern os_err_t         os_task_yield(void);
extern os_err_t         os_task_control(os_task_t *task, enum os_task_ctrl_cmd cmd, void *arg);
extern os_task_t       *os_task_find(char *name);
extern os_err_t         os_task_id_verify(os_task_t *id);


extern os_err_t         os_task_sleep(os_tick_t tick);
extern os_err_t         os_task_msleep(os_uint32_t ms);
extern os_err_t         os_task_delay(os_tick_t tick);
extern os_err_t         os_task_mdelay(os_uint32_t ms);

extern void             os_enter_critical(void);
extern void             os_exit_critical(void);
extern os_uint16_t      os_critical_level(void);

#ifdef OS_USING_SHELL

extern os_err_t sh_list_task(os_int32_t argc, char **argv);

#ifdef OS_USING_TASK_MONITOR
extern os_uint8_t os_task_get_by_priority_order(os_task_t* task_out[], os_uint8_t size);
#endif

#endif

#ifdef __cplusplus
}
#endif

#endif

