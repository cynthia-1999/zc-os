//
// Created by zc on 2022/10/16.
//
#include "tools/fileinfo.h"
#include "tools/floppy.h"

int main() {

    char* boot_filepath = "/home/ziya/CLionProjects/zc-os/build/boot/boot.o";
    char* setup_filepath = "/home/ziya/CLionProjects/zc-os/build/boot/setup.o";

    Floppy* floppy = create_floppy();

    FileInfo * boot_fileinfo = readFile(boot_filepath);
    write_boot_loader(floppy, boot_fileinfo);

    FileInfo * setup_fileinfo = readFile(setup_filepath);
    write_floppy_fileinfo(floppy, setup_fileinfo, 0, 0, 2);

    create_image("/home/ziya/CLionProjects/zc-os/a.img", floppy);

    return 0;
}