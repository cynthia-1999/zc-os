//
// Created by zc on 23-4-5.
//

#ifndef ZC_OS_HEAD_H
#define ZC_OS_HEAD_H

typedef struct gdt_item_t{
    unsigned short limit_low;      // 段界限 0 ~ 15 位
    unsigned int base_low : 24;    // 基地址 0 ~ 23 位 16M
    unsigned char type : 4;        // 段类型
    unsigned char segment : 1;     // 1 表示代码段或数据段，0 表示系统段
    unsigned char DPL : 2;         // Descriptor Privilege Level 描述符特权等级 0 ~ 3
    unsigned char present : 1;     // 存在位，1 在内存中，0 在磁盘上
    unsigned char limit_high : 4;  // 段界限 16 ~ 19;
    unsigned char available : 1;   // 该安排的都安排了，送给操作系统吧
    unsigned char long_mode : 1;   // 64 位扩展标志
    unsigned char big : 1;         // 32 位 还是 16 位;
    unsigned char granularity : 1; // 粒度 4KB（1） 或 1B（0）.
    unsigned char base_high;       // 基地址 24 ~ 31 位
} __attribute__((packed)) gdt_item_t;

typedef struct gdt_selector_t{
    char RPL : 2;
    char TI : 1;
    short index : 13;
} __attribute__((packed)) gdt_selector_t;

#pragma pack(2)
typedef struct rgdt_ptr_t{
    short   limit;
    unsigned long long int **base;    // 这个base需要大端存储，默认是小端存储
} rgdt_ptr_t;
#pragma pack()

#endif //ZC_OS_HEAD_H
