#pragma once

#include <stdlib.h>

typedef enum priority_queue_status_code {
    SUCCESS,
    PRIORITY_QUEUE_EMPTY_ERROR,
    NULL_DATA_ERROR,
    ALLOCATION_ERROR,
} PriorityQueueStatusCode;

typedef struct priority_queue {
    void* array;
    size_t size;
    size_t capacity;
    size_t nmeb;
    int (*compar)(const void*, const void*);
} PriorityQueue;

// Initializes PriorityQueue with array of size size with each
// element of size nmeb. If array is NULL then size is ignored
// Array is copied into priority queue
PriorityQueue pq_init(void* array, int (*compar)(const void*, const void*), size_t nmeb, size_t size);

// Initializes queue dynamically on a heap
PriorityQueue* pq_init_dynamic(void* array, int (*compar)(const void*, const void*), size_t nmeb, size_t size);

// clears the priority queue, is allocated dynamically, pointer
// should be freed manually afterwards
void pq_drop(PriorityQueue* pq);

// Peeks the top element from the priority queue, copies it into data
PriorityQueueStatusCode pq_peek(const PriorityQueue* pq, void* data);

// copies element pointed to by data into priority queue
PriorityQueueStatusCode pq_put(PriorityQueue* pq, const void* data);

// removes element from priority queue, copies element into data
PriorityQueueStatusCode pq_pop(PriorityQueue* pq, void* data);
