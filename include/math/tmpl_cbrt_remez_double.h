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
 *                           tmpl_cbrt_remez_double                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the Remez minimax polynomial for cbrt(x) about x = 1.        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Cbrt_Remez                                                *
 *  Purpose:                                                                  *
 *      Computes the Remez minimax polynomial of degree 2 for cbrt(x) on the  *
 *      interval 1 <= x <= 1 + 1/128.                                         *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      cbrt_x (double):                                                      *
 *          The evaluation of the Remez minimax polynomial for cbrt(x).       *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomial.                       *
 *  Notes:                                                                    *
 *      Only accurate for values near 1. Peak relative error on the interval  *
 *      [1, 1 + 1/28] is 10^-9. Much less than double precision, but double   *
 *      precision is attained in the cbrt function by using Newton's method   *
 *      after calling this routine.                                           *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 8, 2023                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_CBRT_REMEZ_DOUBLE_H
#define TMPL_CBRT_REMEZ_DOUBLE_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the Remez minimax polynomial at x = 1.                   */
#define A0 (+1.000000000909414432420604780739805683220058751649040157764717E+00)
#define A1 (+3.333312337128901899438791242710004591007975419381606149309224E-01)
#define A2 (-1.103924930854689350877233791895646403286896731306260302904416E-01)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) A0 + z*(A1 + z*A2)

/*  Function for computing the Remez polynomial of cbrt on [1, 1 + 1/128].    */
TMPL_STATIC_INLINE
double tmpl_Double_Cbrt_Remez(double x)
{
    /*  The series is computed at x = 1. Shift the input.                     */
    const double xs = x - 1.0;

    /*  Use Horner's method to evaluate the polynomial.                       */
    return TMPL_POLY_EVAL(xs);
}
/*  End of tmpl_Double_Cbrt_Remez.                                            */

/*  Undefine all macros in case someone wants to #include this file.          */
#undef A0
#undef A1
#undef A2
#undef TMPL_POLY_EVAL

#endif
/*  End of include guard.                                                     */
