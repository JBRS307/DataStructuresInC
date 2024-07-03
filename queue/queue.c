#include <stdlib.h>

#include "queue.h"

Queue queue_init() {
    Queue q;
    q.head = NULL;
    q.tail = NULL;
    q.size = 0;
    return q;
}