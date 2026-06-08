#include <stdlib.h>
#include <stddef.h>
#include "scheduler.h"
#include "queue.h"

struct Scheduler {
    Queue* ready_queue;
};

Scheduler* scheduler_create_fifo(void) {
    Scheduler* s = (Scheduler*)malloc(sizeof(Scheduler));
    if (!s) return NULL;
    s->ready_queue = queue_create();
    return s;
}

void scheduler_add_process(Scheduler* s, int pid, int burst_time) {
    (void)burst_time; // Evita warning de variable no usada
    if (!s || !s->ready_queue) return;
    enqueue(s->ready_queue, pid);
}

int scheduler_next(Scheduler* s) {
    if (!s || !s->ready_queue || queue_is_empty(s->ready_queue)) {
        return -1;
    }
    return dequeue(s->ready_queue);
}

void scheduler_destroy(Scheduler* s) {
    if (!s) return;
    queue_destroy(s->ready_queue);
    free(s);
}