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
 *                          tmpl_quick_hypot3_double                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes sqrt(x^2 + y^2 + z^2) at double precision.                   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Quick_Hypot3                                              *
 *  Purpose:                                                                  *
 *      Computes the magnitude of the vector (x, y, z) in space.              *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          The x component of the point.                                     *
 *      y (double):                                                           *
 *          The y component of the point.                                     *
 *      z (double):                                                           *
 *          The z component of the point.                                     *
 *  Output:                                                                   *
 *      mag (double):                                                         *
 *          The magnitude of (x, y, z) in space.                              *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_Double_Sqrt:                                                 *
 *              Computes the square root of a real number.                    *
 *  Method:                                                                   *
 *      Use the Pythagorean formula. Given P = (x, y, z), we have:            *
 *                                                                            *
 *          ||P|| = sqrt(x^2 + y^2 + z^2)                                     *
 *                                                                            *
 *  Notes:                                                                    *
 *      The intermediate computation, x^2 + y^2 + z^2, will overflow if any   *
 *      input is too big, and underflow if too small. For most reasonable     *
 *      inputs this is not an issue. If you are working with very large       *
 *      (10^150) or very small (10^-150) numbers, use tmpl_Double_Hypot3.     *
 *      That function is slightly slower, but safely handles such inputs.     *
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
#ifndef TMPL_QUICK_HYPOT3_DOUBLE_H
#define TMPL_QUICK_HYPOT3_DOUBLE_H

/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  Let the compiler know about the square root function.                     */
extern double tmpl_Double_Sqrt(double x);

/*  Double precision 3D hypotenuse function.                                  */
TMPL_INLINE_DECL
double tmpl_Double_Quick_Hypot3(double x, double y, double z)
{
    /*  Use the Pythagorean formula and return.                               */
    return tmpl_Double_Sqrt(x*x + y*y + z*z);
}
/*  End of tmpl_Double_Quick_Hypot3.                                          */

#endif
/*  End of include guard.                                                     */
