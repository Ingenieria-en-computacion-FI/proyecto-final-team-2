#include <stdlib.h>
#include <stddef.h>
#include "stack.h"

struct Node {
    int value;
    struct Node* next;
};

struct Stack {
    struct Node* top;
};

// Crea una pila vacía
Stack* stack_create(void) {
    Stack* stack = malloc(sizeof(Stack));
    if (!stack) return NULL;
    stack->top = NULL;
    return stack;
}

// Inserta un elemento en el tope (Push)
void stack_push(Stack* stack, int value) {
    if (!stack) return;
    struct Node* new_node = malloc(sizeof(struct Node));
    if (!new_node) return;
    
    new_node->value = value;
    new_node->next = stack->top;
    stack->top = new_node;
}

// Remueve y retorna el elemento del tope (Pop)
int stack_pop(Stack* stack) {
    if (stack_is_empty(stack)) {
        return -1; 
    }
    
    struct Node* temp = stack->top;
    int popped_value = temp->value;
    
    stack->top = temp->next;
    free(temp);
    
    return popped_value;
}

// Observa el elemento del tope sin removerlo (Peek)
int stack_peek(Stack* stack) {
    if (stack_is_empty(stack)) {
        return -1;
    }
    return stack->top->value;
}

// Verifica si la pila está vacía (Retorna 1 si está vacía, 0 si no)
int stack_is_empty(Stack* stack) {
    return (stack == NULL || stack->top == NULL);
}

// Libera toda la memoria asignada a la pila
void stack_destroy(Stack* stack) {
    if (!stack) return;
    
    while (!stack_is_empty(stack)) {
        stack_pop(stack);
    }
    free(stack);
}
