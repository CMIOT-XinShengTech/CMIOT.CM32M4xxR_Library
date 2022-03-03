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
 * @file        os_timer.h
 *
 * @brief       Header file for timer interface.
 *
 * @revision
 * Date         Author          Notes
 * 2020-02-12   OneOS Team      First version.
 ***********************************************************************************************************************
 */
#ifndef __OS_TIMER_H__
#define __OS_TIMER_H__

#include <oneos_config.h>
#include <os_types.h>
#include <os_stddef.h>
#include <os_object.h>

#ifdef __cplusplus
extern "C" {
#endif

#define OS_TIMER_FLAG_DEACTIVATED   0x0     /* Timer is deactive. */
#define OS_TIMER_FLAG_ACTIVATED     0x1     /* Timer is active. */

#define OS_TIMER_FLAG_ONE_SHOT      0x0     /* One shot timer. */
#define OS_TIMER_FLAG_PERIODIC      0x2     /* Periodic timer. */

#define OS_TIMER_FLAG_HARD_TIMER    0x0     /* Hard timer,the timer's callback function will be called in tick isr. */
#define OS_TIMER_FLAG_SOFT_TIMER    0x4     /* Soft timer,the timer's callback function will be called in timer task. */

#ifndef OS_TIMER_SKIP_LIST_LEVEL
#define OS_TIMER_SKIP_LIST_LEVEL    1
#endif

/* 1 or 3 */
#ifndef OS_TIMER_SKIP_LIST_MASK
#define OS_TIMER_SKIP_LIST_MASK     0x3
#endif

enum os_timer_ctrl_cmd
{
    OS_TIMER_CTRL_SET_TIME = 0x0,
    OS_TIMER_CTRL_GET_TIME,
    OS_TIMER_CTRL_SET_ONESHOT,
    OS_TIMER_CTRL_SET_PERIODIC
};

struct os_timer
{
    os_object_t      parent;                            /* Inherit from os_object. */

    os_list_node_t   row[OS_TIMER_SKIP_LIST_LEVEL];

    void           (*timeout_func)(void *parameter);    /* Timeout function. */
    void            *parameter;                         /* Timeout function's parameter. */

    os_tick_t        init_tick;                         /* Timer timeout tick. */
    os_tick_t        timeout_tick;                      /* Timeout tick. */
};
typedef struct os_timer os_timer_t;

#ifdef OS_USING_HOOK

extern void os_timer_start_set_hook(void (*hook)(os_timer_t *timer));

extern void os_timer_stop_set_hook(void (*hook)(os_timer_t *timer));

extern void os_timer_enter_set_hook(void (*hook)(os_timer_t *timer));

extern void os_timer_exit_set_hook(void (*hook)(os_timer_t *timer));

#endif /* end OS_USING_HOOK */

#ifdef OS_USING_HEAP
extern os_timer_t *os_timer_create(const char    *name, 
                                   void         (*timeout)(void *parameter), 
                                   void          *parameter, 
                                   os_tick_t      time, 
                                   os_uint8_t     flag);
extern os_err_t os_timer_destroy(os_timer_t *timer);
#endif

extern void os_timer_init(os_timer_t    *timer,
                          const char    *name, 
                          void         (*timeout)(void *parameter), 
                          void          *parameter, 
                          os_tick_t      time, 
                          os_uint8_t     flag);
extern void os_timer_deinit(os_timer_t *timer);

extern os_err_t os_timer_start(os_timer_t *timer);
extern os_err_t os_timer_stop(os_timer_t *timer);
extern os_err_t os_timer_control(os_timer_t *timer, enum os_timer_ctrl_cmd cmd, void *arg);
extern void     os_system_timer_init(void);
extern void     os_system_timer_task_init(void);

extern os_tick_t os_timer_next_timeout_tick(void);
#ifdef OS_USING_TIMER_SOFT
extern os_tick_t os_soft_timer_next_timeout_tick(void);
#endif

#ifdef __cplusplus
}
#endif

#endif

