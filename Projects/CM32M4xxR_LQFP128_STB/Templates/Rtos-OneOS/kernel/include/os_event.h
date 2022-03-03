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
 * @file        os_event.h
 *
 * @brief       Header file for event interface.
 *
 * @revision
 * Date         Author          Notes
 * 2020-02-13   OneOS team      First Version
 ***********************************************************************************************************************
 */

#ifndef __OS_EVENT_H__
#define __OS_EVENT_H__

#include <oneos_config.h>
#include <os_ipc.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef OS_USING_EVENT

enum os_event_option
{
    OS_EVENT_OPTION_AND               = 0x01,
    OS_EVENT_OPTION_OR                = 0x02,
    OS_EVENT_OPTION_CLEAR             = 0x04
};
typedef enum os_event_option os_event_option_t;

/**
 ***********************************************************************************************************************
 * @struct      struct os_event
 *
 * @brief       Define event descriptor.
 ***********************************************************************************************************************
 */
struct os_event
{
    os_ipc_object_t parent;                 /* Inherit from ipc_object. */

    os_uint32_t     set;                    /* Event set. */
};
typedef struct os_event os_event_t;

extern os_err_t    os_event_init(os_event_t *event, const char *name, os_ipc_flag_t flag);
extern os_err_t    os_event_deinit(os_event_t *event);

#ifdef OS_USING_HEAP
extern os_event_t *os_event_create(const char *name, os_ipc_flag_t flag);
extern os_err_t    os_event_destroy(os_event_t *event);
#endif

extern os_err_t    os_event_send(os_event_t *event, os_uint32_t set);
extern os_err_t    os_event_recv(os_event_t     *event,
                                 os_uint32_t    interested_set,
                                 os_uint8_t     option,
                                 os_tick_t      timeout,
                                 os_uint32_t    *recved_set);
extern os_err_t    os_event_control(os_event_t *event, os_ipc_cmd_t cmd, void *arg);

#ifdef OS_USING_HOOK
extern void        os_event_send_set_hook(void (*hook)(os_event_t *event));
extern void        os_event_try_recv_set_hook(void (*hook)(os_event_t *event));
extern void       os_event_recv_set_hook(void (*hook)(os_event_t *event));
#endif /* end of OS_USING_HOOK */

#endif /* OS_USING_EVENT */

#ifdef __cplusplus
}
#endif

#endif /* __OS_EVENT_H__ */
