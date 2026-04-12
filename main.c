#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "int.h"
#include "double.h"
#include "io.h"
#include "errors.h"
#include <windows.h>

int run_auto_tests() {
    printf("\n>>> ЗАПУСК АВТОМАТИЧЕСКИХ ТЕСТОВ (30 СЦЕНАРИЕВ)\n");
    int passed = 0;

    for (int i = 1; i <= 30; i++) {
        IType* currentType = (i % 2 == 0) ? getDoubleType() : getIntType();
        int size = (i % 3) + 2;

        SquareMatrix* m = createMatrix(size, currentType);
        if (!m) continue;

        double dFactor = 1.5;
        int iFactor = 2;
        void* alphas[10] = {NULL};

        alphas[1] = (currentType->typeId == 1) ? (void*)&dFactor : (void*)&iFactor;

        if (addRowCombination(m, 0, alphas) == 0) {
            printf("Test #%d: OK (Size %d, TypeId %d)\n", i, size, currentType->typeId);
            passed++;
        }

        freeMatrix(m);
    }
    printf(">>> ИТОГО: %d/30 пройдены.\n\n", passed);
    return passed;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    int testTrigger = 1;
    if (testTrigger) {
        run_auto_tests();
        waitForEnter();
    }

    int choice = -1;
    SquareMatrix* currentMat = NULL;

    while (choice != 0) {
        CLEAR_SCREEN();
        printf("=== МЕНЮ УПРАВЛЕНИЯ КВАДРАТНЫМИ МАТРИЦАМИ ===\n");
        printf("1. Создать новую матрицу (Int)\n");
        printf("2. Создать новую матрицу (Double)\n");
        printf("3. Линейная комбинация строк\n");
        printf("4. Вывести текущую матрицу\n");
        printf("0. Выход\n");
        printf("Выбор: ");

        if (scanf("%d", &choice) != 1) {
            clear_input_buffer();
            continue;
        }

        switch (choice) {
            case 1:
            case 2: {
                int n;
                printf("Введите размер квадратной матрицы (N): ");
                scanf("%d", &n);
                if (currentMat) freeMatrix(currentMat);
                currentMat = createMatrix(n, (choice == 1) ? getIntType() : getDoubleType());
                printf("Матрица %dx%d создана (заполнена нулями по умолчанию).\n", n, n);
                waitForEnter();
                break;
            }
            case 3:
                if (!currentMat) {
                    printf("Сначала создайте матрицу!\n");
                } else {
                    printf("Выполняется расчет комбинации (тестовый прогон)...\n");
                    void* alphas[100] = {NULL};
                    addRowCombination(currentMat, 0, alphas);
                    printf("Готово.\n");
                }
                waitForEnter();
                break;
            case 4:
                if (!currentMat) {
                    printf("Матрица пуста.\n");
                } else {
                    printf("Текущая матрица (%dx%d):\n", currentMat->size, currentMat->size);
                    for (int i = 0; i < currentMat->size; i++) {
                        for (int j = 0; j < currentMat->size; j++) {
                            printf("%s\t", currentMat->type->funcs->print(currentMat->data[i * currentMat->size + j]));
                        }
                        printf("\n");
                    }
                }
                waitForEnter();
                break;
            case 0:
                printf("Завершение программы...\n");
                if (currentMat) freeMatrix(currentMat);
                break;
            default:
                printf("Неверный выбор.\n");
                waitForEnter();
                break;
        }
    }

    freeINT();
    freeDouble();

    return 0;
}