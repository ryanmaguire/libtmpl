/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_LAMBERTW_MACLAURIN_FLOAT_H
#define TMPL_LAMBERTW_MACLAURIN_FLOAT_H

/*  TMPL_STATIC_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the Maclaurin series.                                    */
#define A1 (+1.000000000000000000E+00F)
#define A2 (-1.000000000000000000E+00F)
#define A3 (+1.500000000000000000E+00F)
#define A4 (-2.666666666666666519E+00F)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) x*(A1 + x*(A2 + x*(A3 + x*A4)))

/*  Computes the LambertW function via a Maclaurin series for small inputs.   */
TMPL_STATIC_INLINE
float tmpl_Float_LambertW_Maclaurin(float x)
{
    /*  Use Horner's method to evaluate the polynomial at x.                  */
    return TMPL_POLY_EVAL(x);
}
/*  End of tmpl_Float_LambertW_Maclaurin.                                     */

/*  Undefine everything in case someone wants to #include this file.          */
#undef A1
#undef A2
#undef A3
#undef A4
#undef TMPL_POLY_EVAL

#endif
/*  End of include guard.                                                     */
