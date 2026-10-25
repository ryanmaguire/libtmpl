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
 *                       tmpl_arcsin_rat_remez_ldouble                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes a rational Remez approximation of asin(x) for |x| < 1/2 at   *
 *      long double precision.                                                *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Arcsin_Rat_Remez                                         *
 *  Purpose:                                                                  *
 *      Computes a rational minimax approximation for arcsin across the       *
 *      interval [-1/2, 1/2].                                                 *
 *  Arguments:                                                                *
 *      x (const long double):                                                *
 *          A real number in the interval [-1/2, 1/2].                        *
 *  Output:                                                                   *
 *      asin_x (long double):                                                 *
 *          asin(x) to long double precision.                                 *
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
 *      asin(x) can then be computed using asin(x) = x + x * r(x), where r is *
 *      the rational Remez approximation for f.                               *
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
 *          Header file containing the TMPL_ALWAYS_INLINE macro.              *
 *  2.) tmpl_attributes.h:                                                    *
 *          Header with macros for C23 attributes on supported compilers.     *
 *  3.) tmpl_math_auxiliary.h:                                                *
 *          Function prototype / forward declaration found here.              *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 1, 2023                                                  *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/06/01: Ryan Maguire                                                  *
 *      Corrected name and comments. This was previously called a "Pade"      *
 *      approximant, but it is not. The coefficients for the Pade approximant *
 *      and the rational minimax function are slightly different.             *
 *  2026/10/10: Ryan Maguire                                                  *
 *      Rewrote to use the new auxiliary function. Moved to math_auxiliary    *
 *      directory and replaced TMPL_STATIC_INLINE with TMPL_ALWAYS_INLINE.    *
 ******************************************************************************/

/*  Location of the TMPL_ALWAYS_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  Function prototype / forward declaration found here.                      */
#include <libtmpl/include/tmpl_math_auxiliary.h>

/*  Computes a rational Remez approximation for asin(x) on [-1/2, 1/2].       */
TMPL_CONST_FUNC
TMPL_ALWAYS_INLINE
long double
tmpl_LDouble_Arcsin_Rat_Remez(const long double x)
TMPL_UNSEQUENCED
{
    /*  Compute a rational Remez approximation for (asin(x) - x) / x.         */
    const long double rat = tmpl_LDouble_Arcsin_Aux_Rat_Remez(x * x);

    /*  Compute asin(x) from this.                                            */
    return x + x * rat;
}
/*  End of tmpl_LDouble_Arcsin_Rat_Remez.                                     */
