[BITS 32]
[SECTION .text]

extern current
extern task_exit
extern sched
extern inc_scheduling_times
extern get_task_ppid

; 切idle任务专用
global switch_idle_task
switch_idle_task:
    ; 恢复上下文
    mov eax, [current]

    ; 恢复ebp0 esp0
    mov esp, [eax + 4]
    mov ebp, [eax + 15 * 4]

    ; 恢复通用寄存器
    mov ecx, [eax + 11 * 4]
    mov edx, [eax + 12 * 4]
    mov ebx, [eax + 13 * 4]
    mov esi, [eax + 16 * 4]
    mov edi, [eax + 17 * 4]

    mov eax, [eax + 8 * 4]      ; eip

    sti

    jmp eax

    ; 下面这两句正常情况执行不到,一种保险策略,以防万一
    sti
    hlt

global switch_task
switch_task:
    ; 恢复上下文
    mov eax, [current]

    ; 恢复ebp0 esp0
    mov esp, [eax + 4]
    mov ebp, [eax + 15 * 4]

    ; 压入返回地址，在task运行完成之后在任务队列清除自己的内存，并回收内存
    mov eax, task_exit_handler
    push eax

.recover_env:
    mov eax, [current]

    ; 恢复通用寄存器
    mov ecx, [eax + 11 * 4]
    mov edx, [eax + 12 * 4]
    mov ebx, [eax + 13 * 4]
    mov esi, [eax + 16 * 4]
    mov edi, [eax + 17 * 4]

    mov eax, [eax + 8 * 4]      ; eip

    sti

    jmp eax

task_exit_handler:
    mov eax, [current]
    push eax
    push 0                      ; exit code = 0 表示正常退出
    call task_exit
    add esp, 8

    call sched

    ; 下面这两句正常情况执行不到,一种保险策略
    sti
    hlt