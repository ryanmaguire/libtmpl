/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_LAMBERTW_NEAR_BRANCH_DOUBLE_H
#define TMPL_LAMBERTW_NEAR_BRANCH_DOUBLE_H

/*  TMPL_STATIC_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  TODO:
 *      Add references and papers.
 *      Explain the mu and alpha functions that give the coefficients for this
 *      polynomial. Explain the branch cut.
 */

/*  Coefficients for the polynomial.                                          */
#define A00 (-1.0000000000000000000000000000000000000000000000000E+00)
#define A01 (+2.3316439815971242033635360621684008763802362991876E+00)
#define A02 (-1.8121878856393634902401916475684416651714980624666E+00)
#define A03 (+1.9366311144923597553632774576683830638268857483151E+00)
#define A04 (-2.3535512018816145168215435615164839701241005150647E+00)
#define A05 (+3.0668589010506319128931489227040074984883898993015E+00)
#define A06 (-4.1753356002581771388549841774603735734126538575619E+00)
#define A07 (+5.8580237298747741488150538461186213041592413801079E+00)
#define A08 (-8.4010322175239773709841616885138862868648416074309E+00)
#define A09 (+1.2250753501314460423767939360054731987609556025030E+01)
#define A10 (-1.8100697012472442755377164038863042726359728131858E+01)
#define A11 (+2.7029044799010561650311482280446256052054836349789E+01)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) \
A00 + z*(\
    A01 + z*(\
        A02 + z*(\
            A03 + z*(\
                A04 + z*(\
                    A05 + z*(\
                        A06 + z*(\
                            A07 + z*(\
                                A08 + z*(\
                                    A09 + z*(\
                                        A10 + z*A11\
                                    )\
                                )\
                            )\
                        )\
                    )\
                )\
            )\
        )\
    )\
)

/*  The expansion is in terms of the square root of the input.                */
extern double tmpl_Double_Sqrt(double x);

/*  Given x = y - 1/e, with y near the branch point, computes LambertW(y).    */
TMPL_STATIC_INLINE
double tmpl_Double_LambertW_Near_Branch(double x)
{
    const double q = tmpl_Double_Sqrt(x);
    return TMPL_POLY_EVAL(q);
}
/*  End of tmpl_Double_LambertW_Near_Branch.                                  */

/*  Undefine everything in case someone wants to #include this file.          */
#undef A00
#undef A01
#undef A02
#undef A03
#undef A04
#undef A05
#undef A06
#undef A07
#undef A08
#undef A09
#undef A10
#undef A11
#undef TMPL_POLY_EVAL

#endif
/*  End of include guard.                                                     */
