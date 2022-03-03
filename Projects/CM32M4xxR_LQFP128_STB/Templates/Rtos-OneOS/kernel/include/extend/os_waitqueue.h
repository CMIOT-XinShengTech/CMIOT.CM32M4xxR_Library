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
 * @file        os_waitqueue.h
 *
 * @brief       Header file for waitqueue interface.
 *
 * @revision
 * Date         Author          Notes
 * 2020-03-19   OneOS Team      First Version
 ***********************************************************************************************************************
 */
#ifndef __OS_WAITQUEUE_H__
#define __OS_WAITQUEUE_H__

#include <os_errno.h>
#include <os_task.h>

#ifdef OS_USING_WAITQUEUE

#ifdef __cplusplus
extern "C" {
#endif

#define OS_WQ_FLAG_CLEAN    0x00
#define OS_WQ_FLAG_WAKEUP   0x01


struct os_waitqueue_node;
typedef os_err_t (*os_waitqueue_func_t)(struct os_waitqueue_node *wait, void *key);

/**
 ***********************************************************************************************************************
 * @struct      struct os_waitqueue_node
 *
 * @brief       Define waitqueue_node structure.
 ***********************************************************************************************************************
 */
struct os_waitqueue_node
{
    os_task_t          *polling_task;
    os_list_node_t      list;

    os_waitqueue_func_t wakeup;
    os_uint32_t         key;
};
typedef struct os_waitqueue_node os_waitqueue_node_t;

/**
 ***********************************************************************************************************************
 * @struct      struct os_waitqueue_node
 *
 * @brief       Define waitqueue structure.
 ***********************************************************************************************************************
 */
struct os_waitqueue
{
    os_uint32_t flag;               /*  Whether wake up has occurred. */
    os_list_node_t waiting_list;    /*  Waitqueue_nodes are linked on this list. */
};
typedef struct os_waitqueue os_waitqueue_t;


OS_INLINE void os_waitqueue_node_init(os_waitqueue_node_t *node,
                                      os_waitqueue_func_t  func,
                                      os_task_t           *polling_task,
                                      os_uint32_t          key)
{
    node->polling_task = polling_task;
    os_list_init(&node->list);

    node->wakeup = func;
    node->key = (os_uint32_t)key;
}

extern void     os_waitqueue_init(os_waitqueue_t *queue);

extern os_err_t os_waitqueue_default_do_wake(struct os_waitqueue_node *wait, void *key);

extern void     os_waitqueue_add(os_waitqueue_t *queue, os_waitqueue_node_t *node);

extern void     os_waitqueue_remove(os_waitqueue_node_t *node);

extern void     os_waitqueue_wakeup(os_waitqueue_t *queue, void *key);

extern os_err_t os_waitqueue_wait(os_waitqueue_t *queue, os_int32_t condition, os_tick_t timeout);


#define DEFINE_WAIT_FUNC(name, function, key)               \
                    struct os_waitqueue_node name = {       \
                    os_task_self(),                         \
                    OS_LIST_INIT(((name).list)),            \
                                                            \
                    function,                               \
                    key                                     \
                    }

#define DEFINE_WAIT_DEFAULT_FUNC(name) DEFINE_WAIT_FUNC(name, os_waitqueue_default_do_wake, 0)

#ifdef __cplusplus
}
#endif

#endif  /* OS_USING_WAITQUEUE */

#endif /* __OS_WAITQUEUE_H__ */

