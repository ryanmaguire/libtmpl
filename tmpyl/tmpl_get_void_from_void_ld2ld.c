
#include "tmpl_py_c_api.h"

void
tmpl_get_void_from_void_ld2ld(void *in, void *out,
                              unsigned long int dim,
                              long double(*f)(long double))
{
    unsigned long int n;
    long double *out_data = out;

    for (n=0; n<dim; ++n)
        out_data[n] = f(((long double *)in)[n]);
}

