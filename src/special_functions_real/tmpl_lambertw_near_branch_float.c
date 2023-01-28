#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_special_functions_real.h>

/*  TODO:
 *      Inline this function.
 *      Add comments and doc-string.
 *      Add references and papers.
 *      Explain the mu and alpha functions that give the coefficients for this
 *      polynomial. Explain the branch cut.
 */


/*  Coefficients for the polynomial.                                          */
#define A00 (-1.0000000000000000000000000000000000000000000000000E+00F)
#define A01 (+2.3316439815971242033635360621684008763802362991876E+00F)
#define A02 (-1.8121878856393634902401916475684416651714980624666E+00F)
#define A03 (+1.9366311144923597553632774576683830638268857483151E+00F)
#define A04 (-2.3535512018816145168215435615164839701241005150647E+00F)
#define A05 (+3.0668589010506319128931489227040074984883898993015E+00F)
#define A06 (-4.1753356002581771388549841774603735734126538575619E+00F)
#define A07 (+5.8580237298747741488150538461186213041592413801079E+00F)
#define A08 (-8.4010322175239773709841616885138862868648416074309E+00F)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) \
A00 + z*(\
    A01 + z*(\
        A02 + z*(\
            A03 + z*(\
                A04 + z*(\
                    A05 + z*(\
                        A06 + z*(\
                            A07 + z*A08\
                        )\
                    )\
                )\
            )\
        )\
    )\
)

float tmpl_Float_LambertW_Near_Branch(float x)
{
    const float q = tmpl_Float_Sqrt(x);
    return TMPL_POLY_EVAL(q);
}

#undef A00
#undef A01
#undef A02
#undef A03
#undef A04
#undef A05
#undef A06
#undef A07
#undef A08
#undef TMPL_POLY_EVAL
