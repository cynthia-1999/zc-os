//
// Created by zc on 23-4-5.
//

#ifndef ZC_OS_STDARG_H
#define ZC_OS_STDARG_H

typedef char* va_list;

#define va_start(p, count) (p = (va_list)&count + sizeof(char*))    // p指向第一个参数
#define va_arg(p, t) (*(t*)((p += sizeof(char*)) - sizeof(char*)))  // 取当前参数，同时将p移到下一个参数
#define va_end(p) (p = 0)

#endif //ZC_OS_STDARG_H
