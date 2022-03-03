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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "menu.h"

/** @addtogroup CM32M4xxR_IAP_Bootloader
 * @{
 */

/* Private function prototypes -----------------------------------------------*/
static void IAP_Init(void);
static void Key_Init(void);
/**
 * @brief  Main program
 * @param  None
 * @retval None
 */
int main(void) {

	/* Mode Select Key Configure */
	Key_Init();

	/* Test if WKUP Key is pressed */
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_PIN_0) == Bit_RESET) {
		/* Initialise Flash */
		FLASH_Init();
		/* Execute the IAP driver in order to reprogram the Flash */
		IAP_Init();
		/* Display main menu */
		Main_Menu();
	}
	/* Keep the user application running */
	else {
		JumpApp();
	}

	while (1) {
	}
}
/**
 * @brief  Initialize Key Port,to select startup mode
 * @param  None
 * @retval None
 */
void Key_Init(void)
{
	GPIO_InitType GPIO_InitStructure;

	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);

	/* Key Config */
	GPIO_InitStructure.Pin = GPIO_PIN_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/**
 * @brief  Initialize the IAP: Configure USART.
 * @param  None
 * @retval None
 */
void IAP_Init(void) {
	/* USART resources configuration (Clock, GPIO pins and USART registers) ----*/
	/* USART configured as follow:
	 - BaudRate = 115200 baud
	 - Word Length = 8 Bits
	 - One Stop Bit
	 - No parity
	 - Hardware flow control disabled (RTS and CTS signals)
	 - Receive and transmit enabled
	 */
	GPIO_InitType GPIO_InitStructure;
	USART_InitType USART_InitStructure;

	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO | RCC_APB2_PERIPH_GPIOE, ENABLE);
	RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_UART5, ENABLE);

	GPIO_ConfigPinRemap(GPIO_RMP2_UART5, ENABLE);

	GPIO_InitStructure.Pin = GPIO_PIN_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_InitStructure.Pin = GPIO_PIN_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	USART_InitStructure.BaudRate = 115200;
	USART_InitStructure.WordLength = USART_WL_8B;
	USART_InitStructure.StopBits = USART_STPB_1;
	USART_InitStructure.Parity = USART_PE_NO;
	USART_InitStructure.HardwareFlowControl = USART_HFCTRL_NONE;
	USART_InitStructure.Mode = USART_MODE_TX | USART_MODE_RX;

	/* Init uart */
	USART_Init(UART5, &USART_InitStructure);

	/* Enable uart */
	USART_Enable(UART5, ENABLE);
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(const uint8_t* expr, const uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* Infinite loop */
    while (1)
    {

    }
}
#endif

/**
 * @}
 */

