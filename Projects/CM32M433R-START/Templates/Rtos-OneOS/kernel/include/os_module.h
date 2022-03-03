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
 * @file        os_module.h
 *
 * @brief       Header file for module interface.
 *
 * @revision
 * Date         Author          Notes
 * 2020-06-20   OneOS Team      First Version
 ***********************************************************************************************************************
 */
#ifndef __OS_MODULE_H__
#define __OS_MODULE_H__

#include <oneos_config.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef OS_USING_MODULE

struct os_module_symtab
{
    void       *addr;
    const char *name;
};

#define EXPORT_SYMBOL(symbol)                                            \
const char __osmsym_##symbol##_name[] OS_SECTION(".rodata.name") = #symbol;     \
OS_USED const struct os_module_symtab __osmsym_##symbol OS_SECTION("MSymTab")= \
{                                                                     \
    (void *)&symbol,                                                  \
    __osmsym_##symbol##_name                                          \
};

#else
#define EXPORT_SYMBOL(symbol)
#endif

#ifdef OS_USING_MODULE
#include <os_task.h>
#define OS_MODULE_STAT_INIT       0x00
#define OS_MODULE_STAT_RUNNING    0x01
#define OS_MODULE_STAT_CLOSING    0x02
#define OS_MODULE_STAT_CLOSED     0x03

struct os_module;

typedef void (*os_module_init_func_t)(struct os_module *module);
typedef void (*os_module_cleanup_func_t)(struct os_module *module);
typedef int  (*os_module_entry_func_t)(int argc, char** argv);

struct os_module
{
    struct os_object parent;
    os_list_node_t   object_list;  /* objects inside this module */

    os_uint8_t stat;        /* status of module */

    /* main task of this module */
    os_uint16_t     priority;
    os_uint32_t     stack_size;
    struct os_task *main_task;
    /* the return code */
    int             ret_code;

    /* VMA base address for the first LOAD segment */
    os_uint32_t vstart_addr;

    /* module entry, RT_NULL for dynamic library */
    os_module_entry_func_t  entry_addr;
    char *cmd_line;         /* command line */

    void       *mem_space;  /* memory space */
    os_uint32_t mem_size;   /* sizeof memory space */

    /* init and clean function */
    os_module_init_func_t     init_func;
    os_module_cleanup_func_t  cleanup_func;

    os_uint16_t nref;       /* reference count */

    os_uint16_t nsym;       /* number of symbols in the module */
    struct os_module_symtab *symtab;    /* module symbol table */
};

extern struct os_module *os_module_find(const char *name);
extern struct os_module *os_module_create(void);
extern struct os_module *os_module_self(void);

extern void         os_module_set_name(struct os_module *module, const char *path);
extern os_err_t     os_module_destroy(struct os_module *module);
extern void         os_module_stop_child_task(void);
extern os_uint32_t  os_module_symbol_find(const char *sym_str);

void os_module_exit(int ret_code);


#endif

#ifdef __cplusplus
}
#endif

#endif /* __OS_MODULE_H__ */

