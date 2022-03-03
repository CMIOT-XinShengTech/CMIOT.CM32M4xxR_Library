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
 * @file        os_mailbox.h
 *
 * @brief       Header file for mailbox interface.
 *
 * @revision
 * Date         Author          Notes
 * 2020-02-13   OneOS team      First Version
 ***********************************************************************************************************************
 */

#ifndef __OS_MAILBOX_H__
#define __OS_MAILBOX_H__

#include <oneos_config.h>
#include "os_ipc.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef OS_USING_MAILBOX

/**
 ***********************************************************************************************************************
 * @struct      struct os_mailbox
 *
 * @brief       Define mailbox descriptor.
 ***********************************************************************************************************************
 */
struct os_mailbox
{
    struct os_ipc_object parent;                        /* Inherit from ipc_object. */

    os_uint32_t         *msg_pool;                      /* Start address of message buffer. */

    os_uint16_t          size;                          /* Size of message pool. */

    os_uint16_t          entry;                         /* Index of messages in msg_pool. */
    os_uint16_t          in_offset;                     /* Input offset of the message buffer. */
    os_uint16_t          out_offset;                    /* Output offset of the message buffer. */

    os_list_node_t       suspend_sender_task;           /* Sender task suspended on this mailbox. */
};
typedef struct os_mailbox os_mailbox_t;

/*
 * mailbox interface
 */


#ifdef OS_USING_HEAP

extern os_mailbox_t *os_mb_create(const char *name, os_size_t max_mails, os_ipc_flag_t flag);

extern os_err_t os_mb_destroy(os_mailbox_t *mb);

#endif                                 

extern os_err_t os_mb_init(os_mailbox_t  *mb,
                           const char    *name,                              
                           void          *msg_pool,
                           os_size_t      msg_pool_size,
                           os_ipc_flag_t  flag);
    
extern os_err_t os_mb_deinit(os_mailbox_t *mb);

extern os_err_t os_mb_send(os_mailbox_t *mb, os_uint32_t value, os_tick_t timeout);

extern os_err_t os_mb_recv(os_mailbox_t *mb, os_uint32_t *value, os_tick_t timeout);

extern os_err_t os_mb_control(os_mailbox_t *mb, os_ipc_cmd_t cmd, void *arg);

#ifdef OS_USING_HOOK

extern void os_mb_try_send_set_hook(void (*hook)(os_mailbox_t *mb));
    
extern void os_mb_send_set_hook(void (*hook)(os_mailbox_t *mb));
    
extern void os_mb_try_recv_set_hook(void (*hook)(os_mailbox_t *mb));
    
extern void os_mb_recv_set_hook(void (*hook)(os_mailbox_t *mb));
    
#endif /* end OS_USING_HOOK */

#ifdef OS_USING_SHELL
    
extern os_err_t sh_list_mailbox(os_int32_t argc, char **argv);
    
#endif /* end OS_USING_SHELL */



#endif /* end of OS_USING_MAILBOX */
    


#ifdef __cplusplus
}
#endif

#endif /* __OS_MAILBOX_H__ */
