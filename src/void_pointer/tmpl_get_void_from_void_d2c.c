
#include <libtmpl/include/tmpl_complex.h>
#include <libtmpl/include/tmpl_void_pointer.h>

void
tmpl_get_void_from_void_d2c(void *in, void *out,
                            unsigned long int dim,
                            tmpl_ComplexDouble (*f)(double))
{
    unsigned long int n;
    tmpl_ComplexDouble *out_data = out;

#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (n=0; n<dim; ++n)
        out_data[n] = f(((double *)in)[n]);

}
