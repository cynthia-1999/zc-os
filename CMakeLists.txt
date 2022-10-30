cmake_minimum_required(VERSION 3.5.1)
project(zc_os)

set(CMAKE_CXX_STANDARD 14)

add_executable(zc_os main.c tools/floppy.c tools/fileinfo.c)