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
 *                      tmpl_vec3_scaled_add_to_ldouble                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for performing vector addition at long double precision.*
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DLDouble_Scaled_AddTo                                           *
 *  Purpose:                                                                  *
 *      Computes the affine transformation P += a*Q.                          *
 *  Arguments:                                                                *
 *      P (tmpl_ThreeVectorLongDouble * const):                               *
 *          A pointer to a vector in R^3. The sum is stored here.             *
 *      a (long double):                                                      *
 *          Scale factor for Q.                                               *
 *      Q (const tmpl_ThreeVectorLongDouble * const):                         *
 *          Another pointer to a vector in R^3.                               *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use the definition of vector addition. If P = (Px, Py, Pz) and        *
 *      Q = (Qx, Qy, Qz), then the vector sum P + a*Q has coordinates:        *
 *          x = Px + a*Qx                                                     *
 *          y = Py + a*Qy                                                     *
 *          z = Pz + a*Qz                                                     *
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
 *  Date:       June 11, 2024                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC3_SCALED_ADD_TO_LDOUBLE_H
#define TMPL_VEC3_SCALED_ADD_TO_LDOUBLE_H

/*  The TMPL_INLINE_DECL macro is provided here.                              */
#include <libtmpl/include/tmpl_config.h>

/*  Three-vector typedef found here.                                          */
#include <libtmpl/include/types/tmpl_vec3_ldouble.h>

/*  Function for performing affine transformations.                           */
TMPL_INLINE_DECL
void
tmpl_3DLDouble_Scaled_AddTo(tmpl_ThreeVectorLongDouble * const P, long double a,
                            const tmpl_ThreeVectorLongDouble * const Q)
{
    /*  Affine transformation, add scaled components of Q to P.               */
    P->dat[0] += a*Q->dat[0];
    P->dat[1] += a*Q->dat[1];
    P->dat[2] += a*Q->dat[2];
}
/*  End of tmpl_3DLDouble_Scaled_AddTo.                                       */

#endif
/*  End of include guard.                                                     */
