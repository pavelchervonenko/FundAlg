#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int write_symbols(FILE *file, const char *data)
{
    if (fprintf(file, "%s", data) < 0)
    {
        return -1;
    }
    return 0;
}

int read_symbols(FILE *file, char *data, size_t data_size)
{
    int current;
    size_t i = 0;

    while ((current = fgetc(file)) != EOF && isspace(current))
        ;

    if (current == EOF)
    {
        return EOF;
    }

    if (i < data_size - 1)
    {
        data[i++] = (char)current;
    }

    while ((current = fgetc(file)) != EOF && !isspace(current))
    {
        if (i < data_size - 1)
        {
            data[i++] = (char)current;
        }
    }

    data[i] = '\0';
    return 0;
}

void transfer_to_number_system(char *symbol, int base)
{
    // Выделяем память для нового символа
    char *new_symbol = malloc(4096 * sizeof(char));
    if (!new_symbol)
    {
        printf("ERROR: Memory allocation failed\n");
        return;
    }

    char *ptr = new_symbol;  // Указатель на новый символ
    size_t remaining = 4096; // Оставшееся количество символов

    for (int i = 0; symbol[i] != '\0'; i++)
    {
        int ascii_value = (int)symbol[i];
        char converted[20]; // Достаточно места для представления числа в любом из оснований

        if (base == 4)
        {
            // Преобразование в четверичную систему счисления
            int num = ascii_value;
            char base4[20];
            int index = 0;
            while (num > 0)
            {
                base4[index++] = (num % 4) + '0';
                num /= 4;
            }

            // Записываем в обратном порядке
            for (int j = index - 1; j >= 0; j--)
            {
                ptr[0] = base4[j];
                ptr++;
                remaining--;
            }
        }
        else if (base == 8)
        {
            // Преобразование в восьмеричную систему счисления
            int num = ascii_value;
            int count = snprintf(ptr, remaining, "%o", num); // Используем стандартную функцию snprintf
            ptr += count;                                    // Увеличиваем указатель, чтобы продолжать записывать
            remaining -= count;
        }
        else
        {
            printf("ERROR: Unsupported base: %d\n", base);
            free(new_symbol);
            return; // Завершаем, если основание не поддерживается
        }

        if (remaining <= 0)
        {
            printf("ERROR: Output buffer overflow\n");
            free(new_symbol);
            return; // Проверка переполнения буфера
        }
    }

    // Завершаем строку
    *ptr = '\0';

    // Выводим результат
    strcpy(symbol, new_symbol);
    free(new_symbol);
}

int function_for_r(const char *input_file1, const char *input_file2, const char *output_file)
{
    FILE *file1 = fopen(input_file1, "r");
    if (!file1)
    {
        printf("ERROR: Failed to open file: %s\n", input_file1);
        return -1;
    }
    FILE *file2 = fopen(input_file2, "r");
    if (!file2)
    {
        fclose(file1);
        printf("ERROR: Failed to open file: %s\n", input_file2);
        return -1;
    }
    FILE *output = fopen(output_file, "w");
    if (!output)
    {
        fclose(file1);
        fclose(file2);
        printf("ERROR: Failed to open file: %s\n", output_file);
        return -1;
    }

    char data1[1024];
    char data2[1024];

    int eof1 = 0, eof2 = 0;
    int i = 1;

    while (!eof1 || !eof2)
    {
        if (i % 2 != 0 && !eof1)
        {
            eof1 = read_symbols(file1, data1, sizeof(data1));
            if (eof1 != EOF && write_symbols(output, data1) < 0)
            {
                fclose(file1);
                fclose(file2);
                fclose(output);
                printf("ERROR: Failed to write to output file: %s\n", output_file);
                return -1;
            }
            fputc(' ', output);
        }
        else if (!eof2)
        {
            eof2 = read_symbols(file2, data2, sizeof(data2));
            if (eof2 != EOF && write_symbols(output, data2) < 0)
            {
                fclose(file1);
                fclose(file2);
                fclose(output);
                printf("ERROR: Failed to write to output file: %s\n", output_file);
                return -1;
            }
            fputc(' ', output);
        }
        i++;
    }

    fclose(file1);
    fclose(file2);
    fclose(output);
    return 0;
}

int function_for_a(const char *input_file, const char *output_file)
{
    FILE *input = fopen(input_file, "r");
    if (!input)
    {
        fprintf(stderr, "Error opening input file: %s\n", input_file);
        return -1;
    }
    FILE *output = fopen(output_file, "w");
    if (!output)
    {
        fclose(input);
        fprintf(stderr, "Error opening output file: %s\n", output_file);
        return -1;
    }

    char data[1024];
    int eof = 0;
    int i = 1;

    while (!eof)
    {
        eof = read_symbols(input, data, sizeof(data));
        if (eof != EOF)
        {
            if (i % 10 == 0)
            {
                for (int j = 0; data[j] != '\0'; j++)
                {
                    data[j] = tolower(data[j]);
                }
                transfer_to_number_system(data, 4);
            }
            else if (i % 2 == 0)
            {
                for (int j = 0; data[j] != '\0'; j++)
                {
                    data[j] = tolower(data[j]);
                }
            }
            else if (i % 5 == 0)
            {
                transfer_to_number_system(data, 8);
            }

            if (write_symbols(output, data) < 0)
            {
                fclose(input);
                fclose(output);
                printf("ERROR: Failed to write to output file: %s\n", output_file);
                return -1;
            }
            fputc(' ', output);
            i++;
        }
    }

    fclose(input);
    fclose(output);
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        printf("ERROR: Invalid input\n");
        return -1;
    }

    if (strcmp(argv[1], "-r") == 0)
    {
        if (argc != 5)
        {
            printf("ERROR: Incorrect number of arguments for -r\n");
            return -1;
        }
        return function_for_r(argv[2], argv[3], argv[4]);
    }
    else if (strcmp(argv[1], "-a") == 0)
    {
        if (argc != 4)
        {
            printf("ERROR: Incorrect number of arguments for -a\n");
            return -1;
        }
        return function_for_a(argv[2], argv[3]);
    }
    else
    {
        printf("ERROR: Invalid flag\n");
        return -1;
    }
}