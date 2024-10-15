#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "task5.h"

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
