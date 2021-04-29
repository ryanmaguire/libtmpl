
#include "tmpl_py_c_api.h"
#include <stdlib.h>

void *
tmpl_get_array_from_one_double(void *in, unsigned long dim,
                               double (*f)(double));
{
    unsigned long n;
    void *out;
    double *out_data;
    out_data = malloc(sizeof(*out_data)*dim);

    for (n = 0UL; n < dim; ++n)
        out_data[n] = f(((double *)in)[n]);

    out = out_data;
    return out;
}

