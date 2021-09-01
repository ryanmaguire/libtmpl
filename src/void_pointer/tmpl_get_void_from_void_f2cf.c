
#include <libtmpl/include/tmpl_complex.h>
#include <libtmpl/include/tmpl_void_pointer.h>

void
tmpl_get_void_from_void_f2cf(void *in, void *out,
                             unsigned long int dim,
                             tmpl_ComplexFloat (*f)(float))
{
    unsigned long int n;
    float *x = in;
    tmpl_ComplexFloat *z = out;

#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (n=0; n<dim; ++n)
        z[n] = f(x[n]);
}
