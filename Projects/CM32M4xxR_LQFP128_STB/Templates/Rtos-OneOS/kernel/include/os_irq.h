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
 * @file        os_irq.h
 *
 * @brief       The header file for os irq utils.
 *
 * @revision
 * Date         Author          Notes
 * 2020-02-19   OneOS Team      First Version
 ***********************************************************************************************************************
 */
 
#ifndef __OS_IRQ_H__
#define __OS_IRQ_H__

#include <oneos_config.h>
#include <os_types.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef OS_USING_HOOK
extern void os_interrupt_enter_set_hook(void (*hook)(void));
extern void os_interrupt_leave_set_hook(void (*hook)(void));
#endif

extern void       os_interrupt_enter(void);
extern void       os_interrupt_leave(void);
extern os_uint8_t os_interrupt_get_nest(void);

#ifdef __cplusplus
}
#endif

#endif

