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
 *                        tmpl_arccos_rat_remez_float                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes a degree (7, 2) rational Remez approximation of acos(x)      *
 *      for |x| < 1/2 at single precision.                                    *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Arccos_Rat_Remez                                           *
 *  Purpose:                                                                  *
 *      Computes a degree (7, 2) rational minimax approximation for arccos    *
 *      across the interval [-1/2, 1/2].                                      *
 *  Arguments:                                                                *
 *      x (const float):                                                      *
 *          A real number in the interval [-1/2, 1/2].                        *
 *  Output:                                                                   *
 *      acos_x (float):                                                       *
 *          acos(x) to single precision.                                      *
 *  Called Functions:                                                         *
 *      src/math_auxiliary/                                                   *
 *          tmpl_Float_Arcsin_Aux_Rat_Remez:                                  *
 *              Computes a degree (6, 2) rational Remez approximation for     *
 *              (asin(x) - x) / x.                                            *
 *  Method:                                                                   *
 *      The auxiliary helper function computes a degree (6, 2) rational       *
 *      Remez approximation for the function                                  *
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
 *      1.) Accurate to single precision for |x| < 1/2. There are no checks   *
 *          that the input falls within this interval.                        *
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
 *  3.) tmpl_math_constants.h:                                                *
 *          Provides common math constants like pi and e.                     *
 *  4.) tmpl_math_auxiliary.h:                                                *
 *          Function prototype / forward declaration found here.              *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 2, 2023                                               *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/04/18: Ryan Maguire                                                  *
 *      Changed src/math/tmpl_arccos_pade_float.c to just include this file.  *
 *  2023/05/13: Ryan Maguire                                                  *
 *      Corrected name and comments. This was previously called a "Pade"      *
 *      approximant, but it is not. The coefficients for the Pade approximant *
 *      and the rational minimax function are slightly different.             *
 *  2024/10/29: Ryan Maguire                                                  *
 *      Updating coefficients. These are now the exact output of the python   *
 *      script found in libtmpl_data. Attempting to create reproducible       *
 *      results in doing this.                                                *
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

/*  Computes a degree (7, 2) Remez approximation for acos(x) on [-1/2, 1/2].  */
TMPL_CONST_FUNC
TMPL_ALWAYS_INLINE
float
tmpl_Float_Arccos_Rat_Remez(const float x)
TMPL_UNSEQUENCED
{
    /*  Compute a degree (6, 2) Remez approximation for (asin(x) - x) / x.    */
    const float rat = tmpl_Float_Arcsin_Aux_Rat_Remez(x);

    /*  From this we can compute acos(x) using                                *
     *                                                                        *
     *      acos(x) = pi / 2 - asin(x)                                        *
     *              = pi / 2 - (x + x * r(x))                                 *
     *                                                                        *
     *  where r is the Remez approximation for (asin(x) - x) / x. To improve  *
     *  accuracy, we split pi into pi_hi + pi_lo using two floats:            *
     *                                                                        *
     *      acos(x) = pi / 2 - (x + x * r(x))                                 *
     *              = pi_hi / 2 - (x - (pi_lo / 2 - x * r(x)))                *
     *                                                                        *
     *  This final expression is returned.                                    */
    const float low_bits = tmpl_float_pi_by_two_lo - x * rat;
    return tmpl_float_pi_by_two_hi - (x - low_bits);
}
/*  End of tmpl_Float_Arccos_Rat_Remez.                                       */
