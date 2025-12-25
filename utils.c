#include <stdio.h>
#include "library.h"

/* Clears unwanted input from buffer */
void clearBuffer() {
    while (getchar() != '\n');
}

/* Reads only valid integers */
int getValidInt(char message[]) {
    int value;

    while (1) {
        printf("%s", message);

        if (scanf("%d", &value) == 1 && value >= 0) {
            clearBuffer();
            return value;
        }

        printf("Invalid input. Please enter a number.\n");
        clearBuffer();
    }
}
