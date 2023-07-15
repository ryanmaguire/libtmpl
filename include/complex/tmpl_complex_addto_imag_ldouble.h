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
 *                      tmpl_complex_addto_imag_ldouble                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for complex addition.                        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CLDouble_AddTo_Imag                                              *
 *  Purpose:                                                                  *
 *      Adds a complex number with an imaginary one:                          *
 *                                                                            *
 *          z + iy = (a + ib) + iy = a + i(b + y)                             *
 *                                                                            *
 *  Arguments:                                                                *
 *      z (tmpl_ComplexLongDouble *):                                         *
 *          A pointer to a complex number. The sum is stored here.            *
 *      y (long double):                                                      *
 *          An imaginary number.                                              *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Compute the component-wise sum and store it in the first pointer.     *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Contains the TMPL_INLINE_DECL macro.                              *
 *  2.) tmpl_complex.h:                                                       *
 *          Header where complex types and function prototypes are defined.   *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 6, 2023                                              *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/07/10: Ryan Maguire                                                  *
 *      Changed src/complex/tmpl_complex_addto_imag_ldouble.c to include this.*
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COMPLEX_ADDTO_IMAG_LDOUBLE_H
#define TMPL_COMPLEX_ADDTO_IMAG_LDOUBLE_H

/*  TMPL_INLINE_DECL found here.                                              */
#include <libtmpl/include/tmpl_config.h>

/*  Where the prototypes are declared and where complex types are defined.    */
#include <libtmpl/include/tmpl_complex.h>

/*  In C99, since _Complex is a built-in data type, given long double         *
 *  _Complex z and long double y, you can just do z += _Complex_I*y. With C89 *
 *  we use structs to define complex numbers. Structs cannot be added, so we  *
 *  need a function for computing the sum.                                    */

/*  Long double precision complex addition. Equivalent of += operation.       */
TMPL_INLINE_DECL
void tmpl_CLDouble_AddTo_Imag(tmpl_ComplexLongDouble *z, long double y)
{
    /*  Add the value to the imaginary part of the complex number.            */
    z->dat[1] += y;
}
/*  End of tmpl_CLDouble_AddTo_Imag.                                          */

#endif
/*  End of include guard.                                                     */
