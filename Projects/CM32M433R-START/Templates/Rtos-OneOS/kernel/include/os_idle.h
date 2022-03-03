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
 * @file        os_idle.h
 *
 * @brief       The header file for idle task.
 *
 * @revision
 * Date         Author          Notes
 * 2020-02-19   OneOS Team      First Version
 ***********************************************************************************************************************
 */
 
#ifndef __OS_IDLE_H__
#define __OS_IDLE_H__

#include <oneos_config.h>
#include <os_types.h>
#include <os_stddef.h>
#include <os_object.h>
#include <os_task.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(OS_USING_HOOK) || defined(OS_USING_IDLE_HOOK)
extern os_err_t os_idle_task_set_hook(void (*hook)(void));
extern os_err_t os_idle_task_del_hook(void (*hook)(void));
#endif

#ifdef __cplusplus
}
#endif

#endif

