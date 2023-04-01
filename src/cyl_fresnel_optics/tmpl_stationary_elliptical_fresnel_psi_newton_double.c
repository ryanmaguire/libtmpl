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

double
tmpl_Double_Stationary_Elliptical_Fresnel_Psi_Newton(double k, double r,
                                                     double r0, double phi,
                                                     double phi0, double B,
                                                     double ecc, double peri,
                                                     double rx, double ry,
                                                     double rz, double eps,
                                                     unsigned int toler)
{
    double d2psi;
    unsigned int n = 0U;
    double D = tmpl_Double_Cyl_Fresnel_Observer_Distance(r0, phi, rx, ry, rz);
    double ecc_cos_factor = 1.0 + ecc * tmpl_Double_Cos(phi - peri);
    double factor = r * ecc_cos_factor;
    double rho = r;
    double dpsi = tmpl_Double_Elliptical_Fresnel_dPsi_dPhi(
        k, rho, r0, phi, phi0, B, D, ecc, peri
    );

    double err = tmpl_Double_Abs(dpsi);

    while(err > eps)
    {
        dpsi = tmpl_Double_Elliptical_Fresnel_dPsi_dPhi(
            k, rho, r0, phi, phi0, B, D, ecc, peri
        );
        d2psi = tmpl_Double_Cyl_Fresnel_d2Psi_dPhi2(
            k, rho, r0, phi, phi0, B, D
        );

        phi = phi - dpsi / d2psi;

        ++n;

        if (n > toler)
            break;

        D = tmpl_Double_Cyl_Fresnel_Observer_Distance(r0, phi, rx, ry, rz);
        ecc_cos_factor = 1.0 + ecc * tmpl_Double_Cos(phi - peri);
        rho = factor / ecc_cos_factor;
    }
    return phi;
}
