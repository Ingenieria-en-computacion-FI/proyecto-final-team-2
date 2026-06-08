#include <stdlib.h>
#include <stddef.h>
#include "queue.h"

typedef struct Node {
    int value;
    struct Node* next;
} Node;

struct Queue {
    Node* front;
    Node* rear;
};

Queue* queue_create(void) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (!queue) return NULL;
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

void enqueue(Queue* queue, int value) {
    if (!queue) return;
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) return;
    new_node->value = value;
    new_node->next = NULL;
    
    if (queue->rear == NULL) {
        queue->front = new_node;
        queue->rear = new_node;
    } else {
        queue->rear->next = new_node;
        queue->rear = new_node;
    }
}

int dequeue(Queue* queue) {
    if (queue_is_empty(queue)) return -1;
    
    Node* temp = queue->front;
    int value = temp->value;
    
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    
    free(temp);
    return value;
}

int queue_is_empty(Queue* queue) {
    return (queue == NULL || queue->front == NULL);
}

void queue_destroy(Queue* queue) {
    if (!queue) return;
    while (!queue_is_empty(queue)) {
        dequeue(queue);
    }
    free(queue);
}