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

static void heapify(void* array, size_t i, size_t size, size_t nmeb, int (*compar)(const void*, const void*)) {
    size_t l, r, min_ind;
    l = left(i);
    r = right(i);
    min_ind = i;

    if ((l < size) && (compar(array+offset(l, nmeb), array+offset(min_ind, nmeb)) < 0)) {
        min_ind = l;
    }
    if ((r < size) && (compar(array+offset(r, nmeb), array+offset(min_ind, nmeb)) < 0)) {
        min_ind = r;
    }

    if (min_ind != i) {
        swap(array+offset(i, nmeb), array+offset(min_ind, nmeb), nmeb);
        heapify(array, min_ind, size, nmeb, compar);
    }
}

static void move_up(void* array, size_t i, size_t nmeb, int (*compar)(const void*, const void*)) {
    if (i == 0) {
        return;
    }

    size_t p = parent(i);

    if (compar(array+offset(i, nmeb), array+offset(p, nmeb)) < 0) {
        swap(array+offset(i, nmeb), array+offset(p, nmeb), nmeb);
        move_up(array, p, nmeb, compar);
    }
}

static void build_heap(void* array, size_t size, size_t nmeb, int (*compar)(const void*, const void*)) {
    for (size_t i = parent(size-1); i > 0; i--) {
        heapify(array, i, size, nmeb, compar);
    }
    heapify(array, 0, size, nmeb, compar);
}

// end of static functions

PriorityQueue pq_init(void* array, int (*compar)(const void*, const void*), size_t nmeb, size_t size) {
    PriorityQueue pq;
    if (array != NULL) {
        pq.array = malloc(size*nmeb);
        memcpy(pq.array, array, size*nmeb);
        pq.size = size;
        pq.capacity = size;
        build_heap(pq.array, size, nmeb, compar);
    } else {
        pq.array = malloc(nmeb);
        pq.size = 0;
        pq.capacity = 1;
    }
    pq.nmeb = nmeb;
    pq.compar = compar;
    return pq;
}

PriorityQueue* pq_init_dynamic(void* array, int (*compar)(const void*, const void*), size_t nmeb, size_t size) {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    if (pq == NULL) {
        return NULL;
    }

    if (array != NULL) {
        pq->array = malloc(size*nmeb);
        memcpy(pq->array, array, size*nmeb);
        pq->size = size;
        pq->capacity = size;
        build_heap(pq->array, size, nmeb, compar);
    } else {
        pq->array = malloc(nmeb);
        pq->size = 0;
        pq->capacity = 1;
    }
    pq->nmeb = nmeb;
    pq->compar = compar;
    return pq;
}

void pq_drop(PriorityQueue* pq) {
    free(pq->array);
}

PriorityQueueStatusCode pq_peek(const PriorityQueue* pq, void* data) {
    if (data == NULL) {
        return NULL_DATA_ERROR;
    }

    if (pq->size == 0) {
        return PRIORITY_QUEUE_EMPTY_ERROR;
    }

    memcpy(data, pq->array, pq->nmeb);
    return SUCCESS;
}

PriorityQueueStatusCode pq_put(PriorityQueue* pq, const void* data) {
    if (data == NULL) {
        return NULL_DATA_ERROR;
    }

    if (pq->size == pq->capacity) {
        pq->array = realloc(pq->array, 2*(pq->capacity)*(pq->nmeb));
        pq->capacity *= 2;
    }

    size_t index = pq->size;
    memcpy(pq->array+offset(index, pq->nmeb), data, pq->nmeb);

    move_up(pq->array, index, pq->nmeb, pq->compar);
    pq->size++;
    return SUCCESS;
}

PriorityQueueStatusCode pq_pop(PriorityQueue* pq, void* data) {
    if (data == NULL) {
        return NULL_DATA_ERROR;
    }

    if (pq->size == 0) {
        return PRIORITY_QUEUE_EMPTY_ERROR;
    }

    memcpy(data, pq->array, pq->nmeb);

    swap(pq->array, pq->array+offset(pq->size - 1, pq->nmeb), pq->nmeb);
    pq->size--;

    heapify(pq->array, 0, pq->size, pq->nmeb, pq->compar);

    return SUCCESS;
}