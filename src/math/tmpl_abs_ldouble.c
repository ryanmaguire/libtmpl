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
 *                              tmpl_abs_ldouble                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes f(x) = |x| at long double precision.                         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Abs                                                      *
 *  Purpose:                                                                  *
 *      Computes the absolute value of a real number.                         *
 *                   --                                                       *
 *                  |   x,  x >= 0                                            *
 *          |x|  =  |  -x,  else                                              *
 *                   --                                                       *
 *  Arguments:                                                                *
 *      x (long double):                                                      *
 *          A real number, the argument for |x|.                              *
 *  Output:                                                                   *
 *      abs_x (long double):                                                  *
 *          The absolute value of x.                                          *
 *  64-bit Double / 80-bit Extended / 128-bit Quadruple Versions:             *
 *      Called Functions:                                                     *
 *          None.                                                             *
 *      Method:                                                               *
 *          The absolute value can be computed by setting s to 0. Note, this  *
 *          method will work for NaN and inf, and the output will be          *
 *          "positive" NaN and positive infinity, respectively.               *
 *      Error:                                                                *
 *          Based on 525,979,238 samples with -10^6 < x < 10^6.               *
 *              max relative error: 0.0                                       *
 *              rms relative error: 0.0                                       *
 *              max absolute error: 0.0                                       *
 *              rms absolute error: 0.0                                       *
 *  128-bit Double-Double Version:                                            *
 *      Called Functions:                                                     *
 *          None.                                                             *
 *      Method:                                                               *
 *          Given:                                                            *
 *              x = x_hi + x_lo                                               *
 *          we compute:                                                       *
 *              abs_x = abs_hi + abs_lo                                       *
 *          as follows. If x_hi and x_lo have the same sign, then:            *
 *              |x_hi + x_lo| = |x_hi| + |x_lo|                               *
 *          so abs_hi = |x_hi| and abs_lo = |x_lo|. If x_hi and x_lo have     *
 *          different signs, then:                                            *
 *              |x_hi + x_lo| = |x_hi| - |x_lo|                               *
 *          So abs_hi = |x_hi| and abs_lo = -|x_lo|. In both cases,           *
 *          abs_hi = |x_hi|. To compute this we just set the sign bit of x_hi *
 *          to zero. abs_lo depends on whether x_hi and x_lo have the same    *
 *          sign. This can be computed via the exclusive or, or XOR. The sign *
 *          of abs_lo is the exclusive or of the signs of x_hi and x_lo.      *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          None.                                                             *
 *      Method:                                                               *
 *          Use an if-then statement to check if the input is positive,       *
 *          returning x for non-negative and -x otherwise.                    *
 *      Error:                                                                *
 *          Based on 525,979,238 samples with -10^6 < x < 10^6.               *
 *              max relative error: 0.0                                       *
 *              rms relative error: 0.0                                       *
 *              max absolute error: 0.0                                       *
 *              rms absolute error: 0.0                                       *
 *  Notes:                                                                    *
 *      If IEEE-754 is not supported and if the input is NaN one may get      *
 *      +/- NaN (which is still NaN). This is because NaN always              *
 *      evaluates to false when a comparison is made (==, <, >, etc.).        *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_USE_INLINE macro.                     *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 16, 2021                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2020/11/01: Ryan Maguire                                                  *
 *      Created file (Wellesley College for librssringoccs).                  *
 *  2020/12/08: Ryan Maguire                                                  *
 *      Frozen for v1.3 of librssringoccs.                                    *
 *  2021/02/16: Ryan Maguire                                                  *
 *      Copied file from rss_ringoccs.                                        *
 *  2021/02/24: Ryan Maguire                                                  *
 *      Added IEEE 754 code for computing the absolute value function.        *
 *  2021/09/10: Ryan Maguire                                                  *
 *      Moved float and long double to their own files.                       *
 *  2022/03/01: Ryan Maguire                                                  *
 *      Added check for TMPL_USE_MATH_ALGORITHMS macro. This function will    *
 *      use fabs from math.h if TMPL_USE_MATH_ALGORITHMS is not 1.            *
 *  2022/09/12: Ryan Maguire                                                  *
 *      Added inline support.                                                 *
 *  2022/09/13: Ryan Maguire                                                  *
 *      Remove math.h version (fabsl alias). This version is now a macro for  *
 *      the fabsl function in tmpl_math.h (only if TMPL_USE_MATH_ALGORITHMS   *
 *      is set to zero).                                                      *
 ******************************************************************************/

/*  Location of the TMPL_USE_INLINE macro.                                    */
#include <libtmpl/include/tmpl_config.h>

/*  This file is only compiled if inline support is not requested.            */
#if TMPL_USE_INLINE != 1

/*  Header file where the prototype for the function is defined.              */
#include <libtmpl/include/tmpl_math.h>

/*  Only implement this if the user requested libtmpl algorithms.             */
#if TMPL_USE_MATH_ALGORITHMS == 1

/*  Check for IEEE-754 long double support.                                   */
#if TMPL_HAS_IEEE754_LDOUBLE == 1

/*  64-bit double, 80-bit extended, and 128-bit quadruple implementations     *
 *  of long double use the same idea: Set the sign bit to zero. The           *
 *  double-double implementation of long double needs to be more careful.     */
#if TMPL_LDOUBLE_ENDIANNESS != TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_BIG_ENDIAN && \
    TMPL_LDOUBLE_ENDIANNESS != TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_LITTLE_ENDIAN

/******************************************************************************
 *        64-Bit Double / 80-Bit Extended / 128-bit Quadruple Versions        *
 ******************************************************************************/

/*  Long double precision absolute value function (fabsl equivalent).         */
long double tmpl_LDouble_Abs(long double x)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_IEEE754_LDouble w;

    /*  Set the long double part of w to the input.                           */
    w.r = x;

    /*  Set the sign bit to 0, indicating positive.                           */
    w.bits.sign = 0x0U;

    /*  Return the long double part of the union.                             */
    return w.r;
}
/*  End of tmpl_LDouble_Abs.                                                  */

#else
/*  Else for 64-bit double / 80-bit extended / 128-bit quadruple versions.    */

/******************************************************************************
 *                       128-bit Double-Double Version                        *
 ******************************************************************************/

/*  Long double precision absolute value function (fabsl equivalent).         */
long double tmpl_LDouble_Abs(long double x)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_IEEE754_LDouble w;

    /*  Set the long double part of w to the input.                           */
    w.r = x;

    /*  For double-double we have x = xhi + xlo. Define                       *
     *  abs_x = |x| = abs_xhi + abs_xlo. If xhi and xlo have the same sign,   *
     *  |x| = |xhi| + |xlo| and so abs_xhi = |xhi| and abs_xlo = |xlo|. If    *
     *  xhi and xlo have different signs, |x| = |xhi| - |xlo| so              *
     *  abs_xhi = |xhi| and abs_xlo = -|xlo|. In both cases abs_xhi = |xhi|.  *
     *  The sign of abs_xlo depends on the signs of xhi and xlo. That is,     *
     *  whether or not they are the same. Indeed, the sign of abs_xlo is the  *
     *  exlusive or, also called XOR, of the signs of xhi and xlo. Use this.  */
    w.bits.signb = w.bits.signa ^ w.bits.signb;
    w.bits.signa = 0x0U;

    /*  Return the long double part of the union.                             */
    return w.r;
}
/*  End of tmpl_LDouble_Abs.                                                  */

#endif
/*  End of 128-bit double-double version.                                     */

#else
/*  Else for #if TMPL_HAS_IEEE754_LDOUBLE == 1.                               */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Lacking IEEE-754 support, an if-then statement works and is portable.     */

/*  Long double precision absolute value function (fabsl equivalent).         */
long double tmpl_LDouble_Abs(long double x)
{
    /*  If x is positive return it, otherwise return its negative.            */
    if (x >= 0.0L)
        return x;
    else
        return -x;
}
/*  End of tmpl_LDouble_Abs.                                                  */

#endif
/*  End of #if TMPL_HAS_IEEE754_LDOUBLE == 1.                                 */

#endif
/*  End of #if TMPL_USE_MATH_ALGORITHMS == 1.                                 */

#endif
/*  End of #if TMPL_USE_INLINE != 1.                                          */
