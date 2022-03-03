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
 * @file        os_assert.h
 *
 * @brief       Support diagnostic functions
 *
 * @revision
 * Date         Author          Notes
 * 2020-02-12   OneOS Team      First version
 ***********************************************************************************************************************
 */

#ifndef __OS_ASSERT_H__
#define __OS_ASSERT_H__

#include <oneos_config.h>
#include <os_util.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef OS_USING_ASSERT
#define OS_ASSERT(EX)                                                           \
do                                                                              \
{                                                                               \
    if (!(EX))                                                                  \
    {                                                                           \
        os_assert_handler(#EX, __FUNCTION__, __LINE__);                         \
    }                                                                           \
} while (0)
#else
#define OS_ASSERT(EX)
#endif /* OS_USING_ASSERT */

#ifdef __cplusplus
}
#endif

#endif /* __OS_ASSERT_H__ */

