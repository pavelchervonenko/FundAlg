#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>

typedef enum
{
    SUCCSES,
    ERROR_INPUT,
    MATH_ERROR,
    OVERFLOF
} status_return;

double factorial(int n)
{
    if (n < 0)
    {
        return 0;
    }
    double result;
    if (n == 0)
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

status_return sum_c(const double x, const double epsilon, double *result)
{
    if (epsilon <= 0 || result == NULL)
    {
        return ERROR_INPUT;
    }

    double sum = 0.0;
    double current = 1.0; // Начинаем с первого элемента ряда
    int n = 1;            // Начинаем с n = 1, потому что первый элемент соответствует n = 0

    while (fabs(current) >= epsilon)
    {
        sum += current; // Обновляем сумму

        // Переход к следующему члену
        double fact_n = factorial(n);
        double fact_3n = factorial(3 * n);

        // Проверка на переполнение
        if (fact_n == 0 || fact_3n == 0 || fact_3n > DBL_MAX / (pow(3, 3 * n) * pow(fact_n, 3) * pow(x, 2 * n)))
        {
            return OVERFLOF;
        }

        current = (pow(3, 3 * n) * pow(fact_n, 3) * pow(x, 2 * n)) / fact_3n; // Новый член ряда

        n++; // Увеличиваем n для следующего члена
    }

    *result = sum;  // Записываем результат
    return SUCCSES; // Возвращаем статус успеха
}

// status_return sum_c(const double x, const double epsilon, double *result)
// {
//     if (epsilon <= 0 || result == NULL)
//     {
//         return ERROR_INPUT;
//     }

//     double sum = 0.0;
//     int n = 1;
//     double current = 1.0;
//     while (fabs(current) >= epsilon)
//     {
//         sum += current;
//         n++;
//         double fact_n = factorial(n);
//         double fact_3n = factorial(3 * n);

//         if (fact_n == 0 || fact_3n == 0)
//         {
//             return OVERFLOF;
//         }
//         current = (pow(3, 3 * n) * pow(fact_n, 3) * pow(x, 2 * n)) / fact_3n;
//         if (fabs(current) == INFINITY)
//         {
//             return OVERFLOF;
//         }
//     }

//     *result = sum;
//     return SUCCSES;
// }

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
