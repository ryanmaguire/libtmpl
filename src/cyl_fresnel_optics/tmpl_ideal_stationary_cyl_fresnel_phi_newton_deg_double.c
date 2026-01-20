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
 *          tmpl_ideal_stationary_cyl_fresnel_phi_newton_deg_double           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the stationary value phi of the cylindrical Fresnel kernel.  *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Ideal_Stationary_Cyl_Fresnel_Phi_Newton_Deg               *
 *  Purpose:                                                                  *
 *      Computes the value phi such that dpsi / dphi = 0. This is the         *
 *      stationary value of the cylindrical Fresnel kernel, and is used in    *
 *      stationary phase approximation for Fresnel inversion / reconstruction.*
 *      The computation is done using Newton's method.                        *
 *  Arguments:                                                                *
 *      k (double):                                                           *
 *          The wavenumber, in the reciprocal of the units of rho.            *
 *      rho (double):                                                         *
 *          The "dummy" radius, usually a variable that is integrated over.   *
 *      rho0 (double):                                                        *
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
 *      eps (double):                                                         *
 *          The "epsilon" factor, the allowed error in the computation of the *
 *          stationary phase. Once |dpsi / dphi| < eps, the computation will  *
 *          stop and the resulting phi will be returned.                      *
 *      max_iters (unsigned int):                                             *
 *          The maximum number of iterations allowed in Newton's method       *
 *          before the algorithm is halted and the current value of phi is    *
 *          returned. For most practical applications, toler = 4 or toler = 5 *
 *          is sufficient.                                                    *
 *  Outputs:                                                                  *
 *      phi_s (double):                                                       *
 *          The stationary value of phi.                                      *
 *  Called Functions:                                                         *
 *      src/math/                                                             *
 *          tmpl_Double_Cosd:                                                 *
 *              Computes cosine, in degrees.                                  *
 *          tmpl_Double_SinCosd:                                              *
 *              Computes sine and cosine, in degrees.                         *
 *          tmpl_Double_Sqrt:                                                 *
 *              Computes the square root of a positive number.                *
 *          tmpl_Double_Abs:                                                  *
 *              Computes the absolute value of a real number.                 *
 *  Method:                                                                   *
 *      Use Newton's method. Given the initial guess phi, we compute:         *
 *          phi_s = phi - psi' / psi''                                        *
 *          phi = phi_s                                                       *
 *      and repeat until either the value |psi'| is small, or we have done    *
 *      "max_iters" number of iterations.                                     *
 *  Notes:                                                                    *
 *      1.) Angles must be in degrees.                                        *
 *      2.) Lengths can be in whatever units, but they must be the same units.*
 *      3.) It is assumed B, D, rho, rho0, and phi0 are independent of phi.   *
 *      4.) It is also assumed that the vector from the ring intercept point  *
 *          to the observer is perpendicular to the y axis. This is why this  *
 *          function is called "ideal". For real geometry this may be off.    *
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
 *  2025/05/23: Ryan Maguire                                                  *
 *      Changed name to "ideal" since this uses the ideal scenario where      *
 *      u . y = 0, where u is the vector from the ring intercept point to the *
 *      observer. Cleaned up some comments as well.                           *
 ******************************************************************************/

/*  Trig functions and square root found here.                                */
#include <libtmpl/include/tmpl_math.h>

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_cyl_fresnel_optics.h>

/*  Computes the stationary value of phi for the cylindrical Fresnel kernel.  */
double
tmpl_Double_Ideal_Stationary_Cyl_Fresnel_Phi_Newton_Deg(double k,
                                                        double rho,
                                                        double rho0,
                                                        double phi,
                                                        double phi0,
                                                        double B,
                                                        double D,
                                                        double eps,
                                                        unsigned int max_iters)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    double xi, eta, psi0, dxi, deta, deta2, dxi2, rcpr_psi0, rcpr_psi0_cubed;
    double cos_phi, sin_phi, cos_phi0, sin_phi0, cos_phi_phi0, sin_phi_phi0;
    double dpsi, d2psi, err, num_factor;

    /*  Index for keeping track of the number of iterations.                  */
    unsigned int n = 0U;

    /*  The functions tmpl_Double_Ideal_Cyl_Fresnel_d2Psi_dPhi2 and           *
     *  tmpl_Double_Ideal_Cyl_Fresnel_dPsi_dPhi do a lot of the same          *
     *  calculations involving cos, sin, and sqrt, and it is redundant to     *
     *  do this twice for the same variables. Instead of calling these two    *
     *  functions, precompute the needed variables and calculate a simplified *
     *  version of dpsi / d2psi.                                              */

    /*  Compute 1 / D and its square to save the number of divisions we need  *
     *  to compute. Multiplication is usually ~10 times faster.               */
    const double rcpr_D = 1.0 / D;
    const double rcpr_D_squared = rcpr_D * rcpr_D;

    /*  cos(B) appears in the xi factor. B is given in degrees, use Cosd.     */
    const double cos_B = tmpl_Double_Cosd(B);

    /*  This term appears in dxi, dxi2, and xi.                               */
    const double xi_factor = cos_B * rcpr_D;

    /*  And this term appears in eta, deta, and deta2.                        */
    const double eta_factor = 2.0 * rho * rho0 * rcpr_D_squared;

    /*  Compute sine and cosine simultaneously using SinCosd.                 */
    tmpl_Double_SinCosd(phi0, &sin_phi0, &cos_phi0);

    /*  Normalize the requested error by the wavenumber and distance.         */
    eps /= k*D;

    /*  Iteratively perform Newton's method until the error is small.         */
    do {

        /*  If we've performed enough iterations, stop Newton's method.       */
        if (n > max_iters)
            break;

        /*  Compute sine and cosine simultaneously using SinCosd.             */
        tmpl_Double_SinCosd(phi, &sin_phi, &cos_phi);
        tmpl_Double_SinCosd(phi0, &sin_phi0, &cos_phi0);

        /*  Since we've computed cos and sin of phi and phi0, cos and sin of  *
         *  phi-phi0 can be computed without the need to call cos and sin     *
         *  again. This is the angle difference formula:                      *
         *                                                                    *
         *      cos(x - y) = cos(x)cos(y) + sin(x)sin(y)                      *
         *      sin(x - y) = sin(x)cos(y) - cos(x)sin(y)                      *
         *                                                                    *
         *  This saves us a call to SinCosd.                                  */
        cos_phi_phi0 = cos_phi * cos_phi0 + sin_phi * sin_phi0;
        sin_phi_phi0 = sin_phi * cos_phi0 - cos_phi * sin_phi0;

        /*  The Fresnel kernel is given in terms of auxiliary functions xi    *
         *  and eta. These are defined by:                                    *
         *                                                                    *
         *      xi = [rho cos(phi) - rho0 cos(phi0)] cos(B) / D               *
         *      eta = [rho^2 + rho0^2 - 2 rho rho0 cos(phi - phi0)] / D^2     *
         *      psi = kD [sqrt(1 + eta - 2 xi) + xi - 1]                      *
         *                                                                    *
         *  Compute xi and eta. Both appear in the formula for the first and  *
         *  second derivative of the Fresnel kernel with respect to phi.      */
        xi = xi_factor * (rho * cos_phi - rho0 * cos_phi0);
        eta = (rho0*rho0 + rho*rho)*rcpr_D_squared - eta_factor*cos_phi_phi0;

        /*  Applying the quotient rule to psi, the final result will contain  *
         *  the factor sqrt(1 + eta - 2xi), and the cube of this expression.  */
        psi0 = tmpl_Double_Sqrt(1.0 + eta - 2.0 * xi);
        rcpr_psi0 = 1.0 / psi0;
        rcpr_psi0_cubed = rcpr_psi0 * rcpr_psi0 * rcpr_psi0;

        /*  From the definition of xi, we have:                               *
         *                                                                    *
         *      xi = [rho cos(phi) - rho0 cos(phi0)] cos(B) / D               *
         *                                                                    *
         *  The derivative with respect to phi is then:                       *
         *                                                                    *
         *      xi' = -rho sin(phi) cos(B) / D                                *
         *                                                                    *
         *  The second derivative is given by:                                *
         *                                                                    *
         *      xi'' = -rho cos(phi) cos(B) / D                               *
         *                                                                    *
         *  Both xi' and xi'' appear in the expression for psi''. Compute.    */
        dxi = -xi_factor * rho * sin_phi;
        dxi2 = -xi_factor * rho * cos_phi;

        /*  A similar computation must be done for eta. The definition is:    *
         *                                                                    *
         *      eta = [rho^2 + rho0^2 - 2 rho rho0 cos(phi - phi0)] / D^2     *
         *                                                                    *
         *  The derivative with respect to phi is then:                       *
         *                                                                    *
         *      eta' = 2 rho rho0 sin(phi - phi0) / D^2                       *
         *                                                                    *
         *  And the second derivative is:                                     *
         *                                                                    *
         *      eta'' = 2 rho rho0 cos(phi - phi0) / D^2                      *
         *                                                                    *
         *  Compute both of the terms.                                        */
        deta = eta_factor * sin_phi_phi0;
        deta2 = eta_factor * cos_phi_phi0;

        /*  Compute the first partial derivative with respect to phi.         */
        num_factor = deta - 2.0 * dxi;
        dpsi = 0.5 * rcpr_psi0 * num_factor + dxi;

        /*  The second partial derivative can be expressed in terms of the    *
         *  variables we have thus far computed. We have:                     *
         *                                                                    *
         *      psi'' = kD [                                                  *
         *          (eta'' - 2 xi'') / [2 sqrt(1 + eta - 2 xi)] -             *
         *          (eta' - 2 xi')^2 / [4 (1 + eta - 2 xi)^3/2] + xi''        *
         *      ]                                                             *
         *                                                                    *
         *  Compute this final expression and use it for Newton's method.     */
        d2psi = -0.25 * rcpr_psi0_cubed * num_factor * num_factor;
        d2psi += 0.5 * rcpr_psi0 * (deta2 - 2.0 * dxi2) + dxi2;

        /*  Perform the Newton iteration, and increment n. Note, the output   *
         *  of dpsi / d2psi will be in radians, but phi is in degrees. Scale  *
         *  dpsi / d2psi by 180 / pi to avoid incorrectly mixing units.       */
        phi = phi - tmpl_double_rad_to_deg * dpsi / d2psi;
        ++n;

        /*  Update the error. We want the partial derivative to be small.     */
        err = tmpl_Double_Abs(dpsi);

    } while (err > eps);

    return phi;
}
/*  End of tmpl_Double_Ideal_Stationary_Cyl_Fresnel_Phi_Newton_Deg.           */
