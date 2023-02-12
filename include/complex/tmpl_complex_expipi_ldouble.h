#ifndef TMPL_COMPLEX_EXPIPI_LDOUBLE_H
#define TMPL_COMPLEX_EXPIPI_LDOUBLE_H

#include <libtmpl/include/tmpl_config.h>

#if TMPL_USE_INLINE == 1

#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_complex.h>

TMPL_INLINE_DECL
tmpl_ComplexLongDouble tmpl_CLDouble_ExpiPi(long double t)
{
    tmpl_ComplexLongDouble z;
    tmpl_LDouble_SinCosPi(t, &z.dat[1], &z.dat[0]);
    return z;
}
#endif
#endif
