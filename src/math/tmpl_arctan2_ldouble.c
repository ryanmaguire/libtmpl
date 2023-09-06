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
 *                            tmpl_arctan2_ldouble                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Compute the angle the point (x, y) makes with the x axis.             *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Arctan2                                                  *
 *  Purpose:                                                                  *
 *      Computes the angle the point (x, y) makes with the x axis.            *
 *  Arguments:                                                                *
 *      y (long double):                                                      *
 *          A real number, the vertical component of the point.               *
 *      x (long double):                                                      *
 *          A real number, the horizontal component of the point.             *
 *  Output:                                                                   *
 *      theta (long double):                                                  *
 *          The angle, between -pi and pi, the point (x, y) makes with the    *
 *          x axis.                                                           *
 *  64-Bit Double / 80-Bit Extended:                                          *
 *      Called Functions:                                                     *
 *          tmpl_LDouble_Abs (tmpl_math.h):                                   *
 *              Computes the absolute value of a real number.                 *
 *          tmpl_LDouble_Arctan_Asymptotic (tmpl_math.h):                     *
 *              Computes the asymptotic expansion of arctan for large         *
 *              positive real numbers. Very accurate for x > 16.              *
 *          tmpl_LDouble_Arctan_Maclaurin (tmpl_math.h):                      *
 *              Computes the Maclaurin series of arctan. More terms are used  *
 *              in this function than tmpl_LDouble_Arctan_Very_Small.         *
 *          tmpl_LDouble_Arctan_Very_Small (tmpl_math.h):                     *
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
 *                      exponent of the long double z.                        *
 *                                                                            *
 *                      For larger values, use the asmyptotic expansion.      *
 *      Error (64-Bit Double):                                                *
 *          Based on 788,968,857 random samples with -100 < x, y < 100.       *
 *              max relative error: 4.4955987686353023e-16                    *
 *              rms relative error: 9.2214263529102684e-17                    *
 *              max absolute error: 4.4408920985006262e-16                    *
 *              rms absolute error: 1.6454528697674011e-16                    *
 *          Values assume 100% accuracy of glibc. Actual error in glibc is    *
 *          less than 1 ULP (~2 x 10^-16).                                    *
 *      Error (80-Bit Extended):                                              *
 *          Based on 394,484,428 random samples with -100 < x, y < 100.       *
 *              max relative error: 2.1682630157549489e-19                    *
 *              rms relative error: 3.9719504311123539e-20                    *
 *              max absolute error: 2.1684043449710089e-19                    *
 *              rms absolute error: 7.2247868870500588e-20                    *
 *          Values assume 100% accuracy of glibc. Actual error in glibc is    *
 *          less than 1 ULP (~1 x 10^-19).                                    *
 *  128-Bit Quadruple / 128-Bit Double-Double:                                *
 *      Called Functions:                                                     *
 *          tmpl_LDouble_Abs (tmpl_math.h):                                   *
 *              Computes the absolute value of a real number.                 *
 *          tmpl_LDouble_Arctan_Pade (tmpl_math.h):                           *
 *              Compute the Pade approximant for atan. Very accurate for      *
 *              small values. Used to get relative error to ~10^-34.          *
 *      Method:                                                               *
 *          Similar to double / extended method, but with a large lookup      *
 *          table and using the Pade approximant instead of Maclaurin series. *
 *      Error (128-Bit Quadruple):                                            *
 *          Based on 25,000,000 random samples with -100 < x, y < 100.        *
 *              max relative error: 1.7473101468321921e-34                    *
 *              rms relative error: 5.2509800591011004e-35                    *
 *              max absolute error: 3.8518598887744717e-34                    *
 *              rms absolute error: 1.0894746550053625e-34                    *
 *          Values assume 100% accuracy of glibc. Actual error in glibc is    *
 *          less than 1 ULP (~2 x 10^-34).                                    *
 *      Error (128-Bit Double-Double):                                        *
 *          Based on 25,000,000 random samples with -100 < x, y < 100.        *
 *              max relative error: 1.5693901271014608e-32                    *
 *              rms relative error: 4.0465499798622827e-33                    *
 *              max absolute error: 2.4651903288156619e-32                    *
 *              rms absolute error: 6.3562982935323872e-33                    *
 *          Values assume 100% accuracy of glibc. Comments for their          *
 *          double-double implementation claim the peak error is 1.7 x 10^-34.*
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_LDouble_Abs (tmpl_math.h):                                   *
 *              Computes the absolute value of a real number.                 *
 *          tmpl_LDouble_Arctan_Asymptotic (tmpl_math.h):                     *
 *              Computes the asymptotic expansion of arctan for large         *
 *              positive real numbers. Very accurate for x > 16.              *
 *          tmpl_LDouble_Arctan_Maclaurin (tmpl_math.h):                      *
 *              Computes the Maclaurin series of arctan. More terms are used  *
 *              in this function than tmpl_LDouble_Arctan_Very_Small.         *
 *          tmpl_LDouble_Arctan_Very_Small (tmpl_math.h):                     *
 *              Computes the inverse tangent of small numbers using a         *
 *              Maclaurin series. Accurate for values smaller than 1/32.      *
 *          tmpl_LDouble_Is_NaN (tmpl_math.h):                                *
 *              Determines if a long double is Not-a-Number.                  *
 *          tmpl_LDouble_Is_Inf (tmpl_math.h):                                *
 *              Determines if a long double is infinity.                      *
 *      Method:                                                               *
 *          Same as double / extended, except the index of the lookup table   *
 *          is computed via if-then statements to narrow down the range of x. *
 *      Error:                                                                *
 *          Based on 394,484,428 random samples with -100 < x, y < 100.       *
 *              max relative error: 2.1682630157549489e-19                    *
 *              rms relative error: 3.9719504311123539e-20                    *
 *              max absolute error: 2.1684043449710089e-19                    *
 *              rms absolute error: 7.2247868870500588e-20                    *
 *          Values assume 100% accuracy of glibc. Actual error in glibc is    *
 *          less than 1 ULP (~1 x 10^-19).                                    *
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

/*  Quadruple precision and double-double use Pade approximants.              */
#if TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_BIG_ENDIAN    || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_LITTLE_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_BIG_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_LITTLE_ENDIAN

/*  Pade approximant provided here.                                           */
#include <libtmpl/include/math/tmpl_arctan_pade_ldouble.h>

#else
/*  Double precision, extended precision, and portable includes.              */

/*  Maclaurin expansion provided here.                                        */
#include <libtmpl/include/math/tmpl_arctan_maclaurin_ldouble.h>

/*  Smaller Maclaurin expansion that avoids underflow.                        */
#include <libtmpl/include/math/tmpl_arctan_very_small_ldouble.h>

/*  Asymptotic expansion for arctan. Good for large positive inputs.          */
#include <libtmpl/include/math/tmpl_arctan_asymptotic_ldouble.h>

#endif
/*  End of double-double / quadruple vs. double / extended / portable.        */

/*  Check for IEEE-754 support.                                               */
#if TMPL_HAS_IEEE754_LDOUBLE == 1

/*  64-bit double and 80-bit extended use the same idea.                      */
#if TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN           || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_BIG_ENDIAN              || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_96_BIT_EXTENDED_LITTLE_ENDIAN  || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_96_BIT_EXTENDED_BIG_ENDIAN     || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_EXTENDED_LITTLE_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_EXTENDED_BIG_ENDIAN

/******************************************************************************
 *                  64-Bit Double / 80-Bit Extended Versions                  *
 ******************************************************************************/

/*  Long double precision inverse tangent (atan2l equivalent).                */
long double tmpl_LDouble_Arctan2(long double y, long double x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_LDouble wx, wy, w;
    long double arg, out, v, atan_v;
    unsigned int ind;

    /*  Set the long double part of the words to the two inputs.              */
    wx.r = x;
    wy.r = y;

    /*  Special cases, NaN and INF.                                           */
    if (TMPL_LDOUBLE_IS_NAN_OR_INF(wx))
    {
        /*  Check if x is NaN. If it is, return NaN.                          */
        if (TMPL_LDOUBLE_IS_NAN(wx))
            return x;

        /*  x is infinity. Check if y is NaN or Inf.                          */
        if (TMPL_LDOUBLE_IS_NAN_OR_INF(wy))
        {
            /*  Check if y is NaN. If it is, return NaN.                      */
            if (TMPL_LDOUBLE_IS_NAN(wy))
                return y;

            /*  Both x and y are infinity. 4 special cases corresponding to   *
             *  North-East, North-West, South-West, and South-East.           */
            if (!TMPL_LDOUBLE_IS_NEGATIVE(wx) &&
                !TMPL_LDOUBLE_IS_NEGATIVE(wy))
                return tmpl_Pi_By_Four_L;
            else if (TMPL_LDOUBLE_IS_NEGATIVE(wx) &&
                     !TMPL_LDOUBLE_IS_NEGATIVE(wy))
                return tmpl_Three_Pi_By_Four_L;
            else if (TMPL_LDOUBLE_IS_NEGATIVE(wx) &&
                     TMPL_LDOUBLE_IS_NEGATIVE(wy))
                return -tmpl_Three_Pi_By_Four_L;
            else
                return -tmpl_Pi_By_Four_L;
        }

        /*  y is finite and x is infinite. The angle is 0 or pi.              */
        if (TMPL_LDOUBLE_IS_NEGATIVE(wx))
            w.r = tmpl_One_Pi_L;
        else
            w.r = 0.0L;

        /*  Preserve the sign of y.                                           */
        if (TMPL_LDOUBLE_IS_NEGATIVE(wy))
            return -w.r;
        else
            return w.r;
    }

    /*  Check if y is infinite or NaN.                                        */
    else if (TMPL_LDOUBLE_IS_NAN_OR_INF(wy))
    {
        /*  We've already checked that x is finite. Check if y is NaN.        */
        if (TMPL_LDOUBLE_IS_NAN(wy))
            return y;

        /*  y is infinite and x is finite. The angle is +/- pi/2.             */
        if (TMPL_LDOUBLE_IS_NEGATIVE(wy))
            return -tmpl_Pi_By_Two_L;
        else
            return tmpl_Pi_By_Two_L;
    }

    /*  Next special case, y = 0.                                             */
    else if (y == 0.0L)
    {
        /*  If x is negative, return Pi.                                      */
        if (TMPL_LDOUBLE_IS_NEGATIVE(wx))
        {
            /*  Preserve the sign of y. If y is a negative zero, return -Pi.  */
            if (TMPL_LDOUBLE_IS_NEGATIVE(wy))
                return -tmpl_One_Pi_L;
            else
                return tmpl_One_Pi_L;
        }

        /*  Otherwise, return 0. To preserve the sign of y, return y.         */
        else
            return y;
    }

    /*  Lastly, the case where x is zero to avoid division-by-zero.           */
    else if (x == 0.0L)
    {
        /*  y is not zero, so the answer is +/- pi/2.                         */
        if (TMPL_LDOUBLE_IS_NEGATIVE(wy))
            return -tmpl_Pi_By_Two_L;
        else
            return tmpl_Pi_By_Two_L;
    }

    /*  We have z = y/x. Reduce to x and y positive by computing |z|.         */
    w.r = tmpl_LDouble_Abs(wy.r / wx.r);

    /*  Small values, |z| < 1/32. Use the MacLaurin series to a few terms.    */
    if (TMPL_LDOUBLE_EXPO_BITS(w) < TMPL_LDOUBLE_UBIAS - 4U)
        out = tmpl_LDouble_Arctan_Very_Small(w.r);

    /*  For |z| > 16, use the asymptotic expansion.                           */
    else if (TMPL_LDOUBLE_EXPO_BITS(w) > TMPL_LDOUBLE_UBIAS + 3U)
        out = tmpl_LDouble_Arctan_Asymptotic(w.r);

    /*  Otherwise use the lookup table to reduce. Note we have reduced to the *
     *  case where -4 <= expo <= 3, where expo is the exponent of z.          */
    else
    {
        /*  The table is indexed by values near 0.0625, 0.125, 0.25, 0.5, 1,  *
         *  2, 4, and 8. The index thus corresponds to 4 + expo, where expo   *
         *  is the exponent of the number z. Compute this. The exponent       *
         *  in the IEEE-754 representation of a number is offset by a bias.   *
         *  Subtract off this bias to compute the actual index.               */
        ind = (TMPL_LDOUBLE_EXPO_BITS(w) + 4U) - TMPL_LDOUBLE_UBIAS;

        /*  Get the corresponding values from the lookup tables.              */
        v = tmpl_atan_ldouble_v[ind];
        atan_v = tmpl_atan_ldouble_atan_of_v[ind];

        /*  Use 4.4.34 from Abramowitz and Stegun to compute the new argument.*/
        arg = (w.r - v) / (1.0L + w.r*v);
        out = atan_v + tmpl_LDouble_Arctan_Maclaurin(arg);
    }

    /*  Reduce to the case where x > 0 via atan2(y, -x) = pi - atan2(y, x).   */
    if (TMPL_LDOUBLE_IS_NEGATIVE(wx))
        out = tmpl_One_Pi_L - out;

    /*  Reduce to y > 0 via atan2(-y, x) = -atan2(y, x).                      */
    if (TMPL_LDOUBLE_IS_NEGATIVE(wy))
        return -out;
    else
        return out;
}
/*  End of tmpl_LDouble_Arctan.                                               */

#else
/*  Else for 64-bit double / 80-bit extended precision versions.              */

/******************************************************************************
 *                 128-Bit Quadruple / 128-Bit Double-Double                  *
 ******************************************************************************/

/*  To get quadruple or double-double precision, the Taylor series is too     *
 *  slow. Instead, the Pade approximant is used after reducing the argument.  */

/*  Long double precision inverse tangent (atan2 equivalent).                 */
long double tmpl_LDouble_Arctan2(long double y, long double x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_LDouble wx, wy, w;
    long double out, t;
    unsigned int n;

    /*  Set the long double part of the words to the two inputs.              */
    wx.r = x;
    wy.r = y;

    /*  Special cases, NaN and INF.                                           */
    if (TMPL_LDOUBLE_IS_NAN_OR_INF(wx))
    {
        /*  Check if x is NaN. If it is, return NaN.                          */
        if (TMPL_LDOUBLE_IS_NAN(wx))
            return x;

        /*  x is infinity. Check if y is NaN or Inf.                          */
        if (TMPL_LDOUBLE_IS_NAN_OR_INF(wy))
        {
            /*  Check if y is NaN. If it is, return NaN.                      */
            if (TMPL_LDOUBLE_IS_NAN(wy))
                return y;

            /*  Both x and y are infinity. 4 special cases corresponding to   *
             *  North-East, North-West, South-West, and South-East.           */
            if (!TMPL_LDOUBLE_IS_NEGATIVE(wx) &&
                !TMPL_LDOUBLE_IS_NEGATIVE(wy))
                return tmpl_Pi_By_Four_L;
            else if (TMPL_LDOUBLE_IS_NEGATIVE(wx) &&
                     !TMPL_LDOUBLE_IS_NEGATIVE(wy))
                return tmpl_Three_Pi_By_Four_L;
            else if (TMPL_LDOUBLE_IS_NEGATIVE(wx) &&
                     TMPL_LDOUBLE_IS_NEGATIVE(wy))
                return -tmpl_Three_Pi_By_Four_L;
            else
                return -tmpl_Pi_By_Four_L;
        }

        /*  y is finite and x is infinite. The angle is 0 or pi.              */
        if (TMPL_LDOUBLE_IS_NEGATIVE(wx))
            w.r = tmpl_One_Pi_L;
        else
            w.r = 0.0L;

        /*  Preserve the sign of y.                                           */
        if (TMPL_LDOUBLE_IS_NEGATIVE(wy))
            return -w.r;
        else
            return w.r;
    }

    /*  Check if y is infinite or NaN.                                        */
    else if (TMPL_LDOUBLE_IS_NAN_OR_INF(wy))
    {
        /*  We've already checked that x is finite. Check if y is NaN.        */
        if (TMPL_LDOUBLE_IS_NAN(wy))
            return y;

        /*  y is infinite and x is finite. The angle is +/- pi/2.             */
        if (TMPL_LDOUBLE_IS_NEGATIVE(wy))
            return -tmpl_Pi_By_Two_L;
        else
            return tmpl_Pi_By_Two_L;
    }

    /*  Next special case, y = 0.                                             */
    else if (y == 0.0L)
    {
        /*  If x is negative, return Pi.                                      */
        if (TMPL_LDOUBLE_IS_NEGATIVE(wx))
        {
            /*  Preserve the sign of y. If y is a negative zero, return -Pi.  */
            if (TMPL_LDOUBLE_IS_NEGATIVE(wy))
                return -tmpl_One_Pi_L;
            else
                return tmpl_One_Pi_L;
        }

        /*  Otherwise, return 0. To preserve the sign of y, return y.         */
        else
            return y;
    }

    /*  Lastly, the case where x is zero to avoid division-by-zero.           */
    else if (x == 0.0L)
    {
        /*  y is not zero, so the answer is +/- pi/2.                         */
        if (TMPL_LDOUBLE_IS_NEGATIVE(wy))
            return -tmpl_Pi_By_Two_L;
        else
            return tmpl_Pi_By_Two_L;
    }

    /*  We have z = y/x. Reduce to x and y positive by computing |z|.         */
    w.r = tmpl_LDouble_Abs(wy.r / wx.r);

    /*  Avoid underflow. If |x| < 2^-56, atan(x) = x to quadruple precision.  */
    if (TMPL_LDOUBLE_EXPO_BITS(w) < TMPL_LDOUBLE_UBIAS - 56U)
        out = w.r;

    /*  For |x| > 16, use the asymptotic expansion.                           */
    else if (TMPL_LDOUBLE_EXPO_BITS(w) > TMPL_LDOUBLE_UBIAS + 3U)
        out = tmpl_Pi_By_Two_L - tmpl_LDouble_Arctan_Pade(1.0L/w.r);

    /*  Otherwise reduce and use the Pade approximant.                        */
    else
    {
        n = (unsigned int)(8.0L*w.r + 0.25L);
        t = 0.125L * (long double)n;
        t = (w.r - t) / (1.0L + w.r*t);
        out = tmpl_ldouble_atan_n_by_8[n] + tmpl_LDouble_Arctan_Pade(t);
    }

    /*  Reduce to the case where x > 0 via atan2(y, -x) = pi - atan2(y, x).   */
    if (TMPL_LDOUBLE_IS_NEGATIVE(wx))
        out = tmpl_One_Pi_L - out;

    /*  Reduce to y > 0 via atan2(-y, x) = -atan2(y, x).                      */
    if (TMPL_LDOUBLE_IS_NEGATIVE(wy))
        return -out;
    else
        return out;
}
/*  End of tmpl_LDouble_Arctan.                                               */

#endif
/*  End of double-double / quadruple precision versions.                      */

#else
/*  Else for #if TMPL_HAS_IEEE754_LDOUBLE == 1.                               */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Long double precision inverse tangent (atan2l equivalent).                */
long double tmpl_LDouble_Arctan2(long double y, long double x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    long double z, arg, out, v, atan_v;
    unsigned int ind;

    /*  Special cases, NaN and INF.                                           */
    if (tmpl_LDouble_Is_NaN(x))
        return x;
    else if (tmpl_LDouble_Is_NaN(y))
        return y;
    else if (tmpl_LDouble_Is_Inf(x))
    {
        /*  x is infinity. Check if y is infinity as well.                    */
        if (tmpl_LDouble_Is_Inf(y))
        {
            /*  Both x and y are infinity. 4 special cases corresponding to   *
             *  North-East, North-West, South-West, and South-East.           */
            if (x > 0.0L && y > 0.0L)
                return tmpl_Pi_By_Four_L;
            else if (x < 0.0L && y > 0.0L)
                return tmpl_Three_Pi_By_Four_L;
            else if (x < 0.0L && y < 0.0L)
                return -tmpl_Three_Pi_By_Four_L;
            else
                return -tmpl_Pi_By_Four_L;
        }

        /*  y is finite and x is infinite. The angle is 0 or pi.              */
        if (x < 0.0L)
            return tmpl_One_Pi_L;
        else
            return 0.0L;
    }

    /*  Check if y is infinite.                                               */
    else if (tmpl_LDouble_Is_Inf(y))
    {
        /*  y is infinite and x is finite. The angle is +/- pi/2.             */
        if (y < 0.0L)
            return -tmpl_Pi_By_Two_L;
        else
            return tmpl_Pi_By_Two_L;
    }

    /*  Next special case, y = 0.                                             */
    else if (y == 0.0L)
    {
        /*  If x is negative, return Pi.                                      */
        if (x < 0.0L)
            return tmpl_One_Pi_L;

        /*  Otherwise, return 0. To preserve the sign of y, return y.         */
        else
            return y;
    }

    /*  Lastly, the case where x is zero to avoid division-by-zero.           */
    else if (x == 0.0L)
    {
        /*  y is not zero, so the answer is +/- pi/2.                         */
        if (y < 0.0L)
            return -tmpl_Pi_By_Two_L;
        else
            return tmpl_Pi_By_Two_L;
    }

    /*  We have z = y/x. Reduce by computing the absolute value of this.      */
    z = tmpl_LDouble_Abs(y / x);

    /*  For small values, z < 1/32, use the Maclaurin series to a few terms.  */
    if (z < 0.0625L)
    {
        out = tmpl_LDouble_Arctan_Very_Small(z);
        goto TMPL_LDOUBLE_ARCTAN2_FINISH;
    }

    /*  Otherwise compute the greatest power of two less than z. To compute   *
     *  the index of the lookup table, take this value and add 4 to it. Store *
     *  the answer in "ind" and find this value by checking the range of z.   */
    else if (z < 0.125L)
        ind = 0U;
    else if (z < 0.25L)
        ind = 1U;
    else if (z < 0.5L)
        ind = 2U;
    else if (z < 1.0L)
        ind = 3U;
    else if (z < 2.0L)
        ind = 4U;
    else if (z < 4.0L)
        ind = 5U;
    else if (z < 8.0L)
        ind = 6U;
    else if (z < 16.0L)
        ind = 7U;

    /*  For z > 16, use the asymptotic expansion.                             */
    else
    {
        out = tmpl_LDouble_Arctan_Asymptotic(z);
        goto TMPL_LDOUBLE_ARCTAN2_FINISH;
    }

    /*  Use the lookup table for arctan. Get the pre-computed values.         */
    v = tmpl_atan_ldouble_v[ind];
    atan_v = tmpl_atan_ldouble_atan_of_v[ind];

    /*  Compute the argument via formula 4.4.34 from Abramowitz and Stegun.   */
    arg = (z - v) / (1.0L + z*v);
    out = atan_v + tmpl_LDouble_Arctan_Maclaurin(arg);

    /*  Last step, perform the argument reduction. We computed |y/x| at the   *
     *  start but have not changed x or y so their signs are untouched.       *
     *  Inspect the signs of each to finish the computation.                  */
TMPL_LDOUBLE_ARCTAN2_FINISH:

    /*  Reduce to x > 0 via atan2(y, x) = pi - atan2(y, -x).                  */
    if (x < 0.0L)
        out = tmpl_One_Pi_L - out;

    /*  Reduce to y > 0 via atan2(y, x) = -atan2(-y, x).                      */
    if (y < 0.0L)
        return -out;
    else
        return out;
}
/*  End of tmpl_LDouble_Arctan.                                               */

#endif
/*  End of #if TMPL_HAS_IEEE754_LDOUBLE == 1.                                 */

#endif
/*  End of #if TMPL_USE_MATH_ALGORITHMS == 1.                                 */
