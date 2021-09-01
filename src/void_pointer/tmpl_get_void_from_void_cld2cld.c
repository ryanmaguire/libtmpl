
#include <libtmpl/include/tmpl_complex.h>
#include <libtmpl/include/tmpl_void_pointer.h>

void
tmpl_get_void_from_void_cld2cld(void *in, void *out,
                                unsigned long int dim,
                                tmpl_ComplexLongDouble (*f)(tmpl_ComplexLongDouble))
{
    unsigned long int n;
    tmpl_ComplexLongDouble *z = in;
    tmpl_ComplexLongDouble *w = out;

#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (n = 0UL; n < dim; ++n)
        w[n] = f(z[n]);
}
