#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef enum
{
    SUCCESS,
    FACTORIAL,
    HEX_DIGITS,
    NUMBER_IS_COMPOSITE,
    NUMBER_IS_PRIME,
    ERROR_UNKNOWN_ARGUMENT,
    ERROR_UNKNOWN_FLAG,
    ERROR_OUT_OF_RANGE,
    ERROR_NO_MULTIPLES,
    ERROR_NOT_PRIME,
    ERROR_NOT_PRIME_NOT_COMPOSITE,
    ERROR_NEGATIVE_VALUE_X,
    ERROR
} status_return;

typedef status_return (*callback)(long long);

int string_equal(const char *left, const char *right)
{
    return !strcmp(left, right);
}

int fing_flag(const char *arg, const char **flags_array, int flags_array_size)
{
    for (int i = 0; i < flags_array_size; i++)
    {
        if (string_equal(arg, flags_array[i]))
        {
            return i / 2;
        }
    }
    return -1;
}

status_return function_h(long long x)
{
    if (x <= 0)
    {
        return ERROR_OUT_OF_RANGE;
    }
    int flag = 0;
    for (int i = 1; i <= 100; i++)
    {
        if (i % x == 0)
        {
            printf("%d ", i);
            flag = 1;
        }
    }
    if (!flag)
    {
        return ERROR_NO_MULTIPLES;
    }
    return SUCCESS;
}

status_return function_p(long long x)
{
    if (x == 0 || x == 1)
    {
        return ERROR_NOT_PRIME_NOT_COMPOSITE;
    }
    for (int i = 2; i <= sqrt(x); i++)
    {
        if (abs(x) % i == 0)
        {
            printf("%lld", x);
            return NUMBER_IS_COMPOSITE;
        }
    }
    printf("%lld", x);
    return NUMBER_IS_PRIME;
}

status_return function_s(long long x)
{
    int flag = 0;
    for (int i = (sizeof(x) * 8 - 4); i >= 0; i -= 4)
    {
        int digit = (x >> i) & 0xF;
        if (digit || flag)
        {
            printf("%X ", digit);
            flag = 1;
        }
    }
    if (!flag)
    {
        printf("0");
    }
    return SUCCESS;
}

status_return function_e(long long x)
{
    if (x < 1 || x > 10)
    {
        return ERROR_OUT_OF_RANGE;
    }
    for (int base = 1; base <= 10; base++)
    {
        long long result = base;
        for (int i = 1; i <= x; i++)
        {
            result *= base;
            printf("%lld ", result);
        }
        printf("\n");
    }
    return SUCCESS;
}

status_return function_a(long long x)
{
    if (x < 1)
    {
        return ERROR_NEGATIVE_VALUE_X;
    }
    int sum = (x * (x + 1)) / 2;
    printf("%d\n", sum);
    return SUCCESS;
}

status_return function_f(long long x)
{
    if (x < 0)
    {
        return ERROR_NEGATIVE_VALUE_X;
    }
    if (x > 12)
    {
        return ERROR_OUT_OF_RANGE;
    }
    int factorial = 1;
    for (int i = 1; i <= x; i++)
    {
        factorial *= i;
    }
    printf("%d", factorial);
    return FACTORIAL;
}