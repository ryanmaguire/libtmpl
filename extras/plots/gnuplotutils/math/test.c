
#include <math.h>
#include <stdio.h>
#include <libtmpl/include/tmpl_math.h>
#include <time.h>
#include <stdlib.h>

int main(void)
{
    double start, end, dx, *x, *y0, *y1, max, temp;
    clock_t t1, t2;
    unsigned int N = 1E8;
    unsigned int n;
    start = -2000.0;
    end   =  2000.0;
    max   =  0.0;
	dx    = (end - start) / (double)N;

    x  = malloc(sizeof(*x)  * N);
    y0 = malloc(sizeof(*y0) * N);
    y1 = malloc(sizeof(*y1) * N);

    for (n = 0U; n < N; ++n)
        x[n] = start + (double)n * dx;

    t1 = clock();
    for (n = 0U; n < N; ++n)
        y0[n] = tmpl_Double_Mod_2(x[n]);
    t2 = clock();
    printf("tmpl: %f\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    t1 = clock();
    for (n = 0U; n < N; ++n)
        y1[n] = fmod(x[n], 2.0);
    t2 = clock();
    printf("glibc: %f\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    for (n = 0U; n < N; ++n)
    {
        temp = fabs(y1[n] - y0[n]);

        if (temp > max)
            max = temp;
    }

    free(x);
    free(y0);
    free(y1);
    printf("%.16f\n", max);
    return 0;
}
