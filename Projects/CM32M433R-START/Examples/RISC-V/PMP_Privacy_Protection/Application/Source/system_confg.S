
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
  mret

.macro SWTICH_STACK
  csrrw sp,CSR_MSCRATCHCSW, sp
.endm

/**
 * \brief  Global interrupt disabled
 * \details
 *  This function disable global interrupt.
 * \remarks
 *  - All the interrupt requests will be ignored by CPU.
 */
.macro DISABLE_MIE
    csrc CSR_MSTATUS, MSTATUS_MIE
.endm


/**
 * \brief  Macro for context save
 * \details
 * This macro save ABI defined caller saved registers in the stack.
 * \remarks
 * - This Macro could use to save context when you enter to interrupt
 * or exception
*/
/* Save caller registers */
.macro SAVE_CONTEXT
    /* Allocate stack space for context saving */
#ifndef __riscv_32e
    addi sp, sp, -20*REGBYTES
#else
    addi sp, sp, -14*REGBYTES
#endif /* __riscv_32e */

    STORE x1,	0*REGBYTES(sp)
    STORE x4,	1*REGBYTES(sp)
    STORE x5,	2*REGBYTES(sp)
    STORE x6,	3*REGBYTES(sp)
    STORE x7,	4*REGBYTES(sp)
    STORE x10,	5*REGBYTES(sp)
    STORE x11,	6*REGBYTES(sp)
    STORE x12,	7*REGBYTES(sp)
    STORE x13,	8*REGBYTES(sp)
    STORE x14,	9*REGBYTES(sp)
    STORE x15,	10*REGBYTES(sp)
#ifndef __riscv_32e
    STORE x16,	14*REGBYTES(sp)
    STORE x17,	15*REGBYTES(sp)
    STORE x28,	16*REGBYTES(sp)
    STORE x29,	17*REGBYTES(sp)
    STORE x30,	18*REGBYTES(sp)
    STORE x31,	19*REGBYTES(sp)
#endif /* __riscv_32e */
.endm

/**
 * \brief  Macro for restore caller registers
 * \details
 * This macro restore ABI defined caller saved registers from stack.
 * \remarks
 * - You could use this macro to restore context before you want return
 * from interrupt or exeception
 */
/* Restore caller registers */
.macro RESTORE_CONTEXT
    LOAD x1,	0*REGBYTES(sp)
    LOAD x4,	1*REGBYTES(sp)
    LOAD x5,	2*REGBYTES(sp)
    LOAD x6,	3*REGBYTES(sp)
    LOAD x7,	4*REGBYTES(sp)
    LOAD x10,	5*REGBYTES(sp)
    LOAD x11,	6*REGBYTES(sp)
    LOAD x12,	7*REGBYTES(sp)
    LOAD x13,	8*REGBYTES(sp)
    LOAD x14,	9*REGBYTES(sp)
    LOAD x15,	10*REGBYTES(sp)
#ifndef __riscv_32e
    LOAD x16,	14*REGBYTES(sp)
    LOAD x17,	15*REGBYTES(sp)
    LOAD x28,	16*REGBYTES(sp)
    LOAD x29,	17*REGBYTES(sp)
    LOAD x30,	18*REGBYTES(sp)
    LOAD x31,	19*REGBYTES(sp)

    /* De-allocate the stack space */
    addi sp, sp, 20*REGBYTES
#else
    /* De-allocate the stack space */
    addi sp, sp, 14*REGBYTES
#endif /* __riscv_32e */

.endm

/**
 * \brief  Macro for save necessary CSRs to stack
 * \details
 * This macro store MCAUSE, MEPC, MSUBM to stack.
 */
.macro SAVE_CSR_CONTEXT
    /* Store CSR mcause to stack using pushmcause */
    csrrwi  x0, CSR_PUSHMCAUSE, 11
    /* Store CSR mepc to stack using pushmepc */
    csrrwi  x0, CSR_PUSHMEPC, 12
    /* Store CSR msub to stack using pushmsub */
    csrrwi  x0, CSR_PUSHMSUBM, 13
.endm

/**
 * \brief  Macro for restore necessary CSRs from stack
 * \details
 * This macro restore MSUBM, MEPC, MCAUSE from stack.
 */
.macro RESTORE_CSR_CONTEXT
    LOAD x5,  13*REGBYTES(sp)
    csrw CSR_MSUBM, x5
    LOAD x5,  12*REGBYTES(sp)
    csrw CSR_MEPC, x5
    LOAD x5,  11*REGBYTES(sp)
    csrw CSR_MCAUSE, x5
.endm

.section .text.trap
.align 6
.global exc_entry
exc_entry:

    SWTICH_STACK
    /* Save the caller saving registers (context) */
    SAVE_CONTEXT
    /* Save the necessary CSR registers */
    SAVE_CSR_CONTEXT
    /*
     * Set the exception handler function arguments
     * argument 1: mcause value
     * argument 2: current stack point(SP) value
     */
    csrr a0, mcause
    mv a1, sp
    /*
     * TODO: Call the exception handler function
     * By default, the function template is provided in
     * system_Device.c, you can adjust it as you want
     */
    call core_exception_handler

    //li t0, MSTATUS_MPP
    //csrc mstatus, t0
    /* Restore the necessary CSR registers */
    RESTORE_CSR_CONTEXT
    /* Restore the caller saving registers (context) */
    RESTORE_CONTEXT

    SWTICH_STACK
    /* Return to regular code */
    mret
