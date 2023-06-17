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
 *                       tmpl_positive_difference_float                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the positive difference of two numbers, max(x-y, 0).         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Positive_Difference                                        *
 *  Purpose:                                                                  *
 *      Computes max(x-y, 0). Equivalent to the C99 fdimf function.           *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *      y (float):                                                            *
 *          Another real number.                                              *
 *  Output:                                                                   *
 *      fdim_xy (float):                                                      *
 *          The positive difference of x and y, max(x-y, 0).                  *
 *  IEEE-754 Version:                                                         *
 *      Called Functions:                                                     *
 *          None.                                                             *
 *      Method:                                                               *
 *          Check if either input is NaN, returning NaN if so. Otherwise      *
 *          compute max(x-y, 0).                                              *
 *      Error:                                                                *
 *          Based on 4,334,124,512 samples with -100 < x, y < 100.            *
 *              max relative error: 0.0                                       *
 *              rms relative error: 0.0                                       *
 *              max absolute error: 0.0                                       *
 *              rms absolute error: 0.0                                       *
 *          Values assume 100% accuracy of glibc. Actual error in glibc is    *
 *          less than 1 ULP (~1 x 10^-7).                                     *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_math.h:                                                      *
 *              tmpl_Float_Is_NaN:                                            *
 *                  Determines if a float is Not-a-Number.                    *
 *      Method:                                                               *
 *          Same as the IEEE-754 method, but uses tmpl_Float_Is_NaN to check  *
 *          if either input is not-a-number.                                  *
 *      Error:                                                                *
 *          Based on 4,334,124,512 samples with -100 < x, y < 100.            *
 *              max relative error: 0.0                                       *
 *              rms relative error: 0.0                                       *
 *              max absolute error: 0.0                                       *
 *              rms absolute error: 0.0                                       *
 *          Values assume 100% accuracy of glibc. Actual error in glibc is    *
 *          less than 1 ULP (~1 x 10^-7).                                     *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_INLINE_DECL macro.                    *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 12, 2023                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_POSITIVE_DIFFERENCE_FLOAT_H
#define TMPL_POSITIVE_DIFFERENCE_FLOAT_H

/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  Header file where the prototype for the function is defined.              */
#include <libtmpl/include/tmpl_math.h>

/*  Check for IEEE-754 support.                                               */
#if TMPL_HAS_IEEE754_FLOAT == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  Single precision positive difference (fdimf equivalent).                  */
TMPL_INLINE_DECL
float tmpl_Float_Positive_Difference(float x, float y)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_Float wx, wy;

    /*  Set the float part of the words to the inputs.                        */
    wx.r = x;
    wy.r = y;

    /*  Check if x is NaN. Return NaN if it is.                               */
    if (TMPL_FLOAT_IS_NOT_A_NUMBER(wx))
        return x;

    /*  Same check for y.                                                     */
    if (TMPL_FLOAT_IS_NOT_A_NUMBER(wy))
        return y;

    /*  Otherwise compute the positive difference. If y is greater than or    *
     *  equal to x, the positive difference is zero.                          */
    if (y >= x)
        return 0.0F;

    /*  Lastly, if x > y, the positive difference is the difference x - y.    */
    return x - y;
}
/*  End of tmpl_Float_Positive_Difference.                                    */

#else
/*  Else for #if TMPL_HAS_IEEE754_FLOAT == 1.                                 */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Single precision positive difference (fdimf equivalent).                  */
TMPL_INLINE_DECL
float tmpl_Float_Positive_Difference(float x, float y)
{
    /*  Check if x is NaN, returning NaN if so.                               */
    if (tmpl_Float_Is_NaN(x))
        return x;

    /*  Same check for y.                                                     */
    else if (tmpl_Float_Is_NaN(y))
        return y;

    /*  Otherwise compute the positive difference. If y is greater than or    *
     *  equal to x, the positive difference is zero.                          */
    if (y >= x)
        return 0.0F;

    /*  Lastly, if x > y, the positive difference is the difference x - y.    */
    return x - y;
}
/*  End of tmpl_Float_Positive_Difference.                                    */

#endif
/*  End of #if TMPL_HAS_IEEE754_FLOAT == 1.                                   */

#endif
/*  End of include guard.                                                     */
