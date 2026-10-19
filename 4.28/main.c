#include <math.h>
#include <stdio.h>

/* 4.28: Calculating Weekly Pay */
int main(void)
{
    int paycode, quantity;
    double salary, hours, hourly_rate, sales, amount_per_item;

    for (;;) {
        printf("\n1 Manager\n2 Hourly worker\n3 Commission worker\n4 Pieceworker\n");
        printf("Enter paycode (-1 to end): ");
        if (scanf("%d", &paycode) != 1) {
            fprintf(stderr, "Invalid paycode input.\n");
            return 1;
        }
        if (paycode == -1) {
            break;
        }

        switch (paycode) {
        case 1:
            printf("Enter fixed weekly salary: ");
            if (scanf("%lf", &salary) != 1 || !isfinite(salary) || salary < 0.0) {
                fprintf(stderr, "Invalid weekly salary.\n");
                return 1;
            }
            break;
        case 2:
            printf("Enter hours worked: ");
            if (scanf("%lf", &hours) != 1 || !isfinite(hours) || hours < 0.0) {
                fprintf(stderr, "Invalid working hours.\n");
                return 1;
            }
            printf("Enter hourly rate: ");
            if (scanf("%lf", &hourly_rate) != 1 || !isfinite(hourly_rate) || hourly_rate < 0.0) {
                fprintf(stderr, "Invalid hourly rate.\n");
                return 1;
            }
            if (hours <= 40.0) {
                salary = hours * hourly_rate;
            } else {
                salary = 40.0 * hourly_rate + (hours - 40.0) * hourly_rate * 1.5;
            }
            break;
        case 3:
            printf("Enter gross weekly sales: ");
            if (scanf("%lf", &sales) != 1 || !isfinite(sales) || sales < 0.0) {
                fprintf(stderr, "Invalid sales.\n");
                return 1;
            }
            salary = 250.0 + 0.057 * sales;
            break;
        case 4:
            printf("Enter amount paid per item: ");
            if (scanf("%lf", &amount_per_item) != 1 || !isfinite(amount_per_item) || amount_per_item < 0.0) {
                fprintf(stderr, "Invalid amount per item.\n");
                return 1;
            }
            printf("Enter number of items produced: ");
            if (scanf("%d", &quantity) != 1 || quantity < 0) {
                fprintf(stderr, "Invalid item quantity.\n");
                return 1;
            }
            salary = amount_per_item * quantity;
            break;
        default:
            printf("Invalid paycode. Enter 1, 2, 3, 4, or -1.\n");
            continue;
        }

        if (!isfinite(salary)) {
            fprintf(stderr, "Weekly pay is too large.\n");
            return 1;
        }
        printf("Weekly pay is $%.2f\n", salary);
    }

    return 0;
}
