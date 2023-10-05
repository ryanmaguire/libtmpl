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
 *                      tmpl_bessel_i0_maclaurin_double                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the Maclaurin expansion of I0(x) at double precision.        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Bessel_I0_Maclaurin                                       *
 *  Purpose:                                                                  *
 *      Computes the Maclaurin expansion of I0(x) for small x.                *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      I0_x (double):                                                        *
 *          The modified Bessel function I0 at x.                             *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Compute the Maclaurin series of I0(x) using Horner's method:          *
 *                                                                            *
 *                   infty                                                    *
 *                   -----                                                    *
 *                   \          x^2n                                          *
 *          I0(x) =  /      ------------                                      *
 *                   -----   (n!)^2 4^n                                       *
 *                   n = 0                                                    *
 *                                                                            *
 *      Use the first 9 terms (0 <= n <= 8) of this expansion to compute.     *
 *  Notes:                                                                    *
 *      For |x| < 0.5 this is accurate to double precision.                   *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_INLINE_DECL macro.                    *
 *  3.) tmpl_special_functions_real.h:                                        *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 10, 2022                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_BESSEL_I0_MACLAURIN_DOUBLE_H
#define TMPL_BESSEL_I0_MACLAURIN_DOUBLE_H

/*  TMPL_INLINE_DECL macro found here.                                        */
#include <libtmpl/include/tmpl_config.h>

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_special_functions_real.h>

/*  Coefficients for the polynomial.                                          */
#define A00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define A01 (+2.5000000000000000000000000000000000000000000000000E-01)
#define A02 (+1.5625000000000000000000000000000000000000000000000E-02)
#define A03 (+4.3402777777777777777777777777777777777777777777778E-04)
#define A04 (+6.7816840277777777777777777777777777777777777777778E-06)
#define A05 (+6.7816840277777777777777777777777777777777777777778E-08)
#define A06 (+4.7095027970679012345679012345679012345679012345679E-10)
#define A07 (+2.4028075495244394053917863441672965482489292013102E-12)
#define A08 (+9.3859669903298414273116654069035021415973796926178E-15)

/*  Helper macro for evaluating a polynomial with Horner's method.            */
#define TMPL_POLY_EVAL(z) \
A00+z*(A01+z*(A02+z*(A03+z*(A04+z*(A05+z*(A06+z*(A07+z*A08)))))))

/*  Compute the modified Bessel function I0 with a Maclaurin series.          */
TMPL_STATIC_INLINE
double tmpl_Double_Bessel_I0_Maclaurin(double x)
{
    /*  The function is even and the series is in terms of x^2.               */
    const double x2 = x*x;

    /*  Use Horner's method to compute and return.                            */
    return TMPL_POLY_EVAL(x2);
}
/*  End of tmpl_Double_Bessel_I0_Maclaurin.                                   */

/*  Undef everything in case someone wants to #include this file.             */
#undef TMPL_POLY_EVAL
#undef A00
#undef A01
#undef A02
#undef A03
#undef A04
#undef A05
#undef A06
#undef A07
#undef A08

#endif
/*  End of include guard.                                                     */
