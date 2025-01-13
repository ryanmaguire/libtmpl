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
 *                       tmpl_complex_addto_imag_double                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for complex addition.                        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CDouble_AddTo_Imag                                               *
 *  Purpose:                                                                  *
 *      Adds a complex number with an imaginary one:                          *
 *                                                                            *
 *          z + iy = (a + ib) + iy                                            *
 *                 = a + i(b + y)                                             *
 *                                                                            *
 *  Arguments:                                                                *
 *      z (tmpl_ComplexDouble * const):                                       *
 *          A pointer to a complex number. The sum is stored here.            *
 *      y (double):                                                           *
 *          An imaginary number.                                              *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Compute the component-wise sum and store it in the first pointer.     *
 *  Notes:                                                                    *
 *      1.) No checks for NaN or infinity are made.                           *
 *      2.) No checks for NULL pointers are made.                             *
 *      3.) A lot of the complex number code was originally written for       *
 *          rss_ringoccs, but has since migrated to libtmpl.                  *
 *          librssringoccs is also released under the GPLv3.                  *
 *      4.) This provides a "+=" operator. It is faster to use:               *
 *              tmpl_CDouble_AddTo_Imag(&z, y)                                *
 *          instead of writing:                                               *
 *              z = tmpl_CDouble_Add_Imag(y, z).                              *
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
 *  Date:       February 6, 2023                                              *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/07/10: Ryan Maguire                                                  *
 *      Changed src/complex/tmpl_complex_addto_imag_double.c to include this. *
 *  2024/12/16: Ryan Maguire                                                  *
 *      Added references. Changed include to "tmpl_complex_double.h".         *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COMPLEX_ADDTO_IMAG_DOUBLE_H
#define TMPL_COMPLEX_ADDTO_IMAG_DOUBLE_H

/*  TMPL_INLINE_DECL found here.                                              */
#include <libtmpl/include/tmpl_config.h>

/*  Complex numbers provided here.                                            */
#include <libtmpl/include/types/tmpl_complex_double.h>

/*  In C99, since _Complex is a built-in data type, given double _Complex z   *
 *  and double y, you can just do z += _Complex_I*y. With C89 we use structs  *
 *  to define complex numbers. Structs cannot be added, so we need a function *
 *  for computing the sum.                                                    */

/*  Double precision complex addition. Equivalent of += operation.            */
TMPL_INLINE_DECL
void tmpl_CDouble_AddTo_Imag(tmpl_ComplexDouble * const z, double y)
{
    /*  Add the value to the imaginary part of the complex number.            */
    z->dat[1] += y;
}
/*  End of tmpl_CDouble_AddTo_Imag.                                           */

#endif
/*  End of include guard.                                                     */
