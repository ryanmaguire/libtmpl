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
 *                         tmpl_unit_clamp_impl_float                         *
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
 *      Use the formula directly, return Min(Max(x, 0), 1).                   *
 *  Notes:                                                                    *
 *      1.) There are no checks for NaN or infinity.                          *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing the TMPL_ALWAYS_INLINE macro.              *
 *  2.) tmpl_attributes.h:                                                    *
 *          Provides optional C23 attributes for optimization.                *
 *  3.) tmpl_max.h:                                                           *
 *          Header where the TMPL_MAX macro is defined.                       *
 *  4.) tmpl_min.h:                                                           *
 *          Header where the TMPL_MIN macro is defined.                       *
 *  5.) tmpl_math.h:                                                          *
 *          Location of the function prototype / forward declaration.         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 19, 2023                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2026/06/10: Ryan Maguire                                                  *
 *      Added C23 attributes to improve optimization on modern compilers.     *
 *      Changed implementation to use the TMPL_MIN and TMPL_MAX macros.       *
 *  2026/07/13: Ryan Maguire                                                  *
 *      Merged inline and non-inline versions, added TMPL_ALWAYS_INLINE macro.*
 ******************************************************************************/

/*  Location of the TMPL_ALWAYS_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  TMPL_MAX and TMPL_MIN macros provided here.                               */
#include <libtmpl/include/helper/tmpl_max.h>
#include <libtmpl/include/helper/tmpl_min.h>

/*  Function prototype / forward declaration found here.                      */
#include <libtmpl/include/tmpl_math.h>

/*  Single precision unit clamp function.                                     */
TMPL_CONST_FUNC
TMPL_ALWAYS_INLINE
float tmpl_Float_Unit_Clamp(const float x)
TMPL_UNSEQUENCED
{
    /*  Use the clamp formula directly, compute Min(Max(x, 0), 1).            */
    const float lower_clamp = TMPL_MAX(x, 0.0F);
    return TMPL_MIN(lower_clamp, 1.0F);
}
/*  End of tmpl_Float_Unit_Clamp.                                             */
