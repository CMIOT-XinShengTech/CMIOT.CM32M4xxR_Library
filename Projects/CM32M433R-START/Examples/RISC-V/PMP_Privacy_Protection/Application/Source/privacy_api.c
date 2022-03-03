#include "privacy.h"
#include "nuclei_sdk_soc.h"
#include <stdio.h>

#define SYSTEM_CALL_PRIVACY         1

#define SYSTEM_ECALL(__num, __a0, __a1, __a2)                                    \
	({                                                                    \
		register unsigned long a0 asm("a0") = (unsigned long)(__a0);  \
		register unsigned long a1 asm("a1") = (unsigned long)(__a1);  \
		register unsigned long a2 asm("a2") = (unsigned long)(__a2);  \
		register unsigned long a7 asm("a7") = (unsigned long)(__num); \
		asm volatile("ecall"                                          \
			     : "+r"(a0)                                       \
			     : "r"(a1), "r"(a2), "r"(a7)                      \
			     : "memory");                                     \
		a0;                                                           \
	})

uint8_t privacy_encrypt_api(uint8_t *src, uint16_t src_len, uint8_t * dst)
{
  SYSTEM_ECALL(SYSTEM_CALL_PRIVACY,src,src_len,dst);
  return 0;
}


void PMP_SYSCALL_Handler(unsigned long mcause, unsigned long sp) {
  printf("PMP Exception Occures Run at 0x%lx, Enter System Call !!!\r\n", __RV_CSR_READ(CSR_MEPC));
  uint32_t saved_regs = sp;
  uint32_t mepc = ((uint32_t *)saved_regs)[12];
  uint32_t funcId = ((uint32_t *)saved_regs)[15];
  switch(funcId)
  {
    case SYSTEM_CALL_PRIVACY:
      printf("Enter Privacy System CALL\r\n");
      uint8_t *src = (uint8_t *)((uint32_t *)saved_regs)[5];
      uint16_t src_len = (uint16_t)((uint32_t *)saved_regs)[6];
      uint8_t *out = (uint8_t *)((uint32_t *)saved_regs)[7];
      privacy_encrypt(src, src_len, out);

    break;
    default:
      printf("System Call not Defined\r\n");
      while(1);
      return;
  }

  mepc += 4;
  ((uint32_t *)saved_regs)[12] = mepc;
}
