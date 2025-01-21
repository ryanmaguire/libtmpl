
#include <libtmpl/include/types/tmpl_complex_float.h>
#include <libtmpl/include/types/tmpl_complex_path_float.h>
#include <libtmpl/include/tmpl_void_pointer.h>
#include <stddef.h>

void
tmpl_Void_Array_F2CF(const void * const in,
                     void * const out,
                     size_t length,
                     const tmpl_ComplexFloatPath func)
{
    size_t n;
    const float * const x = in;
    tmpl_ComplexFloat * const z = out;

    if (!in || !out || !length)
        return;

#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (n = 0; n < length; ++n)
        z[n] = func(x[n]);
}
