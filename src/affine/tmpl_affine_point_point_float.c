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
 *                       tmpl_affine_point_point_float                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Creates an affine transformation from two-point form.                 *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function:                                                                 *
 *      tmpl_AffFloat_Point_Point                                             *
 *  Purpose:                                                                  *
 *      Creates an affine transformation from two-point form.                 *
 *  Arguments:                                                                *
 *      x0 (const float):                                                     *
 *          The x-component of the zeroth point.                              *
 *      y0 (const float):                                                     *
 *          The y-component of the zeroth point.                              *
 *      x1 (const float):                                                     *
 *          The x-component of the first point.                               *
 *      y1 (const float):                                                     *
 *          The y-component of the first point.                               *
 *  Output:                                                                   *
 *      transform (tmpl_AffineFloat):                                         *
 *          The transform f(x) = mx + b.                                      *
 *  Called Functions:                                                         *
 *      src/affine/                                                           *
 *          tmpl_AffFloat_Point_Slope:                                        *
 *              Creates an affine transformation from point-slope form.       *
 *  Method:                                                                   *
 *      Given a line with points (x0, y0) and (x1, y1) on it, we have:        *
 *                                                                            *
 *              y  -  y   -      -                                            *
 *               1     0 |        |                                           *
 *          y = -------- | x - x  | + y                                       *
 *              x  -  x  |      0 |    0                                      *
 *               1     0  -      -                                            *
 *                                                                            *
 *      The slope is m = (y1 - y0) / (x1 - x0) and the y-intercept is         *
 *      b = y0 - m * x0.                                                      *
 *  Notes:                                                                    *
 *      1.) No checks for NaN or infinity are made.                           *
 *                                                                            *
 *      2.) Two-point form requires x0 != x1. No checks for this are made.    *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Provides the TMPL_ALWAYS_INLINE macro.                            *
 *  2.) tmpl_attributes.h:                                                    *
 *          Provides (optional) C23 attributes for optimization.              *
 *  3.) tmpl_affine.h:                                                        *
 *          Location of the affine typedef and function prototype.            *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 3, 2026                                              *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2026/06/28: Ryan Maguire                                                  *
 *      Added C23 attributes, merged inline and non-inline versions.          *
 ******************************************************************************/

/*  TMPL_ALWAYS_INLINE macro found here, used for link-time optimization.     */
#include <libtmpl/include/tmpl_config.h>

/*  Optional C23 attributes for optimization provided here.                   */
#include <libtmpl/include/tmpl_attributes.h>

/*  The affine typedef and function prototype are provided here.              */
#include <libtmpl/include/tmpl_affine.h>

/*  Creates an affine transformation from two-point form.                     */
TMPL_CONST_FUNC
TMPL_ALWAYS_INLINE
tmpl_AffineFloat
tmpl_AffFloat_Point_Point(const float x0,
                          const float y0,
                          const float x1,
                          const float y1)
TMPL_UNSEQUENCED
{
    /*  Given (x0, y0) and (x1, y1), the slope is the ratio of the difference.*/
    const float slope = (y1 - y0) / (x1 - x0);

    /*  We now have the slope and a point on the line, (x0, y0). We may       *
     *  produce the transformation using the point-slope form.                */
    return tmpl_AffFloat_Point_Slope(x0, y0, slope);
}
/*  End of tmpl_AffFloat_Point_Point.                                         */
