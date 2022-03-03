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
 * @file        os_mq.h
 *
 * @brief       Header file for message queue interface.
 *
 * @revision
 * Date         Author          Notes
 * 2020-02-14   OneOS Team      First Version
 ***********************************************************************************************************************
 */
#ifndef __OS_MQ_H__
#define __OS_MQ_H__

#include <oneos_config.h>
#include <os_ipc.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef OS_USING_MESSAGEQUEUE

/* Message header length. */
#define OS_MQ_MSG_HDR_LEN       sizeof(os_mq_msg_t)

/**
 ***********************************************************************************************************************
 * @struct      struct os_mq_msg
 *
 * @brief       Struct os_mq_msg is placed at the head of each message to organize all messages.
 ***********************************************************************************************************************
 */
struct os_mq_msg
{
    struct os_mq_msg   *next;
    os_uint32_t         msg_len;
};
typedef struct os_mq_msg os_mq_msg_t;

/**
 ***********************************************************************************************************************
 * @struct      struct os_mq
 *
 * @brief       Define message queue descriptor.
 ***********************************************************************************************************************
 */
struct os_mq
{
    struct os_ipc_object parent;                        /* Inherit from ipc_object. */

    void                *msg_pool;                      /* Message pool. */

    os_uint16_t          msg_size;                      /* Message size of each message. */
    os_uint16_t          max_msgs;                      /* Max number of messages. */

    os_uint16_t          entry;                         /* Index of messages in the queue. */

    void                *msg_queue_head;                /* List head. */
    void                *msg_queue_tail;                /* List tail. */
    void                *msg_queue_free;                /* Pointer indicated the free node of queue. */
    
    os_list_node_t       suspend_sender_task;           /* Sender task suspended on this messages queue. */
};
typedef struct  os_mq os_mq_t;

/*
 * message queue interface
 */

#ifdef OS_USING_HEAP

extern os_mq_t  *os_mq_create(const char     *name,
                              os_size_t       msg_size,
                              os_size_t       max_msgs,
                              os_ipc_flag_t   flag);

extern os_err_t os_mq_destroy(os_mq_t *mq);

#endif

extern os_err_t os_mq_init(os_mq_t        *mq,
                           const char     *name,
                           void           *msg_pool,
                           os_size_t       msg_pool_size,
                           os_size_t       msg_size,
                           os_ipc_flag_t   flag);

                            
extern os_err_t os_mq_deinit(os_mq_t *mq);

extern os_err_t os_mq_send(os_mq_t *mq, void *buffer, os_size_t buff_size, os_tick_t timeout);

extern os_err_t os_mq_send_urgent(os_mq_t *mq, void *buffer, os_size_t buff_size, os_tick_t timeout);

extern os_err_t os_mq_recv(os_mq_t    *mq,
                           void       *buffer,
                           os_size_t   buff_size,
                           os_tick_t   timeout,
                           os_size_t  *recv_size);

extern os_err_t os_mq_control(os_mq_t *mq, os_ipc_cmd_t cmd, void *arg);

#ifdef OS_USING_HOOK

extern void os_mq_try_send_set_hook(void (*hook)(os_mq_t *mq));
    
extern void os_mq_send_set_hook(void (*hook)(os_mq_t *mq));
    
extern void os_mq_try_recv_set_hook(void (*hook)(os_mq_t *mq));
    
extern void os_mq_recv_set_hook(void (*hook)(os_mq_t *mq));
    
#endif /* end OS_USING_HOOK */

#ifdef OS_USING_SHELL

extern os_err_t sh_list_msgqueue(os_int32_t argc, char **argv);

#endif /* end OS_USING_SHELL */


#endif

#ifdef __cplusplus
}
#endif

#endif /* __OS_MQ_H__ */
