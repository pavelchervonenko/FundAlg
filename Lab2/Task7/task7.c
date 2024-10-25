#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef double (*Function)(double);

typedef enum
{
    SUCCESS,
    INVALID_INTERVAL,
    MEMORY_ERROR,
    NO_CONVERGENCE
} StatusCode;

StatusCode bisection(double a, double b, double epsilon, Function f, double *root)
{
    if (f(a) * f(b) >= 0)
    {
        return INVALID_INTERVAL; // Ensure a and b bracket the root
    }

    double c;
    while ((b - a) / 2 > epsilon)
    {
        c = (a + b) / 2;
        if (f(c) == 0.0)
        {
            *root = c;
            return SUCCESS;
        }
        if (f(a) * f(c) < 0)
        {
            b = c;
        }
        else
        {
            a = c;
        }
    }
    *root = (a + b) / 2;
    return SUCCESS;
}

// Example function: f(x) = x^3 - 4x + 1
double exampleFunction(double x)
{
    return x * x * x - 4 * x + 1;
}

int main()
{
    double a, b, epsilon;

    printf("Enter the start of the interval (a): ");
    scanf("%lf", &a);

    printf("Enter the end of the interval (b): ");
    scanf("%lf", &b);

    printf("Enter the precision (epsilon): ");
    scanf("%lf", &epsilon);

    double root;
    StatusCode status = bisection(a, b, epsilon, exampleFunction, &root);

    if (status == SUCCESS)
    {
        printf("Root found: %.10f\n", root);
    }
    else
    {
        printf("Error: Invalid interval or no convergence\n");
    }

    return 0;
}