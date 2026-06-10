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
 *                           tmpl_unit_clamp_float                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes f(x) = Min(Max(x, 0), 1). That is, "clamps" the input.       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Unit_Clamp                                                 *
 *  Purpose:                                                                  *
 *      Clamps a real number to fall between zero and one.                    *
 *                                                                            *
 *          clamp(x) = Min(Max(x, 0), 1)                                      *
 *                                                                            *
 *  Arguments:                                                                *
 *      x (const float):                                                      *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      clamp_x (float):                                                      *
 *          The clamped value of x. Lies between 0 and 1.                     *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Check if 0 <= x <= 1. If so, return x. Otherwise "clamp" the input    *
 *      and return 0 if too small and 1 if too big.                           *
 *  Notes:                                                                    *
 *      1.) There are no checks for NaN or infinity.                          *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_INLINE_DECL macro.                    *
 *  2.) tmpl_attributes.h:                                                    *
 *          Provides optional C23 attributes for optimization.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 19, 2023                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2026/06/10: Ryan Maguire                                                  *
 *      Added C23 attributes to improve optimization on modern compilers.     *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_INLINE_MATH_UNIT_CLAMP_FLOAT_H
#define TMPL_INLINE_MATH_UNIT_CLAMP_FLOAT_H

/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  Single precision unit clamp function.                                     */
TMPL_CONST_FUNC
TMPL_INLINE_DECL
float tmpl_Float_Unit_Clamp(const float x)
TMPL_UNSEQUENCED
{
    /*  If the input falls to the left of the allowed interval (too small),   *
     *  clip it and return the minimum allowed value (which is zero).         */
    if (x < 0.0F)
        return 0.0F;

    /*  Similarly for large values. Clamp to the maximum allowed value.       */
    if (x > 1.0F)
        return 1.0F;

    /*  Otherwise the input falls between zero and one. Return the input.     */
    return x;
}
/*  End of tmpl_Float_Unit_Clamp.                                             */

#endif
/*  End of include guard.                                                     */
