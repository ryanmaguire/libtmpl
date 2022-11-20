#include <stdio.h>
#include <stdlib.h>
#include <libtmpl/include/tmpl_sort.h>
#include <gsl/gsl_sort_double.h>
#include <time.h>

static double rand_real(void)
{
    int n = rand();
    return (double)(n) / (double)(RAND_MAX);
}

int main(void)
{
    const size_t len = (size_t)(1E7);
    double *arrtmpl = (double *)(malloc(sizeof(*arrtmpl)*len));
    double *arrc = (double *)(malloc(sizeof(*arrc)*len));
    size_t n;
    int success;
    clock_t t1, t2;

    for (n = 0; n < len; ++n)
    {
        double x = rand_real();
        arrtmpl[n] = x;
        arrc[n] = x;
    }

    t1 = clock();
    success = tmpl_Double_Merge_Sort(arrtmpl, len);
    t2 = clock();

    if (!success)
    {
        puts("tmpl_Double_Merge_Sort failed, malloc returned NULL.");
        return -1;
    }

    printf("libtmpl: %f\n", (double)(t2 - t1)/(double)CLOCKS_PER_SEC);

    t1 = clock();
    gsl_sort(arrc, 1, n);
    t2 = clock();
    printf("C:       %f\n", (double)(t2 - t1)/(double)CLOCKS_PER_SEC);

    for (n = 0; n < len; ++n)
    {
        if (arrtmpl[n] != arrc[n])
        {
            puts("FAIL");
            return -1;
        }
    }
    puts("PASS");
    return 0;
}
