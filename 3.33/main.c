#include <stdio.h>

/* 3.33: Hollow Rectangle of Plus Symbols */
int main(void)
{
    int length, breadth;

    printf("Enter length (rows) and breadth (columns): ");
    if (scanf("%d%d", &length, &breadth) != 2 || length <= 0 || breadth <= 0) {
        fprintf(stderr, "Length and breadth must be positive integers.\n");
        return 1;
    }

    for (int row = 0; row < length; ++row) {
        for (int column = 0; column < breadth; ++column) {
            if (row == 0 || row == length - 1 || column == 0 || column == breadth - 1) {
                printf("+");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }

    return 0;
}
