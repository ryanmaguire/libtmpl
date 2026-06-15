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
 *                       tmpl_cospi_remez_small_double                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes a Remez approximation for cos(pi x).                         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_SinPi_Remez_Small                                         *
 *  Purpose:                                                                  *
 *      Computes a degree 7 Remez approximation for cos(pi x).                *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number between -2^-7 and 2^7.                              *
 *  Output:                                                                   *
 *      cospi_x (double):                                                     *
 *          The value cos(pi x) to double precision.                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomial.                       *
 *  Notes:                                                                    *
 *      1.) Accurate to double precision for |x| < 2^-7.                      *
 *                                                                            *
 *      2.) Peak theoretical error is less than 10^-20. Peak floating-point   *
 *          error (64-bit double precision) is less than 1 ULP.               *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 *  2.) tmpl_attributes.h:                                                    *
 *          Provides C23 attributes for optimization hints.                   *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 15, 2026                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COSPI_REMEZ_SMALL_DOUBLE_H
#define TMPL_COSPI_REMEZ_SMALL_DOUBLE_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Optional C23 attributes for optimization found here.                      */
#include <libtmpl/include/tmpl_attributes.h>

/*  Coefficients for the Remez polynomial.                                    */
#define A00 (-4.9348022005446793094144475456990697833677672726859E+00)
#define A01 (+4.0587121264167667512488580317860010716638286050473E+00)
#define A02 (-1.3352627687344178974206770812012210534608093973702E+00)
#define A03 (+2.3532748012463992147510490415376698570667022495328E-01)

/*  Helper macro for evaluating the polynomial via Horner's method.           */
#define TMPL_POLY_EVAL(z) A00 + z * (A01 + z * (A02 + z * A03))

/*  Computes a Remez approximation for cos(pi x) on [-2^-7, 2^-7].            */
TMPL_CONST_FUNC
TMPL_STATIC_INLINE
double tmpl_Double_CosPi_Remez_Small(const double x)
TMPL_UNSEQUENCED
{
    /*  cospi is even, the polynomial is in terms of x^{2n} = (x^2)^n.        */
    const double x2 = x * x;

    /*  Evaluate the polynomial using Horner's method and return.             */
    const double poly = TMPL_POLY_EVAL(x2);
    return 1.0 + x2 * poly;
}
/*  End of tmpl_Double_CosPi_Remez_Small.                                     */

/*  Undefine everything to avoid collisions with other macros.                */
#include "tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
