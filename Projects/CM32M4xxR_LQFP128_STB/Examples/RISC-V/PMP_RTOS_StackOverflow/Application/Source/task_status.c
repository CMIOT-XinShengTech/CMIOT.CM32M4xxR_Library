/*****************************************************************************
 * Copyright (c) 2019, China Mobile IoT Company Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * CMIOT' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY CMIOT "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL CMIOT BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file task_status.c
 * @author CMIOT Solution Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, China Mobile IoT Company Inc. All rights reserved.
 */

#include "rtthread.h"
#include "stack_mgt.h"


static struct rt_thread thread_green;
static struct rt_thread thread_red;
static uint8_t trap_var = 0;

/* trap function */
/* recursive calls cause stack overflows */
__attribute__ ((noinline))  void recursive_func() {
  uint8_t tmp[0x10] = {0};
  tmp[2] = tmp[1] + tmp[2];
  recursive_func();

  rt_kprintf("res : %d\r\n", tmp[2]);
}

/* green thread function, include trap function */
void task_green_entry(void *args) {
  while (1) {
    if (trap_var > 10) {
      rt_kprintf("enter recursive call, trigger stack overflow \r\n");
      recursive_func();
    }
    rt_kprintf("green task is running\r\n");
    rt_thread_delay(1000);

    trap_var++;
  }
}

/* red thread function,  check the running state of the system*/
void task_red_entry(void *args) {
  while (1) {
    rt_kprintf("red task is running\r\n");
    rt_thread_delay(1000);
  }
}

/* create stack protected green thread cmd*/
void green() {
  trap_var = 0;
  stack_mgt_init();
  uint8_t *stack = stack_mgt_getFreeStack();
  rt_thread_init(&thread_green,
      "green",
      task_green_entry,
      RT_NULL,
      stack,
      THREAD_STACK_SIZE,
      10,
      20);
  rt_thread_startup(&thread_green);
}

/* create observation red thread cmd*/
void red() {
  stack_mgt_init();
  uint8_t *stack = stack_mgt_getFreeStack();
  rt_thread_init(&thread_red,
      "red",
      task_red_entry,
      RT_NULL,
      stack,
      THREAD_STACK_SIZE,
      11,
      20);
  rt_thread_startup(&thread_red);
}