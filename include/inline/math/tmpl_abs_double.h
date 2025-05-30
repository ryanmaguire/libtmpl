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
 *                              tmpl_abs_double                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes f(x) = |x| at double precision.                              *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Abs                                                       *
 *  Purpose:                                                                  *
 *      Computes the absolute value of a real number.                         *
 *                   --                                                       *
 *                  |   x,  x >= 0                                            *
 *          |x|  =  |  -x,  else                                              *
 *                   --                                                       *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number, the argument for |x|.                              *
 *  Output:                                                                   *
 *      abs_x (double):                                                       *
 *          The absolute value of x.                                          *
 *  IEEE-754 Version:                                                         *
 *      Called Functions:                                                     *
 *          None.                                                             *
 *      Method:                                                               *
 *          Set the sign bit to 0. A 64-bit double is represented by:         *
 *                                                                            *
 *          s eeeeeeeeeee xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*
 *          - ----------- ----------------------------------------------------*
 *         sign exponent                mantissa                              *
 *                                                                            *
 *          The absolute value can be computed by setting s to 0. Note, this  *
 *          method will work for NaN and inf, and the output will be          *
 *          "positive" NaN and positive infinity, respectively.               *
 *      Error:                                                                *
 *          Based on 1,051,958,476 samples with -10^6 < x < 10^6.             *
 *              max relative error: 0.0                                       *
 *              rms relative error: 0.0                                       *
 *              max absolute error: 0.0                                       *
 *              rms absolute error: 0.0                                       *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          None.                                                             *
 *      Method:                                                               *
 *          Use an if-then statement to check if the input is negative,       *
 *          returning x for non-negative and -x otherwise.                    *
 *      Error:                                                                *
 *          Based on 1,051,958,476 samples with -10^6 < x < 10^6.             *
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
 *          Header file containing TMPL_INLINE_DECL macro.                    *
 *  2.) tmpl_ieee754_double.h:                                                *
 *          Header file containing the IEEE data type.                        *
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
 *  2022/05/05: Ryan Maguire                                                  *
 *      Adding inline support. This is about 2x faster. It is now the default *
 *      configuration in the Makefile.                                        *
 *  2022/05/31: Ryan Maguire                                                  *
 *      Added benchmarks.                                                     *
 *  2022/09/13: Ryan Maguire                                                  *
 *      Removed math.h version (fabs alias). This version is now a macro for  *
 *      the fabs function in tmpl_math.h (only if TMPL_USE_MATH_ALGORITHMS is *
 *      set to zero).                                                         *
 *  2023/04/18: Ryan Maguire                                                  *
 *      Changed src/math/tmpl_abs_double.c to just include this file.         *
 *  2024/10/23: Ryan Maguire                                                  *
 *      Added clarification that the portable method does not change signed   *
 *      zeros. That is, negative zero will output negative zero.              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ABS_DOUBLE_H
#define TMPL_ABS_DOUBLE_H

/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  Only used if libtmpl algorithms are requested.                            */
#if TMPL_USE_MATH_ALGORITHMS == 1

/*  Location of the TMPL_HAS_IEEE754_DOUBLE macro and IEEE data type.         */
#include <libtmpl/include/types/tmpl_ieee754_double.h>

/*  Check for IEEE-754 support.                                               */
#if TMPL_HAS_IEEE754_DOUBLE == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  Double precision absolute value function (fabs equivalent).               */
TMPL_INLINE_DECL
double tmpl_Double_Abs(double x)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_IEEE754_Double w;

    /*  Set the double part of the word to the input x.                       */
    w.r = x;

    /*  Set the sign bit to zero, indicating positive.                        */
    w.bits.sign = 0x0U;

    /*  Return the double part of the union.                                  */
    return w.r;
}
/*  End of tmpl_Double_Abs.                                                   */

#else
/*  Else for #if TMPL_HAS_IEEE754_DOUBLE == 1.                                */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Lacking IEEE-754 support, an if-then statement works and is portable.     */

/*  Double precision absolute value function (fabs equivalent).               */
TMPL_INLINE_DECL
double tmpl_Double_Abs(double x)
{
    /*  For negative inputs, flip the sign and make it positive.              */
    if (x < 0.0)
        return -x;

    /*  Otherwise return the input. Note, "negative" zero will still be       *
     *  negative. The portable method is unable to detect signed zeros.       */
    return x;
}
/*  End of tmpl_Double_Abs.                                                   */

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE == 1.                                  */

#endif
/*  End of #if TMPL_USE_MATH_ALGORITHMS == 1.                                 */

#endif
/*  End of include guard.                                                     */
