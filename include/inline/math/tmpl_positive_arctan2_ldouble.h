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
 *                       tmpl_positive_arctan2_ldouble                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Compute the positive angle the point (x, y) makes with the x axis.    *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Positive_Arctan2                                         *
 *  Purpose:                                                                  *
 *      Computes the positive angle the point (x, y) makes with the x axis.   *
 *  Arguments:                                                                *
 *      y (long double):                                                      *
 *          A real number, the vertical component of the point.               *
 *      x (long double):                                                      *
 *          A real number, the horizontal component of the point.             *
 *  Output:                                                                   *
 *      theta (long double):                                                  *
 *          The angle, between 0 and 2pi, the point (x, y) makes with the     *
 *          x axis.                                                           *
 *  Called Functions:                                                         *
 *      src/math/                                                             *
 *          tmpl_LDouble_Arctan2:                                             *
 *              Computes the standard atan2 function, returning an angle      *
 *              between -pi and pi.                                           *
 *  Method:                                                                   *
 *      Call the tmpl_LDouble_Arctan2 function and shift the result by        *
 *      2*pi if the output is negative.                                       *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_INLINE_DECL macro.                    *
 *  2.) tmpl_math_constants.h:                                                *
 *          Header file providing math constants like 2 pi.                   *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 6, 2025                                                   *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_POSITIVE_ARCTAN2_LDOUBLE_H
#define TMPL_POSITIVE_ARCTAN2_LDOUBLE_H

/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  tmpl_LDouble_Two_Pi provided here.                                        */
#include <libtmpl/include/constants/tmpl_math_constants.h>

/*  Tell the compiler about the main Arctan2 function.                        */
extern long double tmpl_LDouble_Arctan2(long double y, long double x);

/*  Long double precision positive angle function.                            */
TMPL_INLINE_DECL
long double tmpl_LDouble_Positive_Arctan2(long double y, long double x)
{
    /*  Most of the work is handled by the Arctan2 routine.                   */
    const long double angle = tmpl_LDouble_Arctan2(y, x);

    /*  Shift by two pi if the angle is negative. Since angles are equivalent *
     *  mod two pi, this does not change the true angle. The Arctan2 function *
     *  always returns a value between -pi and pi, so shifting by two pi      *
     *  guarantees the output is non-negative. Note, if "angle" is NaN, the   *
     *  output will also be NaN since comparing a NaN using "==" always       *
     *  returns False. Hence there are no checks for NaNs here.               */
    if (angle < 0.0L)
        return angle + tmpl_LDouble_Two_Pi;

    /*  Otherwise the angle lies between 0 and pi already. Simply return it.  */
    return angle;
}
/*  End of tmpl_LDouble_Positive_Arctan2.                                     */

#endif
/*  End of include guard.                                                     */
