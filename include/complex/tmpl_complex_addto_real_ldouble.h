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
 *                       tmpl_complex_addto_real_ldouble                      *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for complex addition.                        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CLDouble_AddTo_Real                                              *
 *  Purpose:                                                                  *
 *      Adds a complex number with a real one:                                *
 *                                                                            *
 *          z + x = (a + ib) + x                                              *
 *                = (a + x) + ib                                              *
 *                                                                            *
 *  Arguments:                                                                *
 *      z (tmpl_ComplexLongDouble * const):                                   *
 *          A pointer to a complex number. The sum is stored here.            *
 *      x (lnog double):                                                      *
 *          A real number.                                                    *
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
 *              tmpl_CLDouble_AddTo_Real(&z, x)                               *
 *          instead of writing:                                               *
 *              z = tmpl_CLDouble_Add_Real(x, z).                             *
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
 *  Date:       February 6, 2023                                              *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/07/10: Ryan Maguire                                                  *
 *      Changed src/complex/tmpl_complex_addto_real_ldouble.c to include this.*
 *  2024/12/16: Ryan Maguire                                                  *
 *      Added references. Changed include to "tmpl_complex_ldouble.h".        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COMPLEX_ADDTO_REAL_LDOUBLE_H
#define TMPL_COMPLEX_ADDTO_REAL_LDOUBLE_H

/*  TMPL_INLINE_DECL found here.                                              */
#include <libtmpl/include/tmpl_config.h>

/*  Complex numbers provided here.                                            */
#include <libtmpl/include/tmpl_complex_ldouble.h>

/*  In C99, since _Complex is a built-in data type, given long double         *
 *  _Complex z and long double x, you can just do z += x. With C89 we use     *
 *  structs to define complex numbers. Structs cannot be added, so we need a  *
 *  function for computing the sum.                                           */

/*  Long double precision complex addition. Equivalent of += operation.       */
TMPL_INLINE_DECL
void tmpl_CLDouble_AddTo_Real(tmpl_ComplexLongDouble * const z, long double x)
{
    /*  Add the value to the real part of the complex number.                 */
    z->dat[0] += x;
}
/*  End of tmpl_CLDouble_AddTo_Real.                                          */

#endif
/*  End of include guard.                                                     */
