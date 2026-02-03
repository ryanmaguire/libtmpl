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
 *                     tmpl_affine_intercept_form_ldouble                     *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Creates an affine transformation from intercept form.                 *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function:                                                                 *
 *      tmpl_AffLDouble_Intercept_Form                                        *
 *  Purpose:                                                                  *
 *      Creates an affine transformation from intercept form.                 *
 *  Arguments:                                                                *
 *      x0 (const long double):                                               *
 *          The solution to f(x) = 0 for the transformation f(x) = mx + b.    *
 *      y0 (const long double):                                               *
 *          The y-intercept of the transformation, "b" in f(x) = mx + b.      *
 *  Output:                                                                   *
 *      transform (tmpl_AffineLongDouble):                                    *
 *          The transform f(x) = mx + b.                                      *
 *  Called Functions:                                                         *
 *      None.                                                                 *
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
 *          Header file containing the TMPL_INLINE_DECL macro.                *
 *  2.) tmpl_affine_ldouble.h:                                                *
 *          Location of the tmpl_AffineLongDouble typedef.                    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 3, 2026                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_AFFINE_INTERCEPT_FORM_LDOUBLE_H
#define TMPL_AFFINE_INTERCEPT_FORM_LDOUBLE_H

/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  The tmpl_AffineLongDouble typedef is provided here.                       */
#include <libtmpl/include/types/tmpl_affine_ldouble.h>

/*  Creates an affine transformation given its two intercepts.                */
TMPL_INLINE_DECL
tmpl_AffineLongDouble
tmpl_AffLDouble_Intercept_Form(const long double x0, const long double y0)
{
    /*  Variable for the output.                                              */
    tmpl_AffineLongDouble transform;

    /*  Solving x / x0 + y / y0 = 1 gives us m = -y0 / x0 and b = y0.         */
    transform.dat[0] = -y0 / x0;
    transform.dat[1] = y0;
    return transform;
}
/*  End of tmpl_AffLDouble_Intercept_Form.                                    */

#endif
/*  End of include guard.                                                     */
