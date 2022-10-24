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
 *                            tmpl_copysign_ldouble                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes f(x, y) = |x|*sgn(y), where sgn is the sign function.        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Copysign                                                 *
 *  Purpose:                                                                  *
 *      Copies the sign of y into x.                                          *
 *  Arguments:                                                                *
 *      x (long double):                                                      *
 *          A real number.                                                    *
 *      y (long double):                                                      *
 *          A real number, the sign of which will be copied to x.             *
 *  Output:                                                                   *
 *      cpysgn (long double):                                                 *
 *          The value |x|*sgn(y).                                             *
 *  64-bit double / 80-bit extended / 128-bit quadruple:                      *
 *      Called Functions:                                                     *
 *          None.                                                             *
 *      Method:                                                               *
 *          Copy the sign bit of y into x.                                    *
 *      Error:                                                                *
 *          Based on 843,061,299 samples with -10^2 < x, y < 10^2.            *
 *              max relative error: 0.0                                       *
 *              rms relative error: 0.0                                       *
 *              max absolute error: 0.0                                       *
 *              rms absolute error: 0.0                                       *
 *  128-bit double-double:                                                    *
 *      Called Functions:                                                     *
 *          None.                                                             *
 *      Method:                                                               *
 *          Compare the signs of the high word, negating x if needed.         *
 *      Error:                                                                *
 *          Based on 10,000,000 samples with -10^2 < x < 10^2.                *
 *              max relative error: 0.0                                       *
 *              rms relative error: 0.0                                       *
 *              max absolute error: 0.0                                       *
 *              rms absolute error: 0.0                                       *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_LDouble_Abs (tmpl_math.h):                                   *
 *              Computes the absolute value of a real number.                 *
 *      Method:                                                               *
 *          Use an if-then statement to check the sign of y.                  *
 *      Error:                                                                *
 *          Based on 843,061,299 samples with -10^2 < x, y < 10^2.            *
 *              max relative error: 0.0                                       *
 *              rms relative error: 0.0                                       *
 *              max absolute error: 0.0                                       *
 *              rms absolute error: 0.0                                       *
 *  Notes:                                                                    *
 *      If IEEE-754 is not supported and y is zero, x is returned as is.      *
 *      IEEE-754 has signed zeros, other float representations may not.       *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_USE_INLINE macro.                     *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 24, 2022                                              *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2022/10/24: Ryan Maguire                                                  *
 *      Added license.                                                        *
 ******************************************************************************/

/*  Location of the TMPL_USE_INLINE macro.                                    */
#include <libtmpl/include/tmpl_config.h>

/*  This file is only compiled if inline support is not requested.            */
#if TMPL_USE_INLINE != 1

/*  Header file where the prototype for the function is defined.              */
#include <libtmpl/include/tmpl_math.h>

/*  Only implement this if the user requested libtmpl algorithms.             */
#if TMPL_USE_MATH_ALGORITHMS == 1

/*  Check for IEEE-754 support.                                               */
#if TMPL_HAS_IEEE754_LDOUBLE == 1

/*  64-bit double, 80-bit extended, and 128-bit quadruple implementations     *
 *  of long double use the same idea: Copy the sign bit of y to x. The        *
 *  double-double implementation of long double needs to be more careful.     */
#if TMPL_LDOUBLE_ENDIANNESS != TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_BIG_ENDIAN && \
    TMPL_LDOUBLE_ENDIANNESS != TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_LITTLE_ENDIAN

/******************************************************************************
 *        64-Bit Double / 80-Bit Extended / 128-bit Quadruple Versions        *
 ******************************************************************************/

/*  Long double precision coypsign function (coypsignl equivalent).           */
long double tmpl_LDouble_Copysign(long double x, long double y)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_IEEE754_LDouble wx, wy;

    /*  Set the long double part of the words to the inputs.                  */
    wx.r = x;
    wy.r = y;

    /*  Set the sign bit of x to the sign bit of y.                           */
    wx.bits.sign = wy.bits.sign;

    /*  Return the long double part of the union.                             */
    return wx.r;
}
/*  End of tmpl_LDouble_Copysign.                                             */

#else
/*  Else for 64-bit double / 80-bit extended / 128-bit quadruple versions.    */

/******************************************************************************
 *                       128-bit Double-Double Version                        *
 ******************************************************************************/

/*  Long double precision coypsign function (coypsignl equivalent).           */
long double tmpl_LDouble_Copysign(long double x, long double y)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_IEEE754_LDouble wx, wy;

    /*  Set the long double part of the words to the inputs.                  */
    wx.r = x;
    wy.r = y;

    /*  Compare the sign bits, negating if needed.                            */
    if (wx.bits.signa != wy.bits.signa)
        wx.r = -wx.r;

    /*  Return the long double part of the union.                             */
    return wx.r;
}
/*  End of tmpl_LDouble_Copysign.                                             */

#endif
/*  End of 128-bit double-double version.                                     */

#else
/*  Else for #if TMPL_HAS_IEEE754_LDOUBLE == 1.                               */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Lacking IEEE-754 support, an if-then statement works and is portable.     */
long double tmpl_LDouble_Copysign(long double x, long double y)
{
    /*  If y is negative, compute -|x|.                                       */
    if (y < 0.0L)
        return -tmpl_LDouble_Abs(x);

    /*  If y is positive, compute |x|.                                        */
    else if (0.0L < y)
        return tmpl_LDouble_Abs(x);

    /*  And lastly, if y is zero, return x.                                   */
    else
        return x;
}
/*  End of tmpl_LDouble_Copysign.                                             */

#endif
/*  End of #if TMPL_HAS_IEEE754_LDOUBLE == 1.                                 */

#endif
/*  End of #if TMPL_USE_MATH_ALGORITHMS == 1.                                 */

#endif
/*  End of #if TMPL_USE_INLINE != 1.                                          */
