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
 *                  tmpl_cyl_fresnel_dpsi_dphi_d_deg_ldouble                  *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the first partial derivative of the Cylindrical Fresnel      *
 *      kernel with respect to phi for long double. The distance D from       *
 *      the point on the plane to the observer is not a constant, but         *
 *      varies as a function of phi. The partial derivative of D with respect *
 *      to phi is thus included in the computation.                           *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Cyl_Fresnel_dPsi_dPhi_D                                  *
 *  Purpose:                                                                  *
 *      Computes the first partial derivative of the cylindrical Fresnel      *
 *      kernel with respect to phi at long double precision with all angles   *
 *      in degrees. The lengths may be in whatever units, but they must be in *
 *      the same units. For this function the distance D from the observer    *
 *      to the point on the plane is not constant, but varies as a function   *
 *      of phi. The partial derivative dD/dphi is used in the computation.    *
 *  Arguments:                                                                *
 *      k (long double):                                                      *
 *          The wavenumber, in the reciprocal of the units of r.              *
 *      r (long double):                                                      *
 *          The "dummy" radius, usually a variable that is integrated over.   *
 *      r0 (long double):                                                     *
 *          The radius of the point of interest.                              *
 *      phi (long double):                                                    *
 *          The "dummy" azimuthal angle, often integrated over.               *
 *      phi0 (long double):                                                   *
 *          The azimuthal angle of the point of interest.                     *
 *      B (long double):                                                      *
 *          The opening angle of the plane. For planetary ring systems this   *
 *          is the ring opening angle of the rings with respect to Earth.     *
 *      rx (long double):                                                     *
 *          The x coordinated of the observer with respect to the plane.      *
 *      ry (long double):                                                     *
 *          The y coordinated of the observer with respect to the plane.      *
 *      rz (long double):                                                     *
 *          The z coordinated of the observer with respect to the plane.      *
 *  Outputs:                                                                  *
 *      dpsi_dphi (long double):                                              *
 *          The first partial derivative of the cylindrical Fresnel kernel    *
 *          with respect to phi.                                              *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_LDouble_Cosd:                                                *
 *              Computes cosine, in degrees.                                  *
 *          tmpl_LDouble_SinCosd:                                             *
 *              Computes sine and cosine, in degrees.                         *
 *          tmpl_LDouble_Sqrt:                                                *
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
 *               = kD ([sqrt(1 + eta - 2 xi)]' + xi') +                       *
 *                 kD' (kD [sqrt(1 + eta - 2 xi) + xi - 1])                   *
 *               = kD ([eta' - 2 xi'] / (2 sqrt(1 + eta - 2 xi)) + xi') +     *
 *                 kD' (kD [sqrt(1 + eta - 2 xi) + xi - 1])                   *
 *                                                                            *
 *      We need to compute xi' and eta'.                                      *
 *                                                                            *
 *          xi' = ([r cos(phi) - r0 cos(phi0)] cos(B) / D)'                   *
 *              = -r sin(phi) cos(B) / D +                                    *
 *                 [r cos(phi) - r0 cos(phi0)] cos(B) (1 / D)'                *
 *              = -r sin(phi) cos(B) / D -                                    *
 *                 [r cos(phi) - r0 cos(phi0)] (cos(B) / D^2) D'              *
 *                                                                            *
 *      For the eta factor we get:                                            *
 *                                                                            *
 *          eta' = ([r^2 + r0^2 - 2 r r0 cos(phi - phi0)] / D^2)'             *
 *               = 2 r r0 sin(phi - phi0) / D^2 +                             *
 *                 [r^2 + r0^2 - 2 r r0 cos(phi - phi0)] (1 / D^2)'           *
 *               = 2 r r0 sin(phi - phi0) / D^2 -                             *
 *                 2 ([r^2 + r0^2 - 2 r r0 cos(phi - phi0)] / D^3) D'         *
 *                                                                            *
 *      From Pythagoras, we have:                                             *
 *                                                                            *
 *          dx = rx - r cos(phi)                                              *
 *          dy = ry - r sin(phi)                                              *
 *          dz = rz                                                           *
 *          D = sqrt(dx^2 + dy^2 + dz^2)                                      *
 *                                                                            *
 *      The derivative is then:                                               *
 *                                                                            *
 *          D' = sqrt([rx - r cos(phi)]^2 + [ry - r sin(phi)]^2 + rz^2)'      *
 *             = ([rx - r cos(phi)]^2 + [ry - r sin(phi)]^2 + rz^2)' / (2 D)  *
 *             = r([rx - r cos(phi)]sin(phi) - [ry - r sin(phi)]cos(phi)) / D *
 *                                                                            *
 *  Notes:                                                                    *
 *      Angles must be in degrees. Lengths can be in whatever units, but they *
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
 *  2023/03/22: Ryan Maguire                                                  *
 *      Migrated from rss_ringoccs. Cleaned up code.                          *
 ******************************************************************************/

/*  Trig functions and square root found here.                                */
#include <libtmpl/include/tmpl_math.h>

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_cyl_fresnel_optics.h>

/*  Computes the partial derivative of psi with respect to phi with varying D.*/
long double
tmpl_LDouble_Cyl_Fresnel_dPsi_dPhi_D_Deg(long double k, long double r,
                                         long double r0, long double phi,
                                         long double phi0, long double B,
                                         long double rx, long double ry,
                                         long double rz)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    long double xi, eta, psi0, dxi, deta, rcpr_D, rcpr_D_squared;
    long double cos_phi, sin_phi, cos_phi0, sin_phi0, cos_phi_phi0;
    long double sin_phi_phi0, dpsi, dD, D, dx, dy, xi_factor, eta_factor;

    /*  Precompute cosines and sines to save on computations.                 */
    const long double cos_B = tmpl_LDouble_Cosd(B);

    /*  Compute sine and cosine simultaneously using SinCos.                  */
    tmpl_LDouble_SinCosd(phi, &sin_phi, &cos_phi);
    tmpl_LDouble_SinCosd(phi0, &sin_phi0, &cos_phi0);

    /*  Since we've computed cos and sin of phi and phi0, cos and sin of      *
     *  phi-phi0 can be computed without the need to call cos and sin again.  */
    cos_phi_phi0 = cos_phi*cos_phi0 + sin_phi*sin_phi0;
    sin_phi_phi0 = sin_phi*cos_phi0 - cos_phi*sin_phi0;

    /*  Compute the distance from the observer to the plane using Pythagoras. */
    dx = rx - r*cos_phi;
    dy = ry - r*sin_phi;
    D = tmpl_LDouble_Sqrt(dx*dx + dy*dy + rz*rz);

    /*  Compute 1/D and it's square to save the number of divisions we need   *
     *  to compute. Multiplication is usually ~10 times faster.               */
    rcpr_D = 1.0L / D;
    rcpr_D_squared = rcpr_D * rcpr_D;

    /*  Compute the derivative of D with respect to phi.                      */
    dD = r*(dx*sin_phi - dy*cos_phi)*rcpr_D;

    /*  These terms occur frequently.                                         */
    xi_factor = cos_B * rcpr_D;
    eta_factor = 2.0L * r * r0 * rcpr_D_squared;

    /*  Compute xi variable (MTR86 Equation 4b) and eta (Equation 4c).        */
    xi = xi_factor * (r * cos_phi - r0 * cos_phi0);
    eta = (r0*r0 + r*r)*rcpr_D_squared - eta_factor*cos_phi_phi0;
    psi0 = tmpl_LDouble_Sqrt(1.0L + eta - 2.0L*xi);

    /*  Compute derivatives (Use calculus before hand).                       */
    dxi = -xi_factor * (r * sin_phi) - xi*rcpr_D*dD;
    deta = eta_factor * sin_phi_phi0 - 2.0L * eta * rcpr_D * dD;
    dpsi = k * D * ((0.5L/psi0) * (deta - 2.0L*dxi) + dxi);
    dpsi += k * dD * (psi0 + xi - 1.0L);

    return dpsi;
}
/*  End of tmpl_LDouble_Cyl_Fresnel_dPsi_dPhi_D_Deg.                          */
