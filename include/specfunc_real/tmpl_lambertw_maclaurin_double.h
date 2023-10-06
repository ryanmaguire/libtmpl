/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_LAMBERTW_MACLAURIN_DOUBLE_H
#define TMPL_LAMBERTW_MACLAURIN_DOUBLE_H

/*  TMPL_STATIC_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the Maclaurin series.                                    */
#define A1 (+1.000000000000000000E+00)
#define A2 (-1.000000000000000000E+00)
#define A3 (+1.500000000000000000E+00)
#define A4 (-2.666666666666666519E+00)
#define A5 (+5.208333333333333037E+00)
#define A6 (-1.080000000000000071E+01)
#define A7 (+2.334305555555555500E+01)
#define A8 (-5.201269841269841265E+01)
#define A9 (+1.186252232142857110E+02)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) \
z * (A1 + z*(A2 + z*(A3 + z*(A4 + z*(A5 + z*(A6 + z*(A7 + z*(A8 + z*A9))))))))

/*  Computes the LambertW function via a Maclaurin series for small inputs.   */
TMPL_STATIC_INLINE
double tmpl_Double_LambertW_Maclaurin(double x)
{
    /*  Use Horner's method to evaluate the polynomial at x.                  */
    return TMPL_POLY_EVAL(x);
}
/*  End of tmpl_Double_LambertW_Maclaurin.                                    */

/*  Undefine everything in case someone wants to #include this file.          */
#undef A1
#undef A2
#undef A3
#undef A4
#undef A5
#undef A6
#undef A7
#undef A8
#undef A9
#undef TMPL_POLY_EVAL

#endif
/*  End of include guard.                                                     */
