//
// Created by zc on 23-4-5.
//

#ifndef ZC_OS_TTY_H
#define ZC_OS_TTY_H

#include "types.h"

void console_init(void);
void console_write(char *buf, u32 count);

#endif //ZC_OS_TTY_H
