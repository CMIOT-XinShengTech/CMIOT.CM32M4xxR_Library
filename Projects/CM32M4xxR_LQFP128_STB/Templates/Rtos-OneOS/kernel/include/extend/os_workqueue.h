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
 * @file        os_workqueue.h
 *
 * @brief       Header file for workqueue interface.
 *
 * @revision
 * Date         Author          Notes
 * 2020-04-06   OneOS Team      First version.
 ***********************************************************************************************************************
 */
#ifndef __OS_WORKQUEUE_H__
#define __OS_WORKQUEUE_H__

#include <oneos_config.h>
#include <os_stddef.h>
#include <os_list.h>
#include <os_timer.h>
#include <os_task.h>
#include <os_sem.h>

#ifdef __cplusplus
extern "C" {
#endif

enum os_work_stage
{
    OS_WORK_STAGE_INIT       = 0,       /* The work is in initialization state. */
    OS_WORK_STAGE_SUBMITTING = 1,       /* The work is on delaying_list_head, waiting time arrives for execution. */
    OS_WORK_STAGE_PENDING    = 2,       /* The work is on pending_list_head, queuing for execution. */
    OS_WORK_STAGE_PROCESSING = 3,       /* The work is in progress. */
    OS_WORK_STAGE_CANCELED   = 4        /* The work is canceled. */
};
typedef enum os_work_stage os_work_stage_t;

struct os_workqueue;
struct os_work
{
    os_list_node_t      list;
    
    void              (*func)(struct os_work *work, void *data);    /* Callback function for work. */
    void               *data;                                       /* Private data for callback function. */

    void              (*cleanup)(struct os_work *work);             /* The cleanup function of the work using for deinit. */
    
    os_work_stage_t     stage;                                      /* Execution stage of the work. */
    os_uint16_t         ref_count;                                  /* Reference count. */
    
    os_timer_t          timer;                                      /* Using for delayed work. */
    os_sem_t            sem;                                        /* Using for synchronization cancellation. */
    
    struct os_workqueue *workqueue;                                 /* Workqueue used to execute work. */
};
typedef struct os_work os_work_t;

struct os_workqueue
{
    os_list_node_t  pending_list_head;    
    os_list_node_t  delaying_list_head;  

    os_work_t      *work_current;           /* Work in progress on workqueue. */
    os_task_t      *process_task;           /* Task on the workqueue to execute work. */
    
    os_sem_t        process_sem;            /* Semaphore for synchronization. */                                   

    os_bool_t       destroy;                /* Used to flag whether the workqueue is destroyed. */             
};
typedef struct os_workqueue os_workqueue_t;

extern os_workqueue_t *os_workqueue_create(const char *name, os_uint32_t stack_size, os_uint8_t priority);
extern os_err_t        os_workqueue_destroy(os_workqueue_t *queue);
extern os_err_t        os_workqueue_submit_work(os_workqueue_t *queue, os_work_t *work, os_tick_t delay_time);
extern os_err_t        os_workqueue_cancel_work(os_workqueue_t *queue, os_work_t *work);
extern os_err_t        os_workqueue_cancel_work_sync(os_workqueue_t *queue, os_work_t *work);
extern void            os_workqueue_cancel_all_work(os_workqueue_t *queue);

extern void            os_work_init(os_work_t *work, void (*func)(os_work_t *work, void *data), void *data);
extern void            os_work_deinit(os_work_t *work, void (*cleanup)(os_work_t *work));

#ifdef OS_USING_SYSTEM_WORKQUEUE
extern os_err_t        os_submit_work(os_work_t *work, os_tick_t delay_time);
extern os_err_t        os_cancel_work(os_work_t *work);
extern os_err_t        os_cancel_work_sync(os_work_t *work);
extern void            os_cancel_all_work(void);
#endif /* OS_USING_SYSTEM_WORKQUEUE */

#ifdef __cplusplus
}
#endif

#endif /* __OS_WORKQUEUE_H__ */

