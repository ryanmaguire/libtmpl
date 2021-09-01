
#include <libtmpl/include/tmpl_complex.h>
#include <libtmpl/include/tmpl_void_pointer.h>

void
tmpl_get_void_from_void_cf2cf(void *in, void *out,
                              unsigned long int dim,
                              tmpl_ComplexFloat (*f)(tmpl_ComplexFloat))
{
    unsigned long int n;
    tmpl_ComplexFloat *z = in;
    tmpl_ComplexFloat *w = out;

#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (n = 0UL; n < dim; ++n)
        w[n] = f(z[n]);
}