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
 *                     tmpl_complex_conjugateself_double                      *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for the complex conjugate.                   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CDouble_ConjugateSelf                                            *
 *  Purpose:                                                                  *
 *      Computes the complex conjugate of a complex number.                   *
 *                                                                            *
 *          conj(z) = conj(x + iy) = x - iy                                   *
 *                                                                            *
 *  Arguments:                                                                *
 *      z (tmpl_ComplexDouble *):                                             *
 *          A pointer to a complex number.                                    *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Negate the imaginary part of z and return.                            *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file where TMPL_INLINE_DECL is found.                      *
 *  2.) tmpl_complex_double.h:                                                *
 *          Header providing double precision complex numbers.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 07, 2023                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/07/10: Ryan Maguire                                                  *
 *      Changed src/complex/tmpl_complex_conjugateself_double.c to use this.  *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COMPLEX_CONJUGATESELF_DOUBLE_H
#define TMPL_COMPLEX_CONJUGATESELF_DOUBLE_H

/*  TMPL_INLINE_DECL macro found here.                                        */
#include <libtmpl/include/tmpl_config.h>

/*  Complex numbers provided here.                                            */
#include <libtmpl/include/types/tmpl_complex_double.h>

/*  Double precision complex conjugate function.                              */
TMPL_INLINE_DECL
void tmpl_CDouble_ConjugateSelf(tmpl_ComplexDouble *z)
{
    /*  The complex conjugate of x + iy is x - iy. Negate the imagary part.   */
    z->dat[1] = -z->dat[1];
}
/*  End of tmpl_CDouble_Conjugate.                                            */

#endif
/*  End of include guard.                                                     */
