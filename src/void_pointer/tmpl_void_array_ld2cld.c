#include <libtmpl/include/types/tmpl_complex_ldouble.h>
#include <libtmpl/include/types/tmpl_complex_path_ldouble.h>
#include <libtmpl/include/tmpl_void_pointer.h>
#include <stddef.h>

void
tmpl_Void_Array_LD2CLD(const void * const in,
                       void * const out,
                       size_t length,
                       const tmpl_ComplexLongDoublePath func)
{
    size_t n;
    const long double * const x = in;
    tmpl_ComplexLongDouble * const z = out;

    if (!in || !out || !length)
        return;

#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (n = 0; n < length; ++n)
        z[n] = func(x[n]);
}
