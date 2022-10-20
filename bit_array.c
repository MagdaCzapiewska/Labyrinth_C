// Source: http://www.mathcs.emory.edu/~cheung/Courses/255/Syllabus/1-C-intro/bit-array.html

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "bit_array.h"

/* Function set_bit() sets the k-th bit in the bit array A
*/
void set_bit(uint32_t *A, size_t k) {
    size_t i = k / THIRTY_TWO;
    size_t pos = k % THIRTY_TWO;

    unsigned int flag = 1; // flag = 00...001
    flag = flag << pos;

    A[i] = A[i] | flag;
}

/* Function clear_bit() clears the k-th bit in the bit array A
*/
void clear_bit(uint32_t *A, size_t k) {
    size_t i = k / THIRTY_TWO;
    size_t pos = k % THIRTY_TWO;

    unsigned int flag = 1; // flag = 00...001
    flag = flag << pos;
    flag = ~flag;

    A[i] = A[i] & flag;
}

/* Function test_bit() tests the k-th bit in the bit array A
*/
bool test_bit(uint32_t *A, size_t k) {
    size_t i = k / THIRTY_TWO;
    size_t pos = k % THIRTY_TWO;

    unsigned int flag = 1; // flag = 00...001
    flag = flag << pos;

    if (A[i] & flag) {
        return true; // bit is 1
    }
    else {
        return false; // bit is 0
    }
}