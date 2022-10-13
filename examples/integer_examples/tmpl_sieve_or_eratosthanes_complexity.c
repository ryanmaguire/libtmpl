#include <stdio.h>
#include <time.h>
#include <libtmpl/include/tmpl_integer.h>

int main(void)
{
    clock_t t1, t2;
    double *times;
    tmpl_ULongVector *out;
    unsigned int N = 1E5;
    unsigned int n;

    for (n = 0; n < N; ++n)
    {
        t1 = clock();
        out = tmpl_Sieve_of_Eratosthenes(n);
        t2 = clock();
        tmpl_Destroy_ULongVector(&out);
        printf("%f\n", (double)(t2-t1)/CLOCKS_PER_SEC);
    }

    return 0;
}

