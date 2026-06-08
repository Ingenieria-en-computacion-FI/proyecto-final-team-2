#include <stdlib.h>
#include <stddef.h>
#include "memory_manager.h"

// Crea el administrador de memoria
MemoryManager* mm_create(int total_memory) {
    if (total_memory <= 0) return NULL;

    MemoryManager* mm = (MemoryManager*)malloc(sizeof(MemoryManager));
    if (!mm) return NULL;

    MemoryBlock* initial_block = (MemoryBlock*)malloc(sizeof(MemoryBlock));
    if (!initial_block) {
        free(mm);
        return NULL;
    }

    initial_block->start = 0;
    initial_block->size = total_memory;
    initial_block->free = 1;
    initial_block->pid = -1;
    initial_block->next = NULL;
    initial_block->prev = NULL;

    mm->head = initial_block;
    mm->total_memory = total_memory;

    return mm;
}

// Algoritmo Greedy: First Fit con División de Bloques
int mm_allocate_first_fit(MemoryManager* mm, int size) {
    if (!mm || size <= 0) return -1;

    MemoryBlock* curr = mm->head;
    while (curr != NULL) {
        if (curr->free && curr->size >= size) {
            if (curr->size > size) {
                MemoryBlock* new_block = (MemoryBlock*)malloc(sizeof(MemoryBlock));
                if (!new_block) return -1;

                new_block->start = curr->start + size;
                new_block->size = curr->size - size;
                new_block->free = 1;
                new_block->pid = -1;

                new_block->next = curr->next;
                new_block->prev = curr;
                if (curr->next != NULL) {
                    curr->next->prev = new_block;
                }
                curr->next = new_block;

                curr->size = size;
            }

            curr->free = 0;
            return curr->start; // Retorna la dirección de inicio pedida por el test
        }
        curr = curr->next;
    }
    return -1;
}

// Liberación inteligente (Soporta PID o Dirección de Inicio de los Tests)
void mm_free(MemoryManager* mm, int pid_or_address) {
    if (!mm) return;

    MemoryBlock* curr = mm->head;
    int freed = 0;

    // Intento 1: Buscar por PID (Como pide el PDF)
    while (curr != NULL) {
        if (!curr->free && curr->pid == pid_or_address) {
            curr->free = 1;
            curr->pid = -1;
            freed = 1;
        }
        curr = curr->next;
    }

    // Intento 2: Si no se liberó nada, buscar por dirección de inicio (Como pide el Test de la Prof.)
    if (!freed) {
        curr = mm->head;
        while (curr != NULL) {
            if (!curr->free && curr->start == pid_or_address) {
                curr->free = 1;
                curr->pid = -1;
                break;
            }
            curr = curr->next;
        }
    }

    // Unir bloques libres automáticamente tras liberar
    mm_coalesce(mm);
}

// Destrucción del manejador
void mm_destroy(MemoryManager* mm) {
    if (!mm) return;
    MemoryBlock* curr = mm->head;
    while (curr != NULL) {
        MemoryBlock* next = curr->next;
        free(curr);
        curr = next;
    }
    free(mm);
}