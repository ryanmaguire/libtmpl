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
 *  Date:       June 12, 2025                                                 *
 ******************************************************************************/

/*  Trig functions and square root found here.                                */
#include <libtmpl/include/tmpl_math.h>

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_cyl_fresnel_optics.h>

/*  2D vector functions found here.                                           */
#include <libtmpl/include/tmpl_vec2.h>

/*  Complex functions and data types found here.                              */
#include <libtmpl/include/tmpl_complex.h>

tmpl_ComplexDouble
tmpl_Double_Stationary_Cyl_Fresnel_Kernel(
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
    const double rcpr_rho0_dist = 1.0 / rho0_dist;

    const double sin_B = uz / rho0_dist;

    const double uxn = ux * rcpr_rho0_dist;
    const double uyn = uy * rcpr_rho0_dist;
    const double uzn = uz * rcpr_rho0_dist;

    unsigned int iters = 0U;
    const double r_s = tmpl_2DDouble_L2_Norm(rho);
    double phi_s = tmpl_2DDouble_Polar_Angle(rho);
    tmpl_TwoVectorDouble rho_s = *rho;
    double err;
    const tmpl_ComplexDouble rotate = tmpl_CDouble_Rect(1.0, -1.0);

    double dx_s, dy_s, dot, mag, d2psi, psi, scale, weight;
    tmpl_ComplexDouble ker;

    eps /= k;

    do {
        /*  The difference between the "dummy" point in the plane, rho, that  *
         *  is integrated over, and the orthogonal projection of the position *
         *  vector for the observer, R, onto the ring plane.                  */
        const double dx = R->dat[0] - rho_s.dat[0];
        const double dy = R->dat[1] - rho_s.dat[1];

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
        const double left1 = (dx * rho_s.dat[1] - dy * rho_s.dat[0]) / rho_dist;
        const double right1 = uyn * rho_s.dat[0] - uxn * rho_s.dat[1];
        const double dpsi = left1 + right1;

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
        const double diff = rho_s.dat[0] * R->dat[1] - rho_s.dat[1] * R->dat[0];
        const double sum = R->dat[0] * rho_s.dat[0] + R->dat[1] * rho_s.dat[1];

        /*  Call the combination of the left and center parts "left". Compute.*/
        const double left2 = (diff*diff*rcpr_rho_dist_sq - sum) * rcpr_rho_dist;

        /*  The expression u . rho'' is -(ux * rho_x + uy * rho_y). The right *
         *  expression is this factor divided by the distance from R to rho0. */
        const double right2 = uxn * rho_s.dat[0] + uyn * rho_s.dat[1];
        d2psi = left2 + right2;

        err = tmpl_Double_Abs(dpsi);
        phi_s = phi_s + dpsi / d2psi;
        rho_s = tmpl_2DDouble_Polar(r_s, phi_s);
        ++iters;

        if (iters > max_iters)
            break;

    } while (err > eps);

    /*  psi is given by k (un . (R - rho_s) + |R - rho_s|).                   */
    dx_s = R->dat[0] - rho_s.dat[0];
    dy_s = R->dat[1] - rho_s.dat[1];
    dot = uxn * dx_s + uyn * dy_s + uzn * uz;
    mag = tmpl_Double_Hypot3(dx_s, dy_s, uz);
    psi = k * (mag - dot) - tmpl_Double_Pi_By_Four;

    /*  Compute the scale factor from the stationary phase approximation.     */
    weight = tmpl_Double_Rcpr_Pi * tmpl_Double_Abs(k / d2psi);
    scale = 0.5 * sin_B * r_s * tmpl_Double_Sqrt(weight) / mag;

    /*  The Fresnel kernel is the scale factor times exp(i psi). The          *
     *  stationary phase also contains exp(-i pi / 4), which rotates the      *
     *  result. This is equivalent to multiplying by (1 - i) / sqrt(2).       */
    ker = tmpl_CDouble_Polar(scale, psi);
    tmpl_CDouble_MultiplyBy(&ker, &rotate);
    return ker;
}
