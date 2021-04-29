
#include "tmpl_py_c_api.h"
#include <stdlib.h>

void *
tmpl_get_carray_from_one_double(double *in, unsigned long dim,
                                tmpl_ComplexDouble (*f)(double));
{
    long n;
    void *out;
    rssringoccs_ComplexDouble *out_data;
    out_data = malloc(sizeof(*out_data)*dim);

    for (n=0; n<dim; ++n)
        out_data[n] = f(in[n]);

    out = out_data;
    return out;
}
