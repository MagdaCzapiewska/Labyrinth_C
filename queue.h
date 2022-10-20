#include "structures.h"

#ifndef QUEUE_H
#define QUEUE_H

extern bool empty(Queue *);

extern void init(Queue **, Queue_buckle **);

extern void push(Queue **, Queue_buckle **, size_t, size_t);

extern void pop(Queue **, Queue_buckle **);

extern size_t first(Queue *);

extern void delete_queue(Queue **, Queue_buckle **);

#endif /* QUEUE_H */

