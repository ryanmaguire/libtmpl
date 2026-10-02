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
 *                         tmpl_exp_pos_kernel_double                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes exp(x) for 1 < x < log(DBL_MAX).                             *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Exp_Pos_Kernel                                            *
 *  Purpose:                                                                  *
 *      Computes exp(x) for positive values, 1 < x < log(DBL_MAX).            *
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
 *      overflow or underflow. Since the input is positive, we only need to   *
 *      worry about overflow. Shifting by -1 prevents overflow from           *
 *      occurring in the intermediate steps. We then scale by 2^1 to cancel   *
 *      the shift in the final result.                                        *
 *  Notes:                                                                    *
 *      1.) Accurate to double precision and within 1 ULP of glibc.           *
 *                                                                            *
 *      2.) The input must be positive and lie between 1 and log(DBL_MAX).    *
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

/*  Function for computing exp(x) for 1 < x < log(DBL_MAX).                   */
TMPL_CONST_FUNC
TMPL_ALWAYS_INLINE
double
tmpl_Double_Exp_Pos_Kernel(const double x)
TMPL_UNSEQUENCED
{
    /*  The shift factor is to avoid overflow. For 1 < x < log(DBL_MAX),      *
     *  computing round7(x / ln(2)) = 128 * round(x / ln(2) / 128) may result *
     *  in a number such that 2^round7(x / ln(2)) overflows to infinity, even *
     *  if exp(x) is representable as a double. Shifting back by 1 and then   *
     *  scaling by 2^1 prevents this.                                         */
    const double shift = -1.0;
    const double scale = +2.0;
    return tmpl_Double_Exp_Kernel(x, shift, scale);
}
/*  End of tmpl_Double_Exp_Pos_Kernel.                                        */
