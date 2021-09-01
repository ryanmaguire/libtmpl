
#include <libtmpl/include/tmpl_void_pointer.h>

void
tmpl_get_void_from_void_d2d(void *in, void *out,
                            unsigned long int dim,
                            double (*f)(double))
{
    unsigned long int n;
    double *x = in;
    double *y = out;

#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (n = 0UL; n < dim; ++n)
        y[n] = f(x[n]);
}

