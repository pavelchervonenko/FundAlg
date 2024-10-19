#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int function_d(const char *input_filename, const char *output_filename)
{
    FILE *input_file = fopen(input_filename, "r");
    if (!input_file)
    {
        printf("ERROR: Failed opening input file\n");
        return -1;
    }

    FILE *output_file = fopen(output_filename, "w");
    if (!output_file)
    {
        printf("ERROR: Failed opening output file\n");
        fclose(input_file);
        return -1;
    }

    char line[1024];
    while (fgets(line, sizeof(line), input_file))
    {
        for (size_t i = 0; line[i] != '\0'; i++)
        {
            if (!isdigit(line[i]))
            {
                fputc(line[i], output_file);
            }
        }
    }
    if (!(input_file))
    {
        printf("ERROR: failed reading input file\n");
        fclose(input_file);
        fclose(output_file);
        return -1;
    }

    fclose(input_file);
    fclose(output_file);
    return 0;
}

int function_i(const char *input_filename, const char *output_filename)
{
    FILE *input_file = fopen(input_filename, "r");
    if (!input_file)
    {
        printf("ERROR: Failed opening input file\n");
        return -1;
    }

    FILE *output_file = fopen(output_filename, "w");
    if (!output_file)
    {
        printf("ERROR: Failed opening output file\n");
        fclose(input_file);
        return -1;
    }

    char line[1024];
    while (fgets(line, sizeof(line), input_file))
    {
        int count = 0;
        for (size_t i = 0; line[i] != '\0'; i++)
        {
            if (isalpha(line[i]))
            {
                count++;
            }
        }
        fprintf(output_file, "%d\n", count);
    }

    if (!(input_file))
    {
        printf("ERROR: failed reading input file\n");
        fclose(input_file);
        fclose(output_file);
        return -1;
    }

    fclose(input_file);
    fclose(output_file);
    return 0;
}

int function_s(const char *input_filename, const char *output_filename)
{
    FILE *input_file = fopen(input_filename, "r");
    if (!input_file)
    {
        printf("ERROR: Failed opening input file\n");
        return -1;
    }

    FILE *output_file = fopen(output_filename, "w");
    if (!output_file)
    {
        printf("ERROR: Failed opening output file\n");
        fclose(input_file);
        return -1;
    }

    char line[1024];
    while (fgets(line, sizeof(line), input_file))
    {
        int count = 0;
        for (size_t i = 0; line[i] != '\0'; ++i)
        {
            if (!isalnum(line[i]) && !isspace(line[i]))
            {
                count++;
            }
        }
        fprintf(output_file, "%d\n", count);
    }
    if (!(input_file))
    {
        printf("ERROR: failed reading input file\n");
        fclose(input_file);
        fclose(output_file);
        return -1;
    }

    fclose(input_file);
    fclose(output_file);
    return 0;
}

int function_a(const char *input_filename, const char *output_filename)
{
    FILE *input_file = fopen(input_filename, "r");
    if (!input_file)
    {
        printf("ERROR: Failed opening input file\n");
        return -1;
    }

    FILE *output_file = fopen(output_filename, "w");
    if (!output_file)
    {
        printf("ERROR: Failed opening output file\n");
        fclose(input_file);
        return -1;
    }

    char line[1024];
    while (fgets(line, sizeof(line), input_file))
    {
        for (size_t i = 0; line[i] != '\0'; ++i)
        {
            if (!isdigit(line[i]))
            {
                fprintf(output_file, "%02X", (unsigned char)line[i]);
            }
            else
            {
                fputc(line[i], output_file);
            }
        }
    }
    if (!(input_file))
    {
        printf("ERROR: failed reading input file\n");
        fclose(input_file);
        fclose(output_file);
        return -1;
    }

    fclose(input_file);
    fclose(output_file);
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 3 || argc > 4)
    {
        printf("ERROR: Invalid number of argument\n");
        return -1;
    }

    char *flag = argv[1];
    char *input_filename = argv[2];
    char *output_filename = NULL;
    char flag_char;

    if (strlen(flag) < 2 || (flag[0] != '/' && flag[0] != '-'))
    {
        printf("ERROR: Invalid flag format\n");
        return -1;
    }

    int custom_output = 0;
    if (flag[1] == 'n')
    {
        if (argc != 4)
        {
            printf("ERROR: Output filename required with -n option\n");
            return -1;
        }
        if (strlen(flag) < 3 || (flag[2] != 'd' && flag[2] != 'i' && flag[2] != 's' && flag[2] != 'a'))
        {
            printf("ERROR: Invalid flag format\n");
            return -1;
        }

        output_filename = argv[3];
        custom_output = 1;
        flag_char = flag[2];
    }
    else
    {
        flag_char = flag[1];
    }

    if (custom_output == 0)
    {
        size_t length = strlen(input_filename) + strlen("out_") + 1;
        output_filename = malloc(length);
        if (!output_filename)
        {
            printf("ERROR: Failed memory allocation");
            return -1;
        }
        int current = snprintf(output_filename, length, "out_%s", input_filename);
        if (current < 0 || (size_t)current >= length)
        {
            printf("ERROR: Failed snprintf");
            free(output_filename);
            return -1;
        }
    }

    switch (flag_char)
    {
    case 'd':
        if (function_d(input_filename, output_filename) != 0)
        {
            if (!custom_output)
                free(output_filename);
            return -1;
        }
        break;
    case 'i':
        if (function_i(input_filename, output_filename) != 0)
        {
            if (!custom_output)
                free(output_filename);
            return -1;
        }
        break;
    case 's':
        if (function_s(input_filename, output_filename) != 0)
        {
            if (!custom_output)
                free(output_filename);
            return -1;
        }
        break;
    case 'a':
        if (function_a(input_filename, output_filename) != 0)
        {
            if (!custom_output)
                free(output_filename);
            return -1;
        }
        break;
    default:
        printf("ERROR: Invalid flag\n");
        if (!custom_output)
            free(output_filename);
        return -1;
    }

    if (!custom_output)
        free(output_filename);

    return 0;
}
