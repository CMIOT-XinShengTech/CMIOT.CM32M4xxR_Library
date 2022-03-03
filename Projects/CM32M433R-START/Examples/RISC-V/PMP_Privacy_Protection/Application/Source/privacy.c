#include "nuclei_sdk_soc.h"
#include "cm32m4xxr_aes.h"
#include <stdint.h>


static uint8_t const userkey[16] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x00};
uint8_t privacy_encrypt(uint8_t *src, uint16_t src_len, uint8_t *dst) {
  uint32_t ret;
  uint16_t i = 0;
  for(i = 0; i < src_len; i++)
  {
    dst[i] = src[i] ^ userkey[i % 16];
  }
  AES_PARM param;
  param.in = (uint32_t *)src;
  param.out = (uint32_t *)dst;
  param.iv = (uint32_t *)0;
  param.key = (uint32_t *)userkey;
  param.keyWordLen = 4;
  param.inWordLen = 4;
  param.En_De = AES_ENC;
  param.Mode = AES_ECB;

  AES_Init(&param);
  AES_Crypto(&param);
  AES_Close();

  return 0;
}
