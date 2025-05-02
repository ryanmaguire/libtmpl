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
 *                      tmpl_vec2_l2_dist_squared_double                      *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the square of the L2 (Euclidean) distance in the plane.      *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_2DDouble_L2_Dist_Squared                                         *
 *  Purpose:                                                                  *
 *      Computes the square of the Euclidean distance between two points in   *
 *      the plane.                                                            *
 *  Arguments:                                                                *
 *      P (const tmpl_TwoVectorDouble * const):                               *
 *          A pointer to a point in the Euclidean plane.                      *
 *      Q (const tmpl_TwoVectorDouble * const):                               *
 *          Another point in the Euclidean plane.                             *
 *  Output:                                                                   *
 *      dist_squared (double):                                                *
 *          The square of the distance between points P and Q.                *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      The distance between two points is given by the Pythagorean formula.  *
 *      That is, if P = (a, b) and Q = (c, d), then the square of the         *
 *      distance is:                                                          *
 *                                                                            *
 *          dist(P, Q)^2 = || P - Q ||^2                                      *
 *                       = || (a, b) - (c, d) ||^2                            *
 *                       = || (a - c, b - d) ||^2                             *
 *                       = (a - c)^2 + (b - d)^2                              *
 *                                                                            *
 *      This final expression is returned.                                    *
 *  Notes:                                                                    *
 *      1.) There are no checks for NULL pointers. It is assumed P and Q are  *
 *          valid pointers to 2D vectors.                                     *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Location of the TMPL_INLINE_DECL macro.                           *
 *  2.) tmpl_vec2_double.h:                                                   *
 *          The tmpl_TwoVectorDouble typedef is provided here.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 2, 2025                                                   *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC2_L2_DIST_SQUARED_DOUBLE_H
#define TMPL_VEC2_L2_DIST_SQUARED_DOUBLE_H

/*  The TMPL_INLINE_DECL macro is provided here.                              */
#include <libtmpl/include/tmpl_config.h>

/*  Two-vector typedef found here.                                            */
#include <libtmpl/include/types/tmpl_vec2_double.h>

/*  Function for computing the square of the L2 distance between two points.  */
TMPL_INLINE_DECL
double
tmpl_2DDouble_L2_Dist_Squared(const tmpl_TwoVectorDouble * const P,
                              const tmpl_TwoVectorDouble * const Q)
{
    /*  Use the Pythagorean formula on the vector P - Q.                      */
    const double dx = P->dat[0] - Q->dat[0];
    const double dy = P->dat[1] - Q->dat[1];
    return dx*dx + dy*dy;
}
/*  End of tmpl_2DDouble_L2_Dist_Squared.                                     */

#endif
/*  End of include guard.                                                     */
