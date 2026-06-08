#ifndef SCHEDULER_H
#define SCHEDULER_H

typedef struct Scheduler Scheduler;

Scheduler* scheduler_create_fifo(void);
void scheduler_add_process(Scheduler* s, int pid, int burst_time);
int scheduler_next(Scheduler* s);
void scheduler_destroy(Scheduler* s);

#endif