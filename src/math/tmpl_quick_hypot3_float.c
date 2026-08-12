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
 *      x (const float):                                                      *
 *          The x-component of the point.                                     *
 *      y (const float):                                                      *
 *          The y-component of the point.                                     *
 *      z (const float):                                                      *
 *          The z-component of the point.                                     *
 *  Output:                                                                   *
 *      mag (float):                                                          *
 *          The magnitude of the vector (x, y, z) in 3-space.                 *
 *  Called Functions:                                                         *
 *      src/math/                                                             *
 *          tmpl_Float_Sqrt:                                                  *
 *              Computes the square root of a real number.                    *
 *  Method:                                                                   *
 *      Use the Pythagorean formula. Given p = (x, y, z), we have:            *
 *                                                                            *
 *          || p || = sqrt(x^2 + y^2 + z^2)                                   *
 *                                                                            *
 *  Notes:                                                                    *
 *      The intermediate computation, x^2 + y^2 + z^2, will overflow if any   *
 *      input is too big, and underflow if too small. For most reasonable     *
 *      inputs this is not an issue. If you are working with very large       *
 *      (10^19) or very small (10^-19) numbers, use tmpl_Float_Hypot3.        *
 *      That function is slightly slower, but safely handles such inputs.     *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing the TMPL_ALWAYS_INLINE macro.              *
 *  2.) tmpl_attributes.h:                                                    *
 *          Provides optional C23 attributes for optimization.                *
 *  3.) tmpl_math.h:                                                          *
 *          Header file providing the forward declaration and sqrt.           *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 10, 2024                                                 *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2026/08/11: Ryan Maguire                                                  *
 *      Merged inline and non-inline versions, added TMPL_ALWAYS_INLINE use.  *
 ******************************************************************************/

/*  Location of the TMPL_ALWAYS_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  Function prototype / forward declaration and square root found here.      */
#include <libtmpl/include/tmpl_math.h>

/*  Single-precision 3D hypotenuse function.                                  */
TMPL_ALWAYS_INLINE
TMPL_CONST_FUNC
float
tmpl_Float_Quick_Hypot3(const float x, const float y, const float z)
TMPL_UNSEQUENCED
{
    /*  Use the Pythagorean formula and return.                               */
    return tmpl_Float_Sqrt(x * x + y * y + z * z);
}
/*  End of tmpl_Float_Quick_Hypot3.                                           */
