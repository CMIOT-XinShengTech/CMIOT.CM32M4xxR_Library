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

#include <main.h>
#include <stdio.h>
#include "log.h"
#include "es8156.h"

/** @addtogroup CM32M4xxR_StdPeriph_Examples
 * @{
 */



extern int32_t es8156_init(es8156_dev_t *dev, es8156_config_t *es8156_config);
extern int i2c_master_init(void);
extern int32_t i2c_master_send(uint8_t addr, uint8_t *data, uint32_t date_len);
extern int32_t i2c_master_send_recv(uint8_t addr, uint8_t *data_write, uint32_t date_len_write, uint8_t *data_read, uint32_t date_len_read);
extern int32_t i2c_master_recv(uint8_t addr, uint8_t *data, uint32_t date_len);
extern void i2s_to_dac_init(void);
extern void i2s_to_adc_init(void);

/**
 * @brief  Main function.
 */
int main(void)
{
    /*!< At this stage the microcontroller clock setting is already configured,
        this is done through SystemInit() function which is called from startup
        file (startup_cm32m4xxr.s) before to branch to application main.
        To reconfigure the default setting of SystemInit() function, refer to
        system_cm32m4xxr.c file
      */
	log_init();
	log_info("This is a SoundOut demo-----------------------------------\r\n");
	i2c_master_init();
	es8156_dev_t es8156_dev;
	es8156_config_t es8156_config;

	es8156_dev.es8156_addr = 0x10;
	es8156_dev.es8156_iic_write = i2c_master_send;
	es8156_dev.es8156_iic_write_read = i2c_master_send_recv;
	//es8156_dev.es8156_iic_read = i2c_master_recv;

	es8156_config.i2s_rate = ES8156_I2S_SAMPLE_RATE_48000;
	//es8156_config.i2s_rate = ES8156_I2S_SAMPLE_RATE_32000;
	es8156_config.i2s_mode = ES8156_I2S_MODE_SLAVE;
	es8156_config.i2s_protocol = ES8156_NORMAL_I2S;
	es8156_config.data_len = ES8156_16BIT_LENGTH;
	es8156_config.i2s_sclk_freq = ES8156_I2S_SCLK_48FS;
	//es8156_config.i2s_sclk_freq = ES8156_I2S_SCLK_64FS;
	es8156_config.mclk_freq = ES8156_MCLK_256FS;
	//es8156_config.mclk_freq = ES8156_MCLK_384FS;

	es8156_init(&es8156_dev, &es8156_config);
	i2s_to_dac_init();

	log_info("demo end-----------------------------------\r\n");
    while (1)
    {
    }
}

/**
 * @}
 */

/**
 * @}
 */
