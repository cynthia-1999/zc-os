//
// Created by zc on 23-4-5.
//

#include "../include/linux/tty.h"
#include "../include/linux/kernel.h"
#include "../include/linux/traps.h"
#include "../include/linux/memory.h"
#include "../include/asm/system.h"
#include "../include/linux/task.h"
#include "../include/linux/sched.h"

void kernel_main(void) {
    console_init();
    gdt_init();
    idt_init();
    init_timer();

    printk("zc_os\n");

    print_memory_info();
    memory_init();
    memory_map_init();

    virtual_memory_init();

    task_init();

    sched();

    __asm__("sti;");

    //int i = 10 / 0;
    while (true);
}