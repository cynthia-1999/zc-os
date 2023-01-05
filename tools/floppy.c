//
// Created by zc on 22-11-10.
//

#include "floppy.h"
#include "common.h"

Floppy *create_floppy(){
    Floppy* floppy = calloc(sizeof(Floppy), 1);
    if(!floppy){
        perror("calloc falied.");
        return NULL;
    }

    floppy->size = 2 * 80 * 18 * 512;
    floppy->content = calloc(1, floppy->size);
    if(!floppy->content){
        perror("floppy->content calloc failed.");
        exit(-1);
    }
    return floppy;
}


void write_boot_loader(Floppy* floppy, FileInfo* fileInfo){
    if(floppy == NULL || fileInfo == NULL){
        PRINT_ERROR("null pointer.\n");
        exit(-1);
    }
    memcpy(floppy->content, fileInfo->content, fileInfo->size);
}

void write_floppy(Floppy* floppy, char* str, int face, int track, int section){
    if(floppy == NULL){
        PRINT_ERROR("null pointer.\n");
        exit(-1);
    }
    char* offset = floppy->content + face*80*18*512 + track*18*512 + (section-1)*512;
    memcpy(offset, str, strlen(str));
}

void write_floppy_fileinfo(Floppy* floppy, FileInfo* fileInfo, int face, int track, int section){
    if(floppy == NULL){
        PRINT_ERROR("null pointer.\n");
        exit(-1);
    }
    char* offset = floppy->content + face*80*18*512 + track*18*512 + (section-1)*512;
    memcpy(offset, fileInfo->content, fileInfo->size);
}

void create_image(char* name, Floppy* floppy){
    if(floppy == NULL){
        PRINT_ERROR("null pointer.\n");
        exit(-1);
    }
    FILE* file = fopen(name, "w+");
    if(!file){
        perror("file create failed.");
        exit(-1);
    }
    fwrite(floppy->content, 1, floppy->size, file);
}