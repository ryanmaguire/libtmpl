#include <libtmpl/include/tmpl_config.h>

#if TMPL_USE_INLINE != 1

#include <libtmpl/include/tmpl_math.h>

/*  Coefficients for the computation of the polynomial approximation. The     *
 *  coefficients for the Taylor series are 1 / (1 + 2n).                      */
#define A0 (1.0F)
#define A1 (-3.33333333333329318027E-01F)
#define A2 (1.99999999998764832476E-01F)
#define A3 (-1.42857142725034663711E-01F)

float tmpl_Float_Arctan_Very_Small(float x)
{
    const float x2 = x*x;
    return x*(A0 + x2*(A1 + x2*(A2 + x2*A3)));
}

#undef A0
#undef A1
#undef A2
#undef A3
#endif
