
#include <libtmpl/include/types/tmpl_complex_path_double.h>
#include <libtmpl/include/tmpl_void_pointer.h>
#include <stddef.h>

void
tmpl_Void_Array_L2CD(const void * const in,
                     void * const out,
                     size_t length,
                     const tmpl_ComplexDoublePath func)
{
    size_t n;
    const signed long int * const x = in;
    tmpl_ComplexDouble * const y = out;

    if (!in || !out || !length)
        return;

#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (n = 0; n < length; ++n)
        y[n] = func((double)(x[n]));
}
