#include <libtmpl/include/tmpl_config.h>

#if TMPL_USE_INLINE != 1

#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_complex.h>

tmpl_ComplexLongDouble tmpl_CLDouble_ExpiPi(long double t)
{
    tmpl_ComplexLongDouble z;
    tmpl_LDouble_SinCosPi(t, &z.dat[1], &z.dat[0]);
    return z;
}
#endif
