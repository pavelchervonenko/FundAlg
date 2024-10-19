#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef enum
{
    SUCCSES,
    ERROR_INPUT,
    MATH_ERROR,
    OVERFLOF
} status_return;

double factorial(int n)
{
    // if (n < 0)
    // {
    //     return 0;
    // }
    double result = 1.0;
    if (n == 0 || n == 1)
    {
        result = 1.0;
    }
    else
    {
        result = n * factorial(n - 1);
    }
    // for (int i = 2; i <= n; i++)
    // {
    //     if (result > ULLONG_MAX / i)
    //     {
    //         return 0;
    //     }
    //     result *= i;
    // }
    return result;
}

double double_factorial(int n)
{
    if (n < 0)
    {
        return 0;
    }
    double result = 0.0;
    if (n == 0 || n == 1)
    {
        result = 1;
    }
    else
    {
        result = n * double_factorial(n - 2);
        return result;
    }
    // for (int i = n; i > 1; i -= 2)
    // {
    //     if (result > ULLONG_MAX / i)
    //     {
    //         return 0;
    //     }
    //     result *= i;
    // }
    return result;
}

status_return sum_a(const double x, const double epsilon, double *result)
{
    if (epsilon <= 0 || result == NULL)
    {
        return ERROR_INPUT;
    }

    double sum = 0.0;
    int n = 0;
    double current = 1.0; // при n = 0

    while (fabs(current) >= epsilon)
    {
        sum += current;
        n++;
        double fact = factorial(n);
        if (fact == 0)
        {
            return OVERFLOF;
        }
        current = pow(x, n) / fact;
        if (fabs(current) == INFINITY)
        {
            return OVERFLOF;
        }
    }

    *result = sum;
    return SUCCSES;
}

status_return sum_b(const double x, const double epsilon, double *result)
{
    if (epsilon <= 0 || result == NULL)
    {
        return ERROR_INPUT;
    }

    double sum = 0.0;
    int n = 0;
    double current = 1.0;

    while (fabs(current) >= epsilon)
    {
        sum += current;
        n++;
        double fact = factorial(2 * n);
        if (fact == 0)
        {
            return OVERFLOF;
        }
        current = pow(-1, n) * pow(x, 2 * n) / fact;
        if (fabs(current) == INFINITY)
        {
            return OVERFLOF;
        }
    }

    *result = sum;
    return SUCCSES;
}

status_return sum_c(double x, double epsilon, double *result)
{
    double sum = 0.0;
    double term;
    double n = 0;

    do
    {
        unsigned long long n_factorial = factorial(n);
        unsigned long long three_n_factorial = factorial(3 * n);

        if (three_n_factorial == 0)
        {
            break;
        }

        term = (pow(3, 3 * n) * pow(n_factorial, 3) * pow(x, 2 * n)) / (double)three_n_factorial;
        sum += term;
        n++;
    } while (fabs(term) > epsilon);

    *result = sum;
    return SUCCSES;
}

status_return sum_d(const double x, const double epsilon, double *result)
{
    if (epsilon <= 0 || result == NULL)
    {
        return ERROR_INPUT;
    }

    double sum = 0.0;
    int n = 1;
    double current = (pow(-1, n) * double_factorial(2 * n - 1) * pow(x, 2 * n)) / double_factorial(2 * n);
    while (fabs(current) >= epsilon)
    {
        sum += current;
        n++;
        current = (pow(-1, n) * double_factorial(2 * n - 1) * pow(x, 2 * n)) / double_factorial(2 * n);
        if (fabs(current) == INFINITY)
        {
            return OVERFLOF;
        }
    }

    *result = sum;
    return SUCCSES;
}

int main(int argc, char *argv[])
{
    if (argc == 3)
    {
        printf("Using epsilon >> %s\n", argv[1]);
        printf("Using x >> %s\n", argv[2]);
    }
    else
    {
        printf("ERROR: Incorrect input\n");
        return ERROR_INPUT;
    }

    char *endptr;

    double epsilon = strtod(argv[1], &endptr);
    if (endptr == argv[1] || *endptr != '\0' || epsilon <= 0 || epsilon >= 1)
    {
        printf("ERROR: Epsilon takes the wrong value\n");
        return ERROR_INPUT;
    }

    double x = strtod(argv[2], &endptr);
    if (endptr == argv[2] || *endptr != '\0')
    {
        printf("ERROR: X takes the wrong value\n");
        return ERROR_INPUT;
    }
    if (fabs(x) == INFINITY)
    {
        printf("ERROR: Number out of range\n");
        return ERROR_INPUT;
    }

    double result;
    status_return status;

    status = sum_a(x, epsilon, &result);
    switch (status)
    {
    case SUCCSES:
        printf("The solution of the example A: %.10lf\n", result);
        break;
    case ERROR_INPUT:
        printf("ERROR in A. Incorrect input\n");
        break;
    case OVERFLOF:
        printf("ERROR in A. Overflow\n");
        break;
    }

    status = sum_b(x, epsilon, &result);
    switch (status)
    {
    case SUCCSES:
        printf("The solution of the example B: %.10lf\n", result);
        break;
    case ERROR_INPUT:
        printf("ERROR in B. Incorrect input\n");
        break;
    case OVERFLOF:
        printf("ERROR in B. Overflow\n");
        break;
    }

    status = sum_c(x, epsilon, &result);
    switch (status)
    {
    case SUCCSES:
        printf("The solution of the example C: %.10lf\n", result);
        break;
    case ERROR_INPUT:
        printf("ERROR in C. Incorrect input\n");
        break;
    case OVERFLOF:
        printf("ERROR in C. Overflow\n");
        break;
    }

    status = sum_d(x, epsilon, &result);
    switch (status)
    {
    case SUCCSES:
        printf("The solution of the example D: %.10lf\n", result);
        break;
    case ERROR_INPUT:
        printf("ERROR in D. Incorrect input\n");
        break;
    case OVERFLOF:
        printf("ERROR in D. Overflow\n");
        break;
    }

    return 0;
}
