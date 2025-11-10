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
 *                        tmpl_cyl_fresnel_psi_double                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the cylindrical Fresnel kernel.                              *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Cyl_Fresnel_Psi                                           *
 *  Purpose:                                                                  *
 *      Computes the Cylindrical Fresnel kernel from the position vectors of  *
 *      the observer, the ring intercept point, and the dummy varible of      *
 *      integration.                                                          *
 *  Arguments:                                                                *
 *      k (double):                                                           *
 *          The wavenumber, in the reciprocal of the units of geo->intercept. *
 *      geo (const tmpl_CylFresnelGeometryDouble * const):                    *
 *          The geometry of the observation. This contains the position       *
 *          vector for the observer, and the vectors in the xy plane for the  *
 *          intercept point (where the line of sight for the observer crosses *
 *          the xy plane), and the dummy variable of integration.             *
 *  Outputs:                                                                  *
 *      psi (double):                                                         *
 *          The Fresnel kernel.                                               *
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
 *      We compute this final expression using the hypot3 function and the    *
 *      standard formula for the dot product in three dimensions.             *
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
tmpl_Double_Cyl_Fresnel_Psi(
    double k, const tmpl_CylFresnelGeometryDouble * const geo
);

/*  Tell the compiler about the L2 norm function, Hypot3.                     */
extern double tmpl_Double_Hypot3(double x, double y, double z);

/*  Computes the Fresnel kernel, psi, with vectors in Cartesian coordinates.  */
double
tmpl_Double_Cyl_Fresnel_Psi(
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

    /*  If we let un denote the unit normal vector in the direction of u, the *
     *  Fresnel kernel is given by:                                           *
     *                                                                        *
     *      psi = k (|| R - rho || - un . (R - rho))                          *
     *                                                                        *
     *  Since un = u / ||u||, we can compute this dot product via:            *
     *                                                                        *
     *      un . (R - rho) = u . (R - rho) / || u ||                          *
     *                                                                        *
     *  Compute || u || and the dot product.                                  */
    const double norm_u = tmpl_Double_Hypot3(ux, uy, uz);
    const double dot = (ux*dx + uy*dy + uz*uz) / norm_u;

    /*  The magnitute || R - rho || can be computed using the hypot3 function.*/
    const double mag = tmpl_Double_Hypot3(dx, dy, uz);

    /*  The output is the difference scaled by the wavenumber, k.             */
    return k * (mag - dot);
}
/*  End of tmpl_Double_Cyl_Fresnel_Psi.                                       */
