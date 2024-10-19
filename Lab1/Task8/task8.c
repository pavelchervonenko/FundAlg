#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int find_minimum_base(const char *str)
{
    int maximum_digit = 1;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (isdigit(str[i]))
        {
            if (str[i] - '0' > maximum_digit)
            {
                maximum_digit = str[i] - '0';
            }
        }
        else if (isalpha(str[i]))
        {
            if (tolower(str[i]) - 'a' + 10 > maximum_digit)
            {
                maximum_digit = tolower(str[i]) - 'a' + 10;
                ;
            }
        }
        else
        {
            return -1;
        }
    }
    if (maximum_digit < 1)
    {
        return 2;
    }
    else
    {
        return maximum_digit + 1;
    }
}

long long conversion_to_decimal_system(const char *str, int base)
{
    long long degree = 1;
    long long value = 0;
    int length = strlen(str);

    for (int i = length - 1; i >= 0; i--)
    {
        int digit;
        if (isdigit(str[i]))
        {
            digit = str[i] - '0';
        }
        else if (isalpha(str[i]))
        {
            digit = tolower(str[i]) - 'a' + 10;
        }
        else
        {
            return -1;
        }

        if (digit >= base)
        {
            return -1;
        }

        if (value > LLONG_MAX / base || (value == LLONG_MAX / base && digit > LLONG_MAX % base))
        {
            return -1;
        }
        value += digit * degree;
        if (i > 0 && degree > LLONG_MAX / base)
        {
            return -1;
        }

        degree *= base;
    }
    return value;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("ERROR: Invailid input\n");
        return -1;
    }

    if (strcmp(argv[1], argv[2]) == 0)
    {
        printf("ERROR: Input and output files must be different\n");
        return -1;
    }

    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL)
    {
        printf("ERROR: Failed opening input file\n");
        return -1;
    }

    FILE *output_file = fopen(argv[2], "w");
    if (output_file == NULL)
    {
        printf("ERROR: Failed opening output file\n");
        fclose(input_file);
        return 1;
    }

    char number_string[101];

    while (fscanf(input_file, "%100s", number_string) == 1)
    {
        int i = 0;
        while (number_string[i] == '0' && number_string[i + 1] != '\0')
        {
            i++;
        }

        if (number_string[i] == '\0')
        {
            fprintf(output_file, "0 2 0\n");
            continue;
        }

        int minimum_base = find_minimum_base(number_string + i);

        if (minimum_base == -1 || minimum_base > 36 || minimum_base < 2)
        {
            fprintf(output_file, "Invalid number: %s\n", number_string + i);
            continue;
        }

        long long decimal_value = conversion_to_decimal_system(number_string + i, minimum_base);
        if (decimal_value == -1)
        {
            fprintf(output_file, "Overflow detected for number: %s\n", number_string + i);
            continue;
        }

        fprintf(output_file, "%s %d %lld\n", number_string + i, minimum_base, decimal_value);
    }

    fclose(input_file);
    fclose(output_file);
    return 0;
}

// gcc ex8.c -o ex8

// ./ex8.exe input8.txt output8.txt