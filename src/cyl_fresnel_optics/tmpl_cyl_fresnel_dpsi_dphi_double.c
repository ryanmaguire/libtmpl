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
 *                     tmpl_cyl_fresnel_dpsi_dphi_double                      *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the partial derivative of the cylindrical Fresnel kernel     *
 *      with respect to the azimuthal angle, phi.                             *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Cyl_Fresnel_dPsi_dPhi                                     *
 *  Purpose:                                                                  *
 *      Computes the partial derivative of psi, the Fresnel kernel, with      *
 *      respect to phi, the azimuth angle.                                    *
 *  Arguments:                                                                *
 *      k (double):                                                           *
 *          The wavenumber, in the reciprocal of the units of rho.            *
 *      rho (const tmpl_TwoVectorDouble * const):                             *
 *          The dummy variable of integration, a point in the ring plane.     *
 *          This vector is expressed in terms of its Cartesian coordinates.   *
 *      rho0 (const tmpl_TwoVectorDouble * const):                            *
 *          The point of interest in the plane, in the same units as rho.     *
 *          This vector is given in terms of its Cartesian coordinates.       *
 *      R (cnst tmpl_ThreeVectorDouble * TMPL_RESTRICT const):                *
 *          The position vector for the observer. Same units as rho and rho0, *
 *          and also given in terms of its Cartesian coordinates.             *
 *  Outputs:                                                                  *
 *      dpsi (double):                                                        *
 *          The partial derivative of the Fresnel kernel with respect to phi. *
 *  Called Functions:                                                         *
 *      src/math/                                                             *
 *          tmpl_Double_Hypot3:                                               *
 *              Computes the magnitude of the vector (x, y, z).               *
 *  Method:                                                                   *
 *      Use the formula for the Fresnel kernel. The Fresnel transform is:     *
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
 *      rho0, and the xy plane). The Fresnel kernel is the psi quantity, it   *
 *      is purely geometric and given by:                                     *
 *                                                                            *
 *                   -                                          -             *
 *                  |                    R - rho0                |            *
 *          psi = k | || R - rho || - -------------- . (R - rho) |            *
 *                  |                 || R - rho0 ||             |            *
 *                   -                                          -             *
 *                                                                            *
 *      Where k is the wavenumber, in reciprocal units of the wavelength, L.  *
 *      By labeling u = R - rho0, and un = u / || u ||, the unit normal in    *
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
 *                   | (R - rho) . rho'            |                          *
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
 *                    -                                                   -   *
 *                   | -dx * rho_y + dy * rho_x   -ux * rho_y + uy * rho_x |  *
 *          psi' = k | ------------------------ + ------------------------ |  *
 *                   |      || R - rho ||              || R - rho0 ||      |  *
 *                    -                                                   -   *
 *                                                                            *
 *      This final expression is computed.                                    *
 *  Notes:                                                                    *
 *      1.) All vectors are given in Cartesian coordinates.                   *
 *      2.) There are no checks for NULL pointers. It is assumed that rho,    *
 *          rho0, and R are valid pointers to 2D and 3D vectors, respectively.*
 *      3.) Since R is the only pointer to a 3D vector, it is declared with   *
 *          the "restrict" qualifier. On compilers lacking restrict support,  *
 *          the TMPL_RESTRICT macro expands to an empty expression.           *
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
 *  1.) tmpl_config.h:                                                        *
 *          Header file with TMPL_RESTRICT.                                   *
 *  2.) tmpl_vec2_double.h:                                                   *
 *          Location of the tmpl_TwoVectorDouble typedef.                     *
 *  2.) tmpl_vec3_double.h:                                                   *
 *          Location of the tmpl_ThreeVectorDouble typedef.                   *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 23, 2025                                                  *
 ******************************************************************************/

/*  TMPL_RESTRICT found here.                                                 */
#include <libtmpl/include/tmpl_config.h>

/*  vec2 and vec3 typedefs provided here.                                     */
#include <libtmpl/include/types/tmpl_vec2_double.h>
#include <libtmpl/include/types/tmpl_vec3_double.h>

/*  Forward declaration / function prototype.                                 */
extern double
tmpl_Double_Cyl_Fresnel_dPsi_dPhi(
    double k,
    const tmpl_TwoVectorDouble * const rho,
    const tmpl_TwoVectorDouble * const rho0,
    const tmpl_ThreeVectorDouble * TMPL_RESTRICT const R
);

/*  Tell the compiler about the L2 norm function, Hypot3.                     */
extern double tmpl_Double_Hypot3(double x, double y, double z);

/*  Computes the partial derivative of the Fresnel kernel with respect to phi.*/
double
tmpl_Double_Cyl_Fresnel_dPsi_dPhi(
    double k,
    const tmpl_TwoVectorDouble * const rho,
    const tmpl_TwoVectorDouble * const rho0,
    const tmpl_ThreeVectorDouble * TMPL_RESTRICT const R
)
{
    /*  The relative position vector, u, of the observer from the ring        *
     *  intercept point. Since rho0 lies in the plane, there is no z part.    */
    const double ux = R->dat[0] - rho0->dat[0];
    const double uy = R->dat[1] - rho0->dat[1];
    const double uz = R->dat[2];

    /*  The difference between the "dummy" point in the plane, rho, that is   *
     *  integrated over, and the orthogonal projection of the position vector *
     *  for the observer, R, onto the ring plane.                             */
    const double dx = R->dat[0] - rho->dat[0];
    const double dy = R->dat[1] - rho->dat[1];

    /*  We need the distances from R to rho and R to rho0. These can be       *
     *  computed with the Hypot3 function.                                    */
    const double rho_dist = tmpl_Double_Hypot3(dx, dy, uz);
    const double rho0_dist = tmpl_Double_Hypot3(ux, uy, uz);

    /*  The derivative is given by:                                           *
     *                                                                        *
     *                -                                                   -   *
     *               | -dx * rho_y + dy * rho_x   -ux * rho_y + uy * rho_x |  *
     *      psi' = k | ------------------------ + ------------------------ |  *
     *               |      || R - rho ||              || R - rho0 ||      |  *
     *                -                                                   -   *
     *                                                                        *
     *  Call the left expression "left" and the right one "right." Compute.   */
    const double left = (-dx * rho->dat[1] + dy * rho->dat[0]) / rho_dist;
    const double right = (-ux * rho->dat[1] + uy * rho->dat[0]) / rho0_dist;

    /*  The output is the sum scaled by the wavenumber, k.                    */
    return k * (left + right);
}
/*  End of tmpl_Double_Cyl_Fresnel_dPsi_dPhi.                                 */
