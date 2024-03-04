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
 *                          tmpl_erf_maclaurin_double                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of erf(x) at double precision.          *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Erf_Maclaurin                                             *
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of erf(x) for small values x.           *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      erf_x (double):                                                       *
 *          The Maclaurin series of erf(x).                                   *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomial.                       *
 *                                                                            *
 *                             infty                                          *
 *                             -----                                          *
 *                      2      \        (-1)^n                                *
 *          erf(x) = --------  /      ----------- * x^{2n+1}                  *
 *                   sqrt(pi)  -----  (2n + 1) n!                             *
 *                             n = 0                                          *
 *                                                                            *
 *      Use the first 7 terms (0 <= n <= 6) and compute.                      *
 *  Notes:                                                                    *
 *      Only accurate for small values. For |x| < 0.125 this function is      *
 *      accurate to double precision (10^-16 relative error). The larger      *
 *      the input is, the worse the error. By the alternating series theorem, *
 *      the absolute error is bounded by (1/75600)*|x|^15.                    *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 19, 2023                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ERF_MACLAURIN_FLOAT_H
#define TMPL_ERF_MACLAURIN_FLOAT_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the polynomial.                                          */
#define A00 (+1.1283791670955125738961589031215451716881012586580E+00F)
#define A01 (-3.7612638903183752463205296770718172389603375288600E-01F)
#define A02 (+1.1283791670955125738961589031215451716881012586580E-01F)
#define A03 (-2.6866170645131251759432354836227265992573839491857E-02F)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) A00 + z*(A01 + z*(A02 + z*A03))

/*  Function for computing erf(x) via a Maclaurin series.                     */
TMPL_STATIC_INLINE
float tmpl_Float_Erf_Maclaurin(float x)
{
    /*  The polynomial is odd, in terms of x^{2n+1}. Compute x^2.             */
    const float x2 = x*x;

    /*  Evaluate the polynomial using Horner's method and return.             */
    const float poly = TMPL_POLY_EVAL(x2);
    return x*poly;
}
/*  End of tmpl_Float_Erf_Maclaurin.                                          */

/*  #undef everything in case someone wants to #include this file.            */
#undef TMPL_POLY_EVAL
#undef A00
#undef A01
#undef A02
#undef A03

#endif
/*  End of include guard.                                                     */
