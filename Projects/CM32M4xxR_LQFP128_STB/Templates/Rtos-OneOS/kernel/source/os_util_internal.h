/**
 ***********************************************************************************************************************
 * Copyright (c) 2020, China Mobile Communications Group Co.,Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with 
 * the License. You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on 
 * an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the 
 * specific language governing permissions and limitations under the License.
 *
 * @file        os_util_internal.h
 *
 * @brief       Provides function declarations of utility functions similar to C library, only use for kernel.
 *
 * @revision
 * Date         Author          Notes
 * 2020-02-20   OneOS Team      First version.
 ***********************************************************************************************************************
 */
#ifndef __OS_UTIL_INTERNAL_H__
#define __OS_UTIL_INTERNAL_H__

#include <os_types.h>
#include <os_util.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void       *os_memset(void *src, os_uint8_t val, os_size_t count);
extern void       *os_memcpy(void *dst, const void *src, os_size_t count);
extern void       *os_memmove(void *dst, const void *src, os_size_t count);
extern os_int32_t  os_memcmp(const void *str1, const void *str2, os_size_t count);
extern char       *os_strcpy(char *dst, const char *src);
extern char       *os_strncpy(char *dst, const char *src, os_size_t count);
extern os_int32_t  os_strcmp(const char *str1, const char *str2);
extern os_int32_t  os_strncmp(const char *str1, const char *str2, os_size_t count);
extern os_size_t   os_strlen(const char *str);
extern os_size_t   os_strnlen(const char *str, os_size_t max_len);
extern char       *os_strchr(const char *str, char ch);
extern char       *os_strstr(const char *str1, const char *str2);

#ifdef __cplusplus
}
#endif

#endif /* __OS_UTIL_INTERNAL_H__ */

