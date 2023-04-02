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
 *                      tmpl_cyl_fresnel_psi_alt_double                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the Cylindrical Fresnel kernel at double precision.          *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Cyl_Fresnel_Psi_Alt                                       *
 *  Purpose:                                                                  *
 *      Computes the cylindrical Fresnel kernel at double precision with all  *
 *      angles in radians. The lengths may be in whatever units, but they     *
 *      must be in the same units. Nearly identical to                        *
 *      tmpl_Double_Cyl_Fresnel_Psi, this function takes in the "weighted"    *
 *      wavenumber kD, instead of just k. Useful for when you want kD to be   *
 *      a constant, but allow D to vary.                                      *
 *  Arguments:                                                                *
 *      kD (double):                                                          *
 *          The weighted wavenumber, unitless.                                *
 *      r (double):                                                           *
 *          The "dummy" radius, usually a variable that is integrated over.   *
 *      r0 (double):                                                          *
 *          The radius of the point of interest.                              *
 *      phi (double):                                                         *
 *          The "dummy" azimuthal angle, often integrated over.               *
 *      phi0 (double):                                                        *
 *          The azimuthal angle of the point of interest.                     *
 *      B (double):                                                           *
 *          The opening angle of the plane. For planetary ring systems this   *
 *          is the ring opening angle of the rings with respect to Earth.     *
 *      D (double):                                                           *
 *          The distance from the observer to the point in the plane.         *
 *  Outputs:                                                                  *
 *      psi (double):                                                         *
 *          The cylindrical Fresnel kernel as a function of the inputs.       *
 *  Called Functions:                                                         *
 *      tmpl_Double_Cos (tmpl_math.h):                                        *
 *          Computes cosine, in radians.                                      *
 *      tmpl_Double_Sqrt (tmpl_math.h):                                       *
 *          Computes the square root of a positive number.                    *
 *  Method:                                                                   *
 *      Following Marouf, Tyler, and Rosen (1986), appeal to equations        *
 *      (4a), (4b), and (4c) to compute the Fresnel kernel.                   *
 *  Notes:                                                                    *
 *      Angles must be in radians. Lengths can be in whatever units, but they *
 *      must be the same units.                                               *
 *  References:                                                               *
 *      1.) Profiling Saturn's Rings, Marouf, Tyler, Rosen 1986, Icarus 68.   *
 *      2.) Introduction to Fourier Optics, Joseph Goodman, 2005.             *
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

/*  Function for computing the cylindrical Fresnel kernel.                    */
double
tmpl_Double_Cyl_Fresnel_Psi_Alt(double kD, double r, double r0, double phi,
                                double phi0, double B, double D)
{
    /*  Compute 1/D and it's square to save the number of divisions we need   *
     *  to compute. Multiplication is usually ~10 times faster.               */
    const double rcpr_D = 1.0 / D;
    const double rcpr_D_squared = rcpr_D * rcpr_D;

    /*  Precompute cosines and sines to save on computations.                 */
    const double cos_B = tmpl_Double_Cos(B);
    const double cos_phi = tmpl_Double_Cos(phi);
    const double cos_phi0 = tmpl_Double_Cos(phi0);
    const double cos_phi_phi0 = tmpl_Double_Cos(phi - phi0);

    /*  Compute xi variable (MTR86 Equation 4b) and eta (Equation 4c).        */
    const double xi = (cos_B * rcpr_D) * (r * cos_phi - r0 * cos_phi0);
    const double eta = (r0*r0 + r*r - 2.0*r*r0*cos_phi_phi0) * rcpr_D_squared;

    /* Sign of xi swapped from MTR86.                                         */
    return kD * (tmpl_Double_Sqrt(1.0 + eta - 2.0*xi) + xi - 1.0);
}
/*  End of tmpl_Double_Cyl_Fresnel_Psi_Alt.                                   */
