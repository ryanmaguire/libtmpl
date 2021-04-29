
#include "tmpl_py_c_api.h"

void
tmpl_get_void_from_void_f2f(void *in, void *out,
                            unsigned long int dim,
                            float (*f)(float))
{
    unsigned long int n;
    float *out_data = out;

    for (n = 0UL; n < dim; ++n)
        out_data[n] = f(((float *)in)[n]);
}

