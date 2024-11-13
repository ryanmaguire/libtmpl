
#include <libtmpl/include/tmpl_complex_double.h>
#include <libtmpl/include/tmpl_complex_function_types.h>
#include <libtmpl/include/tmpl_void_pointer.h>
#include <stddef.h>

void
tmpl_Void_Array_CD2CD(const void * const in,
                      void * const out,
                      size_t length,
                      const tmpl_ComplexDoubleFunction func)
{
    size_t n;
    const tmpl_ComplexDouble * const z = in;
    tmpl_ComplexDouble * const w = out;

    if (!in || !out || !length)
        return;

#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (n = 0; n < length; ++n)
        w[n] = func(z[n]);
}