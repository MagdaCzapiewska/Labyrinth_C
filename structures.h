#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct hexadecimal {
    char *array;
    size_t array_length;
    size_t number_of_elements;
} Hexadecimal;

typedef struct r {
    uint32_t a;
    uint32_t b;
    uint32_t m;
    uint32_t r;
    uint32_t s_0;
} R;

typedef struct line {
    size_t *content;
    size_t k;
    size_t length_of_the_array;
} Line;

typedef struct queue {
    size_t index;
    size_t value;
    struct queue *next;
} Queue;

typedef struct queue_buckle {
    Queue *beginning;
    Queue *ending;
} Queue_buckle;

#endif /* STRUCTURES_H */