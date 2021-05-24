
#include <libtmpl/include/tmpl_void_pointer.h>

void
tmpl_get_void_from_void_ld2ld(void *in, void *out,
                              unsigned long int dim,
                              long double(*f)(long double))
{
    unsigned long int n;
    long double *out_data = out;

#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (n=0; n<dim; ++n)
        out_data[n] = f(((long double *)in)[n]);
}

