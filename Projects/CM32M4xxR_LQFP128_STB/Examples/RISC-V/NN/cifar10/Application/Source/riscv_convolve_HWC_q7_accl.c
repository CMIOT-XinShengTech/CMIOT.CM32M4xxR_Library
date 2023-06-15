
#include <riscv_convolve_hwc_q7_accl.h>


/**
 * @brief Accelerated Q7 convolution function
 * @param[in]       Im_in       pointer to input tensor
 * @param[in]       dim_im_in   input tensor dimention
 * @param[in]       ch_im_in    number of input tensor channels
 * @param[in]       wt          pointer to kernel weights
 * @param[in]       ch_im_out   number of filters, i.e., output tensor channels
 * @param[in]       dim_kernel  filter kernel size
 * @param[in]       padding     padding sizes
 * @param[in]       stride      convolution stride
 * @param[in]       bias        pointer to bias
 * @param[in]       bias_shift  amount of left-shift for bias
 * @param[in]       out_shift   amount of right-shift for output
 * @param[in,out]   Im_out      pointer to output tensor
 * @param[in]       dim_im_out  output tensor dimension
 * @param[in,out]   bufferA     pointer to buffer space for input 
 * @param[in,out]   bufferB     pointer to buffer space for output
 * @return     The function returns <code>RISCV_MATH_SUCCESS</code> 
 *
 * @details
 *
 * <b>Buffer size:</b>
 *
 * bufferA size: 2*ch_im_in*dim_kernel*dim_kernel
 *
 * bufferB size: 0
 *
 * This accelerated version is designed to work for any input tensor and weight
 * dimension. 
 */

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
                          )
{



   uint32_t  wt_addr     = (uint32_t) wt;
   uint32_t  im_in_addr  = (uint32_t) Im_in;
   uint32_t  im_out_addr = (uint32_t) Im_out;
   uint32_t  bias_addr   = (uint32_t) bias;

   uint32_t  shifts =  (((uint32_t)out_shift) << 16) | (uint32_t) (bias_shift);
   
   jj_init_ch (ch_im_in , ch_im_out);
   jj_init_im (dim_im_in , dim_im_out);
   jj_init_fs (dim_kernel , stride);
   jj_init_pw (padding , wt_addr);
   jj_init_imaddr (im_in_addr , im_out_addr);
   jj_init_bias(shifts, bias_addr);
   jj_loop ();

   return RISCV_MATH_SUCCESS;
}

