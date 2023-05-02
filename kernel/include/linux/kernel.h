//
// Created by zc on 23-4-5.
//

#ifndef ZC_OS_KERNEL_H
#define ZC_OS_KERNEL_H

#include "../stdarg.h"
#include "types.h"

int vsprintf(char *buf, const char *fmt, va_list args);

int printk(const char * fmt, ...);

uint get_cr3();
void set_cr3(uint v);
void enable_page();

#endif //ZC_OS_KERNEL_H
