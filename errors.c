#include "errors.h"
int clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    return 0;
}