
#include <libtmpl/include/tmpl_complex_ldouble.h>
#include <libtmpl/include/tmpl_complex_function_types.h>
#include <libtmpl/include/tmpl_void_pointer.h>
#include <stddef.h>

void
tmpl_Void_Array_CLD2CLD(const void * const in,
                        void * const out,
                        size_t length,
                        const tmpl_ComplexLongDoubleFunction func)
{
    size_t n;
    const tmpl_ComplexLongDouble * const z = in;
    tmpl_ComplexLongDouble * const w = out;

    if (!in || !out || !length)
        return;

#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (n = 0; n < length; ++n)
        w[n] = func(z[n]);
}
