
#include "tmpl_py_c_api.h"

void
tmpl_get_void_from_void_d2c(void *in, void *out,
                            unsigned long int dim,
                            tmpl_ComplexDouble (*f)(double))
{
    unsigned long int n;
    tmpl_ComplexDouble *out_data = out;

    for (n=0; n<dim; ++n)
        out_data[n] = f(((double *)in)[n]);

}
