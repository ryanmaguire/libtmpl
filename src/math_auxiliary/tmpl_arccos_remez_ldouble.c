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
 *                          tmpl_arccos_remez_ldouble                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes a Remez polynomial for acos(x) at long double precision.     *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Arcsin_Remez                                             *
 *  Purpose:                                                                  *
 *      Computes a Remez polynomial for acos(x) with |x| < 1/8.               *
 *  Arguments:                                                                *
 *      x (const long double):                                                *
 *          A real number in the interval [-1/8, 1/8].                        *
 *  Output:                                                                   *
 *      acos_x (long double):                                                 *
 *          acos(x) to long double precision.                                 *
 *  Called Functions:                                                         *
 *      src/math_auxiliary/                                                   *
 *          tmpl_LDouble_Arcsin_Aux_Remez:                                    *
 *              Computes a Remez polynomial for (asin(x) - x) / x.            *
 *  Method:                                                                   *
 *      The auxiliary helper function computes a Remez polynomial for         *
 *                                                                            *
 *                 asin(x) - x                                                *
 *          f(x) = -----------                                                *
 *                      x                                                     *
 *                                                                            *
 *      acos(x) can then be computed using                                    *
 *                                                                            *
 *          acos(x) = pi / 2 - asin(x)                                        *
 *                                                                            *
 *                  = pi / 2 - (x + x * p(x))                                 *
 *                                                                            *
 *      where p is the Remez polynomial for f. For extra accuracy we split    *
 *      pi into pi_hi + pi_lo and compute                                     *
 *                                                                            *
 *          acos(x) = pi_hi / 2 - (x - (pi_lo / 2 - x * p(x)))                *
 *                                                                            *
 *  Notes:                                                                    *
 *      1.) Accurate to long double precision for |x| < 1/8. There are no     *
 *          checks that the input falls within this interval.                 *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing the TMPL_ALWAYS_INLINE macro.              *
 *  2.) tmpl_attributes.h:                                                    *
 *          Header with macros for C23 attributes on supported compilers.     *
 *  3.) tmpl_math_constants.h:                                                *
 *          Provides common constants like pi.                                *
 *  4.) tmpl_math_auxiliary.h:                                                *
 *          Contains the function prototype / forward declaration.            *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 6, 2026                                               *
 ******************************************************************************/

/*  Location of the TMPL_ALWAYS_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  Common math constants like pi / 2 found here.                             */
#include <libtmpl/include/constants/tmpl_math_constants.h>

/*  Function prototype / forward declaration found here.                      */
#include <libtmpl/include/tmpl_math_auxiliary.h>

/*  Computes a Remez polynomial for acos(x) on [-1/8, 1/8].                   */
TMPL_CONST_FUNC
TMPL_ALWAYS_INLINE
long double
tmpl_LDouble_Arccos_Remez(const long double x)
TMPL_UNSEQUENCED
{
    /*  Compute a Remez polynomial for (asin(x) - x) / x.                     */
    const long double poly = tmpl_LDouble_Arcsin_Aux_Remez(x);

    /*  Next, use                                                             *
     *                                                                        *
     *      acos(x) = pi / 2 - asin(x)                                        *
     *              = pi / 2 - (x + x * p(x))                                 *
     *                                                                        *
     *  where p is the Remez polynomial for (asin(x) - x) / x. To improve     *
     *  accuracy, we split pi into pi_hi + pi_lo using two long doubles:      *
     *                                                                        *
     *      acos(x) = pi / 2 - (x + x * p(x))                                 *
     *              = pi_hi / 2 - (x - (pi_lo / 2 - x * p(x)))                *
     *                                                                        *
     *  This final expression is returned.                                    */
    const long double low_bits = tmpl_ldouble_pi_by_two_lo - x * poly;
    return tmpl_ldouble_pi_by_two_hi - (x - low_bits);
}
/*  End of tmpl_LDouble_Arccos_Remez.                                         */

/*  Undefine everything to avoid collisions with other macros.                */
#include <libtmpl/include/tmpl_math_undef.h>
