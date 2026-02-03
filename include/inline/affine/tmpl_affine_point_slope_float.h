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
 *                       tmpl_affine_point_slope_float                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Creates an affine transformation from point-slope form.               *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function:                                                                 *
 *      tmpl_AffFloat_Point_Slope                                             *
 *  Purpose:                                                                  *
 *      Creates an affine transformation from point-slope form.               *
 *  Arguments:                                                                *
 *      x0 (const float):                                                     *
 *          The x component of the point.                                     *
 *      y0 (const float):                                                     *
 *          The y component of the point.                                     *
 *      slope (const float):                                                  *
 *          The slope of the transformation, "m" in f(x) = mx + b.            *
 *  Output:                                                                   *
 *      transform (tmpl_AffineFloat):                                         *
 *          The transform f(x) = m(x - x0) + y0.                              *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Given the slope "m" and a point (x0, y0) that falls on the line, we   *
 *      have:                                                                 *
 *                                                                            *
 *          f(x) = m (x - x ) + y                                             *
 *                         0     0                                            *
 *                                                                            *
 *               = m x + y  - m x                                             *
 *                        0      0                                            *
 *                                                                            *
 *      The slope is m and the y-intercept is y0 - m * x0. We store these     *
 *      values in the affine transformation.                                  *
 *  Notes:                                                                    *
 *      1.) No checks for NaN or infinity are made.                           *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing the TMPL_INLINE_DECL macro.                *
 *  2.) tmpl_affine_float.h:                                                  *
 *          Location of the tmpl_AffineFloat typedef.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 29, 2026                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_AFFINE_POINT_SLOPE_FLOAT_H
#define TMPL_AFFINE_POINT_SLOPE_FLOAT_H

/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  The tmpl_AffineFloat typedef is provided here.                            */
#include <libtmpl/include/types/tmpl_affine_float.h>

/*  Creates an affine transformation given its slope and y0 = f(x0).          */
TMPL_INLINE_DECL
tmpl_AffineFloat
tmpl_AffFloat_Point_Slope(const float x0,
                          const float y0,
                          const float slope)
{
    /*  Variable for the output.                                              */
    tmpl_AffineFloat transform;

    /*  Given f(x) = m (x - x0) + y0, the slope is m and the y-intercept can  *
     *  be found by expanding this out, giving us b = y0 - m * x0.            */
    transform.dat[0] = slope;
    transform.dat[1] = y0 - slope * x0;
    return transform;
}
/*  End of tmpl_AffFloat_Point_Slope.                                         */

#endif
/*  End of include guard.                                                     */
