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
 *                        tmpl_complex_subtract_ldouble                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for complex subtraction.                     *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CLDouble_Subtract                                                *
 *  Purpose:                                                                  *
 *      Subtracts two complex numbers:                                        *
 *                                                                            *
 *          z - w = (a + ib) - (c + id)                                       *
 *                = (a - c) + i(b - d)                                        *
 *                                                                            *
 *  Arguments:                                                                *
 *      z (const tmpl_ComplexLongDouble):                                     *
 *          A complex number.                                                 *
 *      w (const tmpl_ComplexLongDouble):                                     *
 *          Another complex number.                                           *
 *  Output:                                                                   *
 *      diff (tmpl_ComplexLongDouble):                                        *
 *          The difference of z and w.                                        *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Subtract the components and return.                                   *
 *  Notes:                                                                    *
 *      1.) No checks for NaN or infinity are made.                           *
 *                                                                            *
 *      2.) A lot of the complex number code was originally written for       *
 *          rss_ringoccs, but has since migrated to libtmpl.                  *
 *          librssringoccs is also released under the GPLv3.                  *
 *  References:                                                               *
 *      1.) https://en.wikipedia.org/wiki/complex_number                      *
 *                                                                            *
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
 *          Header providing long double precision complex numbers.           *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 30, 2020                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2026/01/15: Ryan Maguire                                                  *
 *      Moved float and long double to their own files, inlined the function. *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COMPLEX_SUBTRACT_LDOUBLE_H
#define TMPL_COMPLEX_SUBTRACT_LDOUBLE_H

/*  TMPL_INLINE_DECL found here.                                              */
#include <libtmpl/include/tmpl_config.h>

/*  Complex numbers provided here.                                            */
#include <libtmpl/include/types/tmpl_complex_float.h>

/*  In C99, since _Complex is a built-in data type, given                     *
 *  long double _Complex z and long double _Complex w, you can just do z - w. *
 *  With C89 we use structs to define complex numbers. Structs cannot be      *
 *  subtracted, so we need a function for computing the difference of two     *
 *  complex numbers.                                                          */

/*  Long double precision complex subtraction.                                */
TMPL_INLINE_DECL
tmpl_ComplexLongDouble
tmpl_CLDouble_Subtract(const tmpl_ComplexLongDouble z,
                       const tmpl_ComplexLongDouble w)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexLongDouble diff;

    /*  The difference of two complex numbers simply subtracts the components.*/
    diff.dat[0] = z.dat[0] - w.dat[0];
    diff.dat[1] = z.dat[1] - w.dat[1];
    return diff;
}
/*  End of tmpl_CLDouble_Subtract.                                            */

#endif
/*  End of include guard.                                                     */
