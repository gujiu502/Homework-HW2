#include <math.h>
#include <stdio.h>

/* 3.19: Interest Calculator */
int main(void)
{
    double principal, rate, interest;
    int days;

    for (;;) {
        printf("Enter loan principal (-1 to end): ");
        if (scanf("%lf", &principal) != 1 || !isfinite(principal)) {
            fprintf(stderr, "Invalid principal.\n");
            return 1;
        }
        if (principal == -1.0) {
            break;
        }
        if (principal < 0.0) {
            fprintf(stderr, "Principal must be nonnegative.\n");
            return 1;
        }
        printf("Enter interest rate: ");
        if (scanf("%lf", &rate) != 1 || !isfinite(rate) || rate < 0.0) {
            fprintf(stderr, "Invalid interest rate.\n");
            return 1;
        }
        printf("Enter term of the loan in days: ");
        if (scanf("%d", &days) != 1 || days < 0) {
            fprintf(stderr, "Invalid number of days.\n");
            return 1;
        }

        interest = principal * rate * days / 365.0;
        if (!isfinite(interest)) {
            fprintf(stderr, "Interest is too large.\n");
            return 1;
        }
        printf("The interest charge is $%.2f\n\n", interest);
    }

    return 0;
}
