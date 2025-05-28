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
 *                          tmpl_vec2_polard_ldouble                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Creates a long double precision 2D vector from its polar coordinates. *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_2DLDouble_Polard                                                 *
 *  Purpose:                                                                  *
 *      Computes the point in the plane given its polar representation. That  *
 *      is, given radius r and angle theta, computes:                         *
 *                                                                            *
 *          P = (r cos(theta), r sin(theta))                                  *
 *                                                                            *
 *  Arguments:                                                                *
 *      r (long double):                                                      *
 *          The magnitude of the point.                                       *
 *      theta (long double):                                                  *
 *          The angle of the point, in degrees.                               *
 *  Output:                                                                   *
 *      P (tmpl_TwoVectorLongDouble):                                         *
 *          The point (r cos(theta), r sin(theta)) in the plane.              *
 *  Called Functions:                                                         *
 *      src/math/                                                             *
 *          tmpl_LDouble_SinCosd:                                             *
 *              Computes sin(t) and cos(t) simultaneously in degrees.         *
 *  Method:                                                                   *
 *      Compute x = cos(t) and y = sin(t) and return P = (rx, ry).            *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file where TMPL_INLINE_DECL is found.                      *
 *  2.) tmpl_vec2_ldouble.h:                                                  *
 *          Header providing long double precision 2D vectors.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 28, 2025                                                  *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC2_POLARD_LDOUBLE_H
#define TMPL_VEC2_POLARD_LDOUBLE_H

/*  The TMPL_INLINE_DECL macro is provided here.                              */
#include <libtmpl/include/tmpl_config.h>

/*  Two-vector typedef found here.                                            */
#include <libtmpl/include/types/tmpl_vec2_ldouble.h>

/*  Tell the compiler about the SinCosd function.                             */
extern void
tmpl_LDouble_SinCosd(long double t, long double *sin_t, long double *cos_t);

/*  Create a long double precision 2D vector from its polar coordinates.      */
TMPL_INLINE_DECL
tmpl_TwoVectorLongDouble
tmpl_2DLDouble_Polard(long double r, long double theta)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_TwoVectorLongDouble P;

    /*  Compute sin(theta) and cos(theta) simultaneously.                     */
    tmpl_LDouble_SinCosd(theta, &P.dat[1], &P.dat[0]);

    /*  Scale the x and y coordinates by r to finish the computation.         */
    P.dat[0] *= r;
    P.dat[1] *= r;
    return P;
}
/*  End of tmpl_2DLDouble_Polard.                                             */

#endif
/*  End of include guard.                                                     */
