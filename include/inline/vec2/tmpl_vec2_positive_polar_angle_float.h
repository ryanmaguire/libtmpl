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
 *                    tmpl_vec2_positive_polar_angle_float                    *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the positive angle a vector makes with the positive x axis.  *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_2DFloat_Positive_Polar_Angle                                     *
 *  Purpose:                                                                  *
 *      Computes the angle the point P = (a, b) makes with (1, 0) in radians. *
 *  Arguments:                                                                *
 *      P (const tmpl_TwoVectorFloat * const):                                *
 *          A pointer to a point in the Euclidean plane.                      *
 *  Output:                                                                   *
 *      angle (float):                                                        *
 *          The positive angle, in radians, the point P makes with the x axis.*
 *  Called Functions:                                                         *
 *      src/math/                                                             *
 *          tmpl_Float_Positive_Arctan2:                                      *
 *              Computes the angle made by the point (x, y).                  *
 *  Method:                                                                   *
 *      The atan2 function computes angles. Given P = (a, b), we return       *
 *      atan2(b, a).                                                          *
 *  Notes:                                                                    *
 *      1.) There are no checks for NULL pointers. It is assumed P is a valid *
 *          pointer to a 2D vector.                                           *
 *      2.) The returned angle is in radians and lies between 0 and 2*pi.     *
 *      3.) There is a jump discontinuity, or "branch cut", along the         *
 *          negative x axis.                                                  *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Location of the TMPL_INLINE_DECL macro.                           *
 *  2.) tmpl_vec2_float.h:                                                    *
 *          The tmpl_TwoVectorFloat typedef is provided here.                 *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 9, 2025                                                   *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC2_POSITIVE_POLAR_ANGLE_FLOAT_H
#define TMPL_VEC2_POSITIVE_POLAR_ANGLE_FLOAT_H

/*  The TMPL_INLINE_DECL macro is provided here.                              */
#include <libtmpl/include/tmpl_config.h>

/*  Two-vector typedef found here.                                            */
#include <libtmpl/include/types/tmpl_vec2_float.h>

/*  The positive arctan2 is inlined by default. Check if inline is available. */
#if TMPL_USE_INLINE == 1

/*  Implemented here.                                                         */
#include <libtmpl/include/inline/math/tmpl_positive_arctan2_float.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  Otherwise, the compiler about the positive atan2 function.                */
extern float tmpl_Float_Positive_Arctan2(float y, float x);

#endif
/*  End for #if TMPL_USE_INLINE == 1.                                         */

/*  Function for computing the positive angle a vector makes with the x axis. */
TMPL_INLINE_DECL
float tmpl_2DFloat_Positive_Polar_Angle(const tmpl_TwoVectorFloat * const P)
{
    return tmpl_Float_Positive_Arctan2(P->dat[1], P->dat[0]);
}
/*  End of tmpl_2DFloat_Positive_Polar_Angle.                                 */

#endif
/*  End of include guard.                                                     */
