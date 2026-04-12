#ifndef MATRIX_H
#define MATRIX_H

#include "itype.h"

typedef struct {
    int size;
    IType *type;
    void **data;
} SquareMatrix;

SquareMatrix* createMatrix(int n, IType* type);
void freeMatrix(SquareMatrix* m);
int addRowCombination(SquareMatrix* m, int targetRow, void** alphas);

#endif