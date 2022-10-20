#include <stdbool.h>
#include <stdint.h>
#include "structures.h"

#ifndef CREATING_LABYRINTH_REPRESENTATION_H
#define CREATING_LABYRINTH_REPRESENTATION_H

#define THIRTY_TWO 32
#define TWO_POW_THIRTY_TWO 4294967296

extern int hex_char_value(int);

extern void allocate_an_array_and_fill_with_zeros(uint32_t **, size_t);

extern void convert_hex_to_bits(Hexadecimal *, uint32_t *, size_t, bool *);

extern void convert_R_to_bits(R, uint32_t *, size_t, bool *);

#endif /* CREATING_LABYRINTH_REPRESENTATION_H */