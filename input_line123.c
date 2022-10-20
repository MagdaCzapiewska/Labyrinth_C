#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include "input_line123.h"
#include "structures.h"

#define THIRTY_TWO 32
#define SIXTEEN 16
#define TEN 10
#define EIGHT 8

/* Function more() gives a number bigger than it's argument.
It will be used in reallocating the array. The factor is chosen
freely by a programmer and adding 1 makes it certain that if argument
is 0, returned value will be a positive number.
*/
size_t more(size_t a) {
    if (a <= (SIZE_MAX / THIRTY_TWO - 1)) {
        return a * 2 + 1;
    }
    else {
        return (SIZE_MAX / SIXTEEN);
    }
}

/* Function put_in_an_array() increases the size of an array if needed
and puts a number in an array.
*/
void put_in_an_array(Line *n, size_t x) {
    if (n->k == n->length_of_the_array) {
        n->length_of_the_array = more(n->length_of_the_array);
        n->content = realloc(n->content, sizeof(size_t) * (n->length_of_the_array));
        if (n->content == NULL) {
            fprintf(stderr, "ERROR 0\n");
            exit(1);
        }
    }
    (n->content)[n->k] = x;
    ++(n->k);
}

/* Function increase_current_value() changes value of a number
as needed before reading next digit
*/
void increase_current_value(size_t *x, bool *result, int mark) {
    if (*x <= SIZE_MAX / TEN) {
        *x *= TEN;
        if (*x <= SIZE_MAX - (mark - (int)('0'))) {
             *x += (mark - (int)('0'));
        }
        else {
            *result = false;
        }
    }
    else {
        *result = false;
    }
}

/* Function read_n() reads n_1, n_2, ..., n_k, memorises them 
in dynamically allocated array and memorises k.
It returns false, if ERROR 1 or ERROR 0 should be written, and true otherwise.
*/
bool read_n(Line *n, bool *memory) {
    int mark;
    bool result = true;

    mark = getchar();
    while (mark != (int)('\n')) {
        if (mark == EOF) {
            if (result && (n->k >= 1)) { // Line 1 is correct, but there is no line 2.
                printf("ERROR 2\n");
            }
            else { // Data in line 1 is incorrect.
                printf("ERROR 1\n");
            }
            free(n->content);
            exit(1);
        }
        else if ((!isspace(mark)) && (!isdigit(mark))) {
            result = false; //especially if mark == (int)('-')
            mark = getchar();
        }
        else if (isdigit(mark)) {
            size_t x = mark - (int)('0');
            mark = getchar();

            while (isdigit(mark)) {
                increase_current_value(&x, &result, mark);
                mark = getchar();
            }    
            if (x == 0) {
                result = false;
            }
            if (result) {
                if (n->k < (SIZE_MAX / SIXTEEN - 1)) {
                    put_in_an_array(n, x);
                }
                else {
                    *memory = false;
                    result = false;
                }
            }
        }
        else if (isspace(mark)) {
            mark = getchar();
        }
    }
    return result;
}

/* Function not_able_to_allocate_memory() returns true if the product
n_1 * n_2 * ... * n_k, equated with the size of the labyrinth,
is bigger than SIZE_MAX
*/
bool not_able_to_allocate_memory(Line *n, long long unsigned int *help) {
    bool result = false;
    
    // Due to the action performed by function read_n() it is
    // certain that every element of n->content is no bigger than
    // SIZE_MAX

    if (n->k == 1) {
        *help = (n->content)[0];
    }
    if (n->k >= 2) { // if (n->k == 1) the result remains false
        size_t factor_1 = (n->content)[0], factor_2 = (n->content)[1];
        result = __builtin_umulll_overflow(factor_1, factor_2, help);
        size_t i = 2;
        while ((!result) && (i < n->k)) {
            factor_1 = (*help);
            factor_2 = (n->content)[i];
            result = __builtin_umulll_overflow(factor_1, factor_2, help);
            ++i;
        }
    }
    
    return result;
}

/* Function read_coordinates() reads cube coordinates and produces
the index of the cube in an array that is representation of a labyrinth.
It returns false, if ERROR 2 or ERROR 3 should be written, and true otherwise.
*/
bool read_coordinates(size_t *cube, size_t *the_other_cube, Line n, int error_number) {
    int mark;
    bool result = true;

    mark = getchar();
    size_t factor = 1;
    size_t which_coordinate = 1;
    while (mark != (int)('\n')) {
        if (mark == EOF) {
            printf("ERROR %d\n", error_number);
            free(n.content);
            free(cube);
            free(the_other_cube);
            exit(1);
        }
        else if ((!isspace(mark)) && (!isdigit(mark))) {
            result = false; //especially if mark == (int)('-')
            mark = getchar();
        }
        else if (isdigit(mark)) {
            size_t x = mark - (int)('0');
            mark = getchar();

            while (isdigit(mark)) {
                increase_current_value(&x, &result, mark);
                mark = getchar();
            }    
            if (x == 0) {
                result = false;
            }
            if (result) {
                long long unsigned int help_1, help_2;
                if (which_coordinate > n.k) {
                    result = false;
                }
                else if (which_coordinate > 1) {
                    result = !(__builtin_umulll_overflow(factor, (n.content)[which_coordinate - 2], &help_1));
                    ++which_coordinate;
                    if (result) {
                        factor = help_1;
                    }
                }
                else { //which_coordinate == 1
                    ++which_coordinate;
                }
                if (result) {
                    if (x > (n.content)[which_coordinate - 2]) {
                    result = false;
                    }
                    else {
                        result = !(__builtin_umulll_overflow(x - 1, factor, &help_1));
                        if (result) {
                            result = !(__builtin_uaddll_overflow(help_1, *cube, &help_2));
                            if (result) {
                                *cube = help_2;
                            }
                        }
                    }
                }
            }
        }
        else if (isspace(mark)) {
            mark = getchar();
        }
    }
    if (which_coordinate < ((n.k) + 1)) {
        result = false;
    }

    return result;
}