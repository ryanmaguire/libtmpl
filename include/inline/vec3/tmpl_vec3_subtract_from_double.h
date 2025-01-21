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
 *                       tmpl_vec3_subtract_from_double                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for performing vector subtraction at double precision.  *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DDouble_SubtractFrom                                            *
 *  Purpose:                                                                  *
 *      Computes the vector difference of two vectors at double precision.    *
 *  Arguments:                                                                *
 *      target (tmpl_ThreeVectorDouble * const):                              *
 *          A pointer to a vector in R^3. The difference will be stored here. *
 *      source (const tmpl_ThreeVectorDouble * const):                        *
 *          Another pointer to a vector in R^3.                               *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use the definition of vector subtraction. If P = (Px, Py, Pz) and     *
 *      Q = (Qx, Qy, Qz), then the vector difference P-Q has coordinates:     *
 *          x = Px - Qx                                                       *
 *          y = Py - Qy                                                       *
 *          z = Pz - Qz                                                       *
 *  Notes:                                                                    *
 *      No checks for Infs or NaNs are performed.                             *
 *      No checks for Null pointers are performed.                            *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Location of the TMPL_INLINE_DECL macro.                           *
 *  2.) tmpl_vec3_double.h:                                                   *
 *          The tmpl_ThreeVectorDouble typedef is provided here.              *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 11, 2024                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC3_SUBTRACT_FROM_DOUBLE_H
#define TMPL_VEC3_SUBTRACT_FROM_DOUBLE_H

/*  The TMPL_INLINE_DECL macro is provided here.                              */
#include <libtmpl/include/tmpl_config.h>

/*  Three-vector typedef found here.                                          */
#include <libtmpl/include/types/tmpl_vec3_double.h>

/*  Function for performing vector subtraction in R^3.                        */
TMPL_INLINE_DECL
void
tmpl_3DDouble_SubtractFrom(tmpl_ThreeVectorDouble * const target,
                           const tmpl_ThreeVectorDouble * const source)
{
    target->dat[0] -= source->dat[0];
    target->dat[1] -= source->dat[1];
    target->dat[2] -= source->dat[2];
}
/*  End of tmpl_3DDouble_SubtractFrom.                                        */

#endif
/*  End of include guard.                                                     */
