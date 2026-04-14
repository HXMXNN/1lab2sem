#include "matrix.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

SquareMatrix* createMatrix(int n, IType* type) {
    SquareMatrix* m = malloc(sizeof(SquareMatrix));
    if (!m) return NULL;
    m->size = n;
    m->type = type;
    m->data = malloc(sizeof(void*) * n * n);
    for (int i = 0; i < n * n; i++) {
        m->data[i] = malloc(type->size);
        memset(m->data[i], 0, type->size);
    }
    return m;
}

SquareMatrix* addMatrices(SquareMatrix* a, SquareMatrix* b) {
    if (a->size != b->size || a->type->typeId != b->type->typeId) return NULL;
    SquareMatrix* res = createMatrix(a->size, a->type);
    for (int i = 0; i < a->size * a->size; i++) {
        a->type->math->add(a->data[i], b->data[i], res->data[i]);
    }
    return res;
}

int scaleMatrix(SquareMatrix* m, void* scalar) {
    if (!m || !scalar) return 1;
    for (int i = 0; i < m->size * m->size; i++) {
        m->type->math->mul(m->data[i], scalar, m->data[i]);
    }
    return 0;
}

SquareMatrix* multiplyMatrices(SquareMatrix* a, SquareMatrix* b) {
    if (a->size != b->size || a->type->typeId != b->type->typeId) return NULL;
    int n = a->size;
    SquareMatrix* res = createMatrix(n, a->type);
    void* tempMul = malloc(a->type->size);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                a->type->math->mul(a->data[i * n + k], b->data[k * n + j], tempMul);
                a->type->math->add(res->data[i * n + j], tempMul, res->data[i * n + j]);
            }
        }
    }
    free(tempMul);
    return res;
}

int addRowCombination(SquareMatrix* m, int targetRow, void** alphas, int alphaTypeId) {
    if (!m || targetRow < 0 || targetRow >= m->size) return 200;
    if (m->type->typeId != alphaTypeId) {
        printf("\n[ОШИБКА ТИПА]: Несовпадение Matrix(%d) и Alpha(%d)\n", m->type->typeId, alphaTypeId);
        return 200;
    }
    void* scaled = malloc(m->type->size);
    int n = m->size;
    for (int j = 0; j < n; j++) {
        for (int k = 0; k < n; k++) {
            if (k == targetRow || alphas[k] == NULL) continue;
            m->type->math->mul(m->data[k * n + j], alphas[k], scaled);
            m->type->math->add(m->data[targetRow * n + j], scaled, m->data[targetRow * n + j]);
        }
    }
    free(scaled);
    return 0;
}

void freeMatrix(SquareMatrix* m) {
    if (!m) return;
    for (int i = 0; i < m->size * m->size; i++) free(m->data[i]);
    free(m->data);
    free(m);
}