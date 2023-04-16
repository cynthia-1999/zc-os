//
// Created by zc on 23-4-16.
//
#include "../include/linux/traps.h"

void write_xdt_ptr(xdt_ptr_t* p, short limit, int base) {
    p->limit = limit;
    p->base = base;
}