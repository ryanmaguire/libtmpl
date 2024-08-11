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
 *                              tmpl_dist_float                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the distance from x to y on the number line.                 *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Dist                                                       *
 *  Purpose:                                                                  *
 *      Computes the Euclidean distance d(x, y) = |x - y|.                    *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *      y (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      dist (float):                                                         *
 *          The distance |x - y|.                                             *
 *  IEEE-754 Version:                                                         *
 *      Called Functions:                                                     *
 *          None.                                                             *
 *      Method:                                                               *
 *          Computes x - y and then sets the sign bit to zero.                *
 *      Error:                                                                *
 *          Based on 3,372,245,197 samples with -100 < x, y < 100.            *
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
 *          Based on 3,372,245,197 samples with -100 < x, y < 100.            *
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
 *      Changed src/math/tmpl_dist_float.c to include this file.              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_DIST_FLOAT_H
#define TMPL_DIST_FLOAT_H

/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  Location of the TMPL_HAS_IEEE754_FLOAT macro and IEEE data type.          */
#include <libtmpl/include/tmpl_ieee754_float.h>

/*  Check for IEEE-754 support.                                               */
#if TMPL_HAS_IEEE754_FLOAT == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  Single precision 1-D distance function.                                   */
TMPL_INLINE_DECL
float tmpl_Float_Dist(float x, float y)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_IEEE754_Float w;

    /*  Set the float part of the word to the signed distance x - y.          */
    w.r = x - y;

    /*  Set the sign bit to zero to compute the absolute value.               */
    w.bits.sign = 0x00U;

    /*  Return the float part of the union.                                   */
    return w.r;
}
/*  End of tmpl_Float_Dist.                                                   */

#else
/*  Else for #if TMPL_HAS_IEEE754_FLOAT == 1.                                 */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Lacking IEEE-754 support, an if-then statement works and is portable.     */
TMPL_INLINE_DECL
float tmpl_Float_Dist(float x, float y)
{
    /*  If x < y we have |x - y| = y - x. Compute this.                       */
    if (x < y)
        return y - x;

    /*  Otherwise |x - y| = x - y. Compute this and return.                   */
    return x - y;
}
/*  End of tmpl_Float_Dist.                                                   */

#endif
/*  End of #if TMPL_HAS_IEEE754_FLOAT == 1.                                   */

#endif
/*  End of include guard.                                                     */
