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
 *                     tmpl_complex_multiplyby_real_double                    *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for complex multiplication.                  *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CDouble_MultiplyBy_Real                                          *
 *  Purpose:                                                                  *
 *      Multiplies two complex numbers:                                       *
 *                                                                            *
 *          z * x = (a + ib) * x                                              *
 *                = ax + ibx                                                  *
 *                                                                            *
 *  Arguments:                                                                *
 *      z (tmpl_ComplexDouble * const):                                       *
 *          A pointer to a complex number, the product is stored here.        *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Multiplying by a real number is the same thing as scalar              *
 *      multiplication in the plane. We scale the components of z and return. *
 *  Notes:                                                                    *
 *      1.) No checks for NaN or infinity are made.                           *
 *      2.) No checks for NULL pointers are made.                             *
 *      3.) This provides a "*=" operator. It is faster to use:               *
 *              tmpl_CDouble_MultiplyBy_Real(&z, x)                           *
 *          instead of writing:                                               *
 *              z = tmpl_CDouble_Multiply_Real(x, z).                         *
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
 *  2.) tmpl_complex_double.h:                                                *
 *          Header providing double precision complex numbers.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 16, 2024                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COMPLEX_MULTIPLYBY_REAL_DOUBLE_H
#define TMPL_COMPLEX_MULTIPLYBY_REAL_DOUBLE_H

/*  TMPL_INLINE_DECL found here.                                              */
#include <libtmpl/include/tmpl_config.h>

/*  Complex numbers provided here.                                            */
#include <libtmpl/include/types/tmpl_complex_double.h>

/*  In C99, since _Complex is a built-in data type, given double _Complex z   *
 *  and double x, you can just do z * x. Structs cannot be multiplied so we   *
 *  need a function for computing this.                                       */

/*  Double precision complex multiplication. Equivalent of *= operation.      */
TMPL_INLINE_DECL
void
tmpl_CDouble_MultiplyBy_Real(tmpl_ComplexDouble * const z, double x)
{
    /*  Multiplying by a real number is just scalar multiplication.           */
    z->dat[0] *= x;
    z->dat[1] *= x;
}
/*  End of tmpl_CDouble_MultiplyBy_Real.                                      */

#endif
/*  End of include guard.                                                     */
