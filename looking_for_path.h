#include <stdbool.h>
#include <stdint.h>
#include "input_line123.h"
#include "queue.h"
#include "structures.h"

#ifndef LOOKING_FOR_PATH_H
#define LOOKING_FOR_PATH_H

extern void push_neighbours_into_the_queue(Line, uint32_t *, Queue **, Queue_buckle **, 
                                            size_t, size_t, bool *, size_t, size_t);

extern bool bfs(Line, uint32_t *, size_t, size_t, size_t, size_t *);

#endif /* LOOKING_FOR_PATH_H */