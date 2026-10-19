#include <math.h>
#include <stdio.h>

/* 3.18: Sales Commission Calculator */
int main(void)
{
    double sales, salary;

    for (;;) {
        printf("Enter sales in dollars (-1 to end): ");
        if (scanf("%lf", &sales) != 1 || !isfinite(sales)) {
            fprintf(stderr, "Invalid sales.\n");
            return 1;
        }
        if (sales == -1.0) {
            break;
        }
        if (sales < 0.0) {
            fprintf(stderr, "Sales must be nonnegative.\n");
            return 1;
        }

        salary = 200.0 + 0.09 * sales;
        printf("Salary is: $%.2f\n\n", salary);
    }

    return 0;
}
