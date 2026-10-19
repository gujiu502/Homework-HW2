#include <stdio.h>

/* 4.27: Pythagorean Triples */
int main(void)
{
    printf("%6s%6s%12s\n", "Side 1", "Side 2", "Hypotenuse");

    /* side1 <= side2 avoids listing the same triangle twice. */
    for (int side1 = 1; side1 <= 500; ++side1) {
        for (int side2 = side1; side2 <= 500; ++side2) {
            for (int hypotenuse = side2 + 1; hypotenuse <= 500; ++hypotenuse) {
                if (side1 * side1 + side2 * side2 == hypotenuse * hypotenuse) {
                    printf("%6d%6d%12d\n", side1, side2, hypotenuse);
                }
            }
        }
    }

    return 0;
}
