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
 * @file        os_startup.c
 *
 * @brief       The starting-up process of OneOS.
 *
 * @details     During starting-up process, do something as follows:
 *                  1) Board initialization.
 *                  2) Timer system initialization.
 *                  3) Scheduler system initialization.
 *                  4) Application initialization. The important job is to create a main task.
 *                  5) Task of executing soft timers initialization.
 *                  6) Idle task initialization.
 *                  7) Start scheduler
 *
 * @revision
 * Date         Author          Notes
 * 2020-03-01   OneOS Team      First version
 ***********************************************************************************************************************
 */

#include <oneos_config.h>
#include <os_types.h>
#include <os_errno.h>
#include <os_stddef.h>
#include <os_task.h>
#include <os_hw.h>
#include <os_idle.h>

#include "os_kernel_internal.h"

#define STARTUP_TAG                 "STARTUP"

#ifndef OS_MAIN_TASK_STACK_SIZE
#define OS_MAIN_TASK_STACK_SIZE     2048
#endif

#ifndef OS_MAIN_TASK_PRIORITY
#define OS_MAIN_TASK_PRIORITY       (OS_TASK_PRIORITY_MAX / 3)
#endif

/* If there is not enable heap, we should use static task and stack. */
#ifndef OS_USING_HEAP
OS_ALIGN(OS_ALIGN_SIZE)
static os_uint8_t   gs_os_main_stack[OS_MAIN_TASK_STACK_SIZE];
static os_task_t    gs_os_main_task;
#endif


/**
 ***********************************************************************************************************************
 * Auto Initialization will initialize some driver and components as following order:
 * os_init_start        --> 0
 * 
 * os_board_init_start  --> 0.end
 * OS_BOARD_INIT        --> 1
 * os_board_init_end    --> 1.end
 *
 * OS_PREV_INIT         --> 2
 * OS_DEVICE_INIT       --> 3
 * OS_CMPOENT_INIT      --> 4
 * OS_ENV_INIT          --> 5
 * OS_APP_INIT          --> 6
 *
 * os_init_end          --> 6.end
 *
 * These automatically initializaiton, the driver or component initial function must
 * be defined with:
 * OS_BOARD_INIT(fn);
 * OS_PREV_INIT(fn);
 * OS_DEVICE_INIT(fn);
 * ...
 * OS_APP_INIT(fn);
 * etc.
 ***********************************************************************************************************************
 */

static os_int32_t os_init_start(void)
{
    return 0;
}
OS_INIT_EXPORT(os_init_start, "0");

static os_int32_t os_board_init_start(void)
{
    return 0;
}
OS_INIT_EXPORT(os_board_init_start, "0.end");

static os_int32_t os_board_init_end(void)
{
    return 0;
}
OS_INIT_EXPORT(os_board_init_end, "1.end");

static int os_init_end(void)
{
    return 0;
}
OS_INIT_EXPORT(os_init_end, "6.end");


/**
 ***********************************************************************************************************************
 * @brief           Auto initialization for board.
 *
 * @param           No parameter.
 *
 * @return          No return value.
 ***********************************************************************************************************************
 */
void os_board_auto_init(void)
{
    const os_init_fn_t *fn_ptr_board_init_start;
    const os_init_fn_t *fn_ptr_board_init_end;
    const os_init_fn_t *fn_ptr;

    fn_ptr_board_init_start = &__os_call_os_board_init_start + 1;
    fn_ptr_board_init_end   = &__os_call_os_board_init_end - 1;

    for (fn_ptr = fn_ptr_board_init_start; fn_ptr <= fn_ptr_board_init_end; fn_ptr++)
    {
        (void)(*fn_ptr)();
    }

    return;
}

/**
 ***********************************************************************************************************************
 * @brief           Auto initialization for others (pre/device/component/env/app).
 *
 * @param           No parameter.
 *
 * @return          No return value.
 ***********************************************************************************************************************
 */
static void os_other_auto_init(void)
{
    const os_init_fn_t *fn_ptr_other_init_start;
    const os_init_fn_t *fn_ptr_other_init_end;
    const os_init_fn_t *fn_ptr;

    fn_ptr_other_init_start = &__os_call_os_board_init_end + 1;
    fn_ptr_other_init_end   = &__os_call_os_init_end - 1;

    for (fn_ptr = fn_ptr_other_init_start; fn_ptr <= fn_ptr_other_init_end; fn_ptr++)
    {
        (void)(*fn_ptr)();
    }

    return;
}

/**
 ***********************************************************************************************************************
 * @brief           The system main task
 *
 * @param[in]       para            The private data for system main task
 *
 * @return          No return value.
 ***********************************************************************************************************************
 */
static void os_main_task_entry(void *para)
{
    /* Auto initialization for pre/device/component/env/app */
    os_other_auto_init();

/* Invoke system main function */
#if defined(__CC_ARM) || defined(__CLANG_ARM)
    extern int $Super$$main(void);
    $Super$$main();
#elif defined(__ICCARM__) || defined(__GNUC__)
    extern int main(void);
    main();
#endif
}

/**
 ***********************************************************************************************************************
 * @brief           Application initialization. The important job is to create a main task.
 *
 * @param           No parameter.
 *
 * @return          No return value.
 ***********************************************************************************************************************
 */
static void os_application_init(void)
{
    os_task_t *task;

#ifdef OS_USING_HEAP
    task = os_task_create("main", 
                          os_main_task_entry, 
                          OS_NULL,
                          OS_MAIN_TASK_STACK_SIZE,
                          OS_MAIN_TASK_PRIORITY,
                          20);
    OS_ASSERT(OS_NULL != task);
#else
    os_err_t ret;

    task = &gs_os_main_task;
    ret = os_task_init(task,
                       "main", 
                       os_main_task_entry, 
                       OS_NULL,
                       gs_os_main_stack,
                       OS_MAIN_TASK_STACK_SIZE,
                       OS_MAIN_TASK_PRIORITY,
                       20);
    OS_ASSERT(OS_EOK == ret);
#endif
    
    os_task_startup(task);
    return;
}

/**
 ***********************************************************************************************************************
 * @brief           Startup OneOS.
 *
 * @param           No parameter.
 *
 * @return          No return value.
 ***********************************************************************************************************************
 */
static void os_startup(void)
{
    /* Disable interrupt until first task is to be scheduled. Refer to os_hw_context_switch_to() */
    os_hw_interrupt_disable();

    /* Board initialization */
    os_hw_board_init();

    /* Timer system initialization */
    os_system_timer_init();

    /* Scheduler system initialization */
    os_system_scheduler_init();

    /* Application initialization. The important job is to create a main task */
    os_application_init();

    /* Task of executing soft timers initialization */
    os_system_timer_task_init();

    /* Idle task initialization */
    os_idle_task_init();

    /* Start scheduler */
    os_system_scheduler_start();

    /* Never reach here */
    return;
}

#if defined(__CC_ARM) || defined(__CLANG_ARM)
/* Re-define main function */
int $Sub$$main(void)
{
    /* Start up the operating system */
    os_startup();
    
    return 0;
}

#elif defined(__ICCARM__)
extern void __iar_data_init3(void);

/* __low_level_init will auto called by IAR c-startup */
int __low_level_init(void)
{
    /* Call IAR table copy function. */
    __iar_data_init3();

    /* Start up the operating system */
    os_startup();
    
    return 0;
}

#elif defined(__GNUC__)
/* Add -eentry to arm-none-eabi-gcc argument */
int entry(void)
{
    /* Start up the operating system */
    os_startup();
    
    return 0;
}
#endif

/**
 ***********************************************************************************************************************
 * @brief           Board initialization.
 *
 * @attention       This function is weak, and could be implemented in BSP.
 *
 * @param           No parameter.
 *
 * @return          No return value.
 ***********************************************************************************************************************
 */
OS_WEAK void os_hw_board_init(void)
{
    return;
}

