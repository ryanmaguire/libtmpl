
#include "tmpl_py_auxiliary.h"
#include <stdlib.h>

void *
tmpl_get_void_from_double(double *in, unsigned long dim, double (*f)(double))
{
    long n;
    void *out;
    double *out_data;
    out_data = malloc(sizeof(*out_data) * dim);

    for (n=0; n<dim; ++n)
        out_data[n] = f(in[n]);

    out = out_data;
    return out;
}

