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
 *                tmpl_ideal_cyl_fresnel_dpsi_dphi_deg_ldouble                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the first partial derivative of the cylindrical Fresnel      *
 *      kernel with respect to phi, assuming ideal geometry.                  *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Ideal_Cyl_Fresnel_dPsi_dPhi_Deg                          *
 *  Purpose:                                                                  *
 *      Computes the first partial derivative of the cylindrical Fresnel      *
 *      kernel with respect to phi at single precision with all angles in     *
 *      degrees. The lengths may be in whatever units, but they must be in    *
 *      the same units. It is assumed that the geometry satisfies the         *
 *      description found in the Marouf, Tyler, and Rosen paper. In           *
 *      particular the vector from the ring intercept point to the observer   *
 *      must be perpendicular to the y axis.                                  *
 *  Arguments:                                                                *
 *      k (long double):                                                      *
 *          The wavenumber, in the reciprocal of the units of rho.            *
 *      rho (long double):                                                    *
 *          The "dummy" radius, usually a variable that is integrated over.   *
 *      rho0 (long double):                                                   *
 *          The radius of the point of interest.                              *
 *      phi (long double):                                                    *
 *          The "dummy" azimuthal angle, often integrated over.               *
 *      phi0 (long double):                                                   *
 *          The azimuthal angle of the point of interest.                     *
 *      B (long double):                                                      *
 *          The opening angle of the plane. For planetary ring systems this   *
 *          is the ring opening angle of the rings with respect to Earth.     *
 *      D (long double):                                                      *
 *          The distance from the observer to the point in the plane.         *
 *  Outputs:                                                                  *
 *      dpsi_dphi (long double):                                              *
 *          The first partial derivative of the cylindrical Fresnel kernel    *
 *          with respect to phi.                                              *
 *  Called Functions:                                                         *
 *      src/math/                                                             *
 *          tmpl_LDouble_Cosd:                                                *
 *              Computes cosine, in degrees.                                  *
 *          tmpl_LDouble_SinCosd:                                             *
 *              Computes sine and cosine, in degrees.                         *
 *          tmpl_LDouble_Sqrt:                                                *
 *              Computes the square root of a positive number.                *
 *  Method:                                                                   *
 *      Use the product and chain rules a few times to compute. We have:      *
 *                                                                            *
 *          xi = [rho cos(phi) - rho0 cos(phi0)] cos(B) / D                   *
 *          eta = [rho^2 + rho0^2 - 2 rho rho0 cos(phi - phi0)] / D^2         *
 *          psi = kD [sqrt(1 + eta - 2 xi) + xi - 1]                          *
 *                                                                            *
 *      Note the sign of xi is flipped from the MTR86 definition.             *
 *                                                                            *
 *          psi' = (kD [sqrt(1 + eta - 2 xi) + xi - 1])'                      *
 *               = kD ([sqrt(1 + eta - 2 xi)]' + xi')                         *
 *               = kD ([eta' - 2 xi'] / [2 sqrt(1 + eta - 2 xi)] + xi')       *
 *                                                                            *
 *      We need to compute xi' and eta'.                                      *
 *                                                                            *
 *          xi' = ([rho cos(phi) - rho0 cos(phi0)] cos(B) / D)'               *
 *              = -rho sin(phi) cos(B) / D                                    *
 *                                                                            *
 *      For the eta factor we get:                                            *
 *                                                                            *
 *          eta' = ([rho^2 + rho0^2 - 2 rho rho0 cos(phi - phi0)] / D^2)'     *
 *               = 2 rho rho0 sin(phi - phi0) / D^2                           *
 *                                                                            *
 *      The first partial derivative is:                                      *
 *                                                                            *
 *          kD ([eta' - 2 xi'] / [2 sqrt(1 + eta - 2 xi)] + xi')              *
 *                                                                            *
 *  Notes:                                                                    *
 *      1.) Angles must be in degrees.                                        *
 *      2.) Lengths can be in whatever units, but they must be the same units.*
 *      3.) It is assumed B, D, rho, rho0, and phi0 are independent of phi.   *
 *      4.) It is also assumed that the vector from the ring intercept point  *
 *          to the observer is perpendicular to the y axis. This is why this  *
 *          function is called "ideal". For real geometry this may be         *
 *          slightly off. For accurate computations in these scenarios, use   *
 *          the non-ideal version (tmpl_LDouble_Cyl_Fresnel_dPsi_dPhi).       *
 *  References:                                                               *
 *      1.) Marouf, E., Tyler, G., Rosen, P. (June 1986)                      *
 *          Profiling Saturn's Rings by Radio Occultation                     *
 *          Icarus Vol. 68, Pages 120-166.                                    *
 *                                                                            *
 *          This paper describes the theory of diffraction as applied to      *
 *          planetary ring systems. The Fresnel kernel is described here.     *
 *                                                                            *
 *      2.) Goodman, J. (2005)                                                *
 *          Introduction to Fourier Optics                                    *
 *          McGraw-Hill Series in Electrical and Computer Engineering.        *
 *                                                                            *
 *          Covers most of the theory behind diffraction and the application  *
 *          of Fourier analysis to optics. The Fresnel transform is given an  *
 *          in-depth treatise in this book.                                   *
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
 *  2025/05/21: Ryan Maguire                                                  *
 *      Changed function name to "Ideal" since this assumes the ideal         *
 *      geometry given in the MTR86 paper. The non-ideal function now uses    *
 *      the geometry of an arbitrary coordinate system with z axis            *
 *      perpendicular to the ring plane.                                      *
 ******************************************************************************/

/*  Trig functions and square root found here.                                */
#include <libtmpl/include/tmpl_math.h>

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_cyl_fresnel_optics.h>

/*  Computes the first partial derivative of psi with respect to phi.         */
long double
tmpl_LDouble_Ideal_Cyl_Fresnel_dPsi_dPhi_Deg(long double k,
                                             long double rho, long double rho0,
                                             long double phi, long double phi0,
                                             long double B, long double D)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    long double xi, eta, psi0, dxi, deta, sin_phi, cos_phi;
    long double cos_phi0, sin_phi0, cos_phi_phi0, sin_phi_phi0;

    /*  Compute 1/D and its square to save the number of divisions we need    *
     *  to compute. Multiplication is usually ~10 times faster.               */
    const long double rcpr_D = 1.0L / D;
    const long double rcpr_D_squared = rcpr_D * rcpr_D;

    /*  cos(B) appears in the xi factor. B is given in degrees, use Cosd.     */
    const long double cos_B = tmpl_LDouble_Cosd(B);

    /*  This term appears in dxi and xi.                                      */
    const long double xi_factor = cos_B * rcpr_D;

    /*  And this term appears in eta and deta.                                */
    const long double eta_factor = 2.0L * rho * rho0 * rcpr_D_squared;

    /*  Compute sine and cosine simultaneously using SinCos.                  */
    tmpl_LDouble_SinCosd(phi, &sin_phi, &cos_phi);
    tmpl_LDouble_SinCosd(phi0, &sin_phi0, &cos_phi0);

    /*  Since we've computed cos and sin of phi and phi0, cos and sin of      *
     *  phi-phi0 can be computed without the need to call cos and sin again.  *
     *  This is the angle difference formula:                                 *
     *                                                                        *
     *      cos(x - y) = cos(x)cos(y) + sin(x)sin(y)                          *
     *      sin(x - y) = sin(x)cos(y) - cos(x)sin(y)                          *
     *                                                                        *
     *  This saves us a call to SinCos.                                       */
    cos_phi_phi0 = cos_phi * cos_phi0 + sin_phi * sin_phi0;
    sin_phi_phi0 = sin_phi * cos_phi0 - cos_phi * sin_phi0;

    /*  The Fresnel kernel is given in terms of auxiliary functions xi and    *
     *  eta. These are defined by:                                            *
     *                                                                        *
     *      xi = [rho cos(phi) - rho0 cos(phi0)] cos(B) / D                   *
     *      eta = [rho^2 + rho0^2 - 2 rho rho0 cos(phi - phi0)] / D^2         *
     *      psi = kD [sqrt(1 + eta - 2 xi) + xi - 1]                          *
     *                                                                        *
     *  Compute xi and eta. Both appear in the formula for the derivative of  *
     *  the Fresnel kernel, and the second derivative, with respect to phi.   */
    xi = xi_factor * (rho * cos_phi - rho0 * cos_phi0);
    eta = (rho0*rho0 + rho*rho) * rcpr_D_squared - eta_factor * cos_phi_phi0;

    /*  From the definition of xi, we have:                                   *
     *                                                                        *
     *      xi = [rho cos(phi) - rho0 cos(phi0)] cos(B) / D                   *
     *                                                                        *
     *  The derivative with respect to phi is then:                           *
     *                                                                        *
     *      xi' = -rho sin(phi) cos(B) / D                                    *
     *                                                                        *
     *  cos(B) / D is the xi factor, use this to compute.                     */
    dxi = -xi_factor * rho * sin_phi;

    /*  A similar computation must be done for eta. The definition is:        *
     *                                                                        *
     *      eta = [rho^2 + rho0^2 - 2 rho rho0 cos(phi - phi0)] / D^2         *
     *                                                                        *
     *  The derivative with respect to phi is then:                           *
     *                                                                        *
     *      eta' = 2 rho rho0 sin(phi - phi0) / D^2                           *
     *                                                                        *
     *  The eta factor contains most of this expression.                      */
    deta = eta_factor * sin_phi_phi0;

    /*  Applying the quotient rule to psi, the final result will contain the  *
     *  factor sqrt(1 + eta - 2xi). Compute this.                             */
    psi0 = tmpl_LDouble_Sqrt(1.0L + eta - 2.0L * xi);

    /*  We now have all of the pieces for the first partial derivative.       */
    return k * D * ((0.5L / psi0) * (deta - 2.0L * dxi) + dxi);
}
/*  End of tmpl_LDouble_Ideal_Cyl_Fresnel_dPsi_dPhi_Deg.                      */
