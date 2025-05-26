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
 *  Date:       May 26, 2025                                                  *
 ******************************************************************************/

/*  Trig functions and square root found here.                                */
#include <libtmpl/include/tmpl_math.h>

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_cyl_fresnel_optics.h>

/*  2D vector functions found here.                                           */
#include <libtmpl/include/tmpl_vec2.h>

double
tmpl_Double_Stationary_Cyl_Fresnel_Psi(
    double k,
    const tmpl_TwoVectorDouble * const rho,
    const tmpl_TwoVectorDouble * const rho0,
    const tmpl_ThreeVectorDouble * TMPL_RESTRICT const R,
    double eps,
    unsigned int max_iters
)
{
    tmpl_TwoVectorDouble rho_s;
    double dpsi, d2psi, err;
    unsigned int n = 0U;
    const double r_s = tmpl_2DDouble_L2_Norm(rho);
    double phi_s = tmpl_2DDouble_Polar_Angle(rho);

    do {
        rho_s = tmpl_2DDouble_Polar(r_s, phi_s);
        dpsi = tmpl_Double_Cyl_Fresnel_dPsi_dPhi(k, &rho_s, rho0, R);
        d2psi = tmpl_Double_Cyl_Fresnel_d2Psi_dPhi2(k, &rho_s, rho0, R);
        phi_s = phi_s - dpsi / d2psi;
        err = tmpl_Double_Abs(dpsi);

        ++n;

        if (n > max_iters)
            break;

    } while(err > eps);

    return tmpl_Double_Cyl_Fresnel_Psi(k, &rho_s, rho0, R);
}
