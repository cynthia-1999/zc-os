//
// Created by zc on 23-4-5.
//

#include "../include/linux/tty.h"
#include "../include/linux/kernel.h"
#include "../include/linux/traps.h"

void kernel_main(void) {
    console_init();
    gdt_init();

    printk("zc_os");

    while (true);
}