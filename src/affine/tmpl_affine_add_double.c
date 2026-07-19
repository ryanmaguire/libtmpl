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
 *                           tmpl_affine_add_double                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Performs addition for affine transformations.                         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function:                                                                 *
 *      tmpl_AffDouble_Add                                                    *
 *  Purpose:                                                                  *
 *      Adds two affine transformations together.                             *
 *  Arguments:                                                                *
 *      f (const tmpl_AffineDouble * const):                                  *
 *          An affine transformation, f(x) = a * x + b.                       *
 *      g (const tmpl_AffineDouble * const):                                  *
 *          Another affine transformation, g(x) = c * x + d.                  *
 *  Output:                                                                   *
 *      transform (tmpl_AffineDouble):                                        *
 *          The transform h(x) = f(x) + g(x).                                 *
 *  Called Functions:                                                         *
 *      src/affine/                                                           *
 *          tmpl_AffDouble_Slope_Intercept:                                   *
 *              Creates an affine transformation from slope-intercept form.   *
 *  Method:                                                                   *
 *      If f(x) = a * x + b and g(x) = c * x + d, then the sum is given by    *
 *                                                                            *
 *          h(x) = f(x) + g(x)                                                *
 *               = a * x + b + c * x + d                                      *
 *               = (a + c) * x + (b + d)                                      *
 *                                                                            *
 *      The slopes and the y-intercepts add together. These sums are          *
 *      computed and stored in a new transformation.                          *
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
 *  Date:       July 19, 2026                                                 *
 ******************************************************************************/

/*  TMPL_ALWAYS_INLINE macro found here, used for link-time optimization.     */
#include <libtmpl/include/tmpl_config.h>

/*  Optional C23 attributes for optimization provided here.                   */
#include <libtmpl/include/tmpl_attributes.h>

/*  The affine typedef and function prototype are provided here.              */
#include <libtmpl/include/tmpl_affine.h>

/*  Computes the sum of two affine transformations.                           */
TMPL_PURE_FUNC
TMPL_ALWAYS_INLINE
tmpl_AffineDouble
tmpl_AffDouble_Add(const tmpl_AffineDouble * const f,
                   const tmpl_AffineDouble * const g)
TMPL_UNSEQUENCED
{
    /*  The sum of two affine transformations is given by summing the slopes  *
     *  and the y-intercepts. Compute these.                                  */
    const double slope = f->dat[0] + g->dat[0];
    const double intercept = f->dat[1] + g->dat[1];

    /*  Given the slope and y-intercept, we can construct the transformation  *
     *  using slope-intercept form.                                           */
    return tmpl_AffDouble_Slope_Intercept(slope, intercept);
}
/*  End of tmpl_AffDouble_Add.                                                */
