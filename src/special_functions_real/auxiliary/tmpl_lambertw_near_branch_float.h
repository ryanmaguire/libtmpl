/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_LAMBERTW_NEAR_BRANCH_FLOAT_H
#define TMPL_LAMBERTW_NEAR_BRANCH_FLOAT_H

/*  TMPL_STATIC_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the polynomial.                                          */
#define A0 (-1.0000000000000000000000000000000000000000000000000E+00F)
#define A1 (+2.3316439815971242033635360621684008763802362991876E+00F)
#define A2 (-1.8121878856393634902401916475684416651714980624666E+00F)
#define A3 (+1.9366311144923597553632774576683830638268857483151E+00F)
#define A4 (-2.3535512018816145168215435615164839701241005150647E+00F)
#define A5 (+3.0668589010506319128931489227040074984883898993015E+00F)
#define A6 (-4.1753356002581771388549841774603735734126538575619E+00F)
#define A7 (+5.8580237298747741488150538461186213041592413801079E+00F)
#define A8 (-8.4010322175239773709841616885138862868648416074309E+00F)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) \
A0 + z*(A1 + z*(A2 + z*(A3 + z*(A4 + z*(A5 + z*(A6 + z*(A7 + z*A8)))))))

/*  The expansion is in terms of the square root of the input.                */
extern float tmpl_Float_Sqrt(float x);

/*  Given x = y - 1/e, with y near the branch point, computes LambertW(y).    */
TMPL_STATIC_INLINE
float tmpl_Float_LambertW_Near_Branch(float x)
{
    const float q = tmpl_Float_Sqrt(x);
    return TMPL_POLY_EVAL(q);
}
/*  End of tmpl_Float_LambertW_Near_Branch.                                   */

/*  Undefine everything in case someone wants to #include this file.          */
#undef A0
#undef A1
#undef A2
#undef A3
#undef A4
#undef A5
#undef A6
#undef A7
#undef A8
#undef TMPL_POLY_EVAL

#endif
/*  End of include guard.                                                     */
