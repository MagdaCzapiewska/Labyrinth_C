#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "queue.h"
#include "structures.h"

/* Function empty() gives true if there is only a dummy in a queue and false otherwise.
*/
bool empty(Queue *q) {
    if(q->next == NULL) {
        return true;
    }
    else {
        return false;
    }
}

/* Function init() allocates memory when new queue is initialised.
*/
void init(Queue **q, Queue_buckle **b) {
    *q = malloc(sizeof(**q));
    (*q)->next = NULL;
    (*q)->value = 0;
    (*q)->index = 0;

    *b = malloc(sizeof(**b));
    (*b)->beginning = *q;
    (*b)->ending = *q;

    if ((q == NULL) || (b == NULL)) {
        fprintf(stderr, "ERROR 0\n");
        exit(1);
    }
}

/* Function push() put an element at the end of a queue.
*/
void push(Queue **q, Queue_buckle **b, size_t value, size_t index) {
    Queue *new_element = malloc(sizeof(**q));
    if (new_element == NULL) {
        fprintf(stderr, "ERROR 0\n");
        exit(1);
    }
    ((*b)->ending)->next = new_element;
    (*b)->ending = new_element;

    new_element->value = value;
    new_element->index = index;
    new_element->next = NULL;
}

/* Function pop() deletes an element at the beginning of a queue (after a dummy)
*/
void pop(Queue **q, Queue_buckle **b) {
    if(!empty(*q)) {
        if ((*q)->next == (*b)->ending) {
            (*b)->ending = *q;
        }
        Queue *help = ((*q)->next)->next;
        free((*q)->next);
        (*q)->next = help;
    }
}

/* Function first() gives (first element of a queue after a dummy)->index and 0 if there is only a dummy
*/
size_t first(Queue *q) {
    if (q->next != NULL) {
        return (q->next)->index;
    }
    else {
        return 0;
    }
}

/* Function delete() deallocates memory after a queue is no longer needed
*/
void delete_queue(Queue **q, Queue_buckle **b) {
    free(*b);
    Queue *help_1 = *q;
    Queue *help_2;
    
    while (help_1 != NULL) {
        help_2 = help_1->next;
        free(help_1);
        help_1 = help_2;
    }
}

