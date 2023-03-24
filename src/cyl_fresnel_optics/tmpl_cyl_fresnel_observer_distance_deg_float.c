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
 *                tmpl_cyl_fresnel_observer_distance_deg_float                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the distance from a point in the plane to the observer.      *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Cyl_Fresnel_Observer_Distance_Deg                          *
 *  Purpose:                                                                  *
 *      Given a point (r cos(phi), r sin(phi), 0) in the ring plane, and      *
 *      (rx, ry, rz) in space, compute the distance between the points. This  *
 *      is usually the distance from the observer to a particular point of    *
 *      interest in the plane.                                                *
 *  Arguments:                                                                *
 *      r (float):                                                            *
 *          The radius of the point in the plane.                             *
 *      phi (float):                                                          *
 *          The azimuthal angle of the point, in degrees.                     *
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
 *      tmpl_Float_SinCosd (tmpl_math.h):                                     *
 *          Computes sine and cosine, in degrees.                             *
 *      tmpl_Float_Sqrt (tmpl_math.h):                                        *
 *          Computes the square root of a positive number.                    *
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
 *  Notes:                                                                    *
 *      Angles must be in degrees. Lengths can be in whatever units, but they *
 *      must be the same units.                                               *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file with cosine and sqrt.                                 *
 *  2.) tmpl_cyl_fresnel_optics.h:                                            *
 *          Header file where the prototype is given.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 22, 2023                                                *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/03/23: Ryan Maguire                                                  *
 *      Created file.                                                         *
 ******************************************************************************/

/*  Trig functions and square root found here.                                */
#include <libtmpl/include/tmpl_math.h>

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_cyl_fresnel_optics.h>

/*  Function for computing the distance from an observer to a plane point.    */
float
tmpl_Float_Cyl_Fresnel_Observer_Distance_Deg(float r, float phi,
                                             float rx, float ry, float rz)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    float sin_phi, cos_phi, x, y, dx, dy;

    /*  Simultaneously compute sine and cosine of phi.                        */
    tmpl_Float_SinCosd(phi, &sin_phi, &cos_phi);

    /*  Compute the Cartesian coordinates of the ring point.                  */
    x = r * cos_phi;
    y = r * sin_phi;

    /*  Compute the distances in the individual components.                   */
    dx = x - rx;
    dy = y - ry;

    /*  The largest a float can be before the square overflows is roughly     *
     *  10^19. 10^19 kilometers is about 10 times the diameter of the Milky   *
     *  way galaxy. While such large scales are possible in astronomical      *
     *  study, it is highly unlikely that an observer to the ring plane would *
     *  be that far away. Because of this we can just use the standard        *
     *  Pythagorean formula without worrying about overflow.                  */
    return tmpl_Float_Sqrt(dx*dx + dy*dy + rz*rz);
}
/*  End of tmpl_Float_Cyl_Fresnel_Observer_Distance.                          */
