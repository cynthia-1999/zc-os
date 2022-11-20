//
// Created by zc on 22-11-8.
//

#ifndef ZC_OS_COMMON_H
#define ZC_OS_COMMON_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>

/*===================================
 * Log Classification
 ===================================*/

#define LOG_INFO        0
#define LOG_WARNING     1
#define LOG_DEBUG       2
#define LOG_ERROR       3

#define DEBUG
#define DEBUG_LEVEL LOG_INFO

#define PRINT(info, ...) do{\
    print("[Info](%s:%d->%s):" info"", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__);\
}while(0)

#define PRINT_INFO(info, ...) do{ \
    if(DEBUG_LEVEL <= LOG_INFO){ \
    print("[Info](%s:%d->%s):" info"", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__);\
    }\
}while(0)

#define PRINT_WAINING(info, ...) do{ \
    if(DEBUG_LEVEL <= LOG_WARNING){ \
    print("[Warning](%s:%d->%s):" info "", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__);\
    }\
}while(0)

#define PRINT_DEBUG(info, ...) do{ \
    if(DEBUG_LEVEL <= LOG_DEBUG){ \
    print("[Debug](%s:%d->%s):" info"", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__);\
    }\
}while(0)

#define PRINT_ERROR(info, ...) do{ if(DEBUG_LEVEL <= LOG_ERROR){ printf("[Error] (%s:%d->%s):" info"", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__); } }while(0)

#define assert(cond, msg){if (!cond){fprintf(stderr, "assert fails %s %d: %s \n", __FILE__, __LINE__, msg); abort();}}

#define WRITE(str) do{ \
    write(STDOUT_FILENO, str, strlen(str));\
}while(0)

#define ASSERT_ZERO(status, str) do{ \
    if(0 != status){                 \
        WRITE(str);                  \
        exit(-1);                    \
    }\
}while(0)
#endif //ZC_OS_COMMON_H

