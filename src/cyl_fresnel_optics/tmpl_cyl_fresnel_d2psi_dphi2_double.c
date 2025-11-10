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
 *                    tmpl_cyl_fresnel_d2psi_dphi2_double                     *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the second partial derivative of the cylindrical Fresnel     *
 *      phase with respect to the azimuthal angle, phi.                       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Cyl_Fresnel_d2Psi_dPhi2                                   *
 *  Purpose:                                                                  *
 *      Computes the second partial derivative of psi, the Fresnel phase,     *
 *      with respect to phi, the azimuth angle.                               *
 *  Arguments:                                                                *
 *      k (double):                                                           *
 *          The wavenumber, in the reciprocal of the units of geo->intercept. *
 *      geo (const tmpl_CylFresnelGeometryDouble * const):                    *
 *          The geometry of the observation. This contains the position       *
 *          vector for the observer, and the vectors in the xy plane for the  *
 *          intercept point (where the line of sight for the observer crosses *
 *          the xy plane), and the dummy variable of integration.             *
 *  Outputs:                                                                  *
 *      d2psi (double):                                                       *
 *          The second partial derivative of the Fresnel phase, psi, with     *
 *          respect to phi, the azimuth angle.                                *
 *  Called Functions:                                                         *
 *      src/math/                                                             *
 *          tmpl_Double_Hypot3:                                               *
 *              Computes the magnitude of the vector (x, y, z).               *
 *  Method:                                                                   *
 *      Use the formula for the Fresnel phase. The Fresnel transform is:      *
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
 *      We combine these three expressions to compute psi''.                  *
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
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 23, 2025                                                  *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2025/11/10: Ryan Maguire                                                  *
 *      Rewrote to use tmpl_CylFresnelGeometryDouble struct.                  *
 ******************************************************************************/

/*  The cylindrical Fresnel geometry struct.                                  */
#include <libtmpl/include/types/tmpl_cyl_fresnel_geometry_double.h>

/*  Forward declaration / function prototype.                                 */
extern double
tmpl_Double_Cyl_Fresnel_d2Psi_dPhi2(
    double k, const tmpl_CylFresnelGeometryDouble * const geo
);

/*  Tell the compiler about the L2 norm function, Hypot3.                     */
extern double tmpl_Double_Hypot3(double x, double y, double z);

/*  Second partial derivative of the Fresnel phase with respect to phi.       */
double
tmpl_Double_Cyl_Fresnel_d2Psi_dPhi2(
    double k, const tmpl_CylFresnelGeometryDouble * const geo
)
{
    /*  The relative position vector, u, of the observer from the ring        *
     *  intercept point. Since rho0 lies in the plane, there is no z part.    */
    const double ux = geo->position.dat[0] - geo->intercept.dat[0];
    const double uy = geo->position.dat[1] - geo->intercept.dat[1];
    const double uz = geo->position.dat[2];

    /*  The difference between the "dummy" point in the plane, rho, that is   *
     *  integrated over, and the orthogonal projection of the position vector *
     *  for the observer, R, onto the ring plane.                             */
    const double dx = geo->position.dat[0] - geo->dummy.dat[0];
    const double dy = geo->position.dat[1] - geo->dummy.dat[1];

    /*  We need the distances from R to rho and R to rho0. These can be       *
     *  computed with the Hypot3 function.                                    */
    const double rho_dist = tmpl_Double_Hypot3(dx, dy, uz);
    const double rho0_dist = tmpl_Double_Hypot3(ux, uy, uz);

    /*  The second derivative contains both 1 / || R - rho || and the square  *
     *  of this expression. Pre-compute the reciprocal and its square.        */
    const double rcpr_rho_dist = 1.0 / rho_dist;
    const double rcpr_rho_dist_sq = rcpr_rho_dist * rcpr_rho_dist;

    /*  The second derivative is given by:                                    *
     *                                                                        *
     *                 -                                                      *
     *                | (rho - R) . rho'' + rho' . rho'                       *
     *      psi'' = k | ------------------------------ -                      *
     *                |          || R - rho ||                                *
     *                 -                                                      *
     *                                                   -                    *
     *                  ((rho - R) . rho')^2              |                   *
     *                  -------------------- + un . rho'' |                   *
     *                    || R - rho ||^3/2               |                   *
     *                                                   -                    *
     *                                                                        *
     *  The first expression simplifies to x rho_x + y rho_y and the          *
     *  central piece is (rho_x y - rho_y x)^2. Compute the sum portion.      */
    const double sum =
        geo->position.dat[0] * geo->dummy.dat[0] +
        geo->position.dat[1] * geo->dummy.dat[1];

    /*  Compute the difference part, rho_x y - rho_y x.                       */
    const double diff =
        geo->dummy.dat[0] * geo->position.dat[1] -
        geo->dummy.dat[1] * geo->position.dat[0];

    /*  Call the combination of the left and center parts "left". Compute.    */
    const double left = (sum - diff * diff * rcpr_rho_dist_sq) * rcpr_rho_dist;

    /*  The expression u . rho'' is -(ux * rho_x + uy * rho_y). The right     *
     *  expression is this factor divided by the distance from R to rho0.     */
    const double right =
        -(ux * geo->dummy.dat[0] + uy * geo->dummy.dat[1]) / rho0_dist;

    /*  The Fresnel phase is scaled by the wavenumber, k, and hence so is the *
     *  second derivative with respect to the azimuth angle, phi.             */
    return k * (left + right);
}
/*  End of tmpl_Double_Cyl_Fresnel_d2Psi_dPhi2.                               */
