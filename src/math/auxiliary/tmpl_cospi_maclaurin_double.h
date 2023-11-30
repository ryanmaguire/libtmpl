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
 *                     tmpl_cospi_maclaurin_double_inline                     *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of cos(pi x) at double precision.       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_CosPi_Maclaurin                                           *
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of cos(pi x) for small values x.        *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      cos_pix (double):                                                     *
 *          The Maclaurin series of cos(pi x).                                *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomial.                       *
 *                                                                            *
 *                        infty                                               *
 *                        -----                                               *
 *                        \        (-1)^n pi^{2n}                             *
 *          cos(pi x) =   /        -------------- * x^{2n}                    *
 *                        -----         (2n)!                                 *
 *                        n = 0                                               *
 *                                                                            *
 *      Use the first 5 terms (0 <= n <= 4) and compute.                      *
 *  Notes:                                                                    *
 *      Only accurate for values near 0.                                      *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_USE_INLINE macro.                     *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 24, 2022                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COSPI_MACLAURIN_DOUBLE_H
#define TMPL_COSPI_MACLAURIN_DOUBLE_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the Maclaurin series at double precision.                */
#define A0 (+1.0000000000000000000000000000000000000000E+00)
#define A1 (-4.9348022005446793094172454999380755676568E+00)
#define A2 (+4.0587121264167682181850138620293796354053E+00)
#define A3 (-1.3352627688545894958753047828505831928711E+00)
#define A4 (+2.3533063035889320454187935277546542154507E-01)

/*  Maclaurin series for cos(pi x), double precision, to 5 terms.             */
TMPL_STATIC_INLINE
double tmpl_Double_CosPi_Maclaurin(double x)
{
    /*  Declare necessary variables.                                          */
    const double x2 = x*x;

    /*  Use Horner's method to compute the polynomial.                        */
    return A0 + x2*(A1 + x2*(A2 + x2*(A3 + x2*A4)));
}
/*  End of tmpl_Double_CosPi_Maclaurin.                                       */

/*  Undefine the coefficients in case someone wants to #include this file.    */
#undef A0
#undef A1
#undef A2
#undef A3
#undef A4

#endif
/*  End of include guard.                                                     */
