//
// Created by zc on 23-4-20.
//

#include "../include/linux/memory.h"
#include "../include/asm/system.h"
#include "../include/linux/kernel.h"

#define ARDS_ADDR   0x1100
#define LOW_MEM     0x100000    // 1M以下物理内存给内核使用

#define ZONE_VALID      1   // ards 可用内存区域
#define ZONE_RESERVEd   2   // ards 不可用内存区域

void print_memory_info(){
    memory_info_t* p = (memory_info_t*)ARDS_ADDR;
    memory_info_item_t* p_data = (memory_info_item_t*)(ARDS_ADDR+2);

    unsigned short times = p->times;
    printk("times: %x\n", p->times);
    for(int i = 0; i < times; ++i){
        memory_info_item_t* tmp = p_data + i;
        printk("%x, %x, %x, %x, %d \n", tmp->base_addr_low, tmp->base_addr_high, tmp->length_low, tmp->length_high,
               tmp->type);
    }
}