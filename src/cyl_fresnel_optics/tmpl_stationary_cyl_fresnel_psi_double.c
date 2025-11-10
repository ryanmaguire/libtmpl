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
 *                   tmpl_stationary_cyl_fresnel_psi_double                   *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the Fresnel phase, psi, evaluated at the stationary azimuth  *
 *      angle, which is the angle phi = phi_s such that d psi / d phi = 0.    *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Stationary_Cyl_Fresnel_Psi                                *
 *  Purpose:                                                                  *
 *      Computes the stationary cylindrical Fresnel phase, psi.               *
 *  Arguments:                                                                *
 *      k (double):                                                           *
 *          The wavenumber, in the reciprocal of the units of geo->intercept. *
 *      geo (const tmpl_CylFresnelGeometryDouble * const):                    *
 *          The geometry of the observation. This contains the position       *
 *          vector for the observer, and the vectors in the xy plane for the  *
 *          intercept point (where the line of sight for the observer crosses *
 *          the xy plane), and the dummy variable of integration.             *
 *      eps (double):                                                         *
 *          The epsilon factor, the threshold for breaking the Newton-Raphson *
 *          loop for d psi / d phi.                                           *
 *      max_iters (unsigned int):                                             *
 *          The maximum number of iterations allowed for Newton-Raphson.      *
 *  Outputs:                                                                  *
 *      psi_s (double):                                                       *
 *          The Fresnel phase evaluated at the stationary azimuth angle.      *
 *  Called Functions:                                                         *
 *      src/math/                                                             *
 *          tmpl_Double_Abs:                                                  *
 *              Computes the absolute value of a real number.                 *
 *          tmpl_Double_Hypot3:                                               *
 *              Computes the magnitude of the vector (x, y, z).               *
 *      src/vec2/                                                             *
 *          tmpl_2DDouble_Polar:                                              *
 *              Computes a 2D vector from its polar coordinates.              *
 *          tmpl_2DDouble_Polar_Angle:                                        *
 *              Computes the angle a 2D vector makes with the x axis.         *
 *          tmpl_2DDouble_L2_Norm:                                            *
 *              Computes the Euclidean norm of a 2D vector.                   *
 *  Method:                                                                   *
 *      Apply Newton-Raphson with the Fresnel phase. The Fresnel transform is:*
 *                                                                            *
 *                              -    -                                        *
 *          ^         sin(B)   | |  | |          exp(i psi)                   *
 *          T(rho0) = ------   |    |   T(rho) ------------- d rho            *
 *                     i L   | |  | |          || R - rho ||                  *
 *                            -    -  2                                       *
 *                                   R                                        *
 *                                                                            *
 *      Where R is the position vector for the observer, rho0 is the position *
 *      vector for the point of interest, rho is the dummy variable (vector)  *
 *      of integration, L is the wavelength, and B is the opening angle (the  *
 *      angle made by the vector going from the observer, R, to the point     *
 *      rho0, and the xy plane). The Fresnel phase is the psi quantity, it    *
 *      is purely geometric and given by:                                     *
 *                                                                            *
 *                   -                                          -             *
 *                  |                    R - rho0                |            *
 *          psi = k | || R - rho || - -------------- . (R - rho) |            *
 *                  |                 || R - rho0 ||             |            *
 *                   -                                          -             *
 *                                                                            *
 *      Where k is the wavenumber, in reciprocal units of the wavelength, L.  *
 *      By labeling u = R - rho0, and un = u / || u ||, the unit vector in    *
 *      the direction of u, this becomes:                                     *
 *                                                                            *
 *          psi = k (|| R - rho || - un . (R - rho))                          *
 *                                                                            *
 *      The rho vector is given by (r cos(phi), r sin(phi)), where r is the   *
 *      magnitude and phi is the azimuth angle. The partial derivative of psi *
 *      with respect to phi then becomes:                                     *
 *                                                                            *
 *          psi' = k(|| R - rho ||' - un . (R - rho)')                        *
 *               = k(|| R - rho ||' + un . rho')                              *
 *                    -                           -                           *
 *                   | (rho - R) . rho'            |                          *
 *               = k | --------------- + un . rho' |                          *
 *                   |  || R - rho ||              |                          *
 *                    -                           -                           *
 *                                                                            *
 *      The second derivative is then:                                        *
 *                                                                            *
 *                     -                                                      *
 *                    | (rho - R) . rho'' + rho' . rho'                       *
 *          psi'' = k | ------------------------------ -                      *
 *                    |          || R - rho ||                                *
 *                     -                                                      *
 *                                                       -                    *
 *                      ((rho - R) . rho')^2              |                   *
 *                      -------------------- + un . rho'' |                   *
 *                        || R - rho ||^3/2               |                   *
 *                                                       -                    *
 *                                                                            *
 *      Using the following substitutions:                                    *
 *                                                                            *
 *          rho = (r cos(phi), r sin(phi), 0)                                 *
 *          R   = (x, y, z)                                                   *
 *                                                                            *
 *      The derivatives are then:                                             *
 *                                                                            *
 *          rho'  = (-r sin(phi), r cos(phi), 0)                              *
 *          rho'' = (-r cos(phi), -r sin(phi), 0)                             *
 *                                                                            *
 *      This first expression becomes:                                        *
 *                                                                            *
 *          (rho - R) . rho'' + rho' . rho' = x r cos(phi) + y r sin(phi)     *
 *                                                                            *
 *      Since r cos(phi) is the x-coordinate of rho, rho_x, and r sin(phi) is *
 *      the y-coordinate of rho, rho_y, we may rewrite this:                  *
 *                                                                            *
 *          (rho - R) . rho'' + rho' . rho' = x rho_x + y rho_y               *
 *                                                                            *
 *      The middle expression becomes equally simple:                         *
 *                                                                            *
 *          ((rho - R) . rho')^2 = (rho_x y - rho_y x)^2                      *
 *                                                                            *
 *      The final expression, un . rho'', has a nice formula as well. If we   *
 *      define u = R - rho0 = (ux, uy, uz), we get:                           *
 *                                                                            *
 *                       -ux * rho_x - uy * rho_y                             *
 *          un . rho'' = ------------------------                             *
 *                            || R - rho0 ||                                  *
 *                                                                            *
 *      We use this to compute psi' and psi'' simultaneously, and then given  *
 *      the initial guess phi_s = phi, we iteratively apply Newton-Raphson:   *
 *                                                                            *
 *          phi_s = phi_s - psi' / psi''                                      *
 *                                                                            *
 *      We then check |psi'| to see if this is small, returning psi if so,    *
 *      and otherwise continuing until max_iters iterations has been done.    *
 *  Notes:                                                                    *
 *      1.) All vectors in geo are given in Cartesian coordinates.            *
 *      2.) All lengths are assumed to be in the same units.                  *
 *      3.) There are no checks for NULL pointers. It is assumed geo is valid.*
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
 *  1.) tmpl_cyl_fresnel_geometry_double.h:                                   *
 *          Location of the tmpl_CylFresnelGeometryDouble typedef.            *
 *  2.) tmpl_math.h:                                                          *
 *          Header providing the Hypot3 and Abs functions.                    *
 *  3.) tmpl_vec2.h:                                                          *
 *          Header providing the L2 norm and polar angle functions.           *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 26, 2025                                                  *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2025/11/10: Ryan Maguire                                                  *
 *      Rewrote to use tmpl_CylFresnelGeometryDouble struct.                  *
 ******************************************************************************/

/*  The cylindrical Fresnel geometry struct.                                  */
#include <libtmpl/include/types/tmpl_cyl_fresnel_geometry_double.h>

/*  Hypot3 and the absolute value function are provided here.                 */
#include <libtmpl/include/tmpl_math.h>

/*  2D vector functions found here.                                           */
#include <libtmpl/include/tmpl_vec2.h>

/*  Forward declaration / function prototype.                                 */
extern double
tmpl_Double_Stationary_Cyl_Fresnel_Psi(
    double k,
    const tmpl_CylFresnelGeometryDouble * const geo,
    double eps,
    unsigned int max_iters
);

/*  The primary algorithm is to inline and combine the first and second       *
 *  derivative computations into one, saving us a lot of repetitive           *
 *  calculations and redundant function calls.                                */
#if 1

/*  Function for computing the stationary Fresnel phase.                      */
double
tmpl_Double_Stationary_Cyl_Fresnel_Psi(
    double k,
    const tmpl_CylFresnelGeometryDouble * const geo,
    double eps,
    unsigned int max_iters
)
{
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
    double dx_s, dy_s, mag, dot;

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
         *  computed with the Hypot3 function. The distance from R to rho0    *
         *  has already been computed, and R and rho0 are constant throughout *
         *  this computation. Ne need to re-compute.                          */
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
         *  expression is this factor divided by the distance from R to rho0. *
         *  The normalized variables, uxn and uyn, have this scale factor.    */
        const double right2 = uxn * rho_s.dat[0] + uyn * rho_s.dat[1];

        /*  The second derivative can now be computed from the previous terms.*/
        const double d2psi = left2 + right2;

        /*  Update the error to the magnitude of the first partial derivative.*/
        err = tmpl_Double_Abs(dpsi);

        /*  Update the guess by applying the Newton-Raphson iterate.          */
        phi_s = phi_s + dpsi / d2psi;

        /*  The angle for the dummy variable has been updated. Re-compute.    */
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

    /*  The Fresnel phase is scaled by the wavenumber. Return.                */
    return k * (mag - dot);
}
/*  End of tmpl_Double_Stationary_Cyl_Fresnel_Psi.                            */

/*  Alternatively, we may use other functions in libtmpl to perform the       *
 *  computation. This has several benefits:                                   *
 *                                                                            *
 *      1.) Significantly shorter function.                                   *
 *      2.) Easier to diagnose bugs by writing unit tests for each function.  *
 *      3.) Good programming practice, splitting parts into other functions.  *
 *      4.) Easier to follow / read.                                          *
 *                                                                            *
 *  Unfortunately, it has a major downside, it is more than 2 times slower.   *
 *  The reason is simple, the psi, psi', and psi'' functions all need to      *
 *  compute very similar expressions, making functions calls to each of these *
 *  means we are computing these expressions several times redundantly. We    *
 *  use the code below simply to test the code above for bugs. The default    *
 *  build uses the faster (but harder to read) version above.                 */
#else

/*  The zeroth, first, and second partial derivatives of psi found here.      */
#include <libtmpl/include/tmpl_cyl_fresnel_optics.h>

/*  Function for computing the stationary Fresnel phase.                      */
double
tmpl_Double_Stationary_Cyl_Fresnel_Psi(
    double k,
    const tmpl_CylFresnelGeometryDouble * const geo,
    double eps,
    unsigned int max_iters
)
{
    /*  Decompose the dummy variable into its polar coordinates.              */
    const double r_s = tmpl_2DDouble_L2_Norm(&geo->dummy);
    double phi_s = tmpl_2DDouble_Polar_Angle(&geo->dummy);

    /*  The input is a constant, but we need to modify the data as we perform *
     *  Newton's method. Make a copy.                                         */
    tmpl_CylFresnelGeometryDouble geo_s = *geo;

    /*  Variable for the error, which is the absolute value of psi'.          */
    double err;

    /*  Variable for keeping track of the number of iterations performed.     */
    unsigned int iters = 0U;

    /*  Loop through and iteratively apply Newton's method.                   */
    do {
        /*  Newton's method updates the guess via:                            *
         *                                                                    *
         *                    psi'                                            *
         *      phi  = phi  - -----                                           *
         *         s      s   psi''                                           *
         *                                                                    *
         *  Compute the first and second partial derivatives and update phi_s.*/
        const double dpsi = tmpl_Double_Cyl_Fresnel_dPsi_dPhi(k, &geo_s);
        const double d2psi = tmpl_Double_Cyl_Fresnel_d2Psi_dPhi2(k, &geo_s);
        phi_s = phi_s - dpsi / d2psi;

        /*  Reset the dummy variable to use the new angle.                    */
        geo_s.dummy = tmpl_2DDouble_Polar(r_s, phi_s);

        /*  Compute the error in the guess, which is |psi'|.                  */
        err = tmpl_Double_Abs(dpsi);

        /*  Update the number of iterations to avoid an infinite loop.        */
        ++iters;

        if (iters > max_iters)
            break;

    } while(err > eps);

    /*  Return the Fresnel phase evaluated at the stationary azimuth angle.   */
    return tmpl_Double_Cyl_Fresnel_Psi(k, &geo_s);
}
/*  End of tmpl_Double_Stationary_Cyl_Fresnel_Psi.                            */

#endif
