//
// Created by zc on 23-4-20.
//

#ifndef ZC_OS_MEMORY_H
#define ZC_OS_MEMORY_H

#include "types.h"

#define  PAGE_SIZE 4096

typedef struct{
    unsigned int base_addr_low;     //基地址的低32位
    unsigned int base_addr_high;    //基地址的高32位
    unsigned int length_low;        //内存长度的低32位
    unsigned int length_high;       //内存长度的高32位
    unsigned int type;              //本段内存的类型
}memory_info_item_t;

typedef struct{
    unsigned short  times;
    memory_info_item_t* data;
}memory_info_t;

// physics management
typedef struct{
    uint addr_start;        //可用内存起始地址 一般是1M
    uint addr_end;          //可用内存终止地址
    uint valid_mem_size;
    uint pages_total;       //机器物理地址共多少page
    uint pages_free;        //物理内存还剩多少page
    uint pages_used;        //物理内存用了多少page
}physics_memory_info_t;

typedef struct{
    uint addr_base;         //可用物理内存开始位置 3M
    uint pages_total;       //共有对少page 机器物理内存共多少page
    uint bitmap_item_used;  //如果1B映射一个page，共用了多少page
    uchar* map;
}physics_memory_map_t;
void print_memory_info();

void memory_init();
void memory_map_init();

void* virtual_memory_init();

// 分配、释放物理页
void* get_free_page();
void free_page(void* p);

// 分配、释放虚拟内存
void* kmalloc(size_t len);
void kfree_s(void *obj, int size);

#endif //ZC_OS_MEMORY_H
