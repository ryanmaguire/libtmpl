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
 *                   tmpl_cyl_fresnel_dpsi_dphi_deg_double                    *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the first partial derivative of the Cylindrical Fresnel      *
 *      kernel with respect to phi at double precision.                       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Cyl_Fresnel_dPsi_dPhi_Deg                                 *
 *  Purpose:                                                                  *
 *      Computes the first partial derivative of the cylindrical Fresnel      *
 *      kernel with respect to phi at double precision with all angles in     *
 *      degrees. The lengths may be in whatever units, but they must be in    *
 *      the same units.                                                       *
 *  Arguments:                                                                *
 *      k (double):                                                           *
 *          The wavenumber, in the reciprocal of the units of r.              *
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
 *      dpsi_dphi (double):                                                   *
 *          The first partial derivative of the cylindrical Fresnel kernel    *
 *          with respect to phi.                                              *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_Double_Cosd:                                                 *
 *              Computes cosine, in degrees.                                  *
 *          tmpl_Double_SinCosd:                                              *
 *              Computes sine and cosine, in degrees.                         *
 *          tmpl_Double_Sqrt:                                                 *
 *              Computes the square root of a positive number.                *
 *  Method:                                                                   *
 *      Use the product and chain rules a few times to compute. We have:      *
 *                                                                            *
 *          xi = [r cos(phi) - r0 cos(phi0)] cos(B) / D                       *
 *          eta = [r^2 + r0^2 - 2 r r0 cos(phi - phi0)] / D^2                 *
 *          psi = kD [sqrt(1 + eta - 2 xi) + xi - 1]                          *
 *                                                                            *
 *      Note the sign of xi is flipped from the MTR86 definition.             *
 *                                                                            *
 *          psi' = (kD [sqrt(1 + eta - 2 xi) + xi - 1])'                      *
 *               = kD ([sqrt(1 + eta - 2 xi)]' + xi')                         *
 *               = kD ([eta' - 2 xi'] / (2 sqrt(1 + eta - 2 xi)) + xi')       *
 *                                                                            *
 *      We need to compute xi' and eta'.                                      *
 *                                                                            *
 *          xi' = ([r cos(phi) - r0 cos(phi0)] cos(B) / D)'                   *
 *              = -r sin(phi) cos(B) / D                                      *
 *                                                                            *
 *      For the eta factor we get:                                            *
 *                                                                            *
 *          eta' = ([r^2 + r0^2 - 2 r r0 cos(phi - phi0)] / D^2)'             *
 *               = 2 r r0 sin(phi - phi0) / D^2                               *
 *                                                                            *
 *      The first partial derivative is:                                      *
 *                                                                            *
 *          kD ([eta' - 2 xi'] / [2 sqrt(1 + eta - 2 xi)) + xi']              *
 *                                                                            *
 *  Notes:                                                                    *
 *      Angles must be in degrees. Lengths can be in whatever units, but they *
 *      must be the same units.                                               *
 *                                                                            *
 *      It is assumed that B and D are independent of phi. This may not be    *
 *      the case for "real" geometry from actual data sets.                   *
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
 *  2023/03/22: Ryan Maguire                                                  *
 *      Migrated from rss_ringoccs. Cleaned up code.                          *
 ******************************************************************************/

/*  Trig functions and square root found here.                                */
#include <libtmpl/include/tmpl_math.h>

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_cyl_fresnel_optics.h>

/*  Computes the first partial derivative of psi with respect to phi.         */
double
tmpl_Double_Cyl_Fresnel_dPsi_dPhi_Deg(double k, double r, double r0, double phi,
                                      double phi0, double B, double D)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    double xi, eta, psi0, dxi, deta, sin_phi, cos_phi;
    double cos_phi0, sin_phi0, cos_phi_phi0, sin_phi_phi0;

    /*  Compute 1/D and it's square to save the number of divisions we need   *
     *  to compute. Multiplication is usually ~10 times faster.               */
    const double rcpr_D = 1.0 / D;
    const double rcpr_D_squared = rcpr_D * rcpr_D;

    /*  Precompute cosines and sines to save on computations.                 */
    const double cos_B = tmpl_Double_Cosd(B);

    /*  This term appears in dxi and xi.                                      */
    const double xi_factor = cos_B * rcpr_D;

    /*  And this term appears in eta and deta.                                */
    const double eta_factor = 2.0 * r * r0 * rcpr_D_squared;

    /*  Compute sine and cosine simultaneously using SinCosd.                 */
    tmpl_Double_SinCosd(phi, &sin_phi, &cos_phi);
    tmpl_Double_SinCosd(phi0, &sin_phi0, &cos_phi0);

    /*  Since we've computed cos and sin of phi and phi0, cos and sin of      *
     *  phi-phi0 can be computed without the need to call cos and sin again.  */
    cos_phi_phi0 = cos_phi*cos_phi0 + sin_phi*sin_phi0;
    sin_phi_phi0 = sin_phi*cos_phi0 - cos_phi*sin_phi0;

    /*  Compute xi variable (MTR86 Equation 4b) and eta (Equation 4c).        */
    xi = xi_factor * (r * cos_phi - r0 * cos_phi0);
    eta = (r0*r0 + r*r)*rcpr_D_squared - eta_factor*cos_phi_phi0;
    psi0 = tmpl_Double_Sqrt(1.0 + eta - 2.0*xi);

    /*  Compute derivatives.                                                  */
    dxi = -xi_factor * (r * sin_phi);
    deta = eta_factor * sin_phi_phi0;

    /*  Compute the first partial derivative.                                 */
    return k*D*((0.5/psi0)*(deta - 2.0*dxi) + dxi);
}
/*  End of tmpl_Double_Cyl_Fresnel_dPsi_dPhi_Deg.                             */
