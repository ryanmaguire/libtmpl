/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
 *  under the terms of the GNU General Public License as published by         *
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
 *                       tmpl_vec3_multiply_by_ldouble                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for performing the Hadamard product.                    *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DLDouble_MultiplyBy                                             *
 *  Purpose:                                                                  *
 *      Computes the Hadamard product of two vectors at single precision.     *
 *  Arguments:                                                                *
 *      target (tmpl_ThreeVectorLongDouble * const):                          *
 *          A pointer to a vector in R^3. The product will be stored here.    *
 *      source (const tmpl_ThreeVectorLongDouble * const):                    *
 *          Another pointer to a vector in R^3.                               *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use the definition of Hadamard product. If P = (Px, Py, Pz) and       *
 *      Q = (Qx, Qy, Qz), then the product has coordinates:                   *
 *          x = Px * Qx                                                       *
 *          y = Py * Qy                                                       *
 *          z = Pz * Qz                                                       *
 *  Notes:                                                                    *
 *      No checks for Infs or NaNs are performed.                             *
 *      No checks for Null pointers are performed.                            *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Location of the TMPL_INLINE_DECL macro.                           *
 *  2.) tmpl_vec3_ldouble.h:                                                  *
 *          The tmpl_ThreeVectorLongDouble typedef is provided here.          *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 12, 2024                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC3_MULTIPLY_BY_LDOUBLE_H
#define TMPL_VEC3_MULTIPLY_BY_LDOUBLE_H

/*  The TMPL_INLINE_DECL macro is provided here.                              */
#include <libtmpl/include/tmpl_config.h>

/*  Three-vector typedef found here.                                          */
#include <libtmpl/include/types/tmpl_vec3_ldouble.h>

/*  Function for performing the Hadamard product in R^3.                      */
TMPL_INLINE_DECL
void
tmpl_3DLDouble_MultiplyBy(tmpl_ThreeVectorLongDouble * const target,
                          const tmpl_ThreeVectorLongDouble * const source)
{
    target->dat[0] *= source->dat[0];
    target->dat[1] *= source->dat[1];
    target->dat[2] *= source->dat[2];
}
/*  End of tmpl_3DLDouble_MultiplyBy.                                         */

#endif
/*  End of include guard.                                                     */
