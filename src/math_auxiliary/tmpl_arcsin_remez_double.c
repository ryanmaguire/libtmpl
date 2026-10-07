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
 *                          tmpl_arcsin_remez_double                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes a Remez polynomial for asin(x) at double precision.          *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Arcsin_Remez                                              *
 *  Purpose:                                                                  *
 *      Computes a degree 13 Remez polynomial for asin(x) with |x| < 1/8.     *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number in the interval [-1/8, 1/8].                        *
 *  Output:                                                                   *
 *      asin_x (double):                                                      *
 *          asin(x) to double precision.                                      *
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
 *      is even, so the degree 10 Remez polynomial for f(x) on [-1/8, 1/8]    *
 *      only requires 5 + 1 = 6 non-zero terms. asin(x) is then computed by   *
 *                                                                            *
 *                         3                                                  *
 *          asin(x) = x + x  p(x)                                             *
 *                                                                            *
 *      where p is the Remez polynomial for f. p(x) is evaluated using        *
 *      Horner's method.                                                      *
 *  Notes:                                                                    *
 *      1.) Accurate to double precision for |x| < 1/8. There are no checks   *
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
#define A00 (+1.6666666666666656293481345275688480130071045466573E-01)
#define A01 (+7.5000000000477049774617709946013607390518865927319E-02)
#define A02 (+4.4642856787430947600823955193235375582518886056675E-02)
#define A03 (+3.0382041227401833288830911184935457270396756757083E-02)
#define A04 (+2.2360264850884186132567530659511508895783907274177E-02)
#define A05 (+1.8023799292951331941625122396560343869425939766530E-02)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) \
A00 + z * (A01 + z * (A02 + z * (A03 + z * (A04 + z * A05))))

/*  Computes a degree 13 Remez polynomial for asin(x).                        */
TMPL_CONST_FUNC
TMPL_ALWAYS_INLINE
double
tmpl_Double_Arcsin_Remez(const double x)
TMPL_UNSEQUENCED
{
    /*  The Remez polynomial for (asin(x) - x) / x^3 is even. Compute x^2.    */
    const double x2 = x * x;

    /*  Evaluate the Remez polynomial using Horner's method.                  */
    const double poly = TMPL_POLY_EVAL(x2);

    /*  asin(x) = x + x^3 * p(x), where p is the Remez polynomial.            */
    return x + x * (x2 * poly);
}
/*  End of tmpl_Double_Arcsin_Remez.                                          */

/*  Undefine everything to avoid collisions with other macros.                */
#include <libtmpl/include/tmpl_math_undef.h>
