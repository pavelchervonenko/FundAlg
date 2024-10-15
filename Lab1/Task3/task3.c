#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include "task3.h"

int main(int argc, char *argv[])
{
    const char *flags[] = {"-q", "/q", "-m", "/m", "-t", "/t"};

    for (int i = 1; i < argc; i++)
    {
        int value = correct_flag(argv[i], flags, sizeof(flags) / sizeof(char *));

        if (value == ERROR_FLAG)
        {
            printf("ERROR: The flag was not found - %s\n", argv[i]);
            return -1;
        }
        else
        {
            switch ((char)value)
            {
            case 'q':
            {
                int operation_status = SUCCESS;
                double *argq = checking_arguments(flags, argv, argc, &i, 4, &operation_status, sizeof(flags) / sizeof(char *));
                if (operation_status == BREAK)
                {
                    free(argq);
                    break;
                }
                else if (operation_status == ERROR_MUST_BE_A_NUMBER_BREAK)
                {
                    printf("The argument must be a number!\n");
                    break;
                }
                else if (operation_status == CONTINUE)
                {
                    free(argq);
                    continue;
                }
                else if (operation_status == ERROR)
                {
                    printf("Memory error!\n");
                }
                function_for_q(argq[0], argq[1], argq[2], argq[3]);
                free(argq);
                break;
            }

            case 'm':
            {
                int rt = SUCCESS;
                double *argq = checking_for_right(flags, argv, argc, &i, 2, &rt, sizeof(flags) / sizeof(char *));
                if (rt == BREAK)
                {
                    free(argq);
                    break;
                }
                else if (rt == ERROR_MUST_BE_A_NUMBER_BREAK)
                {
                    printf("The argument must be a number!\n");
                    break;
                }
                else if (rt == CONTINUE)
                {
                    free(argq);
                    continue;
                }
                else if (rt == ERROR)
                {
                    printf("Memory error!\n");
                }
                int r = is_miltiple(argq[0], argq[1]);
                if (r == ERROR_ZERO_DIVISION)
                {
                    printf("Zero division error! The argument mustn't be equal to 0!\n");
                }
                else if (r == MULTIPLE)
                {
                    printf("The first number is a multiple of the second.\n");
                }
                else if (r == N_MULTIPLE)
                {
                    printf("The first numbers is not multiple of the second.\n");
                }
                free(argq);
                break;
            }

            break;
            case 't':
            {
                int rt = SUCCESS;
                double *argq = checking_for_right(flags, argv, argc, &i, 4, &rt, sizeof(flags) / sizeof(char *));
                if (rt == BREAK)
                {
                    free(argq);
                    break;
                }
                else if (rt == ERROR_MUST_BE_A_NUMBER_BREAK)
                {
                    printf("The argument must be a number!\n");
                    break;
                }
                else if (rt == CONTINUE)
                {
                    free(argq);
                    continue;
                }
                else if (rt == ERROR)
                {
                    printf("Memory error!\n");
                }
                int r = is_rectangular(argq[0], argq[1], argq[2], argq[3]);
                if (r == RECTANGLE)
                {
                    printf("It can be a rectangular.\n");
                }
                else if (r == N_RECTANGLE)
                {
                    printf("It can't be a rectangular.\n");
                }
                else if (r == MUST_BE_BIGGER_THAN_ZERO)
                {
                    printf("Sides must be bigger than 0\n");
                }
                free(argq);
                break;
            }

            break;
            default:
                break;
            }
        }
    }
    return 0;
}