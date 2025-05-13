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
 *                          tmpl_vec2_scaleby_float                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      In-place scalar multiplication for single precision 2D vectors.       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_2DFloat_ScaleBy                                                  *
 *  Purpose:                                                                  *
 *      Performs scalar multiplication in-place for 2D vectors.               *
 *  Arguments:                                                                *
 *      P (tmpl_TwoVectorFloat * const):                                      *
 *          A pointer to a point in the plane. The product is stored here.    *
 *      r (float):                                                            *
 *          A real number, the scalar multiplier.                             *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Scalar multiplication is done component-wise. That is, if P = (a, b), *
 *      then the product is given by:                                         *
 *                                                                            *
 *          prod = r * P                                                      *
 *               = r * (a, b)                                                 *
 *               = (r*a, r*b)                                                 *
 *                                                                            *
 *      In other words:                                                       *
 *                                                                            *
 *          x = r * a                                                         *
 *          y = r * b                                                         *
 *                                                                            *
 *      We perform these products, storing the result in P.                   *
 *  Notes:                                                                    *
 *      1.) There are no checks for NULL pointers. It is assumed P is a valid *
 *          pointer to a 2D vector.                                           *
 *      2.) This function acts as the "*=" operator for tmpl_TwoVectorFloat.  *
 *          That is, the function performs P *= r.                            *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Location of the TMPL_INLINE_DECL macro.                           *
 *  2.) tmpl_vec2_float.h:                                                    *
 *          The tmpl_TwoVectorFloat typedef is provided here.                 *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 13, 2025                                                  *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC2_SCALEBY_FLOAT_H
#define TMPL_VEC2_SCALEBY_FLOAT_H

/*  The TMPL_INLINE_DECL macro is provided here.                              */
#include <libtmpl/include/tmpl_config.h>

/*  Two-vector typedef found here.                                            */
#include <libtmpl/include/types/tmpl_vec2_float.h>

/*  Function for scaling a 2D vector by a real number in-place.               */
TMPL_INLINE_DECL
void tmpl_2DFloat_ScaleBy(tmpl_TwoVectorFloat * const P, float r)
{
    /*  The scalar product of r and P scales the components.                  */
    P->dat[0] *= r;
    P->dat[1] *= r;
}
/*  End of tmpl_2DFloat_ScaleBy.                                              */

#endif
/*  End of include guard.                                                     */
