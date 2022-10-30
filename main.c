//
// Created by zc on 2022/10/16.
//
#include "tools/fileinfo.h"
#include "tools/floppy.h"

int main(int argc, char** argv) {

    char* boot_filepath = "/home/ziya/CLionProjects/zc-os/build/boot/boot.o";
    //char* boot_filepath = argv[0];

    Floppy* floppy = create_floppy();

    Fileinfo* boot_fileinfo = read_file(boot_filepath);
    write_bootloader(floppy, boot_fileinfo);

    char* image_path = argv[1];
    create_image("/home/ziya/CLionProjects/zc-os/a.img", floppy);

    return 0;
}