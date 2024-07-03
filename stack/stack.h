#pragma once

#include <stdlib.h>
#include <stdbool.h>

typedef enum stack_status_code {
    SUCCESS,
    STACK_EMPTY,
    ALLOCATION_ERROR,
    NULL_ELEM_ERROR,
} StackStatusCode;

// elements on stack can be allocated both statically and dynamically
// if allocated dynamically - REMEMBER TO FREE
typedef struct stack_node {
    void* data; // Pointer to element to be placed on stack
    size_t nmeb; // size of the element pointed to by data
    struct stack_node* prev; // previous node on stack
} StackNode;

typedef struct stack {
    StackNode* top; // pointer to top element
    size_t size; // stack size
} Stack;

// initializes stack
Stack stack_init();

// check if stack is empty
bool stack_is_empty(const Stack* stack);

// returns size of the stack
size_t stack_size(const Stack* stack);

// pushes element to the stack
StackStatusCode stack_push(Stack* stack, void* data, size_t nmeb);

// peeks the top element on stack, saves pointer to element in data and
// size of the element to nmeb
StackStatusCode stack_peek(const Stack* stack, void** data, size_t* nmeb);

// takes the top element off the stack; saves element in the data and its
// size into nmeb
StackStatusCode stack_pop(Stack* stack, void** data, size_t* nmeb);