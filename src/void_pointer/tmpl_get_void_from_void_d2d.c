
#include <libtmpl/include/tmpl_void_pointer.h>

void
tmpl_get_void_from_void_d2d(void *in, void *out,
                            unsigned long int dim,
                            double (*f)(double))
{
    unsigned long int n;
    double *out_data = out;

#pragma omp parallel for
    for (n = 0UL; n < dim; ++n)
        out_data[n] = f(((double *)in)[n]);
}

