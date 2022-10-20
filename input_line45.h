#include <stdbool.h>
#include <stdint.h>
#include "creating_labyrinth_representation.h"
#include "structures.h"

#ifndef INPUT_LINE45_H
#define INPUT_LINE45_H

#define TEN 10
#define FOUR 4

extern int skip_spaces(int);

extern int skip_zeros(int);

bool hex_char(int);

extern void increase_current_value_R(uint32_t *, bool *, int);

extern bool read_line_5(void);

extern size_t more_for_hex(size_t);

extern bool accepted(Hexadecimal *, size_t, size_t, int);

extern void put_into_hex(Hexadecimal *, int);

extern bool read_hex(Hexadecimal *, size_t, int *);

extern void read_a_number(uint32_t *, bool *, int *);

extern bool read_R(R *, int *);

extern bool read_line_4(uint32_t *, size_t, int *, bool *);

#endif /* INPUT_LINE45_H */