#ifndef TMPL_SINCOS_SIN_PRECISE_SMALL_H
#define TMPL_SINCOS_SIN_PRECISE_SMALL_H

#define A1 (-1.666666666666666574148081281237e-01)
#define A2 (8.333333333332328812792511030239e-03)
#define A3 (-1.984126983441464233542950168498e-04)
#define A4 (2.755729806860771032218275847225e-06)
#define A5 (-2.502201484831839766033848070168e-08)

static double tmpl_Double_Sin_Precise_Small(double x, double dx)
{
    const double x2 = x*x;
    const double poly = x*(A1 + x2*(A2 + x2*(A3 + x2*(A4 + x2*A5))));
    return (poly - 0.5*dx)*x2 + dx + x;
}

#undef A1
#undef A2
#undef A3
#undef A4
#undef A5
#endif
