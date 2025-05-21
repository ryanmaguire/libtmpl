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
 *                 tmpl_ideal_cyl_fresnel_d2psi_dphi2_ldouble                 *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the second partial derivative of the cylindrical Fresnel     *
 *      kernel with respect to phi, assuming ideal geometry.                  *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Ideal_Cyl_Fresnel_d2Psi_dPhi2                            *
 *  Purpose:                                                                  *
 *      Computes the second partial derivative of the cylindrical Fresnel     *
 *      kernel with respect to phi at long double precision with all angles   *
 *      in radians. The lengths may be in whatever units, but they must be in *
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
 *      d2psi_dphi2 (long double):                                            *
 *          The second partial derivative of the cylindrical Fresnel kernel   *
 *          with respect to phi.                                              *
 *  Called Functions:                                                         *
 *      src/math/                                                             *
 *          tmpl_LDouble_Cos:                                                 *
 *              Computes cosine, in radians.                                  *
 *          tmpl_LDouble_SinCos:                                              *
 *              Computes sine and cosine, in radians.                         *
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
 *          xi'' = -rho cos(phi) cos(B) / D                                   *
 *                                                                            *
 *      And the second derivative of eta is:                                  *
 *                                                                            *
 *          eta'' = 2 rho rho0 cos(phi - phi0) / D^2                          *
 *                                                                            *
 *      Piecing all of this together gives us the second partial derivative.  *
 *  Notes:                                                                    *
 *      1.) Angles must be in radians.                                        *
 *      2.) Lengths can be in whatever units, but they must be the same units.*
 *      3.) It is assumed B, D, rho, rho0, and phi0 are independent of phi.   *
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
 *  2023/03/20: Ryan Maguire                                                  *
 *      Migrated from rss_ringoccs. Cleaned up code.                          *
 *  2025/05/20: Ryan Maguire                                                  *
 *      Changed function name to "Ideal" since this assumes the ideal         *
 *      geometry given in the MTR86 paper. The non-ideal function now uses    *
 *      the geometry of an arbitrary coordinate system with z axis            *
 *      perpendicular to the ring plane.                                      *
 ******************************************************************************/

/*  Trig functions and square root found here.                                */
#include <libtmpl/include/tmpl_math.h>

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_cyl_fresnel_optics.h>

/*  Computes the second partial derivative of psi with respect to phi.        */
long double
tmpl_LDouble_Ideal_Cyl_Fresnel_d2Psi_dPhi2(long double k,
                                           long double rho, long double rho0,
                                           long double phi, long double phi0,
                                           long double B, long double D)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    long double xi, eta, psi0, dxi, dxi2, deta, deta2, psi_d2, sin_phi, cos_phi;
    long double cos_phi0, sin_phi0, cos_phi_phi0, sin_phi_phi0;
    long double num_factor, rcpr_psi0, rcpr_psi0_cubed;

    /*  Compute 1/D and its square to save the number of divisions we need    *
     *  to compute. Multiplication is usually ~10 times faster.               */
    const long double rcpr_D = 1.0L / D;
    const long double rcpr_D_squared = rcpr_D * rcpr_D;

    /*  cos(B) appears in the xi factor. B is given in radians, use Cos.      */
    const long double cos_B = tmpl_LDouble_Cos(B);

    /*  This term appears in dxi, dxi2, and xi.                               */
    const long double xi_factor = cos_B * rcpr_D;

    /*  And this term appears in eta, deta, and deta2.                        */
    const long double eta_factor = 2.0L * rho * rho0 * rcpr_D_squared;

    /*  Compute sine and cosine simultaneously using SinCos.                  */
    tmpl_LDouble_SinCos(phi, &sin_phi, &cos_phi);
    tmpl_LDouble_SinCos(phi0, &sin_phi0, &cos_phi0);

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

    /*  Applying the quotient rule to psi, the final result will contain the  *
     *  factor sqrt(1 + eta - 2xi), and also the cube of this expression.     */
    psi0 = tmpl_LDouble_Sqrt(1.0L + eta - 2.0L * xi);
    rcpr_psi0 = 1.0L / psi0;
    rcpr_psi0_cubed = rcpr_psi0 * rcpr_psi0 * rcpr_psi0;

    /*  From the definition of xi, we have:                                   *
     *                                                                        *
     *      xi = [rho cos(phi) - rho0 cos(phi0)] cos(B) / D                   *
     *                                                                        *
     *  The derivative with respect to phi is then:                           *
     *                                                                        *
     *      xi' = -rho sin(phi) cos(B) / D                                    *
     *                                                                        *
     *  The second derivative is given by:                                    *
     *                                                                        *
     *      xi'' = -rho cos(phi) cos(B) / D                                   *
     *                                                                        *
     *  Both xi' and xi'' appear in the expression for psi''. Compute.        */
    dxi = -xi_factor * rho * sin_phi;
    dxi2 = -xi_factor * rho * cos_phi;

    /*  A similar computation must be done for eta. The definition is:        *
     *                                                                        *
     *      eta = [rho^2 + rho0^2 - 2 rho rho0 cos(phi - phi0)] / D^2         *
     *                                                                        *
     *  The derivative with respect to phi is then:                           *
     *                                                                        *
     *      eta' = 2 rho rho0 sin(phi - phi0) / D^2                           *
     *                                                                        *
     *  And the second derivative is:                                         *
     *                                                                        *
     *      eta'' = 2 rho rho0 cos(phi - phi0) / D^2                          *
     *                                                                        *
     *  Compute both of the terms.                                            */
    deta = eta_factor * sin_phi_phi0;
    deta2 = eta_factor * cos_phi_phi0;

    /*  The second partial derivative can be expressed in terms of the        *
     *  variables we have thus far computed. We have:                         *
     *                                                                        *
     *      psi'' = kD [                                                      *
     *          (eta'' - 2 xi'') / [2 sqrt(1 + eta - 2 xi)] -                 *
     *          (eta' - 2 xi')^2 / [4 (1 + eta - 2 xi)^3/2] + xi''            *
     *      ]                                                                 *
     *                                                                        *
     *  Compute this final expression and return.                             */
    num_factor = deta - 2.0L * dxi;
    psi_d2 = -0.25L * rcpr_psi0_cubed * num_factor * num_factor;
    psi_d2 += 0.5L * rcpr_psi0 * (deta2 - 2.0L * dxi2) + dxi2;
    psi_d2 *= k * D;
    return psi_d2;
}
/*  End of tmpl_LDouble_Ideal_Cyl_Fresnel_d2Psi_dPhi2.                        */
