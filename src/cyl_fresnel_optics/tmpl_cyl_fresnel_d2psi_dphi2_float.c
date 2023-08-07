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
 *                     tmpl_cyl_fresnel_d2psi_dphi2_float                     *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the second partial derivative of the Cylindrical Fresnel     *
 *      kernel with respect to phi at single precision.                       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Cyl_Fresnel_d2Psi_dPhi2                                    *
 *  Purpose:                                                                  *
 *      Computes the second partial derivative of the cylindrical Fresnel     *
 *      kernel with respect to phi at single precision with all angles in     *
 *      radians. The lengths may be in whatever units, but they must be in    *
 *      the same units.                                                       *
 *  Arguments:                                                                *
 *      k (float):                                                            *
 *          The wavenumber, in the reciprocal of the units of r.              *
 *      r (float):                                                            *
 *          The "dummy" radius, usually a variable that is integrated over.   *
 *      r0 (float):                                                           *
 *          The radius of the point of interest.                              *
 *      phi (float):                                                          *
 *          The "dummy" azimuthal angle, often integrated over.               *
 *      phi0 (float):                                                         *
 *          The azimuthal angle of the point of interest.                     *
 *      B (float):                                                            *
 *          The opening angle of the plane. For planetary ring systems this   *
 *          is the ring opening angle of the rings with respect to Earth.     *
 *      D (float):                                                            *
 *          The distance from the observer to the point in the plane.         *
 *  Outputs:                                                                  *
 *      d2psi_dphi2 (float):                                                  *
 *          The second partial derivative of the cylindrical Fresnel kernel   *
 *          with respect to phi.                                              *
 *  Called Functions:                                                         *
 *      tmpl_Float_Cos (tmpl_math.h):                                         *
 *          Computes cosine, in radians.                                      *
 *      tmpl_Float_SinCos (tmpl_math.h):                                      *
 *          Computes sine and cosine, in radians.                             *
 *      tmpl_Float_Sqrt (tmpl_math.h):                                        *
 *          Computes the square root of a positive number.                    *
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
 *      The second partial derivative is then:                                *
 *                                                                            *
 *          psi'' = kD [                                                      *
 *              (eta'' - 2 xi'') / [2 sqrt(1 + eta - 2 xi)] +                 *
 *              (eta' - 2 xi') [1 / (2 sqrt(1 + eta - 2 xi))]' + xi''         *
 *          ]                                                                 *
 *                                                                            *
 *      The square root part simplifies, and we get:                          *
 *                                                                            *
 *          psi'' = kD [                                                      *
 *              (eta'' - 2 xi'') / [2 sqrt(1 + eta - 2 xi)] -                 *
 *              (eta' - 2 xi')^2 / [4 (1 + eta - 2 xi)^3/2] + xi''            *
 *          ]                                                                 *
 *                                                                            *
 *      The second derivative of xi is:                                       *
 *                                                                            *
 *          xi'' = -r cos(phi) cos(B) / D                                     *
 *                                                                            *
 *      And the second derivative of eta is:                                  *
 *                                                                            *
 *          eta'' = 2 r r0 cos(phi - phi0) / D^2                              *
 *                                                                            *
 *      Piecing all of this together gives us the second partial derivative.  *
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
 *  2023/03/20: Ryan Maguire                                                  *
 *      Migrated from rss_ringoccs. Cleaned up code.                          *
 ******************************************************************************/

/*  Trig functions and square root found here.                                */
#include <libtmpl/include/tmpl_math.h>

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_cyl_fresnel_optics.h>

/*  Computes the second partial derivative of psi with respect to phi.        */
float
tmpl_Float_Cyl_Fresnel_d2Psi_dPhi2(float k, float r, float r0, float phi,
                                   float phi0, float B, float D)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    float xi, eta, psi0, dxi, dxi2, deta, deta2, psi_d2, sin_phi, cos_phi;
    float cos_phi0, sin_phi0, cos_phi_phi0, sin_phi_phi0;
    float num_factor, rcpr_psi0, rcpr_psi0_cubed;

    /*  Compute 1/D and it's square to save the number of divisions we need   *
     *  to compute. Multiplication is usually ~10 times faster.               */
    const float rcpr_D = 1.0F / D;
    const float rcpr_D_squared = rcpr_D * rcpr_D;

    /*  Precompute cosines and sines to save on computations.                 */
    const float cos_B = tmpl_Float_Cos(B);

    /*  This term appears in dxi and dxi2 and xi.                             */
    const float xi_factor = cos_B * rcpr_D;

    /*  And this term appears in eta, deta, and deta2.                        */
    const float eta_factor = 2.0F * r * r0 * rcpr_D_squared;

    /*  Compute sine and cosine simultaneously using SinCos.                  */
    tmpl_Float_SinCos(phi, &sin_phi, &cos_phi);
    tmpl_Float_SinCos(phi0, &sin_phi0, &cos_phi0);

    /*  Since we've computed cos and sin of phi and phi0, cos and sin of      *
     *  phi-phi0 can be computed without the need to call cos and sin again.  */
    cos_phi_phi0 = cos_phi*cos_phi0 + sin_phi*sin_phi0;
    sin_phi_phi0 = sin_phi*cos_phi0 - cos_phi*sin_phi0;

    /*  Compute xi variable (MTR86 Equation 4b) and eta (Equation 4c).        */
    xi = xi_factor * (r * cos_phi - r0 * cos_phi0);
    eta = (r0*r0 + r*r)*rcpr_D_squared - eta_factor*cos_phi_phi0;
    psi0 = tmpl_Float_Sqrt(1.0F + eta - 2.0F*xi);
    rcpr_psi0 = 1.0F / psi0;
    rcpr_psi0_cubed = rcpr_psi0*rcpr_psi0*rcpr_psi0;

    /*  Compute derivatives.                                                  */
    dxi = -xi_factor * (r * sin_phi);
    dxi2 = -xi_factor * (r * cos_phi);
    deta = eta_factor * sin_phi_phi0;
    deta2 = eta_factor * cos_phi_phi0;

    /*  Compute the second partial derivative.                                */
    num_factor = deta - 2.0F*dxi;
    psi_d2 = -0.25F * rcpr_psi0_cubed * num_factor * num_factor;
    psi_d2 += (0.5F * rcpr_psi0) * (deta2 - 2.0F*dxi2) + dxi2;
    psi_d2 *= k*D;
    return psi_d2;
}
/*  End of tmpl_Double_Cyl_Fresnel_d2Psi_dPhi2.                               */
