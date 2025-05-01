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
 *                      tmpl_two_vector_l2_dist_ldouble                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides the L2 (Euclidean) distance function in the Euclidean plane. *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_2DLDouble_L2_Dist                                                *
 *  Purpose:                                                                  *
 *      Computes the Euclidean distance between two points in the plane.      *
 *  Arguments:                                                                *
 *      P (const tmpl_TwoVectorLongDouble * const):                           *
 *          A pointer to a point in the Euclidean plane.                      *
 *      Q (const tmpl_TwoVectorLongDouble * const):                           *
 *          Another point in the Euclidean plane.                             *
 *  Output:                                                                   *
 *      dist (long double):                                                   *
 *          The distance between points P and Q.                              *
 *  Called Functions:                                                         *
 *      src/math/                                                             *
 *          tmpl_LDouble_Hypot:                                               *
 *              Computes the length of the line from (0, 0) to (x, y).        *
 *  Method:                                                                   *
 *      The distance between two points is given by the Pythagorean formula.  *
 *      That is, if P = (a, b) and Q = (c, d), then the distance is:          *
 *                                                                            *
 *          dist(P, Q) = || P - Q ||                                          *
 *                     = || (a, b) - (c, d) ||                                *
 *                     = || (a - c, b - d) ||                                 *
 *                     = sqrt((a - c)^2 + (b - d)^2)                          *
 *                                                                            *
 *      This is computed using the tmpl_LDouble_Hypot function.               *
 *  Notes:                                                                    *
 *      1.) There are no checks for NULL pointers. It is assumed P and Q are  *
 *          valid pointers to 2D vectors.                                     *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Location of the TMPL_INLINE_DECL macro.                           *
 *  2.) tmpl_vec2_ldouble.h:                                                  *
 *          The tmpl_TwoVectorLongDouble typedef is provided here.            *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 20, 2020                                            *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2025/05/01: Ryan Maguire                                                  *
 *      Inlined the function, added detailed docstring.                       *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC2_L2_DIST_LDOUBLE_H
#define TMPL_VEC2_L2_DIST_LDOUBLE_H

/*  The TMPL_INLINE_DECL macro is provided here.                              */
#include <libtmpl/include/tmpl_config.h>

/*  Two-vector typedef found here.                                            */
#include <libtmpl/include/types/tmpl_vec2_ldouble.h>

/*  Tell the compiler about the hypotenuse function.                          */
extern long double tmpl_LDouble_Hypot(long double x, long double y);

/*  Function for computing the Euclidean distance between two points.         */
TMPL_INLINE_DECL
long double
tmpl_2DLDouble_L2_Dist(const tmpl_TwoVectorLongDouble * const P,
                       const tmpl_TwoVectorLongDouble * const Q)
{
    /*  Use the Pythagorean formula on the vector P - Q.                      */
    return tmpl_LDouble_Hypot(P->dat[0] - Q->dat[0], P->dat[1] - Q->dat[1]);
}
/*  End of tmpl_2DLDouble_L2_Dist.                                            */

#endif
/*  End of include guard.                                                     */
