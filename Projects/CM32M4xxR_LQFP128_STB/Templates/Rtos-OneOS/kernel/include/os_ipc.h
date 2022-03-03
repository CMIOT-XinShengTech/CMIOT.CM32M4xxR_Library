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
 * @file        os_ipc.h
 *
 * @brief       Ipc common data type definition and common interface implementation.
 *
 * @revision
 * Date         Author          Notes
 * 2020-02-11   OneOS Team      First Version
 ***********************************************************************************************************************
 */

#ifndef __OS_IPC_H__
#define __OS_IPC_H__

#include <oneos_config.h>
#include <os_types.h>
#include <os_list.h>
#include <os_stddef.h>
#include <os_object.h>
#include <os_task.h>

#ifdef __cplusplus
extern "C" {
#endif

#define OS_IPC_WAITING_FOREVER    ((os_tick_t)0xFFFFFFFF)
#define OS_IPC_WAITING_NO         ((os_tick_t)0)

/**
 ***********************************************************************************************************************
 * @enum        enum os_ipc_flag
 *
 * @brief       The ways to wake up blocked tasks.
 *
 ***********************************************************************************************************************
 */
enum os_ipc_flag
{
    OS_IPC_FLAG_FIFO,               /* Wake up blocked tasks in a first-in, first-out order. */
    OS_IPC_FLAG_PRIO,               /* Wake up blocked tasks in order of priority. */
};
typedef enum os_ipc_flag os_ipc_flag_t;

/**
 ***********************************************************************************************************************
 * @enum        enum os_ipc_cmd
 *
 * @brief       Define ipc control command.
 *
 ***********************************************************************************************************************
 */
enum os_ipc_cmd
{
    OS_IPC_CMD_RESET,
    OS_IPC_CMD_UNKNOWN,
};
typedef enum os_ipc_cmd os_ipc_cmd_t;


/**
 ***********************************************************************************************************************
 * @struct      struct os_ipc_object
 *
 * @brief       Define ipc object descriptor.
 *
 ***********************************************************************************************************************
 */
struct os_ipc_object
{
    os_object_t    parent;                              /* Inherit from os_object. */

    os_list_node_t suspend_task;                        /* Tasks pended on this resource. */
};
typedef struct os_ipc_object os_ipc_object_t;

extern os_err_t os_ipc_object_init(os_ipc_object_t *ipc);

extern os_err_t os_ipc_list_suspend(os_list_node_t *list,
                                    os_task_t      *task,
                                    os_uint8_t      flag);

extern os_err_t os_ipc_list_resume(os_list_node_t *list);

extern os_err_t os_ipc_list_resume_all(os_list_node_t *list);

#ifdef OS_USING_SHELL

extern void os_ipc_show_waiting_task(os_list_node_t *list);

#endif

#ifdef __cplusplus
}
#endif

#endif /* __OS_IPC_H__ */

