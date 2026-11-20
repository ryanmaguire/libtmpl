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
 *                           tmpl_sqrt_remez_double                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes a Remez minimax polynomial for sqrt(x) on [1, 1 + 1/128].    *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Sqrt_Remez                                                *
 *  Purpose:                                                                  *
 *      Computes a degree 2 Remez polynomial for sqrt(x) on [1, 1 + 1/128].   *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      sqrt_x (double):                                                      *
 *          sqrt(x), accurate on [1, 1 + 1/128] to about 9 or 10 digits.      *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      To ensure that sqrt(1) = 1, exactly, we use the Remez polynomial for  *
 *      the function                                                          *
 *                                                                            *
 *                 sqrt(x + 1) - 1                                            *
 *          f(x) = ---------------                                            *
 *                        x                                                   *
 *                                                                            *
 *      Letting p be the degree 1 Remez polynomial for f on [0, 1/128], we    *
 *      compute sqrt(x) using                                                 *
 *                                                                            *
 *          sqrt(x) = 1 + (x - 1) * p(x - 1)                                  *
 *                                                                            *
 *      p(x - 1) is evaluated using Horner's method.                          *
 *  Notes:                                                                    *
 *      1.) For 1 <= x <= 1 + 1/128 this returns sqrt(x) to 9 or 10 decimals. *
 *          To obtain double precision you must apply 1 iteration of Newton's *
 *          method after evaluating the Remez polynomial.                     *
 *                                                                            *
 *      2.) This function assumes x is in the interval [1, 1 + 1/128]. There  *
 *          are no checks for this.                                           *
 *                                                                            *
 *      3.) If hardware FMA is available, then combining this function with   *
 *          a single iteration of Newton's method produces sqrt(x) correctly  *
 *          rounded, meaning the peak error is bounded by 1/2 ULP. Without    *
 *          hardware FMA the peak error (after applying Newton's method) is   *
 *          bounded by 1 ULP.                                                 *
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
 *  Date:       March 27, 2024                                                *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2025/05/19: Ryan Maguire                                                  *
 *      Changed coefficients so sqrt(1) is exactly 1. The Remez polynomial    *
 *      is now computed for (sqrt(x + 1) - 1) / x on the interval [0, 1/128]. *
 *      Labeling this p(x), the output is 1 + (x - 1) * p(x - 1), and hence   *
 *      sqrt(1) = 1, exact. Previously the Remez polynomial was computed for  *
 *      sqrt(x + 1), the constant term being 1.00000000092137931324220803332, *
 *      about 10^-10 off from 1. The resulting polynomial, combined with      *
 *      Newton's method in the main sqrt routine, produced a value that did   *
 *      indeed round to 1 (meaning tmpl_Double_Sqrt(1.0) = 1.0 previously),   *
 *      but by modifying the coefficients slightly we can very easily verify  *
 *      that sqrt(1.0) = 1.0 will occur without relying on the rouding mode,  *
 *      and no penalty to the accuracy or performance of the function occurs. *
 *  2026/11/18: Ryan Maguire                                                  *
 *      Moved function to the math_auxiliary directory, added C23 attributes. *
 ******************************************************************************/

/*  Location of the TMPL_ALWAYS_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  Function prototype / forward declaration found here.                      */
#include <libtmpl/include/tmpl_math_auxiliary.h>

/*  Coefficients for the Remez polynomial.                                    */
#define A00 (+4.9999952710402341176619144737945297154350813287950E-01)
#define A01 (-1.2451433174963825931999964469903198888523489420988E-01)

/*  Helper macro for evaluating the polynomial via Horner's method.           */
#define TMPL_POLY_EVAL(z) A00 + z * A01

/*  Evaluates sqrt(x) for 1 <= x < 1 + 1/128 using a Remez polynomial.        */
TMPL_CONST_FUNC
TMPL_ALWAYS_INLINE
double
tmpl_Double_Sqrt_Remez(const double x)
TMPL_UNSEQUENCED
{
    /*  The expansion is centered about x = 1. Shift the input.               */
    const double xs = x - 1.0;

    /*  Use Horner's method to evaluate the polynomial.                       */
    const double poly = TMPL_POLY_EVAL(xs);

    /*  The Remez polynomial is for (sqrt(x) - 1) / (x - 1). Compute sqrt(x)  *
     *  from this.                                                            */
    return 1.0 + xs * poly;
}
/*  End of tmpl_Double_Sqrt_Remez.                                            */

/*  Undefine everything in case someone wants to #include this file.          */
#include <libtmpl/include/tmpl_math_undef.h>
