//
// Created by zc on 23-4-5.
//

#ifndef ZC_OS_TRAPS_H
#define ZC_OS_TRAPS_H

#include "head.h"

void gdt_init();

void idt_init();

void init_timer();

void write_xdt_ptr(xdt_ptr_t* p, short limit, int base);

#endif //ZC_OS_TRAPS_H
