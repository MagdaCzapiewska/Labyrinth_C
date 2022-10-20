#include <stdbool.h>
#include "structures.h"

#ifndef INPUT_LINE123_H
#define INPUT_LINE123_H

extern size_t more(size_t);

extern void put_in_an_array(Line *, size_t);

extern void increase_current_value(size_t *, bool *, int);

extern bool read_n(Line *, bool *);

extern bool not_able_to_allocate_memory(Line *, long long unsigned int *);

extern bool read_coordinates(size_t *, size_t *, Line, int);

#endif /* INPUT_LINE123_H */