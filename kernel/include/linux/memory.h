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

void print_memory_info();

#endif //ZC_OS_MEMORY_H
