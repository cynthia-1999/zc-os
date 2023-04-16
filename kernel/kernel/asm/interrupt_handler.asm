[bits 32]
[SECTION .text]

extern printk

global interrupt_handler
interrupt_handler:
    push msg
    call printk
    add esp, 4

    iret ; 将程序从终端处理程序返回到被异常、外部中断或软件生成中断的程序或过程

msg:
    db "interrupt_handler", 10, 0
