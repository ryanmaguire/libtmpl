
#include "tmpl_py_c_api.h"

void
tmpl_get_void_from_void_l2l(void *in, void *out,
                            unsigned long int dim,
                            long int (*f)(long int))
{
    unsigned long int n;
    long int *out_data = out;

    for (n=0; n<dim; ++n)
        out_data[n] = f(((long *)in)[n]);
}

