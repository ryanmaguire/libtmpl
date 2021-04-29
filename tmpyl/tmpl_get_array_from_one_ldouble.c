
#include "tmpl_py_c_api.h"
#include <stdlib.h>

void *
tmpl_get_array_from_one_ldouble(void *in, unsigned long dim,
                                long double(*f)(long double));
{
    long n;
    void *out;
    long double *out_data;
    out_data = malloc(sizeof(*out_data)*dim);

    for (n=0; n<dim; ++n)
        out_data[n] = f(((long double *)in)[n]);

    out = out_data;
    return out;
}
