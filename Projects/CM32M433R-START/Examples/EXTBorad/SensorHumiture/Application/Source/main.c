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

#include "main.h"

/** @addtogroup CM32M4xxR_StdPeriph_Examples
 * @{
 */

/**
 * @brief  Main function
 */
int main(void)
{
	uint8_t res;
	aht20_handle_t aht20_handle;
	uint32_t raw_temperature;
	uint32_t raw_humidity;
	uint8_t humidity;
	float temperature;

	log_init();

    /* link interface function */
    DRIVER_AHT20_LINK_INIT(&aht20_handle, aht20_handle_t);
    DRIVER_AHT20_LINK_IIC_INIT(&aht20_handle, sensor_interface_iic_init);
    DRIVER_AHT20_LINK_IIC_DEINIT(&aht20_handle, sensor_interface_iic_deinit);
    DRIVER_AHT20_LINK_IIC_READ_CMD(&aht20_handle, sensor_interface_iic_read_cmd);
    DRIVER_AHT20_LINK_IIC_WRITE_CMD(&aht20_handle, sensor_interface_iic_write_cmd);
    DRIVER_AHT20_LINK_DELAY_MS(&aht20_handle, sensor_interface_delay_ms);
    DRIVER_AHT20_LINK_DEBUG_PRINT(&aht20_handle, sensor_interface_debug_print);

    /* aht20 init */
    res = aht20_init(&aht20_handle);
    if (res != 0)
    {
        printf("aht20: init failed.\n");
        while(1);
    }
    else
    {
    	printf("aht20: init success.\n");
    }

    while (1)
    {
    	delay_ms(1000);
    	aht20_read_temperature_humidity(&aht20_handle, &raw_temperature, &temperature, &raw_humidity, &humidity);
    	printf("Temperature:%.2f, Humidity:%d%% RH(%%) \r\n", temperature, humidity);
    }
}



/**
 * @}
 */

/**
 * @}
 */
