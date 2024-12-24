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
 *               tmpl_stationary_cyl_fresnel_psi_newton_double                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the stationary value phi of the cylindrical Fresnel kernel.  *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Stationary_Cyl_Fresnel_Psi_Newton                         *
 *  Purpose:                                                                  *
 *      Computes the value phi such that dpsi / dphi = 0. This is the         *
 *      stationary value of the cylindrical Fresnel kernel, and is used in    *
 *      stationary phase approximation for Fresnel inversion / reconstruction.*
 *      The computation is done using Newton's method.                        *
 *  Arguments:                                                                *
 *      k (double):                                                           *
 *          The wavenumber, in the reciprocal of the units of r.              *
 *      r (double):                                                           *
 *          The "dummy" radius, usually a variable that is integrated over.   *
 *      r0 (double):                                                          *
 *          The radius of the point of interest.                              *
 *      phi (double):                                                         *
 *          The guess for the stationary value, used as the starting point of *
 *          Newton's method. phi = phi0 is often a good guess.                *
 *      phi0 (double):                                                        *
 *          The azimuthal angle of the point of interest. Same units as phi.  *
 *      B (double):                                                           *
 *          The opening angle of the plane. For planetary ring systems, this  *
 *          is the ring opening angle of the rings with respect to Earth.     *
 *      D (double):                                                           *
 *          The distance from the source of light to the plane.               *
 *      eps (double):                                                         *
 *          The "epsilon" factor, the allowed error in the computation of the *
 *          stationary phase. Once |dpsi / dphi| < eps, the computation will  *
 *          stop and the resulting phi will be returned.                      *
 *      toler (unsigned int):                                                 *
 *          The tolerance in the computation, the maximum number of           *
 *          iterations allowed in Newton's method before the algorithm is     *
 *          halted and the current value of phi is returned. For most         *
 *          practical application, toler = 4 or toler = 5 is sufficient.      *
 *  Outputs:                                                                  *
 *      phi_s (double):                                                       *
 *          The stationary value of phi.                                      *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
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
 *      "toler" number of iterations.                                         *
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
 *  2023/03/22: Ryan Maguire                                                  *
 *      Migrated from rss_ringoccs. Cleaned up code.                          *
 ******************************************************************************/

/*  Trig functions and square root found here.                                */
#include <libtmpl/include/tmpl_math.h>

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_cyl_fresnel_optics.h>

/*  Computes the stationary value of phi for the cylindrical Fresnel kernel.  */
double
tmpl_Double_Stationary_Cyl_Fresnel_Psi_Newton_Deg(double k,
                                                  double r,
                                                  double r0,
                                                  double phi,
                                                  double phi0,
                                                  double B,
                                                  double D,
                                                  double eps,
                                                  unsigned int toler)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    double xi, eta, psi0, dxi, deta, deta2, dxi2, rcpr_psi0, rcpr_psi0_cubed;
    double cos_phi, sin_phi, cos_phi0, sin_phi0, cos_phi_phi0, sin_phi_phi0;
    double dpsi, d2psi, err, num_factor;

    /*  Index for keeping track of the number of iterations.                  */
    unsigned int n = 0U;

    /*  The functions tmpl_Double_Cyl_Fresnel_d2Psi_dPhi2 and                 *
     *  tmpl_Double_Cyl_Fresnel_dPsi_dPhi make a lot of the same computations.*
     *  Calculations involving cos, sin, and sqrt, and it is redundant to     *
     *  do this twice for the same variables. Instead of calling these two    *
     *  functions, precompute the needed variables and calculate a simplified *
     *  version of dpsi / d2psi.                                              */

    /*  Compute 1/D and it's square to save the number of divisions we need   *
     *  to compute. Multiplication is usually ~10 times faster.               */
    const double rcpr_D = 1.0 / D;
    const double rcpr_D_squared = rcpr_D * rcpr_D;

    /*  Precompute cosines and sines to save on computations.                 */
    const double cos_B = tmpl_Double_Cosd(B);

    /*  This term appears in dxi and dxi2 and xi.                             */
    const double xi_factor = cos_B * rcpr_D;

    /*  And this term appears in eta, deta, and deta2.                        */
    const double eta_factor = 2.0 * r * r0 * rcpr_D_squared;

    /*  Compute sine and cosine simultaneously using SinCos.                  */
    tmpl_Double_SinCosd(phi0, &sin_phi0, &cos_phi0);

    /*  Normalize the requested error by the wavenumber and distance.         */
    eps /= k*D;

    /*  Iteratively perform Newton's method until the error is small.         */
    do {

        /*  If we've performed enough iterations, stop Newton's method.       */
        if (n > toler)
            break;

        /*  Compute sine and cosine simultaneously using SinCos.              */
        tmpl_Double_SinCosd(phi, &sin_phi, &cos_phi);

        /*  Since we've computed cos and sin of phi and phi0, cos and sin of  *
         *  phi-phi0 can be computed without the need to call cos and sin.    */
        cos_phi_phi0 = cos_phi*cos_phi0 + sin_phi*sin_phi0;
        sin_phi_phi0 = sin_phi*cos_phi0 - cos_phi*sin_phi0;

        /*  Compute xi variable (MTR86 Equation 4b) and eta (Equation 4c).    */
        xi = xi_factor * (r * cos_phi - r0 * cos_phi0);
        eta = (r0*r0 + r*r)*rcpr_D_squared - eta_factor*cos_phi_phi0;
        psi0 = tmpl_Double_Sqrt(1.0 + eta - 2.0*xi);
        rcpr_psi0 = 1.0 / psi0;
        rcpr_psi0_cubed = rcpr_psi0*rcpr_psi0*rcpr_psi0;

        /*  Compute derivatives.                                              */
        dxi = -xi_factor * (r * sin_phi);
        dxi2 = -xi_factor * (r * cos_phi);
        deta = eta_factor * sin_phi_phi0;
        deta2 = eta_factor * cos_phi_phi0;

        num_factor = deta - 2.0*dxi;
        dpsi = (0.5 * rcpr_psi0) * num_factor + dxi;
        d2psi = -0.25 * rcpr_psi0_cubed * num_factor * num_factor;
        d2psi += (0.5 * rcpr_psi0) * (deta2 - 2.0*dxi2) + dxi2;

        /*  Perform the Newton iteration, and increment n.                    */
        phi = phi - tmpl_Double_Rad_To_Deg * dpsi / d2psi;
        ++n;

        /*  Update the error. We want the partial derivative to be small.     */
        err = tmpl_Double_Abs(dpsi);

    } while (err > eps);

    return phi;
}
/*  End of tmpl_Double_Stationary_Cyl_Fresnel_Psi_Newton.                     */
