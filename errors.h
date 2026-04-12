#ifndef ERRORS_H
#define ERRORS_H
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    memoAllocFailed = 100,
    differentTypes = 200,
    success = 0,
} errors;

int clear_input_buffer();
#endif