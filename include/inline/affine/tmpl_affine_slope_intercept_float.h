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
 *                     tmpl_affine_slope_intercept_float                      *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Creates an affine transformation from slope-intercept form.           *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function:                                                                 *
 *      tmpl_AffFloat_Slope_Intercept                                         *
 *  Purpose:                                                                  *
 *      Creates an affine transformation from slope-intercept form.           *
 *  Arguments:                                                                *
 *      slope (const float):                                                  *
 *          The slope of the transformation, "m" in f(x) = mx + b.            *
 *      intercept (const float):                                              *
 *          The y-intercept of the transformation, "b" in f(x) = mx + b.      *
 *  Output:                                                                   *
 *      transform (tmpl_AffineFloat):                                         *
 *          The transform f(x) = mx + b.                                      *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Copy the arguments into an affine transformation struct and return.   *
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
#ifndef TMPL_AFFINE_SLOPE_INTERCEPT_FLOAT_H
#define TMPL_AFFINE_SLOPE_INTERCEPT_FLOAT_H

/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  The tmpl_AffineFloat typedef is provided here.                            */
#include <libtmpl/include/types/tmpl_affine_float.h>

/*  Creates an affine transformation given its slope and y-intercept.         */
TMPL_INLINE_DECL
tmpl_AffineFloat
tmpl_AffFloat_Slope_Intercept(const float slope, const float intercept)
{
    /*  Variable for the output.                                              */
    tmpl_AffineFloat transform;

    /*  The data in an affine transformation is a contiguous array. The       *
     *  zeroth element represents the slope and the first is the y-intercept. *
     *  Copy the arguments into the struct and return.                        */
    transform.dat[0] = slope;
    transform.dat[1] = intercept;
    return transform;
}
/*  End of tmpl_AffFloat_Slope_Intercept.                                     */

#endif
/*  End of include guard.                                                     */
