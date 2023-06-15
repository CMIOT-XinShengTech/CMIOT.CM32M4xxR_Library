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
 * @file        board.c
 *
 * @brief       Initializes the CPU, System clocks, and Peripheral device
 *
 * @revision
 * Date         Author          Notes
 * 2020-02-20   OneOS Team      First Version
 ***********************************************************************************************************************
 */

#include <stdint.h>
#include <os_hw.h>
#include <os_task.h>
//#include <os_device.h>
#include <riscv_encoding.h>
#include <os_memory.h>
#include <os_irq.h>
#include <os_clock.h>
//#include <drv_gpio.h>
//#include <drv_usart.h>
#include <oneos_config.h>
//#include <board.h>

extern void os_hw_ticksetup(void);
/** _stack_start symbol defined in linker script of Nuclei SDK */
extern void *_stack_start;

/** _heap_end symbol defined in linker script of Nuclei SDK */
extern void *__heap_limit;
#define HEAP_BEGIN  &__heap_limit
#define HEAP_END    &_stack_start

void os_hw_board_init()
{
    /* System Clock Update */
    /* System Tick Configuration */
    os_hw_ticksetup();

/* System Tick Configuration */
#ifdef OS_USING_PIN
    os_hw_pin_init();
#endif

#if defined(OS_USING_HEAP)
	os_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif

/* Call components board initial (use OS_BOARD_INIT()) */
#if 1//def OS_USING_COMPONENTS_INIT
    os_board_auto_init();
#endif
}

