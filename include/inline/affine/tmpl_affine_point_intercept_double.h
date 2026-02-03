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
 *                     tmpl_affine_point_intercept_double                     *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Creates an affine transformation from a point and the y-intercept.    *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function:                                                                 *
 *      tmpl_AffDouble_Point_Intercept                                        *
 *  Purpose:                                                                  *
 *      Creates an affine transformation from a point and the y-intercept.    *
 *  Arguments:                                                                *
 *      x0 (const double):                                                    *
 *          The x-component of the point.                                     *
 *      y0 (const double):                                                    *
 *          The y-component of the point.                                     *
 *      intercept (const double):                                             *
 *          The y-intercept.                                                  *
 *  Output:                                                                   *
 *      transform (tmpl_AffineDouble):                                        *
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
 *      b = y0 - m * x0. If (x1, y1) corresponds to the y-intercept, then     *
 *      x1 = 0 and hence the slope becomes m = (y0 - y1) / x0 and the         *
 *      y-intercept is simply y1.                                             *
 *  Notes:                                                                    *
 *      1.) No checks for NaN or infinity are made.                           *
 *                                                                            *
 *      2.) Point-intercept requires x0 != 0. No checks for this are made.    *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing the TMPL_INLINE_DECL macro.                *
 *  2.) tmpl_affine_double.h:                                                 *
 *          Location of the tmpl_AffineDouble typedef.                        *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 3, 2026                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_AFFINE_POINT_INTERCEPT_DOUBLE_H
#define TMPL_AFFINE_POINT_INTERCEPT_DOUBLE_H

/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  The tmpl_AffineDouble typedef is provided here.                           */
#include <libtmpl/include/types/tmpl_affine_double.h>

/*  Creates an affine transformation from point-intercept form.               */
TMPL_INLINE_DECL
tmpl_AffineDouble
tmpl_AffDouble_Point_Intercept(const double x0,
                               const double y0,
                               const double intercept)
{
    /*  Variable for the output.                                              */
    tmpl_AffineDouble transform;

    /*  Given (x0, y0) and (0, y1), the slope is the ratio of the difference. */
    const double slope = (y0 - intercept) / x0;

    /*  We now have the slope and the intercept. We can create the transform  *
     *  using the slope-intercept form.                                       */
    transform.dat[0] = slope;
    transform.dat[1] = intercept;
    return transform;
}
/*  End of tmpl_AffDouble_Point_Intercept.                                    */

#endif
/*  End of include guard.                                                     */
