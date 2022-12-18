#include <stdio.h>
#include <stdlib.h>
#include <libtmpl/include/tmpl_sort.h>
#include <time.h>

static double rand_real(void)
{
    int n = rand();
    return (double)(n) / (double)(RAND_MAX);
}

static inline int comp(const void* a, const void* b)
{
    double va = *(const double*)a;
    double vb = *(const double*)b;
    return (va > vb) - (va < vb);
}

int main(void)
{
    const size_t len = (size_t)(1E5);
    double *arrtmpl = (double *)(malloc(sizeof(*arrtmpl)*len));
    double *arrc = (double *)(malloc(sizeof(*arrc)*len));
    size_t n;
    clock_t t1, t2;

    for (n = 0; n < len; ++n)
    {
        double x = rand_real();
        arrtmpl[n] = x;
        arrc[n] = x;
    }

    printf("samples: %e\n", (double)(len));
    t1 = clock();
    tmpl_Double_Merge_Sort(arrtmpl, len);
    t2 = clock();
    printf("libtmpl: %f\n", (double)(t2 - t1)/(double)CLOCKS_PER_SEC);

    t1 = clock();
    qsort(arrc, len, sizeof(double), comp);
    t2 = clock();
    printf("C:       %f\n", (double)(t2 - t1)/(double)CLOCKS_PER_SEC);

    free(arrc);
    free(arrtmpl);
    return 0;
}
