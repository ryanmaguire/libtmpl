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
 *                          tmpl_quick_hypot3_float                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes sqrt(x^2 + y^2 + z^2) at single precision.                   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Quick_Hypot3                                               *
 *  Purpose:                                                                  *
 *      Computes the magnitude of the vector (x, y, z) in space.              *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          The x component of the point.                                     *
 *      y (float):                                                            *
 *          The y component of the point.                                     *
 *      z (float):                                                            *
 *          The z component of the point.                                     *
 *  Output:                                                                   *
 *      mag (float):                                                          *
 *          The magnitude of (x, y, z) in space.                              *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_Float_Sqrt:                                                  *
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
 *      (10^18) or very small (10^-18) numbers, use tmpl_Float_Hypot3.        *
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
#ifndef TMPL_QUICK_HYPOT3_FLOAT_H
#define TMPL_QUICK_HYPOT3_FLOAT_H

/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  Let the compiler know about the square root function.                     */
extern float tmpl_Float_Sqrt(float x);

/*  Single precision 3D hypotenuse function.                                  */
TMPL_INLINE_DECL
float tmpl_Float_Quick_Hypot3(float x, float y, float z)
{
    /*  Use the Pythagorean formula and return.                               */
    return tmpl_Float_Sqrt(x*x + y*y + z*z);
}
/*  End of tmpl_Float_Quick_Hypot3.                                           */

#endif
/*  End of include guard.                                                     */
