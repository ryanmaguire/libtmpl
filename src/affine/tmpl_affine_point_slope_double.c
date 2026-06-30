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
 *                       tmpl_affine_point_slope_double                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Creates an affine transformation from point-slope form.               *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function:                                                                 *
 *      tmpl_AffDouble_Point_Slope                                            *
 *  Purpose:                                                                  *
 *      Creates an affine transformation from point-slope form.               *
 *  Arguments:                                                                *
 *      x0 (const double):                                                    *
 *          The x component of the point.                                     *
 *      y0 (const double):                                                    *
 *          The y component of the point.                                     *
 *      slope (const double):                                                 *
 *          The slope of the transformation, "m" in f(x) = mx + b.            *
 *  Output:                                                                   *
 *      transform (tmpl_AffineDouble):                                        *
 *          The transform f(x) = m * (x - x0) + y0.                           *
 *  Called Functions:                                                         *
 *      src/affine/                                                           *
 *          tmpl_AffDouble_Slope_Intercept:                                   *
 *              Creates the transform f(x) = mx + b given m and b.            *
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
 *          Provides the TMPL_ALWAYS_INLINE macro.                            *
 *  2.) tmpl_attributes.h:                                                    *
 *          Provides (optional) C23 attributes for optimization.              *
 *  3.) tmpl_affine.h:                                                        *
 *          Location of the affine typedef and function prototype.            *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 29, 2026                                              *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2026/06/29: Ryan Maguire                                                  *
 *      Added C23 attributes, merged inline and non-inline versions.          *
 ******************************************************************************/

/*  TMPL_ALWAYS_INLINE macro found here, used for link-time optimization.     */
#include <libtmpl/include/tmpl_config.h>

/*  Optional C23 attributes for optimization provided here.                   */
#include <libtmpl/include/tmpl_attributes.h>

/*  The affine typedef and function prototype are provided here.              */
#include <libtmpl/include/tmpl_affine.h>

/*  Creates an affine transformation given its slope and y0 = f(x0).          */
TMPL_CONST_FUNC
TMPL_ALWAYS_INLINE
tmpl_AffineDouble
tmpl_AffDouble_Point_Slope(const double x0,
                           const double y0,
                           const double slope)
TMPL_UNSEQUENCED
{
    /*  Given f(x) = m * (x - x0) + y0, the slope is m and the y-intercept    *
     *  can be found by expanding this out, giving us b = y0 - m * x0.        */
    const double intercept = y0 - slope * x0;

    /*  The transformation can be computed from slope-intercept form.         */
    return tmpl_AffDouble_Slope_Intercept(slope, intercept);
}
/*  End of tmpl_AffDouble_Point_Slope.                                        */
