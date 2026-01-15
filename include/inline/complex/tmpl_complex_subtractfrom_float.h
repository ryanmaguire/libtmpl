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
 *                      tmpl_complex_subtractfrom_float                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for complex subtraction.                     *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CFloat_SubtractFrom                                              *
 *  Purpose:                                                                  *
 *      Subtracts two complex numbers:                                        *
 *                                                                            *
 *          z - w = (a + ib) - (c + id)                                       *
 *                = (a - c) + i(b - d)                                        *
 *                                                                            *
 *  Arguments:                                                                *
 *      z (tmpl_ComplexFloat * const):                                        *
 *          A pointer to a complex number. The difference is stored here.     *
 *      w (const tmpl_ComplexFloat * const):                                  *
 *          Another complex number.                                           *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Compute the component-wise difference and store it in the first       *
 *      pointer.                                                              *
 *  Notes:                                                                    *
 *      1.) No checks for NaN or infinity are made.                           *
 *      2.) No checks for NULL pointers are made.                             *
 *      3.) A lot of the complex number code was originally written for       *
 *          rss_ringoccs, but has since migrated to libtmpl.                  *
 *          librssringoccs is also released under the GPLv3.                  *
 *      4.) This provides a "-=" operator. It is faster to use:               *
 *              tmpl_CFloat_SubtractFrom(&z, &w)                              *
 *          instead of writing:                                               *
 *              z = tmpl_CFloat_Subtract(z, w).                               *
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
 *  2.) tmpl_complex_float.h:                                                 *
 *          Header providing single precision complex numbers.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 15, 2026                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COMPLEX_SUBTRACTFROM_FLOAT_H
#define TMPL_COMPLEX_SUBTRACTFROM_FLOAT_H

/*  TMPL_INLINE_DECL found here.                                              */
#include <libtmpl/include/tmpl_config.h>

/*  Complex numbers provided here.                                            */
#include <libtmpl/include/types/tmpl_complex_float.h>

/*  In C99, since _Complex is a built-in data type, given float _Complex z0   *
 *  and float _Complex z1, you can just do z0 -= z1. With C89 we use structs  *
 *  to define complex numbers. Structs cannot be subtracted, so we need a     *
 *  function for computing the difference of two complex values.              */

/*  Single precision complex subtraction. Equivalent of -= operation.         */
TMPL_INLINE_DECL
void
tmpl_CFloat_SubtractFrom(tmpl_ComplexFloat * const z,
                         const tmpl_ComplexFloat * const w)
{
    /*  Complex subtraction is done component-wise.                           */
    z->dat[0] -= w->dat[0];
    z->dat[1] -= w->dat[1];
}
/*  End of tmpl_CFloat_SubtractFrom.                                          */

#endif
/*  End of include guard.                                                     */
