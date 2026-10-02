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
 *                         tmpl_exp_neg_kernel_double                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes exp(x) for log(DBL_MIN) < x < -1.                            *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Exp_Neg_Kernel                                            *
 *  Purpose:                                                                  *
 *      Computes exp(x) for negative values, log(DBL_MIN) < x < -1.           *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number, the argument for exp(x).                           *
 *  Output:                                                                   *
 *      exp_x (double):                                                       *
 *          The exponential of x.                                             *
 *  Called Functions:                                                         *
 *      src/math_auxiliary/                                                   *
 *          tmpl_Double_Exp_Kernel:                                           *
 *              Computes exp(x) for |x| > 1.                                  *
 *  Method:                                                                   *
 *      The exp kernel function computes exp(x) using                         *
 *                                                                            *
 *          exp(x) = exp(ln(2) * x / ln(2))                                   *
 *                 = 2^(x / ln(2))                                            *
 *                 = 2^z                                                      *
 *                 = 2^(shift + round7(z) + z - round7(z) - shift)            *
 *                 = scale * 2^(shift + round7(z)) * 2^(z - round7(z))        *
 *                                                                            *
 *      where z = x / ln(2), round7(z) = round(128 * z) / 128 (that is, z     *
 *      rounded to the 7th bit past the binary point), and scale = 2^-shift.  *
 *      The shift is used to ensure that 2^(shift + round7(z)) does not       *
 *      overflow or underflow. Since the input is negative, we only need to   *
 *      worry about underflow. Shifting by 54 prevents underflow from         *
 *      occurring in the intermediate steps. We then scale by 2^-54 to cancel *
 *      the shift in the final result.                                        *
 *  Notes:                                                                    *
 *      1.) Accurate to double precision and within 1 ULP of glibc. This      *
 *          includes inputs that produce denormal outputs.                    *
 *                                                                            *
 *      2.) The input must be negative and lie between log(DBL_MIN) and -1.   *
 *          There are no checks for this.                                     *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_ALWAYS_INLINE macro.                  *
 *  2.) tmpl_attributes.h:                                                    *
 *          Header with macros for C23 attributes on supported compilers.     *
 *  3.) tmpl_math_auxiliary.h:                                                *
 *          Header file where the function declaration is found.              *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 07, 2022                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/01/30: Ryan Maguire                                                  *
 *      Changed Maclaurin series to Remez Minimax polynomial. Fixed comments. *
 *  2026/10/01: Ryan Maguire                                                  *
 *      Rewrote to merge positive and negative kernel functions together.     *
 *      Both now call the main exp kernel function. Moved all exp helper      *
 *      functions to the math_auxiliary directory.                            *
 ******************************************************************************/

/*  Location of the TMPL_ALWAYS_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  Function prototype / forward declaration found here.                      */
#include <libtmpl/include/tmpl_math_auxiliary.h>

/*  Function for computing exp(x) for log(DBL_MIN) < x < -1.                  */
TMPL_CONST_FUNC
TMPL_ALWAYS_INLINE
double
tmpl_Double_Exp_Neg_Kernel(const double x)
TMPL_UNSEQUENCED
{
    /*  The shift factor is to avoid underflow. For 64-bit double-precision   *
     *  numbers there are 52 bits in the mantissa, plus the implied bit.      *
     *  Shifting by 54 prevents underflow from occurring in the intermediate  *
     *  steps. The scale factor to cancel this is 2^-54.                      */
    const double shift = 54.0;
    const double scale = 5.5511151231257827021181583404541015625E-17;
    return tmpl_Double_Exp_Kernel(x, shift, scale);
}
/*  End of tmpl_Double_Exp_Neg_Kernel.                                        */
