#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include "creating_labyrinth_representation.h"
#include "bit_array.h"
#include "structures.h"
#include "multiple_usage.h"



/* Function allocate_an_array_and_fill_with_zeros() allocates memory that is needed
and fills it with zeros.
*/
void allocate_an_array_and_fill_with_zeros(uint32_t **representation, size_t product) {
    size_t number_of_cells = product / THIRTY_TWO;
    if ((product % THIRTY_TWO) != 0) {
        ++number_of_cells;
    }
    *representation = calloc(number_of_cells, sizeof(**representation));
}

/* Function convert_hex_to_bits() reads characters that occur in hexadecimal representation
of a number from an array and changes them to binary representation.
*/
void convert_hex_to_bits(Hexadecimal *hex, uint32_t *representation, size_t how_many_bits, bool *labyrinth_without_walls) {
    size_t index = 0;
    for (size_t i = hex->number_of_elements - 1; i > 0; --i) {
        int decimal = hex_char_value((hex->array)[i]);
        for (int j = 0; j < 4; ++j) {
            if ((decimal % 2) == 1) {
            set_bit(representation, index);
            *labyrinth_without_walls = false;
            }
            decimal /= 2;
            ++index;
        }
    }
    int decimal = hex_char_value((hex->array)[0]);
    for (int j = 0; j < 4; ++j) {
        if ((decimal % 2) == 1) {
            if (index < how_many_bits) {
                set_bit(representation, index);
                *labyrinth_without_walls = false;
            }
        }
        decimal /= 2;
        ++index;
    }
}

/* Function convert_R_to_bits() calculates s_1, s_2, ..., s_r, w_1, w_2, ..., w_r
and sets bits in labyrinth representation.
*/
void convert_R_to_bits(R numbers, uint32_t *representation, size_t how_many_bits, bool *labyrinth_without_walls) {
    size_t s_smaller_index = numbers.s_0;
    size_t s_bigger_index;
    size_t w;
    size_t maxi = SIZE_MAX - TWO_POW_THIRTY_TWO;

    for (uint32_t i = 1; i <= numbers.r; ++i) {
        s_bigger_index = (numbers.a * s_smaller_index + numbers.b) % numbers.m;
        w = s_bigger_index % how_many_bits;

        while (w < how_many_bits) {
            set_bit(representation, w);
            *labyrinth_without_walls = false;
            if (w < maxi) {
                w += TWO_POW_THIRTY_TWO;
            }
        }
        s_smaller_index = s_bigger_index;
    }
}