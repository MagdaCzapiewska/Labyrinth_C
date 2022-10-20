#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "queue.h"
#include "input_line123.h"
#include "looking_for_path.h"
#include "bit_array.h"
#include "structures.h"

/* Function push_neighbours_into_the_queue() looks for empty cubes in the labyrinth that are only 1 step
apart from cube with an index that is given as an argument and puts them at the end of the queue
*/
void push_neighbours_into_the_queue(Line n, uint32_t *representation, Queue **q, Queue_buckle **b, 
                                    size_t index, size_t distance, bool *success, 
                                    size_t product, size_t y) {
    size_t jump = 1; // Variable jump tells what is the difference in indexes of neighbours.
    size_t checker = 1; // Sometimes even if two cubes' indexes difference is jump, they are not
                        // neighbours. They have to give the same result when divided by checker.
    size_t i = 0;

    while (!(*success) && (i < n.k)) {
        checker *= (n.content)[i];
        if (index >= jump) {
            if ((index / checker) == ((index - jump) / checker)) {
                if (!test_bit(representation, index - jump)) {
                    set_bit(representation, index - jump);
                    push(q, b, distance, index - jump);
                    if ((index - jump) == y) {
                        *success = true;
                    }
                }
            }
        }
        if (index <= product - jump) {
            if ((index / checker) == ((index + jump) / checker)) {
                if (!test_bit(representation, index + jump)) {
                    set_bit(representation, index + jump);
                    push(q, b, distance, index + jump);
                    if ((index + jump) == y) {
                        *success = true;
                    }
                }
            }
        }
        jump = checker;
        ++i;
    }
}

/* Fuction bfs() performs BFS algorithm and returns true if y is reachable from x
*/
bool bfs(Line n, uint32_t *representation, size_t product, size_t x, size_t y, size_t *path) {
    bool destination_reached = false;
    Queue *q;
    Queue_buckle *b;
    
    init(&q, &b);
    push(&q, &b, 0, x);

    while(!empty(q) && !destination_reached) {
        push_neighbours_into_the_queue(n, representation, &q, &b, first(q), (q->next)->value + 1, 
                                        &destination_reached, product, y);
        pop(&q, &b);
    }

    if (destination_reached) {
        *path = (b->ending)->value;
    }

    delete_queue(&q, &b);

    return destination_reached;
}