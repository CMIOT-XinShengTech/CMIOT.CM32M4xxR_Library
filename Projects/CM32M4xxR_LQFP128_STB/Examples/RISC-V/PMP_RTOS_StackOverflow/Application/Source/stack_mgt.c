#include "stack_mgt.h"
#include "nuclei_sdk_soc.h"
#include <stdint.h>
#include <string.h>
//thread stack managment
//thread stack is 8KB Size, and located at 0x200019000, support 4 thread slot, each 2KB;
#define USER_STACK_BASE 0x20019000
#define USER_STACK_SIZE (THREAD_STACK_SIZE * MAX_STACK_SLOT)

static uint8_t tstack[THREAD_STACK_SIZE * MAX_STACK_SLOT] __attribute__((section(".tstack")));
static uint8_t s_stackSlot[MAX_STACK_SLOT] = {0};
static uint8_t stackInit = 0;


/**
 * user stack segment init
 * fill user stack to zero
 */
void stack_mgt_init() {
  if (stackInit == 0) {
    memset(tstack, 0, THREAD_STACK_SIZE * MAX_STACK_SLOT);
    stackInit = 1;
  } else {
  }
}

/**
 * get available user stack segment
 * @return stack base pointer
 */
uint8_t *stack_mgt_getFreeStack() {
  uint8_t i = 0;
  for (i = 0; i < MAX_STACK_SLOT; i++) {
    if (s_stackSlot[i] == 0) {
      s_stackSlot[i] = 1;
      return tstack + i * THREAD_STACK_SIZE;
    }
  }
  return (void *)0;
}

/**
 * free user stack, when thread exit
 * @param stack user stack base pointer
 */
void stack_mgt_freeStack(uint8_t *stack) {
  s_stackSlot[(stack - tstack) / THREAD_STACK_SIZE] = 0;
}

/**
 * PMP check hook function during thread scheduling
 * @param flag		n/a
 * @param stack_addr	user stack base pointer
 * @param stack_size	user stack size
 */
void rt_stack_mpu_hook(uint8_t flag, uint8_t *stack_addr, uint32_t stack_size) {
  PMP_Region_InitTypeDef pmp_init;

  if ((uint32_t)stack_addr >= USER_STACK_BASE && (uint32_t)stack_addr < (USER_STACK_BASE + USER_STACK_SIZE)) {
    pmp_init.Number = PMP_REGION_NUMBER5;
    pmp_init.Enable = PMP_REGION_ENABLE;                   // Enable Configuration
    pmp_init.Lock = PMP_REGION_UNLOCK;                     // Configuration Lock, may not modify unless reset, and also match in Machine Mode
    pmp_init.BaseAddress = (uint32_t)stack_addr;                     //Seting Thread stack Base
    pmp_init.Size = PMP_REGION_SIZE_128B;                  //Setting stack slot size
    pmp_init.AddressMatching = PMP_ADDRESS_MATCHING_NAPOT; //Setting PMP Size to NAPOT mode -> 2^n
    pmp_init.AccessPermission = PMP_ACCESS_R;              //Setting array permission is Read Only
    PMP_ConfigRegion(&pmp_init);
  } else {
    PMP_ClearRegion(PMP_REGION_NUMBER5);
  }
}
