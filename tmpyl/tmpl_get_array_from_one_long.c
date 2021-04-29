
#include "tmpl_py_c_api.h"
#include <stdlib.h>

void *
tmpl_get_array_from_one_long(void *in, unsigned long dim, long (*f)(long));
{
    unsigned long n;
    long x;
    void *out;
    long *out_data;
    out_data = malloc(sizeof(*out_data)*dim);

    for (n=0; n<dim; ++n)
    {
        x = ((long *)in)[n];
        out_data[n] = f(x);
    }

    out = out_data;
    return out;
}
