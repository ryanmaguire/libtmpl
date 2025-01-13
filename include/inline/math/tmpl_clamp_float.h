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
 *                              tmpl_clamp_float                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes f(x) = Min(Max(x, min), max). That is, "clamps" the input.   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Clamp                                                      *
 *  Purpose:                                                                  *
 *      Clamps a real number to fall between two values.                      *
 *                                                                            *
 *          clamp(x, min, max) = Min(Max(x, min), max)                        *
 *                                                                            *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *      min (float):                                                          *
 *          The smallest allowed value for x.                                 *
 *      max (float):                                                          *
 *          The largest allowed value for x.                                  *
 *  Output:                                                                   *
 *      clamp_x (float):                                                      *
 *          The clamped value of x. Lies between min and max.                 *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Check if min <= x <= max. If so, return x. Otherwise "clamp" the      *
 *      input and return min if too small and max if too big.                 *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_INLINE_DECL macro.                    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 19, 2023                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_CLAMP_FLOAT_H
#define TMPL_CLAMP_FLOAT_H

/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  Single precision clamp function.                                          */
TMPL_INLINE_DECL
float tmpl_Float_Clamp(float x, float min, float max)
{
    /*  If the input falls to the left of the allowed interval (is too small),*
     *  clip it and return the minimum allowed value.                         */
    if (x < min)
        return min;

    /*  Similarly for large values. Clamp to the maximum allowed value.       */
    else if (x > max)
        return max;

    /*  Otherwise the input falls between min and max. Return the input.      */
    return x;
}
/*  End of tmpl_Float_Clamp.                                                  */

#endif
/*  End of include guard.                                                     */
