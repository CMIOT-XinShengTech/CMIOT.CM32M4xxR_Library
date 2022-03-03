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
 * @file        os_mem_pool.c
 *
 * @brief       This file implements the memory pool functions.
 *
 * @revision
 * Date         Author          Notes
 * 2020-03-09   OneOS team      First Version
 ***********************************************************************************************************************
 */

#include <os_types.h>
#include <os_task.h>
#include <os_stddef.h>
#include <os_errno.h>
#include <os_hw.h>
#include <os_dbg.h>
#include <os_clock.h>
#include <os_irq.h>
#include <os_module.h>

#include <os_memory.h>

#include "os_kernel_internal.h"

#ifdef OS_USING_MEM_POOL

#define OS_MEMPOOL_MAGIC        0x10011ea0
#define OS_MEMPOOL_MASK         0xfffffffe
#define OS_MEMPOOL_USED         0x01
#define OS_MEMPOOL_FREED        0x00

#ifdef OS_USING_HOOK

static void (*gs_os_mp_alloc_hook)(os_mp_t *mp, void *block) = OS_NULL;
static void (*gs_os_mp_free_hook)(os_mp_t *mp, void *block)  = OS_NULL;

/**
 ***********************************************************************************************************************
 * @brief           This function sets a hook called at the end of os_mp_alloc()
 *
 * @param[in]       hook             The hook function is complemented by user.
 *
 * @return          None.
 ***********************************************************************************************************************
 */
void os_mp_alloc_set_hook(void (*hook)(os_mp_t *mp, void *block))
{
    gs_os_mp_alloc_hook = hook;
}
EXPORT_SYMBOL(os_mp_alloc_set_hook);

/**
 ***********************************************************************************************************************
 * @brief           This function sets a hook called at the end of os_mp_free().
 *
 * @param[in]       hook             The hook function is complemented by user.
 *
 * @return          None.
 ***********************************************************************************************************************
 */
void os_mp_free_set_hook(void (*hook)(os_mp_t *mp, void *block))
{
    gs_os_mp_free_hook = hook;
}
EXPORT_SYMBOL(os_mp_free_set_hook);

#endif

/**
 ***********************************************************************************************************************
 * @brief           This function will initlialize a memory pool object and put it on object list.
 *
 * @param[in]       mp              The pointer to a memory pool object.
 * @param[in]       name            The name of memory pool.
 * @param[in]       start           The start address of memory pool.
 * @param[in]       size            The total size of memory pool.
 * @param[in]       block_size      The size for each block.
 *
 * @return          The operation result.
 * @retval          OS_EOK          If the operation successful.
 * @retval          else            Error code.
 ***********************************************************************************************************************
 */
os_err_t os_mp_init(os_mp_t    *mp,
                    const char *name,
                    void       *start,
                    os_size_t  size,
                    os_size_t  block_size)
{
    os_uint8_t *block_ptr;
    register os_size_t offset;

    OS_ASSERT(OS_NULL != mp);
    OS_ASSERT(OS_NULL != start);

    /* Initialize object. */
    os_object_init(&(mp->parent), OS_OBJECT_MEMPOOL, name, OS_TRUE);

    /* Initialize memory pool */
    mp->start_address = start;
    mp->size = OS_ALIGN_DOWN(size, OS_ALIGN_SIZE);

    /* Align the block size. */
    block_size = OS_ALIGN_UP(block_size, OS_ALIGN_SIZE);
    mp->block_size = block_size;

    /* Align to align size byte. */
    mp->block_total_count = mp->size / (mp->block_size + OS_MEMPOOL_HEAD_SIZE);
    mp->block_free_count  = mp->block_total_count;

    OS_ASSERT(0 != mp->block_total_count);

    /* Initialize suspended task list. */
    os_list_init(&(mp->suspend_task));

    /* Initialize free block list. */
    block_ptr = (os_uint8_t *)mp->start_address;
    for (offset = 0; offset < mp->block_total_count; offset ++)
    {
        *(os_uint8_t **)(block_ptr + offset * (block_size + OS_MEMPOOL_HEAD_SIZE)) =
            (os_uint8_t *)(block_ptr + (offset + 1) * (block_size + OS_MEMPOOL_HEAD_SIZE));
    }

    *(os_uint8_t **)(block_ptr + (offset - 1) * (block_size + OS_MEMPOOL_HEAD_SIZE)) = OS_NULL;

    mp->block_list = block_ptr;

    return OS_EOK;
}
EXPORT_SYMBOL(os_mp_init);

/**
 ***********************************************************************************************************************
 * @brief           This function will deinitlialize a memory pool object and delete it from object list.
 *
 * @param[in]       mp              The pointer to a memory pool object.
 *
 * @return          The operation result.
 * @retval          OS_EOK          If the operation successful.
 * @retval          else            Error code.
 ***********************************************************************************************************************
 */
os_err_t os_mp_deinit(os_mp_t *mp)
{
    struct os_task *task;
    register os_ubase_t temp;

    OS_ASSERT(mp != OS_NULL);
    OS_ASSERT(OS_OBJECT_MEMPOOL == os_object_get_type(&mp->parent));
    OS_ASSERT(OS_TRUE == os_object_is_static(&mp->parent));

    /* Wake up all suspended tasks. */
    while (!os_list_empty(&(mp->suspend_task)))
    {
        temp = os_hw_interrupt_disable();

        /* Get next suspend task. */
        task = os_list_entry(mp->suspend_task.next, os_task_t, task_list);
        /* Set error code to OS_ERROR */
        task->error = OS_ERROR;

        os_task_resume(task);

        os_hw_interrupt_enable(temp);
    }

    os_object_deinit(&(mp->parent));

    return OS_EOK;
}
EXPORT_SYMBOL(os_mp_deinit);

#ifdef OS_USING_HEAP

/**
 ***********************************************************************************************************************
 * @brief           This function will create a memory pool object from heap and put it on object list.
 *
 * @param[in]       name            The name of memory pool.
 * @param[in]       block_count     The count of blocks in memory poolx.
 * @param[in]       block_size      The size for each block.
 *
 * @return          The pointer to the created memory pool object.
 * @retval          pointer         If operation successful.
 * @retval          OS_NULL         Error occurred.
 ***********************************************************************************************************************
 */
os_mp_t *os_mp_create(const char *name,
                      os_size_t  block_count,
                      os_size_t  block_size)
{
    os_uint8_t *block_ptr;
    os_mp_t *mp;
    register os_size_t offset;
    
    OS_ASSERT(0 != block_count);

    OS_DEBUG_NOT_IN_INTERRUPT;

    mp = (os_mp_t *)OS_KERNEL_MALLOC(sizeof(os_mp_t));
    if (mp == OS_NULL)
    {
        return OS_NULL;
    }

    os_object_init(&(mp->parent), OS_OBJECT_MEMPOOL, name, OS_FALSE);

    /* Initialize memory pool */
    block_size     = OS_ALIGN_UP(block_size, OS_ALIGN_SIZE);
    mp->block_size = block_size;
    mp->size       = (block_size + sizeof(os_uint8_t *)) * block_count;

    /* Allocate memory */
    mp->start_address = OS_KERNEL_MALLOC((block_size + OS_MEMPOOL_HEAD_SIZE) * block_count);
    if (OS_NULL == mp->start_address)
    {
        os_object_deinit(&(mp->parent));

        return OS_NULL;
    }

    mp->block_total_count = block_count;
    mp->block_free_count  = mp->block_total_count;

    /* Initialize suspended task list */
    os_list_init(&(mp->suspend_task));

    /* Initialize free block list */
    block_ptr = (os_uint8_t *)mp->start_address;
    for (offset = 0; offset < mp->block_total_count; offset ++)
    {
        *(os_uint8_t **)(block_ptr + offset * (block_size + OS_MEMPOOL_HEAD_SIZE))
            = block_ptr + (offset + 1) * (block_size + OS_MEMPOOL_HEAD_SIZE);
    }

    *(os_uint8_t **)(block_ptr + (offset - 1) * (block_size + OS_MEMPOOL_HEAD_SIZE)) = OS_NULL;

    mp->block_list = block_ptr;

    return mp;
}
EXPORT_SYMBOL(os_mp_create);

/**
 ***********************************************************************************************************************
 * @brief           Destory an memory pool object created from heap.
 *
 * @param[in]       mp              The memory pool to destroy.
 *
 * @return          The operation result.
 * @retval          OS_EOK          If the operation successful.
 * @retval          else            Error code.
 ***********************************************************************************************************************
 */
os_err_t os_mp_destroy(os_mp_t *mp)
{
    struct os_task *task;
    register os_ubase_t temp;

    OS_DEBUG_NOT_IN_INTERRUPT;

    OS_ASSERT(OS_NULL != mp);
    OS_ASSERT(OS_OBJECT_MEMPOOL == os_object_get_type(&mp->parent));
    OS_ASSERT(OS_FALSE == os_object_is_static(&mp->parent));


    /* Wake up all suspended tasks */
    while (!os_list_empty(&(mp->suspend_task)))
    {
        temp = os_hw_interrupt_disable();

        /* Get next suspend task */
        task = os_list_entry(mp->suspend_task.next, os_task_t, task_list);
        /* Set error code to OS_ERROR */
        task->error = OS_ERROR;

        os_task_resume(task);

        os_hw_interrupt_enable(temp);
    }

    os_object_deinit(&mp->parent);

    /* Free memory pool */
    OS_KERNEL_FREE(mp->start_address);
    OS_KERNEL_FREE(mp);

    return OS_EOK;
}
EXPORT_SYMBOL(os_mp_destroy);
#endif

/**
 ***********************************************************************************************************************
 * @brief           This function allocates a free block from memory pool. If all blocks have been allocated, the calling
 *                  task blocks until either other tasks free a block or the waiting time expires.
 *
 * @param[in]       mp              The pointer to memory pool object.
 * @param[in]       timeout         Waiting time (in clock ticks).
 *
 * @return          The pointer to allocated memory or OS_NULL if no free memory was found.
 ***********************************************************************************************************************
 */
void *os_mp_alloc(os_mp_t *mp, os_tick_t timeout)
{
    os_uint8_t *block_ptr;
    register os_base_t level;
    os_task_t *task;
    os_uint32_t before_sleep = 0;

    OS_ASSERT(OS_NULL != mp);
    OS_ASSERT(OS_OBJECT_MEMPOOL == os_object_get_type(&mp->parent));
    OS_ASSERT((timeout < (OS_TICK_MAX / 2)) || (OS_MEM_WAITING_FOREVER == timeout));

    task = os_task_self();

    level = os_hw_interrupt_disable();

    while (mp->block_free_count == 0)
    {
        /* Memory block is unavailable and no waiting. */
        if (timeout == OS_MEM_WAITING_NO)
        {
            /* enable interrupt */
            os_hw_interrupt_enable(level);

            os_set_errno(OS_ETIMEOUT);

            return OS_NULL;
        }

        OS_DEBUG_NOT_IN_INTERRUPT;

        task->error = OS_EOK;

        /* Suspend calling task */
        os_task_suspend(task);
        os_list_add_tail(&(mp->suspend_task), &(task->task_list));

        if (timeout != OS_MEM_WAITING_FOREVER)
        {
            /* Init task timer and start it */
            before_sleep = os_tick_get();

            os_timer_control(&(task->task_timer),
                             OS_TIMER_CTRL_SET_TIME,
                             &timeout);
            os_timer_start(&(task->task_timer));
        }

        os_hw_interrupt_enable(level);

        os_schedule();

        if (task->error != OS_EOK)
        {
            return OS_NULL;
        }

        if (timeout > before_sleep)
        {
            timeout -= os_tick_get() - before_sleep;
        }
        else
        {
            timeout = OS_MEM_WAITING_NO;
        }

        level = os_hw_interrupt_disable();
    }

    /* Memory block is available, decrease the free block counter */
    mp->block_free_count--;

    /* Get block from block list */
    block_ptr = mp->block_list;
    OS_ASSERT(block_ptr != OS_NULL);

    /* Mark the allocated block as not available. */
    *(os_uint32_t *)(block_ptr + sizeof(os_uint8_t *)) = OS_MEMPOOL_MAGIC | OS_MEMPOOL_USED;

    /* Setup the next free node. */
    mp->block_list = *(os_uint8_t **)block_ptr;

    /* Set control pointer to memory pool */
    *(os_uint8_t **)block_ptr = (os_uint8_t *)mp;

    os_hw_interrupt_enable(level);

    OS_OBJECT_HOOK_CALL(gs_os_mp_alloc_hook,
                        (mp, (os_uint8_t *)(block_ptr + OS_MEMPOOL_HEAD_SIZE)));

    return (os_uint8_t *)(block_ptr + OS_MEMPOOL_HEAD_SIZE);
}
EXPORT_SYMBOL(os_mp_alloc);

/**
 ***********************************************************************************************************************
 * @brief           This function frees a memory block allocated by os_mp_alloc(). If there are tasks blocked on memory pool,
 *                  one task of them will be woken up.
 *
 * @param[in]       block          The pointer to memory block.
 *
 * @return          None
 ***********************************************************************************************************************
 */
void os_mp_free(void *block)
{
    os_uint8_t **block_ptr;
    os_mp_t *mp;
    os_task_t *task;
    register os_base_t level;

    if (OS_NULL == block)
    {
        return;
    }

    /* Check magic */
    OS_ASSERT((*(os_uint32_t *)((os_uint8_t *)block - sizeof(os_uint32_t)) & OS_MEMPOOL_MASK) == OS_MEMPOOL_MAGIC);
    OS_ASSERT((*(os_uint32_t *)((os_uint8_t *)block - sizeof(os_uint32_t)) & OS_MEMPOOL_USED) == OS_MEMPOOL_USED);

    /* Mark the block as available */
    *(os_uint32_t *)((os_uint8_t *)block - sizeof(os_uint32_t)) &= OS_MEMPOOL_FREED;

    /* Get the control block of pool which the block belongs to */
    block_ptr = (os_uint8_t **)((os_uint8_t *)block - OS_MEMPOOL_HEAD_SIZE);
    mp        = (os_mp_t *)*block_ptr;

    OS_OBJECT_HOOK_CALL(gs_os_mp_free_hook, (mp, block));

    level = os_hw_interrupt_disable();

    /* Increase the free block count */
    mp->block_free_count ++;

    /* Link the block into the block list */
    *block_ptr = mp->block_list;
    mp->block_list = (os_uint8_t *)block_ptr;

    /* Resume suspend task */
    if (!os_list_empty(&(mp->suspend_task)))
    {
        task = os_list_entry(mp->suspend_task.next,
                               os_task_t,
                               task_list);

        task->error = OS_EOK;

        os_task_resume(task);

        os_hw_interrupt_enable(level);

        os_schedule();

        return;
    }

    os_hw_interrupt_enable(level);
}
EXPORT_SYMBOL(os_mp_free);

#ifdef OS_USING_SHELL

#include <shell.h>
#include <os_ipc.h>

static os_err_t _list_mempool(struct os_list_node *list)
{
    int maxlen;
    struct os_mempool *mp;
    struct os_list_node *node;
    const char *item_title = "mempool";

    maxlen = os_object_name_maxlen(item_title, list);

    os_kprintf("%-*.s block total free\r\n", maxlen, item_title); 
    os_object_split(maxlen);
    os_kprintf(     " ----  ----  ----\r\n");
    for (node = list->next; node != list; node = node->next)
    {
        mp = (struct os_mempool *)os_list_entry(node, struct os_object, list);
        if (!os_list_empty(&(mp->suspend_task)))
        {
            os_kprintf("%-*.*s %04d  %04d  %04d:",
                       maxlen, OS_NAME_MAX,
                       mp->parent.name,
                       mp->block_size,
                       mp->block_total_count,
                       mp->block_free_count);
            os_ipc_show_waiting_task(&(mp->suspend_task));
            os_kprintf("\r\n");
        }
        else
        {
            os_kprintf("%-*.*s %04d  %04d  %04d\r\n",
                       maxlen, OS_NAME_MAX,
                       mp->parent.name,
                       mp->block_size,
                       mp->block_total_count,
                       mp->block_free_count);
        }
    }

    return OS_EOK;
}

static os_err_t sh_list_mempool(os_int32_t argc, char **argv)
{
    struct os_object_info *info;

    info = os_object_get_info(OS_OBJECT_MEMPOOL);
    return _list_mempool(&info->object_list);
}
SH_CMD_EXPORT(memp, sh_list_mempool, "show memory pool information");
#endif /* end of OS_USING_SHELL */

#endif /* end of OS_USING_MEM_POOL */
