//
// Created by zc on 22-11-10.
//

#ifndef ZC_OS_FLOPPY_H
#define ZC_OS_FLOPPY_H

#include "fileinfo.h"

typedef struct{
    int size;
    char* content;
}Floppy;

Floppy* create_floppy();

//向软盘的0柱面、0磁道的第一个扇区写入引导信息（boot_loader)
void write_boot_loader(Floppy* floppy, FileInfo* fileInfo);

//向软盘的face柱面、track磁道的第section个扇区中写入str信息。
void write_floppy(Floppy* floppy, char* str, int face, int track, int section);

//向软盘的face柱面、track磁道的第section个扇区中写入fileinfo文件信息。
void write_floppy_fileinfo(Floppy* floppy, FileInfo* fileInfo, int face, int track, int section);

//创建镜像
void create_image(char* name, Floppy* floppy);


#endif //ZC_OS_FLOPPY_H
