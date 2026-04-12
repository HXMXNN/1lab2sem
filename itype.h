#ifndef ITYPE_H
#define ITYPE_H

#include <stddef.h>

typedef struct {
    int (*add)(const void* a, const void* b, void* res);
    int (*mul)(const void* a, const void* b, void* res);
    char* (*print)(const void* a);
    int (*free)(void* a);
} TypeFuncs;

typedef struct {
    size_t size;
    int typeId;
    TypeFuncs *funcs;
} IType;

#endif