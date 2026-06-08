#ifndef QUEUE_H
#define QUEUE_H

typedef struct Queue Queue;

Queue* queue_create(void);
void enqueue(Queue* queue, int value);
int dequeue(Queue* queue);
int queue_is_empty(Queue* queue);
void queue_destroy(Queue* queue);

#endif
