#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "input_line123.h"
#include "creating_labyrinth_representation.h"
#include "looking_for_path.h"
#include "input_line45.h"
#include "bit_array.h"
#include "structures.h"

/* Function finish() frees memory and writes about an error.
*/
void finish(size_t *a, size_t *b, size_t *c, int number) {
    free(a);
    free(b);
    free(c);
    fprintf(stderr, "ERROR %d\n", number);
    exit(1);
}

int main(void) {
    Line n; // This struct is declared in structures.h. It stores data n_1, n_2, ... n_k.
    size_t product = 0; // Variable declared to contain n_1 * n_2 * ... * n_k.
    long long unsigned int help;

    n.content = NULL;
    n.k = 0;
    n.length_of_the_array = 0;

    bool memory = true; // Bool memory tells if n.k is small enough, so it is possible
    // to store all the n_1, n_2, ..., n_k.
    bool result = read_n(&n, &memory);
    if (!memory || not_able_to_allocate_memory(&n, &help)) {
        finish(n.content, NULL, NULL, 0);
    }
    else if (!result) {
        finish(n.content, NULL, NULL, 1);
    }

    product = help;

    if (n.k == 0) {
        finish(n.content, NULL, NULL, 1);
    }

    size_t *start = malloc(sizeof(*start)); // *start will store index of a cube which is a starting point.
    size_t *end = malloc(sizeof(*end)); // *end will store index  of a cube which is destination.
    *start = 0;
    *end = 0;

    if ((start == NULL) || (end == NULL)) {
        finish(n.content, start, end, 0);
    }

    if (!read_coordinates(start, end, n, 2)) {
        finish(n.content, start, end, 2);
    }

    if (!read_coordinates(end, start, n, 3)) {
        finish(n.content, start, end, 3);
    }
    
    uint32_t *representation = NULL;
    allocate_an_array_and_fill_with_zeros(&representation, product);

    if (representation == NULL) {
        finish(n.content, start, end, 0);
    }

    int mark;
    bool labyrinth_without_walls = true;
    result = read_line_4(representation, product, &mark, &labyrinth_without_walls);

    if (!result) {
        free(representation);
        finish(n.content, start, end, 4);
    }
    else { // mark == EOF || mark == (int)('\n')
        if (mark == (int)('\n')) {
            result = read_line_5();
        }
    }

    if (!result) {
        free(representation);
        finish(n.content, start, end, 5);
    }
    else {
        if (test_bit(representation, *start)) {
            free(representation);
            finish(n.content, start, end, 2);
        }
        else if (test_bit(representation, *end)) {
            free(representation);
            finish(n.content, start, end, 3);
        }
        size_t path;

        if (*start == *end) {
            path = 0;
        }
        else if (labyrinth_without_walls) {
            // Corner case: There are no walls in the labyrinth. There are
            // several steps to make in each dimension. One step in a labyrinth
            // can change a coordinate in only one dimension and only by one.
            // So minimum number of steps needed is a sum of steps in every dimension.
            path = 0;
            size_t start_cube = *start;
            size_t end_cube = *end;
            size_t old_product = 1;
            size_t new_product = 1;
            for (size_t i = 0; i < n.k; ++i) {
                new_product *= n.content[i];
                size_t x_coordinate = (start_cube % new_product) / old_product + 1;
                size_t y_coordinate = (end_cube % new_product) / old_product + 1;
                path += abs((int)(x_coordinate - y_coordinate));

                start_cube = (start_cube - (x_coordinate - 1) * old_product);
                end_cube = (end_cube - (y_coordinate - 1) * old_product);

                old_product = new_product;
            }
        }
        else {
            result = bfs(n, representation, product, *start, *end, &path);
        }

        if(!result) {
            printf("NO WAY\n");
        }
        else{
            printf("%lu\n", path);
        }
        free(representation);
        free(n.content);
        free(start);
        free(end);
    }
    
    return 0;
}