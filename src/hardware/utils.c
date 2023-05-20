#include "utils.h"

#define TAU 6.2831853071795864769252867665590057683936
clock_t begin_t;
clock_t end_t;

void init_clock()
{
    begin_t = clock();
    end_t = clock();
}

void tick_clock()
{
    end_t = clock();
}

double nibble_rnd(int x)
{
    return (double)rand() / RAND_MAX * (x);
}

char nibble_chr(int x)
{
    return (char)x;
}

int nibble_flr(double x)
{
    return (int)floor(x);
}

int nibble_ceil(double x)
{
    return (int)ceil(x);
}

double nibble_time(void)
{
    return ((double)(end_t - begin_t) / CLOCKS_PER_SEC) * 10;
}

char *nibble_sub(char *str, int start, int end)
{
    char *result;
    int i = 0;

    if (end <= -1)
    {
        end = strlen(str);
    }

    result = malloc(end - start + 1);

    for (i = 0; i < end - start; i++)
    {
        result[i] = str[start + i];
    }
    result[i] = '\0';
    return result;
}

double nibble_sin(double x)
{
    return -sin(x * 3.1415 * 2);
}

double nibble_cos(double x)
{
    return cos(x * 3.1415 * 2);
}

double nibble_atan2(double x, double y)
{
    return 0.75 + atan2((double)x, (double)y) / TAU;
}

void nibble_trace(char *text)
{
    printf("%s\n", text);
}

double nibble_api_mid(double x, double y, double z)
{
    return x > y   ? y > z ? y : MIN(x, z)
             : x > z ? x
                   : MIN(y, z);
}