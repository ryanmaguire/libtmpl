
#include <libtmpl/include/tmpl_complex_double.h>
#include <libtmpl/include/tmpl_complex_path_types.h>
#include <libtmpl/include/tmpl_void_pointer.h>
#include <stddef.h>

void
tmpl_Void_Array_D2CD(const void * const in,
                     void * const out,
                     size_t length,
                     const tmpl_ComplexDoublePath func)
{
    size_t n;
    const double * const x = in;
    tmpl_ComplexDouble * const z = out;

    if (!in || !out || !length)
        return;

#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (n = 0; n < length; ++n)
        z[n] = func(x[n]);
}
