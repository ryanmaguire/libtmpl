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
 *                   tmpl_vec2_positive_polar_angle_ldouble                   *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the positive angle a vector makes with the positive x axis.  *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_2DLDouble_Positive_Polar_Angle                                   *
 *  Purpose:                                                                  *
 *      Computes the angle the point p = (a, b) makes with (1, 0) in radians. *
 *  Arguments:                                                                *
 *      p (const tmpl_TwoVectorLongDouble * const):                           *
 *          A pointer to a point in the Euclidean plane.                      *
 *  Output:                                                                   *
 *      angle (long double):                                                  *
 *          The positive angle, in radians, the point p makes with the x axis.*
 *  Called Functions:                                                         *
 *      src/math/                                                             *
 *          tmpl_LDouble_Positive_Arctan2:                                    *
 *              Computes the positive angle made by the point (x, y).         *
 *  Method:                                                                   *
 *      The atan2 function computes angles. Given p = (a, b), we return       *
 *      atan2(b, a).                                                          *
 *  Notes:                                                                    *
 *      1.) No checks for Infs or NaNs are performed.                         *
 *                                                                            *
 *      2.) No checks for Null pointers are performed.                        *
 *                                                                            *
 *      3.) The returned angle is in radians and lies between 0 and 2 pi.     *
 *                                                                            *
 *      4.) There is a jump discontinuity, or "branch cut", along the         *
 *          negative x axis.                                                  *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Location of the TMPL_ALWAYS_INLINE macro.                         *
 *  2.) tmpl_attributes.h:                                                    *
 *          Provides C23 attributes for optimization.                         *
 *  2.) tmpl_math.h:                                                          *
 *          Provides the atan2 function.                                      *
 *  3.) tmpl_vec2.h:                                                          *
 *          Header containing vector types and the function prototype.        *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 9, 2025                                                   *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2026/09/02: Ryan Maguire                                                  *
 *      Merged inline and non-inline versions, added C23 attributes.          *
 ******************************************************************************/

/*  The TMPL_ALWAYS_INLINE macro is provided here.                            */
#include <libtmpl/include/tmpl_config.h>

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  Positive atan2 function provided here.                                    */
#include <libtmpl/include/tmpl_math.h>

/*  Two-vector typedef and function prototype given here.                     */
#include <libtmpl/include/tmpl_vec2.h>

/*  Function for computing the positive angle a vector makes with the x axis. */
TMPL_PURE_FUNC
TMPL_ALWAYS_INLINE
long double
tmpl_2DLDouble_Positive_Polar_Angle(const tmpl_TwoVectorLongDouble * const p)
TMPL_UNSEQUENCED
{
    return tmpl_LDouble_Positive_Arctan2(p->dat[1], p->dat[0]);
}
/*  End of tmpl_2DLDouble_Positive_Polar_Angle.                               */
