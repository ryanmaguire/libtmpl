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
 *                    tmpl_affine_point_intercept_ldouble                     *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Creates an affine transformation from a point and the y-intercept.    *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function:                                                                 *
 *      tmpl_AffLDouble_Point_Intercept                                       *
 *  Purpose:                                                                  *
 *      Creates an affine transformation from a point and the y-intercept.    *
 *  Arguments:                                                                *
 *      x0 (const long double):                                               *
 *          The x-component of the point.                                     *
 *      y0 (const long double):                                               *
 *          The y-component of the point.                                     *
 *      intercept (const long double):                                        *
 *          The y-intercept.                                                  *
 *  Output:                                                                   *
 *      transform (tmpl_AffineLongDouble):                                    *
 *          The transform f(x) = mx + b.                                      *
 *  Called Functions:                                                         *
 *      src/affine/                                                           *
 *          tmpl_AffDouble_Slope_Intercept:                                   *
 *              Creates the transform f(x) = mx + b given m and b.            *
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
 *  2026/06/26: Ryan Maguire                                                  *
 *      Added C23 attributes, merged inline and non-inline versions.          *
 ******************************************************************************/

/*  TMPL_ALWAYS_INLINE macro found here, used for link-time optimization.     */
#include <libtmpl/include/tmpl_config.h>

/*  Optional C23 attributes for optimization provided here.                   */
#include <libtmpl/include/tmpl_attributes.h>

/*  The affine typedef and function prototype are provided here.              */
#include <libtmpl/include/tmpl_affine.h>

/*  Creates an affine transformation from point-intercept form.               */
TMPL_CONST_FUNC
TMPL_ALWAYS_INLINE
tmpl_AffineLongDouble
tmpl_AffLDouble_Point_Intercept(const long double x0,
                                const long double y0,
                                const long double intercept)
TMPL_UNSEQUENCED
{
    /*  Given (x0, y0) and (0, y1), the slope is the ratio of the difference. */
    const long double slope = (y0 - intercept) / x0;

    /*  We now have the slope and the intercept. We can create the transform  *
     *  using the slope-intercept form.                                       */
    return tmpl_AffLDouble_Slope_Intercept(slope, intercept);
}
/*  End of tmpl_AffLDouble_Point_Intercept.                                   */
