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
 * @file        os_util.c
 *
 * @brief       This file provides some utility functions similar to C library, so kernel does not depend on any
 *              C library.
 *
 * @revision
 * Date         Author          Notes
 * 2020-02-20   OneOS Team      First version.
 * 2020-07-31   OneOS Team      Add assert hook.
 ***********************************************************************************************************************
 */
#include <stdio.h>
#include <os_types.h>
#include <os_stddef.h>
#include <oneos_config.h>
#include <os_errno.h>
#include <os_hw.h>
#include <os_clock.h>
#include <os_assert.h>
#include <os_module.h>
#include <os_task.h>
#include <os_memory.h>

#include "os_kernel_internal.h"

void (*os_assert_hook)(const char *ex_string, const char *func, os_int32_t line) =  OS_NULL;

#ifdef OS_USING_HEAP
/**
 ***********************************************************************************************************************
 * @brief           This function allocates a memory block, which address is aligned to the specified alignment size.
 *
 * @param[in]       size            The allocated memory block size.
 * @param[in]       align           The alignment size.
 *
 * @return          The allocated memory pointer.
 * @retval          OS_NULL         Allocated memory block failed.
 * @retval          else            Allocated memory block successfull.
 ***********************************************************************************************************************
 */
void *os_malloc_align(os_size_t size, os_size_t align)
{
    void *align_ptr;
    void *ptr;
    os_size_t align_size;

    /* Align the alignment size to 4 byte */
    align = ((align + 0x03) & ~0x03);

    /* Get total aligned size */
    align_size = ((size + 0x03) & ~0x03) + align;

    /* Allocate memory block from heap */
    ptr = os_malloc(align_size);
    if (ptr != OS_NULL)
    {
        /* The allocated memory block is aligned */
        if (((os_uint32_t)ptr & (align - 1)) == 0)
        {
            align_ptr = (void *)((os_uint32_t)ptr + align);
        }
        /* The allocated memory block is not aligned */
        else
        {
            align_ptr = (void *)(((os_uint32_t)ptr + (align - 1)) & ~(align - 1));
        }

        /* Set the pointer before alignment pointer to the real pointer */
        *((os_uint32_t *)((os_uint32_t)align_ptr - sizeof(void *))) = (os_uint32_t)ptr;

        ptr = align_ptr;
    }

    return ptr;
}
EXPORT_SYMBOL(os_malloc_align);

/**
 ***********************************************************************************************************************
 * @brief           This function release the memory block, which is allocated by os_malloc_align() function and 
 *                  address is aligned.
 *
 * @param[in]       ptr             The memory block pointer.
 *
 * @return          No return value.
 ***********************************************************************************************************************
 */
void os_free_align(void *ptr)
{
    void *real_ptr;

    OS_ASSERT(ptr);

    real_ptr = (void *) * (os_uint32_t *)((os_uint32_t)ptr - sizeof(void *));
    os_free(real_ptr);

    return;
}
EXPORT_SYMBOL(os_free_align);
#endif /* OS_USING_HEAP */

/**
 ***********************************************************************************************************************
 * @brief           This function will set the content of memory to specified value.
 *
 * @param[out]      buff            Pointer to the start of the buffer.
 * @param[in]       val             The value to fill the buffer with
 * @param[in]       count           The size of the buffer.
 *
 * @return          The address of the buffer filled with specified value.
 ***********************************************************************************************************************
 */
void *os_memset(void *buff, os_uint8_t val, os_size_t count)
{
#ifdef OS_USING_TINY_SIZE
    os_uint8_t *addr_tmp;
    
    addr_tmp = (os_uint8_t *)buff;
    while (count--)
    {
        *addr_tmp = val;
        addr_tmp++;
    }
    
    return buff;
#else
#define BLOCK_SIZE              (sizeof(os_ubase_t))
#define ADDR_ALIGNED(addr)      (!((os_ubase_t)(addr) & (BLOCK_SIZE -1)))
#define TOO_SMALL(len)          ((len) < BLOCK_SIZE)

    os_uint8_t  *addr_tmp;
    os_ubase_t  *aligned_addr;
    os_ubase_t  buffer;
    os_ubase_t  base_val;
    os_uint32_t i;

    addr_tmp = (os_uint8_t *)buff;

    if (!TOO_SMALL(count) && ADDR_ALIGNED(buff))
    {
        aligned_addr = (os_ubase_t *)buff;
        base_val     = (os_ubase_t)val;
        buffer       = base_val;

        for (i = 1; i < BLOCK_SIZE; i++)
        {
            buffer = (buffer << 8) | base_val;   
        }
     
        while (count >= BLOCK_SIZE)
        {
            *aligned_addr = buffer;
            aligned_addr++;
            count -= BLOCK_SIZE;
        }

        addr_tmp = (os_uint8_t *)aligned_addr;
    }

    while (count--)
    {
        *addr_tmp = val;
        addr_tmp++;
    }

    return buff;
    
#undef BLOCK_SIZE
#undef ADDR_ALIGNED
#undef TOO_SMALL
#endif
}

/**
 ***********************************************************************************************************************
 * @brief           This function will copy memory content from source address to destination address.
 *
 * @param[out]      dst             The address of destination memory.
 * @param[in]       src             The address of source memory.
 * @param[in]       count           The copied length.
 *
 * @return          The address of destination memory.
 ***********************************************************************************************************************
 */
void *os_memcpy(void *dst, const void *src, os_size_t count)
{
#ifdef OS_USING_TINY_SIZE
    char       *dst_tmp;
    const char *src_tmp;

    dst_tmp = (char *)dst;
    src_tmp = (const char *)src;

    while (count--)
    {
        *dst_tmp = *src_tmp;
        dst_tmp++;
        src_tmp++;
    }

    return dst;
#else
#define BLOCK_SIZE                          (sizeof(os_ubase_t))
#define ADDR_BOTH_ALIGNED(addr1, addr2)                             \
    (!(((os_ubase_t)(addr1) & (BLOCK_SIZE -1)) || ((os_ubase_t)(addr2) & (BLOCK_SIZE -1))))
#define TOO_SMALL(len)                      ((len) < BLOCK_SIZE)

    char             *dst_tmp;
    const char       *src_tmp;
    os_ubase_t       *aligned_dst;
    const os_ubase_t *aligned_src;

    dst_tmp = (char *)dst;
    src_tmp = (const char *)src;

    if (!TOO_SMALL(count) && ADDR_BOTH_ALIGNED(src_tmp, dst_tmp))
    {
        aligned_dst = (os_ubase_t *)dst_tmp;
        aligned_src = (const os_ubase_t *)src_tmp;

        while (count >= BLOCK_SIZE)
        {
            *aligned_dst = *aligned_src;
            aligned_dst++;
            aligned_src++;
            count -= BLOCK_SIZE;
        }
        
        dst_tmp = (char *)aligned_dst;
        src_tmp = (const char *)aligned_src; 
    }

    while (count--)
    {
        *dst_tmp = *src_tmp;
        dst_tmp++;
        src_tmp++;
    }

    return dst;
    
#undef BLOCK_SIZE
#undef ADDR_BOTH_ALIGNED
#undef TOO_SMALL
#endif
}

/**
 ***********************************************************************************************************************
 * @brief           This function will move memory content from source address to destination address.
 *
 * @param[out]      dst             The address of destination memory.
 * @param[in]       src             The address of source memory.
 * @param[in]       count           The copied length.
 *
 * @return          The address of destination memory.
 ***********************************************************************************************************************
 */
void *os_memmove(void *dst, const void *src, os_size_t count)
{
    char       *dst_tmp;
    const char *src_tmp;

    dst_tmp = (char *)dst;
    src_tmp = (const char *)src;

    /* Copy backwards */
    if ((dst_tmp > src_tmp) && (dst_tmp < src_tmp + count))
    {
        dst_tmp += count;
        src_tmp += count;

        while (count--)
        {
            dst_tmp--;
            src_tmp--;
            *dst_tmp = *src_tmp;
        }
    }
    /* Copy forwards */
    else
    {
        while (count--)
        {
            *dst_tmp = *src_tmp;
            dst_tmp++;
            src_tmp++;
        }
    }

    return dst;
}

/**
 ***********************************************************************************************************************
 * @brief           This function will compare two areas of memory.
 *
 * @param[in]       area1           One area of memory.
 * @param[in]       area2           Another area of memory.
 * @param[in]       count           The size of the area.
 *
 * @return          The compared result.
 * @retval          0               Two areas are equal.
 * @retval          else            Two areas are not equal.
 ***********************************************************************************************************************
 */
os_int32_t os_memcmp(const void *area1, const void *area2, os_size_t count)
{
    const os_uint8_t *area1_tmp;
    const os_uint8_t *area2_tmp;
    os_int32_t       ret;

    area1_tmp = (const os_uint8_t *)area1;
    area2_tmp = (const os_uint8_t *)area2;
    ret = 0;

    for ( ; count > 0; area1_tmp++, area2_tmp++, count--)
    {
        ret = *area1_tmp - *area2_tmp;
        if (ret != 0)
        {
            break;
        }
    }

    return ret;
}

/**
 ***********************************************************************************************************************
 * @brief           Copy a '\0' terminated string.
 *
 * @param[out]      dst             The address of destination string where to copy the string to.
 * @param[in]       src             The address of source memory where to copy the string from.
 *
 * @return          TThe address of destination string. 
 ***********************************************************************************************************************
 */
char *os_strcpy(char *dst, const char *src)
{
    char *dst_tmp;

    dst_tmp = dst;
    while (1)
    {
        *dst_tmp = *src;
        if (*dst_tmp != '\0')
        {
            dst_tmp++;
            src++;
        }
        else
        {
            break;
        }
    }

    return dst;
}

/**
 ***********************************************************************************************************************
 * @brief           This function will copy string no more than count bytes.
 *
 * @param[out]      dst             The address of destination string where to copy the string to.
 * @param[in]       src             The address of source memory where to copy the string from.
 * @param[in]       count           The maximum copied length.
 *
 * @return          TThe address of destination string. 
 ***********************************************************************************************************************
 */
char *os_strncpy(char *dst, const char *src, os_size_t count)
{
    char *dst_tmp;

    for (dst_tmp = dst; (count > 0) && (*src != '\0'); count--)
    {
        *dst_tmp = *src;
        dst_tmp++;
        src++;
    }

    for ( ; count > 0; count--)
    {
        *dst_tmp = '\0';
        dst_tmp++;
    }

    return dst;
}

/**
 ***********************************************************************************************************************
 * @brief           This function will compare two strings without specified length.
 *
 * @param[in]       str1            One string to be compared.
 * @param[in]       str2            Another string to be compared.
 *
 * @return          The result.
 * @retval          0               Two strings are equal.
 * @retval          else            Two strings are not equal.
 ***********************************************************************************************************************
 */
os_int32_t os_strcmp(const char *str1, const char *str2)
{
    os_uint8_t value1;
    os_uint8_t value2;
    
    for ( ; *str1 == *str2; str1++, str2++)
    {
        if (*str1 == '\0')
        {
            return 0;
        }
    }

    value1 = *((const os_uint8_t *)str1);
    value2 = *((const os_uint8_t *)str2);
    
    return (value1 - value2);
}

/**
 ***********************************************************************************************************************
 * @brief           This function will compare two strings with specified length.
 *
 * @param[in]       str1            One string to be compared.
 * @param[in]       str2            Another string to be compared.
 * @param[in]       count           The maximum compare length.
 *
 * @return          The result.
 * @retval          0               Two strings are equal.
 * @retval          else            Two strings are not equal.
 ***********************************************************************************************************************
 */
os_int32_t os_strncmp(const char *str1, const char *str2, os_size_t count)
{
    os_uint8_t value1;
    os_uint8_t value2;

    for ( ; count > 0; str1++, str2++, count--)
    {
        if (*str1 != *str2)
        {
            value1 = *((const os_uint8_t *)str1);
            value2 = *((const os_uint8_t *)str2);

            return (value1 - value2);
        }
        else if (*str1 == '\0')
        {
            return 0;
        }
    }

    return 0;
}

/**
 ***********************************************************************************************************************
 * @brief           This function will return the length of a string, which terminate will '\0' character.
 *
 * @param[in]       str             The string.
 *
 * @return          The length of string.
 ***********************************************************************************************************************
 */
os_size_t os_strlen(const char *str)
{
    const char *str_tmp;

    for (str_tmp = str; *str_tmp != '\0'; str_tmp++)
    {
        ;
    }
    
    return (str_tmp - str);
}

/**
 ***********************************************************************************************************************
 * @brief           The os_strnlen() function returns the number of characters in the string pointed to by str, 
 *                  excluding the terminating null byte ('\0'), but at most maxlen. In doing this, os_strnlen() looks 
 *                  only at the first maxlen characters in the string pointed to by str and never beyond (str + max_len).
 *
 * @param[in]       str             The string.
 * @param[in]       max_len         The max size.
 *
 * @return          The length of string.
 ***********************************************************************************************************************
 */
os_size_t os_strnlen(const char *str, os_size_t max_len)
{
    const char *str_tmp;

    for (str_tmp = str; (*str_tmp != '\0') && (str_tmp - str < max_len); str_tmp++)
    {
        ;
    }
    
    return (str_tmp - str);
}
#if defined(__CC_ARM) || defined(__CLANG_ARM)
os_size_t strnlen(const char *str, os_size_t max_len) __attribute__((alias("os_strnlen")));
#endif

/**
 ***********************************************************************************************************************
 * @brief           This function will return the first occurrence of a char.
 *
 * @param[in]       str             The source string.
 * @param[in]       ch              The char to be found.
 *
 * @return          The first occurrence of a char(ch) in str.
 * @retval          OS_NULL         No found a char(ch) in str.
 * @retval          else            The first occurrence of a char(ch) in str.
 ***********************************************************************************************************************
 */
char *os_strchr(const char *str, char ch)
{
    for ( ; *str != ch; str++)
    {
        if (*str == '\0')
        {
            return OS_NULL;
        }
    }

    return (char *)str;
}

/**
 ***********************************************************************************************************************
 * @brief           This function will return the first occurrence of a string.
 *
 * @param[in]       str1            The source string.
 * @param[in]       str2            The string to be found.
 *
 * @return          The first occurrence of a str2 in str1.
 * @retval          OS_NULL         No found str2 in str1.
 * @retval          else            The first occurrence of a str2 in str1.
 ***********************************************************************************************************************
 */
char *os_strstr(const char *str1, const char *str2)
{
    os_size_t str1_len;
    os_size_t str2_len;

    str2_len = os_strlen(str2);
    if (!str2_len)
    {
        return (char *)str1;
    }
    
    str1_len = os_strlen(str1);
    while (str1_len >= str2_len)
    {
        if (!os_memcmp(str1, str2, str2_len))
        {
            return (char *)str1;
        }
        
        str1++;
        str1_len--;
    }

    return OS_NULL;
}

#ifdef OS_USING_HEAP
/**
 ***********************************************************************************************************************
 * @brief           This function will duplicate a string.
 *
 * @param[in]       str             The string to be duplicated
 *
 * @return          The duplicated string pointer.
 * @retval          OS_NULL         Duplicate string failed.
 * @retval          else            Duplicate string success.
 ***********************************************************************************************************************
 */
char *os_strdup(const char *str)
{
    os_size_t  len;
    char      *str_tmp;

    len = os_strlen(str) + 1;
    str_tmp = (char *)os_malloc(len);
    if (!str_tmp)
    {
        return OS_NULL;
    }

    os_memcpy(str_tmp, str, len);

    return str_tmp;
}

EXPORT_SYMBOL(os_strdup);
#if defined(__CC_ARM) || defined(__CLANG_ARM)
char *strdup(const char *s) __attribute__((alias("os_strdup")));
#endif
#endif /* OS_USING_HEAP */

 /**
 ***********************************************************************************************************************
 * @brief           This function sets a hook function called at the beginning of os_assert_handler.
 *
 * @param[in]       hook            The hook function is complemented by user.
 *
 * @return          None
 ***********************************************************************************************************************
 */
void os_assert_set_hook(void (*hook)(const char *ex_string, const char *func, os_int32_t line))
{
    os_assert_hook = hook;
}

/**
 ***********************************************************************************************************************
 * @brief           The OS_ASSERT function.
 *
 * @param[in]       ex_string       The assertion condition string.
 * @param[in]       func            The function name when assertion.
 * @param[in]       line            The file line number when assertion.
 *
 * @return          No return value.
 ***********************************************************************************************************************
 */
void os_assert_handler(const char *ex_string, const char *func, os_int32_t line)
{
    if(OS_NULL == os_assert_hook)
    {
#ifdef OS_USING_MODULE
        if (os_module_self())
        {
            /* close assertion module */
            os_module_exit(-1);
        }
        else
#endif
        {
            os_kprintf("(%s) assertion failed at function: %s, line number: %d \r\n", ex_string, func, line);

            while (1)
            {
                ;
            }
        }
    }
    else
    {
        os_assert_hook(ex_string, func, line);
    }
}

/* Private function */
#define isdigit(c)          ((unsigned int)((c) - '0') < 10)

OS_INLINE int divide(long long *n, int base)
{
    int res;

    /* Optimized for processor which does not support divide instructions. */
    if (10 == base)
    {
        res = (int)(((unsigned long long)(*n)) % 10U);
        *n  = (long long)(((unsigned long long)(*n)) / 10U);
    }
    else
    {
        res = (int)(((unsigned long long)(*n)) % base);
        *n  = (long long)(((unsigned long long)(*n)) / base);
    }

    return res;
}

OS_INLINE int skip_atoi(const char **s)
{
    register int i = 0;
    
    while (isdigit(**s))
    {
        i = i * 10 + *((*s)++) - '0';
    }
    
    return i;
}

#define ZEROPAD     (1 << 0)    /* Pad with zero */
#define SIGN        (1 << 1)    /* Unsigned/signed long */
#define PLUS        (1 << 2)    /* Show plus */
#define SPACE       (1 << 3)    /* Space if plus */
#define LEFT        (1 << 4)    /* Left justified */
#define SPECIAL     (1 << 5)    /* 0x */
#define LARGE       (1 << 6)    /* Use 'ABCDEF' instead of 'abcdef' */

static char *print_number(char      *buf,
                          char      *end,
                          long long num,
                          int       base,
                          int       s,
                          int       precision,
                          int       type)
{
    char              c;
    char              sign;
    char              tmp[32];
    int               precision_bak;
    const char        *digits;
    static const char small_digits[] = "0123456789abcdef";
    static const char large_digits[] = "0123456789ABCDEF";
    register int      i;
    register int      size;

    precision_bak = precision;
    size          = s;

    digits = (type & LARGE) ? large_digits : small_digits;
    if (type & LEFT)
    {
        type &= ~ZEROPAD;
    }
    
    c = (type & ZEROPAD) ? '0' : ' ';

    /* Get sign */
    sign = 0;
    if (type & SIGN)
    {
        if (num < 0)
        {
            sign = '-';
            num  = -num;
        }
        else if (type & PLUS)
        {
            sign = '+';
        }
        else if (type & SPACE)
        {
            sign = ' ';
        }
    }

    if (type & SPECIAL)
    {
        if (base == 16)
        {
            size -= 2;
        }
        else if (base == 8)
        {
            size--;
        }
    }

    i = 0;
    if (num == 0)
    {
        tmp[i++] = '0';
    }
    else
    {
        while (num != 0)
        {
            tmp[i++] = digits[divide(&num, base)];
        }
    }

    if (i > precision)
    {
        precision = i;
    }
    size -= precision;

    if (!(type & (ZEROPAD | LEFT)))
    {
        if ((sign) && (size > 0))
        {
            size--;
        }
        
        while (size-- > 0)
        {
            if (buf < end)
            {
                *buf = ' ';
            }
            
            ++buf;
        }
    }

    if (sign)
    {
        if (buf < end)
        {
            *buf = sign;
        }
        
        --size;
        ++buf;
    }

    if (type & SPECIAL)
    {
        if (base == 8)
        {
            if (buf < end)
            {
                *buf = '0';
            }
            
            ++buf;
        }
        else if (base == 16)
        {
            if (buf < end)
            {
                *buf = '0';
            }
            ++buf;

            if (buf < end)
            {
                *buf = type & LARGE ? 'X' : 'x';
            }
            ++buf;
        }
    }

    /* No align to the left */
    if (!(type & LEFT))
    {
        while (size-- > 0)
        {
            if (buf < end)
            {
                *buf = c;
            }
            
            ++buf;
        }
    }

    while (i < precision--)
    {
        if (buf < end)
        {
            *buf = '0';
        }
        
        ++buf;
    }

    /* Put number in the temporary buffer */
    while ((i-- > 0) && (precision_bak != 0))
    {
        if (buf < end)
        {
            *buf = tmp[i];
        }
        ++buf;
    }

    while (size-- > 0)
    {
        if (buf < end)
        {
            *buf = ' ';
        }
        ++buf;
    }

    return buf;
}

/**
 ***********************************************************************************************************************
 * @brief           This function will fill a formatted string to buffer.
 *
 * @param[out]      buf             The buffer to save formatted string.
 * @param[in]       size            The size of buffer.
 * @param[in]       fmt             The format.
 * @param[in]       args            The arguments.
 *
 * @return          The length of filling string to buffer.
 * @retval          >= 0            The actual fill length.
 * @retval          < 0             Fill buffer failed.
 ***********************************************************************************************************************
 */
os_int32_t os_vsnprintf(char *buf, os_size_t size, const char *fmt, va_list args)
{
    unsigned long long num;
    int i;
    int len;
    char *str;
    char *end;
    char c;
    const char *s;

    os_uint8_t base;            /* The base of number */
    os_uint8_t flags;           /* Flags to print number */
    os_uint8_t qualifier;       /* 'h', 'l', or 'L' for integer fields */
    os_int32_t field_width;     /* Width of output field */
    int precision;              /* min. # of digits for integers and max for a string */

    str = buf;
    end = buf + size;

    /* Make sure end is always >= buf */
    if (end < buf)
    {
        end  = ((char *) - 1);
        size = end - buf;
    }

    for ( ; *fmt; ++fmt)
    {
        if (*fmt != '%')
        {
            if (str < end)
            {
                *str = *fmt;
            }
            ++str;
            
            continue;
        }

        /* Process flags */
        flags = 0;
        while (1)
        {
            /* Skips the first '%' also */
            ++fmt;
            if (*fmt == '-')
            {
                flags |= LEFT;
            }
            else if (*fmt == '+')
            {
                flags |= PLUS;
            }
            else if (*fmt == ' ')
            {
                flags |= SPACE;
            }
            else if (*fmt == '#')
            {
                flags |= SPECIAL;
            }
            else if (*fmt == '0')
            {
                flags |= ZEROPAD;
            }
            else
            {
                break;
            }
        }

        /* Get field width */
        field_width = -1;
        if (isdigit(*fmt))
        {
            field_width = skip_atoi(&fmt);
        }
        else if (*fmt == '*')
        {
            ++fmt;
            
            /* It's the next argument */
            field_width = va_arg(args, int);
            if (field_width < 0)
            {
                field_width = -field_width;
                flags |= LEFT;
            }
        }

        /* Get the precision */
        precision = -1;
        if (*fmt == '.')
        {
            ++fmt;
            if (isdigit(*fmt))
            {
                precision = skip_atoi(&fmt);
            }
            else if (*fmt == '*')
            {
                ++fmt;
                
                /* It's the next argument */
                precision = va_arg(args, int);
            }
            
            if (precision < 0)
            {
                precision = 0;
            }
        }
        
        /* Get the conversion qualifier */
        qualifier = 0;
        if ((*fmt == 'h') || (*fmt == 'l') || (*fmt == 'L'))
        {
            qualifier = *fmt;
            ++fmt;
            
            if ((qualifier == 'l') && (*fmt == 'l'))
            {
                qualifier = 'L';
                ++fmt;
            }
        }

        /* The default base */
        base = 10;

        switch (*fmt)
        {
        case 'c':
            if (!(flags & LEFT))
            {
                while (--field_width > 0)
                {
                    if (str < end)
                    {
                        *str = ' ';
                    }
                    
                    ++str;
                }
            }

            /* Get character */
            c = (os_uint8_t)va_arg(args, int);
            if (str < end)
            {
                *str = c;
            }
            ++str;

            /* Put width */
            while (--field_width > 0)
            {
                if (str < end)
                {
                    *str = ' ';
                }
                ++str;
            }
            
            continue;
        case 's':
            s = va_arg(args, char *);
            if (!s)
            {
                s = "(NULL)";
            }
            
            len = os_strlen(s);
            if (precision > 0 && len > precision)
            {
                len = precision;
            }
            
            if (!(flags & LEFT))
            {
                while (len < field_width--)
                {
                    if (str < end)
                    {
                        *str = ' ';
                    }
                    ++str;
                }
            }

            for (i = 0; i < len; ++i)
            {
                if (str < end)
                {
                    *str = *s;
                }
                
                ++str;
                ++s;
            }

            while (len < field_width--)
            {
                if (str < end)
                {
                    *str = ' ';
                }
                ++str;
            }
            
            continue;
        case 'p':
            if (field_width == -1)
            {
                field_width = sizeof(void *) << 1;
                flags       |= ZEROPAD;
            }

            str = print_number(str,
                               end,
                               (long)va_arg(args, void *),
                               16,
                               field_width,
                               precision,
                               flags);

            continue;
        case '%':
            if (str < end)
            {
                *str = '%';
            }
            ++str;
            
            continue;
        /* Integer number formats - set up the flags and "break" */
        case 'o':
            base = 8;
            break;
            
        case 'X':
            flags |= LARGE;
        case 'x':
            base = 16;
            break;

        case 'd':
        case 'i':
            flags |= SIGN;
        case 'u':
            break;

        default:
            if (str < end)
            {
                *str = '%';
            }
            ++str;

            if (*fmt)
            {
                if (str < end)
                {
                    *str = *fmt;
                }
                ++str;
            }
            else
            {
                --fmt;
            }
            
            continue;
        }

        if (qualifier == 'L')
        {
            num = va_arg(args, long long);
        }
        else if (qualifier == 'l')
        {
            num = va_arg(args, os_uint32_t);
            if (flags & SIGN)
            {
                num = (os_int32_t)num;
            }
        }
        else if (qualifier == 'h')
        {
            num = (os_uint16_t)va_arg(args, os_int32_t);
            if (flags & SIGN)
            {
                num = (os_int16_t)num;
            }
        }
        else
        {
            num = va_arg(args, os_uint32_t);
            if (flags & SIGN)
            {
                num = (os_int32_t)num;
            }
        }

        str = print_number(str, end, num, base, field_width, precision, flags);
    }

    if (size > 0)
    {
        if (str < end)
        {
            *str = '\0';
        }
        else
        {
            end[-1] = '\0';
        }
    }

    /* The trailing null byte doesn't count towards the total ++str;*/
    return str - buf;
}
EXPORT_SYMBOL(os_vsnprintf);

/**
 ***********************************************************************************************************************
 * @brief           This function will fill a formatted string to buffer.
 *
 * @param[out]      buf             The buffer to save formatted string.
 * @param[in]       size            The size of buffer.
 * @param[in]       fmt             The format.
 *
 * @return          The length of filling string to buffer.
 * @retval          >= 0            The actual fill length.
 * @retval          < 0             Fill buffer failed.
 ***********************************************************************************************************************
 */
os_int32_t os_snprintf(char *buf, os_size_t size, const char *fmt, ...)
{
    os_int32_t n;
    va_list    args;

    va_start(args, fmt);
    n = os_vsnprintf(buf, size, fmt, args);
    va_end(args);

    return n;
}
EXPORT_SYMBOL(os_snprintf);

#ifndef OS_USING_CPU_FFS
const os_uint8_t gs_lowest_bit_bitmap[] =
{
    /* 00 */ 0, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 10 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 20 */ 5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 30 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 40 */ 6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 50 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 60 */ 5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 70 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 80 */ 7, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 90 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* A0 */ 5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* B0 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* C0 */ 6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* D0 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* E0 */ 5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* F0 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0
};

/**
 ***********************************************************************************************************************
 * @brief           This function finds the first bit set (beginning with the least significant bit) in value and 
 *                  return the index of that bit.
 *
 * @details         Bits are numbered starting at 1 (the least significant bit).  A return value of zero from any of 
 *                  these functions means that the argument(value) was zero.
 *
 * @param[in]       value           The value to be found the first bit set.
 *
 * @return          The index of first bit set.
 ***********************************************************************************************************************
 */
os_int32_t os_find_first_bit_set(os_int32_t value)
{
    if (value == 0)
    {
        return 0;
    }
    
    if (value & 0xff)
    {
        return gs_lowest_bit_bitmap[value & 0xff] + 1;
    }
    
    if (value & 0xff00)
    {
        return gs_lowest_bit_bitmap[(value & 0xff00) >> 8] + 9;
    }
    
    if (value & 0xff0000)
    {
        return gs_lowest_bit_bitmap[(value & 0xff0000) >> 16] + 17;
    }
    
    return gs_lowest_bit_bitmap[(value & 0xff000000) >> 24] + 25;
}
#endif /* OS_USING_CPU_FFS */

