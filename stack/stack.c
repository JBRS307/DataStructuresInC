#include <stdlib.h>
#include <stdbool.h>

#include "stack.h"

Stack stack_init() {
    Stack new_stack;
    new_stack.top = NULL;
    new_stack.size = 0;
    return new_stack;
}

bool stack_is_empty(const Stack* stack) {
    return stack->size == 0;
}

size_t stack_size(const Stack* stack) {
    return stack->size;
}

StackStatusCode stack_push(Stack* stack, void* data, size_t nmeb) {
    if (data == NULL) {
        return NULL_ELEM_ERROR;
    }

    StackNode* node = (StackNode*)malloc(sizeof(StackNode));
    if (node == NULL) {
        return ALLOCATION_ERROR;
    }

    node->nmeb = nmeb;
    node->data = data;
    node->prev = stack->top;
    stack->top = node;
    stack->size++;
    return SUCCESS;
}

StackStatusCode stack_peek(const Stack* stack, void** data, size_t* nmeb) {
    if (stack->size == 0) {
        return STACK_EMPTY;
    }

    if (data != NULL) {
        *data = stack->top->data;
    }
    if (nmeb != NULL) {
        *nmeb = stack->top->nmeb;
    }

    return SUCCESS;
}

StackStatusCode stack_pop(Stack* stack, void** data, size_t* nmeb) {
    if (data == NULL) {
        return NULL_ELEM_ERROR; // to prevent potential memory leaks
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