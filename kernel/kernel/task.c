//
// Created by zc on 23-7-21.
//
#include "../include/linux/kernel.h"
#include "../include/linux/task.h"
#include "../include/linux/sched.h"
#include "../include/linux/memory.h"
#include "../include/string.h"

task_t* tasks[NR_TASKS] = {0};
extern task_t* current;
extern int jiffy;
extern int cpu_tickes;

extern void sched_task();
extern void move_to_user_mode();

int find_empty_process() {
    int ret = 0;

    bool is_finded = false;

    for (int i = 0; i < NR_TASKS; ++i) {
        if (0 == tasks[i]) {
            is_finded = true;

            ret = i;
            break;
        }
    }

    if (!is_finded) {
        printk("no valid pid\n");
        return -1;
    }

    return ret;
}

task_union_t* create_task(char* name, task_fun_t fun, int priority) {
    task_union_t* task_union = (task_union_t*)kmalloc(4096);
    memset(task_union, 0, PAGE_SIZE);

    task_union->task.pid = find_empty_process();
    task_union->task.ppid = (NULL == current)? 0 : current->pid;

    task_union->task.priority = priority;
    task_union->task.counter = priority;
    task_union->task.scheduling_times = 0;

    strcpy(task_union->task.name, name);

    // 加入tasks
    tasks[task_union->task.pid] = &(task_union->task);

    task_union->task.tss.cr3 = (int)task_union + sizeof(task_t);
    task_union->task.tss.eip = fun;

    // r0 stack
    task_union->task.esp0 = (int)task_union + PAGE_SIZE;
    task_union->task.ebp0 = task_union->task.esp0;

    task_union->task.tss.esp0 = task_union->task.esp0;

    task_union->task.state = TASK_READY;

    return task_union;
}

void* idle(void* arg) {
    create_task("init", move_to_user_mode, 1);

    while (true) {
//        printk("#2 idle task running...\n");

        __asm__ volatile ("sti;");
        __asm__ volatile ("hlt;");
//        sched();
    }
}

void task_init() {
    create_task("idle", idle, 0);
}

pid_t get_task_pid(task_t* task) {
    return task->pid;
}

pid_t get_task_ppid(task_t* task) {
    return task->ppid;
}

int inc_scheduling_times(task_t* task) {
    return task->scheduling_times++;
}

void task_exit(int code, task_t* task) {
    for (int i = 1; i < NR_TASKS; ++i) {
        task_t* tmp = tasks[i];

        if (task == tmp) {
            printk("task exit: %s\n", tmp->name);

            tmp->exit_code = code;

            // 先移除，后面有父子进程再相应处理
            tasks[i] = NULL;

            current = NULL;

            kfree_s(tmp, 4096);

            break;
        }
    }
}

void task_sleep(int ms){
    CLI

    if(NULL == current){
        printk("task sleep: current task is null\n");
        return;
    }

    int ticks = ms / jiffy;
    ticks += (0 == (ms % jiffy)) ? 0 : 1;

    current->counter = cpu_tickes + ticks;
    current->state = TASK_SLEEPING;

    sched_task();
}

void task_wakeup() {
    for (int i = 1; i < NR_TASKS; ++i) {
        task_t* task = tasks[i];

        if (NULL == task) continue;
        if (TASK_SLEEPING != task->state) continue;

        if (cpu_tickes >= task->counter) {
            task->state = TASK_READY;
            task->counter = task->priority;
        }
    }
}

int get_esp3(task_t* task) {
    return task->esp3;
}

void set_esp3(task_t* task, int esp) {
    task->tss.esp = esp;
}