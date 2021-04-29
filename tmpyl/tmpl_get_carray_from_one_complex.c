
#include "tmpl_py_c_api.h"
#include <stdlib.h>

void *
tmpl_get_carray_from_one_complex(void *in, unsigned long int dim,
                                 tmpl_ComplexDouble (*f)(tmpl_ComplexDouble))
{
    long n;
    void *out;
    rssringoccs_ComplexDouble *out_data;
    rssringoccs_ComplexDouble z;
    out_data = malloc(sizeof(*out_data) * dim);

    for (n=0; n<dim; ++n)
    {
        z = ((rssringoccs_ComplexDouble *)in)[n];
        out_data[n] = f(z);
    }

    out = out_data;
    return out;
}

