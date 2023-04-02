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
tmpl_Double_Stationary_Cyl_Fresnel_Psi_dD_dPhi_Newton(double k, double r,
                                                      double r0, double phi,
                                                      double phi0, double B,
                                                      double rx, double ry,
                                                      double rz, double eps,
                                                      unsigned int toler)
{
    double d2psi;
    unsigned int n = 0U;
    double D = tmpl_Double_Cyl_Fresnel_Observer_Distance(r0, phi, rx, ry, rz);
    double dpsi = tmpl_Double_Cyl_Fresnel_dPsi_dPhi_D(
        k, r, r0, phi, phi0, B, rx, ry, rz
    );

    double err = tmpl_Double_Abs(dpsi);

    while (err > eps)
    {
        d2psi = tmpl_Double_Cyl_Fresnel_d2Psi_dPhi2(k, r, r0, phi, phi0, B, D);
        phi = phi - dpsi / d2psi;

        ++n;

        if (n > toler)
            break;

        D = tmpl_Double_Cyl_Fresnel_Observer_Distance(r0, phi, rx, ry, rz);
        dpsi = tmpl_Double_Cyl_Fresnel_dPsi_dPhi_D(
            k, r, r0, phi, phi0, B, rx, ry, rz
        );

        err = tmpl_Double_Abs(dpsi);
    }

    return phi;
}
