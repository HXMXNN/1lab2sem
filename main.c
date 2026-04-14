#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "int.h"
#include "double.h"

int run_auto_tests() {
    printf("\n>>> ЗАПУСК АВТОМАТИЧЕСКИХ ТЕСТОВ (30 СЦЕНАРИЕВ)\n");
    int passed = 0;

    for (int i = 1; i <= 30; i++) {
        IType* currentType = (i % 2 == 0) ? getDoubleType() : getIntType();
        int size = (i % 3) + 2;

        SquareMatrix* m = createMatrix(size, currentType);

        double dFactor = 1.5;
        int iFactor = 2;
        void* alphas[4] = {NULL, NULL, NULL, NULL};
        alphas[1] = (i % 2 == 0) ? (void*)&dFactor : (void*)&iFactor;

        if (addRowCombination(m, 0, alphas) == 0) {
            printf("Test #%d: OK (Size %d, Type %d)\n", i, size, currentType->typeId);
            passed++;
        }
        freeMatrix(m);
    }
    printf(">>> ИТОГО: %d/30 пройдены.\n\n", passed);
    return passed;
}

int main() {
    int testTrigger = 1;
    if (testTrigger) run_auto_tests();

    int choice = -1;
    SquareMatrix* currentMat = NULL;

    while (choice != 0) {
        printf("=== МЕНЮ МАТРИЦЫ ===\n");
        printf("1. Создать новую матрицу (Int)\n");
        printf("2. Создать новую матрицу (Double)\n");
        printf("3. Линейная комбинация строк\n");
        printf("4. Вывести на экран\n");
        printf("0. Выход\n");
        printf("Выбор: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
            case 2:
                if (currentMat) freeMatrix(currentMat);
                currentMat = createMatrix(3, (choice == 1) ? getIntType() : getDoubleType());
                printf("Матрица 3x3 создана.\n");
                break;
            case 3:
                printf("Выполняется расчет...\n");
                break;
            case 4:
                if (currentMat) {
                    for (int i = 0; i < currentMat->size; i++) {
                        for (int j = 0; j < currentMat->size; j++) {
                            printf("%s\t", currentMat->type->ops->print(currentMat->data[i * currentMat->size + j]));
                        }
                        printf("\n");
                    }
                }
                break;
            case 0:
                printf("Завершение.\n");
                break;
        }
    }
    if (currentMat) freeMatrix(currentMat);
    freeINT();
    freeDouble();
    return 0;
}