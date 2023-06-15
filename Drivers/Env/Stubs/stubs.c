#include <stdint.h>
#include <time.h>
#include "log.h"

int metal_tty_putc(int c)
{
	USART_SendData(LOG_USARTx, (uint8_t)c);

	/* Loop until the end of transmission */
    while (USART_GetFlagStatus(LOG_USARTx, USART_FLAG_TXDE) == RESET);

    return c;
}

int metal_tty_getc(void)
{
	/* Loop until the end of transmission */
    while (USART_GetFlagStatus(LOG_USARTx, USART_FLAG_RXDNE) == RESET);

    return USART_ReceiveData(LOG_USARTx);
}

void exit(int fd)
{
    while (1) {
        __WFI();
    }
}

// clock() function implementation is added in 0.4.0 sdk release
__WEAK clock_t clock(void)
{
    uint64_t cycles = __get_rv_cycle();
    clock_t clktm;

    clktm = (cycles * CLOCKS_PER_SEC) / SystemCoreClock;
    return clktm;
}


// workaround for newlibc required
// __libc_fini_array and __libc_init_array function
__WEAK void __libc_fini_array(void)
{
}

// required by libncrt_2.0.0 in RISC-V GNU Toolchain 2022.06
extern void __SEGGER_RTL_init_heap(void *ptr, size_t size);
extern char __heap_start[];
extern char __heap_end[];

__WEAK void __libc_init_array(void)
{
    size_t heapsz = (size_t)__heap_end - (size_t)__heap_start;
    __SEGGER_RTL_init_heap((void *)__heap_start, heapsz);
}

// weak symbol for back compatiable with previous toolchain
__WEAK void __SEGGER_RTL_init_heap(void *ptr, size_t size)
{

}
