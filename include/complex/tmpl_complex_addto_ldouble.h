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
 *                         tmpl_complex_addto_ldouble                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for complex addition.                        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CLDouble_AddTo                                                   *
 *  Purpose:                                                                  *
 *      Adds two complex numbers:                                             *
 *                                                                            *
 *          z + w = (a + ib) + (c + id) = (a + c) + i(b + d)                  *
 *                                                                            *
 *  Arguments:                                                                *
 *      z (tmpl_ComplexLongDouble *):                                         *
 *          A pointer to a complex number. The sum is stored here.            *
 *      w (const tmpl_ComplexLongDouble *):                                   *
 *          Another complex number.                                           *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Compute the component-wise sum and store it in the first pointer.     *
 *  Notes:                                                                    *
 *      This provides a "+=" operator to tmpl_ComplexLongDouble. It is faster *
 *      to use tmpl_CLDouble_AddTo(&z, &w) instead of                         *
 *      z = tmpl_CLDouble_Add(z, w).                                          *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Contains the TMPL_INLINE_DECL macro.                              *
 *  2.) tmpl_complex.h:                                                       *
 *          Header where complex types and function prototypes are defined.   *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 8, 2022                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/02/06: Ryan Maguire                                                  *
 *      Moved float and long double versions to their own files.              *
 *  2023/07/08: Ryan Maguire                                                  *
 *      Changed src/complex/tmpl_complex_addto_ldouble.c to include this file.*
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COMPLEX_ADDTO_LDOUBLE_H
#define TMPL_COMPLEX_ADDTO_LDOUBLE_H

/*  TMPL_INLINE_DECL found here.                                              */
#include <libtmpl/include/tmpl_config.h>

/*  Where the prototypes are declared and where complex types are defined.    */
#include <libtmpl/include/tmpl_complex.h>

/*  In C99, since _Complex is a built-in data type, given two long double     *
 *  _Complex values z0 and z1, you can just do z0 += z1. With C89 we use      *
 *  structs to define complex numbers. Structs cannot be added, so we need a  *
 *  function for computing the sum of two complex values.                     */

/*  Long double precision complex addition. Equivalent of += operation.       */
TMPL_INLINE_DECL
void
tmpl_CLDouble_AddTo(tmpl_ComplexLongDouble *z, const tmpl_ComplexLongDouble *w)
{
    /*  Complex addition is done component-wise.                              */
    z->dat[0] += w->dat[0];
    z->dat[1] += w->dat[1];
}
/*  End of tmpl_CLDouble_AddTo.                                               */

#endif
/*  End of include guard.                                                     */
