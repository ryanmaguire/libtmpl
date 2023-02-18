#include <libtmpl/include/tmpl_config.h>

#if TMPL_USE_INLINE != 1

#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_complex.h>

tmpl_ComplexDouble tmpl_CDouble_ExpiPi(double t)
{
    tmpl_ComplexDouble z;
    tmpl_Double_SinCosPi(t, &z.dat[1], &z.dat[0]);
    return z;
}
#endif
