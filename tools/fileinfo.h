//
// Created by zc on 22-11-8.
//

#ifndef ZC_OS_FILEINFO_H
#define ZC_OS_FILEINFO_H


typedef struct{
    char* name;
    int size;
    char* content;
}FileInfo;

FileInfo* readFile(char* file);

#endif //ZC_OS_FILEINFO_H
