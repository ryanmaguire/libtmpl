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
 *                        tmpl_arccos_rat_remez_ldouble                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes a rational Remez approximation of acos(x) for |x| < 1/2 at   *
 *      long double precision.                                                *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Arccos_Rat_Remez                                         *
 *  Purpose:                                                                  *
 *      Computes a rational minimax approximation for arccos across the       *
 *      interval [-1/2, 1/2].                                                 *
 *  Arguments:                                                                *
 *      x (const long double):                                                *
 *          A real number in the interval [-1/2, 1/2].                        *
 *  Output:                                                                   *
 *      acos_x (long double):                                                 *
 *          acos(x) to long double precision.                                 *
 *  Called Functions:                                                         *
 *      src/math_auxiliary/                                                   *
 *          tmpl_LDouble_Arcsin_Aux_Rat_Remez:                                *
 *              Computes a rational Remez approximation for (asin(x) - x) / x.*
 *  Method:                                                                   *
 *      The auxiliary helper function computes a rational Remez approximation *
 *      for the function                                                      *
 *                                                                            *
 *                 asin(x) - x                                                *
 *          f(x) = -----------                                                *
 *                      x                                                     *
 *                                                                            *
 *      acos(x) can then be computed using                                    *
 *                                                                            *
 *          acos(x) = pi / 2 - asin(x)                                        *
 *                  = pi / 2 - (x + x * r(x))                                 *
 *                                                                            *
 *      where r is the rational Remez approximation for f. For extra accuracy *
 *      we split pi into pi_hi + pi_lo and compute                            *
 *                                                                            *
 *          acos(x) = pi_hi / 2 - (x - (pi_lo / 2 - x * r(x)))                *
 *                                                                            *
 *  Notes:                                                                    *
 *      1.) Accurate to long double precision for |x| < 1/2. There are no     *
 *          checks that the input falls within this interval.                 *
 *  References:                                                               *
 *      1.) Maguire, Ryan (2024)                                              *
 *          tmpld                                                             *
 *          https://github.com/ryanmaguire/libtmpl_data                       *
 *                                                                            *
 *          Python library providing an implementation of the rational        *
 *          Remez exchange algorithm. The coefficients for the                *
 *          approximation used by this function were computed using this.     *
 *                                                                            *
 *      2.) Tasissa, Abiy (2019)                                              *
 *          Function Approximation and the Remez Exchange Algorithm.          *
 *          https://sites.tufts.edu/atasissa/files/2019/09/remez.pdf          *
 *                                                                            *
 *          Survey of the Remez polynomial and Remez exchange algorithm.      *
 *          The implementation in tmpld is based on these notes.              *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_ALWAYS_INLINE macro.                  *
 *  2.) tmpl_attributes.h:                                                    *
 *          Header with macros for C23 attributes on supported compilers.     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 2, 2023                                               *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/04/18: Ryan Maguire                                                  *
 *      Changed src/math/tmpl_arccos_pade_ldouble.c to just include this file.*
 *  2023/05/13: Ryan Maguire                                                  *
 *      Corrected name and comments. This was previously called a "Pade"      *
 *      approximant, but it is not. The coefficients for the Pade approximant *
 *      and the rational minimax function are slightly different.             *
 *  2024/10/29: Ryan Maguire                                                  *
 *      Updating coefficients to be exactly the output of the Python scripts  *
 *      found in the libtmpl_data repo. Added a degree (18, 16) approximation *
 *      for double-double, instead of using the same degree (18, 18)          *
 *      coefficients that quadruple uses. Using a (10, 10) approximation for  *
 *      80-bit extended instead of a (12, 10) approximation. Peak theoretical *
 *      error is 2 * 10^-20. Unit tests show the actual error is still 1 ULP. *
 *  2026/06/12: Ryan Maguire                                                  *
 *      Added references.                                                     *
 *  2026/10/10: Ryan Maguire                                                  *
 *      Rewrote to use the new auxiliary function. Moved to math_auxiliary    *
 *      directory and replaced TMPL_STATIC_INLINE with TMPL_ALWAYS_INLINE.    *
 ******************************************************************************/

/*  Location of the TMPL_ALWAYS_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  Common math constants like pi / 2 found here.                             */
#include <libtmpl/include/constants/tmpl_math_constants.h>

/*  Function prototype / forward declaration found here.                      */
#include <libtmpl/include/tmpl_math_auxiliary.h>

/*  Function for computing a rational Remez approximation for acos(x).        */
TMPL_CONST_FUNC
TMPL_ALWAYS_INLINE
long double
tmpl_LDouble_Arccos_Rat_Remez(const long double x)
TMPL_UNSEQUENCED
{
    /*  Compute a rational Remez approximation for (asin(x) - x) / x.         */
    const long double rat = tmpl_LDouble_Arcsin_Aux_Rat_Remez(x);

    /*  From this we can compute acos(x) using                                *
     *                                                                        *
     *      acos(x) = pi / 2 - asin(x)                                        *
     *              = pi / 2 - (x + x * r(x))                                 *
     *                                                                        *
     *  where r is the Remez approximation for (asin(x) - x) / x. To improve  *
     *  accuracy, we split pi into pi_hi + pi_lo using two long doubles:      *
     *                                                                        *
     *      acos(x) = pi / 2 - (x + x * r(x))                                 *
     *              = pi_hi / 2 - (x - (pi_lo / 2 - x * r(x)))                *
     *                                                                        *
     *  This final expression is returned.                                    */
    const long double low_bits = tmpl_ldouble_pi_by_two_lo - x * rat;
    return tmpl_ldouble_pi_by_two_hi - (x - low_bits);
}
/*  End of tmpl_LDouble_Arccos_Rat_Remez.                                     */
