/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify           *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  libtmpl is distributed in the hope that it will be useful,                *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with libtmpl.  If not, see <https://www.gnu.org/licenses/>.         *
 ******************************************************************************
 *                     tmpl_normalized_fresnel_sin_double                     *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the normalized Fresnel sine at double precision.             *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Normalized_Fresnel_Sin                                    *
 *  Purpose:                                                                  *
 *      Compute the normalized Fresnel sine of the input.                     *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number, the argument for C(x).                             *
 *  Output:                                                                   *
 *      C_x (double):                                                         *
 *          The normalized Fresnel sine function C(x).                        *
 *  Called Functions:                                                         *
 *      tmpl_special_functions_real.h:                                        *
 *          tmpl_Double_Normalized_Fresnel_Sin_Maclaurin:                     *
 *              Computes C(x) using a Maclaurin series.                       *
 *          tmpl_Double_Normalized_Fresnel_Sin_Pade:                          *
 *              Computes C(x) using a Pade approximant.                       *
 *          tmpl_Double_Normalized_Fresnel_Sin_Remez:                         *
 *              Computes C(x) using a Remez polynomial via a lookup table.    *
 *          tmpl_Double_Normalized_Fresnel_Sin_Auxiliary_Small:               *
 *              Computes C(x) using auxiliary functions for 2 <= x < 4.       *
 *          tmpl_Double_Normalized_Fresnel_Sin_Auxiliary:                     *
 *              Computes C(x) using auxiliary functions for 4 <= x < 2^17.    *
 *          tmpl_Double_Normalized_Fresnel_Sin_Asymptotic:                    *
 *              Computes C(x) for x >= 2^17.                                  *
 *      tmpl_math.h:                                                          *
 *          tmpl_Double_Abs:                                                  *
 *              Computes |x|. Only used if IEEE-754 support is not available. *
 *          tmpl_Double_Is_NaN_Or_Inf:                                        *
 *              Determines if a real number is NaN or infinity.               *
 *          tmpl_Double_Is_NaN:                                               *
 *              Determines if the input is Not-a-Number.                      *
 *  Method:                                                                   *
 *      The IEEE-754 method and the portable method use the same tricks.      *
 *      The normalized Fresnel sine functions is defined by the integral:     *
 *                                                                            *
 *                    x                                                       *
 *                    -                                                       *
 *                   | |      -     2 -                                       *
 *                   |       |  pi t   |                                      *
 *          C(x) =   |   sin |  -----  | dt                                   *
 *                 | |       |    2    |                                      *
 *                  -         -       -                                       *
 *                  0                                                         *
 *                                                                            *
 *      By integrating the Maclaurin series for sin(pi/2 x^2) term by term,   *
 *      we obtain:                                                            *
 *                                                                            *
 *                 infty                                                      *
 *                 -----       n  4n+1  -   -  2n                             *
 *                 \       (-1)  x     | pi  |                                *
 *          C(x) = /       ----------- | --- |                                *
 *                 -----   (4n+1)(2n)!  - 2 -                                 *
 *                 n = 0                                                      *
 *                                                                            *
 *      For small x, |x| < 1/4, use the first few terms of this. For slightly *
 *      larger x, |x| < 1, use a Pade approximant based off of this series.   *
 *                                                                            *
 *      For larger x, reduce x to being positive via C(x) = -C(-x).           *
 *      For 1 <= |x| < 2, a lookup table is used with pre-computed            *
 *      coefficients for Remez polynomials on the intervals                   *
 *      [1 + n / 32, 1 + (n+1) / 32].                                         *
 *                                                                            *
 *      The Fresnel functions exhibit highly oscillatory behavior, and can    *
 *      be computed using auxiliary functions "f" and "g" defined via:        *
 *                                                                            *
 *          C(x) = 0.5 + f(x) cos(pi/2 x^2) - g(x) sin(pi/2 x^2)              *
 *          S(x) = 0.5 - f(x) sin(pi/2 x^2) - g(x) cos(pi/2 x^2)              *
 *                                                                            *
 *      Solving for f and g gives us the following:                           *
 *                                                                            *
 *          f(x) = sin(pi/2 x^2) (C(x) - 0.5) - cos(pi/2 x^2) (S(x) - 0.5)    *
 *          g(x) = -sin(pi/2 x^2) (S(x) - 0.5) - cos(pi/2 x^2) (C(x) - 0.5)   *
 *                                                                            *
 *      Remez polynomials are used on the intervals [2, 4] and [4, 2^17] for  *
 *      f and g in terms of t = 1/x. Care is taken to compute cos(pi/2 x^2)   *
 *      and sin(pi/2 x^2) without the precision loss that occurs from         *
 *      squaring "x" by using a double-double trick.                          *
 *                                                                            *
 *      For 2^17 <= x < 2^52 we use the asymptotic expansion. This is:        *
 *                                                                            *
 *                 1    1                                                     *
 *          C(x) ~ - + ---- sin(pi/2 x^2)                                     *
 *                 2   pi x                                                   *
 *                                                                            *
 *      Again, care is taken to compute sin(pi/2 x^2) without precision loss  *
 *      by computing x^2 using a double-double trick.                         *
 *                                                                            *
 *      For very large x, |x| > 2^52, use the limit and return 1/2.           *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_ieee754_double.h:                                                *
 *          Header file providing a union type for IEEE-754 double.           *
 *  2.) tmpl_special_functions_real.h:                                        *
 *          Header file containing the functions prototype.                   *
 *  3.) tmpl_math.h:                                                          *
 *          Header file containing tmpl_Double_Abs. Only included if IEEE-754 *
 *          support is not available.                                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       July 11, 2024                                                 *
 ******************************************************************************/

/*  TMPL_HAS_IEEE754_DOUBLE macro found here.                                 */
#include <libtmpl/include/types/tmpl_ieee754_ldouble.h>

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_special_functions_real.h>

/*  Absolute value function needed.                                           */
#if TMPL_USE_INLINE == 1
#include <libtmpl/include/inline/math/tmpl_abs_ldouble.h>
#else
extern long double tmpl_LDouble_Abs(long double x);
#endif

/******************************************************************************
 *                         Static / Inlined Functions                         *
 ******************************************************************************/

/*  Computes C(x) using auxiliary functions "f" and "g" for large x.          */
#include "auxiliary/tmpl_normalized_fresnel_sin_auxiliary_ldouble.h"

/*  Computes C(x) using auxiliary functions "f" and "g" for 2 <= x < 4.       */
#include "auxiliary/tmpl_normalized_fresnel_sin_auxiliary_small_ldouble.h"

/*  Computes C(x) using an asymptotic expansion for x > 2^17.                 */
#include "auxiliary/tmpl_normalized_fresnel_sin_asymptotic_ldouble.h"

/*  Computes C(x) using a Maclaurin series for |x| < 1 / 4.                   */
#include "auxiliary/tmpl_normalized_fresnel_sin_maclaurin_ldouble.h"

/*  Computes C(x) using a Pade approximant for |x| < 1.                       */
#include "auxiliary/tmpl_normalized_fresnel_sin_pade_ldouble.h"

/*  Computes C(x) using a lookup table of Remez coefficients for 1 <= x < 2.  */
#include "auxiliary/tmpl_normalized_fresnel_sin_remez_ldouble.h"

/*  Speed boost if IEEE-754 support is available.                             */
#if TMPL_HAS_IEEE754_LDOUBLE == 1

#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT
#define TMPL_LDOUBLE_UNDERFLOW_EXPO (TMPL_LDOUBLE_UBIAS - 0x11U)
#define TMPL_LDOUBLE_ASYMPTOTIC_EXPO (TMPL_LDOUBLE_UBIAS + 0x11U)
#define TMPL_LDOUBLE_LIMIT_EXPO (TMPL_LDOUBLE_UBIAS + 0x34U)
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_80_BIT
#define TMPL_LDOUBLE_UNDERFLOW_EXPO (TMPL_LDOUBLE_UBIAS - 0x15U)
#define TMPL_LDOUBLE_ASYMPTOTIC_EXPO (TMPL_LDOUBLE_UBIAS + 0x15U)
#define TMPL_LDOUBLE_LIMIT_EXPO (TMPL_LDOUBLE_UBIAS + 0x3FU)
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE
#define TMPL_LDOUBLE_UNDERFLOW_EXPO (TMPL_LDOUBLE_UBIAS - 0x22U)
#define TMPL_LDOUBLE_ASYMPTOTIC_EXPO (TMPL_LDOUBLE_UBIAS + 0x22U)
#define TMPL_LDOUBLE_LIMIT_EXPO (TMPL_LDOUBLE_UBIAS + 0x68U)
#else
#define TMPL_LDOUBLE_UNDERFLOW_EXPO (TMPL_LDOUBLE_UBIAS - 0x25U)
#define TMPL_LDOUBLE_ASYMPTOTIC_EXPO (TMPL_LDOUBLE_UBIAS + 0x25U)
#define TMPL_LDOUBLE_LIMIT_EXPO (TMPL_LDOUBLE_UBIAS + 0x70U)
#endif

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  Computes the normalized Fresnel sine of a real number.                    */
long double tmpl_LDouble_Normalized_Fresnel_Sin(long double x)
{
    /*  Variable for the output.                                              */
    long double out;

    /*  Union of a double and the bits representing it. Used for type-punning.*/
    tmpl_IEEE754_LDouble w;

    /*  Set the double part of the word to the input.                         */
    w.r = x;

    /*  Special case, NaN or Infinity.                                        */
    if (TMPL_LDOUBLE_IS_NAN_OR_INF(w))
    {
        /*  For not-a-number, return the input. Output is also not-a-number.  */
        if (TMPL_LDOUBLE_IS_NAN(w))
            return x;

        /*  The normalized Fresnel integrals are asymptotic to +/- 1/2.       */
        if (TMPL_LDOUBLE_IS_NEGATIVE(w))
            return -0.5L;

        return 0.5L;
    }

    /*  For small inputs we can use the Taylor series and Pade approximants.  */
    if (TMPL_LDOUBLE_EXPO_BITS(w) < TMPL_LDOUBLE_UBIAS)
    {
        /*  Avoid underflow. The error is O(x^4). Return x for small x.       */
        if (TMPL_LDOUBLE_EXPO_BITS(w) < TMPL_LDOUBLE_UNDERFLOW_EXPO)
            return x;

        /*  For values bounded by 1/4, use a Maclaurin polynomial.            */
        if (TMPL_LDOUBLE_EXPO_BITS(w) < TMPL_LDOUBLE_UBIAS - 0x02U)
            return tmpl_LDouble_Normalized_Fresnel_Sin_Maclaurin(x);

        /*  For |x| < 1 we can use a Pade approximate.                        */
        return tmpl_LDouble_Normalized_Fresnel_Sin_Pade(x);
    }

    /*  For larger numbers use the fact the the Fresnel functions are odd.    */
    w.r = tmpl_LDouble_Abs(w.r);

    /*  For |x| not too large we can use the auxiliary functions.             */
    if (TMPL_LDOUBLE_EXPO_BITS(w) < TMPL_LDOUBLE_ASYMPTOTIC_EXPO)
    {
        /*  For 1 <= |x| < 2 it is worth speeding up the computation and      *
         *  avoiding calls to the trig functions. We do this using a table of *
         *  coefficients for Remez polynomials spaced 1/32 apart.             */
        if (TMPL_LDOUBLE_EXPO_BITS(w) == TMPL_LDOUBLE_UBIAS)
            out = tmpl_LDouble_Normalized_Fresnel_Sin_Remez(w);

        /*  For 2 <= |x| < 4, less care is needed to accurately use the       *
         *  auxiliary functions. This gives us a bit of a speed boost.        */
        else if (TMPL_LDOUBLE_EXPO_BITS(w) == TMPL_LDOUBLE_UBIAS + 0x01)
            out = tmpl_LDouble_Normalized_Fresnel_Sin_Auxiliary_Small(w.r);

        /*  For |x| > 4 we need to use the auxiliary functions more carefully.*
         *  A "double-double" trick is carried out to maintain accuracy.      */
        else
            out = tmpl_LDouble_Normalized_Fresnel_Sin_Auxiliary(w.r);
    }

    /*  For very large inputs use a single term of the asymptotic series.     */
    else if (TMPL_LDOUBLE_EXPO_BITS(w) < TMPL_LDOUBLE_LIMIT_EXPO)
        out = tmpl_LDouble_Normalized_Fresnel_Sin_Asymptotic(w.r);

    /*  For very very large inputs use the limit, 1/2.                        */
    else
        out = 0.5L;

    /*  C(x) is odd. For negative inputs, return -C(-x).                      */
    if (x < 0.0L)
        return -out;

    return out;
}
/*  End of tmpl_Double_Normalized_Fresnel_Sin.                                */

#else
/*  Else for #if TMPL_HAS_IEEE754_DOUBLE == 1.                                */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  tmpl_Double_Abs is found here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  Computes the normalized Fresnel sine of a real number.                    */
long double tmpl_LDouble_Normalized_Fresnel_Sin(long double x)
{
    /*  Variable for the output.                                              */
    long double out;

    /*  C(x) is odd. Compute |x| and work with that.                          */
    const long double abs_x = tmpl_LDouble_Abs(x);

    /*  Special case, NaN or Infinity.                                        */
    if (tmpl_LDouble_Is_NaN_Or_Inf(x))
    {
        /*  For not-a-number, return the input. Output is also not-a-number.  */
        if (tmpl_LDouble_Is_NaN(x))
            return x;

        /*  The normalized Fresnel integrals are asymptotic to +/- 1/2.       */
        if (x < 0.0L)
            return -0.5L;

        return 0.5L;
    }

    /*  For small inputs we can use the Taylor series and Pade approximants.  */
    if (abs_x < 1.0L)
    {
        /*  Avoid underflow. The error is O(x^4). Return x for |x| < 2^-21.   */
        if (abs_x < 4.76837158203125e-07L)
            return x;

        /*  For values bounded by 1/4, use a Maclaurin polynomial.            */
        if (abs_x < 0.25L)
            return tmpl_LDouble_Normalized_Fresnel_Sin_Maclaurin(x);

        /*  For |x| < 1 we can use a Pade approximate. The numerator and      *
         *  denominator are in terms of x^4, so we can get very high orders   *
         *  of the approximant for free. The (20, 16) Pade approximant        *
         *  requires 5 terms for the numerator and 4 for the denominator.     */
        return tmpl_LDouble_Normalized_Fresnel_Sin_Pade(x);
    }

    /*  For |x| < 2^21 we can use the auxiliary functions.                    */
    if (abs_x < 2097152.0L)
    {
        /*  For 1 <= |x| < 2 it is worth speeding up the computation and      *
         *  avoiding calls to the trig functions. We do this using a table of *
         *  coefficients for Remez polynomials spaced 1/32 apart.             */
        if (abs_x < 2.0L)
            out = tmpl_LDouble_Normalized_Fresnel_Sin_Remez(abs_x);

        /*  For 2 <= |x| < 4, less care is needed to accurately use the       *
         *  auxiliary functions. This gives us a bit of a speed boost.        */
        else if (abs_x < 4.0L)
            out = tmpl_LDouble_Normalized_Fresnel_Sin_Auxiliary_Small(abs_x);

        /*  For |x| > 4 we need to use the auxiliary functions more carefully.*
         *  A "double-double" trick is carried out to maintain accuracy.      */
        else
            out = tmpl_LDouble_Normalized_Fresnel_Sin_Auxiliary(abs_x);
    }

    /*  For very large inputs, 2^17 <= |x| < 2^63, a single term of the       *
     *  asymptotic series is all that is needed. Use this.                    */
    else if (abs_x < 9.223372036854775808E+18L)
        out = tmpl_LDouble_Normalized_Fresnel_Sin_Asymptotic(abs_x);

    /*  The error of the asymptotic expansion is O(1 / x). For very large     *
     *  inputs, |x| > 2^52, we can use the limit, which is 1/2.               */
    else
        out = 0.5L;

    /*  C(x) is odd. For negative inputs, return -C(-x).                      */
    if (x < 0.0L)
        return -out;

    return out;
}
/*  End of tmpl_LDouble_Normalized_Fresnel_Sin.                               */

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE == 1.                                  */
