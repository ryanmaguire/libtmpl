/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
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
 *  Purpose:                                                                  *
 *      Computes the cross product of two vectors.                            *
 ******************************************************************************
 *  Author:     Ryan Maguire, Wellesley College                               *
 *  Date:       December 21, 2020                                             *
 ******************************************************************************/

/*  Function prototype and three-vector typedef found here.                   */
#include <libtmpl/include/tmpl_euclidean_spatial_geometry.h>

/*  Function for computing an orthogonal vector to the given input.           */
tmpl_ThreeVector
tmpl_Orthogonal_ThreeVector(tmpl_ThreeVector P)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    double Px, Py, x, y, z;
    tmpl_ThreeVector out;

    /*  Extract the x and y components from P. We won't need the z part.      */
    Px = tmpl_ThreeVector_X(P);
    Py = tmpl_ThreeVector_Y(P);

    /*  If the x component is zero, (1,0,0) will be orthogonal to P since the *
     *  dot product will be 1*0 + 0*Py + 0*Pz = 0. Return (1,0,0).            */
    if (Px == 0.0)
    {
        x = 1.0;
        y = 0.0;
        z = 0.0;
    }
    else
    {
        /*  Similarly, if the y component is zero, return (0,1,0).            */
        if (Py == 0.0)
        {
            x = 0.0;
            y = 1.0;
            z = 0.0;
        }

        /*  If both the x and y components are non-zero, we can set the       *
         *  output to (1, -Px/Py, 0), which is orthogonal to P.               */
        else
        {
            x = 1.0;
            y = -Px/Py;
            z = 0.0;
        }
        /*  End of if (Py == 0.0).                                            */
    }
    /*  End of if (Px == 0.0).                                                */

    out = tmpl_ThreeVector_Rect(x, y, z);
    return out;
}
/*  End of tmpl_Orthogonal_ThreeVector.                                */
