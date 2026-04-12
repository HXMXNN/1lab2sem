#include "matrix.h"
#include <stdlib.h>
#include <string.h>

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

void freeMatrix(SquareMatrix* m) {
    if (!m) return;
    for (int i = 0; i < m->size * m->size; i++) {
        free(m->data[i]);
    }
    free(m->data);
    free(m);
}

int addRowCombination(SquareMatrix* m, int targetRow, void** alphas) {
    if (!m || targetRow < 0 || targetRow >= m->size) return 200;
    void* scaled = malloc(m->type->size);
    int n = m->size;

    for (int j = 0; j < n; j++) {
        for (int k = 0; k < n; k++) {
            if (k == targetRow || alphas[k] == NULL) continue;
            m->type->funcs->mul(m->data[k * n + j], alphas[k], scaled);
            m->type->funcs->add(m->data[targetRow * n + j], scaled, m->data[targetRow * n + j]);
        }
    }
    free(scaled);
    return 0;
}