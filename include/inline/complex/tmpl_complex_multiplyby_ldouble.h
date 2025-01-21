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
 *                      tmpl_complex_multiplyby_ldouble                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for complex multiplication.                  *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CLDouble_MultiplyBy                                              *
 *  Purpose:                                                                  *
 *      Multiplies two complex numbers:                                       *
 *                                                                            *
 *          z * w = (a + ib) * (c + id)                                       *
 *                = (ac + ibc + iad + i^2bd                                   *
 *                = (ac - bd) + i(bc + ad)                                    *
 *                                                                            *
 *  Arguments:                                                                *
 *      z (tmpl_ComplexLongDouble * const):                                   *
 *          A pointer to a complex number, the product is stored here.        *
 *      w (const tmpl_ComplexLongDouble * const):                             *
 *          Another pointer to a complex number.                              *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use the product formula, which is given by the distributive law and   *
 *      the property that i^2 = -1.                                           *
 *  Notes:                                                                    *
 *      1.) No checks for NaN or infinity are made.                           *
 *      2.) No checks for NULL pointers are made.                             *
 *      3.) This provides a "*=" operator. It is faster to use:               *
 *              tmpl_CLDouble_MultiplyBy(&z, &w)                              *
 *          instead of writing:                                               *
 *              z = tmpl_CLDouble_Multiply(z, w).                             *
 *          The improvement varies depending on compiler and architecture.    *
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
 *  Date:       December 16, 2024                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COMPLEX_MULTIPLYBY_LDOUBLE_H
#define TMPL_COMPLEX_MULTIPLYBY_LDOUBLE_H

/*  TMPL_INLINE_DECL found here.                                              */
#include <libtmpl/include/tmpl_config.h>

/*  Complex numbers provided here.                                            */
#include <libtmpl/include/types/tmpl_complex_ldouble.h>

/*  In C99, since _Complex is a built-in type, given long double _Complex z1  *
 *  and long double _Complex z2, you can just do z1 * z2. Structs cannot be   *
 *  multiplied so we need a function for computing this.                      */

/*  Long double precision complex multiplication. Equivalent of *= operation. */
TMPL_INLINE_DECL
void
tmpl_CLDouble_MultiplyBy(tmpl_ComplexLongDouble * const z,
                         const tmpl_ComplexLongDouble * const w)
{
    /*  Avoid overwriting data, save the real part of z.                      */
    const long double z_real = z->dat[0];

    /*  Multiplication is done using the distributive law and i^2 = -1.       */
    z->dat[0] = z->dat[0] * w->dat[0] - z->dat[1] * w->dat[1];
    z->dat[1] = z_real * w->dat[1] + z->dat[1] * w->dat[0];
}
/*  End of tmpl_CLDouble_MultiplyBy.                                          */

#endif
/*  End of include guard.                                                     */
