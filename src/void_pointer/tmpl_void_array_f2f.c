#include <libtmpl/include/tmpl_real_function_types.h>
#include <libtmpl/include/tmpl_void_pointer.h>
#include <stddef.h>

void
tmpl_Void_Array_F2F(const void * const in,
                    void * const out,
                    size_t length,
                    const tmpl_FloatFunction func)
{
    size_t n;
    const float * const x = in;
    float * const y = out;

    if (!in || !out || !length)
        return;

#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (n = 0; n < length; ++n)
        y[n] = func(x[n]);
}
