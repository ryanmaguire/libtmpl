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
 *                            tmpl_arctan2_float                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Compute the angle the point (x, y) makes with the x axis.             *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Arctan2                                                    *
 *  Purpose:                                                                  *
 *      Computes the angle the point (x, y) makes with the x axis.            *
 *  Arguments:                                                                *
 *      y (float):                                                            *
 *          A real number, the vertical component of the point.               *
 *      x (float):                                                            *
 *          A real number, the horizontal component of the point.             *
 *  Output:                                                                   *
 *      theta (float):                                                        *
 *          The angle, between -pi and pi, the point (x, y) makes with the    *
 *          x axis.                                                           *
 *  Called Functions:                                                         *
 *      tmpl_Float_Arctan_Asymptotic   (tmpl_math.h):                         *
 *          Computes the asymptotic expansion of the inverse tangent function *
 *          for large positive real numbers. Very accurate for x > 16.        *
 *      tmpl_Float_Arctan_Maclaurin    (tmpl_math.h):                         *
 *          Computes the inverse tangent using a Maclaurin series. More terms *
 *          are used in this function than tmpl_Float_Arctan_Very_Small.      *
 *      tmpl_Float_Arctan_Very_Small   (tmpl_math.h):                         *
 *          Computes the inverse tangent of small numbers using a Maclaurin   *
 *          series. Accurate for values smaller than 1/16.                    *
 *      tmpl_Float_Is_NaN              (tmpl_math.h):                         *
 *          Determines if a float is Not-a-number.                            *
 *      tmpl_Float_Is_Inf              (tmpl_math.h):                         *
 *          Determines if a float is infinity.                                *
 *  Method:                                                                   *
 *      Depends on one of several cases:                                      *
 *          y zero:                                                           *
 *              x positive:                                                   *
 *                  return 0.                                                 *
 *              x negative:                                                   *
 *                  return Pi.                                                *
 *              x zero:                                                       *
 *                  return 0.                                                 *
 *              x NaN:                                                        *
 *                  return NaN.                                               *
 *          x zero:                                                           *
 *              y positive:                                                   *
 *                  return pi/2.                                              *
 *              x negative:                                                   *
 *                  return -pi/2.                                             *
 *              x NaN:                                                        *
 *                  return NaN.                                               *
 *          y infinite:                                                       *
 *              x finite:                                                     *
 *                  pi/2 if y is positive, -pi/2 if y is negative.            *
 *              x infinite:                                                   *
 *                  pi/4 if x and y are positive.                             *
 *                  -pi/4 if x positive, y negative.                          *
 *                  3pi/4 if x negative, y positive.                          *
 *                  -3pi/4 if x and y negative.                               *
 *              x NaN:                                                        *
 *                  return NaN.                                               *
 *          x infinite:                                                       *
 *              y finite:                                                     *
 *                  0 if y is positive, pi if y is negative.                  *
 *              y NaN:                                                        *
 *                  return NaN.                                               *
 *              y infinite:                                                   *
 *                  See previous cases.                                       *
 *          x and y finite:                                                   *
 *              Reduce y to positive via:                                     *
 *                  atan2(y, x) = -atan2(-y, x)                               *
 *              Reduce x to positive via:                                     *
 *                  atan2(y, x) = pi - atan2(y, -x)                           *
 *              Given x and y positive, compute atan(z), z = y/x:             *
 *                  For very small values of z, use the Maclaurin series to   *
 *                  the first few terms.                                      *
 *                                                                            *
 *                  For values less than 16, use formula 4.4.34 from          *
 *                  Abramowitz and Stegun to reduce the argument to a smaller *
 *                  value. This formula states that:                          *
 *                                                                            *
 *                                                 u - v                      *
 *                      atan(u) - atan(v) = atan( -------- )                  *
 *                                                 1 + uv                     *
 *                                                                            *
 *                  Use a lookup table for atan(v) with precomputed values.   *
 *                  Reduce and use a Maclaurin series.                        *
 *                                                                            *
 *                  For larger values, use the asmyptotic expansion.          *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_USE_INLINE macro.                     *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 22, 2022                                            *
 ******************************************************************************/

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  Only implement this if the user requested libtmpl algorithms.             */
#if TMPL_USE_MATH_ALGORITHMS == 1

/*  Lookup table of precomputed arctan values found here.                     */
#include <libtmpl/include/tmpl_math_arctan_tables.h>

/*  Check for IEEE-754 support.                                               */
#if TMPL_HAS_IEEE754_FLOAT == 1

/*  Single precision inverse tangent (atan2 equivalent).                      */
float tmpl_Float_Arctan2(float y, float x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_Float wx, wy, w;
    float arg, out, v, atan_v;
    unsigned int ind;

    /*  Set the float part of the words to the two inputs.                    */
    wx.r = x;
    wy.r = y;

    /*  Special cases, NaN and INF.                                           */
    if (wx.bits.expo == TMPL_FLOAT_NANINF_EXP)
    {
        /*  Check if x is NaN. If it is, return NaN.                          */
        if (wx.bits.man0 || wx.bits.man1)
            return x;

        /*  x is infinity. Check if y is NaN or Inf.                          */
        if (wy.bits.expo == TMPL_FLOAT_NANINF_EXP)
        {
            /*  Check if y is NaN. If it is, return NaN.                      */
            if (wy.bits.man0 || wy.bits.man1)
                return y;

            /*  Both x and y are infinity. 4 special cases corresponding to   *
             *  North-East, North-West, South-West, and South-East.           */
            if (!wx.bits.sign && !wy.bits.sign)
                return tmpl_Pi_By_Four_F;
            else if (wx.bits.sign && !wy.bits.sign)
                return tmpl_Three_Pi_By_Four_F;
            else if (wx.bits.sign && wy.bits.sign)
                return -tmpl_Three_Pi_By_Four_F;
            else
                return -tmpl_Pi_By_Four_F;
        }

        /*  y is finite and x is infinite. The angle is 0 or pi.              */
        if (wx.bits.sign)
            return tmpl_One_Pi_F;
        else
            return 0.0F;
    }

    /*  Check if y is infinite or NaN.                                        */
    else if (wy.bits.expo == TMPL_FLOAT_NANINF_EXP)
    {
        /*  We've already checked that x is finite. Check if y is NaN.        */
        if (wy.bits.man0 || wy.bits.man1)
            return y;

        /*  y is infinite and x is finite. The angle is +/- pi/2.             */
        if (wy.bits.sign)
            return -tmpl_Pi_By_Two_F;
        else
            return tmpl_Pi_By_Two_F;
    }

    /*  Next special case, y = 0.                                             */
    else if (y == 0.0F)
    {
        /*  If x is negative, return Pi.                                      */
        if (wx.bits.sign)
        {
            /*  Preserve the sign of y. If y is a negative zero, return -Pi.  */
            if (wy.bits.sign)
                return -tmpl_One_Pi_F;
            else
                return tmpl_One_Pi_F;
        }

        /*  Otherwise, return 0. To preserve the sign of y, return y.         */
        else
            return y;
    }

    /*  Lastly, the case where x is zero to avoid division-by-zero.           */
    else if (x == 0.0F)
    {
        /*  y is not zero, so the answer is +/- pi/2.                         */
        if (wy.bits.sign)
            return -tmpl_Pi_By_Two_F;
        else
            return tmpl_Pi_By_Two_F;
    }

    /*  We have z = y/x. Compute the absolute value by setting sign to 0.     */
    w.r = wy.r / wx.r;
    w.bits.sign = 0x00U;

    /*  Small values, |z| < 1/32. Use the MacLaurin series to 6 terms.        */
    if (w.bits.expo < TMPL_FLOAT_BIAS - 4U)
        out = tmpl_Float_Arctan_Very_Small(w.r);

    /*  For |z| > 16, use the asymptotic expansion.                           */
    else if (w.bits.expo > TMPL_FLOAT_BIAS + 3U)
        out = tmpl_Float_Arctan_Asymptotic(w.r);

    /*  Otherwise use the lookup table to reduce. Note we have reduced to the *
     *  case where -4 <= expo <= 3, where expo is the exponent of z.          */
    else
    {
        /*  The table is indexed by values near 0.0625, 0.125, 0.25, 0.5, 1,  *
         *  2, 4, and 8. The index thus corresponds to 4 + expo, where expo   *
         *  is the exponent of the number z. Compute this. The exponent       *
         *  in the IEEE-754 representation of a number is offset by a bias.   *
         *  Subtract off this bias to compute the actual index.               */
        ind = (w.bits.expo + 4U) - TMPL_FLOAT_BIAS;

        /*  Get the corresponding values from the lookup tables.              */
        v = tmpl_atan_float_v[ind];
        atan_v = tmpl_atan_float_atan_of_v[ind];

        /*  Use 4.4.34 from Abramowitz and Stegun to compute the new argument.*/
        arg = (w.r - v) / (1.0F + w.r*v);
        out = atan_v + tmpl_Float_Arctan_Maclaurin(arg);
    }

    /*  Reduce to the case where x > 0 via atan2(y, -x) = pi - atan2(y, x).   */
    if (wx.bits.sign)
        out = tmpl_One_Pi_F - out;

    /*  Reduce to y > 0 via atan2(-y, x) = -atan2(y, x).                      */
    if (wy.bits.sign)
        return -out;
    else
        return out;
}
/*  End of tmpl_Float_Arctan.                                                 */

#else
/*  Else for #if TMPL_HAS_IEEE754_FLOAT == 1.                                 */

/*  Portable implementation of atan2.                                         */

/*  Single precision inverse tangent (atan2 equivalent).                      */
float tmpl_Float_Arctan2(float y, float x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    float z, arg, out, v, atan_v;
    unsigned int ind;

    /*  Special cases, NaN and INF.                                           */
    if (tmpl_Float_Is_NaN(x))
        return x;
    else if (tmpl_Float_Is_NaN(y))
        return y;
    else if (tmpl_Float_Is_Inf(x))
    {
        /*  x is infinity. Check if y is infinity as well.                    */
        if (tmpl_Float_Is_Inf(y))
        {
            /*  Both x and y are infinity. 4 special cases corresponding to   *
             *  North-East, North-West, South-West, and South-East.           */
            if (x > 0.0F && y > 0.0F)
                return tmpl_Pi_By_Four_F;
            else if (x < 0.0F && y > 0.0F)
                return tmpl_Three_Pi_By_Four_F;
            else if (x < 0.0F && y < 0.0F)
                return -tmpl_Three_Pi_By_Four_F;
            else
                return -tmpl_Pi_By_Four_F;
        }

        /*  y is finite and x is infinite. The angle is 0 or pi.              */
        if (x < 0.0F)
            return tmpl_One_Pi_F;
        else
            return 0.0F;
    }

    /*  Check if y is infinite or NaN.                                        */
    else if (tmpl_Float_Is_Inf(y))
    {
        /*  y is infinite and x is finite. The angle is +/- pi/2.             */
        if (x < 0.0F)
            return -tmpl_Pi_By_Two_F;
        else
            return tmpl_Pi_By_Two_F;
    }

    /*  Next special case, y = 0.                                             */
    else if (y == 0.0F)
    {
        /*  If x is negative, return Pi.                                      */
        if (x < 0.0F)
            return tmpl_One_Pi_F;

        /*  Otherwise, return 0. To preserve the sign of y, return y.         */
        else
            return y;
    }

    /*  Lastly, the case where x is zero to avoid division-by-zero.           */
    else if (x == 0.0F)
    {
        /*  y is not zero, so the answer is +/- pi/2.                         */
        if (y < 0.0F)
            return -tmpl_Pi_By_Two_F;
        else
            return tmpl_Pi_By_Two_F;
    }

    /*  We have z = y/x. Reduce by computing the absolute value of this.      */
    z = tmpl_Float_Abs(y / x);

    /*  For small values, z < 1/32, use the Maclaurin series to a few terms.  */
    if (z < 0.0625F)
    {
        out = tmpl_Float_Arctan_Very_Small(z);
        goto TMPL_FLOAT_ARCTAN2_FINISH;
    }

    /*  Otherwise compute the greatest power of two less than z.              */
    else if (z < 0.125F)
        ind = 0U;
    else if (z < 0.25F)
        ind = 1U;
    else if (z < 0.5F)
        ind = 2U;
    else if (z < 1.0F)
        ind = 3U;
    else if (z < 2.0F)
        ind = 4U;
    else if (z < 4.0F)
        ind = 5U;
    else if (z < 8.0F)
        ind = 6U;
    else if (z < 16.0F)
        ind = 7U;

    /*  For |x| > 16, use the asymptotic expansion.                           */
    else
    {
        out = tmpl_Float_Arctan_Asymptotic(z);
        goto TMPL_FLOAT_ARCTAN2_FINISH;
    }

    /*  Use the lookup table for arctan. Get the pre-computed values.         */
    v = tmpl_atan_float_v[ind];
    atan_v = tmpl_atan_float_atan_of_v[ind];

    /*  Compute the argument via formula 4.4.34 from Abramowitz and Stegun.   */
    arg = (z - v) / (1.0F + z*v);
    out = atan_v + tmpl_Float_Arctan_Maclaurin(arg);

    /*  Last step, perform the argument reduction. We computed |y/x| at the   *
     *  start but have not changed x or y so their signs are untouched.       *
     *  Inspect the signs of each to finish the computation.                  */
TMPL_FLOAT_ARCTAN2_FINISH:

    /*  Reduce to x > 0 via atan2(y, x) = pi - atan2(y, -x).                  */
    if (x < 0.0F)
        out = tmpl_One_Pi_F - out;

    /*  Reduce to y > 0 via atan2(y, x) = -atan2(-y, x).                      */
    if (y < 0.0F)
        return -out;
    else
        return out;
}
/*  End of tmpl_Float_Arctan.                                                 */

#endif
/*  End of #if TMPL_HAS_IEEE754_FLOAT == 1.                                   */

#endif
/*  End of #if TMPL_USE_MATH_ALGORITHMS == 1.                                 */