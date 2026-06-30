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
 *                         tmpl_affine_compose_double                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Composes two affine transformations.                                  *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function:                                                                 *
 *      tmpl_AffDouble_Compose                                                *
 *  Purpose:                                                                  *
 *      Creates h(x) = g(f(x)) from two affine transformations g and f.       *
 *  Arguments:                                                                *
 *      g (const tmpl_AffineDouble * const):                                  *
 *          The outer transformation, the one composed on the left.           *
 *      f (const tmpl_AffineDouble * const):                                  *
 *          The inner transformation, the one composed on the right.          *
 *  Output:                                                                   *
 *      transform (tmpl_AffineDouble):                                        *
 *          The transform h(x) = g(f(x)).                                     *
 *  Called Functions:                                                         *
 *      src/affine/                                                           *
 *          tmpl_AffDouble_Slope_Intercept:                                   *
 *              Creates the transform f(x) = mx + b given m and b.            *
 *  Method:                                                                   *
 *      Given f(x) = a * x + b and g(x) = c * x + d, the composition is       *
 *                                                                            *
 *          g(f(x)) = g(a * x + b)                                            *
 *                  = c * (a * x + b) + d                                     *
 *                  = (a * c) * x + (b * c + d)                               *
 *                                                                            *
 *      The slope is a * c and the intercept is b * c + d.                    *
 *  Notes:                                                                    *
 *      1.) No checks for NaN or infinity are made.                           *
 *                                                                            *
 *      2.) No checks for NULL pointers are made.                             *
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
 *  Date:       June 30, 2026                                                 *
 ******************************************************************************/

/*  TMPL_ALWAYS_INLINE macro found here, used for link-time optimization.     */
#include <libtmpl/include/tmpl_config.h>

/*  Optional C23 attributes for optimization provided here.                   */
#include <libtmpl/include/tmpl_attributes.h>

/*  The affine typedef and function prototype are provided here.              */
#include <libtmpl/include/tmpl_affine.h>

/*  Composes two affine transformations together.                             */
TMPL_PURE_FUNC
TMPL_ALWAYS_INLINE
extern tmpl_AffineDouble
tmpl_AffDouble_Compose(const tmpl_AffineDouble * const g,
                       const tmpl_AffineDouble * const f)
TMPL_UNSEQUENCED
{
    /*  Given f(x) = a * x + b ang g(x) = c * x + d, the composition has      *
     *  y-intercept b * c + d and slope a * c. Compute these.                 */
    const double intercept = f->dat[1] * g->dat[0] + g->dat[1];
    const double slope = f->dat[0] * g->dat[0];

    /*  The transformation can be constructed from slope-intercept form.      */
    return tmpl_AffDouble_Slope_Intercept(slope, intercept);
}
/*  End of tmpl_AffDouble_Compose.                                            */
