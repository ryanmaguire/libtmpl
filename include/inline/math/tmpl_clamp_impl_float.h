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
 *                           tmpl_clamp_impl_float                            *
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
 *      x (const float):                                                      *
 *          A real number.                                                    *
 *      min (const float):                                                    *
 *          The smallest allowed value for x.                                 *
 *      max (const float):                                                    *
 *          The largest allowed value for x.                                  *
 *  Output:                                                                   *
 *      clamp_x (float):                                                      *
 *          The clamped value of x. Lies between min and max.                 *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use the formula directly, return Min(Max(x, min), max).               *
 *  Notes:                                                                    *
 *      1.) There are no checks for NaN or infinity.                          *
 *                                                                            *
 *      2.) There are no checks for min < max.                                *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_INLINE_DECL macro.                    *
 *  2.) tmpl_attributes.h:                                                    *
 *          Provides optional C23 attributes for optimization.                *
 *  3.) tmpl_max.h:                                                           *
 *          Header where the TMPL_MAX macro is defined.                       *
 *  4.) tmpl_min.h:                                                           *
 *          Header where the TMPL_MIN macro is defined.                       *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 19, 2023                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2026/06/10: Ryan Maguire                                                  *
 *      Added C23 attributes to improve optimization on modern compilers.     *
 *      Changed implementation to use the TMPL_MIN and TMPL_MAX macros.       *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_INLINE_MATH_CLAMP_IMPL_FLOAT_H
#define TMPL_INLINE_MATH_CLAMP_IMPL_FLOAT_H

/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  TMPL_MAX and TMPL_MIN macros provided here.                               */
#include <libtmpl/include/helper/tmpl_max.h>
#include <libtmpl/include/helper/tmpl_min.h>

/*  Single precision clamp function.                                          */
TMPL_CONST_FUNC
TMPL_INLINE_DECL
float
tmpl_Float_Clamp(const float x, const float min, const float max)
TMPL_UNSEQUENCED
{
    /*  Use the clamp formula directly, compute Min(Max(x, min), max).        */
    const float lower_clamp = TMPL_MAX(x, min);
    return TMPL_MIN(lower_clamp, max);
}
/*  End of tmpl_Float_Clamp.                                                  */

#endif
/*  End of include guard.                                                     */
