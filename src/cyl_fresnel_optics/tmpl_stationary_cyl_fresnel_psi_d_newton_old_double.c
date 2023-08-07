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

static double dpsi(double kD, double r, double r0, double phi,
                   double phi0, double B, double D)
{
    double xi, eta, psi0, dxi, deta;
    const double rcpr_D = 1.0 / D;
    const double cosB_over_D = tmpl_Double_Cos(B) * rcpr_D;
    const double rcpr_D_squared = rcpr_D * rcpr_D;
    double sin_phi, cos_phi, sin_phi0, cos_phi0;
    double sin_phi_phi0, cos_phi_phi0;

    tmpl_Double_SinCos(phi, &sin_phi, &cos_phi);
    tmpl_Double_SinCos(phi0, &sin_phi0, &cos_phi0);
    cos_phi_phi0 = cos_phi*cos_phi0 + sin_phi*sin_phi0;
    sin_phi_phi0 = sin_phi*cos_phi0 - cos_phi*sin_phi0;

    /*  Compute xi variable (MTR86 Equation 4b) and eta (Equation 4c).        */
    xi = cosB_over_D * (r * cos_phi - r0 * cos_phi0);
    eta = (r0*r0 + r*r - 2.0*r*r0*cos_phi_phi0) * rcpr_D_squared;
    psi0 = tmpl_Double_Sqrt(1.0 + eta - 2.0*xi);

    /*  Compute derivatives (Use calculus before hand).                       */
    dxi = -cosB_over_D * (r * sin_phi);
    deta = 2.0 * r * r0 * sin_phi_phi0 * rcpr_D_squared;

    return kD * ((0.5/psi0)*(deta - 2.0*dxi) + dxi);
}

static double d2psi(double kD, double r, double r0, double phi,
                    double phi0, double B, double D)
{
    double xi, eta, psi0, dxi, deta, dxi2, deta2, psi_d2, num_factor;
    const double rcpr_D = 1.0 / D;
    const double cosB_over_D = tmpl_Double_Cos(B) * rcpr_D;
    const double rcpr_D_squared = rcpr_D * rcpr_D;
    double sin_phi, cos_phi, sin_phi0, cos_phi0;
    double sin_phi_phi0, cos_phi_phi0;
    double rcpr_psi0, rcpr_psi0_cubed;

    tmpl_Double_SinCos(phi, &sin_phi, &cos_phi);
    tmpl_Double_SinCos(phi0, &sin_phi0, &cos_phi0);
    cos_phi_phi0 = cos_phi*cos_phi0 + sin_phi*sin_phi0;
    sin_phi_phi0 = sin_phi*cos_phi0 - cos_phi*sin_phi0;

    /*  Compute xi variable (MTR86 Equation 4b) and eta (Equation 4c).        */
    xi = cosB_over_D * (r * cos_phi - r0 * cos_phi0);
    eta = (r0*r0 + r*r - 2.0*r*r0*cos_phi_phi0) * rcpr_D_squared;
    psi0 = tmpl_Double_Sqrt(1.0 + eta - 2.0*xi);
    rcpr_psi0 = 1.0 / psi0;
    rcpr_psi0_cubed = rcpr_psi0 * rcpr_psi0 * rcpr_psi0;

    /*  Compute derivatives.                                                  */
    dxi = -cosB_over_D * (r * sin_phi);
    dxi2 = -cosB_over_D * (r * cos_phi);
    deta = 2.0 * r * r0 * sin_phi_phi0 * rcpr_D_squared;
    deta2 = 2.0 * r * r0 * cos_phi_phi0 * rcpr_D_squared;

    /*  Compute the second partial derivative.                                */
    num_factor = deta - 2.0*dxi;
    psi_d2 = (-0.25 * rcpr_psi0_cubed) * num_factor * num_factor;
    psi_d2 += (0.5 * rcpr_psi0) * (deta2 - 2.0*dxi2) + dxi2;
    return kD*psi_d2;
}

double
tmpl_Double_Stationary_Cyl_Fresnel_Psi_D_Newton_Old(double kD, double r,
                                                    double r0, double phi,
                                                    double phi0, double B,
                                                    double rx, double ry,
                                                    double rz, double eps,
                                                    unsigned int toler)
{
    unsigned int n = 0U;
    double D = tmpl_Double_Cyl_Fresnel_Observer_Distance(r0, phi, rx, ry, rz);
    double psi_prime = dpsi(kD, r, r0, phi, phi0, B, D);
    double err = tmpl_Double_Abs(psi_prime);
    double psi_2prime;

    while (err > eps)
    {
        psi_2prime = d2psi(kD, r, r0, phi, phi0, B, D);

        phi = phi - psi_prime / psi_2prime;
        ++n;

        if (n > toler)
            break;

        D = tmpl_Double_Cyl_Fresnel_Observer_Distance(r0, phi, rx, ry, rz);
        psi_prime = dpsi(kD, r, r0, phi, phi0, B, D);
        err = tmpl_Double_Abs(psi_prime);
    }

    return phi;
}
