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
 *                        tmpl_two_vector_addto_ldouble                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      In-place vector addition for long double precision 2D vectors.        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_2DLDouble_AddTo                                                  *
 *  Purpose:                                                                  *
 *      Adds two points in the plane component-wise and in-place.             *
 *  Arguments:                                                                *
 *      P (tmpl_TwoVectorLongDouble * const):                                 *
 *          A pointer to a point in the plane. The sum is stored here.        *
 *      Q (const tmpl_TwoVectorLongDouble * const):                           *
 *          Another point in the Euclidean plane.                             *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Vector addition is done component-wise. That is, if P = (a, b) and    *
 *      Q = (c, d), then the vector sum is given by:                          *
 *                                                                            *
 *          sum = P + Q                                                       *
 *              = (a, b) + (c, d)                                             *
 *              = (a + c, b + d)                                              *
 *                                                                            *
 *      In other words:                                                       *
 *                                                                            *
 *          x = a + c                                                         *
 *          y = b + d                                                         *
 *                                                                            *
 *      We perform these sums, storing the result in P.                       *
 *  Notes:                                                                    *
 *      1.) There are no checks for NULL pointers. It is assumed P and Q are  *
 *          valid pointers to 2D vectors.                                     *
 *      2.) This function is the "+=" operator for tmpl_TwoVectorLongDouble.  *
 *          That is, the function performs P += Q.                            *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Location of the TMPL_INLINE_DECL macro.                           *
 *  2.) tmpl_vec2_ldouble.h:                                                  *
 *          The tmpl_TwoVectorLongDouble typedef is provided here.            *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 1, 2025                                                   *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC2_ADDTO_LDOUBLE_H
#define TMPL_VEC2_ADDTO_LDOUBLE_H

/*  The TMPL_INLINE_DECL macro is provided here.                              */
#include <libtmpl/include/tmpl_config.h>

/*  Two-vector typedef found here.                                            */
#include <libtmpl/include/types/tmpl_vec2_ldouble.h>

/*  Function for adding 2 two-dimensional vectors in-place.                   */
TMPL_INLINE_DECL
void
tmpl_2DLDouble_AddTo(tmpl_TwoVectorLongDouble * const P,
                     const tmpl_TwoVectorLongDouble * const Q)
{
    /*  The sum of two vectors simply adds their components together.         */
    P->dat[0] += Q->dat[0];
    P->dat[1] += Q->dat[1];
}
/*  End of tmpl_2DLDouble_AddTo.                                              */

#endif
/*  End of include guard.                                                     */
