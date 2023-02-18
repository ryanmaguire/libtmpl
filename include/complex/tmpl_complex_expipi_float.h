#ifndef TMPL_COMPLEX_EXPIPI_FLOAT_H
#define TMPL_COMPLEX_EXPIPI_FLOAT_H

#include <libtmpl/include/tmpl_config.h>

#if TMPL_USE_INLINE == 1

#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_complex.h>

TMPL_INLINE_DECL
tmpl_ComplexFloat tmpl_CFloat_ExpiPi(float t)
{
    tmpl_ComplexFloat z;
    tmpl_Float_SinCosPi(t, &z.dat[1], &z.dat[0]);
    return z;
}
#endif
#endif
