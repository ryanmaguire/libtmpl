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
 *                         tmpl_affine_addto_ldouble                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Performs addition in-place for affine transformations.                *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function:                                                                 *
 *      tmpl_AffLDouble_AddTo                                                 *
 *  Purpose:                                                                  *
 *      Adds one affine transformation to another.                            *
 *  Arguments:                                                                *
 *      target (tmpl_AffineLongDouble * const):                               *
 *          An affine transformation, the sum is stored here.                 *
 *      source (const tmpl_AffineLongDouble * const):                         *
 *          Another affine transformation.                                    *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      If f(x) = a * x + b and g(x) = c * x + d, then the sum is given by    *
 *                                                                            *
 *          h(x) = f(x) + g(x)                                                *
 *               = a * x + b + c * x + d                                      *
 *               = (a + c) * x + (b + d)                                      *
 *                                                                            *
 *      The slopes and the y-intercepts add together.                         *
 *  Notes:                                                                    *
 *      1.) No checks for NaN or infinity are made.                           *
 *                                                                            *
 *      2.) No checks for NULL pointers are made.                             *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Provides the TMPL_ALWAYS_INLINE macro.                            *
 *  2.) tmpl_affine.h:                                                        *
 *          Location of the affine typedef and function prototype.            *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       July 19, 2026                                                 *
 ******************************************************************************/

/*  TMPL_ALWAYS_INLINE macro found here, used for link-time optimization.     */
#include <libtmpl/include/tmpl_config.h>

/*  The affine typedef and function prototype are provided here.              */
#include <libtmpl/include/tmpl_affine.h>

/*  Computes the sum of two affine transformations in-place.                  */
TMPL_ALWAYS_INLINE
void
tmpl_AffLDouble_AddTo(tmpl_AffineLongDouble * const target,
                      const tmpl_AffineLongDouble * const source)
{
    /*  The sum of two affine transformations is given by summing the slopes  *
     *  and the y-intercepts.                                                 */
    target->dat[0] += source->dat[0];
    target->dat[1] += source->dat[1];
}
/*  End of tmpl_AffLDouble_AddTo.                                             */
