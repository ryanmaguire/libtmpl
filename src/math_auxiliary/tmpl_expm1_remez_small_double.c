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
 *                        tmpl_expm1_remez_small_double                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes a Remez polynomial for exp(x) - 1 at double precision.       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Expm1_Remez_Small                                         *
 *  Purpose:                                                                  *
 *      Computes a degree 5 Remez polynomial for exp(x) - 1 for |x| < 1 / 256.*
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number in the interval [-1 / 256, 1 / 256].                *
 *  Output:                                                                   *
 *      expm1_x (double):                                                     *
 *          exp(x) - 1 to double precision.                                   *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      exp(x) - 1 goes to zero as x -> 0. To avoid precision loss, the       *
 *      degree four Remez polynomial for (exp(x) - 1) / x is computed on the  *
 *      interval [-1 / 256, 1 / 256]. This polynomial is evaluated using      *
 *      Horner's method and then scaled by x to compute exp(x) - 1.           *
 *  Notes:                                                                    *
 *      1.) Accurate to double precision for |x| < 1 / 256. There are no      *
 *          checks that the input falls within this interval.                 *
 *                                                                            *
 *      2.) Since this function computes exp(x) - 1 ~= x * p(x), where p is a *
 *          polynomial, the relative error remains excellent even for very    *
 *          small inputs.                                                     *
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
 *  Date:       May 13, 2023                                                  *
 ******************************************************************************/

/*  Location of the TMPL_ALWAYS_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  Function prototype / forward declaration found here.                      */
#include <libtmpl/include/tmpl_math_auxiliary.h>

/*  Coefficients for the degree 4 Remez polynomial of (exp(x) - 1) / x on the *
 *  interval [-1 / 256, 1 / 256].                                             */
#define A00 (+9.9999999999999999996514611340908502585157349290002E-01)
#define A01 (+4.9999999999989902588777641171025460932977300504347E-01)
#define A02 (+1.6666666666669121135482823456601378042344182234590E-01)
#define A03 (+4.1666693147021956705603119934401714443225170111611E-02)
#define A04 (+8.3333332048504529963063689474968075725842681351594E-03)

/*  Helper macro for evaluating the polynomial using Horner's method.         */
#define TMPL_POLY_EVAL(z) A00 + z * (A01 + z * (A02 + z * (A03 + z * A04)))

/*  Computes a Remez polynomial for exp(x) - 1 on [-1/256, 1/256].            */
TMPL_CONST_FUNC
TMPL_ALWAYS_INLINE
double
tmpl_Double_Expm1_Remez_Small(const double x)
TMPL_UNSEQUENCED
{
    /*  The Remez coefficients are for (exp(x) - 1) / x. Scaling by x gives   *
     *  us expm1(x).                                                          */
    const double poly = TMPL_POLY_EVAL(x);
    return x * poly;
}
/*  End of tmpl_Double_Expm1_Remez_Small.                                     */

/*  Undefine everything to avoid collisions with other macros.                */
#include <libtmpl/include/tmpl_math_undef.h>
