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
 *                        tmpl_vec3_projection_ldouble                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for vector projection at long double precision.         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DLDouble_Projection                                             *
 *  Purpose:                                                                  *
 *      Computes the projection of one vector along another.                  *
 *  Arguments:                                                                *
 *      P (const tmpl_ThreeVectorLongDouble * const):                         *
 *          A pointer to a vector in R^3.                                     *
 *      Q (const tmpl_ThreeVectorLongDouble * const):                         *
 *          Another pointer to a vector in R^3.                               *
 *  Output:                                                                   *
 *      proj (long double):                                                   *
 *          The projection of P along Q.                                      *
 *  Called Functions:                                                         *
 *      tmpl_vec3.h:                                                          *
 *          tmpl_3DLDouble_Normalize:                                         *
 *              Normalizes a vector to unit magnitude.                        *
 *          tmpl_3DLDouble_Dot_Product:                                       *
 *              Computes the dot product of two vectors.                      *
 *  Method:                                                                   *
 *      Normalize Q to unit magnitude and then return the dot product with P. *
 *  Notes:                                                                    *
 *      No checks for Infs or NaNs are performed.                             *
 *      No checks for Null pointers are performed.                            *
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
#ifndef TMPL_VEC3_PROJECTION_LDOUBLE_H
#define TMPL_VEC3_PROJECTION_LDOUBLE_H

/*  The TMPL_INLINE_DECL macro is provided here.                              */
#include <libtmpl/include/tmpl_config.h>

/*  Three-vector typedef found here.                                          */
#include <libtmpl/include/tmpl_vec3.h>

/*  Function for computing the projection of one vector onto another.         */
TMPL_INLINE_DECL
long double
tmpl_3DLDouble_Projection(const tmpl_ThreeVectorLongDouble * const P,
                          const tmpl_ThreeVectorLongDouble * const Q)
{
    /*  To avoid overflow, or underflow, normalize Q.                         */
    const tmpl_ThreeVectorLongDouble Qn = tmpl_3DLDouble_Normalize(Q);

    /*  With Q normalized, the projection is just the dot product.            */
    return tmpl_3DLDouble_Dot_Product(P, &Qn);
}
/*  End of tmpl_3DLDouble_Projection.                                         */

#endif
/*  End of include guard.                                                     */
