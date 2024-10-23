
#include <libtmpl/include/tmpl_complex_ldouble.h>
#include <libtmpl/include/tmpl_complex_functional_types.h>
#include <libtmpl/include/tmpl_void_pointer.h>
#include <stddef.h>

void
tmpl_Void_Array_CLD2LD(const void * const in,
                       void * const out,
                       size_t length,
                       const tmpl_ComplexLongDoubleFunctional func)
{
    size_t n;
    const tmpl_ComplexLongDouble * const z = in;
    long double * const x = out;

    if (!in || !out || !length)
        return;

#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (n = 0; n < length; ++n)
        x[n] = func(z[n]);
}
