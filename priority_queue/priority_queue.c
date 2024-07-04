#include <stdlib.h>
#include <string.h>

#include "priority_queue.h"

// static functions
static size_t left(size_t i) {
    return 2*i+1;
}

static size_t right(size_t i) {
    return 2*i+2;
}

static size_t parent(size_t i) {
    return (i-1)/2;
}

static size_t offset(size_t i, size_t nmeb) {
    return i * nmeb;
}

static void swap(void* a, void* b, size_t nmeb) {
    void* temp = malloc(nmeb);
    memcpy(temp, a, nmeb);
    memcpy(a, b, nmeb);
    memcpy(b, temp, nmeb);
    free(temp);
}

static void heapify(void* array, size_t i, size_t size, size_t nmeb, comparator f) {
    size_t l, r, min_ind;
    l = left(i);
    r = right(i);
    min_ind = i;

    if (l < size && f(array+offset(l, nmeb), array+offset(min_ind, nmeb)) < 0) {
        min_ind = l;
    }
    if (r < size && f(array+offset(r, nmeb), array+offset(min_ind, nmeb)) < 0) {
        min_ind = r;
    }

    if (min_ind != i) {
        swap(array+offset(i, nmeb), array+offset(min_ind, nmeb), nmeb);
        heapify(array, min_ind, size, nmeb, f);
    }
}

static void build_heap(void* array, size_t size, size_t nmeb, comparator f) {
    for (size_t i = parent(size-1); i >= 0; i--) {
        heapify(array, i, size, nmeb, f);
    }
}

// end of static functions

PriorityQueue pq_init(void* array, comparator f, size_t nmeb, size_t size) {
    PriorityQueue pq;
    if (array != NULL) {
        build_heap(array, size, nmeb, f);
        pq.array = array;
        pq.size = size;
        pq.capacity = size;
        pq.nmeb = nmeb;
    } else {
        pq.array = NULL;
        pq.size = 0;
        pq.capacity = 0;
        pq.nmeb = nmeb;
    }
    return pq;
}

PriorityQueue* pq_init_dynamic(void* array, comparator f, size_t nmeb, size_t size) {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    if (pq == NULL) {
        return NULL;
    }

    if (array != NULL) {
        build_heap(array, size, nmeb, f);
        pq->array = array;
        pq->size = size;
        pq->capacity = size;
        pq->nmeb = nmeb;
    } else {
        pq->array = NULL;
        pq->size = 0;
        pq->capacity = 0;
        pq->nmeb = nmeb;
    }
    return pq;
}