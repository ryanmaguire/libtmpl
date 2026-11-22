/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
 *  under the terms of the GNU General Public License as published by         *
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
 *                              tmpl_sqrt_ldouble                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing square roots at long double precision.    *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Sqrt                                                     *
 *  Purpose:                                                                  *
 *      Computes y = sqrt(x), the unique non-negative number y such that for  *
 *      non-negative x we have x = y^2.                                       *
 *  Arguments:                                                                *
 *      x (const long double):                                                *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      sqrt_x (long double):                                                 *
 *          The square root of x at long double precision.                    *
 *  Called Functions:                                                         *
 *      sqxbr (s390x instructions).                                           *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Location of the TMPL_ALWAYS_INLINE macro.                         *
 *  2.) tmpl_attributes.h:                                                    *
 *          Provides optional C23 attributes for optimization.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 22, 2026                                             *
 ******************************************************************************/

/*  TMPL_ALWAYS_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  Function prototype / forward declaration.                                 */
extern long double tmpl_LDouble_Sqrt(const long double x);

/*  Function for computing square roots at long double precision.             */
TMPL_CONST_FUNC

/*  If SIMD_FAST_MATH mode is enabled, do not use always_inline. This will    *
 *  prevent the compiler from selecting the SIMD versions.                    */
#if TMPL_USE_SIMD_FAST_MATH != 1
TMPL_ALWAYS_INLINE
#endif

long double
tmpl_LDouble_Sqrt(const long double x)
TMPL_UNSEQUENCED
{
    /*  Variable for the output, sqrt(x).                                     */
    long double sqrt_x;

    /*  s390x provides the sqxbr instruction for computing square roots.      */
    __asm__("sqxbr %0, %1" : "=f" (sqrt_x) : "f" (x));

    return sqrt_x;
}
/*  End of tmpl_LDouble_Sqrt.                                                 */
