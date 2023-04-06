//
// Created by zc on 23-4-5.
//

#include "../include/linux/tty.h"
#include "../include/linux/kernel.h"

void kernel_main(void) {
    console_init();

    char* s = "zc_os";

    for (int i = 0; i < 2048; ++i) {
        printk("name: %s, age:%d\n", s, i);
    }

    while (true);
}