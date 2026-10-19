#include <stdio.h>

/* 4.31: Diamond-Printing Program */
int main(void)
{
    for (int row = 0; row < 9; ++row) {
        int spaces = (row <= 4) ? 4 - row : row - 4;
        int stars = 9 - 2 * spaces;

        for (int column = 0; column < spaces; ++column) {
            printf(" ");
        }
        for (int column = 0; column < stars; ++column) {
            printf("*");
        }
        printf("\n");
    }

    return 0;
    
}
