#pragma once

#include <stdlib.h>

typedef enum queue_status_code {
    SUCCESS,
} QueueStatusCode;

typedef struct queue_node {
    void* elem;
    struct queue_node* next;
    struct queue_node* prev;
    size_t nmeb;
} QueueNode;

typedef struct queue {
    QueueNode* head;
    QueueNode* tail;
    size_t size;
} Queue;

// initializes empty queue
Queue queue_init();

// checks if queue is empty
bool queue_is_empty(const Queue* q);

// returns size of the queue
size_t queue_size(const Queue* q);

