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
 * @file        os_memory.h
 *
 * @brief       Header file for memory management interface.
 *
 * @revision
 * Date         Author          Notes
 * 2020-03-09   OneOS team      First Version
 ***********************************************************************************************************************
 */

#ifndef __OS_MEMORY_H__
#define __OS_MEMORY_H__

#include <oneos_config.h>
#include <os_types.h>
#include <os_object.h>

#ifdef __cplusplus
extern "C" {
#endif


#ifdef OS_USING_HEAP

#ifndef OS_USING_SEMAPHORE
#error "Macro OS_USING_SEMAPHORE must be set."
#endif

/* Common heap memory interface. */
extern void  os_system_heap_init(void *begin_addr, void *end_addr);

extern void *os_malloc(os_size_t nbytes);
extern void  os_free(void *ptr);
extern void *os_realloc(void *ptr, os_size_t nbytes);
extern void *os_calloc(os_size_t count, os_size_t size);
extern void *os_malloc_align(os_size_t size, os_size_t align);
extern void  os_free_align(void *ptr);


#ifdef OS_USING_HOOK

extern void os_malloc_set_hook(void (*hook)(void *ptr, os_size_t size));
extern void os_free_set_hook(void (*hook)(void *ptr));

#endif /* end of OS_USING_HOOK */


#ifdef OS_MEM_STATS
extern void  os_memory_info(os_uint32_t *total,
                            os_uint32_t *used,
                            os_uint32_t *max_used);
#ifdef OS_USING_SHELL
extern os_err_t sh_list_mem(os_int32_t argc, char **argv);
#endif
#endif /* end of OS_MEM_STATS */
#endif /* end of OS_USING_HEAP */

#ifdef OS_USING_MEM_HEAP

#ifndef OS_USING_SEMAPHORE
#error "Macro OS_USING_SEMAPHORE must be set."
#endif

#include <os_sem.h>

/**
 ***********************************************************************************************************************
 * @struct      os_memheap_item
 *
 * @brief       Define memory heap item.
 ***********************************************************************************************************************
 */
struct os_memheap_item
{
    os_uint32_t             magic;                      /* Magic number for memheap. */
    struct os_memheap      *pool_ptr;                   /* The pointer to pool. */

    struct os_memheap_item *next;                       /* Next memheap item. */
    struct os_memheap_item *prev;                       /* Prev memheap item. */

    struct os_memheap_item *next_free;                  /* Next free memheap item. */
    struct os_memheap_item *prev_free;                  /* Prev free memheap item. */
};

/**
 ***********************************************************************************************************************
 * @struct      os_memheap
 *
 * @brief       Define memory heap object
 ***********************************************************************************************************************
 */
struct os_memheap
{
    os_object_t             parent;                     /* Inherit from os_object. */

    void                   *start_addr;                 /* Pool start address and size. */

    os_uint32_t             pool_size;                  /* Pool size. */
    os_uint32_t             available_size;             /* Available size. */
    os_uint32_t             max_used_size;              /* Maximum allocated size. */

    struct os_memheap_item *block_list;                 /* Used block list. */

    struct os_memheap_item *free_list;                  /* Free block list. */
    struct os_memheap_item  free_header;                /* Free block list header. */

    os_sem_t                lock;                       /* Semaphore lock. */
};

/* memheap interface */
extern os_err_t os_memheap_init(struct os_memheap *memheap,
                                const char        *name,
                                void              *start_addr,
                                os_size_t         size);
extern os_err_t os_memheap_deinit(struct os_memheap *heap);
extern void    *os_memheap_alloc(struct os_memheap *heap, os_size_t size);
extern void    *os_memheap_realloc(struct os_memheap *heap, void *ptr, os_size_t newsize);
extern void     os_memheap_free(void *ptr);

#endif /* end of OS_USING_MEM_HEAP */

#ifdef OS_USING_MEM_POOL
#include <os_list.h>

#define OS_MEM_WAITING_FOREVER                   ((os_tick_t)0xFFFFFFFF)
#define OS_MEM_WAITING_NO                        ((os_tick_t)0)
#define OS_MEMPOOL_HEAD_SIZE                     (sizeof(os_uint8_t *) + sizeof(os_uint32_t))
#define OS_MEMPOOL_SIZE(block_count, block_size) ((OS_MEMPOOL_HEAD_SIZE + OS_ALIGN_UP(block_size, OS_ALIGN_SIZE)) * block_count)

/**
 ***********************************************************************************************************************
 * @struct      os_mempool
 *
 * @brief       Define memory pool object
 ***********************************************************************************************************************
 */
struct os_mempool
{
    os_object_t    parent;                              /* Inherit from os_object. */

    void          *start_address;                       /* Memory pool start. */
    os_size_t      size;                                /* Size of memory pool. */

    os_size_t      block_size;                          /* Size of memory blocks. */
    os_uint8_t    *block_list;                          /* Memory blocks list. */

    os_size_t      block_total_count;                   /* Numbers of memory block. */
    os_size_t      block_free_count;                    /* Numbers of free memory block. */

    os_list_node_t suspend_task;                        /* Tasks pended on this resource. */
};
typedef struct os_mempool os_mp_t;

/* Memory pool interface. */
extern os_err_t os_mp_init(os_mp_t    *mp,
                           const char *name,
                           void       *start,
                           os_size_t  size,
                           os_size_t  block_size);
extern os_err_t os_mp_deinit(os_mp_t *mp);

extern os_mp_t *os_mp_create(const char *name,
                             os_size_t  block_count,
                             os_size_t  block_size);
extern os_err_t os_mp_destroy(os_mp_t *mp);

extern void    *os_mp_alloc(os_mp_t *mp, os_tick_t timeout);
extern void     os_mp_free(void *block);

#endif /* OS_USING_MEM_POOL */

#ifdef __cplusplus
}
#endif

#endif /* __OS_MEMORY_H__ */

