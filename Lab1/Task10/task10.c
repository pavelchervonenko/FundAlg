#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
    SUCCESS,
    ERROR_INCORRECT_BASE,
} status_return;

int main()
{
    printf("Enter the base of the number system from 2 to 36\n");
    int base;
    scanf("%d", &base);

    if (base < 2 || base > 36)
    {
        printf("ERROR: Incorrect base of the number system\n");
        return ERROR_INCORRECT_BASE;
    }

    char input_data[65];
    long long maxxn
}