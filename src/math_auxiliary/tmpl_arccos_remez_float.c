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
 *                          tmpl_arccos_remez_float                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes a Remez polynomial for acos(x) at single precision.          *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Arcsin_Remez                                               *
 *  Purpose:                                                                  *
 *      Computes a degree 5 Remez polynomial for acos(x) with |x| < 1/8.      *
 *  Arguments:                                                                *
 *      x (const float):                                                      *
 *          A real number in the interval [-1/8, 1/8].                        *
 *  Output:                                                                   *
 *      acos_x (float):                                                       *
 *          acos(x) to single precision.                                      *
 *  Called Functions:                                                         *
 *      src/math_auxiliary/                                                   *
 *          tmpl_Float_Arcsin_Aux_Remez:                                      *
 *              Computes a degree 5 Remez polynomial for (asin(x) - x) / x.   *
 *  Method:                                                                   *
 *      The auxiliary helper function computes a degree 4 Remez polynomial    *
 *      for the function                                                      *
 *                                                                            *
 *                 asin(x) - x                                                *
 *          f(x) = -----------                                                *
 *                      x                                                     *
 *                                                                            *
 *      acos(x) can then be computed using                                    *
 *                                                                            *
 *          acos(x) = pi / 2 - asin(x)                                        *
 *                  = pi / 2 - (x + x * p(x))                                 *
 *                                                                            *
 *      where p is the Remez polynomial for f. For extra accuracy we split    *
 *      pi into pi_hi + pi_lo and compute                                     *
 *                                                                            *
 *          acos(x) = pi_hi / 2 - (x - (pi_lo / 2 - x * p(x)))                *
 *                                                                            *
 *  Notes:                                                                    *
 *      1.) Accurate to single precision for |x| < 1/8. There are no checks   *
 *          that the input falls within this interval.                        *
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

/*  Computes a degree 5 Remez polynomial for acos(x) on [-1/8, 1/8].          */
TMPL_CONST_FUNC
TMPL_ALWAYS_INLINE
float
tmpl_Float_Arccos_Remez(const float x)
TMPL_UNSEQUENCED
{
    /*  Compute a degree 4 Remez polynomial for (asin(x) - x) / x.            */
    const float poly = tmpl_Float_Arcsin_Aux_Remez(x);

    /*  Next, use                                                             *
     *                                                                        *
     *      acos(x) = pi / 2 - asin(x)                                        *
     *              = pi / 2 - (x + x * p(x))                                 *
     *                                                                        *
     *  where p is the Remez polynomial for (asin(x) - x) / x. To improve     *
     *  accuracy, we split pi into pi_hi + pi_lo using two floats:            *
     *                                                                        *
     *      acos(x) = pi / 2 - (x + x * p(x))                                 *
     *              = pi_hi / 2 - (x - (pi_lo / 2 - x * p(x)))                *
     *                                                                        *
     *  This final expression is returned.                                    */
    const float low_bits = tmpl_float_pi_by_two_lo - x * poly;
    return tmpl_float_pi_by_two_hi - (x - low_bits);
}
/*  End of tmpl_Float_Arccos_Remez.                                           */
