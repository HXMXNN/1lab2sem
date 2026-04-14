#include "matrix.h"
#include <stdlib.h>

SquareMatrix* createMatrix(int n, IType* type) {
    SquareMatrix* m = malloc(sizeof(SquareMatrix));
    if (!m) return NULL;
    m->size = n;
    m->type = type;
    m->data = malloc(sizeof(void*) * n * n);
    for (int i = 0; i < n * n; i++) {
        m->data[i] = malloc(type->size);
    }
    return m;
}

int addRowCombination(SquareMatrix* m, int targetRow, void** alphas) {
    if (!m || targetRow < 0 || targetRow >= m->size) return 200;

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