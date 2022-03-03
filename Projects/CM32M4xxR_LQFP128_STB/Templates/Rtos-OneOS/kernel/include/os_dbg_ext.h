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
 * @brief       Define the macro of printing log. This macro will only compile logs higher or equal than a certain
 *              level (DBG_EXT_LVL) into bin file.
 *
 * @revision
 * Date         Author          Notes
 * 2020-03-11   OneOS Team      First version.
 ***********************************************************************************************************************
 */

#ifndef __OS_DBG_EXT_H__
#define __OS_DBG_EXT_H__

#include <oneos_config.h>
#include <os_types.h>
#include <os_stddef.h>
#include <os_util.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__OS_DBG_H__) && defined(__OS_DBG_EXT_H__)
#error "os_dbg.h and os_dbg_ext.h are not be used simultaneously in a smae file!!!"
#endif

#ifdef OS_DEBUG

#if !defined(DBG_EXT_TAG)
#define DBG_EXT_TAG                 "NO_TAG"
#endif

#if !defined(DBG_EXT_LVL)
#define DBG_EXT_LVL                 DBG_EXT_WARNING
#endif

#ifdef OS_USING_DLOG
#include <dlog.h>

#define DBG_EXT_ERROR               LOG_LVL_ERROR
#define DBG_EXT_WARNING             LOG_LVL_WARNING
#define DBG_EXT_INFO                LOG_LVL_INFO
#define DBG_EXT_DEBUG               LOG_LVL_DEBUG

/* Print logs with function name and file line number, and use dlog interface */
#ifdef OS_DEBUG_LOG_WITH_FUNC_LINE

#if (DBG_EXT_ERROR <= DBG_EXT_LVL)
#define LOG_EXT_E(fmt, ...)     \
    dlog_output(DBG_EXT_ERROR, DBG_EXT_TAG, OS_TRUE, fmt " [%s][%d]", ##__VA_ARGS__, __FUNCTION__, __LINE__)
#else
#define LOG_EXT_E(fmt, ...)
#endif

#if (DBG_EXT_WARNING <= DBG_EXT_LVL)
#define LOG_EXT_W(fmt, ...)     \
    dlog_output(DBG_EXT_WARNING, DBG_EXT_TAG, OS_TRUE, fmt " [%s][%d]", ##__VA_ARGS__, __FUNCTION__, __LINE__)
#else
#define LOG_EXT_W(fmt, ...)
#endif

#if (DBG_EXT_INFO <= DBG_EXT_LVL)
#define LOG_EXT_I(fmt, ...)     \
    dlog_output(DBG_EXT_INFO, DBG_EXT_TAG, OS_TRUE, fmt " [%s][%d]", ##__VA_ARGS__, __FUNCTION__, __LINE__)
#else
#define LOG_EXT_I(fmt, ...)
#endif

#if (DBG_EXT_DEBUG <= DBG_EXT_LVL)
#define LOG_EXT_D(fmt, ...)     \
    dlog_output(DBG_EXT_DEBUG, DBG_EXT_TAG, OS_TRUE, fmt " [%s][%d]", ##__VA_ARGS__, __FUNCTION__, __LINE__)
#else
#define LOG_EXT_D(fmt, ...)
#endif

/* Print logs without function name and file line number, and use dlog interface */
#else /* Not define OS_DEBUG_LOG_WITH_FUNC_LINE */

#if (DBG_EXT_ERROR <= DBG_EXT_LVL)
#define LOG_EXT_E(fmt, ...)     dlog_output(DBG_EXT_ERROR,   DBG_EXT_TAG, OS_TRUE, fmt, ##__VA_ARGS__)
#else
#define LOG_EXT_E(fmt, ...)
#endif

#if (DBG_EXT_WARNING <= DBG_EXT_LVL)
#define LOG_EXT_W(fmt, ...)     dlog_output(DBG_EXT_WARNING, DBG_EXT_TAG, OS_TRUE, fmt, ##__VA_ARGS__)
#else
#define LOG_EXT_W(fmt, ...)
#endif

#if (DBG_EXT_INFO <= DBG_EXT_LVL)
#define LOG_EXT_I(fmt, ...)     dlog_output(DBG_EXT_INFO,    DBG_EXT_TAG, OS_TRUE, fmt, ##__VA_ARGS__)
#else
#define LOG_EXT_I(fmt, ...)
#endif

#if (DBG_EXT_DEBUG <= DBG_EXT_LVL)
#define LOG_EXT_D(fmt, ...)     dlog_output(DBG_EXT_DEBUG,   DBG_EXT_TAG, OS_TRUE, fmt, ##__VA_ARGS__)
#else
#define LOG_EXT_D(fmt, ...)
#endif

#endif /* OS_DEBUG_LOG_WITH_FUNC_LINE */

#define LOG_EXT_RAW(fmt, ...)               dlog_raw(fmt, ##__VA_ARGS__)
#define LOG_EXT_HEX(width, buf, size)       dlog_hexdump(DBG_EXT_TAG, tag, width, buf, size)

#else /* Not define OS_USING_DLOG */

#define DBG_EXT_ERROR               0   /* Equal to KERN_ERROR */
#define DBG_EXT_WARNING             1   /* Equal to KERN_WARNING */
#define DBG_EXT_INFO                2   /* Equal to KERN_INFO */
#define DBG_EXT_DEBUG               3   /* Equal to KERN_DEBUG */

/* Print logs with function name and file line number, and use kernel log interface */
#ifdef OS_DEBUG_LOG_WITH_FUNC_LINE

#if (DBG_EXT_ERROR <= DBG_EXT_LVL)
#define LOG_EXT_E(fmt, ...)     \
    os_kernel_print(DBG_EXT_ERROR, DBG_EXT_TAG, OS_TRUE, fmt " [%s][%d]", ##__VA_ARGS__, __FUNCTION__, __LINE__)
#else
#define LOG_EXT_E(fmt, ...)
#endif

#if (DBG_EXT_WARNING <= DBG_EXT_LVL)
#define LOG_EXT_W(fmt, ...)     \
    os_kernel_print(DBG_EXT_WARNING, DBG_EXT_TAG, OS_TRUE, fmt " [%s][%d]", ##__VA_ARGS__, __FUNCTION__, __LINE__)
#else
#define LOG_EXT_W(fmt, ...)
#endif

#if (DBG_EXT_INFO <= DBG_EXT_LVL)
#define LOG_EXT_I(fmt, ...)     \
    os_kernel_print(DBG_EXT_INFO, DBG_EXT_TAG, OS_TRUE, fmt " [%s][%d]", ##__VA_ARGS__, __FUNCTION__, __LINE__)
#else
#define LOG_EXT_I(fmt, ...)
#endif

#if (DBG_EXT_DEBUG <= DBG_EXT_LVL)
#define LOG_EXT_D(fmt, ...)     \
    os_kernel_print(DBG_EXT_DEBUG, DBG_EXT_TAG, OS_TRUE, fmt " [%s][%d]", ##__VA_ARGS__, __FUNCTION__, __LINE__)
#else
#define LOG_EXT_D(fmt, ...)
#endif

/* Print logs without function name and file line number, and use kernel log interface */
#else /* Not define OS_DEBUG_LOG_WITH_FUNC_LINE */

#if (DBG_EXT_ERROR <= DBG_EXT_LVL)
#define LOG_EXT_E(fmt, ...)     os_kernel_print(DBG_EXT_ERROR,   DBG_EXT_TAG, OS_TRUE, fmt, ##__VA_ARGS__)
#else
#define LOG_EXT_E(fmt, ...)
#endif

#if (DBG_EXT_WARNING <= DBG_EXT_LVL)
#define LOG_EXT_W(fmt, ...)     os_kernel_print(DBG_EXT_WARNING, DBG_EXT_TAG, OS_TRUE, fmt, ##__VA_ARGS__)
#else
#define LOG_EXT_W(fmt, ...)
#endif

#if (DBG_EXT_INFO <= DBG_EXT_LVL)
#define LOG_EXT_I(fmt, ...)     os_kernel_print(DBG_EXT_INFO,    DBG_EXT_TAG, OS_TRUE, fmt, ##__VA_ARGS__)
#else
#define LOG_EXT_I(fmt, ...)
#endif

#if (DBG_EXT_DEBUG <= DBG_EXT_LVL)
#define LOG_EXT_D(fmt, ...)     os_kernel_print(DBG_EXT_DEBUG,   DBG_EXT_TAG, OS_TRUE, fmt, ##__VA_ARGS__)
#else
#define LOG_EXT_D(fmt, ...)
#endif

#endif /* OS_DEBUG_LOG_WITH_FUNC_LINE */

#define LOG_EXT_RAW(fmt, ...)               os_kprintf(fmt, ##__VA_ARGS__)
#define LOG_EXT_HEX(width, buf, size)

extern void os_kernel_print(os_uint16_t level, const char *tag, os_bool_t newline, const char *fmt, ...);
#endif /* OS_USING_DLOG */

#else  /* Not define OS_DEBUG */
#define LOG_EXT_E(fmt, ...)
#define LOG_EXT_W(fmt, ...)
#define LOG_EXT_I(fmt, ...)
#define LOG_EXT_D(fmt, ...)
#define LOG_EXT_RAW(fmt, ...)
#define LOG_EXT_HEX(width, buf, size)

#endif /* OS_DEBUG */

#ifdef __cplusplus
}
#endif

#endif /* __OS_DBG_EXT_H__ */

