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
 * @file        os_mutex.h
 *
 * @brief       Header file for mutex interface.
 *
 * @revision
 * Date         Author          Notes
 * 2020-02-21   OneOS team      First Version
 ***********************************************************************************************************************
 */

#ifndef __OS_MUTEX_H__
#define __OS_MUTEX_H__

#include <oneos_config.h>
#include <os_ipc.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef OS_USING_MUTEX

/**
 ***********************************************************************************************************************
 * @struct      struct os_mutex
 *
 * @brief       Define mutex descriptor.
 ***********************************************************************************************************************
 */
struct os_mutex
{
    os_ipc_object_t parent;                        /* Inherit from os_ipc_object. */

    os_uint8_t      original_priority;             /* Priority of last task lock the mutex. */
    os_uint8_t      nested;                        /* Number of times current owner lock the mutex. */
    os_bool_t       recursive;                     /* Support recursive call. */

    os_task_t       *owner;                        /* Current owner of the mutex. */
};
typedef struct os_mutex os_mutex_t;

extern os_err_t    os_mutex_init(os_mutex_t *mutex, const char *name, os_ipc_flag_t flag, os_bool_t recursive);
extern os_err_t    os_mutex_deinit(os_mutex_t *mutex);

#ifdef OS_USING_HEAP
extern os_mutex_t *os_mutex_create(const char *name, os_ipc_flag_t flag, os_bool_t recursive);
extern os_err_t    os_mutex_destroy(os_mutex_t *mutex);
#endif

extern os_err_t    os_mutex_lock(os_mutex_t *mutex, os_tick_t timeout);
extern os_err_t    os_mutex_unlock(os_mutex_t *mutex);
extern os_err_t    os_mutex_recursive_lock(os_mutex_t *mutex, os_tick_t timeout);
extern os_err_t    os_mutex_recursive_unlock(os_mutex_t *mutex);
extern os_err_t    os_mutex_control(os_mutex_t *mutex, os_ipc_cmd_t cmd, void *arg);

#ifdef OS_USING_HOOK  
extern void        os_mutex_try_lock_set_hook(void (*hook)(os_mutex_t *mutex));
extern void        os_mutex_lock_set_hook(void (*hook)(os_mutex_t *mutex));
extern void        os_mutex_unlock_set_hook(void (*hook)(os_mutex_t *mutex));
#endif /* end of OS_USING_HOOK */

#endif /* OS_USING_MUTEX */

#ifdef __cplusplus
}
#endif

#endif /* __OS_MUTEX_H__ */

