#include <libtmpl/include/types/tmpl_complex_float.h>
#include <libtmpl/include/types/tmpl_complex_functional_float.h>
#include <libtmpl/include/tmpl_void_pointer.h>
#include <stddef.h>

void
tmpl_Void_Array_CF2F(const void * const in,
                     void * const out,
                     size_t length,
                     const tmpl_ComplexFloatFunctional func)
{
    size_t n;
    const tmpl_ComplexFloat * const z = in;
    float * const x = out;

    if (!in || !out || !length)
        return;

#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (n = 0; n < length; ++n)
        x[n] = func(z[n]);
}
