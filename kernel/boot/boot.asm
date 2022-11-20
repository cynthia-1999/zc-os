; 0柱面0磁道1扇區
[ORG  0x7c00]

[SECTION .data]
BOOT_MAIN_ADDR equ 0x500    ;equ指令用于将一个数值或寄存器名赋值给一个自定的符号名
                            ;符号名 equ 表达式
                            ;符号名 equ 寄存器名
                            ;表达式必须是一个简单再定位表达式，用equ指令复制以后的字符名，可以用作数据地址、代码地址、位地址或者直接当作立即数使用

[SECTION .text]
[BITS 16]
global _start
_start:
    ; 设置屏幕模式为文本模式，清除屏幕
    mov ax, 3
    int 0x10

    ;mov     ax, 0
    ;mov     ss, ax
    ;mov     ds, ax
    ;mov     es, ax
    ;mov     fs, ax
    ;mov     gs, ax
    ;mov     si, ax

    ;读软盘
    mov ch, 0   ; 柱面
    mov dh, 0   ; 磁头
    mov cl, 2   ; 2扇区
    mov bx, BOOT_MAIN_ADDR  ;把数据读到0x500的位置

    mov ah, 0x02 ;读盘操作
    mov al, 1   ;连续读1个扇区
    mov dl, 0   ;驱动器编号

    int 0x13    ;使用0x13 BIOS中断读盘

    mov  si, jump_to_setup_msg
    call print

    xchg bx, bx
    jmp  BOOT_MAIN_ADDR

read_floppy_error:
    mov si, read_floppy_error_msg
    call print
    jmp $

; 如何调用
; mov     si, msg   ; 1 传入字符串
; call    print     ; 2 调用
print:
    mov ah, 0x0e
    mov bh, 0
    mov bl, 0x01
.loop:
    mov al, [si]
    cmp al, 0
    jz .done
    int 0x10

    inc si
    jmp .loop
.done:
    ret

read_floppy_error_msg:
    db "read floppy error", 10, 13, 0

jump_to_setup_msg:
    db "jump to setup...", 10, 13, 0

msg:
    db "hello, world", 10, 13, 0

times 510 - ($ - $$) db 0
db 0x55, 0xaa