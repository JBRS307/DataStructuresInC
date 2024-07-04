#pragma once

#include <stdlib.h>

typedef enum priority_queue_status_code {
    SUCCESS,
    ALLOCATION_ERROR,
} PriorityQueueStatusCode;

typedef int (*comparator)(const void*, const void*);

typedef struct priority_queue {
    void* array;
    size_t size;
    size_t capacity;
    size_t nmeb;
    comparator f;
} PriorityQueue;

// Initializes PriorityQueue with array of size size with each
// element of size nmeb. If array is NULL then size is ignored
// Array is not copied
PriorityQueue pq_init(void* array, comparator f, size_t nmeb, size_t size);

PriorityQueue* pq_init_dynamic(void* array, comparator f, size_t nmeb, size_t size);
