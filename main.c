#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "matrix.h"
#include "int.h"
#include "double.h"

void run_table_operations_tests() {
    printf("\n>>> 1. ПРОВЕРКА БАЗОВЫХ ОПЕРАЦИЙ (ТАБЛИЦА)\n");

    IType* iType = getIntType();
    SquareMatrix* m1 = createMatrix(2, iType);
    SquareMatrix* m2 = createMatrix(2, iType);

    int val1 = 10, val2 = 20;
    memcpy(m1->data[0], &val1, sizeof(int));
    memcpy(m2->data[0], &val2, sizeof(int));

    SquareMatrix* sum = addMatrices(m1, m2);
    if (sum && *(int*)sum->data[0] == 30) printf("[OK] Матричное сложение\n");

    int factor = 2;
    scaleMatrix(m1, &factor);
    if (*(int*)m1->data[0] == 20) printf("[OK] Умножение на скаляр\n");

    SquareMatrix* mul = multiplyMatrices(m1, m2);
    if (mul) printf("[OK] Матричное умножение\n");

    freeMatrix(m1); freeMatrix(m2); freeMatrix(sum); freeMatrix(mul);
}

void run_30_extended_tests() {
    printf("\n>>> 2. ЗАПУСК 30 РАСШИРЕННЫХ ТЕСТОВ (ЛИНЕЙНАЯ КОМБИНАЦИЯ)\n");
    int passed = 0;

    for (int i = 1; i <= 30; i++) {
        IType* mType = (i % 2 == 0) ? getDoubleType() : getIntType();
        SquareMatrix* m = createMatrix(2, mType);

        double dVal = 1.5;
        int iVal = 3;
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
                printf("Тест №%d: OK (Ошибка типа поймана)\n", i);
                passed++;
            } else {
                printf("Тест №%d: ПРОВАЛ (Типы не совпали, но ошибка не выдана)\n", i);
            }
        } else {
            if (res == 0) {
                printf("Тест №%d: OK (Корректное выполнение)\n", i);
                passed++;
            }
        }
        freeMatrix(m);
    }
    printf(">>> ИТОГО: %d/30 пройдены.\n", passed);
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    run_table_operations_tests();
    run_30_extended_tests();

    freeINT();
    freeDouble();

    printf("\nВсе требования таблицы и тесты выполнены. Нажмите Enter...");
    getchar();
    return 0;
}