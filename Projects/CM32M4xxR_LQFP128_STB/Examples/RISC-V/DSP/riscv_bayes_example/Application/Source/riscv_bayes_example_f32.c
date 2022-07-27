/*******************************************************************************
 *
 * COPYRIGHT(c) 2020, China Mobile IOT
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *	1. Redistributions of source code must retain the above copyright notice,
 *	   this list of conditions and the following disclaimer.
 *	2. Redistributions in binary form must reproduce the above copyright notice,
 *	   this list of conditions and the following disclaimer in the documentation
 *	   and/or other materials provided with the distribution.
 *	3. Neither the name of China Mobile IOT nor the names of its contributors
 *	   may be used to endorse or promote products derived from this software
 *	   without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *******************************************************************************/

/**
 * @file main.c
 * @author CMIOT Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */

/* ----------------------------------------------------------------------
* Copyright (C) 2019-2020 ARM Limited. All rights reserved.
* Copyright (c) 2019 Nuclei Limited. All rights reserved.
*
* $Date:         09. December 2019
* $Revision:     V1.0.0
*
* Project:       NMSIS DSP Library
* Title:         riscv_bayes_example_f32.c
*
* Description:   Example code demonstrating how to use Bayes functions.
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
*   - Neither the name of ARM LIMITED nor the names of its contributors
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
 * @defgroup BayesExample Bayes Example
 *
 * \par Description:
 * \par
 * Demonstrates the use of Bayesian classifier functions. It is complementing the tutorial
 * about classical ML with NMSIS-DSP and python scikit-learn:
 * https://developer.arm.com/solutions/machine-learning-on-arm/developer-material/how-to-guides/implement-classical-ml-with-arm-nmsis-dsp-libraries
 *
 */


/** \example riscv_bayes_example_f32.c
  */
#include "main.h"
#include "bsp.h"
#include <math.h>
#include <stdio.h>
#include "riscv_math.h"



/*
Those parameters can be generated with the python library scikit-learn.
*/
riscv_gaussian_naive_bayes_instance_f32 S;

#define NB_OF_CLASSES 3
#define VECTOR_DIMENSION 2
#define SEMIHOSTING

const float32_t theta[NB_OF_CLASSES*VECTOR_DIMENSION] = {
  1.4539529436590528f, 0.8722776016801852f,
  -1.5267934452462473f, 0.903204577814203f,
  -0.15338006360932258f, -2.9997913665803964f
}; /**< Mean values for the Gaussians */

const float32_t sigma[NB_OF_CLASSES*VECTOR_DIMENSION] = {
  1.0063470889514925f, 0.9038018246524426f,
  1.0224479953244736f, 0.7768764290432544f,
  1.1217662403241206f, 1.2303890106020325f
}; /**< Variances for the Gaussians */

const float32_t classPriors[NB_OF_CLASSES] = {
  0.3333333333333333f, 0.3333333333333333f, 0.3333333333333333f
}; /**< Class prior probabilities */

int32_t main(void)
{
  log_init();
  /*  Enable Vector  */
#if (defined (__RISCV_FEATURE_VECTOR) && (__RISCV_FEATURE_VECTOR == 1))
  __RV_CSR_SET(CSR_MSTATUS, 0x200);
#endif

  /* Array of input data */
  float32_t in[2];

  /* Result of the classifier */
  float32_t result[NB_OF_CLASSES];
  float32_t temp[NB_OF_CLASSES];
  float32_t maxProba;
  uint32_t index;

  S.vectorDimension = VECTOR_DIMENSION;
  S.numberOfClasses = NB_OF_CLASSES;
  S.theta = theta;
  S.sigma = sigma;
  S.classPriors = classPriors;
  S.epsilon=4.328939296523643e-09f;

  in[0] = 1.5f;
  in[1] = 1.0f;

  index = riscv_gaussian_naive_bayes_predict_f32(&S, in, result,temp);

  maxProba = result[index];

#if defined(SEMIHOSTING)
  printf("Class = %d\n", index);
#endif

  in[0] = -1.5f;
  in[1] = 1.0f;

  index = riscv_gaussian_naive_bayes_predict_f32(&S, in, result,temp);

  maxProba = result[index];

#if defined(SEMIHOSTING)
  printf("Class = %d\n", index);
#endif

  in[0] = 0.0f;
  in[1] = -3.0f;

  index = riscv_gaussian_naive_bayes_predict_f32(&S, in, result,temp);

  maxProba = result[index];

#if defined(SEMIHOSTING)
  printf("Class = %d\n", index);
#endif

  printf("Passed\n");
  return 0;
}

/**
 * @}
 */

/**
 * @}
 */
