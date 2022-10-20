#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <ctype.h>
#include "creating_labyrinth_representation.h"
#include "input_line45.h"
#include "structures.h"
#include "multiple_usage.h"

/* Function skip_spaces() skips characters that isspace() returns true for,
extept '\n'.
*/
int skip_spaces(int mark) {
    while(isspace(mark) && (mark != (int)('\n'))) {
        mark = getchar();
    }
    return mark;
}

/* Function skip_zeros() skips '0' characters.
*/
int skip_zeros(int mark) {
    while(mark == (int)('0')) {
        mark = getchar();
    }
    return mark;
}

/* Function hex_char() tells if a character is suitable to be a part of hexadecimal representation
of a number.
*/
bool hex_char(int c) {
    if (((c >= (int)('0')) && (c <= (int)('9'))) || ((c >= (int)('a')) && (c <= (int)('f')))
        || ((c >= (int)('A')) && (c <= (int)('F')))) {
            return true;
    }
    else {
        return false;
    }
}

/* Function increase_current_value() changes value of a number
as needed before reading next digit
*/
void increase_current_value_R(uint32_t *x, bool *result, int mark) {
    if (*x <= UINT32_MAX / TEN) {
        *x *= TEN;
        if (*x <= UINT32_MAX - (mark - (int)('0'))) {
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

/* Function read_line_5() reads the 5-th line of input if the 4-th was ended
by '\n'. Input is correct if there is no line 5 or it is only EOF in it.
*/
bool read_line_5(void) {
    int mark = getchar();
    if (mark != EOF) {
        return false;
    }
    else {
        return true;
    }
}

/* Function more() gives a number bigger than it's argument.
It will be used in reallocating the array. The factor is chosen
freely by a programmer and adding 1 makes it certain that if argument
is 0, returned value will be a positive number.
*/
size_t more_for_hex(size_t a) {
    if (a <= (SIZE_MAX / 2 - 1)) {
        return a * 2 + 1;
    }
    else {
        return (SIZE_MAX / 2);
    }
}

/* Function accepted() tells if hexadecimal number will be still small enough to represent labyrinth
if there will be another character added at the end
*/
bool accepted(Hexadecimal *h, size_t how_many_bits, size_t hmb_divided_by_four, int mark) {
    if (h->number_of_elements < hmb_divided_by_four) {
        return true;
    }
    else if (h->number_of_elements == hmb_divided_by_four) {
        int hmb_modulo_four = how_many_bits % 4; //This is the amount of leading zeros that should be found
                                                // in binary representation of (h->array)[0] in order
                                                // to enable acceptance.
        if (hmb_modulo_four == 0) {
            return false;
        }
        else {
            int decimal;
            if (h->number_of_elements > 0) {
                decimal = hex_char_value((int)((h->array)[0]));
            }
            else {
                decimal = hex_char_value((char)(mark));
            }
            int not_to_reach = 1; // Final version: not_to_reach = 2 ^ (hmb_modulo_four).
            for (int i = 1; i <= hmb_modulo_four; ++i) {
                not_to_reach *= 2;
            }
            
            if (decimal < not_to_reach) {
                return true;
            }
            else {
                return false;
            }
        }
    }
    else {
        return false;
    }
}

/* Function put_into_hex() increases the size of an array if needed
and puts a (int)(character) into an array.
It is always possible because n_1 * n_2 * ... * n_k (form the content of the task)
turned out earlier to be <= SIZE_MAX (if it had not, the program would have finished earlier). 
Each character stores information about 4 numbers from n_1 * n_2 * ... n_k numbers.
It means there are not more than SIZE_MAX / 4 cells needed. The computer can allocate
SIZE_MAX / 2 cells of type char in one array. 
*/
void put_into_hex(Hexadecimal *h, int c) {
    if (h->number_of_elements == h->array_length) {
        h->array_length = more_for_hex(h->array_length);
        h->array = realloc(h->array, sizeof(*(h->array)) * (h->array_length));
        if (h->array == NULL) {
            fprintf(stderr, "ERROR 0\n");
            exit(1);
        }
    }
    (h->array)[h->number_of_elements] = (char)(c);
    ++(h->number_of_elements);
}

/* Function read_hex() reads the 4-th line if it starts with "0x".
*/
bool read_hex(Hexadecimal *hex, size_t how_many_bits, int *mark) {
    bool result = true;
    bool found_zero_at_the_beginning = false;
    bool first = true;
    size_t hmb_divided_by_four = how_many_bits / FOUR; // So we do not have to count it every time.
    *mark = getchar();
    if (*mark == (int)('0')) {
        found_zero_at_the_beginning = true;
    }
    *mark = skip_zeros(*mark);

    if (((*mark) == EOF) || ((*mark) == (int)('\n'))) {
        if (found_zero_at_the_beginning) {
            put_into_hex(hex, (int)('0'));
        }
        else {
            result = false;
        }
    }
    else {
        bool reading_in_progress = true;
        while (result && reading_in_progress) {
            if (!first) {
                *mark = getchar();
            }
            if (!hex_char(*mark)) {
                if(!isspace(*mark)) {
                    result = false;
                }
                else if (isspace(*mark)) {
                    if ((*mark) == (int)('\n')) {
                        if (hex->number_of_elements == 0) {
                            result = false;
                        }
                        else {
                            reading_in_progress = false; // But result remains true.
                        }
                    }
                    else {
                        reading_in_progress = false;
                    }
                }
            }
            else {
                if (accepted(hex, how_many_bits, hmb_divided_by_four, *mark)) {
                    put_into_hex(hex, *mark);
                }
                else {
                    result = false; // Hexadecimal number is too big.
                }
            }
            first = false;
        }
    }

    if (result) { // White space was found and there should be only white spaces until '\n' or EOF.
        *mark = skip_spaces(*mark);
        if (((*mark) != EOF) && ((*mark) != (int)('\n'))) {
            result = false;
        }
    }
    return result;

}

/* Function read_a_number() reads a number when reading "R line".
*/
void read_a_number(uint32_t *x, bool *result, int *mark) {
    *mark = getchar();
    while (isdigit(*mark)) {
        increase_current_value_R(x, result, *mark);
        *mark = getchar();
    }
    *mark = skip_spaces(*mark);
}

/* Function read_R() reads the 4-th line if it starts with 'R'.
*/
bool read_R(R *numbers, int *mark) {
    bool result = true;
    uint32_t x;
    *mark = getchar();
    *mark = skip_spaces(*mark);
    if (!isdigit(*mark)) {
        result = false;
    }
    else {
        x = (*mark) - (int)('0');
        read_a_number(&x, &result, mark);
        if (result) { // It means function read_a_number has not read anything above UINT32_MAX.
            numbers->a = x;
        }
        if (!isdigit(*mark)) {
            result = false;
        }
        else {
            x = (*mark) - (int)('0');
            read_a_number(&x, &result, mark);
            if (result) {
                numbers->b = x;
            }
            if (!isdigit(*mark)) {
                result = false;
            }
            else {
                x = (*mark) - (int)('0');
                read_a_number(&x, &result, mark);
                if (result && (x != 0)) {
                    numbers->m = x;
                }
                else {
                    result = false;
                }
                if (!isdigit(*mark)) {
                    result = false;
                }
                else {
                    x = (*mark) - (int)('0');
                    read_a_number(&x, &result, mark);
                    if (result) {
                        numbers->r = x;
                    }
                    if (!isdigit(*mark)) {
                        result = false;
                    }
                    else {
                        x = (*mark) - (int)('0');
                        read_a_number(&x, &result, mark);
                        if (result) {
                            numbers->s_0 = x;
                        }
                        if(!(((*mark) == EOF) || ((*mark) == (int)('\n')))) {
                            result = false;
                        }
                    }
                }
            }
        }
    }

    return result;
}

/* Function read_line_4() reads the 4-th line of input.
*/
bool read_line_4(uint32_t *representation, size_t how_many_bits, int *mark, bool *labyrinth_without_walls) {
    bool result = true;
    *mark = getchar();
    *mark = skip_spaces(*mark);

    if (((*mark) != (int)('0')) && ((*mark) != (int)('R'))) { // Also handles the situation when mark
                                                        // is (int)('\n') or EOF. 
        result = false;
    }
    else if ((*mark) == (int)('0')) {
        (*mark) = getchar();
        if ((*mark) == (int)('x')) {
            Hexadecimal hex;
            hex.array = NULL;
            hex.array_length = 0;
            hex.number_of_elements = 0;
            result = read_hex(&hex, how_many_bits, mark);
            if (!result) {
                free(hex.array);
            }
            else {
                convert_hex_to_bits(&hex, representation, how_many_bits, labyrinth_without_walls);
                free(hex.array);
            }
        }
        else {
            result = false;
        }
    }
    else if ((*mark) == (int)('R')) {
        R numbers;
        numbers.a = 0; numbers.b = 0; numbers.m = 0; numbers.r = 0, numbers.s_0 = 0;
        result = read_R(&numbers, mark);

        if(result) {
            convert_R_to_bits(numbers, representation, how_many_bits, labyrinth_without_walls);
        }
    }

    return result;
}