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

#if 0

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

#else

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
    /*  The relative position vector, u, of the observer from the ring        *
     *  intercept point. Since rho0 lies in the plane, there is no z part.    */
    const double ux = R->dat[0] - rho0->dat[0];
    const double uy = R->dat[1] - rho0->dat[1];
    const double uz = R->dat[2];

    /*  Compute the distance between rho0 and R. This is "D" in MTR86.        */
    const double rho0_dist = tmpl_Double_Hypot3(ux, uy, uz);

    unsigned int iters = 0U;
    const double r_s = tmpl_2DDouble_L2_Norm(rho);
    double phi_s = tmpl_2DDouble_Polar_Angle(rho);
    tmpl_TwoVectorDouble rhos = *rho;
    double err;
    eps /= k;

    do {
        /*  The difference between the "dummy" point in the plane, rho, that  *
         *  is integrated over, and the orthogonal projection of the position *
         *  vector for the observer, R, onto the ring plane.                  */
        const double dx = R->dat[0] - rhos.dat[0];
        const double dy = R->dat[1] - rhos.dat[1];

        /*  We need the distances from R to rho and R to rho0. These can be   *
         *  computed with the Hypot3 function.                                */
        const double rho_dist = tmpl_Double_Hypot3(dx, dy, uz);

        /*  The second derivative contains both 1 / || R - rho || and the     *
         *  square of this expression. Pre-compute these.                     */
        const double rcpr_rho_dist = 1.0 / rho_dist;
        const double rcpr_rho_dist_sq = rcpr_rho_dist * rcpr_rho_dist;

        /*  The derivative is given by:                                       *
         *                                                                    *
         *               -                                                 -  *
         *              | dx * rho_y - dy * rho_x   uy * rho_x -ux * rho_y  | *
         *      psi' = k| ----------------------- + ----------------------  | *
         *              |     || R - rho ||             || R - rho0 ||      | *
         *               -                                                 -  *
         *                                                                    *
         *  Call the left expression "left" and the right one "right."        */
        const double left1 = (dx * rhos.dat[1] - dy * rhos.dat[0]) / rho_dist;
        const double right1 = (uy * rhos.dat[0] - ux * rhos.dat[1]) / rho0_dist;

        /*  The second derivative is given by:                                *
         *                                                                    *
         *                 -                                                  *
         *                | (R - rho) . rho'' - rho' . rho'                   *
         *      psi'' = k | ------------------------------ -                  *
         *                |          || R - rho ||                            *
         *                 -                                                  *
         *                                                   -                *
         *                  ((R - rho) . rho')^2              |               *
         *                  -------------------- + un . rho'' |               *
         *                    || R - rho ||^3/2               |               *
         *                                                   -                *
         *                                                                    *
         *  The first expression simplifies to -(x rho_x + y rho_y) and the   *
         *  central piece is (rho_x y - rho_y x)^2. Compute both of these.    */
        const double diff = rhos.dat[0] * R->dat[1] - rhos.dat[1] * R->dat[0];
        const double sum = R->dat[0] * rhos.dat[0] + R->dat[1] * rhos.dat[1];

        /*  Call the combination of the left and center parts "left". Compute.*/
        const double left2 = (diff*diff*rcpr_rho_dist_sq - sum) * rcpr_rho_dist;

        /*  The expression u . rho'' is -(ux * rho_x + uy * rho_y). The right *
         *  expression is this factor divided by the distance from R to rho0. */
        const double right2 = (ux * rhos.dat[0] + uy * rhos.dat[1]) / rho0_dist;

        const double dpsi = left1 + right1;
        const double d2psi = left2 + right2;

        err = tmpl_Double_Abs(dpsi);
        phi_s = phi_s + dpsi / d2psi;
        rhos = tmpl_2DDouble_Polar(r_s, phi_s);
        ++iters;

        if (iters > max_iters)
            break;

    } while (err > eps);

    /*  The output is the sum scaled by the wavenumber, k.                    */
    return tmpl_Double_Cyl_Fresnel_Psi(k, &rhos, rho0, R);
}

#endif
