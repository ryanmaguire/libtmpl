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
 *                  tmpl_cyl_fresnel_observer_distance_float                  *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the distance from a point in the plane to the observer.      *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Cyl_Fresnel_Observer_Distance                              *
 *  Purpose:                                                                  *
 *      Given a point (r cos(phi), r sin(phi), 0) in the ring plane, and      *
 *      (rx, ry, rz) in space, compute the distance between the points. This  *
 *      is usually the distance from the observer to a particular point of    *
 *      interest in the plane.                                                *
 *  Arguments:                                                                *
 *      r (float):                                                            *
 *          The radius of the point in the plane.                             *
 *      phi (float):                                                          *
 *          The azimuthal angle of the point, in radians.                     *
 *      rx (float):                                                           *
 *          The x component of the observer.                                  *
 *      ry (float):                                                           *
 *          The y component of the observer.                                  *
 *      rz (float):                                                           *
 *          The z component of the observer.                                  *
 *  Outputs:                                                                  *
 *      dist (float):                                                         *
 *          The distance from the point to the observer.                      *
 *  Called Functions:                                                         *
 *      src/math/                                                             *
 *          tmpl_Float_SinCos:                                                *
 *              Computes sine and cosine, in radians.                         *
 *          tmpl_Float_Hypot3:                                                *
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
 *      1.) Angles must be in radians.                                        *
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
 *  2025/06/18: Ryan Maguire                                                  *
 *      Removed explicit includes, replaced with forward declarations.        *
 ******************************************************************************/

/*  Forward declaration / function prototype.                                 */
extern float
tmpl_Float_Cyl_Fresnel_Observer_Distance(float r, float phi,
                                         float rx, float ry, float rz);

/*  Tell the compiler about the SinCos and Hypot3 functions.                  */
extern void tmpl_Float_SinCos(float t, float *sin_t, float *cos_t);
extern float tmpl_Float_Hypot3(float x, float y, float z);

/*  Function for computing the distance from an observer to a plane point.    */
float
tmpl_Float_Cyl_Fresnel_Observer_Distance(float r, float phi,
                                         float rx, float ry, float rz)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    float sin_phi, cos_phi, x, y, dx, dy;

    /*  Simultaneously compute sine and cosine of phi, in radians.            */
    tmpl_Float_SinCos(phi, &sin_phi, &cos_phi);

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
     *      The largest a float can be before the square overflows is roughly *
     *      10^19. 10^19 kilometers is about 10 times the diameter of the     *
     *      Milky way galaxy. While such large scales are possible in         *
     *      astronomical study, it is highly unlikely that an observer to the *
     *      ring plane would be that far away. Because of this one might      *
     *      prefer to use the sqrt function directly. We use the safer Hypot3 *
     *      function, but inlining sqrt(dx^2 + dy^2 + rz^2) can give a small  *
     *      speed boost (a few percent).                                      */
    return tmpl_Float_Hypot3(dx, dy, rz);
}
/*  End of tmpl_Float_Cyl_Fresnel_Observer_Distance.                          */
