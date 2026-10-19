#include <math.h>
#include <stdio.h>

/* 3.20: Salary Calculator */
int main(void)
{
    int hours;
    double hourly_rate, salary;

    for (;;) {
        printf("Enter # of hours worked (-1 to end): ");
        if (scanf("%d", &hours) != 1) {
            fprintf(stderr, "Invalid working hours.\n");
            return 1;
        }
        if (hours == -1) {
            break;
        }
        if (hours < 0) {
            fprintf(stderr, "Working hours must be nonnegative.\n");
            return 1;
        }
        printf("Enter hourly rate of the worker ($00.00): ");
        if (scanf("%lf", &hourly_rate) != 1 || !isfinite(hourly_rate) || hourly_rate < 0.0) {
            fprintf(stderr, "Invalid hourly rate.\n");
            return 1;
        }

        if (hours <= 40) {
            salary = hours * hourly_rate;
        } else {
            salary = 40 * hourly_rate + (hours - 40) * hourly_rate * 1.5;
        }
        if (!isfinite(salary)) {
            fprintf(stderr, "Salary is too large.\n");
            return 1;
        }
        printf("Salary is $%.2f\n\n", salary);
    }

    return 0;
}
