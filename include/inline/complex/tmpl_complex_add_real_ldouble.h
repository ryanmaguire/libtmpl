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
 *                        tmpl_complex_add_real_ldouble                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for complex addition.                        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CLDouble_Add_Real                                                *
 *  Purpose:                                                                  *
 *      Adds a real number to a complex one.                                  *
 *                                                                            *
 *          w = z + x                                                         *
 *            = (a + ib) + x                                                  *
 *            = (a + x) + ib                                                  *
 *                                                                            *
 *  Arguments:                                                                *
 *      x (const long double):                                                *
 *          The real number we wish to add to z.                              *
 *      z (const tmpl_ComplexLongDouble):                                     *
 *          A complex number.                                                 *
 *  Output:                                                                   *
 *      sum (tmpl_ComplexLongDouble):                                         *
 *          The sum of z and x.                                               *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Add the real-valued input to the real part of the complex number.     *
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
 *          Header file where the TMPL_INLINE_DECL macro is found.            *
 *  2.) tmpl_complex_ldouble.h:                                               *
 *          Header providing long double precision complex numbers.           *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 16, 2021                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2020/12/03: Ryan Maguire                                                  *
 *      Created function (Wellesley college for librssringoccs).              *
 *      Moved here from rss_ringoccs_complex_add.c.                           *
 *      Frozen for v1.3 of rss_ringoccs.                                      *
 *  2021/02/16: Ryan Maguire                                                  *
 *      Copied from rss_ringoccs.                                             *
 *      Made compatible with libtmpl.                                         *
 *      Soft freeze for alpha release of libtmpl.                             *
 *  2021/06/26: Ryan Maguire                                                  *
 *      Hard freeze for alpha release of libtmpl. Reviewed code and comments. *
 *      No more changes unless something breaks.                              *
 *  2023/02/06: Ryan Maguire                                                  *
 *      Moved float and long double to their own files. Inlined routines.     *
 *      Updated and added comments.                                           *
 *  2023/07/08: Ryan Maguire                                                  *
 *      Changed src/complex/tmpl_complex_add_real_ldouble.c to use this file. *
 *  2024/12/15: Ryan Maguire                                                  *
 *      Added references. Changed include to "tmpl_complex_ldouble.h".        *
 *  2026/01/08: Ryan Maguire                                                  *
 *      Added const qualifiers to arguments and cleaned up a bit.             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COMPLEX_ADD_REAL_LDOUBLE_H
#define TMPL_COMPLEX_ADD_REAL_LDOUBLE_H

/*  TMPL_INLINE_DECL macro found here.                                        */
#include <libtmpl/include/tmpl_config.h>

/*  Complex numbers provided here.                                            */
#include <libtmpl/include/types/tmpl_complex_ldouble.h>

/*  In C99, since _Complex is a built-in data type, long doubles and _Complex *
 *  long doubles can be added via x + z. With C89 we use structs to define    *
 *  complex numbers. Since we can't add a long double to a struct, we need a  *
 *  function for computing the sum of complex numbers with real ones.         */

/*  Long double precision complex addition where one variable is real.        */
TMPL_INLINE_DECL
tmpl_ComplexLongDouble
tmpl_CLDouble_Add_Real(const long double x, const tmpl_ComplexLongDouble z)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_ComplexLongDouble sum;

    /*  Add the value to the real part of the complex number and return.      */
    sum.dat[0] = z.dat[0] + x;
    sum.dat[1] = z.dat[1];
    return sum;
}
/*  End of tmpl_CLDouble_Add_Real.                                            */

#endif
/*  End of include guard.                                                     */
