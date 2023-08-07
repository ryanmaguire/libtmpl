#ifndef TMPL_BESSEL_J0_MACLAURIN_DOUBLE_H
#define TMPL_BESSEL_J0_MACLAURIN_DOUBLE_H

#include <libtmpl/include/tmpl_config.h>
#include <libtmpl/include/tmpl_special_functions_real.h>

/*  Coefficients for the polynomial.                                          */
#define A00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define A01 (-2.5000000000000000000000000000000000000000000000000E-01)
#define A02 (+1.5625000000000000000000000000000000000000000000000E-02)
#define A03 (-4.3402777777777777777777777777777777777777777777778E-04)
#define A04 (+6.7816840277777777777777777777777777777777777777778E-06)
#define A05 (-6.7816840277777777777777777777777777777777777777778E-08)
#define A06 (+4.7095027970679012345679012345679012345679012345679E-10)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) \
A00 + z*(A01 + z*(A02 + z*(A03 + z*(A04 + z*(A05 + z*A06)))))

TMPL_INLINE_DECL
double tmpl_Double_Bessel_J0_Maclaurin(double x)
{
    const double x2 = x*x;
    return TMPL_POLY_EVAL(x2);
}

#undef A00
#undef A01
#undef A02
#undef A03
#undef A04
#undef A05
#undef A06
#undef TMPL_POLY_EVAL

#endif
