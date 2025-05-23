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
 *                        tmpl_cyl_fresnel_psi_ldouble                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the cylindrical Fresnel kernel.                              *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Cyl_Fresnel_Psi                                          *
 *  Purpose:                                                                  *
 *      Computes the Cylindrical Fresnel kernel from the position vectors of  *
 *      the observer, the ring intercept point, and the dummy varible of      *
 *      integration.                                                          *
 *  Arguments:                                                                *
 *      k (long double):                                                      *
 *          The wavenumber, in the reciprocal of the units of rho.            *
 *      rho (const tmpl_TwoVectorLongDouble * const):                         *
 *          The dummy variable of integration, a point in the ring plane.     *
 *          This vector is expressed in terms of its Cartesian coordinates.   *
 *      rho0 (const tmpl_TwoVectorLongDouble * const):                        *
 *          The point of interest in the plane, in the same units as rho.     *
 *          This vector is given in terms of its Cartesian coordinates.       *
 *      R (cnst tmpl_ThreeVectorLongDouble * TMPL_RESTRICT const):            *
 *          The position vector for the observer. Same units as rho and rho0, *
 *          and also given in terms of its Cartesian coordinates.             *
 *  Outputs:                                                                  *
 *      psi (long double):                                                    *
 *          The Fresnel kernel.                                               *
 *  Called Functions:                                                         *
 *      src/math/                                                             *
 *          tmpl_LDouble_Hypot3:                                              *
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
 *  2.) tmpl_vec2_ldouble.h:                                                  *
 *          Location of the tmpl_TwoVectorLongDouble typedef.                 *
 *  2.) tmpl_vec3_ldouble.h:                                                  *
 *          Location of the tmpl_ThreeVectorLongDouble typedef.               *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 23, 2025                                                  *
 ******************************************************************************/

/*  TMPL_RESTRICT found here.                                                 */
#include <libtmpl/include/tmpl_config.h>

/*  vec2 and vec3 typedefs provided here.                                     */
#include <libtmpl/include/types/tmpl_vec2_ldouble.h>
#include <libtmpl/include/types/tmpl_vec3_ldouble.h>

/*  Forward declaration / function prototype.                                 */
extern long double
tmpl_LDouble_Cyl_Fresnel_Psi(
    long double k,
    const tmpl_TwoVectorLongDouble * const rho,
    const tmpl_TwoVectorLongDouble * const rho0,
    const tmpl_ThreeVectorLongDouble * TMPL_RESTRICT const R
);

/*  Tell the compiler about the L2 norm function, Hypot3.                     */
extern long double
tmpl_LDouble_Hypot3(long double x, long double y, long double z);

/*  Computes the Fresnel kernel, psi, with vectors in Cartesian coordinates.  */
long double
tmpl_LDouble_Cyl_Fresnel_Psi(
    long double k,
    const tmpl_TwoVectorLongDouble * const rho,
    const tmpl_TwoVectorLongDouble * const rho0,
    const tmpl_ThreeVectorLongDouble * TMPL_RESTRICT const R
)
{
    /*  The relative position vector, u, of the observer from the ring        *
     *  intercept point. Since rho0 lies in the plane, there is no z part.    */
    const long double ux = R->dat[0] - rho0->dat[0];
    const long double uy = R->dat[1] - rho0->dat[1];
    const long double uz = R->dat[2];

    /*  The difference between the "dummy" point in the plane, rho, that is   *
     *  integrated over, and the orthogonal projection of the position vector *
     *  for the observer, R, onto the ring plane.                             */
    const long double dx = R->dat[0] - rho->dat[0];
    const long double dy = R->dat[1] - rho->dat[1];

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
    const long double norm_u = tmpl_LDouble_Hypot3(ux, uy, uz);
    const long double dot = (ux*dx + uy*dy + uz*uz) / norm_u;

    /*  The magnitute || R - rho || can be computed using the hypot3 function.*/
    const long double mag = tmpl_LDouble_Hypot3(dx, dy, uz);

    /*  The output is the difference scaled by the wavenumber, k.             */
    return k * (mag - dot);
}
/*  End of tmpl_LDouble_Cyl_Fresnel_Psi.                                      */
