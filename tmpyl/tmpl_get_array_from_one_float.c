
#include "tmpl_py_c_api.h"
#include <stdlib.h>

void *
tmpl_get_array_from_one_float(void *in, unsigned long dim, float (*f)(float));
{
    unsigned long n;
    void *out;
    float *out_data;
    float x;
    out_data = malloc(sizeof(*out_data) * dim);

    for (n = 0UL; n < dim; ++n)
    {
        x = ((float *)in)[n];
        out_data[n] = f(x);
    }

    out = out_data;
    return out;
}
