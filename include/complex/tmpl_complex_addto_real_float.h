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
 *                       tmpl_complex_addto_real_float                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for complex addition.                        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CFloat_AddTo_Real                                                *
 *  Purpose:                                                                  *
 *      Adds a complex number with a real one:                                *
 *                                                                            *
 *          z + x = (a + ib) + x = (a + x) + ib                               *
 *                                                                            *
 *  Arguments:                                                                *
 *      z (tmpl_ComplexFloat *):                                              *
 *          A pointer to a complex number. The sum is stored here.            *
 *      x (float):                                                            *
 *          A real number.                                                    *
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
 *      Changed src/complex/tmpl_complex_addto_real_float.c to include this.  *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COMPLEX_ADDTO_REAL_FLOAT_H
#define TMPL_COMPLEX_ADDTO_REAL_FLOAT_H

/*  TMPL_INLINE_DECL found here.                                              */
#include <libtmpl/include/tmpl_config.h>

/*  Where the prototypes are declared and where complex types are defined.    */
#include <libtmpl/include/tmpl_complex.h>

/*  In C99, since _Complex is a built-in data type, given float _Complex z    *
 *  and float x, you can just do z += x. With C89 we use structs to define    *
 *  complex numbers. Structs cannot be added, so we need a function.          */

/*  Single precision complex addition. Equivalent of += operation.            */
TMPL_INLINE_DECL
void tmpl_CFloat_AddTo_Real(tmpl_ComplexFloat * const z, float x)
{
    /*  Add the value to the real part of the complex number.                 */
    z->dat[0] += x;
}
/*  End of tmpl_CFloat_AddTo_Real.                                            */

#endif
/*  End of include guard.                                                     */
