/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_MATH_ARCTAN_MACLAURIN_INLINE_H
#define TMPL_MATH_ARCTAN_MACLAURIN_INLINE_H

/*  TMPL_USE_INLINE macro found here.                                         */
#include <libtmpl/include/tmpl_config.h>

/*  This code is only used if inline code is requested. Check TMPL_USE_INLINE.*/
#if TMPL_USE_INLINE == 1

/*  IEEE-754 data types and macros found here.                                */
#include <libtmpl/include/tmpl_math.h>

#define A0 (1.00000000000000000000F)
#define A1 (-3.33333333333329318027E-01F)
#define A2 (1.99999999998764832476E-01F)
#define A3 (-1.42857142725034663711E-01F)
#define A4 (1.11111104054623557880E-01F)

/*  This function computes arctan(x) via a MacLaurin series for small |x|.    */
static inline float tmpl_Float_Arctan_Maclaurin(float x)
{
    /*  Declare necessary variables.                                          */
    const float x2 = x*x;
    return x*(A0 + x2*(A1 + x2*(A2 + x2*(A3 + x2*A4))));
}
/*  End of tmpl_Float_Arctan_Maclaurin.                                       */

#undef A0
#undef A1
#undef A2
#undef A3
#undef A4

#define A0 (1.00000000000000000000)
#define A1 (-3.33333333333329318027E-01)
#define A2 (1.99999999998764832476E-01)
#define A3 (-1.42857142725034663711E-01)
#define A4 (1.11111104054623557880E-01)
#define A5 (-9.09088713343650656196E-02)
#define A6 (7.69187620504482999495E-02)
#define A7 (-6.66107313738753120669E-02)
#define A8 (5.83357013379057348645E-02)

/*  Maclaurin series for arctan, double precision, to 9 terms.                */
static inline double tmpl_Double_Arctan_Maclaurin(double x)
{
    /*  Declare necessary variables.                                          */
    const double x_sq = x*x;

    /*  Use Horner's method to compute the polynomial. The signs of the       *
     *  coefficients oscillate.                                               */
    return x * (
        A0 + x_sq * (
            A1 + x_sq * (
                A2 + x_sq * (
                    A3 + x_sq * (
                        A4 + x_sq * (
                            A5 + x_sq * (
                                A6 + x_sq * (
                                    A7 + x_sq * A8
                                )
                            )
                        )
                    )
                )
            )
        )
    );
}
/*  End of tmpl_Double_Arctan_Maclaurin.                                      */

#undef A0
#undef A1
#undef A2
#undef A3
#undef A4
#undef A5
#undef A6
#undef A7
#undef A8

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

#endif
/*  End of include guard.                                                     */
