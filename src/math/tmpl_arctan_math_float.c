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
 *                             tmpl_arctan_float                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the arc-tangent function at single precision.                *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Arctan                                                     *
 *  Purpose:                                                                  *
 *      Computes atan(x), the inverse tangent function.                       *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      atan_x (float):                                                       *
 *          The arc-tangent of x.                                             *
 *  IEEE-754 Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_Float_Arctan_Asymptotic (tmpl_math.h):                       *
 *              Computes the asymptotic expansion of arctan for large         *
 *              positive real numbers. Very accurate for x > 16.              *
 *          tmpl_Float_Arctan_Maclaurin (tmpl_math.h):                        *
 *              Computes the Maclaurin series of arctan. More terms are used  *
 *              in this function than tmpl_Float_Arctan_Very_Small.           *
 *          tmpl_Float_Arctan_Very_Small (tmpl_math.h):                       *
 *              Computes the inverse tangent of small numbers using a         *
 *              Maclaurin series. Accurate for values smaller than 1/16.      *
 *      Method:                                                               *
 *          Check if the input is NaN or infinity. Return NaN if it is        *
 *          NaN, and sign(x) * pi / 2 if it is +/- infinity.                  *
 *                                                                            *
 *          Next, use the fact that atan(x) is odd to reduce to the case      *
 *          x >= 0. For small values, use the MacLaurin series. For values in *
 *          certain ranges, use formula 4.4.34 from Abramowitz and Stegun to  *
 *          reduce the argument to a smaller value. This formula states that: *
 *                                                                            *
 *                                         u - v                              *
 *              atan(u) - atan(v) = atan( -------- )                          *
 *                                         1 + uv                             *
 *                                                                            *
 *          Extract the exponent of the input x. That is, given:              *
 *                                                                            *
 *              x = s * 1.m * 2^e                                             *
 *                                                                            *
 *          where s is the sign, m the mantissa, and e the exponent, extract  *
 *          the value e. Precompute 8 values of atan(v) and use the value e   *
 *          to index this list (e varies from -4 to 3, corresponding to 1/16  *
 *          to 8). For e < -4 we have |x| < 1/16, so use the MacLaurin        *
 *          series. For e > 3 we have |x| >= 16, so use the asymptotic        *
 *          expansion. Values of |x| lying between 2^e and 2^{e+1} will use   *
 *          these precomputed values in the formula above from Abramowitz and *
 *          Stegun. Because of this we can skip most of the if-then           *
 *          statements used in the portable method.                           *
 *                                                                            *
 *          The following values were obtained via guess-and-check to reduce  *
 *          the relative error to below 1 * 10^-7 ~= 2^-23 = single epsilon.  *
 *                                                                            *
 *                                     u - v                                  *
 *          atan(u) = atan(v) + atan( -------- )                              *
 *                                     1 + uv                                 *
 *                                                                            *
 *          x in [0, 1/16)    atan(x) ~= x-x^3/3+x^5/5-x^7/7                  *
 *          x in [1/16, 1/8)  u = x, v = 0.05, reduce and use polynomial.     *
 *          x in [1/8, 1/4)   u = x, v = 0.18, reduce and use polynomial.     *
 *          x in [1/4, 1/2)   u = x, v = 0.35, reduce and use polynomial.     *
 *          x in [1/2, 1)     u = x, v = 0.72, reduce and use polynomial.     *
 *          x in [1, 2)       u = x, v = 1.35, reduce and use polynomial.     *
 *          x in [2, 4)       u = x, v = 2.50, reduce and use polynomial.     *
 *          x in [4, 8)       u = x, v = 4.00, reduce and use polynomial.     *
 *          x in [8, 16)      u = x, v = 8.00, reduce and use polynomial.     *
 *          x >= 16           atan(x) ~= pi/2 + atan(-1/x).                   *
 *      Error:                                                                *
 *          Based on 788,968,857 random samples with -10^6 < x < 10^6.        *
 *              max relative error: 2.3223344540012894e-16                    *
 *              rms relative error: 7.4233764024303319e-17                    *
 *              max absolute error: 2.2204460492503131e-16                    *
 *              rms absolute error: 1.1660491924987274e-16                    *
 *          Values assume 100% accuracy of glibc. Actual error in glibc is    *
 *          less than 1 ULP (~2 x 10^-16).                                    *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_Float_Abs (tmpl_math.h):                                     *
 *              Computes the absolute value of a real number.                 *
 *          tmpl_Float_Arctan_Asymptotic (tmpl_math.h):                       *
 *              Computes the asymptotic expansion of arctan for large         *
 *              positive real numbers. Very accurate for x > 16.              *
 *          tmpl_Float_Arctan_Maclaurin (tmpl_math.h):                        *
 *              Computes the Maclaurin series of arctan. More terms are used  *
 *              in this function than tmpl_Float_Arctan_Very_Small.           *
 *          tmpl_Float_Arctan_Very_Small (tmpl_math.h):                       *
 *              Computes the inverse tangent of small numbers using a         *
 *              Maclaurin series. Accurate for values smaller than 1/16.      *
 *          tmpl_Float_Is_NaN (tmpl_math.h):                                  *
 *              Determines if a float is Not-a-Number.                        *
 *          tmpl_Float_Is_Inf (tmpl_math.h):                                  *
 *              Determines if a float is infinity.                            *
 *      Method:                                                               *
 *          Same as IEEE-754 version but use if-then statements to narrow     *
 *          the range of x and use the appropriate values in the table.       *
 *      Error:                                                                *
 *          Based on 788,968,857 random samples with -10^6 < x < 10^6.        *
 *              max relative error: 2.3223344540012894e-16                    *
 *              rms relative error: 7.4233764024303319e-17                    *
 *              max absolute error: 2.2204460492503131e-16                    *
 *              rms absolute error: 1.1660491924987274e-16                    *
 *          Values assume 100% accuracy of glibc. Actual error in glibc is    *
 *          less than 1 ULP (~2 x 10^-16).                                    *
 *  Notes:                                                                    *
 *      There are three special cases. If the input is NaN, the output will   *
 *      also be NaN. If the input is positive infinity, the limit is used and *
 *      pi/2 is returned. If the input is negative infinity, the limit is     *
 *      used and -pi/2 is returned.                                           *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_USE_MATH_ALGORITHMS macro.            *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 09, 2021                                            *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2022/09/12: Ryan Maguire                                                  *
 *      Added IEEE-754 version. This yields a 2.3x speed boost.               *
 ******************************************************************************/

/*  TMPL_USE_MATH_ALGORITHMS found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Only implement this if the user requested libtmpl algorithms.             */
#if TMPL_USE_MATH_ALGORITHMS == 1

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

/******************************************************************************
 *                         Static / Inlined Functions                         *
 ******************************************************************************/

/*  Maclaurin expansion provided here.                                        */
#include "auxiliary/tmpl_arctan_maclaurin_float.h"

/*  Smaller Maclaurin expansion that avoids underflow.                        */
#include "auxiliary/tmpl_arctan_very_small_float.h"

/*  Asymptotic expansion for arctan. Good for large positive inputs.          */
#include "auxiliary/tmpl_arctan_asymptotic_float.h"

/******************************************************************************
 *                              Constant Values                               *
 ******************************************************************************/

/*  The angles north-east, north-west, south-west, and south-east use these.  */
#define TMPL_PI_BY_TWO (+1.570796326794896619231321691639751442099E+00F)

/*  Check for IEEE-754 support.                                               */
#if TMPL_HAS_IEEE754_FLOAT == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  Single precision inverse tangent (atanf equivalent).                      */
float tmpl_Float_Arctan(float x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_Float w, tmp;
    float arg, out, v, atan_v;
    unsigned int ind;

    /*  Set the float part of the word to the input.                          */
    w.r = x;

    /*  Special cases, NaN and INF.                                           */
    if (TMPL_FLOAT_IS_NAN_OR_INF(w))
    {
        /*  Check if the input is NaN. If it is, simply return the input.     */
        if (TMPL_FLOAT_IS_NAN(w))
            return x;

        /*  For infinity the limit is pi/2. Negative infinity gives -pi/2.    */
        if (w.bits.sign)
            return -TMPL_PI_BY_TWO;

        return TMPL_PI_BY_TWO;
    }

    /*  Small values, |x| < 1/16. Use the MacLaurin series to a few terms.    */
    else if (w.bits.expo < TMPL_FLOAT_UBIAS - 4U)
    {
        /*  For very very small, avoid underflow. Return the first term of    *
         *  the Maclaurin series.                                             */
        if (w.bits.expo < TMPL_FLOAT_UBIAS - 12U)
            return x;

        return tmpl_Float_Arctan_Very_Small(x);
    }

    /*  The arctan function is odd. Compute |x| by setting sign to positive.  */
    tmp.bits.sign = w.bits.sign;
    w.bits.sign = 0x00U;

    /*  For |x| > 16, use the asymptotic expansion.                           */
    if (w.bits.expo > TMPL_FLOAT_UBIAS + 3U)
    {
        out = tmpl_Float_Arctan_Asymptotic(w.r);

        /*  Use the fact that atan is odd to complete the computation.        */
        if (tmp.bits.sign)
            return -out;

        return out;
    }

    /*  The exponent tells us the index for the tables tmpl_atan_float_v and  *
     *  tmpl_atan_float_atan_of_v that correspond to x. The index is simply   *
     *  the exponent plus four (since the lowest value is 1/16 = 2^-4, we     *
     *  need to shift up by 4). The exponent has a bias, per the IEEE-754     *
     *  format, so we must subtract this off to get the correct index.        */
    ind = (w.bits.expo + 4U) - TMPL_FLOAT_UBIAS;
    v = tmpl_atan_float_v[ind];
    atan_v = tmpl_atan_float_atan_of_v[ind];

    /*  Compute the argument via formula 4.4.34 from Abramowitz and Stegun.   */
    arg = (w.r - v) / (1.0F + w.r*v);
    out = atan_v + tmpl_Float_Arctan_Maclaurin(arg);

    /*  Use the fact that atan is an odd function to complete the computation.*/
    if (tmp.bits.sign)
        return -out;

    return out;
}
/*  End of tmpl_Float_Arctan.                                                 */

#else
/*  Else for #if TMPL_HAS_IEEE754_FLOAT == 1.                                 */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Single precision inverse tangent (atanf equivalent).                      */
float tmpl_Float_Arctan(float x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    float abs_x, arg, out, v, atan_v;
    unsigned int ind;

    /*  Special cases, NaN and INF.                                           */
    if (tmpl_Float_Is_NaN(x))
        return x;

    else if (tmpl_Float_Is_Inf(x))
    {
        /*  The limit as x -> inf is pi/2 and -pi/2 as x -> -inf.             */
        if (x < 0.0F)
            return -TMPL_PI_BY_TWO;

        return TMPL_PI_BY_TWO;
    }

    /*  The inverse tangent function is odd. Reduce x to non-negative.        */
    abs_x = tmpl_Float_Abs(x);

    /*  Small values, |x| < 1/16. Use the MacLaurin series to a few terms.    */
    if (abs_x < 0.0625F)
        return tmpl_Float_Arctan_Very_Small(x);

    /*  Otherwise get the correct index for the lookup table.                 */
    else if (abs_x < 0.125F)
        ind = 0U;
    else if (abs_x < 0.25F)
        ind = 1U;
    else if (abs_x < 0.5F)
        ind = 2U;
    else if (abs_x < 1.0F)
        ind = 3U;
    else if (abs_x < 2.0F)
        ind = 4U;
    else if (abs_x < 4.0F)
        ind = 5U;
    else if (abs_x < 8.0F)
        ind = 6U;
    else if (abs_x < 16.0F)
        ind = 7U;

    /*  For |x| > 16, use the asymptotic expansion.                           */
    else
    {
        out = tmpl_Float_Arctan_Asymptotic(abs_x);

        /*  Use the fact the atan is odd to finish the computation.           */
        if (x < 0.0F)
            return -out;

        return out;
    }

    /*  Get the nearby values from the lookup tables.                         */
    v = tmpl_atan_float_v[ind];
    atan_v = tmpl_atan_float_atan_of_v[ind];

    /*  Compute the argument via formula 4.4.34 from Abramowitz and Stegun.   */
    arg = (abs_x - v) / (1.0F + abs_x*v);
    out = atan_v + tmpl_Float_Arctan_Maclaurin(arg);

    /*  Use the fact that atan is an odd function to complete the computation.*/
    if (x < 0.0F)
        return -out;

    return out;
}
/*  End of tmpl_Float_Arctan.                                                 */

#endif
/*  End of #if TMPL_HAS_IEEE754_FLOAT == 1.                                   */

/*  Undefine everything in case someone wants to #include this file.          */
#include "auxiliary/tmpl_math_undef.h"

#endif
/*  End of #if TMPL_USE_MATH_ALGORITHMS == 1.                                 */
