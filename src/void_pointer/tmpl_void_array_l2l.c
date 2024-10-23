
#include <libtmpl/include/tmpl_integer_function_types.h>
#include <libtmpl/include/tmpl_void_pointer.h>
#include <stddef.h>

void
tmpl_Void_Array_L2L(const void * const in,
                    void * const out,
                    size_t length,
                    tmpl_LongFunction func)
{
    size_t n;
    const signed long int * const x = in;
    signed long int * const y = out;

    if (!in || !out || !length)
        return;

#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (n = 0; n < length; ++n)
        y[n] = func(x[n]);
}
