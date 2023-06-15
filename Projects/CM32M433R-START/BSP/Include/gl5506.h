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
*#include "nuclei_sdk_soc.h"
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
 * @file gl5506.h
 * @author CMIOT Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */
#ifndef __GL5506_H__
#define __GL5506_H__

#include "nuclei_sdk_soc.h"

#define GL5506_ADC_INDEX	ADC1
#define GL5506_ADC_CHANNEL	ADC1_Channel_07_PC1
#define GL5506_ADC_PORT		GPIOC
#define GL5506_ADC_PIN		GPIO_PIN_1

#define GL5506_RES_BRIGHT_THRESHOLD	7000		//7K
#define GL5506_RES_DARK_THRESHOLD	500000		//500K

typedef enum {
	GL5506_ERROR_OK            = 0x00U,  /*!< No error   */
	GL5506_ERROR_PARA          = 0x01U,  /*!< Parameter error */
}GL5506_ErrorType;

typedef enum{
	GL5506_STATUS_BRIGHT,
	GL5506_STATUS_DARK,
	GL5506_STATUS_MEDIUM,
}GL5506_StatusType;

typedef struct{
	uint16_t adcsample;
	uint16_t voltage;		//mV
	uint32_t resistance;	//ohm
	GL5506_StatusType status;
}GL5506_ResultType;


/* For all LEDs on BaseBoard and ExtBoard*/
GL5506_ErrorType gl5506_init(void);
GL5506_ErrorType gl5506_getresult(GL5506_ResultType* pResult);

#endif /* __GL5506_H__ */
