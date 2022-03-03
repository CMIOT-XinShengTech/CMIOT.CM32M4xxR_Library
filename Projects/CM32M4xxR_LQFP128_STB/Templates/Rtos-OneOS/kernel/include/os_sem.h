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
 * @file        os_sem.h
 *
 * @brief       Header file for semaphore interface
 *
 * @revision
 * Date         Author          Notes
 * 2020-02-11   OneOS team      First Version
 ***********************************************************************************************************************
 */

#ifndef __OS_SEM_H__
#define __OS_SEM_H__

#include <oneos_config.h>
#include <os_types.h>
#include <os_ipc.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef OS_USING_SEMAPHORE

#define OS_SEM_MAX_COUNT         0x10000U

/**
 ***********************************************************************************************************************
 * @struct      struct os_semaphore
 *
 * @brief       Define semaphore descriptor.
 ***********************************************************************************************************************
 */
struct os_semaphore
{
    os_ipc_object_t parent;                        /* Inherit from os_ipc_object. */

    os_uint16_t     count;                         /* Count of semaphore. */
};
typedef struct os_semaphore os_sem_t;

extern os_err_t  os_sem_init(os_sem_t *sem, const char *name, os_uint16_t value, os_ipc_flag_t flag);
extern os_err_t  os_sem_deinit(os_sem_t *sem);

#ifdef OS_USING_HEAP
extern os_sem_t *os_sem_create(const char *name, os_uint16_t value, os_ipc_flag_t flag);
extern os_err_t  os_sem_destroy(os_sem_t *sem);
#endif

extern os_err_t  os_sem_wait(os_sem_t *sem, os_tick_t timeout);
extern os_err_t  os_sem_post(os_sem_t *sem);
extern os_err_t  os_sem_control(os_sem_t *sem, os_ipc_cmd_t cmd, void *arg);

#ifdef OS_USING_HOOK
extern void      os_sem_try_wait_set_hook(void (*hook)(os_sem_t *sem));
extern void      os_sem_wait_set_hook(void (*hook)(os_sem_t *sem));
extern void      os_sem_post_set_hook(void (*hook)(os_sem_t *sem));
#endif /* end OS_USING_HOOK */

#endif /* OS_USING_SEMAPHORE */

#ifdef __cplusplus
}
#endif

#endif /* __OS_SEM_H__ */

