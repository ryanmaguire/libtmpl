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
 *                     tmpl_vec3_l2_norm_squared_ldouble                      *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for the square of the Euclidean norm.                   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DLDouble_L2_Norm_Squared                                        *
 *  Purpose:                                                                  *
 *      Computes the square of the Euclidean norm.                            *
 *  Arguments:                                                                *
 *      P (const tmpl_ThreeVectorLongDouble * const):                         *
 *          A pointer to a vector in R^3.                                     *
 *  Output:                                                                   *
 *      norm_sq (long double):                                                *
 *          The square of the Euclidean norm of P.                            *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Compute the sum of the squares and return.                            *
 *  Notes:                                                                    *
 *      No checks for Infs or NaNs are performed.                             *
 *      No checks for Null pointers are performed.                            *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Location of the TMPL_INLINE_DECL macro.                           *
 *  2.) tmpl_vec3_ldouble.h:                                                  *
 *          Header containing ThreeVector typedef.                            *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 12, 2024                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC3_L2_NORM_SQUARED_LDOUBLE_H
#define TMPL_VEC3_L2_NORM_SQUARED_LDOUBLE_H

/*  TMPL_INLINE_DECL macro provided here.                                     */
#include <libtmpl/include/tmpl_config.h>

/*  ThreeVector typedef given here.                                           */
#include <libtmpl/include/tmpl_vec3_ldouble.h>

/*  Function for computing the square of the Euclidean norm.                  */
TMPL_INLINE_DECL
long double
tmpl_3DLDouble_L2_Norm_Squared(const tmpl_ThreeVectorLongDouble * const P)
{
    return P->dat[0]*P->dat[0] + P->dat[1]*P->dat[1] + P->dat[2]*P->dat[2];
}
/*  End of tmpl_3DLDouble_L2_Norm_Squared.                                    */

#endif
/*  End of include guard.                                                     */
