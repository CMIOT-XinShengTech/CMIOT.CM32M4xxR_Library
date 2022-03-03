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
 * @file        os_object.c
 *
 * @brief       This file implements the object functions
 *
 * @revision
 * Date         Author          Notes
 * 2020-02-10   OneOS team      First Version
 ***********************************************************************************************************************
 */
#include <oneos_config.h>
#include <os_errno.h>
#include <os_object.h>
#include <os_module.h>
#include <os_hw.h>
#include "os_kernel_internal.h"
#include "os_util_internal.h"

/**
 ***********************************************************************************************************************
 * @enum        enum os_object_info_type
 *
 * @brief       Define object information type enumeration.
 ***********************************************************************************************************************
 */
enum os_object_info_type
{
    OS_OBJECT_INFO_TASK = 0,    /* The object is a task. */
#ifdef OS_USING_SEMAPHORE
    OS_OBJECT_INFO_SEMAPHORE,   /* The object is a semaphore. */
#endif
#ifdef OS_USING_MUTEX
    OS_OBJECT_INFO_MUTEX,       /* The object is a mutex. */
#endif
#ifdef OS_USING_EVENT
    OS_OBJECT_INFO_EVENT,       /* The object is a event. */
#endif
#ifdef OS_USING_MAILBOX
    OS_OBJECT_INFO_MAILBOX,     /* The object is a mail box. */
#endif
#ifdef OS_USING_MESSAGEQUEUE
    OS_OBJECT_INFO_MESSAGEQUEUE,/* The object is a message queue. */
#endif
#ifdef OS_USING_MEM_HEAP
    OS_OBJECT_INFO_MEMHEAP,     /* The object is a memory heap */
#endif
#ifdef OS_USING_MEM_POOL
    OS_OBJECT_INFO_MEMPOOL,     /* The object is a memory pool. */
#endif
#ifdef OS_USING_DEVICE
    OS_OBJECT_INFO_DEVICE,      /* The object is a device */
#endif
    OS_OBJECT_INFO_TIMER,       /* The object is a timer. */
#ifdef OS_USING_MODULE
    OS_OBJECT_INFO_MODULE,      /* The object is a module. */
#endif
    OS_OBJECT_INFO_UNKNOWN,     /* The object is unknown. */
};

/**
 ***********************************************************************************************************************
 * @def         _OBJ_CONTAINER_LIST_INIT
 *
 * @brief       This macro will initialize empty of object head.  
 *
 * @param       c               The object head.
 ***********************************************************************************************************************
 */
#define _OBJ_CONTAINER_LIST_INIT(c)     \
    {&(gs_os_object_container[c].object_list), &(gs_os_object_container[c].object_list)}

static os_object_info_t gs_os_object_container[OS_OBJECT_INFO_UNKNOWN] =
{
    /* initialize object container - task */
    {OS_OBJECT_TASK, _OBJ_CONTAINER_LIST_INIT(OS_OBJECT_INFO_TASK)},
#ifdef OS_USING_SEMAPHORE
    /* initialize object container - semaphore */
    {OS_OBJECT_SEMAPHORE, _OBJ_CONTAINER_LIST_INIT(OS_OBJECT_INFO_SEMAPHORE)},
#endif
#ifdef OS_USING_MUTEX
    /* initialize object container - mutex */
    {OS_OBJECT_MUTEX, _OBJ_CONTAINER_LIST_INIT(OS_OBJECT_INFO_MUTEX)},
#endif
#ifdef OS_USING_EVENT
    /* initialize object container - event */
    {OS_OBJECT_EVENT, _OBJ_CONTAINER_LIST_INIT(OS_OBJECT_INFO_EVENT)},
#endif
#ifdef OS_USING_MAILBOX
    /* initialize object container - mailbox */
    {OS_OBJECT_MAILBOX, _OBJ_CONTAINER_LIST_INIT(OS_OBJECT_INFO_MAILBOX)},
#endif
#ifdef OS_USING_MESSAGEQUEUE
    /* initialize object container - message queue */
    {OS_OBJECT_MESSAGEQUEUE, _OBJ_CONTAINER_LIST_INIT(OS_OBJECT_INFO_MESSAGEQUEUE)},
#endif
#ifdef OS_USING_MEM_HEAP
    /* initialize object container - memory heap */
    {OS_OBJECT_MEMHEAP, _OBJ_CONTAINER_LIST_INIT(OS_OBJECT_INFO_MEMHEAP)},
#endif
#ifdef OS_USING_MEM_POOL
    /* initialize object container - memory pool */
    {OS_OBJECT_MEMPOOL, _OBJ_CONTAINER_LIST_INIT(OS_OBJECT_INFO_MEMPOOL)},
#endif
#ifdef OS_USING_DEVICE
    /* initialize object container - device */
    {OS_OBJECT_DEVICE, _OBJ_CONTAINER_LIST_INIT(OS_OBJECT_INFO_DEVICE)},
#endif
    /* initialize object container - timer */
    {OS_OBJECT_TIMER, _OBJ_CONTAINER_LIST_INIT(OS_OBJECT_INFO_TIMER)},
#ifdef OS_USING_MODULE
    /* initialize object container - module */
    {OS_OBJECT_MODULE, _OBJ_CONTAINER_LIST_INIT(OS_OBJECT_INFO_MODULE)},
#endif
};

#ifdef OS_USING_HOOK
static void (*gs_os_object_attach_hook)(os_object_t *object) = OS_NULL;
static void (*gs_os_object_detach_hook)(os_object_t *object) = OS_NULL;

/**
 ***********************************************************************************************************************
 * @brief           This function will set a hook function, the hook will be called 
 *                  at the end of os_object_init function
 *
 * @param[in]       hook             The hook function is complemented by user.
 *
 * @return          None
 ***********************************************************************************************************************
 */
void os_object_attach_set_hook(void (*hook)(os_object_t *object))
{
    gs_os_object_attach_hook = hook;
}

/**
 ***********************************************************************************************************************
 * @brief           This function will set a hook function, the hook will be called 
 *                  at the beginning of os_object_deinit function.
 *
 * @param[in]       hook             The hook function is complemented by user.
 *
 * @return          None
 ***********************************************************************************************************************
 */
void os_object_detach_set_hook(void (*hook)(os_object_t *object))
{
    gs_os_object_detach_hook = hook;
}

#endif

/**
 ***********************************************************************************************************************
 * @brief           This function will return the information pointer of the specified object.
 *
 * @param[in]       type            The type of object.
 *
 * @return          The infomation pointer of the specified object.
 * @retval          OS_NULL         Get the object infomation failed.
 * @retval          else            Get the object infomation successful.
 ***********************************************************************************************************************
 */
os_object_info_t *os_object_get_info(enum os_object_type type)
{
    os_int32_t index;

    for (index = OS_OBJECT_INFO_TASK; index < OS_OBJECT_INFO_UNKNOWN; index++)
    {
        if (gs_os_object_container[index].type == type) 
        {
            return &gs_os_object_container[index];
        }
    }

    return OS_NULL;
}
EXPORT_SYMBOL(os_object_get_info);

/**
 ***********************************************************************************************************************
 * @brief           This function will initialize an object and place it on object list.
 *
 * @param[in]       object          The descriptor of object.
 * @param[in]       type            The type of object.
 * @param[in]       name            Pointer to object name string.
 * @param[in]       static_flag     The static flag of object.
 *
 * @return          None.
 ***********************************************************************************************************************
 */
void os_object_init(os_object_t *object, enum os_object_type type, const char *name, os_bool_t static_flag)
{
    os_list_node_t     *node;
    os_object_info_t   *info;
    os_object_t        *obj;
    register os_base_t temp;
    
#ifdef OS_USING_MODULE
    struct os_module *module = os_module_self();
#endif

    OS_ASSERT(OS_NULL != object);

    info = os_object_get_info(type);
    OS_ASSERT(OS_NULL != info);

    os_enter_critical();
    
    /* Try to find object,check object type to avoid re-initialization. */
    os_list_for_each(node, &info->object_list)
    {
        obj = os_list_entry(node, os_object_t, list);
        OS_ASSERT(obj != object);
    }
    (void)obj;
    
    os_exit_critical();

    object->type = type;
    
    object->is_static = static_flag;

    /* Before copy name, make sure name is all '\0'. */
    os_memset(object->name, 0, sizeof(object->name));
    
    if (OS_NULL != name)
    {
        os_strncpy(object->name, name, OS_NAME_MAX);
    }

    OS_OBJECT_HOOK_CALL(gs_os_object_attach_hook, (object));

    temp = os_hw_interrupt_disable();

#ifdef OS_USING_MODULE
    if (module)
    {
        os_list_add(&module->object_list, &object->list);
        object->module_id = (void *)module;
    }
    else
#endif
    {
        /* place object on related types of object list */
        os_list_add(&info->object_list, &object->list);
    }

    os_hw_interrupt_enable(temp);
}

/**
 ***********************************************************************************************************************
 * @brief           This function will deinitialize an object and remove it from object list.
 *
 * @param[in]       object          The object to be deinitialized.
 *
 * @return          None.
 ***********************************************************************************************************************
 */
void os_object_deinit(os_object_t *object)
{
    register os_base_t temp;

    OS_ASSERT(OS_NULL != object);

    OS_OBJECT_HOOK_CALL(gs_os_object_detach_hook, (object));

    /* Reset object type. */
    object->type = OS_OBJECT_NULL;

    temp = os_hw_interrupt_disable();

    /* Remove from object list. */
    os_list_del(&object->list);

    os_hw_interrupt_enable(temp);
}

/**
 ***********************************************************************************************************************
 * @brief           This function returns static flag of the object.
 *
 * @param[in]       object          The descriptor of object.
 *
 * @return          Static flag of the object.
 * @retval          OS_FASLE        The memory space of object is not static.
 * @retval          OS_TRUE         The memory space of object is static.
 ***********************************************************************************************************************
 */
os_bool_t os_object_is_static(os_object_t *object)
{
    OS_ASSERT(OS_NULL != object);

    return object->is_static;
}

/**
 ***********************************************************************************************************************
 * @brief           This function returns type of the object
 *
 * @param[in]       object          The descriptor of object.
 *
 * @return          Type of the object.
 ***********************************************************************************************************************
 */
os_uint8_t os_object_get_type(os_object_t *object)
{
    OS_ASSERT(OS_NULL != object);

    return object->type;
}

/**
 ***********************************************************************************************************************
 * @brief           This function will find object by name on related types of object list.
 *                  
 * @param[in]       name            Pointer to object name string
 * @param[in]       type            The type of object.
 *
 * @return          On success, return a object descriptor; on error, OS_NULL is returned.
 * @retval          not OS_NULL     Return a object descriptor.
 * @retval          OS_NULL         Call os_object_find failed.
 ***********************************************************************************************************************
 */
os_object_t *os_object_find(const char *name, os_uint8_t type)
{
    os_object_t      *object;
    os_list_node_t   *node;
    os_object_info_t *info;

    if ((OS_NULL == name) || (type > OS_OBJECT_UNKNOWN))
    {
        return OS_NULL;
    }

    /* Which is invoke in interrupt status. */
    OS_DEBUG_NOT_IN_INTERRUPT;

    os_enter_critical();

    /* Try to find object. */
    info = os_object_get_info((enum os_object_type)type);
    OS_ASSERT(OS_NULL != info);
    
    os_list_for_each(node, &info->object_list)
    {
        object = os_list_entry(node, os_object_t, list);
        if (0 == os_strncmp(object->name, name, OS_NAME_MAX))
        {
            os_exit_critical();
            
            return object;
        }
    }

    os_exit_critical();

    return OS_NULL;
}

#ifdef OS_USING_SHELL
/**
 ***********************************************************************************************************************
 * @brief           This function returns the maximum length of the object type name and object name.
 *
 * @details         This function is used for kernel object alignment print,will find the maximum length in the kernel 
 *                  object type name and object name in the object list.
 *
 * @param[in]       type_name       The object type name.
 * @param[in]       list            The object list.
 *
 * @return          The maximum length of object type name and object name.
 ***********************************************************************************************************************
 */
os_int32_t os_object_name_maxlen(const char *type_name, os_list_node_t *list)
{
    os_base_t       level;
    os_int32_t      max_length;
    os_int32_t      length;
    os_object_t    *object;
    os_list_node_t *node;

    max_length = os_strlen(type_name);

    level = os_hw_interrupt_disable();

    for (node = list->next; node != list; node = node->next)
    {
        object = os_list_entry(node, os_object_t, list);
        length = os_strlen(object->name);
        if (length > max_length)
        {
            max_length = length;
        }
    }
    
    os_hw_interrupt_enable(level);

    if ((max_length > OS_NAME_MAX) || (0 == max_length))
    {
        max_length = OS_NAME_MAX;
    }

    return max_length;
}

/**
 ***********************************************************************************************************************
 * @brief           This function prints the specified number of '-'
 *
 * @param[in]       len       number of '-'.
 *
 * @return          None.
 ***********************************************************************************************************************
 */
void os_object_split(os_int32_t len)
{
    while (len--)
    {
        os_kprintf("-");
    }
}
#endif

