#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

enum status_return
{
    ERROR_FLAG = -1000,
    SUCCESS = 0,
    BREAK,
    CONTINUE,
    ERROR,
    ERROR_MEMORY,
    ERROR_ZERO_DIVISION,
    MULTIPLE,
    N_MULTIPLE,
    RECTANGLE,
    N_RECTANGLE,
    ERROR_MUST_BE_A_NUMBER,
    ERROR_MUST_BE_A_NUMBER_BREAK,
    MUST_BE_BIGGER_THAN_ZERO
};

typedef int (*callback)(double *);

int correct_flag(char *current_argumet, const char **flags, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (!strcmp(current_argumet, flags[i]))
        {
            return current_argumet[1];
        }
    }
    return ERROR_FLAG;
}

int has_only_numbers(char *arg)
{
    for (int i = 0; i < strlen(arg); i++)
    {
        if (!((arg[i] >= '0' && arg[i] <= '9') || arg[i] == '.' || arg[i] == '-'))
        {
            return 0;
        }
    }
    return 1;
}

int find_X2(double epsilon, double a, double b, double c)
{
    if (a == 0 && b != 0)
    {
        printf("%fx^2 + %fx + %f = 0\nx1 = x2 = %f\n\n", a, b, c, -c / b);
        return SUCCESS;
    }
    else if (a == 0 && b == 0 && c == 0)
    {
        printf("%fx^2 + %fx + %f = 0\nNo solvings!\n\n", a, b, c);
        return SUCCESS;
    }
    double discriminant = (b * b) - (4 * a * c);
    if (discriminant < 0)
    {
        discriminant = discriminant * -1;
        printf("%fx^2 + %fx + %f = 0\nNo solvings in R! Only in C.\nx1/x2 = (-%f +- i(sqrt(%f))) / (2 * %f)\n\n", a, b, c, b, discriminant, a);
        return SUCCESS;
    }
    double x1 = (-b + sqrt(discriminant)) / (2 * a);
    double x2 = (-b - sqrt(discriminant)) / (2 * a);
    if (fabs(x1 - x2) < epsilon)
    {
        printf("%fx^2 + %fx + %f = 0\nx1 = x2 = %f\n\n", a, b, c, x1);
        return SUCCESS;
    }
    printf("%fx^2 + %fx + %f = 0\nx1 = %f, x2 = %f\n\n", a, b, c, x1, x2);
    return SUCCESS;
}

int dbl_cmp(double epsilon, double x1, double x2)
{
    if (fabs(x1 - x2) < epsilon)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int function_for_q(double epsilon, double x1, double x2, double x3)
{
    int x[] = {x1, x2, x3};
    double combinations[6][3];
    double combination[3];
    int count = 0;
    for (int k = 0; k < 3; k++)
    {
        for (int i = 1; i <= 2; i++)
        {
            for (int j = k, n = 0; j < 3, n < 3; j = (j + i) % 3, n++)
            {
                combination[n] = x[j % 3];
            }
            int flag = 0;
            for (int i = 0; i < count; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (dbl_cmp(epsilon, combination[j], combinations[i][j]))
                    {
                        flag++;
                    }
                }
                if (flag == 3)
                {
                    flag = -1;
                    break;
                }
                else
                {
                    flag = 0;
                }
            }
            if (!flag)
            {
                find_X2(epsilon, combination[0], combination[1], combination[2]);
                for (int i = 0; i < 3; i++)
                {
                    combinations[count][i] = combination[i];
                }
                count++;
            }
            else
            {
                break;
            }
        }
    }

    return SUCCESS;
}

int is_miltiple(int x1, int x2)
{
    if (x2 == 0)
    {
        return ERROR_ZERO_DIVISION;
    }
    if (x1 % x2 == 0)
    {

        return MULTIPLE;
    }
    else
    {
        return N_MULTIPLE;
    }
}

int is_rectangular(double epsilon, double a, double b, double c)
{
    if (dbl_cmp(epsilon, 0.0, a) || dbl_cmp(epsilon, 0.0, b) || dbl_cmp(epsilon, 0.0, c) || a < 0 || b < 0 || c < 0)
    {
        return MUST_BE_BIGGER_THAN_ZERO;
    }
    if (dbl_cmp(epsilon, a * a + b * b, c * c) || dbl_cmp(epsilon, a * a + c * c, b * b) || dbl_cmp(epsilon, b * b + c * c, a * a))
    {

        return RECTANGLE;
    }
    else
    {

        return N_RECTANGLE;
    }
}

double *checking_for_right(const char **flags, char *argv[], int argc, int *i, int right_count_arguments, int *operation_status, int arguments_size)
{
    int ii = (*i) + 1;
    int count = 0;
    (*operation_status) = SUCCESS;
    while (ii < argc)
    {

        if (correct_flag(argv[ii], flags, arguments_size) == ERROR_FLAG)
        {

            ++count;
            ++ii;
            continue;
        }
        else
        {
            break;
        }
        ++count;
        ++ii;
    }
    if (count != right_count_arguments)
    {
        printf("ERROR: The wrong count of arguments! Must be %d for %s key!\n", right_count_arguments, argv[(*i)]);
        if ((*i) + count < argc)
        {
            (*i) = (*i) + count;
        }
        else
        {
            (*operation_status) = BREAK;
            return NULL; // добавленно
        }
        (*operation_status) = CONTINUE;
        return NULL; // добавленно
    }
    (*i)++;
    double *argq = (double *)malloc(sizeof(double) * right_amount);
    if (argq == NULL)
    {
        (*rt) = ERROR;
        return NULL;
    }
    int flag = 0;
    for (int j = (*i); j < (*i) + right_amount; j++)
    {
        if (has_only_numbers(argv[j]))
        {
            argq[j - (*i)] = atof(argv[j]);
        }
        else
        {
            (*rt) = ERROR_MUST_BE_A_NUMBER_BREAK;
            flag = 1;
            break;
        }
    }
    if (flag)
    {
        (*i) = (*i) + right_amount - 1;
        return NULL;
    }
    (*i) = (*i) + right_amount - 1;
    return argq;
}
