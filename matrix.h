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

SquareMatrix* addMatrices(SquareMatrix* a, SquareMatrix* b);
SquareMatrix* multiplyMatrices(SquareMatrix* a, SquareMatrix* b);
int scaleMatrix(SquareMatrix* m, void* scalar);
int addRowCombination(SquareMatrix* m, int targetRow, void** alphas, int alphaTypeId);

#endif