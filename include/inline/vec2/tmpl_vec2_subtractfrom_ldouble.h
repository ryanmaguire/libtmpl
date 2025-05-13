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
 *                       tmpl_vec2_subtractfrom_ldouble                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      In-place vector subtraction for single precision 2D vectors.          *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_2DLDouble_SubtractFrom                                           *
 *  Purpose:                                                                  *
 *      Subtracts two points in the plane component-wise and in-place.        *
 *  Arguments:                                                                *
 *      P (tmpl_TwoVectorLongDouble * const):                                 *
 *          A pointer to a point in the plane. The difference is stored here. *
 *      Q (const tmpl_TwoVectorLongDouble * const):                           *
 *          Another point in the Euclidean plane.                             *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Vector subtraction is done component-wise. That is, if P = (a, b) and *
 *      Q = (c, d), then the vector difference is given by:                   *
 *                                                                            *
 *          diff = P - Q                                                      *
 *               = (a, b) - (c, d)                                            *
 *               = (a - c, b - d)                                             *
 *                                                                            *
 *      In other words:                                                       *
 *                                                                            *
 *          x = a - c                                                         *
 *          y = b - d                                                         *
 *                                                                            *
 *      We perform these differences, storing the result in P.                *
 *  Notes:                                                                    *
 *      1.) There are no checks for NULL pointers. It is assumed P and Q are  *
 *          valid pointers to 2D vectors.                                     *
 *      2.) This function is the "-=" operator for tmpl_TwoVectorLongDouble.  *
 *          That is, the function performs P -= Q.                            *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Location of the TMPL_INLINE_DECL macro.                           *
 *  2.) tmpl_vec2_ldouble.h:                                                  *
 *          The tmpl_TwoVectorLongDouble typedef is provided here.            *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 13, 2025                                                  *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC2_SUBTRACTFROM_LDOUBLE_H
#define TMPL_VEC2_SUBTRACTFROM_LDOUBLE_H

/*  The TMPL_INLINE_DECL macro is provided here.                              */
#include <libtmpl/include/tmpl_config.h>

/*  Two-vector typedef found here.                                            */
#include <libtmpl/include/types/tmpl_vec2_ldouble.h>

/*  Function for subtracting 2 two-dimensional vectors in-place.              */
TMPL_INLINE_DECL
void
tmpl_2DLDouble_SubtractFrom(tmpl_TwoVectorLongDouble * const P,
                            const tmpl_TwoVectorLongDouble * const Q)
{
    /*  The difference of two vectors simply subtracts their components.      */
    P->dat[0] -= Q->dat[0];
    P->dat[1] -= Q->dat[1];
}
/*  End of tmpl_2DLDouble_SubtractFrom.                                       */

#endif
/*  End of include guard.                                                     */
