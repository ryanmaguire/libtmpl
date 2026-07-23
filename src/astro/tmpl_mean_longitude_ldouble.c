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
 *                        tmpl_mean_longitude_ldouble                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes mean longitude from mean angular motion.                     *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Mean_Longitude                                           *
 *  Purpose:                                                                  *
 *      Computes mean longitude from mean angular motion.                     *
 *  Arguments:                                                                *
 *      epoch_mean_longitude (const long double):                             *
 *          The initial mean longitude at a given epoch.                      *
 *      mean_motion (const long double):                                      *
 *          The average angular speed needed to complete one full orbit.      *
 *      epoch (const long double):                                            *
 *          The moment in time for the initial mean longitude angle.          *
 *      time (const long double):                                             *
 *          The time the mean longitude is calculated with respect to.        *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Compute                                                               *
 *                                                                            *
 *          L = e + n * (t1 - t0)                                             *
 *                                                                            *
 *      where e is the epoch mean longitude, n is the mean angular motion,    *
 *      t0 is the epoch, and t1 is the desired time.                          *
 *  Notes:                                                                    *
 *      1.) The units for the epoch mean longitude and time may be arbitrary, *
 *          but the units for mean motion must be the ratio of your chosen    *
 *          units. That is, mean angular motion must have the units of        *
 *          epoch_mean_longitude / time.                                      *
 *                                                                            *
 *      2.) The units for the output angle will be the same as the units of   *
 *          the epoch mean longitude.                                         *
 *                                                                            *
 *      3.) No checks for NaNs or infinity are made.                          *
 *  References:                                                               *
 *      1.) Meeus, Jean (1991)                                                *
 *          Astronomical Algorithms, First Edition                            *
 *          William-Bell, Inc.                                                *
 *                                                                            *
 *          Chapter 31 describes the six orbital elements, and contains a     *
 *          brief description of mean longitude.                              *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Provides the TMPL_ALWAYS_INLINE macro.                            *
 *  2.) tmpl_attributes.h:                                                    *
 *          Provides (optional) C23 attributes for optimization.              *
 *  3.) tmpl_astro.h:                                                         *
 *          Function prototype given here.                                    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       July 23, 2026                                                 *
 ******************************************************************************/

/*  TMPL_ALWAYS_INLINE macro found here, used for link-time optimization.     */
#include <libtmpl/include/tmpl_config.h>

/*  Optional C23 attributes for optimization provided here.                   */
#include <libtmpl/include/tmpl_attributes.h>

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_astro.h>

/*  Function for computing mean longitude from mean motion.                   */
TMPL_CONST_FUNC
TMPL_ALWAYS_INLINE
long double
tmpl_LDouble_Mean_Longitude(const long double epoch_mean_longitude,
                            const long double  mean_motion,
                            const long double  epoch,
                            const long double  time)
TMPL_UNSEQUENCED
{
    /*  Mean motion measures the average rate of change in the longitude      *
     *  angle, meaning the net change in the mean longitude (not the true     *
     *  longitude) is simply the produce of the mean motion and the elapsed   *
     *  time. Compute this.                                                   */
    const long double  angle_change = mean_motion * (time - epoch);

    /*  The current mean longitude is the initial value plus the change.      */
    return epoch_mean_longitude + angle_change;
}
/*  End tmpl_LDouble_Mean_Longitude.                                          */
