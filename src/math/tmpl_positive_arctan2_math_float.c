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
 *                        tmpl_positive_arctan2_float                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Compute the positive angle the point (x, y) makes with the x axis.    *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Positive_Arctan2                                           *
 *  Purpose:                                                                  *
 *      Computes the positive angle the point (x, y) makes with the x axis.   *
 *  Arguments:                                                                *
 *      y (const float):                                                      *
 *          A real number, the vertical component of the point.               *
 *      x (const float):                                                      *
 *          A real number, the horizontal component of the point.             *
 *  Output:                                                                   *
 *      theta (float):                                                        *
 *          The angle, between 0 and 2pi, the point (x, y) makes with the     *
 *          x axis.                                                           *
 *  Called Functions:                                                         *
 *      src/math/                                                             *
 *          tmpl_Float_Arctan2:                                               *
 *              Computes the standard atan2 function, returning an angle      *
 *              between -pi and pi.                                           *
 *  Method:                                                                   *
 *      Call the tmpl_Float_Arctan2 function and shift the result by          *
 *      2 * pi if the output is negative.                                     *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing the TMPL_ALWAYS_INLINE macro.              *
 *  2.) tmpl_attributes.h:                                                    *
 *          Provides optional C23 attributes for optimization.                *
 *  3.) tmpl_math.h:                                                          *
 *          Header file providing the forward declaration and arctan2.        *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 6, 2025                                                   *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2026/08/12: Ryan Maguire                                                  *
 *      Merged inline and non-inline versions, added TMPL_ALWAYS_INLINE use.  *
 ******************************************************************************/

/*  Location of the TMPL_ALWAYS_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  2 pi, and other math constants, found here.                               */
#include <libtmpl/include/constants/tmpl_math_constants.h>

/*  Function prototype / forward declaration and arctan2 found here.          */
#include <libtmpl/include/tmpl_math.h>

/*  Single-precision positive angle function.                                 */
TMPL_CONST_FUNC
TMPL_ALWAYS_INLINE
float
tmpl_Float_Positive_Arctan2(const float y, const float x)
TMPL_UNSEQUENCED
{
    /*  Most of the work is handled by the Arctan2 routine.                   */
    const float angle = tmpl_Float_Arctan2(y, x);

    /*  Shift by two pi if the angle is negative. Since angles are equivalent *
     *  mod two pi, this does not change the true angle. The Arctan2 function *
     *  always returns a value between -pi and pi, so shifting by two pi      *
     *  guarantees the output is non-negative. Note, if "angle" is NaN, the   *
     *  output will also be NaN since comparing a NaN using "<" always        *
     *  returns False. Hence there are no checks for NaNs here.               */
    if (angle < 0.0F)
        return angle + tmpl_float_two_pi;

    /*  Otherwise the angle lies between 0 and pi already. Simply return it.  */
    return angle;
}
/*  End of tmpl_Float_Positive_Arctan2.                                       */
