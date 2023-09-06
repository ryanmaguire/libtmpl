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
 *                            tmpl_arctan2_double                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Compute the angle the point (x, y) makes with the x axis.             *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Arctan2                                                   *
 *  Purpose:                                                                  *
 *      Computes the angle the point (x, y) makes with the x axis.            *
 *  Arguments:                                                                *
 *      y (double):                                                           *
 *          A real number, the vertical component of the point.               *
 *      x (double):                                                           *
 *          A real number, the horizontal component of the point.             *
 *  Output:                                                                   *
 *      theta (double):                                                       *
 *          The angle, between -pi and pi, the point (x, y) makes with the    *
 *          x axis.                                                           *
 *  IEEE-754 Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_math.h:                                                      *
 *              tmpl_Double_Arctan_Asymptotic:                                *
 *                  Computes the asymptotic expansion of arctan for large     *
 *                  positive real numbers. Very accurate for x > 16.          *
 *              tmpl_Double_Arctan_Maclaurin:                                 *
 *                  Computes the Maclaurin series of arctan. More terms are   *
 *                  used in this function than tmpl_Double_Arctan_Very_Small. *
 *              tmpl_Double_Arctan_Very_Small:                                *
 *                  Computes the inverse tangent of small numbers using a     *
 *                  Maclaurin series. Accurate for values smaller than 1/16.  *
 *      Method:                                                               *
 *          Depends on one of several cases:                                  *
 *              y zero:                                                       *
 *                  x positive:                                               *
 *                      return 0.                                             *
 *                  x negative:                                               *
 *                      return Pi.                                            *
 *                  x zero:                                                   *
 *                      return 0.                                             *
 *                  x NaN:                                                    *
 *                      return NaN.                                           *
 *              x zero:                                                       *
 *                  y positive:                                               *
 *                      return pi/2.                                          *
 *                  y negative:                                               *
 *                      return -pi/2.                                         *
 *                  y NaN:                                                    *
 *                      return NaN.                                           *
 *              y infinite:                                                   *
 *                  x finite:                                                 *
 *                      pi/2 if y is positive, -pi/2 if y is negative.        *
 *                  x infinite:                                               *
 *                      pi/4 if x and y are positive.                         *
 *                      -pi/4 if x positive, y negative.                      *
 *                      3pi/4 if x negative, y positive.                      *
 *                      -3pi/4 if x and y negative.                           *
 *                  x NaN:                                                    *
 *                      return NaN.                                           *
 *              x infinite:                                                   *
 *                  y finite:                                                 *
 *                      0 if y is positive, pi if y is negative.              *
 *                  y NaN:                                                    *
 *                      return NaN.                                           *
 *              x and y finite:                                               *
 *                  Reduce y to positive via:                                 *
 *                      atan2(y, x) = -atan2(-y, x)                           *
 *                  Reduce x to positive via:                                 *
 *                      atan2(y, x) = pi - atan2(y, -x)                       *
 *                  Given x and y positive, compute atan(z), z = y/x:         *
 *                      For very small values of z, use the Maclaurin series  *
 *                      to the first few terms.                               *
 *                                                                            *
 *                      For values less than 16, use formula 4.4.34 from      *
 *                      Abramowitz and Stegun to reduce the argument to a     *
 *                      smaller value. This formula states that:              *
 *                                                                            *
 *                                                     u - v                  *
 *                          atan(u) - atan(v) = atan( -------- )              *
 *                                                     1 + uv                 *
 *                                                                            *
 *                      Use a lookup table for atan(v) with precomputed       *
 *                      values. Reduce and use a Maclaurin series.            *
 *                      The index of the lookup table is computed via the     *
 *                      exponent of the double z.                             *
 *                                                                            *
 *                      For larger values, use the asmyptotic expansion.      *
 *      Error:                                                                *
 *          Based on 788,968,857 random samples with -100 < x, y < 100.       *
 *              max relative error: 4.4955987686353023e-16                    *
 *              rms relative error: 9.2214263529102684e-17                    *
 *              max absolute error: 4.4408920985006262e-16                    *
 *              rms absolute error: 1.6454528697674011e-16                    *
 *          Values assume 100% accuracy of glibc. Actual error in glibc is    *
 *          less than 1 ULP (~2 x 10^-16).                                    *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_math.h:                                                      *
 *              tmpl_Double_Abs:                                              *
 *                  Computes the absolute value of a real number.             *
 *              tmpl_Double_Arctan_Asymptotic:                                *
 *                  Computes the asymptotic expansion of arctan for large     *
 *                  positive real numbers. Very accurate for x > 16.          *
 *              tmpl_Double_Arctan_Maclaurin:                                 *
 *                  Computes the Maclaurin series of arctan. More terms are   *
 *                  used in this function than tmpl_Double_Arctan_Very_Small. *
 *              tmpl_Double_Arctan_Very_Small:                                *
 *                  Computes the inverse tangent of small numbers using a     *
 *                  Maclaurin series. Accurate for values smaller than 1/16.  *
 *              tmpl_Double_Is_NaN:                                           *
 *                  Determines if a double is Not-a-Number.                   *
 *              tmpl_Double_Is_Inf:                                           *
 *                  Determines if a double is infinity.                       *
 *      Method:                                                               *
 *          Same as IEEE-754 method, except the index of the lookup table is  *
 *          computed via if-then statements to narrow down the range of x.    *
 *      Error:                                                                *
 *          Based on 788,968,857 random samples with -100 < x, y < 100.       *
 *              max relative error: 4.4955987686353023e-16                    *
 *              rms relative error: 9.2214263529102684e-17                    *
 *              max absolute error: 4.4408920985006262e-16                    *
 *              rms absolute error: 1.6454528697674011e-16                    *
 *          Values assume 100% accuracy of glibc. Actual error in glibc is    *
 *          less than 1 ULP (~2 x 10^-16).                                    *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_USE_MATH_ALGORITHMS macro.            *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 15, 2022                                            *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2022/09/13: Ryan Maguire                                                  *
 *      Added license, comments, and description of algorithm.                *
 *  2023/06/06: Ryan Maguire                                                  *
 *      Added checks for overflow and underflow in the division step.         *
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
#include <libtmpl/include/math/tmpl_arctan_maclaurin_double.h>

/*  Smaller Maclaurin expansion that avoids underflow.                        */
#include <libtmpl/include/math/tmpl_arctan_very_small_double.h>

/*  Asymptotic expansion for arctan. Good for large positive inputs.          */
#include <libtmpl/include/math/tmpl_arctan_asymptotic_double.h>

/*  Check for IEEE-754 support.                                               */
#if TMPL_HAS_IEEE754_DOUBLE == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  Double precision inverse tangent (atan2 equivalent).                      */
double tmpl_Double_Arctan2(double y, double x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_Double wx, wy, wz, out;

    /*  Set the double part of the words to the two inputs.                   */
    wx.r = x;
    wy.r = y;

    /*  Special cases, NaN and INF.                                           */
    if (TMPL_DOUBLE_IS_NAN_OR_INF(wx))
    {
        /*  Check if x is NaN. If it is, return NaN.                          */
        if (TMPL_DOUBLE_IS_NAN(wx))
            return x;

        /*  x is infinity. Check if y is NaN or Inf.                          */
        if (TMPL_DOUBLE_IS_NAN_OR_INF(wy))
        {
            /*  Check if y is NaN. If it is, return NaN.                      */
            if (TMPL_DOUBLE_IS_NAN(wy))
                return y;

            /*  Both x and y are infinity. 4 special cases corresponding to   *
             *  North-East, North-West, South-West, and South-East. First     *
             *  case, x and y are both positive. Return north-east.           */
            if (!wx.bits.sign && !wy.bits.sign)
                return tmpl_Pi_By_Four;

            /*  y is positive, x is negative, return north-west.              */
            else if (wx.bits.sign && !wy.bits.sign)
                return tmpl_Three_Pi_By_Four;

            /*  x and y are both negative, return south-west.                 */
            else if (wx.bits.sign && wy.bits.sign)
                return -tmpl_Three_Pi_By_Four;

            /*  Lastly, x is positive and y is negative, return south-east.   */
            return -tmpl_Pi_By_Four;
        }

        /*  y is finite and x is infinite. The angle is 0 or pi.              */
        if (wx.bits.sign)
            out.r = tmpl_One_Pi;
        else
            out.r = 0.0;

        /*  Preserve the sign of y.                                           */
        out.bits.sign = wy.bits.sign;
        return out.r;
    }

    /*  Check if y is infinite or NaN.                                        */
    else if (TMPL_DOUBLE_IS_NAN_OR_INF(wy))
    {
        /*  We've already checked that x is finite. Check if y is NaN.        */
        if (TMPL_DOUBLE_IS_NAN(wy))
            return y;

        /*  y is infinite and x is finite. The angle is +/- pi/2.             */
        out.r = tmpl_Pi_By_Two;

        /*  The sign of the output is the same as the sign of y. Copy this.   */
        out.bits.sign = wy.bits.sign;
        return out.r;
    }

    /*  Next special case, y = 0.                                             */
    else if (y == 0.0)
    {
        /*  If x is negative, return Pi.                                      */
        if (wx.bits.sign)
        {
            /*  Preserve the sign of y. If y is a negative zero, return -Pi.  */
            out.r = tmpl_One_Pi;

            /*  The sign of the output is the same as the sign of y.          */
            out.bits.sign = wy.bits.sign;
            return out.r;
        }

        /*  Otherwise, return 0. To preserve the sign of y, return y.         */
        return y;
    }

    /*  Lastly, the case where x is zero to avoid division-by-zero.           */
    else if (x == 0.0)
    {
        /*  y is not zero, so the answer is +/- pi/2.                         */
        out.r = tmpl_Pi_By_Two;

        /*  The sign of the output is the same as the sign of y. Copy this.   */
        out.bits.sign = wy.bits.sign;
        return out.r;
    }

    /*  We have z = y/x. Compute the absolute value by setting sign to 0.     */
    wz.r = wy.r / wx.r;
    wz.bits.sign = 0x00U;

    /*  Small values, |z| < 1/16.                                             */
    if (wz.bits.expo < TMPL_DOUBLE_UBIAS - 4U)
    {
        /*  For very small values, |z| < 2^-60, use atan(z) = z to avoid      *
         *  underflow. atan(z) = z + O(z^3), so the error is negligible.      */
        if (wz.bits.expo < TMPL_DOUBLE_UBIAS - 60U)
            out.r = wz.r;

        /*  Otherwise use a Maclaurin series to a few terms.                  */
        else
            out.r = tmpl_Double_Arctan_Very_Small(wz.r);
    }

    /*  Large values, |z| >= 16.                                              */
    else if (wz.bits.expo > TMPL_DOUBLE_UBIAS + 3U)
    {
        /*  For very large values, |z| > 2^60, use the limiting value of pi/2.*
         *  The error goes like atan(z) = pi/2 + O(1/z). For |z| > 2^60 the   *
         *  remainder term is less than double precision epsilon (2^-52) so   *
         *  we can safely return pi/2.                                        */
        if (wz.bits.expo > TMPL_DOUBLE_UBIAS + 60U)
            out.r = tmpl_Pi_By_Two;

        /*  Otherwise use the asymptotic expansion.                           */
        else
            out.r = tmpl_Double_Arctan_Asymptotic(wz.r);
    }

    /*  Otherwise use the lookup table to reduce. Note we have reduced to the *
     *  case where -4 <= expo <= 3, where expo is the exponent of z.          */
    else
    {
        /*  The table is indexed by values near 0.0625, 0.125, 0.25, 0.5, 1,  *
         *  2, 4, and 8. The index thus corresponds to 4 + expo, where expo   *
         *  is the exponent of the number z. Compute this. The exponent       *
         *  in the IEEE-754 representation of a number is offset by a bias.   *
         *  Subtract off this bias to compute the actual index.               */
        const unsigned int ind = (wz.bits.expo + 4U) - TMPL_DOUBLE_UBIAS;

        /*  Get the corresponding values from the lookup tables.              */
        const double v = tmpl_atan_double_v[ind];
        const double atan_v = tmpl_atan_double_atan_of_v[ind];

        /*  Use 4.4.34 from Abramowitz and Stegun to compute the new argument.*/
        const double arg = (wz.r - v) / (1.0 + wz.r*v);

        /*  "arg" is small and we can compute with a Maclaurin polynomial.    */
        out.r = atan_v + tmpl_Double_Arctan_Maclaurin(arg);
    }

    /*  Reduce to the case where x > 0 via atan2(y, -x) = pi - atan2(y, x).   */
    if (wx.bits.sign)
        out.r = tmpl_One_Pi - out.r;

    /*  Reduce to y > 0 via atan2(-y, x) = -atan2(y, x).                      */
    out.bits.sign = wy.bits.sign;
    return out.r;
}
/*  End of tmpl_Double_Arctan.                                                */

#else
/*  Else for #if TMPL_HAS_IEEE754_DOUBLE == 1.                                */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Double precision inverse tangent (atan2 equivalent).                      */
double tmpl_Double_Arctan2(double y, double x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    double z, arg, out, v, atan_v;
    unsigned int ind;

    /*  Special cases, NaN and INF.                                           */
    if (tmpl_Double_Is_NaN(x))
        return x;
    else if (tmpl_Double_Is_NaN(y))
        return y;
    else if (tmpl_Double_Is_Inf(x))
    {
        /*  x is infinity. Check if y is infinity as well.                    */
        if (tmpl_Double_Is_Inf(y))
        {
            /*  Both x and y are infinity. 4 special cases corresponding to   *
             *  North-East, North-West, South-West, and South-East.           */
            if (x > 0.0 && y > 0.0)
                return tmpl_Pi_By_Four;
            else if (x < 0.0 && y > 0.0)
                return tmpl_Three_Pi_By_Four;
            else if (x < 0.0 && y < 0.0)
                return -tmpl_Three_Pi_By_Four;
            else
                return -tmpl_Pi_By_Four;
        }

        /*  y is finite and x is infinite. The angle is 0 or pi.              */
        if (x < 0.0)
            return tmpl_One_Pi;
        else
            return 0.0;
    }

    /*  Check if y is infinite.                                               */
    else if (tmpl_Double_Is_Inf(y))
    {
        /*  y is infinite and x is finite. The angle is +/- pi/2.             */
        if (y < 0.0)
            return -tmpl_Pi_By_Two;
        else
            return tmpl_Pi_By_Two;
    }

    /*  Next special case, y = 0.                                             */
    else if (y == 0.0)
    {
        /*  If x is negative, return Pi.                                      */
        if (x < 0.0)
            return tmpl_One_Pi;

        /*  Otherwise, return 0. To preserve the sign of y, return y.         */
        else
            return y;
    }

    /*  Lastly, the case where x is zero to avoid division-by-zero.           */
    else if (x == 0.0)
    {
        /*  y is not zero, so the answer is +/- pi/2.                         */
        if (y < 0.0)
            return -tmpl_Pi_By_Two;
        else
            return tmpl_Pi_By_Two;
    }

    /*  We have z = y/x. Reduce by computing the absolute value of this.      */
    z = tmpl_Double_Abs(y / x);

    /*  For small values, z < 1/16, use the Maclaurin series to a few terms.  */
    if (z < 0.0625)
    {
        out = tmpl_Double_Arctan_Very_Small(z);
        goto TMPL_DOUBLE_ARCTAN2_FINISH;
    }

    /*  Otherwise compute the greatest power of two less than z. To compute   *
     *  the index of the lookup table, take this value and add 4 to it. Store *
     *  the answer in "ind" and find this value by checking the range of z.   */
    else if (z < 0.125)
        ind = 0U;
    else if (z < 0.25)
        ind = 1U;
    else if (z < 0.5)
        ind = 2U;
    else if (z < 1.0)
        ind = 3U;
    else if (z < 2.0)
        ind = 4U;
    else if (z < 4.0)
        ind = 5U;
    else if (z < 8.0)
        ind = 6U;
    else if (z < 16.0)
        ind = 7U;

    /*  For z > 16, use the asymptotic expansion.                             */
    else
    {
        out = tmpl_Double_Arctan_Asymptotic(z);
        goto TMPL_DOUBLE_ARCTAN2_FINISH;
    }

    /*  Use the lookup table for arctan. Get the pre-computed values.         */
    v = tmpl_atan_double_v[ind];
    atan_v = tmpl_atan_double_atan_of_v[ind];

    /*  Compute the argument via formula 4.4.34 from Abramowitz and Stegun.   */
    arg = (z - v) / (1.0 + z*v);
    out = atan_v + tmpl_Double_Arctan_Maclaurin(arg);

    /*  Last step, perform the argument reduction. We computed |y/x| at the   *
     *  start but have not changed x or y so their signs are untouched.       *
     *  Inspect the signs of each to finish the computation.                  */
TMPL_DOUBLE_ARCTAN2_FINISH:

    /*  Reduce to x > 0 via atan2(y, x) = pi - atan2(y, -x).                  */
    if (x < 0.0)
        out = tmpl_One_Pi - out;

    /*  Reduce to y > 0 via atan2(y, x) = -atan2(-y, x).                      */
    if (y < 0.0)
        return -out;
    else
        return out;
}
/*  End of tmpl_Double_Arctan.                                                */

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE == 1.                                  */

#endif
/*  End of #if TMPL_USE_MATH_ALGORITHMS == 1.                                 */
