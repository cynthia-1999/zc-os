;0柱面 0磁道 2扇区
[ORG  0x500]

[SECTION .data]
KERNEL_ADDR equ 0x1200

; 用于存储内存检测的数据
ARDS_TIMES_BUFFER equ 0x1100
AEDS_BUFFER equ 0x1102
ARDS_TIMES dw 0

; 存储填充以后的offset，下次检测的结果接着写
CHECK_BUFFER_OFFSET dw 0

[SECTION .gdt]
SEG_BASE equ 0
SEG_LIMIT equ 0xfffff

CODE_SELECTOR equ (1 << 3)
DATA_SELECTOR equ (2 << 3)

gdt_base:
    dd 0, 0
gdt_code:
    dw SEG_LIMIT & 0xffff
    dw SEG_BASE & 0xffff
    db SEG_BASE >> 16 & 0xff
    ; P_DPL_S_TYPE
    db 0b1_00_1_1000
    ; G_DB_AVL_LIMIT
    db 0b0_1_00_0000 | (SEG_LIMIT >> 16 & 0xf)
    db SEG_BASE >> 24 & 0xff
gdt_data:
    dw SEG_LIMIT & 0xffff
    dw SEG_BASE & 0xffff
    db SEG_BASE >> 16 & 0xff
    ;    P_DPL_S_TYPE
    db 0b1_00_1_0010
    ;    G_DB_AVL_LIMIT
    db 0b1_1_00_0000 | (SEG_LIMIT >> 16 & 0xf)
    db SEG_BASE >> 24 & 0xf
gdt_ptr:
    dw $ - gdt_base - 1
    dd gdt_base


[SECTION .text]
[BITS 16]
global setup_start
setup_start:
    mov     ax, 0
    mov     ss, ax
    mov     ds, ax
    mov     es, ax
    mov     fs, ax
    mov     gs, ax
    mov     si, ax

    mov si, prepare_enter_protected_mode_msg
    call print

get_memory_info:
    xor     ebx, ebx
    mov     di, AEDS_BUFFER

.loop:
    mov     eax, 0xe820
    mov     ecx, 20
    mov     edx, 0x534D4150
    int     0x15

    ; 出错CF=1
    jc      get_memory_info_error

    add     di, cx             ; 下次填充的结果存到下个结构体

    inc     dword [ARDS_TIMES] ; 检测次数 + 1

    cmp     ebx, 0             ; 检测的时候，ebx会被bios修改，ebx不为0就要继续检测
    jne     .loop

    mov     ax, [ARDS_TIMES]            ; 保存内存检测次数
    mov     [ARDS_TIMES_BUFFER], ax

    mov     [CHECK_BUFFER_OFFSET], di   ; 保存offet

.get_memory_info_success:
    mov si, get_memory_info_success_msg
    call print

enter_protected_mode:
    ; 关中断
    cli

    ; 加载gdt表
    lgdt [gdt_ptr]

    ; 打开A20
    in    al,  92h
    or    al,  00000010b
    out   92h, al

    ; 设置保护模式
    mov eax, cr0
    or eax, 1
    mov cr0, eax

    xchg bx, bx
    jmp CODE_SELECTOR:protected_mode

get_memory_info_error:
    mov si, get_memory_info_error_msg
    call print

    jmp $


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

[BITS 32]
protected_mode:
   mov ax, DATA_SELECTOR
   mov ds, ax
   mov ss, ax
   mov es, ax
   mov fs, ax
   mov gs, ax

   mov esp, 0x9fbff

   ; 将内核读入内存
   mov edi, KERNEL_ADDR
   mov ecx, 3   ; start
   mov bl, 60   ; count
   call read_hd

   jmp CODE_SELECTOR:KERNEL_ADDR

read_hd:
    ; 0x1f2 8bits 指定读取或写入的扇区数
    mov dx, 0x1f2
    mov al, bl
    out dx, al

    ; 0x1f3 8bits lba地址的低8位
    inc dx
    mov al, cl
    out dx, al

    ; 0x1f4 8bits lba地址的中8位
    inc dx
    mov al, ch
    out dx, al

    ; 0x1f5 8bits lba地址的高8位
    inc dx
    shr ecx, 16
    mov al, cl
    out dx, al

    ; 0x1f6 8bit
    ; 0-3 位iba地址的24-27
    ; 4 0表示主盘 1表示从盘
    ; 5、7位固定为1
    ; 6 0表示CHS模式，1表示LAB模式
    inc dx
    shr ecx, 8
    and cl, 0b1111
    mov al, 0b1110_0000
    or al, cl
    out dx, al

    ; 0x1f7 8bit
    inc dx
    mov al, 0x20
    out dx, al

    ; 设置loop次数，读多少个扇区要loop多少次
    mov cl, bl
.start_read:
    push cx ; 保留loop次数，防止被下面的代码修改破坏

    call .wait_hd_prepare
    call read_hd_data

    pop cx  ; 恢复loop次数
    loop .start_read

.return:
    ret

; 一直等待，直到硬盘的状态是：不繁忙，数据已准备好
; 第7位为0,第3位为1,第0位为0
.wait_hd_prepare:
    mov dx, 0x1f7

.check:
    in al, dx
    and al, 0b1000_1000
    cmp al, 0b0000_1000
    jnz .check

    ret

; 读硬盘，一次读两个字节，读256次，刚好一个扇区
read_hd_data:
    mov dx, 0x1f0
    mov cx, 256

.read_word:
   in ax, dx
   mov [edi], ax
   add edi, 2
   loop .read_word

   ret

msg:
    db "hello world!", 10, 13, 0

prepare_enter_protected_mode_msg:
    db "Prepare to go into protected mode ...", 10, 13, 0

get_memory_info_error_msg:
    db "Get memory info fail...", 10, 13, 0

get_memory_info_success_msg:
    db "Get memory info success...", 10, 13, 0