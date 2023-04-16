//
// Created by zc on 23-4-16.
//
#include "../../include/linux/kernel.h"
#include "../../include/linux/traps.h"

void clock_handler(int idt_index) {
    //send_eoi(idt_index);

    printk("clock handler: 0x%x\n", idt_index);
}