#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include "task1.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("ERROR: Incorrect input of arguments\n");
        return ERROR_UNKNOWN_ARGUMENT;
    }

    char *end;
    long long x = strtol(argv[1], &end, 10);
    if (*end != '\0')
    {
        printf("ERROR: Number out of range\n");
        return ERROR_OUT_OF_RANGE;
    }
    if (x == LLONG_MAX || x == LLONG_MIN)
    {
        printf("ERROR: Number out of range\n");
        return ERROR_OUT_OF_RANGE;
    }

    const char *flag = argv[2];
    const char *flags[] = {"-h", "/h", "-p", "/p", "-s", "/s", "-e", "/e", "-a", "/a", "-f", "/f"};
    callback functions[] = {function_h, function_p, function_s, function_e, function_a, function_f};

    int flag_index = fing_flag(flag, flags, sizeof(flags) / sizeof(flags[0]));
    if (flag_index == -1)
    {
        printf("ERROR: Unknown flags\n");
        return ERROR_UNKNOWN_FLAG;
    }
    status_return status = functions[flag_index](x);
    switch (status)
    {
    case SUCCESS:
        break;
    case ERROR_UNKNOWN_ARGUMENT:
        printf("ERROR: Incorrect input of arguments\n");
        break;
    case ERROR_OUT_OF_RANGE:
        printf("ERROR: Number out of range\n");
        break;
    case ERROR_NO_MULTIPLES:
        printf("ERROR: No multiples found\n");
        break;
    case ERROR_NOT_PRIME:
        printf("ERROR: Not a valid prime candidate\n");
        break;
    case ERROR_UNKNOWN_FLAG:
        printf("ERROR: Unknown flags\n");
        break;
    case ERROR_NOT_PRIME_NOT_COMPOSITE:
        printf("ERROR: This digit is not prime and not composite\n");
        break;
    default:
        printf("i dont know(((\n");
    }

    return status;
}