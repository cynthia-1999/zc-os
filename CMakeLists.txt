cmake_minimum_required(VERSION 3.5.1)
project(zc_os)

set(CMAKE_CXX_STANDARD 14)

add_executable(zc_os main.c tools/fileinfo.c tools/floppy.c kernel/init/main.c kernel/lib/string.c kernel/include/stdarg.h kernel/include/string.h kernel/include/asm/io.h kernel/include/asm/system.h kernel/include/linux/kernel.h kernel/include/linux/tty.h kernel/include/linux/types.h kernel/kernel/chr_drv/console.c kernel/kernel/printk.c kernel/kernel/vsprintf.c kernel/include/linux/head.h kernel/include/linux/traps.h kernel/kernel/gdt.c kernel/kernel/idt.c kernel/kernel/traps.c kernel/kernel/chr_drv/keyboard.c kernel/kernel/exception.c kernel/kernel/chr_drv/clock.c)