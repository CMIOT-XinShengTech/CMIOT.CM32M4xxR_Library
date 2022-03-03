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
 * @file        os_module.c
 *
 * @brief       This file implements the kernel module functions.
 *
 * @revision
 * Date         Author          Notes
 * 2020-06-20   OneOS Team      First Version
 ***********************************************************************************************************************
 */

#include <oneos_config.h>
#include <os_errno.h>
#include <os_module.h>

#include <os_sem.h>
#include <os_mutex.h>
#include <os_event.h>
#include <os_mailbox.h>
#include <os_mq.h>

#include "os_kernel_internal.h"
#include "os_util_internal.h"

#define MODULE_TAG       "MODULE"

/**
 ***********************************************************************************************************************
 * @brief           This function will create a kernel module object from heap and put it on list. 
 *
 * @details         Create a kernel module object from heap and put it on kernel object list.
 *                  If create a kernel module object in module , The module object is placed on module list for 
 *                  garbage collected.
 *
 * @param           None
 *
 * @return          The pointer to the created module.
 * @retval          pointer         If operation successful.
 * @retval          OS_NULL         Error occurred.
 ***********************************************************************************************************************
 */
struct os_module *os_module_create(void)
{
    struct os_module *module = OS_NULL;

    module = (struct os_module *)OS_KERNEL_MALLOC(sizeof(struct os_module));
    if (module == OS_NULL)
    {
        OS_KERN_LOG(KERN_ERROR, MODULE_TAG, "Malloc module memory failed");
        return OS_NULL;
    }
    os_memset(module, 0x0, sizeof(struct os_module));
    
    /* init module object */
    os_object_init((os_object_t *)module, OS_OBJECT_MODULE, "module", OS_FALSE);

    module->stat = OS_MODULE_STAT_INIT;
    /* set initial priority and stack size */
    module->priority = OS_TASK_PRIORITY_MAX - 1;
    module->stack_size = 2048;

    os_list_init(&(module->object_list));

    return module;
}


static void os_module_destroy_child_task(struct os_module *module, os_task_t *task)
{
    OS_ASSERT(task->module_id == module);

    /* lock scheduler to prevent scheduling in cleanup function. */
    os_enter_critical();

    /* remove task from task_list (ready or defunct task list) */
    os_list_del(&(task->task_list));

    if ((task->stat & OS_TASK_STAT_MASK) != OS_TASK_CLOSE 
        && (task->task_timer.parent.type == OS_OBJECT_TIMER)
        && task->task_timer.parent.is_static)
    {
        /* release task timer */
        os_timer_deinit(&(task->task_timer));
    }

    /* change stat */
    task->stat = OS_TASK_CLOSE;

    /* invoke task cleanup */
    if (task->cleanup != OS_NULL)
    {
        task->cleanup(task);
    }
    
    os_exit_critical();
    
    os_object_deinit((os_object_t *)task);
    
#ifdef RT_USING_HEAP
    if(task->parent.is_static)
    {
        /* release task's stack */
        OS_KERNEL_FREE(task->stack_addr);
        /* release task object */
        OS_KERNEL_FREE(task);
    }
#endif
}

/**
 ***********************************************************************************************************************
 * @brief           This function will destroy the specified module by module descriptor.
 *
 * @details         It will destroy specified module,reclaim all kernel resources within the module. If the module is 
                    executed as a program(*.mo), garbage collection is uniformly placed idle task(defunct task).           
 *                  
 * @attention       It corresponds to os_module_create.
 *
 * @param[in]       module      The descriptor of kernel module
 *
 * @return          On success, return OS_EOK; on error, return a error code.
 * @retval          OS_EOK          Successfully destroy a module.
 * @retval          OS_EBUSY        Kernle module is running and cannot be destroy.
 * @retval          OS_ERROR        Function param is OS_NULL.
 ***********************************************************************************************************************
 */ 
os_err_t os_module_destroy(struct os_module *module)
{
    int i;

    OS_DEBUG_NOT_IN_INTERRUPT;

    /* check parameter */
    if (module == OS_NULL)
    {
        return OS_ERROR;
    }

    /* can not destroy a running module */
    if (module->stat == OS_MODULE_STAT_RUNNING)
    {
        return OS_EBUSY;
    }

    /* do module cleanup */
    if (module->cleanup_func)
    {
        os_enter_critical();
        module->cleanup_func(module);
        os_exit_critical();
    }

    /* cleanup for all kernel objects inside module*/
    {
        struct os_object *object = OS_NULL;
        struct os_list_node *node = OS_NULL;

        /* detach/delete all tasks in this module */
        for (node = module->object_list.next; node != &(module->object_list); )
        {
            int object_type;

            object = os_list_entry(node, struct os_object, list);
            object_type = object->type;

            /* to next node */
            node = node->next;

            if (object->is_static)
            {
                switch (object_type)
                {
                case OS_OBJECT_TASK:
                    os_module_destroy_child_task(module, (os_task_t *)object);
                    break;
#ifdef OS_USING_SEMAPHORE
                case OS_OBJECT_SEMAPHORE:
                    os_sem_deinit((os_sem_t *)object);
                    break;
#endif
#ifdef OS_USING_MUTEX
                case OS_OBJECT_MUTEX:
                    os_mutex_deinit((os_mutex_t *)object);
                    break;
#endif
#ifdef OS_USING_EVENT
                case OS_OBJECT_EVENT:
                    os_event_deinit((os_event_t *)object);
                    break;
#endif
#ifdef OS_USING_MAILBOX
                case OS_OBJECT_MAILBOX:
                    os_mb_deinit((os_mailbox_t *)object);
                    break;
#endif
#ifdef OS_USING_MESSAGEQUEUE
                case OS_OBJECT_MESSAGEQUEUE:
                    os_mq_deinit((os_mq_t *)object);
                    break;
#endif
#ifdef OS_USING_MEM_HEAP
                case OS_OBJECT_MEMHEAP:
                    os_memheap_deinit((struct os_memheap*)object);
                    break;
#endif
#ifdef OS_USING_MEM_POOL
                case OS_OBJECT_MEMPOOL:
                    os_mp_deinit((struct os_mempool*)object);
                    break;
#endif
                case OS_OBJECT_TIMER:
                    os_timer_deinit((os_timer_t *)object);
                    break;
                default:
                     OS_KERN_LOG(KERN_ERROR, MODULE_TAG,"Unsupported object type in module.");
                    break;
                }
            }
            else
            {
                switch (object_type)
                {
                case OS_OBJECT_TASK:
                    os_module_destroy_child_task(module, (os_task_t *)object);
                    break;
#ifdef OS_USING_SEMAPHORE
                case OS_OBJECT_SEMAPHORE:
                    os_sem_destroy((os_sem_t *)object);
                    break;
#endif
#ifdef OS_USING_MUTEX
                case OS_OBJECT_MUTEX:
                    os_mutex_destroy((os_mutex_t *)object);
                    break;
#endif
#ifdef OS_USING_EVENT
                case OS_OBJECT_EVENT:
                    os_event_destroy((os_event_t *)object);
                    break;
#endif
#ifdef OS_USING_MAILBOX
                case OS_OBJECT_MAILBOX:
                    os_mb_destroy((os_mailbox_t *)object);
                    break;
#endif
#ifdef OS_USING_MESSAGEQUEUE
                case OS_OBJECT_MESSAGEQUEUE:
                    os_mq_destroy((os_mq_t *)object);
                    break;
#endif
#ifdef OS_USING_MEM_HEAP
                /* no delete operation */
#endif
#ifdef OS_USING_MEM_POOL
                case OS_OBJECT_MEMPOOL:
                    os_mp_destroy((struct os_mempool*)object);
                    break;
#endif
                case OS_OBJECT_TIMER:
                    os_timer_destroy((os_timer_t *)object);
                    break;
                default:
                    OS_KERN_LOG(KERN_ERROR, MODULE_TAG,"Unsupported object type in module.");
                    break;
                }
            }
        }
    }

    /**/
    if (module->cmd_line)
    {
        os_free(module->cmd_line);
    }
    /* release module symbol table */
    for (i = 0; i < module->nsym; i ++)
    {
        os_free((void *)module->symtab[i].name);
    }
    if (module->symtab != OS_NULL)
    {
        os_free(module->symtab);
    }

    /* destory module */
    os_free(module->mem_space);
    /* delete module object */
    os_object_deinit((os_object_t *)module);
    os_free(module);
    
    return OS_EOK;
}

/**
 ***********************************************************************************************************************
 * @brief           This function return the currently running kernel module descriptor.
 *
 * @param           None
 *
 * @return          The currently running kernel module descriptor.
 * @retval          not OS_NULL     Return a kernel module  descriptor.
 * @retval          OS_NULL         Not running in the context of a kernel module
 ***********************************************************************************************************************
 */
struct os_module *os_module_self(void)
{
    os_task_t *tid;
    struct os_module *ret = OS_NULL;

    tid = os_task_self();
    if (tid)
    {
        ret = (struct os_module*)tid->module_id;
    }

    return ret;
}
/**
 ***********************************************************************************************************************
 * @brief           This function will stop all child task within a module
 *
 * @details         Stop all child task within a module for later garbage collection.
 *
 * @param           None
 *
 * @return          None
 ***********************************************************************************************************************
 */
void os_module_stop_child_task(void)
{
    struct os_module *module;

    module = os_module_self();
    if (!module)
    {
        /* not a module task */
        return; 
    }

    os_enter_critical();
    if (module->stat == OS_MODULE_STAT_RUNNING)
    {
        struct os_object    *object = OS_NULL;
        struct os_list_node *node = OS_NULL;

        /* set stat to closing */
        module->stat = OS_MODULE_STAT_CLOSING;

        /* suspend all tasks in this module */
        for (node = module->object_list.next; node != &(module->object_list); node = node->next)
        {
            object = os_list_entry(node, struct os_object, list);

            if (object->type == OS_OBJECT_TASK)
            {
                os_task_t *task = (os_task_t *)object;

                /* stop timer and suspend task*/
                if ((task->stat & OS_TASK_STAT_MASK) != OS_TASK_CLOSE
                    ||(task->stat & OS_TASK_STAT_MASK) != OS_TASK_INIT)
                {
                    os_timer_stop(&(task->task_timer));
                    os_task_suspend(task);
                }
            }
        }
    }
    os_exit_critical();

    return;
 }

/**
 ***********************************************************************************************************************
 * @brief           This function exit a kernel module
 *
 * @attention       This function stop all child task and destroy main task.Garbage collection is uniformly placed 
                    idle task(defunct task)
 *
 * @param[in]       ret_code       exit code
 *
 * @return          None
 ***********************************************************************************************************************
 */
void os_module_exit(int ret_code)
 {
    os_task_t *task;
    struct os_module *module;

    module = os_module_self();
    if (module == OS_NULL)
    {
        return;
    }
    /* disable scheduling */
    os_enter_critical();

    /* module is not running */
    if (module->stat != OS_MODULE_STAT_RUNNING) 
    {
        /* restore scheduling */
        os_exit_critical();

        return;
    }

    /* set return code */
    module->ret_code = ret_code; 

    os_module_stop_child_task();

    task = module->main_task;
    if ((task->stat & OS_TASK_STAT_MASK) == OS_TASK_CLOSE)
    {
        /* main task already closed */
        os_exit_critical();

        return ;
    }

    /* delete task: insert to defunct task list */
    os_task_destroy(task);
    /* enable scheduling */
    os_exit_critical();
 }

/**
 ***********************************************************************************************************************
 * @brief           This function set kernel module name
 *
 * @param[in]       module       The descriptor of kernel module 
 * @param[in]       path         Pointer to module name string   
 *
 * @return          None
 ***********************************************************************************************************************
 */
void os_module_set_name(struct os_module *module, const char *path)
{
    int size;
    struct os_object *object;
    const char *first, *end, *ptr;

    object = &(module->parent);
    ptr   = first = (char *)path;
    end   = path + os_strlen(path);

    while (*ptr != '\0')
    {
        if (*ptr == '/')
        {
            first = ptr + 1;
        }
        
        if (*ptr == '.')
        {
            end = ptr - 1;
        }
        
        ptr++;
    }

    size = end - first + 1;
    if (size > OS_NAME_MAX)
    {
        size = OS_NAME_MAX;
    }

    os_strncpy(object->name, first, size);
    object->name[size] = '\0';
}

static struct os_module_symtab *gs_os_module_symtab_begin = OS_NULL;
static struct os_module_symtab *gs_os_module_symtab_end   = OS_NULL;

int os_module_init(void)
{
#if defined(__GNUC__) && !defined(__CC_ARM)
    extern int __osmsymtab_start;
    extern int __osmsymtab_end;

    gs_os_module_symtab_begin = (struct os_module_symtab *)&__osmsymtab_start;
    gs_os_module_symtab_end   = (struct os_module_symtab *)&__osmsymtab_end;
#elif defined (__CC_ARM)
    extern int MSymTab$$Base;
    extern int MSymTab$$Limit;
    gs_os_module_symtab_begin = (struct os_module_symtab *)&MSymTab$$Base;
    gs_os_module_symtab_end   = (struct os_module_symtab *)&MSymTab$$Limit;
#endif

    return 0;
}
OS_CMPOENT_INIT(os_module_init);

/**
 ***********************************************************************************************************************
 * @brief           This function will return the address of specified symbol  
 *
 * @details         Symbols need to be exported through the EXPORT_SYMBOL before they can be found.
 *
 * @param[in]       sym_str         Symbol name to look for.   
 *
 * @return          On success, return a symbol addr; on fail, OS_NULL is returned.
 * @retval          not 0     The address of symbol to look for.
 * @retval          0         Not symbol was found
 ***********************************************************************************************************************
 */
os_uint32_t os_module_symbol_find(const char *sym_str)
{
    /* find in kernel symbol table */
    struct os_module_symtab *index;

    for (index = gs_os_module_symtab_begin; index != gs_os_module_symtab_end; index ++)
    {
        if (os_strcmp(index->name, sym_str) == 0)
        {
            return (os_uint32_t)index->addr;
        }

    }
    
    return 0;
} 

/**
 ***********************************************************************************************************************
 * @brief           This function will find kernel module by name 
 * 
 * @param[in]       name       Module name to look for
 *
 * @return          On success, return a kernel module descriptor; on error, OS_NULL is returned.
 * @retval          not OS_NULL     Return a module descriptor.
 * @retval          OS_NULL         Call os_object_find failed
 ***********************************************************************************************************************
 */
 struct os_module *os_module_find(const char *name)
{
    struct os_object *object;
    struct os_module *ret = OS_NULL;

    object = os_object_find(name, OS_OBJECT_MODULE);
    if (object)
    {
        ret = (struct os_module*) object;
    }

    return ret;
}
EXPORT_SYMBOL(os_module_find);

#ifdef OS_USING_SHELL

#include <shell.h>
static int sh_list_symbols(os_int32_t argc, char **argv)
{
    /* find in kernel symbol table */
    struct os_module_symtab *index;

    os_kprintf("begin: 0x%x end:0x%x\n",gs_os_module_symtab_begin,gs_os_module_symtab_end);
    for (index = gs_os_module_symtab_begin;
         index != gs_os_module_symtab_end;
         index ++)
    {
        os_kprintf("%s => 0x%08x\n", index->name, index->addr);
    }

    return 0;
}
SH_CMD_EXPORT(list_symbols, sh_list_symbols, "list module export sym");

static int sh_list_module(os_int32_t argc, char **argv)
{
    struct os_module *module;
    struct os_list_node *list, *node;
    struct os_object_info *info;

    info = os_object_get_info(OS_OBJECT_MODULE);
    list = &info->object_list;

    os_kprintf("module   ref      address \n");
    os_kprintf("-------- -------- ------------\n");
    for (node = list->next; node != list; node = node->next)
    {
        module = (struct os_module *)(os_list_entry(node, struct os_object, list));
        os_kprintf("%-*.*s %-04d  0x%08x\n",
                   OS_NAME_MAX, OS_NAME_MAX, module->parent.name, module->nref, module->mem_space);
    }

    return 0;
}
SH_CMD_EXPORT(list_module, sh_list_module, "list module");

#endif
