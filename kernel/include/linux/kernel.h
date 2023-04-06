//
// Created by zc on 23-4-5.
//

#ifndef ZC_OS_KERNEL_H
#define ZC_OS_KERNEL_H

#include "../stdarg.h"

int vsprintf(char *buf, const char *fmt, va_list args);

int printk(const char * fmt, ...);

#endif //ZC_OS_KERNEL_H
