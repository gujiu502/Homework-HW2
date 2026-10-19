#include <math.h>
#include <stdio.h>

/* 3.17: Credit Limit Calculator */
int main(void)
{
    int account;
    double beginning_balance, charges, credits, credit_limit, balance;

    for (;;) {
        printf("Enter account number (-1 to end): ");
        if (scanf("%d", &account) != 1) {
            fprintf(stderr, "Invalid account number.\n");
            return 1;
        }
        if (account == -1) {
            break;
        }
        if (account <= 0) {
            fprintf(stderr, "Account number must be positive.\n");
            return 1;
        }

        printf("Enter beginning balance: ");
        if (scanf("%lf", &beginning_balance) != 1 || !isfinite(beginning_balance)) {
            fprintf(stderr, "Invalid beginning balance.\n");
            return 1;
        }
        printf("Enter total charges: ");
        if (scanf("%lf", &charges) != 1 || !isfinite(charges) || charges < 0.0) {
            fprintf(stderr, "Invalid total charges.\n");
            return 1;
        }
        printf("Enter total credits: ");
        if (scanf("%lf", &credits) != 1 || !isfinite(credits) || credits < 0.0) {
            fprintf(stderr, "Invalid total credits.\n");
            return 1;
        }
        printf("Enter credit limit: ");
        if (scanf("%lf", &credit_limit) != 1 || !isfinite(credit_limit) || credit_limit < 0.0) {
            fprintf(stderr, "Invalid credit limit.\n");
            return 1;
        }

        /* Compare money at cent precision, including exact-limit balances. */
        balance = round((beginning_balance + charges - credits) * 100.0) / 100.0;
        if (!isfinite(balance)) {
            fprintf(stderr, "Balance is too large.\n");
            return 1;
        }
        if (balance > credit_limit) {
            printf("Account:      %d\n", account);
            printf("Credit limit: %.2f\n", credit_limit);
            printf("Balance:      %.2f\n", balance);
            printf("Credit limit exceeded.\n");
        }
        printf("\n");
    }

    return 0;
}
