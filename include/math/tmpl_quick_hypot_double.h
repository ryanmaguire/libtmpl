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
 *                          tmpl_quick_hypot_double                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes sqrt(x^2 + y^2) at double precision.                         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Quick_Hypot                                               *
 *  Purpose:                                                                  *
 *      Computes the magnitude of the point (x, y) in the plane.              *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          The x component of the point.                                     *
 *      y (double):                                                           *
 *          The y component of the point.                                     *
 *  Output:                                                                   *
 *      mag (double):                                                         *
 *          The magnitude of (x, y) in the plane.                             *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_Double_Sqrt:                                                 *
 *              Computes the square root of a real number.                    *
 *  Method:                                                                   *
 *      Use the Pythagorean formula and compute. Given P = (x, y), we have:   *
 *                                                                            *
 *          ||P|| = sqrt(x^2 + y^2)                                           *
 *                                                                            *
 *  Notes:                                                                    *
 *      The intermediate computation, x^2 + y^2, will overflow if x or y is   *
 *      very big, and underflow if either is very small. For most reasonable  *
 *      inputs this is not an issue. If you are working with very large       *
 *      (10^150) or very small (10^-150) numbers, use tmpl_Double_Hypot. That *
 *      function is slightly slower, but safely handles such inputs.          *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_INLINE_DECL macro.                    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 10, 2024                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_QUICK_HYPOT_DOUBLE_H
#define TMPL_QUICK_HYPOT_DOUBLE_H

/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  Let the compiler know about the square root function.                     */
extern double tmpl_Double_Sqrt(double x);

/*  Double precision hypotenuse function.                                     */
TMPL_INLINE_DECL
double tmpl_Double_Quick_Hypot(double x, double y)
{
    /*  Use the Pythagorean formula and return.                               */
    return tmpl_Double_Sqrt(x*x + y*y);
}
/*  End of tmpl_Double_Quick_Hypot.                                           */

#endif
/*  End of include guard.                                                     */
