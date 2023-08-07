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
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 8, 2021                                                  *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/03/24: Ryan Maguire                                                  *
 *      Migrated from rss_ringoccs.                                           *
 ******************************************************************************/

/*
 * TODO: Add doc string and comments.
 */

/*  Trig functions and square root found here.                                */
#include <libtmpl/include/tmpl_math.h>

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_cyl_fresnel_optics.h>

/*  Computes the partial derivative of the elliptical Fresnel kernel.         */
double
tmpl_Double_Elliptical_Fresnel_dPsi_dPhi(double k, double r, double r0,
                                         double phi, double phi0, double B,
                                         double D, double ecc, double peri)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    double xi, eta, psi0, dxi_phi, deta_phi, dxi_rho, deta_rho;
    double cos_phi, sin_phi, cos_phi0, sin_phi0;
    double cos_phi_phi0, sin_phi_phi0;
    double dpsi_rho, dpsi_phi, drho_phi;
    double cos_phi_peri, sin_phi_peri, factor, ecc_cos_factor;

    /*  Compute 1/D and it's square to save the number of divisions we need   *
     *  to compute. Multiplication is usually ~10 times faster.               */
    const double rcpr_D = 1.0 / D;
    const double rcpr_D_squared = rcpr_D * rcpr_D;

    /*  Precompute cosines and sines to save on computations.                 */
    const double cos_B = tmpl_Double_Cos(B);

    /*  This term appears in dxi and dxi2 and xi.                             */
    const double xi_factor = cos_B * rcpr_D;

    /*  And this term appears in eta, deta, and deta2.                        */
    const double eta_factor = 2.0 * r * r0 * rcpr_D_squared;

    tmpl_Double_SinCos(phi, &sin_phi, &cos_phi);
    tmpl_Double_SinCos(phi0, &sin_phi0, &cos_phi0);
    tmpl_Double_SinCos(phi - peri, &sin_phi_peri, &cos_phi_peri);

    /*  Since we've computed cos and sin of phi and phi0, cos and sin of      *
     *  phi-phi0 can be computed without the need to call cos and sin again.  */
    cos_phi_phi0 = sin_phi*sin_phi0 + cos_phi*cos_phi0;
    sin_phi_phi0 = sin_phi*cos_phi0 - cos_phi*sin_phi0;

    /*  These terms appear do to the eccentricity.                            */
    ecc_cos_factor = 1.0 + ecc * cos_phi_peri;
    factor = r * ecc_cos_factor;

    /*  Compute xi variable (MTR86 Equation 4b) and eta (Equation 4c).        */
    xi = xi_factor * (r * cos_phi - r0 * cos_phi0);
    eta = (r0*r0 + r*r)*rcpr_D_squared - eta_factor*cos_phi_phi0;
    psi0 = tmpl_Double_Sqrt(1.0 + eta - 2.0*xi);

    /*  Compute derivatives.                                                  */
    dxi_phi = -xi_factor * (r * sin_phi);
    dxi_rho = xi_factor * cos_phi;

    deta_phi = eta_factor * sin_phi_phi0;
    deta_rho = 2.0 * (r - r0 * cos_phi_phi0) * rcpr_D_squared;

    drho_phi = factor*ecc*sin_phi_peri / (ecc_cos_factor*ecc_cos_factor);

    dpsi_rho = (deta_rho - 2.0 * dxi_rho) * (0.5 / psi0) + dxi_rho;
    dpsi_phi = (deta_phi - 2.0 * dxi_phi) * (0.5 / psi0) + dxi_phi;

    /*  Compute the partial derivative.                                       */
    return k*D*(dpsi_phi + dpsi_rho*drho_phi);
}
/*  End of tmpl_Double_Elliptical_Fresnel_dPsi_dPhi.                          */
