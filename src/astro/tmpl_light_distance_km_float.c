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
 *                        tmpl_light_distance_km_float                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the distance (kilometers) traveled by light over time.       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Light_Distance_KM                                          *
 *  Purpose:                                                                  *
 *      Computes the distance traveled by light in a vacuum, in kilometers.   *
 *  Arguments:                                                                *
 *      t0 (const float):                                                     *
 *          The start time, in seconds.                                       *
 *      t1 (const float):                                                     *
 *          The final time, in seconds.                                       *
 *  Output:                                                                   *
 *      dist (float):                                                         *
 *          The distance traveled in kilometers by light over time |t1 - t0|. *
 *  Called Functions:                                                         *
 *      src/                                                                  *
 *          tmpl_Float_Dist:                                                  *
 *              Computes the distance on the number line from x to y.         *
 *  Method:                                                                   *
 *      Compute speed_of_light * |t1 - t0|.                                   *
 *  Notes:                                                                    *
 *      1.) Lengths are in kilometers, times are in seconds.                  *
 *                                                                            *
 *      2.) Distance is a non-negative quantity.                              *
 *                                                                            *
 *      3.) No checks for NaNs or infinity are made.                          *
 *                                                                            *
 *      4.) There is no assumption that t0 < t1 or t1 < t0. That is, you may  *
 *          swap the order of the inputs without changing the output.         *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Provides the TMPL_ALWAYS_INLINE macro.                            *
 *  2.) tmpl_attributes.h:                                                    *
 *          Provides (optional) C23 attributes for optimization.              *
 *  3.) tmpl_astro.h:                                                         *
 *          Function prototype given here.                                    *
 *  4.) tmpl_astro_constants.h:                                               *
 *          Provides useful astronomical constants, like the speed of light.  *
 *  5.) tmpl_math.h:                                                          *
 *          Header file containing the distance function.                     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 30, 2024                                            *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2026/07/23: Ryan Maguire                                                  *
 *      Added C23 attributes, added KM to function name.                      *
 ******************************************************************************/

/*  TMPL_ALWAYS_INLINE macro found here, used for link-time optimization.     */
#include <libtmpl/include/tmpl_config.h>

/*  Optional C23 attributes for optimization provided here.                   */
#include <libtmpl/include/tmpl_attributes.h>

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_astro.h>

/*  Speed of light in kilometers per second found here.                       */
#include <libtmpl/include/constants/tmpl_astro_constants.h>

/*  Distance function found here.                                             */
#include <libtmpl/include/tmpl_math.h>

/*  Function for computing the distance light travels in time t1 - t0.        */
TMPL_CONST_FUNC
TMPL_ALWAYS_INLINE
float tmpl_Float_Light_Distance_KM(const float t0, const float t1)
TMPL_UNSEQUENCED
{
    return tmpl_float_speed_of_light_kmps * tmpl_Float_Dist(t0, t1);
}
/*  End tmpl_Float_Light_Distance_KM.                                         */
