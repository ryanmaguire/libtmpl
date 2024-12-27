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
 *                          tmpl_sinpi_remez_double                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes a Remez approximation for sin(pi x).                         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_SinPi_Remez                                               *
 *  Purpose:                                                                  *
 *      Computes a degree 9 Remez approximation for sin(pi x).                *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number between -1/16 and 1/16.                             *
 *  Output:                                                                   *
 *      sinpi_x (double):                                                     *
 *          The value sin(pi x) to double precision.                          *
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
#ifndef TMPL_SINPI_REMEZ_DOUBLE_H
#define TMPL_SINPI_REMEZ_DOUBLE_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the Remez polynomial.                                    */
#define A00 (+3.1415926535897932253943657564760926561615735901235E+00)
#define A01 (-5.1677127800498027098844341911090269051780350893582E+00)
#define A02 (+2.5501640395345801327662224517478562312008723260125E+00)
#define A03 (-5.9926428355266007325628778116378250761851339410863E-01)
#define A04 (+8.2073955533342145746714238819442999697400119725551E-02)

/*  Helper macro for evaluating the polynomial via Horner's method.           */
#define TMPL_POLY_EVAL(z) A00 + z*(A01 + z*(A02 + z*(A03 + z*A04)))

/*  Computes a Remez approximation for sin(pi x) on [-2^-4, 2^-4].            */
TMPL_STATIC_INLINE
double tmpl_Double_SinPi_Remez(double x)
{
    /*  sin(pi x) is odd, the polynomial is in terms of x^{2n+1}.             */
    const double x2 = x * x;
    const double poly = TMPL_POLY_EVAL(x2);
    return x * poly;
}
/*  End of tmpl_Double_SinPi_Remez.                                           */

/*  Undefine everything in case someone wants to #include this file.          */
#include "tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
