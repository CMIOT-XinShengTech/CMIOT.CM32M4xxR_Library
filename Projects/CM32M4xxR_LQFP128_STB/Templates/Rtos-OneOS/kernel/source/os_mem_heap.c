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
 * @file        os_mem_heap.c
 *
 * @brief       This file implements the memory heap functions.
 *
 * @revision
 * Date         Author          Notes
 * 2020-03-09   OneOS team      First Version
 ***********************************************************************************************************************
 */

#include <os_dbg.h>
#include <os_module.h>
#include <os_memory.h>
#include <os_errno.h>

#include "os_kernel_internal.h"
#include "os_util_internal.h"

#ifdef OS_USING_MEM_HEAP

#define HEAP_TAG                "MHEAP"

#define OS_MEMHEAP_MAGIC        0x1ea01ea0
#define OS_MEMHEAP_MASK         0xfffffffe
#define OS_MEMHEAP_USED         0x01
#define OS_MEMHEAP_FREED        0x00

#define OS_MEMHEAP_IS_USED(i)   ((i)->magic & OS_MEMHEAP_USED)
#define OS_MEMHEAP_MINIALLOC    12

#define OS_MEMHEAP_SIZE         OS_ALIGN_UP(sizeof(struct os_memheap_item), OS_ALIGN_SIZE)
#define MEMITEM_SIZE(item)      ((os_uint32_t)item->next - (os_uint32_t)item - OS_MEMHEAP_SIZE)

/**
 ***********************************************************************************************************************
 * @brief           This function initlializes a memory heap object and put it on object list.
 *
 * @param[in]       memheap         The pointer to a memory heap object.
 * @param[in]       name            The name of memory heap.
 * @param[in]       start           The start address of memory pool.
 * @param[in]       size            The total size of memory pool.
 *
 * @return          The operation result.
 * @retval          OS_EOK          If the operation successful.
 * @retval          else            Error code.
 ***********************************************************************************************************************
 */
os_err_t os_memheap_init(struct os_memheap *memheap,
                         const char        *name,
                         void              *start_addr,
                         os_size_t         size)
{
    struct os_memheap_item *item;

    OS_ASSERT(memheap != OS_NULL);

    /* Initialize pool object */
    os_object_init(&(memheap->parent), OS_OBJECT_MEMHEAP, name, OS_TRUE);

    memheap->start_addr     = (void *)(OS_ALIGN_UP((os_uint32_t)start_addr, OS_ALIGN_SIZE));
    memheap->pool_size      = OS_ALIGN_DOWN((os_uint32_t)start_addr + (os_uint32_t)size, OS_ALIGN_SIZE)
                              - (os_uint32_t)memheap->start_addr;
    memheap->available_size = memheap->pool_size - (2 * OS_MEMHEAP_SIZE);
    memheap->max_used_size  = memheap->pool_size - memheap->available_size;

    /* Initialize the free list header */
    item            = &(memheap->free_header);
    item->magic     = OS_MEMHEAP_MAGIC;
    item->pool_ptr  = memheap;
    item->next      = OS_NULL;
    item->prev      = OS_NULL;
    item->next_free = item;
    item->prev_free = item;

    /* Set the free list to free list header */
    memheap->free_list = item;

    /* Initialize the first big memory block */
    item            = (struct os_memheap_item *)memheap->start_addr;
    item->magic     = OS_MEMHEAP_MAGIC;
    item->pool_ptr  = memheap;
    item->next      = OS_NULL;
    item->prev      = OS_NULL;
    item->next_free = item;
    item->prev_free = item;

    item->next = (struct os_memheap_item *)
                 ((os_uint8_t *)item + memheap->available_size + OS_MEMHEAP_SIZE);
    item->prev = item->next;

    /* Block list header */
    memheap->block_list = item;

    /* Place the big memory block to free list */
    item->next_free = memheap->free_list->next_free;
    item->prev_free = memheap->free_list;
    memheap->free_list->next_free->prev_free = item;
    memheap->free_list->next_free            = item;

    /* Move to the end of memory pool to build a small tailer block,
     * which prevents block merging
     */
    item = item->next;
    /* It's a used memory block */
    item->magic     = OS_MEMHEAP_MAGIC | OS_MEMHEAP_USED;
    item->pool_ptr  = memheap;
    item->next      = (struct os_memheap_item *)memheap->start_addr;
    item->prev      = (struct os_memheap_item *)memheap->start_addr;
    /* Not in free list */
    item->next_free = item->prev_free = OS_NULL;

    /* Initialize semaphore lock */
    os_sem_init(&memheap->lock, name, 1, OS_IPC_FLAG_FIFO);

    OS_KERN_LOG(KERN_DEBUG, HEAP_TAG, "memory heap: start addr 0x%08x, size %d, free list header 0x%08x",
                memheap->start_addr, memheap->pool_size, &(memheap->free_header));

    return OS_EOK;
}
EXPORT_SYMBOL(os_memheap_init);

/**
 ***********************************************************************************************************************
 * @brief           This function deinitlializes a memory heap object.
 *
 * @param[in]       heap            The pointer to a memory heap object.
 *
 * @return          The operation result.
 * @retval          OS_EOK          If the operation successful.
 * @retval          else            Error code.
 ***********************************************************************************************************************
 */
os_err_t os_memheap_deinit(struct os_memheap *heap)
{
    OS_ASSERT(heap);
    OS_ASSERT(os_object_get_type(&heap->parent) == OS_OBJECT_MEMHEAP);

    os_sem_deinit(&heap->lock);
    os_object_deinit(&heap->parent);

    return OS_EOK;
}
EXPORT_SYMBOL(os_memheap_deinit);

/**
 ***********************************************************************************************************************
 * @brief           This function allocates 'size' bytes memory space from heap.
 *
 * @param[in]       heap            The pointer to memory heap object.
 * @param[in]       size            The size of the requested space in bytes.
 *
 * @return          The pointer to allocated memory or NULL if no free memory was found.
 ***********************************************************************************************************************
 */
void *os_memheap_alloc(struct os_memheap *heap, os_size_t size)
{
    os_err_t result;
    os_uint32_t free_size;
    struct os_memheap_item *header_ptr;

    OS_ASSERT(heap != OS_NULL);
    OS_ASSERT(os_object_get_type(&heap->parent) == OS_OBJECT_MEMHEAP);

    if (size > heap->available_size)
    {
        return OS_NULL;
    }

    /* Align allocated size */
    size = OS_ALIGN_UP(size, OS_ALIGN_SIZE);
    if (size < OS_MEMHEAP_MINIALLOC)
        size = OS_MEMHEAP_MINIALLOC;

    OS_KERN_LOG(KERN_DEBUG, HEAP_TAG, "allocate %d on heap:%8.*s", size, OS_NAME_MAX, heap->parent.name);

    if (size < heap->available_size)
    {
        /* Search on free list */
        free_size = 0;

        /* Lock memheap */
        result = os_sem_wait(&(heap->lock), OS_IPC_WAITING_FOREVER);
        if (result != OS_EOK)
        {
            os_set_errno(result);

            return OS_NULL;
        }

        /* Get the first free memory block */
        header_ptr = heap->free_list->next_free;
        while (header_ptr != heap->free_list && free_size < size)
        {
            /* Get current freed memory block size */
            free_size = MEMITEM_SIZE(header_ptr);
            if (free_size < size)
            {
                /* Move to next free memory block */
                header_ptr = header_ptr->next_free;
            }
        }

        /* Determine if the memory is available. */
        if (free_size >= size)
        {
            /* A block that satisfies the request has been found. */

            /* Determine if the block needs to be split. */
            if (free_size >= (size + OS_MEMHEAP_SIZE + OS_MEMHEAP_MINIALLOC))
            {
                struct os_memheap_item *new_ptr;

                /* Split the block. */
                new_ptr = (struct os_memheap_item *)
                          (((os_uint8_t *)header_ptr) + size + OS_MEMHEAP_SIZE);

                OS_KERN_LOG(KERN_DEBUG, HEAP_TAG, "split: block[0x%08x] nextm[0x%08x] prevm[0x%08x] to new[0x%08x]",
                            header_ptr,
                            header_ptr->next,
                            header_ptr->prev,
                            new_ptr);

                /* Mark the new block as a memory block and freed. */
                new_ptr->magic = OS_MEMHEAP_MAGIC;

                /* Put the pool pointer into the new block. */
                new_ptr->pool_ptr = heap;

                /* Break down the block list */
                new_ptr->prev          = header_ptr;
                new_ptr->next          = header_ptr->next;
                header_ptr->next->prev = new_ptr;
                header_ptr->next       = new_ptr;

                /* Remove header ptr from free list */
                header_ptr->next_free->prev_free = header_ptr->prev_free;
                header_ptr->prev_free->next_free = header_ptr->next_free;
                header_ptr->next_free = OS_NULL;
                header_ptr->prev_free = OS_NULL;

                /* Insert new_ptr to free list */
                new_ptr->next_free = heap->free_list->next_free;
                new_ptr->prev_free = heap->free_list;
                heap->free_list->next_free->prev_free = new_ptr;
                heap->free_list->next_free            = new_ptr;
                OS_KERN_LOG(KERN_DEBUG, HEAP_TAG, "new ptr: next_free 0x%08x, prev_free 0x%08x",
                            new_ptr->next_free, new_ptr->prev_free);

                /* Decrement the available byte count.  */
                heap->available_size = heap->available_size -
                                       size -
                                       OS_MEMHEAP_SIZE;
                if (heap->pool_size - heap->available_size > heap->max_used_size)
                    heap->max_used_size = heap->pool_size - heap->available_size;
            }
            else
            {
                /* Decrement the entire free size from the available bytes count. */
                heap->available_size = heap->available_size - free_size;
                if (heap->pool_size - heap->available_size > heap->max_used_size)
                    heap->max_used_size = heap->pool_size - heap->available_size;

                /* Remove header_ptr from free list */
                OS_KERN_LOG(KERN_DEBUG, HEAP_TAG, "one block: block[0x%08x], next_free 0x%08x, prev_free 0x%08x",
                            header_ptr,
                            header_ptr->next_free,
                            header_ptr->prev_free);

                header_ptr->next_free->prev_free = header_ptr->prev_free;
                header_ptr->prev_free->next_free = header_ptr->next_free;
                header_ptr->next_free = OS_NULL;
                header_ptr->prev_free = OS_NULL;
            }

            /* Mark the allocated block as not available. */
            header_ptr->magic |= OS_MEMHEAP_USED;

            /* Release lock */
            os_sem_post(&(heap->lock));

            /* Return a memory address to the caller.  */
            OS_KERN_LOG(KERN_DEBUG, HEAP_TAG, "alloc mem: memory[0x%08x], heap[0x%08x], size: %d",
                        (void *)((os_uint8_t *)header_ptr + OS_MEMHEAP_SIZE),
                        header_ptr,
                        size);

            return (void *)((os_uint8_t *)header_ptr + OS_MEMHEAP_SIZE);
        }

        /* Release lock */
        os_sem_post(&(heap->lock));
    }

    OS_KERN_LOG(KERN_DEBUG, HEAP_TAG, "allocate memory: failed");

    /* Return the completion status.  */
    return OS_NULL;
}
EXPORT_SYMBOL(os_memheap_alloc);

/**
 ***********************************************************************************************************************
 * @brief           This function changes the size of the memory block pointed to by ptr to 'newsize' bytes.
 *
 * @param[in]       heap            The pointer to memory heap object.
 * @param[in]       ptr             The pointer to old memory block.
 * @param[in]       newsize         The size of the requested memory in bytes.
 *
 * @return          The pointer to allocated memory or NULL if no free memory was found.
 ***********************************************************************************************************************
 */
void *os_memheap_realloc(struct os_memheap *heap, void *ptr, os_size_t newsize)
{
    os_err_t result;
    os_size_t oldsize;
    struct os_memheap_item *header_ptr;
    struct os_memheap_item *new_ptr;

    OS_ASSERT(heap);
    OS_ASSERT(os_object_get_type(&heap->parent) == OS_OBJECT_MEMHEAP);

    if (newsize == 0)
    {
        os_memheap_free(ptr);

        return OS_NULL;
    }

    if (newsize > heap->available_size)
    {
        return OS_NULL;
    }

    /* Align allocated size */
    newsize = OS_ALIGN_UP(newsize, OS_ALIGN_SIZE);
    if (newsize < OS_MEMHEAP_MINIALLOC)
        newsize = OS_MEMHEAP_MINIALLOC;

    if (ptr == OS_NULL)
    {
        return os_memheap_alloc(heap, newsize);
    }

    /* Get memory block header and get the size of memory block */
    header_ptr = (struct os_memheap_item *)
                 ((os_uint8_t *)ptr - OS_MEMHEAP_SIZE);
    oldsize = MEMITEM_SIZE(header_ptr);
    /* Re-allocate memory */
    if (newsize > oldsize)
    {
        void *new_ptr;
        struct os_memheap_item *next_ptr;

        /* Lock memheap */
        result = os_sem_wait(&(heap->lock), OS_IPC_WAITING_FOREVER);
        if (result != OS_EOK)
        {
            os_set_errno(result);
            return OS_NULL;
        }

        next_ptr = header_ptr->next;

        /* header_ptr should not be the tail */
        OS_ASSERT(next_ptr > header_ptr);

        /* Check whether the following free space is enough to expand */
        if (!OS_MEMHEAP_IS_USED(next_ptr))
        {
            os_int32_t nextsize;

            nextsize = MEMITEM_SIZE(next_ptr);
            OS_ASSERT(next_ptr > 0);

            /* Here is the ASCII art of the situation that we can make use of
             * the next free node without alloc/memcpy, |*| is the control
             * block:
             *
             *      oldsize           free node
             * |*|-----------|*|----------------------|*|
             *         newsize          >= minialloc
             * |*|----------------|*|-----------------|*|
             */
            if (nextsize + oldsize > newsize + OS_MEMHEAP_MINIALLOC)
            {
                /* Decrement the entire free size from the available bytes count. */
                heap->available_size = heap->available_size - (newsize - oldsize);
                if (heap->pool_size - heap->available_size > heap->max_used_size)
                    heap->max_used_size = heap->pool_size - heap->available_size;

                /* Remove next_ptr from free list */
                OS_KERN_LOG(KERN_DEBUG, HEAP_TAG, "remove block: block[0x%08x], next_free 0x%08x, prev_free 0x%08x",
                            next_ptr,
                            next_ptr->next_free,
                            next_ptr->prev_free);

                next_ptr->next_free->prev_free = next_ptr->prev_free;
                next_ptr->prev_free->next_free = next_ptr->next_free;
                next_ptr->next->prev = next_ptr->prev;
                next_ptr->prev->next = next_ptr->next;

                /* Build a new one on the right place */
                next_ptr = (struct os_memheap_item *)((char *)ptr + newsize);

                OS_KERN_LOG(KERN_DEBUG, HEAP_TAG, "new free block: block[0x%08x] nextm[0x%08x] prevm[0x%08x]",
                            next_ptr,
                            next_ptr->next,
                            next_ptr->prev);

                /* Mark the new block as a memory block and freed. */
                next_ptr->magic = OS_MEMHEAP_MAGIC;

                /* Put the pool pointer into the new block. */
                next_ptr->pool_ptr = heap;

                next_ptr->prev          = header_ptr;
                next_ptr->next          = header_ptr->next;
                header_ptr->next->prev = next_ptr;
                header_ptr->next       = next_ptr;

                /* Insert next_ptr to free list */
                next_ptr->next_free = heap->free_list->next_free;
                next_ptr->prev_free = heap->free_list;
                heap->free_list->next_free->prev_free = next_ptr;
                heap->free_list->next_free            = next_ptr;
                OS_KERN_LOG(KERN_DEBUG, HEAP_TAG, "new ptr: next_free 0x%08x, prev_free 0x%08x",
                            next_ptr->next_free,
                            next_ptr->prev_free);

                /* Release lock */
                os_sem_post(&(heap->lock));

                return ptr;
            }
        }

        /* Release lock */
        os_sem_post(&(heap->lock));

        /* Re-allocate a memory block */
        new_ptr = (void *)os_memheap_alloc(heap, newsize);
        if (new_ptr != OS_NULL)
        {
            os_memcpy(new_ptr, ptr, oldsize < newsize ? oldsize : newsize);
            os_memheap_free(ptr);
        }

        return new_ptr;
    }

    /* Don't split when there is less than one node space left */
    if (newsize + OS_MEMHEAP_SIZE + OS_MEMHEAP_MINIALLOC >= oldsize)
        return ptr;

    /* Lock memheap */
    result = os_sem_wait(&(heap->lock), OS_IPC_WAITING_FOREVER);
    if (result != OS_EOK)
    {
        os_set_errno(result);

        return OS_NULL;
    }

    /* Split the block. */
    new_ptr = (struct os_memheap_item *)
              (((os_uint8_t *)header_ptr) + newsize + OS_MEMHEAP_SIZE);

    OS_KERN_LOG(KERN_DEBUG, HEAP_TAG, "split: block[0x%08x] nextm[0x%08x] prevm[0x%08x] to new[0x%08x]",
                header_ptr,
                header_ptr->next,
                header_ptr->prev,
                new_ptr);

    /* Mark the new block as a memory block and freed. */
    new_ptr->magic = OS_MEMHEAP_MAGIC;
    /* Put the pool pointer into the new block. */
    new_ptr->pool_ptr = heap;

    /* Break down the block list */
    new_ptr->prev          = header_ptr;
    new_ptr->next          = header_ptr->next;
    header_ptr->next->prev = new_ptr;
    header_ptr->next       = new_ptr;

    /* Determine if the block can be merged with the next neighbor. */
    if (!OS_MEMHEAP_IS_USED(new_ptr->next))
    {
        struct os_memheap_item *free_ptr;

        /* Merge block with next neighbor. */
        free_ptr = new_ptr->next;
        heap->available_size = heap->available_size - MEMITEM_SIZE(free_ptr);

        OS_KERN_LOG(KERN_DEBUG, HEAP_TAG, "merge: right node 0x%08x, next_free 0x%08x, prev_free 0x%08x",
                    header_ptr, header_ptr->next_free, header_ptr->prev_free);

        free_ptr->next->prev = new_ptr;
        new_ptr->next   = free_ptr->next;

        /* Remove free ptr from free list */
        free_ptr->next_free->prev_free = free_ptr->prev_free;
        free_ptr->prev_free->next_free = free_ptr->next_free;
    }

    /* Insert the split block to free list */
    new_ptr->next_free = heap->free_list->next_free;
    new_ptr->prev_free = heap->free_list;
    heap->free_list->next_free->prev_free = new_ptr;
    heap->free_list->next_free            = new_ptr;
    OS_KERN_LOG(KERN_DEBUG, HEAP_TAG, "new free ptr: next_free 0x%08x, prev_free 0x%08x",
                new_ptr->next_free,
                new_ptr->prev_free);

    /* Increment the available byte count.  */
    heap->available_size = heap->available_size + MEMITEM_SIZE(new_ptr);

    /* Release lock */
    os_sem_post(&(heap->lock));

    /* Return the old memory block */
    return ptr;
}
EXPORT_SYMBOL(os_memheap_realloc);

/**
 ***********************************************************************************************************************
 * @brief           This function frees the memory space pointed to by ptr, which must have been returned by a previous
 *                  call to os_memheap_malloc() or os_memheap_realloc().
 *
 * @param[in]       ptr             The pointer to memory block.
 *
 * @return          None.
 ***********************************************************************************************************************
 */
void os_memheap_free(void *ptr)
{
    os_err_t result;
    struct os_memheap *heap;
    struct os_memheap_item *header_ptr, *new_ptr;
    os_uint32_t inseos_header;

    if (ptr == OS_NULL) return;

    /* Set initial status as OK */
    inseos_header = 1;
    new_ptr       = OS_NULL;
    header_ptr    = (struct os_memheap_item *)
                    ((os_uint8_t *)ptr - OS_MEMHEAP_SIZE);

    OS_KERN_LOG(KERN_DEBUG, HEAP_TAG, "free memory: memory[0x%08x], block[0x%08x]",
                ptr, header_ptr);

    /* Check magic */
    OS_ASSERT((header_ptr->magic & OS_MEMHEAP_MASK) == OS_MEMHEAP_MAGIC);
    OS_ASSERT(header_ptr->magic & OS_MEMHEAP_USED);
    /* Check whether this block of memory has been over-written. */
    OS_ASSERT((header_ptr->next->magic & OS_MEMHEAP_MASK) == OS_MEMHEAP_MAGIC);

    /* Get pool ptr */
    heap = header_ptr->pool_ptr;

    OS_ASSERT(heap);
    OS_ASSERT(os_object_get_type(&heap->parent) == OS_OBJECT_MEMHEAP);

    /* Lock memheap */
    result = os_sem_wait(&(heap->lock), OS_IPC_WAITING_FOREVER);
    if (result != OS_EOK)
    {
        os_set_errno(result);

        return ;
    }

    /* Mark the memory as available. */
    header_ptr->magic &= ~OS_MEMHEAP_USED;
    /* Adjust the available number of bytes. */
    heap->available_size = heap->available_size + MEMITEM_SIZE(header_ptr);

    /* Determine if the block can be merged with the previous neighbor. */
    if (!OS_MEMHEAP_IS_USED(header_ptr->prev))
    {
        OS_KERN_LOG(KERN_DEBUG, HEAP_TAG, "merge: left node 0x%08x",
                    header_ptr->prev);

        /* Adjust the available number of bytes. */
        heap->available_size = heap->available_size + OS_MEMHEAP_SIZE;

        /* Merge block with previous neighbor. */
        (header_ptr->prev)->next = header_ptr->next;
        (header_ptr->next)->prev = header_ptr->prev;

        /* Move header pointer to previous. */
        header_ptr = header_ptr->prev;
        /* Don't insert header to free list */
        inseos_header = 0;
    }

    /* Determine if the block can be merged with the next neighbor. */
    if (!OS_MEMHEAP_IS_USED(header_ptr->next))
    {
        /* Adjust the available number of bytes. */
        heap->available_size = heap->available_size + OS_MEMHEAP_SIZE;

        /* Merge block with next neighbor. */
        new_ptr = header_ptr->next;

        OS_KERN_LOG(KERN_DEBUG, HEAP_TAG, "merge: right node 0x%08x, next_free 0x%08x, prev_free 0x%08x",
                    new_ptr, new_ptr->next_free, new_ptr->prev_free);

        new_ptr->next->prev = header_ptr;
        header_ptr->next    = new_ptr->next;

        /* Remove new ptr from free list */
        new_ptr->next_free->prev_free = new_ptr->prev_free;
        new_ptr->prev_free->next_free = new_ptr->next_free;
    }

    if (inseos_header)
    {
        /* No left merge, insert to free list */
        header_ptr->next_free = heap->free_list->next_free;
        header_ptr->prev_free = heap->free_list;
        heap->free_list->next_free->prev_free = header_ptr;
        heap->free_list->next_free            = header_ptr;

        OS_KERN_LOG(KERN_DEBUG, HEAP_TAG, "insert to free list: next_free 0x%08x, prev_free 0x%08x",
                    header_ptr->next_free, header_ptr->prev_free);
    }

    /* Release lock */
    os_sem_post(&(heap->lock));
}
EXPORT_SYMBOL(os_memheap_free);

#if defined(OS_USING_HEAP) && defined(OS_USING_MEM_HEAP_AS_HEAP)

#if defined(OS_USING_MEM_SMALL)
#error "ERROR: Macros OS_USING_MEM_HEAP_AS_HEAP and OS_USING_MEM_SMALL cannot be set at same time"
#endif

#if defined(OS_USING_MEM_SLAB)
#error "ERROR: Macros OS_USING_MEM_HEAP_AS_HEAP and OS_USING_MEM_SLAB cannot be set at same time"
#endif

#ifdef OS_USING_HOOK
static void (*gs_os_malloc_hook)(void *ptr, os_size_t size) = OS_NULL;
static void (*gs_os_free_hook)(void *ptr)  = OS_NULL;

/**
 ***********************************************************************************************************************
 * @brief           This function sets a hook called at the end of os_malloc()
 *
 * @param[in]       hook             The hook function is complemented by user.
 *
 * @return          None.
 ***********************************************************************************************************************
 */
void os_malloc_set_hook(void (*hook)(void *ptr, os_size_t size))
{
    gs_os_malloc_hook = hook;
}
EXPORT_SYMBOL(os_malloc_set_hook);

/**
 ***********************************************************************************************************************
 * @brief           This function sets a hook called at the end of os_free().
 *
 * @param[in]       hook             The hook function is complemented by user.
 *
 * @return          None.
 ***********************************************************************************************************************
 */
void os_free_set_hook(void (*hook)(void *ptr))
{
    gs_os_free_hook = hook;
}
EXPORT_SYMBOL(os_free_set_hook);

#endif /* end of OS_USING_HOOK */


static struct os_memheap gs_heap;

/**
 ***********************************************************************************************************************
 * @brief           This function initlializes the default heap in the system.
 *
 * @param[in]       begin_addr      The start address of heap.
 * @param[in]       end_addr        The end address of heap.
 *
 * @return          None.
 ***********************************************************************************************************************
 */
void os_system_heap_init(void *begin_addr, void *end_addr)
{
    /* Initialize a default heap in the system */
    os_memheap_init(&gs_heap,
                    "heap",
                    begin_addr,
                    (os_uint32_t)end_addr - (os_uint32_t)begin_addr);
}

/**
 ***********************************************************************************************************************
 * @brief           This function allocates 'size' bytes and returns a pointer to the allocated memory. The memory is not
 *                  initialized. If size is 0, then it returns NULL. If there are more than one memory heap objects, this
 *                  function tries to find suitable memory one object by one.
 *
 * @param[in]       size            The size of the requested block in bytes.
 *
 * @return          The pointer to allocated memory or OS_NULL if no free memory was found.
 ***********************************************************************************************************************
 */
void *os_malloc(os_size_t size)
{
    void *ptr;

    if (0 == size)
    {
        return OS_NULL;
    }

    /* Try to allocate in system heap */
    ptr = os_memheap_alloc(&gs_heap, size);
    if (ptr == OS_NULL)
    {
        struct os_object *object;
        struct os_list_node *node;
        struct os_memheap *heap;
        struct os_object_info *information;

        /* Try to allocate on other memory heap */
        information = os_object_get_info(OS_OBJECT_MEMHEAP);
        OS_ASSERT(information != OS_NULL);
        for (node  = information->object_list.next;
             node != &(information->object_list);
             node  = node->next)
        {
            object = os_list_entry(node, struct os_object, list);
            heap   = (struct os_memheap *)object;

            OS_ASSERT(heap);
            OS_ASSERT(os_object_get_type(&heap->parent) == OS_OBJECT_MEMHEAP);

            /* Skip default system heap */
            if (heap == &gs_heap)
                continue;

            ptr = os_memheap_alloc(heap, size);
            if (ptr != OS_NULL)
            {
                OS_OBJECT_HOOK_CALL(gs_os_malloc_hook, ((void *)ptr, size)); 
                break;
            }
               
        }
    }
    else
    {
        OS_OBJECT_HOOK_CALL(gs_os_malloc_hook, ((void *)ptr, size)); 
    }
  
    return ptr;
}
EXPORT_SYMBOL(os_malloc);

/**
 ***********************************************************************************************************************
 * @brief           This function frees the memory space pointed to by 'rmem', which must have been returned by a previous
 *                  call to os_malloc(), os_realloc or os_calloc().
 *
 * @param[in]       rmem           The pointer to memory space.
 *
 * @return          None.
 ***********************************************************************************************************************
 */
void os_free(void *rmem)
{
    OS_OBJECT_HOOK_CALL(gs_os_free_hook, (rmem));
    os_memheap_free(rmem);
}
EXPORT_SYMBOL(os_free);

/**
 ***********************************************************************************************************************
 * @brief           This function changes the size of the memory block pointed to by 'rmem' to 'newsize' bytes. If size
 *                  is equal to 0, it works in the same way as os_free(). If 'rmem' is OS_NULL, it works in the same way
 *                  as os_malloc().
 *
 * @param[in]       rmem            The pointer of memory block to change.
 * @param[in]       newsize         The size of new memory block.
 *
 * @return          The pointer to newly allocated memory or NULL.
 ***********************************************************************************************************************
 */
void *os_realloc(void *rmem, os_size_t newsize)
{
    void *new_ptr;
    struct os_memheap_item *header_ptr;

    if (rmem == OS_NULL)
    {
        return os_malloc(newsize);
    }

    if (newsize == 0)
    {
        os_free(rmem);
        return OS_NULL;
    }

    /* Get old memory item */
    header_ptr = (struct os_memheap_item *)
                 ((os_uint8_t *)rmem - OS_MEMHEAP_SIZE);

    new_ptr = os_memheap_realloc(header_ptr->pool_ptr, rmem, newsize);
    if (new_ptr == OS_NULL && newsize != 0)
    {
        /* Allocate memory block from other memheap */
        new_ptr = os_malloc(newsize);
        if (new_ptr != OS_NULL && rmem != OS_NULL)
        {
            os_size_t oldsize;

            /* Get the size of old memory block */
            oldsize = MEMITEM_SIZE(header_ptr);
            if (newsize > oldsize)
                os_memcpy(new_ptr, rmem, oldsize);
            else
                os_memcpy(new_ptr, rmem, newsize);

            os_free(rmem);
        }
    }

    return new_ptr;
}
EXPORT_SYMBOL(os_realloc);

/**
 ***********************************************************************************************************************
 * @brief           This function allocates memory for an array of 'count' elements of 'size' bytes each and returns a
 *                  pointer to the allocated memory. The memory is set to zero.
 *
 * @param[in]       count           Number of array to allocate.
 * @param[in]       size            Size of each element to allocate.
 *
 * @return          The pointer to allocated memory or OS_NULL if no free memory was found.
 ***********************************************************************************************************************
 */
void *os_calloc(os_size_t count, os_size_t size)
{
    void *ptr;
    os_size_t total_size;

    total_size = count * size;
    ptr = os_malloc(total_size);
    if (ptr != OS_NULL)
    {
        /* Clean memory */
        os_memset(ptr, 0, total_size);
    }

    return ptr;
}
EXPORT_SYMBOL(os_calloc);

#ifdef OS_MEM_STATS
/**
 ***********************************************************************************************************************
 * @brief           This function shows the information of memory usage.
 *
 * @param[out]       total           The total amount of usable memory, in bytes.
 * @param[out]       used            The amount of used memory, in bytes.
 * @param[out]       max_used        The maximum amount of the used memory, in bytes.
 *
 * @return           None.
 ***********************************************************************************************************************
*/
void os_memory_info(os_uint32_t *total, os_uint32_t *used, os_uint32_t *max_used)
{
    struct os_object      *object;
    struct os_list_node   *node;
    struct os_memheap     *heap;
    struct os_object_info *info;

    info = os_object_get_info(OS_OBJECT_MEMHEAP);
    OS_ASSERT(info != OS_NULL);

    if (OS_NULL != total)
    {
        *total = 0;
    }

    if (OS_NULL != used)
    {
        *used = 0;
    }

    if (OS_NULL != max_used)
    {
        *max_used = 0;
    }
            
    for (node  = info->object_list.next; node != &(info->object_list); node  = node->next)
    {
        object = os_list_entry(node, struct os_object, list);
        heap   = (struct os_memheap *)object;

        OS_ASSERT(heap);
        OS_ASSERT(os_object_get_type(&heap->parent) == OS_OBJECT_MEMHEAP);

        *total += heap->pool_size;
        *used += (heap->pool_size - heap->available_size);
        *max_used += heap->max_used_size;
    }

}
#endif /* end of OS_MEM_STATS */

#endif /* end of defined(OS_USING_HEAP) && defined(OS_USING_MEM_HEAP_AS_HEAP) */

#ifdef OS_USING_SHELL

#include <shell.h>

static os_err_t list_memheap_info(struct os_list_node *list)
{
    int maxlen;
    struct os_memheap *mh;
    os_list_node_t *node;
    const char *item_title = "memheap";

    maxlen = os_object_name_maxlen(item_title, list);

    os_kprintf("%-*.s  pool size  max used size available size\r\n", maxlen, item_title); 
    os_object_split(maxlen);
    os_kprintf(      " ---------- ------------- --------------\r\n");
    for (node = list->next; node != list; node = node->next)
    {
        mh = (struct os_memheap *)os_list_entry(node, struct os_object, list);

        os_kprintf("%-*.*s %-010d %-013d %-05d\r\n",
                   maxlen,
                   OS_NAME_MAX,
                   mh->parent.name,
                   mh->pool_size,
                   mh->max_used_size,
                   mh->available_size);
    }

    return OS_EOK;
}

static os_err_t sh_list_memheap(os_int32_t argc, char **argv)
{
    struct os_object_info *info;

    info = os_object_get_info(OS_OBJECT_MEMHEAP);
    return list_memheap_info(&info->object_list);
}
SH_CMD_EXPORT(memh, sh_list_memheap, "show memory heap information");
#endif /* end of OS_USING_SHELL */

#endif /* end of OS_USING_MEM_HEAP */

