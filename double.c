#include <stdlib.h>
#include <stdio.h>
#include "double.h"

static IType* DOUBLE_TYPE_INSTANCE = NULL;

int doubleAdd(const void* a, const void* b, void* res) {
    if (!a || !b || !res) return 100;
    *(double*)res = *(double*)a + *(double*)b;
    return 0;
}

int doubleMul(const void* a, const void* b, void* res) {
    if (!a || !b || !res) return 100;
    *(double*)res = (*(double*)a) * (*(double*)b);
    return 0;
}

char* doublePrint(const void* a) {
    static char buf[64];
    sprintf(buf, "%.3f", *(double*)a);
    return buf;
}

int doubleFree(void* a) {
    return 0;
}

IType* getDoubleType() {
    if (DOUBLE_TYPE_INSTANCE == NULL) {
        DOUBLE_TYPE_INSTANCE = malloc(sizeof(IType));
        if (!DOUBLE_TYPE_INSTANCE) return NULL;

        DOUBLE_TYPE_INSTANCE->math = malloc(sizeof(TypeMath));
        DOUBLE_TYPE_INSTANCE->ops = malloc(sizeof(TypeOps));

        DOUBLE_TYPE_INSTANCE->size = sizeof(double);
        DOUBLE_TYPE_INSTANCE->typeId = 1;

        DOUBLE_TYPE_INSTANCE->math->add = doubleAdd;
        DOUBLE_TYPE_INSTANCE->math->mul = doubleMul;

        DOUBLE_TYPE_INSTANCE->ops->print = doublePrint;
        DOUBLE_TYPE_INSTANCE->ops->free = doubleFree;
    }
    return DOUBLE_TYPE_INSTANCE;
}

void freeDouble() {
    if (DOUBLE_TYPE_INSTANCE) {
        if (DOUBLE_TYPE_INSTANCE->math) free(DOUBLE_TYPE_INSTANCE->math);
        if (DOUBLE_TYPE_INSTANCE->ops) free(DOUBLE_TYPE_INSTANCE->ops);
        free(DOUBLE_TYPE_INSTANCE);
        DOUBLE_TYPE_INSTANCE = NULL;
    }
}