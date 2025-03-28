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
 *                              tmpl_dist_ldouble                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the distance from x to y on the number line.                 *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Dist                                                     *
 *  Purpose:                                                                  *
 *      Computes the Euclidean distance d(x, y) = |x - y|.                    *
 *  Arguments:                                                                *
 *      x (long double):                                                      *
 *          A real number.                                                    *
 *      y (long double):                                                      *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      dist (long double):                                                   *
 *          The distance |x - y|.                                             *
 *  64-bit double / 80-bit extended / 128-bit quadruple:                      *
 *      Called Functions:                                                     *
 *          None.                                                             *
 *      Method:                                                               *
 *          Computes x - y and then sets the sign bit to zero.                *
 *      Error:                                                                *
 *          Based on 843,061,299 samples with -100 < x, y < 100.              *
 *              max relative error: 0.0                                       *
 *              rms relative error: 0.0                                       *
 *              max absolute error: 0.0                                       *
 *              rms absolute error: 0.0                                       *
 *  128-bit double-double:                                                    *
 *      Called Functions:                                                     *
 *          None.                                                             *
 *      Method:                                                               *
 *          Compute x - y and then compute the absolute value of this.        *
 *      Error:                                                                *
 *          Based on 10,000,000 samples with -100 < x < 100.                  *
 *              max relative error: 0.0                                       *
 *              rms relative error: 0.0                                       *
 *              max absolute error: 0.0                                       *
 *              rms absolute error: 0.0                                       *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          None.                                                             *
 *      Method:                                                               *
 *          Compute y - x if x < y and x - y otherwise.                       *
 *      Error:                                                                *
 *          Based on 843,061,299 samples with -10^2 < x, y < 10^2.            *
 *              max relative error: 0.0                                       *
 *              rms relative error: 0.0                                       *
 *              max absolute error: 0.0                                       *
 *              rms absolute error: 0.0                                       *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_INLINE_DECL macro.                    *
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
 *  2023/06/13: Ryan Maguire                                                  *
 *      Changed src/math/tmpl_dist_ldouble.c to include this file.            *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_DIST_LDOUBLE_H
#define TMPL_DIST_LDOUBLE_H

/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  Location of the TMPL_HAS_IEEE754_LDOUBLE macro and IEEE data type.        */
#include <libtmpl/include/types/tmpl_ieee754_ldouble.h>

/*  Check for IEEE-754 support.                                               */
#if TMPL_HAS_IEEE754_LDOUBLE == 1

/*  64-bit double, 80-bit extended, and 128-bit quadruple implementations     *
 *  of long double use the same idea. Double-Double is different.             */
#if TMPL_LDOUBLE_TYPE != TMPL_LDOUBLE_DOUBLEDOUBLE

/******************************************************************************
 *        64-Bit Double / 80-Bit Extended / 128-bit Quadruple Versions        *
 ******************************************************************************/

/*  Long double precision 1-D distance function.                              */
TMPL_INLINE_DECL
long double tmpl_LDouble_Dist(long double x, long double y)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_IEEE754_LDouble w;

    /*  Set the long double part of the word to the signed distance x - y.    */
    w.r = x - y;

    /*  Set the sign bit to zero to compute the absolute value.               */
    w.bits.sign = 0x00U;

    /*  Return the long double part of the union.                             */
    return w.r;
}
/*  End of tmpl_LDouble_Dist.                                                 */

#else
/*  Else for 64-bit double / 80-bit extended / 128-bit quadruple versions.    */

/******************************************************************************
 *                       128-bit Double-Double Version                        *
 ******************************************************************************/

/*  Long double precision 1-D distance function.                              */
TMPL_INLINE_DECL
long double tmpl_LDouble_Dist(long double x, long double y)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_IEEE754_LDouble w;

    /*  Set the long double part of the word to the signed distance x - y.    */
    w.r = x - y;

    /*  Compute the absolute value of the double-double by setting the low    *
     *  word's sign to the XOR of the two signs, and the high word's sign to  *
     *  zero. See tmpl_abs_ldouble.h comments for more.                       */
    w.bits.signl = w.bits.sign ^ w.bits.signl;
    w.bits.sign = 0x00U;

    /*  Return the long double part of the union.                             */
    return w.r;
}
/*  End of tmpl_LDouble_Dist.                                                 */

#endif
/*  End of 128-bit double-double version.                                     */

#else
/*  Else for #if TMPL_HAS_IEEE754_LDOUBLE == 1.                               */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Lacking IEEE-754 support, an if-then statement works and is portable.     */
TMPL_INLINE_DECL
long double tmpl_LDouble_Dist(long double x, long double y)
{
    /*  If x < y we have |x - y| = y - x. Compute this.                       */
    if (x < y)
        return y - x;

    /*  Otherwise |x - y| = x - y. Compute this and return.                   */
    return x - y;
}
/*  End of tmpl_LDouble_Dist.                                                 */

#endif
/*  End of #if TMPL_HAS_IEEE754_LDOUBLE == 1.                                 */

#endif
/*  End of include guard.                                                     */
