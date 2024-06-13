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
 *                      tmpl_vec3_quick_projection_float                      *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for vector projection at single precision.              *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DFloat_Quick_Projection                                         *
 *  Purpose:                                                                  *
 *      Computes the projection of one vector along another.                  *
 *  Arguments:                                                                *
 *      P (const tmpl_ThreeVectorFloat * const):                              *
 *          A pointer to a vector in R^3.                                     *
 *      Q (const tmpl_ThreeVectorFloat * const):                              *
 *          Another pointer to a vector in R^3.                               *
 *  Output:                                                                   *
 *      proj (float):                                                         *
 *          The projection of P along Q.                                      *
 *  Called Functions:                                                         *
 *      tmpl_vec3.h:                                                          *
 *          tmpl_3DFloat_L2_Norm_Squared:                                     *
 *              Computes the square of the L2 norm of a vector.               *
 *          tmpl_3DFloat_Dot_Product:                                         *
 *              Computes the dot product of two vectors.                      *
 *  Method:                                                                   *
 *      Divide the dot product of P and Q by ||Q||^2.                         *
 *  Notes:                                                                    *
 *      1.) No checks for Infs or NaNs are performed.                         *
 *      2.) No checks for Null pointers are performed.                        *
 *      3.) This method does not prevent overflow. If you are using vectors   *
 *          with very large components, use tmpl_3DFloat_Projection. That     *
 *          function safely handles overflow, but is slower.                  *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Location of the TMPL_INLINE_DECL macro.                           *
 *  2.) tmpl_vec3.h:                                                          *
 *          ThreeVector typedef and vector functions.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       July 13, 2024                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC3_QUICK_PROJECTION_FLOAT_H
#define TMPL_VEC3_QUICK_PROJECTION_FLOAT_H

/*  The TMPL_INLINE_DECL macro is provided here.                              */
#include <libtmpl/include/tmpl_config.h>

/*  Three-vector typedef found here.                                          */
#include <libtmpl/include/tmpl_vec3.h>

/*  Function for computing the projection of one vector onto another.         */
TMPL_INLINE_DECL
float
tmpl_3DFloat_Quick_Projection(const tmpl_ThreeVectorFloat * const P,
                              const tmpl_ThreeVectorFloat * const Q)
{
    /*  The projection is the dot product divided by ||Q||^2.                 */
    return tmpl_3DFloat_Dot_Product(P, Q) / tmpl_3DFloat_L2_Norm_Squared(Q);
}
/*  End of tmpl_3DFloat_Quick_Projection.                                     */

#endif
/*  End of include guard.                                                     */
