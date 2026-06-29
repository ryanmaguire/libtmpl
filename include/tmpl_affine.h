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
 *                                tmpl_affine                                 *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides routines for working with 1D affine transformations.         *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file with the TMPL_USE_INLINE macro.                       *
 *  2.) tmpl_affine_double.h:                                                 *
 *          Location of the double precision typedef.                         *
 *  3.) tmpl_affine_float.h:                                                  *
 *          Location of the single precision typedef.                         *
 *  4.) tmpl_affine_ldouble.h:                                                *
 *          Location of the long double precision typedef.                    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 29, 2026                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_AFFINE_H
#define TMPL_AFFINE_H

/*  The TMPL_USE_INLINE macro is found here.                                  */
#include <libtmpl/include/tmpl_config.h>

/*  Optional C23 attributes for optimization are found here.                  */
#include <libtmpl/include/tmpl_attributes.h>

/*  Locations of the Affine data types at various precisions.                 */
#include <libtmpl/include/types/tmpl_affine_double.h>
#include <libtmpl/include/types/tmpl_affine_float.h>
#include <libtmpl/include/types/tmpl_affine_ldouble.h>

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_AffDouble_Intercept_Form                                         *
 *  Purpose:                                                                  *
 *      Creates an affine transformation from intercept form.                 *
 *  Arguments:                                                                *
 *      x0 (const double):                                                    *
 *          The solution to f(x) = 0 for the transformation f(x) = mx + b.    *
 *      y0 (const double):                                                    *
 *          The y-intercept of the transformation, "b" in f(x) = mx + b.      *
 *  Output:                                                                   *
 *      transform (tmpl_AffineDouble):                                        *
 *          The transform f(x) = mx + b.                                      *
 *  Notes:                                                                    *
 *      1.) Float and long double equivalents are provided.                   *
 *                                                                            *
 *      2.) No checks for NaN or infinity are made.                           *
 *                                                                            *
 *      3.) Intercept form is only well-defined when both the x-intercept and *
 *          the y-intercept are non-zero. That is, the line is not allowed to *
 *          pass through the origin. No checks are made for non-zero inputs.  *
 ******************************************************************************/
TMPL_CONST_FUNC
extern tmpl_AffineDouble
tmpl_AffDouble_Intercept_Form(const double x0, const double y0)
TMPL_UNSEQUENCED;

TMPL_CONST_FUNC
extern tmpl_AffineFloat
tmpl_AffFloat_Intercept_Form(const float x0, const float y0)
TMPL_UNSEQUENCED;

TMPL_CONST_FUNC
extern tmpl_AffineLongDouble
tmpl_AffLDouble_Intercept_Form(const long double x0, const long double y0)
TMPL_UNSEQUENCED;

/******************************************************************************
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
 *  Notes:                                                                    *
 *      1.) Float and long double equivalents are provided.                   *
 *                                                                            *
 *      2.) No checks for NaN or infinity are made.                           *
 *                                                                            *
 *      3.) Point-intercept requires x0 != 0. No checks for this are made.    *
 ******************************************************************************/
TMPL_CONST_FUNC
extern tmpl_AffineDouble
tmpl_AffDouble_Point_Intercept(const double x0,
                               const double y0,
                               const double intercept)
TMPL_UNSEQUENCED;

TMPL_CONST_FUNC
extern tmpl_AffineFloat
tmpl_AffFloat_Point_Intercept(const float x0,
                              const float y0,
                              const float intercept)
TMPL_UNSEQUENCED;

TMPL_CONST_FUNC
extern tmpl_AffineLongDouble
tmpl_AffLDouble_Point_Intercept(const long double x0,
                                const long double y0,
                                const long double intercept)
TMPL_UNSEQUENCED;

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_AffDouble_Point_Point                                            *
 *  Purpose:                                                                  *
 *      Creates an affine transformation from two-point form.                 *
 *  Arguments:                                                                *
 *      x0 (const double):                                                    *
 *          The x-component of the zeroth point.                              *
 *      y0 (const double):                                                    *
 *          The y-component of the zeroth point.                              *
 *      x1 (const double):                                                    *
 *          The x-component of the first point.                               *
 *      y1 (const double):                                                    *
 *          The y-component of the first point.                               *
 *  Output:                                                                   *
 *      transform (tmpl_AffineDouble):                                        *
 *          The transform f(x) = mx + b.                                      *
 *  Notes:                                                                    *
 *      1.) Float and long double equivalents are provided.                   *
 *                                                                            *
 *      2.) No checks for NaN or infinity are made.                           *
 *                                                                            *
 *      3.) Two-point form requires x0 != x1. No checks for this are made.    *
 ******************************************************************************/
TMPL_CONST_FUNC
extern tmpl_AffineDouble
tmpl_AffDouble_Point_Point(const double x0,
                           const double y0,
                           const double x1,
                           const double y1)
TMPL_UNSEQUENCED;

TMPL_CONST_FUNC
extern tmpl_AffineFloat
tmpl_AffFloat_Point_Point(const float x0,
                          const float y0,
                          const float x1,
                          const float y1)
TMPL_UNSEQUENCED;

TMPL_CONST_FUNC
extern tmpl_AffineLongDouble
tmpl_AffLDouble_Point_Point(const long double x0,
                            const long double y0,
                            const long double x1,
                            const long double y1)
TMPL_UNSEQUENCED;

/******************************************************************************
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
 *          The transform f(x) = m(x - x0) + y0.                              *
 *  Notes:                                                                    *
 *      1.) Float and long double equivalents are provided.                   *
 *                                                                            *
 *      2.) No checks for NaN or infinity are made.                           *
 ******************************************************************************/
TMPL_CONST_FUNC
extern tmpl_AffineDouble
tmpl_AffDouble_Point_Slope(const double x0,
                           const double y0,
                           const double slope)
TMPL_UNSEQUENCED;

TMPL_CONST_FUNC
extern tmpl_AffineFloat
tmpl_AffFloat_Point_Slope(const float x0,
                          const float y0,
                          const float slope)
TMPL_UNSEQUENCED;

TMPL_CONST_FUNC
extern tmpl_AffineLongDouble
tmpl_AffLDouble_Point_Slope(const long double x0,
                            const long double y0,
                            const long double slope)
TMPL_UNSEQUENCED;

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_AffDouble_Slope_Intercept                                        *
 *  Purpose:                                                                  *
 *      Creates an affine transformation from slope-intercept form.           *
 *  Arguments:                                                                *
 *      slope (const double):                                                 *
 *          The slope of the transformation, "m" in f(x) = mx + b.            *
 *      intercept (const double):                                             *
 *          The y-intercept of the transformation, "b" in f(x) = mx + b.      *
 *  Output:                                                                   *
 *      transform (tmpl_AffineDouble):                                        *
 *          The transform f(x) = mx + b.                                      *
 *  Notes:                                                                    *
 *      1.) Float and long double equivalents are provided.                   *
 *                                                                            *
 *      2.) No checks for NaN or infinity are made.                           *
 ******************************************************************************/
TMPL_CONST_FUNC
extern tmpl_AffineDouble
tmpl_AffDouble_Slope_Intercept(const double slope,
                               const double intercept)
TMPL_UNSEQUENCED;

TMPL_CONST_FUNC
extern tmpl_AffineFloat
tmpl_AffFloat_Slope_Intercept(const float slope,
                              const float intercept)
TMPL_UNSEQUENCED;

TMPL_CONST_FUNC
extern tmpl_AffineLongDouble
tmpl_AffLDouble_Slope_Intercept(const long double slope,
                                const long double intercept)
TMPL_UNSEQUENCED;

#endif
/*  End of include guard.                                                     */
