#include <libtmpl/include/tmpl_real_function_types.h>
#include <libtmpl/include/tmpl_void_pointer.h>
#include <stddef.h>

void
tmpl_Void_Array_D2D(const void * const in,
                    void * const out,
                    size_t length,
                    const tmpl_DoubleFunction func)
{
    size_t n;
    const double * const x = in;
    double * const y = out;

    if (!in || !out || !length)
        return;

#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (n = 0; n < length; ++n)
        y[n] = func(x[n]);
}
