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
 * @file        os_completion.h
 *
 * @brief       Header file for completion interface.
 *
 * @revision
 * Date         Author          Notes
 * 2020-03-20   OneOS Team      First Version
 ***********************************************************************************************************************
 */
#ifndef __OS_COMPLETION_H__
#define __OS_COMPLETION_H__

#include <os_types.h>
#include <os_list.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 ***********************************************************************************************************************
 * @struct      struct os_completion
 *
 * @brief       completion descriptor
 ***********************************************************************************************************************
 */
struct os_completion
{
    os_uint32_t    flag;

    os_list_node_t suspended_list;
};

typedef struct os_completion os_completion_t;

extern void     os_completion_init(os_completion_t *completion);
extern void     os_completion_deinit(os_completion_t *completion);
extern os_err_t os_completion_wait(os_completion_t *completion, os_tick_t timeout);
extern void     os_completion_done(os_completion_t *completion);

#ifdef __cplusplus
}
#endif

#endif /* __OS_COMPLETION_H__ */

