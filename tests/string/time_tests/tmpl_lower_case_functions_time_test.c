#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#include <libtmpl/include/tmpl_string.h>

int main(void)
{
    char *str, *test1, *test2, *test3;
    int random;
    unsigned long int n;
    unsigned long int N = 1E6;
    clock_t t1, t2;

    str = malloc(N);
    test1 = malloc(N);
    test2 = malloc(N);
    test3 = malloc(N);

    for (n = 0; n < N; ++n)
    {
        random = rand() % 255;
        str[n] = (char)random;
    }

    t1 = clock();
    for (n = 0; n < N; ++n)
        test1[n] = tmpl_ASCII_Lower_Case(str[n]);
    t2 = clock();
    printf("tmpl_ASCII_Lower_Case: %f\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    t1 = clock();
    for (n = 0; n < N; ++n)
        test2[n] = tmpl_Lower_Case(str[n]);
    t2 = clock();
    printf("tmpl_Lower_Case:       %f\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    t1 = clock();
    for (n = 0; n < N; ++n)
        test3[n] = tolower(str[n]);
    t2 = clock();
    printf("tolower:               %f\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    for (n = 0U; n < N; ++n)
    {
        if ((test1[n] != test3[n]) || (test2[n] != test3[n]))
        {
            puts("FAILED");
            return -1;
        }
    }

    puts("PASSED");
    free(test1);
    free(test2);
    free(test3);
    return 0;
}

