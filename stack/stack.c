#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "stack.h"

Stack stack_init() {
    Stack new_stack;
    new_stack.top = NULL;
    new_stack.size = 0;
    return new_stack;
}

Stack* stack_init_dynamic() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

bool stack_is_empty(const Stack* stack) {
    return stack->size == 0;
}

size_t stack_size(const Stack* stack) {
    return stack->size;
}

StackStatusCode stack_push(Stack* stack, void* data, size_t nmeb) {
    if (data == NULL) {
        return NULL_DATA_ERROR;
    }

    StackNode* node = (StackNode*)malloc(sizeof(StackNode));
    if (node == NULL) {
        return ALLOCATION_ERROR;
    }

    node->nmeb = nmeb;
    node->data = malloc(nmeb);
    memcpy(node->data, data, nmeb);

    node->prev = stack->top;
    stack->top = node;
    stack->size++;
    return SUCCESS;
}

StackStatusCode stack_peek(const Stack* stack, void** data, size_t* nmeb) {
    if (data == NULL) {
        return NULL_DATA_ERROR;
    }

    if (stack->size == 0) {
        return STACK_EMPTY;
    }

    *data = stack->top->data;
    if (nmeb != NULL) {
        *nmeb = stack->top->nmeb;
    }

    return SUCCESS;
}

StackStatusCode stack_pop(Stack* stack, void** data, size_t* nmeb) {
    if (data == NULL) {
        return NULL_DATA_ERROR; // to prevent potential memory leaks
    }
    if (stack->size == 0) {
        return STACK_EMPTY;
    }


    *data = stack->top->data;
    if (nmeb != NULL) {
        *nmeb = stack->top->nmeb;
    }
    StackNode* removed = stack->top;
    stack->top = removed->prev;
    stack->size--;

    free(removed);
    return SUCCESS;
}