[SECTION .text]
[BITS 32]
extern kernel_main

global _start

_start:
; 配置8259a芯片，响应中断用
.config_8259a:
    ; 向主发送ICW1
    mov al, 11h ;0001 0001
    out 20h, al

    ; 向从发送ICW1
    out 0a0h, al

    ; 向主发送ICW2
    mov al, 20h ;0010 0000
    out 21h, al

    ; 向从发送ICW2
    mov al, 28h ;0010 1000
    out 0a1h, al

    ; 向主发送ICW3
    mov al, 04h ;0000 0100
    out 21h, al

    ; 向从发送ICW3
    mov al, 02h ;0000 0010
    out 0A1h , al

    ; 向主发送ICW4
    mov al, 03h  ;0000 0011(自动EIO）
    out 021h, al

    ; 向从发送ICW4
    out 0A1h, al

;屏蔽所有中断，只接收键盘中断和时钟中断
    mov al, 11111100b
    out 21h, al

;屏蔽从芯片所有中断
    mov al, 11111111b
    out 0A1h, al

;调用C程序
    call kernel_main
    jmp $