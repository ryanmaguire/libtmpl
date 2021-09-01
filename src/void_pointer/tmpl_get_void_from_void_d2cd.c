
#include <libtmpl/include/tmpl_complex.h>
#include <libtmpl/include/tmpl_void_pointer.h>

void
tmpl_get_void_from_void_d2cd(void *in, void *out,
                             unsigned long int dim,
                             tmpl_ComplexDouble (*f)(double))
{
    unsigned long int n;
    double *x = in;
    tmpl_ComplexDouble *z = out;

#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (n=0; n<dim; ++n)
        z[n] = f(x[n]);

}
