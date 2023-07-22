//
// Created by zc on 23-4-16.
//
#include "../../include/linux/kernel.h"
#include "../../include/linux/traps.h"
#include "../../include/asm/io.h"
#include "../../include/asm/system.h"
#include "../../include/linux/sched.h"

#define IRQ0_FREQUENCY  100
#define INPUT_FREQUENCY 1193180
#define COUNTER0_VALUE  INPUT_FREQUENCY/IRQ0_FREQUENCY
#define COUNTER0_PORT   0X40
#define COUNTER0_NO     0
#define COUNTER0_MODE   2
#define READ_WRITE_LATCH   3
#define PIT_CONTROL_PORT   0x43

// 通过对8253定时器进行设置，修改时钟中断的频率
// 把操作的计数器counter_no、读写锁属性rwl、计数器模式counter_mode写入模式控制寄存器并赋予初始值counter_value
void frequency_set(unsigned char counter_port, unsigned char counter_no, unsigned char rwl, unsigned char counter_mode, unsigned short counter_value){
    // 往控制字寄存器端口0x43中写入控制字
    out_byte(PIT_CONTROL_PORT, (unsigned char)(counter_no << 6 | rwl << 4 | counter_mode << 1));
    // 先写入counter_value的低8位
    out_byte(counter_port, (unsigned char)counter_value);
    // 再写入counter_value的高8位
    out_byte(counter_port, (unsigned char)(counter_value >> 8));
}

// 初始化PIT8253
void init_timer(){
    printk("init timer...\n");
    //设置8253的定时周期，也就是发生中断的周期
    frequency_set(COUNTER0_PORT, COUNTER0_NO, READ_WRITE_LATCH, COUNTER0_MODE, COUNTER0_VALUE);
    printk("init timer done...\n");
}

void clock_handler(int idt_index) {
    //send_eoi(idt_index);

    printk("clock handler: 0x%x\n", idt_index);

    do_timer();
}