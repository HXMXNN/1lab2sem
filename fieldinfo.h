#ifndef FIELDINFO_H
#define FIELDINFO_H

#include <stddef.h>

typedef struct FieldInfo {
    size_t elementSize;
    void* (*sum)(const void*, const void*);
    void* (*mul)(const void*, const void*);
    void* (*scalarMul)(const void*, const void*);
    char* (*toString)(const void*, const void*);
    int (*freeElement)(void*);
} FieldInfo;

#endif