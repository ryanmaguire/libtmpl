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
 *                     tmpl_complex_quick_divide_ldouble                      *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for complex division.                        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CLDouble_Quick_Divide                                            *
 *  Purpose:                                                                  *
 *      Divides two complex numbers.                                          *
 *                                                                            *
 *          div(z, w) = z / w                                                 *
 *                                                                            *
 *  Arguments:                                                                *
 *      z (tmpl_ComplexLongDouble):                                           *
 *          A complex number.                                                 *
 *      w (tmpl_ComplexLongDouble):                                           *
 *          Another complex number.                                           *
 *  Output:                                                                   *
 *      quot (tmpl_ComplexLongDouble):                                        *
 *          The quotient z / w.                                               *
 *  Method:                                                                   *
 *      Use the standard division formula. We have:                           *
 *                                                                            *
 *           z    a + i b                                                     *
 *          --- = -------                                                     *
 *           w    c + i d                                                     *
 *                                                                            *
 *                          c - i d                                           *
 *              = (a + ib) ---------                                          *
 *                         c^2 + d^2                                          *
 *                                                                            *
 *                 ac + bd       bc - ad                                      *
 *              = --------- + i ---------                                     *
 *                c^2 + d^2     c^2 + d^2                                     *
 *                                                                            *
 *      We compute these and store them in the output complex number.         *
 *  Notes:                                                                    *
 *      1.) No error check is performed on the inputs. In particular, there   *
 *          are no checks for zero in the denominator, or NaNs or infinities. *
 *      2.) Division is not commutative. tmpl_CLDouble_Quick_Divide(z, w)     *
 *          returns z / w, and not w / z. That is, the first entry is divided *
 *          by the second one.                                                *
 *      3.) This function is much faster than tmpl_CLDouble_Divide, but it is *
 *          susceptible to underflow and overflow. Do not use this with       *
 *          complex numbers that have very small or very large components.    *
 *  References:                                                               *
 *      1.) https://en.wikipedia.org/wiki/complex_number                      *
 *                                                                            *
 *          Fair introduction to complex numbers provided here.               *
 *                                                                            *
 *      2.) Ahfors, L. (1979)                                                 *
 *          "Complex Analysis, Third Edition"                                 *
 *          McGraw-Hill, International Series in Pure and Applied Mathematics *
 *          Chapter 1 "The Algebra of Complex Numbers"                        *
 *          Section 1 "Arithmetic Operations"                                 *
 *                                                                            *
 *          Standard undergraduate textbook on complex analysis.              *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          TMPL_INLINE_DECL macro found here.                                *
 *  2.) tmpl_complex_ldouble.h:                                               *
 *          Header providing long double precision complex numbers.           *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 5, 2025                                                  *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COMPLEX_QUICK_DIVIDE_LDOUBLE_H
#define TMPL_COMPLEX_QUICK_DIVIDE_LDOUBLE_H

/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  Complex numbers provided here.                                            */
#include <libtmpl/include/types/tmpl_complex_ldouble.h>

/*  In C99, since _Complex is a built-in data type, given long double         *
 *  _Complex z and long double _Complex w, you can just do z / w. Structs     *
 *  cannot be divided so we need a function for computing this.               */

/*  Long double precision complex division without overflow/underflow checks. */
TMPL_INLINE_DECL
tmpl_ComplexLongDouble
tmpl_CLDouble_Quick_Divide(tmpl_ComplexLongDouble z, tmpl_ComplexLongDouble w)
{
    /*  Variable for the output, the quotient z / w.                          */
    tmpl_ComplexLongDouble quot;

    /*  The denominator is the square of the magnitude of w.                  */
    const long double factor = 1.0L / (w.dat[0]*w.dat[0] + w.dat[1]*w.dat[1]);

    /*  Use the standard division formula and return.                         */
    quot.dat[0] = (z.dat[0] * w.dat[0] + z.dat[1] * w.dat[1]) * factor;
    quot.dat[1] = (z.dat[1] * w.dat[0] - z.dat[0] * w.dat[1]) * factor;
    return quot;
}
/*  End of tmpl_CLDouble_Quick_Divide.                                        */

#endif
/*  End of include guard.                                                     */
