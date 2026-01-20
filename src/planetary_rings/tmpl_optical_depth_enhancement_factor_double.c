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
 *                tmpl_optical_depth_enhancement_factor_double                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the beta factor (enhancement factor) for optical depth.      *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Optical_Depth_Enhancement_Factor                          *
 *  Purpose:                                                                  *
 *      Computes the beta factor for the optical depth calculation for        *
 *      occultation observations in a planetary ring system.                  *
 *  Arguments:                                                                *
 *      opening (const double):                                               *
 *          The opening angle of the ring plane with respect to the observer, *
 *          in radians. Most often this is the angle made between the line    *
 *          going from the core of the Earth and the core of the planet with  *
 *          respect to the ring plane.                                        *
 *      azimuth (const double):                                               *
 *          The azimuthal angle, in radians, of the point under consideration.*
 *  Output:                                                                   *
 *      beta (double):                                                        *
 *          The enhancement factor, unitless.                                 *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_Double_Cos:                                                  *
 *              Computes cosine, in radians.                                  *
 *          tmpl_Double_Tan:                                                  *
 *              Computes tangent, in radians.                                 *
 *  Method:                                                                   *
 *      Apply equation 16 from Gresh et. al, 1986:                            *
 *                                                                            *
 *          Beta = tan(opening) / cos(azimuth)                                *
 *                                                                            *
 *  Notes:                                                                    *
 *      1.) All angles are in radians. The output is unitless.                *
 *      2.) No checks for NaNs or Infs are made.                              *
 *  References:                                                               *
 *      1.) An Analysis of Bending Waves in Saturn's Rings Using Voyager      *
 *          Radio Occultation Data, Gresh, Rosen, Tyler, 1986, Icarus Vol 68. *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  None.                                                                     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 1, 2024                                               *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2026/01/20: Ryan Maguire                                                  *
 *      Moved function from astro directory to planetary_rings.               *
 ******************************************************************************/

/*  Function prototype / forward declaration.                                 */
extern double
tmpl_Double_Optical_Depth_Enhancement_Factor(const double opening,
                                             const double azimuth);

/*  Trig functions needed for the computation.                                */
extern double tmpl_Double_Cos(const double x);
extern double tmpl_Double_Tan(const double x);

/*  Function for computing the beta factor for optical depth.                 */
double
tmpl_Double_Optical_Depth_Enhancement_Factor(const double opening,
                                             const double azimuth)
{
    /*  Following Equation 16 from Gresh 1986, compute the effective angle.   */
    const double tan_b = tmpl_Double_Tan(opening);
    const double cos_phi = tmpl_Double_Cos(azimuth);
    return cos_phi / tan_b;
}
/*  End tmpl_Double_Optical_Depth_Enhancement_Factor.                         */
