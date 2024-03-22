#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <libtmpl/include/tmpl_array_integer.h>

static signed int randint(void)
{
    int n = rand();
    double x = (double)n / (double)RAND_MAX;
    return (int)(x * 2.0);
}

int main(void)
{
    size_t n;
    const size_t N = (size_t)1E9;
    signed int * const arr = malloc(sizeof(*arr) * N);
    clock_t t0, t1;
    double rms0, rms1;

    for (n = 0; n < N; ++n)
        arr[n] = randint();

    t0 = clock();
    rms0 = tmpl_Int_Array_Double_RMS(arr, N);
    t1 = clock();

    printf("RMS:       %e\n", (double)(t1 - t0) / CLOCKS_PER_SEC);

    t0 = clock();
    rms1 = tmpl_Int_Array_Double_Quick_RMS(arr, N);
    t1 = clock();

    printf("Quick RMS: %e\n", (double)(t1 - t0) / CLOCKS_PER_SEC);

    printf("%e\n%e\n", rms0, rms1);
    return 0;
}
