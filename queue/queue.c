#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "queue.h"

Queue queue_init() {
    Queue q;
    q.head = NULL;
    q.tail = NULL;
    q.size = 0;
    return q;
}

Queue* queue_init_dynamic() {
    Queue* q = (Queue*)malloc(sizeof(Queue));

    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

bool queue_is_empty(const Queue* q) {
    return q->size == 0;
}

size_t queue_size(const Queue* q) {
    return q->size;
}

QueueStatusCode queue_peek(const Queue* q, void** data, size_t* nmeb) {
    if (data == NULL) {
        return NULL_DATA_ERROR;
    }
    if (queue_is_empty(q)) {
        return QUEUE_EMPTY_ERROR;
    }

    *data = q->head->data;
    if (nmeb != NULL) {
        *nmeb = q->head->nmeb;
    }

    return SUCCESS;
}

QueueStatusCode queue_push(Queue* q, void* data, size_t nmeb) {
    if (data == NULL) {
        return NULL_DATA_ERROR;
    }

    QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
    node->data = malloc(nmeb);
    if (node->data == NULL) {
        return ALLOCATION_ERROR;
    }

    memcpy(node->data, data, nmeb);
    node->nmeb = nmeb;

    node->prev = q->tail;
    node->next = NULL;
    q->tail = node;
    if (queue_is_empty(q)) {
        q->head = node;
    }
    q->size++;

    return SUCCESS;
}

QueueStatusCode queue_pop(Queue* q, void** data, size_t* nmeb) {
    if (data == NULL) {
        return NULL_DATA_ERROR;
    }
    if (queue_is_empty(q)) {
        return QUEUE_EMPTY_ERROR;
    }

    QueueNode* removed = q->head;
    q->head = removed->next;
    if (q->size == 1) {
        q->tail = NULL;
    }
    q->size--;

    *data = removed->data;
    if (nmeb != NULL) {
        *nmeb = removed->nmeb;
    }


    free(removed);
    return SUCCESS;
}