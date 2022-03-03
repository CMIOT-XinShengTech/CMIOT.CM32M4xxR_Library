#ifndef __PRIVACY_H__
#define __PRIVACY_H__

#include <stdint.h>

uint8_t privacy_encrypt(uint8_t *src, uint16_t src_len, uint8_t * dst);

uint8_t privacy_encrypt_aes(uint8_t *src, uint16_t src_len, uint8_t * dst);

#endif
