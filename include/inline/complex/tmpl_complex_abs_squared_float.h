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
 *                       tmpl_complex_abs_squared_float                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for f(z) = |z|^2.                            *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CFloat_Abs_Squared                                               *
 *  Purpose:                                                                  *
 *      Computes the square of the absolute value, f(z) = |z|^2:              *
 *                                                                            *
 *          f(z) = f(x + iy) = x^2 + y^2                                      *
 *                                                                            *
 *  Arguments:                                                                *
 *      z (const tmpl_ComplexFloat):                                          *
 *          A complex number.                                                 *
 *  Output:                                                                   *
 *      abs_sq_z (float):                                                     *
 *          The square of the absolute value of z.                            *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Extract the real and imaginary parts of z and return x^2 + y^2.       *
 *  Error:                                                                    *
 *      Based on 268,435,456 random samples:                                  *
 *          Max Relative Error: 0.000000e+00                                  *
 *          RMS Relative Error: 0.000000e+00                                  *
 *  Notes:                                                                    *
 *      1.) This function is susceptible to underflow and overflow. For very  *
 *          small arguments (say, less than sqrt(FLT_MIN)) or very large      *
 *          arguments (greater than sqrt(FLT_MAX)), the function f(z) = |z|^2 *
 *          will underflow and overflow, respectively. This function does not *
 *          attempt to mitigate this.                                         *
 *                                                                            *
 *      2.) There are no checks for NaN or infinity. NaN inputs will produce  *
 *          NaN, and infinity (positive or negative) will output infinity.    *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file where the macro TMPL_INLINE_DECL is found.            *
 *  2.) tmpl_complex_float.h:                                                 *
 *          Header providing single precision complex numbers.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 16, 2021                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2020/11/30: Ryan Maguire                                                  *
 *      Wrote routines for the complex abs squared function (Wellesley        *
 *      College for librssringoccs).                                          *
 *  2020/12/02: Ryan Maguire                                                  *
 *      Moved functions here from rss_ringoccs_complex_abs.c                  *
 *      Frozen for v1.3.                                                      *
 *  2021/02/16: Ryan Maguire                                                  *
 *      Copied from rss_ringoccs.                                             *
 *      Edited to make it compatible with libtmpl.                            *
 *      Soft freeze for alpha release of libtmpl.                             *
 *  2021/05/11: Ryan Maguire                                                  *
 *      Hard freeze for alpha release of libtmpl. Reviewed code and comments. *
 *      No more changes unless something breaks.                              *
 *  2022/04/28: Ryan Maguire                                                  *
 *      Added this function as an optional inline function.                   *
 *  2023/02/06: Ryan Maguire                                                  *
 *      Moved float and long double to their own files.                       *
 *  2023/07/06: Ryan Maguire                                                  *
 *      Changed src/complex/tmpl_complex_abs_squared_float.c to use this.     *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COMPLEX_ABS_SQUARED_FLOAT_H
#define TMPL_COMPLEX_ABS_SQUARED_FLOAT_H

/*  The TMPL_INLINE_DECL macro is found here.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Complex numbers provided here.                                            */
#include <libtmpl/include/types/tmpl_complex_float.h>

/*  Single precision abs squared function.                                    */
TMPL_INLINE_DECL
float tmpl_CFloat_Abs_Squared(const tmpl_ComplexFloat z)
{
    /*  Use the Pythagorean formula |z|^2 = x^2 + y^2 and return.             */
    return z.dat[0]*z.dat[0] + z.dat[1]*z.dat[1];
}
/*  End of tmpl_CFloat_Abs_Squared.                                           */

#endif
/*  End of include guard.                                                     */
