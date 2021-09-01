
#include <libtmpl/include/tmpl_void_pointer.h>

void
tmpl_get_void_from_void_f2f(void *in, void *out,
                            unsigned long int dim,
                            float (*f)(float))
{
    unsigned long int n;
    float *x = in;
    float *y = out;

#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (n = 0UL; n < dim; ++n)
        y[n] = f(x[n]);
}

