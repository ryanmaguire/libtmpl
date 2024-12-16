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
 *                         tmpl_complex_addto_double                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for complex addition.                        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CDouble_AddTo                                                    *
 *  Purpose:                                                                  *
 *      Adds two complex numbers:                                             *
 *                                                                            *
 *          z + w = (a + ib) + (c + id)                                       *
 *                = (a + c) + i(b + d)                                        *
 *                                                                            *
 *  Arguments:                                                                *
 *      z (tmpl_ComplexDouble * const):                                       *
 *          A pointer to a complex number. The sum is stored here.            *
 *      w (const tmpl_ComplexDouble * const):                                 *
 *          Another complex number.                                           *
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
 *              tmpl_CDouble_AddTo(&z, &w)                                    *
 *          instead of writing:                                               *
 *              z = tmpl_CDouble_Add(z, w).                                   *
 *          Some benchmarks show this can up to 2x faster, depending on       *
 *          compiler and hardware.                                            *
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
 *          Header where complex types are defined.                           *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 8, 2022                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/02/06: Ryan Maguire                                                  *
 *      Moved float and long double versions to their own files.              *
 *  2023/07/08: Ryan Maguire                                                  *
 *      Changed src/complex/tmpl_complex_addto_double.c to include this file. *
 *  2024/12/15: Ryan Maguire                                                  *
 *      Added references. Changed include to "tmpl_complex_double.h".         *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COMPLEX_ADDTO_DOUBLE_H
#define TMPL_COMPLEX_ADDTO_DOUBLE_H

/*  TMPL_INLINE_DECL found here.                                              */
#include <libtmpl/include/tmpl_config.h>

/*  Complex numbers provided here.                                            */
#include <libtmpl/include/tmpl_complex_double.h>

/*  In C99, since _Complex is a built-in data type, given double _Complex z0  *
 *  and double _Complex z1, you can just do z0 += z1. With C89 we use structs *
 *  to define complex numbers. Structs cannot be added, so we need a function *
 *  for computing the sum of two complex values.                              */

/*  Double precision complex addition. Equivalent of += operation.            */
TMPL_INLINE_DECL
void
tmpl_CDouble_AddTo(tmpl_ComplexDouble * const z,
                   const tmpl_ComplexDouble * const w)
{
    /*  Complex addition is done component-wise.                              */
    z->dat[0] += w->dat[0];
    z->dat[1] += w->dat[1];
}
/*  End of tmpl_CDouble_AddTo.                                                */

#endif
/*  End of include guard.                                                     */
