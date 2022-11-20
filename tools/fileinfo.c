//
// Created by zc on 22-11-10.
//
#include "common.h"
#include "fileinfo.h"

FileInfo* readFile(char* filename){
    if(!filename){
        return NULL;
    }

    FileInfo *file_info = calloc(1, sizeof(FileInfo));
    if(!file_info){
        perror("calloc failed.");
        exit(-1);
    }

    file_info->name = filename;

    FILE* file = fopen(filename, "rb");
    if(!file){
        perror("open file failed.");
        exit(-1);
    }

    if(fseek(file, 0, SEEK_END) != 0){
        perror("fseek failed.");
        exit(-1);
    }

    file_info->size = ftell(file);
    if(file_info->size == -1){
        perror("ftell error.");
        exit(-1);
    }

    //还原文件指针
    fseek(file, 0, SEEK_SET);
    file_info->content = calloc(1, file_info->size);

    if(!file_info->content){
        perror("file_info->content calloc failed.");
        exit(-1);
    }

    int size = fread(file_info->content, 1, file_info->size, file);
    if(size != file_info->size){
        perror("read file failed.");
        exit(-1);
    }

    fclose(file);
    return file_info;
}