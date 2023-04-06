//
// Created by zc on 23-4-5.
//

#ifndef ZC_OS_IO_H
#define ZC_OS_IO_H

char in_byte(int port);
short in_word(int port);

void out_byte(int port, int v);
void out_word(int port, int v);

#endif //ZC_OS_IO_H
