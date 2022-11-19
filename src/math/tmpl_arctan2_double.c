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
 *          tmpl_Double_Arctan_Asymptotic (tmpl_math.h):                      *
 *              Computes the asymptotic expansion of arctan for large         *
 *              positive real numbers. Very accurate for x > 16.              *
 *          tmpl_Double_Arctan_Maclaurin (tmpl_math.h):                       *
 *              Computes the Maclaurin series of arctan. More terms are used  *
 *              in this function than tmpl_Double_Arctan_Very_Small.          *
 *          tmpl_Double_Arctan_Very_Small (tmpl_math.h):                      *
 *              Computes the inverse tangent of small numbers using a         *
 *              Maclaurin series. Accurate for values smaller than 1/32.      *
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
 *          Based on 788,968,857 random samples with -100 < |x|, |y| < 100.   *
 *              max relative error: 4.4955987686353023e-16                    *
 *              rms relative error: 9.2214263529102684e-17                    *
 *              max absolute error: 4.4408920985006262e-16                    *
 *              rms absolute error: 1.6454528697674011e-16                    *
 *          Values assume 100% accuracy of glibc. Actually error in glibc is  *
 *          less than 1 ULP (~2 x 10^-16).                                    *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_Double_Abs (tmpl_math.h):                                    *
 *              Computes the absolute value of a real number.                 *
 *          tmpl_Double_Arctan_Asymptotic (tmpl_math.h):                      *
 *              Computes the asymptotic expansion of arctan for large         *
 *              positive real numbers. Very accurate for x > 16.              *
 *          tmpl_Double_Arctan_Maclaurin (tmpl_math.h):                       *
 *              Computes the Maclaurin series of arctan. More terms are used  *
 *              in this function than tmpl_Double_Arctan_Very_Small.          *
 *          tmpl_Double_Arctan_Very_Small (tmpl_math.h):                      *
 *              Computes the inverse tangent of small numbers using a         *
 *              Maclaurin series. Accurate for values smaller than 1/32.      *
 *          tmpl_Double_Is_NaN (tmpl_math.h):                                 *
 *              Determines if a double is Not-a-Number.                       *
 *          tmpl_Double_Is_Inf (tmpl_math.h):                                 *
 *              Determines if a double is infinity.                           *
 *      Method:                                                               *
 *          Same as IEEE-754 method, except the index of the lookup table is  *
 *          computed via if-then statements to narrow down the range of x.    *
 *      Error:                                                                *
 *          Based on 788,968,857 random samples with -100 < |x|, |y| < 100.   *
 *              max relative error: 4.4955987686353023e-16                    *
 *              rms relative error: 9.2214263529102684e-17                    *
 *              max absolute error: 4.4408920985006262e-16                    *
 *              rms absolute error: 1.6454528697674011e-16                    *
 *          Values assume 100% accuracy of glibc. Actually error in glibc is  *
 *          less than 1 ULP (~2 x 10^-16).                                    *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_USE_MATH_ALGORITHMS macro.            *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 *  3.) tmpl_math_arctan_double_tables.h:                                     *
 *          Header file containing pre-computed values of arctan(x).          *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 15, 2022                                            *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2022/09/13: Ryan Maguire                                                  *
 *      Added license, comments, and description of algorithm.                *
 ******************************************************************************/

/*  TMPL_USE_MATH_ALGORITHMS found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Only implement this if the user requested libtmpl algorithms.             */
#if TMPL_USE_MATH_ALGORITHMS == 1

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  Lookup table of precomputed arctan values found here.                     */
#include <libtmpl/include/math/tmpl_math_arctan_double_tables.h>

/*  Check for IEEE-754 support.                                               */
#if TMPL_HAS_IEEE754_DOUBLE == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  Double precision inverse tangent (atan2 equivalent).                      */
double tmpl_Double_Arctan2(double y, double x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_Double wx, wy, w;
    double arg, out, v, atan_v;
    unsigned int ind;

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
             *  North-East, North-West, South-West, and South-East.           */
            if (!wx.bits.sign && !wy.bits.sign)
                return tmpl_Pi_By_Four;
            else if (wx.bits.sign && !wy.bits.sign)
                return tmpl_Three_Pi_By_Four;
            else if (wx.bits.sign && wy.bits.sign)
                return -tmpl_Three_Pi_By_Four;
            else
                return -tmpl_Pi_By_Four;
        }

        /*  y is finite and x is infinite. The angle is 0 or pi.              */
        if (wx.bits.sign)
            w.r = tmpl_One_Pi;
        else
            w.r = 0.0;

        /*  Preserve the sign of y.                                           */
        w.bits.sign = wy.bits.sign;
        return w.r;
    }

    /*  Check if y is infinite or NaN.                                        */
    else if (TMPL_DOUBLE_IS_NAN_OR_INF(wy))
    {
        /*  We've already checked that x is finite. Check if y is NaN.        */
        if (TMPL_DOUBLE_IS_NAN(wy))
            return y;

        /*  y is infinite and x is finite. The angle is +/- pi/2.             */
        if (wy.bits.sign)
            return -tmpl_Pi_By_Two;
        else
            return tmpl_Pi_By_Two;
    }

    /*  Next special case, y = 0.                                             */
    else if (y == 0.0)
    {
        /*  If x is negative, return Pi.                                      */
        if (wx.bits.sign)
        {
            /*  Preserve the sign of y. If y is a negative zero, return -Pi.  */
            if (wy.bits.sign)
                return -tmpl_One_Pi;
            else
                return tmpl_One_Pi;
        }

        /*  Otherwise, return 0. To preserve the sign of y, return y.         */
        else
            return y;
    }

    /*  Lastly, the case where x is zero to avoid division-by-zero.           */
    else if (x == 0.0)
    {
        /*  y is not zero, so the answer is +/- pi/2.                         */
        if (wy.bits.sign)
            return -tmpl_Pi_By_Two;
        else
            return tmpl_Pi_By_Two;
    }

    /*  We have z = y/x. Compute the absolute value by setting sign to 0.     */
    w.r = wy.r / wx.r;
    w.bits.sign = 0x00U;

    /*  Small values, |z| < 1/32. Use the MacLaurin series to a few terms.    */
    if (w.bits.expo < TMPL_DOUBLE_UBIAS - 4U)
        out = tmpl_Double_Arctan_Very_Small(w.r);

    /*  For |z| > 16, use the asymptotic expansion.                           */
    else if (w.bits.expo > TMPL_DOUBLE_UBIAS + 3U)
        out = tmpl_Double_Arctan_Asymptotic(w.r);

    /*  Otherwise use the lookup table to reduce. Note we have reduced to the *
     *  case where -4 <= expo <= 3, where expo is the exponent of z.          */
    else
    {
        /*  The table is indexed by values near 0.0625, 0.125, 0.25, 0.5, 1,  *
         *  2, 4, and 8. The index thus corresponds to 4 + expo, where expo   *
         *  is the exponent of the number z. Compute this. The exponent       *
         *  in the IEEE-754 representation of a number is offset by a bias.   *
         *  Subtract off this bias to compute the actual index.               */
        ind = (w.bits.expo + 4U) - TMPL_DOUBLE_UBIAS;

        /*  Get the corresponding values from the lookup tables.              */
        v = tmpl_atan_double_v[ind];
        atan_v = tmpl_atan_double_atan_of_v[ind];

        /*  Use 4.4.34 from Abramowitz and Stegun to compute the new argument.*/
        arg = (w.r - v) / (1.0 + w.r*v);
        out = atan_v + tmpl_Double_Arctan_Maclaurin(arg);
    }

    /*  Reduce to the case where x > 0 via atan2(y, -x) = pi - atan2(y, x).   */
    if (wx.bits.sign)
        out = tmpl_One_Pi - out;

    /*  Reduce to y > 0 via atan2(-y, x) = -atan2(y, x).                      */
    if (wy.bits.sign)
        return -out;
    else
        return out;
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
        if (x < 0.0)
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

    /*  For small values, z < 1/32, use the Maclaurin series to a few terms.  */
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
