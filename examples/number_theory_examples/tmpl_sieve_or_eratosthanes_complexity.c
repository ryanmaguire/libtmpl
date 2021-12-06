

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <libtmpl/include/tmpl_number_theory.h>

int main(void)
{
    clock_t t1, t2;
    double *times;
    tmpl_ULongVector *out;
    unsigned int N = 1E5;
    unsigned int n;
    out = malloc(sizeof(*out) * N);

    for (n = 0; n < N; ++n)
    {
        t1 = clock();
        out = tmpl_Sieve_of_Eratosthenes(n);
        t2 = clock();
        tmpl_Destroy_ULongVector(&out);
        times[n] = (double)(t2-t1)/CLOCKS_PER_SEC;
    }
}

