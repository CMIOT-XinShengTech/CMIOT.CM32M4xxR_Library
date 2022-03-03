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
 * @file        os_clock.c
 *
 * @brief       This file implements the system clock.
 *
 * @revision
 * Date         Author          Notes
 * 2020-02-12   OneOS Team      First Version
 ***********************************************************************************************************************
 */
#include <os_clock.h>
#include <os_task.h>
#include <os_module.h>
#include <os_hw.h>
#include "os_kernel_internal.h"

static os_tick_t gs_os_tick = 0;

/**
 ***********************************************************************************************************************
 * @brief           This function return the system tick count.
 *
 * @param           None
 *
 * @return          Return the system tick count.
 ***********************************************************************************************************************
 */
os_tick_t os_tick_get(void)
{
    return gs_os_tick;
}
EXPORT_SYMBOL(os_tick_get);

/**
 ***********************************************************************************************************************
 * @brief           This function set the system tick count to specified value.
 *
 * @param[in]       tick       The specified tick value.
 *
 * @return          None
 ***********************************************************************************************************************
 */
void os_tick_set(os_tick_t tick)
{
    os_base_t level;

    level = os_hw_interrupt_disable();

    gs_os_tick = tick;

    os_hw_interrupt_enable(level);
}

/**
 ***********************************************************************************************************************
 * @brief           This function is supposed to be called by tick interrupt. It do tick update related system work.
 *                  Update tick counter; maintain time slice based schedule; handle outdated timer.  
 *
 * @param           None
 *
 * @return          None
 ***********************************************************************************************************************
 */
void os_tick_increase(void)
{
    os_task_t *task;

    ++gs_os_tick;

    /* Check time slice */
    task = (os_task_t *)os_task_self();

    --(task->remaining_tick);

    if (0 == task->remaining_tick)
    {
        /* Change to initialized tick */
        task->remaining_tick = task->init_tick;

        os_task_yield();
    }

    os_timer_check();
}

/**
 ***********************************************************************************************************************
 * @brief           This function convert time in millisecond into ticks. 
 *
 * @param           ms      Time value in millisecond.
 *
 * @return          Return time value in ticks.
 ***********************************************************************************************************************
 */
os_tick_t os_tick_from_ms(os_uint32_t ms)
{
    os_tick_t tick;

    tick = OS_TICK_PER_SECOND * (ms / 1000);
    tick += (OS_TICK_PER_SECOND * (ms % 1000) + 999) / 1000;

    return tick;
}
EXPORT_SYMBOL(os_tick_from_ms);

