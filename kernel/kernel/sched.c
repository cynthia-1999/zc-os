//
// Created by zc on 23-7-21.
//

#include "../include/linux/sched.h"
#include "../include/linux/task.h"


extern void switch_idle_task(task_t* task);

extern task_t* tasks[NR_TASKS];

task_t* current = NULL;

task_t* find_ready_task() {
    task_t* next = NULL;

    for (int i = 1; i < NR_TASKS; ++i) {
        task_t* task = tasks[i];

        if (NULL == task) continue;

        // 实现程序继续执行
        if(current == task && TASK_RUNNING == task->state){
            task->state = TASK_READY;
        }

        if (TASK_READY != task->state) continue;

        next = task;
    }

    return next;
}

void sched() {
    task_t* next = find_ready_task();

    if (NULL == next) {
        current = tasks[0];

        switch_idle_task(tasks[0]);

        return;
    }
    next->state = TASK_RUNNING;

    current = next;

    switch_task(next);
}

void do_timer(){
    sched();
}