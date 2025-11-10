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

/*  The cylindrical Fresnel geometry struct.                                  */
#include <libtmpl/include/types/tmpl_cyl_fresnel_geometry_double.h>

/*  Hypot3 and the absolute value function are provided here.                 */
#include <libtmpl/include/tmpl_math.h>

/*  2D vector functions found here.                                           */
#include <libtmpl/include/tmpl_vec2.h>

/*  Complex functions and data types found here.                              */
#include <libtmpl/include/tmpl_complex.h>

/*  Forward declaration / function prototype.                                 */
extern tmpl_ComplexDouble
tmpl_Double_Stationary_Cyl_Fresnel_Kernel(
    double k,
    const tmpl_CylFresnelGeometryDouble * const geo,
    double eps,
    unsigned int max_iters
);

/*  Function for computing the full stationary Fresnel kernel.                */
tmpl_ComplexDouble
tmpl_Double_Stationary_Cyl_Fresnel_Kernel(
    double k,
    const tmpl_CylFresnelGeometryDouble * const geo,
    double eps,
    unsigned int max_iters
)
{
    /*  Rotation factor for the output, sqrt(2) * exp(-i pi / 4).             */
    const tmpl_ComplexDouble rotate = tmpl_CDouble_Rect(1.0, -1.0);

    /*  The relative position vector, u, of the observer from the ring        *
     *  intercept point. Since rho0 lies in the plane, there is no z part.    */
    const double ux = geo->position.dat[0] - geo->intercept.dat[0];
    const double uy = geo->position.dat[1] - geo->intercept.dat[1];
    const double uz = geo->position.dat[2];

    /*  Compute the distance between rho0 and R. This is "D" in MTR86.        */
    const double rho0_dist = tmpl_Double_Hypot3(ux, uy, uz);
    const double rcpr_rho0_dist = 1.0 / rho0_dist;

    /*  Compute the unit normal vector pointing from the intercept point to   *
     *  the observer. We do this by normalizing the u vector.                 */
    const double uxn = ux * rcpr_rho0_dist;
    const double uyn = uy * rcpr_rho0_dist;
    const double uzn = uz * rcpr_rho0_dist;

    /*  Using u and rho, we can compute the sine of the opening angle without *
     *  the need for trig functions. Compute.                                 */
    const double sin_opening = uz / rho0_dist;

    /*  The radius of the dummy variable does not change, but we still need   *
     *  this to update the angle in the Newton-Raphson loop.                  */
    const double r_s = tmpl_2DDouble_L2_Norm(&geo->dummy);

    /*  The angle does change, iteratively as we apply Newton-Raphson. The    *
     *  initial guess for Newton-Raphson is the angle of the dummy variable.  */
    double phi_s = tmpl_2DDouble_Polar_Angle(&geo->dummy);

    /*  The geo object is constant, but we need a 2D vector to update. Get a  *
     *  copy and store it in a new variable.                                  */
    tmpl_TwoVectorDouble rho_s = geo->dummy;

    /*  Variable for keeping track of the number of iterations performed.     */
    unsigned int iters = 0U;

    /*  Error variable used to track the magnitude of psi'.                   */
    double err;

    /*  Variables for the computation of psi. psi is computed via:            *
     *                                                                        *
     *      psi = k (|| R - rho || - un . (R - rho))                          *
     *                                                                        *
     *  mag is the left term, dot is the right term, and dx_s and dx_y are    *
     *  x and y components of R - rho, respectively.                          */
    double dx_s, dy_s, dot, mag;

    /*  Variable for the output, which is given by:                           *
     *                                                                        *
     *                               ---------                                *
     *            sin(B)  1 - i     /   2 pi     exp(i psi_s)                 *
     *      ker = ------ -------   / --------- ---------------                *
     *               L   sqrt(2) \/  |psi_s''| || R - rho_s ||                *
     *                                                                        *
     *                                 ---------                              *
     *             sin(B)   1 - i     /   2 pi     exp(i psi_s)               *
     *          = -------- -------   / --------- ---------------              *
     *            2 pi / k sqrt(2) \/  |psi_s''| || R - rho_s ||              *
     *                                                                        *
     *                                 ------------                           *
     *                      1 - i     /     1        exp(i psi_s)             *
     *          = k sin(B) -------   / ------------ ---------------           *
     *                        2    \/  pi |psi_s''| || R - rho_s ||           *
     *                                                                        *
     *  We need variables for psi, psi'', and the scale factor for the kernel.*/
    double d2psi, psi, weight, scale;
    tmpl_ComplexDouble ker;

    /*  The wavenumber is usually quite large. To get a good relative error,  *
     *  scale the epsilon factor by the reciprocal of the wavenumber.         */
    eps /= k;

    /*  Loop through and iteratively apply Newton's method.                   */
    do {
        /*  The difference between the "dummy" point in the plane, rho, that  *
         *  is integrated over, and the orthogonal projection of the position *
         *  vector for the observer, R, onto the ring plane.                  */
        const double dx = geo->position.dat[0] - rho_s.dat[0];
        const double dy = geo->position.dat[1] - rho_s.dat[1];

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
         *                | (rho - R) . rho'' + rho' . rho'                   *
         *      psi'' = k | ------------------------------ -                  *
         *                |          || R - rho ||                            *
         *                 -                                                  *
         *                                                   -                *
         *                  ((rho - R) . rho')^2              |               *
         *                  -------------------- + un . rho'' |               *
         *                    || R - rho ||^3/2               |               *
         *                                                   -                *
         *                                                                    *
         *  The first expression simplifies to x rho_x + y rho_y and the      *
         *  central piece is (rho_x y - rho_y x)^2. Compute the sum portion.  */
        const double sum =
            geo->position.dat[0] * geo->dummy.dat[0] +
            geo->position.dat[1] * geo->dummy.dat[1];

        /*  Compute the difference part, rho_x y - rho_y x.                   */
        const double diff =
            geo->dummy.dat[0] * geo->position.dat[1] -
            geo->dummy.dat[1] * geo->position.dat[0];

        /*  Call the combination of the left and center parts "left". Compute.*/
        const double left2 = (diff*diff*rcpr_rho_dist_sq - sum) * rcpr_rho_dist;

        /*  The expression u . rho'' is -(ux * rho_x + uy * rho_y). The right *
         *  expression is this factor divided by the distance from R to rho0. */
        const double right2 = uxn * rho_s.dat[0] + uyn * rho_s.dat[1];

        /*  The second derivative can now be computed from the previous terms.*/
        d2psi = left2 + right2;

        /*  Update the error to the magnitude of the first partial derivative.*/
        err = tmpl_Double_Abs(dpsi);

        /*  Update the guess by applying the Newton-Raphson iterate.          */
        phi_s = phi_s + dpsi / d2psi;

        /*  The angle for the dummy variable has updated. Re-compute.         */
        rho_s = tmpl_2DDouble_Polar(r_s, phi_s);

        /*  Update the number of iterations to avoid an infinite loop.        */
        ++iters;

        if (iters > max_iters)
            break;

    } while (err > eps);

    /*  If the Newton-Raphson method converged, rho_s is now computed about   *
     *  the stationary azimuth angle, which is the angle phi = phi_s such     *
     *  that d psi / d phi = 0. Compute psi with respect to this new angle.   */
    dx_s = geo->position.dat[0] - rho_s.dat[0];
    dy_s = geo->position.dat[1] - rho_s.dat[1];
    dot = uxn * dx_s + uyn * dy_s + uzn * uz;
    mag = tmpl_Double_Hypot3(dx_s, dy_s, uz);

    /*  The Fresnel phase is scaled by the wavenumber. Compute.               */
    psi = k * (mag - dot);

    /*  Compute the Fresnel kernel at the stationary azimuth angle, phi_s.    *
     *  Note, this function returns the scale factor that is present from     *
     *  the stationary phase approximation. The general integral is:          *
     *                                                                        *
     *                          -    -                                        *
     *      ^         sin(B)   | |  | |        exp(i  psi)                    *
     *      T(rho0) = ------   |    |   T(rho) ----------- drho               *
     *                lambda | |  | |          | R - rho |                    *
     *                        -    -                                          *
     *                                                                        *
     *  Where rho is a vector in this expression. Writing                     *
     *  rho = (r cos(phi), r sin(phi)), drho = r dr dphi, and assuming        *
     *  circular symmetry, T(rho) = T(r), we obtain:                          *
     *                                                                        *
     *                         inf         2 pi                               *
     *                          -           -                                 *
     *      ^         sin(B)   | |         | | exp(i  psi)                    *
     *      T(rho0) = ------   |  r T(r)   |   ----------- dphi dr            *
     *                lambda | |         | |   | R - rho |                    *
     *                        -           -                                   *
     *                        0           0                                   *
     *                                                                        *
     *  The phi integral is handled via stationary phase, producing:          *
     *                                                                        *
     *                                                                        *
     *        2 pi                                                            *
     *         -                          _________                           *
     *        | | exp(i  psi)            / 2 pi     exp(i (psi_s - pi/4))     *
     *        |   ----------- dphi ~=   / --------- -------------------       *
     *      | |   | R - rho |         \/  |psi_s''|    | R - rho_s |          *
     *       -                                                                *
     *       0                                                                *
     *                                                                        *
     *  Where phi_s is the stationary azimuth angle, psi_s and psi_s''        *
     *  the evaluation of psi and psi'' at phi = phi_s, respectively, and     *
     *  where rho_s = (r cos(phi_s), r sin(phi_s)). The stationary            *
     *  cylindrical Fresnel kernel is r times this expression. This           *
     *  function computes this quantity.                                      */
    weight = k * tmpl_Double_Rcpr_Pi / tmpl_Double_Abs(d2psi);
    scale = 0.5 * sin_opening * r_s * tmpl_Double_Sqrt(weight) / mag;

    /*  The Fresnel kernel is the scale factor times exp(i psi). The          *
     *  stationary phase also contains exp(-i pi / 4), which rotates the      *
     *  result. This is equivalent to multiplying by (1 - i) / sqrt(2).       */
    ker = tmpl_CDouble_Polar(scale, psi);
    tmpl_CDouble_MultiplyBy(&ker, &rotate);
    return ker;
}
/*  End of tmpl_Double_Stationary_Cyl_Fresnel_Psi.                            */
