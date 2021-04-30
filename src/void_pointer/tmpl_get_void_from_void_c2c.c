
#include <libtmpl/include/tmpl_config.h>
#include <libtmpl/include/tmpl_complex.h>
#include <libtmpl/include/tmpl_void_pointer.h>

void
tmpl_get_void_from_void_c2c(void *in, void *out,
                            unsigned long int dim,
                            tmpl_ComplexDouble (*f)(tmpl_ComplexDouble))
{
    unsigned long int n;
    tmpl_ComplexDouble *out_data = out;

#if __TMPL_USING_OPENMP__ == 1
#pragma omp parallel for
#endif
    for (n = 0UL; n < dim; ++n)
        out_data[n] = f(((tmpl_ComplexDouble *)in)[n]);
}

