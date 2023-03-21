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
 *                       tmpl_cyl_fresnel_scale_double                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the Cylindrical Fresnel scale at double precision.           *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Cyl_Fresnel_Scale                                         *
 *  Purpose:                                                                  *
 *      Computes the cylindrical Fresnel scale at double precision with all   *
 *      angles in radians. The lengths may be in whatever units, but they     *
 *      must be in the same units.                                            *
 *  Arguments:                                                                *
 *      lamda (double):                                                       *
 *          The wavelength, in the same units as D.                           *
 *      D (double):                                                           *
 *          The distance from the source of light to the plane.               *
 *      phi (double):                                                         *
 *          The azimuthal angle in radians.                                   *
 *      B (double):                                                           *
 *          The opening angle of the plane. For planetary ring systems this   *
 *          is the ring opening angle of the rings with respect to Earth.     *
 *  Outputs:                                                                  *
 *      f_scale (double):                                                     *
 *          The cylindrical Fresnel scale.                                    *
 *  Called Functions:                                                         *
 *      tmpl_Double_Sin (tmpl_math.h):                                        *
 *          Computes sine, in radians.                                        *
 *      tmpl_Double_SinCos (tmpl_math.h):                                     *
 *          Simultaneously computes sine and cosine of the input.             *
 *      tmpl_Double_Sqrt (tmpl_math.h):                                       *
 *          Computes the square root of a positive number.                    *
 *  Method:                                                                   *
 *      Following Marouf, Tyler, and Rosen (1986), appeal to equation (6)     *
 *      to compute the cylindrical Fresnel scale.                             *
 *  Notes:                                                                    *
 *      Angles must be in radians. Lengths can be in whatever units, but they *
 *      must be the same units.                                               *
 *  References:                                                               *
 *      1.) Profiling Saturn's Rings, Marouf, Tyler, Rosen 1986, Icarus 68.   *
 *      2.) Introduction to Fourier Optics, Joseph Goodman, 2005.             *
 *      3.) Principles of Optics, Max Born, Emil Wolf, 7th edition, 1999.     *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file with cosine and sqrt.                                 *
 *  2.) tmpl_cyl_fresnel_optics.h:                                            *
 *          Header file where the prototype is given.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 8, 2021                                                  *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/03/21: Ryan Maguire                                                  *
 *      Migrated from rss_ringoccs. Cleaned up code.                          *
 ******************************************************************************/

/*  Trig functions and square root found here.                                */
#include <libtmpl/include/tmpl_math.h>

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_cyl_fresnel_optics.h>

/*  Function for computing the cylindrically symmetric Fresnel scale.         */
double
tmpl_Double_Cyl_Fresnel_Scale(double lambda, double D, double phi, double B)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    double cos_B, sin_B, cos_B_sin_phi;
    double numerator, denominator;

    /*  The sine of the azimuthal angle appears in the numerator.             */
    const double sin_phi = tmpl_Double_Sin(phi);

    /*  Compute cos(B) and sin(B) simultaneously with SinCos.                 */
    tmpl_Double_SinCos(B, &sin_B, &cos_B);

    /*  The product of cos(B) and sin(phi) appears in the numerator.          */
    cos_B_sin_phi = cos_B * sin_phi;

    /*  Use Eqn (6) from MTR86 and compute the square of the Fresnel scale.   */
    numerator = lambda * D * (1.0 - cos_B_sin_phi*cos_B_sin_phi);

    /*  Next, compute the denominator of the square of the Fresnel scale.     */
    denominator = 2.0 * sin_B * sin_B;

    /*  numerator / denominator gives F^2. Return the square root of this.    */
    return tmpl_Double_Sqrt(numerator / denominator);
}
/*  End of tmpl_Double_Cyl_Fresnel_Scale.                                     */
