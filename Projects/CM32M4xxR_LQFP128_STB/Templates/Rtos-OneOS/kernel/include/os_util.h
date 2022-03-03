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
 * @file        os_util.h
 *
 * @brief       This file provides a part of external interface declaration of kernel utility functions. These 
 *              functions are optimized. 
 *
 * @revision
 * Date         Author          Notes
 * 2020-02-20   OneOS Team      First version.
 * 2020-07-31   OneOS Team      Add os_assert_set_hook declaration.
 ***********************************************************************************************************************
 */
#ifndef __OS_UTIL_H__
#define __OS_UTIL_H__

#include <oneos_config.h>
#include <os_types.h>
#include <os_stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

extern os_int32_t  os_vsnprintf(char *buf, os_size_t size, const char *fmt, va_list args);
extern os_int32_t  os_snprintf(char *buf, os_size_t size, const char *fmt, ...);
extern void        os_kprintf(const char *fmt, ...);
extern void        os_assert_handler(const char *ex_string, const char *func, os_int32_t line);
extern void        os_assert_set_hook(void (*hook)(const char *ex_string, const char *func, os_int32_t line));

#ifdef OS_USING_HEAP
extern char *os_strdup(const char *str);

#if defined(__CC_ARM) || defined(__CLANG_ARM)
extern char *strdup(const char *str);
#endif
#endif /* OS_USING_HEAP */

#if defined(__CC_ARM) || defined(__CLANG_ARM)
extern os_size_t strnlen(const char *str, os_size_t max_len);
#endif

#ifdef __cplusplus
}
#endif

#endif /* __OS_UTIL_H__ */

