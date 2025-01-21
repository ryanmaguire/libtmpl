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
 *                           tmpl_vec3_dist_ldouble                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the Euclidean distance between two points in R^3.            *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DLDouble_Dist                                                   *
 *  Purpose:                                                                  *
 *      Computes the distance between two points in space.                    *
 *  Arguments:                                                                *
 *      P (const tmpl_ThreeVectorLongDouble * const):                         *
 *          A pointer to a vector in R^3.                                     *
 *      Q (const tmpl_ThreeVectorLongDouble * const):                         *
 *          Another pointer to a vector in R^3.                               *
 *  Output:                                                                   *
 *      dist (long double):                                                   *
 *          The distance between P and Q.                                     *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_LDouble_Hypot3:                                              *
 *              Computes the magnitude of (x, y, z).                          *
 *  Method:                                                                   *
 *      Compute the L2 norm of P - Q and return.                              *
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
 *  3.) tmpl_math.h:                                                          *
 *          Header file providing the Hypot3 function.                        *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 12, 2024                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC3_DIST_LDOUBLE_H
#define TMPL_VEC3_DIST_LDOUBLE_H

/*  TMPL_INLINE_DECL macro found here.                                        */
#include <libtmpl/include/tmpl_config.h>

/*  Three-vector typedef found here.                                          */
#include <libtmpl/include/types/tmpl_vec3_ldouble.h>

/*  Hypot3 function found here.                                               */
#include <libtmpl/include/tmpl_math.h>

/*  Computes the Euclidean distance between two points.                       */
TMPL_INLINE_DECL
long double
tmpl_3DLDouble_Dist(const tmpl_ThreeVectorLongDouble * const P,
                    const tmpl_ThreeVectorLongDouble * const Q)
{
    /*  Compute the components of P - Q.                                      */
    const long double dx = P->dat[0] - Q->dat[0];
    const long double dy = P->dat[1] - Q->dat[1];
    const long double dz = P->dat[2] - Q->dat[2];

    /*  The Euclidean distance is the norm of P - Q. Return this.             */
    return tmpl_LDouble_Hypot3(dx, dy, dz);
}
/*  End of tmpl_3DLDouble_Dist.                                               */

#endif
/*  End of include guard.                                                     */
