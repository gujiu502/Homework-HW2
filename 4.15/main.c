#include <math.h>
#include <stdio.h>

/* 4.15: Modified Compound-Interest Program */
int main(void)
{
    const double principal = 5000.0;

    /* Integer steps avoid accumulating floating-point error in the loop. */
    for (int half_percent = 20; half_percent <= 24; ++half_percent) {
        double rate = half_percent / 200.0;

        printf("Interest rate: %.1f%%\n", rate * 100.0);
        printf("%4s%20s\n", "Year", "Amount on deposit");
        for (int year = 1; year <= 15; ++year) {
            double amount = principal * pow(1.0 + rate, year);
            printf("%4d%20.2f\n", year, amount);
        }
        printf("\n");
    }

    return 0;
}
