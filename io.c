#include "io.h"
#include "errors.h"
int waitForEnter() {
    printf("\nНажмите ENTER для продолжения...");
    clear_input_buffer();
    return 0;
}