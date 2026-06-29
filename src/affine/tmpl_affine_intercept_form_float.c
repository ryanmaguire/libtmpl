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
 *                      tmpl_affine_intercept_form_float                      *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Creates an affine transformation from intercept form.                 *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function:                                                                 *
 *      tmpl_AffFloat_Intercept_Form                                          *
 *  Purpose:                                                                  *
 *      Creates an affine transformation from intercept form.                 *
 *  Arguments:                                                                *
 *      x0 (const float):                                                     *
 *          The solution to f(x) = 0 for the transformation f(x) = mx + b.    *
 *      y0 (const float):                                                     *
 *          The y-intercept of the transformation, "b" in f(x) = mx + b.      *
 *  Output:                                                                   *
 *      transform (tmpl_AffineFloat):                                         *
 *          The transform f(x) = mx + b.                                      *
 *  Called Functions:                                                         *
 *      src/affine/                                                           *
 *          tmpl_AffFloat_Slope_Intercept:                                    *
 *              Creates the transform f(x) = mx + b given m and b.            *
 *  Method:                                                                   *
 *      If x0 and y0 are the x and y intercepts, respectively, and if both of *
 *      them are non-zero (meaning the line is not parallel to either axis,   *
 *      and it does not pass through the origin), then:                       *
 *                                                                            *
 *          x     y                                                           *
 *          -  +  -  =  1                                                     *
 *          x     y                                                           *
 *           0     0                                                          *
 *                                                                            *
 *      From this, we get:                                                    *
 *                                                                            *
 *                   y                                                        *
 *                    0                                                       *
 *          y = y  - -- x                                                     *
 *               0   x                                                        *
 *                    0                                                       *
 *                                                                            *
 *      The y-intercept is y0 and the slope is -y0 / x0.                      *
 *  Notes:                                                                    *
 *      1.) No checks for NaN or infinity are made.                           *
 *                                                                            *
 *      2.) Intercept form is only well-defined when both the x-intercept and *
 *          the y-intercept are non-zero. That is, the line is not allowed to *
 *          pass through the origin. No checks are made for non-zero inputs.  *
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

/*  Creates an affine transformation given its two intercepts.                */
TMPL_CONST_FUNC
TMPL_ALWAYS_INLINE
tmpl_AffineFloat
tmpl_AffFloat_Intercept_Form(const float x0, const float y0)
TMPL_UNSEQUENCED
{
    /*  Solving x / x0 + y / y0 = 1 gives us m = -y0 / x0 and b = y0.         */
    const float slope = -y0 / x0;

    /*  The transformation can be constructed from slope-intercept form.      */
    return tmpl_AffFloat_Slope_Intercept(slope, y0);
}
/*  End of tmpl_AffFloat_Intercept_Form.                                      */
