#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "int.h"
#include "double.h"

void run_extended_tests() {
    printf("\n>>> ЗАПУСК ТЕСТОВ (ВКЛЮЧАЯ КРАЙНИЕ СЛУЧАИ)\n");
    int passed = 0;

    for (int i = 1; i <= 30; i++) {
        IType* mType = (i % 2 == 0) ? getDoubleType() : getIntType();
        SquareMatrix* m = createMatrix(2, mType);

        double dVal = 1.1;
        int iVal = 5;
        void* alphas[2] = {NULL, NULL};

        int alphaType;
        if (i % 5 == 0) {
            alphaType = (mType->typeId == 0) ? 1 : 0;
            alphas[1] = (alphaType == 1) ? (void*)&dVal : (void*)&iVal;
        } else {
            alphaType = mType->typeId;
            alphas[1] = (alphaType == 1) ? (void*)&dVal : (void*)&iVal;
        }

        int res = addRowCombination(m, 0, alphas, alphaType);

        if (i % 5 == 0) {
            if (res == 200) {
                printf("Test #%d: OK (Ошибка несоответствия типов обнаружена)\n", i);
                passed++;
            } else {
                printf("Test #%d: FAILED (Программа должна была заблокировать неверный тип)\n", i);
            }
        } else {
            if (res == 0) {
                printf("Test #%d: OK (Корректное выполнение)\n", i);
                passed++;
            }
        }
        freeMatrix(m);
    }
    printf(">>> ИТОГО: %d/30 пройдены.\n", passed);
}

int main() {
    run_extended_tests();
    return 0;
}