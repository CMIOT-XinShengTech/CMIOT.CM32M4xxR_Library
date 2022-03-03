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
 * @file        os_mem_slab.c
 *
 * @brief       This file implements the functions to allocate and free dynamic memory.
 *
 * @revision
 * Date         Author          Notes
 * 2020-03-09   OneOS team      First Version
 ***********************************************************************************************************************
 */

#include <os_dbg.h>
#include <os_sem.h>
#include <os_module.h>
#include <os_memory.h>

#include "os_kernel_internal.h"
#include "os_util_internal.h"

#if defined (OS_USING_HEAP) && defined (OS_USING_MEM_SLAB)

#if defined(OS_USING_MEM_SMALL)
#error "ERROR: Macros OS_USING_MEM_SLAB and OS_USING_MEM_SMALL cannot be set at same time"
#endif

#if defined(OS_USING_MEM_HEAP_AS_HEAP)
#error "ERROR: Macros OS_USING_MEM_SLAB and OS_USING_MEM_HEAP_AS_HEAP cannot be set at same time"
#endif

#define SLAB_TAG                        "MSLAB"

#define OS_MM_PAGE_SIZE                 4096
#define OS_MM_PAGE_MASK                 (OS_MM_PAGE_SIZE - 1)
#define OS_MM_PAGE_BITS                 12

#ifdef OS_MEM_STATS
static os_size_t gs_used_mem, gs_max_mem;
#endif

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

/*
 * slab allocator implementation
 *
 * A slab allocator reserves a ZONE for each chunk size, then lays the
 * chunks out in an array within the zone.  Allocation and deallocation
 * is nearly instantanious, and fragmentation/overhead losses are limited
 * to a fixed worst-case amount.
 *
 * The downside of this slab implementation is in the chunk size
 * multiplied by the number of zones.  ~80 zones * 128K = 10MB of VM per cpu.
 * In a kernel implementation all this memory will be physical so
 * the zone size is adjusted downward on machines with less physical
 * memory.  The upside is that overhead is bounded... this is the *worst*
 * case overhead.
 *
 * Slab management is done on a per-cpu basis and no locking or mutexes
 * are required, only a critical section.  When one cpu frees memory
 * belonging to another cpu's slab manager an asynchronous IPI message
 * will be queued to execute the operation.   In addition, both the
 * high level slab allocator and the low level zone allocator optimize
 * M_ZERO requests, and the slab allocator does not have to pre initialize
 * the linked list of chunks.
 *
 * XXX Balancing is needed between cpus.  Balance will be handled through
 * asynchronous IPIs primarily by reassigning the z_Cpu ownership of chunks.
 *
 * XXX If we have to allocate a new zone and M_USE_RESERVE is set, use of
 * the new zone should be restricted to M_USE_RESERVE requests only.
 *
 *  Alloc Size  Chunking        Number of zones
 *  0-127       8               16
 *  128-255     16              8
 *  256-511     32              8
 *  512-1023    64              8
 *  1024-2047   128             8
 *  2048-4095   256             8
 *  4096-8191   512             8
 *  8192-16383  1024            8
 *  16384-32767 2048            8
 *  (if OS_MM_PAGE_SIZE is 4K the maximum zone allocation is 16383)
 *
 *  Allocations >= gs_zone_limit go directly to kmem.
 *
 *          API REQUIREMENTS AND SIDE EFFECTS
 *
 *    To operate as a drop-in replacement to the FreeBSD-4.x malloc() we
 *    have remained compatible with the following API requirements:
 *
 *    + small power-of-2 sized allocations are power-of-2 aligned (kern_tty)
 *    + all power-of-2 sized allocations are power-of-2 aligned (twe)
 *    + malloc(0) is allowed and returns non-OS_NULL (ahc driver)
 *    + ability to allocate arbitrarily large chunks of memory
 */

/*
 * Chunk structure for free elements
 */
typedef struct slab_chunk
{
    struct slab_chunk *c_next;
} slab_chunk;

/*
 * The IN-BAND zone header is placed at the beginning of each zone.
 */
typedef struct slab_zone
{
    os_int32_t  z_magic;        /* Magic number for sanity check */
    os_int32_t  z_nfree;        /* Total free chunks / ualloc space in zone */
    os_int32_t  z_nmax;         /* Maximum free chunks */

    struct slab_zone *z_next;   /* zoneary[] link if z_nfree non-zero */
    os_uint8_t  *z_baseptr;     /* The pointer to start of chunk array */

    os_int32_t  z_uindex;       /* Current initial allocation index */
    os_int32_t  z_chunksize;    /* Chunk size for validation */

    os_int32_t  z_zoneindex;    /* Zone index */
    slab_chunk  *z_freechunk;   /* Free chunk list */
} slab_zone;

#define ZALLOC_SLAB_MAGIC       0x51ab51ab
#define ZALLOC_ZONE_LIMIT       (16 * 1024)     /* Max slab-managed alloc */
#define ZALLOC_MIN_ZONE_SIZE    (32 * 1024)     /* Minimum zone size */
#define ZALLOC_MAX_ZONE_SIZE    (128 * 1024)    /* Maximum zone size */
#define NZONES                  72              /* Number of zones */
#define ZONE_RELEASE_THRESH     2               /* Threshold number of zones */

static slab_zone *gs_zone_array[NZONES];        /* Linked list of zones NFree > 0 */
static slab_zone *gs_zone_free;                 /* Whole zones that have become free */

static int gs_zone_free_cnt;
static int gs_zone_size;
static int gs_zone_limit;
static int gs_zone_page_cnt;

/*
 * Misc constants.  Note that allocations that are exact multiples of
 * OS_MM_PAGE_SIZE, or exceed the zone limit, fall through to the kmem module.
 */
#define MIN_CHUNK_SIZE      8       /* in bytes */
#define MIN_CHUNK_MASK      (MIN_CHUNK_SIZE - 1)

/*
 * Array of descriptors that describe the contents of each page
 */
#define PAGE_TYPE_FREE      0x00
#define PAGE_TYPE_SMALL     0x01
#define PAGE_TYPE_LARGE     0x02
struct memusage
{
    os_uint32_t type: 2 ;       /* page type */
    os_uint32_t size: 30;       /* pages allocated or offset from zone */
};
static struct memusage *gs_memusage = OS_NULL;
#define btokup(addr)    \
    (&gs_memusage[((os_uint32_t)(addr) - gs_heap_start) >> OS_MM_PAGE_BITS])

static os_uint32_t gs_heap_start, gs_heap_end;

/* page allocator */
struct os_page_head
{
    struct os_page_head *next;      /* next valid page */
    os_size_t page;                 /* number of page  */

    /* dummy */
    char dummy[OS_MM_PAGE_SIZE - (sizeof(struct os_page_head *) + sizeof(os_size_t))];
};
static struct os_page_head *gs_page_list;
static os_sem_t gs_heap_sem;

static void *os_page_alloc(os_size_t npages)
{
    struct os_page_head *b, *n;
    struct os_page_head **prev;

    if (0 == npages)
    {
        return OS_NULL;
    }

    os_sem_wait(&gs_heap_sem, OS_IPC_WAITING_FOREVER);
    for (prev = &gs_page_list; (b = *prev) != OS_NULL; prev = &(b->next))
    {
        if (b->page > npages)
        {
            /* Splite pages */
            n       = b + npages;
            n->next = b->next;
            n->page = b->page - npages;
            *prev   = n;
            break;
        }

        if (b->page == npages)
        {
            /* Remove this node */
            *prev = b->next;
            break;
        }
    }

    os_sem_post(&gs_heap_sem);

    return b;
}

static void os_page_free(void *addr, os_size_t npages)
{
    struct os_page_head *b, *n;
    struct os_page_head **prev;

    OS_ASSERT(OS_NULL != addr);
    OS_ASSERT(0 == (os_uint32_t)addr % OS_MM_PAGE_SIZE);
    OS_ASSERT(0 != npages);

    n = (struct os_page_head *)addr;

    os_sem_wait(&gs_heap_sem, OS_IPC_WAITING_FOREVER);

    for (prev = &gs_page_list; (b = *prev) != OS_NULL; prev = &(b->next))
    {
        OS_ASSERT(b->page > 0);
        OS_ASSERT(b > n || b + b->page <= n);

        if (b + b->page == n)
        {
            if (b + (b->page += npages) == b->next)
            {
                b->page += b->next->page;
                b->next  = b->next->next;
            }

            goto _return;
        }

        if (b == n + npages)
        {
            n->page = b->page + npages;
            n->next = b->next;
            *prev   = n;

            goto _return;
        }

        if (b > n + npages)
        {
            break;
        }
    }

    n->page = npages;
    n->next = b;
    *prev   = n;

_return:
    os_sem_post(&gs_heap_sem);
}

/*
 * Initialize the page allocator
 */
static void os_page_init(void *addr, os_size_t npages)
{
    OS_ASSERT(OS_NULL != addr);
    OS_ASSERT(0 != npages);

    gs_page_list = OS_NULL;
    os_page_free(addr, npages);
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
    os_uint32_t limsize, npages;

    OS_DEBUG_NOT_IN_INTERRUPT;

    /* Align begin and end addr to page size */
    gs_heap_start = OS_ALIGN_UP((os_uint32_t)begin_addr, OS_MM_PAGE_SIZE);
    gs_heap_end   = OS_ALIGN_DOWN((os_uint32_t)end_addr, OS_MM_PAGE_SIZE);

    if (gs_heap_start >= gs_heap_end)
    {
        OS_KERN_LOG(KERN_ERROR, SLAB_TAG, "os_system_heap_init, wrong address[0x%x - 0x%x]",
                    (os_uint32_t)begin_addr, (os_uint32_t)end_addr);

        return;
    }

    limsize = gs_heap_end - gs_heap_start;
    npages  = limsize / OS_MM_PAGE_SIZE;

    /* Initialize heap semaphore */
    os_sem_init(&gs_heap_sem, "heap", 1, OS_IPC_FLAG_FIFO);

    OS_KERN_LOG(KERN_DEBUG, SLAB_TAG, "heap[0x%x - 0x%x], size 0x%x, 0x%x pages",
                gs_heap_start, gs_heap_end, limsize, npages);

    /* Init pages */
    os_page_init((void *)gs_heap_start, npages);

    /* Calculate zone size */
    gs_zone_size = ZALLOC_MIN_ZONE_SIZE;
    while (gs_zone_size < ZALLOC_MAX_ZONE_SIZE && (gs_zone_size << 1) < (limsize / 1024))
    {
        gs_zone_size <<= 1;
    }

    gs_zone_limit = gs_zone_size / 4;
    if (gs_zone_limit > ZALLOC_ZONE_LIMIT)
    {
        gs_zone_limit = ZALLOC_ZONE_LIMIT;
    }

    gs_zone_page_cnt = gs_zone_size / OS_MM_PAGE_SIZE;

    OS_KERN_LOG(KERN_DEBUG, SLAB_TAG, "zone size 0x%x, zone page count 0x%x",
                gs_zone_size, gs_zone_page_cnt);

    /* Allocate gs_memusage array */
    limsize  = npages * sizeof(struct memusage);
    limsize  = OS_ALIGN_UP(limsize, OS_MM_PAGE_SIZE);
    gs_memusage = os_page_alloc(limsize / OS_MM_PAGE_SIZE);

    OS_KERN_LOG(KERN_DEBUG, SLAB_TAG, "gs_memusage 0x%x, size 0x%x",
                (os_uint32_t)gs_memusage, limsize);
}

OS_INLINE int zoneindex(os_size_t *bytes)
{
    /* unsigned for shift opt */
    os_uint32_t n = (os_uint32_t)(*bytes);

    if (n < 128)
    {
        *bytes = n = (n + 7) & ~7;

        /* 8 byte chunks, 16 zones */
        return (n / 8 - 1);
    }
    if (n < 256)
    {
        *bytes = n = (n + 15) & ~15;

        return (n / 16 + 7);
    }
    if (n < 8192)
    {
        if (n < 512)
        {
            *bytes = n = (n + 31) & ~31;

            return (n / 32 + 15);
        }
        if (n < 1024)
        {
            *bytes = n = (n + 63) & ~63;

            return (n / 64 + 23);
        }
        if (n < 2048)
        {
            *bytes = n = (n + 127) & ~127;

            return (n / 128 + 31);
        }
        if (n < 4096)
        {
            *bytes = n = (n + 255) & ~255;

            return (n / 256 + 39);
        }
        *bytes = n = (n + 511) & ~511;

        return (n / 512 + 47);
    }
    if (n < 16384)
    {
        *bytes = n = (n + 1023) & ~1023;

        return (n / 1024 + 55);
    }

    OS_KERN_LOG(KERN_ERROR, SLAB_TAG, "Unexpected byte count %d", n);

    return 0;
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
    slab_zone *z;
    os_int32_t zi;
    slab_chunk *chunk;
    struct memusage *kup;

    if (0 == size)
    {
        return OS_NULL;
    }

    /*
     * Handle large allocations directly.  There should not be very many of
     * these so performance is not a big issue.
     */
    if (size >= gs_zone_limit)
    {
        if (size > gs_heap_end - gs_heap_start)
        {
            return OS_NULL;
        }

        size = OS_ALIGN_UP(size, OS_MM_PAGE_SIZE);

        chunk = os_page_alloc(size >> OS_MM_PAGE_BITS);
        if (OS_NULL == chunk)
        {
            return OS_NULL;
        }

        /* set kup */
        kup = btokup(chunk);
        kup->type = PAGE_TYPE_LARGE;
        kup->size = size >> OS_MM_PAGE_BITS;

        OS_KERN_LOG(KERN_DEBUG, SLAB_TAG, "malloc a large memory 0x%x, page cnt %d, kup %d",
                    size,
                    size >> OS_MM_PAGE_BITS,
                    ((os_uint32_t)chunk - gs_heap_start) >> OS_MM_PAGE_BITS);

        os_sem_wait(&gs_heap_sem, OS_IPC_WAITING_FOREVER);

#ifdef OS_MEM_STATS
        gs_used_mem += size;
        if (gs_used_mem > gs_max_mem)
        {
            gs_max_mem = gs_used_mem;
        }
#endif
        goto done;
    }

    os_sem_wait(&gs_heap_sem, OS_IPC_WAITING_FOREVER);

    /*
     * Attempt to allocate out of an existing zone.  First try the free list,
     * then allocate out of unallocated space.  If we find a good zone move
     * it to the head of the list so later allocations find it quickly
     * (we might have thousands of zones in the list).
     *
     * Note: zoneindex() will panic of size is too large.
     */
    zi = zoneindex(&size);
    OS_ASSERT(zi < NZONES);

    OS_KERN_LOG(KERN_DEBUG, SLAB_TAG, "try to malloc 0x%x on zone: %d", size, zi);

    if ((z = gs_zone_array[zi]) != OS_NULL)
    {
        OS_ASSERT(z->z_nfree > 0);

        /* Remove us from the gs_zone_array[] when we become empty */
        if (0 == --z->z_nfree)
        {
            gs_zone_array[zi] = z->z_next;
            z->z_next = OS_NULL;
        }

        /*
         * No chunks are available but nfree said we had some memory, so
         * it must be available in the never-before-used-memory area
         * governed by uindex.  The consequences are very serious if our zone
         * got corrupted so we use an explicit os_kprintf rather then a KASSERT.
         */
        if (z->z_uindex + 1 != z->z_nmax)
        {
            z->z_uindex = z->z_uindex + 1;
            chunk = (slab_chunk *)(z->z_baseptr + z->z_uindex * size);
        }
        else
        {
            /* find chunk on free chunk list */
            chunk = z->z_freechunk;

            /* Remove this chunk from list */
            z->z_freechunk = z->z_freechunk->c_next;
        }

#ifdef OS_MEM_STATS
        gs_used_mem += z->z_chunksize;
        if (gs_used_mem > gs_max_mem)
        {
            gs_max_mem = gs_used_mem;
        }
#endif

        goto done;
    }

    /*
     * If all zones are exhausted we need to allocate a new zone for this
     * index.
     *
     * At least one subsystem, the tty code (see CROUND) expects power-of-2
     * allocations to be power-of-2 aligned.  We maintain compatibility by
     * adjusting the base offset below.
     */
    {
        os_int32_t off;

        if ((z = gs_zone_free) != OS_NULL)
        {
            /* remove zone from free zone list */
            gs_zone_free = z->z_next;
            -- gs_zone_free_cnt;
        }
        else
        {
            /* unlock heap, since page allocator lock it*/
            os_sem_post(&gs_heap_sem);

            /* allocate a zone from page */
            z = os_page_alloc(gs_zone_size / OS_MM_PAGE_SIZE);
            if (OS_NULL == z)
            {
                chunk = OS_NULL;
                goto __exit;
            }

            os_sem_wait(&gs_heap_sem, OS_IPC_WAITING_FOREVER);

            OS_KERN_LOG(KERN_DEBUG, SLAB_TAG, "alloc a new zone: 0x%x",
                        (os_uint32_t)z);

            /* Set message usage */
            for (off = 0, kup = btokup(z); off < gs_zone_page_cnt; off ++)
            {
                kup->type = PAGE_TYPE_SMALL;
                kup->size = off;

                kup ++;
            }
        }

        /* Clear to zero */
        os_memset(z, 0, sizeof(slab_zone));

        /* Get offset of slab zone struct in zone */
        off = sizeof(slab_zone);

        /*
         * Guarentee power-of-2 alignment for power-of-2-sized chunks.
         * Otherwise just 8-byte align the data.
         */
        if ((size | (size - 1)) + 1 == (size << 1))
        {
            off = (off + size - 1) & ~(size - 1);
        }
        else
        {
            off = (off + MIN_CHUNK_MASK) & ~MIN_CHUNK_MASK;
        }

        z->z_magic     = ZALLOC_SLAB_MAGIC;
        z->z_zoneindex = zi;
        z->z_nmax      = (gs_zone_size - off) / size;
        z->z_nfree     = z->z_nmax - 1;
        z->z_baseptr   = (os_uint8_t *)z + off;
        z->z_uindex    = 0;
        z->z_chunksize = size;

        chunk = (slab_chunk *)(z->z_baseptr + z->z_uindex * size);

        /* Link to zone array */
        z->z_next = gs_zone_array[zi];
        gs_zone_array[zi] = z;

#ifdef OS_MEM_STATS
        gs_used_mem += z->z_chunksize;
        if (gs_used_mem > gs_max_mem)
        {
            gs_max_mem = gs_used_mem;
        }
#endif
    }

done:
    os_sem_post(&gs_heap_sem);
    OS_OBJECT_HOOK_CALL(gs_os_malloc_hook, ((char *)chunk, size));

__exit:
    return chunk;
}
EXPORT_SYMBOL(os_malloc);

/**
 ***********************************************************************************************************************
 * @brief           This function changes the size of the memory block pointed to by 'ptr' to 'size' bytes. If 'size'
 *                  is equal to 0, it works in the same way as os_free(). If 'ptr' is OS_NULL, it works in the same way
 *                  as os_malloc().
 *
 * @param[in]       rmem            The pointer of memory block to change.
 * @param[in]       newsize         The size of new memory block.
 *
 * @return          The pointer to newly allocated memory or NULL.
 ***********************************************************************************************************************
 */
void *os_realloc(void *ptr, os_size_t size)
{
    void *nptr;
    slab_zone *z;
    struct memusage *kup;

    if (OS_NULL == ptr)
    {
        return os_malloc(size);
    }

    if (0 == size)
    {
        os_free(ptr);

        return OS_NULL;
    }

    /*
     * Get the original allocation's zone.  If the new request winds up
     * using the same chunk size we do not have to do anything.
     */
    kup = btokup((os_uint32_t)ptr & ~OS_MM_PAGE_MASK);
    if (PAGE_TYPE_LARGE == kup->type)
    {
        os_size_t osize;

        osize = kup->size << OS_MM_PAGE_BITS;
        if ((nptr = os_malloc(size)) == OS_NULL)
        {
            return OS_NULL;
        }
        os_memcpy(nptr, ptr, size > osize ? osize : size);
        os_free(ptr);

        return nptr;
    }
    else if (PAGE_TYPE_SMALL == kup->type)
    {
        z = (slab_zone *)(((os_uint32_t)ptr & ~OS_MM_PAGE_MASK) -
                          kup->size * OS_MM_PAGE_SIZE);
        OS_ASSERT(ZALLOC_SLAB_MAGIC == z->z_magic);

        zoneindex(&size);
        if (z->z_chunksize == size)
        {
            return (ptr); /* same chunk */
        }

        /*
         * Allocate memory for the new request size.  Note that zoneindex has
         * already adjusted the request size to the appropriate chunk size, which
         * should optimize our bcopy().  Then copy and return the new pointer.
         */
        if ((nptr = os_malloc(size)) == OS_NULL)
        {
            return OS_NULL;
        }

        os_memcpy(nptr, ptr, size > z->z_chunksize ? z->z_chunksize : size);
        os_free(ptr);

        return nptr;
    }

    return OS_NULL;
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

    p = os_malloc(count * size);

    if (p)
    {
        os_memset(p, 0, count * size);
    }

    return p;
}
EXPORT_SYMBOL(os_calloc);

/**
 ***********************************************************************************************************************
 * @brief           This function frees the memory space pointed to by 'ptr', which must have been returned by a previous
 *                  call to os_malloc(), os_realloc or os_calloc().
 *
 * @param[in]       rmem           The pointer to memory space.
 *
 * @return          None.
 ***********************************************************************************************************************
 */
void os_free(void *ptr)
{
    slab_zone *z;
    slab_chunk *chunk;
    struct memusage *kup;

    if (OS_NULL == ptr)
    {
        return ;
    }

    OS_OBJECT_HOOK_CALL(gs_os_free_hook, (ptr));

    /* Get memory usage */
#if OS_DEBUG_SLAB
    {
        os_uint32_t addr = ((os_uint32_t)ptr & ~OS_MM_PAGE_MASK);
        OS_KERN_LOG(KERN_DEBUG, SLAB_TAG, "free a memory 0x%x and align to 0x%x, kup index %d",
                    (os_uint32_t)ptr,
                    (os_uint32_t)addr,
                    ((os_uint32_t)(addr) - gs_heap_start) >> OS_MM_PAGE_BITS);
    }
#endif

    kup = btokup((os_uint32_t)ptr & ~OS_MM_PAGE_MASK);
    /* Release large allocation */
    if (PAGE_TYPE_LARGE == kup->type)
    {
        os_uint32_t size;

        os_sem_wait(&gs_heap_sem, OS_IPC_WAITING_FOREVER);
        /* Clear page counter */
        size = kup->size;
        kup->size = 0;

#ifdef OS_MEM_STATS
        gs_used_mem -= size * OS_MM_PAGE_SIZE;
#endif
        os_sem_post(&gs_heap_sem);

        OS_KERN_LOG(KERN_DEBUG, SLAB_TAG, "free large memory block 0x%x, page count %d",
                    (os_uint32_t)ptr, size);

        /* Free this page */
        os_page_free(ptr, size);

        return;
    }

    os_sem_wait(&gs_heap_sem, OS_IPC_WAITING_FOREVER);

    /* zone case. get out zone. */
    z = (slab_zone *)(((os_uint32_t)ptr & ~OS_MM_PAGE_MASK) -
                      kup->size * OS_MM_PAGE_SIZE);
    OS_ASSERT(ZALLOC_SLAB_MAGIC == z->z_magic);

    chunk          = (slab_chunk *)ptr;
    chunk->c_next  = z->z_freechunk;
    z->z_freechunk = chunk;

#ifdef OS_MEM_STATS
    gs_used_mem -= z->z_chunksize;
#endif

    /*
     * Bump the number of free chunks.  If it becomes non-zero the zone
     * must be added back onto the appropriate list.
     */
    if (0 == z->z_nfree++)
    {
        z->z_next = gs_zone_array[z->z_zoneindex];
        gs_zone_array[z->z_zoneindex] = z;
    }

    /*
     * If the zone becomes totally free, and there are other zones we
     * can allocate from, move this zone to the FreeZones list.  Since
     * this code can be called from an IPI callback, do *NOT* try to mess
     * with kernel_map here.  Hysteresis will be performed at malloc() time.
     */
    if (z->z_nfree == z->z_nmax &&
        (z->z_next || gs_zone_array[z->z_zoneindex] != z))
    {
        slab_zone **pz;

        OS_KERN_LOG(KERN_DEBUG, SLAB_TAG, "free zone 0x%x", (os_uint32_t)z, z->z_zoneindex);

        /* Remove zone from zone array list */
        for (pz = &gs_zone_array[z->z_zoneindex]; z != *pz; pz = &(*pz)->z_next)
            ;
        *pz = z->z_next;

        /* Reset zone */
        z->z_magic = -1;

        /* Insert to free zone list */
        z->z_next = gs_zone_free;
        gs_zone_free = z;

        ++ gs_zone_free_cnt;

        /* Release zone to page allocator */
        if (gs_zone_free_cnt > ZONE_RELEASE_THRESH)
        {
            register os_base_t i;

            z         = gs_zone_free;
            gs_zone_free = z->z_next;
            -- gs_zone_free_cnt;

            /* Set message usage */
            for (i = 0, kup = btokup(z); i < gs_zone_page_cnt; i ++)
            {
                kup->type = PAGE_TYPE_FREE;
                kup->size = 0;
                kup ++;
            }

            os_sem_post(&gs_heap_sem);

            /* Release pages */
            os_page_free(z, gs_zone_size / OS_MM_PAGE_SIZE);

            return;
        }
    }

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
        *total = gs_heap_end - gs_heap_start;
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
#include <os_errno.h>

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
    os_kprintf("total memory: %d\r\n", gs_heap_end - gs_heap_start);
    os_kprintf("used memory : %d\r\n", gs_used_mem);
    os_kprintf("maximum allocated memory: %d\r\n", gs_max_mem);

    return OS_EOK;
}
SH_CMD_EXPORT(mem, sh_list_mem, "show memory usage information");

#endif
#endif


#endif
