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
 *                      tmpl_affine_point_point_ldouble                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Creates an affine transformation from two-point form.                 *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function:                                                                 *
 *      tmpl_AffLDouble_Point_Point                                           *
 *  Purpose:                                                                  *
 *      Creates an affine transformation from two-point form.                 *
 *  Arguments:                                                                *
 *      x0 (const long double):                                               *
 *          The x-component of the zeroth point.                              *
 *      y0 (const long double):                                               *
 *          The y-component of the zeroth point.                              *
 *      x1 (const long double):                                               *
 *          The x-component of the first point.                               *
 *      y1 (const long double):                                               *
 *          The y-component of the first point.                               *
 *  Output:                                                                   *
 *      transform (tmpl_AffineLongDouble):                                    *
 *          The transform f(x) = mx + b.                                      *
 *  Called Functions:                                                         *
 *      None.                                                                 *
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
 *          Header file containing the TMPL_INLINE_DECL macro.                *
 *  2.) tmpl_affine_ldouble.h:                                                *
 *          Location of the tmpl_AffineLongDouble typedef.                    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 3, 2026                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_AFFINE_POINT_POINT_LDOUBLE_H
#define TMPL_AFFINE_POINT_POINT_LDOUBLE_H

/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  The tmpl_AffineLongDouble typedef is provided here.                       */
#include <libtmpl/include/types/tmpl_affine_ldouble.h>

/*  Creates an affine transformation from two-point form.                     */
TMPL_INLINE_DECL
tmpl_AffineLongDouble
tmpl_AffLDouble_Point_Point(const long double x0,
                            const long double y0,
                            const long double x1,
                            const long double y1)
{
    /*  Variable for the output.                                              */
    tmpl_AffineLongDouble transform;

    /*  Given (x0, y0) and (x1, y1), the slope is the ratio of the difference.*/
    const long double slope = (y1 - y0) / (x1 - x0);

    /*  We now have the slope and a point on the line, (x0, y0). We may       *
     *  produce the transformation using the point-slope form.                */
    transform.dat[0] = slope;
    transform.dat[1] = y0 - slope * x0;
    return transform;
}
/*  End of tmpl_AffLDouble_Point_Point.                                       */

#endif
/*  End of include guard.                                                     */
