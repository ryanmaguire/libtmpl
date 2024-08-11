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
 *                            tmpl_copysign_double                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes f(x, y) = |x|*sgn(y), where sgn is the sign function.        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Copysign                                                  *
 *  Purpose:                                                                  *
 *      Copies the sign of y into x.                                          *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *      y (double):                                                           *
 *          A real number, the sign of which will be copied to x.             *
 *  Output:                                                                   *
 *      cpysgn (double):                                                      *
 *          The value |x|*sgn(y).                                             *
 *  IEEE-754 Version:                                                         *
 *      Called Functions:                                                     *
 *          None.                                                             *
 *      Method:                                                               *
 *          Copy the sign bit of y into x. A 64-bit double is represented by: *
 *                                                                            *
 *          s eeeeeeeeeee xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*
 *          - ----------- ----------------------------------------------------*
 *         sign exponent                mantissa                              *
 *                                                                            *
 *          Copysign(x, y) can be computing by setting the sign bit of x      *
 *          equal to the sign bit of y.                                       *
 *      Error:                                                                *
 *          Based on 1,686,122,598 samples with -100 < x, y < 100.            *
 *              max relative error: 0.0                                       *
 *              rms relative error: 0.0                                       *
 *              max absolute error: 0.0                                       *
 *              rms absolute error: 0.0                                       *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_math.h:                                                      *
 *              tmpl_Double_Abs:                                              *
 *                  Computes the absolute value of a real number.             *
 *      Method:                                                               *
 *          Use an if-then statement to check the sign of y.                  *
 *      Error:                                                                *
 *          Based on 1,686,122,598 samples with -100 < x, y < 100.            *
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
 *  2023/06/12: Ryan Maguire                                                  *
 *      Changed src/math/tmpl_copysign_double.c to include this file.         *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COPYSIGN_DOUBLE_H
#define TMPL_COPYSIGN_DOUBLE_H

/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  Location of the TMPL_HAS_IEEE754_DOUBLE macro and IEEE data type.         */
#include <libtmpl/include/tmpl_ieee754_double.h>

/*  Check for IEEE-754 support.                                               */
#if TMPL_HAS_IEEE754_DOUBLE == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  Double precision copysign function (copysign equivalent).                 */
TMPL_INLINE_DECL
double tmpl_Double_Copysign(double x, double y)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_IEEE754_Double wx, wy;

    /*  Set the double part of the words to the inputs.                       */
    wx.r = x;
    wy.r = y;

    /*  Set the sign bit of x to the sign bit of y.                           */
    wx.bits.sign = wy.bits.sign;

    /*  Return the double part of the union.                                  */
    return wx.r;
}
/*  End of tmpl_Double_Copysign.                                              */

#else
/*  Else for #if TMPL_HAS_IEEE754_DOUBLE == 1.                                */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Lacking IEEE-754 support, an if-then statement works and is portable.     */
TMPL_INLINE_DECL
double tmpl_Double_Copysign(double x, double y)
{
    /*  If y is negative, compute -|x|.                                       */
    if (y < 0.0)
        return -tmpl_Double_Abs(x);

    /*  If y is positive, compute |x|.                                        */
    else if (0.0 < y)
        return tmpl_Double_Abs(x);

    /*  And lastly, if y is zero, return x.                                   */
    return x;
}
/*  End of tmpl_Double_Copysign.                                              */

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE == 1.                                  */

#endif
/*  End of include guard.                                                     */
