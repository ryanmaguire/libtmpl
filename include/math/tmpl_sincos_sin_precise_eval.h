#ifndef TMPL_SINCOS_SIN_PRECISE_EVAL_H
#define TMPL_SINCOS_SIN_PRECISE_EVAL_H

#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/math/tmpl_sincos_data_double.h>
#include <libtmpl/include/math/tmpl_sincos_sin_precise_small.h>

#define S0 (1.0)
#define S1 (-1.66666666666664880952546298448555E-01)
#define S2 (8.33333214285722277379541354343671E-03)

#define C0 (4.99999999999999999999950396842453E-01)
#define C1 (-4.16666666666664434524222570944589E-02)
#define C2 (1.38888874007937613028114285595617E-03)

#define TMPL_BIG_NUMBER (5.2776558133248E13)

static double tmpl_Double_Sin_Precise_Eval(double x, double dx)
{
    double xold = x;
    double x2, s, sn, ssn, c, cs, ccs, cor;
    tmpl_IEEE754_Double w;
    unsigned int k;
    const double abs_x = tmpl_Double_Abs(x);

    if (abs_x < 0.126)
        return tmpl_Double_Sin_Precise_Small(x, dx);

    if (x <= 0)
        dx = -dx;

    w.r = TMPL_BIG_NUMBER + abs_x;
    x = abs_x - (w.r - TMPL_BIG_NUMBER);

    x2 = x*x;
    s = x*(S0 + dx + x2*(S1 + x2*S2));
    c = x*dx + x2*(C0 + x2*(C1 + x2*C2));
    k = (w.bits.man3 << 2U) & 0xFFFF;
    sn = tmpl_Double_SinCos_Table[k];
    ssn = tmpl_Double_SinCos_Table[k + 1];
    cs = tmpl_Double_SinCos_Table[k + 2];
    ccs = tmpl_Double_SinCos_Table[k + 3];
    cor = (ssn + s * ccs - sn * c) + cs * s;
    return tmpl_Double_Copysign (sn + cor, xold);
}

#undef S0
#undef S1
#undef S2
#undef C0
#undef C1
#undef C2
#undef TMPL_BIG_NUMBER
#endif
