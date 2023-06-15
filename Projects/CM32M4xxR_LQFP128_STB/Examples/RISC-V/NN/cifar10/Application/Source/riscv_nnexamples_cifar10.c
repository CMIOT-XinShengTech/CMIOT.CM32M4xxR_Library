/* ----------------------------------------------------------------------
* Copyright (C) 2010-2018 Arm Limited. All rights reserved.
* Copyright (c) 2019 Nuclei Limited. All rights reserved.
*
*
* Project:       NMSIS NN Library
* Title:         riscv_nnexamples_cifar10.cpp
*
* Description:   Convolutional Neural Network Example
*
* Target Processor: RISC-V Cores
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*   - Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   - Redistributions in binary form must reproduce the above copyright
*     notice, this list of conditions and the following disclaimer in
*     the documentation and/or other materials provided with the
*     distribution.
*   - Neither the name of Arm LIMITED nor the names of its contributors
*     may be used to endorse or promote products derived from this
*     software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
* -------------------------------------------------------------------- */

/**
 * @ingroup groupExamples
 */

/**
 * @defgroup CNNExample Convolutional Neural Network Example
 *
 * \par Description:
 * \par
 * Demonstrates a convolutional neural network (CNN) example with the use of convolution,
 * ReLU activation, pooling and fully-connected functions.
 *
 * \par Model definition:
 * \par
 * The CNN used in this example is based on CIFAR-10 example from Caffe [1].
 * The neural network consists
 * of 3 convolution layers interspersed by ReLU activation and max pooling layers, followed by a
 * fully-connected layer at the end. The input to the network is a 32x32 pixel color image, which will
 * be classified into one of the 10 output classes.
 * This example model implementation needs 32.3 KB to store weights, 40 KB for activations and
 * 3.1 KB for storing the \c im2col data.
 *
 * \image html CIFAR10_CNN.png "Neural Network model definition"
 *
 * \par Variables Description:
 * \par
 * \li \c conv1_wt, \c conv2_wt, \c conv3_wt are convolution layer weight matrices
 * \li \c conv1_bias, \c conv2_bias, \c conv3_bias are convolution layer bias arrays
 * \li \c ip1_wt, ip1_bias point to fully-connected layer weights and biases
 * \li \c input_data points to the input image data
 * \li \c output_data points to the classification output
 * \li \c col_buffer is a buffer to store the \c im2col output
 * \li \c scratch_buffer is used to store the activation data (intermediate layer outputs)
 *
 * \par NMSIS DSP Software Library Functions Used:
 * \par
 * - riscv_convolve_HWC_q7_RGB()
 * - riscv_convolve_HWC_q7_fast()
 * - riscv_relu_q7()
 * - riscv_maxpool_q7_HWC()
 * - riscv_avepool_q7_HWC()
 * - riscv_fully_connected_q7_opt()
 * - riscv_fully_connected_q7()
 *
 * <b> Refer  </b>
 * \link riscv_nnexamples_cifar10.cpp \endlink
 *
 * \par [1] https://github.com/BVLC/caffe
 */

#include <stdint.h>
#include <stdio.h>
#include "riscv_math.h"
#include "riscv_nnexamples_cifar10_parameter.h"
#include "riscv_nnexamples_cifar10_weights.h"

#include "riscv_nnfunctions.h"
#include "riscv_nnexamples_cifar10_inputs.h"
#include "image_data.h"
#include "bench.h"

#include "log.h"

#ifdef _RTE_
#include "RTE_Components.h"
#ifdef RTE_Compiler_EventRecorder
#include "EventRecorder.h"
#endif
#endif
#include "cm32m4xxr_rcc.h"
// include the input and weights
static q7_t conv1_wt[CONV1_IM_CH * CONV1_KER_DIM * CONV1_KER_DIM * CONV1_OUT_CH] = CONV1_WT;
static q7_t conv1_bias[CONV1_OUT_CH] = CONV1_BIAS;

static q7_t conv2_wt[CONV2_IM_CH * CONV2_KER_DIM * CONV2_KER_DIM * CONV2_OUT_CH] = CONV2_WT;
static q7_t conv2_bias[CONV2_OUT_CH] = CONV2_BIAS;

static q7_t conv3_wt[CONV3_IM_CH * CONV3_KER_DIM * CONV3_KER_DIM * CONV3_OUT_CH] = CONV3_WT;
static q7_t conv3_bias[CONV3_OUT_CH] = CONV3_BIAS;

static q7_t ip1_wt[IP1_DIM * IP1_OUT] = IP1_WT;
static q7_t ip1_bias[IP1_OUT] = IP1_BIAS;

/* Here the image_data should be the raw uint8 type RGB image in [RGB, RGB, RGB ... RGB] format */
#define _DECLARE_IMAGE(img) static uint8_t image_data[CONV1_IM_CH * CONV1_IM_DIM * CONV1_IM_DIM] = IMG_DATA_##img; \
                           const char *image_name = #img;
#define DECLARE_IMAGE(img) _DECLARE_IMAGE(img)
// Change the DECLARE_IMAGE(imgno) to select different images
// img could be airplane, automobile, bird, cat, deer, dog, horse, ship, truck
// no could be 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
// eg. Use deer1:
// DECLARE_IMAGE(deer1);
// eg. Use dog10:
// DECLARE_IMAGE(dog10);
#ifndef TEST_IMAGE
#define TEST_IMAGE deer1
#endif
DECLARE_IMAGE(TEST_IMAGE);

q7_t      output_data[IP1_OUT];

//vector buffer: max(im2col buffer,average pool buffer, fully connected buffer)
q7_t      col_buffer[2 * 5 * 5 * 32 * 2];

q7_t      scratch_buffer[32 * 32 * 10 * 4];

const char* cifar10_label[] = {"Plane", "Car", "Bird", "Cat", "Deer", "Dog", "Frog", "Horse", "Ship", "Truck"};

int main()
{
  #ifdef RTE_Compiler_EventRecorder
  EventRecorderInitialize (EventRecordAll, 1);  // initialize and start Event Recorder
  #endif
  log_init();
  printf("start execution cnn to classify image %s\n", image_name);
  /* start the execution */

  q7_t     *img_buffer1 = scratch_buffer;
  q7_t     *img_buffer2 = img_buffer1 + 32 * 32 * 32;

  BENCH_INIT;

  /* input pre-processing */
  BENCH_START(preprocess);
  int mean_data[3] = INPUT_MEAN_SHIFT;
  unsigned int scale_data[3] = INPUT_RIGHT_SHIFT;

  //数据预处理，加快收敛速度
  for (int i=0;i<32*32*3; i+=3) {
    img_buffer2[i] =   (q7_t)__SSAT( ((((int)image_data[i]   - mean_data[0])<<7) + (0x1<<(scale_data[0]-1)))
                             >> scale_data[0], 8);
    img_buffer2[i+1] = (q7_t)__SSAT( ((((int)image_data[i+1] - mean_data[1])<<7) + (0x1<<(scale_data[1]-1)))
                             >> scale_data[1], 8);
    img_buffer2[i+2] = (q7_t)__SSAT( ((((int)image_data[i+2] - mean_data[2])<<7) + (0x1<<(scale_data[2]-1)))
                             >> scale_data[2], 8);
  }
  BENCH_END(preprocess);

  BENCH_START(riscv_convolve_HWC_q7_RGB);
  // conv1 img_buffer2 -> img_buffer1
  riscv_convolve_HWC_q7_RGB(img_buffer2, CONV1_IM_DIM, CONV1_IM_CH, conv1_wt, CONV1_OUT_CH, CONV1_KER_DIM, CONV1_PADDING,
                          CONV1_STRIDE, conv1_bias, CONV1_BIAS_LSHIFT, CONV1_OUT_RSHIFT, img_buffer1, CONV1_OUT_DIM,
                          (q15_t *) col_buffer, NULL);

  BENCH_END(riscv_convolve_HWC_q7_RGB);

  BENCH_START(riscv_relu_q7);
  riscv_relu_q7(img_buffer1, CONV1_OUT_DIM * CONV1_OUT_DIM * CONV1_OUT_CH);
  BENCH_END(riscv_relu_q7);

  BENCH_START(riscv_maxpool_q7_HWC);
  // pool1 img_buffer1 -> img_buffer2
  riscv_maxpool_q7_HWC(img_buffer1, CONV1_OUT_DIM, CONV1_OUT_CH, POOL1_KER_DIM,
                     POOL1_PADDING, POOL1_STRIDE, POOL1_OUT_DIM, NULL, img_buffer2);
  BENCH_END(riscv_maxpool_q7_HWC);

  BENCH_START(riscv_convolve_HWC_q7_fast);
  // conv2 img_buffer2 -> img_buffer1
  riscv_convolve_HWC_q7_fast(img_buffer2, CONV2_IM_DIM, CONV2_IM_CH, conv2_wt, CONV2_OUT_CH, CONV2_KER_DIM,
                           CONV2_PADDING, CONV2_STRIDE, conv2_bias, CONV2_BIAS_LSHIFT, CONV2_OUT_RSHIFT, img_buffer1,
                           CONV2_OUT_DIM, (q15_t *) col_buffer, NULL);
  BENCH_END(riscv_convolve_HWC_q7_fast);

  BENCH_START(riscv_relu_q7);
  riscv_relu_q7(img_buffer1, CONV2_OUT_DIM * CONV2_OUT_DIM * CONV2_OUT_CH);
  BENCH_END(riscv_relu_q7);

  BENCH_START(riscv_maxpool_q7_HWC);
  // pool2 img_buffer1 -> img_buffer2
  riscv_maxpool_q7_HWC(img_buffer1, CONV2_OUT_DIM, CONV2_OUT_CH, POOL2_KER_DIM,
                     POOL2_PADDING, POOL2_STRIDE, POOL2_OUT_DIM, col_buffer, img_buffer2);
  BENCH_END(riscv_maxpool_q7_HWC);

  BENCH_START(riscv_convolve_HWC_q7_fast);
  // conv3 img_buffer2 -> img_buffer1
  riscv_convolve_HWC_q7_fast(img_buffer2, CONV3_IM_DIM, CONV3_IM_CH, conv3_wt, CONV3_OUT_CH, CONV3_KER_DIM,
                           CONV3_PADDING, CONV3_STRIDE, conv3_bias, CONV3_BIAS_LSHIFT, CONV3_OUT_RSHIFT, img_buffer1,
                           CONV3_OUT_DIM, (q15_t *) col_buffer, NULL);
  BENCH_END(riscv_convolve_HWC_q7_fast);

  BENCH_START(riscv_relu_q7);
  riscv_relu_q7(img_buffer1, CONV3_OUT_DIM * CONV3_OUT_DIM * CONV3_OUT_CH);
  BENCH_END(riscv_relu_q7);

  BENCH_START(riscv_maxpool_q7_HWC);
  // pool3 img_buffer-> img_buffer2
  riscv_maxpool_q7_HWC(img_buffer1, CONV3_OUT_DIM, CONV3_OUT_CH, POOL3_KER_DIM,
                     POOL3_PADDING, POOL3_STRIDE, POOL3_OUT_DIM, col_buffer, img_buffer2);
  BENCH_END(riscv_maxpool_q7_HWC);

  BENCH_START(riscv_fully_connected_q7_opt);
  riscv_fully_connected_q7_opt(img_buffer2, ip1_wt, IP1_DIM, IP1_OUT, IP1_BIAS_LSHIFT, IP1_OUT_RSHIFT, ip1_bias,
                             output_data, (q15_t *) img_buffer1);
  BENCH_END(riscv_fully_connected_q7_opt);

  BENCH_START(riscv_softmax_q7);
  riscv_softmax_q7(output_data, 10, output_data);
  BENCH_END(riscv_softmax_q7);

  float confidence = 0.0;
  for (int i = 0; i < 10; i++) {
      confidence = (output_data[i]/127.0)*100;
      printf("label %d: %d, %s, %.2f%%\n", \
              i, output_data[i], cifar10_label[i], confidence);
  }
  BENCH_FINISH;

  while(1);
  return 0;
}
