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
 * @file        os_mem_small.c
 *
 * @brief       This file implements the functions to allocate and free dynamic memory.
 *
 * @revision
 * Date         Author          Notes
 * 2020-03-09   OneOS team      First Version
 ***********************************************************************************************************************
 */
#include <oneos_config.h>
#include <os_dbg.h>
#include <os_sem.h>
#include <os_errno.h>
#include <os_module.h>
#include <os_memory.h>

#include "os_util_internal.h"
#include "os_kernel_internal.h"

#if defined (OS_USING_HEAP) && defined (OS_USING_MEM_SMALL)

#if defined(OS_USING_MEM_SLAB)
#error "ERROR: Macros OS_USING_MEM_SMALL and OS_USING_MEM_SLAB cannot be set at same time"
#endif

#if defined(OS_USING_MEM_HEAP_AS_HEAP)
#error "ERROR: Macros OS_USING_MEM_SMALL and OS_USING_MEM_HEAP_AS_HEAP cannot be set at same time"
#endif

#define SMALL_TAG               "MSMALL"

#ifdef OS_USING_HOOK
static void (*gs_os_malloc_hook)(void *ptr, os_size_t size) = OS_NULL;
static void (*gs_os_free_hook)(void *ptr) = OS_NULL;

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
 * @brief           This function sets a hook called at the end of os_mp_free().
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

#define HEAP_MAGIC 0x1ea0
struct heap_mem
{
    os_uint16_t magic;        /* Magic and used flag */
    os_uint16_t used;

    os_size_t next, prev;

#ifdef OS_USING_MEMTRACE
    os_uint8_t task[4];      /* Task name */
#endif
};

/* The pointer to the heap: for alignment, gs_heap_ptr is now a pointer instead of an array */
static os_uint8_t *gs_heap_ptr;

/* The last entry, always unused! */
static struct heap_mem *gs_heap_end;

#define MIN_SIZE 12
#define MIN_SIZE_ALIGNED     OS_ALIGN_UP(MIN_SIZE, OS_ALIGN_SIZE)
#define SIZEOF_STRUCT_MEM    OS_ALIGN_UP(sizeof(struct heap_mem), OS_ALIGN_SIZE)

/* The pointer to the lowest free block */
static struct heap_mem *gs_lfree;

static struct os_semaphore gs_heap_sem;
static os_size_t gs_mem_size_aligned;

#ifdef OS_MEM_STATS
static os_size_t gs_used_mem, gs_max_mem;
#endif
#ifdef OS_USING_MEMTRACE
OS_INLINE void os_mem_setname(struct heap_mem *mem, const char *name)
{
    int index;
    for (index = 0; index < sizeof(mem->task); index ++)
    {
        if ('\0' == name[index])
        {
            break;
        }
        mem->task[index] = name[index];
    }

    for (; index < sizeof(mem->task); index ++)
    {
        mem->task[index] = ' ';
    }
}
#endif

static void plug_holes(struct heap_mem *mem)
{
    struct heap_mem *nmem;
    struct heap_mem *pmem;

    OS_ASSERT((os_uint8_t *)mem >= gs_heap_ptr);
    OS_ASSERT((os_uint8_t *)mem < (os_uint8_t *)gs_heap_end);
    OS_ASSERT(0 == mem->used);

    /* Plug hole forward */
    nmem = (struct heap_mem *)&gs_heap_ptr[mem->next];
    if (mem != nmem &&
        0 == nmem->used &&
        (os_uint8_t *)nmem != (os_uint8_t *)gs_heap_end)
    {
        /* If mem->next is unused and not end of gs_heap_ptr,
         * combine mem and mem->next
         */
        if (gs_lfree == nmem)
        {
            gs_lfree = mem;
        }
        mem->next = nmem->next;
        ((struct heap_mem *)&gs_heap_ptr[nmem->next])->prev = (os_uint8_t *)mem - gs_heap_ptr;
    }

    /* Plug hole backward */
    pmem = (struct heap_mem *)&gs_heap_ptr[mem->prev];
    if (pmem != mem && 0 == pmem->used)
    {
        /* If mem->prev is unused, combine mem and mem->prev */
        if (gs_lfree == mem)
        {
            gs_lfree = pmem;
        }
        pmem->next = mem->next;
        ((struct heap_mem *)&gs_heap_ptr[mem->next])->prev = (os_uint8_t *)pmem - gs_heap_ptr;
    }
}

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
    struct heap_mem *mem;
    os_uint32_t begin_align = OS_ALIGN_UP((os_uint32_t)begin_addr, OS_ALIGN_SIZE);
    os_uint32_t end_align = OS_ALIGN_DOWN((os_uint32_t)end_addr, OS_ALIGN_SIZE);

    OS_DEBUG_NOT_IN_INTERRUPT;

    /* Alignment addr */
    if ((end_align > (2 * SIZEOF_STRUCT_MEM)) &&
        ((end_align - 2 * SIZEOF_STRUCT_MEM) >= begin_align))
    {
        /* Calculate the aligned memory size */
        gs_mem_size_aligned = end_align - begin_align - 2 * SIZEOF_STRUCT_MEM;
    }
    else
    {
        OS_KERN_LOG(KERN_ERROR, SMALL_TAG, "mem init, error begin address 0x%x, and end address 0x%x",
                    (os_uint32_t)begin_addr, (os_uint32_t)end_addr);

        return;
    }

    /* The pointer to begin address of heap */
    gs_heap_ptr = (os_uint8_t *)begin_align;

    OS_KERN_LOG(KERN_DEBUG, SMALL_TAG, "mem init, heap begin address 0x%x, size %d",
                (os_uint32_t)gs_heap_ptr, gs_mem_size_aligned);

    /* Initialize the start of the heap */
    mem        = (struct heap_mem *)gs_heap_ptr;
    mem->magic = HEAP_MAGIC;
    mem->next  = gs_mem_size_aligned + SIZEOF_STRUCT_MEM;
    mem->prev  = 0;
    mem->used  = 0;
#ifdef OS_USING_MEMTRACE
    os_mem_setname(mem, "INIT");
#endif

    /* Initialize the end of the heap */
    gs_heap_end        = (struct heap_mem *)&gs_heap_ptr[mem->next];
    gs_heap_end->magic = HEAP_MAGIC;
    gs_heap_end->used  = 1;
    gs_heap_end->next  = gs_mem_size_aligned + SIZEOF_STRUCT_MEM;
    gs_heap_end->prev  = gs_mem_size_aligned + SIZEOF_STRUCT_MEM;
#ifdef OS_USING_MEMTRACE
    os_mem_setname(gs_heap_end, "INIT");
#endif

    os_sem_init(&gs_heap_sem, "heap", 1, OS_IPC_FLAG_FIFO);

    /* Initialize the lowest-free pointer to the start of the heap */
    gs_lfree = (struct heap_mem *)gs_heap_ptr;
}

/**
 ***********************************************************************************************************************
 * @brief           This function allocates 'size' bytes and returns a pointer to the allocated memory. The memory is not
 *                  initialized. If size is 0, then it returns NULL.
 *
 * @param[in]       size            The size of the requested block in bytes.
 *
 * @return          The pointer to allocated memory or OS_NULL if no free memory was found.
 ***********************************************************************************************************************
 */
void *os_malloc(os_size_t size)
{
    os_size_t ptr, ptr2;
    struct heap_mem *mem, *mem2;

    OS_DEBUG_NOT_IN_INTERRUPT;

    if (0 == size)
    {
        return OS_NULL;
    }

    if (size > gs_mem_size_aligned)
    {
        OS_KERN_LOG(KERN_ERROR, SMALL_TAG, "no memory");

        return OS_NULL;
    }

    /* Alignment size */
    size = OS_ALIGN_UP(size, OS_ALIGN_SIZE);

    if (size > gs_mem_size_aligned)
    {
        OS_KERN_LOG(KERN_ERROR, SMALL_TAG, "no memory");

        return OS_NULL;
    }

    /* Every data block must be at least MIN_SIZE_ALIGNED long */
    if (size < MIN_SIZE_ALIGNED)
    {
        size = MIN_SIZE_ALIGNED;
    }

    /* Wait memory semaphore */
    os_sem_wait(&gs_heap_sem, OS_IPC_WAITING_FOREVER);

    for (ptr = (os_uint8_t *)gs_lfree - gs_heap_ptr;
         ptr < gs_mem_size_aligned - size;
         ptr = ((struct heap_mem *)&gs_heap_ptr[ptr])->next)
    {
        mem = (struct heap_mem *)&gs_heap_ptr[ptr];

        if ((!mem->used) && (mem->next - (ptr + SIZEOF_STRUCT_MEM)) >= size)
        {
            /* mem is not used and at least perfect fit is possible:
             * mem->next - (ptr + SIZEOF_STRUCT_MEM) gives us the 'user data size' of mem */

            if (mem->next - (ptr + SIZEOF_STRUCT_MEM) >=
                (size + SIZEOF_STRUCT_MEM + MIN_SIZE_ALIGNED))
            {
                /* (in addition to the above, we test if another struct heap_mem (SIZEOF_STRUCT_MEM) containing
                 * at least MIN_SIZE_ALIGNED of data also fits in the 'user data space' of 'mem')
                 * -> split large block, create empty remainder,
                 * remainder must be large enough to contain MIN_SIZE_ALIGNED data: if
                 * mem->next - (ptr + (2*SIZEOF_STRUCT_MEM)) == size,
                 * struct heap_mem would fit in but no data between mem2 and mem2->next
                 * @todo we could leave out MIN_SIZE_ALIGNED. We would create an empty
                 *       region that couldn't hold data, but when mem->next gets freed,
                 *       the 2 regions would be combined, resulting in more free memory
                 */
                ptr2 = ptr + SIZEOF_STRUCT_MEM + size;

                /* Create mem2 struct */
                mem2       = (struct heap_mem *)&gs_heap_ptr[ptr2];
                mem2->magic = HEAP_MAGIC;
                mem2->used = 0;
                mem2->next = mem->next;
                mem2->prev = ptr;
#ifdef OS_USING_MEMTRACE
                os_mem_setname(mem2, "    ");
#endif

                /* And insert it between mem and mem->next */
                mem->next = ptr2;
                mem->used = 1;

                if (mem2->next != gs_mem_size_aligned + SIZEOF_STRUCT_MEM)
                {
                    ((struct heap_mem *)&gs_heap_ptr[mem2->next])->prev = ptr2;
                }
#ifdef OS_MEM_STATS
                gs_used_mem += (size + SIZEOF_STRUCT_MEM);
                if (gs_max_mem < gs_used_mem)
                {
                    gs_max_mem = gs_used_mem;
                }
#endif
            }
            else
            {
                /* (A mem2 struct does no fit into the user data space of mem and mem->next will always
                 * be used at this point: if not we have 2 unused structs in a row, plug_holes should have
                 * take care of this).
                 * -> near fit or excact fit: do not split, no mem2 creation
                 * also can't move mem->next directly behind mem, since mem->next
                 * will always be used at this point!
                 */
                mem->used = 1;
#ifdef OS_MEM_STATS
                gs_used_mem += mem->next - ((os_uint8_t *)mem - gs_heap_ptr);
                if (gs_max_mem < gs_used_mem)
                {
                    gs_max_mem = gs_used_mem;
                }
#endif
            }
            /* Set memory block magic */
            mem->magic = HEAP_MAGIC;
#ifdef OS_USING_MEMTRACE
            if (os_task_self())
            {
                os_mem_setname(mem, ((os_object_t *)os_task_self())->name);
            }
            else
            {
                os_mem_setname(mem, "NONE");
            }
#endif

            if (mem == gs_lfree)
            {
                /* Find next free block after mem and update lowest free pointer */
                while (gs_lfree->used && gs_lfree != gs_heap_end)
                    gs_lfree = (struct heap_mem *)&gs_heap_ptr[gs_lfree->next];

                OS_ASSERT(((gs_lfree == gs_heap_end) || (!gs_lfree->used)));
            }

            os_sem_post(&gs_heap_sem);
            OS_ASSERT((os_uint32_t)mem + SIZEOF_STRUCT_MEM + size <= (os_uint32_t)gs_heap_end);
            OS_ASSERT((os_uint32_t)((os_uint8_t *)mem + SIZEOF_STRUCT_MEM) % OS_ALIGN_SIZE == 0);
            OS_ASSERT((((os_uint32_t)mem) & (OS_ALIGN_SIZE - 1)) == 0);

            OS_KERN_LOG(KERN_DEBUG, SMALL_TAG, "allocate memory at 0x%x, size: %d",
                        (os_uint32_t)((os_uint8_t *)mem + SIZEOF_STRUCT_MEM),
                        (os_uint32_t)(mem->next - ((os_uint8_t *)mem - gs_heap_ptr)));

            OS_OBJECT_HOOK_CALL(gs_os_malloc_hook,
                                (((void *)((os_uint8_t *)mem + SIZEOF_STRUCT_MEM)), size));

            /* Return the memory data except mem struct */
            return (os_uint8_t *)mem + SIZEOF_STRUCT_MEM;
        }
    }

    os_sem_post(&gs_heap_sem);

    return OS_NULL;
}
EXPORT_SYMBOL(os_malloc);

/**
 ***********************************************************************************************************************
 * @brief           This function changes the size of the memory block pointed to by 'rmem' to 'newsize' bytes. If 'newsize'
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
    os_size_t size;
    os_size_t ptr, ptr2;
    struct heap_mem *mem, *mem2;
    void *nmem;

    OS_DEBUG_NOT_IN_INTERRUPT;

    if (OS_NULL == rmem)
    {
        return os_malloc(newsize);
    }

    if (0 == newsize)
    {
        os_free(rmem);

        return OS_NULL;
    }

    if (newsize > gs_mem_size_aligned)
    {
        OS_KERN_LOG(KERN_ERROR, SMALL_TAG, "realloc: out of memory");
        return OS_NULL;
    }

    /* Alignment size */
    newsize = OS_ALIGN_UP(newsize, OS_ALIGN_SIZE);
    if (newsize > gs_mem_size_aligned)
    {
        OS_KERN_LOG(KERN_DEBUG, SMALL_TAG, "realloc: out of memory");

        return OS_NULL;
    }

    os_sem_wait(&gs_heap_sem, OS_IPC_WAITING_FOREVER);

    if ((os_uint8_t *)rmem < (os_uint8_t *)gs_heap_ptr ||
        (os_uint8_t *)rmem >= (os_uint8_t *)gs_heap_end)
    {
        /* Illegal memory */
        os_sem_post(&gs_heap_sem);

        return rmem;
    }

    mem = (struct heap_mem *)((os_uint8_t *)rmem - SIZEOF_STRUCT_MEM);

    ptr = (os_uint8_t *)mem - gs_heap_ptr;
    size = mem->next - ptr - SIZEOF_STRUCT_MEM;
    if (size == newsize)
    {
        /* The size is the same as */
        os_sem_post(&gs_heap_sem);

        return rmem;
    }

    if (newsize + SIZEOF_STRUCT_MEM + MIN_SIZE < size)
    {
        /* Split memory block */
#ifdef OS_MEM_STATS
        gs_used_mem -= (size - newsize);
#endif

        ptr2 = ptr + SIZEOF_STRUCT_MEM + newsize;
        mem2 = (struct heap_mem *)&gs_heap_ptr[ptr2];
        mem2->magic = HEAP_MAGIC;
        mem2->used = 0;
        mem2->next = mem->next;
        mem2->prev = ptr;
#ifdef OS_USING_MEMTRACE
        os_mem_setname(mem2, "    ");
#endif
        mem->next = ptr2;
        if (mem2->next != gs_mem_size_aligned + SIZEOF_STRUCT_MEM)
        {
            ((struct heap_mem *)&gs_heap_ptr[mem2->next])->prev = ptr2;
        }

        plug_holes(mem2);

        os_sem_post(&gs_heap_sem);

        return rmem;
    }
    os_sem_post(&gs_heap_sem);

    /* Expand memory */
    nmem = os_malloc(newsize);
    if (OS_NULL != nmem) /* check memory */
    {
        os_memcpy(nmem, rmem, size < newsize ? size : newsize);
        os_free(rmem);
    }

    return nmem;
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
    void *p;

    /* Allocate 'count' objects of size 'size' */
    p = os_malloc(count * size);

    /* Zero the memory */
    if (p)
    {
        os_memset(p, 0, count * size);
    }

    return p;
}
EXPORT_SYMBOL(os_calloc);

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
    struct heap_mem *mem;

    if (OS_NULL == rmem)
    {
        return;
    }

    OS_DEBUG_NOT_IN_INTERRUPT;

    OS_ASSERT((((os_uint32_t)rmem) & (OS_ALIGN_SIZE - 1)) == 0);
    OS_ASSERT((os_uint8_t *)rmem >= (os_uint8_t *)gs_heap_ptr &&
              (os_uint8_t *)rmem < (os_uint8_t *)gs_heap_end);

    OS_OBJECT_HOOK_CALL(gs_os_free_hook, (rmem));

    if ((os_uint8_t *)rmem < (os_uint8_t *)gs_heap_ptr ||
        (os_uint8_t *)rmem >= (os_uint8_t *)gs_heap_end)
    {
        OS_KERN_LOG(KERN_DEBUG, SMALL_TAG, "illegal memory");

        return;
    }

    /* Get the corresponding struct heap_mem ... */
    mem = (struct heap_mem *)((os_uint8_t *)rmem - SIZEOF_STRUCT_MEM);

    OS_KERN_LOG(KERN_DEBUG, SMALL_TAG, "release memory 0x%x, size: %d",
                (os_uint32_t)rmem,
                (os_uint32_t)(mem->next - ((os_uint8_t *)mem - gs_heap_ptr)));


    /* Protect the heap from concurrent access */
    os_sem_wait(&gs_heap_sem, OS_IPC_WAITING_FOREVER);

    /* Which has to be in a used state */
    if (!mem->used || HEAP_MAGIC != mem->magic)
    {
        OS_KERN_LOG(KERN_WARNING, SMALL_TAG, "to free a bad data block:");
        OS_KERN_LOG(KERN_WARNING, SMALL_TAG, "mem: 0x%08x, used flag: %d, magic code: 0x%04x", mem, mem->used, mem->magic);
    }
    OS_ASSERT(mem->used);
    OS_ASSERT(HEAP_MAGIC == mem->magic);
    /* And is now unused. */
    mem->used  = 0;
    mem->magic = HEAP_MAGIC;
#ifdef OS_USING_MEMTRACE
    os_mem_setname(mem, "    ");
#endif

    if (mem < gs_lfree)
    {
        /* The newly freed struct is now the lowest */
        gs_lfree = mem;
    }

#ifdef OS_MEM_STATS
    gs_used_mem -= (mem->next - ((os_uint8_t *)mem - gs_heap_ptr));
#endif

    /* Finally, see if prev or next are free also */
    plug_holes(mem);
    os_sem_post(&gs_heap_sem);
}
EXPORT_SYMBOL(os_free);

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
void os_memory_info(os_uint32_t *total,
                    os_uint32_t *used,
                    os_uint32_t *max_used)
{
    if (OS_NULL != total)
    {
        *total = gs_mem_size_aligned;
    }

    if (OS_NULL != used)
    {
        *used = gs_used_mem;
    }

    if (OS_NULL != max_used)
    {
        *max_used = gs_max_mem;
    }
}

#ifdef OS_USING_SHELL
#include <shell.h>

/**
***********************************************************************************************************************
* @brief           Show the information of heap.
*
* @param[in]       argc                argment count
* @param[in]       argv                argment list
*
* @return          Will only return OS_EOK     
***********************************************************************************************************************
*/
os_err_t sh_list_mem(os_int32_t argc, char **argv)
{
    os_kprintf("total memory: %d\r\n", gs_mem_size_aligned);
    os_kprintf("used memory : %d\r\n", gs_used_mem);
    os_kprintf("maximum allocated memory: %d\r\n", gs_max_mem);

    return OS_EOK;
}
SH_CMD_EXPORT(mem, sh_list_mem, "show memory usage information");

#ifdef OS_USING_MEMTRACE
static os_err_t sh_memcheck(os_int32_t argc, char **argv)
{
    int position;
    os_uint32_t level;
    struct heap_mem *mem;
    level = os_hw_interrupt_disable();
    for (mem = (struct heap_mem *)gs_heap_ptr; mem != gs_heap_end; mem = (struct heap_mem *)&gs_heap_ptr[mem->next])
    {
        position = (os_uint32_t)mem - (os_uint32_t)gs_heap_ptr;
        if (position < 0)
        {
            goto __exit;
        }
        if (position > gs_mem_size_aligned)
        {
            goto __exit;
        }
        if (HEAP_MAGIC != mem->magic)
        {
            goto __exit;
        }
        if (mem->used != 0 && 1 != mem->used)
        {
            goto __exit;
        }
    }
    os_hw_interrupt_enable(level);

    return OS_EOK;
__exit:
    os_kprintf("Memory block wrong:\r\n");
    os_kprintf("address: 0x%08x\r\n", mem);
    os_kprintf("  magic: 0x%04x\r\n", mem->magic);
    os_kprintf("   used: %d\r\n", mem->used);
    os_kprintf("  size: %d\r\n", mem->next - position - SIZEOF_STRUCT_MEM);
    os_hw_interrupt_enable(level);

    return OS_EOK;
}
SH_CMD_EXPORT(memcheck, sh_memcheck, "check memory data");

static os_err_t sh_memtrace(os_int32_t argc, char **argv)
{
    struct heap_mem *mem;

    sh_list_mem(0, OS_NULL);

    os_kprintf("\r\nmemory heap address:\r\n");
    os_kprintf("heap_ptr: 0x%08x\r\n", gs_heap_ptr);
    os_kprintf("lfree   : 0x%08x\r\n", gs_lfree);
    os_kprintf("heap_end: 0x%08x\r\n", gs_heap_end);

    os_kprintf("\r\n--memory item information --\r\n");
    os_kprintf("\r\n  address     size   task\r\n");
    for (mem = (struct heap_mem *)gs_heap_ptr; mem != gs_heap_end; mem = (struct heap_mem *)&gs_heap_ptr[mem->next])
    {
        int position = (os_uint32_t)mem - (os_uint32_t)gs_heap_ptr;
        int size;

        os_kprintf("[0x%08x - ", mem);

        size = mem->next - position - SIZEOF_STRUCT_MEM;
        if (size < 1024)
        {
            os_kprintf("%5d", size);
        }
        else if (size < 1024 * 1024)
        {
            os_kprintf("%4dK", size / 1024);
        }
        else
        {
            os_kprintf("%4dM", size / (1024 * 1024));
        }

        os_kprintf("] %c%c%c%c", mem->task[0], mem->task[1], mem->task[2], mem->task[3]);

        if (HEAP_MAGIC != mem->magic)
        {
            os_kprintf(": ***\r\n");
        }
        else
        {
            os_kprintf("\r\n");
        }
    }

    return OS_EOK;
}
SH_CMD_EXPORT(memtrace, sh_memtrace, "dump memory trace information");
#endif /* end of OS_USING_MEMTRACE */
#endif /* end of OS_USING_SHELL    */

#endif

#endif /* end of OS_USING_HEAP */

