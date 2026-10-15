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
 *                          tmpl_arcsin_remez_float                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes a Remez polynomial for asin(x) at single precision.          *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Arcsin_Remez                                               *
 *  Purpose:                                                                  *
 *      Computes a degree 5 Remez polynomial for asin(x) with |x| < 1/8.      *
 *  Arguments:                                                                *
 *      x (const float):                                                      *
 *          A real number in the interval [-1/8, 1/8].                        *
 *  Output:                                                                   *
 *      asin_x (float):                                                       *
 *          asin(x) to single precision.                                      *
 *  Called Functions:                                                         *
 *      src/math_auxiliary/                                                   *
 *          tmpl_Float_Arcsin_Aux_Remez:                                      *
 *              Computes a degree 4 Remez polynomial for (asin(x) - x) / x.   *
 *  Method:                                                                   *
 *      The auxiliary helper function computes a degree 4 Remez polynomial    *
 *      for the function                                                      *
 *                                                                            *
 *                 asin(x) - x                                                *
 *          f(x) = -----------                                                *
 *                      x                                                     *
 *                                                                            *
 *      asin(x) can be computed using asin(x) = x + x * p(x) where p is the   *
 *      Remez polynomial for f.                                               *
 *  Notes:                                                                    *
 *      1.) Accurate to single precision for |x| < 1/8. There are no checks   *
 *          that the input falls within this interval.                        *
 *  References:                                                               *
 *      1.) Maguire, Ryan (2024)                                              *
 *          tmpld                                                             *
 *          https://github.com/ryanmaguire/libtmpl_data                       *
 *                                                                            *
 *          Python library providing an implementation of the Remez exchange  *
 *          algorithm. The coefficients for the approximation used by this    *
 *          function were computed using this.                                *
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
 *          Contains the function prototype / forward declaration.            *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 6, 2026                                               *
 ******************************************************************************/

/*  Location of the TMPL_ALWAYS_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  Function prototype / forward declaration found here.                      */
#include <libtmpl/include/tmpl_math_auxiliary.h>

/*  Computes a degree 5 Remez polynomial for asin(x) on [-1/8, 1/8].          */
TMPL_CONST_FUNC
TMPL_ALWAYS_INLINE
float
tmpl_Float_Arcsin_Remez(const float x)
TMPL_UNSEQUENCED
{
    /*  Compute a degree 4 Remez polynomial for (asin(x) - x) / x.            */
    const float poly = tmpl_Float_Arcsin_Aux_Remez(x);

    /*  asin(x) = x + x * p(x), where p is the Remez polynomial.              */
    return x + x * poly;
}
/*  End of tmpl_Float_Arcsin_Remez.                                           */
