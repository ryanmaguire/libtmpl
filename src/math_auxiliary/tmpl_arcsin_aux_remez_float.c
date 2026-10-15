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
 *                        tmpl_arcsin_aux_remez_float                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes a degree 4 Remez polynomial for (asin(x) - x) / x at         *
 *      single precision.                                                     *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Arcsin_Aux_Remez                                           *
 *  Purpose:                                                                  *
 *      Computes a degree 4 Remez polynomial for (asin(x) - x) / x            *
 *      with |x| < 1/8.                                                       *
 *  Arguments:                                                                *
 *      x (const float):                                                      *
 *          A real number in the interval [-1/8, 1/8].                        *
 *  Output:                                                                   *
 *      asin_aux_x (float):                                                   *
 *          (asin(x) - x) / x to single precision.                            *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      The function                                                          *
 *                                                                            *
 *                 asin(x) - x                                                *
 *          f(x) = -----------                                                *
 *                       3                                                    *
 *                      x                                                     *
 *                                                                            *
 *      is even, so the degree 2 Remez polynomial for f(x) on [-1/8, 1/8]     *
 *      only requires 1 + 1 = 2 non-zero terms. The polynomial is evaluated   *
 *      using Horner's method and then x^2 * p(x) is returned, where p is the *
 *      Remez polynomial.                                                     *
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

/*  Coefficients for the Remez polynomial.                                    */
#define A00 (+1.6666528409891831422883947932200527995630642732026E-01F)
#define A01 (+7.5704573090386026083598767097110806696653559217707E-02F)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) A00 + z * A01

/*  Computes a degree 4 Remez polynomial for (asin(x) - x) / x.               */
TMPL_CONST_FUNC
TMPL_ALWAYS_INLINE
float
tmpl_Float_Arcsin_Aux_Remez(const float x)
TMPL_UNSEQUENCED
{
    /*  The Remez polynomial for (asin(x) - x) / x^3 is even. Compute x^2.    */
    const float x2 = x * x;

    /*  Evaluate the Remez polynomial using Horner's method.                  */
    const float poly = TMPL_POLY_EVAL(x2);

    /*  (asin(x) - x) / x is given by scaling the polynomial by x^2.          */
    return x2 * poly;
}
/*  End of tmpl_Float_Arcsin_Aux_Remez.                                       */

/*  Undefine everything to avoid collisions with other macros.                */
#include <libtmpl/include/tmpl_math_undef.h>
