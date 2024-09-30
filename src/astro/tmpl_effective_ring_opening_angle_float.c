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
 *                  tmpl_effective_ring_opening_angle_float                   *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the effective ring opening angle of a planetary ring system. *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Effecting_Ring_Opening_Angle                               *
 *  Purpose:                                                                  *
 *      Computes the effective ring opening angle of a planetary ring system  *
 *      from the azimuthal angle of a point under consideration, and from     *
 *      the ring opening angle of the ring plane with respect to the          *
 *      observer.                                                             *
 *  Arguments:                                                                *
 *      opening (const float):                                                *
 *          The opening angle of the ring plane with respect to the observer, *
 *          in radians. Most often this is the angle made between the line    *
 *          going from the core of the Earth and the core of the planet with  *
 *          respect to the ring plane.                                        *
 *      azimuth (const float):                                                *
 *          The azimuthal angle, in radians, of the point under consideration.*
 *  Output:                                                                   *
 *      eff_opening (float):                                                  *
 *          The effective ring opening angle.                                 *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_Float_Cos:                                                   *
 *              Computes cosine, in radians.                                  *
 *          tmpl_Float_Tan:                                                   *
 *              Computes tangent, in radians.                                 *
 *          tmpl_Float_Arctan2:                                               *
 *              Computes the angle made by the point (x, y) and the x axis.   *
 *  Method:                                                                   *
 *      Apply equation 16 from Gresh et. al, 1986:                            *
 *                                                                            *
 *          B    = atan2(tan(opening), cos(azimuth))                          *
 *           eff                                                              *
 *                                                                            *
 *  Notes:                                                                    *
 *      1.) All angles are in radians. The output angle is also in radians.   *
 *      2.) No checks for NaNs or Infs are made.                              *
 *  References:                                                               *
 *      1.) An Analysis of Bending Waves in Saturn's Rings Using Voyager      *
 *          Radio Occultation Data, Gresh, Rosen, Tyler, 1986, Icarus Vol 68. *
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

/*  Trigonometric functions found here.                                       */
#include <libtmpl/include/tmpl_math.h>

/*  Function for computing the effective opening angle for a ring plane.      */
float
tmpl_Float_Effecting_Ring_Opening_Angle(const float opening,
                                        const float azimuth)
{
    /*  Following Equation 16 from Gresh 1986, compute the effective angle.   */
    const float tan_b = tmpl_Float_Tan(opening);
    const float cos_phi = tmpl_Float_Cos(azimuth);
    return tmpl_Float_Arctan2(tan_b, cos_phi);
}
/*  End tmpl_Float_Effecting_Ring_Opening_Angle.                              */
