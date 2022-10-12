/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_MATH_ARCTAN_ASYMPTOTIC_INLINE_H
#define TMPL_MATH_ARCTAN_ASYMPTOTIC_INLINE_H

/*  TMPL_USE_INLINE macro found here.                                         */
#include <libtmpl/include/tmpl_config.h>

/*  This code is only used if inline code is requested. Check TMPL_USE_INLINE.*/
#if TMPL_USE_INLINE == 1

/*  IEEE-754 data types and macros found here.                                */
#include <libtmpl/include/tmpl_math.h>

/*  Coefficients for the computation of the polynomial approximation. The     *
 *  coefficients for the Taylor series are 1 / (1 + 2n).                      */
#define A0 (1.0F)
#define A1 (-3.33333333333329318027E-01F)
#define A2 (1.99999999998764832476E-01F)
#define A3 (-1.42857142725034663711E-01F)

/*  This function computes arctan(x) via the asymptotic expansion.            */
static inline float tmpl_Float_Arctan_Asymptotic(float x)
{
    /*  Declare necessary variables.                                          */
    const float z = 1.0F / x;
    const float z2 = z*z;

    /*  Use Horner's method to compute the polynomial.                        */
    return tmpl_Pi_By_Two_F - z*(A0 + z2*(A1 + z2*(A2 + z2*A3)));
}
/*  End of tmpl_Float_Arctan_Asymptotic.                                      */

#undef A0
#undef A1
#undef A2
#undef A3

#define A0 (1.00000000000000000000000000000E+00)
#define A1 (-3.33333333333333333333333333333E-01)
#define A2 (2.00000000000000000000000000000E-01)
#define A3 (-1.42857142857142857142857142857E-01)
#define A4 (1.11111111111111111111111111111E-01)
#define A5 (-9.09090909090909090909090909090E-02)

/*  Double precision asymptotic expansion for the inverse tangent function.   */
static inline double tmpl_Double_Arctan_Asymptotic(double x)
{
    /*  Declare necessary variables.                                          */
    const double z = 1.0 / x;
    const double z2 = z*z;

    /*  Use Horner's method to compute the polynomial.                        */
    return tmpl_Pi_By_Two -
           z*(A0 + z2*(A1 + z2*(A2 + z2*(A3 + z2*(A4 + z2*A5)))));
}
/*  End of tmpl_Double_Arctan_Asymptotic.                                     */

#undef A0
#undef A1
#undef A2
#undef A3
#undef A4
#undef A5

#if TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_BIG_ENDIAN

#define A0  1.00000000000000000000L
#define A1 -3.33333333333329318027E-01L
#define A2  1.99999999998764832476E-01L
#define A3 -1.42857142725034663711E-01L
#define A4  1.11111104054623557880E-01L
#define A5 -9.09088713343650656196E-02L

/*  Double precision asymptotic expansion for the inverse tangent function.   */
static inline long double tmpl_LDouble_Arctan_Asymptotic(long double x)
{
    /*  Declare necessary variables.                                          */
    const long double z = 1.0L / x;
    const long double z2 = z*z;

    /*  Use Horner's method to compute the polynomial.                        */
    return tmpl_Pi_By_Two_L -
           z*(A0 + z2*(A1 + z2*(A2 + z2*(A3 + z2*(A4 + z2*A5)))));
}
/*  End of tmpl_Double_Arctan_Asymptotic.                                     */

#undef A0
#undef A1
#undef A2
#undef A3
#undef A4
#undef A5

#else

#define A0 (1.000000000000000000000000000000000000E00L)
#define A1 (-3.333333333333333333333333333333333333E-01L)
#define A2 (2.000000000000000000000000000000000000E-01L)
#define A3 (-1.42857142857142857142857142857142857E-01L)
#define A4 (1.111111111111111111111111111111111111E-01L)
#define A5 (-9.09090909090909090909090909090909091E-02L)
#define A6 (7.69230769230769230769230769230769231E-02L)

/*  Asymptotic expansion for atan(x). This works well for large values.       */
static inline long double tmpl_LDouble_Arctan_Asymptotic(long double x)
{
    const long double z = 1.0L / x;
    const long double z2 = z*z;
    return tmpl_Pi_By_Two_L -
           z*(A0 + z2*(A1 + z2*(A2 + z2*(A3 + z2*(A4 + z2*(A5 + z2*A6))))));
}
/*  End of tmpl_LDouble_Arctan_Asymptotic.                                    */

#undef A0
#undef A1
#undef A2
#undef A3
#undef A4
#undef A5
#undef A6

#endif

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

#endif
/*  End of include guard.                                                     */