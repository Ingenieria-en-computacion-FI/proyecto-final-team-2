#include <stdlib.h>
#include <stddef.h>
#include "memory_manager.h"

// Coalescencia: Une bloques libres contiguos para mitigar fragmentación
void mm_coalesce(MemoryManager* mm) {
    if (!mm || !mm->head) return;

    MemoryBlock* curr = mm->head;

    while (curr != NULL && curr->next != NULL) {
        if (curr->free && curr->next->free) {
            MemoryBlock* block_to_delete = curr->next;

            curr->size += block_to_delete->size;
            curr->next = block_to_delete->next;

            if (block_to_delete->next != NULL) {
                block_to_delete->next->prev = curr;
            }

            free(block_to_delete);
            // No avanzamos 'curr' por si hay más bloques libres seguidos
        } else {
            curr = curr->next;
        }
    }
}