#include <libtmpl/include/types/tmpl_function_ldouble.h>
#include <libtmpl/include/tmpl_void_pointer.h>
#include <stddef.h>

void
tmpl_Void_Array_LD2LD(const void * const in,
                      void * const out,
                      size_t length,
                      const tmpl_LongDoubleFunction func)
{
    size_t n;
    const long double * const x = in;
    long double * const y = out;

    if (!in || !out || !length)
        return;

#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (n = 0; n < length; ++n)
        y[n] = func(x[n]);
}
