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
 *                           tmpl_dist_float_inline                           *
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
 *          Based on 3,372,245,196 samples with -10^2 < x, y < 10^2.          *
 *              max relative error: 0.0                                       *
 *              rms relative error: 0.0                                       *
 *              max absolute error: 0.0                                       *
 *              rms absolute error: 0.0                                       *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_Float_Abs (tmpl_math.h):                                     *
 *              Computes the absolute value of a real number.                 *
 *      Method:                                                               *
 *          Compute x - y and pass the result to tmpl_Float_Abs.              *
 *      Error:                                                                *
 *          Based on 3,372,245,196 samples with -10^2 < x, y < 10^2.          *
 *              max relative error: 0.0                                       *
 *              rms relative error: 0.0                                       *
 *              max absolute error: 0.0                                       *
 *              rms absolute error: 0.0                                       *
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

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_MATH_DIST_FLOAT_INLINE_H
#define TMPL_MATH_DIST_FLOAT_INLINE_H

/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  This code is only used if inline code is requested. Check TMPL_USE_INLINE.*/
#if TMPL_USE_INLINE == 1

/*  Header file where the prototype for the function is defined.              */
#include <libtmpl/include/tmpl_math.h>

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
    /*  Pass the difference to the absolute value function and return.        */
    return tmpl_Float_Abs(x - y);
}
/*  End of tmpl_Float_Dist.                                                   */

#endif
/*  End of #if TMPL_HAS_IEEE754_FLOAT == 1.                                   */

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

#endif
/*  End of include guard.                                                     */
