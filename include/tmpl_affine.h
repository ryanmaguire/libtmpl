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

/*  Locations of the Affine data types at various precisions.                 */
#include <libtmpl/include/types/tmpl_affine_double.h>
#include <libtmpl/include/types/tmpl_affine_float.h>
#include <libtmpl/include/types/tmpl_affine_ldouble.h>

/*  Helper macro for including the inline version of functions.               */
#if TMPL_USE_INLINE == 1

/*  Other headers provide this macro too. Make sure it is available.          */
#ifdef TMPL_INLINE_FILE
#undef TMPL_INLINE_FILE
#endif

/*  All inline versions are in libtmpl/include/inline/affine/.                */
#define TMPL_INLINE_FILE(file) <libtmpl/include/inline/affine/file>

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

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

/*  These functions are small enough to inline. Check for inline support.     */
#if TMPL_USE_INLINE

/*  Location of the inlined versions.                                         */
TMPL_INLINE_FILE(tmpl_affine_intercept_form_double.h)
TMPL_INLINE_FILE(tmpl_affine_intercept_form_float.h)
TMPL_INLINE_FILE(tmpl_affine_intercept_form_ldouble.h)

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  Lacking inline support, use the versions in src/affine/.                  */
extern tmpl_AffineDouble
tmpl_AffDouble_Intercept_Form(const double x0, const double y0);

extern tmpl_AffineFloat
tmpl_AffFloat_Intercept_Form(const float x0, const float y0);

extern tmpl_AffineLongDouble
tmpl_AffLDouble_Intercept_Form(const long double x0, const long double y0);

#endif
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_AffDouble_Point_Slope                                            *
 *  Purpose:                                                                  *
 *      Creates an affine transformation from point-slope form.               *
 *  Arguments:                                                                *
 *      slope (const double):                                                 *
 *          The slope of the transformation, "m" in f(x) = mx + b.            *
 *      x0 (const double):                                                    *
 *          The x component of the point.                                     *
 *      y0 (const double):                                                    *
 *          The y component of the point.                                     *
 *  Output:                                                                   *
 *      transform (tmpl_AffineDouble):                                        *
 *          The transform f(x) = m(x - x0) + y0.                              *
 *  Notes:                                                                    *
 *      1.) Float and long double equivalents are provided.                   *
 *                                                                            *
 *      2.) No checks for NaN or infinity are made.                           *
 ******************************************************************************/

/*  These functions are small enough to inline. Check for inline support.     */
#if TMPL_USE_INLINE

/*  Location of the inlined versions.                                         */
TMPL_INLINE_FILE(tmpl_affine_point_slope_double.h)
TMPL_INLINE_FILE(tmpl_affine_point_slope_float.h)
TMPL_INLINE_FILE(tmpl_affine_point_slope_ldouble.h)

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  Lacking inline support, use the versions in src/affine/.                  */
extern tmpl_AffineDouble
tmpl_AffDouble_Point_Slope(const double slope,
                           const double x0,
                           const double y0);

extern tmpl_AffineFloat
tmpl_AffFloat_Point_Slope(const float slope,
                          const float x0,
                          const float y0);

extern tmpl_AffineLongDouble
tmpl_AffLDouble_Point_Slope(const long double slope,
                            const long double x0,
                            const long double y0);

#endif
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

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

/*  These functions are small enough to inline. Check for inline support.     */
#if TMPL_USE_INLINE

/*  Location of the inlined versions.                                         */
TMPL_INLINE_FILE(tmpl_affine_slope_intercept_double.h)
TMPL_INLINE_FILE(tmpl_affine_slope_intercept_float.h)
TMPL_INLINE_FILE(tmpl_affine_slope_intercept_ldouble.h)

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  Lacking inline support, use the versions in src/affine/.                  */
extern tmpl_AffineDouble
tmpl_AffDouble_Slope_Intercept(const double slope,
                               const double intercept);

extern tmpl_AffineFloat
tmpl_AffFloat_Slope_Intercept(const float slope,
                              const float intercept);

extern tmpl_AffineLongDouble
tmpl_AffLDouble_Slope_Intercept(const long double slope,
                                const long double intercept);

#endif
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  Undefine the helper macro since other headers use it too.                 */
#if TMPL_USE_INLINE == 1
#undef TMPL_INLINE_FILE
#endif

#endif
/*  End of include guard.                                                     */
