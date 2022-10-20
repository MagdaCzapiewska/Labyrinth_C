#include <stdbool.h>

#ifndef BIT_ARRAY_H
#define BIT_ARRAY_H

#define THIRTY_TWO 32

void set_bit(uint32_t *, size_t);

void clear_bit(uint32_t *, size_t);

bool test_bit(uint32_t *, size_t);

#endif /* BIT_ARRAY_H */