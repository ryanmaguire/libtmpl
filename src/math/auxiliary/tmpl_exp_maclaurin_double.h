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
 *                         tmpl_exp_maclaurin_double                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of exp(x).                              *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Exp_Maclaurin                                             *
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of exp for small values of x.           *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      exp_x (double):                                                       *
 *          The Maclaurin series of exp.                                      *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomial.                       *
 *                                                                            *
 *                        infty                                               *
 *                        -----                                               *
 *                        \        1   n                                      *
 *           exp(x)   =   /       --- x                                       *
 *                        -----    n!                                         *
 *                        n = 0                                               *
 *                                                                            *
 *      Use the first 9 terms (0 <= n <= 8) and compute.                      *
 *  Notes:                                                                    *
 *      Only accurate for values near 0.                                      *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 9, 2022                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_EXP_MACLAURIN_DOUBLE_H
#define TMPL_EXP_MACLAURIN_DOUBLE_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the polynomial. They are 1 / n!.                         */
#define A0 (1.000000000000000000000000000000000000000E+00)
#define A1 (1.000000000000000000000000000000000000000E+00)
#define A2 (5.000000000000000000000000000000000000000E-01)
#define A3 (1.666666666666666666666666666666666666667E-01)
#define A4 (4.166666666666666666666666666666666666667E-02)
#define A5 (8.333333333333333333333333333333333333333E-03)
#define A6 (1.388888888888888888888888888888888888889E-03)
#define A7 (1.984126984126984126984126984126984126984E-04)
#define A8 (2.480158730158730158730158730158730158730E-05)

/*  Maclaurin series of exp to 9 terms.                                       */
TMPL_STATIC_INLINE
double tmpl_Double_Exp_Maclaurin(double x)
{
    /*  Compute the polynomial via Horner's method and return.                */
    return A0+x*(A1+x*(A2+x*(A3+x*(A4+x*(A5+x*(A6+x*(A7+x*A8)))))));
}
/*  End of tmpl_Double_Exp_Maclaurin.                                         */

/*  Undefine all macros in case someone wants to #include this file.          */
#undef A0
#undef A1
#undef A2
#undef A3
#undef A4
#undef A5
#undef A6
#undef A7
#undef A8

#endif
/*  End of include guard.                                                     */
