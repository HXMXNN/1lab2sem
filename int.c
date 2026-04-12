#include <stdlib.h>
#include <stdio.h>
#include "int.h"

static IType* INT_TYPE_INSTANCE = NULL;

int intAdd(const void* a, const void* b, void* res) {
    *(int*)res = *(int*)a + *(int*)b;
    return 0;
}
int intMul(const void* a, const void* b, void* res) {
    *(int*)res = (*(int*)a) * (*(int*)b);
    return 0;
}
char* intPrint(const void* a) {
    static char buf[32];
    sprintf(buf, "%d", *(int*)a);
    return buf;
}

IType* getIntType() {
    if (INT_TYPE_INSTANCE == NULL) {
        INT_TYPE_INSTANCE = malloc(sizeof(IType));
        INT_TYPE_INSTANCE->funcs = malloc(sizeof(TypeFuncs));
        INT_TYPE_INSTANCE->size = sizeof(int);
        INT_TYPE_INSTANCE->typeId = 0;
        INT_TYPE_INSTANCE->funcs->add = intAdd;
        INT_TYPE_INSTANCE->funcs->mul = intMul;
        INT_TYPE_INSTANCE->funcs->print = intPrint;
    }
    return INT_TYPE_INSTANCE;
}

void freeINT() {
    if (INT_TYPE_INSTANCE) {
        free(INT_TYPE_INSTANCE->funcs);
        free(INT_TYPE_INSTANCE);
        INT_TYPE_INSTANCE = NULL;
    }
}