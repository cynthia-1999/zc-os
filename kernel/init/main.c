//
// Created by zc on 23-4-5.
//

#include "../include/linux/tty.h"
#include "../include/linux/kernel.h"
#include "../include/linux/traps.h"
#include "../include/linux/memory.h"
#include "../include/asm/system.h"

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

    void *p = kmalloc(1);
    printk("0x%p\n", p);
    void* p1 = kmalloc(2);
    printk("0x%p\n", p1);
    kfree_s(p, 1);

    __asm__("sti;");

    //int i = 10 / 0;
    while (true);
}