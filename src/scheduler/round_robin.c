#include <stdlib.h>
#include <stddef.h>
#include "circular_queue.h"

// Definición concreta de la estructura de la cola circular
struct CircularQueue {
    int* data;
    int head;
    int tail;
    int size;
    int capacity;
};

// Crea la cola circular con una capacidad fija (Aritmética estática modular)
CircularQueue* cq_create(int capacity) {
    if (capacity <= 0) return NULL;
    
    CircularQueue* q = (CircularQueue*)malloc(sizeof(CircularQueue));
    if (!q) return NULL;
    
    q->data = (int*)malloc(sizeof(int) * capacity);
    if (!q->data) {
        free(q);
        return NULL;
    }
    
    q->capacity = capacity;
    q->head = 0;
    q->tail = 0;
    q->size = 0;
    return q;
}

// Inserta un elemento de forma circular
void cq_enqueue(CircularQueue* q, int value) {
    if (!q || q->size == q->capacity) return; // Cola llena
    
    q->data[q->tail] = value;
    q->tail = (q->tail + 1) % q->capacity; // Incremento circular modular
    q->size++;
}

// Extrae un elemento de forma circular (Retorna el entero para el assert)
int cq_dequeue(CircularQueue* q) {
    if (!q || q->size == 0) return -1; // Cola vacía
    
    int value = q->data[q->head];
    q->head = (q->head + 1) % q->capacity; // Incremento circular modular
    q->size--;
    return value;
}

// Libera la memoria de la estructura
void cq_destroy(CircularQueue* q) {
    if (!q) return;
    free(q->data);
    free(q);
}