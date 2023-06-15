#ifndef _RISCV_CONVOLVE_Q7_HWC_ACCL_H
#define _RISCV_CONVOLVE_Q7_HWC_ACCL_H

#include "riscv_nnfunctions.h"

#ifdef __cplusplus
extern "C" {
#endif


// CONV NICE Accelerator
__STATIC_FORCEINLINE int jj_init_ch(uint16_t ch_im_in, uint16_t ch_im_out)
{
    int zero = 0;

    asm volatile(
        ".insn r 0xb , 3 ,3 , x0 , %1 , %2"
        : "=r"(zero)
        : "r"(ch_im_in), "r"(ch_im_out));
}

__STATIC_FORCEINLINE int jj_init_im(uint16_t dim_im_in, uint16_t dim_im_out)
{
    int zero = 0;

    asm volatile(
        ".insn r 0xb , 3 ,4 , x0 , %1 , %2"
        : "=r"(zero)
        : "r"(dim_im_in), "r"(dim_im_out));
}

__STATIC_FORCEINLINE int jj_init_fs(uint16_t dim_kernel, uint16_t stride)
{
    int zero = 0;

    asm volatile(
        ".insn r 0xb , 3 ,5 , x0 , %1 , %2"
        : "=r"(zero)
        : "r"(dim_kernel), "r"(stride));
}

__STATIC_FORCEINLINE int jj_init_pw(uint16_t padding, int wt_addr)
{
    int zero = 0;

    asm volatile(
        ".insn r 0xb , 3 ,6 , x0 , %1 , %2"
        : "=r"(zero)
        : "r"(padding), "r"(wt_addr));
}

__STATIC_FORCEINLINE int jj_init_imaddr(int im_in_addr, int im_out_addr)
{
    int zero = 0;

    asm volatile(
        ".insn r 0xb , 3 ,7 , x0 , %1 , %2"
        : "=r"(zero)
        : "r"(im_in_addr), "r"(im_out_addr));
}

__STATIC_FORCEINLINE int jj_init_bias(int shifts, int bias_addr)
{
    int zero = 0;

    asm volatile(
        ".insn r 0xb , 3 ,11 , x0 , %1 , %2"
        : "=r"(zero)
        : "r"(shifts), "r"(bias_addr));
}

__STATIC_FORCEINLINE int jj_loop()
{
    asm volatile(".insn r 0xb , 4 ,8 , x0 , x0 , x0");
}


riscv_status riscv_convolve_q7_HWC_accl(const q7_t * Im_in,
                          const uint16_t dim_im_in,
                          const uint16_t ch_im_in,
                          const q7_t * wt,
                          const uint16_t ch_im_out,
                          const uint16_t dim_kernel,
                          const uint16_t padding,
                          const uint16_t stride,
                          const q7_t * bias,
                          const uint16_t bias_shift,
                          const uint16_t out_shift,
                          q7_t * Im_out, 
                          const uint16_t dim_im_out, 
                          q15_t * bufferA, 
                          q7_t * bufferB
                          );


#ifdef __cplusplus
}
#endif

#endif
