[ORG  0x7c00]

[SECTION .text]
[BITS 16]
global _start
_start:
    ; 设置屏幕模式为文本模式，清除屏幕
    mov ax, 3
    int 0x10

    ;初始化段寄存器
    ;mov     ax, 0
    ;mov     ss, ax
    ;mov     ds, ax
    ;mov     es, ax
    ;mov     fs, ax
    ;mov     gs, ax
    ;mov     si, ax

    ;将msg传入si，调用print函数，
    mov     si, msg
    call    print

    jmp     $

; 如何调用
; mov     si, msg   ; 1 传入字符串
; call    print     ; 2 调用
print:
    mov ah, 0x0e    ;int10中断的设置，ah = 0x0e使显示器像打字机一样的显示字符出来
    mov bh, 0       ;设置当前的显示页，图形模式为下bh=0
    mov bl, 0x01    ;图形模式下，设置文字的颜色bl=0x01，文字模式下无作用
.loop:
    mov al, [si]    ;al存储要显示的字符
    cmp al, 0       ;如果al是结束符号，就停止输出
    jz .done
    int 0x10        ;调用int10中断打印字符

    inc si          ;继续处理下一个字符
    jmp .loop
.done:
    ret

msg:
    db "hello, world", 10, 13, 0

times 510 - ($ - $$) db 0   ;$表示当前位置，$$表示汇编的开头
db 0x55, 0xaa       ;填充魔数