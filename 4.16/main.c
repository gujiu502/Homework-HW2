#include <stdio.h>

/* 4.16: Triangle-Printing Program */
int main(void)
{
    printf("%-13s%-13s%-13s%s\n", "(A)", "(B)", "(C)", "(D)");
    for (int row = 1; row <= 10; ++row) {
        for (int pattern = 0; pattern < 4; ++pattern) {
            int stars = (pattern == 0 || pattern == 3) ? row : 11 - row;

            for (int column = 0; column < 10; ++column) {
                int is_star = (pattern < 2) ? column < stars : column >= 10 - stars;

                if (is_star) {
                    printf("%s", "*");
                } else {
                    printf("%s", " ");
                    
                }
            }
            if (pattern < 3) {
                printf("   ");
            }

        }
        printf("\n");
    }

    return 0;
}
