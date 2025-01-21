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
 *                         tmpl_vec3_quick_dist_float                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the Euclidean distance between two points in R^3.            *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DFloat_Quick_Dist                                               *
 *  Purpose:                                                                  *
 *      Computes the distance between two points in space.                    *
 *  Arguments:                                                                *
 *      P (const tmpl_ThreeVectorFloat * const):                              *
 *          A pointer to a vector in R^3.                                     *
 *      Q (const tmpl_ThreeVectorFloat * const):                              *
 *          Another pointer to a vector in R^3.                               *
 *  Output:                                                                   *
 *      dist (float):                                                         *
 *          The distance between P and Q.                                     *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_Float_Quick_Hypot3:                                          *
 *              Computes the magnitude of (x, y, z).                          *
 *  Method:                                                                   *
 *      Compute the L2 norm of P - Q and return.                              *
 *  Notes:                                                                    *
 *      1.) No checks for Infs or NaNs are performed.                         *
 *      2.) No checks for Null pointers are performed.                        *
 *      3.) This version is susceptible to overflow and underflow. If you are *
 *          using vectors that have very large components, use                *
 *          tmpl_3DFloat_Dist instead. That function safely handles overflow  *
 *          and underflow, but it is slower.                                  *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Location of the TMPL_INLINE_DECL macro.                           *
 *  2.) tmpl_vec3_float.h:                                                    *
 *          Header containing ThreeVector typedef.                            *
 *  3.) tmpl_math.h:                                                          *
 *          Header file providing the Hypot3 function.                        *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 12, 2024                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC3_QUICK_DIST_FLOAT_H
#define TMPL_VEC3_QUICK_DIST_FLOAT_H

/*  TMPL_INLINE_DECL macro found here.                                        */
#include <libtmpl/include/tmpl_config.h>

/*  Three-vector typedef found here.                                          */
#include <libtmpl/include/types/tmpl_vec3_float.h>

/*  Hypot3 function found here.                                               */
#include <libtmpl/include/tmpl_math.h>

/*  Computes the Euclidean distance between two points.                       */
TMPL_INLINE_DECL
float
tmpl_3DFloat_Quick_Dist(const tmpl_ThreeVectorFloat * const P,
                        const tmpl_ThreeVectorFloat * const Q)
{
    /*  Compute the components of P - Q.                                      */
    const float dx = P->dat[0] - Q->dat[0];
    const float dy = P->dat[1] - Q->dat[1];
    const float dz = P->dat[2] - Q->dat[2];

    /*  The Euclidean distance is the norm of P - Q. Return this.             */
    return tmpl_Float_Quick_Hypot3(dx, dy, dz);
}
/*  End of tmpl_3DFloat_Quick_Dist.                                           */

#endif
/*  End of include guard.                                                     */
