#ifndef __STACK_MGT_H__
#define __sTACK_MGT_H__

#include <stdint.h>

#define THREAD_STACK_SIZE     0x800
#define MAX_STACK_SLOT        4

void stack_mgt_init();

uint8_t * stack_mgt_getFreeStack();

void stack_mgt_freeStack(uint8_t * stack);

#endif
