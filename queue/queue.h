#pragma once

#include <stdlib.h>
#include <stdbool.h>

typedef enum queue_status_code {
    SUCCESS,
    QUEUE_EMPTY_ERROR,
    NULL_DATA_ERROR,
    ALLOCATION_ERROR,
} QueueStatusCode;

typedef struct queue_node {
    void* data;
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

// dynamically initializes empty queue
Queue* queue_init_dynamic();

// checks if queue is empty
bool queue_is_empty(const Queue* q);

// returns size of the queue
size_t queue_size(const Queue* q);

// saves first element in data, if nmeb given saves its size 
QueueStatusCode queue_peek(const Queue* q, void** data, size_t* nmeb);

// pushes data of size nmeb into queue. It copies data from data into queue
QueueStatusCode queue_push(Queue* q, void* data, size_t nmeb);

// Removes element from queue, saves data in data.
// If nmeb is not NULL then saves removed element's size
QueueStatusCode queue_pop(Queue* q, void** data, size_t* nmeb);