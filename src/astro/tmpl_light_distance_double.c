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
 *                         tmpl_light_distance_double                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes distance traveled by light over a given time interval.       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Light_Distance                                            *
 *  Purpose:                                                                  *
 *      Computes the distance traveled by light in a vacuum.                  *
 *  Arguments:                                                                *
 *      t0 (const double):                                                    *
 *          The start time, in seconds.                                       *
 *      t1 (const double):                                                    *
 *          The final time, in seconds.                                       *
 *  Output:                                                                   *
 *      dist (double):                                                        *
 *          The distance traveled by light over time |t1 - t0|.               *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_Double_Dist:                                                 *
 *              Computes the distance on the number line form x to y.         *
 *  Method:                                                                   *
 *      Compute SPEED_OF_LIGHT * |t1 - t0|, in kilometers per second.         *
 *  Notes:                                                                    *
 *      1.) The units are kilometers per second.                              *
 *      2.) Distance is a non-negative quantity.                              *
 *      3.) No checks for NaNs or Infs are made.                              *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_astro.h:                                                         *
 *          Function prototype given here.                                    *
 *  2.) tmpl_math.h:                                                          *
 *          Header file containing trigonometric functions.                   *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 30, 2024                                            *
 ******************************************************************************/

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_astro.h>

/*  Distance function found here.                                             */
#include <libtmpl/include/tmpl_math.h>

/*  The speed of light, in kilometers per second, as a double.                */
#define TMPL_SPEED_OF_LIGHT_KILOMETERS_PER_SECOND (299792.4580)

/*  Function for computing the distance light travels in time t1-t0.          */
double tmpl_Double_Light_Distance(const double t0, const double t1)
{
    return TMPL_SPEED_OF_LIGHT_KILOMETERS_PER_SECOND*tmpl_Double_Dist(t0, t1);
}
/*  End tmpl_Double_Light_Distance.                                           */

/*  Undefine everything in case someone wants to #include this file.          */
#undef TMPL_SPEED_OF_LIGHT_KILOMETERS_PER_SECOND
