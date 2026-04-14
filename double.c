#include <stdlib.h>
#include <stdio.h>
#include "double.h"

static IType* DOUBLE_TYPE_INSTANCE = NULL;

int doubleAdd(const void* a, const void* b, void* res) {
    *(double*)res = *(double*)a + *(double*)b;
    return 0;
}

int doubleMul(const void* a, const void* b, void* res) {
    *(double*)res = (*(double*)a) * (*(double*)b);
    return 0;
}

char* doublePrint(const void* a) {
    static char buf[32];
    sprintf(buf, "%.3f", *(double*)a);
    return buf;
}

IType* getDoubleType() {
    if (DOUBLE_TYPE_INSTANCE == NULL) {
        DOUBLE_TYPE_INSTANCE = malloc(sizeof(IType));
        DOUBLE_TYPE_INSTANCE->math = malloc(sizeof(TypeMath));
        DOUBLE_TYPE_INSTANCE->ops = malloc(sizeof(TypeOps));

        DOUBLE_TYPE_INSTANCE->size = sizeof(double);
        DOUBLE_TYPE_INSTANCE->typeId = 1;

        DOUBLE_TYPE_INSTANCE->math->add = doubleAdd;
        DOUBLE_TYPE_INSTANCE->math->mul = doubleMul;
        DOUBLE_TYPE_INSTANCE->ops->print = doublePrint;
        DOUBLE_TYPE_INSTANCE->ops->free = NULL;
    }
    return DOUBLE_TYPE_INSTANCE;
}

void freeDouble() {
    if (DOUBLE_TYPE_INSTANCE) {
        free(DOUBLE_TYPE_INSTANCE->math);
        free(DOUBLE_TYPE_INSTANCE->ops);
        free(DOUBLE_TYPE_INSTANCE);
        DOUBLE_TYPE_INSTANCE = NULL;
    }
}