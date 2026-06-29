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
 *                      tmpl_affine_point_slope_ldouble                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Creates an affine transformation from point-slope form.               *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function:                                                                 *
 *      tmpl_AffLDouble_Point_Slope                                           *
 *  Purpose:                                                                  *
 *      Creates an affine transformation from point-slope form.               *
 *  Arguments:                                                                *
 *      x0 (const long double):                                               *
 *          The x component of the point.                                     *
 *      y0 (const long double):                                               *
 *          The y component of the point.                                     *
 *      slope (const long double):                                            *
 *          The slope of the transformation, "m" in f(x) = mx + b.            *
 *  Output:                                                                   *
 *      transform (tmpl_AffineLongDouble):                                    *
 *          The transform f(x) = m * (x - x0) + y0.                           *
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
tmpl_AffineLongDouble
tmpl_AffLDouble_Point_Slope(const long double x0,
                            const long double y0,
                            const long double slope)
TMPL_UNSEQUENCED
{
    /*  Variable for the output.                                              */
    tmpl_AffineLongDouble transform;

    /*  Given f(x) = m (x - x0) + y0, the slope is m and the y-intercept can  *
     *  be found by expanding this out, giving us b = y0 - m * x0.            */
    transform.dat[0] = slope;
    transform.dat[1] = y0 - slope * x0;
    return transform;
}
/*  End of tmpl_AffLDouble_Point_Slope.                                       */
