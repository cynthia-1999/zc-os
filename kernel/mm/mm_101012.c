//
// Created by zc on 23-5-2.
//
#include "../include/linux/memory.h"
#include "../include/asm/system.h"
#include "../include/linux/kernel.h"
#include "../include/string.h"

/**
 * 一个pdt 4k 0x1000
 * 4g内存需要的页表：(0x1000/4)* (0x1000/4) * 0x1000
 * @return
 */

// 页表从0x20000开始存
#define PDT_START_ADDR 0x20000

// 线性地址从2M开始用
#define VIRTUAL_MEM_START 0x200000

void* virtual_memory_init(){
    // 分配页目录表内存
    int* pdt = (int*)PDT_START_ADDR;

    // 清0
    memset(pdt, 0, PAGE_SIZE);

    //设置页目录表的四个表项
    for(int i = 0; i < 4; ++i){
        //分配pde对应的页表
        int ptt = (int)PDT_START_ADDR + (i+1) * 0x1000;
        // pdt里面的每项，即pde，内容是ptt + 尾12位的权限位
        int pde = 0b00000000000000000000000000000111 | ptt;

        pdt[i] = pde;

        int *ptt_arr = (int*)ptt;
        if(i == 0){
            // 第一块映射区，给内核用
            for(int j = 0; j < 0x400; ++j){
                int* item = &ptt_arr[j];

                int virtual_addr = j * 0x1000;
                *item = 0b00000000000000000000000000000111 | virtual_addr;
            }
        }
        // 暂时还没用到
        else{
            for(int j = 0; j < 0x400; ++j){
                int *item = &ptt_arr[j];

                int virtual_addr = j * 0x1000;
                virtual_addr = virtual_addr + i * 0x400 * 0x1000;
                *item = 0b00000000000000000000000000000111 | virtual_addr;
            }
        }
    }

    BOCHS_DEBUG_MAGIC

    // 设置cr3寄存器
    set_cr3((uint)pdt);

    // 开启分页
    enable_page();

    BOCHS_DEBUG_MAGIC

    return pdt;
}
