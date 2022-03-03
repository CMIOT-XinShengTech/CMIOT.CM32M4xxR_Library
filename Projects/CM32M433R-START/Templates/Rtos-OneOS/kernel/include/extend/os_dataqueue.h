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
 * @file        os_dataqueue.h
 *
 * @brief       Header file for data queue interface.
 *
 * @revision
 * Date         Author          Notes
 * 2020-03-20   OneOS Team      First Version
 ***********************************************************************************************************************
 */
#ifndef __OS_DATAQUEUE_H__
#define __OS_DATAQUEUE_H__

#include <os_types.h>
#include <os_list.h>

#ifdef __cplusplus
extern "C" {
#endif

#define OS_DATAQUEUE_EVENT_UNKNOWN     0x00
#define OS_DATAQUEUE_EVENT_POP         0x01
#define OS_DATAQUEUE_EVENT_PUSH        0x02
#define OS_DATAQUEUE_EVENT_THRESHOLD   0x03

#define OS_DATAQUEUE_SIZE(dq)        ((dq)->put_index - (dq)->get_index)
#define OS_DATAQUEUE_EMPTY(dq)       ((dq)->size - OS_DATAQUEUE_SIZE(dq))

/**
 ***********************************************************************************************************************
 * @struct      struct os_data_item
 *
 * @brief       data item descriptor
 ***********************************************************************************************************************
 */
struct os_data_item
{
    const void *data_ptr;
    os_size_t   data_size;
};
typedef struct os_data_item os_data_item_t;

/**
 ***********************************************************************************************************************
 * @struct      struct os_data_queue
 *
 * @brief       Define data queue descriptor.
 ***********************************************************************************************************************
 */
struct os_data_queue
{
    os_uint16_t size;                       /* Data queue holds the maximum number of data item. */
    os_uint16_t threshold;                  /* When the number of data item less than this,resume the push task. */

    os_uint16_t get_index;                  /* Get index. */
    os_uint16_t put_index;                  /* Put index. */

    os_data_item_t *queue;                  /* The pointer of data item. */

    os_list_node_t  suspended_push_list;    /* Push task on this list. */    
    os_list_node_t  suspended_pop_list;     /* Pop task on this list. */    

    void (*evt_notify)(struct os_data_queue *queue, os_uint32_t event);     /* Event notify. */
};
typedef struct os_data_queue os_data_queue_t;


extern os_err_t os_data_queue_init(os_data_queue_t *queue,
                                   os_uint16_t      size,
                                   os_uint16_t      threshold,
                                   void           (*evt_notify)(os_data_queue_t *queue, os_uint32_t event));

extern os_err_t os_data_queue_deinit(os_data_queue_t *queue);

extern os_err_t os_data_queue_push(os_data_queue_t *queue,
                                   const void      *data_ptr,
                                   os_size_t        data_size,
                                   os_tick_t        timeout);

extern os_err_t os_data_queue_pop(os_data_queue_t *queue, const void **data_ptr, os_size_t *size, os_tick_t timeout);
extern os_err_t os_data_queue_peak(os_data_queue_t *queue, const void **data_ptr, os_size_t *size);
extern void     os_data_queue_reset(os_data_queue_t *queue);

#ifdef __cplusplus
}
#endif

#endif /* __OS_DATAQUEUE_H__ */

