#ifndef TMPL_SQRT_PADE_DOUBLE_H
#define TMPL_SQRT_PADE_DOUBLE_H

#include <libtmpl/include/tmpl_config.h>

#define A0 (+1.000000000E+00)
#define A1 (+2.750000000E+00)
#define A2 (+2.750000000E+00)
#define A3 (+1.203125000E+00)
#define A4 (+2.148437500E-01)
#define A5 (+1.074218750E-02)

#define B0 (+1.0000000E+00)
#define B1 (+2.2500000E+00)
#define B2 (+1.7500000E+00)
#define B3 (+5.4687500E-01)
#define B4 (+5.8593750E-02)
#define B5 (+9.7656250E-04)

TMPL_STATIC_INLINE
double tmpl_Double_Sqrt_Pade(double x)
{
    const double xs = x - 1.0;
    const double num = A0 + xs*(A1 + xs*(A2 + xs*(A3 + xs*(A4 + xs*A5))));
    const double den = B0 + xs*(B1 + xs*(B2 + xs*(B3 + xs*(B4 + xs*B5))));
    return num / den;
}

#undef A0
#undef A1
#undef A2
#undef A3
#undef A4
#undef A5

#undef B0
#undef B1
#undef B2
#undef B3
#undef B4
#undef B5

#endif
