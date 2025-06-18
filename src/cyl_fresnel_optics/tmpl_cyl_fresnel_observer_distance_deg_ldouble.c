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
 *               tmpl_cyl_fresnel_observer_distance_deg_ldouble               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the distance from a point in the plane to the observer.      *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Cyl_Fresnel_Observer_Distance_Deg                        *
 *  Purpose:                                                                  *
 *      Given a point (r cos(phi), r sin(phi), 0) in the ring plane, and      *
 *      (rx, ry, rz) in space, compute the distance between the points. This  *
 *      is usually the distance from the observer to a particular point of    *
 *      interest in the plane.                                                *
 *  Arguments:                                                                *
 *      r (long double):                                                      *
 *          The radius of the point in the plane.                             *
 *      phi (long double):                                                    *
 *          The azimuthal angle of the point, in degrees.                     *
 *      rx (long double):                                                     *
 *          The x component of the observer.                                  *
 *      ry (long double):                                                     *
 *          The y component of the observer.                                  *
 *      rz (long double):                                                     *
 *          The z component of the observer.                                  *
 *  Outputs:                                                                  *
 *      dist (long double):                                                   *
 *          The distance from the point to the observer.                      *
 *  Called Functions:                                                         *
 *      src/math/                                                             *
 *          tmpl_LDouble_SinCosd:                                             *
 *              Computes sine and cosine, in degrees.                         *
 *          tmpl_LDouble_Hypot3:                                              *
 *              Computes the length of the vector (x, y, z).                  *
 *  Method:                                                                   *
 *      Use basic Euclidean geometry and invoke Pythagoras. We have:          *
 *                                                                            *
 *          P = (r cos(phi), r sin(phi), 0)                                   *
 *          Q = (rx, ry, rz)                                                  *
 *                                                                            *
 *          dx = rx - r cos(phi)                                              *
 *          dy = ry - r sin(phi)                                              *
 *          dz = rz                                                           *
 *                                                                            *
 *          dist = sqrt(dx^2 + dy^2 + dz^2)                                   *
 *                                                                            *
 *      This distance is computed using the Hypot3 function.                  *
 *  Notes:                                                                    *
 *      1.) Angles must be in degrees.                                        *
 *      2.) Lengths can be in whatever units, but they must be the same units.*
 *      3.) There are no checks for NaN or infinity.                          *
 *      4.) This function computes the distance using the Hypot3 function,    *
 *          which safely handles both small and large inputs to avoid         *
 *          underflow and overflow, respectively. This is likely not needed   *
 *          for physically realistic inputs, and a small speed boost can be   *
 *          gained by replacing Hypot3 with Sqrt.                             *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  None.                                                                     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 22, 2023                                                *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/03/23: Ryan Maguire                                                  *
 *      Created file.                                                         *
 *  2025/06/17: Ryan Maguire                                                  *
 *      Removed explicit includes, replaced with forward declarations.        *
 ******************************************************************************/

/*  Forward declaration / function prototype.                                 */
extern long double
tmpl_LDouble_Cyl_Fresnel_Observer_Distance_Deg(long double r,
                                               long double phi,
                                               long double rx,
                                               long double ry,
                                               long double rz);

/*  Tell the compiler about the SinCosd and Hypot3 functions.                 */
extern void
tmpl_LDouble_SinCosd(long double t, long double *sin_t, long double *cos_t);

extern long double
tmpl_LDouble_Hypot3(long double x, long double y, long double z);

/*  Function for computing the distance from an observer to a plane point.    */
long double
tmpl_LDouble_Cyl_Fresnel_Observer_Distance_Deg(long double r,
                                               long double phi,
                                               long double rx,
                                               long double ry,
                                               long double rz)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    long double sin_phi, cos_phi, x, y, dx, dy;

    /*  Simultaneously compute sine and cosine of phi, in degrees.            */
    tmpl_LDouble_SinCosd(phi, &sin_phi, &cos_phi);

    /*  Compute the Cartesian coordinates of the ring point.                  */
    x = r * cos_phi;
    y = r * sin_phi;

    /*  Compute the distances in the individual components.                   */
    dx = x - rx;
    dy = y - ry;

    /*  Now that everything is in Cartesian coordinates, we may compute the   *
     *  distance between (x, y, z) and (r cos(phi), r sin(phi), 0) using the  *
     *  Hypot3 function, which uses the Pythagorean formula.                  *
     *                                                                        *
     *  Note:                                                                 *
     *      No physical system could possibly have dx, dy, or rz so large     *
     *      that the sum of the squares may overflow. The system would need   *
     *      to have distances that are roughly 10^125 times the radius of the *
     *      observable universe for the sum of the squares to exceed          *
     *      2^(2^10 - 1), the maximum value for double precision. You would   *
     *      need distances that are roughly 10^2438 times the radius of the   *
     *      universe for the sum of the squares to exceed the maximum value   *
     *      allowed for 80-bit extended precision numbers, which is how long  *
     *      double is implemented on many machines. Because of this, one may  *
     *      safely compute the distance directly by using                     *
     *      sqrt(dx^2 + dy^2 + rz^2). This routine uses the safer Hypot3      *
     *      function, but a small speed boost may be gained by inlining the   *
     *      square root call directly.                                        */
    return tmpl_LDouble_Hypot3(dx, dy, rz);
}
/*  End of tmpl_LDouble_Cyl_Fresnel_Observer_Distance_Deg.                    */
