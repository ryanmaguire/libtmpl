#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

static void spaces1(char* s)
{
    const char* d = s;

    /*  If the input is NULL, the following will cause a segfault. Check.     */
    if (!s)
        return;

    do {
        while (*d == ' ') {
            ++d;
        }
    } while ((*s++ = *d++));
}

static void spaces2(char *s, unsigned int length)
{
    const char* d = s;
    const char* init = s;

    if (!s)
        return;

    while ((d - init) <= length)
    {
        while (((d - init) <= length)  && *d == ' ' )
        {
            ++d;
        }
        *s = *d;
        ++s;
        ++d;
    }

    if ((d - init) <= length) {
        *s = *d;
    }
}

int main(void)
{
    unsigned int length;
    unsigned int* lengths;
    char **strings0, **strings1;
    int random;
    unsigned int n, m;
    unsigned int N = 1E6;
    clock_t t1, t2;

    strings0 = malloc(sizeof(*strings0)*N);
    strings1 = malloc(sizeof(*strings1)*N);
    lengths = (unsigned int*)malloc(sizeof(*lengths) * N);

    for (n = 0U; n < N; ++n)
    {
        length = (rand() % 20);
        lengths[n] = length;
        strings0[n] = malloc(length + 1U);
        strings1[n] = malloc(length + 1U);

        for (m = 0U; m < length; ++m)
        {
            random = rand() % 256;
            strings0[n][m] = (char)random;
            strings1[n][m] = strings0[n][m];
        }

        strings0[n][length] = '\0';
        strings1[n][length] = '\0';
    }

    t1 = clock();
    for (n = 0; n < N; ++n)
        spaces1(strings0[n]);
    t2 = clock();
    printf("Test 1: %f\n", (double)(t2 - t1)/CLOCKS_PER_SEC);

    t1 = clock();
    for (n = 0; n < N; ++n)
        spaces2(strings1[n], lengths[n]);
    t2 = clock();
    printf("Test 2: %f\n", (double)(t2 - t1)/CLOCKS_PER_SEC);

    for (n = 0; n < N; ++n)
    {
        if (strlen(strings0[n]) != strlen(strings1[n]))
            printf("len0 != len1: n = %u\n", n);
        else
        {
            for (m = 0U; m < strlen(strings0[n]); ++m)
            {
                if (strings0[n][m] != strings1[n][m])
                {
                    printf("str0 != str1: %u %s %s\n", n, strings0[n], strings1[n]);
                    break;
                }
            }
        }

        free(strings0[n]);
        free(strings1[n]);
    }

    free(strings0);
    free(strings1);
    free(lengths);
    return 0;
}

