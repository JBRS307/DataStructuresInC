#include <stdlib.h>
#include <stdbool.h>

#include "queue.h"

Queue queue_init() {
    Queue q;
    q.head = NULL;
    q.tail = NULL;
    q.size = 0;
    return q;
}

bool queue_is_empty(const Queue* q) {
    return q->size == 0;
}

size_t queue_size(const Queue* q) {
    return q->size;
}