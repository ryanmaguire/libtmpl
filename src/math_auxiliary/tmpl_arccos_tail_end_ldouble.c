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
 *                        tmpl_arccos_tail_end_ldouble                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes acos(x) for 1/2 <= |x| < 1 at long double precision.         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Arccos_Tail_End                                          *
 *  Purpose:                                                                  *
 *      Computes arccos for 1/2 <= |x| < 1.                                   *
 *  Arguments:                                                                *
 *      x (const long double):                                                *
 *          A real number with 1/2 <= |x| < 1.                                *
 *  Output:                                                                   *
 *      acos_x (long double):                                                 *
 *          acos(x) to long double precision.                                 *
 *  Called Functions:                                                         *
 *      src/math_auxiliary/                                                   *
 *          tmpl_LDouble_Arcsin_Aux_Rat_Remez:                                *
 *              Computes a rational Remez approximation for (asin(x) - x) / x.*
 *      src/math/                                                             *
 *          tmpl_LDouble_Abs:                                                 *
 *              Computes the absolute value of a real number.                 *
 *          tmpl_LDouble_Sqrt:                                                *
 *              Computes the square root of a number.                         *
 *  Method:                                                                   *
 *      Use the following trig identity:                                      *
 *                                                                            *
 *          acos(x) = 2 * asin(sqrt((1 - x) / 2))                             *
 *                                                                            *
 *      The auxiliary helper function computes a rational Remez approximation *
 *      for the function                                                      *
 *                                                                            *
 *                 asin(x) - x                                                *
 *          f(x) = -----------                                                *
 *                      x                                                     *
 *                                                                            *
 *      For positive x, acos(x) can then be computed using                    *
 *                                                                            *
 *          acos(x) = 2 * (z + z * r(z))                                      *
 *                                                                            *
 *      where z = sqrt((1 - x) / 2) and r is the rational Remez approximation *
 *      for f. For negative x, we use                                         *
 *                                                                            *
 *          acos(x) = pi - 2 * (z + z * r(z))                                 *
 *                                                                            *
 *      where z = sqrt((1 + x) / 2). For improved accuracy, we split pi into  *
 *      two parts pi = pi_hi + pi_lo and compute                              *
 *                                                                            *
 *          acos(x) = pi_hi - 2 * (z + (z * r(z) - pi_lo / 2))                *
 *                                                                            *
 *      This final expression is returned.                                    *
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
 *  3.) tmpl_math_constants.h:                                                *
 *          Provides common math constants like pi and e.                     *
 *  4.) tmpl_math.h:                                                          *
 *          Square root and absolute value functions are declared here.       *
 *  5.) tmpl_math_auxiliary.h:                                                *
 *          Function prototype / forward declaration found here.              *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 2, 2023                                               *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/04/18: Ryan Maguire                                                  *
 *      Changed src/math/tmpl_arccos_tail_end_ldouble.c to include this file. *
 *  2024/11/08: Ryan Maguire                                                  *
 *      Changed coefficients to match those found in arccos_rat_remez_ldouble.*
 *      This includes adding (18, 16) approximations for double-double, and   *
 *      making the coefficients for each precision match the output of the    *
 *      Python scripts found in libtmpl_data. This is to help create          *
 *      reproducible results in libtmpl.                                      *
 *  2026/10/17: Ryan Maguire                                                  *
 *      Rewrote to use the new auxiliary function. Moved to math_auxiliary    *
 *      directory and replaced TMPL_STATIC_INLINE with TMPL_ALWAYS_INLINE.    *
 ******************************************************************************/

/*  Location of the TMPL_ALWAYS_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  Common math constants like pi / 2 found here.                             */
#include <libtmpl/include/constants/tmpl_math_constants.h>

/*  The square root and absolute value functions are provided here.           */
#include <libtmpl/include/tmpl_math.h>

/*  Function prototype / forward declaration found here.                      */
#include <libtmpl/include/tmpl_math_auxiliary.h>

/*  Function for computing acos(x) for 1/2 <= |x| < 1.                        */
TMPL_CONST_FUNC
TMPL_ALWAYS_INLINE
long double
tmpl_LDouble_Arccos_Tail_End(const long double x)
TMPL_UNSEQUENCED
{
    /*  The rational function is computed in terms of sqrt((1 - |x|) / 2).    */
    const long double abs_x = tmpl_LDouble_Abs(x);
    const long double z_squared = 0.5L * (1.0L - abs_x);
    const long double z = tmpl_LDouble_Sqrt(z_squared);

    /*  Compute a rational Remez approximation for (asin(z) - z) / z.         */
    const long double rat = tmpl_LDouble_Arcsin_Aux_Rat_Remez(z);

    /*  For negative x, use acos(x) = pi - acos(-x).                          */
    if (x < 0.0L)
    {
        const long double low_bits = z * rat - tmpl_ldouble_pi_by_two_lo;
	    return tmpl_ldouble_pi_hi - 2.0L * (z + low_bits);
    }

    /*  For positive x, we now have (asin(z) - z) / z and need 2 * asin(z).   *
     *  Compute this and return.                                              */
    return 2.0L * (z + z * rat);
}
/*  End of tmpl_LDouble_Arccos_Tail_End.                                      */
