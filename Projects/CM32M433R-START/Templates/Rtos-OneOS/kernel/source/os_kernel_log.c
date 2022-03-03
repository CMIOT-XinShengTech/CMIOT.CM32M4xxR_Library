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
 * @file        os_kernel_log.c
 *
 * @brief       Implementation of kernel printing function.
 *
 * @revision
 * Date         Author          Notes
 * 2020-03-05   OneOS Team      First version.
 ***********************************************************************************************************************
 */

#include <oneos_config.h>
#include <os_types.h>
#include <os_stddef.h>
#include <os_errno.h>
#include <os_clock.h>
#include <os_module.h>
#include <os_task.h>
#include <os_list.h>
#include <stdio.h>

#include "os_kernel_internal.h"
#include "os_util_internal.h"

#ifdef OS_DEBUG

#include <os_device.h>
#define KLOG_NEWLINE_SIGN               "\r\n"

#ifdef KLOG_USING_COLOR
/*
 * CSI(Control Sequence Introducer/Initiator) sign
 * more information on https://en.wikipedia.org/wiki/ANSI_escape_code
 */
#define CSI_START                       "\033["
#define CSI_END                         "\033[0m"

/* Output log front color */
#define F_BLACK                         "30m"
#define F_RED                           "31m"
#define F_GREEN                         "32m"
#define F_YELLOW                        "33m"
#define F_BLUE                          "34m"
#define F_MAGENTA                       "35m"
#define F_CYAN                          "36m"
#define F_WHITE                         "37m"

#define KLOG_COLOR_DEBUG                (OS_NULL)
#define KLOG_COLOR_INFO                 (F_GREEN)
#define KLOG_COLOR_WARN                 (F_YELLOW)
#define KLOG_COLOR_ERROR                (F_RED)

/* Color output info */
static const char *gs_klog_color_output_info[] =
{
    KLOG_COLOR_ERROR,
    KLOG_COLOR_WARN,
    KLOG_COLOR_INFO,
    KLOG_COLOR_DEBUG,
};
#endif /* KLOG_USING_COLOR */

struct os_klog_tag_lvl_filter
{
    os_list_node_t list;                                    /* The filter list */
    char           tag[KLOG_FILTER_TAG_MAX_LEN + 1];        /* Tag name */
    os_uint16_t    level;                                   /* The filter level of the tag */
};
typedef struct os_klog_tag_lvl_filter os_klog_tag_lvl_filter_t;

struct os_klog_ctrl_info
{
    os_list_node_t tag_lvl_list;                            /* The tag filter list */
    os_uint16_t    global_level;                            /* The global filter level */
    char           log_buff[OS_LOG_BUFF_SIZE];              /* Buffer of formatted log information */
};
typedef struct os_klog_ctrl_info os_klog_ctrl_info_t;

static os_klog_ctrl_info_t gs_klog_ctrl_info = 
{
    .tag_lvl_list = OS_LIST_INIT(gs_klog_ctrl_info.tag_lvl_list),
    .global_level = KLOG_GLOBAL_LEVEL
};

const os_int16_t     *g_klog_global_lvl   = (os_int16_t *)&gs_klog_ctrl_info.global_level; 
const os_list_node_t *g_klog_tag_lvl_list = &gs_klog_ctrl_info.tag_lvl_list;

static const char    *gs_klog_level_output_info[] =
{
    "E/",
    "W/",
    "I/",
    "D/"
};
#endif /* OS_DEBUG */

#if defined(OS_USING_DEVICE) && defined(OS_USING_CONSOLE)
static os_device_t *gs_console_device = OS_NULL;

/**
 ***********************************************************************************************************************
 * @brief           This function returns the device using in console.
 *
 * @param           No parameter.
 *
 * @return          The device using in console.
 * @retval          OS_NULL         There is no device in console.
 * @retval          else            The device pointer using in console.
 ***********************************************************************************************************************
 */
os_device_t *os_console_get_device(void)
{
    return gs_console_device;
}
EXPORT_SYMBOL(os_console_get_device);

/**
 ***********************************************************************************************************************
 * @brief           This function will set a device as console device.
 *
 * @details         After setting a device to console, all output of os_kprintf will be redirected to this new device.
 *
 *
 * @param[in]       name            The name of new console device.
 *
 * @return          The old console device pointer.
 * @retval          OS_NULL         Before setting a new device to console, there is no device in console. 
 * @retval          else            Return the old console device pointer.
 ***********************************************************************************************************************
 */
os_device_t *os_console_set_device(const char *name)
{
    os_device_t *new;
    os_device_t *old;

    /* Save old device */
    old = gs_console_device;

    /* Find new console device */
    new = os_device_find(name);
    if (OS_NULL != new)
    {
        if (OS_NULL != gs_console_device)
        {
            /* Close old console device */
            os_device_close(gs_console_device);
        }

        /* Set new console device */
        os_device_open(new, OS_DEVICE_OFLAG_RDWR | OS_DEVICE_FLAG_STREAM);
        gs_console_device = new;
    }

    return old;
}
EXPORT_SYMBOL(os_console_set_device);
#endif /* defined(OS_USING_DEVICE) && defined(OS_USING_CONSOLE) */


/**
 ***********************************************************************************************************************
 * @brief           Output of hardware console.
 *
 * @attention       This function is weak, and could be implemented in BSP.
 *
 * @param[in]       str             The string to output.
 *
 * @return          No return value.
 ***********************************************************************************************************************
 */
OS_WEAK void os_hw_console_output(const char *str)
{
    return;
}

/**
 ***********************************************************************************************************************
 * @brief           This function will output log to console.
 *
 * @param[in]       log_buff        The log buffer.
 *
 * @return          No return value.
 ***********************************************************************************************************************
 */
void os_log_output(const char *log_buff)
{
#if defined(OS_USING_DEVICE) && defined(OS_USING_CONSOLE)
    if (gs_console_device == OS_NULL)
    {
        os_hw_console_output(log_buff);  
    }
    else
    {
        os_uint16_t old_flag = gs_console_device->open_flag;

        gs_console_device->open_flag |= OS_DEVICE_FLAG_STREAM;
        os_device_write(gs_console_device, 0, log_buff, os_strlen(log_buff));
        gs_console_device->open_flag = old_flag;
    }
#else
    os_hw_console_output(log_buff);
#endif

    return;
}

/**
 ***********************************************************************************************************************
 * @brief           This function will print a formatted string on system console.
 *
 * @param[in]       fmt             The format.
 *
 * @return          No return value.
 ***********************************************************************************************************************
 */
void os_kprintf(const char *fmt, ...)
{
    va_list args;
    os_size_t length;
    static char log_buff[OS_LOG_BUFF_SIZE];

    va_start(args, fmt);
    /* 
     * The return value of os_vsnprintf is the number of bytes that would be
     * written to buffer had if the size of the buffer been sufficiently
     * large excluding the terminating null byte. If the output string
     * would be larger than the cm_log_buf, we have to adjust the output
     * length.
     */
    length = os_vsnprintf(log_buff, sizeof(log_buff), fmt, args);
    if (length > sizeof(log_buff) - 1)
    {
        length = sizeof(log_buff) - 1;
        log_buff[length] = '\0';
    }
    
    va_end(args);

    os_log_output(log_buff);

    return;
}
EXPORT_SYMBOL(os_kprintf);

#ifdef OS_DEBUG
static os_bool_t os_get_klog_tag_lvl(const char *tag, os_uint16_t *level)
{
    os_list_node_t           *node;
    os_klog_tag_lvl_filter_t *tag_lvl_filter;
    os_bool_t                found;
    os_int32_t               ret;
    
    OS_ASSERT(tag);
    OS_ASSERT(level);

    os_enter_critical();

    found = OS_FALSE;
    os_list_for_each(node, &gs_klog_ctrl_info.tag_lvl_list)
    {
        tag_lvl_filter = os_list_entry(node, os_klog_tag_lvl_filter_t, list);

        ret = os_strncmp(tag_lvl_filter->tag, tag, KLOG_FILTER_TAG_MAX_LEN);
        if (0 == ret)
        {
            found  = OS_TRUE;
            *level = tag_lvl_filter->level;
            
            break;
        }
    }
    
    os_exit_critical();
    
    return found;
}

/**
 ***********************************************************************************************************************
 * @brief           This function will print kernel log on system console.
 *
 * @attention       This function can only be used in the kernel.
 *
 * @param[in]       level           The Log level.
 * @param[in]       tag             The log tag.
 * @param[in]       newline         Has newline.
 * @param[in]       fmt             Output format.
 *
 * @return          No return value.
 ***********************************************************************************************************************
 */
void os_kernel_print(os_uint16_t level, const char *tag, os_bool_t newline, const char *fmt, ...)
{
    va_list            args;
    static os_int32_t  s_cnt;
    static os_int32_t  s_offset;
    static os_bool_t   s_found;
    static os_uint16_t s_tag_level;
    static os_int32_t  s_newline_len;

    OS_ASSERT(tag);
    
    if (os_list_empty(&gs_klog_ctrl_info.tag_lvl_list))
    {
        if (level > gs_klog_ctrl_info.global_level)
        {
            return;
        }
    }
    else
    {
        s_found = os_get_klog_tag_lvl(tag, &s_tag_level);
        if (s_found)
        {
            if (level > s_tag_level)
            {
                return;
            }
        }
        else
        {
            if (level > gs_klog_ctrl_info.global_level)
            {
                return;
            }
        }
    }

    if (newline)
    {
        s_newline_len = os_strlen(KLOG_NEWLINE_SIGN);
    }
    else
    {
        s_newline_len = 0;
    }
    
    s_offset = 0;
    os_memset(gs_klog_ctrl_info.log_buff, 0, OS_LOG_BUFF_SIZE);

#ifdef KLOG_USING_COLOR
    if (gs_klog_color_output_info[level])
    {
        s_cnt = os_snprintf(gs_klog_ctrl_info.log_buff + s_offset,
                            OS_LOG_BUFF_SIZE - s_offset,
                            "%s%s",
                            CSI_START,
                            gs_klog_color_output_info[level]);
    
        s_offset += s_cnt;
    }
#endif /* KLOG_USING_COLOR */

    s_cnt = os_snprintf(gs_klog_ctrl_info.log_buff + s_offset,
                        OS_LOG_BUFF_SIZE - s_offset,
                        "[%u] %s%s: ",
                        os_tick_get(),
                        gs_klog_level_output_info[level],
                        tag);
    if (s_cnt < 0)
    {
        OS_ASSERT(0);
        return;
    }

    va_start(args, fmt);
    s_offset += s_cnt;
    s_cnt = os_vsnprintf(gs_klog_ctrl_info.log_buff + s_offset, OS_LOG_BUFF_SIZE - s_offset, fmt, args);
    va_end(args);
    
    if (s_cnt < 0)
    {
        OS_ASSERT(s_cnt >= 0);
        return;
    }
    
    s_offset += s_cnt;

#ifdef KLOG_USING_COLOR
    if (s_offset + s_newline_len + os_strlen(CSI_END) + 1 > OS_LOG_BUFF_SIZE)
    {
        s_offset = OS_LOG_BUFF_SIZE;
        s_offset -= ( s_newline_len + os_strlen(CSI_END));
        s_offset -= 1;
    }
#else
    if (s_offset + s_newline_len + 1 > OS_LOG_BUFF_SIZE)
    {
        s_offset = OS_LOG_BUFF_SIZE;
        s_offset -= s_newline_len;
        s_offset -= 1;
    }
#endif

    if (s_newline_len)
    {
        os_strcpy(gs_klog_ctrl_info.log_buff + s_offset, KLOG_NEWLINE_SIGN);
        s_offset += s_newline_len;
    }

#ifdef KLOG_USING_COLOR
    if (gs_klog_color_output_info[level])
    {
        os_strcpy(gs_klog_ctrl_info.log_buff + s_offset, CSI_END);
        s_offset += os_strlen(CSI_END);
    }
#endif /* KLOG_USING_COLOR */

    gs_klog_ctrl_info.log_buff[s_offset] = '\0';

    os_log_output(gs_klog_ctrl_info.log_buff);
    
    return;
}

#ifdef OS_USING_SHELL
#include <shell.h>
#include <stdlib.h>

#include <option_parse.h>
#include <string.h>

struct klog_command_ctrl_info
{

    char                    tag_name[KLOG_FILTER_TAG_MAX_LEN+1];
    os_int32_t              control_info;
    os_uint16_t             level;
};
typedef struct klog_command_ctrl_info  klog_command_ctrl_info_t;

static klog_command_ctrl_info_t        gs_klog_cmd_ctrl_info;

#define COMMAND_SET_OPTION      1
#define COMMAND_GET_OPTION      2
#define COMMAND_DEL_OPTION      3

os_err_t klog_ctrl_info_get(os_int32_t argc, char * const *argv, klog_command_ctrl_info_t *ctrl_info)
{
    opt_state_t state;
    os_int32_t  opt_ret;
    os_int32_t  ret;

    memset(ctrl_info, 0 , sizeof(klog_command_ctrl_info_t));
    
    memset(&state, 0, sizeof(state));
    opt_init(&state, 1);

    ret = OS_EOK;
    while (1)
    {
        opt_ret = opt_get(argc, argv, "n:sgdl:", &state);
        if (opt_ret == OPT_EOF)
        {
            break;
        }

        if ((opt_ret == OPT_BADOPT) || (opt_ret == OPT_BADARG))
        {
            ret = OS_ERROR;
            break;
        }
    
        switch (opt_ret)
        {
        case 'n':
            memset(ctrl_info->tag_name, 0, KLOG_FILTER_TAG_MAX_LEN);
            strncpy(ctrl_info->tag_name, state.opt_arg, KLOG_FILTER_TAG_MAX_LEN);
            break;
            
        case 's':
            ctrl_info->control_info = COMMAND_SET_OPTION;
            break;

        case 'g':
            ctrl_info->control_info = COMMAND_GET_OPTION;
            break;
            
        case 'd':
            ctrl_info->control_info = COMMAND_DEL_OPTION;
            break;
            
        case 'l':
            ctrl_info->level = (os_uint16_t)atoi(state.opt_arg);
            break;

        default:
            os_kprintf("Invalid option: %c\r\n", (char)opt_ret);

            ret = OS_EINVAL;
            break;
        }

        if (ret != OS_EOK)
        {
            break;
        }
    }

    return ret;
}

static os_err_t sh_klog_global_level_control(os_int32_t argc, char **argv)
{
    os_err_t   ret;
    //os_uint16_t level;

    if(argc < 2)
    {
        SH_PRINT("Command format:");
        SH_PRINT("klog_glvl_ctrl [-s | -g] [-l global level]");
        SH_PRINT("parameter Usage:");
  
        SH_PRINT("         -s     Set global level option.");
        SH_PRINT("         -g     Get global level option.");
        SH_PRINT("         -l     Specify a global level that want to be set.");
        SH_PRINT("                level: 0-error, 1-warning, 2-info, 3-debug");

        return OS_EINVAL;
    }
    
    ret = klog_ctrl_info_get(argc,argv,&gs_klog_cmd_ctrl_info);
    
    if (ret != OS_EOK)
    {
        SH_PRINT("Wrong parameter, usage:");
        SH_PRINT("klog_glvl_ctrl [-s | -g] [-l level]");
        return ret;
    }

    if(gs_klog_cmd_ctrl_info.control_info == COMMAND_GET_OPTION)
    {
        SH_PRINT("Kernel log level is: %u", gs_klog_ctrl_info.global_level);
    }

    if(gs_klog_cmd_ctrl_info.control_info == COMMAND_SET_OPTION)
    {
        if (gs_klog_cmd_ctrl_info.level > KERN_DEBUG)
        {
            SH_PRINT("Invalid level(%u)", gs_klog_cmd_ctrl_info.level);
            return OS_EINVAL;
        }
    
        gs_klog_ctrl_info.global_level = gs_klog_cmd_ctrl_info.level;
        
        SH_PRINT("Set kernel log global level(%u) success", gs_klog_cmd_ctrl_info.level);

    }

    return ret; 

}
SH_CMD_EXPORT(klog_glvl_ctrl, sh_klog_global_level_control, "klog global level control");

static os_err_t sh_klog_tag_level_control(os_int32_t argc, char **argv)
{
    os_err_t   ret;
    os_uint16_t level;
    os_bool_t found;
    os_list_node_t           *node;
    os_list_node_t           *next;
    os_klog_tag_lvl_filter_t *tag_lvl_filter;

    if(argc < 2)
    {
        SH_PRINT("Command format:");
        SH_PRINT("klog_tlvl_ctrl [-s | -g | -d] [-n tag name] [-l tag level]");
        SH_PRINT("parameter Usage:");
  
        SH_PRINT("         -s     Set tag level option.");
        SH_PRINT("         -g     Get tag level option.");
        SH_PRINT("         -d     Delete tag level option.");
        SH_PRINT("         -n     Specify the tag name that want set level.");
        SH_PRINT("         -l     Specify a tag level that want to be set.");
        SH_PRINT("                level: 0-error, 1-warning, 2-info, 3-debug");
        return OS_EINVAL;
    }
    ret = klog_ctrl_info_get(argc,argv,&gs_klog_cmd_ctrl_info);
    
    if (ret != OS_EOK)
    {
        SH_PRINT("Wrong parameter, usage:");
        SH_PRINT("klog_tlvl_ctrl [-s | -g | -d] [-n tag name] [-l level]");
        return ret;
    }

    if(gs_klog_cmd_ctrl_info.control_info == COMMAND_GET_OPTION)
    {
#ifndef OS_USING_HEAP
            SH_PRINT("Not using memory heap, excute cmd failed");
            return OS_ENOMEM;
#endif
        if (strlen(gs_klog_cmd_ctrl_info.tag_name) == OS_FALSE)
        {
            SH_PRINT("Wrong parameter, usage:");
            SH_PRINT("klog_tlvl_ctrl [-g] [-n tag name] ");
            return OS_EINVAL;
        }
    
        found = os_get_klog_tag_lvl(gs_klog_cmd_ctrl_info.tag_name, &level);
        if (!found)
        {
            SH_PRINT("Not found tag(%s)", gs_klog_cmd_ctrl_info.tag_name);
            return OS_ERROR;
        }
        
        SH_PRINT("Tag(%s) level is: %u", gs_klog_cmd_ctrl_info.tag_name, level);
    }

    if(gs_klog_cmd_ctrl_info.control_info == COMMAND_SET_OPTION)
    {
        if (strlen(gs_klog_cmd_ctrl_info.tag_name) == OS_FALSE)
        {
            SH_PRINT("Wrong parameter, usage:");
            SH_PRINT("klog_tlvl_ctrl [-s] [-n tag name] [-l level]");
            return OS_EINVAL;
        }
    
        if (gs_klog_cmd_ctrl_info.level > KERN_DEBUG)
        {
            SH_PRINT("Invalid level(%u)", gs_klog_cmd_ctrl_info.level);
            SH_PRINT("level: 0-error, 1-warning, 2-info, 3-debug");
            return OS_EINVAL;
        }

        os_enter_critical();
        
        found = OS_FALSE;
        os_list_for_each(node, &gs_klog_ctrl_info.tag_lvl_list)
        {
            tag_lvl_filter = os_list_entry(node, os_klog_tag_lvl_filter_t, list);
    
            ret = os_strncmp(tag_lvl_filter->tag, gs_klog_cmd_ctrl_info.tag_name, KLOG_FILTER_TAG_MAX_LEN);
            if (0 == ret)
            {
                found = OS_TRUE;
                tag_lvl_filter->level = gs_klog_cmd_ctrl_info.level;
    
                break;
            }
        }
        
        os_exit_critical();
    
        if (!found)
        {
            tag_lvl_filter = OS_KERNEL_MALLOC(sizeof(os_klog_tag_lvl_filter_t));
            if (!tag_lvl_filter)
            {
                SH_PRINT("Alloc memory failed");
                return OS_ENOMEM;
            }
    
            os_memset(tag_lvl_filter->tag, 0, sizeof(tag_lvl_filter->tag));
            os_strncpy(tag_lvl_filter->tag, gs_klog_cmd_ctrl_info.tag_name, KLOG_FILTER_TAG_MAX_LEN);
            tag_lvl_filter->level = gs_klog_cmd_ctrl_info.level;
    
            os_enter_critical();
            os_list_add_tail(&gs_klog_ctrl_info.tag_lvl_list, &tag_lvl_filter->list);
            os_exit_critical();
        }
    
        SH_PRINT("Set kernel log tag level success, tag(%s), level(%u)", 
                  gs_klog_cmd_ctrl_info.tag_name, 
                  gs_klog_cmd_ctrl_info.level);
    }

    if(gs_klog_cmd_ctrl_info.control_info == COMMAND_DEL_OPTION)
    {
#ifndef OS_USING_HEAP
        SH_PRINT("Not using memory heap, excute cmd failed");
        return OS_ENOMEM;
#endif
        if (strlen(gs_klog_cmd_ctrl_info.tag_name) == OS_FALSE)
        {
            SH_PRINT("Wrong parameter, usage:");
            SH_PRINT("klog_tlvl_ctrl [-d] [-n tag name]");
            return OS_EINVAL;
        }
        os_enter_critical();
    
        found = OS_FALSE;
        os_list_for_each_safe(node, next, &gs_klog_ctrl_info.tag_lvl_list)
        {
            tag_lvl_filter = os_list_entry(node, os_klog_tag_lvl_filter_t, list);
    
            ret = os_strncmp(tag_lvl_filter->tag, gs_klog_cmd_ctrl_info.tag_name, KLOG_FILTER_TAG_MAX_LEN);
            if (0 == ret)
            {
                found = OS_TRUE;
                os_list_del(&tag_lvl_filter->list);
                
                break;
            }
        }
        
        os_exit_critical();
    
        if (found)
        {
            OS_KERNEL_FREE(tag_lvl_filter);
            tag_lvl_filter = OS_NULL;
    
            SH_PRINT("Del tag(%s) level success", gs_klog_cmd_ctrl_info.tag_name);
            
            return OS_EOK;
        }
        else
        {
            SH_PRINT("Not found tag(%s), del failed", gs_klog_cmd_ctrl_info.tag_name);
            
            return OS_ERROR;
        }

    }

    return ret; 

}
SH_CMD_EXPORT(klog_tlvl_ctrl, sh_klog_tag_level_control, "klog tag level control");

#endif /* OS_USING_SHELL */

#endif /* OS_DEBUG */

