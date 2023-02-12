#include <libtmpl/include/tmpl_config.h>

#if TMPL_USE_INLINE != 1

#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_complex.h>

tmpl_ComplexFloat tmpl_CFloat_ExpiPi(float t)
{
    tmpl_ComplexFloat z;
    tmpl_Float_SinCosPi(t, &z.dat[1], &z.dat[0]);
    return z;
}
#endif
