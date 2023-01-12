#ifndef TMPL_SINCOS_REDUCTION_H
#define TMPL_SINCOS_REDUCTION_H

#include <libtmpl/include/tmpl_config.h>
#include <libtmpl/include/tmpl_math.h>

#define hp1 (6.123233995736766035868820147292E-17)
#define mp1 (1.5707963407039642333984375)
#define mp2 (-1.390906756437715330321225337684E-08)
#define pp3 (-4.978996231479909897912720928570E-17)
#define pp4 (-1.903488962019326611163352272841e-25)
#define hpinv (6.366197723675813824328884038550e-01)
#define toint (6.755399441055744000000000000000e+15)

TMPL_INLINE_DECL
unsigned int tmpl_Double_SinCos_Reduction(double x, double *a, double *da)
{
    tmpl_IEEE754_Double w;
    const double t = (x * hpinv + toint);
    const double xn = t - toint;
    const double y = (x - xn * mp1) - xn * mp2;
    const double t1 = xn * pp3;
    const double t2 = y - t1;
    const double t3 = xn * pp4;
    const double b = t2 - t3;
    const double db = (y - t2) - t1;
    w.r = t;
    *a = b;
    *da = db + ((t2 - b) - t3);
    return w.bits.man3 & 3;
}

#undef hp1
#undef mp1
#undef mp2
#undef pp3
#undef pp4
#undef hpinv
#undef toint

#endif
