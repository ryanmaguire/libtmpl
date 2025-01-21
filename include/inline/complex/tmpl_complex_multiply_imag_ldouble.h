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
 *                     tmpl_complex_multiply_imag_ldouble                     *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for complex multiplication.                  *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CLDouble_Multiply_Imag                                           *
 *  Purpose:                                                                  *
 *      Multiplies two complex numbers:                                       *
 *                                                                            *
 *          z * iy = (a + ib) * iy                                            *
 *                 = -by + ayi                                                *
 *                                                                            *
 *  Arguments:                                                                *
 *      y (long double):                                                      *
 *          An imaginary number.                                              *
 *      z (tmpl_ComplexLongDouble):                                           *
 *          A complex number.                                                 *
 *  Output:                                                                   *
 *      prod (tmpl_ComplexLongDouble):                                        *
 *          The product of z and iy.                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use the product formula, which is given by the distributive law and   *
 *      the property that i^2 = -1.                                           *
 *  Notes:                                                                    *
 *      1.) No checks for NaN or infinity are made.                           *
 *      2.) A lot of the complex number code was originally written for       *
 *          rss_ringoccs, but has since migrated to libtmpl.                  *
 *          librssringoccs is also released under the GPLv3.                  *
 *  References:                                                               *
 *      1.) https://en.wikipedia.org/wiki/complex_number                      *
 *      2.) Ahfors, L. (1979)                                                 *
 *          "Complex Analysis, Third Edition"                                 *
 *          McGraw-Hill, International Series in Pure and Applied Mathematics *
 *          Chapter 1 "The Algebra of Complex Numbers"                        *
 *          Section 1 "Arithmetic Operations"                                 *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Contains the TMPL_INLINE_DECL macro.                              *
 *  2.) tmpl_complex_ldouble.h:                                               *
 *          Header where complex types are defined.                           *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 18, 2021                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2021/02/18: Ryan Maguire                                                  *
 *      Created file.                                                         *
 *  2024/12/16: Ryan Maguire                                                  *
 *      Added inline version. Moved float and long double to their own files. *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COMPLEX_MULTIPLY_IMAG_LDOUBLE_H
#define TMPL_COMPLEX_MULTIPLY_IMAG_LDOUBLE_H

/*  TMPL_INLINE_DECL found here.                                              */
#include <libtmpl/include/tmpl_config.h>

/*  Complex numbers provided here.                                            */
#include <libtmpl/include/types/tmpl_complex_ldouble.h>

/*  In C99, since _Complex is a built-in type, given long double _Complex z   *
 *  and long double y, you can just do z * _Complex_I*y. With C89 we use      *
 *  structs to define complex numbers. Structs cannot be multiplied, so we    *
 *  need a function for computing the product.                                */

/*  Long double precision complex multiplication.                             */
TMPL_INLINE_DECL
tmpl_ComplexLongDouble
tmpl_CLDouble_Multiply_Imag(long double y, tmpl_ComplexLongDouble z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexLongDouble prod;

    /*  (a + ib) * yi = -by + ayi, compute and return.                        */
    prod.dat[0] = -z.dat[1] * y;
    prod.dat[1] = z.dat[0] * y;
    return prod;
}
/*  End of tmpl_CLDouble_Multiply_Imag.                                       */

#endif
/*  End of include guard.                                                     */
