#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define SIZE 50

void change_elements(int *x, int *y)
{
    int current = *x;
    *x = *y;
    *y = current;
}

int function_finding_elements(int array[], int size)
{
    if (array == NULL || size <= 0)
    {
        return -1;
    }

    int min_value = INT_MAX;
    int min_value_index = 0;

    int max_value = INT_MIN;
    int max_value_index = 0;

    for (int i = 0; i < size; i++)
    {
        if (array[i] < min_value)
        {
            min_value = array[i];
            min_value_index = i;
        }
        if (array[i] > max_value)
        {
            max_value = array[i];
            max_value_index = i;
        }
    }

    if (max_value_index != min_value_index)
    {
        change_elements(&array[min_value_index], &array[max_value_index]);
    }

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("ERROR: Invailid input\n");
        return -1;
    }

    int a;
    int b;

    if (sscanf(argv[1], "%d", &a) != 1 || sscanf(argv[2], "%d", &b) != 1)
    {
        printf("ERROR: Invailid input\n");
        return -1;
    }

    if (a >= b)
    {
        printf("ERROR: Invailid input (a should be less than b)\n");
        return -1;
    }

    int data[SIZE];
    srand(time(NULL));

    printf("Array befor operation:\n");
    for (int i = 0; i < SIZE; i++)
    {
        data[i] = a + rand() % (b - a + 1);
        printf("%d ", data[i]);
    }
    printf("\n");

    if (function_finding_elements(data, SIZE) != 0)
    {
        printf("ERROR: The min and max elements could not be found\n");
        return -1;
    }

    printf("Array after operation:\n");
    for (int i = 0; i < SIZE; i++)
    {
        printf("%d ", data[i]);
    }
    printf("\n");

    int size_a = 10 + rand() % (10001 - 10);
    int size_b = 10 + rand() % (10001 - 10);

    int *data_a = (int *)malloc(size_a * sizeof(int));
    int *data_b = (int *)malloc(size_b * sizeof(int));
    int *data_c = (int *)malloc(size_a * sizeof(int));

    if (!data_a || !data_b || !data_c)
    {
        printf("ERROR: Memory allocation failed\n");
        free(data_a);
        free(data_b);
        free(data_c);
        return -1;
    }

    for (int i = 0; i < size_a; i++)
    {
        data_a[i] = -1000 + rand() % (2001); // (1000 - (-1000) + 1);
    }
    for (int i = 0; i < size_b; i++)
    {
        data_b[i] = -1000 + rand() % (2001);
    }

    for (int i = 0; i < size_a; i++)
    {
        int close_value = data_b[0];
        int min_difference = abs(data_a[i] - data_b[0]);

        for (int j = 1; j < size_b; j++)
        {
            int difference = abs(data_a[i] - data_b[j]);
            if (difference < min_difference)
            {
                min_difference = difference;
                close_value = data_b[j];
            }
        }
        data_c[i] = data_a[i] + close_value;
    }

    // printf("Elements of the C array: \n");
    // for (int i = 0; i < size_a; i++)
    // {
    //     printf("%d ", data_c[i]);
    // }
    // printf("\n");

    free(data_a);
    free(data_b);
    free(data_c);

    return 0;
}
