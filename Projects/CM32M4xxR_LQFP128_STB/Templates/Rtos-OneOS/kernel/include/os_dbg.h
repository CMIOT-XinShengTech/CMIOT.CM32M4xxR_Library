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
 * @file        os_dbg.h
 *
 * @brief       Define the macro of printing log. This macro will compile logs on all levels into bin file.
 *
 * @revision
 * Date         Author          Notes
 * 2020-03-10   OneOS Team      First version.
 ***********************************************************************************************************************
 */

#ifndef __OS_DBG_H__
#define __OS_DBG_H__

#include <oneos_config.h>
#include <os_types.h>
#include <os_stddef.h>
#include <os_util.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__OS_DBG_H__) && defined(__OS_DBG_EXT_H__)
#error "os_dbg.h and os_dbg_ext.h are not be used simultaneously in a same file!!!"
#endif

#ifdef OS_DEBUG

#ifdef OS_USING_DLOG
#include <dlog.h>

#define DBG_ERROR               LOG_LVL_ERROR
#define DBG_WARNING             LOG_LVL_WARNING
#define DBG_INFO                LOG_LVL_INFO
#define DBG_DEBUG               LOG_LVL_DEBUG

/* Print logs with function name and file line number, and use dlog interface */
#ifdef OS_DEBUG_LOG_WITH_FUNC_LINE
#define LOG_E(tag, fmt, ...)    \
    dlog_output(DBG_ERROR, tag, OS_TRUE, fmt " [%s][%d]", ##__VA_ARGS__, __FUNCTION__, __LINE__)

#define LOG_W(tag, fmt, ...)    \
    dlog_output(DBG_WARNING, tag, OS_TRUE, fmt " [%s][%d]", ##__VA_ARGS__, __FUNCTION__, __LINE__)

#define LOG_I(tag, fmt, ...)    \
    dlog_output(DBG_INFO, tag, OS_TRUE, fmt " [%s][%d]", ##__VA_ARGS__, __FUNCTION__, __LINE__)

#define LOG_D(tag, fmt, ...)    \
    dlog_output(DBG_DEBUG, tag, OS_TRUE, fmt " [%s][%d]", ##__VA_ARGS__, __FUNCTION__, __LINE__)

/* Print logs without function name and file line number, and use dlog interface */
#else /* Not define OS_DEBUG_LOG_WITH_FUNC_LINE */
#define LOG_E(tag, fmt, ...)        dlog_output(DBG_ERROR,   tag, OS_TRUE, fmt, ##__VA_ARGS__)
#define LOG_W(tag, fmt, ...)        dlog_output(DBG_WARNING, tag, OS_TRUE, fmt, ##__VA_ARGS__)
#define LOG_I(tag, fmt, ...)        dlog_output(DBG_INFO,    tag, OS_TRUE, fmt, ##__VA_ARGS__)
#define LOG_D(tag, fmt, ...)        dlog_output(DBG_DEBUG,   tag, OS_TRUE, fmt, ##__VA_ARGS__)
#endif /* OS_DEBUG_LOG_WITH_FUNC_LINE */

#define LOG_RAW(fmt, ...)               dlog_raw(fmt, ##__VA_ARGS__)
#define LOG_HEX(tag, width, buf, size)  dlog_hexdump(tag, width, buf, size)

#else /* Not define OS_USING_DLOG */
#define DBG_ERROR               0   /* Equal to KERN_ERROR */
#define DBG_WARNING             1   /* Equal to KERN_WARNING */
#define DBG_INFO                2   /* Equal to KERN_INFO */
#define DBG_DEBUG               3   /* Equal to KERN_DEBUG */

/* Print logs with function name and file line number, and use kernel log interface */
#ifdef OS_DEBUG_LOG_WITH_FUNC_LINE
#define LOG_E(tag, fmt, ...)    \
    os_kernel_print(DBG_ERROR, tag, OS_TRUE, fmt " [%s][%d]", ##__VA_ARGS__, __FUNCTION__, __LINE__)
    
#define LOG_W(tag, fmt, ...)    \
    os_kernel_print(DBG_WARNING, tag, OS_TRUE, fmt " [%s][%d]", ##__VA_ARGS__, __FUNCTION__, __LINE__)
    
#define LOG_I(tag, fmt, ...)    \
    os_kernel_print(DBG_INFO, tag, OS_TRUE, fmt " [%s][%d]", ##__VA_ARGS__, __FUNCTION__, __LINE__)
    
#define LOG_D(tag, fmt, ...)    \
    os_kernel_print(DBG_DEBUG, tag, OS_TRUE, fmt " [%s][%d]", ##__VA_ARGS__, __FUNCTION__, __LINE__)

/* Print logs without function name and file line number, and use kernel log interface */
#else /* Not define OS_DEBUG_LOG_WITH_FUNC_LINE */
#define LOG_E(tag, fmt, ...)        os_kernel_print(DBG_ERROR,   tag, OS_TRUE, fmt, ##__VA_ARGS__)  
#define LOG_W(tag, fmt, ...)        os_kernel_print(DBG_WARNING, tag, OS_TRUE, fmt, ##__VA_ARGS__) 
#define LOG_I(tag, fmt, ...)        os_kernel_print(DBG_INFO,    tag, OS_TRUE, fmt, ##__VA_ARGS__)  
#define LOG_D(tag, fmt, ...)        os_kernel_print(DBG_DEBUG,   tag, OS_TRUE, fmt, ##__VA_ARGS__)
#endif /* OS_DEBUG_LOG_WITH_FUNC_LINE */

#define LOG_RAW(fmt, ...)               os_kprintf(fmt, ##__VA_ARGS__)
#define LOG_HEX(tag, width, buf, size)

extern void os_kernel_print(os_uint16_t level, const char *tag, os_bool_t newline, const char *fmt, ...);
#endif /* OS_USING_DLOG */

#else  /* Not define OS_DEBUG */
#define LOG_E(tag, fmt, ...)
#define LOG_W(tag, fmt, ...)
#define LOG_I(tag, fmt, ...)
#define LOG_D(tag, fmt, ...)
#define LOG_RAW(fmt, ...)
#define LOG_HEX(tag, width, buf, size)
#endif /* OS_DEBUG */

#ifdef __cplusplus
}
#endif

#endif /* __OS_DBG_H__ */

