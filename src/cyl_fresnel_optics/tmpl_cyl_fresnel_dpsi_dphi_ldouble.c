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
 *                     tmpl_cyl_fresnel_dpsi_dphi_ldouble                     *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the partial derivative of the cylindrical Fresnel phase      *
 *      with respect to the azimuthal angle, phi.                             *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Cyl_Fresnel_dPsi_dPhi                                    *
 *  Purpose:                                                                  *
 *      Computes the partial derivative of psi, the Fresnel phase, with       *
 *      respect to phi, the azimuth angle.                                    *
 *  Arguments:                                                                *
 *      k (long double):                                                      *
 *          The wavenumber, in the reciprocal of the units of geo->intercept. *
 *      geo (const tmpl_CylFresnelGeometryLongDouble * const):                *
 *          The geometry of the observation. This contains the position       *
 *          vector for the observer, and the vectors in the xy plane for the  *
 *          intercept point (where the line of sight for the observer crosses *
 *          the xy plane), and the dummy variable of integration.             *
 *  Outputs:                                                                  *
 *      dpsi (long double):                                                   *
 *          The partial derivative of the Fresnel phase with respect to phi.  *
 *  Called Functions:                                                         *
 *      src/math/                                                             *
 *          tmpl_LDouble_Hypot3:                                              *
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
 *      If we write:                                                          *
 *                                                                            *
 *          dx = R_x - rho_x                                                  *
 *          dy = R_y - rho_y                                                  *
 *                                                                            *
 *          ux = R_x - rho0_x                                                 *
 *          uy = R_y - rho0_y                                                 *
 *                                                                            *
 *      We may rewrite this as follows:                                       *
 *                                                                            *
 *                    -                                                  -    *
 *                   | dx * rho_y - dy * rho_x   -ux * rho_y + uy * rho_x |   *
 *          psi' = k | ----------------------- + ------------------------ |   *
 *                   |      || R - rho ||             || R - rho0 ||      |   *
 *                    -                                                  -    *
 *                                                                            *
 *      This final expression is computed.                                    *
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
 *  1.) tmpl_cyl_fresnel_geometry_ldouble.h:                                  *
 *          Location of the tmpl_CylFresnelGeometryLongDouble typedef.        *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 23, 2025                                                  *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2025/11/10: Ryan Maguire                                                  *
 *      Rewrote to use tmpl_CylFresnelGeometryLongDouble struct.              *
 ******************************************************************************/

/*  The cylindrical Fresnel geometry struct.                                  */
#include <libtmpl/include/types/tmpl_cyl_fresnel_geometry_ldouble.h>

/*  Forward declaration / function prototype.                                 */
extern long double
tmpl_LDouble_Cyl_Fresnel_dPsi_dPhi(
    long double k, const tmpl_CylFresnelGeometryLongDouble * const geo
);

/*  Tell the compiler about the L2 norm function, Hypot3.                     */
extern long double
tmpl_LDouble_Hypot3(long double x, long double y, long double z);

/*  Computes the partial derivative of the Fresnel phase with respect to phi. */
long double
tmpl_LDouble_Cyl_Fresnel_dPsi_dPhi(
    long double k, const tmpl_CylFresnelGeometryLongDouble * const geo
)
{
    /*  The relative position vector, u, of the observer from the ring        *
     *  intercept point. Since rho0 lies in the plane, there is no z part.    */
    const long double ux = geo->position.dat[0] - geo->intercept.dat[0];
    const long double uy = geo->position.dat[1] - geo->intercept.dat[1];
    const long double uz = geo->position.dat[2];

    /*  The difference between the "dummy" point in the plane, rho, that is   *
     *  integrated over, and the orthogonal projection of the position vector *
     *  for the observer, R, onto the ring plane.                             */
    const long double dx = geo->position.dat[0] - geo->dummy.dat[0];
    const long double dy = geo->position.dat[1] - geo->dummy.dat[1];

    /*  We need the distances from R to rho and R to rho0. These can be       *
     *  computed with the Hypot3 function.                                    */
    const long double rho_dist = tmpl_LDouble_Hypot3(dx, dy, uz);
    const long double rho0_dist = tmpl_LDouble_Hypot3(ux, uy, uz);

    /*  The derivative is given by:                                           *
     *                                                                        *
     *                -                                                   -   *
     *               |  dx * rho_y - dy * rho_x   -ux * rho_y + uy * rho_x |  *
     *      psi' = k | ------------------------ + ------------------------ |  *
     *               |      || R - rho ||              || R - rho0 ||      |  *
     *                -                                                   -   *
     *                                                                        *
     *  Call the left expression "left" and the right one "right." Compute.   */
    const long double left = dx * geo->dummy.dat[1] - dy * geo->dummy.dat[0];
    const long double right = uy * geo->dummy.dat[0] - ux * geo->dummy.dat[1];

    /*  The output is the sum scaled by the wavenumber, k.                    */
    return k * (left / rho_dist + right / rho0_dist);
}
/*  End of tmpl_LDouble_Cyl_Fresnel_dPsi_dPhi.                                */
