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
 *                          tmpl_sincpi_remez_double                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes a Remez approximation for sinc(pi x).                        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_SincPi_Remez                                              *
 *  Purpose:                                                                  *
 *      Computes the degree 8 Remez approximation for sinc(pi x).             *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number between -1/16 and 1/16.                             *
 *  Output:                                                                   *
 *      sincpi_x (double):                                                    *
 *          sinc(pi x) = sin(pi x) / (pi x) for non-zero x, and 1 if x = 0.   *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomial.                       *
 *  Notes:                                                                    *
 *      Accurate to double precision for |x| < 2^-4.                          *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 27, 2024                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_SINCPI_REMEZ_DOUBLE_H
#define TMPL_SINCPI_REMEZ_DOUBLE_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the Remez polynomial.                                    */
#define A00 (+9.9999999999999999584023803599402842503057380493267E-01)
#define A01 (-1.6449340668481731770654620946697540791552236416947E+00)
#define A02 (+8.1174242517424805647620755190549653822727520593502E-01)
#define A03 (-1.9075174589165808801770314273686444646736191297808E-01)
#define A04 (+2.6124951444471635014865818149908952415094199371260E-02)

/*  Helper macro for evaluating the polynomial via Horner's method.           */
#define TMPL_POLY_EVAL(z) A00 + z*(A01 + z*(A02 + z*(A03 + z*A04)))

/*  Computes a Remez approximation for sinc(pi x) on [-2^-4, 2^-4].           */
TMPL_STATIC_INLINE
double tmpl_Double_SincPi_Remez(double x)
{
    /*  sinc(pi x) is even, the polynomial is in terms of x^2.                */
    const double x2 = x * x;
    return TMPL_POLY_EVAL(x2);
}
/*  End of tmpl_Double_SincPi_Remez.                                          */

/*  Undefine everything in case someone wants to #include this file.          */
#include "tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
