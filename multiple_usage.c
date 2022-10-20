#include <stdio.h>

/* Function hex_char_value() converts one of characters in hexadecimal number into its value
in decimal system. Assumption: hex_char(c) == true (look: input_line45.c).
*/
int hex_char_value(int c) {
    if ((c >= (int)('0')) && (c <= (int)('9'))) {
        return c - (int)('0');
    }
    else if ((c >= (int)('a')) && (c <= (int)('f'))) {
        return c - (int)('a') + 10;
    }
    else if ((c >= (int)('A')) && (c <= (int)('F'))) {
        return c - (int)('A') + 10;
    }
    return -1; // It will never happen if this function is induced only when hex_char(c) == true.
}