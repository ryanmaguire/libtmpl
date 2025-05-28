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
 *                           tmpl_vec2_polar_float                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Creates a single precision 2D vector from its polar coordinates.      *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_2DFloat_Polar                                                    *
 *  Purpose:                                                                  *
 *      Computes the point in the plane given its polar representation. That  *
 *      is, given radius r and angle theta, computes:                         *
 *                                                                            *
 *          P = (r cos(theta), r sin(theta))                                  *
 *                                                                            *
 *  Arguments:                                                                *
 *      r (float):                                                            *
 *          The magnitude of the point.                                       *
 *      theta (float):                                                        *
 *          The angle of the point, in radians.                               *
 *  Output:                                                                   *
 *      P (tmpl_TwoVectorFloat):                                              *
 *          The point (r cos(theta), r sin(theta)) in the plane.              *
 *  Called Functions:                                                         *
 *      src/math/                                                             *
 *          tmpl_Float_SinCos:                                                *
 *              Computes sin(t) and cos(t) simultaneously.                    *
 *  Method:                                                                   *
 *      Compute x = cos(t) and y = sin(t) and return P = (rx, ry).            *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file where TMPL_INLINE_DECL is found.                      *
 *  2.) tmpl_vec2_float.h:                                                    *
 *          Header providing single precision 2D vectors.                     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 3, 2021                                                 *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2020/12/21: Ryan Maguire                                                  *
 *      Created file (Wellesley College for librssringoccs).                  *
 *  2021/03/03: Ryan Maguire                                                  *
 *      Edited file for use in libtmpl.                                       *
 *  2025/05/28: Ryan Maguire                                                  *
 *      Inlined the function.                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC2_POLAR_FLOAT_H
#define TMPL_VEC2_POLAR_FLOAT_H

/*  The TMPL_INLINE_DECL macro is provided here.                              */
#include <libtmpl/include/tmpl_config.h>

/*  Two-vector typedef found here.                                            */
#include <libtmpl/include/types/tmpl_vec2_float.h>

/*  Tell the compiler about the SinCos function.                              */
extern void tmpl_Float_SinCos(float t, float *sin_t, float *cos_t);

/*  Create a single precision 2D vector from its polar coordinates.           */
TMPL_INLINE_DECL
tmpl_TwoVectorFloat tmpl_2DFloat_Polar(float r, float theta)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_TwoVectorFloat P;

    /*  Compute sin(theta) and cos(theta) simultaneously.                     */
    tmpl_Float_SinCos(theta, &P.dat[1], &P.dat[0]);

    /*  Scale the x and y coordinates by r to finish the computation.         */
    P.dat[0] *= r;
    P.dat[1] *= r;
    return P;
}
/*  End of tmpl_2DFloat_Polar.                                                */

#endif
/*  End of include guard.                                                     */
