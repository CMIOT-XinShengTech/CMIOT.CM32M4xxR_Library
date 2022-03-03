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
 * @file        os_object.h
 *
 * @brief       Header file for object interface.
 *
 * @revision
 * Date         Author          Notes
 * 2020-02-10   OneOS Team      First version.
 ***********************************************************************************************************************
 */
#ifndef __OS_OBJECT_H__
#define __OS_OBJECT_H__

#include <oneos_config.h>
#include <os_types.h>
#include <os_list.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 ***********************************************************************************************************************
 * @enum        enum os_object_type
 *
 * @brief       Define object information enumeration.
 ***********************************************************************************************************************
 */
enum os_object_type
{
    OS_OBJECT_NULL   = 0,                   /* The object is not used. */
    OS_OBJECT_TASK,                         /* The object is a task. */
    OS_OBJECT_SEMAPHORE,                    /* The object is a semaphore. */
    OS_OBJECT_MUTEX,                        /* The object is a mutex. */
    OS_OBJECT_EVENT,                        /* The object is a event. */
    OS_OBJECT_MAILBOX,                      /* The object is a mail box. */
    OS_OBJECT_MESSAGEQUEUE,                 /* The object is a message queue. */
    OS_OBJECT_MEMHEAP,                      /* The object is a memory heap */
    OS_OBJECT_MEMPOOL,                      /* The object is a memory pool. */
    OS_OBJECT_DEVICE,                       /* The object is a device */
    OS_OBJECT_TIMER,                        /* The object is a timer. */
    OS_OBJECT_MODULE,                       /* The object is a module. */
    OS_OBJECT_UNKNOWN,                      /* The object is unknown. */
};

/**
 ***********************************************************************************************************************
 * @struct      struct os_object
 *
 * @brief       object descriptor
 ***********************************************************************************************************************
 */
struct os_object
{
    char            name[OS_NAME_MAX + 1];  /* Name of kernel object. */
    os_uint8_t      type;                   /* Type of kernel object. */
    os_uint8_t      flag;                   /* Flag of kernel object. */
    os_bool_t       is_static;              /* Is kernel object static. */
#ifdef OS_USING_MODULE
    void           *module_id;              /* Id of application module. */
#endif
    os_list_node_t  list;                   /* List node of kernel object. */
};
typedef struct os_object os_object_t;

/**
 ***********************************************************************************************************************
 * @struct      struct os_object_info
 *
 * @brief       object information descriptor
 ***********************************************************************************************************************
 */
struct os_object_info
{
    enum os_object_type    type;                  /* Type of kernel object. */
    os_list_node_t         object_list;           /* List node of kernel object. */
};
typedef struct os_object_info os_object_info_t;

 /**
 ***********************************************************************************************************************
 * @def         OS_OBJECT_HOOK_CALL
 *
 * @brief       The macro is used to call the hook function.
 *
 * @param       func            The pointer to hook function.
 * @param       argv            The input parameter to hook function.
 ***********************************************************************************************************************
 */
#ifdef OS_USING_HOOK
#define OS_OBJECT_HOOK_CALL(func, argv) \
    do                                  \
    {                                   \
       if ((func) != OS_NULL)           \
       {                                \
           func argv;                   \
       }                                \
    } while (0)
#else
#define OS_OBJECT_HOOK_CALL(func, argv)
#endif

#ifdef OS_USING_HOOK
extern void os_object_attach_set_hook(void (*hook)(os_object_t *object));
extern void os_object_detach_set_hook(void (*hook)(os_object_t *object));
#endif

extern os_object_info_t *os_object_get_info(enum os_object_type type);

extern void os_object_init(os_object_t *object, enum os_object_type type, const char *name, os_bool_t static_flag);
extern void os_object_deinit(os_object_t *object);

extern os_bool_t    os_object_is_static(os_object_t *object);
extern os_uint8_t   os_object_get_type(os_object_t *object);
extern os_object_t *os_object_find(const char *name, os_uint8_t type);

#ifdef OS_USING_SHELL
extern os_int32_t os_object_name_maxlen(const char *type_name, os_list_node_t *list);
extern void       os_object_split(os_int32_t len);
#endif

#ifdef __cplusplus
}
#endif

#endif

