
#include "riscv_encoding.h"

.section .text.system
/* In CLIC mode, the exeception entry must be 64bytes aligned */
.align 6

.global configMainStack
configMainStack:
  csrw CSR_MSCRATCH, a0
  jr ra



.global enterUserMode
enterUserMode:
  li t0, MSTATUS_MPP
  csrc mstatus, t0
  csrw mepc, a0
  mv a0,a1
  mret


 
