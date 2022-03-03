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
 * @file        os_irq.c
 *
 * @brief       This file implements some os irq utils.
 *
 * @revision
 * Date         Author          Notes
 * 2020-02-19   OneOS Team      First Version
 ***********************************************************************************************************************
 */
 
#include <os_irq.h>
#include <os_dbg.h>
#include <os_module.h>
#include <os_hw.h>
#include "os_kernel_internal.h"

#define IRQ_TAG         "IRQ"

#ifdef OS_USING_HOOK

static void (*gs_os_interrupt_enter_hook)(void) = OS_NULL;
static void (*gs_os_interrupt_leave_hook)(void) = OS_NULL;

/**
 ***********************************************************************************************************************
 * @brief           This function set the interrupt enter hook, which is called when entering an interrupt.
 *
 * @param[in]       hook             The hook function pointer.
 *
 * @return          No return value.
 ***********************************************************************************************************************
 */
void os_interrupt_enter_set_hook(void (*hook)(void))
{
    gs_os_interrupt_enter_hook = hook;
}

/**
 ***********************************************************************************************************************
 * @brief           This function set the interrupt leave hook, which is called when leaving an interrupt.
 *
 * @param           None
 *
 * @return          No return value.
 ***********************************************************************************************************************
 */
void os_interrupt_leave_set_hook(void (*hook)(void))
{
    gs_os_interrupt_leave_hook = hook;
}
#endif

/* Interrupt nesting level */
volatile os_uint8_t g_os_interrupt_nest = 0;

/**
 ***********************************************************************************************************************
 * @brief           This function increase the interrupt nesting level by 1.
 *
 * @attention       This function is supposed to be called every time we enter an interrupt.
 *
 * @param           None
 *
 * @return          No return value.
 ***********************************************************************************************************************
 */
void os_interrupt_enter(void)
{
    os_base_t level;

    level = os_hw_interrupt_disable();

    g_os_interrupt_nest++;

    OS_OBJECT_HOOK_CALL(gs_os_interrupt_enter_hook,());

    os_hw_interrupt_enable(level);
}
EXPORT_SYMBOL(os_interrupt_enter);

/**
 ***********************************************************************************************************************
 * @brief           This function decrease the interrupt nesting level by 1.
 *
 * @attention       This function is supposed to be called every time we leave an interrupt.
 *
 * @param           None
 *
 * @return          No return value.
 ***********************************************************************************************************************
 */
void os_interrupt_leave(void)
{
    os_base_t level;

    level = os_hw_interrupt_disable();

    g_os_interrupt_nest--;

    OS_OBJECT_HOOK_CALL(gs_os_interrupt_leave_hook,());

    os_hw_interrupt_enable(level);
}
EXPORT_SYMBOL(os_interrupt_leave);

/**
 ***********************************************************************************************************************
 * @brief           This function get the interrupt nesting level.
 *
 * @param           None
 *
 * @return          Return the interrupt nesting level.
 ***********************************************************************************************************************
 */
os_uint8_t os_interrupt_get_nest(void)
{
    return g_os_interrupt_nest;
}
EXPORT_SYMBOL(os_interrupt_get_nest);

EXPORT_SYMBOL(os_hw_interrupt_disable);
EXPORT_SYMBOL(os_hw_interrupt_enable);

