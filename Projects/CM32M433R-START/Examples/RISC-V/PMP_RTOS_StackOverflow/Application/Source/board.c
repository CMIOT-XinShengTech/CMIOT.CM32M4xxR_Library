/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-04-22     hqfang       first version
 *
 */

#include "board.h"
#include "bsp.h"
#include "cpuport.h"
#include "nuclei_sdk_soc.h"
#include <rtthread.h>
#include <string.h>

//PMP Exception Handler
void PMP_Exception_Handler(unsigned long mcause, unsigned long sp) {
  rt_kprintf("PMP Exception Occures Run at 0x%lx, Fetching Memory at 0x%lx\r\n!!!", __RV_CSR_READ(CSR_MEPC), __RV_CSR_READ(CSR_MBADADDR));

  rt_interrupt_enter();
  static rt_thread_t fault_thread = RT_NULL;
  rt_thread_t thread = rt_thread_self();
  rt_kprintf("\r\n########################################################\r\n", thread->name);
  rt_kprintf("!!!!!!!!!thread %s stack overflow!!!!!!!!!", thread->name);
  rt_thread_detach(thread);
  rt_kprintf("!!!!!!!!!thread %s terminated!!!!!!!!!", thread->name);
  rt_kprintf("\r\n########################################################\r\n", thread->name);
  fault_thread = thread;
  rt_schedule();
  rt_interrupt_leave();
}

//Configure test_array Acess Permission on PMP
void PMP_Config() {

  PMP_ClearRegion(PMP_REGION_NUMBER0);
  PMP_ClearRegion(PMP_REGION_NUMBER7);

  PMP_Region_InitTypeDef pmp_init;

  pmp_init.Number = PMP_REGION_NUMBER7;
  pmp_init.Enable = PMP_REGION_ENABLE;                   // Enable Configuration
  pmp_init.Lock = PMP_REGION_UNLOCK;                     // Configuration Lock, may not modify unless reset, and also match in Machine Mode
  pmp_init.BaseAddress = 0;                              //Seting test_array Base
  pmp_init.Size = PMP_REGION_SIZE_4GB;                   //Setting array size
  pmp_init.AddressMatching = PMP_ADDRESS_MATCHING_NAPOT; //Setting PMP Size to NAPOT mode -> 2^n
  pmp_init.AccessPermission = PMP_ACCESS_RWX;            //Setting array permission is Read Only

  PMP_ConfigRegion(&pmp_init);

  //PMP_ConfigRegion(&pmp_init);
  sPMP_ClearRegion(SPMP_REGION_NUMBER7);
  sPMP_Region_InitTypeDef spmp_init;
  spmp_init.Number = SPMP_REGION_NUMBER7;
  spmp_init.UserMode = SPMP_USERMODE_SET;
  spmp_init.Enable = SPMP_REGION_ENABLE;                   // Enable Configuration
  spmp_init.Lock = SPMP_REGION_UNLOCK;                     // Configuration Lock, may not modify unless reset, and also match in Machine Mode
  spmp_init.BaseAddress = 0;                               //Seting test_array Base
  spmp_init.Size = SPMP_REGION_SIZE_4GB;                   //Setting array size
  spmp_init.AddressMatching = SPMP_ADDRESS_MATCHING_NAPOT; //Setting PMP Size to NAPOT mode -> 2^n
  spmp_init.AccessPermission = SPMP_ACCESS_RWX;            //Setting array permission is Read Only
  sPMP_ConfigRegion(&spmp_init);
  // Register PMP Exception Handler
  Exception_Register_EXC(CAUSE_FAULT_FETCH, (unsigned long)PMP_Exception_Handler);
  Exception_Register_EXC(CAUSE_FAULT_LOAD, (unsigned long)PMP_Exception_Handler);
  Exception_Register_EXC(CAUSE_FAULT_STORE, (unsigned long)PMP_Exception_Handler);

  __RV_CSR_SET(CSR_MSTATUS, MSTATUS_MPRV);
}

void uart_init() {

	log_init();

}

void rt_broad_init() {
  uart_init();
  PMP_Config();
}

/** _end symbol defined in linker script of Nuclei SDK */
extern void *_end;

/** _heap_end symbol defined in linker script of Nuclei SDK */
extern void *_heap_end;
#define HEAP_BEGIN &_end
#define HEAP_END &_heap_end

/*
 * - Implemented and defined in Nuclei SDK system_<Device>.c file
 * - Required macro NUCLEI_BANNER set to 0
 */
extern void _init(void);

/**
 * @brief Setup hardware board for rt-thread
 *
 */
void rt_hw_board_init(void) {

  /* OS Tick Configuration */
  rt_hw_ticksetup();

#ifdef RT_USING_HEAP
  rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif

  _init(); // __libc_init_array is not used in RT-Thread

  rt_broad_init();

  /* Set the shell console output device */
#ifdef RT_USING_CONSOLE
  rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

  /* Board underlying hardware initialization */
#ifdef RT_USING_COMPONENTS_INIT
  rt_components_board_init();
#endif
}

void rt_hw_console_output(const char *str) {
  uint32_t i = 0;
  uint32_t len = strlen(str);
  for (i = 0; i < len; i++) {
    USART_SendData(LOG_USARTx, (u8)str[i]);
    while (USART_GetFlagStatus(LOG_USARTx, USART_FLAG_TXDE) == RESET)
      ;
  }
}
/******************** end of file *******************/
