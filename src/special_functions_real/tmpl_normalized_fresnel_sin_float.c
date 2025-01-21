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
 *                     tmpl_normalized_fresnel_sin_float                      *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the normalized Fresnel sine at single precision.             *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Normalized_Fresnel_Sin                                     *
 *  Purpose:                                                                  *
 *      Computes the normalized Fresnel sine of the input.                    *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number, the argument for C(x).                             *
 *  Output:                                                                   *
 *      C_x (float):                                                          *
 *          The normalized Fresnel sine function C(x).                        *
 *  Called Functions:                                                         *
 *      tmpl_special_functions_real.h:                                        *
 *          tmpl_Float_Normalized_Fresnel_Sin_Maclaurin:                      *
 *              Computes C(x) using a Maclaurin series.                       *
 *          tmpl_Float_Normalized_Fresnel_Sin_Pade:                           *
 *              Computes C(x) using a Pade approximant.                       *
 *          tmpl_Float_Normalized_Fresnel_Sin_Remez:                          *
 *              Computes C(x) using a Remez polynomial via a lookup table.    *
 *          tmpl_Float_Normalized_Fresnel_Sin_Auxiliary_Small:                *
 *              Computes C(x) using auxiliary functions for 2 <= x < 4.       *
 *          tmpl_Float_Normalized_Fresnel_Sin_Auxiliary:                      *
 *              Computes C(x) using auxiliary functions for 4 <= x < 2^7 .    *
 *          tmpl_Float_Normalized_Fresnel_Sin_Asymptotic:                     *
 *              Computes C(x) for x >= 2^7.                                   *
 *      tmpl_math.h:                                                          *
 *          tmpl_Float_Abs:                                                   *
 *              Computes |x|. Only used if IEEE-754 support is not available. *
 *          tmpl_Float_Is_NaN_Or_Inf:                                         *
 *              Determines if a real number is NaN or infinity.               *
 *          tmpl_Float_Is_NaN:                                                *
 *              Determines if the input is Not-a-Number.                      *
 *  Method:                                                                   *
 *      The IEEE-754 method and the portable method use the same tricks.      *
 *      The normalized Fresnel sine functions is defined by the integral:     *
 *                                                                            *
 *                    x                                                       *
 *                    -                                                       *
 *                   | |      -     2 -                                       *
 *                   |       |  pi t   |                                      *
 *          S(x) =   |   sin |  -----  | dt                                   *
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
 *      Remez polynomials are used on the intervals [2, 4] and [4, 2^7] for   *
 *      f and g in terms of t = 1/x. Care is taken to compute cos(pi/2 x^2)   *
 *      and sin(pi/2 x^2) without the precision loss that occurs from         *
 *      squaring "x" by converting to double.                                 *
 *                                                                            *
 *      For 2^7 <= x < 2^23 we use the asymptotic expansion. This is:         *
 *                                                                            *
 *                 1    1                                                     *
 *          C(x) ~ - + ---- sin(pi/2 x^2)                                     *
 *                 2   pi x                                                   *
 *                                                                            *
 *      Again, care is taken to compute sin(pi/2 x^2) without precision loss  *
 *      by computing x^2 using a double.                                      *
 *                                                                            *
 *      For very large x, |x| > 2^23, use the limit and return 1/2.           *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing the TMPL_HAS_IEEE754_FLOAT macro.          *
 *  2.) tmpl_ieee754_float.h:                                                 *
 *          Header file providing a union type for IEEE-754 float.            *
 *  3.) tmpl_special_functions_real.h:                                        *
 *          Header file containing the functions prototype.                   *
 *  4.) tmpl_math.h:                                                          *
 *          Header file containing tmpl_Float_Abs. Only included if IEEE-754  *
 *          support is not available.                                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       July 11, 2024                                                 *
 ******************************************************************************/

/*  TMPL_HAS_IEEE754_FLOAT macro found here.                                  */
#include <libtmpl/include/types/tmpl_ieee754_float.h>

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_special_functions_real.h>

/******************************************************************************
 *                         Static / Inlined Functions                         *
 ******************************************************************************/

/*  Computes C(x) using auxiliary functions "f" and "g" for large x.          */
#include "auxiliary/tmpl_normalized_fresnel_sin_auxiliary_float.h"

/*  Computes C(x) using auxiliary functions "f" and "g" for 2 <= x < 4.       */
#include "auxiliary/tmpl_normalized_fresnel_sin_auxiliary_small_float.h"

/*  Computes C(x) using an asymptotic expansion for x > 2^7.                  */
#include "auxiliary/tmpl_normalized_fresnel_sin_asymptotic_float.h"

/*  Computes C(x) using a Maclaurin series for |x| < 1 / 4.                   */
#include "auxiliary/tmpl_normalized_fresnel_sin_maclaurin_float.h"

/*  Computes C(x) using a Pade approximant for |x| < 1.                       */
#include "auxiliary/tmpl_normalized_fresnel_sin_pade_float.h"

/*  Computes C(x) using a lookup table of Remez coefficients for 1 <= x < 2.  */
#include "auxiliary/tmpl_normalized_fresnel_sin_remez_float.h"

/*  Speed boost if IEEE-754 support is available.                             */
#if TMPL_HAS_IEEE754_FLOAT == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/


/*  Computes the normalized Fresnel sine of a real number.                    */
float tmpl_Float_Normalized_Fresnel_Sin(float x)
{
    /*  Variable for the output.                                              */
    float out;

    /*  Union of a float and the bits representing it. Used for type-punning.*/
    tmpl_IEEE754_Float w;

    /*  Set the float part of the word to the input.                          */
    w.r = x;

    /*  Special case, NaN or Infinity.                                        */
    if (TMPL_FLOAT_IS_NAN_OR_INF(w))
    {
        /*  For not-a-number, return the input. Output is also not-a-number.  */
        if (TMPL_FLOAT_IS_NAN(w))
            return x;

        /*  The normalized Fresnel integrals are asymptotic to +/- 1/2.       */
        if (TMPL_FLOAT_IS_NEGATIVE(w))
            return -0.5F;

        return 0.5F;
    }

    /*  For small inputs we can use the Taylor series and Pade approximants.  */
    if (w.bits.expo < TMPL_FLOAT_UBIAS)
    {
        /*  Avoid underflow. The error is O(x^7). Use the first term of the   *
         *  Maclaurin series for |x| < 2^-7.                                 */
        if (w.bits.expo < TMPL_FLOAT_UBIAS - 0x07U)
        {
            /*  For very small x, x^3 will underflow and return 0. Avoid this *
             *  and just return zero. The threshold is 2^-50.                 */
            if (w.bits.expo < TMPL_FLOAT_UBIAS - 0x32U)
                return 0.0F;

            /*  Otherwise, use the first term in the Maclaurin series.        */
            return 5.235987755982988730771072305465838140328615E-01F*x*x*x;
        }

        /*  For values bounded by 1/4, use a Maclaurin polynomial.            */
        if (w.bits.expo < TMPL_FLOAT_UBIAS - 0x02U)
            return tmpl_Float_Normalized_Fresnel_Sin_Maclaurin(x);

        /*  For |x| < 1 we can use a Pade approximate. The numerator and      *
         *  denominator are in terms of x^4, so we can get very high orders   *
         *  of the approximant for free. The (12, 8) Pade approximant         *
         *  requires 3 terms for the numerator and 2 for the denominator.     */
        return tmpl_Float_Normalized_Fresnel_Sin_Pade(x);
    }

    /*  For larger numbers use the fact the the Fresnel functions are odd.    */
    w.bits.sign = 0x00U;

    /*  For |x| < 2^7 we can use the auxiliary functions.                     */
    if (w.bits.expo < TMPL_FLOAT_UBIAS + 0x07U)
    {
        /*  For 1 <= |x| < 2 it is worth speeding up the computation and      *
         *  avoiding calls to the trig functions. We do this using a table of *
         *  coefficients for Remez polynomials spaced 1/32 apart.             */
        if (w.bits.expo == TMPL_FLOAT_UBIAS)
            out = tmpl_Float_Normalized_Fresnel_Sin_Remez(w);

        /*  For 2 <= |x| < 4, less care is needed to accurately use the       *
         *  auxiliary functions. This gives us a bit of a speed boost.        */
        else if (w.bits.expo == TMPL_FLOAT_UBIAS + 0x01)
            out = tmpl_Float_Normalized_Fresnel_Sin_Auxiliary_Small(w.r);

        /*  For |x| > 4 we need to use the auxiliary functions more carefully.*
         *  Double arithmetic is carried out to maintain accuracy.            */
        else
            out = tmpl_Float_Normalized_Fresnel_Sin_Auxiliary(w.r);
    }

    /*  For very large inputs, 2^7 <= |x| < 2^23, a single term of the        *
     *  asymptotic series is all that is needed. Use this.                    */
    else if (w.bits.expo < TMPL_FLOAT_UBIAS + 0x17U)
        out = tmpl_Float_Normalized_Fresnel_Sin_Asymptotic(w.r);

    /*  The error of the asymptotic expansion is O(1 / x). For very large     *
     *  inputs, |x| > 2^23, we can use the limit, which is 1/2.               */
    else
        out = 0.5F;

    /*  C(x) is odd. For negative inputs, return -C(-x).                      */
    if (x < 0.0F)
        return -out;

    return out;
}
/*  End of tmpl_Float_Normalized_Fresnel_Sin.                                 */

#else
/*  Else for #if TMPL_HAS_IEEE754_DOUBLE == 1.                                */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  tmpl_Float_Abs is found here.                                             */
#include <libtmpl/include/tmpl_math.h>

/*  Computes the normalized Fresnel sine of a real number.                    */
float tmpl_Float_Normalized_Fresnel_Sin(float x)
{
    /*  Variable for the output.                                              */
    float out;

    /*  C(x) is odd. Compute |x| and work with that.                          */
    const float abs_x = tmpl_Float_Abs(x);

    /*  Special case, NaN or Infinity.                                        */
    if (tmpl_Float_Is_NaN_Or_Inf(x))
    {
        /*  For not-a-number, return the input. Output is also not-a-number.  */
        if (tmpl_Float_Is_NaN(x))
            return x;

        /*  The normalized Fresnel integrals are asymptotic to +/- 1/2.       */
        if (x < 0.0F)
            return -0.5F;

        return 0.5F;
    }

    /*  For small inputs we can use the Taylor series and Pade approximants.  */
    if (abs_x < 1.0F)
    {
        /*  Avoid underflow. The error is O(x^4). Return x for |x| < 2^-17.   */
        if (abs_x < 7.62939453125E-06F)
            return x;

        /*  For values bounded by 1/4, use a Maclaurin polynomial.            */
        if (abs_x < 0.25F)
            return tmpl_Float_Normalized_Fresnel_Sin_Maclaurin(x);

        /*  For |x| < 1 we can use a Pade approximate. The numerator and      *
         *  denominator are in terms of x^4, so we can get very high orders   *
         *  of the approximant for free. The (20, 16) Pade approximant        *
         *  requires 5 terms for the numerator and 4 for the denominator.     */
        return tmpl_Float_Normalized_Fresnel_Sin_Pade(x);
    }

    /*  For |x| < 2^7 we can use the auxiliary functions.                     */
    if (abs_x < 128.0F)
    {
        /*  For 1 <= |x| < 2 it is worth speeding up the computation and      *
         *  avoiding calls to the trig functions. We do this using a table of *
         *  coefficients for Remez polynomials spaced 1/32 apart.             */
        if (abs_x < 2.0F)
            out = tmpl_Float_Normalized_Fresnel_Sin_Remez(abs_x);

        /*  For 2 <= |x| < 4, less care is needed to accurately use the       *
         *  auxiliary functions. This gives us a bit of a speed boost.        */
        else if (abs_x < 4.0F)
            out = tmpl_Float_Normalized_Fresnel_Sin_Auxiliary_Small(abs_x);

        /*  For |x| > 4 we need to use the auxiliary functions more carefully.*
         *  Double arithmetic is carried out to maintain accuracy.            */
        else
            out = tmpl_Float_Normalized_Fresnel_Sin_Auxiliary(abs_x);
    }

    /*  For very large inputs, 2^7 <= |x| < 2^23, a single term of the        *
     *  asymptotic series is all that is needed. Use this.                    */
    else if (abs_x < 8.388608E+06F)
        out = tmpl_Float_Normalized_Fresnel_Sin_Asymptotic(abs_x);

    /*  The error of the asymptotic expansion is O(1 / x). For very large     *
     *  inputs, |x| > 2^52, we can use the limit, which is 1/2.               */
    else
        out = 0.5F;

    /*  C(x) is odd. For negative inputs, return -C(-x).                      */
    if (x < 0.0F)
        return -out;

    return out;
}
/*  End of tmpl_Float_Normalized_Fresnel_Sin.                                 */

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE == 1.                                  */
